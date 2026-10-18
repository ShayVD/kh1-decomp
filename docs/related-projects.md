# Related projects

Other public work on Kingdom Hearts that is worth reading for ideas. Check the
license before reusing anything: code, headers and symbol lists from a repo
with no license cannot be copied into kh1-decomp without the author's
permission. Facts learned by reading (a compiler choice, what a function does)
are fine to rediscover and write up in our own words.

## ethteck/kh1 ("Kingdom Hearts De:Compiled")

<https://github.com/ethteck/kh1>, reviewed 2026-10-16 at commit `0df3b65`.

- **Targets:** original JP `SLPS_251.05` (SHA-1 `9dabbf86…`, the default) and
  Final Mix `SLPS_251.98` (SHA-1 `e70bda789916142aafb53d85cef2e806b35ad8d8`).
  That Final Mix SHA-1 is the SHA-1 of our pinned ELF (SHA-256 `1993a4da…`),
  so it is the same file. Most of their work is on JP; the Final Mix config
  had 56 named symbols and one C file.
- **Toolchain:** splat + ninja + `configure.py`, decomp.me preset 108,
  decomp-permuter, frogress. Game code: ee-gcc 2.96, `-O2 -G0`, which agrees
  with docs/toolchain.md. SDK libraries are built with a second compiler,
  **ee-gcc 2.9-991111** (`-isystem include/gcc-991111`). Worth testing on our
  SDK near misses (docs/sdk.md).
- **Progress (rough):** about 1,240 functions written in C, about 1,720 still
  `INCLUDE_ASM`, counted from the source (not built). Matching is checked by
  rebuilding the whole ROM against a SHA-1.
- **Layout ideas:** file splits named after ReCoM-style structures (`src/ppp/`
  particle system, `gumi.c`, `worldfile.c`, `disk.c`, `memcard.c`), SDK in
  `src/lib/` (libkernl, libmc, libvu0). Useful hints for naming our anonymous
  code.
- **Activity:** Sep 2023 to Nov 2024 (104 commits, mainly Ethan Roseman and
  Noah McQueen), quiet through 2025, tooling refresh and move to GitHub
  Actions in Aug 2026.
- **License:** none, so all rights reserved by default. Read for ideas only;
  ask the maintainers before copying anything, and consider coordinating since
  both projects match the same Final Mix ELF.

## Yannis100/vita-port-skill

<https://github.com/Yannis100/vita-port-skill>, reviewed 2026-10-18 (MIT,
single author, first published 2026-10). An AI-agent "skill" plus reference
notes for porting games to the Vita. Not run or installed; read only.

- **Useful for phase 5:** VitaSDK/CMake setup, memory budget (256 MiB, up to
  365 MiB with `ATTRIBUTE2=12`), a startup settings file (heap, stack,
  clocks), VPK packaging and a VPK checker script, on-device debugging
  (vitacompanion, vita-parse-core), and a write-up of the Halo CE Vita port
  (decompilation + custom GXM backend, precompiled shader bank, null-GXM
  Linux build), which is the closest model to our route.
- **Useful now:** the PS2 FPU and host-build notes, written up as rules 7 and
  8 in docs/portability.md.
- **Not relevant:** Android .so loaders, Java/TeaVM, OpenGL-to-vitaGL ports.
  Nothing on matching or on VU1/GS documentation.
- **PS2 projects it points to** (all early/experimental, worth checking at
  phase 3): ValdiaKun/TimeSplitters (VIF/VU1 interpreter capturing GIF
  packets), mirou1611/AstraRecomp (PS2 static recomp + Vita runtime),
  SandstoneDev/universal-ps2-recompiler (PS2 to PSP).
- **Caveats:** many "verified" entries point at work-in-progress repos, and
  the skill says its SDK facts go stale. Treat it as a reference. Plan: load
  it as a skill (or copy its CMake template and VPK checker, with credit) when
  phase 5 starts.
