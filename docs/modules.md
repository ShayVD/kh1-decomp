# Modules (phase 4: from address groups to real source files)

`src/auto/text_XXXX0000*.c` (autodecomp output, one file per 64 KiB, `_N` when
m2c's externs clashed) and `src/hand/text_XXXX0000_<worker>.c` (hand matches,
one file per worker and range) are provisional: they group functions by address
and by who matched them, not by what they do. The original translation units
are unknown. A **module** is a named source file (or a few, see "Flags") that
holds functions that belong together, typed with shared headers instead of
per-file views. Session 30 moved the first one; this page says what that takes.

## The first module: src/vm/ (session 30)

| file | functions |
|---|---|
| `src/vm/script_vm.c` | 55: every function from 0x001c08e8 to 0x001c4ed0 except the five below, in address order |
| `src/vm/script_vm.nosi.c` | func_001c1718 (needs `-fno-sched-interblock`) |
| `src/vm/script_vm.nostrict.c` | func_001c1980, func_001c3770, func_001c4808, func_001c48c8 (need `-fno-strict-aliasing`) |
| `include/vm/script_vm.h` | `VmOp`, D_0037A198, `VmMsg`, and prototypes of the functions other code calls |
| `include/vm/vm_mgr.h` | `VmMgr`: D_00389C90, the script manager state |

The module was moved in two steps the same session (commit 48d76fe: the
handlers, as `vm_ops.c`; then the runtime). Both halves match together in one
file, in address order, with the default flags, so they were probably one
translation unit, and they now are one file again.

**The handlers, 0x001c08e8-0x001c1d20 (37 functions).** The interpreter loops
run `op = func_001c1ce8(code, pc); arg = func_001c1cf8(code, pc); r =
D_0037A198[op](vm, arg);`. D_0037A198 is a table of 32 function pointers (read
from the ELF): 30 of them are the handlers in 0x001c08e8-0x001c1b58, the other
two are func_001cd208 (opcode 1, src/vm/vm_calc.c since session 31) and func_001dcad0
(opcode 24, still in src/auto; see "Session 31"). The rest of the
range is what those handlers call: the type clamp func_001c0bf0, the save block
accessors func_001c0da0 / func_001c0e50 / func_001c0e80, the cross-VM jump
func_001c1980 (called by the handler func_001c19f8) and the instruction fetch
pair func_001c1ce8 / func_001c1cf8. Each handler's comment gives its opcode
(its index in D_0037A198).

**The runtime, 0x001c1d20-0x001c4ed0 (23 functions).** The loops that call
D_0037A198 (func_001c1d20 runs one VM from a label, func_001c1f80 /
func_001c3408 / func_001c3b10 are per-frame drivers, func_001c2778 runs the
init labels), the script loaders that fill the VM tables (func_001c2ec8,
func_001c3770, func_001c4198, with the string table parsers func_001c2d20 /
func_001c2df0 and the manager reset func_001c29d8), the two message queues
(func_001c4640 / func_001c45e8 on D_006257E0, func_001c4788 / func_001c4730 on
D_006277F0), and the entry points other code calls to start scripts and send
events (func_001c4808, func_001c48c8, func_001c4d90, func_001c4de0,
func_001c4ed0). Every function of both ranges moved: the module is contiguous.
The names stay `func_XXXXXXXX`; none is registered in functions.tsv.

**Where they came from** (60 functions from 17 files): src/auto/text_001c0000.c
(14), src/auto/text_001c0000_8.c (1), src/auto/text_001c0000_9.c (1),
src/hand/text_001a0000_b09.c (1), src/hand/text_001a0000_c08.c (1),
src/hand/text_001a0000_h41.c (8), src/hand/text_001b0000_h14.c (11),
src/hand/nostrict/text_001b0000_h14.c (1), src/hand/text_001b0000_h66.c (3),
src/hand/text_001b0000_s6_13.c (6), src/hand/text_001c0000_b10.c (1),
src/hand/nostrict/text_001c0000_b10.c (2), src/hand/nostrict/text_001c0000_c09.c (1),
src/hand/text_001c0000_h42.c (6), src/hand/text_001c0000_s11_w1.c (1),
src/hand/text_001c0000_s11_w1b.c (1), src/hand/nosi/text_001c0000_s7.c (1).
Seven files were left empty and deleted (auto _8 and _9, nosi/s7, nostrict/b10,
nostrict/c09, s11_w1, s11_w1b), with nostrict/b10's type header.

**Types.**

- Every VM is a `VmRec *` (include/data/types/vm_rec.h), replacing the files'
  views: h14's / h41's / s7's `VM` and `VM_1c0b40`..`VM_1c13e8` (`stack`, `regs`,
  `vars`, `vidx`, `w756`, `depth`, `flags` became `stk`, `var`, `x270`, `x2f0`,
  `x2f4`, `rsp`, `fl.x`), the VmRec aliases (VM, VMa, VmC, VmE, VM_c2778 ...),
  h42's `P` (`a[]` is `lbl`, `b[]` is `ret`) and the M2C_FIELD offsets.
- D_00389C90 is a `VmMgr` (include/vm/vm_mgr.h), replacing ten views (h14, h42,
  h66 and c08 through `#define D_00389C90 (*(View *)&D_00389C90)`, b09, b10,
  nostrict/b10, nostrict/c09, s11_w1, s11_w1b; the auto file indexed it as
  `s64[]`). Where views disagreed the field is a union and each function keeps
  the member its code needs: the flag words at 0x3070 / 0x3078 are `.x` (u64:
  s6_13, b10, h14's `d12408`), `.b` (u32 bit-fields: c08, c09, s11_w1, s11_w1b)
  or `.w` (u64 bit-fields: b09); 0x3180 is h42's `box[15]` or (`.u.s`) the slots
  at 0x3384 and their neighbours. Other renames: c08's `A`..`D` are `a1034` ..
  `a2834`, `e[i].a..f` (c08, b09) are s6_13's `obj, x4, snd, ret, x10, h`,
  h66's `w12340` is `x3034`, s11_w1's `x3178` is h42's `nbox`, b10's `f314c` is
  `x314c`. `x3148` is u32 (c08's `(x3148 >> 23)` needs the logical shift; b09 and
  b10 only store -1). VmMgr ends at 0x3454, under the 0x34d8 other files declare.
- The messages are `VmMsg` (script_vm.h; c08's / h42's / h66's / s11_w1b's
  `Msg`, s6_13's `MsgC` prefix, h14's `{u64 a, b, c, d}` and s6_13's `MsgQ` for
  the queue copies; all gave the same code). D_002C5BB0 is s11_w1b's `S5BB0`
  (c08's `w4, w8, a[], b[]` are `x4, x8, x40[], x60[]`).
- Changed code: func_001c1cf8 needed m2c's operand order (`pc * 4 +
  (s32)code`); calls that passed an `s32` where the module's prototype takes
  `s8 *` got a cast (func_001c4d90, func_001c4808, func_001c48c8).

**Hazards found.**

- A prototype's return type matters even when the result is unused:
  func_001c4de0 only matched with h42's `s32 func_001d59a0(VM *)`, not `void`
  (v0 is clobbered by the call, which changes the register allocation of the
  stores after it). Copy callee prototypes exactly.
- `volatile` matters: h42 declares `extern volatile s32 D_002BBE04`, the piece
  header plain `s32`; the module keeps h42's declaration.
- func_001c4ed0 matched in s6_13 only because a CONTEXT_ONLY copy of
  func_001c1ce8 was above it; in the module the real definition is above it,
  so a separate file for the runtime half failed there and the merged file
  does not.

## Session 31: the rest of the VM, and src/camera/

| file | functions |
|---|---|
| `src/vm/vm_calc.c` | opcode 1: the 18 operations func_001cce38-func_001cd1d0, their table D_003C5898 (defined here) and the dispatcher func_001cd208 |
| `src/vm/vm_find.nofill.c` | func_001e98d0, func_001e99e8, func_001e9b98: the walks over VmMgr's VM list (need nofill) |
| `include/vm/vm_find.h` | their prototypes (script_vm.c includes it) |
| `src/camera/camera.c` | 46: the camera core 0x001c5168-0x001c6d08 and its script functions 0x001c6d08-0x001ca9e8, in address order, except the nine below |
| `src/camera/camera.nostrict.c` | func_001c6d08, func_001c71e8, func_001c7700, func_001c7c18 (load and play camera path k), func_001c8c90, func_001c8d98, func_001c9ca8, func_001ca060 (start channels 2 / 3) |
| `src/camera/camera.nostrict_nofill.c` | func_001c53c8 (interpolate the path at a time) |
| `include/camera/camera.h` | `CamState` (D_003C5510, 0x130 bytes), `CamVec`, `CamV4q`, the core prototypes |

func_001c62a0 (0x001c62a0-0x001c671c, a second path loader) is not matched and
stays original bytes at its place in the camera range.

**Where the boundaries are, and the evidence.**

- *script_vm.c ends at 0x001c4ed0.* Every function from 0x001c08e8 to
  0x001cd300 matches in one file with the default (or nofill) flags, and the
  camera core matches appended to script_vm.c too, so matching cannot place the
  boundary. The types and the call graph do: from 0x001c5168 on the code works
  on D_0037A380 / D_003C5510 and the view (D_002E2780 ...), shares no type with
  the VM, and calls nothing in it; the VM calls only func_001c6720 (reset, at
  script load) and func_001c5b88 (play, every frame). The data agrees: the
  VM's D_0037A378 is directly followed by the camera's D_0037A380.
- *The camera core and its script functions are one file.* The script
  functions match only with func_001c6890 defined above them (h66's
  func_001c91e8, s11_w1d's func_001c99a8: branch-likely vs plain branch without
  it), and func_001c6890 is a core function.
- *The camera ends at 0x001ca9e8.* func_001ca800 (run the active tweens every
  frame) is the last function that touches D_003C5510; from 0x001ca9e8 on the
  functions (h14, h42, h67, h15 ...) use VmMgr and other data. D_003D9FE0, the
  763-entry table func_001dcad0 dispatches through, starts at func_001c6d08
  (its lowest entry) and runs to 0x001ec678: the camera's 32 entries are the
  first of a long script-function library 0x001c6d08-0x001ec6xx
  (153 entries in 0x001c, 505 in 0x001d, 105 in 0x001e).
- *func_001cd208 (opcode 1) moves; func_001dcad0 (opcode 24) does not.*
  func_001cd208 sits directly after its 18 operations, and none of them is a
  D_003D9FE0 entry: the operations, the table D_003C5898 (in .data among the
  VM's) and the dispatcher are one island in the library range, so they are
  their own file. func_001dcad0 is a one-line dispatcher in the middle of the
  library (0x001dcad0) and its table names 763 functions from 0x001c6d08 to
  0x001ec678: it belongs with that library, not with the VM; it stays in
  src/auto/text_001d0000_14.c with D_003D9FE0.
- *func_001e98d0 moves with its two siblings.* func_001e98d0 / func_001e99e8 /
  func_001e9b98 are contiguous (0x001e98d0-0x001e9d00), all walk the same
  VmMgr VM list (x316c, x3034, x3038) and are called from script_vm.c; they
  match together in one nofill file.

**Where they came from.** vm_calc.c: h15 (18), auto text_001c0000_10.c
(func_001cd208 and D_003C5898). vm_find.nofill.c: nofill/h45, s6_16, h68.
camera: h66 (8), h14 (15), nostrict/h14 (4), h42 (7), b10 (4), auto
text_001c0000.c (2), auto text_001c0000_3.c (2), nostrict/c09b (4), s6_14 (2),
s9_w11 (2), s11_w15, s11_w1d, s11_w1e, s7_w19, nostrict_nofill/r2_9 (1 each).
Deleted as empty: s11_w15, s11_w1d, s11_w1e, s6_14, s9_w11, nostrict/c09b,
nostrict/h14, nostrict_nofill/r2_9, and include/data/types/text_001e0000_s6_16.h.
(Session 30's note that c09b and r2_9 were separate translation units was wrong:
they were camera functions.)

**Types.** CamState replaces the views of D_003C5510 (b10's CamS, h66's
Tw_c9ac8 / Tw_c9e80 / Tw_ca800 / Cam_c91e8, h14's Tween, h42's / h14's
D_003C55E0.. names): five tween channels (dur / t / mode, p0 -> p1), the shake,
base / pos / rot, v100 / v110 and f120..f12c (see the comment in camera.h). The
flag word is a three-way union: `fl.x` (u64, whole-word reads: func_001c5b88),
`fl.s` (u32 bit-fields, sharing the word with dur[0]) and `fl.w` (u64
bit-fields); all three occur in the original. Its size stays 0x130 (the
D_003C5510 piece), so cover_check's sizes do not change. The VM side uses
VmRec / VmMgr.

**Hazards found.**

- Union members get alias set 0: a direct store `D_003C5510.fl.s.dur[1] = d`
  gave different code from the view's; storing through a pointer,
  `(&D_003C5510.fl.s)->dur[1] = d`, matched (func_001c99a8, func_001ca0f8,
  func_001ca368). A read of a union member of D_0037A380 likewise needed a cast
  macro, `#define CAM (*(Cam_37A380 *)&D_0037A380)` (func_001c5db8).
- Which symbol an access names matters: gcc treats D_003C55F0 and D_003C5510
  as not aliasing. func_001ca5f8 / func_001ca680 / func_001ca708 were 8 bytes
  short through D_003C5510.rot and matched with `CamVec *b = &D_003C55F0;`
  (b[-1] the position, b[4][0] f120). Keep the symbol the matching file used.
- `*(s32 *)&D_003C5510.st = 0` is 8 bytes longer than `D_003C5510.st = 0`.
- The same "callee defined above" effect as func_001c4ed0 above: removing
  func_001c6890 from h66 made h66's func_001c91e8 NONMATCHING until a
  CONTEXT_ONLY stub stood in (both are in camera.c now). Probe before moving:
  a CONTEXT_ONLY definition of the callee above a candidate shows whether it
  needs one. The 15 retyped func_001c4640 callers showed no change.
- The float keep list grows by six names, D_003C55E4 / E8 / F4 / F8 / D_003C5630
  / 34: addend_check now sees `D_003C5510+0xd4` ... from the camera functions
  that used to name those labels. They are PIECE_LABELs inside the one
  D_003C5510 piece (already kept), so nothing moves differently: with
  `SHIFT_FLOAT_FORCE` releasing exactly these six the list equals the base and
  kh1-shift.elf is byte-identical to the build that keeps them.

**Retypes.** The 15 `void func_001c4640(Msg *)` users (h15, h16, h17,
nofill/h17, h18, h19, h21, h43, nofill/h43, h44, h45, h67, nostrict_nofill/h67,
s11_w1c, s19_s19m1) include script_vm.h and use VmMsg; h44 and h45 lost local
prototypes that conflicted with the header (calls got `(s8 *)` casts); s19m1
keeps its `volatile` message and passes `(VmMsg *)&m`. No code changed.

## Session 32: the message windows, and the library file src/vm/vm_lib.c

| file | functions |
|---|---|
| `src/msgwin/msgwin.c` | 44: every function from 0x001ca9e8 to 0x001cce38, in address order, with the data D_0062A1E0, D_0062A1F0 and D_00629920 |
| `include/msgwin/msgwin.h` | `MsgWin` (the 0xb0-byte template / window record of D_006298F0[8], D_00629E70[4], D_0062A130) and the two functions other code calls |
| `src/vm/vm_lib.c` | the library file's first 32 functions, 0x001cd238-0x001cdf98, except the two below; then opcode 24's table D_003D9FE0 and its dispatcher func_001dcad0 |
| `src/vm/vm_lib.nofill.c` | func_001cd2d8 (send message 2: turn towards a point) |
| `src/vm/vm_lib.nostrict.c` | func_001cd600 (set the entity's rotation from degrees); func_001cf348 (second half) |
| `src/vm/vm_lib.nostrict_nofill.c` | second half: func_001ce4b8, func_001ce5f0, func_001ce750, func_001ce880 (turn to a heading: messages 4 / 21 / 22) |
| `include/vm/vm_obj.h` | second half: `struct VmObj`, the entity as the four vm_lib files read it |

The second half of the session (below) moved 241 more functions, 0x001cdf98-0x001d5408, into the same four files.

**The message windows, 0x001ca9e8-0x001cce38 (44 functions).** Evidence:

- *Data.* Their constants D_003C5640-D_003C5890 (the strings and tables in
  func_001cb120, func_001cb440, func_001cb738, func_001cb7d0, func_001caa20,
  func_001cccf0, func_001cafe8 ...) sit between the camera's D_003C5510
  (0x130 bytes, ending at 0x003C5640) and opcode 1's D_003C5898: the same
  order as the code (camera, message windows, vm_calc). No other code uses
  them.
- *Shared state.* All of them work on the window templates D_006298F0[0..7],
  the 4 open windows D_00629E70 and D_0062A130 (entry 12 of the same 0xb0
  array), and VmMgr's window fields: wst[4] (0x0, state of open window i),
  tst[8] (0x4, state of template k), xc (0xc), tbl[8][256] / cnt[8] (the
  message ids queued per template) and ids[4] (0x1030, the template each window
  shows). The views were h14's / s7_w24's `Big` (b, c, u.d, w, idx), h42's
  (b0, b4, bc, h10, w1010, c1030), h67's / s7_w3's `Str` (st, x4, tbl, cnt,
  ids), h15's (a, b, c) and s7_w37's `BigE`; all now VmMgr.
- *Call graph.* The script functions start a window with func_0010bdd0 /
  func_0010ef70 / func_0010bd90 and a callback from this group (func_001cae20,
  func_001cafe8, func_001cbab0, func_001cbd80, func_001cbea0, func_001cac60,
  func_001ca9f8 / func_001caa20); outside callers are only script_vm.c
  (func_001cab48, the template reset at script load) and h45 (func_001caf58,
  close all), declared in msgwin.h.
- 30 of the 44 are D_003D9FE0 entries (0-7, 33, 80-83, 88, 89, 107, 153,
  176-180, 358, 359, 365, 475, 605, 695, 741, 753, 754); the other 14 are the
  callbacks and the two resets.
- Everything matches in one file with the default flags, including
  func_001cac98 (s7_w37), whose old file's comment ("6 words off, nostrict")
  was stale.

Where they came from: h14 (8), h42 (8), h67 (4), h15 (11), b10 (1), s7_w24
(1), s7_w3 (1), s8_w20 (2), s7_w37 (1), auto text_001c0000.c (2),
text_001c0000_2.c / _6.c / _7.c / _11.c / _12.c (1 each). Deleted as empty:
s8_w20, text_001cac98_s7_w37.c, auto _7, _11 and _12.

Types: `MsgWin` is h42's / s8_w20's `Obj` (h15's and h67's `Win { u64 d[22]
}` gave the same struct copies). VmMgr's `u8 x0[0x10]` became `wst[4]`,
`tst[8]`, `xc[4]` (indexed up to 7 by the resets, as h42's `bc[4]` was) and
its pad at 0x3144 `s32 *x3144` (h14's p12612, where the choice callback
stores the answer). The VMs are VmRec; func_001cb440's view from +4 is a local
`MsgVmSub` taken as `(MsgVmSub *)&vm->obj`, and it matched.

Kept as they were: func_001ccda8 / func_001ccdf0 keep m2c's s32-arithmetic
bodies and the volatile labels D_00629920 (defined here) / D_00629924; two
VmRec forms tried were 9-17 words off. func_001cc170 / func_001cc1c0 keep
h14's labels D_006298F6 / D_006298F8 (`MsgWinH`): writing
`D_006298F0[k].h6 / .h8` matched too, but cover_check then no longer saw
D_006298F8 and float_covered.txt lost it (.bss 52 bytes shorter). Keep the
labels a function used when cover_check lists them.

**h42 retype.** h42 includes script_vm.h; its five message senders use VmMsg,
and the CONTEXT_ONLY func_001c4640, the queue externs and D_0037A21C are gone.
No code changed (the probe of session 31 was right).

**The library file: 0x001cd238-0x001dcad0.** D_003D9FE0 (763 entries) is
not one module's list: entries 0-7 are message windows, 34-52 and 13 later
ones camera, and 547 entries lie in 0x001cd238-0x001dcad0.
Sorted by address those 547 indices form an increasing run of 480 (53
inversions), from entry 8 (func_001cd280) to the last entry, 762
(func_001dca48), which is the last table entry before func_001dcad0. After the
dispatcher no function up to 0x001ddc78 is an entry; the remaining 154 entries
(0x001ddc78-0x001ec678) belong to later code. The library data agrees: the
string tables D_003C58E0 / D_003D97E0 (func_001cf478 / func_001cf5d0), then
D_003D9FE0 itself, then D_003DABCC / D_003DABD0 ... used from 0x001cd238 on.
So 0x001cd238-0x001dcad0 looks like one source file of about 600 functions
that ends with the dispatcher (func_001dca88, a non-entry just before it, is
still to place). It is src/vm/vm_lib.c, filled from both ends:

- the dispatcher and the table moved first: `s32 func_001dcad0(VmRec *vm, s32
  k) { return D_003D9FE0[k](vm); }` (the handler returns the library
  function's result), the table typed `VmLibFn D_003D9FE0[0x2fb]` with
  `s32 func_X();` declarations of its 763 entries;
- then 0x001cd238-0x001cdf98 (34 functions, from h15 (17), h42 (1), auto
  text_001c0000.c (11), text_001c0000_3.c (1), s6_na (1), s6_nb (1), nofill/s9_w7
  (1), nostrict/s7_w24 (1)) above it. h15 and nofill/s9_w7 were left empty and
  deleted. VmRec replaced the views (h15's `VM`, s6_na / s6_nb's `VM` and
  `Msg`, s7_w24's union VM, s9_w7's VM5 / Obj5); `struct VmObj` is completed
  with pos (0x10), rot (0x30) and flags (0x370). The m2c bodies of the
  `vm->sp - 1` and `func_00106780(stk[sp])` functions were rewritten on VmRec
  and match. func_001cd2d8 keeps its message view Msg2 (`u32 val:24`; VmMsg's
  u64 bit-field reads differently) and passes `(VmMsg *)&m`.

When a later move puts a library function above the table whose definition
disagrees with `s32 func_X();` (a `void` one), change that declaration.

**Checks after each commit.** `make -j4` byte-identical (6979 functions),
`make report` 6979 at 100%, `s31_warndiff` no new warnings in the edited
files, and the m12 float build: float_covered.txt identical to the base, and
kh1-shift.elf has the same symbols at the same addresses (nm) and the same
loaded sections. objdiff units: 924 -> 920 (msgwin) -> 921 (vm_lib.c, its two
siblings, minus h15 and s9_w7).

**Files edited** (for the types worker's merge): include/vm/vm_mgr.h,
src/hand/text_001b0000_h14.c, text_001c0000_h42.c, text_001c0000_h67.c,
text_001c0000_b10.c, text_s7_w24.c, text_s7_w3.c, text_00100000_s6_na.c,
text_001c0000_s6_nb.c, nostrict/text_s7_w24.c, src/auto/text_001c0000.c,
text_001c0000_2.c, text_001c0000_3.c, text_001c0000_6.c, text_001d0000_14.c.
Deleted: src/hand/text_001c0000_h15.c, text_001c0000_s8_w20.c,
text_001cac98_s7_w37.c, nofill/text_001c0000_s9_w7.c, src/auto/text_001c0000_7.c,
_11.c, _12.c.

### Second half: 0x001cdf98-0x001d5408 (241 functions)

Six chunks, each its own commit, in address order above the table (the
sibling files take the functions whose old file had other flags):

| chunk | functions | into vm_lib.c | siblings |
|---|---|---|---|
| 0x001cdf98-0x001cfff8 | 63 | 57: h16 (32), h42 (5), h67 (2), h43, s7_w22, s11_w1c, s19_s19m1, auto text_001c0000.c / _1 / _2 / _3 / _6 / _10 (14) | nostrict_nofill: h42 (3), h67 (1); nofill: h42's func_001cede8; nostrict: s7_w24's func_001cf348 |
| 0x001cfff8-0x001d17d0 | 59 | 58: the rest of h16 (13), h43 (5), h67 (2), s7_w3, auto text_001d0000.c / _1 / _2 / _7 / _8 / _10 (37) | nofill: h67's func_001d1080 |
| 0x001d17d0-0x001d3610 | 54 | 41: h17 (9), s6_15 (2), h67, b10, h43, auto (27) | nofill: h43 (8), h67 (2), text_001d0000.c (3) |
| 0x001d3610-0x001d4000 | 25 | 21: h17 (6), s6_15 (2), h43, auto (12) | nofill: h17 (3), h67's func_001d3e30 |
| 0x001d4000-0x001d4c08 | 20 | 19: h17 (6), h43, auto (12) | nofill: b10's func_001d4798 |
| 0x001d4c08-0x001d5408 | 20 | 17: h17 (4), h43 (2), auto (11) | nofill: h43 (3) |

Deleted as empty (22 files): h16, h42, b10, s7_w22, s11_w1c,
s19_s19m1, nofill/h42, nofill/h67, nofill/b10, nofill/text_001d0000.c,
nostrict/s7_w24, nostrict_nofill/h42 and h67, auto text_001c0000_1 / _3 /
_10, text_001d0000_3 / _13 / _15 / _17 / _18 / _19.  objdiff units 921 ->
900.  b10's leftover D_003C5510 / D_003C21A8 / D_003C3A70 declarations went
with it (float_covered.txt unchanged).

**Types.**  Every function is on VmRec / VmMgr / VmMsg except the four
below.  What the moves named:

- *VmRec* (data/types/vm_rec.h): `f68` / `f6c` (0x68: the target heading and
  the step, degrees, of messages 4 / 21 / 22).  Other fields the views used
  map as: cur / v08 = `p`, tgt / f14..f1c = `f14[3]`, spd = `f20`, the
  views' u64 / union flags = `fl.x`, their u32 bit-fields b0 .. b7 =
  `fl.b.bN`, h17's f318 = `rsp`.
- *VmMgr* (include/vm/vm_mgr.h): the effect fade at 0x3098 (`fxk`, `fxn`,
  `fxd[3]`, `fx[4]`, VmFx records: h16 / h42's idx, cnt, d, ptrs and Fx),
  the alpha and colour fades of D_002BC080 at 0x3128 (`an`, `ad`, `rgbn`,
  `rgbd[3]`: h16's cnt2 / step2 / cnt3 / step3), the three screen points of
  func_001d2fd8 / func_001d3078 / func_001d33c8 (`py0`, `px1`, `py1`, `px2`,
  `py2` at 0x3080; the first x is `f3078.b.hi`, since h17's `w[1]` was the
  high word of the 0x3078 flags) and `x3094`.  h67's f316c is `x316c`, the
  auto files' `D_00389C90[1550]` / `[1551]` (s64) are `f3070.x` /
  `f3078.x` and `[3154]` (s32) is `x3148`.
- *struct VmObj* moved from four copies into include/vm/vm_obj.h: x0 (a
  flag word), x4 (id), pos, rot, f3c (heading), p50 (home position), f6c,
  f130, f164, f16c, and at 0x370 a union of the u64 flags and h42's `col[4]`.
  func_001e98d0 / func_001e9b98 return `VmRec *` (the VM with that id), so
  the result views (s19's R, h17's Ent, b10's Ref, s6_15's Ent) are gone.
- *Effects*: D_0038CD3C is `VmFx *[]` in vm_lib (the piece header's `Lt *` is
  h42's view of f0c only).

Kept as they were, with a comment: func_001cf960 keeps s11_w1c's VM view
(`VmRecW`, u64 bit-fields directly in the struct; the session 11 alias-set
reason), func_001cfc28 its message with volatile type / v3 and the `$f0`
register pin (`VmMsgV`), func_001d2c68 and func_001d4798 b10's 16-aligned
message (`VmMsgA`), func_001d1080 / func_001d3e30 the message with the
step (`VmMsgD`).  func_001d2720 keeps the shared `(Cam0_2BC0F0 *)&D_002BC0F0`
cast: `D_002BC0F0.cam0.f20` (the union member) made it longer.
func_001d3828 reads `*(u8 *)(stk + (s32)D_00304BE8 + 0x499)`: indexing a
`u8 *` (two spellings) moved the add.  func_001cfed8 keeps the auto file's
s32 arithmetic as `(s32)D_002C5958 & ~4 & 0xF7FFFFFF` (with the u32 piece
type the two masks fold into one).  The two D_002C5BB4 / D_002C5BB8 reads
keep the auto file's `extern s32` (the piece declares u64 for D_002C5BB8,
which would load with ld).

**VmMgr's slots** (the D_00389C90 casts of h18's func_001d7840, in the
library range): vm_mgr.h's union at 0x3180 of h42's `box[15]` and the
eight slots is gone.  `box[10]` (0x3180-0x3360, as many as fit before the
slots; script_vm.c indexes it only by nbox) and `e[8]` at 0x3384 are plain
fields, so `D_00389C90.e[i].ret` addresses D + 0x3390 + 0x18 i in one step,
as h18's whole-object view did; script_vm.c's `u.s.e[i]` / `u.box[i]`
became `e[i]` / `box[i]` with the same code (s30_hdrdiff SAME for every
includer).  h18 declares VmMgr and its Big / Big2 / E18 views are gone.

What matched as plain code, with the views gone: the m2c bodies (all of
them, including the permuter ones, func_001cf838, func_001d44b8 ..
func_001d4538, where `new_var` / `temp_s1 = arg0 + 4` were needed only on
`void *`), s7_w3's func_001d0380 on `vm->fl.b.b5` (u32 bit-fields inside
VmFl's union) and b10's func_001d4798 in nofill on `fl.b.b0` / `b5`.

## Session 33: the rest of the library file, 0x001d5408-0x001dcad0

Worker s33module moved the remaining 301 functions of the library file into
the four vm_lib files, in eleven chunks (one commit each), in address order
above the table.  0x001cd238-0x001dcad0 is now entirely src/vm/vm_lib*.c:
577 functions (vm_lib.c 539 with the dispatcher, nofill 30, nostrict 4,
nostrict_nofill 4).  No new sibling mode was needed.

| chunk | functions | sources | siblings |
|---|---|---|---|
| 0x001d5408-0x001d5b58 | 26 | auto text_001d0000.c (16), h17 (7), h43 (2) | nofill: nofill/h43's func_001d58c8 |
| 0x001d5b58-0x001d6000 | 7 | auto (4), auto _8, session1_probes' func_001d5f80 | nofill: nofill/s6_15's func_001d5b58 |
| 0x001d6000-0x001d6d60 | 43 | auto (26), _10 (2), _12 (2), _7 (2), _2, _4, h17 (5), h43 (2), s8_w8 | nofill: nofill/h17's func_001d6658 |
| 0x001d6d60-0x001d7678 | 29 | auto (16), _10 (2), _2, h17 (6), h43 (4) | |
| 0x001d7678-0x001d8680 | 15 | h18 (6), auto (3), _10, _4, c10's func_001d7ef8, h67's func_001d8400 | nofill: nofill/b11's func_001d7898 / func_001d7b88 |
| 0x001d8680-0x001d9480 | 36 | auto (20), _7 (2), h18 (8), h67 (2), s6_15 (2), nofill/s8_w1's func_001d9268 | nofill: nofill/s6_15's func_001d9348 |
| 0x001d9480-0x001da088 | 37 | h18 (22), auto (8), _2 (2), _7 (2), h44 (2) | nostrict: nostrict/text_001d0000.c's func_001d9510 |
| 0x001da088-0x001da6d0 | 15 | h18 (12), h44 (2), auto | |
| 0x001da6d0-0x001db080 | 24 | h19 (11), auto (8), _4, _7, _9, h44, b11's func_001dad58 | |
| 0x001db080-0x001dbae0 | 27 | h19 (19), auto (4), _16, _6, s7_w5, s12_s12w5 | |
| 0x001dbae0-0x001dcad0 | 42 | h19 (13), auto (9), _7 (5), _4 (2), _2 (2), _1, _11, _12, _14, _20, h44 (5) | nostrict: nostrict/h19's func_001dbdc8 |

func_001dca88 (not a table entry) went with the last chunk: it is a push
like its neighbours (`stk[++sp] = func_0021add8()`), and the dispatcher
follows it directly.  The library file is therefore 0x001cd238-0x001dcb00.

Deleted as empty (22 files): h17, h18, h43, s8_w8, s7_w5, s12_s12w5,
nofill/h17, nofill/h43 (with include/data/types/nofill_text_001d0000_h43.h),
nofill/s8_w1, nostrict/text_001d0000.c, nostrict/h19, auto
text_001d0000_1 / _4 / _6 / _9 / _10 / _11 / _12 / _14 / _16 / _20.
Partly emptied (the rest is after the dispatcher): auto text_001d0000.c,
_2, _7, _8, h19 (keeps D_0062A640 with its user func_001dd170), h44, h67,
c10, b11, nofill/b11, s6_15, nofill/s6_15; session1_probes lost
func_001d5f80.  objdiff units 900 -> 879.

**Types named.**

- *VmRec* (vm_rec.h): `f24`, `f28` at 0x24 (the move func_001d9480 starts
  and func_001d9348 steps; was pad).  The views' v08 / f14..f1c / f340..f348
  / f2f4 / flags are `p`, `f14[3]`, `f340[3]`, `x2f4`, `fl`.
- *VmMgr* (vm_mgr.h, additive): the camera tween at 0x3460, `cdur`, `ct`,
  `c0`, `c1` (CamS_2BC0F0: start and target of func_001d9100 /
  func_001d8f38; vm_mgr.h now includes the D_002BC0F0 piece), so VmMgr is
  0x34d0 bytes (under the 0x34d8 other files declare); h67's Str and
  s8_w1's Big92 views of those fields are gone from the library.  VmBox is
  `aligned(8)` (s8_w8's and h43's box views were: func_001d63e8 copies a box
  with ld / sd).  The trigger boxes (h43's ent3180 / s8_w8's e[]) are
  `box[]` / `nbox`, the slots' id / f8 / f10 / f14 are `e[i].obj / snd /
  x10 / h`, x3170 / x3174 are auto _8's [3164] / [3165].
- *struct VmObj* (vm_obj.h): `f70`, `fac` (0xac), and two more members of
  the 0x370 union: `b` (h44's bit 44) and `k` (h44's bits 37-38, `kind`).
  h17's `Node`, h43's `Obj`, h44's `Obj3` and h19's `Obj { flags }` are
  VmObj (`x4` the id, `x0` the flag word).
- Local types in vm_lib.c: `VmSave1` (save block 1's four lists at 0xa80,
  c10's Rec / h67's Save), `VmB16` (func_00147778's result), `VmP147840`,
  `VmMsgE` (nofill: the jump's message with the step e[3]).
- Prototypes that disagreed: func_0014ec10 is `void` (as _12 had it; with
  s32 func_001d6080 picked another register); func_00142388 is `s32 (f32 *,
  void *)` (h18: void (f32 *, s32 *), h44: s32 (f32 *, f32 *): both match);
  func_0011ea10 is unprototyped (func_001dbd20 passes a third u64 argument
  through a cast; h19's func_001dbcd8 passes two).

**Kept as views or offsets, with a comment:**

- func_001d58c8 (nofill): a one-field view of D_00389C90 with x3158 as
  `struct VmObj *`: the p->obj stores must alias it (reloaded each
  iteration); VmMgr's s32 is hoisted, and `*(struct VmObj **)&x3158[0]`
  folds the offset into the base.
- func_001d7438 / func_001d74b8: h17's view of the eight slots with obj as
  a pointer (`VmSlotP`); VmSlot's s32 obj made sp load after the store, and
  a cast of `&e[i].obj` folded the slot base into one constant.
- func_001d9268: s8_w1's view of the tween fields as B48 unions (`VmMgrB48`);
  through VmMgr the copy addresses fold into constants.
- func_001d6b70: h17's volatile views of D_002C5AD0 / D_002C5BB0 (S5AD0 via
  a cast macro, S5BB0 as an extern): the pieces' W29S70 / PadSt have no
  fields there.
- func_001d9510 (nostrict): the auto body with fields by offset (`VMF`); on
  VmRec / VmObj it schedules differently (51 words).
- func_001d9750: sp read by offset (`VM_SP`): as a struct field gcc 2.96
  treats the store to the scalar D_0038D0E0 as not aliasing it
  (MEM_IN_STRUCT_P vs a fixed scalar) and keeps sp in a register; the
  original reloads it.
- func_001db658 keeps s7_w5's address arithmetic (`&m[k].sub.x19[j]` is
  longer); func_001db9f8 / func_001dbe78 / func_001dc580 read D_00304BE8 by
  offset (0x580, 0x36 + 0x74 k, and the u16 counters 0x84e-0x866 in its
  pad); func_001dc280 passes `vm + 4 sp` as the auto file did.
- The D_0038CD00 bit tests (h18's F64 / F64b views) became shifts,
  `(s32)(D_0038CD00 >> 61) & 1` ..., and matched.

**The dispatcher.**  Adding names above the table flipped func_001dcad0
between `lw D_003D9FE0(k)` and lui / addiu / addu (2 or 3 extra prototypes
did it; s33types saw the same from script_vm.h).  The likely cause is cse's
hash of a SYMBOL_REF, which uses the address of its name string, so it
depends on every name allocated before it.  `VmLibFn` and `extern VmLibFn
D_003D9FE0[];` are now declared at the top of vm_lib.c, and 0-6 extra
declarations at the top or above the table no longer change it.

**Checks after each commit**: `make -j2` byte-identical (6979 functions),
`make report` 6979 at 100%, `s31_warndiff` 0 new warnings in the edited
files, and the m12 float build (`SHIFT_OVERLAYS` empty): float_covered.txt
identical to the session's base, kh1-shift.elf symbols at the same
addresses (sorted nm identical) and .text / .data / .reginfo identical.

## Session 34: after the dispatcher, 0x001dcb00-0x001e4918

Worker s34module moved the 159 functions from the end of the dispatcher
(0x001dcb00) to the start of the next group (0x001e4918) in six chunks, one
commit each, in address order.  Five functions stay in the library file.
The rest is four new modules.

| module | files | range | functions |
|---|---|---|---|
| vm_lib (the end of the library) | src/vm/vm_lib.c (+4), vm_lib.nofill.c (+1) | 0x001dcb00-0x001dd148 | 5 |
| the event effects | src/event/effect.c (62), effect.norlo.c (1), effect.nofill.c (1); include/event/effect.h | 0x001dd148-0x001e01b8 | 64 |
| the event voices | src/event/voice.c (3), voice.nofill.c (4) | 0x001e01b8-0x001e05a8 | 7 |
| the frame transfer | src/screen/frame.c (6) | 0x001e05a8-0x001e0ab0 | 6 |
| the screen image effects | src/screen/screen.c (27), screen.nofill.c (2) | 0x001e0ab0-0x001e2748 | 29 |
| the shops | src/shop/shop.c (48) | 0x001e2748-0x001e4918 | 48 |

| chunk | commit | functions | from | deleted |
|---|---|---|---|---|
| 0x001dcb00-0x001dd148 | 555abc2 | 5 | h44, auto text_001d0000_8.c, h67, nofill/b11 | nofill/b11 |
| 0x001dd148-0x001ddf98 | 67a1552 | 13 | h19, h44, norlo/s7_w10, nofill/s6_15b, auto _8 ... | norlo/s7_w10 (renamed effect.norlo.c), nofill/s6_15b, auto text_001d0000_8 |
| 0x001ddf98-0x001e01b8 | 4bc8479 | 51 | h44 (17), h20 (10), auto (18), h67 (2), s6_15 (2), s8_w6, h19 | h19, s6_15, s8_w6, auto text_001d0000 / _2 / _5 / _7 |
| 0x001e01b8-0x001e05a8 | fc2719e | 7 | nofill/s6_15 (4), auto text_001e0000_6 / _20, h20 | nofill/s6_15 (renamed voice.nofill.c) |
| 0x001e05a8-0x001e2748 | 44ff82b | 35 | h67, s11_w55, nofill/s11_w66, nofill/s12_s12w18, h20, auto ... | those four, auto text_001e0000_15 / _16 / _27 |
| 0x001e2748-0x001e4918 | 134ae83 | 48 | h20, h44, h45, h68, s9_w2, s9_r2_1, auto text_001e0000 / _4 / _6 / _14 / _17 / _18 / _21 | auto text_001e0000_14, h44, s9_r2_1 |

That is 22 files deleted and 9 new units: objdiff units 879 -> 866.

**How the groups were found.**
- **The library's index run.**  The library's D_003D9FE0 entries rise with the
  address, from 0x001cd238 to the dispatcher.  The 154 later entries do not
  continue that run.  Their indices interleave with it, one module at a time.
  So they are other files, not code after the dispatcher in vm_lib.c.
- **The data of each group:**
  - effects: bss D_0062A220-D_0062A640 (after vm_lib's D_0062A210) and the
    name table D_003DABD8.
  - voices: D_003DAC40 / D_003DACA0.
  - screen: D_003DACB0-D_003DB070 and bss D_0062F640-D_0062F6D0.
  - shop: D_003DB078-D_003DC494 and bss D_0062F6E0-D_0062FF00.
  - The next group starts at 0x001e4918 with D_00630300 and D_003DC498.
- **The calls.**  The five functions that stay in the library use only
  the VM's own data and callers:
  - func_001dcea8 is the only caller of the library's move steps
    (func_001d1080, func_001d3e30, func_001d7898, func_001d9348,
    func_001d9510).
  - func_001dcfd0 has the same two callers as func_001dcea8, the VM
    drivers func_001c1f80 / func_001c3b10 (script_vm.c).
  - func_001dcd98 and func_001dcb00 (nofill, the walk-to step) read the VM
    records D_0038D170 / D_0039A570 / D_0039A580 / D_003A7980.
    func_001dcd98 resumes the VM in VmMgr.x3154.
  - func_001dce90 increments VmMgr.x3380.
  The next function, func_001dd148, starts the effects' own data.
- **Where frame.c ends.**  frame.c is split from screen.c by the
  "callee defined above" effect.  The three cross-fades (s11_w55) only
  match while func_001e0608 / func_001e07a8 are not defined above them in
  the same file.  When they are, a store moves into a branch delay slot.
  screen.c also has its own copy of the packet send (func_001e14e0 =
  func_001e0608).  The voices share no state with the effects, so they are
  their own file too.

**Types named.**
- *include/event/effect.h*:
  - `EvFx`, the 0x3c-byte effect instance (D_0062A428[]): s7_w10's E60 and
    h44's HObj.
  - `EvTask`, the task record: Hd5 / Handler / Task / Tsk.
  - D_0062A220 / D_0062A224 are `void *`.  As s32, func_001ddc78 and
    func_001dde08 do not match.
- *VmMgr* (vm_mgr.h, which now includes vm_rec.h) gains `x3150` and
  `VmRec *x3154`.
- *struct VmObj* (vm_obj.h) gains these fields:
  - `f8`, `dir[4]` (0x20), `f90` (u64), `f150`, used by func_001dcb00.
  - `f68`, a model.
  - `struct VmObj14c *f14c`.
  - `f15c`, the skeleton.
- *The shop:*
  - Its three windows D_0062F6E0 / D_0062F790 / D_0062F840 are `MsgWin`.
    h20's f30 / f34 / f40 / f44 are `v30[0..1]` / `v40[0..1]`.
  - The callback D_0062F8F0 is `ShopCb`.  h20's Cb20 `.b` is `.n`.
  - The item lists D_003DB078 / D_003DB718 are `ShopList`.
  - D_002C5958 is `volatile s32`.
- *Defined in the modules:*
  - effect.c: D_0062A228, D_0062A430, D_0062A640.
  - screen.c: D_0062F640-66C.
  - shop.c: D_0062F900.
- *h44's prototype.*  h44's `HSub *func_001e98d0` went with h44.  Every
  declaration now returns `VmRec *`, and `s33_protodiff.py` reports 0.

**Kept as views or offsets, with a comment:**
- **The VM seen from +4** (`EvVmSub` in effect.c, `ScrVmSub` in screen.c,
  `ShopVmSub` in shop.c).  It is
  `{ struct VmObj *obj; u8 pad4[0x17c]; s32 stk[33]; }` taken as
  `(X *)&vm->obj`.  It is used by four effect requests, three screen script
  functions and the buy / sell openers func_001e3770 / func_001e38b0.  The
  original indexes the stack off vm + 4.  On VmRec, gcc indexes it off vm,
  and the code differs.
- **The shop's text labels.**  The shop calls
  `func_0010ef70(D_0062F760 - 0x80, ...)` and `func_0010e3f0(D_0062F760)`
  (the item window's text).  With `&D_0062F6E0` four functions differ:
  the original builds both addresses from one register.  D_0062F810 (the
  choice window's text) is a label too.
- **The image buffer.**  screen.nofill.c reads the 512x384 frame through
  `IMG ((RGB *)D_00F20000)`.
- **View casts.**  `s27_survey.py --summary` gives 22 at both this
  session's base and the end.  The docs' "18" came from session 32's
  count.  None of the 22 is in the moved code, so no view casts were
  removed.  The basic casts went 742 -> 739.

**The float build: D_0062F840.**  h20 used to declare D_0062F790 as a
0x100-byte `Mgr20`, which covered D_0062F840 (at +0xb0).  So cover_check
kept D_0062F840 in place.  With the windows as MsgWin (0xb0), it would
float.  It is now in tools/shift/float_keep.txt with a note.  The keep set,
the symbols and the loaded sections are identical to the base.  Only
D_0062F840's line in float_covered.txt moved, to the float_keep part.  It
can float once a SHIFT_FLOAT_FORCE=D_0062F840 build has played a shop.

**Nothing was reverted.**

**Checks after each commit:**
- `make -j2` byte-identical (6979 functions).
- `make report` 6979 at 100%.
- `s31_warndiff` 0 new warnings in the edited and new files.
- The m12 float build (`SHIFT_OVERLAYS` empty): float_covered.txt
  identical, kh1-shift.elf symbols at the same addresses, and .text /
  .data / .reginfo identical.  For the shop commit the keep set was
  compared, not the line order.
- `make test` passes at the end.

## Session 35: after the shop, 0x001e4918-0x001ec7c0

Session 35 moved the 204 functions from the shop's end (0x001e4918) to
func_001ec7c0 (the first D_003E3C80 user) in six chunks, one commit each.
The groups were split by their own data and calls.  The D_003D9FE0 index
run did not help here: it rises in address order across all of these
groups, so it does not mark a file edge.

| module | files | range | functions |
|---|---|---|---|
| the record lists | src/list/list.c (56) | 0x001e4918-0x001e7e78 | 56 |
| the script's sound commands | src/event/sound.c (58); include/vm/vm_sub.h | 0x001e7e78-0x001e92b8 | 58 |
| the wave transition | src/screen/wave.c (7), wave.nofill.c (2); include/screen/wave.h | 0x001e92b8-0x001e98d0 | 9 |
| (src/vm/vm_find.nofill.c, already a module) | | 0x001e98d0-0x001e9d00 | |
| the VM helpers | src/vm/vm_util.c (6), vm_util.nofill.c (3) | 0x001e9d00-0x001ea438 | 9 |
| the entity commands | src/vm/vm_ent.c (14) | 0x001ea438-0x001eac68 | 14 |
| the save-data commands | src/save/flags.c (57), flags.fmam.c (1); include/save/save1.h | 0x001eac68-0x001ec7c0 | 58 |

| chunk | commit | deleted |
|---|---|---|
| 0x001e4918-0x001e7e78 | 545fe68 | c10, s9_w2, include/data/pieces/D_003DC498.h |
| 0x001e7e78-0x001e92b8 | 49073d4 | h20, nostrict/text_001e0000.c, auto _21 |
| 0x001e92b8-0x001e98d0 | cace848 | auto _19; nofill/h68 renamed to src/screen/wave.nofill.c |
| 0x001eac68-0x001ec7c0 | 851e940 | b11, fmam/s7_w19 (src/hand/fmam/ is gone; the kh1.toml mode entry stays) |
| 0x001ea438-0x001eac68 | 4984fba | auto _20 |
| 0x001e9d00-0x001ea438 | f152d77 | auto _18, nofill/h21, nofill/h45, h45, s8_w2 |

That is 17 files deleted and 11 new units: objdiff units 866 -> 860.

**Boundaries that differ from session 34's guesses.**  The sound group
runs to 0x001e92b8: it takes func_001e8e38, the eventse loader and the
0x0011c* sound-layer commands.  The wave group is 0x001e92b8-0x001e98d0.
The stretch 0x001e9d00-0x001ec7c0 had no bss of its own; by calls it is
three files (vm_util, vm_ent, the save flags).  func_001ec7c0 sets
D_003E3C80 and starts the next group.

**Types.**
- **VmSub** (include/vm/vm_sub.h): the "+4 view" of the VM,
  `(VmSub *)&vm->obj`, then `s->stk[vm->sp]`.  sound.c uses it, and
  since session 36 effect.c, screen.c and shop.c too.
- **Save1** (include/save/save1.h, 0xdd8 bytes; every offset checked with
  a probe compile): the save record the flag commands read.  list.c and
  vm_lib.c use it too since session 36.
- **WavePkt** (include/screen/wave.h, 0x1960 bytes) with WaveU128 /
  WaveQ / WaveTag.
- vm_mgr.h's VmMgr gains `x34d0` in its tail padding (set by
  func_001ea498).
- list.c: ListCb, ListMenu (0x684), ListSave; the windows are MsgWin.
- The D_00389C90 masks that m2c wrote as `[1550]` are now
  `D_00389C90.f3070.x &= ~0x...ULL` (0x3070) or `.f3078.x` (0x3078).

**Sized externs stay in the .c files.**  tools/shift/cover_check.py sizes
only the `extern` lines in .c files, not in headers.  A sized `extern
WavePkt D_00631620;` moved into wave.h changed float_covered.txt
(D_00633640 became covered).  So the extern is in both wave .c files, with
a comment, and wave.h holds only the types.

**Flag modes.**  The two nostrict functions (func_001e80d0 / func_001e83f8)
match with the default flags in sound.c.  func_001ea580 needed a u8
temporary for the byte toggle of `vm->x0` (16 words differed before).

**Nothing was reverted, and nothing new floats.**  After each commit:
`make` byte-identical (6979 functions), `make report` 6979 at 100%,
`s31_warndiff` 0 new warnings, and the m12 float build with float_covered.txt,
float_reach.txt, the loaded sections and the symbols the same as the base
(the one known symbol diff is D_006305DA, a label).  `make test` passes.

## Session 36: the rest of the 0x001e files, 0x001ec7c0-0x001f0000

Session 36 moved the 171 functions from func_001ec7c0 to 0x001f0000 in
four chunks, one commit each, split by their data and calls (the helpers and
the play timer shared a commit).  No Mac:
static checks only.

| module | files | range | functions |
|---|---|---|---|
| the sound driver's RPC client (platform code) | src/sound/snd_rpc.c (49) | 0x001ec7c0-0x001edc50 | 49 |
| small helpers (vectors, angle wrap, RGBA, a GS scissor packet) | src/util/util.c (6), util.nofill.c (1) | 0x001edc50-0x001ee118 | 7 |
| the play timer | src/game/playtime.c (8), playtime.nofill.c (1) | 0x001ee118-0x001ee428 | 9 |
| the game-data queries (items, abilities, party, munny, init list) | src/game/gamedata.c (76) | 0x001ee428-0x001ef950 | 76 |
| the text functions, first part | src/text/text.c (29), text.nofill.c (1) | 0x001ef950-0x001f0000 | 30 |

| chunk | commit | deleted |
|---|---|---|
| 0x001ec7c0-0x001edc50 | db656ad | auto _8 to _13, _23, _24 |
| 0x001edc50-0x001ee428 | 3957687 | h21, s19_s19m1, s9_r2_5, nofill/text_001e0000 |
| 0x001ee428-0x001ef950 | cae1266 | auto _2, _3, _22, _25, s6_16 |
| 0x001ef950-0x001f0000 | 79f3b8e | auto text_001e0000, _1, _4 to _7, _17, _26, h68, s8_w6 |

That is 27 files deleted and 8 new units: objdiff units 860 -> 841.  Every
src/auto/text_001e0000*.c file is gone.  h22, nofill/h22 and h46 remain for
their functions after 0x001f0000 (h46 also holds func_002081b0).

**What the groups are.**
- **snd_rpc.c** binds SIF RPC server 17 and talks to the IOP through the
  0x2000-byte buffer D_00633640 (word 0 in, word 0 back).  Most commands go
  into the 1024-slot queue D_00635640 (func_001ed000) and func_001edba0 sends
  it (RPC 30).  The IOP writes the status block D_0063D640 (24 SndSe slots
  of 0xb4, then 4 SndStream of 0x48 at D_0063EE40) and the message buffer
  D_0063F640 by DMA.  D_003E3C80 (func_001ec7c0) masks four command groups.
  This is the Vita layer's job (docs/portability.md "sound"); no Plat
  wrapper yet.
- **playtime.c**: func_001ee118 is frames (D_002BBDF4 times D_002BBDEC);
  216000 / 3600 / 60 give hours, minutes, seconds.
- **gamedata.c**: func_00147840(id) is an item record (ItemRec, kind at +2),
  func_001478a0(id & 0x7f) an ability record (AbilRec, AP cost at +0); the
  party is Save_304be8 (D_00304BE8, include/data/pieces/D_00304BE8_s.h:
  h22's Member, h46's Mem74 and s6_16's C116 were all W606Mem_304be8);
  munny is save block 5's x1c (D_003F34B8, at most 99999).
- **text.c**: message blocks (MsgHdr: +0x10 offsets, +0x14 strings; h22's
  Tbl was the same), the control-code walkers over D_003E8D28, the glyph
  table D_003E8E28.  The module goes on after 0x001f0000.

**m2c artefacts fixed on the way.**  Getters that pass their argument
through in a0 had lost it (`func_00147840()` for `func_00147840(id)`); they
take it again, and the K&R `()` prototypes went with it.  Tail-call thunks
written as `void` return the callee's value (func_001efe68 adds 1 to
func_001efd98's).  func_001ed320 / 410 / 738 lost the eight float
parameters m2c passed through (the floats never leave f12-f19).

**Views.**  func_001ecf40 reads the IOP message buffer signed: with a
`(s8 *)` cast on the u8 array gcc keeps the address in a register
differently (8 bytes longer), so snd_rpc.c declares `extern s8
D_0063F640[256]` (bss_0063.c defines it u8) and does not include
bss_0063_mixed.h.  gamedata.c types D_003E3CB8 as u16[] (the lhu) and does
not include data_003E.h, whose M2C_UNK view would conflict.

**Types (static).**  EvVmSub (effect.c), ScrVmSub (screen.c) and ShopVmSub
(shop.c) are VmSub now; list.c's ListSave (lists a-d, open) and vm_lib.c's
VmSave1 are Save1 (l0-l3, ad0.open).

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `make report` 6979 at 100%, `s31_warndiff`
0 new warnings in the edited files, and the m12 float build with
float_covered.txt, float_reach.txt, the loaded bytes and the symbols the
same as the base.  `make test` passes.

## Session 37: the text module goes on, 0x001f00d0-0x001fd248

Session 37 moved 216 functions in four chunks, one commit each, split by
their data and calls.  No Mac: static checks only.

| module | files | range | functions |
|---|---|---|---|
| the text functions, second part (string widths, the GIF glyph builders and their send wrappers, the font setup) | src/text/text.c (+30), text.nofill.c (+5), text.nostrict_nofill.c (1) | 0x001f00d0-0x001f2e98, func_001f2e98 / 2eb8 | 36 |
| the text windows: slots, lists, open / close, queries | src/text/textwin.c (74), textwin.nofill.c (1); include/text/textwin.h | 0x001f3110-0x001f4570 | 75 |
| the window frames, the open / close animation, the update loop | src/text/textwin.c (+22), textwin.nostrict.c (6), textwin.nofill.c (+1) | 0x001f4570-0x001f86e0 | 29 |
| text in the windows: scissor, colour / width, the print wrappers, glyph / number / icon builders | src/text/wintext.c (67), wintext.nostrict.c (6), wintext.nostrict_nogcse.c (3) | 0x001f86e0-0x001fd248 | 76 |

func_001f1fc8 and func_001f2630 (unmatched) sit inside the first range; text.c
has a comment at their place.

| chunk | commit | deleted |
|---|---|---|
| 0x001f00d0-0x001f2e98 | af2befa | s8_w5, nofill/s18_s18m1, nofill/s6_17, nostrict_nofill/s7_w32 |
| 0x001f2e98-0x001f4570 | ac204b0 | h22, nofill/h22, nofill/h69, s11_w2, auto _9 _10 _11 _16, include/data/types/text_001e0000_h22.h |
| 0x001f4570-0x001f86e0 | 6045646 | b12, nofill/s11_w70, nostrict/s7_w22, auto _3 |
| 0x001f86e0-0x001fd248 | ec775f4 | s6_17, nostrict/s6_18, nostrict/s11_w42, nostrict/s12_s12w16, nostrict_nogcse/s6_f9, s11_w41, s11_w9, auto _8 _13 _14 _15 |

That is 27 files deleted and 7 new units: objdiff units 841 -> 821.

**What the groups are.**
- **text.c** (second part): func_001f0148 / func_001f0340 / func_001f0448 measure
  a message string, a two-byte string and a number at size sz (18 is the
  glyph table's own size).  The builders write a GIF header and one sprite per
  glyph after pk and return the end; mode 0/1/2 aligns left / right / centre,
  the end position goes to D_0063F74C / D_0063F750, D_0063F740 is the line
  height.  func_001f2a50 ... func_001f2d68 build into a scratch buffer
  (func_00122048) and send it through path 2.  func_001f2eb8 uploads the font
  image D_003E9660 and its CLUT D_003F1660 and sets up the packet headers of
  D_003F1A70 / D_003F1E70 / D_003F2270 / D_003F27D0, then func_001f3110
  resets the windows.
- **textwin.c**: 24 window slots of 0xf0 bytes at D_0063F758 (**TextWin**,
  include/text/textwin.h).  func_001f31a8 opens one from a descriptor
  (TextWinDesc; D_003E9630 is a scratch one) at the head of the open list
  D_00640DD8 (+0x14 newer, +0x18 older) and the focus list D_00640DDC (+0x1c /
  +0x20); +0xc / +0x10 chain windows side by side.  States: 0 free, 1-3
  opening / open, 4-5 closing; func_001f3680 sets the close request (bit 0 of
  the word at +0x44).  The per-frame func_001f82b0 runs every window's +0x0
  callback newest first, then oldest first steps the state, draws the frame
  (func_001f46b0 by kind +0x70) and calls +0x4, then frees the windows asked
  to close and brings the focus list to the front.  func_001f5fe0
  (textwin.nofill.c, 8.5 KB) runs the animation +0x80 with time +0x9c.
- **wintext.c**: drawing inside a window.  Positions are in 1/16 pixels with
  the window at +0xb0 / +0xb4 (0x7000 / 0x7400 is the GS offset); with bit 0 of
  +0x48 everything is scaled by +0x74 / +0x78 around the anchor
  (func_001f4570 / func_001f45e0, by alignment +0xac).  D_003F1A60 is the
  current text colour and D_003F1A64 the width.  The wrappers centre in the
  window (x = +0xb8 / 2, y = (20 - sz) / 2 + 2) or add a one-pixel outline in
  a second colour.  func_001fc330 / func_001fc750 / func_001fcdc8 draw icons of
  the sprite table D_003E9138.

**TextWin.**  It folds h22's Obj, h23's Obj, h46's Nd / Txt / Win46, s11_w2's W,
b12's Win, h69's Ob / Wnd3 / Wnd4 / Wn, s6_17's Ob, s6_18 / s11_w9 /
s11_w41 / s11_w42 / s6_f9 / s12w16's Txt9, s11_w70's G2Wn and nofill/h22's O68.
Where the views disagreed:
- **+0x4 stays s32** although b12 calls it: with a function pointer (or any
  pointer) type, func_001f31a8's copy `p->x4 = a->x0` schedules differently
  (28 words).  b12's call is `((void (*)(TextWin *))w->x4)(w)`.
  TextWinDesc's +0x0 is s32 for the same reason.
- **+0x40** is a union: `a` (u64 lo:32 / hi:32: bit 0 of hi is the close
  request), `b` (the same bit as b0), `v` (two u32: func_001f3d10 reads +0x44
  with lw) and `w` (u32 x40, b44:1: b12's lw / sw of the bit).
- **+0x48** is a union: `a` (u64 c0:1 / crest:63, s11_w2), `q` (the u64,
  func_001f5e10 / func_001f5fe0 `|= 1`, `&= ~1`) and `w` (two s32: the frame
  and text builders test bit 0 of the low word with lw).
- **+0x50 / +0x54 are two s32** (the animation's positions);
  func_001f31a8 clears both with `*(u64 *)&p->x50 = 0` (one sd).
- **+0x70, +0x80, +0xac** are s32; the switches that read them as u32 cast:
  `switch ((u32)w->x70)` gives the same code.
- +0x68 is `void *` (an entry of D_003E8E30, or 0); +0x94 ... +0xa8 are f32.

**Return types.**  func_001fbb50 matches only when it returns
func_001fb428's value (9 words otherwise), so wintext.c declares
func_001fb428 `s32` although its definition (wintext.nostrict_nogcse.c)
returns nothing; the comment says so.  Elsewhere the m2c `void` thunks
return their callee's value, as in session 36.

**Flag modes.**  Every function kept its old flags; the nostrict / nogcse /
nofill functions went to sibling files with the CONTEXT_ONLY copies they
needed (text.nofill.c and text.nostrict_nofill.c carry func_001efb78 ...
func_001f0340).  func_001f4778 matched in textwin.nostrict.c with the real
func_001f4570 above it (s7_w22 had a `{ return 0; }` stub).

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings, and the m12
float build with float_covered.txt, float_reach.txt, the loaded bytes and the
symbols the same as the base.  At the end `make report` 6979 at 100% and
`make test` passes.

## Session 38: the window menus, 0x001fd248-0x00209d48

Session 38 moved 179 functions in six chunks, one commit each, split by
their data and calls.  No Mac: static checks only.

| module | files | range | functions |
|---|---|---|---|
| the text area of a window (getters / setters of +0xb0 ... +0xda), the pad masks, the cursor movers, the cursor bar and frame, the panels | src/text/winmenu.c (66), winmenu.nostrict.c (3) | 0x001fd248-0x00200000 | 69 |
| the window parts: row highlights, list frames, scroll arrows and bars, page tabs and counter, boxes, lines, sprites | src/text/winpart.c (18), winpart.nostrict.c (21) | 0x00200000-0x00206e28 | 39 |
| the bit sets of D_003F34B8 (clear all / clear / set / test) | src/game/bitsets.c (28) | 0x00206e28-0x00207428 | 28 |
| rows in the colour sets D_003F2C40, tabs, titles, the "n pages" and icon helpers | src/text/winrow.c (32) | 0x00207428-0x00208458 | 32 |
| the lists: the visible cells of a window's list, the list frame | src/text/winlist.c (9), winlist.nostrict.c (1) | 0x00208458-0x00209d48 | 10 |

func_001fd858 (cursor input) and func_00200e28 (unmatched) sit inside these
ranges; winmenu.c has a comment at func_001fd858's place.

| chunk | commit | deleted |
|---|---|---|
| 0x001fd248-0x001fea38 | d75ed2d | auto _0 _1 _2 _5 _6 _7 (text_001f0000), s11_w33, s6_18 |
| 0x001fea38-0x00200000 | f3b02a2 | auto text_001f0000_4 _12, nostrict/s11_w23, nostrict/s9_r2_4, c12 |
| 0x00200000-0x00206e28 | f506736 | nostrict/b12, nostrict/h69, nostrict/s6_19, nostrict/c13, nostrict/c2, nostrict/s10_w14, nostrict/s11_w72, nostrict/s8_w12, s11_w50 |
| 0x00206e28-0x00207428 | acea043 | (none: h23 and the auto files kept other functions) |
| 0x00207428-0x00208458 | 615e19f | h23, h46, auto text_00200000_9 _10, include/data/types/text_001f0000_h23.h |
| 0x00208458-0x00209d48 | 4e08a5c | nostrict/s12_s12w16, h69 |

That is 28 files deleted and 8 new units: objdiff units 821 -> 801.  h23,
h46 and h69 are gone; every src/auto/text_001f0000*.c file is gone.

**What the groups are.**
- **winmenu.c**: the text area of a TextWin in 1/16 pixels: origin +0xb0 /
  +0xb4 (with the GS offset 0x7000), size +0xb8 / +0xba, margins and cell size
  +0xbe ... +0xc8, items +0xca (+0xcc rows of +0xd8 columns, rounded up),
  +0xce, then the scroll +0xd0, the cursor +0xd2, their steps +0xd4 / +0xd6
  (the sign is the direction) and the column cursor +0xda.  func_001fd720 sets
  the pad masks D_00640DE4 ... D_00640DF8 by mode (0 d-pad and stick, 1 d-pad,
  2 stick).  func_001fdfd0 moves the column cursor with the pad's repeat x10
  and trigger x8 (wrapping), func_001fe1b8 scrolls smoothly (a quarter cell a
  frame at D_002BBDFC), func_001fe408 fades the row highlights +0xdc,
  func_001fe5a0 is the confirm (button 0x2000, waiting for the scroll to stop).
  func_001fe660 ... func_001fe9a8 move a menu's own cursor array at +0x24
  (MenuCur, not a window): up / down, left / right, either (+ shoulders), with
  and without wrap.
- **winpart.c**: a list row (frame func_00200648 in the colours cols, then a
  message id / string / outlined string in a 26-pixel band, colour cols[4]),
  the scroll bars (func_00202678, func_00203a10) and the page counter
  "n / m" between the tabs (message 84 is the slash).
- **bitsets.c**: D_003F34B8 (the block that holds the munny at x1c) has seven
  bit sets (b48 64 bits, b56 and b60 32, b64 320, b104, b108, b112); each has
  a clear-all, clear, set and test.  What they record is not known yet.
- **winrow.c**: D_003F2C40 holds row colour sets of 0x14 bytes (+0x0 frame,
  +0x10 text); func_00207a38 draws the two tabs, func_00207b38 ... a title,
  func_00207598 finds D_00640E28 in the id list D_00640E00 (D_00640E20 ids).
- **winlist.c**: the visible cells of a list (rows +0xce + 1 from the scroll,
  columns +0xd8, items +0xcc), the cell under the cursor in the second colour,
  inside the scissor func_001f8e18 / func_001f8f30.

**TextWin.**  +0xd0 ... +0xd6 are a union `ud0` now: `s` (four s16),
`u` (u16 +0xd0 / +0xd2: func_001fe1b8 and func_00200038 load them with lhu)
and `q` (the u64: func_001fe558 tests its high word).  Every other view of
these files fitted TextWin's members: tools/shift/s38move/fold.py folded 16
views in place (`fold.py FILE.c TYPE --write`, then `make`), one file at a
time, before the move.  Two traps:
- **func_001fea38** reads +0xd2 as `((s16 *)&o->ud0)[1]`: as `o->ud0.s.xd2`
  two loads swap (the union member changes the scheduling).
- **func_00202678** keeps its own view WinUF (winpart.c): +0x74 and +0x90 are
  unions there (alias set 0), which its note says the original's order needs.
- D_0063F758 is defined `TextWin D_0063F758[24]` (bss_0063.c,
  bss_0063_typed.h); h23's Obj is gone.

**Return types and parameters.**  func_001fd610 / func_001fd660 take an s32
(an s16 parameter made the callers sign-extend).  func_002014a0 / 1550 /
1600 return their callee's value (their wrappers func_00201440 ... return it);
func_001f9e48 is declared s32 in winpart.c although wintext.c defines it void,
and func_001ff488 s32 in winmenu.c (func_001ffaf0 returns it).  func_001fe1b8
keeps its s32 parameter (the dead `if (a <= 0)` lever needs it).

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings, and the m12
float build with float_covered.txt, float_reach.txt, the loaded bytes and the
symbols the same as the base.  At the end `make report` 6979 at 100% and
`make test` passes.

## Session 39: the menus, 0x00209d48-0x00210000

Session 39 moved 81 functions in five chunks, one commit each, into a new
directory src/menu/ (headers in include/menu/).  No Mac: static checks only.

| module | files | range | functions |
|---|---|---|---|
| the party models of the menus: D_003F3530 (PartyMdl[4], include/menu/partymdl.h), D_003F3870 the count, the nine views D_00640E40 | src/menu/partymdl.c (11) | 0x00209d48-0x0020a8f0 | 11 |
| the backgrounds: two frame-buffer pixels read back into D_003F34B0 (top / bottom colour), full-screen gradients, the two images of D_00641080 / D_00641130 | src/menu/menubg.c (2), menubg.nostrict.c (5) | 0x0020a8f0-0x0020b6a8 | 7 |
| the pointer: a sprite that glides to the cursor cell of a TextWin and fades (D_006411E0 ... D_00641218, defined there) | src/menu/pointer.c (12) | 0x0020b6a8-0x0020be68 | 12 |
| the party rows (name, level, HP, MP of a member) and the callbacks of the windows D_003F3200 / D_003F3230 / D_003F3280 | src/menu/partyrow.c (5) | 0x0020be68-0x0020c1c8 | 5 |
| the top menu: the page list D_00640E00, its window, the window chains, the munny / time panel, set up / open / close, and the page tables D_003F32C8 / D_003F32E8 | src/menu/topmenu.c (17) | 0x0020c1c8-0x0020d7d8 | 17 |
| the item page (page 0, message 0x69): its window callbacks (descriptors D_003F3880 ... D_003F3A80), using an item, the slot and stock lists, the third tab | src/menu/items.c (19), items.n32.c (6), itemslots.c (2), itemstock.c (2) | 0x0020d7d8-0x00210000 | 29 |

| chunk | commit | deleted |
|---|---|---|
| 0x00209d48-0x0020a8f0 | e5467a7 | c3 |
| 0x0020a8f0-0x0020b6a8 | 0b0fdb6 | nostrict/b13, auto text_00200000_4 |
| 0x0020b6a8-0x0020c1c8 | 0eaf30b | s8_w18, auto text_00200000_1 _3 _6 |
| 0x0020c1c8-0x0020d7d8 | 0d68987 | auto text_00200000_2 |
| 0x0020d7d8-0x00210000 | 898f02f | s6_20, n32/s6_n32, auto text_00200000 _5 _7 _8; c14 and s7_w15 renamed (git mv) |

That is 14 files deleted, 8 new units and 2 renamed: objdiff units 801 -> 795.  Every
src/auto/text_00200000*.c file is gone; h24, h47, h70, nostrict/h70 and b13
keep functions above 0x00210000.

**What the groups are.**
- **partymdl.c**: func_00209d48 loads a model for each party member
  (func_001ef8f8(i)) into D_003F3530[i] and counts them; the fourth entry is
  turned on by func_00223ea8 (h72, `D_003F3530[3].active`).  func_0020a248
  sets a model up (its motion, the colours at +0x34 ... +0x47, two u64
  constants at +0x60 / +0x68, and copies of the bones from bone 52 on into +0xc0).
  func_00209f70 sets the views D_00640E40[0..8] (func_00267b08) from
  D_003F31D0[party size - 1] and D_003F31D0[3], with D_003F3150 / D_003F3178
  by the models of D_00304BE8->x48e.  func_00209e18 / func_0020a518 animate
  and draw them (draw ids from 0xea61), func_0020a758 the turning one,
  func_0020a1d8 frees them.
- **menubg**: func_0020a8f0 reads the pixels (4, 16) and (443, 16) of the
  frame buffer (sceGsExecStoreImage) into D_003F34B0[0] / [1]; func_0020a9b0,
  func_0020ab88, func_0020ae98 draw a gradient between them (plain, textured
  with D_003F1A70 / D_003F1E70, or into a packet), func_0020b120 a quad with
  four colours and the alpha mode D_003F31F0[prim].
- **pointer.c**: D_006411FC is the fade state (0 in, 1 shown, 2 out, 3
  hidden), D_00641218 the alpha, D_00641210 / D_00641214 the place in pixels;
  func_0020bc48 starts a glide of a0 frames (it jumps when the target is
  within one pixel), func_0020bd18 aims at a TextWin's cursor cell.
- **topmenu.c**: D_00640E00 holds the pages in menu order (0-4 always, 5
  when func_001ec510, 6, 7 when D_003F34A8 == 1), D_003F32A8[page] their
  message ids (0x69 ... 0x70), D_003F32C8[page] the descriptor of their first
  window and D_003F32E8[page] their open functions (func_002112f8,
  func_00213c90, func_002160a8, func_00217f58, func_00218f88,
  func_0021daa0, func_0021ad08, func_002293f0: the pages from 0x00210000 on).
- **items**: the window descriptors D_003F3880 ... D_003F3A80 start with
  their draw callback (func_0020d7d8, func_0020d900, func_0020da00,
  func_0020e280, func_0020e408, func_0020e588, func_0020eb20, func_0020fea0,
  func_0020fee8, func_0020ff28, func_0020ff80).  The list window's tab
  (+0x24) picks a member's slots (below the party size: func_0020ec50), the
  stock (equal: func_0020f530) or the list of func_001ba3d8 (func_0020fc58).
  Page 0 is most likely the item page (message 0x69, the slot and stock
  lists); not proved by a boot.

**Types and views.**
- **PartyMdl** (0xd0) replaces four views (h47's E3530 / S3530, h70's E3530,
  c3's E9, the auto offsets) and h72's S33C.  +0x34 is a union (`u34.w` for
  the colour word, `u34.c[]` for its bytes).  +0x14 (the model) must be
  `void *`: as s32, func_0020a248 stores +0x78 before it loads +0x14 (the
  alias set of the two s32 fields keeps their order); every callee that takes
  the model takes `void *` in partymdl.c.
- **func_0011fbb0** returns s32 in menubg.c: declared void, func_0020b338
  swaps v0 / v1 in its stack arguments.
- **func_002073b0** (src/game/bitsets.c, one argument) is called with the
  window as a second argument from func_0020fee8: the original moves a0 to a1
  before the call.
- **D_00640E20 / D_00640E24** are s32; func_0020ca68 and func_0020d050 read
  E24 with lhu: `(u16)D_00640E24 * 16` gives it (h70 declared them u16).
- The top menu's list window keeps D_003F34C4's type N_3f34c4 (its +0x28 is
  f32, TextWin's is s32); func_0020ca68 / func_0020d050 keep h70's Obj (+0xb8
  and +0xcc are u16 there); itemslots.c and itemstock.c keep their ObjE views
  (u16 +0xd0 / +0xd2 and s32 +0x40 in one, halves of +0x70 / +0x88 in the
  other).  Everything else in items.c, partyrow.c, pointer.c and menubg is a
  TextWin, and callees whose window views disagreed take `void *` in
  topmenu.c.
- **Flags**: func_0020d530 (nostrict/h70) matches with the default flags and
  is in topmenu.c; the five nostrict functions of menubg stay nostrict
  (func_0020ae98 grows past its slot without it); the six row functions of
  items.n32.c need n32.
- **Data moved with its users**: D_00640E40 and D_003F31D0 (from h70) into
  partymdl.c, D_006411E0 ... D_00641218 (from bss_0064.c and its two headers;
  D_00641204 is f32 now, every user adds frame times to it) into pointer.c,
  D_003F32C8 (now `void *[8]`) and D_003F32E8 (from s6_20) into topmenu.c.

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings (and no
warnings in the new files), and the m12 float build with float_covered.txt,
float_reach.txt, the loaded bytes and the symbols the same as the base.  At
the end `make report` 6979 at 100% and `make test` passes.

## Flags: what a module takes

gcc 2.96 has no per-function flags: `__attribute__((optimize))` and `#pragma GCC
optimize` arrived in gcc 4.4, and every flag in kh1.toml applies to a whole
compile. So functions that match only with different flags cannot share a file.
Options considered:

1. **One file compiled once per flag set**, each pass placing only its own
   functions (the others as CONTEXT_ONLY). Keeps the whole module in one file and
   in order, but one source would give several objects, and obj_for, placements,
   objdiff units, variants.py and shift_ld all assume one object per source.
2. **A flag table in kh1.toml naming files** (`path = "src/vm/script_vm_x.c"`): works
   with no tool change (overrides match by prefix), but the file's flags are
   invisible from its name.
3. **Sibling files named by flag mode** (chosen): `src/vm/script_vm.c` plus
   `src/vm/script_vm.nosi.c` and `src/vm/script_vm.nostrict.c`.

How it works: each `src/hand/<mode>/` override in kh1.toml has a `mode = "<mode>"`
key (nofill, nostrict, nostrict_nofill, nogcse, nostrict_nogcse, n32, n32_nogcse,
n32_nostrict, nosi, nogcse_nosi, nogcse_nosib, faddr, nostrict_norcse, norlo,
fmam, nostrict_nosib). `flags_for` in tools/kh1tool.py gives a file named
`<name>.<mode>.c` (or .cpp / .cc) anywhere under src/ that mode's flags, before
any directory override (dot-files, the matching tools' scratch copies, never
carry a mode). `kh1tool.py gen` stops the build on a src/ file with an unknown
mode and prints the list.
Everything that asks flags_for follows: the build rules (`kh1tool.py gen`),
tools/checkfile.py, objdiff's scratch flags, tools/shift/drafts.py and the
matching helpers. Object files are `out/build/src/vm/script_vm.nosi.c.o`.
To try a file with checkfile, give the copy a mode name that does not start
with a dot (`src/vm/tmp.nostrict.c`), or it gets the default flags.

A sibling file loses the functions above it in the main file. Where that
matters, give it CONTEXT_ONLY stubs of the callees defined above it
(docs/context-only-plan.md): func_001c1718 needs one for func_001c0bf0 (without
it one word differs); `{ return x; }` is enough. The main file keeps a comment
at the moved function's place. The four nostrict functions match together in
one sibling file (func_001c4808 calls func_001c3770 above it, as in b10).

## Headers, externs, data and rodata

- **Module header** (`include/<module>/<name>.h`): prototypes of the functions
  other files call, with the real types. The module includes it, so the
  definitions are checked against it. Other files should include it rather
  than declare their own prototypes. Switching a file changes its types (return
  types and pointer types can change code: see "Hazards" above and
  docs/shiftable-plan.md "Session 29"), so each is a retype checked with `make`.
  s6_13 (session 30), the 15 `void func_001c4640(Msg *)` users (session 31) and
  20 more files (session 33) now include script_vm.h / vm_find.h; only the
  library files the module move owns still differ (s33_protodiff.py).
- **Externs**: use the shared data headers (include/data/data_00XX.h,
  include/data/pieces/D_X.h, include/data/types/*.h), not file-local `extern`s.
  script_vm.c includes data_0038.h / data_003C.h and the piece headers at the top. tools/shift/cover_check.py
  sizes the file-scope externs of every C file, so a module must declare the same
  types its users did, or the float keep list changes; compare
  `out/shift/m12-float/float_covered.txt` before and after (it was identical here).
- **Rodata** (jump tables, strings, float constants) needs nothing: split-rodata
  gives each function its own `.rodata.<fn>`, and link-script infers its address
  from the function's `%hi/%lo` pairs, so it moves with the function
  (func_001c0bf0's and func_001c48c8's jump tables did: out/gen/rodata.tsv now
  names script_vm.c.o and script_vm.nostrict.c.o). A file-scope `const`
  table is attributed to the next function in the file: keep it directly above
  its user, or declare it `extern D_X`.
- **Data defined in C**: each variable is placed by name (`.data.<name>`), so it
  can live in any file; define it in the module that owns it, never `static`.
  This module defines none (D_00629808 stays in src/auto/text_001c0000.c with
  func_001c07f0, its user). Session 31 moved D_003C5898 (opcode 1's table) from
  src/auto/text_001c0000_10.c into src/vm/vm_calc.c with nothing else to change.
- **Removing a function from an old file**: if a function left in that file calls
  it from below, leave a CONTEXT_ONLY copy (or `{}` stub) at its place, since the
  caller may have matched with the definition above it (h42 kept a CONTEXT_ONLY
  func_001c4640 for its five callers until session 32 showed they do not need
  it). Delete what only the moved
  functions used (views, `#define D_X (*(View *)&D_X)` macros, externs,
  prototypes), files left empty, and their include/data/types headers.

## Build and tools

Nothing assumes the src/auto / src/hand names except where noted:

- File discovery: the Makefile takes every `*.c/.cpp/.cc/.s` under src/ (dot-files
  skipped); `kh1tool.py gen` regenerates out/gen/objects.mk when the list changes.
  A new directory needs no registration.
- link-script, patch, verify, progress: work from out/gen/placements.tsv (symbol ->
  address); `decompiled_addrs` (rank) scans all of src/.
- objdiff / report: one unit per source file (src/vm/ is nine units, src/camera/ three and src/msgwin/ one; 924 after session 31, 921 after session 32's first half, 900 after its second half, 879 after session 33).
- autodecomp `--write` only creates new src/auto/ files keyed by address (or
  `--out-dir`); it never touches modules, and a function defined anywhere is not
  retried. Its default flags come from the `src/auto` path.
- Shift build: objects from OBJS, compile rules from objects.mk (variants.py finds
  sources by content); cover_check / reach_check / ptr_only read every src/*.c.
- tools/shift/type_move.py names per-file type headers after the source path
  (src/vm/script_vm.c -> include/data/types/vm_script_vm.h); a module puts its types in
  include/<module>/ instead.
- Every object depends on every header, so adding a header rebuilds everything
  (about 2-3 minutes at -j2).

## Verification (sessions 30 to 39, after each step)

Session 32's second half ran the same checks after each of its seven commits
(`make -j4 && make verify`, `s31_warndiff` 0 new warnings, float_covered.txt
and the kh1-shift.elf symbols / loaded sections identical to the base).

- `make`: OK, byte-identical, 6979 decompiled functions (same as before).
- `make objdiff` / `make report`: all 6979 functions at 100%; placements.tsv
  differs from the base only in the source column of the 60 moved functions.
- `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1 SHIFT_OVERLAYS=<empty dir>`: M12-FLOAT
  OK; float_covered.txt identical to the base, and kh1-shift.elf differs from the
  base only in .symtab / .strtab (object order), every loaded section identical.
- `make test`: PASS.

## Next module moves

- **0x00210000 on: the pages.**  The top menu's pages start here: page 0 (the
  item page) goes on to its open function func_002112f8, set up func_00211358
  and reset func_00211398; the other pages' open functions are func_00213c90,
  func_002160a8, func_00217f58, func_00218f88, func_0021daa0 (page 5),
  func_0021ad08 (page 6) and func_002293f0 (topmenu.c's D_003F32E8; the set up
  / reset lists of func_0020d530 / func_0020d748 name one more function per
  page).  Where each page's code starts is not settled: split by refs.py.
  Old files: auto text_00210000*, s10_w11, n32 / nogcse s6_21, b13, b14,
  s10_r2_7, s7_w16, c15 and what is left of h24, h47, h70.  Move page 0's
  rest into src/menu/items*.c first (it uses D_00641220 ... D_00641BC4 like
  items.c), then one module per page.
  `python3 -I tools/shift/s37move/refs.py 00210000 00214000` lists them.
- What is left of h24, h47, h70, b13 and s7_w19 after that (s7_w15 is now
  src/menu/itemstock.c).
- Keep sized externs in .c files: cover_check reads only those (session 35).
- `tools/shift/s36move/mod.py draft OUT.c func...` writes a draft module from
  the old files (bodies plus every declaration they use, views side by side)
  and `mod.py remove func...` deletes the definitions and the declarations
  only they used (prints EMPTY / NOTE lines).  Sessions 36 to 39 used it for every
  chunk; the checklist below still applies.  It does not copy `static inline`
  helpers (inl_sc) and does not call a file EMPTY while one is left: delete
  such files by hand (session 38: s11_w50, s6_19, c13, s8_w12).
- The library's prototypes of its own functions: the table still declares
  every entry `s32 func_X();`, including the ones now defined above it
  (harmless; a `void` one would conflict, none does).
- Remaining views in vm_lib*.c (see "Session 33" and "Session 32"): each
  was tried on the shared types and is a genuine second view; leave them
  unless a type change makes one fit.
- Remaining views of the camera data: h14 keeps its multi-name `extern f32
  D_003C55E0, D_003C55E4 ...` line (unused, kept for cover_check; drop it
  with a float_covered check).  b10 is gone (session 32).
- Other files' prototypes of VM functions: `python3 -I
  tools/shift/s33types/s33_protodiff.py` lists what is left (none since
  session 34).  `--defs` also lists declarations of functions no header
  declares yet (func_001c4de0, func_001c4ed0, func_001cd238 ...).
- Leave alone the files another worker is retyping in the same session.

## Checklist for a module move

1. Pick the set with evidence (a function table, a call graph, a shared type);
   prefer a contiguous address range. List each function's current file from
   out/gen/placements.tsv, and its flag mode from that file's directory.
2. Copy the bodies into `src/<module>/<name>.c` in address order. Replace views
   with the shared types; include shared headers for data; add a module header
   for what other code calls. Keep `func_XXXXXXXX` names unless the purpose is
   proven (then register it in functions.tsv). Copy callee prototypes exactly
   (return type, `volatile`). For a global with several views, make one type
   whose disagreeing fields are unions, keep each function's member, and keep
   its size under what other files declare.
3. `python3 tools/checkfile.py src/<module>/<name>.c` (jump table words differ there;
   `make` places rodata). For a FAIL, try the function's old flags with
   `KH1_EXTRA_CCFLAGS=...`; if only those match, move it to
   `<name>.<mode>.c` with CONTEXT_ONLY stubs of its callees from above.
4. Remove the definitions from the old files (CONTEXT_ONLY copies where a
   remaining caller below needs one), then their orphaned views, externs,
   prototypes and empty files. Switch other files to the module header only
   where their declarations are already identical.
5. `make` (identical, same function count), `make objdiff`, and
   `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1 SHIFT_OVERLAYS=<empty dir>`
   (in a fresh tree run a plain `make shift` first, then tools/shift/data_owners.py, which needs its M0 link); compare
   float_covered.txt with the same build before the move.
6. Update this page's module table.
