# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 20, 2026-10-20)

- **6,978 / 6,988 functions matched**: 99.86% of functions, 98.83% of code bytes (docs/progress.md). Session 20 matched nothing new. 00125240 is now 3 words with a natural body and FP register pins, so it no longer needs the dead test. 001c62a0 (16w) is a global-alloc priority order, and 00200e28 (24w) looks closed for pins (nonmatchings/session20/NOTES.md).
- **The data float is on**: `SHIFT_FLOAT_DATA_BUDGET ?= 0x4000` floats 753 data names. The float build boots, loads save 05, walks, attacks and opens the menus in PCSX2 (KH1_F20_Q4000). Details are in docs/shiftable-plan.md, "Session 20: the data float".
  - **The session 19 crash**: D_00472190, D_004761D0 and D_0047A210 are declared 0x40 bytes, but code copies 0x4000 bytes through them.
  - **reach_check has four new rules**: `&D_X[i]` passed to a call, idx-base, a stored address counts as unbounded, and uncached aliases.
  - **float_keep.txt has two new groups**: the D_003F8380 staging arena and four object/table records (D_0046E120 ...).
  - **Names that only pointer tables point at stay in place** (`SHIFT_FLOAT_PTR_ONLY ?= 0`): floated, they drop a digit from the load menu.
- **Phase 4 step 4 is done for single-owner data** (docs/shiftable-plan.md, "Session 20: Phase 4"). There are 2,581 data pieces, and `merge_pieces.py` turns names declared larger than their extent into one piece with `PIECE_LABEL`s. Only D_0046A688 and D_00494050 stay extern.
- **bss**: 0x16000 builds the same ELF as 0x11800. The 6 bss names left are large (D_00533BA0 is 0x14014 bytes), so the keep rules now limit the float, not the budget.
- **Fresh-clone trap**: run `tools/shift/data_owners.py` after the first `make shift`, before a float build. The float build now also reads data_owners.tsv for the pointer-only rule.

## What is left (10 functions)

Best drafts are in nonmatchings/session20/ and older. Counts are LCS words.

1. **1-3 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill; pins exhausted), 001f1fc8 (2, nofill; pins exhausted), 00125240 (3; two `lui`s in sched1 order).
2. **7-24 words**: 00265608 (7, SDK gcc991111), 001c62a0 (16, global-alloc order), 00200e28 (24).
3. **Large**: 00110618 (93), 0010d470 (170 natural), 001636d0 (400).

## Session 21 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Run the default float build further in PCSX2**: the world map, the Agrabah warp and a fight (docs/workflow.md "Session 19" PCSX2 loop). Session 20 tested only the End of the World field and menus.
2. **Float the kept records as wholes**: run merge_pieces.py on the four object/table records and the staging arena so they float together. Then try floating the pointer-table-only names with their table, bisecting D_0048F700 ... for the missing digit.
3. **Raise the data budget** in steps (0x6000, 0x8000; the arena leaves 0xD7DC). Boot each one, since every step pulls in new names.
4. **Make reach_check less conservative**: it keeps 1,928 names now (761 with the session 19 rules). Bound decrementing-counter walks such as func_00232ad0's clear loop, and follow a join of two known addresses that gets stored (`cond ? A : B`).
5. **Phase 4**: D_0046A688 (needs D_0046A6A4 out of C) and types for the 1,229 untyped pieces.
6. **Matching (1 worker)**: 001fd858 (1w) or 00265608 (7w) with the pin lever.
7. End with `make progress-update SESSION=21`, commit, open a PR, and refresh this prompt.
