Session 26 Phase 4 helpers (worker s26types; docs/shiftable-plan.md "Session 26: Phase 4 types").
Scratch output goes to $S26_DIR (default /tmp/s26types). Run with `python3 -I` from the repo root.

- s26_cast.py: unify the "users disagree" pieces that session 25 left (`session 25: as ...` comments).
  - `survey [D_X ...]`: each piece's users and their declarations (block-scope externs marked).
  - `try [--apply] [--decl 'T D_X' [--inc h]] [D_X ...]`: one shared declaration in
    include/data/pieces/D_X.h; every user (hand and auto) includes it in place of its own extern
    (file scope, or after its last top `#include` when it only had block-scope externs, which go).
    A user whose own declaration differs keeps its code through casts at each use: `D_X` becomes
    `(*(T *)&D_X)` / `(*(T (*)[n])&D_X)` (the lvalue it declared, volatile kept) or `((T *)&D_X)`
    for a `T D_X[]` user; `&D_X` becomes `((T (*)...)&D_X)`. Accepted only when every changed
    file's `-S` (objects.mk recipe) is identical and gives no new warning. Candidates: the users'
    own declarations (hand files weigh 3; basic types, header types, or a local struct moved with
    type_pieces.move_types), then `void *` (4-byte pointer pieces), `s32 [n]`, `u8 [n]`.
    Without names it runs every piece whose comment still says `session 25: as`; log in try.log.
