# SLPS_251.98 structure notes

Session 1. Measured on the pinned retail ELF (SHA-256 `1993a4da…`, see
docs/target-versions.md); the fan-patched ELF has the same layout.

- One `PT_LOAD` segment at `0x00100000`, file size `0x394068`, memory size
  `0x575018`; entry point `0x00100008`. Plus a `REGINFO` segment.
- Section headers are present but coarse: a single `main` section
  (`0x00100000`, size `0x394050`) holds code and data together; `.bss` at
  `0x00494080` (size `0x1E0F80`); `.reginfo` at `0x00675000`. No symbol table.
- Code runs from `0x00100000` to about `0x00272C70` (last function ends with
  a tail `j` at `0x00272C5C`); data follows. Use
  `text_start/text_end` in kh1.toml rather than the `main` section bounds.
  The heuristic `make layout` finds 5,774 functions in that range; it
  misses some functions reached only by tail `j` and merges a few adjacent
  tiny ones, so expect hand fixes.
- **36 `.DVP.overlay` sections** plus `.DVP.ovlytab` / `.DVP.ovlystrtab`:
  VU microcode assembled with dvp-as (names like
  `.DVP.overlay..0x0.374643955.7345.0`, some with `unknvma`). These are the
  VU1/VU0 programs to document as the renderer spec in phase 3.
- Statically linked SCE libraries, SDK 2.5.0: libkernl, libgraph, libdma,
  libipu, libpad2, libdbc, libvib, libcdvd, libpc, libmc.
- Source file names that survive in asserts: `ttlib/ui.c`, `ttlib/ui_gauge.c`,
  `src/decode.c`, `src/sa_task.c`.

## Segments (kh1.toml `[[segment]]`)

- **game** `0x00100000`-`0x0024F2E0` (5,204 functions). Starts with crt0
  (syscalls at `0x00100178`). The last game functions call into game code
  (`0x0024F210` calls `0x001560F8`); from `0x0024F2E0` on, functions only call
  printf internals and SDK code. Includes hand-written assembly at
  `0x0024E0F0`-`0x0024EBF8` (`sq` context save, `lq`/VU0 macro code, LZ-style
  decoders using `addu t4,zero,a0` idioms): these need `.s` files, not C.
  Also contains the HDD install code (`hdd0:`, `pfs0:kingdom.img`,
  `PP.SLPS-25198.0.KINGDOM`) and memory card paths (`BISLPS-25198-xx`).
- **sdk** `0x0024F2E0`-`0x00272C70` (570 functions): Sony libc (printf at
  `0x002516B8`/`0x002524A0`), libkernl (syscall stubs from `0x00257EB0`),
  then libgraph, libdma, libdbc, libpad2, libvib, libcdvd, libpc, libmc,
  libipu, located by references to their `PsII…2500` version banners. These
  are not ported; the Vita layer replaces them. Finer per-library segments
  can be added later.
