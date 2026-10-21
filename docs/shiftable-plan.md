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

## Session 13: M0

**Status: M0 passes.** `make shift` links a fresh ELF symbolically at the original addresses
and its loaded image equals the original byte for byte.

```
make -j2          # the normal build first (unchanged, still byte-identical)
make shift        # extract data, link out/shift/kh1-shift.elf, run the M0 check
make shift SHIFT_ASM_DIR=<dir> SHIFT_ALIASES=<file>   # with committed asm exports / alias table
```

Last lines of `make shift` (6,972 placed + 16 exported functions):

```
shift-ld: 6988 functions (1 extra asm objects), 230 rodata holes, 174 blob chunks, 1 merged rodata copies; defined 53 aliases + 2 mid-function labels, 2113 data + 1221 bss names, 21 absolute (outside the image)
shift-ld: note: explicit padding 0x00100000-0x00100008 before func_00100008 (no alignment explains it)
shift-elf: out/shift/kh1-shift.elf: load 0x00100000, file-backed 0x394050, memsz 0x575018, entry 0x00100008, 10407 symbols
M0 OK: kh1-shift.elf loads byte-identical to the original: 0x00100000-0x00675018, entry 0x00100008, .bss 0x00494080+0x1e0f98
M0 OK: 10379 functions, labels and D_ names at their original addresses
```

What runs (all outputs under `out/shift/`, gitignored; nothing extracted is committed):

1. `tools/shift/extract_data.py`: checks the SHA-256, checks the headers (one PT_LOAD at
   0x100000, one PROGBITS `main` ending at 0x494050, the 0x18 bytes the PT_LOAD carries
   past it are zero, `.bss` at 0x494080), writes `data/main.bin` = 0x272C70-0x494050 and
   `data/image.json` (entry, sizes, e_flags, the `.reginfo` words).
2. Unplaced functions: with `SHIFT_ASM_DIR` empty (today), `shift_ld.py missing` lists the
   16 layout functions no source places and `tools/asm_export.py` writes them to
   `asm/unplaced.s` (position-dependent `.word`s, correct only at the original addresses;
   **temporary**). With `SHIFT_ASM_DIR=<dir>` every `<dir>/*.s` is assembled instead; their
   `.text.<fn>` sections are placed by name (functions.tsv or `func_XXXXXXXX`) and their
   `.rodata.*` (symbolic jump tables) are located from the `%hi/%lo` pairs like
   `kh1tool link-script` does, so they land as holes at their blob offset.
3. `tools/shift/shift_ld.py gen` writes `kh1-shift.ld`, `blob.s`, `objects.lst` and
   `expected.tsv` (original address of every function, label and D_ name, for the check):
   - `.text 0x100000`: every `.text.<fn>` (out/gen/placements.tsv + extra asm objects) in
     address order. Gaps are `. = ALIGN(n)` with the smallest power of two that gives the
     original start (69 statements: 8, 16, 32, 64; 3,400-odd gaps are the sections' own
     8-alignment); only the 8 zero bytes before crt0 are an explicit `. += 8`. Every layout
     function must be present exactly once.
   - `.data ALIGN(16)`: `D_BLOB`, then `blob.s` chunks (`.incbin "out/shift/data/main.bin",
     off, len`, one section each, alignment 1) around the 229 compiled rodata blocks of
     out/gen/rodata.tsv, at the same offsets. One block is a merged copy
     (`ttlib/ui.c` assert string, `.rodata.func_00249fb0` and `.rodata.func_0024a300` at
     0x491848; the original linker kept one): the second goes to a non-allocated `(INFO)`
     section at `D_BLOB + off`, so its references resolve there and it is not loaded.
   - `_gp = _fbss = _edata` (0x494050, crt0's $gp and clear start), `.bss ALIGN(128)
     (NOLOAD)`: `D_BSS`, size up to `_end` = 0x675018 (includes the `.reginfo` slot).
   - Every name an object references but no placed section defines gets an explicit
     definition: in code, a label next to its function (`name = .;` / `name = . + off;`):
     53 aliases (GOFAST names, `func_00250054`=memset, the libc statics 00251600 etc.) and
     2 mid-function entries (`func_001001d8`, `func_00260f40`); data `D_X = D_BLOB + off`
     (2,113); bss `D_X = D_BSS + off` (1,221, `D_BSS - off` for 0x494050-0x494080);
     absolute only outside the image (21: low kernel RAM 0x9B38-0xAC20, 0x6A0000,
     0x720000, 0x820000, 0x9A0000, 0xF20000, 0xFE0000, 0x1CE0000, GS 0x12000000).
     `SHIFT_ALIASES` files are `INCLUDE`d and their names skipped here (still checked).
   - **No PROVIDE.** A name with no address is a generator error; a name the script misses
     is an ld `undefined reference` (tested by deleting a line); a reference to unplaced
     rodata is an ld "defined in discarded section" error (tested). `.ctx*` and unplaced
     `.rodata*` go to `/DISCARD/`; stray `.text/.data/.bss` input to `.shift_orphan`, which
     `shift_elf.py write` requires to be empty. `.ctx` symbols are already undefined in the
     objects (`fix-obj`), so they never win.
4. `ld -T kh1-shift.ld @objects.lst` (map in `kh1-shift.map`), then
   `tools/shift/shift_elf.py write`: a fresh ELF (PT_LOAD at file offset 0x80, align 0x80,
   RWE, memsz to `_end`; PT_MIPS_REGINFO with `_gp`; original e_flags; sections .text,
   .data, .bss, .reginfo and a symbol table with every function and D_ name for debuggers).
   Its filesz is 0x394050 (the original's 0x394068 includes 0x18 zero bytes; same image).
5. `shift_elf.py verify` (M0): loads both ELFs like the loader (file bytes, zeros to
   memsz) and compares load address, entry, image end, .bss start and every byte, then
   checks every name of `expected.tsv` and D_BLOB/D_BSS in the linked symbol table. On a
   mismatch it prints the first differing words as `0xADDR name+off original new`.

What is temporary (switch to s13s1's outputs when merged):

- `out/shift/asm/unplaced.s` (asm_export of the 16 unmatched functions from the user's
  ELF): replace with `SHIFT_ASM_DIR=<their committed dir>` (make it the Makefile default).
- The 12 `.s` files in src/ are still the position-dependent `.word` versions; M0 passes
  with them, M1 does not. Nothing in the shift tools changes when they become `.reloc`.
- Aliases: derived here from the address of each undefined name (registry/placeholder),
  as in-section labels. With `SHIFT_ALIASES=<their file>` those names come from the file.

What remains for M1/M2:

- **The data blob has no relocations yet** (step 5, `data_relocs.tsv`). M1 (code moves)
  breaks every function pointer and asm jump table in the blob; M2 every data pointer.
  `blob.s` is already chunked, so a relocation becomes `.word sym+addend` between chunks.
- Any asm still at fixed addresses (today: all 12 src `.s` files and the temporary
  export) breaks M1. The M0 check cannot see that (identical at the original addresses);
  an M1 link will.
- M1 rotation must keep each gap's `ALIGN(n)` meaning: moving text by a multiple of 64
  keeps every gap; the data blob needs a delta that is a multiple of 0x1000 (plan 1d), and
  `.bss` is `ALIGN(128)` after the data.
- The merged rodata copy (`.rodup_00491848`, INFO section) is pinned to `D_BLOB + off`:
  fine while the primary block stays in the blob at that offset.
- crt0 still hard-codes 0x494050/0x494080/0x675018 and the stack/heap; `_gp`, `_fbss`,
  `_end`, `D_BSS` exist as linker symbols for when crt0 is symbolic (M2 moves data and bss).
- func_00171078's literal `0x35BD40` (plan 1a) still needs the `KH1_SHIFTABLE` switch
  before M2.
- Step 8 (inverse-map comparator) and the M1/M2 link variants are not written.

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

### Step 9b: getting the overlays off the disc (KINGDOM.IDX / KINGDOM.IMG)

`python3 -I tools/shift/extract_kingdom.py GAME.iso --overlays --out DIR` (or `NAME...`,
`--list`) writes the files the game loads by name; standalone, Python >= 3.10 stdlib.
Self-test: `python3 -I tests/extract_kingdom_test.py`. Format, from the code:

- **Index**: func_00120ba0 does `sceCdSearchFile("\\SYSTEM.CNF;1")` -> D_004F3208 (base
  LSN); func_0011fe20 reads `\\KINGDOM.IDX;1` into D_004E4A00: up to 3,584 entries
  `{u32 hash, u32 flags (bit 0 = compressed), u32 sector, u32 size}`, stop at sector=size=0,
  `sector += base`. So **LBA = LBA(SYSTEM.CNF) + sector**; KINGDOM.IMG has no directory
  entry, only its own index entry "kingdom.img" (D_004F3200, used for the HDD copy
  `pfs0:kingdom.img` in func_001202c0: offset = (LBA - D_004F3200) * 2048).
- **Lookup** func_00120190: `bsearch(hash(name), D_004E4A00, count, 16, func_00120170)`
  (unsigned compare on the hash). **Hash** func_001200f8: `h = (h << 1) ^ ((c << 16) % 0x11021)`
  over the signed chars of the name as passed (case-sensitive, e.g. "dktitle.x").
- **Read** func_001204a0 -> func_001201d0: ceil(size / 2048) sectors; if flag bit 0,
  func_00120040 decodes in place, backwards: last byte = escape key, the 3 bytes before =
  output size (len-2 = bits 0-7); bytes read backwards: literal, or key + 0 = literal key,
  or key + n + (count - 3) = copy count bytes from n bytes above the output pointer.
- **Overlays** (all at 0x00F20000, entry = first byte, `int entry(int cmd, int arg)`; no
  function table is passed, so any call back into the main ELF is by absolute address):
  `dktitle.x` (func_00109770, async func_00120748 -> cb func_00109630: FlushCache(2),
  entry(0, 0)), `dkmovie.x` (func_00111020(mode)
  -> cb func_00110fc8: entry(0, mode)), `xl_limit.x` (func_00158df8 -> cb func_00158db0, which only
  flags it loaded; entry(7/8/9/11, 0) from the same file's code), `xs_dh_break.x` (func_001d09d8 -> cb func_001d09a0:
  entry(0, 0); also func_002335d8(i) sync via D_00425BC0[i]), `gb.x` / `wm.x` (func_001ba7e0 /
  func_001ba870 -> func_001b9c60: sync func_001205f0, FlushCache, `entry()` with no
  arguments), summons `xs_{dumbo,bambi,genie,tink,mushu,simba}.x` (func_0013b3d0:
  sprintf("%s%s", D_00304B00[i], ".x"), cb func_0013b1a0; the matching `.dbt` goes to
  D_0052AE5C). About 15 other sites call entry(cmd 1-11, arg) on whichever overlay is
  resident; arg is 0, a mode, or a pointer into main-ELF data. 0xF20000 is also a plain buffer (image/*.rgb, ...).

## Session 13: data relocations, M1/M2

**Status: M0, M1 and M2 pass statically** (with s13s1's symbolic asm, the 9,523 accepted
data relocations and the KH1_SHIFTABLE variant of func_00171078). Runtime is untested
(PCSX2 runs only on the user's machine, plan section 3).

```
make -j2 && make shift                 # M0 (as before), now with the data relocations
make shift SHIFT_MODE=m1               # builds M0 first, then code rotated, data fixed; comparator
make shift SHIFT_MODE=m2               # builds M0 first, then data+bss moved by 0x1000; comparator
make shift SHIFT_RELOC_TIER=1|2|3|0    # which data_relocs.tsv rows become relocations (default 3, 0 none)
make shift SHIFT_VARIANTS=0            # no KH1_SHIFTABLE objects: strict byte-identical M0
make data-relocs                       # regenerate data_relocs.tsv (needs `make`)
```

### Step 5: `data_relocs.tsv` (tools/shift/find_data_relocs.py)

Committed table, one row per pointer-like word of the data blob (compiled rodata holes
excluded: they carry their own relocations): `offset` (from D_BLOB = 0x272C70), `type`
(`R_MIPS_32`, or `R_MIPS_32+0x20000000` / `+0x30000000` for a mirrored pointer), `symbol`
(the layout name of the function holding the target, `D_BLOB` or `D_BSS`), `addend`,
`tier`, `reason`. Rejected candidates are listed with tier `x`, their reason, and `-` for
symbol/addend, so no non-pointer value is recorded; unaligned-target noise (1,256 words)
is counted, not listed. 13,197 rows, 463 KB (under check_no_assets' 512 KiB: if it
grows, drop the rejected rows first). The header lists every reason code.

Inputs: the original image, layout.tsv, out/gen/rodata.tsv, out/gen/symbols.ld (D_ names
src uses), and a fast linear tracker over the whole original code (~1 s) that records
%hi/%lo addresses code builds (`lui` + `addiu`/load/store, never `ori`: gcc builds
addresses with addiu, so ori pairs are constants) and words code loads and then calls
through (`jalr`/`jr`) or dereferences, per variable or indexed table. Jump tables of the
asm and unmatched functions come from `kh1tool.analyze_asm` + `asm_export.more_jtbls`, as
the symbolic export finds them: 146 entries, exactly the 7 tables s13s1 listed (0x48CE00
32, 0x48CE80 36, 0x48FE80/0x48FEF0/0x48FF40 8 each, 0x48FF60 33, 0x490A80 21).

15,509 candidates (aligned words whose value is in 0x00100000-0x00675018, plus 0x20/0x30
mirrors of 16-aligned data/bss addresses):

| tier | words | reasons |
|---|---|---|
| 1 | 2,049 | calltab 879 (function start in a table code calls through), func 657 (lone function start), ftab 367 (run of >=3 starts), jtbl 146 (asm jump tables) |
| 2 | 7,200 | dma 6,369 (address word after a REF/NEXT/... DMA tag, qword aligned; 0x2A0000 and 0x460000-0x48FFFF), str 448 (string start), ptab 263 (table/variable code dereferences; self-linked lists at 0x46A9xx), func-s16 79, dref 30 (address code builds), stride 10, bref 1 |
| 3 | 274 | near 111 (target within 64 KiB of the word, not s16-like: lists, records), dptr-run 63 / bptr-run 18 (next to other pointer words), dptr 40 / bptr 42 (isolated, no rule against: **the real ambiguous remainder**) |
| x | 4,930 | s16 2,063, unaligned 1,256 (not listed), into-func 1,073, mirror-x 376, colour 58, vucode 53, ascii 34, mipscode 17 |

Rules for the ambiguous words, in order: stride (accepted pointers at x-S and x+S,
S = 8..64), vucode (a VU nop word 0x8000033C/0x000002FF within 4 words), ascii, s16
(both halves |s16| < 0x1000 or the value repeats >= 8 times, with s16 pairs or colours
next to it; 0x00430048 alone appears 1,119 times in the vertex/packet region
0x320000-0x350000), mipscode (>= 3 neighbours decode as common EE instructions), colour
(0x00BBGGRR with two equal channels among such words, or RGBA with alpha 0x80/0xFF/
0x40/0x7F next to it), near, float (all neighbours plausible floats), then run /
isolated. A word into a function that is not a known asm jump table is rejected
(into-func: crt0's 0x1001xx numbers, s16 data); into-table (inside an asm function, next
to distinct words into it) is the escape hatch, 0 rows today. Mirrors: no 0x20/0x30
candidate targets an address code builds (they are ctype/ASCII tables, 0x20202020,
0x30303030), so none is accepted; the type exists for when one is found.

Estimate of what is left: the ~80 isolated tier-3 words (dptr/bptr) are the least
certain accepted rows (several look like sizes, e.g. 0x003FF000, 0x00580000: a false
accept corrupts a number when data moves); the ~130 run/near rows are probably right; on
the reject side, colour/ascii/mipscode/vucode (162) and the s16 rejects in regions that
also hold pointer lists are where a real pointer could hide. So **~300-400 words**
deserve a human look before M2 is trusted at run time, down from the 1,500-2,000
estimated in 1d. The DMA rows assume the tags are real (6,368 REF with qwc 0, 1 NEXT).

Found while classifying: the blob holds MIPS code around 0x46A000-0x46C000 (lui/addiu/lw
patterns next to self-linked lists) as well as VU microcode (0x273000-0x278000 and
others). If that MIPS code is copied elsewhere and run, its own absolute addresses are
not image addresses and need nothing; if it runs in place, it is position-dependent.
Worth disassembling that range.

### Linking them (shift_ld.py)

`shift_ld.py gen --data-relocs data_relocs.tsv --reloc-tier N` (default 3): each blob
chunk between two rodata holes is one section of `.incbin` pieces and `.word sym+addend`
lines (`.align 0` after `.section`: no auto-alignment of `.word`, a chunk can start
unaligned). Code targets use a label `__dr_XXXXXXXX = .;` that the script defines at the
target's function (like the alias labels; static functions work too); data targets
`D_BLOB + off`, bss `D_BSS + off`. Rows inside a rodata hole are skipped (counted).
M0 passes: 9,523 words emitted symbolically, same bytes.

Other changes: `D_00675018` (crt0's heap start = `_end`) is now `D_BSS + 0x1e0f98`, not an
absolute (the image end is inclusive); `__dr_` labels are left out of the output ELF's
symbol table; new options `--out-dir`, `--mode`, `--m1-min`, `--data-shift`,
`--subst-obj OBJ=VARIANT`; `variants.tsv` in the output dir; ld runs with `-q` so the
relocations stay in the linked ELF for the comparator.

### KH1_SHIFTABLE (step 9, func_00171078)

`src/hand/text_00170000_s9_w9.c` reads `D_0035BD40[*b ^ 3]` under `#ifdef KH1_SHIFTABLE`
and the literal `((s32 *)0x35BD40)` otherwise (normal build unchanged, byte-identical).
`tools/shift/variants.py build` compiles every source that mentions KH1_SHIFTABLE again
with `-DKH1_SHIFTABLE` (the exact rule of out/gen/objects.mk) into out/shift/variants/,
and the shift build links that object instead. The symbolic version is 4 bytes longer
(gas does not move an instruction with a %lo fixup into the `jr ra` delay slot: `lw`
before `jr`, then `nop`); it still fits before func_00171098, so the M0 check allows
differences inside a variant's slot and says so (`M0 OK: except 2 words inside
KH1_SHIFTABLE variants by design`). `SHIFT_VARIANTS=0` gives the strict byte-identical
M0; with it, M2 reports exactly this hard-coded address
(`text_00170000_s9_w9.c: 0x00171084 lui/mem 0x0035bd40`), which is the check working.

crt0: s13s1's symbolic crt0_start.s relocates 0x494050/0x494080/0x675018 against
D_00494050 (= `D_BSS - 0x30` = `_gp`), D_00494080 (`D_BSS`) and D_00675018 (`_end`), so
they move in M2. The stack (0x1FE0000) and heap size stay absolute, as planned.

### Step 8: M1, M2 and the inverse-map comparator (tools/shift/shift_cmp.py)

- **M1**: the text is rotated at the largest 64-aligned function start that moves at least
  `--m1-min` (0x10000) bytes and still fits before the fixed data (0x257D40: 0x1AF24 bytes
  to the front, the rest after `. = ALIGN(64)`); `.data` stays at 0x272C70. Every function
  moves; the entry goes to 0x11AF48. **M2**: `.data ALIGN(16) + 0x1000`, so data, `_gp`
  and .bss move by 0x1000 (.bss at 0x495080).
- `shift_cmp.py --ref out/shift --new out/shift/m1|m2` (run by `make shift
  SHIFT_MODE=...`) compares with the M0 link, which is itself checked against the
  original. The address map comes from the two link maps: each input section (function,
  blob chunk, rodata block) is a piece; padding moves with the piece before it;
  `_edata..D_BSS` and .bss move with D_BSS; outside the image nothing moves; an address
  at a piece boundary may map with either neighbour (end pointers). Per piece:
  1. every relocated field of REF (`ld -q`), read at its new place, must be the REF value
     through the map: R_MIPS_32 words, R_MIPS_26 targets, HI16/LO16 pairs as full
     addresses (a LO16 pairs with the HI16 of the same symbol and register, the latest
     before it, else after it);
  2. every other byte must be identical;
  3. position-dependent code: unrelocated `j`/`jal`, and unrelocated `lui` +
     addiu/load/store (or `ori` in asm with an aligned value; `addu rX,rX,idx` keeps the
     %hi), whose address moved;
  4. informational: unrelocated data words whose value is an address that moved, grouped
     by their data_relocs.tsv reason. A real pointer among them is a run-time bug.
  Failures of 1-3 are listed per source file (each asm export and the data blob are
  their own groups); exit status 1.
- Sensitivity checks: the old position-dependent export (`SHIFT_ASM_DIR=`) fails M1 with
  274 absolute `jal`s, all attributed to that one file; SHIFT_VARIANTS=0 fails M2 with the
  func_00171078 literal; an early bug (0x20202020 ctype words accepted as mirrored
  pointers, because a C constant built with lui/ori was taken as an address) showed up
  as 15 relocated blob fields that did not map back.

Results:

```
M1 OK: 7391 input sections (6988 moved), relocated fields checked: HI16/LO16 17075, R_MIPS_26 21418, R_MIPS_32 12197
  relocated fields that do not map back: none; other bytes differing: none; position-dependent code: none
  (86 unrelocated lui/ori pairs ignored as constants: in C, or an unaligned value in asm)
  data words not relocated whose value is a moved address: 2397
    (into-func 1066, unaligned targets 1043, 0x20/0x30 mirrors into code 288)
M2 OK: 7391 input sections (403 moved), same counts, nothing failing
  data words not relocated whose value is a moved address: 4089
    (s16 2063, unaligned 1256, mirror-x 376, mirrors not candidates 232, colour 58, vucode 53, ascii 34, mipscode 17)
```

What remains:

- The comparator proves the relocations that exist; it cannot prove that the rejected
  data words are not pointers (check 4). The ~300-400 words named under step 5 need
  review, ideally with typed recovery: which code reads each table and what it does with
  the word (the tracker here follows one load; struct strides and pointers passed to
  functions are not followed).
- Accepted tier-3 rows can be false (numbers): only M2 exposes them, as wrong numbers at
  run time. `SHIFT_RELOC_TIER=2` builds without them for comparison.
- The 6,369 DMA rows depend on the tag reading; the packets should be parsed properly
  (tag chains, VIF codes) before M2 is trusted in PCSX2.
- Embedded MIPS code around 0x46A000-0x46C000 (step 5).
- Overlays (`dktitle.x` ...): `scan_overlay.py` on the user's files decides whether M1/M2
  can boot at all (plan risk 1).
- Runtime: M0, then M1, then M2 in PCSX2 on the user's machine (out/shift/kh1-shift.elf,
  out/shift/m1/kh1-shift.elf, out/shift/m2/kh1-shift.elf).

## Session 13: reloc review (worker s13s4)

**Status: tier 3 is empty; M0, M1 and M2 pass** with the regenerated `data_relocs.tsv`
(9,330 accepted words, was 9,523: 193 false accepts removed, none of the earlier rejects
turned out to be a pointer). Every word is now decided by a rule with code evidence or by
a reviewed override; nothing is "accepted because nothing argues against it".

| tier | before | after | reasons after |
|---|---|---|---|
| 1 | 2,049 | 2,245 | calltab 879, func 649, ftab 367, **dma-chain 204**, jtbl 146 |
| 2 | 7,200 | 7,085 | dma 6,210, str 423, ptab 263, **typed 70**, func-s16 64, **override 24**, dref 20, stride 10, bref 1 |
| 3 | 274 | **0** | |
| x | 4,930 | 5,838 | resfile 3,954, into-func 527, unaligned 423, mirror-x 376, payload 130, s16 75, kcode 73, spawn-tmpl 68, script 59, colour 54, override-x 43, ascii 30, vucode 23, gifregs 3 |

(`resfile` words and unaligned-target noise are counted, not listed, so the file is
412 KB with 10,697 rows; shift_cmp's check 4 shows them as "not listed".)

### 1. DMA packets: walked and validated

- **Kicks.** The tracker records the chain address passed to `sceDmaSend`
  (func_00266f38, a1; chain mode CHCR 0x105), to the game's VIF1 wrapper func_00106b18
  (a0), also as a tail call (`j`), and stores to a channel's `D<n>_TADR` (0x1000x030,
  built with lui/ori; the `& 0x0FFFFFFF` mask and `move` keep the address).
  66 heads, 52 in the blob (the rest are bss buffers built at run time).
- **Walk.** From each head, tag by tag (REF/REFS: next qword; CNT/END/NEXT/CALL/RET per
  the DMAC rules), 229 tags. Chains end in END or REFE; most heads in 0x2A6000-0x2BD100
  are single REFE tags, 0x3F1A70.. are zero REFE placeholders filled at run time. One
  chain (0x48C770, kicked by func_00103c48 through D1_TADR) ends in a NEXT whose ADDR
  (D_0048CAD4) code overwrites with the run-time packet before the kick: the static
  value is a placeholder, relocating it is harmless.
- **Tag tables.** A qword is a tag when: bits 16-25, PCE and IRQ are zero; id is
  REF/REFS/REFE/NEXT/CALL; ADDR is 16-aligned inside the image; the upper 64 bits are 0
  or VIF codes; for REF*, ADDR + 16*qwc stays inside the blob and the payload's first
  qword is two VIF codes or a GIFtag (NLOOP > 0, FLG != 3); NEXT/CALL ADDR holds a tag.
  Tag-shaped qwords are grouped in runs (gap <= 0x80); a run holding an address code
  builds is a template table (code copies the tag + ADDR into its packets, e.g.
  func_001081c8 copies D_004862D0[0..1]; func_00106ed0 resets the 6 x 1024-entry
  tables at 0x46E150...; their 6,153 `REF qwc 0 -> 0x4862A0` entries point at the null
  REF there). Unreferenced tag-shaped runs (5 qwords) are not used as evidence: they
  are sizes and s16 pairs (0x400000 at 0x2C5A74, 0x3E0000...).
- **Result.** All 6,369 old `dma` rows are confirmed (140 on walked chains, 6,229 in
  referenced tag tables); 45 REFE ADDR words (were near/dref) are now typed. Payloads
  (what REF tags point at, what CNT/END/NEXT carry) are rejected (`payload`, 130 words):
  that removed 26 false accepts: GIFtag REGS 0x00535310 (17, read as a bss pointer),
  VU microcode words equal to string starts (8 `str`), a GS SCISSOR value. Rule:
  `dma-chain` tier 1, `dma` tier 2, `payload` x.

### 2. The code at 0x46A000-0x46C000 and 0x3E65E0

- **0x46AF18 (0x7A8), 0x46B6E0 (0x740), 0x46BE20 (0x28), 0x46BE90 (0x330)** are the
  libkernel kernel patches: func_0025f6d0 / func_0025fa88 / func_00260938 temporarily
  install a copy routine as syscall 0x5A (tables D_0046B6C0, D_0046BE48, D_0046C210:
  {syscall, handler}), copy each blob to **0x80074000, 0x80076000, 0x00082000,
  0x80075000** (func_0025f610 / func_0025fa30 / func_002608d0 (dest, src, size)),
  flush the caches and register the copied entry points. The code runs only there.
  Disassembled: every `lui` is 0x8007 (its own kseg0 home), 0x1000/0xB000/0xBC00 (I/O),
  0x0008, 0xFFFF or 0x7000 (scratchpad); every `j`/`jal` targets 0x8007xxxx. **No
  reference to the main image: position-independent with respect to it; nothing to
  relocate.** The syscall tables' handler words (func_0025f620 etc.) are image
  pointers and are relocated (`func`). The tracker now finds these copies itself
  (`kcode`, 73 words rejected, all were already rejected).
- The rest of 0x46A000-0x46C000 is libc/SDK data: function tables, the newlib `_reent`
  (D_0046A6D8, whose stdin/stdout/stderr and `_current_locale` are pointers, now
  accepted), malloc's self-linked bins (0x46A9D0..., `ptab`), s16 tables
  (0x46A0C8-0x46A528, rejected: two false accepts there), the InitTLB tables
  (0x46C250-0x46C4C0: EntryHi values like 0x00400000 are virtual addresses, rejected).
- **0x3E65E0 is not MIPS**: it is inside the message byte stream D_003E5ED8 that
  func_001efb18 / func_001efc10 index with u16 offsets (D_003E890E); the `mipscode`
  match was chance. Rejected as `script`.

### 3. The ambiguous remainder: new rules and evidence

| rule | evidence | words |
|---|---|---|
| `resfile` | 0x308CE0-0x348CE0 and 0x348CE0-0x350CE0 are model/motion files embedded in the data; func_00148e60 passes them to func_001763f0, which adds the base to the offsets inside (`*p += base`). The file holds offsets and numbers. **83 false accepts removed** (func 5, func-s16 11, str 15, dptr/bptr/near/run 52): in M1 the func words would have been rewritten | 3,954 |
| `script` | byte streams handed to the script VM (func_0010ef70, func_001c4198), the message parser func_001c2d20 and func_001efb18; range = base to the next address code builds; applies to ambiguous words and to lone function starts (4-byte script ops equal to func_00110218) | 59 |
| `spawn-tmpl` | u16/s16 fields (+0xC..+0x20) of the object spawn templates func_001f31a8 takes (`{callback, 0, n < 0x100, s16 xc, xe, u16 x10...}`): 0x00400200, 0x00450160...; also a func-s16 at 0x3F72F8 | 68 |
| `gifregs` | REGS field of a GIFtag with valid NLOOP/FLG/NREG before it | 3 |
| `typed` | `extern T *D_x[...]` / `(*D_x[])()` declarations in src (288 typed ranges, explicit dimensions or up to the next code-built address; s16/u16/f32 arrays with explicit size as non-pointer evidence). **0 contradictions** with the rules: no rejected word lies in a declared pointer array, no accepted word in a declared s16/f32 array | 70 |
| overrides | `tools/shift/data_reloc_overrides.tsv` (offset, end, accept/reject, reason; no values), 19 entries (10 reject, 9 accept) for typed evidence a rule cannot see: E4 byte records (D_002BCB80), mask table (D_002C5990), RGBA colour table (D_003E8E30), the two textures func_0011fbb0 uploads (0x3E9660, 2048 qwc; 0x3F1660, 64 qwc: a tier-1 func and a dref were pixels), TLB tables, s16 tables, D_003F7C48 byte records; accepts for `_reent`, InitTLB's table pointers, D_003F40F8[k].p, D_003F32C8[] / D_003F6568[] (WA *), the object descriptor D_002E2F20, a D_00370200 record, a list head | 24 accepted, 43 rejected |

Also: tracker fixes (`move`/`and` keep an address, `li` constants, `j` tail calls) and
value repeats for the s16 test now count the region rejects (otherwise removing the
resource file from the pool turned two s16 words at 0x305540 into `dptr`).

**Undecided: 0.** The colour/ascii/vucode/s16 rejects outside the typed regions were
re-read (all numbers, text, VU code or s16 pairs); sweeps for accepted words with
number-like neighbours and no pointer neighbour found only template callbacks.

### What is still open

- Tier 1/2 rows were not reviewed one by one: 649 lone `func` and 423 `str` words could
  still hide chance matches outside the regions above (every one found so far was inside
  a typed region: resource file, script, texture, s16 table, spawn template).
- Region ends that come from "the next address code builds" (scripts, resource files)
  are heuristic; the src-declaration check found no contradiction.
- The DMA payload rule trusts the tag's qwc; a template table whose static tags are
  overwritten at run time (like the NEXT at 0x48CAD0) is relocated anyway (harmless).
- Runtime remains the real test (PCSX2, M0 then M1 then M2); `SHIFT_RELOC_TIER=2` is now
  the same as 3.

## Session 13: first PCSX2 runs (user's machine, 2026-10-19)

- Booting an ELF with "Start File" (even the retail SLPS_251.98) dies with "Jump to unaligned address
  (PC 0xffffffff)": use `tools/shift/patch_iso.py ISO ELF OUT.iso` (copy of the user's disc with our ELF,
  minimal headers, in place of SLPS_251.98) and boot the ISO normally.
- **M0 boots to the title screen** from the relinked ELF.
- **M1** (code rotated) dies at boot before any picture with the same 0xffffffff jump. **M2** (data +0x1000)
  sets up 512x447 video, then "Jump to unmapped recLUT page (PC 0x70030c00)" or PC 0x00000001.
- Cause (confirmed statically): every EE overlay on the disc is linked against the main ELF by absolute
  address. `tools/shift/extract_kingdom.py` + `scan_overlay.py` on the user's disc (12 overlays, all at
  0x00F20000): dkmovie.x 137 jal / 14 %hi-%lo / 719 words; dktitle.x 292 / 85 / 219; gb.x 1584 / 138 / 5480;
  wm.x 2994 / 281 / 7390; xs_genie.x, xs_simba.x ~6,000 words each; the small ones 30-250 jal. Calls go to
  SDK and game functions (FlushCache, sprintf, sceGsSyncPath, func_0025b588 ...) and %hi/%lo to data.
  The main ELF passes no function table. So moving any referenced function or datum breaks the overlays;
  dkmovie.x runs first at boot (logo movie), which explains M1's early crash. A residual static scan of
  the main ELF found no other missed pointers (unrelocated data words that equal moved code addresses
  are numbers/bytecode; the 29 code `lui/ori` code-range values are sizes/offsets).
- Options: (1) pin every overlay-referenced function and datum at its original address (fast, constrains
  layout); (2) load-time fixups: a per-overlay relocation table generated at build time from the user's
  disc into out/ (never committed), applied by a KH1_SHIFTABLE hook after each overlay load
  (func_00120748 / func_001205f0 callers); (3) decompile the overlays as extra link units (needed for
  the Vita port eventually; ~2.4 MB of code).

## Session 13: overlay fixups (worker s13s5)

The fix for the M1/M2 boot crashes above, option (2): the overlays are patched at load time from a
table the shift build generates from the user's own disc. M0 and `make` are unchanged (`make` 6,972/6,988
byte-identical; M0 OK).

### Pieces

- `tools/shift/overlay_relocs.py` reads the user's overlays from `SHIFT_OVERLAYS` (default
  `out/overlays`, made by `extract_kingdom.py`; absent -> an empty table) and finds every reference into
  the main image 0x00100000-0x00675018:
  - code/data split by recursive descent from the entry (calls, tail `j`, jump tables bound by their
    `sltiu`, internal function pointers: strong starts `addiu sp,-N` first, then weak ones, gap fill,
    `.text` assumed contiguous);
  - `jal`/`j` fields; %hi/%lo pairs by a "must" flow analysis per function (no fall-through out of delay
    slots, `move` and `addu rX,rX,rY` keep the %hi, calls clobber caller-saved registers; a lui reaching a
    low half by two different values is not paired);
  - aligned data words outside code, classified with the tiers/rules of `find_data_relocs.py` plus
    overlay rules (resource files loaded through func_001763f0 are skipped, ASCII before strings, DMA
    words not on a walked chain are tier 3). Default `--tier 2` (tier 3 is reported only).
  Output (all under `out/shift/<mode>/`, never committed): `ovl_fixups.s`, `ovl_labels.txt`,
  `ovl_fixups.json`, `ovl_report.txt` (per overlay: fixups, mid-function targets, rejections, ambiguous).
- `ovl_fixups.s` holds no overlay bytes: per overlay {name hash (func_001200f8), size, entries, targets};
  entry = kind<<30 | target index<<18 | word offset (J26 0, WORD 1, HI16 2, LO16 3 + the word offset of
  its lui); HI16 entries before LO16; targets = `.word __dr_XXXXXXXX+off, 0xOLD` (or `D_BLOB`/`D_BSS`+off),
  so the linker supplies each new address. Header 'KHOF', version 1. Ends at `kh1_ovl_fixups_end`.
- `shift/ovl_fixup.c` (shift build only, portable C: byte-wise little-endian reads, no EE code except the
  `FlushCache` call): `kh1_ovl_apply_hash()` verifies every field holds its original address (pass 0;
  else -3, nothing written; this also refuses a second application or another disc version), then
  rewrites (jal/j field, %hi with carry, %lo against its rewritten %hi, words).
  `kh1_ovl_flush0(req)` is the EE hook.
- Hook sites, `#ifdef KH1_OVL_FIXUPS` (built only by `variants.py --define KH1_OVL_FIXUPS` for M1/M2):
  `func_00120678` (async read task, src/hand/text_00110000_h30.c) and `func_001205f0` (sync read,
  src/hand/nostrict/text_00110000_s6_04.c) call `kh1_ovl_flush0(r)` in place of their `FlushCache(0)`:
  same size (the variant only swaps `move a0,zero` for `move a0,sN` and the jal target), so no
  function grows and M1's 12 bytes of rotation slack are untouched. It runs after the data is in memory,
  before `FlushCache(2)` and before any code jumps to it.
- Identification: a CD request carries no name. The hook looks up KINGDOM.IDX in memory
  (`D_004E4A00[D_002C5C30]`, {hash, flags, LSN, size}) for the entry with the request's size and LSN
  (or LSN + `D_004F3200`, the HDD path) and applies the table entry with that hash. Files not in the table
  (all non-overlays) cost one index scan. `kh1_ovl_status[4]` = {hash, result, entries, loads fixed}.
- Link: `shift_ld.py --ovl-fixups --ovl-hook --ovl-labels` puts both objects in `.data` after the blob
  (`__ovl_fixup_start..__ovl_fixup_end`), then pads so `_edata`..`D_BSS` keeps its 0x30 distance (crt0
  clears from `D_BSS - 0x30`, which must not reach the table). M1: table 0xaf48 bytes at 0x00494640, hook
  at 0x00494548; .bss/$gp/_end move up by 0xb600 (`_end` 0x00680618; heap end 0x0068a618 stays below the
  fixed buffers at 0x006A0000). M2: same, +0x1000.
- `shift_cmp.py` keys variant objects as the objects they replace, and accepts exactly the hook's
  `jal FlushCache(0)` -> `jal kh1_ovl_flush0(req)` (2 sites); `Links` is shared with the proof.
- `tools/shift/ovl_proof.py` (run by `make shift` for M1/M2): reads the table back from the linked ELF,
  applies it with a Python model and with the real `ovl_fixup.c` compiled for the host
  (`ovl_hook_host.c`, `-DKH1_OVL_HOST`), requires both to agree, then checks every patched field through
  the M0 -> new address map (LO16 as the full pair, HI16 through its LO16s, J26 in its 256 MB segment),
  every other word unchanged, a second application refused, an unknown name ignored, and one
  `jal kh1_ovl_flush0` in each loader function.

### Counts (user's disc, 12 overlays, all at 0x00F20000)

| overlay | jal | j | hi/lo pairs | words | mid-fn | ambiguous | fixup entries |
|---|---|---|---|---|---|---|---|
| dkmovie.x | 136 | 14 | 13 | 0 | 4 | 6 | 176 |
| dktitle.x | 292 | 13 | 99 | 0 | 13 | 5 | 493 |
| gb.x | 1584 | 42 | 148 | 0 | 132 | 18 | 1950 |
| wm.x | 2994 | 94 | 296 | 0 | 157 | 34 | 3698 |
| xl_limit.x | 245 | 19 | 54 | 0 | 0 | 0 | 376 |
| xs_bambi.x | 33 | 3 | 9 | 0 | 0 | 0 | 54 |
| xs_dh_break.x | 43 | 3 | 11 | 0 | 0 | 3 | 70 |
| xs_dumbo.x | 176 | 10 | 33 | 0 | 0 | 0 | 252 |
| xs_genie.x | 150 | 12 | 23 | 0 | 0 | 0 | 208 |
| xs_mushu.x | 77 | 4 | 20 | 0 | 0 | 0 | 125 |
| xs_simba.x | 120 | 8 | 27 | 0 | 0 | 1 | 180 |
| xs_tink.x | 52 | 4 | 9 | 0 | 0 | 0 | 76 |
| total | 5902 | 226 | 742 | 0 | 306 | 67 | 7658 |

- No data word is accepted at tier <= 2. The ~19,400 rejected words are almost all inside resource
  files embedded in the overlays (xs_genie/xs_simba/gb/wm); the earlier scan's thousands of "words" were
  these plus code.
- Mid-function targets: all 306 are `func_0024e1d0+0x298` (0x0024E468), a second entry point in the asm
  blob text_0024e0a4.s; they map through the containing function + offset.
- Ambiguous (67, not fixed): `lui/ori` code-range constants (GS register values etc.), `lui` 0x0010 / 0x0020
  / 0x0044 / 0x0050 with no low half (sizes), and tier-3 words in wm.x/gb.x (`dptr-run`/`bptr`: colours,
  s16 records, bytes, text). Listed in `ovl_report.txt`.
- What the overlays read from the main ELF by fixed address: only through the fixed fields above (jal/j to
  SDK and game functions, %hi/%lo to data and bss). No overlay reads a table of main-ELF pointers that
  the analysis found.

### Static proof

M1 (text rotated) and M2 (data +0x1000) both: `shift_cmp` OK with 2 accepted hook sites; overlay fixups
OK for all 12 overlays (C hook = model, every patched field maps back, all other words unchanged).
With no overlays (`SHIFT_OVERLAYS` empty or absent) the table is empty and the hook is a no-op.

### Unproven (to check in PCSX2)

- References the analysis missed: code not reached by descent (only via pointers it did not find),
  the 67 ambiguous items, tier-3 words, pointers built arithmetically. Any of these breaks only if its
  target moved (M2 moves data only).
- The runtime identification (index lookup by LSN/size) and that every overlay load goes through
  func_00120678 or func_001205f0; the HDD path (LSN - D_004F3200) is not exercised on PCSX2 by default.
- The base 0x00F20000 is assumed for every overlay (true on this disc; a different load address would
  fail verification, -3, and leave the file unpatched).
- M1/M2 move .bss, $gp and `_end` up by the table (+0xb600): anything that assumes bss addresses (save
  states, cheats) or a heap end below 0x0068a618 is not covered by the static check.
- Overlay code that runs before the first load completes (none expected) or overlays reloaded over
  themselves without a fresh read (pass 0 refuses a second patch, so a reload from disc is fine).

## Session 13: PCSX2 runs with overlay fixups (2026-10-19)

M1 and M2 rebuilt at 3f7cff4, patched into copies of the user's disc with
`tools/shift/patch_iso.py` (minimal ELF: M1 3,798,760 B, M2 3,802,856 B, slot 3,805,184 B,
so about 2-6 KB of headroom is left; growth beyond that needs another way onto the disc).

| build | boot / logos | title | New Game → opening movie → Station of Awakening |
|---|---|---|---|
| M1 (code moved) | ok (was: PC 0xffffffff at boot) | ok | ok |
| M2 (data moved) | ok | ok | ok |

Not exercised yet: anything after the first 3D scene (gb.x, wm.x, xl_limit.x, xs_*.x),
Load, Special Movie, and the HDD path.

## Session 14: runtime in PCSX2, and a wrong-relocation bug (2026-10-19)

Shay's save (End of the World, LV100) was imported into a PCSX2 memory card with `mymcplus`
(`.max` import); PCSX2's memory-card folder points at `Downloads/kh1-test/memcards` on that machine.

| what | M1 | M2 |
|---|---|---|
| title, Load (incl. unformatted-card message), Special Movie | ok | ok (title, Load) |
| New Game, settings, opening movie, Dive to the Heart | ok | not re-run |
| load save at End of the World, magic (Firaga) | ok | ok |
| save to the memory card (file 05), and load that file in M0 | ok | — |
| world map (wm.x), gummi flight (gb.x) and back, warp drive | ok | ok |
| Halloween Town, Guillotine Gate landing | **broken, fixed below** | **broken, fixed below** |

Summons (xs_*.x) and xl_limit.x are still unexercised at runtime: KH1 only allows summons with
enemies present (M0 refuses them in the same spots), and none were in reach of the landing points.

### The Halloween Town bug: fake %lo relocations from delay-slot flow

Symptom: M1 and M2 drew large flat untextured polygons and no characters at the Halloween Town
landing (Sora missing at the End of the World save point too); M0 fine, same camera.

Bisected at runtime with `shift_ld.py --bss-pad N` (experiment only: M0 layout, nothing moved,
.bss/$gp/`_end` pushed up by N inside the NOLOAD .bss):

- N = 0xb600 (what M1/M2's overlay table adds): broken exactly like M1/M2;
- N = 0x10000: identical to M0.

So something depended on bss addresses modulo 64 KB: a %lo. Cause in `tools/asm_export.py`
`flow_pairs`: every delay slot also got the ordinary fall-through edge, so a `lui` in the delay
slot of a branch-likely (executed only when taken) reached the not-taken path, and a plain
`lw $v0,0($a0)` (a struct load) became `%lo(D_00570000)`:

```
00167350 bltzl $v0,.L001673FC
00167354  lui $a0,%hi(...)        <- runs only when taken
...
0016737C lw $v0,0($a0)            <- $a0 = *(s4), not the lui; was R_MIPS_LO16 D_00570000
```

Fix: a delay slot's successors come only from its branch (taken target; plus k+2 for an
ordinary conditional branch). Regenerated `shift/unmatched/`: 4 fake relocations gone in
func_00166570, func_001636d0 (both .bss, the runtime bug) and func_0010d470 (data, would have
broken M2 elsewhere); the lui in func_00166570 now pairs with its real low half (D_00574F20).
Fixed M1 and M2 render Halloween Town identically to M0 (same frame).

Lesson: `shift_cmp.py` and `ovl_proof.py` check that every relocated field maps back, so they
cannot see a relocation that is wrong but self-consistent. Only a runtime run with a shift that is
not a multiple of 64 KB (or a register-flow check per LO16) catches it. `overlay_relocs.py` already
had the correct delay-slot rule.

### Overlay ambiguous fields: reviewed (session 14)

All 67 `ambiguous` entries in `ovl_report.txt` (user's disc) were read in context; none is an
address, so leaving them unpatched is correct:

- `lui/ori` "code-range" values (14): buffer sizes and offsets added to an allocated base
  (dkmovie.x 0x003AB87F, 0x00123800, 0x00124800, 0x00162780, 0x00286F80, all `addu reg, v0` or
  stored as sizes), 64-bit GIF tag / GS register words built with `dsll32` (dktitle.x, wm.x
  0x002A4000), colours with an alpha byte or'ed in after `sll 0x18` (gb.x/wm.x 0x002747B8,
  wm.x 0x004D3F28), unaligned odd values (0x00531531, 0x00535310, 0x00193C7F, 0x00323280),
  and a VIF/GIF flag word (xs_dh_break.x 0x00100100).
- `lui` 0x0010/0x0020/0x0044/0x0050 with no low half (24): allocation sizes passed to
  func_001bb500 (`lui a0,0x44; li a1,128`), bit masks for 64-bit GS register fields next to
  `0xf0ffffff`/`0xfff0ffff` masks, and `0x500000 - s0` size arithmetic in dkmovie.x.
- tier-3 data words in gb.x/wm.x (27): RGB colour tables (0x00346900 next to 0x00301010,
  0x00101010), s16 pairs inside records whose neighbours are overlay-internal pointers
  (0x00400140, 0x00510050), byte tables (0x00303600, 0x002F2E00, 0x00393938 ...), and ASCII
  (0x00303630 = "060\0" inside a string list). xs_dh_break.x's two words are inside
  compressed/texture bytes.

### Disc scan for code pointers (session 14)

All 3,326 KINGDOM.IDX entries (KINGDOM.IDX at LBA 2450, 57,344 bytes; base LBA 282 = SYSTEM.CNF)
were decompressed and scanned for aligned words equal to a main-ELF function start and for `jal`
words to one. Only the 12 known overlays and copies of the main ELF hold significant `jal`
counts: there is no other code file on the disc. Function-pointer hits in data files are round
values (noise). So a disc file holding main-ELF code addresses is not a known risk for M1. (A C
scanner was used; pure Python was too slow for one 180 s shell call on the user's machine.)

### Lone function and string relocations: reviewed (session 14)

All 1,136 lone-pointer rows of `data_relocs.tsv` were dumped with their context (649 `func`, 64
`func-s16`, 423 `str`; the dump: target, the address code builds that the word belongs to and the
functions that build it, the next code-built address, the 6 words on each side with their reasons,
the target's direct `jal` count, for strings the text). Filters picked 208 suspects (no accepted
pointer next to it, number-like neighbours, a target that code also calls directly, short or
non-alphanumeric strings); all 208 were read.

- **Rejected (e07f611, 10 words, 3 override ranges):** chance matches inside typed byte/u16
  records: the glyph table D_003E4658 (`{u16 code, f2, f4; u8 w, f7}`, 5 func + 3 ftab), the
  SmG digit-glyph table D_003E9110 (1), the H20 header/offset data D_00308874 (1).
- **Confirmed (the other 198 suspects), by kind:**
  - object/menu templates 0x3F3200-0x3F7EA0 (func_001f31a8's WA): a callback at +0x0 or +0x30
    whose target nothing calls directly (`jal` count 0), next to `{0, 4, s16 x, y...}` fields;
    the `str` hits there are WA* arrays (D_003F32C8[] ...) whose target template starts with
    printable bytes;
  - state tables 0x35BD50-0x35C408 (func_00172010, func_00172d90, func_00173740 ...): 16-byte
    records `{0, n, flags, handler}`; handlers are reached only through the table (or are the
    shared default func_0016b670);
  - the libkernel syscall tables at 0x46AF04, 0x46B6C4, 0x46BE4C, 0x46C214 (session 13 kcode);
  - string tables: the 2-character names at 0x2BCC28 (func_00112270), the overlay name
    "xs_dh_break.x" at 0x425BC0 next to its handler table, a `{.., "...x", ftab}` record at
    0x304B44.
- `data_relocs.tsv` is unchanged beyond e07f611 (642 func, 64 func-s16, 423 str accepted). The
  dump tool was a throwaway; the rule set did not change.

## Session 14: M12, SHIFT_DRAFTS and a LO16 check

### M12: code rotated and data/bss moved (`make shift SHIFT_MODE=m12`)

`shift_ld.py --mode m12`: the text is rotated like M1 and `.data` is placed at
`blob_start + --data-shift` (0x1000) like M2, so every function, every data byte, `_gp`, .bss and
`_end` move (bss by 0xc600 with the overlay table: not a multiple of 64 KB). The rotation point is
chosen against the moved data start, so it differs from M1's (0x262A00, 0x10264 bytes to the
front). Output `out/shift/m12/`.

```
M12 OK: 7391 input sections (7391 moved), relocated fields checked: HI16/LO16 17071, KH1_OVL_FIXUPS hook 2, R_MIPS_26 21416, R_MIPS_32 11994
  entry 0x00100008 -> 0x00110288 ok; _gp 0x00494050 -> 0x004a0650, D_BSS 0x00494080 -> 0x004a0680
M12 overlay fixups OK: 12 overlays, table 0xaf48 bytes at 0x00495640 ...
```

Also: a function that grows (KH1_SHIFTABLE variant, or a draft) now costs exactly what it pushes
the next function by (`ALIGN(64) + start % 64`), not a flat 64 bytes; m2 refuses growth larger
than `--data-shift`. Runtime: not run yet (PCSX2 is on the user's machine).

### SHIFT_DRAFTS (`make shift SHIFT_MODE=m12 SHIFT_DRAFTS=1`)

Links the near-miss C drafts listed in `shift/drafts.tsv` (16 rows: name, C file under
nonmatchings/, the src/ directory whose compile rule builds it, LCS words its header claims) in
place of their `shift/unmatched/` asm exports, into `out/shift/<mode>-drafts/`. Never matched
code and never counted: `make` does not build them, and the result is a static word diff, not a
behaviour claim (the earlier draft of this table had a `static: equiv` column; it was not backed
by a review and was dropped).

- `tools/shift/drafts.py build` compiles each draft with the exact `kh1tool gen` rule of its
  mode (flags from kh1.toml), checks one `.text.<name>` and no data, prints the
  `--draft-obj NAME=OBJ` arguments; a failure keeps the asm export (`compile.tsv`).
- `shift_ld.py --draft-obj`: the draft's `.text.<name>` takes the asm export's place in the
  layout (a longer draft pushes later code by multiples of 64, a shorter one leaves padding); its
  `.rodata*` (jump tables) goes after the blob (`__draft_rodata_start`); an asm object whose
  functions are all drafted is left out, a partly drafted one has those sections discarded. A
  draft with an undefined name nothing defines and no address is refused per function
  (`no-link`, asm export kept). The asm version's jump tables stay in the blob, relocated
  against the draft's start (self-consistent, unused). Needs a moved mode; with m1 the text has
  no room before the fixed data once a draft grows, so use m2 or m12.
- `shift_cmp.py` maps a drafted function as one piece (start to start) and skips its bytes;
  everything else is checked as usual. `ovl_proof.py` and the LO16 check run as usual.
- `drafts.py report` (run by make): per function, words of the asm export vs the draft with
  relocated fields masked (difflib LCS, so a little above the headers' true-DP counts), the same
  over instruction kinds only (registers and immediates ignored), and whether the `jal`/`j`
  targets are the same (mapped M0 -> NEW).

Result (m12, all 16 compile and link; the text grows by 0x140, from func_0010d470 +0x98,
func_00110618 +0x10, func_00125240 +4; func_00166570 is 8 bytes shorter):

| function | orig words | draft words | off | kinds off | calls |
|---|---|---|---|---|---|
| func_0010d470 | 992 | 1030 | 239 | 91 | same 22 |
| func_00110618 | 268 | 272 | 98 | 59 | same 10 |
| func_00125240 | 45 | 46 | 5 | 2 | same 5 |
| func_001636d0 | 1062 | 1062 | 416 | 125 | same 84 |
| func_00166570 | 1044 | 1042 | 22 | 6 | same 75 |
| func_00192958 | 300 | 300 | 17 | 1 | same 7 |
| func_001c62a0 | 287 | 287 | 58 | 9 | same 1 |
| func_001cfc28 | 66 | 66 | 1 | 1 | same 2 |
| func_001eddc0 | 95 | 95 | 2 | 2 | same 0 |
| func_001f18e8 | 322 | 322 | 2 | 0 | same 3 |
| func_001f1fc8 | 409 | 409 | 2 | 1 | same 14 |
| func_001f2630 | 264 | 264 | 1 | 0 | same 15 |
| func_001fd858 | 477 | 477 | 1 | 1 | same 5 |
| func_00200e28 | 389 | 389 | 24 | 16 | same 11 |
| func_0021e120 | 250 | 250 | 3 | 2 | same 14 |
| sceGsDefDispEnv | 221 | 221 | 9 | 6 | same 4 |

`M12-DRAFTS OK` (everything but the 16 drafted functions maps back), overlay fixups OK, LO16
check 0. A "kinds off" of 0-2 means the draft differs in registers/scheduling only; the larger
ones (0010d470, 00110618, 001636d0, 00200e28) differ in code shape and are the ones to run at
runtime first if drafts are ever tried in PCSX2. Several drafts are FLAGGED in their headers
(dead tests kept for matching); none of that is checked here.

### LO16 base check (`tools/shift/lo16_check.py`, run by every `make shift`)

The 22ec674 bug (a fake `%lo` on a struct load) is invisible to shift_cmp and ovl_proof: the
field maps back because the relocation itself is what moves it. The new check reads the linked
ELF (`ld -q` relocations) and, for every R_MIPS_LO16, walks the control flow backwards along every
path until the base register is written. Each path must end in a `lui` with an R_MIPS_HI16
(passing through `addu rX,rX,rY`, `move`, and a stack spill/restore of the register); the
function entry, a call that clobbers a caller-saved base, any other write, or an unrelocated
lui is a finding, and `make shift` fails on it. Control flow as in the fixed `flow_pairs`
(delay slots only from their branch, likely branches skip the slot when not taken), calls return
to k+2 with caller-saved registers clobbered, and each `jr` goes to the entries of its own jump
table (the `lui/lw %lo(T)` before it; all in-function R_MIPS_32 targets if it is not found).
Unreachable words (the nop after `b`) are not paths. About 3.5 s for the whole link.

- Current tree (m0, m1, m2, m12, m12-drafts): 17,071 LO16 fields (17,074 with drafts),
  **0 findings**.
- Sensitivity: with the `shift/unmatched/` exports from before 22ec674 it reports exactly the
  4 fake relocations of that fix (func_0010d470 x2: `$v0` clobbered by a call; func_001636d0 and
  func_00166570: `$a0` written by a load on some path).
- Before the per-table `jr` edges and the spill rule it had 1,248 and then 13 false positives in
  compiled C (state machines whose `switch` re-dispatches through a second table; libc
  functions that spill a %hi with `sq`/`lq`); both were checker imprecision, not bad relocations.
- Not covered: the HI16 side (a lui whose low halves are wrong is caught only through them), and
  the overlay fixups' own %hi/%lo pairing (overlay_relocs.py, already the correct delay-slot rule).

### Disc room for a bigger ELF

`patch_iso.py` overwrites SLPS_251.98 in place, so the ELF must fit the retail file's sectors:
3,805,184 bytes. Minimal ELF sizes now: M0 3,752,168 (53 KB left), M1 3,798,760 (6.4 KB), M2 and
M12 3,802,856 (2.3 KB), M12 with drafts 3,803,240 (1.9 KB). M1 adds the overlay table and hook
(0xb600 bytes with alignment); M2/M12 add the 0x1000 data shift as file-backed zeros. Options, roughly
in order of effort:

1. **Append the ELF at the end of the image** (`patch_iso.py --append`, written and booted in session 15; see "Session 15" below): put the file in
   new sectors after the last one, point its ISO 9660 directory record (LBA and size, both byte
   orders) there, and raise the PVD volume space size. No size limit for PCSX2; a burned DVD-5
   still has room (the image is about 3.5 GB). If the disc also carries UDF descriptors, their
   file entry for SLPS_251.98 must be updated too or stay unused (the PS2 BIOS and PCSX2 read ISO
   9660). Recommended first: simplest, and it removes the limit for every later build.
2. **Several PT_LOAD segments** (in `minimal_elf`): split at the long zero runs of the data
   (17 runs of >= 4 KB, 1,054,481 bytes in all; the largest 0x4B2CB at 0x37A375) and at the M2
   gap, each run becoming the `memsz - filesz` tail of a segment. Saves up to ~1 MB with no game
   change, **if** the loader zero-fills each segment's tail: PCSX2's fast-boot loader and the
   BIOS `LoadExecPS2` both need checking (crt0 only clears .bss). Test with M0 first.
3. **Smaller overlay table**: 7,658 entries x 4 bytes plus 529 targets x 8 bytes. Dropping the
   per-target "old address" word (check the overlay by its name hash and size instead) and
   delta-encoding word offsets as u16 would roughly halve 44 KB. Or move the table to its own
   file read at boot.
4. **A free gap inside the image**: list every ISO 9660 extent and look for unused sector runs
   (padding before KINGDOM.IMG, dummy files); size unknown until scanned on the user's disc.
5. **A loader stub**: a small ELF in the slot reads the real ELF (from an appended file, or
   compressed: M1 compresses to about 1.05 MB with zlib -9) and jumps to it. Needs CD/IOP calls
   in the stub; the right answer for real hardware with a size budget, the most work.

Rotation slack and M2's 0x1000 are not a budget: growth in code or data comes out of the same
disc slot, so option 1 (for testing) or 2 (if it boots) should come before any larger change.

## Session 15: M12, drafts and an appended ELF in PCSX2 (2026-10-19)

Same setup as session 14 (Shay's save, PCSX2 2.8.2 on the Mac, memory cards in
`Downloads/kh1-test/memcards`). Test ISOs now: `KH1_M0.iso`, `KH1_M12.iso` (M12 in the retail slot),
`KH1_BIG.iso` (appended ELF; holds whatever was patched last, the drafts build at the end of the session).

| what | M12 | M12, data +0x21000 (3.93 MB, appended) | M12 + SHIFT_DRAFTS (appended) |
|---|---|---|---|
| boot, title, Load, save at End of the World | ok | ok | ok |
| area change (End of the World) | ok | — | ok |
| world map (wm.x), warp drive, landing menu | ok | ok | ok |
| Agrabah (storage room, Main Street, Plaza), fights, pots | ok | — | ok |
| summon in a fight | ok (Simba, xs_simba.x) | — | ok (Genie, xs_genie.x) |
| game over and Continue | ok | — | ok |
| Halloween Town, Guillotine Square landing | — | ok (textured, characters) | — |

Not run: Trinity Limit (`xl_limit.x` is also loaded by func_00158ec8 whenever a field allows it, so
its load path ran in every field above; Shay judged the rest enough). Traverse Town was not reached
(the world-map cursor would not go past the warp holes left of Agrabah with keyboard input; it needs
a diagonal or another route). The drafts build was the one with the session 14 00125240 draft (5 words,
184 bytes); `shift/drafts.tsv` now points at the 3-word session 15 draft (180 bytes), which links and
passes the static checks but was not booted.

Summons need enemies on screen and Donald/Goofy kill Agrabah's small Heartless within a second, and
the party menu only swaps members (no solo party). What worked: land at the storage room, walk out
into Main Street and open Magic > Summon in the same batch as the walk, before the party engages.

### `patch_iso.py --append` (disc room, option 1)

The ELF goes in new sectors after the last sector of the volume: the ISO 9660 directory record of
SLPS_251.98 gets the new LBA and size (both byte orders), the PVD volume space size (offset 80, both
byte orders) grows to cover it, and the UDF anchor that sat in the last sector (the disc is a UDF
bridge: anchors at 256 and N-1) is copied to the new last sector. The UDF side is not otherwise
changed (its file entry still points at the retail slot and its partition ends at the old end); the
BIOS and PCSX2 boot through ISO 9660. The retail slot is zeroed, so a working boot can only have read
the appended copy. Patching an already-appended OUT reuses the same sectors and truncates the image to
the new end; patching without `--append` puts an appended OUT back into the retail slot (volume size
and length restored). Checked in the container with a genisoimage `-udf` image (isoinfo extracts the
appended file byte-identical; append, re-append, back to slot, append again), and in PCSX2 with
KH1_BIG.iso: a 3,933,928-byte M12 (data and bss moved by 0x21000, `make shift SHIFT_MODE=m12
SHIFT_DATA_SHIFT=0x21000`, 128 KB over the slot) boots and plays with the retail slot zeroed.

`SHIFT_DATA_SHIFT` (Makefile, m2/m12; default 0x1000, output dir gets `-ds<N>`) is how to make a big
test ELF. The real growth (code from C rewrites, bigger tables) can now come from anywhere: the slot
limit is gone for PCSX2 and for a burned DVD-5 (about 3.5 GB used). Options 2-5 above are only needed
for a fixed-size disc layout.

## Session 16: Phase 4 begins (data defined in C)

The goal of phase 4: gameplay C stops naming data by address (`extern u8 D_006489E0[]`) and owns it
instead, so data can move freely and, later, compile for a host. `make` stays byte-identical.

### Mechanism

- **`-fdata-sections -fno-common`** on every C object (kh1tool gen), except paths listed in
  `kh1.toml [toolchain] data_sections_skip` (`src/sdk/`: newlib's static const tables change layout
  under it). Each global gets its own `.data.<name>` section; with `-fno-common` zero-initialised
  globals also land in `.data.<name>`, not `.comm`. `static` variables still go to plain `.bss` and
  cannot be placed; the link-script step refuses any stray .data/.bss/.sdata/.sbss.
- **Placement**: a variable named `D_XXXXXXXX` (or listed in functions.tsv) is placed at that address
  by the matching link script (`.d_ADDR ADDR : { KEEP(obj(.data.name)) }`; out/gen/data.tsv). A
  variable in the data range is written into the image by `patch` and checked by `verify` ("DATA
  MISMATCH"); one in the bss range must be all zero (patch refuses otherwise). Overlaps, addresses
  outside the image and unnamed variables are errors.
- **Shiftable**: shift_ld.py places data-range variables into the matching hole of the data blob and
  bss-range ones at `D_BSS + off`, so M0/M1/M2/M12 are unchanged.
- **`SHIFT_FLOAT=1`** (m1/m2/m12; output dir gets `-float`): C-defined variables leave the original
  layout. A floated data variable leaves a gap in the blob and is placed after it
  (`__float_data_start`); floated bss goes after the original bss (`__float_bss_start`), and
  `D_00675018` (the old `_end`) becomes `_end`. shift_ld refuses if a blob pointer or another D_ name
  lands inside a floated variable. shift_cmp maps the floated pieces through the inverse map, plus
  `_end`.
- **`tools/shift/data_owners.py`** (needs `make shift`; ~80 s): per D_ name the region, extent to the
  next anchor, reach, referencing files, blob pointers in, and a verdict (`single`, `single+p`,
  `shared`); `--file SRC` lists one file's names. Writes out/shift/data_owners.tsv.

### First conversions

- `src/hand/nostrict/text_00230000_s6_24.c` (the menu objects func_0023b570 builds): 62 single-owner
  bss buffers became definitions (`u8 D_006489E0[0x240] ALIGNED(16);`, sizes from the extent).
  Shared names and the game-data tables it reads stay extern.
- `src/hand/text_00110000_s9_w8.c`: the two collision-query handler tables `D_002BD178` and
  `D_002BD1A8` (11 function pointers each) are now initialised C arrays.
- Link-script: "64 variables (2 data, 62 bss)". `make`: byte-identical. M0 and M12: OK.
  M12 + `SHIFT_FLOAT=1`: compare OK, overlay fixups OK, LO16 0; `D_002BD178` moved to 0x495050,
  `D_006489E0` to 0x681620, `_end` 0x6889A0.

**Runtime** (PCSX2 2.8.2, `KH1_BIG.iso` with the M12-float ELF appended): boots, title, loads the
End of the World save, walks, main menu, Items and Status all work. func_0023b570 runs from the menu
init func_00236f18 at boot, and func_00116368 (the tables' user) is the collision query every walk
step calls, so both conversions ran.

### Counts (data_owners.py, session 16)

| region | single | single+p | shared |
| --- | ---: | ---: | ---: |
| bss | 399 | 0 | 839 |
| data | 1,262 | 36 | 842 |

50 of the single-owner data names are pointer-only tables (every word a code or data address), e.g.
`D_00469FD8`, `D_00469FF8`, `D_0046A018` (text_00240000_h75.c), `D_0036245C`, `D_003C5898`.

### Plan for the rest

1. **Single-owner bss (399)** -> definitions in the owning file, sizes from the extent column
   (check reach <= extent; round to the element type). Mechanical; batch per file, `make` after each.
2. **Pointer-only single-owner tables (50)** -> initialised arrays of function/data pointers in their
   owner, as with D_002BD178. Data pointers in them name other D_ symbols, which is fine.
3. **Shared names** -> one definition in a common module per subsystem (`src/data/*.c`) plus a
   header declaration, so every user includes the same type. Start with the bss ones (no bytes).
4. **Numeric tables and strings (game data)** stay out of the repo. They become per-symbol pieces cut
   from the extracted blob at build time (`.incbin` of `out/extract/data/<name>.bin`, like the blob
   today), so each can float on its own.
5. **Float per piece**: once a range has no anchors left inside it, SHIFT_FLOAT moves it; the data
   relocations in data_relocs.tsv that point into it are retargeted at the new symbol instead of
   `D_BLOB+x` / `D_BSS+x`.
6. `single+p` (36): define in place first; float only after step 5 retargets their blob pointers.

The end state is a link where no `D_BLOB`/`D_BSS` offset is left, which is also what a host build
needs.

## Session 17: Phase 4 steps 1-3 (data defined in C)

`make` stays byte-identical throughout. 642 variables are now C definitions (606 bss, 36 data); the
link script places each at its address.

### Tools

- **`tools/shift/define_vars.py`** (step 1): single-owner bss `extern` -> definition in the owner.
  Sizes come from the compiler (a probe copy of the file with `int __kh1sz_N = sizeof(...)`), checked
  against the extent: `exact`, `fill` (`T D[]` filled to the extent), `pad` (a scalar nobody takes the
  address of; the rest of the extent is padding), else `manual`. `ALIGNED(min(lowbit(addr), 16, or 64
  for objects of 64+ bytes))`. 205 automatic, 19 m2c `M2C_UNK D[n]` buffers, 14 menu sprite packets
  (0x160-byte objects: `u8 tail[0x160 - 0xE8]` added to the local packet type), 3 by hand. About 25
  stay manual (sizeof larger than the extent, `__asm__` label tricks in s6_10, indexed types).
- **`tools/shift/define_ptr_tables.py`** (step 2): single-owner tables whose every word is an accepted
  pointer (data_relocs.tsv) or zero become initialised arrays, appended at the end of the owner (where
  every function is declared); the extern stays where it was. 34 tables plus the session 16 pair.
- **`tools/shift/define_shared.py`** (step 3): a shared bss name that every user declares with the same
  basic type gets one definition in `src/data/bss_XXXX.c` (XXXX = address bits 31..16) and one
  declaration in `include/data/bss_XXXX.h`. Users include the header and keep their own identical
  extern for now, so the compiler checks them against the definition. 306 names; 490 left (users
  disagree on the type: 369; struct/typedef types; size vs extent).
- **`tools/shift/cover_check.py`**: lists C-defined variables that sit inside another declared object,
  or right after a name no C declaration sizes. Run by every SHIFT_FLOAT build; shift_ld keeps those in
  place (`--float-skip-file`). 48 today.

### Hazards found (all keep `make` identical; they only matter when data moves)

- **gcc alignment**: an array at an address that is not 8-aligned, with a size that is not a multiple
  of 8, gets `.align 3` and a padded section: placement fails. Both tools skip those.
- **Known alignment changes code**: `ALIGNED(8)` on `D_0062A228` turned a builtin `strcpy` into ld/sd
  moves (two functions stopped matching). That one has no ALIGNED.
- **Declaration order changes code**: including `data/bss_0055.h` at the top of text_00150000_h58.c
  (declaring D_005516C0 earlier) changed how func_0015b060 forms the D_00551970 address; that file
  includes it at the end.
- **Overlay-shared**: `D_0046A6A8` is written by dktitle.x; floated, the overlay fixup proof fails.
  Stays extern.
- **Fields named on their own** (more in "Session 18"): `D_005759A4`/`D_005759A6` are fields x64/x66 of the camera struct at
  `D_00575940` (another file declares `Cam`, sizeof 0x68). Defined in C they are fine, floated they leave
  the struct. Likewise D_0046A6A4 inside D_0046A688, D_0057590C inside D_00575900 (20 more:
  cover_check.py). This is what hung the bss float at boot.
- **Indexed past the extent**: D_00425BC0 (func_002335d8 indexes it; D_00425BC4, named by
  text_001d0000.c, is its next entry) and the D_00575030/50/60 arrays stay extern.
- **Arena**: crt0 calls SetupHeap(_end, 0xA000), and the game's fixed arenas start at 0x006A0000
  (`func_0014a090`), then 0x720000, 0x820000, 0x9A0000, 0xF20000 (overlays), 0xFE0000, 0x1CE0000.
  Floating all bss pushed `_end` to 0x6C7400 and hung at boot. shift_cmp now fails when `_end` passes
  0x6A0000 and warns when `_end + 0xA000` does.

### Float build changes

- shift_ld: floated pieces align to `min(lowbit(addr), 64)`; C bss variables with no other name between
  them float as one block at the same offsets (code walks from one menu object into the next); a
  budget of bss (`SHIFT_FLOAT_BSS_BUDGET`, smallest runs first) floats, the rest stays at its D_BSS
  offset; `SHIFT_FLOAT_SKIP` names stay in place.
- shift_cmp accepts a HI16/LO16 field up to 0x40 outside a floated piece with the same delta
  (`D_003F31D0[x-1]` in h70.c).
- **`SHIFT_FLOAT_BSS_BUDGET` defaults to 0.** With bss floated (budget 0x10000, covered names kept) the
  game runs at 60 fps but never draws the title: more hidden struct fields to find. Bisect with
  `SHIFT_FLOAT_BSS_BUDGET=0x400` (17 small names) and `SHIFT_FLOAT_SKIP`.

### Runtime (PCSX2, KH1_BIG.iso with the M12-float ELF appended)

- Build with 9 floated tables, no bss: title, save load in End of the World, walking, main menu, Items,
  Status, attacks and Fire, the world map (gummi overlay) and a warp to Halloween Town.
- Final build (35 tables floated, bss in place, covered names kept): title, save load, walk, attack,
  main menu.
- **Boot tests can mislead**: one build showed "No Image" after 30 s and booted on a second try; wait
  45 s and retry a hang once before believing it. Check which ELF is really on the device
  (`shasum`): a local file of the same name had been rebuilt, and the bisection compared against it.

## Session 18: bss floats again (SHIFT_FLOAT_BSS_BUDGET ?= 0x10000)

`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` floats up to 0x10000 bytes of bss by default again (155 runs,
`_end` 0x68f4c4). In PCSX2 (KH1_BIG.iso, ELF appended) it reaches the title, loads the End of the World
save, walks, attacks, casts, and opens the main menu. No fight yet: there were no enemies near that save
point. `make` stays byte-identical.

### What hung the title (three new hazard patterns)

- **Displacement from another object's base.** `addiu a0,%lo(D_X)` then `lw 0x4(a0)` reaches a name
  that no relocation mentions (D_00575014 inside D_00575010; D_00656254/78/9C, the 0x24-byte entries of
  D_00656230). `tools/shift/reach_check.py` runs a constant propagation over every function's CFG
  (original ELF, plus the overlays) and also follows call arguments: each function's reach from its
  argument registers, propagated through callees, is applied at every call site that passes an address.
  memcpy, memset and the pool init func_0011efa8 are checked with their byte counts.
- **An array indexed past its declared end into the next name.** `D_00550400` (0x48-byte entries) is
  walked for i < 64, and D_005512A0 is entries 52..63 under its own name. reach_check keeps every floated
  name that is the next anchor after an indexed base in another piece (`idx-next`). That also covers
  pointer walks: a register that holds different addresses on two paths into a join becomes base +
  unknown. This rule is conservative and keeps about 110 names in place.
- **IOP-written blocks.** The sound driver's RPC status block `D_0063D640` (0x2000 bytes, its address is
  sent to the IOP in text_001e0000_h68.c) is written by DMA. D_0063F248 (+0x1c08) and D_0063F540
  (+0x1f00) are fields of it, polled after FlushCache(0). No static check sees these, so they are listed in
  `tools/shift/float_keep.txt`. D_0063F540 was the last culprit.

The float build now keeps 171 names in place (cover_check, reach_check and float_keep). reach_check's
list is written to `out/shift/<mode>-float/float_reach.txt`, and the log shows each access it found.

### Tools

- `tools/shift/reach_check.py [--ld LINK.ld] [--out FILE] [--all] [--debug ADDR]`: the check above. With
  no `--ld`, every C-defined variable is its own piece, which is conservative inside floated runs.
- `tools/shift/float_holes.py STATE.p2s`: reads eeMemory.bin from a PCSX2 state saved with
  System > Save State > Save To File (into Downloads/kh1-test, no folder change needed). It lists every
  floated variable whose old place, which should be all zero, has been written. This found D_005512A0 and
  D_0063F248 from one hung boot.
- `SHIFT_FLOAT_ONLY="names"` (shift_ld `--float-only`) floats only those bss names. Bisect with it:
  `SHIFT_FLOAT_SKIP` lets the budget pull in the next-smallest runs, so the tested set changes.

### Bisection log (PCSX2, about 2 min per boot)

| budget / set | runs | title |
| --- | ---: | --- |
| 0x10000 (reach_check v1: displacements and calls) | 170 | no |
| 0x10000 (+ idx-next, the 2 stale-write names kept) | 156 | no (no stale writes left) |
| 0x400 | 15 | yes |
| 0x800 / 0x1000 / 0x2000 | 30 / 59 / 109 | no |
| 0x400 set + 7 names (D_00641BA4 ... D_00642EA4) | 22 | yes |
| 0x400 set + D_005516E8 D_006257D4 D_006277E4 D_0062F6D0 | 19 | yes |
| 0x10000 with D_0063F248, D_0063F540 kept | 155 | **yes** (title, save, walk, attack, magic, menu) |

### Phase 4 step 3: shared names whose users disagree on the type (worker s18d1)

- 387 more shared bss names are C definitions. That makes 1,029 C-defined variables (36 data, 993 bss),
  and `make` stays byte-identical. By type: 277 basic types, 10 multi-dimensional or pointer arrays, and
  100 struct types. The struct typedefs, with the file-local types they use, moved verbatim into
  `include/data/types/<dir>_<stem>.h` (52 hand files; `tools/shift/type_move.py`).
- Each definition goes into `src/data/bss_XXXX.c` and its declaration into `include/data/bss_XXXX_mixed.h`
  (basic types) or `bss_XXXX_typed.h` (structs). A user whose declaration agrees includes that header at
  the end of the file, after all code, and only if the file still compiles with it (`-fsyntax-only`). A user
  that disagrees keeps its own extern with a `/* src/data/bss_XXXX.c: <type> */` comment.
- `tools/shift/define_shared.py --mixed [--types] [--exclude NAME]` picks one declaration per name: exact
  before fill before pad, a real type before M2C_UNK, hand files first, then the most users. The chosen one
  must cover every other complete declaration.
- **Hazard: data_owners.py does not use C-defined names as anchors.** A definition is referenced through its
  own section, so the reference never names the D_ symbol. That means extents in data_owners.tsv can run over
  existing definitions (D_0054B808 into D_0054B818). define_shared.py clamps each extent at the next C-defined
  variable. data_owners.py itself still needs out/gen/data.tsv added as anchors.
- 74 names were skipped. 37 have no declaration that fits the extent, and 25 have a declaration larger
  than the extent (a field named on its own). 6 have an extent that is not a multiple of the element, 3 have
  no single file-scope extern, and 3 clash on a type name in bss_0061 (`u128`, `PppMtx`; they need one shared
  header). For 2, one element fills the whole extent (indexed past it).
- The float build after it floats 577 C variables in 120 runs. 314 are kept in place, and 138 bss stay over
  the budget. In PCSX2 it reaches the title, loads the save, walks, attacks and opens the menu
  (KH1_F18D.ELF).
- Some batch-1 names got a basic type (`u8 D_00495210[0x40]`) although a hand file's struct (`Mtx`) also
  fits; these can be upgraded later.

## Session 19: data_owners anchors and the skipped shared names (worker s19d1)

`make` stays byte-identical after every batch. 1,080 variables are now C definitions (36 data, 1,044 bss),
51 more than session 18.

### data_owners.py: C-defined variables are anchors

- `tools/shift/data_owners.py` reads out/gen/data.tsv (`--data-tsv`). Every C-defined variable is an anchor,
  and a reference through a section symbol (how a file reaches its own definition) is counted for the
  C variable that holds the target. So the defining file shows up among a variable's users, and a variable
  no other file names gets a row too.
- Against the M0 link: 154 extents shrank, and 332 C variables that only their own file references now have
  rows (1,025 of 1,029 C variables have one; the other 4 are not referenced at all). No extent runs over a
  C variable any more. bss `single` went from 99 to 399, because the defining files now count as users.
- define_shared.py's clamp is gone. In its place is a check that stops with "rerun data_owners.py" when an
  extent runs over a C variable, which means data_owners.tsv is older than the last `make`. It found nothing.
- cover_check.py reads data_owners.tsv for "the name just below". With the C variables as rows, 7 names it
  used to keep in place now float: D_002BD1A8, D_003F32E8, D_003F5A00, D_00469FD8, D_00469FF8, D_0046A018
  and D_006202A0. Each one now sits right after a C variable whose size is known. Check them in PCSX2
  (title, menu, the world map) before trusting them.
- The fixed extents changed no skip reason by themselves. All 76 names define_shared.py --mixed listed were
  still skipped: the 73 from session 18 (74 there) plus the 3 bss_0061 type clashes.

### One shared type header (bss_0061)

- `include/data/types/shared.h` defines `u128` (`unsigned int`, mode TI) and `PppMtx` once. The h39 and
  nostrict h40 type headers, text_00180000_h40.c and text_001a0000_h13.c include it instead of defining
  them. text_00170000_s6_10.c's own `typedef int u128` became `unsigned`, matching the header it includes
  (gcc 2.96 accepts a repeated identical typedef, but not one that differs). The code is unchanged.
- define_shared.py: a type that shared.h defines needs no move (tsrc `include/data/types/shared.h`), and
  type_move.py copies a source's `#include "data/types/shared.h"` into the header it writes.
- With that, D_00616010 (`PppQv[3]`), D_0061E780 (`PppMtx`) and D_0061EEA0 (`GsTag[0x10]`) are defined.
- D_005759B0 hits the same problem with `V4`. text_00170000_b06.c and the nostrict b06 header each define
  an anonymous `struct { f32 x, y, z, w; } V4`, and two anonymous structs are different types even with the
  same fields. It needs `V4` in shared.h and `CamB` moved by hand. It stays skipped for now.

### define_shared.py --relax (with --mixed and --name)

- **pad-align**: a declaration smaller than the extent, where the rest is only alignment: the next anchor
  is the first 8- or 16-aligned address after it. The code's reach must fit, and no other name may land
  inside the extent. Taken addresses and sized arrays are allowed, because reach_check keeps a name in place
  when code reaches past it through a pointer.
- **fill-floor**: `T D[]` filled with floor(extent / sizeof T) elements when the remainder is only
  alignment. D_00645250 is `Save3C[99]`, and 99 is also the loop bound in text_00210000_s6_22.c.
- It also reads repeated identical `extern` lines, function pointers `T (*D)(args)` and `T *volatile D`.
  A user whose externs all declare some pointer counts as 4 bytes for a pad.
- With `--name`, names whose users agree go through this path too. The default mode refuses repeated
  extern lines, volatile types and struct types.
- `Save3C` moved by hand into include/data/types/text_00220000_c16.h, because that header already existed.

### Counts

| batch | names |
| --- | ---: |
| bss_0061 clashes (shared.h) | 3 |
| --relax on the skipped names: 12 pad-align, 2 fill-floor, 1 fill, 4 pad | 19 |
| --relax with function and volatile pointers: 3 exact, 3 pad, 2 pad-align, 1 fill-floor | 9 |
| --relax on the default mode's skipped names: 9 exact, 3 fill, 8 pad-align | 20 |

Some picks have a basic type where a hand file has a better one, for example `s32 D_00615E68` (36 users,
and most hand files say `PppMtxOwner *`). These can be upgraded later, like session 18's.

### Still skipped (45 of the 76, plus 7 other shared names from the default mode)

- **Another name lies inside the object** (a declaration is larger than the extent; a field named on its
  own), 25 names: D_00494BC0, D_004DBC20, D_004E2430, D_00525298, D_00525328, D_0052EB50, D_0054C440,
  D_00573E40, D_005758F0, D_00575900, D_00575940, D_00615E70, D_00615FC0, D_0062F6E0, D_0062F790,
  D_00630300, D_00630460, D_006305C0, D_00641250, D_00643020, D_00647FE8, D_00651E50, D_006561D0,
  D_006627B0, D_00669700. Defining these needs the enclosing object in C, with the inner names as fields or
  link-script aliases (`D_inner = D_outer + off`), and shift_ld must accept those inside a floated variable.
- **The name is part of a larger object**, 9 names: D_004E2450 and D_004E2458 (inside `s32 D_004E2430[64][16]`),
  D_00575970 (inside `Cam D_00575940`), D_00615FF8 (inside `PppMtx D_00615FC0`), D_00651E70 and
  D_00655264 (inside D_00651E50, which code reaches up to +0x4124), D_00623E49, D_006298F8, D_00629924.
- **Indexed past the extent, or rows that do not fit it**, 6 names: D_00575020, D_006305D0 (one element
  fills the extent), D_0054F438 (0x18-byte elements, extent 8), D_00623E40 and D_00623ED4 (96-byte rows
  that overlap D_00623E49), D_006298F0 (0xb0-byte objects, extent 6).
- **The declared type is too small, or the layout is unclear**, 3 names: D_00551740 (the code reaches
  +0x224, but the struct is 0x210), D_00631620 (`Pkt620` is 0x1960 of a 0x2020 extent, and its address is
  passed on as a DMA packet), D_00656230 (`Gm *` in the hand file, but session 18 found 0x24-byte entries).
- **Inside the IOP-written block** D_0063D640: D_0063EE40.
- **Type clash**: D_005759B0 (`V4`, see above). D_00668280 is a clash too (`Q4`, from the default mode's list).
- The other names from the default mode's list that stay skipped: D_004F3208, D_00551700, D_00616000,
  D_0062F670, D_00642EB0 and D_00642F60. Each is a scalar or M2C_UNK in a much larger extent, or a
  declaration larger than the extent.

### Float build

`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` passes: shift_cmp OK, the 12 overlay fixup proofs OK, LO16 0.
594 C variables float in 109 runs, 333 stay in place (cover_check, reach_check, float_keep), and 153 bss
are over the 0x10000 budget. `_end` is 0x68f524. Not run in PCSX2 yet.

## Session 19: Phase 4 step 4, shared data pieces (worker s19d2)

Shared *data* names (the file-backed region 0x272C70-0x494050) are now per-symbol pieces of the
user's ELF. `make` stays byte-identical; the M12 float build floats them one by one. No game bytes
enter the repo: the sources name an address, a size and, for pointers, a relocation.

### Mechanism

- **`include/data/piece.inc`**: `PIECE name, size, align` puts one name in its own section
  `.data.<name>` (global, `.type @object`, `.size`) as an `.incbin` of `out/data/pieces/<name>.bin`,
  and fails the assembly if the file is not `size` bytes. A piece that holds pointers is written
  `PIECE_BEGIN name, size, align` / `PIECE_BYTES name, off, len` (original bytes) / `.word sym+addend` /
  `PIECE_END name, size`. The section alignment is `min(lowbit(addr), lowbit(size), 16)`: MIPS gas pads a
  section to its alignment, so it must divide the size (a floated piece is aligned by its old address
  in shift_ld anyway). `.align 0` turns off gas's automatic `.word` alignment.
- **`tools/shift/cut_pieces.py`** (Makefile, before the piece objects assemble): reads the PIECE lines
  of `src/data/data_*.s`, checks the ELF's SHA-256 against kh1.toml and writes each piece's bytes to
  `out/data/pieces/` (only when they change; `out/data/pieces.stamp`).
- **Placement**: `kh1tool link-script` now also takes the `.data.*` sections of `src/data/*.s`, so a piece
  is a row of out/gen/data.tsv like a C variable: `make` places it at its address, `patch` writes it,
  `verify` compares it. shift_ld, cover_check and reach_check treat it like any C-defined variable.
- **`tools/shift/define_pieces.py [--verdict V] [--pointers] [--limit N] [--apply]`**: picks the names.
  The extent is data_owners.py's, clamped at the next variable in out/gen/data.tsv, the next compiled
  rodata block (rodata.tsv, sizes from the objects) and the end of the data (data_owners.py's own anchors
  do not include C-defined names; this works around it without touching it). A name is skipped when it
  starts inside such a block, when a C user declares it larger than the extent (probe compile), or, in
  the default mode, when any data_relocs.tsv row lies in the extent. `--pointers` takes those: an
  accepted row becomes `.word` (a code target by its function name, or `func_XXXXXXXX` for an unnamed
  one; a data/bss target as `variable+offset` when it lies inside a defined variable or a piece of the
  same run, else as its `D_XXXXXXXX` name; both links resolve these, the matching one through the
  PROVIDEs kh1tool gen derives from the `.s` text); a rejected (tier x) row stays bytes.
- **Types**: when every C user outside src/sdk/ declares the name the same way with a basic type, the
  declaration goes to `include/data/data_XXXX.h` and those users include it at their end (only if the file
  still compiles with it, as define_shared.py does). Otherwise the PIECE line carries an
  `/* untyped: ... */` comment saying why (users disagree, a struct type, no file-scope extern).
- **Step 5, retargeting** (shift_ld): a data_relocs blob word whose target lies inside any defined variable
  (C or piece) is emitted as `.word variable+offset` instead of `D_BLOB+x` / `D_BSS+x`, so it follows the
  variable when it floats (6 words today). Words inside pieces are relocations of their own (above).
- **Overlay fixups** (overlay_relocs.py): an overlay field that points into a defined variable names that
  variable in the fixup table, so overlay code follows a floated piece. This was needed at once:
  dktitle.x builds `%hi/%lo(D_002A3F44)`, and ovl_proof failed when that piece floated.
- **`SHIFT_FLOAT_DATA_BUDGET`** (shift_ld `--float-data-budget`; the worker used 0x4000, the default is 0
  since the PCSX2 test in "Session 19: runtime" below): floated data goes after the
  blob and pushes .bss and `_end` up by as much, against the same 0x6A0000 arena as the bss budget.
  Data variables float smallest first (cost: size rounded up to its alignment) and are packed by
  alignment, largest first, so the padding stays within the cost. With it `_end` is 0x693EA4 and
  `_end + 0xA000` stays below 0x6A0000 (no heap warning).

### Counts

- 809 shared data names are pieces in 26 modules `src/data/data_0029.s` ... `data_0049.s` (734 without
  pointers, 75 from `--pointers`: 59 with 166 `.word` relocations, 16 whose rows are all rejected).
  404 are declared in `include/data/data_XXXX.h` (294 user files include a header); 405 are untyped.
  `make`: link-script "1838 variables (845 data, 993 bss)", byte-identical.
- 34 shared data names stay extern: 33 are declared larger than their extent by some user (a field named
  on its own, or indexed past it), and D_00494050 has an empty extent (the end of the data).
- M12 float (`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`; compare, overlay fixups and LO16 OK): 493 of the
  809 pieces float (37 of them with pointers), 290 stay in place (cover_check: 121 right after a name no
  declaration sizes, 42 inside another declared object; reach_check: 127 more), 26 data variables are over
  the budget (0x3A696 bytes, the big tables). 511 data variables float in all.
- `HI16/LO16 sym+addend just outside a floated variable 2`: dtoa.c's `tens[k - 1]` folds to
  `D_00491FE0 - 8`; that piece floats, and shift_cmp accepts it as before.

### Hazards and notes

- With 0x4000 of floated data, PCSX2 itself crashes a few seconds after loading a save (twice); with 0
  the same build plays. See "Session 19: runtime" below; the bisection is still to do.
- A piece's `.word D_XXXXXXXX` (and the 6 retargeted blob words) is a reference data_owners.py now sees:
  the target's files column can list `src/data/data_XXXX.s` (or the blob), which changes its verdict and
  keeps define_shared.py, which wants only `.c` users, off it.
- Declared types that are structs (`Glyph`, `PN`, `Tex4440` ...) need the type moved to a shared header
  first (type_move.py) before a header can declare the piece.

### Left

- The 34 shared names above; the 1,368 single-owner data names (`single` 1,226, `single+p` 142) can go
  through the same tool (`--verdict single --verdict single+p`, then `--pointers`): a dry run gives 1,015
  pieces plus the pointer ones.
- The untyped pieces want a type once their users agree; the pieces kept in place by cover_check's "after
  an unsized name" rule float once that name is sized (a piece or a C definition).
- The data budget: the end state packs the blob (no gaps left by floated pieces), which needs every
  `D_BLOB + x` name and pointer gone first.

## Session 19: runtime, reach_check bounds and the bss budget (0x11800)

### reach_check bounds the indexed accesses

Session 18's `idx-next` rule kept every floated name that an indexed access from the name just below
could reach, because the index was unknown. reach_check now carries an upper bound for small values and
uses it (`analyse()` docstring):
- `andi` gives a bound, and so do `lbu` (0xFF) and `lhu` (0xFFFF). Shifts and multiplies by a constant
  scale it, and `addu`/`addiu` add bounds together.
- A `slti`/`sltiu`/`slt`/`sltu` result tested by `beq`/`bne` against $0 bounds the operand on the taken
  edge. A loop counter or a pointer walk (base, then base + stride on the back edge) that such a test caps
  is IDX with the largest offset. Growth that is not capped widens to unbounded after two rounds.
- An `idx` access now reports the largest byte it can reach (`ub + imm`), or None. In main(), a base whose
  bounded accesses all end before the next name drops its `idx-next` keep ("# N indexed bases have
  bounded accesses that end before the next name": 71).
- `SHIFT_REACH_FLAGS=--no-bounds` brings back the session 18 rule (for bisecting).

On the 1,029 floated variables the bounds rule keeps 276 names instead of 285. Nine names float that did
not before: D_005516D0, D_005739F8, D_00573AC0, D_00575090, D_00575310, D_005758D0, D_005758E0,
D_006469B8 and D_006469D0.

### A hazard no static check sees: the GIF packet buffer

With the bounds, the build hung when loading a save (KH1_F19B). With `--no-bounds` it played (F19C).
Bisecting the nine names (`SHIFT_FLOAT_ONLY`) found D_00573AC0. func_00162428 and its neighbours store
`D_00573AC0 | 0x20000000` (the uncached alias) into D_0055C648, and func_0015f8c8 builds a GIF packet
through that pointer. The packet runs far past D_00573AC0's declared 0x10 bytes (D_00573E40.call sends it
with qwc 0x50). Nothing follows a stored pointer, so no check can see that the next names are part of the
buffer. Session 18 kept it only by chance: a loop over D_005739F8 ends next to it. D_00573AC0 and
D_00573AD0 are now in float_keep.txt. General rule: **a name whose address is stored (especially with
0x20000000 or 0x30000000 ORed in) is a buffer of unknown size.** A future reach_check pass could flag every
`or`/`lui 0x2000` of a floated address.

### The bss budget and the arena

- `SHIFT_FLOAT_BSS_BUDGET ?= 0x11800` (was 0x10000). With the data float off, `_end` is 0x691424 (0x695124 with 0x4000 of data) and
  `_end + 0xA000` stays below 0x6A0000. With no data float, the arena leaves room for about 0x4BDC more, so about 0x16000 of
  bss. 0x15000 was booted only before the packet-buffer fix, so it is untested with the current keep
  list.
- `SHIFT_FLOAT_DATA_BUDGET ?= 0` (was 0x4000 in s19d2's merge). With 0x4000 (KH1_F19D: 493 pieces float),
  the build reaches the title, but PCSX2 itself crashes a few seconds after loading save 05. This happened
  twice: the emulator closes, it does not just hang. With the data budget at 0 (F19E: "548 data variables
  over the 0x0 budget stay in the blob", 110 bss runs float), the build loads the save, warps to Agrabah
  and walks. The cause is not known. A crash of the emulator rather than a hang points at a DMA or VIF
  transfer built from a moved table (inferred). Next: bisect with smaller data budgets (0x800, 0x2000) and
  `SHIFT_FLOAT_ONLY`.

### Runtime log (PCSX2, End of the World save 05 and an Agrabah fight)

| ELF | build | result |
|---|---|---|
| F19A | session 18 rules, bss 0x10000 | title, save, Agrabah fight: OK (the Phase 3 dump, renderer-spec §6) |
| F19B | bounds, bss 0x15000 | hangs loading the save |
| F19C | `--no-bounds`, bss 0x15000 | OK |
| F19X / F19X2 | bisection of the nine names | D_00573AC0 in: hang; out: OK |
| F19D | merged, bounds + keep, bss 0x11800, data 0x4000 | title OK, PCSX2 crashes after loading the save |
| F19E | the same with data 0 (the default now) | save, field, world map, Agrabah: OK |

### Notes

- **Fresh clone trap**: the float build needs out/shift/data_owners.tsv, which only
  `tools/shift/data_owners.py` writes (after `make shift`). Without it cover_check fails with a missing
  file. Run data_owners.py once after the first `make shift`.
- `patch_iso.py --append --in-place` reuses its earlier appended sectors when the ELF fits, so KH1_BIG.iso
  did not grow this session (this corrects the session 18 note).

## Session 20: Phase 4, single-owner data pieces (worker s20d1)

Every data name of the file-backed region is now a piece or a C definition, except two. `make` stayed
byte-identical after every step: link-script "3661 variables (2617 data, 1044 bss)". The data pieces
are 2,581 names in 27 modules (`src/data/data_0027.s` ... `data_0049.s`), 1,772 more than session 19.

### Steps

| step | tool | pieces | typed | notes |
| --- | --- | ---: | ---: | --- |
| single-owner, no pointers | `define_pieces.py --verdict single --verdict single+p` | 1,052 | 720 | 123 user files include a header |
| single-owner with pointers | the same with `--pointers` | 363 | 278 | 271 with `.word` (7,627 words), 92 whose rows are all rejected |
| names only `.word` relocations name | all verdicts, then `--pointers` | 411 | 4 | 377 + 34 (251 words); see below |
| declared larger than the extent | `merge_pieces.py` (new) | 31 merged | 0 | absorb 85 pieces and 2 extern names |

Net: 1,826 pieces added, 85 absorbed into 31 merged ones. Of the 2,581 pieces, 1,352 have a header
declaration (`include/data/data_XXXX.h`, 1,406 extern lines) and 1,229 are untyped (the comment says
why: users disagree, a struct type, no C user, merged). 8,048 `.word` relocations in all.

### Mechanism changes

- **Names that only data names.** A piece's `.word D_XXXXXXXX` (a blob pointer to a place no code
  names) is a reference data_owners.py sees, so after the single-owner pieces landed, rerunning
  data_owners.py gave 375 new rows (`single+p`, user `src/data/data_XXXX.s`), mostly 0x8-0x20-byte
  entries a pointer table points at one by one. They went through define_pieces.py like the rest.
  Rerun `make shift` + data_owners.py after any batch with `--pointers`, until a dry run finds nothing
  (it did after one round).
- **define_pieces.py: non-user declarations.** A header declaration is included at the end of every
  user, but other files may already include the same header for other names. Two names broke the
  build that way: `D_002BBC20` and `D_003F5C90` are `M2C_UNK` in their one user (an auto file) and
  `u8[]`/`u16[]` in a hand file whose function is `CONTEXT_ONLY` (no reference in the link, so not a
  user). define_pieces.py now reads every file-scope extern of the name in src/ (outside src/sdk/) and
  leaves the name untyped when any of them differs ("a non-user file declares it otherwise").
- **Merged pieces** (`tools/shift/merge_pieces.py [--name D_X] [--apply]`). A name some C user declares
  larger than its extent (a struct whose fields are named on their own, an array indexed past the next
  name) becomes one piece of the whole object: `PIECE_BEGIN D_X, size` with `PIECE_LABEL D_X, D_inner,
  off` for every name inside (include/data/piece.inc: a global `@object` label; the macro checks the
  offset). The size is the largest declaration, grown until no piece straddles its end (D_00351E10 is
  declared 0x31C4 and becomes 0x9070, because D_00351E50 ran to 0x9E80); a name inside that is itself
  declared larger grows it too (D_0038CD00 inside D_00389C90, D_003C55F0 inside D_003C5510). The
  absorbed pieces keep their `.word` relocations at their offset; bytes that were no piece get theirs
  from data_relocs.tsv. Refused when the object covers a C variable or compiled rodata. The inner names
  need nothing else: `make` resolves them to the label (it overrides the PROVIDE), shift_ld sees them
  defined by an object (no `D_BLOB + x` line), and they move with the section.
- define_pieces.py counts PIECE_LABEL names as done; cover_check.py counts a name that lies inside a
  defined variable as sized (its "after a name no declaration sizes" rule: 121 in session 19, 13 now).
- The module and header comments say "Data names" (they hold single-owner names too).

### What is left

- **Two extern data names.** `D_0046A688` is declared 0x20 bytes but holds the C variable D_0046A6A4
  at +0x1C (and D_0046A6A8, which dktitle.x writes, follows; session 17). Merging needs D_0046A6A4 out
  of C first and the overlay-shared name kept in place. `D_00494050` is the end of the file-backed
  data (`_gp` in the matching link, the 0x30 bytes before .bss): it has no bytes of its own.
- 7 names start inside a compiled rodata block (another file names a constant of D_0048CC10,
  D_0048D110/18, D_004917D8, D_00491848, D_00491978, D_004919A8); they are part of that block and move
  with it.
- 0xA2C blob bytes in about 150 gaps belong to no name: almost all are the padding between compiled
  rodata blocks, plus a few unnamed runs (0x400 at 0x46A9D8, 0xA8 at 0x4937E0, 0x74 at 0x48FDA4). They
  stay as blob chunks.
- 1,229 untyped pieces; the merged ones want the struct of their largest declaration in a shared header.

### Float build

- Default budgets (bss 0x11800, data 0): `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` passes (compare,
  12 overlay fixup proofs, LO16 0). "2151 data variables over the 0x0 budget stay in the blob", 110 bss
  runs float, `_end` 0x691424 (unchanged).
- `SHIFT_FLOAT_DATA_BUDGET=0x4000`: links and passes the same checks; 886 data variables float (511 in
  session 19), `_end` 0x695424, one `HI16/LO16 sym+addend just outside a floated variable` (dtoa's
  `tens[k - 1]`, as before). 776 variables stay in place (cover_check 46, reach_check, float_keep).
  Not run in PCSX2; the data float still crashes the emulator from session 19 (to bisect).

### Hazards

- **Separately pointed entries.** The 375 data-only names are entries a pointer table addresses one by
  one. As pieces they float independently; if code also walks from one entry to the next (pointer +
  stride, not through the table), floating breaks that and no static check sees it (the pointer is
  loaded from data). Suspect these first when bisecting the data float; a merged piece per table
  (merge_pieces.py with a size by hand) would keep them together.
- Merged pieces float as one block, so they are large (D_002C64A0 is 0x1C200, D_00351E10 0x9070): the
  data budget sorts them last, which is what we want until the blob is packed.
- A label shares the piece's section: reach_check and cover_check see the piece, not the label. A user
  that declares an inner name larger than the rest of the piece is not checked by merge_pieces.py;
  cover_check would flag the variable after it ("inside D_inner"), and it lists none today.

## Session 20: the data float (SHIFT_FLOAT_DATA_BUDGET ?= 0x4000)

`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` now floats 0x4000 bytes of data by default: 753 data names and
112 bss runs (1,217 variables), `_end` 0x688824 (`_end + 0xA000` leaves 0xD7DC below 0x6A0000). In PCSX2
(KH1_BIG.iso, ELF appended, KH1_F20_Q4000) it boots, the load menu text is right, save 05 loads, and
walking, attacking, the main menu and Items work. The world map and a fight were not run on this build.
`make` stays byte-identical. Each finding below was found by boot bisection and is now a static rule or
a float_keep entry.

### The crash (session 19, F19D): tables declared 0x40, copied 0x4000 deep

Bisection (`SHIFT_FLOAT_ONLY_DATA`, below) on the session 19 rules: 0x2000 (457 names) plays, 0x4000
crashes PCSX2 within ~15 s of loading save 05; the 66 names between them split to 16. D_00472190,
D_004761D0 and D_0047A210 are declared 0x40 bytes, but func_001072c0 and func_001073f0 copy
`D_00494AA0[i]` words at a time from `&D_X[b]` with b growing through the whole table, about 0x4000
bytes (D_004721D0, D_00476210, D_0047A250 are the 0x3FC0-0x3FD0-byte tails, still blob names). Floated
alone, the copy reads whatever follows the head (inferred: the copied data feeds the renderer, and the
emulator dies on what it gets). reach_check missed it in two ways, both fixed:
- **`&D_X[i]` passed to a call** was not an access: only exact addresses and argument values were
  recorded at call sites. Now an IDX argument is an indexed access from its base, bounded only when the
  index has a bound, the callee's reach from that argument is known, and the callee does not walk or
  index that argument (`wide` arguments: an ARG combined with an unknown value, or joined with another
  offset of itself, propagated up through callers). memcpy and memset stay with their byte counts.
- **idx-base**: session 18's idx-next keeps the next name when it floats. When the indexed base floats
  and the next name stays in the blob, the array now runs into a blob name, so the base stays too
  (`--no-idx-base` turns it off).

### Three more hazards as more data floated

- **A staging arena** (black field, HUD only, after the save loads): D_003F8380 ... D_0040EB80 are seven
  parts of one 0x16C00-byte area. func_00232ad0(-1) clears it all from D_003F8380 with one pointer walk,
  func_00232ad0(0..6) clears each part, and a getter in text_00220000_h25.c hands out each part's address.
  The four 0x400-byte parts floated. All seven are in float_keep.txt.
- **A stored buffer pointer** (garbled text on the load menu and in the command menu; the pattern changes
  every boot): func_001e* stores `&D_003E4658` and 0x310 into D_003E8E28/2C. D_003E4658 is declared 8
  bytes, so the next names (D_003E4660 ... D_003E46A8) are inside the buffer. New rule: **an address that
  a `sw`/`sd` stores is an unbounded indexed base** (204 addresses; idx-next and idx-base then keep it and
  its neighbour; `--no-stored`). This generalises session 19's packet-buffer note.
- **Parallel object/table records** (hangs while loading the save): D_0046E120/40/50, D_00472160/80/90,
  D_004761A0/C0/D0, D_0047A1E0/A200/A210 are a 0x20-byte object, a 0x10-byte entry and the 0x4000 table
  above (with a 0x10-byte header before the last three). `o->p = cond ? D_00472160 : D_0046E120` is a
  join reach_check turns into an unknown index, so the stored-address rule does not see it. One
  `float_holes.py` run on a savestate of the hang showed writes into the old places of D_004761A0 and
  D_004761C0. All eleven names are in float_keep.txt. These four records want to be merged pieces
  (merge_pieces.py) so they float as wholes.
- **Uncached alias** (rule only, `--no-uncached`): a name whose address is built with 0x20000000 or
  0x30000000 ORed in keeps itself and the next name. It finds session 19's D_00573AC0 by itself and adds
  D_0046D800 (sceCd's 0x440-byte buffer, which sceCdInit and friends reach uncached).

### Pointer-table-only names stay (SHIFT_FLOAT_PTR_ONLY ?= 0)

Names whose only users are pieces' `.word`s (data_owners.py files column all `src/data/*.s`: 466 names, the
entries s20d1 warned about) stay in place by default. With them floated, the load menu drops the digit of
"スロット1"/"スロット2" (the rest plays); D_0048F700 ... D_0048F870 (0x10-byte entries of a data_0037.s
table) were the new names in that build. Not bisected further. `SHIFT_FLOAT_PTR_ONLY=1` floats them.

### Budget refill

Every name taken out of the float lets the budget pull in the next-smallest ones, so each fix exposed new
names (twice: the hang above came from 157 names the pointer-only rule freed room for). After a rule
change, boot the default build again before calling it tested; compare floated sets with the ELF's own
symbols (D_ names whose address moved by other than the common data delta).

### The bss budget

With the new rules only 6 bss names are over the 0x11800 budget, and the smallest of them alone
(D_00533BA0, 0x14014 bytes) is larger than the arena room left: 0x16000 builds the same ELF as 0x11800.
The bss float is now limited by the keep rules, not the budget.

### Tools

- `SHIFT_FLOAT_ONLY_DATA="names"` (shift_ld `--float-only-data`; `@FILE` reads names from a file): only
  these data names float (bss as usual). Bisect with the floated list of a good build plus half the
  suspects; `SHIFT_FLOAT_SKIP` changes the set through the budget refill.
- reach_check.py: `--no-idx-base`, `--no-stored`, `--no-uncached` turn the session 20 rules off one by one.
  On the default (no `--ld`) run it keeps 1,928 names; the session 19 rules keep 761 on the same pieces.

### Bisection log (PCSX2, save 05; the load menu shows text bugs before loading)

| ELF | build | result |
|---|---|---|
| F20_D0x4000U | s19 rules + uncached, data 0x4000 | PCSX2 crashes after loading |
| F20_D0x2000 | s19 rules, data 0x2000 (457 names) | plays |
| F20_A / B1 | 0x2000 set + 33 / + 17 of the 66 | play (culprit in the last 16) |
| F20_N0 / N0x4000 | indexed-argument + idx-base rules, data 0 / 0x4000 | plays / black field |
| F20_NX | N0x4000 without the four 0x400-byte arena parts | plays |
| F20_M4000 | s20d1's pieces merged, data 0x4000 (835 names) | field draws, text garbled |
| F20_T1 ... T7 | bisection of the 528 new names | T7 (8 names) garbled: D_003E4658 |
| F20_S4000 | + stored rule | plays; slot digit missing on the load menu |
| F20_P4000 | + pointer-table-only kept | load menu right; hangs loading the save |
| F20_Q4000 | + the record names in float_keep (the default now) | plays (field, walk, attack, menus) |

## Session 21: neighbour+offset names (addend_check) and looser reach_check

### The Agrabah walls: D_002A6274 read as D_002A6278's neighbour

The session 20 default (KH1_F20_Q4000, data 0x4000) reaches the world map and warps to Agrabah, but there
Sora walks through the walls into the void (the screen looks black or flashing). Bisection with
`SHIFT_FLOAT_ONLY_DATA` (save 06 in Agrabah, walk into a wall) isolated one name:

| ELF | floated data | result |
|---|---|---|
| F21_D0 | none | walls hold |
| F21_A, A1, A1a, A1a2x, A1a2xa | halves of the Q4000 set | through the walls |
| F21_A1a1 | the other quarter | walls hold |
| F21_P1, P1a | narrower halves | through the walls |
| F21_S6274 | D_002A6274 alone | through the walls |

D_002A6274 is the collision header's triangle pointer (func_00105288 fills D_002A6270 ... D_002A62AC from
the loaded header). Every code reference was relocated, nothing read the old address, and its value at run
time was right. The stray read is in the same function: func_00105288 walks the fix-up list through
`((s32 *)&D_002A6274)[1]`, which is D_002A6278 but assembles to `%hi/%lo(D_002A6274+4)` (the matching form:
`p = (s32 *)D_002A6278` changes the schedule). With D_002A6274 floated the load reads 4 bytes past its new
place, so the room's collision list is never fixed up. Static checks miss it because the relocation is
correct for the symbol it names; shift_cmp counted it ("HI16/LO16 sym+addend just outside a floated
variable 1") but does not fail on it.

**addend_check.py** (run by `make shift SHIFT_FLOAT=1`, output `float_addend.txt`): reads the m0 link
(`ld -q` keeps relocations) and, for each HI16/LO16 pair and R_MIPS_32 against a D_ name, works out the
addend; when sym+addend lands outside [sym, next name), it keeps both names. 72 names on the current tree
(D_002A6274/78, D_002C5950/58, D_0035AE80 + three, D_00651E50 + two, ...). Q4000 also floated D_002C5958
alone (its base D_002C5950 stays): a latent hazard of the same kind. D_002A6274/78 are in keep_check.py.

### reach_check (worker s21r1)

Default run keeps 1,832 names (was 1,928). Each rule has a `--no-*` switch (SHIFT_REACH_FLAGS):
- `--no-countdown` (1,864 without it): a pointer walk capped by a decrementing counter (`bgtz`/`bne`/`bgez`),
  or an up-counter from an exact start (`addiu; slti; bne`), gets the trip count as bound (one back edge,
  one way in). func_00232ad0's clears end exactly at +0x16C00 / +0x400.
- `--no-join` (1,836): a join of exact addresses outside a loop head is a set of up to 8 addresses;
  accesses, stores and call arguments go to each. func_00107d30's `o->p = c ? A : B` now stores all six
  record addresses, so the session 20 records are found without float_keep.
- `--no-arg-join` (1,946): an argument joined with an unrelated value is not a walk of that argument.
- `--no-block-bound` (1,875): `&B[i]` passed to memcpy/memset/pool init is bounded by its count.
- Coverage fixes (they add keeps): `--no-hi-index` (1,640 without it; `D[i]` as `lui` + `addu` + `%lo` was
  not seen) and `--no-switch` (1,779; jump tables are read from the ELF and case bodies are analysed).
  `lq` clears its register. Turn these two off to bisect a boot problem they might hide behind.
- The largest group left is arguments to callees that walk or store them (strcat, scePrintf,
  sceSifCallRpc buffers, DMA addresses such as func_00266f38's): real hazards, kept.
- **keep_check.py** lists the runtime-bisected names (sessions 18-21); the float build fails if one is not
  kept (unless SHIFT_REACH_FLAGS is set). tests/reach_check_test.py is in `make test`.

With both: 721 data names and 118 bss runs float (1,230 variables); `keep_check: 35/35`.

### Runtime (PCSX2, save 06 in Agrabah)

- **KH1_F21_RA** (addend_check + s21r1 rules): the walls hold, but the storage room's walls are black from
  some angles and Gate Plaza draws only sky and a floating door. KH1_F21_D0 (no data floated) draws both.
  **RX** (RA without countdown/join/arg-join/block-bound) shows the same, so the new rules are not the cause.
- Bisection over the 695 names both floated: C1 (first half) good; C2 bad; C2a good; C2b bad; C2b1 good;
  **C2b2a (44 names) bad**. 33 of the 44 are entries of pointer tables that define_ptr_tables.py moved into C
  (D_0048CF78 ... in text_00110000_6.c, D_0048D2D0 ... in h53, D_0048DDA8 ... in text_00130000_4.c): the
  session 20 pointer-table-only rule reads data_owners.tsv, where these now have a C owner, so it missed
  them. **tools/shift/ptr_only.py** lists every name that only a C pointer table names (108); the float build
  keeps them with the rest (SHIFT_FLOAT_PTR_ONLY=0).
- **KH1_F21_RB** (with ptr_only; 690 data names, `_end` 0x6913E4): the storage room draws and a fight
  (Pot Spider) works, but in the alley behind the right-hand door the buildings vanish when the camera faces
  away from the wall (pots and party float in the sky). Bisection there does not converge: each half of the
  677 floated data names (H1, H2, with bss 0x11800) draws the alley, the whole set does not. Keeping libcdvd's
  state block (float_keep.txt, RC) did not change it.
- **The bss float is the other half**: the same 677 data names with `SHIFT_FLOAT_BSS_BUDGET=0` (RCB0,
  `_end` 0x685598) draw everything; bss 0x4000 (111 of 118 runs, `_end` 0x687CA4) does not, so it is not
  `_end` or heap room. D0 (bss 0x11800, no data) draws everything too. Something overruns into, or reads
  past, a neighbour that only some layouts put next to it. **Default is now data 0x4000 with bss 0**
  (identical to RCB0).
- Next step (not done): pad each floated name (e.g. 0x40 bytes of a sentinel), reproduce in the alley,
  save a state and look for a pad that changed; that names the overrunning object without bisection.
- Quick test: load save 06, hold back 7 s (storage room wall view), right 6 s (through the right door
  into the alley), forward 5 s, back 4 s: the camera then faces away from the wall and the buildings must
  draw. A first glance at the alley is not enough. The door to Gate Plaza is on the left wall by a big red pot.


## Session 22: the alley bug was a split record, and split_check.py

### Session 21's alley conclusions were wrong

Session 21 compared builds on a first glance at the alley and with a route whose last camera angle varied.
With a fixed route (below), **RCB0 (data 0x4000, bss 0, the session 21 default) is bad too** and so is H2;
retail and D0 (no data floated) draw the alley. The data float alone is enough; the bss float and the
`_end` / tail address were never the cause (G380: .bss moved by 0x380 with no data floated, good).

### Test T (deterministic alley test)

Load save 06 and wait 25 s; hold back 7 s, then right 6 s (through the right-hand door into the alley);
wait 6 s; hold R2 (camera right) 1.5 s and look at the booth/shelf view; hold R2 1.5 s again and look at
the door view. Retail shows walls in both. A bad build shows sky with the door or pots floating in it.

### Pads first: no overrun

shift_ld `--float-pad N` / `--float-bss-pad N` (Makefile `SHIFT_FLOAT_PAD`, `SHIFT_FLOAT_BSS_PAD`) put a
sentinel (data, `FLOAT_PAD_WORD`) or zeros (bss) after each floated name, each at `__fpad_<name>`;
**tools/shift/float_pads.py STATE.p2s** lists the pads that changed. With data 0x4000 + bss 0x11800 and pads
0x10/0x40, the alley was bad but **0 of 795 pads changed** (and float_holes.py: 0 of 1,186 holes written):
nothing writes past a floated name. (A data pad of 0x40 pushes `_end` into the 0x6A0000 arena.)

Bisection tools added for the layout hunt: `SHIFT_FLOAT_BSS_GAP=N` (N bytes before the floated bss),
`SHIFT_FLOAT_DATA_GAP=N` (moves .bss as if N more bytes of data floated) and `SHIFT_FLOAT_BSS_SLOTS=names|@FILE`
(the bss tail is laid out in full, but only runs holding these names move; the others keep an empty slot).

### Bisection with test T

Over the 677 default data names: DB (half) bad, dB2 bad, dB2b (43) bad, both halves of dB2b good: a pair.
b1 + b2[:5] bad, b1[:5] + b2[:5] good, b1[5:10] + b2[:5] bad; singles with b2[:5]: D_0046C5D8 good,
D_004862D0 good, **D_0048BFD0 hangs loading save 06** (twice). The default build with only D_0048BFD0 kept
draws the alley (K0), and so does bss 0x11800 (K1).

D_0048BFD0 (0x8 bytes, C reads it as two words) and D_0048BFD8 (0x88) are one 0x90-byte record: the
object/table records (D_0046E120+4, D_004761A0+4, D_0047E220+4, D_0048C630+0xc) point at D_0048BFD0, and
whoever follows that pointer reads past its 8 bytes. Floated, its tail is whatever floated after it, so
the symptom moved with the layout (sky, hang); that is why halves looked like pairs.

### The data 0x6000 / 0x8000 title

With D_0048BFD0 kept, data 0x6000 and 0x8000 (with or without bss 0x11800) boot with **no picture** ("No
Image" in PCSX2; the game runs blind, keys start a new game). Over the 87 names 0x6000 adds: v2 bad, v22 bad,
v221 bad, v221b bad, the IPU (D_0046E0B0) and VU0 (D_0046C590) tables alone good, **x1 = D_002A6178 +
D_002A6658 bad**, x2 = D_002B6668 + D_002BC918 good. Both are u64 colour registers (RGBAQ) that C writes
inside a GIF packet: D_002A6120 (0x58) + D_002A6178 (0x68) is one packet, and the DMA tag D_002A61E0 points
at D_002A6120; floated, C writes the colour where the DMA no longer reads.

### tools/shift/split_check.py

One rule covers both: when a `.word` in src/data points at one of two adjacent pieces and the boundary
between them is not 16-aligned, the two are one object; both stay in place. 272 names; it adds 9 of the
default 0x4000 set (D_0048BFD0 among them) and 9 of the 87 extra. The Makefile appends it to
float_covered.txt; keep_check.py now lists D_0048BFD0, D_002A6178 and D_002A6658 (38 names).

### Runtime (PCSX2, save 06)

| Build | Floated | Title | Alley (test T) |
|---|---|---|---|
| K0 | data 0x4000, bss 0, D_0048BFD0 kept | ok | ok |
| K1 | data 0x4000, bss 0x11800, D_0048BFD0 kept | ok | ok |
| K6C | data 0x6000, bss 0x11800, split_check | ok | ok |
| K8C | data 0x8000, bss 0x11800, split_check (`_end` 0x695264) | ok | ok |

**Defaults are now data 0x8000, bss 0x11800** (0x8000 floats 2 names more than 0x6000; `_end` + 0xA000
leaves 0xD9C below 0x6A0000). Not run on these builds: Gate Plaza, the world map and a fight (walking blind
from the alley kept going back into the storage room). The libcdvd block session 21 added to float_keep.txt
was a guess for this bug and may not be needed.

## Session 23: runtime on data 0x8000 / bss 0x11800, and whole pieces

### Runtime on the session 22 defaults (KH1_F22_K8C = the default build, byte-identical)

Save 06: the load menu, test T, the world map and a warp drive to Neverland (the pirate ship), and a fight
there all work. **Test T's "alley" is Gate Plaza**: the main menu names the area behind the storage room's
right-hand door アグラバー：城門広場 (Gate Plaza). Sessions 21-22 called it the alley; it is the same place.

Quick world-map route from save 06 (no walking): at the save point Up, L (save menu), Down, Down, L (Gummi
Ship), L (yes); on the map W (warp hole), D (Halloween Town), D (Neverland, Warp Drive only), L, L (land on
the ship). Heartless appear on the ship's lower deck after walking about 10 s (S, A, D, W).

### The libcdvd block is not needed

float_keep.txt's libcdvd block (session 21's guess for the alley bug) is gone. KH1_F23_NOCD floats 16 of
its names (D_0046C614 ... D_0046C650) and plays: title, load menu, test T, warp, fight.

### merge_pieces.py --group / --split

- `--group D_X:SIZE` makes one piece of D_X ... D_X + SIZE whatever the declarations say (inner names become
  PIECE_LABELs; bytes that were no piece take their data_relocs rows as `.word`). `--split` does it for every
  maximal run of adjacent pieces whose inner boundaries are not 16-aligned when a `.word` points into the run
  (split_check.py's rule): 77 pieces from 299 names; split_check.py now lists nothing.
- The plan reads out/gen/data.tsv, so run `make` after each `--apply` before the next plan (a stale
  data.tsv gave pieces a label of their own name and duplicate definitions).
- keep_check.py: a runtime name that is now a label inside a merged piece is reported as "one piece with
  D_X"; the piece's own name still has to be kept when the bisection said so.

### The object/table records are six VIF1 DMA chains

Decoding the tags (bits 28-30 of the first word): D_0046E120 + k * 0x4040 (k = 0..5, the last at D_00482260)
are six chains: `ref` D_0048BFD0 qwc 9 (the 0x90-byte record of session 22), `ref` D_0048C060 qwc 42 (now a
0x2A0 piece), an entry and a 0x4010-byte table of `ref` tags C fills per frame, ending with an `end` tag at
+0x4030. func_00107d30 stores the chain's address into the object func_00106db0 kicks (VIF1 TADR, CHCR
0x105). Session 20's "0x10-byte headers" D_00472150 and D_0047A1D0 are the previous chain's end tag
(text_00110000_h52.c and others copy D_00472150 as an end-tag template). Each chain is one piece now
(`--group D_0046E120:0x4040` and so on), and so is the 0x16C00-byte staging arena.

| ELF | build | result |
|---|---|---|
| F23_REC | records cut at the wrong place (0x4050, "headers" first) + 0x16C00 arena, three floated | hangs loading save 06 |
| F23_REC2 | MRG2 data + D_0046E120 and D_00472160 floated whole, bss 0 | save 06 loads; hangs (black, FPS N/A) walking into Gate Plaza |
| F23_MRG2 | the default after the merges (same float set as NOCD plus D_0046A6B0 0x320, D_0046E100) | title, load, test T, warp, fight: OK |

float_holes.py on REC2's hang savestate: 0 of 729 floated names have writes at their old place, so the
REC2 hang is a read (or a DMA) of the old place, not found yet. The six chain heads and the arena head stay
in float_keep.txt. (At the default budgets none of them would float anyway: 0x4040 each.)

### Phase 4

- D_0046A688 is a piece: a table of eight function pointers (func_0024d8a0 ... func_0024e078). D_0046A6A4,
  its last entry, was a C definition in text_00100000_c00.c and is now a PIECE_LABEL. D_0046A6A8 (dktitle.x
  writes it) stays its own piece. `make` identical; the float build's loaded image did not change.
- shift/drafts.tsv: 001636d0 uses the session 23 394w draft (PR #27); `SHIFT_DRAFTS=1` links all nine.
- 1,035 pieces are still "untyped" in their comments.

## Session 24: why a whole DMA chain could not float, and pointer-table-only names float

### The REC2 hang: chain 1's table is also a 32-byte array

Session 23's hang savestate (Downloads/kh1-test/s23_rec2_hang.p2s) was read here without PCSX2:
`PCSX2 Internal Structures.dat` holds cpuRegs 32 bytes after the `cpuRegs` tag (GPRs 16 bytes each, then
HI, LO, CP0, sa, IsDelaySlot, pc) and eeHwRegs.bin the DMA channel registers (offset = address - 0x10000000).
The EE sat in the kernel idle loop (pc 0x80001578, EPC 0x26815c in `_DisableDmac`), VIF1 idle with an `end`
tag in the heap: every game thread was blocked, no DMA was stuck.

The memory showed the cause. func_00106ed0 sets `D_00494BA8 = D_0046E150` (chain 0's table, 16-byte
entries) and `D_00494BAC = D_00472190` (chain 1's table, **32-byte entries**), and fills D_00494BB0 entries
of each (622 in Gate Plaza; func_00107548 reads them back). 622 * 32 = 0x4DC0 bytes from chain1+0x30 run
0xDB0 bytes past chain 1's 0x4010-byte table into chain 2. Only words 2-3 of each qword are written (floats
at +8 and +0x18), the halves of a DMA tag that the DMA ignores (CHCR 0x105, TTE off), so the original layout
survives it. With chain 1 floated alone, the writes landed on whatever floated after it: in REC2 D_004914E0
... D_002A62F0, among them D_002A3F30 (a header pointer func_001081c8 and func_00107c48 follow) and the
collision header. float_holes.py could not see it: the old places stay clean, the new neighbours are hit.
D_00494BB0 is loaded from the room's data, so no static rule bounds it; up to 1024 entries reach chain2+0x3FF0.

- **Chains 1 and 2 are one piece**: `merge_pieces.py --group D_00472160:0x8080` (D_004761A0 is a label).
  Chain 0's table only holds 16-byte entries (0x26E0 bytes for 622) and chains 3-5 are kept by reach_check
  (idx-next) anyway.
- **KH1_F24_REC3** (data = the MRG2 set + chain 0 + the merged chains 1-2, bss 0, forced with
  SHIFT_FLOAT_FORCE): loads save 06, Gate Plaza draws and a fight there works. REC2 hung at this point.
- The chains stay in float_keep.txt (each is far over the 0x8000 data budget; nothing changes by default).

### SHIFT_FLOAT_FORCE (tools/shift/float_force.py)

`SHIFT_FLOAT_FORCE="names|@FILE"` takes names out of float_covered.txt after keep_check (which then does not
fail the build), so a hypothesis about a kept name can be booted: combine with `SHIFT_FLOAT_ONLY_DATA` and a
large `SHIFT_FLOAT_DATA_BUDGET`. Runtime experiments only; the default never sets it.

### Pointer-table-only names float by default (SHIFT_FLOAT_PTR_ONLY=1)

Session 20 kept the 466 names only pieces' `.word`s name because floating them dropped the slot digit on the
load menu. On the session 23 tree that bug is gone (the session 22-23 split and group merges hold the walked
tables together). The only thing that stopped `SHIFT_FLOAT_PTR_ONLY=1` was keep_check: D_003E4670/80/90 are
inside D_003E4658's 0x310-byte buffer and were kept only by the pointer-only rule. D_003E4658 is now one piece
(`--group D_003E4658:0x310`; it grows to 0x42B8 because the 0x4270-byte D_003E46A0 starts inside the buffer).

| ELF | build | result |
|---|---|---|
| F24_REC3 | MRG2 set + D_0046E120 + D_00472160 (0x8080), bss 0 | save 06, Gate Plaza, fight: OK |
| F24_P1 | defaults + SHIFT_FLOAT_PTR_ONLY=1: 1,061 data names, 118 bss runs, `_end` 0x6953E4 | slot digits right, save 06, Gate Plaza + fight, world map, warp drive to Neverland, fight on the ship: OK |

**The default float build is now F24_P1** (loaded bytes identical, also after the s24types merge):
data 0x8000 with pointer-table-only names, bss 0x11800. `_end + 0xA000` leaves 0xC1C below 0x6A0000.

## Session 24: Phase 4 types (worker s24types)

`make` stayed byte-identical after every batch. The M12 float build (`make shift SHIFT_MODE=m12
SHIFT_FLOAT=1`: M12-FLOAT OK, overlay fixups OK) gives a kh1-shift.elf identical to the one before the
session, whole file (types emit no code and move no section).

### tools/shift/type_pieces.py

- Reads the pieces whose comment has `--note` (default "untyped: merged") and, for the piece name and every
  PIECE_LABEL in it, the file-scope externs of all C files outside src/sdk/ (repeated identical lines are
  fine). It picks one declaration per name: the largest (sizeof probed in the user's file; `T D[]` counts as
  one element) that fits what is left of the piece, then a real type before M2C_UNK, complete before `[]`,
  hand before auto, most users. The piece's own name chosen as `T D[]` is written `T D[size / sizeof T]`.
- A struct type the chosen file defines moves to include/data/types/ (type_move.py). When the file's type
  header exists, the types go to a new `<stem>_p.h` (`_p2.h` ...) that includes it: **never grow a type
  header other files include** (appending `Ent16` to text_00100000_s11_w71.h broke src/data/bss_0049.c,
  whose bss_0049_typed.h also includes nostrict_text_00100000_s11_w45.h with its own `Ent16`).
- The declarations go to **include/data/pieces/D_X.h, one header per piece** (a module-wide header clashed
  with about twice as many users: one wrong name or one type-name clash, e.g. a local `V4`, keeps the file
  out). Each header must compile on its own. Every file that names a declared name tries the header at its
  end (`compiles_with`); a compatible extern (`T D[]` vs `T D[N]`, `M2C_UNK` vs `s32`) is fine.
- Names already declared in include/data/data_XXXX.h are left there (12 merged heads were: merge_pieces.py
  writes "untyped: merged" whatever the absorbed pieces' headers say).
- `--all-users` (the second pass) types a piece only when one type serves every file that names it, and a
  local struct type only when no other file names the piece. `--includes-only` reruns the include step.
- The .s comment of a typed piece names its header (`/* data/pieces/D_X.h */`; merged ones keep
  `merged (...)`).

### Counts

| category (comment) | before | typed | left |
| --- | ---: | ---: | ---: |
| merged | 114 | 46 (34 new, 12 in data_XXXX.h); 153 of 330 labels | 68 |
| users disagree | 305 | 31 (`--all-users`) | 274 |
| no C user ... with one file-scope extern | 496 | 42 (`--all-users`: 41 function pointers, D_0037733C..D_003773D8 and D_0046A6A8, and T78D8 D_003F78D8[8]) | 454 |
| type X is not a common.h basic type | 112 | 93 (`--all-users`) | 19 |
| element size does not divide the extent | 5 | 4 (as `T D[]`) | 1 |
| a non-user file declares it otherwise, the D_0046A688 table | 3 | 0 | 3 |
| **all** | **1,035** | **216** | **819** |

214 headers in include/data/pieces/, 549 includes in 245 user files; 87 new type headers in
include/data/types/ (33 of them `_pN.h`).

Why the rest stay untyped:
- 53 merged pieces and 454 others: no C file declares the piece at all (names only data `.word`s or asm reach;
  the split_check/record groups of session 23). 15 merged pieces have typed labels but an unnamed head; a
  struct made up from the labels alone would be a guess, so they say `untyped: no C user declares it
  (merged); labels in ...`.
- 274 "users disagree": `s32`/`u32`, `T`/`T[]`, different local structs; no one type compiles in every
  user. The merged pieces have the same split (e.g. D_00389C90: 20 local struct types in 55 files; its header
  declares `Str`, from text_001c0000_h67.c: 2 files declare it that way, 5 include the header). Unifying needs one shared struct per
  object and edits to each user, function by function, with `make` checking the code.
- 15 struct-typed pieces: the type is local to one file and other files name the piece (T16, Q16, Glyph,
  PCur), or a user's own `u128` typedef clashes with shared.h's; their comments say which.

### Hazards

- gcc 2.96 accepts `extern volatile s32 X;` followed by `extern s32 X;` (only the qualifier differs), so
  the end-of-file include does not prove the qualifiers agree: D_002BBE04's header says `s32`, and
  text_001c0000_h42.c still reads it as `volatile`. A later C definition from these headers must check the
  users' qualifiers.
- A header included at a user's end only checks the declarations; it changes nothing before it, so the code
  cannot change. Nothing may ever move these includes to the top of a file without a `make`.
