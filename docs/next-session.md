# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 29, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-29.
- **Runtime**: the IOP block D_0063D640, D_00272C70, the staging arena D_003F8380 and DMA chains 0-2 (D_0046E120, D_00472160) all float by default now. The ones reach_check still pins are in the new tools/shift/float_release.txt (Makefile `SHIFT_FLOAT_RELEASE`). The default build KH1_F29_N plays the usual route (docs/shiftable-plan.md "Session 29").
- **reach_check nest-carry** (`--no-nest-carry`): counters carried across nested loops. 1,348 -> 1,338 names pinned.
- **Phase 4** (worker s29types): view casts 463 -> 275. The VM tables share `VmRec` and the vector pieces share `FVec4`. What is left and why: docs/shiftable-plan.md "Session 29: Phase 4 types".
- **PCSX2 loop**: the Mac's shell sandbox did not start in session 29, so patch_iso.py ran through a Remote Control session, and once through me in Terminal (docs/workflow.md "Session 29"). Try device_bash first.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 30 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **reach_check, the next largest groups** (`--explain`, float_reach.log): the idx tail (2-6 names per function) and `stored` (func_0023b570's stack arguments to func_0023aed0, 38 names: follow stack arguments into the callee's `lw aN, off(sp)`). Every rule gets a `--no-*` switch and a test case in tests/reach_check_test.py, and `--no-*` must reproduce the old list byte for byte.
2. **Boot the result** (ask for the Mac and PCSX2 if a rule releases names): stage out/overlays from Downloads/kh1-test/ovl, build the default, copy the ELF to Downloads/kh1-test/s30, patch KH1_BIG.iso, and run the usual route: save 06 with Donald and Goofy, test T, the desert fight, save 05 End of the World, and the warp drive to Neverland. A new name pinned by a check that played can go in float_release.txt.
3. **Phase 4**: the remaining 275 view casts: D_002C58D0 (one matrix type: retype h30's `V4` array and c04's `M4` locals first), the 18 left in D_00304BE8, D_002A6238's bit-field views, and b11's Actor/Obj views before its VM view. `make` must stay identical.
4. **Phase 4, real modules (a first try)**: the src/auto/text_XXXX0000.c files are provisional (docs/workflow.md "Bulk matching"). Move one subsystem whose data types are now shared (the VmRec users) into a named module, and write down in docs/ what that takes. The build must stay byte-identical.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=30`, commit, open a PR, and refresh this prompt.
