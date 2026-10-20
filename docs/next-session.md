# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 19, 2026-10-20)

- **6,978 / 6,988 functions matched**: 99.86% of functions, 98.83% of code bytes (docs/progress.md). Session 19 matched 001cfc28, 0021e120 and 001eddc0 by putting session 18's register pins on older drafts whose schedule was already right (docs/matching-tips.md "Session 19"). Pins on computed values dissolve when cse sees all their uses; 001f2630 and 001f1fc8 look closed for that lever (nonmatchings/session19/NOTES.md).
- **Float build** (docs/shiftable-plan.md, the three "Session 19" sections):
  - The bss budget is now `SHIFT_FLOAT_BSS_BUDGET ?= 0x11800`; `_end` is 0x691424.
  - reach_check bounds indexed accesses, so 9 more names float.
  - D_00573AC0, a GIF packet buffer reached only through a stored pointer, is in float_keep.txt.
  - The build plays: it loads the save, crosses the world map and lands in Agrabah. An Agrabah fight was tested on the session 18 rules (F19A).
- **Phase 4 step 4**: 809 shared data names are per-symbol `.incbin` pieces cut from the user's ELF at build time (`src/data/data_XXXX.s`, `tools/shift/cut_pieces.py`). data_owners.py now anchors on C definitions, and more shared names are C definitions.
- **The data float is off** (`SHIFT_FLOAT_DATA_BUDGET ?= 0`). With 0x4000 (493 pieces), PCSX2 itself crashes a few seconds after loading a save; the cause is unknown.
- **Phase 3 fight dump**: an Agrabah fight draws only P10/P11/P18. It shows no P19/P20 and still no skinned part (renderer-spec §6 item 4).
- **Fresh clone trap**: run `tools/shift/data_owners.py` after the first `make shift`, before a float build.

## What is left (10 functions)

Best drafts are in nonmatchings/session19/ and older. Counts are LCS words.

1. **1-3 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill; pins exhausted), 001f1fc8 (2, nofill; pins exhausted), 00125240 (3 flagged; the leftover is a `lui`).
2. **7-24 words**: 00265608 (7, SDK gcc991111), 001c62a0 (16; s19m1 draft in nonmatchings/session19), 00200e28 (24).
3. **Large**: 00110618 (93), 0010d470 (170 natural), 001636d0 (400).

## Session 20 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Bisect the data float crash**: try data budgets of 0x800 and 0x2000, then `SHIFT_FLOAT_ONLY` on the culprit range. Boot each in PCSX2 and load save 05. Look for tables that DMA or VIF code reads by address (inferred cause).
2. **Raise the bss budget** towards 0x16000 (the arena limit with no data float). Boot-test each step: 0x15000 is untested since the packet-buffer fix.
3. **reach_check**: flag floated names whose address is stored with 0x20000000/0x30000000 ORed in (uncached buffers like D_00573AC0).
4. **Phase 4**: the 1,368 single-owner data names as pieces (`--verdict single --verdict single+p`, then `--pointers`), and the 34 shared names that stay extern.
5. **Matching (1 worker)**: 001c62a0 (16w) and 00200e28 (24w) with register pins, or the `lui` in 00125240.
6. **Runtime (optional)**: a cutscene or boss fight dump for P19/P20 and a skinned part.
7. End with `make progress-update SESSION=20`, commit, open a PR, and refresh this prompt.
