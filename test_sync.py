"""Offline integration checks; never execute downloaded solution code."""

import io
import json
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from unittest.mock import Mock, patch
from urllib.error import HTTPError
from urllib.parse import parse_qs, urlparse

from sync import LeetCode, STATE_FILE, SyncError, collect, save_solution, sync


def submission(number, slug="two-sum", status="Accepted"):
    return {"id": number, "title_slug": slug, "title": slug.title(), "status_display": status}


def detail(slug="two-sum", lang="python3", difficulty="Easy"):
    return {
        "code": "# Example source\nprint('hello')\n\n", "statusCode": 10,
        "timestamp": 1700000000, "lang": {"name": lang},
        "question": {"titleSlug": slug, "difficulty": difficulty},
    }


class SyncTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.client = Mock()
        self.client.username.return_value = "test-user"
        self.client.detail.side_effect = lambda number: detail()

    def run_sync(self, rows, dry_run=False):
        self.client.history.return_value = iter(rows)
        with redirect_stdout(io.StringIO()):
            return sync(self.client, self.root, dry_run)

    def state(self):
        return json.loads((self.root / STATE_FILE).read_text())

    def test_import_one_latest_accepted_per_problem_and_repeat_without_work(self):
        self.client.detail.side_effect = lambda number: detail("two-sum" if number == 4 else "add-two-numbers")
        count = self.run_sync([
            submission(5, status="Wrong Answer"), submission(4), submission(3),
            submission(2, "add-two-numbers"), submission(1, status="Compile Error"),
        ])
        self.assertEqual(count, 2)
        self.assertEqual(self.client.detail.call_count, 2)
        self.assertEqual(self.state()["checkpoint"], "4")
        self.assertEqual(len(list(self.root.glob("solutions/*/*/solution.*"))), 2)
        original = (self.root / STATE_FILE).read_bytes()
        self.client.detail.reset_mock()
        self.assertEqual(self.run_sync([submission(5, status="Wrong Answer")]), 0)
        self.client.history.assert_called_with("4")
        self.client.detail.assert_not_called()
        self.assertEqual((self.root / STATE_FILE).read_bytes(), original)

    def test_new_accepted_replaces_language_without_leaving_duplicate(self):
        self.run_sync([submission(1)])
        self.client.detail.side_effect = lambda number: detail(lang="javascript")
        self.run_sync([submission(2)])
        directory = self.root / "solutions/easy/two-sum"
        self.assertFalse((directory / "solution.py").exists())
        self.assertTrue((directory / "solution.js").exists())
        self.assertEqual(self.state()["problems"]["two-sum"]["id"], "2")

    def test_groups_solutions_by_difficulty(self):
        for difficulty in ("Easy", "Medium", "Hard"):
            with self.subTest(difficulty=difficulty):
                slug = f"example-{difficulty.lower()}"
                result = save_solution(self.root, submission(1, slug), detail(slug, difficulty=difficulty), None)
                expected = f"solutions/{difficulty.lower()}/{slug}/solution.py"
                self.assertEqual(result["path"], expected)
                self.assertEqual((self.root / expected).read_text(), detail()["code"])

    def test_invalid_difficulty_does_not_write_or_checkpoint(self):
        self.client.detail.side_effect = lambda number: detail(difficulty="../escape")
        with self.assertRaises(SyncError):
            self.run_sync([submission(1)])
        self.assertEqual(list(self.root.iterdir()), [])

    def test_failure_does_not_advance_checkpoint_and_retry_completes(self):
        self.run_sync([submission(1)])
        original = (self.root / STATE_FILE).read_bytes()
        self.client.detail.side_effect = [detail(), SyncError("temporary failure")]
        with self.assertRaises(SyncError):
            self.run_sync([submission(3, "zzz"), submission(2)])
        self.assertEqual((self.root / STATE_FILE).read_bytes(), original)
        self.client.detail.side_effect = lambda number: detail("zzz" if number == 3 else "two-sum")
        self.assertEqual(self.run_sync([submission(3, "zzz"), submission(2)]), 2)
        self.assertEqual(self.state()["checkpoint"], "3")

    def test_pending_submission_is_revisited_after_verdict(self):
        self.run_sync([submission(1)])
        self.run_sync([submission(3), submission(2, "add-two-numbers", "Judging")])
        self.assertEqual(self.state()["checkpoint"], "1")
        self.client.detail.side_effect = lambda number: detail("add-two-numbers")
        self.assertEqual(self.run_sync([submission(3), submission(2, "add-two-numbers")]), 1)
        self.assertEqual(self.state()["checkpoint"], "3")

    def test_dry_run_fetches_source_without_writing(self):
        self.assertEqual(self.run_sync([submission(1)], dry_run=True), 1)
        self.client.detail.assert_called_once_with(1)
        self.assertEqual(list(self.root.iterdir()), [])

    def test_account_mismatch_stops_before_reading_history(self):
        self.run_sync([submission(1)])
        self.client.username.return_value = "someone-else"
        self.client.history.reset_mock()
        with self.assertRaises(SyncError):
            self.run_sync([])
        self.client.history.assert_not_called()

    def test_untrusted_paths_and_mismatched_detail_are_rejected(self):
        with self.assertRaises(SyncError):
            collect([submission(1, "../../escape")])
        with self.assertRaises(SyncError):
            save_solution(self.root, submission(1), detail(), {"path": "../outside"})
        with self.assertRaises(SyncError):
            save_solution(self.root, submission(1), detail("wrong-problem"), None)
        (self.root / "solutions").symlink_to(self.root.parent, target_is_directory=True)
        with self.assertRaises(SyncError):
            save_solution(self.root, submission(1), detail(), None)

    def test_history_paginates_and_stops_at_checkpoint(self):
        client = LeetCode("session", "csrf")
        client.request = Mock(side_effect=[
            {"submissions_dump": [submission(4), submission(3)], "has_next": True, "last_key": "next"},
            {"submissions_dump": [submission(2), submission(1)], "has_next": True},
        ])
        self.assertEqual([row["id"] for row in client.history("2")], [4, 3])
        query = parse_qs(urlparse(client.request.call_args.args[0]).query)
        self.assertEqual(query["offset"], ["2"])
        self.assertEqual(query["lastkey"], ["next"])

    def test_repeated_page_or_malformed_history_fails_closed(self):
        client = LeetCode("session", "csrf")
        page = {"submissions_dump": [submission(1)], "has_next": True}
        client.request = Mock(return_value=page)
        with self.assertRaises(SyncError):
            list(client.history(None))
        client.request.return_value = {"submissions_dump": []}
        with self.assertRaises(SyncError):
            list(client.history(None))

    @patch("sync.time.sleep")
    def test_rate_limit_retries_and_auth_failure_does_not(self, sleep):
        client = LeetCode("private-session", "private-csrf")
        response = Mock()
        response.__enter__ = Mock(return_value=io.StringIO('{"ok": true}'))
        response.__exit__ = Mock(return_value=False)
        limited = HTTPError("https://leetcode.com", 429, "limited", {"Retry-After": "2"}, None)
        client.opener.open = Mock(side_effect=[limited, response])
        self.assertEqual(client.request("/graphql/"), {"ok": True})
        self.assertEqual(client.opener.open.call_count, 2)
        client.opener.open.side_effect = HTTPError("https://leetcode.com", 403, "private-session", {}, None)
        with self.assertRaises(SyncError) as error:
            client.request("/graphql/")
        self.assertNotIn("private-session", str(error.exception))

    @patch("sync.time.sleep")
    def test_forbidden_response_reports_cause_without_response_or_secrets(self, sleep):
        client = LeetCode("private-session", "private-csrf")
        cases = [
            ({"cf-mitigated": "challenge"}, b"private-session", "Cloudflare challenge"),
            ({}, b"CSRF verification failed. private-csrf", "CSRF validation failed"),
        ]
        for headers, body, expected in cases:
            with self.subTest(expected=expected):
                client.opener.open = Mock(side_effect=HTTPError(
                    "https://leetcode.com", 403, "Forbidden", headers, io.BytesIO(body),
                ))
                with self.assertRaises(SyncError) as error:
                    client.request("/graphql/")
                self.assertIn(expected, str(error.exception))
                self.assertNotIn("private-session", str(error.exception))
                self.assertNotIn("private-csrf", str(error.exception))


if __name__ == "__main__":
    unittest.main()
