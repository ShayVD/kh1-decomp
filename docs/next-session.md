# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 28, 2026-10-22)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-28.
- **reach_check end-ptr rule** (docs/shiftable-plan.md "Session 28: end pointers, the IOP block and D_BLOB"): finds the actor table D_002C64A0 by itself; it left float_keep.txt and keep_check enforces it. The default float set is unchanged from KH1_F27_R12.
- **Ready but never booted** (no PCSX2 access in session 28): the IOP block is one piece D_0063D640 (src/data/data_0063.s), and shift_cmp accepts a floated D_00272C70 (D_BLOB checked as the .data start). `SHIFT_FLOAT_FORCE="D_00272C70 D_0063D640"` links and passes M12-FLOAT. Both stay in float_keep.txt until that build has played.
- **Phase 4**: view casts 796 -> 463 (worker s28types); D_002E26A0 and D_003044D8 typed. What is left and why: "Session 28: Phase 4 types".

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 29 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot the pending floats first** (ask for the Mac and PCSX2 at the start): stage out/overlays from Downloads/kh1-test/ovl, build the default (expect = F27_R12) and `SHIFT_FLOAT_FORCE="D_00272C70 D_0063D640"`, boot the usual route (save 06 with Donald and Goofy, test T, a desert fight, Neverland ship fight, End of the World). If it plays, drop both from float_keep.txt. Then try D_003F8380 / D_0046E120 / D_00472160 forced (F27_C2 played) and decide whether to make them default via float_keep comments or a targeted reach_check exception.
2. **reach_check idx**: relational bounds for nested loops whose inner counter carries over the outer loop (func_00103a70's 4x4 copy). The stored group (func_0023aed0) is not worth it (pointers go into its Out record).
3. **Phase 4**: the remaining 463 view casts: a VM type shared by D_0039A580 / D_0038D170 / D_003C3A70 / D_003A7990 / D_003B4DA0, one vector type set (V4/V3) for D_002E2780/2790, D_002C58A0/B0, D_002C58D0, and the D_00304BE8 overlaps. `make` must stay identical.
4. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
5. End with `make progress-update SESSION=29`, commit, open a PR, and refresh this prompt.
