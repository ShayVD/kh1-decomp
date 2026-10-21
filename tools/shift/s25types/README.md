Session 25 Phase 4 helpers (worker s25types; docs/shiftable-plan.md "Session 25: Phase 4 types").
Scratch output goes to $S25_DIR (default /tmp/s25types). Run with `python3 -I` from the repo root.

- s25_unify.py: try one declaration for one piece: replace each user's extern with
  `#include "data/pieces/D_X.h"`, compile every changed user with its objects.mk recipe (`-S`), and
  accept only if the assembly is identical and no new warning appears.
- s25_drive.py: run s25_unify over the basic-type disagreements (s32/u32, T/T[], M2C_UNK, volatile).
- s25_drive2.py: struct, pointer and src/auto cast targets (moves struct types with type_pieces.move_types).
- s25_reasons.py: writes each refused piece's reason into its .s comment from drive2's output.
