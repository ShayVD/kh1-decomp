# Vita port plan (phase 5)

Written in session 59 (2026-10-24), at the end of phase 4's wrapper work. Static: nothing here has been built
for the Vita yet. It lists what each platform header needs on the Vita, what is still PS2-only code outside the
headers, what still pins the original layout, and the order to bring the port up. Sources: the headers'
own comments (include/platform/*.h), docs/portability.md, docs/renderer-spec.md, docs/shiftable-plan.md and
docs/related-projects.md (vita-port-skill: VitaSDK / CMake, memory budget, VPK packaging, the Halo CE port).

## 0. Ground rules carried over

- The matching PS2 build stays the reference: every Vita change is either a new file (src/vita/ or a
  platform/ implementation) or a `#ifdef KH1_PS2` branch inside include/platform/. No matched C changes for
  the port unless it is byte-identical on the PS2 build (the same rule as phase 4).
- The repo still carries no game data. The port reads the user's own disc: an extraction tool (phase 5,
  last item) writes KINGDOM.IMG's files and the overlays to the memory card / ux0: data directory.
- Pointers are 32 bits on both the EE and the Vita's Cortex-A9, so every struct that holds a pointer keeps
  its layout and the model / map files' in-place relocated pointers (docs/structs.md) work as they are.
  **A 64-bit desktop host build (portability.md rule 8) must be built `-m32`** for the same reason.

## 1. The platform headers on the Vita

Every header already declares the Vita side (the `#else` of `KH1_PS2`): the same names as plain functions.
What each implementation does:

| header | PS2 side | Vita side (vitasdk) | size |
| --- | --- | --- | --- |
| pad.h | libpad2, libdbc, libvib | `sceCtrlPeekBufferPositive` (+ `sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG)`), the result written in libpad2's 128-byte layout (digital bytes 0-1 active low, sticks after) so src/pad/padread*.c decodes it unchanged; L2 / R2 / L3 / R3 from the rear touch pad or the back of the screen; vibration a no-op (PS TV: `sceCtrlSetActuator`) | small |
| thread.h | EE kernel | `sceKernelCreateThread` / `StartThread`, `sceKernelCreateSema` / `WaitSema` / `SignalSema` (the i* forms the same), priorities mapped to the Vita's range; FlushCache a no-op; the DMAC handlers become a call from PlatDmaSend's end (the draw list's interrupt-driven executor, renderer-spec §4.1, turns into a plain loop); PlatPcStart / Stop no-ops | small |
| mc.h | libmc | a save directory per "BISLPS-25198-NN" under ux0:data/kh1/ (`sceIoOpen` ...); synchronous, PlatMcSync answers at once; the save icons are the PS2 icon files, not shown | small |
| cd.h | libcdvd | sectors of the user's extracted KINGDOM.IMG (or the whole ISO) with `sceIoLseek` / `sceIoRead`; PlatCdSync / GetError answer 0, DiskReady 2; power-off a no-op | small |
| file.h | sifdev | the same calls on ux0:data/kh1/; the HDD devices answer "no drive" (PlatFsDevctl < 0) | small |
| iop.h | SIF RPC, IOP reboot, module loads | no IOP: the module loads and the reboot succeed, `PlatSifSearchModuleByName` -1; `PlatSifCallRpc` on server 17 decodes the sound commands in place (§3, sound) | small, but the sound driver behind it is large |
| math.h | `sqrt.s` inline | `sqrtf` (VFP `vsqrt.f32`); see portability.md rule 7 for the EE's flush-to-zero / no-NaN differences | trivial |
| vu.h | libvu0 (VU0 macro mode) | a C / NEON libvu0 under the sceVu0 names of include/sce/libvu0.h (session 58: the macros are the same on every target); keep the VU's clamps in PlatVu0Normalize (vrsqrt) and PlatVu0DivVector | medium (about 60 routines, each a few lines) |
| gs.h | libgraph, GS privileged registers | the renderer's model of the GS: image loads / stores are texture uploads / reads in a 4 MiB GS-memory mirror; the display / draw environments and PMODE / DISPFB / DISPLAY values are kept for the final pass; SyncPath / SyncV return at once (SyncV paces on `sceDisplayWaitVblankStart`) | medium |
| dma.h | libdma, DMA / VIF registers | `PlatDmaSend` walks the DMA chain (tag ids 0-7, bit 31 = scratchpad) and hands GIF packets (channel 2) to the GS parser and VIF1 packets (channel 1) to the VIF1 / VU1 replacement (§2); the hand-started VIF1 chains (Chcr with STR) are the same walk at the last Tadr; the status reads answer idle | large (it is the renderer's front end) |

Not yet a header (portability.md rule 2 "Still direct", left for phase 5 because they are platform files the
Vita replaces whole):

- **src/sound/snd_rpc.c**: the EE side of the IOP sound driver (51 functions, RPC server 17, one 8 KiB buffer,
  a queued 8-word command format). The Vita build replaces the file, or keeps it and implements PlatSifCallRpc.
- **src/game/dkmovie.c** and the movie overlay dkmovie.x: sceIpuInit / sceIpuSync and the IPU's MPEG-2.
- **src/gfx/gspkt.nostrict_nofill.c** func_00237018 (the GIF sender: tag, flush, sync, send) and
  src/gfx/shadow.c's CHCR bit pokes: both work through dma.h once PlatDmaSend walks chains.
- The scratchpad is wrapped (session 59): src/util/heap.c's frame stack D_004F6EB8 runs from PLAT_SPR_BASE to
  PLAT_SPR_END and func_00237018 tags scratchpad packets with PLAT_DMA_SPR (dma.h). On the Vita the header
  already makes PLAT_SPR_BASE a 16 KiB buffer (`PlatSpr`, to define in src/vita/) and PLAT_DMA_SPR 0 (a Vita
  pointer can have bit 31 set). The `n | 0x70000000` words in src/text/ and src/gfx/ are DMA end tags, data the
  chain walker reads, not addresses.

## 2. The renderer (the largest piece)

docs/renderer-spec.md §5 is the design: do not emulate VIF / VU; decode the model data on the CPU and draw with
GXM. In order:

1. **GIF packet parser** (PATH3, 2D): every UI, font, fade and texture upload goes through PlatDmaSend on
   channel 2 as GIF tags (PACKED / REGLIST / IMAGE). Parse them into a GS state machine (the registers of
   renderer-spec §3.2) and emit GXM draws: sprites and triangles with the TEST / ALPHA / TEX0 / CLAMP state
   of §5's table. This alone shows the title screen, menus and text.
2. **GS memory mirror**: 4 MiB, PSMCT32 / PSMT8 / PSMT4 / CLUT layouts swizzled as the GS does, because the
   game uploads to GS addresses and later draws with TEX0 pointing there (the off-screen buffer at 0x3A0000,
   §3.4, is drawn to and then used as a texture). Decoded textures cached by (TBP, PSM, CLUT) and dropped
   when an upload overwrites their blocks.
3. **VIF1 / VU1 replacement** (PATH1, 3D): channel 1 chains carry UNPACKs and MSCALs to the 22 VU1
   microprograms (renderer-spec §2: renderer A P0-P8 for the maps, renderer B P10-P20 for characters,
   P21 on VU0). Each program becomes a GXM vertex / fragment shader pair over vertex data decoded at load
   (§5's table: strip flags to indices, skinning from the matrix palette, the fog and lighting clamps).
   Pre-compile the shaders (vita-port-skill: the Halo CE port's shader bank).
4. **The draw list** stays: built in frame N, replayed in frame N+1 in key order (§4.2), from a loop instead
   of the DMA-end interrupts.
5. **The final pass**: the 384 -> 448 copy, the fade colour and the flashes become a full-screen pass to the
   960x544 framebuffer (4:3 in the middle, or a widened projection later).

The **VU0 macro-mode asm** (src/asm/vu0_render_1.s and vu0_render_2.s: func_001b8198, 001b6910, 001b1ab8,
001afac0, 001b3870, 001ab0e0, 001ae010; 785 KB of words, hand-written inside a gcc shell, docs/workflow.md
"Session 7") has no C. These build effect / particle packets with VU0 in the loop; each needs a C rewrite
from its disassembly (not matching: a functional C version for the port only, in src/vita/). The same for
src/asm/text_0024e0a4.s (sq context save, lq / VU0 code, decoders, the 0x00121F6C block copy, the 0x00121FC4
normalize, the 0x00162C5C matrix multiply) and src/asm/text_001aa1f8.s (128-bit clears and the func_001bfac8
context switch, which becomes a Vita thread or a ucontext switch). The 116 game files with `__asm__`
(mostly `sync`, `sync.l`, `mfc0` and VU0 macros) need a `KH1_PS2` guard or a C equivalent each: a script can
list them (`grep -rln __asm__ src --include=*.c | grep -v ^src/sdk`).

## 3. Other subsystems

- **Sound**: the IOP driver on the disc is not ours to run. The Vita side decodes snd_rpc.c's commands (sound
  effect slots, 4 streams, the BGM sequences, volumes) and plays them with `sceAudioOut` through a small
  mixer: VAG ADPCM for the banks, the sequence format still to document (a session of its own: the IOP
  module's command handler, read from the disc's IRX). The status block D_0063D640 the IOP wrote by DMA is
  written by the mixer.
- **Movies**: the PSS files are MPEG-2 video for the IPU. The Vita's `sceAvPlayer` plays H.264 MP4, so either
  the extraction tool transcodes them (needs a host ffmpeg: the user's own data, never shipped) or the port
  links a software MPEG-2 decoder (libmpeg2, GPL: check the licence against ours first).
- **Overlays**: 12 MIPS overlays load at 0x00F20000 (dkmovie, dktitle, gb, wm, xl_limit, xs_bambi,
  xs_dh_break, xs_dumbo, xs_genie, xs_mushu, xs_simba, xs_tink; shiftable-plan "Session 13: overlay
  fixups"). They are game code on the disc, not in the ELF, so **the port needs them decompiled to C** (not
  matching against the ELF, but against the overlay files; the same toolchain and objdiff). wm.x (world
  map, 2,994 calls) and gb.x (Gummi ships, 1,584) are the big ones; dktitle.x is needed first (the title).
  Until then the port can only run the field: this is phase 5's largest unknown after the renderer.
- **The 9 unmatched functions**: their best drafts (nonmatchings/session23-match/) are functionally the
  same code; `SHIFT_DRAFTS=1` builds them. The Vita build uses the drafts.
- **Types**: `typedef int u128 __attribute__((mode(TI)))` is in 50 game files; 32-bit ARM gcc has no 128-bit
  integer. On the Vita u128 becomes a 16-byte aligned struct of four u32 (copies and clears only: check
  each file for arithmetic on it). s64 / u64 (239 files) are fine on ARM (slower). Plain `long` is 64-bit on
  the EE and 32-bit on the Vita (2 game files: check them).
- **Floating point**: rule 7 (flush-to-zero, no infinities, round toward zero). Compile with
  `-ffp-contract=off`; set the VFP's flush-to-zero bit at start (FPSCR.FZ) to match the EE's denormals.

## 4. What still pins the original layout

Nothing in the port needs the PS2 addresses, but these still assume them (docs/shiftable-plan.md):

- **The fixed memory map** (session 26): the pools at 0x6A0000-0x7F2C00, the block heap D_00820000 -
  D_009A0000, the load area D_009A0000 - 0xF20000 (dktitle.x names 0x9A0000 and 0xBA0000 itself), the overlay
  area D_00F20000, the 12 slots of 0x40000 at D_00FE0000, the area at 0x1CE0000 and the stack. The game C
  uses them through D_ names, so the Vita link (or a src/vita/memmap.c) defines each as a static array or a
  block from one big allocation (about 30 MiB: the Vita has 256 MiB for an app, 365 MiB with `ATTRIBUTE2=12`).
  The overlays' own constants (dktitle.x's 0x9A0000) follow when they are decompiled.
- **The data blob**: 1,352 names reach_check pins (session 59; an index or walk may run into the next name, so their order
  matters) plus addend_check, split_check and float_keep.txt. On the Vita every data name is defined in C or
  in src/data/*.s; the .s pieces must become C (or be assembled for ARM as plain `.word` / `.byte` data, which
  the GNU assembler accepts) **in the same order** wherever a pin says the order matters. Keep one
  translation unit per pinned run so the Vita linker keeps the order.
- **Absolute addresses in data**: pointer tables in .data hold PS2 addresses as words where the shift tools
  could not prove a relocation (shiftable-plan "Session 13: reloc review", the "ambiguous" items). Each must be
  a symbol in C before the Vita build links; the M12 shifted build boots (session 29) only because the shift
  tools patch the rest.
- **func_00171078**'s `((s32 *)0x35BD40)[i]` (portability.md "Known absolute addresses"): `D_0035BD40` on the
  Vita (the KH1_SHIFTABLE variant already does it).

## 5. Bring-up order

1. **Host build first** (portability.md rule 8): a Linux `-m32` build of all game C against a null platform
   (every Plat* a stub, PlatCdRead from the extracted image, the draw calls dropped). Goal: the code
   compiles off the EE (u128, `__asm__` guards, the asm files as C stubs), links with the memory map of §4,
   and runs the boot to the title without crashing. This finds most port bugs without hardware.
2. **Extraction tool** (tools/vita/extract.py, the user's disc in, ux0:data/kh1/ out): KINGDOM.IDX / IMG
   (tools/shift/extract_kingdom.py already reads them), the overlays, the IRX sound banks, the movies.
3. **vitasdk skeleton**: CMake + VPK (vita-port-skill's template, with credit), the heap size, the memory map
   from one allocation, pad / thread / mc / cd / file / iop on vitasdk. The game runs headless (no draws).
4. **2D**: the GIF parser and the GS memory mirror on GXM: logos, the title, the menus, the save screens.
5. **3D**: renderer A (maps), then B (characters), then the VU0 effect routines rewritten in C.
6. **Sound**: the snd_rpc command decoder and the mixer.
7. **Overlays**: dktitle.x first, then dkmovie.x (with the movie decision of §3), then wm.x and gb.x, then the
   summons (xs_*.x) and xl_limit.x.
8. **Performance**: the Cortex-A9 at 444 MHz runs C compiled from the EE's code; the VU0 maths in NEON
   (vu.h) and the renderer's CPU decode are the likely hot spots; measure on the host build first.

### 5.1 Session 60: the host build census

`make host-census` (tools/host/census.py; after a PS2 `make`, which cuts the data pieces) compiles every
game C file (src/ minus src/sdk/: 512 files) with the host compiler to 32-bit x86 objects in out/host/, and
with `--link` also assembles src/data/*.s for x86 (`.word` read as `.long`), compiles the null platform
host/null/plat_null.c and counts the symbols still undefined. Flags: `-m32 -malign-double -std=gnu89 -O1
-fno-strict-aliasing -fno-pic -fno-stack-protector -DKH1_HOST` and gcc 2.96's leniency (implicit
declarations, int / pointer conversions) as warnings. `-malign-double` matters: i386 aligns long long to 4
inside structs, the EE and the Vita's EABI to 8 (actor.h's layout check fails without it). The PS2 build is
unchanged: every commit built byte-identical, the 677 objects are bit-identical to session 59's and `make
shift` passes M0.

**Compile census** (first error per file; `--files CAUSE` lists them, `--show FILE` prints one):

| step | gcc 13 | what fixed it |
| --- | --- | --- |
| start (KH1_PS2 headers, no fixes) | 298 / 512 | |
| common.h: `KH1_HOST` target (takes the platform headers' `#else` side), u64 / s64 as long long off the EE | | bitfields wider than their type (178 errors), struct size checks (62) |
| u128: `typedef kh1_s128 u128;` in the 50 files (common.h: TI on the EE, a 16-byte aligned struct of four u32 elsewhere) | 443 | "unable to emulate TI" (69) |
| `KH1_Q(v)` for the 53 constant stores into u128 (clears, GIF tags, GS register words) | 459 | the game does **no u128 arithmetic**: every u128 use is a copy or a constant store |
| builtins on (as the EE game code has them), CONTEXT_ONLY = weak only off the EE | 463 | fabsf implicit-declaration clashes, a `.ctx` section with code and data |
| PlatSync / PlatSyncEi / PlatBreak (thread.h) for 21 bare `sync`, one `sync; ei` and src/util/param.c's `break` traps | 465 | |
| `KH1_REG("$n")` for 34 register-pinned locals | 469 | |
| lvalue form of 14 cast defines that are assigned (`#define D_X (*(T **)&D_X)`; 2 kept as casts under `#ifdef KH1_PS2` because the lvalue form changed the match) | 473 | |
| **now** | **473 / 512** (clang 18: 470) | |

**The 39 files left** all fail on inline MIPS asm: 118 VU0 macro-mode statements in 32 files (`lqc2`,
`vmul`, `qmtc2` ...: 29 of the files are src/ppp/, the particle / effect code, plus src/coll/ 3,
src/model/ 3, src/sound/sndctl.c, src/util/vecutil.nostrict.c, src/hand/vu0.c), 6 lq / sq copies in 2
files, 3 MMI (`pextlb` ...) in 3 and one FPU statement. Each needs a C equivalent in a `#else` (a C / NEON
version of the same VU0 sequence; the sceVu0 C routines of §1's vu.h row are the model), not a guard:
this is real port work, about 130 statements, most of them small (`vcopymatrix`, `VU0_RAND`, the
`H39_*` frame macros shared by the ppp files). src/gfx/opdma.c also stores two 96-bit literals into
u128s (gcc 2.96 cannot build one from halves, "unsupported wide integer operation"): it needs a
`#ifdef KH1_PS2` pair there.

**Link census** (`--link`, 503 objects: 473 game, 29 data, the null platform): 561 symbols undefined.

| count | kind | next step |
| --- | --- | --- |
| 308 | defined in one of the 39 files above | the asm work above |
| 94 | D_ data / bss that only the PS2 linker script defines (out/gen/symbols.ld: bss with no C definition) | generate host definitions with sizes (from the data tables), or define them in C |
| 39 | libc / libm the host supplies (memcpy, sprintf, sinf, atan2f ...) plus `__builtin_args_info` | src/util/task.nostrict.c reads the EE's saved argument registers (`__builtin_next_arg(fn) - 8 * (8 - __builtin_args_info(2))`): rewrite with va_list for the port |
| 36 | sceVu0* called directly (not through vu.h) | the C / NEON libvu0 of §1 (vu.h already has the names) |
| 22 | game func_ in no host object: the 9 unmatched (their drafts, SHIFT_DRAFTS) and ppp functions a macro defines in a failing file | |
| 20 | func_ in the SDK segment (libc / libgraph helpers the game calls by address) | name them and map to the host libc or the platform |
| 18 | defined in src/asm/ (the hand asm) | C rewrites (§2) |
| 13 | D_ below 0x100000 (kernel / scratchpad offsets) | look at each |
| 8 | D_ in the fixed memory map (§4) | src/host/memmap.c |
| 3 | sceIpu* (dkmovie.c), sceVpu0Reset | the movie decision (§3); a no-op |

Every Plat* resolves against the null platform (98 stubs generated from the headers' `#else` sides: a call
succeeds and answers "done" or "nothing there", PlatCdDiskReady 2, PlatSifSearchModuleByName -1, PlatFsDevctl
-1; PlatSpr is the 16 KiB scratchpad). host/ is outside src/, so the PS2 build never sees it.

**Next for the host build**: the opdma.c pair; the VU0 statements file by file (start with the macros
several ppp files share); generate the 94 bss definitions and the memory map; then a first `-m32` link
(`ld -m elf_i386` with a main() that calls the game's entry) and the run to the first PlatCdRead.

### 5.1a Session 61: every game file compiles; the link census at 109

All 512 game files now compile on the host with gcc 13 (clang 18: 507), and the link census is down from
561 undefined symbols to 109. The PS2 build stayed byte-identical at every commit: the original `__asm__`
stays under `#ifdef KH1_PS2` and the C equivalent goes in the `#else`.

**What made the 39 files compile:**

- **opdma.c**: the two 96-bit u128 literals are a `#ifdef KH1_PS2` pair (the `#else` builds the kh1_s128
  from its four words), the lq / sq copies are struct copies, and the R seed goes through PlatVu0RXor.
- **include/platform/vu.h** has an off-EE section of C helpers that mirror the VU0 macro-mode sequences the
  game repeats: PlatVu0Rand (the R register LFSR, five `vrxor -1` then `vrnext`, minus 1.0: `VU0_RAND`),
  Add4 / Sub4 / Scale4 / Scale3W / ScaleXYZ, Dot3, Cross3 and Normalize3 (w = 0), Dist3 / DistSq3, Length3,
  PlatVu0Sqrt (vsqrt takes |x|), Apply (d = m0 x + m1 y + m2 z + m3 w, alias-safe), Ftoi0 (truncates and
  saturates) / Ftoi4, SubFlags (the MAC flags after vsub, `cfc2 vi17`), ClipW (vclipw's six bits),
  ScreenFlags (the sticky 0x40 / 0x80 status test of x, y, w-1, 4096-x, 4096-y) and RotRows (microprogram
  P21, `vcallms 0`: rows of Rx*Ry*Rz, docs/renderer-spec.md).
- **The register-file model** (PlatVu0Regs PlatVu0 in host/port/vu0.c: vf[32], ACC, Q, MAC, status, clip;
  vf0 stays (0,0,0,1)) for the long sequences that are not worth hand translation: PlatVu0Fmac(op, d, mask,
  s, t, bc) covers vadd / vsub / vmul / vmadd / vmsub / vmax / vmini with every broadcast and ACC form, plus
  Opmula / Opmsub, Move, Ftoi / Itof, Div / SqrtQ, Lq / Sq, Qmtc2 / Qmfc2. Masks are x=8 y=4 z=2 w=1, the MAC
  flags Z in bits 0-3 and S in 4-7 (w lowest), as on the VU.
- **tools/host/vu2c.py** translates one asm statement to calls on that model (`python3 -I tools/host/vu2c.py
  FILE LINE [--reg '$6=p']`): the VU0 subset, the GPR subset the sequences mix in (lui / ori / dsll / addi /
  add / and / move / li / lb / lw), labels and branches as gotos (with the delay slot under `.set noreorder`;
  in reorder mode GAS puts a nop after a likely branch itself, so the next line is not a delay slot), "m"
  operands and cfc2 / ctc2 on vi16 / 17 / 18 / 22. kemdl and keshpdtt went through it unedited.
- **By hand**: all 33 leaf functions of src/hand/vu0.c, ryjshipoly's spline solver and evaluator, ryjmb's
  matrix chains, the keshptail / keshptailx macro sets (V3_* on a static register array), colobj / mapcoll
  (VSUB_MAC), mdlgs / mdldraw, eiwind, the ryjmb filters and about twenty files with one or two sequences.
- **PLAT_UNCACHED(p)** (include/platform/dma.h) replaces the 13 `| 0x20000000` uncached-mirror addresses in
  mdlgs, mdldraw and texspot: the EE's uncached alias on the PS2, the plain address elsewhere.

**Stale registers.** A few sequences read a VU register that the same asm block never writes, so on the PS2
they see whatever an earlier block left there. The C cannot know the leftover, so it picks a value and
says so in a comment: func_001a9080's stored $vf31 and func_001a9218's $vf31 z / w (src/hand/vu0.c), the
$vf15 w that ryjshipoly stores (0 in the C) and the $vf9 w in eiwind's v[3]. They matter only if a boot
shows a difference.

**Clang** fails 5 files on code gcc accepts: K&R prototype mismatches in gumisave.c and vecutil.nofill.c,
nested functions in keshptail / keshptailx, an `auto` storage class in kethdraw. Fine while the port builds
with gcc; the Vita toolchain is gcc too.

**Link census** (545 objects: 512 game, 29 data, 4 null platform / port), 109 undefined:

| count | kind | next step |
| --- | --- | --- |
| 39 | libc / libm / compiler, plus `__builtin_args_info` | the host libc; task.nostrict.c needs va_list (§5.1) |
| 20 | func_ in the SDK segment (func_0024f318 ... func_0026b9c0) | name each and map it to libc or the platform |
| 20 | defined in src/asm/ (func_001001d8, func_00121f6c ... func_0024ef88) | C rewrites (§2) |
| 13 | D_ below 0x100000 (D_00009B38 ... D_0000AC20) | kernel / scratchpad offsets: look at each |
| 8 | D_ in the fixed memory map (D_006A0000 ... D_12000000) | src/host/memmap.c (§4) |
| 7 | game func_ in no host object (the unmatched) | their drafts |
| 2 | sceIpuInit / sceIpuSync (dkmovie.c) | the movie decision (§3) |

What resolved since session 60:

- **host_defs()** in census.py generates out/host/defs_host.c, which removes the 94 symbols.ld-only names
  and more. Every undefined D_ between 0x100000 and 0x6A0000 becomes a byte array sized to the next known
  address (symbols.ld's PROVIDEs and data.tsv) and aligned to its address's low bits. That is 110 names;
  the 7 below .bss take their initial bytes from the user's ELF, read at build time and never committed.
- **host/port/libvu0.c** defines the 36 sceVu0 routines and sceVpu0Reset in C, checked against
  include/sce/libvu0.h. sceVu0InversMatrix is the rigid inverse (transpose plus -R^T t), as the library is.

**Next for the host build**: a first `-m32` link with a main() that calls the game's entry, against the
host libc. That needs src/host/memmap.c for the 8 fixed addresses, a decision for the 13 low D_, C for
the 20 src/asm functions (or stubs to start), the 20 SDK func_ named, and task.nostrict.c's
`__builtin_args_info` rewritten. Then run to the first PlatCdRead.

### 5.2 Session 60: overlays, dktitle.x

The overlay files are on the user's Mac (Downloads/kh1-test/ovl), not in the container, so the inventory
is ready but not run. `python3 -I tools/ovl/inventory.py dktitle.x [--tsv out/ovl/dktitle.layout.tsv]`
(stdlib only, uses tools/shift/scan_overlay.py's decoder and names) lists the overlay's functions (the
entry, jal targets inside the file, and what follows an unconditional jump and its delay slot when no
branch reaches past it), where code ends and data starts, each function's size, calls inside the overlay,
calls into the main ELF (game / SDK, named) and %hi/%lo data references, and the count of strings in the
data part (never their text). `--selftest` runs the function finder on three slices of the main ELF
against layout.tsv: every start found, 0-0.6% extra splits.

What is known already (shiftable-plan "Session 13: overlay fixups"): dktitle.x loads at 0x00F20000, entry
`int entry(int cmd, int arg)` at its first byte, called from func_00109770 / func_00109630 as entry(0, 0);
292 jal and 13 j into the main ELF, 99 %hi/%lo pairs, 13 mid-function references, 5 ambiguous; it writes
D_0046A6A8 and names 0x9A0000 / 0xBA0000 (the load area) itself.

**Plan to decompile it** (the user's file is the target, like SLPS_251.98 is now; never committed):
1. Run the inventory; write its `--tsv` as an overlay layout (functions named `ovl_dktitle_XXXXXXXX`).
2. Toolchain check as in session 1: m2c drafts of 5-8 small leaf functions, built with ee-gcc 2.96 `-O2
   -G0` and compared with objdiff against the overlay's bytes. If they match, the overlay uses the main
   ELF's compiler and flags; if not, try the flag modes of kh1.toml (nofill, nostrict ...).
3. A second build target in kh1tool (an overlay config: file, base 0xF20000, layout) that links the
   overlay's C at its addresses with the main ELF's symbols as externs (symbols.ld) and patches a copy of
   the file, verified byte-identical like the main ELF.
4. Its calls into the main ELF are then ordinary calls by name, so the port links it with the rest.

## 6. Open questions

- The sound driver's command set and the sequence format (needs the IRX from the disc).
- Which renderer B programs (P19 / P20) the scripts use (renderer-spec §6.4): needs a cutscene run.
- Whether any game code depends on the EE's 64-bit registers beyond u64 / s64 types (m2c wrote `s32` for
  some 64-bit moves; the matching build cannot tell).
- The licence of a software MPEG-2 decoder against the repo's licence.
