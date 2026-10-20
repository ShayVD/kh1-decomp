# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 22, 2026-10-20)

- **6,979 / 6,988 functions matched**: 99.87% of functions, 98.84% of code bytes (docs/progress.md). func_00125240 matched (worker s22m1, an early `f32 *q = &D_002E27A4;` on the pinned draft). 001c62a0 is at 15 words (nonmatchings/session22/NOTES.md).
- **The Agrabah alley bug is found**: session 21 blamed data + bss floated together, but its controls were wrong; the data float alone breaks the alley (RCB0 is bad with a fixed route). The cause was D_0048BFD0, the 8-byte head of a 0x90-byte record that the object/table records point at. Floated, its reader got whatever floated after it (sky, or a hang loading save 06). Pads after every floated name showed no write past any of them.
- **New tools/shift/split_check.py** keeps both pieces of any pointed-at object cut at a non-16-aligned boundary (272 names). It also fixes the second bug: data 0x6000/0x8000 drew no title because two GIF-packet colour fields (D_002A6178, D_002A6658) floated off their packets. keep_check.py has 38 names now.
- **Float defaults are now data 0x8000, bss 0x11800** (`_end` 0x695264, 0xD9C left below the 0x6A0000 arena with the heap). Title and alley verified in PCSX2 (KH1_F22_K8C). **Not run yet on these defaults: Gate Plaza, the world map and a fight.**
- **Test T** (deterministic alley test), the pad tool (`SHIFT_FLOAT_PAD`, float_pads.py) and the layout knobs (`SHIFT_FLOAT_BSS_GAP`, `SHIFT_FLOAT_DATA_GAP`, `SHIFT_FLOAT_BSS_SLOTS`) are in docs/shiftable-plan.md "Session 22".
- **Test memcard**: save 05 is Traverse Town and save 06 is in Agrabah (cursor starts on 06). Keys are sometimes dropped in menus; zoom to check the cursor before each confirm.

## What is left (9 functions)

Best drafts are in nonmatchings/session22/ and older. Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill; pins exhausted), 001f1fc8 (2, nofill; pins exhausted), 00265608 (4, sched2 dependence).
2. **15-24 words**: 001c62a0 (15, global-alloc order), 00200e28 (24).
3. **Large**: 00110618 (93), 0010d470 (170 natural), 001636d0 (400).

## Session 23 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Runtime on the new defaults**: boot the default float build and run Gate Plaza, the world map (warp), and a fight. If one fails, bisect the names 0x8000/0x11800 add over 0x4000/0 (shiftable-plan.md "Session 22" has the method).
2. **Drop what is no longer needed**: test the build without float_keep.txt's libcdvd block (a session 21 guess for the alley bug).
3. **Float the kept records as wholes** (merge_pieces.py on the four object/table records, the staging arena and the split_check pairs). Then try floating the pointer-table-only names with their table, bisecting D_0048F700 ... for the missing digit.
4. **Phase 4**: D_0046A688 (needs D_0046A6A4 out of C) and types for the untyped pieces.
5. **Matching (1 worker)**: 001c62a0 (15w) or 00265608 (4w).
6. End with `make progress-update SESSION=23`, commit, open a PR, and refresh this prompt.
