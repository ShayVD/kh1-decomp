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
   `include/platform/pad.h` is the template. `include/platform/mc.h` (session 44)
   wraps libmc for src/memcard/, the only code that calls it; the save and
   load screens queue requests (include/memcard/mcreq.h) and never touch libmc.
   Session 45 put the GS packet code in src/gfx/ (gspkt*.c: the drawing
   environment and the GIF DMA sender func_00237018, which tests for the
   scratchpad at 0x70000000; drawlist*.c and prim*.c build GS primitives
   with libvu0) and named libvu0 (docs/sdk.md): the next wrappers are
   include/platform/gs.h for func_00237018, FlushCache and sceGsSyncPath, and a
   vector maths header for the sceVu0 calls.
   Session 54 found more platform code to wrap: src/pad/padread*.c (libpad2
   and libdbc: scePad2Init, scePad2CreateSocket, scePad2GetButtonProfile,
   sceDbcInit; scePcStart), src/io/discfile.c and src/io/cdqueue.c
   (libcdvd: sceCdInit, sceCdRead, sceCdDiskReady, sceCdSearchFile;
   sceSifInitRpc) for an `iop` / `cd` wrapper, and src/sound/sndctl.c, which
   only calls src/sound/snd_rpc.c (already the platform file for sound).
   Session 55 added: src/util/thread.c (the kernel's threads and semaphores:
   CreateThread, CreateSema, WaitSema, iSignalSema), src/gfx/dmapool.c (libdma
   sends on the channel D_002A6B84, the packet buffers), src/game/dkmovie.c
   (the movie overlay dkmovie.x at D_00F20000 and sceIpuInit / sceIpuSync),
   src/screen/dispenv.c and src/screen/display.c (sceGsDefDispEnv,
   sceGsPutDrawEnv, the GS CSR at 0x12001000 / 0x12000000 read and written
   directly), src/screen/capture.c (sceGsExecStoreImage / LoadImage of the
   frame) and src/game/framectl.c's func_0010f658 (the display flip).
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
7. **Floating point is not IEEE on the EE.** The R5900 FPU flushes denormals
   to zero, has no infinities or NaNs (overflow saturates to the largest
   finite value), and rounds toward zero. ARM VFP/NEON on the Vita is IEEE by
   default, so the same matched code can produce slightly different results.
   For the Vita build: compile game code with `-ffp-contract=off` (no fused
   multiply-add), and keep any code whose behaviour depends on these edge cases
   (physics, collision, replays, anything compared for equality) easy to find,
   so a clamping/rounding helper can be added there if bugs show up. Do not
   add such helpers to matched PS2 code. Source: the PS2 recompiler notes in
   vita-port-skill (see docs/related-projects.md); not yet tested on our code.
8. **Plan a desktop host build with a null renderer.** Halo CE's Vita port
   (a decompilation, like ours) builds the game for Linux against a GPU layer
   that does nothing, to measure CPU cost and catch crashes without hardware.
   The `Plat` wrappers make the same thing possible here: a `null` platform
   that implements every wrapper as a no-op or a file read lets phase 4/5 run
   the game logic on a PC first. Keep wrappers narrow enough that a stub of
   each is a few lines.

## Known absolute addresses in matched code

- func_00171078 (src/hand/text_00170000_s9_w9.c) reads `((s32 *)0x35BD40)[i]`: the original
  used a hard-coded address (the delay-slot fill proves it). Phase 4 must turn it back into
  `D_0035BD40`.
