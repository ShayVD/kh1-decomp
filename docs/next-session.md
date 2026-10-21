# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 27, 2026-10-21)

- **6,979 / 6,988 functions matched**: 99.87% of functions, 98.84% of code bytes (docs/progress.md). No matching work in session 27.
- **Floated slots are given back** (docs/shiftable-plan.md "Session 27: floated slots are given back"): `SHIFT_FLOAT_COMPACT=1` is the default. Each run of floated slots shrinks by a multiple of 64; D_BLOB/D_BSS+offset references go through the piecewise map in compact.tsv (shift_ld CompactMap; shift_cmp and float_holes read it). The pools and block heap are back at 0x6A0000 / 0x820000.
- **reach_check has seven more rules** ("Session 27: reach_check rules"): it pins 1,347 names (was 1,803). The default build (= KH1_F27_R12) floats **2,051 of 3,412 names**, `_end` 0x687564, and plays save 06 with the party, test T, a desert fight, the warp to Neverland and a ship fight, End of the World and a fight; float_holes 0 of 2,051.
- **The actor table hazard**: D_002C64A0 (1200-byte entries) is walked with D_002E26A0's address as its end, so floating it lost Donald and Goofy (bisected R1-R11). float_keep.txt pins it. No check finds this pattern yet.
- float_keep.txt also pins D_00272C70 (= D_BLOB; shift_cmp maps D_BLOB through it if it floats).
- **Phase 4**: worker s27types folded 43 pieces, removing 745 of 1,541 view casts (tools/shift/s27types/, "Session 27: Phase 4 types"). About 796 casts are left; D_002E26A0 and D_003044D8 still need code changes.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 28 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **An end-pointer rule in reach_check**: find every compare (`sltu`/`slt`/`beq` after a subtract) of a walked pointer against another name's address (`&NEXT` as a table end, like D_002C64A0 / D_002E26A0) and pin the table to the name. Check it finds the actor table on its own, then take D_002C64A0 out of float_keep.txt and boot (save 06: Donald and Goofy must be there).
2. **The rest of float_keep.txt**: fix shift_cmp's D_BLOB mapping so D_00272C70 can float; make the IOP block D_0063D640 a piece covering its 0x2000 bytes and try it with SHIFT_FLOAT_FORCE; try making F27_C2's forced names (D_003F8380, D_0046E120, D_00472160) the default if reach_check can release them.
3. **reach_check's remaining groups**: idx (nested loops whose inner counter carries across the outer loop; needs relational bounds) and stored (func_0023b570's stack arguments to func_0023aed0). Boot after any rule change (keep_check must pass); the riskiest releases are listed in the reach_check section.
4. **Phase 4**: fold the ~796 remaining view casts (tools/shift/s27types/ helpers), then D_002E26A0 and D_003044D8. `make` must stay identical.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=28`, commit, open a PR, and refresh this prompt.
