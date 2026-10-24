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
   `include/platform/pad.h` is the template (libpad2 since session 56). `include/platform/mc.h` (session 44)
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
   **Session 56 wrote the wrappers** (each byte-identical, one header per
   commit): `dma.h` (PlatDmaGetChan / PlatDmaSend, 38 files; libdma named in
   functions.tsv), `gs.h` (PlatGsSyncPath, image load / store packets and
   their execution, reset, vsync, display and drawing environments; 58
   files), `thread.h` (the EE kernel: PlatFlushCache / PlatIFlushCache,
   threads, semaphores, DMAC handlers, the performance counters; 48 files),
   `pad.h` (rewritten for libpad2 / libdbc / libvib: the session-1 template
   wrapped libpad, which the game never links) and `iop.h` (SIF RPC: the
   sound driver's one client in src/sound/snd_rpc.c, sceSifInitRpc).  The SCE
   declarations behind them are in include/sce/ (libdma.h, libgraph.h,
   eekernel.h, libpad2.h, sifrpc.h), hand-written from the public
   signatures with opaque packet types; the PS2 macros cast the game's own
   structs.  Still calling the SDK directly: src/io/discfile.c, cdqueue.c and
   src/game/hdd*.c, src/gfx/opfile.c (libcdvd and the sifdev file calls, most
   still unnamed func_ addresses: docs/sdk.md "Session 56"),
   src/game/dkmovie.c's func_00111238 (a keep-alive stub calling sceCdRead,
   sceIpuInit / sceIpuSync and libcdvd with no arguments; a guess: it keeps
   them linked for the movie overlay dkmovie.x), src/gfx/opimage.c (two libgraph calls through typed function
   pointers), src/model/mdlgs*.c (FlushCache / iFlushCache stored as a hook
   pointer), the GS CSR writes at 0x12000000 / 0x12001000
   (src/screen/display.c, src/game/framectl.c), the VIF / DMA registers that
   src/model/mdlgs.nostrict.c and src/gfx/shadow.c poke through the channel
   (PlatDmaGetChanAs), and the pad masks of src/text/winmenu.c and
   src/menu/customize.c.
   **A trap when writing a wrapper:** gcc 2.96 emits different code for
   `D = f()` (it keeps &D in a saved register over the call) whenever f's
   return type is not exactly D's type, even a typedef of the same struct
   or `void *` against a typedef of void.  So PlatDmaChan is a macro, not a
   typedef; code holding the channel as another type calls
   `PlatDmaGetChanAs(T, id)` (a typed call); and where the original did
   convert (func_0011fa88 stores the int socket into a u32) the variable keeps
   the other type.  A void vs int return can also change registers after a
   call (sceGsResetGraph is declared void).
   **Session 57 wrapped the disc and the files** (each byte-identical, the
   float check, the data names the same): `cd.h` (libcdvd: PlatCdRead /
   Sync / GetError / DiskReady / SearchFile / Seek for the sector reads of
   src/io/discfile.c and cdqueue.c, PlatCdInit / Mmode / InitEeCB at boot,
   PlatCdPOffCallback / PowerOff in src/game/hdd*.c, PlatCdGetError in
   movies.c and dkmovie.c's keep-alive stub), `file.h` (sifdev: PlatFsOpen /
   Lseek / Read / Close for discfile.c's HDD read path and src/gfx/opfile.c,
   the directory, mount, 64-bit seek, ioctl2 and devctl calls of hdd*.c,
   PlatFsReset) and `iop.h`'s second half (PlatSifRebootIop / SyncIop,
   PlatSifLoadModule / LoadStartModule, PlatSifSearchModuleByName).  The SCE
   side is include/sce/libcdvd.h and sifdev.h (sceOpen variadic as in the
   SDK: the calls compile the same).  `gs.h` gained the privileged-register
   helpers (PlatGsPutPmode / PutDispfb1 / PutDisplay1 / PutExtwrite,
   PlatGsGetCsr() & PLAT_GS_CSR_FIELD) for framectl.c, fade.c, dispenv.c and
   display.c, and `pad.h` the button names (PAD_CROSS ... PAD_SQUARE,
   PAD_RSTICK / PAD_LSTICK / PAD_DIR for the stick directions in bits 20-23
   and 28-31): winmenu.c, customize.c and every `D_00425BC8->xN & 0xV` test
   (132 in 31 files, tools/shift/s57pad/padmask.py).  No game file calls
   libcdvd, sifdev, loadfile or the IOP reboot by func_ address now.
   **Session 58 wrapped the vector maths** (each byte-identical, the float
   check and the data names the same; one commit per directory):
   `vu.h` (PlatVu0ApplyMatrix ... PlatVu0ClipAll, PlatVpu0Reset: every
   libvu0 routine in functions.tsv) over include/sce/libvu0.h, the public
   signatures with a vector as `f32 *` and a matrix as `f32 (*)[4]`.  The
   macros cast each argument to the libvu0 type (`(f32)` for a scalar, so a
   float stays a float), so the game's own V4 / V4f / PppVec4 / Mtx types and
   m2c's s32 "pointers" pass unchanged; unlike the other headers the macros
   are the same on every target: the Vita port links a C (NEON) libvu0 under
   the sceVu0 names (src/ppp/keth.nostrict.c's rotation table points at
   sceVu0RotMatrixX / Y / Z directly).  2,633 calls in 192 files, through
   tools/shift/s58vu/conv.py, which drops each file's own prototypes and cast
   views (any indentation, `__asm__` labels, `_dNN` aliases) and prints
   ARITY for a call whose argument count is not libvu0's.  What the build
   caught (docs/matching-tips.md "Session 58"): m2c calls missing a
   pass-through argument, a cast view that passed the float scale first,
   DropShadowMatrix's mode written third, two tail calls read as returns.
   Also: `dma.h` register helpers (PlatDmaPutStat, PlatDmaPutVif1Chcr / Qwc /
   Tadr for the hand-started VIF1 chains of src/gfx/sceneeff.c, dmapool.c,
   mdlpkt.c; PlatVifPutErr, PlatVif1GetStat() & PLAT_VIF1_STAT_BUSY in
   src/model/mdlgs.nostrict.c), `thread.h`'s PlatFlushCacheFn /
   PlatIFlushCacheFn (mdlgs*.c's flush hook D_00351BC8), src/gfx/opimage.c
   through gs.h (its typed libgraph pointers were not needed), and the
   button masks where a local holds the pad state
   (tools/shift/s57pad/padvar.py: winmenu.c, journal_s0/s1/s3.c,
   choice.nofill.c).
   **Session 59:** the scratchpad constants went into `dma.h`
   (PLAT_SPR_BASE / PLAT_SPR_END for src/util/heap.c's frame stack
   D_004F6EB8, PLAT_DMA_SPR for func_00237018's bit-31 scratchpad tag in
   src/gfx/gspkt.nostrict_nofill.c; byte-identical).  The other `| 0x70000000`
   words in src/text/ and src/gfx/ are DMA tag ids (7, end) with a qword count,
   a data format the Vita's chain walker reads, not an address.  Rule 2 is done
   for phase 4: what is left below is replaced whole by the Vita port
   (docs/vita-port-plan.md).
   **Still direct:** dkmovie.c's func_00111238 (calls sceIpuInit /
   sceIpuSync with no arguments, a keep-alive stub: a prototyped wrapper
   would add argument moves, so it stays as m2c wrote it), src/gfx/shadow.c's
   func_00127500 (sets VIF1's CHCR bits through the PlatDmaGetChanAs pointer
   before PlatDmaSend: harmless on a port whose channel is a plain struct),
   field.c's func_00262c78 (`__main`, session 62: gcc's once-only
   `__do_global_ctors`), the libvu0 inline
   VU0 macro code (src/hand/vu0.c and the asm functions: renderer-spec.md),
   and the pad state read through other globals than D_00425BC8 (none
   found by name; a pointer copied into a struct would not show).
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
   each is a few lines. **Started in session 60**: `make host-census`
   (tools/host/census.py, `gcc -m32 -malign-double -DKH1_HOST`) and the null
   platform host/null/plat_null.c; counts in docs/vita-port-plan.md section 5.1.
9. **Write new C so the host compiler takes it too** (session 60). The
   matching build is unchanged by each of these (the macros expand to the
   same tokens on `KH1_PS2`), so use them in new matches:
   - `u128` constants: `x = KH1_Q(0);` not `x = 0;` (common.h: off the EE a
     u128 is a 16-byte struct, so only copies and KH1_Q stores compile;
     the game does no other u128 arithmetic). Declare the type as
     `typedef kh1_s128 u128;` (or kh1_u128), never `mode(TI)` in a game file.
   - A register-pinned local: `register f32 k KH1_REG("$f0");`.
   - A `#define D_X ((T *) D_X)` view that is assigned to is a cast as an
     lvalue (gcc 2.96 only): write `#define D_X (*(T **)&D_X)`. Where that
     changes the match (two cases: src/ai/partyai.c, src/camera/camctl.c),
     keep the cast under `#ifdef KH1_PS2` with the lvalue form in `#else`.
   - Bare `sync` / `sync; ei` / `break`: PlatSync() / PlatSyncEi() /
     PlatBreak() (platform/thread.h).
   - Varargs: `__builtin_stdarg_start` is gcc 2.96's; guard it
     (src/text/fldtext.c) or use src/sdk/libc/stdarg.h's va_start.
   - VU0 macro-mode and other MIPS `__asm__`: keep the asm under
     `#ifdef KH1_PS2` and put a C equivalent in the `#else` (session 61: all
     512 game files now compile, so a new match without one breaks the host
     census). Use the PlatVu0* helpers of platform/vu.h for the usual
     sequences, or tools/host/vu2c.py to translate a long block onto the
     modelled register file (vita-port-plan 5.1a).
   - An uncached-mirror address (`(u32)p | 0x20000000`): PLAT_UNCACHED(p)
     (platform/dma.h).
10. **No register passthrough** (session 62). On the EE a call that leaves
    out arguments still works when the caller's own a0-a7 / $f12+ hold them,
    and a `void` function's caller can read the v0 / $f0 its last call left;
    on x86 and ARM both read garbage. m2c writes both (`void f(void) { g(); }`
    for a wrapper that tail-jumps to `g(x)`, `M2C_UNK g();` called with no
    arguments). Pass every argument the callee's definition takes (add the
    caller's own parameters: a wrapper of `g(a, b)` is `f(a, b)`), and make a
    function whose callers use its value return it (`return g(...);`, with the
    callee's type in the local cast or prototype: a `u16` or `M2C_UNK -> f32`
    conversion stops the tail call, so declare it as the callee returns it).
    Both kept every object bit-identical in session 62.
    `python3 -I tools/host/argcheck.py` lists what is left (a heuristic over
    the text: some hits are benign, e.g. an unused last parameter; it keeps a
    BENIGN table of hits read by hand and left, with the reason).
    Session 63: a call through m2c's `#define f ((T (*)()) f)` cast in the
    callee's own file misses arguments too (argcheck checks those now); type
    the cast when a float is passed (an unprototyped call passes a double).
    A function that matches only when defined void, although its callers read
    the v0 its last statement leaves, is `KH1_V0(s32) f(...)` and ends with
    `KH1_V0_RETURN(x);` (common.h: void and nothing in the PS2 build). A
    callee's return type can change its same-file callers' code
    (func_00111130's did func_001111b0's), so only change the ones a caller
    reads.
    Session 65: a call through a pointer (`w->cb()`, `D_xxx[i].fn()`) has
    no name for argcheck to look up. `python3 -I tools/host/indcheck.py`
    (clang syntax trees) lists them with the targets it can find (data
    tables, the ELF's words, setters, parameters) and a READ table of the
    ones read by hand; a call that matches only without the arguments the
    EE leaves in a0-a3 keeps the EE's call in `#ifdef KH1_PS2` and passes
    them on the host (objwin.c's close callback). Calls of libc / libm
    builtins with missing arguments (asin(), nan()) show as CLANG rows.
    Session 66: no `?` row is left; a new indirect call that indcheck cannot
    resolve gets a READ entry (or a RECORD_SETTERS / RECORD_TABLES /
    FIELD_SAME line) before it is done. When the caller only forwards what it
    was given, add the parameter and pass it: plctl.c's func_0013e558
    takes `(o, dir)` because its class handlers read the direction from a1.

11. **No EE-only argument order or return class** (session 64). The EE passes integer
    arguments in a0-a7 and float ones in $f12-$f19, each its own sequence, and a 64-bit value in
    one register; a float comes back in $f0, an integer in v0. So a prototype or m2c cast that
    puts an f32 before an int the definition has after it (`f(s32, f32, s32)` for `f(s32, s32,
    f32)`), passes an s32 where the definition takes a u64, or declares `void` / `s32` for a
    function that returns f32, still works on the EE. Off the EE every argument has one place
    in one sequence and a 64-bit one takes two (the callee reads the wrong values), and on x86 a
    float return the caller does not take leaves the x87 stack unbalanced (and one it takes from
    a void function pops nothing). `python3 -I tools/host/abicheck.py` lists them (each
    prototype and cast against the definition, by class: 32-bit integer, 64-bit integer, f32,
    f64, 128-bit). Give the declaration the definition's types and order and reorder the call's
    arguments. When the reorder changes the PS2 code (gcc 2.96 evaluates the arguments in
    another order), keep the EE's declaration in an `#ifdef KH1_PS2` branch and give the host
    the definition's order plus a macro that reorders the calls:

        #ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
        void func_001315c0(void *, s32, f32, void *);
        #else
        void func_001315c0(void *, s32, void *, f32);
        #define func_001315c0(a1, a2, a3, a4) (func_001315c0)(a1, a2, a4, a3)
        #endif

    abicheck skips the `KH1_PS2` branch. Session 64 fixed all 146 hits (every PS2 object the
    same): 72 return types; the 64-bit arguments (func_0011fb38's register number and
    func_0011fb78's a1 are s32 in their definitions now, which settles 9 callers, and 5 callers
    declare the u64 they pass); 12 declarations reordered with their calls and 13 host-order
    branches; class19.c's extra argument to func_00121b08 (which takes the f32 only).
    abicheck reads the text; indcheck.py (session 65) compares the same classes from clang's syntax
    trees, so it also sees headers, struct typedefs, `()` declarations, block-scope externs and every
    m2c cast at a call, and an f32 an unprototyped call promotes to double. Run both after a new
    declaration (indcheck prints only the rows to act on: SHORT, ABI, PROMO, CLANG).

## Known absolute addresses in matched code

- func_00171078 (src/hand/text_00170000_s9_w9.c) reads `((s32 *)0x35BD40)[i]`: the original
  used a hard-coded address (the delay-slot fill proves it). Phase 4 must turn it back into
  `D_0035BD40`.
