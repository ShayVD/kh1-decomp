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
two are func_001cd208 and func_001dcad0 (far away; not moved). The rest of the
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
  prototypes, mostly different from the header (`void func_001c4640(Msg *)` in
  15 files, `void func_001c19f8(VMa *, s32)`, `s32 func_001c2df0(s32, s32)` ...);
  only s6_13's (`s32 func_001c1ce8(s8 *, s32)`) was identical, and s6_13 now
  includes script_vm.h. Switching the others changes their types (return types
  and pointer types can change code: see "Hazards" above and
  docs/shiftable-plan.md "Session 29"), so each is a retype checked with `make`.
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
  func_001c07f0, its user).
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
- objdiff / report: one unit per source file (the module is three units; 927 in all).
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

## Verification (session 30, after each step)

- `make`: OK, byte-identical, 6979 decompiled functions (same as before).
- `make objdiff` / `make report`: all 6979 functions at 100%; placements.tsv
  differs from the base only in the source column of the 60 moved functions.
- `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1 SHIFT_OVERLAYS=<empty dir>`: M12-FLOAT
  OK; float_covered.txt identical to the base, and kh1-shift.elf differs from the
  base only in .symtab / .strtab (object order), every loaded section identical.
- `make test`: PASS.

## Next module moves

- The rest of the VM: the two far handlers func_001cd208 / func_001dcad0, the VM
  lookup func_001e98d0, and the code right after this module (0x001c4ed0 on:
  h66's camera functions func_001c5168 / func_001c5b88, then the function
  handlers 0x001c6890-0x001cc208 that h14 / h15 / h16 / h42 / h67 match against
  VM views and the camera tween D_003C5510). Check first whether they match at the
  end of script_vm.c: if they do, they extend this file; if the first one does
  not, the translation unit probably ends at 0x001c4ed0.
- Other files that still loop over D_0037A198 (nostrict/c09b, nostrict_nofill/r2_9)
  are elsewhere in the address space; they are separate translation units.
- Retype the 15 `void func_001c4640(Msg *)` users to script_vm.h's `s32 (VmMsg *)`
  one file at a time (the return type may change their code).
- Leave alone the files another worker is retyping in the same session (session
  30: the D_002C58D0, D_00304BE8 and D_002A6238 users and b11).

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
