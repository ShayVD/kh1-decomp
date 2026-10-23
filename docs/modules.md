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
  definitions are checked against it. Other files still declare their own
  prototypes, mostly different from the header (`void func_001c19f8(VMa *, s32)`,
  `s32 func_001c2df0(s32, s32)` ...). Switching them changes their types (return
  types and pointer types can change code: see "Hazards" above and
  docs/shiftable-plan.md "Session 29"), so each is a retype checked with `make`.
  s6_13 (session 30) and the 15 `void func_001c4640(Msg *)` users (session 31)
  now include script_vm.h.
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
  caller may have matched with the definition above it. h42 keeps a CONTEXT_ONLY
  func_001c4640 for its five callers below it. Delete what only the moved
  functions used (views, `#define D_X (*(View *)&D_X)` macros, externs,
  prototypes), files left empty, and their include/data/types headers.

## Build and tools

Nothing assumes the src/auto / src/hand names except where noted:

- File discovery: the Makefile takes every `*.c/.cpp/.cc/.s` under src/ (dot-files
  skipped); `kh1tool.py gen` regenerates out/gen/objects.mk when the list changes.
  A new directory needs no registration.
- link-script, patch, verify, progress: work from out/gen/placements.tsv (symbol ->
  address); `decompiled_addrs` (rank) scans all of src/.
- objdiff / report: one unit per source file (src/vm/ is five units and src/camera/ three; 924 in all after session 31).
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

## Verification (sessions 30 and 31, after each step)

- `make`: OK, byte-identical, 6979 decompiled functions (same as before).
- `make objdiff` / `make report`: all 6979 functions at 100%; placements.tsv
  differs from the base only in the source column of the 60 moved functions.
- `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1 SHIFT_OVERLAYS=<empty dir>`: M12-FLOAT
  OK; float_covered.txt identical to the base, and kh1-shift.elf differs from the
  base only in .symtab / .strtab (object order), every loaded section identical.
- `make test`: PASS.

## Next module moves

- **The script-function library** 0x001c6d08-0x001ec678: the 763 entries of
  D_003D9FE0 (func_001dcad0's table, opcode 24), in 0x001c/0x001d/0x001e
  (153 / 505 / 105 entries). The camera's 32 were the first group. Find the next
  groups by data (each group's shared global, like D_003C5510 for the camera)
  and by "needs X defined above", and move func_001dcad0 with D_003D9FE0 once
  the group around 0x001dcad0 is known. The functions right after the camera
  (0x001ca9e8-0x001cce38: h14, h42, h67, h15, b10 ...) work on VmMgr and are
  the next candidates.
- Remaining views of the camera data: b10 still includes the D_003C5510 piece
  header (CamS) for its other functions, and h14 keeps its multi-name
  `extern f32 D_003C55E0, D_003C55E4 ...` line (unused now, kept for
  cover_check; drop it with a float_covered check).
- h42's CONTEXT_ONLY func_001c4640 (still `Msg *`) is not needed by its callers
  (a probe without it changes nothing): retype h42 to script_vm.h and drop it.
- Other files' prototypes of VM functions that differ from script_vm.h
  (`s32 func_001c4640`, `func_001c19f8(VMa *, s32)`, `func_001c2df0(s32, s32)`):
  retype one file at a time with `make`.
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
   (run tools/shift/data_owners.py first in a fresh tree); compare
   float_covered.txt with the same build before the move.
6. Update this page's module table.
