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

## Verification (sessions 30 to 33, after each step)

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

- **After the dispatcher**: 0x001dcb00 onwards (no table entries until
  0x001ddc78; then 154 entries to 0x001ec678) is other code; find its groups
  by data as for the message windows.  What is there now: auto
  text_001d0000.c (6), _2 (8), _7 (2), h19 (4, and the data D_0062A640),
  h44, h67, c10, b11, nofill/b11, s6_15, nofill/s6_15 and the 0x001e
  files.  Whether the 154 later entries belong to vm_lib.c (code after the
  dispatcher in the same file) or to other files is open: try them appended
  to vm_lib.c and look at their data before deciding.
- The library's prototypes of its own functions: the table still declares
  every entry `s32 func_X();`, including the ones now defined above it
  (harmless; a `void` one would conflict, none does).
- Remaining views in vm_lib*.c (see "Session 33" and "Session 32"): each
  was tried on the shared types and is a genuine second view; leave them
  unless a type change makes one fit.
- Remaining views of the camera data: h14 keeps its multi-name `extern f32
  D_003C55E0, D_003C55E4 ...` line (unused, kept for cover_check; drop it
  with a float_covered check).  b10 is gone (session 32).
- Other files' prototypes of VM functions: session 33 retyped every one
  outside the library files (docs/shiftable-plan.md "Session 33: Phase 4
  types").  `python3 -I tools/shift/s33types/s33_protodiff.py` lists what is
  left (8 declarations in b11, nofill/b11, s6_15, nofill/s6_15, h44 at the
  types pass; h17 and h18 are gone since).  Retype one file at a time with
  `make`; `--defs` also lists declarations of functions no header declares
  yet (func_001c4de0, func_001c4ed0, func_001cd238 ...).
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
