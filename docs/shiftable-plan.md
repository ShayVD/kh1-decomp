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

## Session 25: the fixed pools move, and a bigger float

### What the 0x6A0000 limit was

Only two functions name an address between the image and 0x820000 (checked over the ELF's code and all
twelve overlays: every other `lui 0x67..0x81` is a mask or a colour constant):

- `func_0014a090` hands out three pools from **D_006A0000**, sizes from the words of D_00350D18
  (0x40000, 0x20000, 0x20000): 0x6A0000-0x720000.
- `func_00133628` hands out seven from **D_00720000**, sizes from D_00304318 rounded down to 16 (0x1B800 ...
  0x20000, 0xD2C00 in all): 0x720000-0x7F2C00.
- The next fixed region is `func_00121c78`'s D_00820000; 0x7F2C00-0x820000 (0x2D400 bytes) is unused.

Both size tables are only read. Nothing else holds an address inside the pools at build time (they are
handed out at run time), so the two bases can move together as long as the second area ends by 0x820000.

**shift_ld `ARENA_POOLS`**: in the moved modes D_006A0000 is `MAX(0x6A0000, ALIGN(_end + 0xA000, 0x1000))`
and D_00720000 is 0x80000 after it, with an `ASSERT` that the second area ends by 0x820000 (ld fails with
"fixed pools ... would reach 0x00820000: float less"). The sizes are read from the user's ELF. Below the
limit nothing changes (MAX), so m1/m2/m12 without the float are the same ELFs as before.
`SHIFT_FIXED_ARENA=1` (`--fixed-arena`) keeps the old fixed bases. shift_cmp maps 0x6A0000-0x7F2C00 to the
new base, prints "fixed pools moved after crt0's heap", and checks `_end` against the new base. The largest
`_end` possible is 0x6C3400 (pools at 0x6CD400).

`out/shift/<mode>-float/float_over_budget.tsv` (new) lists every name the budgets left out, smallest first.

### Budgets and runtime (PCSX2, save 06)

| ELF | build | result |
|---|---|---|
| F25_A | data 0x20000 (1,103 data names: every one the checks allow except the 0x16C00, 0x20000 and 0x40000 tables), bss 0x11800, pools at 0x6C0000 (0x10000-aligned) | load menu, test T, warp drive to Neverland, fight on the ship: OK |
| F25_B | + bss 0x26000 (D_00533BA0's 0x14000 run floats; 119 runs), pools at 0x6C5000 (0x1000-aligned), `_end` 0x6BABA4 | same route: OK |
| F25_C | the default after the reach_check rules below: 1,079 data names, 119 bss runs, `_end` 0x6B7924, pools at 0x6C2000 | same route: OK |

**Defaults are now data 0x20000, bss 0x26000.** What still stays: the three big data tables (D_0040EF80
0x16C00, D_002E31F0 0x20000, D_00308CE0 0x40000) and the bss runs of D_004F8310 (0x1CC48) and 0x30C9C; any of
them would push the pools past 0x820000 (about 0x8800 of room is left).

### reach_check: pointer globals and the next name after a piece

- **via-ptr** (`--no-ptr-global` turns it off): a load of a word from an image address G (`lw r, %lo(G)`)
  is the pointer G holds (`PTR` state); loads and stores through it, and indexes into it (`addu` with an
  unknown value), are accesses through G. Every address code stores into G (`sw A, %lo(G)`) gets them as
  its own indexed accesses: bounded when every access through G has a constant offset, otherwise
  unbounded. On D_00494BAC it finds func_00106ed0's `D_00494BAC = D_00472190` and func_00107548's indexed
  reads (27 bases in the hit list carry a via-ptr reason today, all also kept by older rules). A comparison against a constant still bounds a loaded word
  (refine treats PTR like an unknown).
- **piece-next** (`--no-piece-next`): an unbounded indexed base whose next name is inside its own piece (a
  merged piece's label, the rest of a bss run) keeps the first name after the piece instead. Without it an
  index into a merged piece kept nothing. It keeps 30 more names on today's tree (e.g. D_0046E120, chain 0,
  and D_003773E0).
- **The check**: with D_00472160 split back into two 0x4040 chains (`--data-tsv` with a copy of
  out/gen/data.tsv), reach_check now reports `00472190 (D_00472160) -> 004761a0 (D_004761A0)
  idx-next[arg:wide,piece-next,stored,via-ptr:00494bac]`, i.e. chain 1 keeps chain 2 by itself. piece-next
  is what finds it (the stored rule already made the index unbounded); via-ptr names the reason. Stride
  bounds were not needed: the count (D_00494BB0) comes from room data, so the reach is unbounded either way.

## Session 25: Phase 4 types (worker s25types)

129 of the 274 "users disagree" pieces are typed (276 comment lines -> 146: 145 untyped pieces plus the
D_0046A688 table, whose comment has another format); D_003E8D04's stale comment was fixed. 82 are basic
types (s32/u32, T/T[] sized to the piece, M2C_UNK, char/u8, volatile where every user already reads the
name as volatile), 47 struct, struct-pointer or pointer types. `make` stayed byte-identical after each
batch, and the M12 float build's kh1-shift.elf is unchanged (same sha256 as KH1_F25_C).

- Unlike session 24, every user includes include/data/pieces/D_X.h **in place of** its own extern, so the
  users really compile against the shared declaration. A piece was accepted only if the `-S` output of
  every changed file (its objects.mk recipe) stayed identical and no new warning appeared; per-file `-S`
  catches what an end-of-file include cannot.
- Hand files only change declarations. src/auto/ users whose declaration differed keep their code through
  a cast to the type they had (`(*(s32 *)&D_X)`, `((M2C_UNK *)&D_X)`): same lvalue, but expression edits.
- Struct types moved with type_pieces.move_types into 18 new headers in include/data/types/ (`_pN.h` where
  the file's header existed; no shared header grew).
- Some picks follow the code, not the meaning: D_002BBF60, D_002BC020, D_002A6C10 are `s32 [4][4]`
  (text_00100000_b00.c copies them as ints; h52 calls them Mtx52, f32), and D_002A6C60 is a scalar
  `volatile unsigned char` for a 0x3400-byte piece (its one auto user's declaration). Some struct pieces
  keep `T D[]` without a size.
- The 145 left: each comment says `session 25: as <decl tried>: does not compile in X / code changes in Y /
  new warning in Z`. They need real work: one struct per object with the hand users' fields renamed, or
  casts in hand code; volatile mismatches change code (D_002A3F50).
- Helpers: tools/shift/s25types/ (s25_unify.py one piece + one declaration with the `-S` check; the drive
  scripts batch it; README there).

## Session 26: the memory map past 0x820000, and everything floats

### The fixed regions (static scan of the ELF and all twelve overlays)

Every `lui` of 0x82..0x1FF (and the 0x20/0x30 mirrors) paired with an `addiu`/load in the main ELF's
code, and in each overlay: the `ori` pairs and unpaired `lui`s are masks, colours and float bits.

| Region | Who names it | What it is |
| --- | --- | --- |
| 0x6A0000-0x7F2C00 | func_0014a090, func_00133628 | the fixed pools (session 25); 0x7F2C00-0x820000 unused |
| **0x820000-0x9A0000** | func_00121c78 (base), func_00121d60 (end, D_009A0000) | a block heap: 511 20-byte records from D_004F45B0 (+4 start, +8 size, +0x10 next); the head's block starts at D_00820000 |
| 0x9A0000-0xF20000 | func_00109388 (func_0011cb80 / func_0011cd20 at boot), func_001129c8 (D_004D92DC = D_009A0000), dktitle.x (0x9A0000 and 0xBA0000) | a load area; in the savestates up to 0xE42100 |
| 0xF20000- | 28 places; every overlay is linked there | overlays; wm.x's bss runs to about 0x1090000, so it overlaps the next region while the world map is loaded |
| 0xF45200 | func_001e1c20 | a fixed address inside the overlay area |
| 0xFE0000-0x12E0000 | func_00124218, func_00155760, func_00155878, func_001559a8, func_001559f0, func_00155c68 | 12 slots of 0x40000 (D_00550400, 72-byte entries; `sra 18` maps an address back to its slot) |
| 0x1CE0000- | func_00155a50 (returns it) | used up to the stack in every savestate |
| 0x1FE0000 | crt0 (func_00100008) | the stack |

Only func_00121c78 names 0x820000 (no overlay does), and nothing holds an address inside the heap at
build time. The overlays at 0xF20000 cannot move (linked there), and dktitle.x names 0x9A0000 itself, so
the load area stays.

### How much each region uses: tools/shift/mem_regions.py

`python3 -I tools/shift/mem_regions.py STATE.p2s [--heap-base N]` prints, per region, the last non-zero
byte (an upper bound on the high-water mark: PCSX2 starts with zeroed RAM and freed memory keeps its
bytes) and a map of 64 KB blocks, and walks the heap's free list. Over the session 19-26 savestates
(title, Agrabah, Gate Plaza, fights, the ship, End of the World):

| State | heap blocks in use | heap high-water (from the base) |
| --- | --- | --- |
| s19_f19d_title | 1 | 0 |
| s19_fight1 (Agrabah fight) | 65 | 0x9E038 (the largest) |
| s21_q4000_agrabah | 42 | 0x65D34 |
| s22_pad_alley (Gate Plaza) | 55 | 0x78780 |
| s26_f26a_ship (Neverland, fight) | 53 | 0x79040 |
| s26_f26b_eotw (End of the World, fight) | 62 | 0x69708 |

The heap is 0x180000 bytes; the game uses at most about 0xA0000 of it in these states.

### shift_ld BLOCK_HEAP: the heap base follows the pools

In the moved modes `D_00820000 = MAX(0x820000, ALIGN(D_00720000 + pools, 0x1000))`, so the base moves
only once the pools reach it; its end stays at D_009A0000, so the heap shrinks by as much.
`ASSERT(D_00820000 + 0xE0000 <= 0x9A0000)` (BLOCK_HEAP_MIN: the high-water mark above plus a margin)
replaces session 25's "pools must end by 0x820000". shift_cmp maps the base and prints "block heap base
moved after the pools". `SHIFT_FIXED_HEAP=1` (`--fixed-heap`) keeps it at 0x820000 (then the old assert
applies).

**Defaults are now data 0x100000, bss 0x100000**: the budgets leave nothing out
(float_over_budget.tsv is empty). The three big tables (D_0040EF80, D_002E31F0, D_00308CE0) and the
D_004F8310 / 0x30C9C bss runs float. KH1_F26_A = the default build: 1,602 floated variables, `_end`
0x74B164, pools at 0x756000, heap at 0x8A9000 (0xF7000 of 0x180000 left).

| ELF | build | result |
| --- | --- | --- |
| F26_A | the default (everything the checks allow) | load menu, test T, a fight in Gate Plaza, world map warp drive to Neverland, a fight on the ship: OK; float_holes: 0 of 1,602 floated names written at their old place |
| F26_B | + SHIFT_FLOAT_FORCE="D_0046E120 D_00472160" (DMA chains 0 and 1-2 whole), heap at 0x8B5000 | test T and a fight in Gate Plaza, save 05 (End of the World) and a fight there: OK |

**Every floated byte costs twice**: the blob keeps the original slot, and the copy goes after the image,
so each name floated shrinks the block heap. With the staging arena D_003F8380 (0x16C00) forced as well,
the link fails the BLOCK_HEAP_MIN assert. Cutting floated pieces out of the blob (or ending the blob
at the last kept name) is what gives the room back; that is the next step if more must float.

### What the float still pins

1,848 names stay in place in the default build: reach_check 1,803 (an index or a walk may run into the
next name), addend_check 72, cover_check, split_check and float_keep.txt (several overlap).
keep_check's 38 runtime names are all still held, and all but D_0063F540, D_002A6274/78 (addend_check)
and the merged labels are held by reach_check by itself, so float_keep.txt only adds D_0063F540 today.
The pins that runtime has shown to be safe as whole pieces: DMA chains 0 and 1-2 (F24_REC3, F26_B). They
stay pinned because reach_check finds the indexing that crosses into the next chain (idx-next) and each
costs heap; floating them is a SHIFT_FLOAT_FORCE experiment, not the default.

## Session 26: Phase 4 types (worker s26types)

143 of the 145 "users disagree" pieces that session 25 left (`session 25: as <decl>: ...`) are typed:
each has include/data/pieces/D_X.h, and every C user includes it in place of its own extern(s), file
scope or block scope. `make` stayed byte-identical after every batch; every changed file's `-S` was
checked against the previous version (no new warning). 383 C files changed (276 hand, 107 auto),
178 new headers (143 pieces, 35 types), all compile on their own (s26_hdrcheck.py). The shift/float
build was not run (types emit no code and the objects are byte-identical; another worker owns the float).

| how | pieces |
| --- | ---: |
| one declaration, users whose own type differs cast at each use (s26_cast.py) | 128 |
| a union of the users' views, each user names its member (s26_union.py, by hand for the UV tables) | 12 |
| one declaration, users convert values (D_0046A040, D_003DABD0) | 2 |
| a struct the users index differently (D_0048C6F0 `V4i_48C6F0 { s32 v[4]; } [8]`) | 1 |
| left untyped (D_002E26A0, D_003044D8) | 2 |

The shared types: 36 `s32`, 31 `u8 [n]` (byte blocks seen as several structs), 9 `void *`,
6 `f32`, 5 `u32`, and about 50 struct/union types (moved from the chosen user into include/data/types,
or self-contained in the piece header under a unique name: SV62B4, Blk26C0, UvTab16, U<addr>...).

### What changed in the users

- A user whose declaration differs keeps its exact code through casts at each use: an int/pointer
  scalar is read as a converted value (`((Grid *)D_X)`), stored as one (`D_X = (s32)p;`); other views
  use the lvalue they declared (`(*(Cam *)&D_X).unk7C`, `((f32 *)&D_X)` for a `T D_X[]` user,
  `((T (*)[n])&D_X)` for `&D_X`). Volatile users keep `volatile` in their cast. A pointer-array user of a
  pointer-array name converts each element read (`((Act *)D_X[i])`).
- Unions (D_002BC0C0/F0, D_002BC0A8, D_00304DB0, D_00351A30, D_003F2C40, D_003E3D70, D_0037A380,
  D_00364130, D_0035BD40, the UV tables D_002A3F60/D_002A4060): the piece header holds one uniquely named
  copy of each view's type (`View30_2BC0C0`, with the view's own typedef dependencies and struct tags)
  and `typedef union { ... } U<addr>;`; the user's typedef becomes an alias (`typedef View30_2BC0C0 View30;`)
  where it was, and its code names its member (`D_002BC0C0.view30`, `D_002A3F60.f[i][0]`). A view whose
  type lives in a data/types header shared with other files brings that header into the piece header.
- A few lines were only reformatted (an extern split from a typedef or a prototype on the same line).
- `.s` comments: `/* data/pieces/D_X.h */` as before.

### Hazards

- **Union member accesses get alias set 0 in gcc 2.96** (type punning through a union is allowed), so a
  user whose scheduling relied on type-based aliasing changes code through a union (D_003044D8's s8_lead,
  most of D_002E26A0's users). Casts through a pointer (`*(T *)&D_X`) also change the MEM flags
  (MEM_IN_STRUCT_P / scalar) and can move loads; value casts of a scalar (`(T *)D_X`) and element casts
  (`(T *)D_X[i]`) were not seen to change code in this session (the -S check still decides each file).
- An array declaration vs a scalar one changes code too (an `ARRAY_REF` is in-struct, a scalar `VAR_DECL`
  is not): src/auto/text_00120000_15.c reloads D_002E26A0 after a store only when it is a scalar.
- The `-S` check now accepts output that differs only in local label numbers (`$L12`/`$LC3`, renumbered by
  first use; `S26_STRICT=1` for exact): gcc's label counter moves when a declaration moves. `make` checks
  the bytes.
- Several pieces' records overrun the piece (D_003F2C40: 0x14-byte entries in 0x10; D_003E3D70: 0xe4 in
  0xe0; D_003044D8; D_003DABD0 `void *[]` with users reading [1]): their union members are zero-length
  arrays (`[size / sizeof]` = 0) or `[]`. The tables continue into the next pieces (split_check groups).
- D_00308CDC is `void *volatile` (h56's store needs it); the other users read it through a non-volatile
  cast, exactly as before. Shared declarations are not a statement about the qualifier the data needs.
- The piece headers are included where the extern was, mid-file; moving them changes nothing only if the
  types they bring do not clash (s26_hdrcheck.py checks each header alone, not every combination).

### Left

- D_002E26A0 (63 users, 0xc): `void *D_002E26A0[3]` with element casts keeps every hand user, but
  src/auto/text_00120000_15.c needs a scalar `void *` declaration (see above). Typing it needs that auto
  function's code written another way.
- D_003044D8 (7 users, 16-byte records): six views; s8_lead's ColEntA changes code through a union or a
  cast, c02/s6_03 change under ColEntA. Needs one merged record struct and the users' field accesses
  rewritten to it, function by function.
- The 128 cast-unified pieces are correct but not pretty: many users still see their own struct through a
  cast. Folding their views into one struct (or a union, where no user depends on TBAA) is the next step.
- The 63 "no C user declares it (merged)" pieces: none has a C user of its head (three heads are named
  only by their own label headers), so nothing was typed there.

Helpers: tools/shift/s26types/ (README there): s26_cast.py (one declaration + casts; `hdr` for hand
unifications), s26_union.py (union of views, `--elem`, `--cast F`), s26_check.py (-S of changed files vs
HEAD), s26_hdrcheck.py.

## Session 27: floated slots are given back (SHIFT_FLOAT_COMPACT, default on)

Until session 26 a floated variable cost its size twice: its original slot stayed in the layout as a hole
(`. += size` in the .data script; an empty range of .bss) and the copy went after the image, so every name
floated pushed `_end`, the fixed pools and the block heap up.

### shift_ld --float-compact

- After the budgets, every run of **contiguous** floated slots (data: the `primary` blob list; bss: the floated
  runs) is a hole. It shrinks by the largest multiple of **64** (`COMPACT_ALIGN`) that fits; the rest of the hole
  stays. Everything after it moves down by the shrink, so every kept name keeps its offset inside its cache line
  (the same 64 float_align keeps for floated names: DMA, SIF and cache-range code rely on it). Kept sections
  aligned beyond 64 would make shift_ld fail (none today). Holes shorter than 64 bytes stay.
- Data: the shrink is taken from the run's last slots (`. += size - cut`, or a comment when a slot is gone
  entirely). Bss: kept variables are placed at `D_BSS + compact offset`, and the end of the original .bss as well.
- Every `D_BLOB + off` / `D_BSS ± off` the script and blob.s emit (tail names, `.rodup_` merged rodata copies,
  `.word D_BLOB+x` / `D_BSS+x` blob relocations) is rewritten with the piecewise map (`CompactMap`): subtract what
  the holes ending at or before the address gave back. An address strictly inside a hole is an error (the older
  in_floated check already refuses names and blob words that point into a floated variable).
- `out/shift/<mode>-float/compact.tsv` (region, start, end, shrink per hole) feeds shift_cmp.py (bss pieces
  between floated variables move by `delta - given back`; data pieces come from the link map as before) and
  float_holes.py (only the first `size - shrink` bytes of each hole are still a hole).
- overlay_relocs.py now names an overlay target outside the C variables `D_XXXXXXXX` (shift_ld defines it like
  any other name, compact or not) instead of `D_BLOB+x`; there were none today. shift_ld collects the fixup
  table's undefined names too (and skips its `__dr_` labels, which `--ovl-labels` defines).
- Makefile: `SHIFT_FLOAT_COMPACT ?= 1`; `SHIFT_FLOAT_COMPACT=0` keeps the holes (output dir `m12-float-holes`).
  The holes build is byte-identical to session 26's default (KH1_F26_A).
- crt0: `_gp` = `_edata` and D_BSS = `_gp + 0x30` still hold (0x004A3DD0 / 0x004A3E00); shift_cmp checks them.

| | holes (F26_A) | compact (F27_C1) |
| --- | --- | --- |
| data given back | 0 | 0x89880 (90 holes; 1,082 floated data slots, most in runs) |
| bss given back | 0 | 0x3B640 (28 holes) |
| `_end` | 0x74B164 | 0x6862A4 |
| fixed pools | moved to 0x756000 | back at 0x6A0000 (`_end + 0xA000` is below it) |
| block heap | 0x8A9000 (0xF7000 left) | back at 0x820000 (0x180000) |

### Floating is now free

With compaction a forced name gives its slot back, so floating more no longer shrinks anything: KH1_F27_C2 =
default + `SHIFT_FLOAT_FORCE="D_003F8380 D_0046E120 D_00472160"` (the 0x16C00 staging arena, which session 26
could not fit, and DMA chains 0 and 1-2) has the same `_end` 0x6862A4 (0xAC540 data bytes given back).

| ELF | build | result (PCSX2) |
| --- | --- | --- |
| F27_C1 | the default (compact) | load menu, test T, Gate Plaza into the desert (area change) and a fight there, world map warp drive to Neverland, a fight on the ship, save 05 End of the World and a fight; float_holes 0 of 1,602; block heap at 0x820000, high-water 0x899040 |
| F27_C2 | + staging arena and chains 0, 1-2 forced | test T, a desert fight, End of the World (the field is drawn: the staging arena whole is fine) and a fight; float_holes 0 of 1,605 |

The forced names stay out of the default: reach_check still pins them (D_003F8370's index may reach the arena;
the chains' idx-next), and float_keep.txt lists them. The IOP block (D_0063D640, 0x2000 bytes the IOP writes by
DMA) cannot be tried this way: it is not a C object, only its fields D_0063F248 / D_0063F540 are, and those
fail alone (session 18). It needs a piece covering the whole block first.

## Session 27: Phase 4 types (worker s27types)

### Result

Counted with `s27_survey.py --summary` (casts of a piece's name in src/):

| | base a5c8821 | now |
|---|---|---|
| view casts (a user's own struct type) | 1541 in 104 pieces | 796 in 85 pieces |
| shared casts (to the folded struct, keep mode) | 0 | 188 |
| basic casts (s32, u8 *, void *, ...) | 676 | 734 |

- 43 pieces folded: 21 with no view cast left (D_002A3F3C D_002BCB60 D_002BCDA0
  D_002C5960 D_002E27C8 D_002E319C D_00304B78 D_00304C70 D_003701D0 D_003DABD4
  D_003E8E08 D_003F34B8 D_003F34C4 D_003F4CF0 D_003F7C48 D_003F7ED0 D_00425BC8
  D_004268B0 D_00426970 D_00449908 D_0048C630), 22 partly (biggest: D_00304BE8
  262->172, D_002E31B0 37->16, D_002A6238 49->34, D_002A624C 35->1, D_0037A378 18->2).
  48 piece headers carry a "session 27 folded" struct.
- 745 of 1541 view casts gone; 191 needless basic casts dropped by `s27_trim.py`.
  The basic count rose because folded users of a piece whose declaration stayed a
  basic type got value / lvalue casts to keep their code (see hazards).

### Left, and why (`s27_reasons.py` over the batch logs)

- Pointer pieces (declaration is a pointer or array of pointers, the view is behind
  it): D_00308CDC (44), D_002E3170 (20), several 1-cast pieces.  The fold handles
  `(S *)&D_X` / `((S *)D_X)` views of the object itself only.
- D_0037A380 (115, the session 26 union piece): users' views hold fields of their
  own vector types (V4, V3_2e2780) at different places, and one user warns.
- Overlaps (13 users): two users read one offset as different fields (e.g.
  D_002C1260 `mn` vs `lo`); needs a union, i.e. alias set 0 -> code changes.
- Union views (12 users): F5968 etc. are unions; folding would change aliasing.
- Field of a local non-struct type, or a local type in two places (8).
- Other users stop compiling (7) or change code (5) once the declaration changes
  (e.g. D_0029B420: indexing a scalar; D_002E2790: text_00130000_b03.c CODE).
- Keep mode needs at least 2 folded files; single-view pieces stay as cast.
- D_002E26A0 and D_003044D8 (need a code shape change): not started.
- D_00425B80, D_002C5C80, D_0039A580, D_004268E0, D_003626F0: an early full-mode fold
  gave union users value casts to the struct-typed old declaration; few, left.
- text_00210000_s6_21.c (nogcse) keeps a local `S4BE8_304be8_v` copy of the save
  block view (folding changes its code).
- Earlier folds dropped some `#include "data/types/..."` lines from piece headers
  (the old view types); make is unchanged, but a user that relied on them gets them
  from its own includes now.

### Hazards found (gcc 2.96)

- Changing a declaration's type changes the alias set of its own loads: a scalar
  declared s32 that becomes a pointer/struct changes code in plain users.  Plain
  users then need lvalue casts `(*(s32 *)&D_X)` (only done when the old declaration
  is a basic type).
- A bigger header changes code in unrelated later functions of a file (address
  hashed tables; e.g. text_00150000_h58.c func_00157a30).  Split mode: the struct
  goes to `D_X_s.h`, only folded users include it.
- `void *` vs `struct S *` declaration also changes code (h58).
- Union member accesses get alias set 0, so union views are not merged.
- Array vs scalar declarations change addressing; arrays of struct with different
  lengths are joined, reframing only when all used subfields stay in one element.
- Signed / unsigned field differences are accepted when `-S` stays the same.

### Tools

See README.md: s27_fold (with s27_layout, s27_merge, s27_ctext, s27lib), s27_batch,
s27_reasons, s27_survey, s27_trim, s27_unfold, s27_check, s27_hdrcheck.

## Session 27: reach_check rules (worker s27reach)

reach_check now pins **1,347** names (was 1,803): 467 released,
11 newly pinned (coverage the more precise analysis found). Each rule has a `--no-*` switch
(SHIFT_REACH_FLAGS); with all seven off the output is byte-identical to session 26's float_reach.txt.

### The 1,803 names by reason (session 26 float_reach.log)

Counted by the reasons of every hit that pins a name (a name with one reason only):

| reason | names | what it was |
| --- | --- | --- |
| arg:noreach | 343 | an address in an argument register the callee never reads (left over), or one it stores or DMAs |
| arg:wide | 252 | the callee walks the argument: printf formats, strcat sources, -1-terminated lists, DMA senders |
| idx | 180 | an unbounded index; many were loop counters whose bound widened away |
| stored | 80 | the address is stored, mostly as a stack argument (func_0023b570 -> func_0023aed0's 9th+ arguments) |
| idx-ub | 40 | a bounded index that ends past the next name |

By callee: func_00106b18 / func_00106bd8 / func_00266f38 (DMA chain senders, ~100), scePrintf (47),
func_0010ef70 (26, a window's text pointer), func_00237018 (21, a GIF packet sender),
func_0024afc0 / func_0024af40 (36, -1-terminated index lists), func_00106cd0 (18, DMA ref tags).

### The rules (names each releases on its own, from the final 1,347: `--no-RULE` re-pins them)

| rule (switch) | releases | what it proves |
| --- | --- | --- |
| dead-arg (`--no-dead-arg`) | 184 | `arg_live()`: per function, the argument registers it may read before writing them on any path, through its calls and tail calls (least fixpoint over the call graph). An address left in a0-t3 at a call is not an argument when the callee never reads that register. Conservative: an unknown callee, jalr, a switch `jr`, a branch out of the function or a fall-through past its end read every register; a syscall reads all unless `li v1,N` names one of the SYSCALL_ARGS (FlushCache, semaphores, Enable/DisableIntc/Dmac ...). After a jal the caller-saved registers are dead (EE ABI). |
| counter-cap (`--no-counter-cap`) | 21 | an up-counter loop `i = i0; do { ...; i += k; } while (i < L)` (countdown_loops' up-counter pattern, now listed even with no walked pointer) caps i at its header at max(i0, L-1) (+k when the test sees i before the step). Before, the counter's bound grew 0, 1, 2 and widened to unknown before the slti could cap it, and every index made from it was unbounded (func_00219870's `D[i]` for i < 12). |
| slot-refine (`--no-slot-refine`) | 32 | a `beq/bne t,$0` edge refines the state before the branch's delay slot, not after: `bne v1,$0,loop; sll v0,s2,2` now scales the capped counter. Also reads more switch tables (`sltiu v0,v1,7; beqz v0; sll v0,v1,2` gives the table index its bound), so a switch goes to its cases instead of every label: this both releases names (D_002C64A0) and pins 10 new ones (libc's stored addresses D_00491B40 ..., D_00491D30 ...; they floated in F26_A). |
| str-arg (`--no-str-arg`) | 77 | STRING_ARGS: printf-family formats (scePrintf, func_00259c88, printf, sprintf arg 1), puts/strlen/strcmp/strncmp/strcpy src/strcat src, func_001ea268's encoded-text source. A literal in .data whose first NUL is inside its own object, followed by at most 15 zero bytes (a buffer has a long zero tail or no text), and that no store the analysis sees writes, is read to its NUL. Formats: every `%` must start a whole conversion (func_00259698 skips the byte after a lone `%`, past a NUL). func_001ea268: no control byte 5-7 or 9-31 before the NUL (they take parameter bytes). The callee's quadword reads past the NUL are discarded, so the `arg1:strcat:32` hits are dropped too. |
| list-arg (`--no-list-arg`) | 49 | LIST_CALLS: func_0024afc0(list, out, hdr) and func_0024af40 read a word list to -1 and write 4 / 0xC0 bytes per element to out; func_0024c8b8 reads halfwords to a negative one. A list literal (terminator then at most 12 zero bytes to the next name, no seen store) gives the count, which bounds the list and out at the same call. |
| dma-count (`--no-dma-count`) | 45 | DMA_COUNT_CALLS (block accesses like memcpy's): func_00237018(buf, n) writes an end tag with qwc n-1 at buf and sends buf in chain mode, so 16*n bytes (D_006480D0 is exactly 0x160 = 16*22); func_00106cd0(addr, qwc) appends a ref tag (0x30000000+qwc, addr) to D_00494A90's chain: 16*qwc bytes at addr. Needs a constant count at the call. |
| dma-chain (`--no-dma-chain`) | 99 | CHAIN_CALLS: func_00106b18(chain), func_00106bd8(chain, ...) (through func_00106b98's callback) and func_00266f38(channel, chain) start a chain-mode DMA at the chain. A chain object passed only to these, never stored, uncached, indexed or written by a seen store, whose tags parse (refe/cnt/ref/end only, at most 256, all inside the object) is read to its end tag; each ref/refe target gets an access of 16*qwc bytes from its address (`dma-ref`), so a target whose transfer runs into the next name pins it (D_002BC9B0, new). |

The seven together: 1,803 -> 1,347. `--explain FILE` writes one line per `&B[i]` passed to a call (base,
reason, caller, callee, argument, bound) for the next round. tests/reach_check_test.py covers each rule.

### The default float build, and the actor table

- With all seven rules and compaction (`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` at the end of session 27):
  **2,051 floated names** (was 1,602 in F27_C1), memsz 0x587564 so `_end` **0x687564**: the pools stay at
  0x6A0000 and the block heap at 0x820000. keep_check 38/38, M12-FLOAT OK.
- The worker's branch kept D_00278B50 (0x225F0) and D_002C64A0 (0x1C200) in float_keep.txt for room only: with
  SHIFT_FLOAT_COMPACT a floated slot is given back, so both were taken out again.
- **KH1_F27_R1** (all rules, both floating) loaded save 06 (Agrabah) **without Donald and Goofy**; the rest of
  the field was fine. Bisection, each ELF booted to save 06:

| ELF | build | party |
| --- | --- | --- |
| R1 | all rules | missing |
| R2 | `--no-str-arg` | missing |
| R3 | `--no-dma-chain --no-dma-count --no-list-arg` | missing |
| R4 | all seven off | present (byte-identical to F27_C1) |
| R5 | dead-arg only | present |
| R6 | dead-arg + counter-cap | present |
| R8 | R6 + 14 of slot-refine's releases forced | missing |
| R9 | R6 + 7 of them | missing |
| R10 | R6 + D_002A3F50, D_002BD1F0, D_002C64A0 | missing |
| R11 | R6 + D_002A3F50 | present |

- **D_002C64A0 is the actor table**: 1200-byte entries up to D_002E26A0, and the code walks it with the *next*
  name as its end (`if (p >= D_002E26A0) p = D_002C64A0`, text_00110000_h30.c and others; func_00145aa0 indexes
  up to it). The address of D_002E26A0 is the table's end, so the table cannot move away from it. reach_check
  sees a compare against another name's address, not an access, so no rule pins it. float_keep.txt pins
  D_002C64A0 with this note. A reach_check rule for "address of the next name used as an end bound" (a
  `sltu`/`slt` against `&NEXT`) would find any others.
- **KH1_F27_R12** (all rules + the D_002C64A0 pin, the default now): save 06 with the party, test T, Gate Plaza
  into the desert and a fight, the warp drive to Neverland and a fight on the ship, save 05 End of the World
  (field drawn) and a fight, the in-game menu. float_holes 0 of 2,051; block heap at 0x820000, top block
  0x872980, high-water 0x89A380.

### Riskiest releases (for the boot route)

- **dma-chain (99)**: the DMA chains of func_00100988 / func_001008e8 (D_0029B170 ...), func_00102118
  (D_002A4310 ... D_002A4570), func_001032b0's ref tags (D_002A46D0 ... D_002A48D0, dma-count),
  func_00103058 / func_00102a48 / func_00102da8 / func_00103c48 / func_001039f8 (D_002A4B60 ... D_002A6B80),
  func_00106000 / func_0010b6c0 / func_0010f658 (D_002B65E0 ... D_002BD140), and the VU/VIF chains
  func_0015fc00 sends (D_00277E40 when `e->o->x48 & 0x10` with `fl & 8`, D_00278210 otherwise) and
  func_0015f018 (D_00278680 on VIF0 at init). A tag the game patches through a pointer would break the
  static parse: watch the title, fades, the load menu, and any model drawn with that special mode.
- **list-arg / dma-count (94)**: the 0x00237000-0x0024A000 module: func_0023b570 / func_0023cf30 /
  func_0023cfe8 / func_00243a90 build 0xC0-byte records from the lists (D_00449900, D_0044A810,
  D_00454558 ...) into bss (D_0064FD60, D_00651BD8 ...), and func_002372e0 ... func_00249010 send GIF
  packets (D_006480D0, D_00648630 ..., 16*n bytes). Find what it draws (menu/HUD 3D?) and exercise it.
- **str-arg file names**: strcat sources ".img" / ".dat" / "00_" (D_0048CC30, D_0048D000, D_0048D008,
  D_0048D128, D_002BCC88) and sprintf formats "%s_%s" / "%s%s" (D_0048D320, D_0048DCB0, D_0048E410):
  file loading; a wrong byte shows as a failed load. D_003DD238 / D_003DD240 ("\x01", "\x04") feed
  func_001ea268's text.
- dead-arg, counter-cap and slot-refine are general and argued from the code; the 10 names slot-refine
  newly pins floated in F26_A without trouble.

### Left pinned (the largest groups)

- idx (187 names by that reason alone): a long tail, 2-6 names per function. Many are nested loops whose
  inner counter carries over the outer loop (func_00103a70's 4x4 copy: t5 counts 16 across both loops);
  that needs relational bounds.
- stored (94): func_0023b570 passes 9+ arguments to func_0023aed0 on the stack (38 names); stack
  arguments are not followed.
- arg:noreach / arg:wide that are real: func_0010ef70 (a window keeps the text pointer; the renderer's
  control codes are not verified), sceGsExecLoadImage via func_0010c438 (16), func_001e05a8, printf `%s`
  arguments.

## Session 28: end pointers, the IOP block and D_BLOB

### reach_check end-ptr (`--no-end-ptr`)

A compare or subtract of a value against an exact image address A is an *end use* of A:
`slt`/`sltu` with A on either side (`p < &N` and `&N <= p` look the same), `subu` with A as the minuend
(`&N - p`; `p - &N` is an index into N and does not count), and `beq`/`bne` of A against a pointer the
analysis knows came from another address (a walk: `p != &N`; an identity test `o == &N` against an
unknown value does not count). When A starts a name N, the object before N must stay next to it, so
the hit is (previous name -> N, `end-ptr[end-lt|end-sub|end-eq]`).

- It finds the actor table by itself: func_00123810 and func_001230a0 compare the walk against
  &D_002E26A0 (`sltu v1,v0,a3`), so D_002C64A0 is pinned without float_keep.txt (taken out of it;
  keep_check now lists it, so a rule change cannot float it again).
- 20 addresses are end uses, 10 tie two pieces; only D_002C64A0 is new (the rest were pinned already:
  D_002BCA00, D_002E3168, D_00372F28, D_0045FAC0, D_004F45B0, D_0052AE70/98, D_00547C00, D_0054F438).
- tests/reach_check_test.py case 10 covers the four shapes.

### The IOP status block is one piece (src/data/data_0063.s)

D_0063D640 (0x2000 bytes the sound IOP module writes by DMA) was not a C object: only its fields
D_0063F248 (+0x1c08, defined in src/auto/text_001e0000.c) and D_0063F540 (+0x1f00, src/data/bss_0063.c)
were, and D_0063EE40 (+0x1800) was a linker name. It is now one zero-filled `.data.D_0063D640` section
(.space only, like the C bss names, which -fdata-sections makes progbits) with the three fields as
PIECE_LABELs; the two C definitions became externs. `make` is byte-identical, data.tsv has 1,043 bss
variables (one fewer), and keep_check maps the fields to the piece. float_keep.txt keeps D_0063D640
until a forced build has played (the IOP learns the address from D_00633640[0] = D_0063D640, a code
relocation, so the copy should work).

### D_BLOB when the first data object floats

shift_cmp used to check D_BLOB through the address map, which sends 0x272C70 to D_00272C70's copy once it
floats. D_BLOB is the start of .data in both links (`D_BLOB = .;` first in .data), so it is now checked as
that. `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1 SHIFT_FLOAT_FORCE="D_00272C70 D_0063D640"` links and passes
M12-FLOAT (built with an empty overlay directory, so the overlay table was empty: rebuild with the
overlays before booting). D_00272C70 stays in float_keep.txt until that build has played.

### Tried and dropped: global-bound

A rule bounding loads of a global word that every seen store sets to a small constant (aimed at
func_00233168's `D_003F8370[D_00351E10.x4]`, x4 = memory card port 0/1, which pins the staging arena
D_003F8380): it found 25 such words but released nothing, because D_00351E10's address is passed to
dozens of callees (func_0011fec0, func_00163150, func_00163490 ...) and unbounded indexed stores from
func_0014f830/func_0015ff78 may reach it, so x4 cannot be proved. Not committed. Releasing D_003F8380 needs
either those callees' writes followed or a runtime test with SHIFT_FLOAT_FORCE (F27_C2 played with it).

### Left in reach_check

- stored (func_0023b570 -> func_0023aed0's stack arguments): following the stack arguments would not
  help: func_0023aed0 stores every pointer into its Out record (o->p6 ... o->p17), and p9/p15 are filled
  for i < n (a runtime count), so the names stay stored either way.
- idx (nested loops whose inner counter carries across the outer loop) still needs relational bounds.

## Session 28: Phase 4 types (worker s28types)

### Result

Counted with `s27_survey.py --summary` (the session 28 survey: a header type with
`__attribute__((...))` before its name counts as shared; the base count is the
same with either survey):

| | base 2629fbe | now |
|---|---|---|
| view casts (a user's own struct type) | 796 in 85 pieces | 463 in 84 pieces |
| shared casts (to the piece header's own types) | 188 | 213 |
| basic casts (s32, u8 *, void *, ...) | 734 | 773 |

Per piece (view casts, base -> now):

| piece | before | after | how |
|---|---|---|---|
| D_0037A380 | 115 | 2 | c09b reads union member `scn`; camera view is member `cam` (Cam_37A380) |
| D_00304BE8 | 172 | 73 | 5 more users folded; 63 accesses renamed by `s28_partial.py` |
| D_00308CDC | 44 | 15 | `(V **)&D_X` views fold in keep mode (Cfg_308cdc, 7 users) |
| D_002C1260 | 26 | 0 | one Box_2c1260 { mn[3][4], mx[3][4] } (b01's Box01 goes) |
| D_00425F70 | 22 | 1 | h47 reads f140[] of Cam_425f70; D_00425D80 is a Cam_425f70 |
| D_002BC0F0 | 19 | 0 | h67's CamS is the union's camS; h17 casts to Cam0_2BC0F0 |
| D_002E3170 | 20 | 4 | `Q8_2e3170 *D_002E3170[8]`, the menu cursor stack |
| D_0048C690 | 11 | 0 | D_0048C630 / D_0048C690 are Blk32_48c630 |
| D_002A6238 | 34 | 27 | s28_partial |
| D_0036243C, D_00350D78, D_002E31A0, D_00362434, D_002E31B0, D_003626C0, D_00362430, D_002A6234 | 52 | 34 | s28_partial / s28_trim / retypes (D_002E31A0, D_002E319C are `O8_2e319c *`) |
| D_002E26A0 | (no header) | 24 | typed `void *D_002E26A0[3]` (63 users); element casts C does not need dropped |
| D_003044D8 | (no header) | 2 | typed `ColEnt_3044d8 D_003044D8[]` (7 users) |

The two code shape pieces of session 27 are typed: D_002E26A0 (the three player /
party pointers) and D_003044D8 (collision entity records).  Their users' own casts
now count in the survey (26 view casts left between them).  The basic count rose
mostly because of them: a user's `(s32 *)D_002E26A0` now is a cast of a typed piece.

### Left, and why

- D_00304BE8 (73): members at 0x18..0x70 are read as arrays by some users and as
  scalars or sub-structs at other offsets by others; s28_partial only renames a
  view field that is a whole field, an array, or an element of one in the struct.
- D_002A6238 (27): users partition the bits at 0x10 differently (bit-field layouts
  conflict); a union would get alias set 0 and change code.
- VM family (D_0039A580, D_0038D170, D_003C3A70, D_003A7990, D_003B4DA0, ~60): the
  view pointers are assigned to locals of the user's own VM / E848 / Obj350 types;
  folding needs one global VM type shared by those files' locals, not a cast rename.
- Vector pieces (D_002E2780, D_002E2790, D_002C58A0, D_002C58B0, D_002C58D0, ~60):
  passed to functions prototyped with each file's own V4 / V3 / V53; needs the
  vector types unified across the prototypes first.
- D_002C5968 (volatile flag word read through union views), D_00351E10 (QW buffer
  views), D_0036243C (Box tied to b06's V4), D_002E31B0 (pointer-typed fields):
  each user's view differs in a way that changes alias sets.
- Pieces with one view in one file: keep mode needs at least 2 users.

### Hazards found (gcc 2.96)

- Union member access sometimes keeps the code (c09b, s11_w15 on D_0037A380) and
  sometimes changes it (h42, h17): check every user; those that change cast to the
  member's type instead `(*(Cam_37A380 *)&D_X)`.
- Typing a piece as an array of pointers changed a reload after a store in an auto
  file (text_00120000_15.c): it reads element 0 as `*(s32 *)D_002E26A0` to keep it.
- Cast-lvalue chains `(u16 *)(*(O8 **)&D_X) = f()` must keep the `*(T **)&D_X` form
  even when D_X is already a `T *`: the plain form changes code.
- `((s32 *)&D_X)[8]` in an auto file changed code once D_X was a struct; the field
  form `D_X.x20.v[k]` keeps it.
- Piece types moved into data/types headers (session 24) are invisible to a parser
  of the .c alone; s28_partial parses them from the included headers and probes
  with the original text.

### Tools (tools/shift/s28types/)

- `s28_partial.py`: renames field accesses through a user's view to the piece
  struct's fields one access at a time (`(*(V *)&N).f`, `((V *)N)->f`,
  `((V *)N)[i].f` when the sizes match), -S checked per file.
- `s28_trim.py`: drops value casts of pointer pieces that C does not need
  (`((T *)D_X[i])`, `(*(T **)&D_X)`, `((T *)D_X)` not followed by `->` / `[`).
- `s28_dedup.py`: finds views that copy a header type text for text (found none).
- s27types changes: at most `S27_JOBS` (default 2) parallel compiles in all the
  s26/s27 tools; s27_fold skips files whose cast form differs from the declaration
  instead of failing, folds `(V **)&N` views (keep mode), and refolds split pieces.

## Session 29: the pending floats played, float_release.txt and nest-carry

### Runtime (PCSX2 on the user's Mac, 2026-10-23)

The Mac's shell sandbox (device_bash) would not start this session, so patch_iso.py ran through a Remote
Control session on the Mac (the folder tools only copy whole files and the ISO is 3.6 GB). A later run of the same
command was refused by that Mac's own Claude permission classifier ("Code from External"); the user then ran it
in Terminal. Each ELF is in /mnt/project-files/kh1-runtime/s29/ and Downloads/kh1-test/s29/.

| ELF | build | result |
| --- | --- | --- |
| KH1_F29_D | the session 28 default (`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`) | load menu, save 06 with the party, test T: OK |
| KH1_F29_F | D + `SHIFT_FLOAT_FORCE="D_00272C70 D_0063D640"` | save 06 with the party, test T, a desert fight, save 05 End of the World (field drawn), warp drive to Neverland (ship hold): OK |
| KH1_F29_G | F + `D_003F8380 D_0046E120 D_00472160` | the same route (Neverland: the clock tower): OK |
| KH1_F29_N | the new default (G's floats + nest-carry's 10 names; sha256 cc278ac0...) | save 06 with the party, test T, a desert fight, save 05 End of the World, warp drive to Neverland (ship hold): OK |

The IOP block floated means the sound module's replies, memory card reads and every area load went through the
moved block; nothing missing or garbled. Route notes: from save 06 test T's alley leads (walk left 4 s, right 3 s,
forward 3 s) into the desert at night ("砂漠への道"), where a fight starts within a few steps. On the world map
the left stick (W/A/S/D held 0.8 s / 0.25 s) moves between worlds and the D-pad toggles Normal / Warp Drive: from
End of the World, W 0.8 s is the warp hole and A 0.25 s is Neverland; its landing list is hold, cabin, clock tower.

### float_release.txt (`SHIFT_FLOAT_RELEASE ?= @tools/shift/float_release.txt`)

D_00272C70 left float_keep.txt (nothing else keeps it). D_0063D640, D_003F8380, D_0046E120 and D_00472160 also
left float_keep.txt, but reach_check pins them as idx-next (an index from the object before them that no rule
bounds: D_00635640's, D_003F8370's memory card slot index, the DMA chains' piece-next). They are listed in the new
tools/shift/float_release.txt, which float_force.py applies after keep_check in the default build: whole pieces a
PCSX2 build floated and played. keep_check still checks the keep list before the release (39/39). With the release
the default ELF was byte-identical to KH1_F29_G. `SHIFT_FLOAT_RELEASE=` (empty) keeps them in place again.
float_force.py now skips `#` comments in an @FILE.

### reach_check nest-carry (`--no-nest-carry`)

`nested_carries()` finds an outer loop around countdown_loops' inner loops (the same counter pattern, but inner
back edges are allowed), and:

- a register written once in the outer body, by `addiu r, r, k` inside an inner body and never reset (t5 in
  func_00103a70's 4x4 copy), is capped at the inner header at entry + k * (outer trips * inner trips - 1);
- a register the outer body steps once per iteration outside the inner loops (t6 += 4) is capped at the outer
  header like a walked pointer;
- countdown_loops' walked registers that are offsets, not pointers (t3 = t6 * 4, +4 per inner run), get the same
  cap from their entry bound (only with nest-carry on).

Trip counts come from back_edges() on the loops' entry states. It releases 10 names (1,348 -> 1,338 pinned):
D_0048CAE0 / D_0048CB28 / D_0048CB70 / D_0048CBB8 and D_00494930 / D_00494970 / D_004949B0 (func_00103a70's
matrix copies), D_003F4A48 / D_003F4A78 (func_00219870, 12 words each) and D_0048C630 (after the D_0048C390
piece, func_00107ec0). `--no-nest-carry` reproduces the session 28 list byte for byte; tests/reach_check_test.py
case 11 covers it.

## Session 29: Phase 4 types (worker s29types)

### Result

Counted with `s27_survey.py --summary` (unchanged survey):

| | base 152d0ec | now |
|---|---|---|
| view casts (a user's own struct type) | 463 in 84 pieces | 275 in 75 pieces |
| shared casts (to the piece header's own types) | 213 | 202 |
| basic casts (s32, u8 *, void *, ...) | 773 | 775 |

The shared count fell because casts to E848_3a7990 / V3_2e2780 went with the
casts they stood for; the two new basic casts are h62's `((f32 *)&D_002E2780)[j]`.

This session gives a piece and its users' locals one type, instead of renaming
casts: a file's own view type becomes an alias of the shared type
(`typedef VmRec VM;`) and its field accesses are renamed to the shared fields at
the same offsets (`s29_retype.py`), then the casts of the piece go because the
declaration has that type.

Per piece (view casts, base -> now):

| piece | before | after | how |
|---|---|---|---|
| D_0039A580, D_0038D170, D_003C3A70, D_003A7990, D_003B4DA0 | 62 | 0 | `VmRec D_X[]` (data/types/vm_rec.h); VM / VMa / VmC / VmE / VM_c2778 / KEnt / Ent / E848 / E848b / Obj350 of 16 files alias VmRec |
| D_002E2780, D_002E2790, D_002C58A0, D_002C58B0 | 71 | 0 | `FVec4 D_X` (data/types/fvec.h); the files' V4 / V4f / V3_2e2780 alias FVec4, h53's V53 is `typedef FVec4 V53 __attribute__((aligned(16)))` |
| D_00304BE8 | 73 | 18 | 22 user files read Save_304be8 / W606Mem_304be8 / Sub_304be8 (aliases; record views with `--shift`) |
| D_002C58D0 | 4 | 4 | left (see below) |

Also VM-typed locals of those files that do not cast the pieces now alias VmRec
(h43, h67 VM; s6_13 VmA; h66 VM_c0f30, VM_c1b58, VM_c91e8).

What changed besides the aliases:

- VmRec's `obj` (0x4) is `struct VmObj *`: each file that reads through it
  completes `struct VmObj` with its own entity view (`--objtag`: its typedef gets
  the tag).  h43's `D_00389C90.f3158`, compared with VM ids, became
  `struct VmObj *` too (a `void *` there kept a load in a loop: see hazards).
- `func_001c1ce8 / func_001c1cf8` take `s8 *` (the script) in c08, h66, h42 as in
  s6_13 (they read `code` at 0x70 as an s32 before); `func_00123488 / func_00123618`
  take `s32` in h67 / h68 as in the other files (they passed VM id 0x0 as
  `void *`).  c09 compares `(u32)pc` with `(u32)lbl[k]` where its view had u32.
- The top-level flag bits of b10 / b10n / s6_13 / w1 are `fl.b.bN` of VmFl (a union
  member: same code in every file here).  `f14..f20` is `f14[3], f20`.
- Users that read D_002E2780 / 90 as `f32[4]` pass `&D_X.x` and write `D_X.w`.
- Save_304be8's member: 0x18..0x32 is `x18, x19[8], x21, x22[0x10], x32` (counts
  and lists; h22 indexes x19[j] past 8 as its old a19[0x19] did; h8 reads
  `sub.x32` for the Q9c view); `x5..x7` named; `sub.x1c` renamed `sub.x18`.

### Left, and why

- D_00304BE8 (18): views whose index expression would change (s12w5
  `arr[j + 0x590]`, s6_20 DbSaveB `a[item + 32]`, h73 / s8_w8 Base4BE8 byte arrays
  `r[x * 116]`, s7_w4 `e[k + 1].b74`), arrays laid over other fields (r2_7
  `x1c[]` from the count byte, h56 `b[8]` over the first member bytes, s7_w3
  `s32 f844[3]` over s8 x844[3]), b03 / b03n B3Sv (a whole save copy with its
  own sub layout, also func_00232cc0's return type), s11_w44 P48E (a union),
  h30's `#define D_00304BE8 (*(C01Tbl74 **)&D_00304BE8)`, s6_21 (nogcse view).
- D_002C58D0 (4): the matrix users pass it as `f32 (*)[4]`, `u8 (*)[0x40]`,
  `f32 *` (basic) and as h30's V4 (f32[4]) array, h54n Mtx, c01 C01Mat, h61 V4;
  one matrix type for those needs h30's array V4 and c04's M4 locals retyped.
- b11's own VM (a second VM view in the file whose `obj` is an Actor while its Ent
  `owner` is an Obj): one `struct VmObj` per file; merging Actor and Obj there is
  needed first.
- The rest as session 28 left it (D_002A6238 bit-fields, D_002E26A0 actor
  pointers, D_002C5968, D_00308CDC, D_002E31B0, D_00351E10 ...).

### Hazards found (gcc 2.96)

- Pointer types have their own alias sets: a store through `struct VmObj *` no
  longer aliased a `void *` load, and gcc hoisted it out of a loop (h43).  Give
  both sides the same pointee type rather than casting.
- `typedef T V __attribute__((aligned(16)))` is the same type as T for argument
  checks, and locals declared V keep their 16-byte alignment: h53 kept its code.
- A struct alias replaces a view only if every field the file reads is at the same
  offset with the same type; s29_used finds the reads from gcc's errors, so a
  field named like a type (`u8 f32;`) must be renamed too (fixed in the tool).
- Record views that start before / after the shared record (`((T *)D)[k]` with T
  0x74 bytes from the block's start) fold with `--shift`: `&D->m[k].sub.x22`
  gives the same code as `&((T *)D)[k].x26` in every file tried.
- An alias may not land on padding: one map turned h58's b5 into `pad_5[0]`
  (named x5..x7 now; s29_retype skips pad members).

### Tools (tools/shift/s29types/, README there)

- `s29_stabs.py`: layouts from gcc's stabs (`-gstabs`), headers included.
- `s29_used.py`: the fields of a type a file reads (renamed-copy compile).
- `s29_retype.py`: a file's type becomes an alias of a shared one; accesses
  renamed by layout (`--map`, `--objtag`, `--sub`, `--hdr`, `--shift`, `--force`).
- `s29_recfold.py`: D_00304BE8 record views (`--shift 4` + `->m[k]`).
- `s29_uncast.py` (`--scalar`), `s29_asmdiff.py`.

## Session 30: Phase 4 types (worker s30types)

### Result

Counted with `s27_survey.py --summary` (unchanged survey):

| | base d7b6a3f | now |
|---|---|---|
| view casts (a user's own struct type) | 275 in 75 pieces | 217 in 72 pieces |
| shared casts (to the piece header's own types) | 202 | 202 |
| basic casts (s32, u8 *, void *, ...) | 775 | 750 |

The basic count fell with D_002C58D0's `f32 (*)[4]` / `u8 (*)[0x40]` / `f32 *` casts
(29 -> 5, the auto files' `M2C_UNK *` stay) and s7_w4's `(u8 *)D_00304BE8 + 0x874`.

Per piece (view casts, base -> now):

| piece | before | after | how |
|---|---|---|---|
| D_002C58D0 | 4 | 0 | `FMtx4 D_002C58D0` (`typedef f32 FMtx4[4][4]`, data/types/fvec.h): users pass `D_002C58D0` (f32 (*)[4] / void * / Mtx parameters) or `D_002C58D0[0]` (f32 * parameters); c04's M4, c01's C01Mat, h54n's Mtx alias FMtx4; h61's `#define D_002C58D0 (*(V4 *)&...)` goes |
| D_00304BE8 | 18 | 1 | s8_w8, h73, s7_w4, s7_w3, s12w5, s6_20, h56, b03, b03n, s11_w44, h30n, s6_21 read Save_304be8 / W606Mem_304be8 / Sub_304be8 |
| D_002A6238 | 27 | 2 | the word at 0x10 is a union Fl20_2a6238 of the users' five bit splits; h1 Ent20, h28 Ent14, h51 Tri20, h52 Plane52 / PolyV52, r2_10 ColE alias Ent20_2a6238 |
| D_002A62B0 | 8 | 0 | typed `Ent20_2a6238 *` (the second table h28 walks; s11_w56 casts the loaded address) |
| D_002A6274 | 4 | 0 | typed `Ent20_2a6238 *` (the table D_002A6238 is set from); h51n's Tri20 aliases Ent20_2a6238 |

Also b11 (nofill): its Actor (the jump op's obj, pos[3] at 0x10) is its Obj
(`struct VmObj`, V4 pos at 0x10; V4 is `FVec4` aligned 16), and its VM is
`typedef VmRec VM` (`flags` -> `fl`).  No piece casts there, so no count change.

What changed in the shared types:

- Save_304be8: 0x0 is `s32 x0` (b03's save copy sets it to 5), Sub_304be8's 0x8 is
  `x8[0x10]` (was pad), 0x38 `u16 x38` (b03n reads it unsigned; h6 / h7 only store
  0), and 0x34 is `union { struct { u8 x34; u8 x35; u16 x36; } h; struct { u32 :16;
  u32 b16:1; u32 :15; } b; } w34` (h30n read b16 as `x36 & 1` through a u16 view;
  `sub.x34` is `sub.w34.h.x34`, `sub.b16` is `sub.w34.b.b16`).
- Ent20_2a6238: 0xa / 0xb are `act` / `id` (h28's names; h1 b11, h51 group, r2_10
  xA), 0xc is an anonymous union `{ f32 d; s32 i; u16 h; }` (h51n reads an id there
  before the load stores the plane's d), 0x10 is `Fl20_2a6238 f` = `union { u32 w;
  EntBits_2a6238 e; OnBits_2a6238 o; TriBits_2a6238 t; PlaneBits_2a6238 p;
  ColBits_2a6238 c; }`.  Users that took `&D[i].f` as a word pointer use `.f.w`.
- Record views that started at the block (`((T *)D_00304BE8)[k]`, `r[k * 116]`,
  `e[k + 1].b74`, `arr[j + 0x590]`, `x[item + 0x490]`) became `m[k]`, `m[k].bits`,
  `list599[j]`, `items[item]` with the same code in every file tried here, the loop /
  PRE-sensitive s12w5 and the FLAGGED s11_w44 included.
- s7_w3's CONTEXT_ONLY copy of func_0012d368 read the three party slots at 0x844 as
  s32; it reads `x844[i]` (s8) like h31's real func_0012d368 now.  The context
  function's own -S changed (it is weak in `.ctx`, not placed); kh1.elf did not.

### Left, and why

- D_00304BE8 (1): r2_7's G4BE8c record starts at the block (`e = &v[n]`, then
  `&e->x4`, `e->x1c[s]`): with `&D->m[n].sub` gcc folds the +4 into `e` and the
  register / stack slot of `t` change (the file's comment documents a giv order).
- D_002A6238 (2): r2_10 reads the word at 0x10 as a u64 (`ColTri`, `(w & 0xff) >> 4
  == 11` compares with `dli`); a `kind == 11` bit-field compare uses `li`.  A u64
  member at 0x10 would run past the 20-byte record.
- h1's five `((Ent20 *)((u8 *)D_002A6238 + off))` (off = idx * 20) keep their basic
  `(u8 *)` cast: `D_002A6238[idx]` swaps two addu operands.
- h30's V4 (`f32[4]` aligned 16, used by seven data headers) was not retyped: its
  D_002C58D0 cast went without it (sceVu0UnitMatrix's `V4 *` accepts FMtx4).
- The rest as session 29 left it (D_002E26A0 actor pointers 24, D_002C5968 volatile
  flag views 15, D_00308CDC config views 15, D_002E31B0 14, D_00351E10 10, ...).

### Hazards found (gcc 2.96)

- A direct union member access is alias set 0 in strict files: h52's two bit-field
  reads `D_002A6238[id].f.p.x40` / `.k` with a store between them reloaded the word.
  `(&D_002A6238[id].f.p)->x40` (through a pointer) keeps the code; the other users'
  union accesses (h28 writes, h51 writes, h1 / r2_10 reads) kept theirs as written.
- A union containing a bit-field struct: the struct's bits count from the union's
  start, so a split that began after a byte member needs its own leading pad (`u32
  :16` for b16 when x34 / x35 were outside it).
- `s29_retype` renames only accesses gcc rejects: a view field whose name is also a
  shared field elsewhere (`d`) stayed on the shared field and changed code; the tool
  now refuses such maps (see Tools).
- Removing a view's +N base (r2_7 `e` at the record start - 4) changes register
  allocation even when every address is the same.

### Tools (tools/shift/s30types/, README there)

- `s30_hdrdiff.py HEADER..`: -S check of every source that includes a header,
  directly or through other headers (before `make` when a shared header changes).
- `s29_retype.py` refuses a "name clash" map (a renamed field whose name the shared
  type also uses).

## Session 30: reach_check (worker s30reach)

reach_check pins **1,304** names (was 1,331): 29 released, 2 newly pinned. Counted in a container without the
overlays (`SHIFT_OVERLAYS=` an empty directory); session 29's 1,338 had them, so with the overlays expect about
1,311. With all three new switches on (`--no-path-step --no-arg-bound --no-wr-span`) float_reach.txt *and*
float_reach.log are byte-identical to the session 29 code's. The default float build floats **2,100** names (was
2,073), links and passes M12-FLOAT and keep_check (39/39).

### The 1,331 names by reason (session 29 code, `--explain`)

| reason (every hit that pins the name) | names | what it is |
| --- | --- | --- |
| idx | 185 | an unbounded index |
| idx,idx-ub | 174 | one unbounded index among bounded ones |
| arg:wide | 169 | the callee walks the argument (printf `%s`, DMA senders) |
| arg:noreach | 98 | an address the callee keeps or sends |
| stored | 94 | the address is stored |
| idx-ub | 48 | a bounded index that ends past the next name (real) |

The idx tail, read site by site (about 1,500 unbounded accesses in 350 idx-only names, 2-6 per function): most
indices are loaded from memory (a cursor, a count in a record, a resource offset) or are a function's argument; the
loops among them mostly run to a count loaded from memory (`lw v0, n; slt v0, i, v0`). A common menu shape is
`list[n++] = x` with n a global counter (func_00216280, func_0021dc40: `lw v0,0(s0); addiu v1,v0,1; sw v1,0(s0);
D[v0]`): bounded only by runtime invariants (the readers index by a cursor < count), so no static rule proves
them. What a rule can prove: loops countdown_loops rejected only because the step is not a single write, and
indices made from an argument that every caller passes as a constant.

**stored** (func_0023b570 -> func_0023aed0, 38 names): session 28's claim holds. func_0023aed0
(src/hand/nostrict/text_00230000_c18.c) copies records into p6 ... p17 and then stores every one of them into its
Out record (`o->p6 = p6; ... o->p17 = p17`); p9[i] and p15[i] are filled for i < n, and n is stored too (o->n), so
the drawing code that reads the Out records (D_00650120[0..4], D_00650C00) indexes them by a count in memory.
Following the stack arguments (`lw aN, off(sp)` in the callee) would only move the `stored` from the caller's
`sw` to the callee's: the names stay pinned. Not attempted.

### The rules (each `--no-RULE` in SHIFT_REACH_FLAGS re-pins its names)

| rule (switch) | releases | what it proves |
| --- | --- | --- |
| path-step (`--no-path-step`) | 20 | `path_loops()`: countdown_loops' loops (down-counter `bgtz/bgez/bne c`, or up-counter `slti t,i,L; bne t`), proved over the paths of the body instead of by single writes. Every path from the header that reaches the back edge is followed (the body has no inner back edge, no switch, no linking branch, the header is the only way in; paths that branch or jump out or return are dropped); each register is tracked as {a register's header value + constant} or unknown. On the edge that loops the counter must be c - k (or i + k) on every path, and the test must see it at the same point on every path; a walked register is p + d, 0 <= d <= s, on every path. Covers the step in a likely branch's delay slot on the looping path while the other path returns (func_0011e248), the step in both arms of an if (func_001269d8, func_00266c30, func_001581d8, func_001474a0), the test register reloaded in the back branch's slot (func_0022d730), and a walk through a copy (`a1 = a0; ...; a0 = a1 + 4`, func_00111510). For a loop both functions find, the walked registers of both are kept. A call in the body clobbers the caller-saved registers after its delay slot. |
| arg-bound (`--no-arg-bound`) | 9 (and 2 newly pinned, below) | An index made from an argument (`sll v0,a0,4; lui; addu; lw`) is tracked as ("ax", k, m, a) = a_k * m + a, and the access becomes an `argidx` resolved after the scan: when every way into the function is a direct call the analysis saw (`jal F` or a tail `j F`), its bound is m * (largest a_k over the calls) + a. A call passes an exact value >= 0 or the caller's own argument + offset (a least fixpoint over the call graph; a recursion that keeps growing gives up). Not proved, so unbounded as before: any word equal to F in the ELF file or an overlay, code that builds F (lui/addiu/ori), a jal/j word for F the analysis did not record (an overlay, code outside layout.tsv, data), a branch into F from another function, code before F that may fall into it, a call with an unknown or negative argument, or an argument that came through a join (analyse's arg-join keeps an argument joined with another value as the argument: it is marked and never used as an index). The log prints `# N functions index by an argument, M called directly only`. |
| wr-span (`--no-wr-span`) | 0 on its own | A fix: the bytes an indexed store may write (`wr`, used by str-arg/list-arg/dma-chain's "no store writes the object") added the store's displacement twice: too far for a positive one, too short for a negative one (`sw $0,-4(v1)` ended 4 bytes early). Without it path-step's newly bounded store in func_00181368 (D_00364130's walk) looked like it wrote D_00370140 and re-pinned the DMA chains D_00370140 / D_00370170 / D_003701B0. |

tests/reach_check_test.py cases 12 (path-step: the three shapes and a path that loops without the step), 13
(wr-span) and 14 (arg-bound: the argidx event, a joined argument, and `arg_bounds()` with constants,
pass-through, a growing recursion and a negative argument).

### The released names

- path-step (20): D_002B75A0 (func_0010c170 & co: 2 slots of 12 bytes), D_002BC0F0 / D_002BC120 /
  D_00351A00 (func_001581d8: 3 ints moved one step toward a target), D_002BCC1C (func_00111510: 39-entry lookup
  table D_002BCB80), D_002E27C0 / D_002E27C8 (func_001269d8: 4 byte pairs, 66 x 4 nested), D_003F60F0
  (func_0021fbb8), D_003F6770 (func_00223508), D_003F7500 / D_003F7510 / D_003F7598 / D_003F75A0 / D_003F7628 /
  D_003F7630 (func_0022d730 / func_0022db98 / func_0022dfd8, menu panels: 3 or 2 entries), D_0046C550 / D_0046C580
  (func_00266c30: the 10 DMA channel register pointers, reset at boot), D_004E4528 / D_004E49E8 (func_001207f8 /
  func_00120aa0: a 1,216-byte pool), D_00532B90 (bss, 128 records of 32 bytes walked by func_001474a0 & co).
- arg-bound (9): D_0048C6F0 / D_0048C770 (func_00100580(i, out) for i = 0..7, func_00108970, func_00114c18:
  `V4i [8]`), D_004D92F0 / D_004D9320 (func_001130a0(i, out), i = 0..2: three vectors), D_002BD178 / D_002BD1A8 /
  D_002BD1E0 (func_00116368(w, i), i <= 10 through func_00118060's own argument: two 11-word tables),
  D_003F31F0 / D_003F3200 (func_0020b120(prim, ...), prim <= 2: GS primitive codes for the menu gradients).
- Newly pinned (2): D_003728C0 / D_00372908. func_001afac0 passes &D_003728C0 to printf (0x1b19bc, t1) on one
  path; analyse's arg-join turned the join of that address with the function's own t1 into "the argument", so the
  access was never seen. arg-bound's marking changed the visit order and an earlier visit now reports it. They
  floated in KH1_F29_N without trouble (a debug printf), but pinning them is right.

### Riskiest releases (for the boot route)

- **arg-bound** is whole-program reasoning (no pointer to the function anywhere). D_0048C6F0 / D_0048C770: boot
  (func_00100580 runs from func_00100610, which func_00100360 calls early) and func_00108970 / func_00114c18; a wrong release shows at the
  title or as a missing/garbled model. D_003F31F0: the menu's gradient boxes (func_0020b120: open the in-game
  menu, the load menu). D_002BD178 & co: func_00116368 (ray tests in text_00110000_h52.c: walk the field, the camera
  against walls). D_004D92F0: func_001130a0 (three vectors, the same field code).
- **path-step**: D_0046C550 (DMA reset at boot: no boot means this), D_00532B90 (bss records func_001474a0 walks
  every frame: walk, fight), D_004E4528 (a pool: load an area), D_003F7500 ... D_003F7630 and D_003F60F0 /
  D_003F6770 (menus: open the in-game menu, its item / status pages, the load menu).
- A boot of the usual route (load menu, save 06 with the party, test T, a desert fight, the in-game menu, save 05
  End of the World, the warp drive to Neverland) covers all of them.

### Hazard found: arg-join loses addresses

analyse's arg-join (session 20) returns the argument for a join of an argument with anything else, so an address
that only one path holds is dropped, and whether an access through it is reported depends on the order the
blocks are visited (events are emitted from intermediate states). D_003728C0 above is one case; others may
exist. A next step: keep the non-argument side (a SET of {the argument, the address}) or emit the address's
events at the join.

## Session 31: reach_check arg-join (worker s31reach)

reach_check pins **1,358** names (was 1,304; both counted without the overlays, `SHIFT_OVERLAYS=` an empty
directory): **54 newly pinned, none released**. With the three new switches on (`--no-arg-keep --no-join-keep
--no-stored-idx`) float_reach.txt and float_reach.log are byte-identical to the session 30 code's, and with
`--no-path-step --no-arg-bound --no-wr-span` added, to the session 29 code's (1,331). The default float build
floats **2,047** names (was 2,100: 53 of the new pins had floated; D_00525354 was kept by something else), links
and passes M12-FLOAT and keep_check (39/39). `make` is unchanged (byte-identical).

The name `--no-arg-join` was taken (session 20/21: an argument joined with anything is walked), so the switch that
restores session 30's arg-join is `--no-arg-keep`.

### The rules (each `--no-RULE` in SHIFT_REACH_FLAGS brings back the session 30 answer)

| rule (switch) | names it pins on its own (from the final 1,358) | what it does |
| --- | --- | --- |
| arg-keep (`--no-arg-keep`) | 17 | A join of an argument with an address keeps the argument (session 20's arg-join) and dropped the address, so the address's accesses after the join were seen only when its path happened to be visited first (events come from every state a point is visited with). Now merge() notes the dropped value and visits the point once more with the joined state but the address in that register (a *shadow visit*: its events are reported and its successors merged as usual). Both orders now report it. |
| join-keep (`--no-join-keep`) | 48 | The same for every other join that does not cover an address (`_covers`): an address joined with an unknown value (dropped), two pointer globals, a %hi or a jump-table word with something else. A register that gets more than SHADOW_MAX (3) values from shadows at one point (a walk around a loop) is widened to the lowest base + unknown, so it ends. |
| stored-idx (`--no-stored-idx`) | 2 | A store of base + index (`&D[i]`, an IDX value) stores the base. Before, only an exact address (or a SET) counted, so a store visited only with a loop's joined state (base + index) was not a `stored` at all (func_001c5ee8's `ent[i-1].lk.next = &ent[i]` was `stored` only in some visit orders). |

The three overlap (both keep rules shadow func_00241d60's tables); together 54. `--visit-seed N` (new) visits each
function's points in a random order (seeded by N and the function's address) for checking order dependence;
`analyse(visit_rng=...)` does the same in tests. tests/reach_check_test.py cases 15 (arg-keep: the load through the
join is seen in 16 random orders; with `arg_keep=False` the default order misses it and some random orders see it;
join-keep: a walk from an address joined into an argument's walk is reported, unbounded, and ends) and 16 (stored-idx); case 3 now notes that
without `joins` the store of the lowest address + index stores that base.

### The newly pinned names (54; untested only in the sense that the layout around them changed)

| function | names | why |
| --- | --- | --- |
| func_00241d60 (src/hand/nostrict/text_00240000_s6_g1.c) | D_00454448, D_00454450, D_00454488, D_00454498, D_004544A0, D_004544B0, D_004544C0, D_004544C8, D_004544D0, D_004544D8, D_004544F8, D_00454518, D_00454538, D_00454558 | `s->a[j] = base + D_00454430[j]` for `j < s->na` in each switch case: the count is stored then reloaded (a count in memory), so the index is unbounded (idx). Each table's address sat in a register joined, at the loop heads, with an argument register (arg-keep) or an unknown value (join-keep). |
| func_00122dc8 (src/hand/text_00110000_h53.c) | D_004F7150 | `if (!buf) buf = D_004F7150[n];` then sprintf / strlen / `buf[i]` through buf: a1 on one path, the address on the other (arg-keep: the exact case of the hazard). |
| func_00132a78 | D_00525354, D_00525358 | the address is in an argument register at a call on one path (arg:noreach; arg-keep). |
| func_0021d348 (src/hand/text_00210000_c15.c) | D_003F34DC, D_003F34E0, D_003F34E4, D_003F34E8, D_003F34EC, D_003F34F0, D_003F34F4, D_003F34F8, D_003F3514, D_003F3518, D_003F351C, D_003F3520 | the state words' addresses are left in t3 at the calls to func_00207830 / func_0021b6a0 on one path (arg:noreach; join-keep). |
| func_00223508 | D_003F6770 | arg:noreach (join-keep). A session 30 path-step release, kept in place again. |
| func_0020e408 | D_003F3940, D_003F3960, D_003F3980 | idx (join-keep) |
| func_0024b7a0 | D_00469FF8, D_0046A018, D_0046A038 | idx (join-keep) |
| func_002705f8 | D_00493F38, D_00493F48, D_00493F58 | idx (join-keep) |
| func_002541b8 | D_004920A8, D_004920F8 | idx (join-keep) |
| func_002524a0 | D_00491D48 | idx, stored (join-keep; libc) |
| func_0016f7b8 | D_0048E9EC | idx from the in-place object before it (join-keep) |
| func_0010d470 | D_004D5AF4 | arg:noreach from the in-place object before it (join-keep) |
| func_001f4058, func_001f4778 & co | D_003E8E30 | idx, stored (join-keep) |
| func_00161a08 | D_005739F8 | stored (join-keep) |
| func_00258f08, func_00265ed8, func_00266380, func_0026ab38 | D_00492138, D_00492B00, D_00492CF8, D_00492D38, D_00492E60, D_004932A8 | `arg0:func_00259c88:8` / `func_00259cc0:8`: an 8-byte block access from 2 bytes before the next name, and func_00266380 walks D_00492D38 (arg:wide) and stores D_00492D70 (join-keep; libc number formatting) |
| func_00127c20, func_00128b20 | D_004F7820, D_004F7C10 | stored as &D[i] (stored-idx) |

**Released: none**, so there is nothing new to boot for a release. The default float ELF is still a new layout
(53 names back in place, so every floated name after them moved): boot it on the usual route next Mac session
(load menu, save 06 with Donald and Goofy, test T, a desert fight, the in-game menu, save 05 End of the World, the
warp drive to Neverland) together with session 30's default, which has not been booted either. If session 30's
default fails and this one passes, D_003F6770 (path-step, now pinned again) is the first suspect.

### Order dependence that remains (`--visit-seed 1..3`, all rules on)

904 of the 6,979 functions (917 with the three rules off) report a different event set in a random order (seeds
1 and 2), mostly `callargs` values and index bounds that change no name. In names (float_reach.txt against the default order):

| names | which order pins them | why |
| --- | --- | --- |
| D_002BD1F0 (func_00118ea0, `i < 6`, 16-byte entries) | random only | imprecision: the default's bound (+80) is right; a random order widens the walk before all the loop's entry edges are joined. |
| D_0048C630 (func_00107ec0, `k < 16`) | random only | imprecision: nest-carry's cap is computed from a partial loop_entry. |
| D_00575080, D_00575088 (func_00169f28, `&D_00575090[bi]`) | random only | imprecision: the base becomes D_00575080 + unknown. |
| D_003F4C90 (func_00219f98) | random only | **a gap**: the loop's join of two bases makes one IDX from the lower (0x3F4C68), and an unbounded index from it ties only that base to its next name; a random order also reports it from 0x3F4C78 (D_003F4C78 -> D_003F4C90). Making `_covers` demand the same base for an unbounded IDX did not reach it (the loss is in join's IDX rule, not a shadow): needs join to keep each base (a SET of bases with an index). |
| D_002B6460 (func_001081c8 / func_001083d8), D_003B4DA0 (func_001c3408 / func_001c3770), 8-10 of func_0021d348's D_003F34xx, D_00493F38 ... (seed 3) | default only | a random order misses them: the default is the more conservative here. |

Mechanisms behind it: (1) a point's pending state is joined again before it is visited (LIFO work list), so
intermediate states are never visited — harmless now that a join no longer drops an address (the keep rules) except
for (4); (2) widening by a growth count; (3) loop caps (counter-cap, nest-carry, countdown) from a loop_entry that
is not complete yet; (4) the IDX join keeps the lower base only. (2) and (3) only lose precision. A next step for
(4): an IDX with several bases, or emit an unbounded `idx` from each base a join folds in.

## Session 31: Phase 4 types (worker s31types)

### Result

These counts come from `s27_survey.py --summary`, with the survey unchanged.
Session 30's table said 217 views at its own HEAD.  The survey run at the
session 31 base gives 214.

| | base 5eda346 | now |
|---|---|---|
| view casts (a user's own struct type) | 214 in 71 pieces | 52 in 22 pieces |
| shared casts (to the piece header's own types) | 202 | 235 |
| basic casts (s32, u8 *, void *, ...) | 750 | 751 |

Per piece (view casts, base -> now):

| piece | before | after |
|---|---|---|
| D_002E26A0 | 24 | 8 |
| D_00308CDC | 15 | 0 |
| D_002C5968 | 15 | 0 |
| D_002E31B0 | 14 | 2 |
| D_00351E10 | 10 | 0 |
| D_0036243C | 8 | 0 |
| D_0037A170, D_00350D88 | 6, 6 | 0, 1 |
| D_00362438 | 5 | 0 |
| D_00425B80, D_002E3170 | 4, 4 | 0, 3 |
| D_003519E0, D_0042B790, D_003F7A70, D_004305B0, D_0035C710 | 3 each | 0 |
| 13 pieces with 2 (D_003E8E28, D_003F1E70, D_00350D78, D_002C1300, D_003626C0, D_0035C490, D_0037A378, D_00425C28, D_002A6234, D_002E2700, D_003044E0, D_002BC148, D_00362434) | 2 each | 0 (D_00362434: 1) |
| 25 pieces with 1 (the texture headers D_00426790..D_00426940 and D_00431D20 / D_00431D50, D_00451040, D_003F1A70, D_003F2270, D_003F27D0, D_00362430, D_00362450, D_002C5958, ...) | 1 each | 0 |
| 17 pieces not reduced (see "Left, and why") | 37 | 37 |

What got typed (the shared types are in each piece's header):

- **D_00308CDC** (`Cfg_308cdc`).  It gained the users' fields: `t[10]` Cfg8Pr,
  `e[10]` Cfg16Pr, x7c[0xc], f88, x90, f94..f96 and fe8.
- **D_002C5968**.  `Sema_2c5968`, `Fl_2c5968` and `W_2c5968` are the volatile
  flag-word splits.
- **D_00351E10**.  The staging-arena QW users declare `extern QW D_00351E10[]`.
- **Texture headers**.
  - D_00426790..D_00426940 and D_00431D20 are `Tex_4268b0[1]`, and Fnt is
    Tex_4268b0.
  - D_00426970 and D_0042B790 are `TexBuf_426970`.
  - D_004305B0 is `Tex6000`.
- **D_0037A170**.  `RunQ_37a170` is 8 bytes, and h66's init writes `q[1]`.
- **Camera**.
  - Path_362438 has names for all its fields.
  - E30_362430's min and max are `FVec4`, and D_0036243C is `E30_362430 *`.
  - CamPt_362434 gained x1c.
  - Cam_425f70 takes h73's names.
- **Smaller views**.
  - W9Tab32: f0 is u32, and f10 / f14 are void *.
  - S5B80_425b80 gained x0 / x4.
  - The collision grid (Grid_2a6234), nodes (Node01) and map vertices (Vtx)
    are now shared.
  - B3Tbl moved to D_003044E0.h.
  - Q8_2e3170 and Fl_2c5958 are new.
  - `Q_3f1a70` is shared by D_003F1A70, D_003F1E70, D_003F2270 and
    D_003F27D0[0x40].
  - D_0035C490 is FVec4, and the h34 / s6_07 box set is BoxSet57_f1b8.
  - E8E28 is Glyph_3e8e28.
  - h28 reads Bits_37a378.
  - The light / sprite record `W8Ent35` is `{v[4], x10, x14, Fl_35c710 u}`.
  - Fx gained a, b, c, and B64 gained x34 / x38.
  - D_00451040 is a Blob, and D_002E2700 is FMtx4.
- **D_002E26A0** is `struct Actor *D_002E26A0[3]`, with the tag incomplete in
  the piece header.  About 25 user files complete it by tagging their own actor
  view `typedef struct Actor {..} X;` (s31_tag), as the VmObj precedent did.
  Where a file had two actor views they were merged first (s31_merge).
- **D_002E31B0** is `S31b0_2e31b0 { struct Actor *f0; s32 f4; }`, the lock-on
  target.  The target prototypes in b04, h58, s7_w3, h31, h5 and s6_07 take
  `struct Actor *`.  h54 (nofill) declares `extern struct Actor *D_00524F58[]`.

`make` stayed byte-identical after every commit, and no file gained a warning
(s31_warndiff).  `make test` passes.  The m12 float shift prints M12-FLOAT OK,
and float_covered.txt is the same as the base.

### Left, and why

- **D_002E26A0 (8)**.
  - h4's `(Act *)&D_002E26A0` is an end pointer.
  - src/vm/script_vm.c was left to the VM worker.
  - h37's ObjBD40 and r2_1's ChrEA are members of the D_0035BD40.h union
    header, and tagging them conflicts with that header's other includers.
- **The VM-area views**: D_003C5510 (7), D_00389C90 (4) and D_0037A380 (2), in
  h66 and h18.  They were avoided while the script VM moves.
- **D_002C5C80 (4)**.  The light vector members disagree: h53, h54, h30 and h4
  use `f32[4]` against `struct V4`.
- **D_002E3170 (3)**: the h49 and s11_w19 Spr views.
- **D_002E31A0 (3)**: the O8 typedef hazard below.
- **D_002E31B0 (2)**.  r2_1's LockEA: tgt is a ChrEA from the union header.
- **D_002A6238 (2) and D_00304BE8 (1)**: as session 30 left them.
- **D_0046A568 (2)**: it needs a union in a strict file (alias set hazard).
- **D_003044D8 (2) and D_00304AD8 (1)**: other actor pointers, not
  struct Actor.
- **D_002A3F48 (2)**.  It holds an s32 address that the auto code uses with
  byte arithmetic.
- **D_00364130 (2)**: two overlapping layouts.
- **Single casts**:
  - D_0029B420: the alignment of the copy.
  - D_002BC070: a volatile Col.
  - D_002C5C60: h4's Vec4.
  - D_002A62AC: s11_w56 computes it as a u8 address.
  - D_00362434: h62's lvalue cast.
  - D_003626F0: the h11 Arg hazard below.
  - D_00350D88: h55's u64 view, which W9Tab32 cannot take (below).

### Hazards found (gcc 2.96)

- **A union member access is alias set 0 in strict files.**  An anonymous
  union in W9Tab32, added for h55's u64 read, changed h9's code.  Reverted.
- **Union stores against struct-field stores.**  h11 stored through an `Arg`
  union.  Retyping those stores as struct-field (or s32 / f32) stores changed
  the load scheduling, through the alias sets.  Reverted.
- **The typedef name in a cast lvalue matters.**  `(*(O8 **)&D)`, with O8 a
  typedef of the declared type, keeps the INDIRECT_REF.  Recasting to the exact
  declared type (`O8_2e319c **`) folds it away and changes the code (s6_05 and
  r2_7 D_002E31A0).  Leave such casts as they are, or drop them only when the
  access becomes a plain `D` / `D[0]`.
- **An extern that conflicts with a shared data header** (D_002E3160 in
  data_002E.h) cannot be retyped per file.  Keep the declared type and cast at
  the use.
- Files under nostrict/ are built without strict aliasing, so the alias-set
  hazards do not reach them.  Most of the merges and tags were done there first.

### Tools (tools/shift/s31types/, README there)

- `s31_recast.py`: renames alias casts to the shared type.
- `s31_tag.py`: gives a file's view a shared incomplete tag and drops the casts.
- `s31_merge.py`: merges a file's second views by stabs offset.
- `s31_warndiff.py`: lists new warnings against HEAD.

## Session 32: Phase 4 types (worker s32types)

### Result

These counts come from `s27_survey.py --summary`, with the survey unchanged.
The survey gives 52 views at the session 31 types HEAD (e5b2c10), as session 31
said.  At this session's base (4ca7f69, main after the session 31 merges) it
gives 56: the camera module (src/camera/camera.c) rewrote h66's 7 D_003C5510
casts as 15 copy casts, and D_00389C90 fell from 4 to 2 (D_0037A380's casts in
camera.c are to its own header types, so they count as shared).

| | base 4ca7f69 | now |
|---|---|---|
| view casts (a user's own struct type) | 56 in 21 pieces | 20 in 13 pieces |
| shared casts (to the piece header's own types) | 223 | 223 |
| basic casts (s32, u8 *, void *, ...) | 750 | 750 |

Per piece (view casts, base -> now):

| piece | before | after | how |
|---|---|---|---|
| D_003C5510 | 15 | 0 | camera.c's `cp_q` / `cp_v` copy helpers take `void *` and cast inside (below) |
| D_002E26A0 | 8 | 1 | script_vm.c's Actor, h37's ObjBD40 and r2_1's ChrEA complete `struct Actor` |
| D_002C5C80 | 4 | 0 | `Lt64_2c5c80` gained the users' fields (flags, radius, pos, dir, col: FVec4) |
| D_002E3170 | 3 | 0 | h49's Spr and s11_w19's Spr17 are Q8_2e3170 |
| D_002E31B0 | 2 | 0 | r2_1's LockEA is S31b0_2e31b0 |
| D_003044D8 | 2 | 0 | x8 is `struct Actor *`; c02's C02Ob2 completes it |
| D_002C5C60, D_002A62AC, D_0029B420 | 1 each | 0 | FVec4; Grid_2a6234 *; s7_w4's cp160 copy helper |
| the other 12 pieces | 19 | 19 | see "Left, and why" |

What got typed:

- **D_002C5C80** (31 light records of 0x40 bytes).  `Lt64_2c5c80` is
  `{ s32 kind; u32 flags; s32 c; f32 radius; FVec4 pos; FVec4 dir; Vec4_2c5c80 col; }`
  and `Vec4_2c5c80` is now `typedef FVec4`.  h53's Light53, h54's Lt2,
  h30's Ent5C80, h4's Ent40 and s6_04's Lt64 alias it.  Users that read the
  vectors as `f32[4]` pass `&l->dir.x` / `&e->col.x` and index `(&l->dir.x)[j]`
  (same code).  h4's Vec4 is FVec4, so its `.v[3]` / `->v[2]` are `.w` / `->z`.
- **D_002E3170**.  The block's 0x14 bytes are `ids[0x10]` then `bright[0x10]`
  (h49's per-item 0x73 / 0xe6 levels at 0x24), and f4 is the u32 item mask.
  As s32, h49's `f4 & (1 << i)` compiled as `sra` / `andi` (a signed shift)
  instead of `sll` / `and`.
- **struct Actor, more completers**.
  - src/vm/script_vm.c's Actor (s31_tag; func_001c1e30 reads `D_002E26A0[0]->pos`).
  - D_0035BD40.h (the union of actor-pointer views) declares `struct Actor;`
    and its `objBD40` / `chrEA` members are `struct Actor *`.  It no longer
    includes r2_1's types header, which h60 (another completer) would have
    pulled in.  h37 completes the tag with ObjBD40.  r2_1's header completes
    it with ChrEA, and EntEA (the lock-on target view, f370 at 0x370) is
    merged into ChrEA (`typedef ChrEA EntEA`).  r2_1's LockEA is
    `typedef S31b0_2e31b0 LockEA` (tgt / part -> f0 / f4).  bss_0057_typed.h's
    other includers (s6_08, b06, bss_0057.c) do not complete struct Actor.
  - D_003044D8's x8 (the owner of a collision entry) is `struct Actor *`.  c02's
    C02Ob2 tag became Actor.  h6's func_00137450 takes `struct Actor *`.
- **D_002C5C60** is `FVec4`.  h60 and r2_1 pass `&D_002C5C60`.
- **D_002A62AC** is `Grid_2a6234 *`.  It is the saved grid that D_002A6234 is
  set from, like D_002A62B0 for D_002A6238.  s11_w56 converts the loaded
  address as it does for D_002A62B0.
- **Copy-width casts** (D_003C5510's 15, D_0029B420's 1).  These casts chose
  how 16 or 160 bytes are copied, not how D_X is laid out.
  - camera.c's `cp_q` copies as `CamV4q` (8-aligned: two ld/sd).
  - `cp_v` copies as `V4_37A380` (16-aligned: lq/sq).
  - s7_w4's Tex records are copied as `Blk160` (20 ld/sd).
  - The helpers now take `void *` and cast inside.  The callers pass
    `D_003C5510.pos` / `&D_0029B420[i]` with their declared types.

`make` stayed byte-identical after every commit, and no file gained a warning
(s31_warndiff).  `make test` passes.  `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`
with no overlays prints M12-FLOAT OK.  No data .s or piece size changed.

### Left, and why

- **D_002E31A0 (3)**.  s6_05 and r2_7 store with `(*(O8 **)&D_002E31A0) = ...`
  (the session 31 lvalue hazard).  `(*(struct O8_2e319c **)&D)`, with a tag
  added to O8_2e319c, keeps the code, because the pointer types are different
  nodes.  The survey would still count it as a view: D_002E31A0.h defines no
  type of its own (O8_2e319c is in D_002E319C.h).  So the code was left as it is.
- **D_00389C90 (2)**.  These are h18's func_001d7840 slot reads.  VmMgr has the
  slots (`u.s.e[i].obj` / `.ret` = h18's key / val), but inside its 0x3180
  union.  Every spelling through VmMgr was tried: `D.u.s.e[i]`,
  `(&D.u.s)->e[i]`, a `VmMgr *` local, and `((VmMgr alias *)&D)->u.s.e[i]`.
  Each one folds the address as D+0x3180, then +0x204, and changes the code.
  It needs the 0x3380 slots outside the union in include/vm/vm_mgr.h.  Also,
  func_001d7840 is in the script-function library that the module worker is
  splitting, so this is left for after the module merge.
- **D_002E26A0 (1)**.  h4's `a < (Act *)&D_002E26A0` is the end pointer of
  D_002C64A0's actor array, not a view.  `D_002C64A0 + 96` would relocate
  against another symbol.
- **D_00362434 (1) and D_00304AD8 (1)**.  These are pointers stored from
  another view of the record.
  - h62's Rec20 reads 0x1c as an s32 id, while CamPt_362434 has the u8 x1c
    (s7_w2).
  - b02's O15 against h32's W32Obj3.  h32 already completes struct Actor with
    W32Ply, whose x130 pointee differs from W32Obj3's.
  - `D = (T *)r` keeps the code in both files, but that only moves the cast
    onto the record.  Both are genuinely two views of one record.
- **Union-like words, unchanged since session 31**.
  - D_0046A568 (2): a u32 word table read as bit-fields (w12) and as s16 halves
    (w3).
  - D_00364130 (2): two overlapping layouts.
  - D_002A6238 (2): r2_10 reads it as u64.
  - D_00350D88 (1): h55 reads it as u64.
  - D_003626F0 (1): h11's Arg union stores.
  - D_002BC070 (1): a volatile s32[4] read as Col.
- **D_002A3F48 (2)**.  The auto files use it as an s32 byte address
  (`D + k * 0x10`).  A pointer type changes their arithmetic.
- **D_00304BE8 (1)**: r2_7, as session 30 left it.

### Hazards found (gcc 2.96)

- **Signedness of a mask field.**  With `s32 f4`, `f4 & (1 << i)` in a loop
  compiles as `(f4 >> i) & 1` with `sra`.  With u32 it compiles as
  `sll` + `and`.  A shared field must take the users' signedness even for bit
  tests.
- **Pointer store against int store (strict files).**  h6's `e->x8 = o`
  (struct Actor * field) reordered the surrounding stores; `*(s32 *)&e->x8 =
  (s32)o` keeps the code.  Same alias-set cause as session 29's VmObj hoist.
- **A member inside a union folds its offset in two steps.**
  `&D.u.s.e[i]` addresses D+0x3180 and then adds the rest.  A cast view
  `((Big2 *)&D)->e[i]` addresses D and then adds 0x3384+12.  Neither a pointer
  local nor an alias cast brings back the one-step form.
- **A shared header that includes a file's types header** spreads that file's
  struct tags to every includer.  D_0035BD40.h had to drop r2_1's header before
  r2_1 could complete struct Actor.

### Tools

No new helpers.  This session used s27_survey / s27_check, s30_hdrdiff, and
s31_tag / s31_warndiff.  s27_check needs `out/gen/objects.mk`, so run `make`
once in a fresh worktree.  A fresh worktree's
`make shift ... SHIFT_FLOAT=1` needs `python3 -I tools/shift/data_owners.py`
first, to write out/shift/data_owners.tsv.

Later in session 32 (worker s32module2): D_00389C90's last two casts are
gone (survey 20 -> 18 view casts, 12 pieces).  include/vm/vm_mgr.h no longer
has the union at 0x3180: `box[10]` stops before the slots and `e[8]` (0x3384)
is a plain field, so `D_00389C90.e[i].obj / .ret` folds the offset in one
step as h18's Big2 view did.  script_vm.c's `u.s.e[i]` / `u.box[i]` became
`e[i]` / `box[i]`; s30_hdrdiff gave SAME for every includer and `make` stayed
byte-identical (docs/modules.md, session 32 "Second half").

## Session 32: reach_check (worker s32reach)

reach_check pins **1,362** names (was 1,358; both without the overlays, `SHIFT_OVERLAYS=` an empty directory):
**4 newly pinned, none released**. The default float build floats **2,043** names (was 2,047; all four had floated),
links and passes M12-FLOAT and keep_check (39/39). `make` is unchanged (byte-identical), `make test` passes. With
`--no-multi-base --no-sign-prune --no-shadow-image --no-arg-drop` float_reach.txt *and* float_reach.log are
byte-identical to the session 31 code's (`--no-multi-base` alone already gives the same names; widen-bases needs
multi-base, so it is off with it).

### The rules (each `--no-RULE` in SHIFT_REACH_FLAGS brings back the session 31 answer)

| rule (switch) | names | what it does |
| --- | --- | --- |
| multi-base (`--no-multi-base`) | 4 newly pinned | The D_003F4C90 gap. func_00219f98 picks D_003F4C68 or D_003F4C78 (a SET) and adds `k * 8` with k loaded: SET + index (and a join of two indexed bases) became one IDX from the lowest base, so the unbounded index tied D_003F4C68 to D_003F4C78 and D_003F4C78 to nothing. An IDX made from a choice now carries the other bases (5th element, `_mkidx`); every access, `stored`, `wr`, `passidx` and `argidx` through it is reported from each base, to the same end. A loop head's join (a walk: D, D + stride) adds no base, and neither does an address inside the other side's bounded range (a walk position some orders visit before the loop's states are joined). For an unbounded IDX `_covers` asks for the base itself (an index from B ties B to *its* next name). |
| widen-bases (`--no-widen-bases`) | 0 (order) | A shadow register widened after SHADOW_MAX values keeps every base it saw (minus walk positions). func_0021d348 leaves one of six state words in t3 at its calls; the widened value kept the lowest, so D_003F34E4 ... D_003F3520 were pinned only in the default order. |
| sign-prune (`--no-sign-prune`) | 0 (order) | bltz/bgez/blez/bgtz (and likely forms) on an exact value take one edge. func_00169f28 `best = -1; ...; if (best >= 0) f(&D_00575090[best])`: an order that reached the test with -1 passed &D[-1] and pinned D_00575080 / D_00575088. |
| shadow-image (`--no-shadow-image`) | 0 (termination) | Only an image address gets a shadow visit (main drops every event from other values). |
| arg-drop (`--no-arg-drop`) | 0 (termination) | Two offsets of an argument join to nothing (a walk), but the next arrival joined with nothing came back as the argument (arg-join), so a point could alternate forever; after ARG_DROP_MAX (8) drops at a point it stays dropped. With the session 31 code **`--visit-seed 4` and `6` never ended** (func_0025632c, memchr: 0xFFFFFFFF in v1 got shadows that each carried a new argument offset). |

tests/reach_check_test.py: case 17 (multi-base: SET + index and a join of two indexed values, both bases in 16
orders; a walk position is not a base; a loop walk's steps are not bases), 18 (sign-prune), 19 (widen-bases), 20
(a memchr-shaped function that the old code did not finish for seeds 4, 22, 25, 28 of 32); case 3 now stores both
addresses with `joins=False`.

### Newly pinned (4) and released (none)

| name | function | why |
| --- | --- | --- |
| D_003F4C90 | func_00219f98 | D_003F4C78[k * 2 (+1)], k loaded (the gap) |
| D_003C21A0 | func_001c3408, func_001c3770 | an unbounded index from D_003B4DA0 (session 31 listed it as "default only") |
| D_002BD170 | func_00115600 & co (6) | an unbounded index from D_002BD160, chosen with D_002BD150 |
| D_00454700 | func_0023d528 | an unbounded index from it (one of several tables), ties it to D_00454730 |

**Newly released (UNTESTED until booted in PCSX2): none.** The default float ELF is again a new layout (4 names back
in place): boot it with session 30's and 31's on the usual route. If it fails and session 31's passes, bisect with
`SHIFT_REACH_FLAGS="--no-multi-base"` (= session 31's names), then session 31/30's switches as their sections say.

### Order dependence (`--visit-seed 1..8`, all rules on; every seed now terminates)

Fixed against session 31: D_003F4C90, D_002B6460, D_003B4DA0, func_0021d348's D_003F34xx, D_00575080 / D_00575088,
D_0048C630. What remains (float_reach.txt against the default order):

| names | seeds | why |
| --- | --- | --- |
| D_002BD1F0 (func_00118ea0) | all, random only | the walk widens (0, 16, 32, then unbounded) before loop_value's cap sees the whole loop_entry; the default's +80 is right |
| D_00493F38, D_00493F48, D_00493F58 (func_002705f8) | 2, 3, 5-8: default only | v1 is one of -1, 0, 1, 2, 3 at a forward join; three growths widen it (the default, unbounded: conservative); orders that see 3 early keep `<= 3` |
| D_00492138, D_00492B00, D_00492CF8, D_004932A8 (func_00258f08 & co, libc formatting) | 4, 5: default only | session 31's join-keep pins; those orders reach the arg-drop cap or join differently |
| D_00654570 (func_00241d60) | 7, 8: random only | a struct copy from `a3 + 2928` with a3 exact in some orders: the copy's walk is unbounded from 0x006529E0 (the in-place block after D_00652898) instead of from 0x00651E70 |

All are widening or intermediate-state imprecision (session 31's mechanisms 1-3); none is a lost base. A fix for the
middle two: widen by growth count only at loop heads (a jump table can make a cycle without one, so a higher count
elsewhere instead); not done, since more precise bounds can release names.

### Hazard found: a bounded index ties the base to the next name only

A bounded access that ends past the next name pins the base and that one name (`idx-next[idx-ub]`), not the names
after it. **func_0021cfc8 reads D_003F5C18[i] for i < 6** (h24.c: `if (D_003F5C18[i]) D_00642E98[D_00642EA0++] = i`),
through D_003F5C1C ... D_003F5C2C, but D_003F5C20 / 24 / 28 / 2C **float in the session 30, 31 and 32 defaults**:
the menu code would read the holes. An `idx-span` rule (pin every name before the end) pinned 512 more names, most
from loose bounds (lhu's 0xFFFF, long SET spans), so it was not kept. Spans under 0x80 bytes name 26 floating names
worth a look first: D_003F5C20-2C (func_0021cfc8, real), D_00351A00 / 10 / 20 (func_00157a30 from D_003519B0;
D_00351A00 was a session 30 path-step release), D_003F31A8 / B0 / E0 / F0 (func_00209f70 from D_003F3150 /
D_003F3178; D_003F31F0 was a session 30 arg-bound release), D_00351BC0 / C4 / C8, D_002B6830, D_002C6490,
D_003F4170, D_003F65C0, D_0046A03C / 40 / 44, D_00492EE8 / F10 / F38, D_004E3A1C, D_0054C218. Next step: read those
functions, then either a bounded idx-span (only when the bound comes from a loop cap or an exact constant) or
float_keep.txt entries.

## Session 33: Phase 4 types (worker s33types)

Item 4 of the session 33 plan: other files' prototypes of the module functions.

### Found

`tools/shift/s33types/s33_protodiff.py` (new) lists every one-line declaration,
in a src/ file outside src/vm, src/camera and src/msgwin, of a function those
modules define, whose type differs from the include/vm, include/camera or
include/msgwin prototype (parameter names dropped; `()` counts as different).
At the base (a0e83e4) it gives **27 declarations in 23 files**, all of
script_vm.h / vm_find.h functions (none of camera.h or msgwin.h).  `--defs`
adds **10** declarations of module functions no header declares.  The README's
examples `func_001c19f8(VMa *, s32)` and `s32 func_001c4640` were already gone
(session 31); the old-style `void func_001c4640();` is b11's.

### Retyped (19 of 27, plus 5 of the 10)

Each file now includes the module header instead of its own prototype.
`make` stayed byte-identical (6979 functions) and s31_warndiff gave 0 new
warnings for every file; s29_asmdiff gave SAME per file first.

- **func_001c2df0** (`s32 (s32, s32)` -> `s8 *(s8 *, s32)`): auto
  text_00210000_6, nostrict/b14, b15, h71, s6_22, h72.  The script pointers
  (D_003F34F0 / F8, D_003F3518 / 3520) stay s32 in data_003F.h (h70 and c15
  do arithmetic on them), so the call is `(s32)func_001c2df0((s8 *)D, k)`.
- **func_001c2ec8, func_001c3770** (`s8 *` first argument): auto
  text_00110000_6, s6_02 (`(s8 *)` at the call).
- **func_001c2d20**: auto text_001e0000_17 / _18 pass `(s8 *)&D, sp, (s8 **)&D`
  (their M2C_UNK externs stay: cover_check sizes them).
- **func_001c0da0 / func_001c0e80, func_001c4788, func_001c4808**: auto
  text_001b0000_10, h47, auto text_00130000_4 (`(void *)`), auto
  text_00130000_8 (no cast needed: s32 to u32 converts).
- **nostrict/c01**: the prototypes are the header's and the loop reads
  `c = (C01Cmd *)func_001c45e8()`.  C01Cmd stays: it is VmMsg except that
  `v` is `u32 :24` where VmMsg has `u64 val:24`, and reading the u64 bit-field
  compiles as `dsrl 8` + `and` instead of `dsll 24` / `dsra 32` (8 calls).
- **s6_16**: Msg (a copy of VmMsg) -> VmMsg, E848 -> VmRec.
- **h45**: E848 (0x350 bytes: a VmRec) -> VmRec, from vm_find.h.  Its VM2
  view -> VmRec, with `(s32)(vm->f328 >> 5) & 1` as `vm->fl.b.b5` (same code;
  `fl.i[0] >> 5` changes it).
- **h21, h46**: the VM view (only sp / stk used) -> VmRec.  nofill/h16's VM
  was unused and is gone.
- **script_vm.h** gains `func_001c1f60`, `func_001c48c8`, `func_001c4d90`, so
  h2 / auto text_00110000_6, h8 / auto text_00130000_8 and nostrict/h55 use it
  (h55 passes `(s32)` addresses; h8 passes `(s32 *)b`).

### Left, and why

- **8 declarations in 6 files** that the library move (worker s33module) owns:
  nofill/b11 (`void func_001c4640();`), nofill/h17 and nofill/s6_15
  (`Ent *func_001e98d0` / `func_001e9b98`), h18 (`P8 *`), h44 (`HSub *`),
  s6_15 and nofill/s6_15 (`func_001c4640(Msg *)`).
- **No header yet**: func_001c4de0 (auto text_00120000_8, agrees with the
  definition; see the hazard below), func_001c4ed0 (s6_na's Ob7 against
  script_vm.c's Obj), func_001cd238 (library), h44's func_001d1080 /
  func_001d3e30 (library).
- **VM views addressed from vm + 4**: h45's VM, h20, fmam/s7_w19 and s8_w6
  index the stack through `Sub *s = &vm->u.s` (a register holding vm + 4) and
  `vm->u.h.sp`.  VmRec's `vm->stk[i]` addresses from vm, which is other code.

### View casts

`s27_survey.py --summary`: view casts **18 in 12 pieces** (unchanged; none of
session 32's list became easy with these types), shared 223, basic 748.

### Hazard found: prototype count in script_vm.h flips vm_lib.c

Adding prototypes to script_vm.h changes the code of src/vm/vm_lib.c's
dispatcher (`return D_003D9FE0[k](vm)`, the table defined above it in the same
file) with the parity of the count: 1 or 3 new declarations keep
`lw $2,D_003D9FE0($5)`, 2 or 4 give `lui` / `addiu` / `addu` / `lw`.  Which
names are added does not matter.  So script_vm.h got 3 (func_001c4de0 was left
out), and s30_hdrdiff on `vm/script_vm.h` is SAME for every includer.  Any
change to the headers vm_lib.c includes needs s30_hdrdiff / `make`, even one
that only adds declarations.

### Checks

`make` byte-identical (6979), `make test` passes, `make shift` M0 OK, and
`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1` (no overlays) prints M12-FLOAT OK
with float_covered.txt and the float ELF's symbols equal to the base's.

## Session 33: reach_check (worker s33reach)

reach_check pins **1,373** names (was 1,362; without the overlays, `SHIFT_OVERLAYS=` an empty directory):
**11 newly pinned, none released**. The default float build floats **2,032** names (was 2,043; all eleven had
floated), links and passes M12-FLOAT and keep_check (39/39). `make` is unchanged (byte-identical, 6979 functions),
`make test` passes (tests/reach_check_test.py case 21). With `--no-idx-span` float_reach.txt *and* float_reach.log
are byte-identical to session 32's.

### The rule: idx-span (`--no-idx-span` brings back the session 32 answer)

Session 32's hazard: a bounded index that ends past the next name pinned the base and that one name (idx-next), not
the names after it. Pinning every name up to the end (session 32's try) pinned 512 more, almost all from loose
bounds. Now only a **tight** end counts: the functions behind an overrun are analysed a second time with analyse's
`tight=True`, where only a loop (a counter's cap, a walk's trip count, nest-carry) or a compare against a constant
(slti/sltiu/sltu on the branch edge) bounds a value; `lbu`, `lhu` and `andi` give no bound (a field's type range or a
mask says nothing about the values the game stores). For each base whose accesses are all bounded and end past the
next name, every name from the next one up to the largest tight end (each access's end is the smaller of its normal
and tight end) is pinned (`idx-span` in float_reach.log). Direct accesses only (`idx` events): the other bounded
overruns (`arg-ub` call arguments, `dma-ref`; 223 of the 368 overrunning accesses) name no floating name today.
A join of different bases outside a loop head stays as it is in tight mode: making it unbounded also lost
func_0021cfc8's walk (a walk position, D + 4, joins the walk's range at the branch target inside the loop).

`--span-log FILE` (new, no effect on the output) writes every bounded base whose accesses end past the next name:
the names inside the overrun and each access that reaches past the next name (end, kind, function, pc). It is how
the verdicts below were found; 110 bases, 833 floating names inside some overrun, most behind `lbu`/`lhu` indexes.

### Verdicts (session 32's 26 names, then the rule's other pins)

| name(s) | function | access | verdict | pinned now |
| --- | --- | --- | --- | --- |
| D_003F5C20, 24, 28, 2C | func_0021cfc8 | D_003F5C18[i], i < 6 (a walk capped by the up-counter) | **real**: the menu reads all six words | yes (idx-span) |
| D_00351A00, 10, 20 | func_00157a30 | D_003519B0[o->x130->x4c] (lhu), 12 words | not real: x4c is a party member id, the same field is checked `< 10` two lines on; D_00351A00 needs index 20 | no |
| (same) | func_001515d0 | D_003514E8[q->b3].id (lbu), 9 entries of 8 | not real: index 163 needed | no |
| D_003F31A8, B0, E0, F0 | func_00209f70 | D_003F3150 / D_003F3178[x48e[i]] (lbu), 10 floats each, i < 4 party slots | not reached: x48e[i] is 0..9 or 0xFF for an empty slot (text_00130000_h7.c: `a < 10 ? a : -1`); 0xFF reads +0x3FC, in **D_003F3530** (pinned by its own unbounded index; float_keep.txt now keeps it too) | no (D_003F3530 kept) |
| D_00351BC0, C4, C8 | func_0015b268 | D_00351B18[x48c] (lbu), 2 words | not real: index 42 needed | no |
| D_002B6830 | func_0010bdd0 | D_002B6780 / 6798 / 67C0 / 67C8[lhu field] | not real: small tables (4-12 entries) indexed by a record's small fields; 52+ needed | no |
| D_002C6490 | func_00122dc8 | D_002C6460[(id >> 16) & 0xff] (andi 0x3fc), 11 names | not real: the other path checks the same byte `< 11`; index 12 needed | no |
| D_003F4170 | func_00216890, 00216ea8, 00217000, 00217490, 002177c8 | D_003F40F8[x48e[cur]] (lbu), 8-byte entries | not real: the cursor stays below the party count (D_003E3D68), ids 0..9 end at D_003F4148, inside D_003F40D0's piece | no |
| D_003F65C0 | func_00222670 | D_003F6568[D_00643668[k]] (lbu), 10 words | not real: func_002210f8 stores only 1..8 there | no |
| D_0046A03C, 40, 44 | func_00249a48 | D_00469FB0[clutType / imageType].psm (lbu), 6 entries | not real (format): TIM2 image and CLUT types are small (the table has 6 entries); index 35 needed | no |
| (same) | func_0024b138 | D_00469FC8[*p] (lbu), 4 function pointers | not real: a jalr through it; index 29 needed | no |
| D_00492EE8, F10, F38 | func_00266d10 | D_00492EA0 / EB0 / EC0[p[k]] (lbu), 16 bytes each | not real: each byte is checked `< 10` first (the analysis loses it: the byte is loaded again) | no |
| D_004E3A1C | func_0011e1c8 | D_004E39F8[i] = {a0, 2} after `for (i = 0; i < 4 && D[i].a; i++)` | **real**: with four slots busy it writes slot 4 = D_004E3A18 / D_004E3A1C, and func_0011e248 / func_0011e368 read both | yes (idx-span) |
| D_0054C218 | func_001497c8 | `for (i = 0; i < 3; i++) if (D_0054C1B0[i].x10 == a)` (bnezl slot load) | not real: loads end at +0x54 of 0x60; the analysis's bound (+0x64) runs past the last load | yes (safe, false) |
| D_003C39B0, 39F0, 3A30 | func_001c0f30 (script VM op 12) | D_003C2D30[idx] for idx < 0xcc0 / 0xd00 / 0xd40 (compares) | **real** (new): the push of s8 variable idx reads D_003C39B0[idx - 0xc80], D_003C39F0[...], D_003C3A30[...] (gcc folded the subtraction into D_003C2D30's %lo), while the pop (func_001c13e8, op 13) writes them by name: floated, the VM read the old slots | yes (idx-span) |
| D_003C39AC | func_001c0f30 | (same) | not real: idx >= 0xc80 starts at D_003C39B0 (no lower bounds) | yes (safe, false) |
| D_00575784 | func_0016f548, func_0016f640 | free list of 30 x 20 bytes from D_00575528; a2 starts at &D_00575784 (the head) and walks the entries | not real: the head is written by name; the loop head's join of &D_00575784 with the walk makes the walk's range cover it | yes (safe, false) |

Real and newly pinned: D_003F5C20, D_003F5C24, D_003F5C28, D_003F5C2C, D_004E3A1C, D_003C39B0, D_003C39F0, D_003C3A30.
Pinned although not reached (safe): D_003C39AC, D_0054C218, D_00575784.

**Newly released (UNTESTED until booted in PCSX2): none.** The default float ELF is a new layout again (11 names back
in place). D_003C39B0 / 39F0 / 3A30 are the script VM's byte variables: if session 30-32's defaults misbehaved in
script-driven scenes (events, flags), this is a candidate cause.

### Order dependence (`--visit-seed 1` and `4`)

Against `--no-idx-span` with the same seed, idx-span adds the same 11 names plus **D_0054F444** (random orders only):
func_0014a398 walks D_0054C440 in 192-byte steps `while (p < &D_0054F440)`; some orders see positions of the walk
(0x0054C5C0, 0x0054C680) as bases, bounded by the sltu, and `ld` reads 8 bytes from `lim - 1`, so their end passes
D_0054F440 (the real last entry ends at 0x0054F388). A safe pin, from session 31's intermediate-state mechanism. The
rest of the differences to the default order are session 32's (D_002BD1F0; seed 4: D_00492138, D_00492B00,
D_00492CF8, D_004932A8).

### Left

Two of the false pins come from bounds one step long, both on loops whose test is a branch-likely with a load in
its slot (func_001497c8: +0x64 for loads ending at +0x54; func_0021cfc8's own bound is +0x1c, one word past the six
it reads, and D_003F5C30 was pinned anyway): likely the slot's load counted on the edge that nullifies it. Fixing either makes bounds tighter, so
it could release names: not done. Lower bounds (idx >= 0xc80) are not modelled.

## Session 34: reach_check (worker s34reach)

reach_check pins **1,356** names (was 1,373; without the overlays, `SHIFT_OVERLAYS=` an empty directory):
**19 released, 2 newly pinned**. The default float build floats **2,049** names (was 2,032), links and passes
M12-FLOAT and keep_check (39/39). `make` is unchanged (byte-identical, 6979 functions), `make test` passes
(tests/reach_check_test.py cases 22-26). With all five new switches
(`--no-likely-slot --no-widen-heads --no-hix-join --no-align-end --no-neg-keep`) float_reach.txt *and*
float_reach.log are byte-identical to session 33's. float_keep.txt gains D_00551600 (pinned either way, see below).
**Every release is UNTESTED until a PCSX2 boot** (docs/float-untested.md has the row).

### The rules (each `--no-RULE` in SHIFT_REACH_FLAGS brings back the session 33 answer for its names)

| rule (switch) | names | what it does |
| --- | --- | --- |
| likely-slot (`--no-likely-slot`) | 15 released (14 stay released: D_00551600 is pinned again by neg-keep) | The delay slot of a countdown loop's **likely** back branch runs only when the back edge is taken, at most back_edges times per entry, so only in the runs before the last. A walked pointer there is at most its header cap (loop_value), one stride less when the slot itself steps it. Before, the slot saw the header cap plus the body's step: one stride more. func_001497c8 (`bnezl a1,loop; lw v1,0(a3)`, `for (i = 0; i < 3; i++) if (D_0054C1B0[i].x10 == a)`) read +0x70 from D_0054C1B0 for loads ending at +0x54; func_0021cfc8's six words now end at +0x18 (D_003F5C30 stays pinned by func_0021db30). Applied on the taken edge only (analyse's slot_cap), for the loops countdown_loops / path_loops prove. |
| widen-heads (`--no-widen-heads`) | 2 released, 2 newly pinned | A growing bound is widened after two growths only at a loop head (a backward branch's or jump's target, or a jump-table case at or before its `jr`); every cycle passes one. Elsewhere it widens only after FWD_GROW_MAX (16) growths, a safety net. Before, a value checked by a compare after the loop head (`i++; slti; beqz exit; sll a2,i,3`) widened again at the forward points after the refine (func_00146a68), and a forward join of a few constants lost its bound in orders that saw them one by one. It also makes func_00241d60's switch reach its cases 3 and 4 from their entries: the table index was widened at a forward point, so the `jr` fell back to the branch labels, which do not include the case entries; the loops inside them were analysed from the switch's state (the copy counter was the argument a2, so the table reads made no event). |
| hix-join (`--no-hix-join`) | 3 released (needs widen-heads) | Two lui + index values (HIX) of one %hi join to that %hi with the larger bound (unbounded if either is), as IDX values do; before, they joined to nothing and join-keep's shadows widened the fourth value to unbounded. A growing HIX bound is widened like the others. func_002705f8 (atanf) reads atanhi[id] / atanlo[id] as `lui at; addu at,at,v0; lwc1 %lo(...)(at)`; id's bounds 0, 4, 8, 12 arrived one by one in the default order. |
| align-end (`--no-align-end`) | 0 (order: D_0054F444) | A bounded access wider than a byte ends at its largest offset **rounded down to its width** + the width (the address of lh/lw/ld/lq and the FPU/VU forms is a multiple of the width; lwl/lwr/ldl/ldr/sdl/sdr count as bytes). func_0014a398 walks D_0054C440 in 192-byte steps `while (p < &D_0054F440)` and reads `ld 0(p)`: p <= END - 1 gave an end of END + 7. Module function aligned_end; direct `idx` accesses (normal and tight). |
| neg-keep (`--no-neg-keep`) | 0 (D_00551600 stays pinned) | Small negative constants a join drops (to an upper bound, which says nothing below zero; -1 and its 32-bit form 0xFFFFFFFF) get one shadow visit holding every negative constant from that side (k = -1 and 16 * k in another register go together). func_001571a8 writes &D_00551608[k] with k still -1 when no slot is free; only some visit orders saw that path before it was joined away. |

### Verdicts (every name the rules release or newly pin)

| name(s) | rule | function | access | verdict | now |
| --- | --- | --- | --- | --- | --- |
| D_002C1310, D_002C1320 | likely-slot | func_0011dc28, func_0011dc98 | `for (i = 3; i >= 0; i--)` over D_002C1310's four words, the next one loaded in the bgezl's slot: +0x0 ... +0xC, ends at its 0x10 | not real (analysis +0x14) | released |
| D_00304BE8 | likely-slot | func_0013cb98 | D_00304BC0's ten words (`lw`, and `lbu` in the bgezl's slot), s0 = 9 ... 0: ends at its 0x28 | not real (analysis +0x29) | released |
| D_003F59C0, D_003F59C8 | likely-slot | func_0021b170 | `for (i = 0; i < 2; i++) if (D_003F59C0[i] == a) return 1` (bnezl slot load): 8 bytes, its size | not real (analysis +0xC) | released |
| D_003F5E58, D_003F5E60 | likely-slot | func_0021e898 | the same shape over D_003F5E58 (8 bytes) | not real | released |
| D_0046BE88 | likely-slot | func_0025fa88 | D_0046BE48's pairs 2 ... 7 (`i = 2; i < 8`, first words at +0x10 ... +0x38): ends at +0x3C of 0x40 | not real (analysis +0x44) | released |
| D_0046C210, D_0046C250 | likely-slot | func_00260938 | D_0046C210's pairs 3 ... 7 (+0x18 ... +0x38): ends at +0x3C of 0x40 | not real (analysis +0x44) | released |
| D_0054C218 | likely-slot | func_001497c8 | D_0054C1B0[i].x10, i < 3: +0x10, +0x30, +0x50, ends at +0x54 of 0x60 (session 33's false pin) | not real (analysis +0x74) | released |
| D_00669390, D_006693B0, D_006693D0 | likely-slot | func_002480d8, func_00247bd0, func_00247b50 | countdown loops (bgezl, slot load) over D_00669388 (2 words), D_00669390 and D_006693B0 (8 words each): each reads exactly its own words | not real (one word more) | released |
| D_00551600 | likely-slot / neg-keep | func_00155a90; func_001571a8 | func_00155a90 reads D_005512A0's 12 x 72-byte entries (ends +0x31C of 0x360; analysis +0x364): not real. But func_001571a8 (sound bank slots) keeps k = -1 until it finds a free D_00551608[j] (34 bytes) and then writes e = &D_00551608[k] unchecked (b0, b1, strcpy of the name): with every slot busy it writes 0x005515E6 ... 0x00551607, D_005512A0's tail and all of D_00551600 | **real** (if all slots are ever busy) | stays pinned (neg-keep, float_keep.txt) |
| D_00531B70, D_00531F70 | widen-heads | func_00146a68 (func_00146928) | D_00531B70[128] of 8 bytes: `for (i = 1; i < 128; i++) if (!D_00531B70[i].h)` (i++ in the bnez's slot, `slti; beqz exit; sll a2,i,3`): i <= 127, ends at its 0x400; func_00146928's countdown also ends there | not real (the bound was widened away after the refine) | released |
| D_00493F38, D_00493F48, D_00493F58 | hix-join (+ widen-heads) | func_002705f8 (atanf, src/sdk/libm/sf_atan.c) | atanhi[id], atanlo[id] (4 floats each) with id in 0 ... 3 (id = -1 skips them: `bgez v1`); aT[0 ... 10] at constant offsets | not real | released |
| D_002BD1F0 | widen-heads | func_00118ea0 | D_002BD1F0[i], i < 6, 16 bytes each: 0x60, its size; the counter steps on two paths (a bc1tl's slot and after the switch), and the default order now loses the bound as the random orders already did | not real | newly pinned (safe) |
| D_00454468 | widen-heads | func_00241d60 | switch cases 3 and 4 (not analysed before): `for (i = 0; i < n; i++)` over D_00454450 (n = 6, its 6 words) and D_00454468 (n = 7 of its 8 words), n stored to a3->x24 and reloaded as the bound | not real | newly pinned (safe) |

Released (UNTESTED until booted in PCSX2, 19): D_002C1310, D_002C1320, D_00304BE8, D_003F59C0, D_003F59C8,
D_003F5E58, D_003F5E60, D_0046BE88, D_0046C210, D_0046C250, D_0054C218, D_00669390, D_006693B0, D_006693D0
(likely-slot), D_00531B70, D_00531F70 (widen-heads), D_00493F38, D_00493F48, D_00493F58 (hix-join). Newly pinned:
D_002BD1F0, D_00454468. Riskiest: D_00493F38 / 48 / 58 (atanf: every angle the game computes), D_00531B70 (the
loader's id/handle table, func_00146a68 registers loads), D_0054C218 (summon/effect slots), D_00669390 ... D_006693D0
(bss tables passed to func_002474e8). None of the released names showed up in any `--visit-seed 1..8` run.

### Order dependence (`--visit-seed 1..8`, all rules on)

Fixed against session 33: D_002BD1F0 (pinned in every order now), D_00493F38 / 48 / 58 (floated in every order),
D_0054F444 (floated in every order: align-end) and D_00551600 (pinned in every order: neg-keep; random orders pinned
it in session 33 too, hidden by func_00155a90's false pin). What remains (float_reach.txt against the default order):

| names | seeds | why |
| --- | --- | --- |
| D_00492138, D_00492B00, D_00492CF8, D_004932A8 (func_00258f08 & co, libc formatting) | 4, 5: default only | session 32's: the reach of func_00259c88's argument (arg-drop / join order); the default is the conservative side |
| D_00654570 (func_00241d60) | 7: random only | session 32's struct copy from a3 + 2928 with a3 exact; cover_check keeps D_00654570 in every order, so the float set does not change |

The float set (float_covered.txt) is therefore the same in every order except for the four libc strings in seeds 4
and 5. A walk position taken as a base (session 31's intermediate-state mechanism) remains possible in general; align-end
only removed the overrun that made it pin D_0054F444.

### Left

- Negative indices are modelled only through exact values (neg-keep makes the default order see them); an index
  that may be negative but is not a constant (`k` from a search that can fail) pins nothing before the base.
- A jump table whose index is not bounded falls back to the branch labels (`starts`), which do not include the case
  entries nothing branches to: the labels inside a case are analysed from the switch's state, the case's first
  instructions not at all (a gap that can miss accesses, not only bound them loosely). widen-heads fixed
  func_00241d60's; reading the table's words when its address is known but its index is not would close it.
- D_00492138 & co (above) and session 31's widening / partial loop_entry mechanisms stay.

## Session 59: reach_check (jt-read, fmt-read)

Both "Left" items of session 34 are closed. reach_check pins **1,352** names (was 1,356; without the overlays):
**4 released, none newly pinned**. The default float build floats **2,053** names (was 2,049), links and passes
M12-FLOAT and keep_check (39/39). `make` is unchanged (tools only), `make test` passes (tests/reach_check_test.py
case 27). With `--no-fmt-read` float_reach.txt is byte-identical to session 58's. **The four releases are UNTESTED
until a PCSX2 boot** (docs/float-untested.md has the rows).

| rule (switch) | names | what it does |
| --- | --- | --- |
| jt-read (`--no-jt-read`) | 0 | An `lw` through a known table address with an index that has no bound (lui + index, or one base + index; or a bound past JT_MAX = 0x400) makes a jump-table value (JT, table, None) when the table's first word is an address in the function. Its `jr` goes to the words read from the table while they are aligned addresses in the function (at most JT_WORDS = 256), and to the branch labels as before. Eight switches had no bound: func_00109770, func_001315c0, func_0016f7b8, func_001bd880, func_001f1fc8, func_001f94f0, func_00218218, func_002541b8; **86 case entries** that no branch targets are now analysed from the switch's state (before: from a fresh state as code after a `jr`, or not at all). The log gains func_001f1fc8 / func_001f94f0's text colour read `D_003E8D04[s[1]]` (a byte index past the 9-word table into D_003E8D28, which other functions pin already) and loses one of func_001bd880's D_00625750 lines (the name is pinned by its other accesses). float_reach.txt is unchanged. |
| fmt-read (`--no-fmt-read`) | 4 released | A string literal passed as the format of a printf-family callee (STRING_ARGS kind "fmt": func_00259c88, scePrintf, printf, sprintf's argument 1) reaches its own bytes up to and with its NUL, when every '%' starts a whole conversion, it has no control bytes but tab / newline / return, and no store the analysis sees writes it. Before, such an argument got the callee's reach from the argument register: func_00259698 (the printer) walks its va_list with `ld / lw / lhu -8($s3)`, and in some visit orders its loop joined that pointer with the format's, so the format reached [-2, +6) and pinned the string before it. str-arg (session 27) did not apply because these strings share an object with the strings after them (the NUL is followed by more text, not padding). 33 format arguments take the rule. |

### Verdicts

| name | function | access | verdict | now |
| --- | --- | --- | --- | --- |
| D_00492138 | func_00258f08 (src/sdk/libkernl, TTY) | `func_00259c88(D_00492150, ...)` ("TTY: err ti->wlen=%08x\n"): the analysis read 2 bytes before it, into D_00492138 ("TTY: send err %d\n") | not real (va_list reads) | released |
| D_00492B00 | func_00265ed8 (libgraph) | scePrintf(D_00492B30, ...): D_00492B00 is "sceGsSyncPath: GIF does not terminate\r\n" | not real | released |
| D_00492CF8 | func_00266380 (libgraph) | scePrintf(D_00492D38, ...): D_00492CF8 is "sceGsExecStoreImage: DMA Ch.1 (GS->MEM) does not terminate\r\n" | not real | released |
| D_004932A8 | func_0026ab38 (libcdvd) | scePrintf(D_004932B8, ...): D_004932A8 is "cdread end\n" | not real | released |

### Order dependence (`--visit-seed 1..8`, all rules on)

float_reach.txt is the same as the default order's in seeds 1-6 and 8. Seed 7 adds D_00654570 (session 32's struct
copy in func_00241d60), which cover_check keeps in every order, so **the float set is the same in every order**.

### Left

- Negative indices are modelled only through exact values (neg-keep); an index that may be negative but is not a
  constant pins nothing before the base.
- A jump table whose first word is not code in the function (a table of another function's addresses, or data) is
  still not read; none was seen.
- Session 31's widening / partial loop_entry mechanisms stay (they change event sets in random orders, not names).
