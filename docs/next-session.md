# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 25, 2026-10-21)

- **6,979 / 6,988 functions matched**: 99.87% of functions, 98.84% of code bytes (docs/progress.md). No matching work in session 25.
- **The 0x6A0000 limit is gone** (docs/shiftable-plan.md "Session 25"): it was two pool areas, func_0014a090's three pools at D_006A0000 (0x80000) and func_00133628's seven at D_00720000 (0xD2C00), with 0x2D400 unused before func_00121c78's D_00820000. shift_ld moves both bases to `_end + 0xA000` (0x1000-aligned) once the float reaches them and asserts they end by 0x820000; `SHIFT_FIXED_ARENA=1` keeps them fixed.
- **Float defaults are data 0x20000, bss 0x26000**: the default build (= KH1_F25_C: 1,079 data names, 119 bss runs, `_end` 0x6B7924, pools at 0x6C2000) plays the load menu, test T in Gate Plaza, the world map warp drive to Neverland and a fight on the ship. Still in place: three data tables (D_0040EF80 0x16C00, D_002E31F0 0x20000, D_00308CE0 0x40000) and two bss runs (D_004F8310 0x1CC48, one of 0x30C9C); only about 0x8800 of room is left before 0x820000. out/shift/m12-float/float_over_budget.tsv lists them.
- **reach_check**: via-ptr (an address stored into a pointer global is reached through the global's loads) and piece-next (an unbounded index inside a merged piece keeps the first name after the piece). With chains 1 and 2 split again (`--data-tsv`), it keeps chain 2 by itself.
- **Phase 4**: 129 of the 274 "users disagree" pieces are typed, users include the piece header in place of their own extern, checked by per-file `-S` (worker s25types; helpers in tools/shift/s25types/). Left: 145 "users disagree" (each comment names the files that break), 68 merged pieces (53 with no C user), 454 with no C user, 19 struct-typed refused.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 26 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **The rest of the float**: map the fixed regions after 0x820000 the way session 25 mapped the pools (func_00121c78's block heap at D_00820000 and its size, D_009A0000, then 0xF20000 overlays, 0xFE0000, 0x1CE0000, the stack at 0x1FE0000) and find which can follow `_end` too (overlays at 0xF20000 cannot: they are linked there). If 0x820000 can move, float the three big data tables and the last two bss runs, and boot (load menu, test T, world map warp, a fight; docs/shiftable-plan.md "Session 23" route).
2. **Full float check**: with everything that the checks allow floated, list what float_keep.txt and keep_check still pin and whether each still needs to (each was a runtime bisection); try dropping one at a time only with a boot.
3. **Phase 4**: the 145 "users disagree" pieces left need one struct per object with the hand users' fields renamed (their comments say which files break), then the 53 merged pieces with no C user. Keep `make` identical and use the per-file `-S` check (tools/shift/s25types/s25_unify.py).
4. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
5. End with `make progress-update SESSION=26`, commit, open a PR, and refresh this prompt.
