# LeetCode → GitHub

Import your old Accepted submissions, then sync new ones every 30 minutes.
One latest Accepted solution per problem, across all languages. Python standard
library only: no packages, database, AI model, or VPS.

## How it works

1. Authenticate with your LeetCode session and verify the signed-in account.
2. On the first run, paginate through all solved problems via GraphQL, then
   select the newest Accepted submission per problem, ignoring failed attempts.
3. Fetch source code only for those selected submissions and write
   `solutions/<difficulty>/<problem-slug>/solution.<extension>` plus a short README with links.
   Difficulty comes from LeetCode and maps to `easy`, `medium`, or `hard`.
4. Store problem/submission IDs and an incremental checkpoint in `.leetcode-sync.json`.
5. GitHub Actions commits solutions and state together, then pushes to this repository.

Later runs compare each problem's last submission time to the saved state.
Unchanged problems need no submission-detail or source-code requests. If a changed
problem has no newer Accepted, only its cached timestamp is updated; this can
produce a metadata-only commit. A newer Accepted for an existing problem
replaces its solution; older versions remain in Git history. Changing language
removes the previous solution file so each problem still has one solution.
An unknown language is preserved as `.txt`.

```text
solutions/
  easy/
    two-sum/
      solution.py
      README.md
  medium/
    add-two-numbers/
      solution.cpp
      README.md
  hard/
    median-of-two-sorted-arrays/
      solution.py
      README.md
```

Folders are created when a solution is synced at that difficulty. Invalid or
missing difficulty stops the run rather than putting a solution in the wrong folder.

There is one commit per scheduled batch, including one batch for the initial
import. Commit dates are the actual sync time; the original submission time is
recorded in each problem's README. Source code is downloaded, never executed.

## Set up on GitHub

Use a repository dedicated to these solutions. Put this project's files on its
**default branch**. The same repository contains the workflow and solutions.

In **Settings → Secrets and variables → Actions**, add two repository secrets:

| Secret | Value |
| --- | --- |
| `LEETCODE_SESSION` | Raw value of the `LEETCODE_SESSION` cookie |
| `LEETCODE_CSRF_TOKEN` | Raw value of the `csrftoken` cookie |

To find them: sign into `leetcode.com`, open browser developer tools →
Application/Storage → Cookies → `https://leetcode.com`. Copy only each cookie's
value. These are login credentials: put them in GitHub Secrets, never in source
files, issues, or chat. No LeetCode password or separate GitHub token is needed.
The workflow uses GitHub's built-in token with repository contents write access.

Optional repository **variables** `COMMIT_NAME` and `COMMIT_EMAIL` set the commit
author. Use an email associated with your GitHub account if you want attribution
to your account. This repository defaults to `hajendra herlambang`
(`<hajendraherlambang742@gmail.com>`); override the variables if you fork it.

Open **Actions → Sync LeetCode → Run workflow** to perform the first import.
Afterward it runs at minutes **17 and 47** each hour. GitHub may delay scheduled
runs, so this is roughly every 30 minutes, not instant synchronization.
Changes to `sync.py` or the workflow on `main` also trigger a run. Solution
commits do not trigger another run.
The workflow serializes runs to prevent two imports from overwriting state.

If branch protection blocks direct pushes, use a dedicated repository/branch
policy that permits this workflow to push; this project does not bypass protections.
GitHub can disable scheduled workflows in public repositories after 60 days
without repository activity. Re-enable the workflow under Actions if needed.

## Run locally

Requires Python 3.11+ and Git only if you want to commit locally. In Bash, read
credentials without placing their values in shell history:

```bash
read -rsp 'LeetCode session: ' LEETCODE_SESSION; echo
read -rsp 'CSRF token: ' LEETCODE_CSRF_TOKEN; echo
export LEETCODE_SESSION LEETCODE_CSRF_TOKEN
python3 sync.py --dry-run  # verifies access and selected source code; writes nothing
python3 sync.py            # writes solutions and state; does not commit or push locally
unset LEETCODE_SESSION LEETCODE_CSRF_TOKEN
```

The script always writes beside `sync.py`, regardless of your working directory.
It does not auto-load `.env` files. Run offline checks with:

```bash
python3 -m unittest -v
```

## Failure and recovery

- Requests have a 30-second timeout, at least one second between requests, and
  bounded retries for rate limits and transient network/server errors.
- Pending/judging submissions keep the previous checkpoint and do not cache
  the problem's update time, so their final verdict is checked again.
  Only Accepted source is saved.
- If any fetch/write fails, the script exits unsuccessfully and the workflow
  skips the commit. The next fresh checkout retries from the committed state.
  A failed local run can leave uncommitted solution files; rerun to finish.
- If a push fails, the remote repository retains its previous checkpoint and
  the next run retries. No force-push or automatic conflict resolution is used.
- Session expiry or HTTP 401/403 requires fresh cookies. Cloudflare can also
  block hosted runners even with valid cookies; try the local dry run to
  distinguish access problems. This implementation does not bypass challenges.
- The first import must complete within the workflow's 60-minute timeout.
  For unusually large histories, run the import locally and commit its output
  before enabling the schedule.
- LeetCode's endpoints are internal and can change. Import covers the history
  LeetCode exposes to your session; deleted/unavailable submissions cannot be
  recovered. Authentication and live account access must be verified during setup.
- State belongs to one LeetCode account. A different login is rejected to avoid
  mixing accounts. Keep the state file committed; removing it triggers a full scan.

## Endpoint references

- [LeetCode CLI's submission-history integration](https://github.com/skygragon/leetcode-cli/blob/master/lib/plugins/leetcode.js)
- [glsync's authenticated submission-detail query](https://github.com/ahmed-e-abdulaziz/glsync/blob/main/code/leetcode-graphql/submission-details-query.json)
- [GitHub scheduled workflow behavior](https://docs.github.com/en/actions/reference/workflows-and-actions/events-that-trigger-workflows#schedule)

Tests use mocked responses. They verify selection, pagination, checkpoints,
updates, retries, and recovery; they do not prove live LeetCode access or a
successful GitHub push for your account.
