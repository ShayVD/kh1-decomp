# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 26, 2026-10-21)

- **6,979 / 6,988 functions matched**: 99.87% of functions, 98.84% of code bytes (docs/progress.md). No matching work in session 26.
- **Everything the static checks allow floats** (docs/shiftable-plan.md "Session 26"): func_00121c78's block heap (0x820000-0x9A0000, end D_009A0000) moves its base after the fixed pools (shift_ld BLOCK_HEAP; `SHIFT_FIXED_HEAP=1` keeps it), with an assert that 0xE0000 bytes are left (the largest use seen in savestates is 0x9E038). Budgets are 0x100000, so nothing is over budget. The default build (= KH1_F26_A: 1,602 floated names, `_end` 0x74B164, pools 0x756000, heap 0x8A9000) plays the load menu, test T, a Gate Plaza fight, the warp to Neverland and a fight on the ship.
- **Memory map past the image** is in that section: load area 0x9A0000 (dktitle.x names it), overlays linked at 0xF20000, 12 slots at 0xFE0000, 0x1CE0000, stack 0x1FE0000. tools/shift/mem_regions.py reads a savestate's use of each.
- **Every floated name costs twice**: its old slot stays a hole (`. += size` in the .data script, the bss slot) and the copy goes after the image, so floating more shrinks the heap. Forcing the 0x16C00 staging arena as well fails the heap assert. KH1_F26_B (default + DMA chains 0 and 1-2 forced) plays Gate Plaza, a fight and End of the World.
- **Still pinned**: 1,848 names, nearly all by reach_check (1,803: an index or walk may run into the next name); float_keep.txt only adds D_0063F540 beyond what the checks keep.
- **Phase 4**: 143 of the 145 "users disagree" pieces are typed (worker s26types: casts at the uses, unions of the users' views); D_002E26A0 and D_003044D8 need code changes (their comments say why). 128 pieces are unified by casts, so many users still see their own struct through a cast. 63 merged pieces have no C user of their head.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 27 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Give floated slots back**: a `SHIFT_FLOAT_COMPACT=1` mode in shift_ld that drops the holes floated data and bss leave (`. += size` lines), so kept pieces close up. Names defined as `D_BLOB + off` / `D_BSS + off` (the tail, rodup blocks, blob `.word D_BLOB+x` relocations) must become offsets that account for the holes before them, and shift_cmp needs the piecewise map. Check that crt0's `_gp`/D_BSS distance still holds. Boot it (load menu, test T, a fight, world map warp, End of the World; docs/shiftable-plan.md "Session 23" route). Then the heap has room for SHIFT_FLOAT_FORCE experiments on the staging arena and the IOP block.
2. **reach_check pins**: pick the biggest groups of the 1,803 reach_check names (float_reach.txt reasons) and see which a bound can release; boot after any rule change (keep_check must still pass).
3. **Phase 4**: fold the 128 cast-unified pieces' views into one struct per object (users' fields renamed, casts removed), keeping `make` identical and the `-S` check (tools/shift/s26types/). Then D_002E26A0 and D_003044D8 (code shape changes, checked by `make`).
4. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
5. End with `make progress-update SESSION=27`, commit, open a PR, and refresh this prompt.
