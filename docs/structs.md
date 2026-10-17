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

## `PppClass` / `PppEntry` (include/ppp.h), session 5

Session 4's "CompClass" is the ppp particle/effect program system. The
0x28-byte records are `PppClass` entries of the class table `D_00370200`
(236 records indexed by class id, record 0 empty); word 0 points to the
class name (`"pppMove"`, `"pppDrawMdl"`...). The 0x10-byte record whose
`+0xC` is `s32 *offsets` is a program's component, `PppEntry`
{cls, stride, data, offsets}. `func_00182d58` relocates a loaded program
(class ids become `&D_00370200[id]`). The slots, from their callers:
`+0x04` frame (every frame, `fn(obj, data, entry)`), `+0x0C` draw,
`+0x1C` con (object created), `+0x20` reset (timer back to 0), `+0x24`
des (before free), each `fn(obj, entry)`; `+0x08` and `+0x10` are never
set, `+0x14` (returns a float) is set by 3 classes and `+0x18` by
`pppKeAcmSolid` only. The callbacks find their data at
`obj + entry->offsets[0]`, so the data behind it has a per-class type.

`Actor +0x098` is `pair`: `func_00137308(a, b)` sets it both ways.
