# Review of the GovanifY/kh2 decomp build system (for reuse in kh1-decomp)

Reviewed at commit `8b5bc47` of https://github.com/GovanifY/kh2 (MIT licence),
October 2026.

## How kh2 works

kh2 is a **patch-in-place** decomp, not a full relink:

1. `layout.tsv` lists every function in `SLPM_666.75` as `addr end size name`
   (11,284 functions). It says "AUTO-GENERATED, DO NOT EDIT", but the generator
   is **not in the repo**; it was exported from an analysis tool (most likely
   Ghidra, given the `FUN_xxxxxxxx` / `thunk_FUN_` names).
2. `functions.tsv` is the symbol registry: `symbol<TAB>addr`. Every decompiled
   function, plus every external symbol decompiled code calls or reads, gets a
   line. Symbols can be written as C++ signatures and are mangled by
   `tools/common.py` (Itanium ABI, i.e. gcc 3.x mangling).
3. Every `src/**/*.cpp` is compiled with
   `ee-g++ -O2 -g0 -x c++ -fno-exceptions -fno-rtti -fpermissive -ffunction-sections`.
   `tools/build_elf.py` generates:
   - `out/generated/symbols.ld`: `PROVIDE(sym = addr);` for every registry entry
     and every `D_xxxxxxxx` / `func_xxxxxxxx` name found in sources, so
     undecompiled code and data resolve to their original addresses;
   - `out/generated/cxx_sections.ld`: one output section per decompiled function,
     pinned at its original address (`.kh2cxx_<addr> 0x<addr> : { KEEP(*(.text.<sym>)) }`);
   - `out/generated/objects.mk`: the object list for make.
4. `ee-ld` links those objects with `kh2.ld`. `build_elf.py normalize` then
   copies the **original ELF** and overwrites each decompiled function's bytes
   with the linked bytes (zero-padding or truncating to the original size).
   Result: `kh2.elf`. A "fast-link" path re-patches only changed sources.
5. `make verify` byte-compares the main segment, `.ctors` and `.dtors` of
   `kh2.elf` against the original and prints `MATCHED!` on success.
6. `tools/objdiff.py` writes `objdiff.json`. Each source file becomes a unit
   whose target object is the original bytes of its functions, and whose base
   object is the patched bytes, both re-assembled from raw `.word`s with symbol
   labels. Undecompiled runs become `unmatched/asm_segment_<addr>.s` units. It
   also emits decomp.me scratch settings (`ee-gcc3.2-040921`, same flags) and a
   progress report; CI publishes a shields.io badge to gh-pages.
7. Toolchain: `docker/ps2/ee-gcc3.2-040921-full.tar.gz` via git LFS (73 MB:
   ee-gcc/g++/as/ld/objdump/objcopy, 32-bit Linux binaries), loaded into an
   Ubuntu 24.04 image with `libc6:i386 libstdc++5:i386` and objdiff-cli 3.7.0.
   Every compile runs inside `docker run`.

## What is reusable as-is for KH1

- **The patch-in-place model.** Decompiled functions can be matched one at a
  time without first producing a relinkable disassembly of the whole ELF. It
  gets to first matches fastest. It does not make the code shiftable, which is
  fine because shiftability is phase 4.
- **File formats**: `functions.tsv` (symbol registry), `layout.tsv` (function
  boundaries), `src/` picked up automatically, `nonmatchings/` as an unbuilt
  dumping ground, `D_xxxxxxxx` / `func_xxxxxxxx` placeholder naming.
- **The linker-script trick** (one pinned output section per function plus
  `PROVIDE` for everything else) and the byte-patch + verify step.
- **objdiff integration design**: per-source units, auto `asm_segment` units for
  undecompiled runs, progress categories, decomp.me scratch metadata.
- **CI shape**: download the ELF from a secret URL, `make verify`, publish a
  progress badge. Works for a public repo without committing the ELF.
- `.clang-format` and the README workflow text.

## What has to change for KH1

| Area | kh2 | KH1 change |
|---|---|---|
| Compiler | ee-gcc 3.2-ee-040921 (2004 SDK) | KH1 shipped in 2002, which predates every ee-gcc 3.2 build. Expected: ee-gcc 2.96-ee-001003-1 or a 2.9-ee-991111 variant. Confirmed in step 3 once the ELF is in hand. |
| Name mangling | Itanium (`_ZN5SOUND4initEv`) in `common.py` | gcc 2.x uses the old ARM-style scheme (`init__5SOUND`). The mangler must be replaced or made per-compiler. |
| Hardcoded layout | `MAIN_VADDR`, `MAIN_SIZE`, `.ctors`/`.dtors` addresses and file offsets in `common.py`, `kh2.ld` | Derive from the KH1 ELF's program headers; keep in one config file. |
| Target file | `SLPM_666.75`, `KH2_ORIG` env var | Our serial's ELF name; `KH1_ORIG` env var. |
| `layout.tsv` generator | Not published | We need our own: a function-boundary pass over the KH1 ELF (jal targets + `jr ra` scan, or a Ghidra headless export). |
| Toolchain delivery | git LFS archive of a full 3.2 toolchain | Wrong compiler for KH1. decomp.me's `decompme/compilers` GitHub releases ship ee-gcc 2.9x/2.96/3.2 as Linux i386 binaries (cc1/cc1plus/as) and are downloadable without LFS. binutils `mips-linux-gnu` (Ubuntu package, supports `-march=r5900`) covers ld/objcopy/objdump. A download script beats committing a binary blob. |
| Docker | Mandatory; every tool call shells into a container | Optional. Native Linux needs only `libc6:i386` (and `libstdc++5:i386` for 3.x); Docker stays as a fallback for macOS. |
| Flags | `-x c++ -fno-exceptions -fno-rtti -ffunction-sections` | 2.9x accepts these, but KH1 may be C, C++ or mixed; flags are set per source group after step 3. `-G0` vs small-data (`$gp`) usage must be checked in the KH1 code (kh2 uses `-G0`). |
| Symbols | Names recovered from the KH2 PS3 E3 demo | No equivalent known for KH1. Names will come from strings, the OpenKH format docs, and the HD ports. |
| Overlays | `ovl_*` folders exist in KH2 | KH1 overlay structure unknown until the ELF and disc layout are inspected. |

## Decision taken for kh1-decomp

Reimplement the same model in a smaller, config-driven tool set
(`tools/kh1tool.py`), keeping kh2's file formats and conventions so contributors
from kh2 feel at home. The kh2 tools are not vendored because about half of
their code is Docker plumbing, caching and Itanium-specific handling that does
not apply here.
