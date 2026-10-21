## Session 26: Phase 4 types (worker s26types)

143 of the 145 "users disagree" pieces that session 25 left (`session 25: as <decl>: ...`) are typed:
each has include/data/pieces/D_X.h, and every C user includes it in place of its own extern(s), file
scope or block scope. `make` stayed byte-identical after every batch; every changed file's `-S` was
checked against the previous version (no new warning). 383 C files changed (276 hand, 107 auto),
178 new headers (143 pieces, 35 types), all compile on their own (s26_hdrcheck.py). The shift/float
build was not run (types emit no code and the objects are byte-identical; another worker owns the float).

| how | pieces |
| --- | ---: |
| one declaration, users whose own type differs cast at each use (s26_cast.py) | 128 |
| a union of the users' views, each user names its member (s26_union.py, by hand for the UV tables) | 12 |
| one declaration, users convert values (D_0046A040, D_003DABD0) | 2 |
| a struct the users index differently (D_0048C6F0 `V4i_48C6F0 { s32 v[4]; } [8]`) | 1 |
| left untyped (D_002E26A0, D_003044D8) | 2 |

The shared types: 36 `s32`, 31 `u8 [n]` (byte blocks seen as several structs), 9 `void *`,
6 `f32`, 5 `u32`, and about 50 struct/union types (moved from the chosen user into include/data/types,
or self-contained in the piece header under a unique name: SV62B4, Blk26C0, UvTab16, U<addr>...).

### What changed in the users

- A user whose declaration differs keeps its exact code through casts at each use: an int/pointer
  scalar is read as a converted value (`((Grid *)D_X)`), stored as one (`D_X = (s32)p;`); other views
  use the lvalue they declared (`(*(Cam *)&D_X).unk7C`, `((f32 *)&D_X)` for a `T D_X[]` user,
  `((T (*)[n])&D_X)` for `&D_X`). Volatile users keep `volatile` in their cast. A pointer-array user of a
  pointer-array name converts each element read (`((Act *)D_X[i])`).
- Unions (D_002BC0C0/F0, D_002BC0A8, D_00304DB0, D_00351A30, D_003F2C40, D_003E3D70, D_0037A380,
  D_00364130, D_0035BD40, the UV tables D_002A3F60/D_002A4060): the piece header holds one uniquely named
  copy of each view's type (`View30_2BC0C0`, with the view's own typedef dependencies and struct tags)
  and `typedef union { ... } U<addr>;`; the user's typedef becomes an alias (`typedef View30_2BC0C0 View30;`)
  where it was, and its code names its member (`D_002BC0C0.view30`, `D_002A3F60.f[i][0]`). A view whose
  type lives in a data/types header shared with other files brings that header into the piece header.
- A few lines were only reformatted (an extern split from a typedef or a prototype on the same line).
- `.s` comments: `/* data/pieces/D_X.h */` as before.

### Hazards

- **Union member accesses get alias set 0 in gcc 2.96** (type punning through a union is allowed), so a
  user whose scheduling relied on type-based aliasing changes code through a union (D_003044D8's s8_lead,
  most of D_002E26A0's users). Casts through a pointer (`*(T *)&D_X`) also change the MEM flags
  (MEM_IN_STRUCT_P / scalar) and can move loads; value casts of a scalar (`(T *)D_X`) and element casts
  (`(T *)D_X[i]`) were not seen to change code in this session (the -S check still decides each file).
- An array declaration vs a scalar one changes code too (an `ARRAY_REF` is in-struct, a scalar `VAR_DECL`
  is not): src/auto/text_00120000_15.c reloads D_002E26A0 after a store only when it is a scalar.
- The `-S` check now accepts output that differs only in local label numbers (`$L12`/`$LC3`, renumbered by
  first use; `S26_STRICT=1` for exact): gcc's label counter moves when a declaration moves. `make` checks
  the bytes.
- Several pieces' records overrun the piece (D_003F2C40: 0x14-byte entries in 0x10; D_003E3D70: 0xe4 in
  0xe0; D_003044D8; D_003DABD0 `void *[]` with users reading [1]): their union members are zero-length
  arrays (`[size / sizeof]` = 0) or `[]`. The tables continue into the next pieces (split_check groups).
- D_00308CDC is `void *volatile` (h56's store needs it); the other users read it through a non-volatile
  cast, exactly as before. Shared declarations are not a statement about the qualifier the data needs.
- The piece headers are included where the extern was, mid-file; moving them changes nothing only if the
  types they bring do not clash (s26_hdrcheck.py checks each header alone, not every combination).

### Left

- D_002E26A0 (63 users, 0xc): `void *D_002E26A0[3]` with element casts keeps every hand user, but
  src/auto/text_00120000_15.c needs a scalar `void *` declaration (see above). Typing it needs that auto
  function's code written another way.
- D_003044D8 (7 users, 16-byte records): six views; s8_lead's ColEntA changes code through a union or a
  cast, c02/s6_03 change under ColEntA. Needs one merged record struct and the users' field accesses
  rewritten to it, function by function.
- The 128 cast-unified pieces are correct but not pretty: many users still see their own struct through a
  cast. Folding their views into one struct (or a union, where no user depends on TBAA) is the next step.
- The 63 "no C user declares it (merged)" pieces: none has a C user of its head (three heads are named
  only by their own label headers), so nothing was typed there.

Helpers: tools/shift/s26types/ (README there): s26_cast.py (one declaration + casts; `hdr` for hand
unifications), s26_union.py (union of views, `--elem`, `--cast F`), s26_check.py (-S of changed files vs
HEAD), s26_hdrcheck.py.
