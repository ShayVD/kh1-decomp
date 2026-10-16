# Portability rules (for the future Vita port)

These apply from the first decompiled function, so phase 5 does not have to
rewrite matched code.

1. **No absolute PS2 addresses in gameplay logic.** Placeholders such as
   `D_0035A0C0` and `func_00123456` are fine while a function is being matched
   (they resolve through `out/gen/symbols.ld`), but must be renamed to real
   symbols once understood. Never write `*(int *)0x0035A0C0` or cast integers
   to pointers into the PS2 address map. Hardware register addresses (GS, DMA,
   VIF, timers) only appear inside platform code.
2. **Every platform call goes through a wrapper in `include/platform/`.**
   Categories: `pad`, `gs` (graphics), `dma`, `vu`, `sound` (libsd/IOP),
   `iop` (file I/O, modules), `memcard`, `thread` (EE kernel). Wrapper names
   start with `Plat`. On the PS2 build a wrapper is a macro or `static inline`
   for the SCE call, so it compiles to exactly the original instructions. On
   the Vita build the same names are implemented with vitasdk.
   `include/platform/pad.h` is the template.
3. **SCE declarations live in `include/sce/`**, written by hand from public
   signatures. Never copy Sony SDK headers or library code into the repo.
   Functions that belong to statically linked SCE libraries are tracked under
   their own `[[segment]]` in `kh1.toml` and are not ported: the Vita layer
   replaces them.
4. **Inline asm, VU0 macro mode and MMI (128-bit) code** go in clearly named
   functions under `src/platform/` or are flagged in `nonmatchings/` with a
   note. Gameplay code that needs vector maths calls a `Plat`/math helper, so
   the Vita build can substitute NEON or plain C.
5. **Sizes and layout**: use `u32`/`s16`/etc. from `include/common.h` for
   anything that mirrors file formats or saved data. On the EE `long` is
   64-bit, on the Vita it is 32-bit, so never use plain `long` for
   on-disk/in-memory structures that must keep their layout.
6. **Endianness** is little on both platforms; alignment rules differ only for
   128-bit types, which are platform code.
