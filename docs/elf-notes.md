# SLPS_251.98 structure notes

Session 1, measured on the fan-patched ELF (see docs/toolchain.md). Re-check
addresses against the retail ELF; the structure should be the same.

- One `PT_LOAD` segment at `0x00100000`, file size `0x394068`, memory size
  `0x575018`; entry point `0x00100008`. Plus a `REGINFO` segment.
- Section headers are present but coarse: a single `main` section
  (`0x00100000`, size `0x394050`) holds code and data together; `.bss` at
  `0x00494080` (size `0x1E0F80`); `.reginfo` at `0x00675000`. No symbol table.
- Code runs from `0x00100000` to about `0x00272C70` (last function ends with
  a tail `j` at `0x00272C5C`); data follows. Use
  `text_start/text_end` in kh1.toml rather than the `main` section bounds.
  The heuristic `make layout` finds about 5,775 functions in that range; it
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
