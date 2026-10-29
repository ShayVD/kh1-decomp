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
| batch 1 | 2026-10-28 | 1590 / 2114 | autodecomp rerun (0 new), dktitle func_00f21068, dkmovie 6 MMI routines as asm, gb/wm main state machine (layout fixed: its switch cases were split off), xs_simba complete (4 by hand), xs_dumbo +4, xs_genie +1, workers: gb +12, wm +8, 12 wm twins via portall.py. Near misses: nonmatchings/session141/. |
| batch 2 | 2026-10-29 | 1662 / 2114 | gb +15 by hand and by the gb worker (each with its wm twin where one exists), wm +50 (two wm workers, twins via portall.py), dkmovie +0 (5 drafts within 7-51 words), xs_mushu func_00f20c58, xs_dh_break +1 (old draft in nostrict mode), xl_limit func_00f20e10, xs_genie +3. gb VU0 / sq functions f3e0d8, f41dc8 (15 words), f24780 left as near misses. |
| batch 3 | 2026-10-29 | 1699 / 2114 | gb +11 (f38408 / f3e388 GIF and skeleton builders by hand, 9 twins of wm matches), wm +21 (f3e388 / f38408 twins, f67928, 18 by the two wm workers), dkmovie +4, dktitle +1 (f25528). New near misses: gb f2d8d8, xs_genie f22078, ~20 wm drafts (nonmatchings/session141/wm/, headers say what's left). gb f41dc8 down to 3 words. |
| batch 4 | 2026-10-29 | 1765 / 2114 | gb +25 (f30d80 / f29c40 / f299c8 by hand via the `k = q * 4 + 8` table index and u16 lock reads, f41dc8 via the f68ec0 `ff` local, worker matches, twins), wm +41 (two workers: u16-bitfield fixes, sprite / grid families via index reuse `j = i; i = g->c[j].t`, f792c8 / f68ec0 packet builders). Workers' tips are in nonmatchings/session141/wm/NOTES-wwm*.md. |
| batch 5 | 2026-10-29 | 1805 / 2114 | gb and wm +40 (gb 448, wm 911: gb twins of wm matches via portall.py / portmap.py, gb f29f10 / f49320, worker matches: packet builders via an indexed `put`, store-order brute force, statement-order hill climbing, f70828 / f757b8 / f6a530 families). Near misses for every drafted function are in nonmatchings/session141/{gb,wm}/ with what was tried in each header. |
