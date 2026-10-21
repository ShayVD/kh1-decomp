# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 24, 2026-10-21)

- **6,979 / 6,988 functions matched**: 99.87% of functions, 98.84% of code bytes (docs/progress.md). No matching work in session 24.
- **The DMA chain hang is explained** (docs/shiftable-plan.md "Session 24"): func_00106ed0 uses chain 1's table (D_00472190) also as 32-byte entries through D_00494BAC, D_00494BB0 of them (622 in Gate Plaza), so it writes 0xDB0 bytes into chain 2 (only qword upper halves, which the DMA ignores). Floated alone it overwrote the names after it. Chains 1 and 2 are one 0x8080 piece now; KH1_F24_REC3 (chain 0 + chains 1-2 floated) plays Gate Plaza and a fight. Found by reading session 23's hang savestate in the container (eeMemory, eeHwRegs, cpuRegs; docs/workflow.md "Session 24").
- **Pointer-table-only names float by default** (`SHIFT_FLOAT_PTR_ONLY=1`): the session 20 slot-digit bug is gone. The default float build (= KH1_F24_P1: 1,061 data names, 118 bss runs, `_end` 0x6953E4) plays the load menu, Gate Plaza, the world map with a warp drive to Neverland, and fights. D_003E4658's buffer is one piece.
- **SHIFT_FLOAT_FORCE** floats kept names for runtime experiments (tools/shift/float_force.py).
- **Phase 4**: tools/shift/type_pieces.py typed 216 pieces (1,035 → 819 untyped), one header per piece in include/data/pieces/. Left: 68 merged pieces (53 with no C user), 274 where users disagree, 454 with no C user, 19 struct-typed refused (reasons in their comments).

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 25 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Grow the float**: with the pointer-only names in, 45 data names are over the 0x8000 budget and `_end + 0xA000` leaves only 0xC1C below the 0x6A0000 arena. Find what the 0x6A0000 limit really is (who allocates there, and whether the arena base can move with `_end`), then raise the data budget and boot (load menu, test T, world map warp, a fight; docs/shiftable-plan.md "Session 23" route).
2. **Static rule for loaded-count arrays**: D_00494BAC is a global pointer set to a data name and indexed by a count loaded from room data with a stride larger than the name's own entries. Teach reach_check to treat "address stored into a pointer global, then indexed through that global" with the strides seen at its users, and check it finds chain 1 → chain 2 by itself.
3. **Phase 4**: the 274 "users disagree" pieces: unify the users' local struct types where they are the same layout under different names (a shared type header per object), keeping `make` identical.
4. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
5. End with `make progress-update SESSION=25`, commit, open a PR, and refresh this prompt.
