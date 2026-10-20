# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 18, 2026-10-20)

- **6,975 / 6,988 functions matched**: 99.81% of functions, 98.72% of code bytes (docs/progress.md). Session 18 matched func_001f18e8 and func_00192958 with a new lever: local register variables that pin a constant or an operation's result (docs/matching-tips.md "Session 18"). sceGsDefDispEnv (00265608) improved from 9 to 7 words.
- **bss floats again by default** (`SHIFT_FLOAT_BSS_BUDGET ?= 0x10000`, docs/shiftable-plan.md "Session 18"). The float build reaches the title, loads the End of the World save, walks, attacks, casts magic and opens the menus in PCSX2. No fight has been tested yet: there are no enemies near that save point.
  - `tools/shift/reach_check.py` keeps names in place when code reaches them from another object: displacements, call arguments, and arrays indexed into the next name.
  - `tools/shift/float_holes.py STATE.p2s` lists stale writes at old addresses, from a state saved with System > Save State > Save To File.
  - `tools/shift/float_keep.txt` keeps the sound IOP's status block (D_0063D640 + 0x1c08 / 0x1f00) in place.
  - `SHIFT_FLOAT_ONLY` is for bisecting.
- **Phase 4 step 3**: 1,029 variables are C definitions (36 data, 993 bss). 387 shared names whose users disagreed on the type now have one definition each (`define_shared.py --mixed --types`, `type_move.py`, headers `include/data/bss_XXXX_{mixed,typed}.h` and `include/data/types/`). 74 were skipped, with the reasons in shiftable-plan.
- **Known tool bug**: `data_owners.py` misses C-defined names as anchors, so its extents run over existing definitions. define_shared.py clamps around it.

## What is left (13 functions)

Best drafts are in nonmatchings/session18/ and older. Counts are LCS words.

1. **1-3 words**: 001fd858 (1, reorg liveness), 001cfc28 (1), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 001eddc0 (2), 0021e120 (3; the s18m1 pinned basin is in nonmatchings/session18), 00125240 (3 flagged; the leftover is a `lui`).
2. **7-39 words**: 00265608 (7, SDK gcc991111), 00200e28 (24), 001c62a0 (39).
3. **Large**: 00110618 (93), 0010d470 (170 natural), 001636d0 (400).

## Session 19 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Runtime**: a fight in the float build. Take the world map to Agrabah (docs/workflow.md "Session 15" route), or use a save with enemies nearby. Do the Phase 3 RAM dump for the P10/P19/P20 triggers during that fight.
2. **Fix data_owners.py anchors** (add out/gen/data.tsv), then retry the 37 + 25 skipped shared names and the 3 type clashes in bss_0061 (one shared `u128`/`PppMtx` header).
3. **Phase 4 step 4**: start on shared *data* (game tables stay out of the repo: per-symbol `.incbin` pieces cut from the user's ELF at build time).
4. **Make reach_check less conservative**: use declared sizes from cover_check to drop `idx-next` hits whose array ends before the next name. Then raise the budget past 0x10000 while `_end + 0xA000` stays under the 0x6A0000 arena.
5. **Matching (1 worker)**: the register-pin lever on 001cfc28 / 001f2630 / 0021e120 with new statement orders, or a new angle for 001636d0 / 0010d470.
6. End with `make progress-update SESSION=19`, commit, open a PR, and refresh this prompt.
