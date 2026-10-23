# s31types: session 31 Phase 4 types helpers

Run with `python3 -I` from the repo root.  They use the s27types libs
(`s27lib`, with `S27_DIR` for scratch), and s31_merge also uses s29types.  Each
one compiles the changed file with `-S` and compares it with HEAD.  `--apply`
writes the file only when the result is SAME.  `make` stays the final check
(byte-identical).

- `s31_recast.py [--apply] FILE.c VIEW SHARED D_X ..`: after `s29_retype` made
  VIEW `typedef SHARED VIEW;`, this renames the casts of the given pieces
  (`(VIEW *)&D_X`, `(VIEW **)&D_X`, `(volatile VIEW *)&D_X`, `(VIEW *)D_X`) to
  SHARED, so the survey counts them as shared.  It drops the alias typedef once
  nothing else uses it.  Do not recast to a declared type when the cast is an
  lvalue (`(*(T **)&D)`): see Hazards in docs/shiftable-plan.md, session 31.
- `s31_tag.py [--apply] FILE.c TAG TYPE[,TYPE2..] [--uncast D_X ..]`: for a piece
  declared through an incomplete tag (`struct Actor *D_002E26A0[3];`), this gives
  the file's own view the tag, as in the VmObj precedent.
  - The first TYPE's `typedef struct [OLD] {..} TYPE;` becomes
    `typedef struct TAG {..} TYPE;`.  An old tag is renamed throughout the file,
    and aliases (`typedef X TYPE;`) are followed.
  - A further TYPE becomes `typedef struct TAG TYPE2;` only when its body is a
    copy of the first.  Otherwise it is reported; merge it first with s31_merge.
  - `--uncast D_X` drops `((TYPE *)D_X[k])`, `(TYPE *)D_X[k]` and
    `(*(TYPE **)&D_X)`, which becomes `D_X[0]`.
- `s31_merge.py [--apply] FILE.c A B [B2 ..]`: merges a file's second views of one
  object (at the same base) into the first.
  - Each B member that A lacks goes into A at its stabs offset, using the
    declaration text from the source, and the pads are recomputed.  B becomes
    `typedef A B;`.
  - Typedefs that the moved members need are hoisted above A, and a B's struct
    tag passes to A.
  - It refuses overlapping members, a name that A uses at another offset, and
    anonymous members.
- `s31_warndiff.py NAME|FILE.c ..`: lists the warnings that appear only in the
  work tree, compared with HEAD, for every src/ file that mentions NAME (or for
  each FILE.c given).  A retype that keeps the code can still add warnings, such
  as a pointer passed to an s32 parameter.  Session 31 kept this at 0.

Count the casts with `python3 -I tools/shift/s27types/s27_survey.py --summary
[--views]`, without changing the survey.  Check a shared header change with
`s30types/s30_hdrdiff.py HEADER`.
