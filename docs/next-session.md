# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 23, 2026-10-21)

- **6,979 / 6,988 functions matched**: 99.87% of functions, 98.84% of code bytes (docs/progress.md). Session 23's matching thread (PR #27) found no new matches; 001636d0 is down to 394 words and 00265608 looks closed (nonmatchings/session23-match/NOTES.md).
- **The float defaults (data 0x8000, bss 0x11800) play**: title, load menu, Gate Plaza (test T), the world map with a warp drive to Neverland, and a fight on the pirate ship. Test T's "alley" is really Gate Plaza (the main menu names it). docs/shiftable-plan.md "Session 23" has a quick world-map route from save 06.
- **float_keep.txt's libcdvd block is gone** (it was a guess; KH1_F23_NOCD plays without it).
- **Whole pieces**: merge_pieces.py `--group D_X:SIZE` / `--split` made one piece of the 0x16C00 staging arena, of each of the six object/table records, and of every split_check pair (split_check.py now lists nothing). `make` is byte-identical. The default build after the merges (KH1_F23_MRG2) plays everything above.
- **The records are six VIF1 DMA chains** of 0x4040 bytes at D_0046E120 + k * 0x4040 (ref tags to D_0048BFD0 and D_0048C060, a table C fills, an `end` tag; session 20's "headers" are the previous chain's end tag). Floating two of them whole (KH1_F23_REC2) loads save 06 but hangs walking into Gate Plaza, and float_holes.py shows no stale writes, so something reads or DMAs from the old place. They stay in float_keep.txt.
- **Phase 4**: D_0046A688 is a piece (a table of eight function pointers) and D_0046A6A4 left C. 1,035 pieces are still untyped.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, sched2 trap_if dependence: closed).
2. **15-24 words**: 001c62a0 (15, global-alloc order; 35w shape fixes the cse1 half), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170 natural, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 24 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Why a whole DMA chain cannot float**: boot REC2-style builds (one chain at a time with `SHIFT_FLOAT_ONLY_DATA`, bss 0) and find who still uses the old place on entering Gate Plaza. Candidates: a VIF/DMA tag elsewhere that points into a chain without a relocation (check data_relocs tier `x` rows and the overlays), uncached (|0x20000000) or physical addresses built in code, or a chain address stored in a savestate-visible structure. A PCSX2 GS dump or a DMA log at the hang would show the tag address.
2. **Try floating the pointer-table-only names with their table** (`SHIFT_FLOAT_PTR_ONLY=1`), bisecting D_0048F700 ... for the missing slot digit on the load menu. Some of those names are now labels inside the D_0048F900 split piece.
3. **Phase 4**: types for the untyped pieces (start with the merged ones: their largest declaration as a struct in a shared header), keeping `make` identical.
4. **Matching (1 worker, optional)**: 001c62a0 (15w) or the 1-2 word nofill pair with a new idea only.
5. End with `make progress-update SESSION=24`, commit, open a PR, and refresh this prompt.
