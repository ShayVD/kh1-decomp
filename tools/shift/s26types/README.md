Session 26 Phase 4 helpers (worker s26types; docs/shiftable-plan.md "Session 26: Phase 4 types").
Scratch output goes to $S26_DIR (default /tmp/s26types). Run with `python3 -I` from the repo root.
One compile pool at a time (each tool compiles with 3 threads).

- s26_cast.py: unify the "users disagree" pieces that session 25 left (`session 25: as ...` comments).
  - `survey [D_X ...]`: each piece's users and their declarations (block-scope externs marked).
  - `try [--apply] [--decl 'T D_X' [--inc h]] [D_X ...]`: one shared declaration in
    include/data/pieces/D_X.h; every user (hand and auto) includes it in place of its own extern
    (file scope, or after its last top `#include` when it only had block-scope externs, which go).
    A user whose own declaration differs keeps its code through casts at each use: int/pointer
    scalars convert the value (`((T *)D_X)`, stores `D_X = (S)v;`), other views use the lvalue they
    declared (`(*(T *)&D_X)`, `((T *)&D_X)` for a `T D_X[]` user, `((T (*)[n])&D_X)` for `&D_X`),
    pointer-array users convert each element read (`((T *)D_X[i])`). `__asm__("D_X")` alias externs and
    `#define D_X D_X_alias ... #undef D_X` regions name other C objects and are left alone.
    Accepted only when every changed file's `-S` (objects.mk recipe) is identical up to local label
    numbers (`S26_STRICT=1`: exact) and gives no new warning. Candidates: the users' own declarations
    (hand files weigh 3; basic types, header types, or a local struct moved with
    type_pieces.move_types), then `void *` (4-byte pointer pieces), `s32 [n]`, `u8 [n]`.
    Without names it runs every piece whose comment still says `session 25: as`; log in try.log.
  - `hdr --decl 'T D_X' [--inc h] [--note text] D_X`: write the header and mark the piece for a
    unification done by hand (check the users with s26_check.py).
  - `S26_KEEP=1`: a refused file's old/new `.s` (and new source) go to $S26_DIR/keep/.
- s26_union.py `[--apply] [--elem] [--cast FILE ...] D_X ...`: the piece as a union of its users'
  views. Each distinct view type is copied into the piece header under a unique name (`<T>_<addr>`,
  with the file's own typedefs it depends on and its struct tags); the user's typedef(s) become aliases
  (`typedef View30_2BC0C0 View30;`) where they were, and its code names its member (`D_X.view30`).
  A type in a data/types header shared with other files is included instead. `--elem`: one union per
  element (`extern E D_X[];`, `D_X[i].m`). Users whose member access changes code fall back to casts
  (tries up to S26_TRIES, default 6). Note: gcc 2.96 gives union member accesses alias set 0.
- s26_check.py `[FILE.c ...]`: `-S` of each file (default: every src .c that differs from HEAD) vs HEAD.
- s26_hdrcheck.py `[REF]`: each include/data header added since REF compiles on its own.
