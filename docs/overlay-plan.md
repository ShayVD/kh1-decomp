# Plan: match every overlay function (phase 2, from session 141)

Session 141 (2026-10-28) starts a continuous push on the 12 EE overlays (docs/overlays.md).
This file is the plan and the running ledger; update the table at the end of each batch.

## Where it starts

`make ovl-progress` at the start of session 141 (every overlay byte-identical, `make ovl`):

| Overlay | Matched / functions | Left | Left "hard" (VU0 / MMI / 128-bit) | Left by size: <=50 / 51-150 / 151-400 / >400 insns |
|---|---|---|---|---|
| dkmovie | 96 / 122 | 26 | 6 | 6 / 9 / 9 / 2 |
| dktitle | 60 / 71 | 11 | 1 | 0 / 3 / 6 / 2 |
| gb | 367 / 533 | 166 | 19 | 10 / 70 / 67 / 19 |
| wm | 747 / 1109 | 362 | 51 | 25 / 163 / 144 / 30 |
| xl_limit | 74 / 76 | 2 | 0 | 0 / 2 / 0 / 0 |
| xs_bambi | 13 / 13 | 0 | 0 | done |
| xs_dh_break | 5 / 9 | 4 | 0 | 0 / 2 / 2 / 0 |
| xs_dumbo | 48 / 54 | 6 | 0 | 0 / 4 / 2 / 0 |
| xs_genie | 58 / 64 | 6 | 0 | 0 / 5 / 1 / 0 |
| xs_mushu | 22 / 24 | 2 | 0 | 0 / 1 / 1 / 0 |
| xs_simba | 29 / 33 | 4 | 0 | 0 / 0 / 4 / 0 |
| xs_tink | 13 / 14 | 1 | 0 | 0 / 1 / 0 / 0 |
| total | 1532 / 2122 | 590 | 77 | |

(docs/progress.md said 1,537 of 2,131 before; 2,122 is what the layouts hold today.)

wm's matched functions are only 92,776 of its 391,196 code bytes: what is left is mostly
large. The easy part is gone; session 131b's notes say the rest is mostly register
allocation, scheduling and big functions.

## Order of work

1. **Re-run autodecomp** over every unmatched overlay function with a larger search budget
   (`--budget 120`), for the reports' scores (the queue) and any free matches. Then twins.py.
2. **Small overlays first** (xs_tink, xs_mushu, xl_limit, xs_genie, xs_dumbo, xs_simba,
   xs_dh_break: 25 functions), so whole overlays close.
3. **dktitle and dkmovie** (37): drafts already exist (ovl/dktitle/drafts.tsv,
   nonmatchings/session13x/); permuter on the 1-6 word ones.
4. **gb, then wm**, closest first by autodecomp score. Every gb match is tried on wm and the
   summons by twins.py (they share most of their code), so gb goes first.
5. **Hard functions** (VU0 macro code, 128-bit copies) last: inline asm where it is clearly
   hand-written; flag the rest in the ledger rather than burning hours.

Rules: a function counts only when `make ovl` is byte-identical and `make ovl-report` says
100% for it. PRs go up in batches (one per overlay group or every ~25 matches), each with
`make ovl` and `make` (main ELF) still byte-identical. Near misses keep their best draft in
`nonmatchings/session141/OVERLAY/` with the words left.

## Ledger

| Batch | Date | Matched after | Notes |
|---|---|---|---|
| start | 2026-10-28 | 1532 / 2122 | |
