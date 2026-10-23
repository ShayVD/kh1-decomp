# s30types: session 30 Phase 4 types helpers

Run with `python3 -I` from the repo root; they use the s27types libs (`s27lib`),
`S27_DIR` for scratch.  `make` stays the final check (byte-identical).

- `s30_hdrdiff.py HEADER..`: `-S` of every source that includes HEADER (an
  include/ path such as `data/pieces/D_002A6238.h`), directly or through other
  include/ headers, against HEAD; SAME / CODE / NOCOMPILE per file.  Use it
  after changing a shared piece header (a union member, a renamed pad), before
  `make`.

Session 30 also changed `s29types/s29_retype.py`: it refuses a map that renames
a field of the file's type to another field while the shared type has a field of
the same name elsewhere ("name clash"): gcc reports no error for such an access,
so it was left pointing at the shared type's field (h1's s16 `d` at 0x6 against
Ent20_2a6238's f32 `d` at 0xc).  Rename it with `--sub` first.
