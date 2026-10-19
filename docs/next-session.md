# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 16, 2026-10-19)

- **6,973 / 6,988 functions matched**: 99.79% of functions, 98.55% of code bytes (docs/progress.md). Session 16 matched func_00166570 (frame-pointer copy lever, docs/matching-tips.md "Session 16"). 00200e28 and 00192958 unchanged (nonmatchings/session16/NOTES.md).
- **Phase 4 has begun** (docs/shiftable-plan.md "Session 16").
  - C objects build with `-fdata-sections -fno-common` (except `src/sdk/`). A variable named `D_XXXXXXXX` is placed at its address by the link script and checked by `verify`. `make` stays byte-identical.
  - 64 variables are now real C definitions: 62 menu bss buffers in text_00230000_s6_24.c and the two collision handler tables in text_00110000_s9_w8.c.
  - `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` moves them off the original layout. It plays in PCSX2 (save load, walking, main menu, Items, Status).
  - `tools/shift/data_owners.py` gives the counts: bss 399 single-owner and 839 shared; data 1,262 single-owner, 36 single-owner with blob pointers, 842 shared; 50 single-owner pointer-only tables. The plan for the rest is in shiftable-plan "Plan for the rest".
- **Phase 3**:
  - Model file headers are in docs/structs.md "Model files", checked against real disc files and a RAM dump (MOBJ offsets relocated in place; map mesh tags are copied, not relocated; renderer A VIF batch format).
  - The 256x256 off-screen pass is the projected character shadow (renderer-spec §3.4); it runs in every field. A field GS dump is in §3.3.
  - Still open: the exact record length rule of the character command stream (skipping op 1 by `arg` hits an op 8), P10/P19/P20 triggers, P21 rotation order.
- How to test the shiftable build: `make shift SHIFT_MODE=m12 [SHIFT_FLOAT=1]`, then `tools/shift/patch_iso.py MY.iso out/shift/<dir>/kh1-shift.elf KH1_BIG.iso --append [--in-place]`, and boot it in PCSX2. Test ISOs, save, memory cards and PCSX2 quirks are in docs/workflow.md "Session 14" to "Session 16".

## What is left (15 functions)

Best drafts are in nonmatchings/session16/ and older. Counts are LCS words.

1. **1-5 words**: 001fd858 (1, flagged reorg liveness), 001cfc28 (1), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 001f18e8 (2), 001eddc0 (2), 0021e120 (3), 00125240 (3 flagged, right size; 8 natural).
2. **9-56 words**: 00265608 (9, SDK gcc991111), 00192958 (17), 00200e28 (24), 001c62a0 (56).
3. **Large**: 00110618 (93), 0010d470 (170 natural; 129 with an unnatural byte-offset probe), 001636d0 (410).

## Session 17 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Phase 4, step 1-2**: convert the 399 single-owner bss names and the 50 pointer-only tables to C definitions, file by file (`data_owners.py --file SRC`). `make` stays byte-identical after each batch. Check with `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`.
2. **Phase 4, step 3**: start the shared-data modules (`src/data/*.c` + headers), bss first.
3. **Matching (1 worker, only with a new angle)**: try the frame-pointer copy lever on the other gcse-linked drafts (00200e28, 001c62a0, 00110618).
4. **Phase 3**: settle the character command stream record length (vif_chain.py on the RAM dump), then the P10/P19/P20 triggers.
5. **Runtime**: one PCSX2 run of the SHIFT_FLOAT build after the bulk conversion (menus, a fight, an area change).
6. End with `make progress-update SESSION=17`, commit, open a PR, and refresh this prompt.
