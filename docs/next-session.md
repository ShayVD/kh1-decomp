# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 17, 2026-10-20)

- **6,973 / 6,988 functions matched**: 99.79% of functions, 98.55% of code bytes (docs/progress.md). Session 17 found no new match; the 001c62a0 draft went from 56 to 39 words (nonmatchings/session17/NOTES.md, docs/matching-tips.md "Session 17").
- **Phase 4, steps 1-3** (docs/shiftable-plan.md "Session 17"). `make` stays byte-identical.
  - 642 variables are C definitions: 606 bss, 36 data. Tools in tools/shift/: `define_vars.py` (single-owner bss), `define_ptr_tables.py` (pointer-only tables), `define_shared.py` (shared bss into `src/data/bss_XXXX.c` + `include/data/bss_XXXX.h`, 306 names), `cover_check.py`.
  - Hazards are listed in shiftable-plan "Hazards found". The big one: some bss names are fields of a larger object another file declares (D_005759A6 is field x66 of the camera at D_00575940). `cover_check.py` finds 48 such names, and the float build keeps them in place.
  - `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` floats the data tables; bss stays in place by default (`SHIFT_FLOAT_BSS_BUDGET ?= 0`). That build plays in PCSX2 (title, save load, walk, attack, menus). With bss floated the game runs at 60 fps but never draws the title.
- **Phase 3**: the character command stream record rule is settled on 7,530 records; the program-bit triggers and the P21 rotation order are in docs/renderer-spec.md and docs/structs.md (`tools/vu/rb_stream.py`).
- How to test in PCSX2: docs/workflow.md "Session 17" (cloud loop, keys, wait 45 s and retry a "No Image" boot once, compare ELF hashes).

## What is left (15 functions)

Best drafts are in nonmatchings/session17/ and older. Counts are LCS words.

1. **1-5 words**: 001fd858 (1, flagged reorg liveness), 001cfc28 (1), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 001f18e8 (2), 001eddc0 (2), 0021e120 (3), 00125240 (3 flagged, right size; 8 natural).
2. **9-39 words**: 00265608 (9, SDK gcc991111), 00192958 (17), 00200e28 (24), 001c62a0 (39).
3. **Large**: 00110618 (93), 0010d470 (170 natural; 129 with an unnatural byte-offset probe), 001636d0 (410).

## Session 18 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **bss float**: find the remaining hidden struct fields. Start from `SHIFT_FLOAT_BSS_BUDGET=0x400` (17 small names) and bisect with `SHIFT_FLOAT_SKIP` in PCSX2. Teach `cover_check.py` each new pattern (asm-declared objects, `T D[]` objects whose real size is known from code). Goal: the default budget back to 0x10000 with the title, a save load and a fight working.
2. **Phase 4, step 3 continued**: the 369 shared bss names whose users disagree on the type. Pick one type per name (usually the hand file's struct), move it into a header, and define it in `src/data/`. Then start shared data (game tables stay out of the repo: step 4).
3. **Matching (1 worker, only with a new angle)**: the loop insn-count lever (static inline helpers) on other loop-heavy drafts: 001636d0, 0010d470.
4. **Phase 3**: P10/P19/P20 triggers in a fight (RAM dump during combat).
5. End with `make progress-update SESSION=18`, commit, open a PR, and refresh this prompt.
