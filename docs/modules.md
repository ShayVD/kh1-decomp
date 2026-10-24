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

## Session 40: the menu pages, 0x002106b8-0x00219128

Session 40 moved 86 functions in five chunks, one commit each (and a sixth
that moved the abilities page's bss and deleted the empty b14), into
src/menu/.  No Mac: static checks only.  Every page ends the same way: its
first window's callback, the title (func_00207830(o, 4, 2, 0, 0, 122,
message)), the open function (topmenu.c's D_003F32E8[page]), set up and
reset (func_0020d530's / func_0020d748's lists).  That is where each split was
made.

| module | files | range | functions |
|---|---|---|---|
| the item page's frame (page 0): its first window D_003F3AB0 (the state D_00641224 opens the list, slot and stock windows), title, open, set up, reset | src/menu/itempage.c (5) | 0x002106b8-0x002113f0 | 5 |
| the equipment page (page 1, message 0x6a): the member list, the slot list (weapon row + Sub_304be8 +0x18 accessory slots), the weapon list (D_00641C10, func_001ef270) and accessory list (D_00642418, func_001ef370), the stat comparisons, the party model's weapon swap | src/menu/equip.c (24), equip.n32.c (1), equip.nogcse.c (1), equip.nostrict.c (1) | 0x002113f0-0x00213d80 | 27 |
| the abilities page (page 2, message 0x6b): the member list, a member's abilities (Sub_304be8 +0x40) or the shared ones (Save +0x599), equip / remove / move, the sort keys D_003F3DE0 and the sort | src/menu/abilities.c (22), abilities.n32.c (2), abilities.nosi.c (1), abilities.nogcse.c (1), abilities.nostrict.c (1) | 0x00213d80-0x00216180 | 27 |
| the customize page (page 3, message 0x6c): the three shortcuts (Save +0x844, the magic list D_00642CA8) and the party members' behaviour (D_003F40F8 settings, presets D_003F41E8 / D_003F4200, style D_003F34B8->a[member]) | src/menu/customize.c (17), customize.nostrict.c (2) | 0x00216180-0x00218020 | 19 |
| the status page (page 4, message 0x6d): the member list, the tab list D_00642CF0 and the tabs (stats, equipment, items, abilities by 12, magic) | src/menu/status.c (8) | 0x00218020-0x00219128 | 8 |

| chunk | commit | deleted |
|---|---|---|
| 0x002106b8-0x002113f0 | 2bbe569 | s10_w11 |
| 0x002113f0-0x00213d80 | 448347e | b13, s7_w16, s10_r2_7, auto text_00210000_13 |
| 0x00213d80-0x00216180 | 46b4a9b | h70, s6_21, auto text_00210000_5; n32/s6_21, nogcse/s6_21, nosi/s11_w44 moved (git mv) |
| 0x00216180-0x00218020 | d73a13e | s12_s12w12, s8_w1, nostrict/s11_w35, auto text_00210000_8 _9; nostrict/h70 moved (git mv) |
| 0x00218020-0x00219128 | edcf650 | s7_w17, auto text_00210000_14 |
| bss | 6ab24bc | b14 (only bss and a static inline left) |

objdiff units 795 -> 788.  The page names (equipment, abilities, customize,
status) come from what the code reads (weapon kinds, AP costs, the magic
shortcuts and party behaviour, the stat tabs); none is proved by a boot.

**Data moved with its users**: D_003F3DE0 (the sort keys, from h70) and
D_00642C34 ... D_00642C50 (from b14) into abilities.c, D_00642D10 /
D_00642D14 (from h71) into status.c.

**Struct findings.**
- **Sub_304be8 +0x40** (`name[0x30]` in D_00304BE8_s.h) holds a member's
  abilities, one byte each (bit 0x80: equipped; func_001ef3a0 and
  func_00214a68 count the entries up to 48), not a name.  **Save +0x599**
  (`list599[0x30]`) is the shared abilities list, **Save +0x844** (`x844[3]`)
  the three shortcuts (func_0013c270 / func_0013c288).  Sub_304be8 +0x18 is
  the accessory-slot count with the accessories at +0x19, the weapon at
  +0x32 (`D_00641BB0->x19[i - 1]` matches func_00212c20 where
  `(&->x18)[i]` does not).  The fields keep their names for now (a rename
  touches every user).
- D_00641BB0 (equip) is `Sub_304be8 *`; two old views used it as an s32
  offset beside the s32 slot index D_00641BB4: the bodies cast
  (`(u8 *)D_00641BB4 + (s32)D_00641BB0`), which keeps the code.

**Traps.**
- **A union access in TextWin reorders**: TextWin's +0xd0 is the union
  `ud0`; func_002106b8, func_00212cc0, func_002134c8, func_00214b20,
  func_00214fc8, func_00215420, func_00215838 and the customize windows keep
  views with plain s16 / u16 +0xd0 / +0xd2 (PageWin, WinU16, WinS16, AbWin,
  WinP24, CuWin*).  A pointer at +0x24 (PageWin, WinP24, CuWin, StWin) is
  also kept: as s32 the stores there move.
- **The return type of a callee whose result is unused still matters**:
  func_002066b0 declared s32 gives func_002119a8 v1 for v0 (2 words);
  customize.c needs func_001f9438 s32 for func_00216890 (the others take
  either).
- **An implicit declaration changes registers**: func_00216180 calls
  func_002161e8 defined below it; without a prototype (implicit int) 2 words
  differ.  Declare every callee.
- func_0020a6c0 / func_0020a728 take one argument (partymdl.h), but
  func_00211840 has the window in a1: equip.c declares them `void f();`
  (K&R), as the old files called them both ways.  func_002122b8 is defined
  with an unused `void *` because its callers pass the window.
- func_00215358 and func_002160a8 are void now (the auto drafts returned the
  callee's value; same code).  D_00641BC4 and D_00642D18 need no `volatile`
  (the auto drafts had it).
- The FLAGGED dead code of func_00214a68 (abilities.nosi.c) and
  func_00217000 (customize.nostrict.c) moved as it was.

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings (and no
warnings in the new files), and the m12 float build with float_covered.txt
(the same set; one line changes place), float_reach.txt, the loaded bytes
and the symbols the same as the base.  At the end, with data_owners.py
rerun, the same; `make report` 6979 at 100% and `make test` passes.

## Session 41: the settings, the config page and page 5's frame, 0x00219128-0x0021dbb8

Session 41 moved 109 functions in five chunks, one commit each, into
src/menu/.  No Mac: static checks only.  Pages 6 and 5 end like pages 0 to 4
(first window with the title func_00207830(o, 4, 2, 0, 0, 122, message),
open = topmenu.c's D_003F32E8[page], then set up / reset from
func_0020d530's / func_0020d748's lists).  Page 5 differs: its set up and
reset also call six section set ups / resets far on (0x0021dbb8 ...
0x00223978), so its frame was split in three by what the code does and its
sections are left for later.

| module | files | range | functions |
|---|---|---|---|
| the settings block's accessors: D_003F34B8 f0 f4 f8 f10 f14 f18 f2c, numbered 0-6 by func_00219158 (get) / func_002191f0 (set), a get / wrapper / set each, the reset func_00219128; func_00219428 tests D_002B6478 == 2 | src/menu/settings.c (28), include/menu/settings.h | 0x00219128-0x00219440 | 28 |
| the config page (page 6, message 0x6f): the option list func_00219f98 (eight rows, D_00642D24 the cursor, row 7 resets), the three two-choice windows (func_00219a88 / c18 / da8), func_00219870's twelve-box frame (D_003F4A48), func_00219500 loads two textures that func_00219598 draws (GS packet + sceGsSyncPath); open func_0021ad08, set up func_0021adb0, reset func_0021adc8, and func_0021add8 (D_003F34B8->b112[1], the top menu's marker on page 5) | src/menu/config.c (16), config.nostrict.c (1) | 0x00219440-0x0021ade8 | 17 |
| page 5's model: D_00643020 (JMdl, 0xd0 bytes, one type for three views), asked for by func_0021b4c8 / func_0021b5c8, loaded by the steps of func_0021b6a0 (D_006430F0), set up func_0021b250, drawn func_0021af38, freed func_0021b418; the camera func_0021ae28 | src/menu/journalmdl.c (15) | 0x0021ade8-0x0021b860 | 15 |
| page 5's sprite frames: func_0021b860 / func_0021bbe0 / func_0021bf68 draw sprites of D_003F4CF0 (GS packets + sceGsSyncPath), the frames func_0021c450 ... func_0021c9a0, the cursor func_0021c4f8, a labelled bar func_0021cbc8, the title box func_0021ccd0 | src/menu/journalfx.c (10), journalfx.nostrict.c (3) | 0x0021b860-0x0021cd68 | 13 |
| page 5's frame (message 0x6e): the section list func_0021cd68 (D_00642E98 / D_00642EA0, openers D_003F5A00), the first window func_0021d348 (loads six files, D_00642EA4 the step; sets D_003F34B8->b112[1] once all six D_003F5C30 flags are set), open func_0021daa0, set up func_0021dad8, reset func_0021db30 | src/menu/journal.c (21) | 0x0021cd68-0x0021dbb8 | 21 |

| chunk | commit | deleted |
|---|---|---|
| 0x00219128-0x00219440 | cb17378 | (nothing: auto text_00210000*, h24 lose their accessors) |
| 0x00219440-0x0021ade8 | b7e60f4 | nostrict/s9_w7, s9_r2_5 (only a CONTEXT_ONLY stub left) |
| 0x0021ade8-0x0021b860 | d3e8e24 | s9_w5 |
| 0x0021b860-0x0021cd68 | 30df3b5 | nostrict/s6_22, nostrict/c15, auto text_00210000_10 _11 |
| 0x0021cd68-0x0021dbb8 | df796a8 | auto text_00210000_2 _4; c15's `#if 0` draft of func_0021d860 |

objdiff units 788 -> 786 (seven new files, nine
deleted).  The names (settings, config, journal) come from what the code
reads (seven stepped options and a reset row; six files loaded, six
section flags, a model per entry); none is proved by a boot.

**Data moved with its users**: D_003F4A48 (from s6_22) into config.c;
D_006430EC (from auto text_00210000_3) into journalmdl.c; D_00642E90 (from
auto text_00210000_4), D_003F59E8 / D_003F5A00 (from h71) and D_003F5C08
(from h47) into journal.c.

**Struct findings.**
- **D_003F34B8** (S34B8_3f34b8): f0 f4 f8 f10 f14 f18 f2c are seven
  settings (index 0-6 of func_00219158 / func_002191f0, maximum
  D_003F4C18[n]); fc has no accessor; **b112[1]** (+0x74) is page 5's
  "complete" marker (set by func_0021d348, cleared by func_0021db30, read by
  func_0021add8 for the top menu).
- **D_00643020** is page 5's model object: one JMdl in journalmdl.c
  (x0 the file, x14 the loaded data freed with &x14, xc8 a JP8 *, xcc
  "loaded"); h24's S3020 view (f0 / f14 / fc8 / fcc) was the same fields.
- func_0021b800 returns func_001efcb0's value (s32; it was void in h24 and
  journalfx.c's func_0021cbc8 passes it on).

**Traps.**
- **A body of the callee above the caller turns one branch into a
  branch-likely**: func_00219f98 needs a CONTEXT_ONLY func_00219380 above it
  (any body; settings.c defines the real one) and func_00219870 a
  CONTEXT_ONLY func_00219598 (an empty body is enough; the real one is in
  config.nostrict.c).  Without them one bne becomes bnel (1 word).
- **mod.py remove can leave a caller without a prototype**: h71's
  func_0021cd68 called func_0021c5e0, defined above it in h71; after the move
  it was implicit int (2 words).  h71 now declares it.  Check moved names
  for callers below their old definitions (a quick script: the first call of
  each name in a file with no declaration before it).
- refs.py's third column lists callees: `grep -v NAME` on its output also
  drops the callers of NAME (func_00219870 nearly stayed behind).
- tools/checkfile.py shows relocation words as differences for data defined
  in the same file (D_003F4A48, D_006430EC, D_00642E90) and for jump tables;
  `-v` lists them; `make` is the judge.
- func_0021d860 needs func_001f9438 / func_001fc308 declared s32 (void: 7
  words, from c15's old note).

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings, and the m12
float build with float_covered.txt, float_reach.txt, the loaded bytes and the
symbols the same as the base.  At the end `make report` 6979 at 100% and
`make test` passes.

## Session 42: page 5's six sections and page 7, 0x0021dbb8-0x002298e0

Session 42 moved 178 functions in ten commits into src/menu/.  No Mac:
static checks only.  Page 5's six sections each end with their opener
(D_003F5A00[k] keeps the section's window), set up and reset; the files are
numbered by k, the index in the opener table, not by address (in memory the
order is 2, 0, 3, 5, 1, 4).  Page 7 starts right after them, at 0x00223980:
the party change, the save / load windows and the page's frame.

| module | files | range | functions |
|---|---|---|---|
| page 5's section 2: three lists of entries (0-48, 49-126, 127-183, flags func_001eb038(func_0021dc08(i)), names messages 0x51 + i), the "complete" flags D_00643278 / D_003F5C38, the entry list func_0021ed60, the entry's detail with its model func_0021e8d8, the model viewer func_0021e670, the file load func_0021e538 (D_003F5C50) | src/menu/journal_s2.c (26), journal_s2.nostrict.c (2) | 0x0021dbb8-0x0021fbb8 | 28 |
| section 0: 31 entries of D_003F5FF0 / D_003F6070 accepted by func_001eb9a8, four rows a page, an entry's text (func_001c2df0 on D_003F3518) | journal_s0.c | 0x0021fbb8-0x002205e0 | 14 |
| section 3: 99 numbered entries (func_001eb318) in nine groups (D_003F61E0[i / 3]), the group list and the 99 as a grid (func_00220c28, nofill) | journal_s3.c (12), journal_s3.nofill.c (1) | 0x002205e0-0x002210f8 | 13 |
| section 5: eight record pages (func_001ec538's flags; five rows of func_001eb5f0(table, row) with three numbers, most likely times) | journal_s5.c | 0x002210f8-0x00222ba8 | 32 |
| section 1: 13 entries of func_001ebc38, four rows a page, an entry's text (D_003F3520) | journal_s1.c | 0x00222ba8-0x00223508 | 14 |
| section 4: five entries of func_001ec5d8 with a count (func_001c0da0) against a goal D_003F6740[i] | journal_s4.c | 0x00223508-0x00223980 | 11 |
| page 7's party change: the list func_00224060 (D_00643770: Sora and the members; func_0013c778 sets the party), the swap list func_00223a90, the model loads func_00223e10 (also called by journal.c's func_0021d348) / func_00223ea8 | src/menu/party.c | 0x00223980-0x002245c8 | 12 |
| page 7's save and load windows: the port choice func_002280c0, the 99-slot list func_00225330 (D_00351E10's directory: magic 'KHSQ', version 0x01317f14), the free-space bar func_00228330, a dozen message boxes with their title setters, and the card task func_00225ea8 (nostrict) | src/menu/savemenu.c (37), savemenu.nostrict.c (1) | 0x002245c8-0x00228760 | 38 |
| page 7's frame (message 0x70): the list func_002287f8 (save, party, a message box, leave), open func_002293f0, set up func_00229820, reset func_00229850; func_002295a0 opens the menu on this page by itself (D_003F34A8 = 1) and func_002297a0 the party change (D_003F34A8 = 2) | src/menu/page7.c | 0x00228760-0x002298e0 | 16 |

| chunk | commit | deleted |
|---|---|---|
| 0x0021dbb8-0x0021fbb8 | 4cb16a5 | auto text_00210000_1 _7 _12, cc, nostrict/b14, nostrict/s19_s19m1 |
| 0x0021fbb8-0x002205e0 | 5ea1109 | auto text_00210000, _3, _6 |
| 0x002205e0-0x002210f8 | e2ea004 | h71, nofill/c2 |
| 0x002210f8-0x00222ba8 | d4887c2 | h24 |
| 0x00222ba8-0x00223508 | e3365b2 | (nothing) |
| 0x00223508-0x00223980 | 06eb7cc | (nothing) |
| 0x00223980-0x002245c8 | a120a18 | c15 |
| 0x002245c8-0x00228760 | a50ee18 | nostrict/s6_g2 (renamed to savemenu.nostrict.c) |
| 0x00228760-0x002298e0 | b1f6d51 | h47, s8_w5, auto text_00220000_1 _10 _11 |

objdiff units 786 -> 779.  The names (journal sections, party, savemenu,
page7) come from what the code reads; none is proved by a boot.  Page 7 is
most likely the save point's menu (save, change the party).

**Shared views.**  include/menu/journal.h: JsWin, the TextWin fields the
sections read (+0xc / +0x10 chain, +0x24, +0x40, +0x90, +0xa0, +0xb0 /
+0xb4, +0xc4 s16, +0xca ... +0xce, +0xd2 a plain s16, +0xd8 / +0xda).
include/menu/page7.h: PtWin (+0xba / +0xc0 as u16: the title setters add to
them with lhu) and func_00223980.  Both could fold into TextWin later
(tools/shift/s38move/fold.py) where +0xd2 is not read as plain s16.

**Data moved with its users**: D_006435BC / C0 / E8, D_00643610 / 38 (from
h71) into journal_s3.c; D_006436C8 (from auto text_00220000_4) into
journal_s4.c as `JsWin *`; D_003F5C50 (from h47) into journal_s2.c;
D_00643710 stays in savemenu.nostrict.c.

**Traps.**
- **A deleted file's initialized data**: h47's `s32 D_003F5C50[0x4]
  ALIGNED(16) = {...}` was lost with the file and `make` still said
  byte-identical (data_003F.s's piece keeps the bytes); only the float check
  saw it (float_covered.txt / float_reach.txt changed: D_003F5C50 left both).
  Before deleting a file, list its definitions with a pattern that keeps
  `ALIGNED(` lines (`grep -n "^[a-zA-Z][^(]*D_[0-9A-F]\{8\}[^;]*ALIGNED"`).
- **A union alias set**: journal_s5.c's func_00222670 stores the page
  window's +0x24 through a `union { s32 i; u16 h; }` (local view JsWin24); with
  the plain s32 of JsWin one load moves (8 words).
- **Return types still change code**: func_001f94f0 must return s32 in
  journal_s2.c's func_0021f5f8 (void: 7 words) and func_00233f18 s32 in
  savemenu.c's func_002280c0 (void: 4 words, two registers swap).
- m2c's `func_001f42b8()` (no argument) takes the window that is still in a0:
  writing `func_001f42b8(a)` gives the same code everywhere in this range.
- func_00227f90 passes three extra registers to func_0020bda8, so savemenu.c
  declares it unprototyped (`void func_0020bda8();`).
- tools/checkfile.py differences that are only relocations: jump tables
  (func_00223ea8, func_00225ea8), double constants in .rodata
  (func_00220c28), data defined in the same file (D_006435E8 ...,
  D_006436C8, D_00643710).  `make` is the judge.

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings in the edited
old files, the new files compile without warnings, and the m12 float build
with float_covered.txt, float_reach.txt, the loaded bytes and the symbols the
same as the base.  At the end `make report` 6979 at 100% and `make test`
passes.

## Session 43: the load screen, small screens, the shop's menu, 0x002298e0-0x002327b0

Session 43 moved 138 functions in nine commits.  No Mac: static checks only.
After page 7 the code is a run of small screens, each opened by itself
(`D_003F34A4 = 1` or its own flag, a task through func_0011ef10 that closes
it when its windows are gone) and each ending with its opener, which is how
the range was split.

| module | files | range | functions |
|---|---|---|---|
| the load screen's card windows: the card task func_0022a698 (the directory "BISLPS-25198-??" into D_00643800, each save's 60-byte head into D_00645250, then the slot list func_00229ec0 on the newest save; step 20 loads the slot into D_003F8380 and starts it), the message boxes D_003F6E40 / D_003F6E70 ... D_003F6F00 with their title setters and openers, the status lines | src/menu/loadmenu.c | 0x002298e0-0x0022b248 | 17 |
| the load screen's frame: opener func_0022bcb8 (D_003F34A4, the chain D_003F71A0 / D_003F71C8[5]), task func_0022bc28, the port window func_0022b410 (D_006437C4; no card: the box func_0022b2e0), the free-space bar func_0022b648, the open func_0022b8a0, the cursor reset func_0022bd20 | src/menu/loadframe.c | 0x0022b248-0x0022bd58 | 17 |
| the game settings screen: opener func_0022d080 (D_003F7380), the step handler func_0022cde8 (D_006469B0 / B4) opening one window per setting of settings.c and a summary (func_0022bd58) | src/menu/gamesetup.c | 0x0022bd58-0x0022d138 | 9 |
| a text screen: opener func_0022d4d8, five lines D_003F73B0 ... D_003F7470 that close one after another on the timers D_006469B8[k] once a button is pressed | src/menu/textfade.c | 0x0022d138-0x0022d728 | 10 |
| three choice screens (openers func_0022daa0 / func_0022dee0 / func_0022e368, titles 0x5f / 0x1ce / 0x1d8, answers D_003F76B4 / B8 / BC); the three list handlers need -fno-fill | src/menu/choice.c (15), choice.nofill.c (3) | 0x0022d728-0x0022e458 | 18 |
| a two-row choice screen with a sine pulse: opener func_0022eb00, list func_0022e460 (answer D_003F7778), the timers D_006469D8 ... D_006469F8 | src/menu/choice2.c | 0x0022e458-0x0022ebe8 | 6 |
| the item shop's menu, buying: the list func_0022eef8 (*D_00646A08 items of D_00646A0C, the count D_00646A28, the party's portraits), the check func_0022ebf8 (D_00646A18), the purchase func_0022ee08 | src/shop/shopbuy.c | 0x0022ebe8-0x0022f818 | 7 |
| selling: whose items func_0022fc88 (D_00646A24), the list builder func_0022f818 (D_00646A30 / D_00646E30 / D_00647230), the list func_0022fcb8, the check func_0022fa58 (D_00646A1C), the sale func_0022fba8 | src/shop/shopsell.c | 0x0022f818-0x002305b0 | 6 |
| the same buy and sell lists for the goods of func_001ba3f0 / func_001ba458 (held / most), priced func_001eeaf0 / func_001eeb08, D_00647640 the total: most likely the Gummi blocks | src/shop/shopgummi.c | 0x002305b0-0x002316f8 | 8 |
| the shop menu's opener func_00231740(mode, list, on_cursor, on_choice) (modes 0-3: buy, sell, the two gummi lists; src/shop/shop.c calls it), its task and wrappers | src/shop/shopframe.c | 0x002316f8-0x002319d0 | 9 |
| the synthesis menu: opener func_00232640 (D_003F7E94), the recipes D_003F7C48 / D_003F7A70, the level func_001ec360 and the made-once flags D_00647670, the checks func_00231cd0 / func_00231dd0, the make func_00231b98, the ingredients func_00232390; the list func_00231ea0 needs -fforce-addr | src/shop/synth.c (13), synth.faddr.c (1) | 0x002319d0-0x002327b0 | 14 |

| chunk | commit | deleted |
|---|---|---|
| 0x002298e0-0x0022b248 | 28e686f | auto text_00220000_7, _8 |
| 0x0022b248-0x0022bd58 | f89f7c5 | auto text_00220000_2, _3, _12 |
| 0x0022bd58-0x0022d138 | 1725a92 | h72 |
| 0x0022d138-0x0022d728 | 5937f60 | auto text_00220000_9 |
| 0x0022d728-0x0022e458 | 3141839 | auto text_00220000_5, nofill/text_00210000_b15 (nofill/text_00220000_b15 renamed to choice.nofill.c) |
| 0x0022e458-0x0022ebe8 | 4f96f69 | c16, auto text_00220000_4, _6 |
| 0x0022ebe8-0x002316f8 + the opener | e1fcb63 | auto text_00220000, _13, text_00230000_12, s6_22 (s8_w9 renamed to shopbuy.c) |
| 0x00231908-0x002319d0 | 4d69581 | (nothing) |
| 0x002319d0-0x002327b0 | 2323b7f | s7_w19 (faddr/text_00230000_s7 renamed to synth.faddr.c) |

objdiff units 779 -> 772.  The names come from what the code reads; none is
proved by a boot.  "Load screen" (a card's directory read, a slot loaded
and started, D_003F720C = 1), "game settings" (one window per setting of
src/menu/settings.c), "item shop" (munny func_001ef7a0, 99 a slot, called
from src/shop/shop.c) and "synthesis" (recipes of ingredients and counts, a
level that grows with what was made) are guesses from the data flow.

**Types.**  All the window handlers now take TextWin (include/text/textwin.h)
or page7.h's PtWin (+0xba / +0xc0 u16, which the title setters need); PtWin
got `s16 xd0` in place of its pad (no code change).  The party is
Save_304be8 / Sub_304be8 everywhere (shopbuy.c's func_0022ebf8 used a
local EbMember view: m[k].sub.x21 / x22[] are its n / items[], x48e its
party[], items[] its cnt[]).  func_001ef7a0 (munny), func_001ee708 and
func_001eeaf0 (prices) are u32 in every file.

**Data moved with its users**: D_00643800, D_006469A8 / AC, D_00646994,
D_0064699C, D_0064524C (from s6_22) into loadmenu.c; D_006469D8 / E0 / E8 /
F0 / F8 (from c16) into choice2.c; D_003F6568 (journal section 5's page
table, initialized, from h72) into journal_s5.c as `u8 *[0xa]`.

**Traps.**
- **The deleted file's initialized data again**: h72 held D_003F6568 (no
  function of h72 used it); `make` passed and only the float check saw it.
  A file with no function left can still define data: grep it before
  deleting (`grep -n "^[a-zA-Z][^(]*D_[0-9A-F]\{8\}[^;]*\(ALIGNED\|=\)"`).
- **A void callee moves a store**: loadmenu.c declares func_0011d768 `s32`
  (s6_22 did); with `void` func_0022a698's stores to D_006469A4 /
  D_006437D8 come out in another order (3 words).  The other 16 functions
  in the file match with either.
- **An implicit declaration on purpose**: choice.nofill.c leaves
  func_001f9438 undeclared as b15 did; a prototype swaps two argument loads
  in two of the three handlers.
- **lb vs lbu**: Dir40's name is `char`; the card task reads the slot
  digits through `(u8 *)` (s6_22's view had `u8 name[]`).
- m2c's no-argument calls (`func_001f42b8()`, `func_001ee708()`,
  `func_001eeaf0()`, `func_001ba3f0()`) take the value still in a0: writing
  the argument gives the same code everywhere here.
- One rodata block fewer (229, 9,740 input sections in the shift build):
  the three nofill handlers' doubles 0.08 now share one .rodata of 0x18
  bytes; they are contiguous in the original (0x004912f0 ...), so the bytes
  and the float layout are the same.
- Leftovers: s6_23 keeps its section-by-section declarations (`#define
  func_001ef7a0 func_001ef7a0_s1` ...) for func_002327b0 and func_00234910,
  the two functions left in it.

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings in the edited
and new files, and the m12 float build with float_covered.txt,
float_reach.txt, the loaded bytes and the symbols the same as the base.  At
the end `make report` 6979 at 100% and `make test` passes.

## Session 44: the list menu, the save files, the pad's stand-ins, the memory card queue, random numbers, 0x002327b0-0x00236a58

Session 44 moved 89 functions in six commits (plus one that names libmc).  No
Mac: static checks only.  From 0x00232de0 on the code is the save system's
own: the save files' names and head, the card check, then the memory card
request queue the save and load screens use, which is the first platform
wrapper candidate of the module plan (docs/portability.md rule 2).

| module | files | range | functions |
|---|---|---|---|
| the list menu: opener func_002329a0(menu, on_cursor, on_choice) (D_003F7EC4, task func_00232960, the window D_003F7EA0 sized from the menu's corners), the list func_002327b0, the close func_00232aa8, an empty func_00232ac8 (gamedata.c calls it); src/list/list.c fills D_003DC498 (ListMenu, now in include/list/listmenu.h) | src/list/listmenu.c | 0x002327b0-0x00232ad0 | 5 |
| the save image's seven blocks in D_003F8380 (0x16c00 bytes: 0xc00, 0x1000, 0x400, 0x400, 0x14000, 0x400, 0x400): clear one or all func_00232ad0, get one func_00232cc0, copy to and from the backup D_0040EF80 func_00232d60 / func_00232da0 | src/game/saveimage.c | 0x00232ad0-0x00232de0 | 4 |
| the save files: the names "BISLPS-25198-NN" and its system.bin, icon.sys, mc_icon.bin, mc_copy.bin, mc_del.bin with NN written in (func_00232f88 ... func_00233118), the head D_00425B80 (magic "KHSQ" 0x5153484B / 0x01317F14, level, munny, play time, name; func_00232de0 / func_00232e08 also the icon title D_003F7ED0), the card check task func_00233168 over both ports (D_003F8370[port]: 0 a save, 1 room for one, 2 no room, 3 not formatted, 4 no card) | src/save/savefile.c | 0x00232de0-0x002335d8 | 11 |
| an overlay run in place: "xs_dh_break.x" (D_00425BC0[i]) loaded to 0x00F20000 and called; no C caller | src/game/xsload.c | 0x002335d8-0x00233610 | 1 |
| the pad's stand-ins: D_00425BC8 points at the real pad D_002C5AD0 or at D_00647710, which func_002336f8 fills each frame from a recording (func_00233650), a replay (func_00233680) or a script of (button, frames) pairs (func_002336b0); D_006477A4 counts idle frames (most likely the title's demo timer) | src/pad/padrec.c | 0x00233610-0x00233a80 | 10 |
| the memory card request queue: sceMcInit and the reset (func_00233a80 / func_00233ac8), the waits func_00233d08 / func_00233db0, the card-changed flags, the automatic card-info poll, the 13 request kinds queued into D_006477B0[64] (func_00234018 ... func_002347e0) and their answer codes (func_00234840 ... func_00234900) | src/memcard/mcqueue.c | 0x00233a80-0x00234910 | 31 |
| the steps: func_002365e0 runs D_00425BD0[kind] (now defined here as function pointers), func_00234910 takes the next request, one step function per kind calls libmc through include/platform/mc.h and maps its answer | src/memcard/mcstep.c | 0x00234910-0x00236618 | 15 |
| random numbers: five LCG seeds D_00648038 (x * 0x41C64E6D + 12345; textwin.c's window styles use seed 4), five float seeds D_00648050, and two float generators on a caller's seed (journal_s3.nofill.c) | src/util/rand.c (8), rand.nostrict_nofill.c (2), rand.nofill.c (2) | 0x00236618-0x00236a58 | 12 |

| chunk | commit | deleted |
|---|---|---|
| 0x002327b0-0x00232ad0 | f80d40f | include/data/types/text_00220000_h48.h (Win is ListMenuDesc in listmenu.h) |
| 0x00232ad0-0x00232de0 | f2bae36 | (nothing) |
| 0x00232de0-0x002335d8 | 2e1c68c | s8_w7, s8_w8, auto text_00230000_9 |
| 0x002335d8-0x00233a80 | a6e8514 | c2 |
| 0x00233a80-0x00236618 | f4ad322 | h48, s6_23, sw, b15 |
| libmc names, include/platform/mc.h | 36e0845 | (nothing) |
| 0x00236618-0x00236a58 | d6fab88 | auto text_00230000_4 |

objdiff units 772 -> 773.  The names come from what the code reads; none is proved by a boot.  The
save file names are the strings at D_003F8298 ... D_003F8350 and the
overlay's at D_00491390.  **libmc is named** (functions.tsv, docs/sdk.md
"Session 44") from each function's mcserv RPC number and arguments.

**Types.**  ListMenu (include/list/listmenu.h) is list.c's type with its
corners `u32` (func_002329a0 shifts them unsigned; list.c only stores
constants).  McCmd (include/memcard/mcreq.h) is the queue entry both views
agreed on (`id` / `x4`).  The memory card globals keep `s32` except
D_00648020 / D_00648024 (`char *`, names) and D_00648028 (`void *`), cast
where the dispatcher copies them out of McCmd.a[].

**Data moved with its users**: D_006477A0 (b15) into padrec.c, D_00425BD0
(the step table, auto text_00230000_11) into mcstep.c, **D_003F71C8 (h48's
pointer table of the load screen's five windows) into src/menu/loadframe.c**:
h48 had no load-screen function left; the first build after removing h48
would have lost it (grep for definitions before deleting, as in session 43).

**Traps.**
- **A pointer type moves an address into a saved register**: listmenu.c
  keeps `extern void *D_0064770C`; as `TextWin *` func_002329a0 computes
  &D_0064770C into s1 before the call to func_001f31a8 (40 words).
- **An old-style declaration of sceMcInit**: mcqueue.c's func_00233a80
  matches with `int sceMcInit(void)` / `s32 sceMcInit()` but not with `void
  sceMcInit()` (v0/v1 swap in the clear loop).
- **An implicit declaration on purpose** (as sw.c had): func_00265b28 stays
  undeclared in mcqueue.c; a prototype changes func_00233db0 by 2 words.
- The six step functions that `return` libmc's first answer stay `s32`
  (a `void` changes the code); the table casts them (`Step`).
- mod.py leaves multi-name `extern` lines and duplicate prototypes behind:
  h73 kept a block of memory card declarations nothing used (removed by
  hand).
- `checkfile.py -v` shows only relocations for the moved functions that
  still FAIL there (jump tables, strings, data defined in the same file).

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings in the edited
and new files, and the m12 float build with float_covered.txt (as a set),
float_reach.txt and the loaded bytes the same as the base; the symbols the
same except, from the libmc commit on, the 14 renamed libmc functions (same
addresses).  At the end `make report` 6979 at 100% and `make test` passes.

## Session 45: the menu models' camera, GS packets, the draw list, primitives, the HUD's set up and textures, 0x00236a58-0x00239558

Session 45 moved 43 functions in four commits (plus one that names libvu0).  No
Mac: static checks only.  From 0x00236f00 on the code is the HUD's (its set up
func_00236f18 calls one set up per part from 0x0023b570 to 0x00249250 and its
textures come from "command2/uitex.bin") and the generic GS code it draws
with: packets, a depth-sorted draw list and batch senders, all on libvu0 and
the GIF DMA channel (docs/portability.md: the renderer's platform layer).

| module | files | range | functions |
|---|---|---|---|
| the menu models' camera func_00236a58 (D_00425F70, Cam_425f70: aims at the target with atan2f or orbits it at `dist`, builds m80 with sceVu0CameraMatrix, mc0, m0 = m40 x m80, the view direction v190; journalmdl.c calls it), a camera matrix from a caller's angles func_00236c68, rotations by three angles func_00236d48 (z, x, y) / func_00236d98 (x, y, z), a scale matrix func_00236de8 | src/menu/mdlcam.c | 0x00236a58-0x00236e40 | 5 |
| vertex range checks (x, y > 0xFFFF or z > 0xFFFF28 in GS 12.4 coordinates; one vertex, a quad) | src/gfx/gsclip.nofill.c | 0x00236e40-0x00236f00 | 2 |
| the HUD's set up func_00236f18 (the draw list D_00425F80 with 256 buckets at D_00425F88, 14 part set ups, D_00425F78 = 0), the start-up upload func_00236f00, three empty hooks | src/hud/hud.c | 0x00236f00-0x00236fd8 | 5 |
| GS packets: a GIFtag for A+D qwords func_00236fd8, one A+D qword func_00237008, the default drawing environment func_002370c8 (FRAME_1 512 wide, ZBUF_1, XYOFFSET_1, SCISSOR_1 512x384, TEST/ALPHA/FBA_1, TEX0/1/2_1, MIPTBP1/2_1, CLAMP_1, PRMODECONT, COLCLAMP; DTHE, DIMX, PABE, TEXA) sent from D_006480D0 by func_002372e0 and a variant by func_00237318; the GIF DMA sender func_00237018 (nostrict_nofill) | src/gfx/gspkt.c, gspkt.nostrict_nofill.c | 0x00236fd8-0x00237548 | 6 |
| the depth-sorted draw list (include/gfx/drawlist.h: DrawList / DrawBucket / DrawNode): set up func_00237600 / func_00237660; push func_00237680 and the raw packet of a kind 4 node func_00237ec0 (nostrict); the projection of a triangle with libvu0's screen clip func_00237548, the push by depth func_002376c8, the node kinds 1 (line) func_00237790, 2 (flat triangle) func_002378c8, 3 (lit textured triangle) func_00237d48, a fan func_00237b30, the point projection func_00237a48, the flushes func_00237f20 (one send per node), func_002380c0 (one per bucket), func_00238258 (one packet of kind 3 nodes) (nostrict_nofill) | src/gfx/drawlist.c (2), drawlist.nostrict.c (2), drawlist.nostrict_nofill.c (10) | 0x00237548-0x00238440 | 14 |
| primitives sent at once (draw-list nodes without the list): lines one by one through D_00648070 func_00238440; flat triangles func_002384e0, textured quads func_00238768 (nostrict); lines func_002386c0, textured quads into a caller's buffer func_002388b8 (the HUD's sprites) (nostrict_nofill) | src/gfx/prim.c (1), prim.nostrict.c (2), prim.nostrict_nofill.c (2) | 0x00238440-0x002389f0 | 5 |
| the HUD's textures: image n of command2/uitex.bin func_002389f0 (nofill), the load and the 21 images' set up func_00238a70 (D_006483B0 defined here; s6_24 nostrict_nofill renamed) | src/hud/hudtex.nofill.c, hudtex.nostrict_nofill.c | 0x002389f0-0x00239368 | 2 |
| the uploads func_00239368 (the textures and a 16x16 CLUT) / func_002393d8 (the font: text.c's image at 0x3600 and CLUT at 0x3A00), the HUD's step func_00239488, the busy check func_002394f8 (vm_lib.c's func_001da178) | src/hud/hud.c | 0x00239368-0x00239558 | 4 |

| chunk | commit | deleted |
|---|---|---|
| 0x00236a58-0x00237548 | ee80d18 | h73, auto text_00230000_8 |
| 0x00237548-0x00238258 | 642fd46 | h25 nostrict, h73 nostrict_nofill, s8_w1, s9_r2_6, s9_w10, auto text_00230000_5 |
| 0x00238258-0x002389f0 | e037448 | s7_w27, s8_w6 |
| 0x002389f0-0x00239558 | d4f4df5 | auto text_00230000_7 (s6_24 nostrict_nofill became hudtex.nostrict_nofill.c) |
| libvu0 names | e3ce7c9 | (nothing) |

objdiff units 773 -> 774.  The names come from what the code reads (the
HUD from "command2/uitex.bin" and its set up list); none is proved by a boot.

**Types.**  include/gfx/drawlist.h is h25's / s9_w10's / h74's Hash, Bucket
and Node (one view; the node kinds read by the flushes).  include/gfx/gspkt.h
declares the packet functions; only the new modules and h48 include it, the
other ~25 files keep their own prototypes (`void func_00237018(void *, s32,
s32)` and variants: switch them one at a time with `make`).
D_00425F80 / D_00425F88 are typed in hud.c (DrawList, DrawBucket[256]) and
left data_0042.h, their only C user being hud.c.

**Data moved with its users**: D_00648070 (h25, the line buffer) into prim.c.
D_006483B0 stays with func_00238a70 (the renamed file).

**Traps.**
- **A third argument nobody reads**: func_00237f20 and func_002380c0 call
  func_00237ec0 with a third 0 (`move a2,zero`); the definition takes two.
  drawlist.nostrict_nofill.c declares it with three (a comment says why).
- **func_002380c0 needs func_00237790 above it** (one bne / bnel): it was
  in h48 below 00237790; moved with it into drawlist.nostrict_nofill.c.
  checkfile showed it only after `make` (NONMATCHING at link time): run
  `make` after each `mod.py remove`, not only checkfile.
- func_00237548 was `void` in h48 and `s32` in its callers: as `s32 ...
  return sceVu0ClipScreen3(...)` it matches and the file needs one type.
- mod.py's drafts put each old file's types side by side (four V4 / I4 /
  node views here): merge them by hand.  A V4 with `aligned(16)` did not
  change func_002376c8 (it was unaligned in s9_w10).

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings, and the m12
float build with float_covered.txt, float_reach.txt, the loaded bytes and the
symbols the same as the base; the libvu0 commit adds the 39 names (same
addresses) and drops five func_ aliases nothing references.  At the end `make
report` 6979 at 100% and `make test` passes.

## Session 46: the HUD's parts, 0x00239558-0x00249fb0 (the gauges 0x0023cfe8-0x00243168 left)

Session 46 moved 206 functions into src/hud/ in 17 commits.  No Mac: static
checks only.  The range is the HUD: hud.c's set up (session 45) calls one set
up per part, each part registering a draw hook with func_0011ef10(priority,
fn) when func_0011ef38(fn) is 0, with a step for hud.c's step (all off), a
busy check, its own GS drawing environment (a 0x160-byte packet: unkE0 = 5,
unk60 = 0x30003, sometimes TEST_1 0x8000000048 at +0x70), D_00351E10 as its
staging buffer and func_002388b8 to add a sprite.  The gauge part
0x0023cfe8-0x00243168 (about 70 functions, ttlib/ui_gauge.c) was left for
session 47: see "Next module moves".

| module | files | range | functions |
|---|---|---|---|
| the HUD's drawing helpers: a glyph through text's func_001f0638, a sprite and its second layer (func_00239630 / func_00239778), a vertical list of entries with a selection frame (func_00239e30) | src/hud/hudspr.c (c17 renamed), .nofill.c, .nostrict.c, .nostrict_nofill.c | 0x00239558-0x0023a318 | 9 |
| the command menu: its draw hook func_0023a968 (the slide D_00449908.f7c / f80, the entries' fade, each open list of D_002E3170), the frame list func_0023a608, the set up func_0023b570; CmdMenu / HudSpr types, the 63 sprite buffers as HudSpr arrays (from s6_24) | src/hud/cmdmenu.c (s11_w19 renamed), .nofill.c, .nostrict.c, .nostrict_nofill.c | 0x0023a318-0x0023c1b0 | 11 |
| markers over actors (ten in D_00651310), the lock-on mark (func_0023c7a0), the three-sprite sign (D_0044A820) | src/hud/marker.c, .nofill.c, .nostrict.c, .nostrict_nofill.c | 0x0023c1b0-0x0023cfe8 | 19 |
| the notice: a queue of five (D_006561D0, NoticeMgr / Notice / NoticeQueue) shown at (160, 344) with the name of an id; most likely "obtained" | src/hud/notice.c, .nostrict.c | 0x00243168-0x00243c10 | 16 |
| the party popups: a title bar, middle and bottom lines of sprites and texts | src/hud/popup.c, .nostrict.c | 0x00243c10-0x00244960 | 11 |
| the counter: a value in five digits (func_00244b10) and its sprites | src/hud/counter.c, .nostrict.c | 0x00244960-0x00245238 | 11 |
| the mark over an actor (D_006627B0: kind, actor, state, alpha) | src/hud/actmark.c, .nostrict.c | 0x00245238-0x00245798 | 9 |
| numbers over the field (ten DmgNum in D_00662A30); most likely damage and heal | src/hud/dmgnum.c, .nostrict.c | 0x00245798-0x00245f58 | 14 |
| the marks over the two party members (PMark D_00668040), read by the battle code h60 | src/hud/partymark.c | 0x00245f58-0x00246570 | 10 |
| the target's gauge (TgtGauge D_00668370), fed by marker.c's func_0023c1b0 | src/hud/tgtgauge.c | 0x00246570-0x00246cf0 | 9 |
| labelled numbers over the field (ten LblNum in .data D_0045FAC0) and their entry points | src/hud/lblnum.c, .nostrict.c (s8_w10 renamed) | 0x00246cf0-0x002474e8 | 13 |
| the timer and score display (MgSlot D_00669350 points at a caller's MgHud: score, distance, time, record); func_002485f0's bits move tgtgauge / marker down; most likely the minigames' | src/hud/timer.c, .nostrict.c | 0x002474e8-0x00248628 | 20 |
| the banner: a five-entry queue (Vec12Queue in D_00669700) shown at (160, 344) in seven parts and an end part | src/hud/banner.c | 0x00248628-0x00248fb8 | 15 |
| a two-sprite display shown once (D_00469F60, D_00669A10) | src/hud/oneshot.c | 0x00248fb8-0x002492d0 | 7 |
| math helpers: a fade step, rotation / translation / look-at / scale matrices on libvu0 (called by name), the GS-to-screen offset, a clip test, Hermite segments (func_00249618 Catmull-Rom, nogcse), an angle wrap, a clamp, a lerp | src/hud/hudmath.c, hudmath.nogcse.c (s8_w5 renamed) | 0x002492d0-0x002499f0 | 20 |
| TIM2 picture uploads: image and CLUT (func_00249a48), image only (func_00249dc8), a list of them, the TEX0 fields (func_00249f08 / func_00249d50), the "TIM2" test, the CLUT copy | src/hud/timload.c | 0x002499f0-0x00249fb0 | 12 |

Each file's top comment says what its code reads and what is a guess; none
of the names is proved by a boot.  objdiff units 774 -> 782; src/hud has 217
functions.

| chunk | commit | deleted |
|---|---|---|
| 0x00239558-0x0023a318 | a65654a | h48 nostrict_nofill (c17 became hudspr.c) |
| 0x0023a318-0x0023c1b0 | 2ba6e16 | c18 nostrict, auto text_00230000_10 (s11_w19 became cmdmenu.c) |
| 0x0023c1b0-0x0023cfe8 | 47608aa | h25, auto text_00230000_1 / _2 / _11 |
| 0x00243168-0x00243c10 | 4550448 | auto text_00240000_14 |
| 0x00243c10-0x00244960 | cf83298 | (nothing) |
| 0x00244960-0x00245238 | 7872427 | (nothing) |
| 0x00245238-0x00245798 | a4f8762 | (nothing) |
| 0x00245798-0x00245f58 | 7f70a64 | (nothing; s7_w1 nostrict keeps its other functions) |
| 0x00245f58-0x00246570 | b5a38b9 | e8040, auto text_00240000_15 |
| 0x00246570-0x00246cf0 | f5a1b55 | (func_002466e8 out of src/anon/session1_probes.c) |
| 0x00246cf0-0x00247350 | dc5d28e | (s8_w10 nostrict became lblnum.nostrict.c) |
| 0x00247350-0x002474e8 | 1c1736a | auto text_00240000_1 |
| 0x002474e8-0x002485b8 | 49c79c2 | b16 |
| 0x002485b8-0x00248fb8 | 21c97f9 | sw, auto text_00240000_6 / _19 |
| 0x00248fb8-0x002492d0 | 1d2a914 | (nothing) |
| 0x002492d0-0x002499f0 | e176401 | s11_w34, auto text_00240000_9 / _10 / _11 (s8_w5 nogcse became hudmath.nogcse.c) |
| 0x002499f0-0x00249fb0 | 5aca32e | c2, auto text_00240000_12 |

**Source names.**  The assert strings name the original files: "ttlib/ui_gauge.c"
(func_00240400, lines 2727 / 2747, "tt_gaugeWorldmap.barrier": D_00454A20 is
tt_gaugeWorldmap) for the gauge part, and "ttlib/ui.c" (func_00249fb0,
func_0024a1c8, func_0024a300, func_0024a490: lines 14, 100, 137, 199) for the
sprite library from 0x00249fb0 on (docs/elf-notes.md).  So 0x00249fb0-0x0024f2e0
is one library file, not HUD parts: move it as src/hud/ui.c (or src/ttlib/).

**Data moved with its users** (by hand, same type and alignment): each part's
drawing environment and sprite buffers (D_00648630, D_00648790, D_00650F40,
D_00650DE0, D_006510A0, D_00656254 ... D_006560F0, D_006562C0, D_00656424,
D_00656430, D_0065FCA0 ... D_0065FC94, D_006627B8 ... D_006626C4, D_006627E0,
D_00662950, D_00662944, D_00667F60 ... D_00667DF0, D_00668290, D_00668120,
D_00668284, D_00668E20, D_00668F90, D_00668F84, D_00669070, D_006691E0,
D_006692C0 ... D_00669338, D_006694B0, D_00669614, D_00669620, D_006697C0,
D_00669924, D_00669930).  The names in src/data/bss_006x.c stay there.

**Traps.**
- **CONTEXT_ONLY copies**: mod.py draft skips them.  func_0023a968 needs a
  CONTEXT_ONLY func_0023a720 above it (beql / beq), cmdmenu.nostrict.c one of
  func_00239a80, dmgnum.nostrict.c func_00245a08 / func_00245ad8.  Grep the
  old file for CONTEXT_ONLY above each moved function.
- **A callee leaving a file**: func_0023a490 failed at link time after
  func_00239630 left h74; a prototype in h74 fixed it.
- **The f32 argument's place**: callers that passed the f32 in another
  position than the definition (EABI: f12 whatever the order) reordered the
  code; popup.c and timer.c call through a `#ifdef KH1_PS2` cast macro
  (DRAW_TEXT) as the old files did.
- **u32 against s32 switches** (sltiu / slti): func_002464f8 needs
  `switch ((s32)...)`, LblNum an `s32 state`.
- **Unused parameters**: a function its callers in the same file give more
  arguments (func_00246750, func_002480d8) takes them.
- **Count the functions before deleting a file**: text_s7_w1 nostrict was
  deleted by mistake (6977) and restored with only its part cut out.
- **A label cover_check needs**: banner.c keeps `extern Vec12Queue
  D_00669714` (D_00669700.q by its own name); without a sized declaration of
  it D_00669760 after it became covered (float_covered.txt changed).
- Header type clash: a local Pkt clashed with bss_0064.h's; marker.c names
  it GsEnv and does not include the header.

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `s31_warndiff` 0 new warnings on the edited
files, 0 warnings in the new ones, and the m12 float build with
float_covered.txt, float_reach.txt and the loaded bytes the same as the base;
the symbols too, except D_006561E4 (a label inside D_006561D0) and
func_00267f50 (sceVu0ClipAll's old alias), which nothing references any more.
At the end `make report` 6979 at 100% and `make test` passes.

## Session 47: the gauges, ttlib/ui.c and the rest of the game segment, 0x0023cfe8-0x00243168 and 0x00249fb0-0x0024f2e0

Session 47 moved 200 functions in six commits.  No Mac: static checks only.
After it no C file under src/auto or src/hand is left in
0x00239558-0x0024f2e0: the game segment ends in modules (the hand asm
src/asm/text_0024e0a4.s stays).  The "123 functions of ttlib/ui.c" in the
plan were five original files, told apart by their assert strings and the
order of their data:

| module | files | range | functions |
|---|---|---|---|
| the gauges (ttlib/ui_gauge.c): the party's round HP / MP gauges and the world map's (tt_gaugeWorldmap, D_00454A20); one Gauge object (0xD00 bytes) and GaugeTbl (D_00651E50) in include/hud/gauge.h | src/hud/gauge.c, .nofill.c, .nostrict.c, .nostrict_nofill.c (h74 renamed) | 0x0023cfe8-0x00243168 | 72 |
| ttlib/ui.c: the sprite animation library (UiSpr with its three tracks, UiPkt; include/hud/ui.h) | src/hud/ui.c, ui.nostrict.c | 0x00249fb0-0x0024b0c8 | 31 |
| src/decode.c: packed blocks through the method table D_00469FC8 (copy, or the asm decoders), the empty assert handler func_0024b1e8 | src/util/decode.c | 0x0024b0c8-0x0024b1f0 | 4 |
| src/sa_task.c: eight cooperative tasks with their own stacks, started and switched by the hand asm (TASK_GRUPE_MAX) | src/util/sa_task.c, sa_task.nostrict.c | 0x0024b1f0-0x0024b9a8 | 34 |
| the movie names (D_0046A058: opn.dat, end.dat, end2.dat, demo.dat, end3.dat, ffx2.dat) and the one chosen | src/game/movies.c | 0x0024b9a8-0x0024ba28 | 6 |
| a named parameter-list reader (a BREAK when a name is missing) | src/util/param.c | 0x0024ba28-0x0024bc68 | 4 |
| the name-entry screen: a five-page character grid, eight characters in D_00669A40, written into a save slot | src/menu/nameentry.c, .nofill.c (s12_s12w14 renamed) | 0x0024bc68-0x0024d4a0 | 19 |
| the HDD install and start-up: dev9 / atad / hdd / pfs.irx, the HDD thread and its semaphore, the installed kingdom.img check | src/game/hdd.c, hdd.nofill.c (s6_25 nofill renamed) | 0x0024d4a0-0x0024e0a4 | 25 |
| the player's model change: swap the controlled character for an object by id, load a character's model | src/game/plmodel.c, plmodel.nostrict_nogcse.c (s6_25 nostrict_nogcse renamed) | 0x0024f008-0x0024f2e0 | 5 |

Each file's top comment says what its code reads and what is a guess; none
of the names is proved by a boot (the HDD path needs the Japanese HDD
unit).  objdiff units 782 -> 757.

| chunk | commit | deleted |
|---|---|---|
| the gauges | 1cc32e1 | 16 files: auto text_00230000 / _3 / _6 and text_00240000_4, h25 nofill, h49 nofill and nostrict, s6_24 and its nostrict, and the nostrict b16, c2, s7_w2, h75, s6_g1, s7_w36, s7_w3 (h74 nostrict_nofill became gauge.nostrict_nofill.c) |
| ttlib/ui.c | d2e3965 | gs, auto text_00240000_5 / _16 / _18 |
| decode.c, sa_task.c | 83471be | h26 and its nostrict, auto text_00240000_8 / _13 / _17 |
| movies, param, name entry | 982d2f6 | s6_25, s9_w3, s10_w12, b17, text_001c0000_s6_nb |
| the HDD | 6456b62 | text_00240000.c, h27, h75, s8_w5, d7b0 nofill, auto text_00240000_2 / _7 |
| the player's model | eb15dfe | h50, auto text_00240000 / _3 |

**Data moved with its users** (same type and alignment): D_00651C00 (QA),
D_00651D70 (Pkt), D_00652888, D_00652898 and D_00654570 (the gauges);
D_00469FC8 (decode.c); D_00469FF8, D_00469FD8 and D_0046A018 (the task
entry tables); D_0046A058 (the movie names); D_00669A80 (the HDD thread's
stack).  The names in src/data/ stay there.

**Traps.**
- **Union members change the alias set.**  An s32 store and a pointer store
  schedule differently under strict aliasing, and any access through a
  union member uses the union's alias set.  func_00241b60 stores the
  actor through Gauge's `unk4i` (an s32 member beside `GActor *unk4`) to
  keep its order; in sa_task.c a union broke func_0024b7a0, so the
  functions that read the stacks as words use a second view, TaskW, and
  Task keeps plain pointers.
- **One base pointer**: ui.c's track functions (a0c0 / a2e0 / a568) need the
  flags inside each track (UiAnim.flags), so they read `s->flags` from the
  track's own pointer.
- **Element types decide the loads**: Gauge's unk90 is `s32 (*)[4]`
  (a `u8 *` gave lbu loads).
- **CONTEXT_ONLY copies again**: gauge.nostrict.c needs a CONTEXT_ONLY
  func_0023d528 above func_0023d698 and a stub of func_0023e330 above
  func_0023ee80 (beql / beq in ee80, f250 and 1260).
- **The f32 argument's place**: gauge.nostrict.c calls through `#ifdef
  KH1_PS2` cast macros (D208, E160_F, AE0_F) as the old files did.
- **A return type decides a register**: plmodel.c's func_00124218 must
  return s32 (void moved a temp from v1 to v0).
- **A label cover_check needs** (as in session 46): hdd.c declares
  `extern char D_004919A8[8]`; with `[]` D_004919B0 after it became covered.
- **Static inline helpers**: mod.py skips them and leaves the old file with
  only them; hdd.nofill.c copies s6_25's four, and the old file was deleted
  by hand.
- checkfile.py stops at a section overlap when a moved function's file
  changes size; a copy with `--no-check-sections` (not committed) was used
  for the drafts, and `make` judged.

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions) and the m12 float build with
float_covered.txt, float_reach.txt, the loaded bytes and the program headers
the same as the base.  At the end `make report` 6979 at 100%, `make test`
passes and `s31_warndiff` reports 0 new warnings.

## Session 48: the Gummi ships, the maths helpers, the task slots and the VM resets, 0x001b9b30-0x001c08e8

Session 48 moved 185 functions in four commits.  No Mac: static checks
only.  After it the only function of 0x001b0000-0x001c08e8 left in src/hand
is the VU0 routine func_001b99b8 (src/hand/vu0.c); the rest of 0x001b0000
was already asm (src/asm/vu0_render*.s).  No assert names here; the groups
come from the strings ("GUMI", "Run Gumi Edit" / "gb.x", "Run WorldMap" /
"wm.x", "already max task!"), the save block's layout and what each
function does.  The data names are ordered with the code (D_003772D0 ...
D_0037A178), so this was most likely one or two original files; the split
below is by purpose and is a guess.

| module | files | range | functions |
|---|---|---|---|
| the Gummi save block (block 4 of the save image, 0xB040 bytes, "GUMI" v0x101: the ship order, ten ships, the held blocks, part values, the mission records, the world flags) and the Gummi Edit / World Map modes (the overlays gb.x / wm.x at 0x00F20000 and the pad block D_00621220 they read) | src/gummi/gumisave.c | 0x001b9b30-0x001bb438 | 69 |
| a downward memory stack (D_0037A148 ... D_0037A154, D_00623200) | src/util/memstack.c | 0x001bb438-0x001bb558 | 6 |
| the Gummi ships: the block table D_00377848, block turns and places as matrices, the garage's lists, a ship's bounds / summary / stats, the part slots | src/gummi/ship.c | 0x001bb558-0x001be758 | 59 |
| maths and memory helpers: a 16-deep stack of 128-bit words, the memory clear func_001be820, Euler / camera matrices, lerp, angle wraps, string copies, key interpolation, quaternions and slerp | src/util/vmath.c | 0x001be758-0x001bfac8 | 28 |
| a second task system (400 slots of 48 bytes at D_0037A16C, the run queue D_0037A170 the asm switcher func_001bfac8 walks); the starts are -fno-strict-aliasing | src/util/task.c, task.nostrict.c | 0x001bfc90-0x001c06f8 | 17 |
| the script manager's resets before the VM runtime (D_00389C90 as VmMgr, the event queue D_006297F8 with its pool D_00629808) | src/vm/vm_init.c | 0x001c06f8-0x001c08e8 | 6 |

Types: include/gummi/gummi.h (GumiShip, GumiPiece, GumiBlock,
GumiBlockTbl, GumiDir, GumiInfo, GumiStat, GumiCell, GumiSlot; one ship type
for the old CdEnt / BbEnt / S9f78 / Inv / ItOwner / Chr_* views, one block
type for ItemInfo / It28) and include/util/task.h (Task, TaskCtx; the old
Slot / Task_bfcd8 / Wk views).  The libvu0 calls in vmath.c use their names.
Each file's top comment says what its code reads and what is a guess; none
of the names is proved by a boot.  objdiff units 757 -> 732.

| chunk | commit | deleted |
|---|---|---|
| the task slots, the VM resets | 60a5d09 | auto text_001c0000 / _2 / _4 / _5 / _6, h14, nostrict h66 |
| vmath.c | 5926749 | h66, auto text_001b0000_9 / _13 |
| memstack.c, ship.c | 8985a4b | c08, s10_r2_8, s11_w17, s7_w34, auto text_001b0000_3 |
| gumisave.c | 35ab2b9 | s11_w4, s12_s12w17, h65, auto text_001b0000 / _1 / _2 / _4 / _5 / _6 / _7 / _8 / _10 / _11 / _12 |

**Data moved with its users** (same type and alignment): D_00629808 (the
event pool, vm_init.c), D_00623200 (memstack.c), D_00621318 (gumisave.c).

**Traps.**
- **A sized extern for cover_check, again**: the old auto file declared
  `extern volatile M2C_UNK D_00623ED4` (4 bytes); with only h41's unsized
  `u8 D_00623ED4[][96]` left, D_00625640 became covered ("after D_00623ED4,
  whose size no C declaration gives").  ship.c keeps `extern s32
  D_00623ED4` and reads the names through a `u8 (*)[96]` cast.
- **Three views of one array** (D_00621308, the sticks): func_001ba708 needs
  volatile stores through base + offsets in a fixed order, func_001ba778
  the `s32 [][2]` indexing (one address, then a move), func_001ba520 plain
  reads.  The file declares `[][2]`; func_001ba708 stores through a local
  `volatile s32 *` (a volatile cast of the array, or `&D[1][1]`, gives
  separate addresses).
- **A union member reloads**: GumiPiece.rot is a union (bit-fields for
  func_001bbdf0 / func_001bbf88); func_001bbbd0 reads it as `*(u16 *)&o->rot`
  (through `o->rot.h` it grew from 268 to 344 bytes).
- **A u8 return makes the compare unsigned**: func_001b9e88 calls
  func_001ba3f0 (u8) through an `s32 (*)(s32)` cast (sltu otherwise); the
  other callers kept their `s32` prototype or did not care.
- **Byte reads of word fields**: func_001bc900 reads the stats' x16 / x36 and
  D_00625640 as `*(u8 *)&` (the old files declared them u8).
- **A store pair needs two pointers**: func_001c0078 sets bit 0 of the
  flags in two branches through two different pointer variables (one
  variable cross-jumps the stores).
- **Indexing changes the code**: task.nostrict.c writes the saved
  arguments as `((u128 *)ctx)[20 + i]`, not `ctx->a[i]`.
- **No-argument calls**: m2c's func_001bbce0() / func_001bb260() /
  func_001bb658() took the caller's a0 and a1; the module writes them
  (func_001bbf38(m, pc), func_001bb3f8(w), func_001ba1e8(i)).

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions) and the m12 float build with
float_covered.txt, float_reach.txt, the loaded bytes, the program headers
and the symbols the same as the base.  At the end `make report` 6979 at
100%, `make test` passes, the seven new files compile with no warnings and
`s31_warndiff` reports 0 new warnings for h13 / h41 / nostrict h41.

## Session 49: the model renderer's helpers and the ppp effect classes, 0x001a0190-0x001aaf88

Session 49 moved 142 functions in six commits.  No Mac: static checks
only.  After it the only functions of 0x001a0000-0x001b0000 left in src/hand
are the 16 VU0 routines in src/hand/vu0.c (func_001a9080 ... func_001a9388,
func_001aae48, func_001aae90).  No assert names here either.  The renderer
groups come from its error strings ("op_spr_alloc error !", "can't open
file %s", "op_oef2_set error : ", "op_md0_onef() light no support !",
docs/elf-notes.md), which suggest original files named op_*.c; the ppp
groups come from the class table D_00370200 (docs/structs.md), whose
entries 206 pppRyjMegaPlaceModel ... 229 pppRyjMegaBirthModelFilter point at
the Con / Des / Frame / Draw functions here.  The split by class is a guess.

| module | files | range | functions |
|---|---|---|---|
| the model renderer's DMA chain: packet stacks, priority lists, the draw dispatch func_001aaf88 (defines D_0061FFA0) | src/gfx/opdma.c | 0x001a9e70-0x001aaf88 | 29 |
| GS image loads (sceGsSetDefLoadImage / sceGsExecLoadImage) | src/gfx/opimage.c | 0x001aa0a8-0x001aa420 | 4 |
| file loads ("can't open file %s") | src/gfx/opfile.c, opfile.nostrict.c | 0x001aaa70-0x001aadf0 | 6 |
| ppp's rotation matrices (X / Y / Z and the five compositions) | src/ppp/pppmtx.c | 0x001a50d0-0x001a5490 | 8 |
| the KeLns draw helpers, the KeBornRnd helper | src/ppp/kelns.c, kelns.nostrict.c, keborn.nostrict.c | 0x001a5520-0x001a67a0 | 16 |
| the KeTh node pools and lists; the strip draw func_001a7718 with its five helpers (alone because of file-scope #defines) | src/ppp/keth.c, keth.nostrict.c, kethdraw.nostrict.c | 0x001a67b8-0x001a8d78 | 17 |
| ppp's maths: an LCG, VU0 random, ray / sphere, atan2, powers, square roots, lengths, a u16 id free list | src/ppp/pppmath.c, pppmath.nostrict.c | 0x001a8d88-0x001a9418 | 11 |
| the KeMdlTfd and KeShpDtt helpers (mostly inline VU0) | src/ppp/kemdltfd.c, kemdltfd.nostrict.c, keshpdtt.nostrict.c | 0x001a9460-0x001a9c30 | 4 |
| pppRyjDrawMatrixWorldDtt(Fr), pppRyjLight, pppRyjDrawKekoto | src/ppp/ryjdtt.c, ryjlight*.c, ryjkekoto*.c | 0x001a1158-0x001a2090 | 13 |
| pppRyjMegaBirthModel | src/ppp/ryjmbmodel.c, ryjmbmodel.nostrict.c | 0x001a0190-0x001a10e0 | 8 |
| pppRyjMegaBirthFilter | src/ppp/ryjmbfilter.c, .nostrict.c, .nostrict_nofill.c | 0x001a2178-0x001a35f0 | 14 |
| pppRyjMegaBirthModelFilter | src/ppp/ryjmbmfilter.c, ryjmbmfilter.nostrict.c | 0x001a3650-0x001a5070 | 14 |

The libvu0 calls keep their addresses (func_00267328 sceVu0MulMatrix,
func_002672f8 sceVu0ApplyMatrix, func_00267560 sceVu0ScaleVector,
func_00267530 sceVu0SubVector, func_002675a8 sceVu0CopyVector,
func_002673b8 sceVu0Normalize, func_00267390 sceVu0InnerProduct) except
where an old file already used the SDK name.  Each file's top comment says
what its code reads and what is a guess; none of the names is proved by a
boot.

| chunk | commit | deleted |
|---|---|---|
| opdma.c, opimage.c, opfile*.c | 45858fd | auto text_001a0000_1 / _7 / _10, c2, s7_w5, s8_w4 (s8_w5 became opfile.nostrict.c) |
| pppmtx.c, kelns*.c, keborn.nostrict.c | 80254fb | none |
| keth*.c, kethdraw, pppmath*.c, kemdltfd*.c, keshpdtt | 78512f1 | auto text_001a0000_3 / _9, h13, nostrict h41, s7_w12b (b09 became kemdltfd.c, s7_w8 keshpdtt.nostrict.c) |
| ryjdtt.c, ryjlight*.c, ryjkekoto*.c | 963f4c3 | auto text_001a0000_4 / _5 / _8 (s8_w11 became ryjkekoto.nostrict.c) |
| ryjmbmodel*.c | 5db6f8a | auto text_001a0000_2, nostrict ctx, s7_w12 |
| ryjmbfilter*.c, ryjmbmfilter*.c | c231461 | auto text_001a0000 / _6, c3, h41, nostrict b09 / h65 / s6_12 (c07 became ryjmbmfilter.nostrict.c) |

**Data moved with its users**: D_0061FFA0 (opdma.c), the pointer table
D_00372750 (keth.nostrict.c).

**Traps.**
- **A float argument without a prototype becomes a double**: a call to
  func_00267560 (sceVu0ScaleVector) with no prototype in scope grew the
  caller; declare `void func_00267560(f32 *, f32 *, f32);`.
- **A view macro changes the alias set**: in a strict-aliasing file,
  pppRyjMegaBirthModelFilterCon needs the declared type `extern volatile
  void *D_00615E60` (a `#define D_00615E60 (*(PppSys **)&D_00615E60)` view
  reorders its loads), while func_001a47b0 in the same file needs that view.
  The file declares the base and wraps func_001a47b0 in #define / #undef.
- **Sized externs for cover_check, again**: opdma.c keeps `extern u128
  D_0061E8B0;` (without it D_0061EEA0 became covered).
- **Callees defined above their callers**: the nostrict filter files keep
  CONTEXT_ONLY copies of 0019f100 / 0019f148 / 0019f1f0 and func_001a26f0;
  `mod.py remove` and any script that reads a module's definitions must skip
  CONTEXT_ONLY lines, or they delete the real definitions elsewhere.
- **K&R definitions**: `mod.py remove` does not parse them
  (session 49 deleted one in h41 by hand).
- **File-scope #defines**: kethdraw.nostrict.c is alone because its draw
  function's #defines would rename fields in the other KeTh functions.

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `tools/shift/s37move/fcheck.sh` with
float_covered.txt, float_reach.txt, the loaded bytes and the program
headers the same as the base, and `s31_warndiff` 0 new warnings.

## Session 50: the ppp effect classes, 0x00183c70-0x001a0000

Session 50 moved 446 functions in thirteen commits, then fixed three missing
prototypes and deleted eight old files left with no function.  No Mac:
static checks only.  After it every function of 0x00183c70-0x001a0000 is in
a module except the VU0 routines func_0019baf8 and func_0019f100 in
src/hand/vu0.c.  All of it is ppp, the effect system: each module holds
classes of the class table D_00370200 (docs/structs.md; their Con / Des /
Frame / Draw slots point here) or the helpers only they call.  The names
come from the table's class names; the split by class is a guess, and
none of it is proved by a boot.  Each file's top comment says what it
does as read from the code.

| module | files | range | functions |
|---|---|---|---|
| the basic component classes: pppPoint, pppMove / Accele, pppAngle / AngMove / AngAccele, pppScale ..., pppColor ..., pppDrawHookDraw | src/ppp/pppcomp.c, pppcomp.nostrict.c | 0x00183c70-0x001847d0 | 25 |
| pppVertexAp / ApLc / ApAt (start effects at a mesh's vertices), pppVtMimeDraw | src/ppp/pppvertex.c, pppvertex.nostrict.c | 0x001847f8-0x001854f0 | 17 |
| the matrix classes: pppMatrixLoc, pppParMatrix, pppChrScl*, pppDrawMatrix / Front / NoRot, pppSMatrix, the rotation-order frames | src/ppp/pppmatrix.c, pppmatrix.nostrict.c | 0x00185538-0x00186158 | 20 |
| pppDrawMdlTs, pppDrawShape | src/ppp/pppdraw.c, pppdraw.nostrict.c | 0x00186178-0x001867c8 | 8 |
| pppPObjPoint, pppPointAp / RAp (start an effect at the owner's position) | src/ppp/ppppoint.c, ppppoint.nostrict.c | 0x001868d0-0x00186ab0 | 5 |
| pppRand* / pppSRand* (random values: frame and con functions, many made by one macro) | src/ppp/ppprand.c, ppprand.nostrict.c | 0x00186d00-0x0018a300 | 62 |
| pppEiWind | src/ppp/eiwind.c, eiwind.nostrict.c | 0x0018a438-0x0018a7d8 | 9 |
| the loop classes: pppMoveLoop / AngMoveLoop / SclMoveLoop, pppPointLoop / AngleLoop / ScaleLoop, pppDrawMatrixLoop, pppDrawMdlLoop(Z) | src/ppp/ppploop.c, ppploop.nostrict.c | 0x0018a7e0-0x0018bde0 | 40 |
| the KeTh classes: pppKeTh, KeThTp / Tp2, KeThHitBorn, KeThSft, the 24 KeThRes | src/ppp/kethcls.c, kethcls.nostrict.c | 0x0018bee0-0x0018d000 | 36 |
| pppKeBornRnd | src/ppp/kebornrnd.c, .nostrict.c, .nostrict_nofill.c | 0x0018d038-0x0018e728 | 23 |
| pppKeMdl | src/ppp/kemdl.c, kemdl.nostrict.c | 0x0018e888-0x0018fcb0 | 15 |
| pppKeShpTail (with the base frame and draw) | src/ppp/keshptail.c, keshptail.nostrict.c | 0x0018fcb8-0x00191ae0 | 17 |
| pppKeShpDtt | src/ppp/keshpdtt.c, keshpdttdraw.nostrict.c | 0x00191b10-0x00191e20 | 3 |
| the lens flare classes: pppKeLnsLp / Arnd / Clm / Crn / Fls, their T versions, KeLnsLpSft | src/ppp/kelnscls.c, kelnscls.nostrict.c | 0x00191e40-0x00193a00 | 38 |
| pppKeMove | src/ppp/kemove.c, kemove.nostrict.c | 0x00193a20-0x00194268 | 14 |
| pppKeMat | src/ppp/kemat.c, kemat.nostrict.c | 0x00194288-0x00194bb8 | 10 |
| pppDrawMdlTs2 / Ts3 and the other model draws | src/ppp/drawmdl.c, drawmdl.nostrict.c | 0x00194cb8-0x00195cc0 | 12 |
| pppKeMdlTfd3, pppKeMdlTfdUv3 | src/ppp/kemdltfd3.c, kemdltfd3.nostrict.c | 0x00195f50-0x00196450 | 4 |
| pppKeShpTailX | src/ppp/keshptailx.c, keshptailx.nostrict.c | 0x00196490-0x00198578 | 13 |
| pppRyjDrawMatrixWorld | src/ppp/ryjmtxworld.c, ryjmtxworld.nostrict.c | 0x001985a8-0x001995d0 | 21 |
| pppRyjShipoly | src/ppp/ryjshipoly.c, ryjshipoly.nostrict.c | 0x001996d0-0x0019bab0 | 18 |
| pppRyjMegaBirth | src/ppp/ryjmb.c, .nostrict.c, .nostrict_nofill.c | 0x0019bb40-0x0019d8a8 | 11 |
| pppRyjMegaBirthPrize | src/ppp/ryjmbprize.c, ryjmbprize.nostrict.c | 0x0019d920-0x0019df80 | 5 |
| pppRyjMegaPlace | src/ppp/ryjmplace.c, ryjmplace.nostrict.c | 0x0019dfc8-0x0019f0d0 | 17 |
| MegaBirthModel's helpers 0019f148 / 0019f1a8 / 0019f1f0 (the real 0019f1f0 replaced its CONTEXT_ONLY copy) | src/ppp/ryjmbmodel.c, ryjmbmodel.nostrict.c | 0x0019f148-0x0019f1f0 | 3 |

| chunk | commit | deleted |
|---|---|---|
| ryjmb*, ryjmbprize*, ryjmplace* | e134fc8 | auto text_00190000_1 / _3 / _14, nostrict s7_w9 / s12_s12w8, nostrict_nofill b08 |
| ryjshipoly*, the s50move tools | 973c54a | auto text_00190000_10, nostrict s11_w62 |
| ryjmtxworld* | bf3dd9d | auto text_00190000_8 |
| keshptailx* | ba266d0 | none |
| drawmdl*, kemdltfd3* | c772a22 | none |
| kemat*, kemove* | deda55c | auto text_00190000_7 / _11 |
| kelnscls* | a554f83 | auto text_00190000_2 / _4 / _6, nostrict s18_s18m2 |
| keshptail*, keshpdtt* (0x0019 done) | 54741e0 | auto text_00190000 / _5 / _9 / _12 / _13, nostrict b08 / h64 |
| KeShpTail's frame and draw, kemdl* | 65ec4ea | auto text_00180000_19 |
| kebornrnd*, kethcls* | bca1eae | auto text_00180000_9 / _17, nostrict c05 / s7_w2 |
| ppploop*, eiwind* | ab5a2cb | none |
| ppprand* | 0eae1ab | hand/nostrict/ppp_rand.c |
| pppcomp*, pppvertex*, pppmatrix*, pppdraw*, ppppoint* | e027599 | auto text_00180000_7 / _8 / _11 / _14 / _15 / _20, hand/ppp.c, nostrict text_00180000 / s6_11 |
| three missing prototypes | 58a9ab2 | none |
| files left with no function | e17f355 | auto text_00180000_13 / _16 / _18, h40 and nostrict h40, nostrict h63, s7_w30, nostrict_nofill s6_11 |

**Data moved with its users**: D_0061E2D0 (from h12 into ryjmb.c).

**New tools** (tools/shift/s50move/):
- `group.py src/ppp/NAME LO HI [--skip f,...]` drafts one file per flag mode
  for every src/auto / src/hand function in the range (vu0.c excepted),
  appending to files that exist, prunes them and runs checkfile on each; a
  FAIL is reported as "same as its old file (rodata)" when the differing
  words match the old file's (jump tables and rodata, placed by `make`), else
  "NEW DIFF".
- `assemble.py OUT.c func...` (or `--onto MODULE.c`) writes the module:
  each function gets what it saw above it in its old file and uses, emitted
  once; clashing typedefs, tags and static inline helpers are renamed
  NAME_<last 5 address digits>; a clashing extern or prototype becomes a
  per-function view (`#define` ... `#undef`); includes are hoisted to the
  top and what the headers declare counts as declared; macro-generated
  definitions (`MACRO(func, ...)` lines) are followed; it prints CONFLICT
  lines for prototypes it left out.
- `prune.py FILE` drops file-scope declarations nothing uses.
- `mod.py remove` (s36move) now also deletes the `MACRO(func, ...)` line of
  a macro-generated definition.

**Traps.**
- **View by value, not by memory**: in a strict-aliasing (default-flag)
  file, `#define D_X (*(T *)&D_X)` loses the scalar's MEM_SCALAR_P and
  reorders its loads (the WoodFrame functions).  View a scalar by value,
  `((T) D_X)`, an array by address, `((T *) D_X)`; keep the memory view only
  where the code takes the address (`&D_X` of a value cast does not compile).
  Where an extern clashes, make the array declaration the base: an array
  view of a scalar base changed D_00615FC0's address folding.
- **Implicit declarations**: three calls had no prototype in scope
  (func_00182588 in pppvertex / ppppoint, func_00267518 in ryjmbmodel, the
  last one from session 49) and still matched.  Check new modules with
  `-Wimplicit-function-declaration` (the ee-gcc command of checkfile.py plus
  that flag): a float argument or a non-int return would not match.
- **A function view for a disagreeing prototype**: `#define F ((RET
  (*)(ARGS)) F)` keeps the call a `jal` and lets one function call with
  three arguments what another declares with two.
- **Old files with only static inline helpers left**: `mod.py remove` does
  not call them EMPTY; `git rm` them (eight this session).
- **Data definitions** still move by hand (D_0061E2D0).
- **The CONTEXT_ONLY copy was not the real code**: ryjmbmodel.nostrict.c's
  copy of func_0019f1f0 did not match once it became the definition; the
  body from s12_s12w8 does.

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `tools/shift/s37move/fcheck.sh` with
float_covered.txt, float_reach.txt, the loaded bytes and the program
headers the same as the base, and `s31_warndiff` 0 new warnings.

## Session 51: the ppp manager core, the camera, the party AI, 0x00170170-0x00183c70

Session 51 moved 396 functions in six commits.  No Mac: static checks only.
After it every function of 0x00170170-0x00183c70 is in a module except the
VU0 routine func_00176850 in src/hand/vu0.c.  The names are read from the
code (what each function writes and calls) and none of it is proved by a
boot; each file's top comment says what it does.

| module | files | range | functions |
|---|---|---|---|
| the ppp manager core: the resource walkers and program relocation, the sprite and texture uploads to GS memory, func_00182588 (make an instance), the depth sort func_00181608 ... | src/ppp/pppsys.c, pppsys.nostrict.c | 0x00180000-0x00183c70 | 73 |
| the ppp object controls: the third ppp task func_0017f8e0, the work buffer (D_00575E40, 0x20000 bytes), the effect heap and draw-list wrappers | src/ppp/pppobj.c, pppobj.nostrict.c | 0x0017f8e0-0x00180000 | 19 |
| the ppp interface to the game: func_00175918 registers the three per-frame tasks, the manager's enable flags (D_0035C6F0 ...) | src/ppp/pppapi.c, pppapi.nostrict.c | 0x00175918-0x001768e8 | 63 |
| the object scripts' second command table: the 21 commands of D_00362340, which the descriptor D_002E2F20 lists after D_002E2810 | src/obj/objcmd2.c, objcmd2.nostrict.c | 0x00176898-0x00176ba8 | 21 |
| pad vibration: two players (D_005757B0[2]) step a vibration pattern into the pad's actuator bytes D_002C5AD0[i][2..3] | src/pad/padvib.c, padvib.nostrict.c | 0x00176ba8-0x00176f08 | 5 |
| the field camera's core and its modes, the mode table D_00362458 ({frame, leave} x 12) | src/camera/fieldcam.c, fieldcam.nostrict.c | 0x00176f08-0x0017b250 | 46 |
| the camera's path mode (mode 9): a cubic Bezier along the path D_00362438 the player's zone picked | src/camera/campath.c, campath.nostrict.c | 0x0017b250-0x0017d628 | 25 |
| the camera's control: a map's camera data (func_0017d9c8 relocates it), modes 10 and 7, the calls the game makes | src/camera/camctl.c, camctl.nostrict.c | 0x0017d628-0x0017f8e0 | 37 |
| the party members' AI: the setup functions of the eight member kinds and their action tables, the setup table D_0035BC80 | src/ai/partyai.c, .nostrict.c, .nostrict_nosib.c | 0x00170170-0x00174fc0 | 102 |
| two texture spots slid over triangle meshes (segment-triangle and segment-plane hits; D_00575790, D_005757A0) | src/gfx/texspot.c, texspot.nostrict.c | 0x00174fc0-0x00175918 | 5 |

| chunk | commit | deleted |
|---|---|---|
| pppsys* | 2d99998 | auto text_00180000 / _1 ... _6 / _12, hand h12 / h39 / b07 / text_00170000_s6_10, nostrict b07 / c2 / h39 / h62 / s7_w11 / s7_w13 |
| pppapi* | 47205c2 | hand text_s7_w24 |
| pppobj* | 5b3ff51 | none |
| objcmd2*, padvib* | 2cf022b | hand text_00170000_s9_w7 |
| fieldcam*, campath*, camctl* | 9113c86 | auto text_00170000_1 / _3 / _5 / _6 / _9 / _11 / _12, hand c04 / b06 / h11 / h61 / s8_w16 / text_00180000_h62, nostrict b06 / s6_10 / s7_w2 / s9_r2_2 |
| partyai*, texspot* | ecdc7a5 | auto text_00170000 / _2 / _4 / _7 / _8 / _10, hand text_00170000 / h38 / s9_w9, nostrict h38 / h61 / s7_w6 |

**Data moved with its users**: D_00575A10, D_00615EF0, D_00615F90,
D_00615FA0, D_00615FB0, D_00615E80 / 90 / A0 and the class-name table
D_003701C0 (pppsys); D_00575E40, D_00616238 (pppobj); D_00362458 and 18 bss
definitions (the camera); D_0035BC80 (from h60 into partyai.nostrict.c);
D_00575790, D_005757A0 (texspot).

**Tool changes** (tools/shift/s50move/assemble.py, prune.py): old-style
declarations plus views for module functions whose prototype disagrees with
the definition; definitions of data become externs (ALIGNED kept); narrow
int arguments count as risky; `__asm__` aliases of variables and prototypes
(`#define D_X D_X_<addr>` + `extern T D_X_<addr> __asm__("D_X")`) are kept,
by classify and by prune; a typedef under its own rename macro is emitted
again; macros get their own scope key; a function with its own view macro
gets no generated view; a 64-bit view of a 32-bit base is a memory view; a
typedef's struct tag counts as a name and duplicates are found by text;
prototypes whose pointer types differ are viewed; m2c's `extern M2C_UNK
func_X;` becomes a prototype; `(*D_X[n])(...)` declarations parse; prune
reads `} __attribute__((...)) NAME;`.

**Traps.**
- **CONTEXT_ONLY stubs for callees defined above**: where the old file
  defined a callee above the function, the module needs a `CONTEXT_ONLY s32
  f(void) { return 0; }` copy of it too, or a likely branch's delay slot
  changes (beql vs beqz words): func_0017adf8 / func_001773b0 in camctl.c,
  func_00176f08 / 00177358 / 0017b200 in campath.c, func_001770b8 in
  campath.nostrict.c.
- **An inline definition gets inlined**: when the callee's definition moves
  into the same file, gcc inlines it.  Call it through an alias, `s32
  f_x(...) __asm__("f");` with `#define f f_x` around the caller
  (func_00174ad8 calls func_00171ae8 that way).
- **A 64-bit view of a 32-bit base** must be a memory view `(*(u64 *)&D_X)`;
  a value cast changes the load.
- **Rename macros**: an old file's `#define D_X D_X_<addr>` with an
  `__asm__` extern is an alias; keep both lines together.
- **Struct tags completed differently**: several old files each complete
  `struct Actor` (D_002E26A0.h declares `struct Actor *D_002E26A0[3]`) with
  their own members.  Renaming the tag breaks the header's array type, not
  renaming it lets the first completion win; 0x00168500-0x00170170
  (partyctl) was left for that reason (draft: 4 default-flag functions fine,
  39 nostrict with 3 NEW DIFFs: 0016a3f8, 0016e1f0, 0016f548).  Give those
  functions their own view of D_002E26A0 (`((struct Actor_x **) D_002E26A0)`)
  and an untagged struct.
- **V4 in two headers**: include/data/types/nostrict_text_00170000_s6_10.h
  and _b06.h both `typedef FVec4 V4;` under the guard KH1_V4_IS_FVEC4.
- **mod.py remove drops an include a remaining typedef needs**:
  text_00160000_c04.c lost data/types/fvec.h; put it back by hand.

**Nothing was reverted, and nothing new floats.**  After each commit: `make`
byte-identical (6979 functions), `tools/shift/s37move/fcheck.sh` with
float_covered.txt, float_reach.txt, the loaded bytes and the program
headers the same as the base, and `s31_warndiff` 0 new warnings; new files
checked with `-Wimplicit-function-declaration`.

## Session 53: 0x0013 and 0x0014, the object and party code under the classes, 0x00130000-0x00150000

Session 53 moved 632 functions in six commits.  No Mac: static checks
only.  After it every function of 0x00130000-0x00150000 is in a module
except the nine of "Left" below.  The names are read from the code and
none is proved by a boot; each file's top comment says what it does.

| module | files | range | functions |
|---|---|---|---|
| an object's motion: the motion table lookup (func_00130070), the motion change every class calls (func_00130340, func_00130398(o, motion, blend), func_00130578), the per-frame bone update (func_00130660, func_00130f18) | src/obj/objmotion.c, .nostrict.c | 0x00130000-0x00131438 | 22 |
| positions on an object's bones (func_001315c0(o, bone, out, t), func_001318e8) | src/obj/objbone.c | 0x00131438-0x00131de0 | 17 |
| the room's object lists D_00525298, D_005252C8 / D_005252F8 / D_00525328 (func_00132c70 builds them for the world / room / area, func_00131e40 loads the objects one by one, func_001320a8 finds a record); D_00525290 defined here | src/obj/roomobj.c, .nostrict.c | 0x00131de0-0x00132f00 | 21 |
| the party members' seven loaded files at D_00720000 (records D_00525368, sizes D_00304318); D_00525430 defined here | src/game/memberfile.c, .nostrict.c | 0x00132f00-0x00133738 | 23 |
| object commands: 32 nodes D_00525A40, 32 triples D_00526640, the task func_00133a88, a node chain (func_001342c8) | src/obj/objcmd.c, .nostrict.c, .nostrict_nofill.c | 0x00133738-0x001347f0 | 13 |
| damage: kinds and thresholds of *D_00308CDC, the damage of an attack (func_001349d0, func_00134ba8), the hit records D_005267C0 / D_005277C0 and the hit test func_001350d8; D_0052A110 defined here | src/obj/damage.c, .nostrict.c | 0x001347f0-0x00135a68 | 31 |
| whether an object is drawn: its box, the on-screen test func_00135bb0, the distance fade func_00135ca0, the colour fade | src/obj/objvis.c, .nostrict.c | 0x00135a68-0x00135ed0 | 6 |
| object draw jobs on D_0052A100 (func_001371f0 queues one, func_00136bc0 runs it) and the per-kind draw callbacks; D_00529800 defined here | src/obj/objdraw.c, .nostrict.c | 0x00135ed0-0x00137308 | 11 |
| small object helpers every class uses (func_001375f0, func_00137618, func_00137688, func_001376e8 ...), the id lists D_0052ABF0 (defined here) / D_0052ACF0 | src/obj/objutil.c, .nostrict.c | 0x00137308-0x00137718 | 14 |
| the objects' update tasks (func_00138400 picks one by kind; func_00137ea8, func_00138130, func_00138258); D_0052A158 defined here | src/obj/objtask.c, .nostrict.c | 0x00137718-0x00138a78 | 28 |
| reactions to commands and hits (*D_00308CDC), the message loop func_00139da8, the nearest target in range (func_0013a440) | src/obj/objreact.c, .nostrict.c | 0x00138a78-0x0013a910 | 27 |
| likely the summons (a guess): func_0013a910 asks whether one is allowed, D_0052AE54 loads its two files named from D_00304B00, the object D_0052AE38 of class 40 (func_0013bf20), the party swap and its end; D_00304B40, D_00304B44, D_00304B68, D_0052AD00-D_0052AD58, D_0052AD78, D_0052AE3C, D_0052AE40 defined here | src/game/summon.c, .nofill.c, .nostrict.c | 0x0013a910-0x0013bf68 | 26 |
| the members' records in the save data D_00304BE8 (func_0013c968 has-ability, func_0013cb98 builds the records from D_00351530) | src/game/memberdata.c, .nofill.c, .nostrict.c | 0x0013bf68-0x0013cec8 | 32 |
| party helpers: a member's slot (func_0013daa8), the leader, the per-class callbacks D_00350DA4, whether the party is together (func_0013dd40); D_00304BF0 (a pointer table) and D_0052AE68 defined here | src/game/partyutil.c, .nostrict.c | 0x0013daa8-0x0013e000 | 10 |
| the player-controlled object's move (func_0013e1f8, func_0013f198) and its motion events (func_0013eab0, func_0013ee40) | src/obj/plctl.c, .nostrict.c | 0x0013e000-0x0013f358 | 14 |
| object classes 0xD and 0xE (func_0013fc80) | src/obj/class0d.c, .nostrict.c | 0x0013f358-0x0013fd10 | 14 |
| the first handlers of classes 9 and 0xA and the helpers class0a calls (func_0013fe28, func_0013ff00 ...) | src/obj/class09.c, .nostrict.c | 0x0013fd10-0x00140000 | 9 |
| object classes 9, 0xA and 0xB (func_00141138 registers them) | src/obj/class0a.c, .nostrict.c | 0x00140000-0x00141200 | 17 |
| the members' HP / MP changes (func_00141468, func_00141540) and stats rebuilt from the save data (func_00141b10) | src/game/partystat.c, .nostrict.c | 0x00141200-0x00142030 | 21 |
| a four-entry cache keyed by world / room / area (D_0052CB20, D_0052EB40) | src/game/roomcache.c, .nostrict.c | 0x00142030-0x00142388 | 6 |
| an object's ground movement: the ground ray, steering, the move with walls (func_00143180 stays in c02, a CONTEXT_ONLY copy is here), the per-state velocity through D_00350D88 | src/obj/objmove.c, .nostrict.c | 0x00142388-0x00144350 | 22 |
| object class 0x11 (func_00144e38) | src/obj/class11.c, .nostrict.c | 0x00144350-0x00144e88 | 13 |
| prizes (a guess: the HP / MP balls and munny drops): drop tables, the pool D_0052EB60 with D_0035C710, the free list D_0052EB50 | src/obj/prize.c, .nofill.c, .nostrict.c | 0x00144e88-0x001467e8 | 23 |
| load and spawn requests: 128 load records D_00531B70 (func_00146a68), the effect entries spawned by id (func_00146bd0, func_001473a8); D_00531F80 defined here | src/game/objreq.c, .nostrict.c | 0x001467e8-0x00147730 | 23 |
| lookups into the data tables D_00547BA0 ... (func_00147840 an item's record, func_00147860 its bonuses) | src/game/datatbl.c, .nofill.c, .nostrict.c | 0x00147730-0x00147a68 | 12 |
| effect objects: 256 records D_00547C00 handed out from D_0054B800, their tasks, func_00148768 starts one; D_00547BC0, D_0054B818, D_0054C160 defined here | src/obj/effobj.c, .nostrict.c | 0x00147a68-0x00148fb0 | 39 |
| the members' items and equipment, the three weapon models D_0054C1B0 (func_00149c80); D_00350D10, D_00350D14 defined here | src/game/memberitem.c, .nostrict.c | 0x00148fb0-0x0014a0f0 | 25 |
| attack hits: 64 records D_0054C440 (func_0014a4a8 fills one, func_0014bdc0 updates them), the mask D_0054F440, the hit timers | src/obj/atkhit.c, .nogcse.c, .nostrict.c | 0x0014a0f0-0x0014c400 | 33 |
| object class 0x15 (func_0014cb38) | src/obj/class15.c, .nostrict.c | 0x0014c400-0x0014cb90 | 11 |
| jump arcs (func_0014cc88, func_0014cce0; gravity 0.48469386) | src/obj/objjump.c | 0x0014cb90-0x0014cee8 | 6 |
| object classes 1, 2, 3 and 5 (func_0014d890) | src/obj/class01.c | 0x0014cee8-0x0014d988 | 15 |
| object class 8 (func_0014e4b8) | src/obj/class08.c | 0x0014d988-0x0014e510 | 13 |
| the room's area boxes D_00350D78 (func_0014f1b8 installs a set, func_0014e5b8 / func_0014ee88 which boxes hold a point / touch a capsule, func_0014f028 the leader's box) | src/obj/areabox.c | 0x0014e510-0x0014f370 | 15 |
| the actor core: func_0014f830 registers a class in D_00350D88, func_0014f5c8 / func_0014f600 / func_0014f658 call a class's handlers, the default handlers | src/obj/actcore.c | 0x0014f370-0x0014f9b0 | 15 |
| an entity's look-at (func_0014f9b0 / func_0014fa38 start and stop it, func_0014fe48 turns) | src/obj/lookat.c, .nostrict.c | 0x0014f9b0-0x00150000 | 5 |

| chunk | commit |
|---|---|
| 0x00140000-0x00144e88 | d111a04 |
| 0x00144e88-0x0014c400 | b8c783b |
| 0x0014c400-0x00150000 | d1e1a05 |
| 0x00130000-0x00135ed0 | fbe72b7 |
| 0x00135ed0-0x0013bf68 | 3193236 |
| 0x0013bf68-0x00140000 | a60cc4f |

**Left** (9 functions, for the c02 move): hand/nostrict/text_00130000_c02.c
keeps func_00135ed0, func_00136d38, func_0013cec8, func_0013cfe8,
func_00143180 and func_001550a0 (taking func_00143180 out swapped
registers in func_0013cfe8 again, as func_001550a0 did in session 52);
hand/text_00130000_h7.c keeps func_0013cf28 and func_0013cfc0 and
auto/text_00130000.c func_0013cf78, the stack pops of func_0013cfe8's
queue (W7Stack), left to move with it.  objmove.nostrict.c holds a
CONTEXT_ONLY copy of func_00143180 so the functions below it compile as
before.

**Data moved with its users** (32 definitions): the files that held them
were deleted when their last function moved, and `make` stayed
byte-identical each time; the names check of out/gen/data.tsv found them
(1 after the second chunk, 7 after the third, 1, 4 and 21 after the 0x0013
chunks).  Each is now defined at its user's extern line with the old
ALIGNED and a "moved from" comment; pointer tables keep their
initialisers (D_00350D10, D_00350D14, D_00304B40, D_00304B44, D_00304B68,
D_00304BF0).

**Traps.**
- **The same register swap, another function**: func_00136bc0 (h32) lost
  3 words when the functions above it moved; a CONTEXT_ONLY copy of
  func_00135d38 alone put it back (found by trying each moved function as
  the only copy), and the copy went away when func_00136bc0 itself moved.
  func_001401d8 matches only with func_0013fe28 above it (an old note):
  class0a.nostrict.c has a CONTEXT_ONLY copy (the real one is in
  class09.nostrict.c).
- **Function-pointer externs**: assemble.py reads `extern M2C_UNK
  (*D_X)(s32);` as a clash with the M2C_UNK typedef and leaves the name
  undeclared (D_0054C210, D_00525364): give the function an alias
  `extern M2C_UNK (*D_X_<fn>)(s32) __asm__("D_X");`.
- **Prototype views of a function defined below**: `W34A9c *
  func_0014a398();` then `#define func_0014a398 ((T) func_0014a398)`
  conflicts with the definition later in the same file: an asm alias of
  the function (`T *func_0014a398_4a0f0(T *) __asm__("func_0014a398");`)
  works.  A call that an old file made with an implicit declaration and
  now meets a `void` prototype (func_001473a8 in func_00146ff0) needs a
  function view with the result type.
- **A cast view drops a sized extern**: `#define D_0052EB50 (*(Snd (*))
  &D_0052EB50)` over `extern u8 D_0052EB50[]` matched but cover_check no
  longer saw `extern Snd D_0052EB50;`, so D_0052EB60 (inside it) left
  float_covered.txt.  Declare the old sized type plainly and alias the
  functions that used the array.
- **mod.py drops includes a remaining typedef needs**: FVec4 came from
  data/pieces/D_002C58A0.h in h33 and b02; `#include
  "data/types/fvec.h"` (or the piece) above the `typedef FVec4 V4;` fixes
  the parse errors.
- struct Actor again (func_001417a0, func_0014a4a8, func_0013a910,
  func_0013bb20, func_00143180's D_003044D8 owner): an alias of
  D_002E26A0 with the function's own type, or a pointer cast at the use.
- Implicit `fabsf` calls came from the old files and matched there too.

**Nothing was reverted, and nothing new floats.**  After each commit:
`make` byte-identical (6979 functions), `tools/shift/s37move/fcheck.sh`
with float_covered.txt, float_reach.txt, the loaded bytes and the program
headers the same as the base, the names of out/gen/data.tsv the same as at
the start of the session, `s31_warndiff` 0 new warnings, and the new files
checked with `-Wimplicit-function-declaration`.

## Session 52: the party control, the model renderer and motion, the object classes, 0x00150000-0x00170170

Session 52 moved 418 functions in three commits.  No Mac: static checks
only.  After it every function of 0x00150000-0x00170170 is in a module
except the VU0 routines in src/hand/vu0.c, the unmatched func_001636d0
(asm) and func_001550a0 (see Traps).  The names are read from the code and
none is proved by a boot; each file's top comment says what it does.

| module | files | range | functions |
|---|---|---|---|
| the party members' control: the action handlers the AI tables name, the follow positions, the target search func_0016ea58, the party's callback list (D_00575528 nodes) and its reset | src/ai/partyctl.c, partyctl.nostrict.c | 0x00168500-0x00170170 | 43 |
| the model renderer's DMA side: the channel handlers, the double-buffered packet lists D_00551D90 / D_00559DC0 (defined here), the GS uploads | src/model/mdlgs.c, mdlgs.nostrict.c | 0x0015ea98-0x00160370 | 22 |
| the model renderer's draw side: the draw task func_00160370, the per-model draw (bucket tables D_0055BE00 / D_0055BEC0 / D_0055C280 defined here), func_00161a08 relocates a "MOBJ" model or a "MENV" map environment, the setup func_00162500 | src/model/mdldraw.c, .nostrict.c, .nostrict_nofill.c | 0x00160370-0x001625c8 | 23 |
| matrix helpers of the model code (the VU0 routines between them stay in vu0.c) | src/model/mtxutil.c, mtxutil.nostrict.c | 0x001625c8-0x00163150 | 8 |
| the skeleton's bone matrices | src/model/skel.nostrict.c | 0x00163150-0x00164768 | 2 |
| motion curves, events and poses (func_00164768 evaluates a key curve, func_00166570 the bone chain) | src/model/motion.nostrict.c | 0x00164768-0x001675c0 | 9 |
| texture animation ("TEXA" chunks: func_001681b8 finds a chunk by tag, func_001680d8 relocates one) | src/model/texanim.c, texanim.nostrict.c | 0x001675c0-0x00168500 | 21 |
| object classes 0x1A, 0x1B, 0x1C, 0x04, 0x1D, 0x1E, 0x00, 0x0F, 0x12, 0x0C, 0x18, 0x19: each file pair holds the handlers its setup registers with func_0014f830(class, ...) in the class table D_00350D88 (32-byte records: a parameter and seven handlers), and their helpers; D_00351970 (class 0x1C's action table) is defined in class1c.nostrict.c | src/obj/class1a ... class19 (.c, .nostrict.c) | 0x00150000-0x00153d88, 0x00155630-0x00155730, 0x00157f70-0x001586a8, 0x00159148-0x00159978, 0x0015a258-0x0015a470, 0x0015ca50-0x0015ea98 | 150 |
| hit reactions (the reaction handlers by state, func_00154e38's tables, the tuning block *D_00308CDC) | src/obj/hitreact.c, hitreact.nostrict.c | 0x00153d88-0x00155630 | 19 |
| object data slots: 64 headers D_00550400 for the 0x40000-byte areas at D_00FE0000 that object files load into; the pool D_0054F980 is defined here | src/obj/objslot.c, .nofill.c, .nostrict.c | 0x00155730-0x00156260 | 22 |
| the point list D_00551600 (nearest point to a position) | src/obj/objpoint.c, objpoint.nostrict.c | 0x00156260-0x00156c28 | 11 |
| party heal objects (func_00156c68 heals the members below their maximum HP) | src/obj/objheal.c, .nostrict.c, .nostrict_nogcse.c | 0x00156c28-0x00157090 | 4 |
| object sounds and voices: the four play slots D_00551670 through snd_rpc, the party members' voice banks (".vsb") in D_00551608 | src/sound/objse.c, objse.nostrict.c | 0x00157090-0x00157f70 | 22 |
| likely the Trinity marks (five kinds in D_00351A30, both partners near, "xl_limit.dat", the code loaded at D_00F20000; the name is a guess) | src/game/trinity.c, trinity.nostrict.c | 0x001586a8-0x00159148 | 15 |
| the leader's trail: func_00159ea8 follows an object and records 32 positions (D_00551700, D_00551740; D_00551734 defined here) | src/obj/trail.c, trail.nostrict.c | 0x00159978-0x0015a258 | 6 |
| objects the player touches (contact handlers with the tables D_00351AA0 / D_00351AB0) | src/obj/objtouch.c, objtouch.nostrict.c | 0x0015a470-0x0015ae48 | 15 |
| level-up: func_0015b268 raises a member's level, func_0015ae48 applies the bonus, the notice buffers D_00551970 (defined here) | src/game/levelup.c, levelup.nostrict.c | 0x0015ae48-0x0015b4a8 | 5 |
| cylinder hits between objects (overlap and push-out by shape pair, an object's cylinder from its bone) | src/obj/cylhit.c, cylhit.nostrict.c | 0x0015b4a8-0x0015ca50 | 21 |

| chunk | commit |
|---|---|
| partyctl* | eba014a |
| src/model/* (and assemble.py's array aliases) | 6a7ca8c |
| 0x00150000-0x0015ea98 (and the rest of the tool changes) | f2ef927 |

**Data moved with its users**: D_0055BE00, D_0055BEC0, D_0055C280
(mdldraw.nostrict.c), D_00559DC0 (mdlgs.nostrict.c), D_0054F980
(objslot.c), D_005516D0 and D_005516E0 (class1d.nostrict.c), D_00551734
(trail.nostrict.c), D_00551970 (levelup.nostrict.c), the pointer table
D_00351970 (class1c.nostrict.c).

**Tool changes** (tools/shift/s50move/assemble.py): every view of a data
name is an `__asm__` alias with the function's own type (`extern T
D_X_<fn>[] __asm__("D_X"); #define D_X D_X_<fn>`), not a cast; multi-name
prototypes (`void f(), g();`) are split per name, for the scope and for
views; a function only taken by address (`&f`) gets no function view (a
cast view is not an lvalue).  tools/checkfile.py skips a local helper that
has no original address instead of stopping.

**Traps.**
- **Cast views change code**: an array view `((T *) D_X)` changed the
  address folding of D_00573F10 (func_00166570, 989 words), D_00575528,
  D_00575328 and D_002E26A0; a value-cast view of a pointer that the
  function assigns (`D_0054F950 = ...` in func_00151808) changed its size;
  a value-cast view of a volatile scalar dropped the volatile
  (func_0015ee10).  An `__asm__` alias gives the old file's own
  declaration and matched every time; assemble.py now emits only aliases.
- **struct Actor again**: functions that read members through
  D_002E26A0 (or D_002E31B0.f0) where their old file completed `struct
  Actor` need an alias with their own type (`extern Act
  *D_002E26A0_58780[3] __asm__("D_002E26A0");`) or a pointer cast at the
  use (func_00158780, func_00158960, func_001557d0, func_0016f548).
- **Data definitions are lost silently**: assemble.py turns an old file's
  definitions into externs and `mod.py remove` deletes the old file, but
  `make` stays byte-identical (the blob fills the gap).  Only the float
  check sees it (sizes in float_covered.txt).  After each chunk compare the
  names of out/gen/data.tsv with the base: session 52 had to put back 11
  (listed above), one of them an initialised pointer table.
- **Rerun tools/shift/data_owners.py after deleting an owner file**, before
  fcheck.sh: its stale owner rows otherwise make cover_check flag the next
  piece.
- **Removing a function can change another one in the old file**:
  taking func_001550a0 out of hand/nostrict/text_00130000_c02.c swapped s6
  and s7 (the two jump-table bases) in func_0013cfe8 further down, even
  with an empty CONTEXT_ONLY stub or extra labels; only a full CONTEXT_ONLY
  copy put it back.  func_001550a0 stays in c02 until func_0013cfe8 moves
  (the 0x0013 session).  Likewise func_0016e1f0 in partyctl.nostrict.c
  matched or not depending on unrelated declarations above it (an extra
  `extern int x;` fixed it before the D_00575328 alias did): gcc 2.96's
  output here depends on what was allocated before the function, so `make`
  after each change is the only judge.
- **group.py's summary hides compile errors**: a draft that does not
  compile prints its errors but no FAIL line; check each new file
  compiled (a MATCH / FAIL line per function) before `mod.py remove`.
- Implicit `fabsf` calls came from the old files (s7_w34, h59, h36, h36's
  cylinder code) and matched there too: left as they were.
  func_0015bad0 / func_0015bb88 got prototypes in class0f.nostrict.c.

**Nothing was reverted, and nothing new floats.**  After each commit:
`make` byte-identical (6979 functions), `tools/shift/s37move/fcheck.sh`
with float_covered.txt, float_reach.txt, the loaded bytes and the program
headers the same as the base, the names of out/gen/data.tsv the same as at
the start of the session, and `s31_warndiff` 0 new warnings; new files
checked with `-Wimplicit-function-declaration`.

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

## Verification (sessions 30 to 52, after each step)

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

- **The game segment is in modules from 0x00130000 to 0x0024f2e0** (session
  53), except the VU0 routines in src/hand/vu0.c, two probes in
  src/anon/session1_probes.c (func_0018ad70, func_001882f8; func_00137418
  is a probe too), the unmatched func_001636d0 and the nine functions of
  "Session 53", Left (c02 and the stack pops).  The functions still in
  src/auto and src/hand lie in 0x001001f8-0x00130000
  (out/gen/placements.tsv): 471 in 0x0012, 391 in 0x0011, 303 in 0x0010,
  plus those nine and the VU0 routines.  Next is 0x0012 (from the top
  down, as sessions 50 to 53 went), and the c02 move: take
  func_0013cfe8 with func_0013cec8 and its stack pops (func_0013cf28,
  func_0013cf78, func_0013cfc0) into one module and check whether
  func_00135ed0, func_00136d38, func_00143180 and func_001550a0 can then
  join objdraw / objmove / their neighbours (CONTEXT_ONLY copies where
  the old order matters).  `python3 -I tools/shift/s50move/group.py
  src/DIR/NAME LO HI` drafts a range per flag mode; check that every new
  file compiled and its NEW DIFF lines, `mod.py remove` the functions,
  `make`, `tools/shift/data_owners.py`, fcheck.sh, compare out/gen/data.tsv's
  names with the base (every deleted file can take data definitions with
  it), and scan the new files for implicit declarations (Sessions 50 to
  53, Traps).  Group by what the functions do (`refs.py LO HI`: their
  calls and data); leave whole-VU0 functions in place
  (docs/matching-tips.md).
- Keep sized externs in .c files: cover_check reads only those (session 35).
- `tools/shift/s36move/mod.py draft OUT.c func...` writes a draft module from
  the old files (bodies plus every declaration they use, views side by side)
  and `mod.py remove func...` deletes the definitions and the declarations
  only they used (prints EMPTY / NOTE lines).  Sessions 36 to 40 used it for every
  chunk; the checklist below still applies.  It does not copy `static inline`
  helpers (inl_sc) and does not call a file EMPTY while one is left: delete
  such files by hand (session 38: s11_w50, s6_19, c13, s8_w12; session 40:
  s10_r2_7, b14).  It does not move data definitions either: move a
  `TYPE D_X ALIGNED(n);` its functions own by hand.
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
