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
context switch, which becomes a Vita thread or a ucontext switch). Session 62: host/port/asm_c.c and
tasks.c have C for every one the link needs, the seven packet builders and func_001aa1f8 as stubs (5.1b). The 116 game files with `__asm__`
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

### 5.1b Session 62: the first link, and the run to the first PlatCdRead

`make host-census` now also links: `python3 -I tools/host/census.py --exe` builds **out/host/kh1-host**
(`gcc -m32 -no-pie`, the host libc and libm, 558 objects: 520 game files including the 8 drafts of
shift/drafts.tsv's unmatched game functions, 29 data, 9 null platform / port) with **no undefined symbol**,
and it runs the boot from the game's own main (func_00100558: `__main`, func_00109288, then func_00109770 for
ever) through the IOP reboot and the module loads to **the first PlatCdRead: func_00120ba0's read of one
sector at lsn 0 into D_004F2A00** (the file it searched for: the null platform answers every search "found
at sector 0"). The null platform stops there (exit 0); `KH1_HOST_CD=go` lets it carry on. A crash prints a
backtrace (host/null/main.c); census objects carry `-g` so gdb and addr2line name the game function.

What closed the 109 undefined of 5.1a:

| what | where | notes |
| --- | --- | --- |
| 8 fixed-map D_ | host/port/memmap.c | one 25 MiB block (0x6A0000-0x1FE0000, aligned 0x40000) with each D_ at its offset, so the regions keep their order and distances (heap.c compares with D_009A0000; objslot.c maps an address to its 0x40000 slot) |
| D_12000000 | memmap.c | GS PMODE, written by src/screen/fade.c's func_00113ab0: a plain u64 until gs.h takes the write |
| 13 D_ below 0x100000 | memmap.c | **offsets, not addresses**: src/gummi/gumisave.c adds &D_00009B38 ... &D_0000AC20 to the Gummi save block func_00232cc0(4) returns; absolute symbols (`.set D_00009B38, 0x9B38`) |
| 20 SDK func_ | host/port/sdk_host.c | named (docs/sdk.md "Session 62"): libc / libm wrappers, `__main` a no-op, sceGsSyncVCallback keeps the callback (kh1_vsync_cb), the data blob's table entries empty; plus newlib's rand / srand and `__assert` argument order |
| 20 src/asm | host/port/asm_c.c, tasks.c | C below; the VU0 packet builders and the GS upload are stubs that draw nothing |
| `__builtin_args_info` | src/util/task.nostrict.c | `__builtin_va_arg` under `#ifndef KH1_PS2` |
| 7 unmatched | shift/drafts.tsv | the drafts compile for the host (001636d0's one `sqc2 $vf0` got a C `#else`); three call sceDmaGetChan / sceDmaSend / sceGsSyncPath by address, which sdk_host.c routes to dma.h / gs.h |
| 2 sceIpu | sdk_host.c | no-ops until the movie decision (section 3) |
| functions.tsv aliases | out/host/aliases.ld | the data blob and the drafts say func_<addr> for a function C defines under its functions.tsv name: `PROVIDE(func_x = name)` in a linker script (an assembler `.set` to another object's symbol stays undefined) |

**The hand asm in C** (host/port/asm_c.c; read from the disassembly, functional, not matching):

- func_00121f6c (src, dst, n): lq / sq copy in 128-byte blocks, do-while n > 0 (a short tail still copies 128).
- func_00121fc4 (d, s): d.xyz = s.xyz / |s.xyz| and **d.w = |s.xyz|**; |s|^2 == 0 gives (0, 0, 1, 0) (vmr32 of vf0).
- func_00162c5c (d, a, b): row i of d = a applied to row i of b (all loads before the stores).
- **The two decoders of src/util/decode.c** (func_0024e75c method 1, func_0024e8d4 method 2), a byte-oriented LZ:
  header byte 0 the method and bytes 1-4 the size; then codes: 0 the end; 1-125 that many literals; 126 n c:
  n + 4 copies of c; 127 lo hi c: (hi << 8 | lo) copies of c; 0x80 and up a back reference of length
  ((code >> 3) & 15) + 3 and distance ((code & 7) << 8 | next) + 1 (method 2: (code >> 4) & 7 and code & 15).
  Within the first 2047 (method 2: 4095) bytes of output a reference before the start writes zeros.
  Returns the bytes read; *size the bytes written.
- func_0024edf0 (m, p[8]): 255 when D_002BBDE0 == 3 and all eight points m p[i] are outside one clip plane
  (vclipw: x > |w|, x < -|w|, y, and z < -|w|; the far plane, bit 0x10, is not counted), else 0: a bounding
  box cull.
- func_0024ef88 (func_00242b68(1) and (2), then func_00241c60 on the two objects at D_002E26A0 + 4 / + 8)
  and func_001001d8 (func_00106c10, then 0).
- Stubs: func_001aa1f8 (16x16 GS image uploads through the scratchpad), the six model packet builders of
  opdma.c's func_001aaf88 and keshptail's func_001b8198 (they return the packet end: the stubs return the
  current one, D_00616224, so nothing is drawn).

**The two task systems** (host/port/tasks.c, POSIX ucontext; the Vita needs its own switch, it has no
ucontext): every task gets a 256 KiB host stack (task.c's small slots have 0x9b0 bytes, sized for EE code)
and the game's context blocks keep only the fields its C reads.

- src/util/sa_task.c's (func_0024e0a4 clear, func_0024e0f0 (entry, arg, priority) create, func_0024e1d0 one
  pass): a context of 0x10320 bytes holds the entry's four argument words (+0), the priority (+32, 16
  lists), the entry (+48), a live word (+176: the EE's saved ra), first-run (+768) and frames-to-wait (+784);
  the pass lists the live ones by priority, counts every task it visits and runs those whose wait reaches 0
  until they wait again or end (the entry's end frees the context). The wait call is 0x0024e468 (func_0024e468
  (frames) in C): **nothing in the main ELF calls it** (no jal, j or %hi/%lo of it), so in the ELF every task
  runs to its end in its first pass; the overlays may wait.
- src/util/task.c's (func_001bfac8, the yield): the running task saves itself and the next queue entry
  runs, new ones from ctx->ra with ctx->a[0..7]; at the queue's end func_001c0460 rebuilds it and the main
  loop (slot 0) runs; a task that returns is ended by func_001bffa0, off its own stack (tasks.c runs that on a
  separate context: a new task may take the same slot).

**Register passthrough (portability.md rule 10).** The run's first crash was m2c's: func_001209d8 called
func_00120930() with no argument because on the EE its own a0 (the module name) was still in the register.
tools/host/argcheck.py lists the two kinds of this the source shows (calls with fewer arguments than the
callee's definition; void-defined functions whose callers use a value). Session 62 fixed 57 of the 119
short calls and 360 of the 644 value uses (49 functions now return their callee's value), every object
bit-identical: **62 calls (30 callees) and 284 value uses (111 functions) are left** (out/host/argcheck.tsv
after `--tsv`). Some are benign (func_00201440's last parameter is unused: callers pass 9 of 10), dkmovie.c's
func_00111238 passes garbage on the EE too (a keep-alive stub), and the rest want the same treatment: read
the caller's asm (`kh1tool.py asm`) for which registers reach the callee, add them as parameters, and for
a value use make the callee return what is in v0 / $f0 at its end (often a tail call: `return g(...)`; when
not, the last call's value or a stored one, case by case).

**The null platform's answers** changed where the game polls: PlatSifRebootIop / SyncIop / LoadModule /
LoadStartModule 1 (iop.h says so; the stubs answered 0 and the boot looped), PlatCdPowerOff 1,
PlatCdSearchFile "found" with lsn 0 / size 0 (the game retries a failed search for ever).

**Next for the host build**: the rest of argcheck's list; a disc behind PlatCdSearchFile / PlatCdRead
(KINGDOM.IDX / IMG from the user's ISO, tools/shift/extract_kingdom.py reads them) to run past the first read
to the title's logic; then a frame loop that answers vsync (kh1_vsync_cb) so the game's waits return.

### 5.1c Session 63: register passthrough closed, a disc behind the host, frames

**Register passthrough** (portability.md rule 10). argcheck's list is down to **0 short calls and 6
value uses** (from 62 and 284), every out/build object bit-identical:

- argcheck skipped calls whose callee is defined in the same file; m2c's `#define f ((T (*)()) f)`
  casts let those compile with missing arguments. It now checks them: **64 more**, in 40 callers,
  nearly all wrappers whose asm leaves the argument registers untouched (`func_00116130(a0, a1)`
  tail-jumps to `func_00115940` with a0 = its own a0). Each caller took the callee's parameters and
  passes them (a script did the first pass, tools/host/argcheck.py names them; the rest by hand). Casts
  that pass a float must be typed (`(f32)`), or the call promotes it to double.
- Its value-use pass no longer counts a statement after `case X:` / a label, a prototype, or `return
  f();` in a void function (284 -> 123), and reads `KH1_V0(type)` definitions.
- 117 value uses fixed or read as unread: the math helpers return their libm call (func_00124d28
  atan2f, func_00121840 acosf, func_001629b0 / func_00121b38 / func_0017c110 / func_001779e8 distances),
  dkmovie.c's overlay-entry wrappers return D_00F20000(cmd, 0), func_00120190 returns its bsearch,
  func_001812d0 the cull, func_0011e340 the sound status. The text drawers func_001fade0,
  func_001fb428, func_001f9e48 (and the draft of func_001f2630) match only as void but their callers
  read the end column they store (D_003F2BD0): `KH1_V0(s32)` + `KH1_V0_RETURN(D_003F2BD0)`.
  argcheck's BENIGN table lists 11 value uses whose value nobody reads: window callbacks (textwin.c
  calls them as void) and functions only ever called as statements.
- **Left (6)**: func_00130398 (class1a.c's func_00150bf8, an object-class callback in D_00350D88's
  table), func_001a1158 (pppRyjDrawKekotoFrame, a ppp program callback), func_001ff488 (winmenu.c's
  func_001ffaf0), func_00203a10 (winpart.c's func_002040a0), func_00206370 (func_002066b0 /
  func_00206710). Their callers have no caller in the main ELF or are called through tables whose
  call sites were not read; **the overlays call main-ELF functions by address** (dktitle.x: 292 jal),
  so check them against the overlay inventory (5.2) before calling them benign.

**A disc behind the host** (host/port/cd_image.c). `KH1_HOST_ISO=PATH out/host/kh1-host` reads the
user's own image by sector (.iso 2048 or raw .bin 2352, as tools/shift/extract_kingdom.py): the game
asks for ISO paths (`\SYSTEM.CNF;1`, `\KINGDOM.IDX;1`) and then reads absolute sectors (KINGDOM.IMG
is not in the ISO directory, its files are found through the index), so the image is read as it is,
not extracted. PlatCdRead copies before it returns (PlatCdSync / PlatCdGetError answer 0). Plain stdio,
no system headers: the Vita can share it. `KH1_HOST_TRACE=1` prints every search and read.

**Frames**: PlatGsSyncV and PlatWaitSema run the game's vblank handler (func_00110218, installed with
sceGsSyncVCallback) once and count a frame (`KH1_HOST_FRAMES=N`, default 600, ends the run with a
summary). There is no other thread, so a wait that would block lets a frame pass: the main loop's frame
wait is func_0010c348 (src/util/thread.c), a semaphore func_00110218 signals through func_0010c378.
PlatSifBindRpc marks the client bound (sceSifClientData +0x24) so src/sound/snd_rpc.c's setup stops
polling.

**A layout dependency found**: func_001a9f88 (src/gfx/opdma.c) links 288 GS tags from D_0061EEA0 on,
across D_0061EEA0 (16 heads, bss_0061.c), D_0061EFA0 (the pool of 256) and D_0061FFA0 (16 heads,
opdma.c): one array at 0x61EEA0 in the original. Off the EE the three are one array in
host/port/memmap.c (`#ifdef KH1_PS2` around the two C definitions). The shiftable build keeps them in
that order only because the link does; phase 4 should make them one definition.

**The run** on tests/host/fake_disc.py's image (no game data: SYSTEM.CNF, a one-entry KINGDOM.IDX):
the boot reads SYSTEM.CNF and KINGDOM.IDX, sets up the sound RPC, func_001094f0 starts the ppp and
opdma lists, and func_00109770's main loop runs its frames (state D_00495160 0, D_002BBDE0 1) with no
more reads. **Next, with the user's ISO** (the Mac session; ask once, never copy it into the repo): run
`KH1_HOST_ISO=... KH1_HOST_TRACE=1 out/host/kh1-host` and record where it stops. Expected: the first
overlay call, D_00F20000(0, 0) after dktitle.x is read into the overlay area, jumps into data on the
host (the overlays need a native build, 5.2), and the GS / VU stubs draw nothing.

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
