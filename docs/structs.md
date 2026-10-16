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
- `+0x160` is a 64-bit flag word in other functions (`|= 1`, `|= 0x40`,
  `>> 0x23 & 1` at `+0x370` similarly); `+0x164` is also read as an s32,
  so the struct keeps `unk164` and leaves 64-bit accesses at `+0x160` as
  `M2C_FIELD`. A union would let both be fields.
- `+0x288`/`+0x28C`/`+0x290` are written together (`func_00131c08`
  sets them from three float arguments).

To extend: rerun `tools/structs.py apply --seed func_00131c08 --struct Actor
--header include/actor.h --write` after new matches (it regenerates the
header from all evidence and only rewrites functions still using
`M2C_FIELD(arg0, …)`), then `make`.
