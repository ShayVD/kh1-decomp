# s29types: one shared type for a piece and its users' locals (session 29)

Run each with `python3 -I` from the repo root.  They use the s27types libs
(`s27lib`: recipes, compile, HEAD export); set `S27_DIR` to a private scratch
directory and `S27_JOBS` (default 2) for parallel compiles.  `make` stays the
final check (byte-identical); `s27types/s27_check.py` checks every changed file
and every includer of a changed header.

- `s29_stabs.py [--flat] FILE.c TYPE..`: layouts of a file's types read from
  gcc's stabs (`-gstabs` added to the file's recipe): offset, bits, type of every
  member, by full path with `--flat`.  Exact for anything gcc can compile, headers
  included (no C parsing).
- `s29_used.py FILE.c TYPE [ALIAS..]`: the fields of TYPE the file reads and on
  which lines: the file's uses of TYPE point at a copy with every member renamed,
  gcc's "has no member named" errors are the accesses.
- `s29_retype.py FILE.c TYPE --shared S --header H [--map f=g] [--objtag T2=TAG]
  [--sub 'OLD=>NEW'] [--hdr H2] [--shift N] [--apply | --force]`: TYPE becomes
  `typedef S TYPE;` and each field access is renamed to the field of S at the same
  offset with the same type (a scalar inside an S array becomes `arr[k]`, a
  top-level bit-field the bit-field at the same bits, a pointer any pointer, an
  array the S array of the same elements from the same offset; never a pad
  member).  Renames are made on the lines gcc reports, one occurrence at a time
  where a line has several.  `--hdr`: TYPE is defined in that include/ header
  (edited too); `--objtag`: the file's pointee struct gets S's tag; `--shift N`:
  TYPE's offset o is S's o - N (record views that start early / late);
  `--force` writes a step whose -S differs (the first of a two-type change).
- `s29_recfold.py FILE.c TYPE [--sub SUBTYPE]`: a D_00304BE8 record view indexed
  from the block's start: retype --shift 4 to W606Mem_304be8, then
  `((TYPE *)D_00304BE8)[k]` -> `D_00304BE8->m[k]`; restores the file unless -S is
  identical.
- `s29_uncast.py [--scalar] --types T,.. --pieces D_X,.. FILE.c..`: drops the casts
  `((T *)&D_X)` of pieces now declared with the users' type (`--scalar`: a single
  object, `&D_X`; else an array).
- `s29_asmdiff.py FILE.c [CANDIDATE.c]`: label-canonical -S diff against HEAD.
