# Recovered structs

Struct layouts recovered so far. Field names are offsets (`unkXXX`) until
their meaning is known; rename them as evidence appears, keeping `make`
byte-identical.

## `Actor` (include/actor.h), session 3

The biggest group from `tools/structs.py`: 324 functions in
`0x001063C8`-`0x001DCB00` that hand the same first argument to each other.
Recovered from 23 matched functions plus 171 unmatched m2c drafts; 90
fields up to `0x414`, so the struct is at least `0x418` bytes. "Actor" is a
provisional name: it is the object most game logic passes around (it has
float fields in the `0x280`-`0x414` range, flag words, and pointers to other
objects of the same kind, e.g. `+0x98` is read and used with the same
`0x16C`/`0x280` fields), but what it represents is not confirmed.

Known so far (from the access patterns, not names):

- `+0x000` s32 bit flags (`& 0x800000` tests).
- `+0x160` is a 64-bit flag word (`|= 1`, `|= 0x40`; `+0x370` is another,
  `>> 0x23 & 1`) whose halves are also read as s32. Session 4: it is a
  union, `unk160_64` (s64) over `unk160`/`unk164` (s32); `+0x000` the same
  (`unk000_64`). `tools/structs.py` makes such a union whenever an 8-aligned
  offset is accessed both as 64-bit and as 32-bit words.
- `+0x098` is `struct Actor *` (another object of the same kind:
  `--self-ptr 0x98`). Accesses through it, and temps that only hold it, are
  rewritten too; no matched function used it yet at the end of session 4.
- Functions whose `arg0` is a `T *` used only as `*arg0` join the struct
  (`*arg0` is field `+0x000`).
- 29 matched functions take `Actor *` (session 4).
- `+0x288`/`+0x28C`/`+0x290` are written together (`func_00131c08`
  sets them from three float arguments).

To extend: rerun `tools/structs.py apply --seed func_00131c08 --struct Actor
--header include/actor.h --self-ptr 0x98 --write` after new matches (it regenerates the
header from all evidence and only rewrites functions still using
`M2C_FIELD(arg0, …)`), then `make`.

## `CompClass` (include/compclass.h), session 4

A component "class" record, 0x28 bytes. About 224 of them sit in arrays in
data between `0x00304B5C` and `0x00425BB4` (consecutive records 0x28 apart;
found by scanning for 10-word records whose words are all 0 or function
starts except `+0xC`, which points into `0x004xxxxx` data). `+0xC` is
`s32 *offsets`, an array of byte offsets; the other nine words are
callbacks (or 0), e.g. `0x003715F4`: `{func_0018c630, 0, 0, &D_0048F278,
func_0018ccf0, 0…}`.

The callbacks are called as `fn(base, class)` and find their data at
`base + class->offsets[i]` (`arg0 + *M2C_FIELD(arg1, s32 **, 0xC)` in m2c
output: the "component family" around `0x00180000`-`0x001A5000`). The
same function serves every object that embeds the component, so the data
behind the offset has no single type: it differs per class (often a
sub-struct at `+0xA0`). 99 matched functions take `CompClass *arg1`
(rewritten with a one-off script: `arg1` used only as
`*M2C_FIELD(arg1, s32 **, 0xC)` / `M2C_FIELD(M2C_FIELD(arg1, void **, 0xC),
s32 *, 4n)`). What each slot is for (init, update, draw…) and what `base`
is (probably an Actor or a part of one) are not known yet.
