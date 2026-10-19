# Shiftable build plan (kh1-decomp, after session 12)

Goal: link all of `src/` plus the unmatched functions and `src/asm` into a new ELF, with
no patching into the original, that boots in PCSX2 to the title screen. All numbers below
were measured on the repo and `out/` build of 2026-10-19 (6,966 functions placed, 22 not).
Scan scripts: `tools/shift/shiftscan_*.py` (read-only, run with `python3 -I`).

## 1. What still depends on absolute addresses

### 1a. Code -> anything (relocations in the compiled objects)

925 objects, 6,954 global definitions. Relocations in code and compiled rodata:
R_MIPS_26 20,996, HI16 15,189, LO16 16,719, R_MIPS_32 2,653. Everything C code references
is already symbolic; the question is only what each symbol resolves to. Today
`out/gen/symbols.ld` PROVIDEs every unresolved name at its original address (10,434 lines).

| Referenced but not defined in src | Symbols | Relocs | In a shiftable build |
|---|---|---|---|
| `D_` in file-backed data, 0x272C70-0x494068 | 2,109 | 16,060 | data blob base + offset |
| `D_` in .bss, 0x494080-0x675018 | 1,220 | 13,369 | bss base + offset |
| `D_` fixed memory past the image: 0x6A0000, 0x720000, 0x820000, 0x9A0000, 0xF20000 (overlay), 0xFE0000, 0x1CE0000 | 7 | 111 | stay absolute |
| `D_` low kernel RAM 0x9B38-0xAC20, GS 0x12000000 | 14 | 52 | stay absolute |
| aliases of matched functions (two names, one address): GOFAST `dpadd`/`fptodp`/... (10 names, 696 relocs), `func_00250054`=memset, `func_002583e0`=FlushCache, ... | 53 | 845 | `alias = canonical;` in the link script |
| ...of which libc statics referenced by their global placeholder (00251600, 00252370, 00253b10, 00253cd0) | 4 | 4 | need a global label |
| unmatched functions (not in src) | 20 | ~170 | asm export (see 2) |
| mid-function entry points: `func_001001d8` (inside 001001d0, after its syscall), `func_00260f40` | 2 | 6 | label inside the asm |

3,762 `func_` placeholders resolve to definitions in src and need nothing.

Danger: a PROVIDE fallback silently resolves any forgotten name to its *old* address.
The shiftable link must not include `symbols.ld` for anything inside 0x100000-0x675018;
every such name must be defined by a placed function, a label, an alias, or the data/bss
base. Anything left is a link error.

Hard-coded addresses in C: I checked every `lui` without a relocation whose value lands in
0x0010xxxx-0x0067xxxx (186) and in the KSEG/uncached mirrors (200). All are constants
(colours like 0x801E1E1E, flags, float bits) except **one**: `func_00171078` reads
`((s32 *)0x35BD40)[i]` (docs/portability.md). It needs `#ifdef KH1_SHIFTABLE` ->
`D_0035BD40` (the matched build keeps the literal).

### 1b. Code layout today

- Code range 0x100000-0x272C70 = 1,518,704 bytes. Placed C/asm: 1,469,428 bytes in 6,966
  functions. Not placed: 22 functions, 35,260 bytes. Padding between functions: 3,478 gaps,
  13,976 bytes, all zero, all 8-byte alignment (3,553 starts are 16-aligned, 3,418 8-aligned,
  17 4-aligned). A sequential link in address order should reproduce every address.
- `.ctx` (CONTEXT_ONLY copies, 23,396 bytes) is discarded; the plain `.orphan` section must
  be empty.

### 1c. Data, rodata and bss

- **All data still comes from the original ELF.** src defines 0 bytes of `.data`/`.bss`.
  The file-backed region after code is 0x272C70-0x494050 (2,233,312 bytes, 63% zero words):
  .data, the VU microcode and DMA packets, tables, then .rodata (~0x48C000 on; strings such
  as `dkmovie.x` at 0x48CF30). .bss 0x494080-0x675018 (1,970,072 bytes), cleared by crt0
  from 0x494050.
- **Compiled rodata**: 228 blocks, 13,440 bytes, placed at original addresses
  (`out/gen/rodata.tsv`): 165 switch jump tables (10,540 bytes = the 2,635 section-relative
  R_MIPS_32 entries) and 63 constant/string blocks (2,900 bytes). Those already relocate
  correctly when code moves. In the shiftable build they are holes cut out of the data blob,
  filled by the compiled sections at the same blob offset.
- Jump tables not compiled from C: the original has 174 `jr` through a non-`ra` register;
  165 are the C tables above, so about 9 tables (vu0_render asm, 0010d470, 001f1fc8,
  001f94f0, ...) live in the blob and need relocations.

### 1d. Pointers inside the data blob (what breaks when code or data moves)

Every aligned word in the blob (compiled-rodata holes removed) whose value falls in
0x100000-0x675018: **15,153 candidates**.

| Target | Words | Notes |
|---|---|---|
| a function start | 1,982 | high confidence; 34 tables of >=3 entries hold 1,256 (ppp class table at 0x370200, callback tables, vtables) |
| inside a function | 1,233 | ~300 real: jump tables of asm/unmatched functions (vu0_render 64, 0010d470 68, 001f1fc8 21, 001f94f0 21...). ~700 "into" matched C functions are mostly numbers (310 hit crt0's 0x100008-0x1001C8: values like 0x001001xx) |
| text, unaligned | 1,056 | noise, gives the noise rate (~350 aligned false hits expected over the text range) |
| data/rodata | 10,135 | 9,273 aligned; 4,092 are DMA REF tags (`0x30000000, 0x004862A0` repeated over 0x470000-0x47FFFF); 873 unaligned non-string = noise; s16 vertex pairs in 0x330000-0x34FFFF are the main false-positive source |
| bss | 740 | ~half unaligned, so ~350 real |

Plus words in mirrored ranges that may be pointers with high bits: 0x80xxxxxx 1,636 (mostly
0x80RRGGBB colours), 0x30xxxxxx 655 (uncached-accelerated), 0x20xxxxxx 250, 0xA0xxxxxx 68.

Estimate: ~2,000 code pointers (certain), ~300 jump-table entries (certain, from the asm
analysis `function_asm` already does), ~8,000-9,000 data->data pointers and ~350 bss
pointers, with **~1,500-2,000 ambiguous words** that need a rule or a human decision.

### 1e. Extracting the data as a build input (never committed)

`kh1tool extract-data` (new): check the SHA-256, cut 0x272C70-0x494050 out of the user's
ELF into `out/data/main.bin` (gitignored, like `out/`). `kh1tool gen-data` writes
`out/gen/data.s`:

```
.section .data.blob,"aw"
D_BLOB:  .incbin "out/data/main.bin", 0x0, 0x1234      # runs of plain bytes
         .word func_0012abcd                          # one recovered pointer
         .incbin "out/data/main.bin", 0x1238, ...
         .space 0x40                                  # hole: compiled .rodata.func_x lands here
```

The relocation list is committed as `data_relocs.tsv` (blob offset, type, target symbol,
addend; **addresses and names only, no game bytes**, like layout.tsv). Rows come from
`kh1tool find-data-relocs` with confidence tiers: (1) function starts and asm jump tables,
(2) aligned pointers to a `D_` symbol code uses or to a place code indexes, DMA tag address
words, (3) everything else ambiguous, decided by rules (s16-pair test, colour test, float
test, neighbours in the same table stride) and spot review. Data/bss D_ symbols become
`D_X = D_BLOB + (X - 0x272C70)` / `D_X = D_BSS + (X - 0x494080)`. Data and bss move by
**one shared delta**, so every `D_A + offset` that m2c wrote (and that may really be
another object) stays correct. Keep the delta a multiple of 0x1000 (DMA, `lq` and VU data
need 16/64-byte alignment).

## 2. Code with no C, SDK, crt0, IOP

- **`.s` files are position-dependent blobs.** 12 files, 18,153 `.word` lines (game:
  `src/asm/` 16,419 words in 6 files: crt0, crt0_start, 001aa1f8, 0024e0a4 (20 functions:
  `sq` context save, VU0 macro code, LZ decoders), vu0_render_1/2; SDK: libkernl_exc,
  libkernl_asm, libc/string.s (MMI str*), libvu0/vu0.s, libpc.s 1,734 words). They carry no
  real relocations: ~91 absolute `jal`/`j` words and ~320 `%hi`/`%lo` words are baked in
  (the comments already name the symbols). `libkernl/syscall.s` (162 stubs) is mnemonic and
  position-independent.
  Fix: `asm_export.py --symbolic` keeps each `.word` (modern gas lacks the VU0 macro
  mnemonics) but zeroes the field and adds `.reloc .-4, R_MIPS_26|HI16|LO16, sym+addend`,
  reusing `function_asm`'s hi/lo tracker; internal branches stay PC-relative; jump tables
  become `.rodata` with `.word .Lxxxx`. Mid-function labels (0x1001D8, 0x260F40) and global
  labels for the 4 libc statics are added here.
- **The 22 unmatched functions** (35,260 bytes): 19 have near-miss drafts (best ones in
  nonmatchings/session12, session11, ... ; e.g. s12w6 0010d470 179w, 00110618 93w, s12w7
  001fd858 112w, s12w11 00265608 26w). **001e1c20 (2,128 B), 001f94f0 (2,388 B) and
  00208458 (2,636 B) have no draft at all** (never attempted). Use symbolic asm export for
  all 22 first: exact, and the boot path needs `sceGsDefDispEnv` (00265608). Drafts go in
  behind a switch one at a time later; a draft's size differs from the original, which only
  the shiftable build can hold. A near miss is not proven equivalent; diff semantics
  (register/schedule-only differences are fine) before trusting it.
- **crt0** (0x100008, asm): clears registers, `SetupThread(_gp=0x494050, stack 0x1FE0000,
  0x20000, args 0x494080, exit func_001001d0)`, clears .bss 0x494050-0x675018,
  `SetupHeap(0x675018, ...)`, `FlushCache`, calls main `func_00100558`. In the shiftable
  build these become `_gp`, `_fbss`, `_end`, `_args` linker symbols; stack and heap stay.
- **SDK** (libkernl, libgraph, libdma, libpad2, libdbc, libvib, libcdvd, libmc, libipu,
  libpc, newlib, libgcc, libvu0): all matched except sceGsDefDispEnv. They are ordinary
  objects; nothing special beyond the asm files above.
- **IOP**: the ELF embeds no IRX (no ELF headers inside). It reboots the IOP with
  `rom0:UDNL cdrom0:\IOPRP250.IMG` and loads sio2man, dbcman, ds2o, mcman, mcserv, libsd
  (plus dev9/atad/hdd/pfs for the HDD install) from the disc by name. IOP code has no EE
  address dependencies, so nothing to build; the disc must be mounted.
- **EE overlays from the disc (main boot risk).** Code at 0x00F20000 is loaded from `.x`
  files: `dkmovie.x`, `dktitle.x` (the title screen), `gb.x`, `wm.x`, `xl_limit.x`,
  `xs_dh_break.x` (`func_00111020` loads dkmovie.x there; callers jump to 0xF20000 with a
  command). If they are linked against the main ELF's absolute addresses (likely), moving
  any function or data they call or read breaks the title screen. Not checkable here (no
  disc). Needed: `kh1tool scan-overlay FILE.x` that the user runs on their own extracted
  files, listing every `jal`/`%hi`/`%lo`/data word that points into 0x100000-0x675018.

## 3. First milestones (testable in this container)

- **M0: symbolic link at the original addresses.** Sequential link (address order,
  natural alignment) of every `.text.*`, the data blob with holes + compiled rodata, and
  NOBITS .bss, through a new `kh1-shift.ld` and no PROVIDE fallback inside the image. Write
  a fresh ELF (one PT_LOAD at 0x100000, entry 0x100008). Pass = the loaded image equals the
  original byte for byte and every function address is unchanged. This proves every
  relocation in the code and asm is right, without moving anything.
- **M1: code moved, data fixed.** Code cannot grow in place (data starts right at
  0x272C70), so rotate instead: move the last functions (total a multiple of 16) to the
  front. Every function moves, data does not, image size is the same. Tests code->code
  and data->code relocations (function pointers, jump tables).
- **M2: data moved.** Insert 0x1000 bytes after .text; data and bss shift by 0x1000. Tests
  code->data and data->data relocations.
- Check for M1/M2: an **inverse-map comparator**: for every relocated field, map the new
  value back through the address map and compare with the original word; every other byte
  must be identical. It proves the relocations that exist are right. It cannot see a missed
  pointer (an unrelocated word stays at its old value in both builds); those only show as
  crashes at run time, so the ambiguous tier in 1d matters.
- **PCSX2 cannot run here.** It is not installed, and booting needs a PS2 BIOS dump and the
  disc image, both user-owned game/console data that must not enter the container. Xvfb is
  present, but that does not help without those. Runtime tests are on the user's machine:
  PCSX2 "Boot ELF" with the user's ISO mounted (so cdrom0: modules and overlays load).
  M0's ELF should behave exactly like the original; then M1, then M2.

## 4. Steps, sizes, risks

| # | Step | Size (rough) | Testable here |
|---|---|---|---|
| 1 | `asm_export.py --symbolic` (`.word` + `.reloc`), regenerate the 12 `.s` files; add mid-function and static labels | ~250 lines tool; ~18k lines regenerated; patch-in-place build must stay byte-identical | yes (`make`) |
| 2 | asm export of the 22 unmatched functions into `src/shift/` (built only by the shift build) | ~9k instruction lines generated | yes |
| 3 | alias table from functions.tsv (one address, many names) + "no PROVIDE inside image" check | ~80 lines | yes |
| 4 | `extract-data` + `gen-data` (incbin chunks, holes for 228 compiled rodata blocks) | ~250 lines | yes |
| 5 | `find-data-relocs` heuristics -> `data_relocs.tsv`; review ambiguous tier | ~400 lines; ~12k rows; 1,500-2,000 words to classify, the long pole | partly |
| 6 | `kh1-shift.ld` generator, `D_` = base+offset definitions, ELF writer, `make shift` | ~300 lines | yes |
| 7 | M0 verify (image == original) | ~100 lines | yes |
| 8 | M1 rotate + M2 data shift + inverse-map comparator | ~250 lines | yes (static only) |
| 9 | `KH1_SHIFTABLE` fix for func_00171078; `scan-overlay` tool for the user's `.x` files | small | tool yes, data no |
| 10 | User runs M0/M1/M2 in PCSX2 to the title screen; fix misses from crashes | iterative | no |
| 11 | Swap in near-miss drafts one by one (needs shiftability) | per function | static diff only |

Order: 1-3 and 6-7 first (M0 needs only the trivial "whole blob, no relocs" data input,
since nothing moves); 4-5 and 8 next; 9-10 last.

Risks, biggest first:

1. **Overlays (`dktitle.x`, `dkmovie.x`) call into the main ELF by absolute address.** If
   so, M1/M2 cannot reach the title screen until the overlay imports are pinned (keep those
   functions/data at original addresses, which constrains layout) or the overlays are
   relocated too (decomp them as extra link units, or fix them up at load time). Find out
   first with `scan-overlay` on the user's files.
2. **Missed data pointers** (~1,500-2,000 ambiguous words). A miss is silent statically and
   crashes or corrupts at run time, possibly long after boot. Mitigate with typed recovery
   (fields code dereferences as pointers, struct strides in tables), DMA/VIF packet
   parsing, and by moving data last (M1 before M2).
3. **Pointers with high bits** (uncached 0x2/0x3 mirrors, KSEG0 0x8/0xA) in data and DMA
   tags hold physical addresses; relocate as `sym + 0x20000000` etc. Colours look the same.
4. **Fixed memory map limits growth.** Buffers at 0x6A0000 and up are absolute; the image
   (end 0x675018) can grow by at most 176,104 bytes (to 0x6A0000) unless those regions are
   made symbolic too (0xF20000 cannot move while overlays are absolute).
5. **Asm blobs** may hide address arithmetic the hi/lo tracker misses (e.g. an address
   built with `ori`, or a `lui` shared across blocks). M0 catches every one of these,
   because the image would differ.
6. **Near-miss drafts** may not be behaviour-identical; three functions have no C at all.
7. **Tooling assumptions**: `infer_rodata` places compiled rodata from code; in the shift
   build those blocks must still land at their blob offset (or anywhere, once data relocs
   are complete). Weak `.ctx` symbols must never be the definition that wins.
8. **Runtime testing is only on the user's machine**; this container can prove
   relocation correctness, not boot.

## Session 13 status (worker s13s1: steps 1-3, 9a)

### Step 1: symbolic asm (done; `make` byte-identical, 6,972 / 6,988)

- `tools/asm_export.py --symbolic` keeps every `.word` and adds, after each relocated word,
  `.reloc .-4, R_MIPS_26|R_MIPS_HI16|R_MIPS_LO16, sym[+-0xOFF]` with the field zeroed (the
  addend sits in the expression; gas writes it in place, REL style). `--regen FILE.s ...`
  rewrites existing exports in place (same header, functions, section names).
- **`.reloc` works**: every `.s` in the build is assembled by binutils `as` (`$(AS)`,
  2.42 here; `kh1tool gen` never sends `.s` files to the ee-gcc drivers), which takes
  `.reloc`. ee-as 2.10 (`ee-gcc -c -x assembler`) rejects it ("Unknown pseudo-op:
  `.reloc'"); no fallback to mnemonics was needed. Keep any shift-build assembly of these
  files on binutils `as` too.
- Targets: code -> the function containing it as the build names it (out/gen/placements.tsv,
  then functions.tsv, else `func_XXXXXXXX`) + offset; data/bss -> `D_XXXXXXXX` of the exact
  address, addend 0. Relocated range is 0x00100000-0x00675018 **inclusive**: crt0 uses
  `D_00675018` (end of .bss, SetupHeap start), `D_00494050` (`_gp`, start of the .bss clear)
  and `D_00494080` (`_args`); define them base + offset like every other D_. Addresses
  outside (stack `D_01FE0000`, 0x6A0000+ buffers, low kernel RAM, hardware) stay absolute.
- %hi/%lo pairing: reaching definitions over each function's control flow (delay slots,
  likely branches, jump tables, call clobbers), checked against kh1tool's linear tracker
  (now `analyze_asm`, same `asm` output). The flow pass found pairs the linear tracker
  missed (a %hi hoisted out of a loop or set in a delay slot: 14 in src/, more in the
  unmatched functions). A lui shared by low halves of different addresses is relocated
  against the first target's symbol (4 cases, all in unmatched functions; listed on stderr).
  Every HI16 is checked to pair (GNU ld: next LO16 against the same symbol) with a LO16 of
  the same addend. Luis in the image range left absolute are listed: all are lui/ori
  constants (0x28/0x41 in vu0_render, 0x10/0x20/0x43 flags in unmatched game code).
- Regenerated: `src/asm/{crt0,crt0_start,text_001aa1f8,text_0024e0a4,vu0_render_1,vu0_render_2}.s`,
  `src/sdk/{libkernl_asm,libkernl_exc,libpc}.s`, `src/sdk/libc/string.s`,
  `src/sdk/libvu0/vu0.s` (11 files; `src/sdk/libkernl/syscall.s` is mnemonic and has no
  relocations). 389 relocations (91 R_MIPS_26, 144 HI16, 154 LO16); the 16 unmatched
  exports have 548 (272 / 133 / 143).
- Labels: global `func_001001d8` (crt0.s, inside func_001001d0) and `func_00260f40`
  (libkernl_exc.s, inside func_00260d00), added by `--regen` for every `func_` address
  C code names inside an exported function. The libc statics are made global with a
  top-level `__asm__(".globl ...")`: func_00251600 in `src/sdk/libc/vfiprintf.c`,
  func_00252370 / func_00253b10 / func_00253cd0 in `src/sdk/libc/vfprintf.c`.
- Jump tables inside word-exported code (entries in the data blob; the data-reloc step
  must relocate them, R_MIPS_32 against the function + offset):

  | table | entries | function |
  |---|---|---|
  | 0x0048CE00 | 32 | func_0010d470 (unmatched) |
  | 0x0048CE80 | 36 | func_0010d470 (unmatched) |
  | 0x0048FE80 | 8 | func_001ab0e0 (vu0_render_2.s) |
  | 0x0048FEF0 | 8 | func_001afac0 (vu0_render_1.s) |
  | 0x0048FF40 | 8 | func_001b1ab8 (vu0_render_1.s) |
  | 0x0048FF60 | 33 | func_001b3870 (vu0_render_2.s) |
  | 0x00490A80 | 21 | func_001f1fc8 (unmatched) |

  Other indirect jumps in the exports: `jr $s0` in func_0024e18c (return address built
  with %hi/%lo of func_0024e18c+0x20, relocated), jalr through registers loaded from data.

### Step 2: unmatched functions (done)

- The true list (layout.tsv minus placements.tsv): **16** functions, 25,964 bytes:
  0010d470 00110618 00125240 001636d0 00166570 00192958 001c62a0 001cfc28 001eddc0
  001f18e8 001f1fc8 001f2630 001fd858 00200e28 0021e120 00265608 (= sceGsDefDispEnv).
- Exports: **`shift/unmatched/func_XXXXXXXX.s`**, one per function, section
  `.text.<name>` (`sceGsDefDispEnv` for 00265608, else `func_XXXXXXXX`). Top-level `shift/`
  because both the Makefile (`find src`) and kh1tool (`src.rglob`) see everything under
  src/; nothing under shift/ is built, PROVIDEd or counted by `make`/`make progress`.
  Regenerate after a build with `python3 -I tools/shift/export_unmatched.py` (it also
  deletes the file of a function that got matched).
- They reference D_ names that src/ never uses (e.g. D_004D59E4), so symbols.ld does not
  PROVIDE them: the shift link must define every undefined `D_XXXXXXXX` from its name.
- `python3 -I tools/shift/verify_exports.py FILES.s [--delta D]` assembles exports, links
  each at its address (+D, with every image symbol +D) and compares with the original (or
  the original with each relocated field moved by D). All 27 files (16 + 11) pass at
  D = 0, 0x12348 and -0x7ff8; it proves the relocations present are right, not that none
  is missing.

### Step 3: aliases and the PROVIDE check (done)

- `python3 -I tools/shift/aliases.py` (after `make`) writes **`shift/aliases.ld`**: 51
  lines `alias = canonical;` (GOFAST `dpadd = __adddf3` ..., `func_00250054 = memset`,
  `func_002583e0 = FlushCache`, `_sbrk_r = func_00250dd0`, ...). A name inside a function
  would get `alias = func + 0xOFF;` (none today). INCLUDE it in kh1-shift.ld.
- `python3 -I tools/shift/provide_check.py [--list]`: what the shift link would still take
  from a PROVIDE inside 0x00100000-0x00675018 when it links every src/ object, the
  unmatched exports and the aliases. Today: **0 non-D_ names**; 2,140 `D_` in data
  (0x272C70-0x494068) and 1,239 `D_` in .bss (incl. D_00675018), all to be defined as
  base + offset. Exit status 1 if anything else appears.
- Cross-check: all src/ objects + shift/unmatched + aliases.ld link with a sequential test
  script and only out-of-image PROVIDEs plus D_ names, with no undefined reference.

### Step 9a: overlay scanner (tool done, no data here)

`python3 -I tools/shift/scan_overlay.py FILE.x [--base 0xF20000] [--all]` lists jal/j into
the main code, %hi/%lo pairs and aligned words pointing into 0x00100000-0x00675018, named
from layout.tsv / functions.tsv, with a summary. Raw files load at --base; an ELF is
detected by its header. Self-test on a synthetic blob: `python3 -I tests/scan_overlay_test.py`
(not wired into `make test`, which is the Makefile's).
