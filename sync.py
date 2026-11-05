"""Sync one latest Accepted solution per LeetCode problem. Python 3.11+, no deps."""

import argparse
import json
import os
import re
import sys
import time
from datetime import datetime, timezone
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.parse import urlencode
from urllib.request import Request, build_opener, HTTPRedirectHandler


STATE_FILE = ".leetcode-sync.json"
EXTENSIONS = {
    "python": "py", "python3": "py", "java": "java", "cpp": "cpp",
    "c": "c", "csharp": "cs", "javascript": "js", "typescript": "ts",
    "golang": "go", "rust": "rs", "ruby": "rb", "swift": "swift",
    "kotlin": "kt", "scala": "scala", "php": "php", "dart": "dart",
    "mysql": "sql", "mssql": "sql", "oraclesql": "sql", "postgresql": "sql",
    "bash": "sh", "racket": "rkt", "erlang": "erl", "elixir": "ex",
    "r": "r", "pandas": "py",
}
DETAIL_QUERY = """
query submissionDetails($submissionId: Int!) {
  submissionDetails(submissionId: $submissionId) {
    code statusCode timestamp lang { name }
    question { titleSlug difficulty }
  }
}
"""


class SyncError(Exception):
    """An actionable failure that is safe to display without credentials."""


class NoRedirects(HTTPRedirectHandler):
    # Never forward the session cookie to another URL, including login redirects.
    def redirect_request(self, req, fp, code, msg, headers, newurl):
        return None


class LeetCode:
    def __init__(self, session, csrf):
        if not session or not csrf:
            raise SyncError("Set LEETCODE_SESSION and LEETCODE_CSRF_TOKEN first.")
        if any(char in session + csrf for char in "\r\n;"):
            raise SyncError("Use raw cookie values, not a complete Cookie header.")
        self.headers = {
            "Cookie": f"LEETCODE_SESSION={session}; csrftoken={csrf}",
            "x-csrftoken": csrf,
            "Content-Type": "application/json",
            "Referer": "https://leetcode.com/",
            "Origin": "https://leetcode.com",
            "User-Agent": "Mozilla/5.0 LeetCodeGitHubSync/1.0",
        }
        self.opener = build_opener(NoRedirects())
        self.last_request = 0.0

    def request(self, path, payload=None):
        body = None if payload is None else json.dumps(payload).encode()
        for attempt in range(4):
            time.sleep(max(0, 1 - (time.monotonic() - self.last_request)))
            self.last_request = time.monotonic()
            request = Request("https://leetcode.com" + path, body, self.headers)
            try:
                with self.opener.open(request, timeout=30) as response:
                    result = json.load(response)
                if not isinstance(result, dict):
                    raise SyncError("LeetCode returned an unexpected response.")
                return result
            except HTTPError as error:
                if error.code in (401, 403):
                    raise SyncError(
                        f"LeetCode HTTP {error.code}: session expired or access blocked. "
                        "Refresh the cookies; if it persists, try running locally."
                    ) from None
                if error.code != 429 and not 500 <= error.code < 600:
                    raise SyncError(f"LeetCode HTTP {error.code}; no checkpoint saved.") from None
                delay = error.headers.get("Retry-After", "")
                delay = min(int(delay), 120) if delay.isdigit() else 2 ** (attempt + 1)
            except (URLError, TimeoutError):
                delay = 2 ** (attempt + 1)
            except (ValueError, UnicodeError):
                raise SyncError("LeetCode returned invalid JSON; no checkpoint saved.") from None
            if attempt < 3:
                time.sleep(delay)
        raise SyncError("LeetCode request failed after 4 attempts; try again later.")

    def graphql(self, query, variables=None):
        result = self.request("/graphql/", {"query": query, "variables": variables or {}})
        if result.get("errors") or not isinstance(result.get("data"), dict):
            raise SyncError("LeetCode GraphQL failed. Check login or endpoint changes.")
        return result["data"]

    def username(self):
        status = self.graphql("query { userStatus { isSignedIn username } }").get("userStatus")
        if not status or not status.get("isSignedIn") or not status.get("username"):
            raise SyncError("LeetCode session is not signed in; refresh the cookies.")
        return status["username"]

    def history(self, checkpoint):
        """Page through the account's complete history, newest first."""
        offset, lastkey = 0, ""
        previous_page = None
        while True:
            params = urlencode({"offset": offset, "limit": 20, "lastkey": lastkey})
            page = self.request("/api/submissions/?" + params)
            rows = page.get("submissions_dump")
            if not isinstance(rows, list) or not isinstance(page.get("has_next"), bool):
                raise SyncError("Unexpected submission history; refusing an incomplete import.")
            signature = tuple(str(row["id"]) for row in rows)
            if signature == previous_page or (not rows and page["has_next"]):
                raise SyncError("Submission pagination stalled; no checkpoint saved.")
            previous_page = signature
            for row in rows:
                if str(row["id"]) == checkpoint:
                    return
                yield row
            if not page["has_next"]:
                return
            offset += len(rows)
            lastkey = page.get("last_key", "")

    def detail(self, submission_id):
        detail = self.graphql(DETAIL_QUERY, {"submissionId": int(submission_id)}).get("submissionDetails")
        if not detail or detail.get("statusCode") != 10 or not detail.get("code"):
            raise SyncError(f"Cannot read Accepted source for submission {submission_id}.")
        return detail


def collect(history):
    """Keep only the newest Accepted per problem; don't checkpoint pending work."""
    accepted = {}
    newest_id = None
    pending = False
    for row in history:
        status = row.get("status_display")
        if not status or row.get("is_pending") or status in {"Pending", "Judging", "Started"}:
            pending = True
        if status != "Accepted":
            continue
        if newest_id is None or int(row["id"]) > int(newest_id):
            newest_id = str(row["id"])
        slug = row["title_slug"]
        if not re.fullmatch(r"[a-z0-9]+(?:-[a-z0-9]+)*", slug):
            raise SyncError("Invalid problem slug in submission history.")
        if slug not in accepted or int(row["id"]) > int(accepted[slug]["id"]):
            accepted[slug] = row
    return accepted, newest_id, pending


def source_path(root, relative):
    path = root / relative
    if not path.resolve().is_relative_to(root.resolve() / "solutions"):
        raise SyncError("Solution path must stay inside solutions/.")
    return path


def save_solution(root, row, detail, previous):
    slug = row["title_slug"]
    if detail["question"]["titleSlug"] != slug:
        raise SyncError("Submission detail does not match its problem.")
    difficulty = detail["question"].get("difficulty")
    if difficulty not in {"Easy", "Medium", "Hard"}:
        raise SyncError("Missing or invalid problem difficulty; no checkpoint saved.")
    directory = f"solutions/{difficulty.lower()}/{slug}"
    language = detail["lang"]["name"]
    extension = EXTENSIONS.get(language, "txt")
    relative = f"{directory}/solution.{extension}"
    path = source_path(root, relative)
    # Validate the old path before mutating any files (state is repository input).
    old_path = source_path(root, previous["path"]) if previous else None
    readme_path = source_path(root, f"{directory}/README.md")
    path.parent.mkdir(parents=True, exist_ok=True)
    code = detail["code"]
    path.write_text(code if code.endswith("\n") else code + "\n", encoding="utf-8")
    if old_path and old_path != path:
        old_path.unlink(missing_ok=True)
    submitted = datetime.fromtimestamp(int(detail["timestamp"]), timezone.utc).isoformat()
    readme = (
        f"# {row['title']}\n\n"
        f"[Problem](https://leetcode.com/problems/{slug}/) · "
        f"[Accepted submission](https://leetcode.com/submissions/detail/{row['id']}/)\n\n"
        f"Difficulty: {difficulty}  \nLanguage: {language}  \nSubmitted: {submitted}\n"
    )
    readme_path.write_text(readme, encoding="utf-8")
    return {"id": str(row["id"]), "path": relative}


def sync(client, root, dry_run=False):
    state_path = root / STATE_FILE
    state = json.loads(state_path.read_text()) if state_path.exists() else {
        "version": 1, "username": None, "checkpoint": None, "problems": {},
    }
    if state.get("version") != 1 or not isinstance(state.get("problems"), dict):
        raise SyncError("Unsupported sync state; restore a valid .leetcode-sync.json.")
    username = client.username()
    if state.get("username") not in (None, username):
        raise SyncError("LeetCode account differs from the saved sync state.")
    accepted, newest_id, pending = collect(client.history(state.get("checkpoint")))
    updated = 0
    for slug, row in sorted(accepted.items()):
        previous = state["problems"].get(slug)
        if previous and int(previous["id"]) >= int(row["id"]):
            continue
        detail = client.detail(row["id"])
        if not dry_run:
            state["problems"][slug] = save_solution(root, row, detail, previous)
        print(f"{'Would sync' if dry_run else 'Synced'} {slug} ({row['id']})")
        updated += 1
    if not dry_run:
        state["username"] = username
        if newest_id and not pending:
            state["checkpoint"] = newest_id
        temporary = state_path.with_suffix(".json.tmp")
        temporary.write_text(json.dumps(state, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        temporary.replace(state_path)
    print(f"{updated} solution(s) {'verified; no files written' if dry_run else 'synced'}.")
    if pending:
        print("Pending submissions found; retaining checkpoint to recheck their final verdict.")
    return updated


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dry-run", action="store_true", help="Fetch and verify without writing files")
    args = parser.parse_args()
    try:
        client = LeetCode(os.getenv("LEETCODE_SESSION", ""), os.getenv("LEETCODE_CSRF_TOKEN", ""))
        sync(client, Path(__file__).resolve().parent, args.dry_run)
    except (SyncError, OSError, ValueError, KeyError, TypeError) as error:
        # Don't print raw HTTP responses, URLs, or credentials.
        message = str(error) if isinstance(error, SyncError) else "Invalid data or local file error; checkpoint not advanced."
        print(f"Sync failed: {message}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
