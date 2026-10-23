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
| `src/vm/vm_ops.c` | 35: every function from 0x001c08e8 to 0x001c1cf8 except the two below, in address order |
| `src/vm/vm_ops.nosi.c` | func_001c1718 (needs `-fno-sched-interblock`) |
| `src/vm/vm_ops.nostrict.c` | func_001c1980 (needs `-fno-strict-aliasing`) |
| `include/vm/script_vm.h` | prototypes of the module's functions other code calls, `VmOp` |

**Why these belong together.** The script interpreter (func_001c3408 in
s6_13, func_001c3770 in b10) runs `op = func_001c1ce8(code, pc); arg =
func_001c1cf8(code, pc); r = D_0037A198[op](vm, arg);`. D_0037A198 is a table of
32 function pointers (read from the ELF): 30 of them are the handlers in
0x001c08e8-0x001c1b58, the other two are func_001cd208 and func_001dcad0 (far
away; not moved). The rest of the range is what those handlers call: the type
clamp func_001c0bf0, the save block accessors func_001c0da0 / func_001c0e50 /
func_001c0e80, the cross-VM jump func_001c1980 (called by the handler
func_001c19f8) and, closing the range, the instruction fetch pair
func_001c1ce8 / func_001c1cf8. The range is contiguous: no function in it was
left out. Each handler's comment in vm_ops.c gives its opcode (its index in
D_0037A198). The names stay `func_XXXXXXXX`; none is registered in functions.tsv.

**Where they came from** (37 functions from 9 files): src/auto/text_001c0000.c
(13), src/auto/text_001c0000_9.c (1; now empty, deleted), src/hand/text_001b0000_h14.c
(8), src/hand/nostrict/text_001b0000_h14.c (1), src/hand/text_001a0000_h41.c (8),
src/hand/text_001b0000_h66.c (2), src/hand/text_001b0000_s6_13.c (1),
src/hand/nosi/text_001c0000_s7.c (1; deleted), src/hand/text_001c0000_h42.c (2).

**Types.** Every handler takes the VM record, now `VmRec *`
(include/data/types/vm_rec.h) instead of nine views: h14's / h41's / s7's `VM`
and `VM_1c0b40`..`VM_1c13e8` (`stack`, `regs`, `vars`, `vidx`, `w756`, `depth`,
`flags` became `stk`, `var`, `x270`, `x2f0`, `x2f4`, `rsp`, `fl.x`), h66's and
s6_13's VmRec aliases, h42's `P` (the VM another VM jumps: `a[]` is `lbl`, `b[]`
is `ret`), and the M2C_FIELD offsets of the autodecomp functions. All of it kept
the code; only func_001c1cf8 needed its m2c operand order back (`pc * 4 +
(s32)code`, not `code + pc * 4`). func_001c4640's message is `VmMsg` in
vm_ops.c (h66's `Msg`) until the message code moves too.

**Context.** All 37 functions match together in one file in address order with
the default flags, although several were matched in files with a different
neighbourhood (h41 defined func_001c1628 above func_001c0bf0, its callee; in the
module the callee is above it, and the code is the same). Only the two flag
functions differ, and only with their own flags: compiling the whole module
with `-fno-sched-interblock` or `-fno-strict-aliasing` breaks other handlers
(func_001c1aa8, func_001c1118, ...), and compiling those two with the default
flags breaks them (func_001c1718 is one instruction longer).

## Flags: what a module takes

gcc 2.96 has no per-function flags: `__attribute__((optimize))` and `#pragma GCC
optimize` arrived in gcc 4.4, and every flag in kh1.toml applies to a whole
compile. So functions that match only with different flags cannot share a file.
Options considered:

1. **One file compiled once per flag set**, each pass placing only its own
   functions (the others as CONTEXT_ONLY). Keeps the whole module in one file and
   in order, but one source would give several objects, and obj_for, placements,
   objdiff units, variants.py and shift_ld all assume one object per source.
2. **A flag table in kh1.toml naming files** (`path = "src/vm/vm_ops_x.c"`): works
   with no tool change (overrides match by prefix), but the file's flags are
   invisible from its name.
3. **Sibling files named by flag mode** (chosen): `src/vm/vm_ops.c` plus
   `src/vm/vm_ops.nosi.c` and `src/vm/vm_ops.nostrict.c`.

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
matching helpers. Object files are `out/build/src/vm/vm_ops.nosi.c.o`.

A sibling file loses the functions above it in the main file. Where that
matters, give it CONTEXT_ONLY stubs of the callees defined above it
(docs/context-only-plan.md): func_001c1718 needs one for func_001c0bf0 (without
it one word differs); `{ return x; }` is enough. The main file keeps a comment
at the moved function's place.

## Headers, externs, data and rodata

- **Module header** (`include/<module>/<name>.h`): prototypes of the functions
  other files call, with the real types. The module includes it, so the
  definitions are checked against it. Other files still declare their own
  prototypes (b10, c09, s6_13 ... declare `s32 func_001c1ce8(s8 *, s32)`, which
  agrees); switching them to the header is a follow-up per file, and must keep
  `make` identical (a different pointer type can change alias sets: see
  docs/shiftable-plan.md "Session 29" hazards).
- **Externs**: use the shared data headers (include/data/data_00XX.h,
  include/data/pieces/D_X.h, include/data/types/*.h), not file-local `extern`s.
  vm_ops.c includes data_0038.h / data_003C.h at the top. tools/shift/cover_check.py
  sizes the file-scope externs of every C file, so a module must declare the same
  types its users did, or the float keep list changes; compare
  `out/shift/m12-float/float_covered.txt` before and after (it was identical here).
- **Rodata** (jump tables, strings, float constants) needs nothing: split-rodata
  gives each function its own `.rodata.<fn>`, and link-script infers its address
  from the function's `%hi/%lo` pairs, so it moves with the function
  (func_001c0bf0's jump table did: out/gen/rodata.tsv now names vm_ops.c.o). A file-scope `const`
  table is attributed to the next function in the file: keep it directly above
  its user, or declare it `extern D_X`.
- **Data defined in C**: each variable is placed by name (`.data.<name>`), so it
  can live in any file; define it in the module that owns it, never `static`.
  This module defines none (D_00629808 stays in src/auto/text_001c0000.c with
  func_001c07f0, its user).
- **Removing a function from an old file**: if a function left in that file calls
  it from below, leave a CONTEXT_ONLY copy (or `{}` stub) at its place, since the
  caller may have matched with the definition above it. Not needed here (the only
  in-file caller, h41's func_001c13e8 of func_001c0bf0, moved too). Delete what
  only the moved functions used (views, externs, prototypes) and files left empty.

## Build and tools

Nothing assumes the src/auto / src/hand names except where noted:

- File discovery: the Makefile takes every `*.c/.cpp/.cc/.s` under src/ (dot-files
  skipped); `kh1tool.py gen` regenerates out/gen/objects.mk when the list changes.
  A new directory needs no registration.
- link-script, patch, verify, progress: work from out/gen/placements.tsv (symbol ->
  address); `decompiled_addrs` (rank) scans all of src/.
- objdiff / report: one unit per source file (the module is three units).
- autodecomp `--write` only creates new src/auto/ files keyed by address (or
  `--out-dir`); it never touches modules, and a function defined anywhere is not
  retried. Its default flags come from the `src/auto` path.
- Shift build: objects from OBJS, compile rules from objects.mk (variants.py finds
  sources by content); cover_check / reach_check / ptr_only read every src/*.c.
- tools/shift/type_move.py names per-file type headers after the source path
  (src/vm/vm_ops.c -> include/data/types/vm_vm_ops.h); a module puts its types in
  include/<module>/ instead.
- Every object depends on every header, so adding a header rebuilds everything
  (about 2-3 minutes at -j2).

## Verification (session 30)

- `make`: OK, byte-identical, 6979 decompiled functions (same as before).
- `make objdiff` / `make report`: every function still in a unit; placements.tsv
  differs only in the source column of the 37 moved functions.
- `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1 SHIFT_OVERLAYS=<empty dir>`: M12-FLOAT
  OK; float_covered.txt identical to the base, and kh1-shift.elf differs from the
  base only in .symtab / .strtab (object order), every loaded section identical.
- `make test`: PASS.

## Next module moves

The next piece of the VM starts right after this one: the interpreter loops that
call `D_0037A198[op]` (func_001c1d20 in h42, func_001c1f80 in c08, func_001c2778
in h66, func_001c3408 in s6_13, func_001c3770 in nostrict/b10, func_001c3b10 in
s11_w1b, func_001c4198 in b10) and the functions between them up to about
0x001c4ed0 (nostrict c09 / c09b, nostrict_nofill r2_9 and s11_w1 also fetch with
func_001c1ce8). That range mixes the default, nostrict and nostrict_nofill
modes, so it will need two or three sibling files. Then: the two far handlers
func_001cd208 / func_001dcad0, the VM lookup func_001e98d0, and the handlers
0x001c6890-0x001cc208 that h14 / h15 / h16 / h42 / h67 match against VM views.
Each move can empty old files and retire per-file view types in
include/data/types/. Leave alone the files another worker is retyping in the
same session (session 30: the D_002C58D0, D_00304BE8 and D_002A6238 users and b11).

## Checklist for a module move

1. Pick the set with evidence (a function table, a call graph, a shared type);
   prefer a contiguous address range. List each function's current file from
   out/gen/placements.tsv, and its flag mode from that file's directory.
2. Copy the bodies into `src/<module>/<name>.c` in address order. Replace views
   with the shared types; include shared headers for data; add a module header
   for what other code calls. Keep `func_XXXXXXXX` names unless the purpose is
   proven (then register it in functions.tsv).
3. `python3 tools/checkfile.py src/<module>/<name>.c` (rodata words differ there;
   `make` places rodata). For a FAIL, try the function's old flags with
   `KH1_EXTRA_CCFLAGS=...`; if only those match, move it to
   `<name>.<mode>.c` with CONTEXT_ONLY stubs of its callees from above.
4. Remove the definitions from the old files (CONTEXT_ONLY copies where a
   remaining caller below needs one), then their orphaned views, externs,
   prototypes and empty files.
5. `make` (identical, same function count), `make objdiff`, and
   `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1 SHIFT_OVERLAYS=<empty dir>`
   (run tools/shift/data_owners.py first in a fresh tree); compare
   float_covered.txt with the same build before the move.
6. Update this page's module table.
