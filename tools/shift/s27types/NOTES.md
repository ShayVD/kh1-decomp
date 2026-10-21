# Session 27: Phase 4 types (worker s27types)

Branch `s27types`, commits a5c8821..HEAD, worktree
`/home/user/kh1-decomp/.claude/worktrees/agent-a4037c9be8e4b7e13`.  `make` byte-identical
after every commit.

## Result

Counted with `s27_survey.py --summary` (casts of a piece's name in src/):

| | base a5c8821 | now |
|---|---|---|
| view casts (a user's own struct type) | 1541 in 104 pieces | 796 in 85 pieces |
| shared casts (to the folded struct, keep mode) | 0 | 188 |
| basic casts (s32, u8 *, void *, ...) | 676 | 734 |

- 43 pieces folded: 21 with no view cast left (D_002A3F3C D_002BCB60 D_002BCDA0
  D_002C5960 D_002E27C8 D_002E319C D_00304B78 D_00304C70 D_003701D0 D_003DABD4
  D_003E8E08 D_003F34B8 D_003F34C4 D_003F4CF0 D_003F7C48 D_003F7ED0 D_00425BC8
  D_004268B0 D_00426970 D_00449908 D_0048C630), 22 partly (biggest: D_00304BE8
  262->172, D_002E31B0 37->16, D_002A6238 49->34, D_002A624C 35->1, D_0037A378 18->2).
  48 piece headers carry a "session 27 folded" struct.
- 745 of 1541 view casts gone; 191 needless basic casts dropped by `s27_trim.py`.
  The basic count rose because folded users of a piece whose declaration stayed a
  basic type got value / lvalue casts to keep their code (see hazards).

## Left, and why (`s27_reasons.py` over the batch logs)

- Pointer pieces (declaration is a pointer or array of pointers, the view is behind
  it): D_00308CDC (44), D_002E3170 (20), several 1-cast pieces.  The fold handles
  `(S *)&D_X` / `((S *)D_X)` views of the object itself only.
- D_0037A380 (115, the session 26 union piece): users' views hold fields of their
  own vector types (V4, V3_2e2780) at different places, and one user warns.
- Overlaps (13 users): two users read one offset as different fields (e.g.
  D_002C1260 `mn` vs `lo`); needs a union, i.e. alias set 0 -> code changes.
- Union views (12 users): F5968 etc. are unions; folding would change aliasing.
- Field of a local non-struct type, or a local type in two places (8).
- Other users stop compiling (7) or change code (5) once the declaration changes
  (e.g. D_0029B420: indexing a scalar; D_002E2790: text_00130000_b03.c CODE).
- Keep mode needs at least 2 folded files; single-view pieces stay as cast.
- D_002E26A0 and D_003044D8 (need a code shape change): not started.
- D_00425B80, D_002C5C80, D_0039A580, D_004268E0, D_003626F0: an early full-mode fold
  gave union users value casts to the struct-typed old declaration; few, left.
- text_00210000_s6_21.c (nogcse) keeps a local `S4BE8_304be8_v` copy of the save
  block view (folding changes its code).
- Earlier folds dropped some `#include "data/types/..."` lines from piece headers
  (the old view types); make is unchanged, but a user that relied on them gets them
  from its own includes now.

## Hazards found (gcc 2.96)

- Changing a declaration's type changes the alias set of its own loads: a scalar
  declared s32 that becomes a pointer/struct changes code in plain users.  Plain
  users then need lvalue casts `(*(s32 *)&D_X)` (only done when the old declaration
  is a basic type).
- A bigger header changes code in unrelated later functions of a file (address
  hashed tables; e.g. text_00150000_h58.c func_00157a30).  Split mode: the struct
  goes to `D_X_s.h`, only folded users include it.
- `void *` vs `struct S *` declaration also changes code (h58).
- Union member accesses get alias set 0, so union views are not merged.
- Array vs scalar declarations change addressing; arrays of struct with different
  lengths are joined, reframing only when all used subfields stay in one element.
- Signed / unsigned field differences are accepted when `-S` stays the same.

## Tools

See README.md: s27_fold (with s27_layout, s27_merge, s27_ctext, s27lib), s27_batch,
s27_reasons, s27_survey, s27_trim, s27_unfold, s27_check, s27_hdrcheck.
