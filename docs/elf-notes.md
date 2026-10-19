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
  The heuristic `make layout` found 5,774 functions in session 1. Session 2
  fixed two scanner bugs: switch jump tables point at case labels right after
  a `jr $ra`, and 55 of those had been taken for function starts; and the
  libkernl syscall stubs (no prologue, reached by tail calls) were merged
  into their neighbours (92 split out). Now 5,811 functions. Session 4: a tail
  call (`j` outside the function plus its delay slot) now ends a function
  when no earlier branch jumps past it, which split 580 functions (wrappers
  such as libm's `w_*` and small functions after a tail call) from the
  ones before them: 6,911 functions. Hand fixes are still possible.
- **36 `.DVP.overlay` sections** plus `.DVP.ovlytab` / `.DVP.ovlystrtab`:
  VU microcode assembled with dvp-as (names like
  `.DVP.overlay..0x0.374643955.7345.0`, some with `unknvma`). These are the
  VU1/VU0 programs: 22 programs, documented in docs/renderer-spec.md
  (session 14).
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
  decoders using `addu t4,zero,a0` idioms): these need `.s` files, not C
(session 5: src/asm/text_0024e0a4.s).
  Also contains the HDD install code (`hdd0:`, `pfs0:kingdom.img`,
  `PP.SLPS-25198.0.KINGDOM`) and memory card paths (`BISLPS-25198-xx`).
- **sdk** `0x0024F2E0`-`0x00272C70` (570 functions): Sony libc (printf at
  `0x002516B8`/`0x002524A0`), libkernl (syscall stubs from `0x00257EB0`),
  then libgraph, libdma, libdbc, libpad2, libvib, libcdvd, libpc, libmc,
  libipu, located by references to their `PsII…2500` version banners. These
  are not ported; the Vita layer replaces them. Finer per-library segments
  can be added later.

## Runtime-loaded code outside the ELF

Game code tail-calls `0x00F20000` (e.g. `func_0012a400` when bit 13 of
`D_002C5958` is set, with `a0 = 6`), and `func_00111020` passes `&D_00F20000`
plus a callback to `func_00120748`. `0x00F20000` is beyond the end of `.bss`
(`0x00675018`), so something is loaded there at run time: an overlay or a
debug/extra module from the disc. Not investigated yet; it matters for the
port (it is code the ELF does not contain).
