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
  written by the mixer. **docs/sound-spec.md** (session 85) lists every command (number, arguments,
  senders, meaning) and the status words the EE waits on.
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
  tools patch the rest. **Session 74 (5.1n): none left.** data_relocs.tsv has no tier-3 row since session 13
  (every word accepted, as a `.word sym` relocation in src/data/*.s, or rejected with a reason), and abscheck's
  data rows (a host data word with no relocation that is a .text address or a variable's start) are 0.
- **func_00171078**'s `((s32 *)0x35BD40)[i]` (portability.md "Known absolute addresses"): `D_0035BD40` on the
  Vita and the host since session 73 (`!defined(KH1_PS2)`, as the KH1_SHIFTABLE variant; 5.1m).

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
(Session 67: the game's threads run as coroutines now, host/null/threads.c, 5.1g.)
PlatSifBindRpc marks the client bound (sceSifClientData +0x24) so src/sound/snd_rpc.c's setup stops
polling.

**A layout dependency found**: func_001a9f88 (src/gfx/opdma.c) links 288 GS tags from D_0061EEA0 on,
across D_0061EEA0 (16 heads, bss_0061.c), D_0061EFA0 (the pool of 256) and D_0061FFA0 (16 heads,
opdma.c): one array at 0x61EEA0 in the original. Session 64 made them one definition (5.1d).

**The run** on tests/host/fake_disc.py's image (no game data: SYSTEM.CNF, a one-entry KINGDOM.IDX):
the boot reads SYSTEM.CNF and KINGDOM.IDX, sets up the sound RPC, func_001094f0 starts the ppp and
opdma lists, and func_00109770's main loop runs its frames (state D_00495160 0, D_002BBDE0 1) with no
more reads. **Next, with the user's ISO** (the Mac session; ask once, never copy it into the repo): run
`KH1_HOST_ISO=... KH1_HOST_TRACE=1 out/host/kh1-host` and record where it stops. Expected: the first
overlay call, D_00F20000(0, 0) after dktitle.x is read into the overlay area, jumps into data on the
host (the overlays need a native build, 5.2), and the GS / VU stubs draw nothing.

### 5.1d Session 64: the value uses read, opdma's one array, argument classes (rule 11)

Static only (the Mac was away). Every PS2 object stayed the same except the four of the opdma
change, and kh1.elf is byte-identical.

**The 6 value uses** (5.1c "Left"): 3 are benign and in argcheck's BENIGN table, which now takes an
optional third name (the caller) so one entry covers one wrapper: func_00150bf8 is class 0x1A's
handler at D_00350D88 +0xC, which only func_0013e558 (plctl.c) calls, as a statement;
pppRyjDrawKekotoFrame is a ppp frame callback, and pppsys.nostrict.c's dispatchers call those as
statements; func_002066b0's 39 main-ELF calls are all statements (recheck against the overlays).
**3 are left** for the overlay check: func_001ffaf0 (winmenu.c), func_002040a0 and func_00206710
(winpart.c) have no jal, no pointer in the ELF's data and no caller in src/. Reading those call
sites found a passthrough argcheck cannot see: func_0013e558 called the +0xC handler as `fn()` with
the actor still in a0 (the handlers take it); it passes `fn(arg0)` now. objse.c's func_001570d0
calls its +0x10 callback with no arguments and a0 is whatever func_001ecfd8 left: no handler can
rely on it, left as is.

**opdma's tag lists are one definition**: `GsTag D_0061EEA0[0x10 + 0x100 + 0x30]` in
src/gfx/opdma.c, with D_0061EFA0 / D_0061FFA0 as `#define` views (+0x10, +0x110 tags);
bss_0061.c's definition and host/port/memmap.c's copy are gone, and vu0_render_1.s /
vu0_render_2.s reach the pool as `D_0061EEA0+0x100` (`.reloc` with an addend: the REL addend goes
in the instruction field, the linked words are the same). The shift build: M0 OK (two fewer D_
names), and the m12 float ELF's loaded bytes are unchanged (fcheck: only the name D_0061FFA0 left
float_covered / float_reach).

**Argument and return classes** (portability.md rule 11, new tools/host/abicheck.py). An LTO link
of the host build (`-flto -Wlto-type-mismatch`) showed declarations that order f32 and integer
parameters differently from the definition, or pass s32 for u64: both work on the EE, where floats
have their own registers and a u64 fits one. abicheck compares every prototype and m2c cast in src/
with the definition, by class: 146 hits, all fixed (72 return types, 9 callers through 64-bit
definitions, 12 reorders, 13 host-order `#ifdef KH1_PS2` branches where gcc 2.96 orders the
arguments' evaluation differently, one extra argument). On x86 a float return nobody pops leaves the
x87 stack unbalanced; that was 50 of the hits.

**The fake-disc run under valgrind** (`valgrind --track-origins=yes out/host/kh1-host`, needs
libc6-dbg:i386): it found func_0010c378 reading the SemaParam PlatIReferSemaStatus did not write
(the null platform fills it now: no thread waits) and func_0011fb78 reading a u64 its callers
passed as s32 (the abicheck class above). After the fixes 60 frames run with **0 errors**.

### 5.1e Session 65: calls through pointers, libm, the null card, classes argcheck could not see

Static only (the Mac was away). Every out/build object is bit-identical to session 64's (sha1 of all 677),
kh1.elf byte-identical, so the float ELF's loaded bytes are unchanged (no row for float-untested.md).

**tools/host/indcheck.py** (new; needs clang): reads each game file's clang syntax tree (`-ast-dump=json`,
the census flags) instead of the text, so it sees what the regex tools cannot:

- **Indirect calls** (portability.md rule 10): every call whose callee is not a function name after casts,
  with the arguments it passes and what its callee expression reads. It resolves the targets from data
  tables (the `.word` entries of src/data/*.s pieces, C initializers, and the user's ELF for pieces that
  are `.incbin` bytes: an indexed array reads words from its start while they are functions or 0),
  assignments of a function to data or to a typed struct field (`Record.field`), and functions passed as
  arguments, followed through setters and parameters to a fixpoint (`@func#i`). Session 65: **242 rows:
  74 OK** (every known target takes no more than the call passes), **8 READ** by hand (its READ table
  says why), **47 OVERLAY** (only an overlay can set the pointer: no writer in src/, or a setter nothing
  in the main ELF calls; 41 are vm_lib.c's hooks D_0037733C ... D_003773E8, all 0 in the ELF), 7 `?def`
  (targets in assembly or the SDK: D_00351BC8 is PlatFlushCacheFn, D_00372750 the libvu0 matrix calls),
  **93 `?`** (targets not resolved: struct callbacks set through code the tool does not follow, e.g. ppp
  component tables, partyctl's cb44, mdlgs's GsTask list). The `?` rows that pass at least one argument
  are typed by matched code and lower risk; read them when a host run reaches them.
- **One real passthrough fixed**: func_0010ba98 (objwin.c, the window task) calls Win.cb at the close
  (state 5) with nothing; on the EE a0 = a1 = the window, and the close callback that func_0010bd90
  installs for a message window, msgwin.c's func_001cae20(id, win), frees the slot whose window is its
  second argument. The host passes `(w, w)` (`#ifdef KH1_PS2` keeps the EE's call, which a `move a0,a1`
  would change).
- **Calls clang refuses**: a builtin called with fewer arguments than its prototype. func_001b9bf8
  (gumisave.c) tail-jumps to asin with the caller's a0: it is `double f(double x) { return asin(x); }`
  now (same code). func_00121550 (vecutil.nofill.c) called nan() with a0 left over; the SDK's nan
  takes nothing, glibc's reads a tag string: the host passes `""` (`KH1_NAN_TAG`). The other CLANG rows are
  files clang cannot parse (gcc nested functions in keshptail(x).nostrict.c and kethdraw.nostrict.c, a
  draft's `$10` asm register): their indirect calls are not listed.
- **Classes** (rule 11): every declaration a file sees (headers, struct typedefs, `()` declarations,
  block-scope externs) and every m2c cast at a call, against the definition; and every f32 an
  unprototyped call promotes to double where the definition takes f32 (0 found). abicheck.py had 0 left
  but read definitions as text: `f32 (*pos)[4]` hid func_001655e0's, and casts it could not pair. Fixed
  (all PS2 objects the same): func_001655e0's f32 3rd (journalmdl.c, partymdl.c, objmotion.nostrict.c's cast;
  the calls reordered), func_00136428's cast in objdraw.nostrict.c (the f32 is the 5th: `(e, f, e->f394,
  &v, s)`), the f32 return of void definitions in m2c casts (func_001195d8, func_00113518, func_0011c868,
  func_0011c7a8: on x86 the caller would pop an empty x87 stack), the void cast of func_001779e8 (an f32
  nobody pops), and mdlgs.nostrict.c's u64 for func_0015fd20's s32 (an `#ifdef KH1_PS2` cast: the EE's
  `dsrl` needs the u64). Returns of i64 read as 32 bits are not counted (the low word on x86 and ARM).

**The null platform's answers**: PlatMcSync answered 0 (busy) forever, so a memory-card request never
ended; it answers 1 now with libmc's "no card detected" (-10) as the result (`cmd` is NULL in every
call), PlatMcGetInfo writes type / free / format 0, and src/memcard/mcstep.c's steps take the default
"no card" branch. PlatPadRead fails and leaves no button pressed (PlatPadGetState never answers 1, so
padread.nostrict.c does not read). The fake-disc run: 120 frames, valgrind 60 frames 0 errors.

**For the overlay session (5.2)**: the OVERLAY rows (the setters func_001c06c0 task.c, func_001468f8
objreq.c, func_0012cab8 cmdmenu.c, D_00304B6C, vm_lib's hooks) and gumisave.c's two calls of the gummi
overlay's entry with no arguments (func_001b9c10 / func_001b9c60: a0 is still FlushCache's 2 on the EE
if the kernel keeps it, a1 what was left): check what each overlay passes and reads.

### 5.1f Session 66: every indirect call resolved, one more passthrough, the null sound answer

Static only (the Mac was away until 2026-10-26). Every out/build object is bit-identical to session 65's
(sha1 of all 677), kh1.elf byte-identical.

**indcheck: 0 `?` left** (of 93). 242 rows: **107 OK, 41 READ, 70 OVERLAY, 3 DATA, 1 OPEN**, 7 `?def`, 13
CLANG. What it learned to follow (its docstring has the details):

- **Record tables filled by a setter** (RECORD_SETTERS), by the offset of the field the call reads: the
  actor class table D_00350D88 (59 records of 0x20, func_0014f830(class, f0 ... f1c) from every class's
  setup; the pieces D_00350D94 / D_00350DA0 / D_00350DA4 are fields of it) and the party's timed
  callbacks (D_00575528's 30 nodes, func_00170f50, the list heads D_00575780 / D_00575784).
- **Static record tables in the ELF** (RECORD_TABLES): ppp's class table D_00370200 (236 x 0x28), so
  pppsys's frame / draw / con / reset / des calls read each record's word at the field's offset.
- **Locals**: `fn = func_X; fn()`, a local table's initializer (hitreact's Tbl6), `t->f14 = fn` with fn
  assigned in a switch, and the field a local was loaded from (`fn = D_X[i].f10; fn()`).
- **Record layouts** (Layout): offsets computed from the tree with gcc's -m32 -malign-double rules (checked
  against gcc's offsetof on nested structs, unions, bit fields and arrays). A field whose name spells its
  offset (f408, x408, cb44) at 0x40 or more meets the same offset under other typedefs (`~@0x408`): two
  views of the actor (O15 / O16, Ob7.f4a0 / x4a0) now share their stores. FIELD_SAME lists the rest read by
  hand (the task pools' fn at +0xC is `@func_0011f090#2`; T15 / T16; T155ef8 / W9Task; W34E32 / Ent9c).
- **A lead for `?` rows**: the functions the ELF's code stores at the same field offset (lui / addiu /
  sw, any struct). It decides nothing; it found the motion entries' callbacks and the party AI's +0x48.
- `--takes NAME...` prints parameter counts (functions, data, fields, `@func#i`) for reading by hand.
- New verdicts: **DATA** (a pointer read from a file loaded at run time: pppsys.c's three PSys.mods calls,
  fn[4..6] of the effect file's module list, which no code found relocates: see them in a real-disc run)
  and **OPEN** (selector.c's Range52.fn: from fldtext's event record, not traced). A READ note never hides a
  SHORT.

The 23 new OVERLAY rows: mcstep.c's 13 calls of the request hook D_00648034 (every queue call in the main
ELF passes 0), partyctl's w->cb44 (4; only cleared), textwin.c's TextWin.x0 (2; its only setter
func_001f4670 has no caller), plact.c's D_002E27D4 and pppcomp.c's hook table D_00616220 (only cleared),
proc.c's func_0011f228 and vmath.c's handler stack (no caller in the main ELF).

**The passthrough it found**: func_0013e558 (plctl.c, called by func_0013f198 with `(o, &dir)`) called
the class's +0xC handler (D_00350D94[class]) with the object only, while 19 of the 24 handlers take
`(obj, dir)`: on the EE a1 still holds the direction. It takes and passes `arg1` now (the PS2 object is the
same: a1 is live from entry to the jalr).

**The null platform's answers**: PlatSifCallRpc answers RPC 0x30 with 1. The sound server's answer is word 0
of the buffer the request was written to (snd_rpc.c), so an unanswered call reads back its request: the
event command func_001e8b50 polls RPC 0x30 (func_001ed600) until what RPC 0x2F started is ready, and for
index 1 it would have waited forever. No caller in the main ELF reads any other RPC answer.
PlatPadGetButtonProfile answers -1 (no pad; padread skips the read). The memory card's counts: PlatMcSync's
-10 is GetDir's count too, so func_00235228 stores -1 and error 3 and never reads the table (Read the same).
The fake-disc run: 120 frames, valgrind 60 frames 0 errors.

### 5.1g Session 67: the last indirect rows, the sound transfer count, the loader thread

Static only (the Mac was away). Every PS2 object stayed the same (sha1 of every out/build .o before and
after), kh1.elf is byte-identical and the shift build M0 OK.

**indcheck's DATA and OPEN rows are read** (0 `?`, 0 DATA, 0 OPEN; 110 OK, 42 READ, 70 OVERLAY, 7 `?def`,
13 CLANG). PSys.mods (+0x78) is not effect-file data: func_00182c10 takes the words after the count at the
program's +0x8 offset (the program is file + 0x110, func_001803f0), the same words pppRelocProgram turns from
class ids into &D_00370200[id] (func_00180540 relocates every program when the effect loads). So the
three system steps call PppClass fn10 / fn14 / fn18 (pppsys.c now types mods as `PppClass **`; pppmatrix.c
and pppvertex.c's copies of the struct too). fn10 is 0 in all 236 classes (a READ note); fn14's three
(pppDrawMatrixWoodFn14 empty, the two RyjMegaBirth filters that store a normal) and fn18's one
(pppKeAcmSolidFn18, empty) take nothing: ppp.h's "returns a float" was the filters' 1.0f store. The OPEN
row: func_0010f558(range, win, start) stores the range at the window's +0xA8, the +0x28 of its text object
(objwin.c's Spr at +0x80), which func_0010cd40 hands func_0010f368 as a Range52; the ranges are msgwin.c's
D_0062A1E0, list.c's D_006305C0 and shop.c's D_0062F8F0 (19 calls, as many jal / j in the ELF), and FIELD_SAME
joins Range52.fn with their MsgCb / ListCb / ShopCb / Cb20.fn: 14 targets, 12 take the index, 2 take nothing.

**The sound transfer count** (host/null/plat_null.c). The status block's word +0x1F00 (D_0063F540,
func_001ecfd8) counts bank transfers not done: func_001ed658 / 001ed220 / 001ed460 (commands 3, 4, 0xB) add
one each and only the IOP's copy of the block counts down. The boot's func_0011cd20 waits for it to be
non-zero after sending the queue; objse.c's sound tasks, summon.c, objreq.c, the bank task func_0011cba0 and
the soft reset func_00109658 wait for 0. Unanswered it stayed 2 from the boot on, and func_00109770's state
0 never got past its load. The null IOP now keeps the block's address from RPC 0 and, a frame after a queue
(RPC 30), takes the transfers it held off the count (kh1_null_iop_frame from kh1_host_vblank). The other
status words read back 0 and every reader treats 0 as "nothing playing" (func_001ecb08 / 001ecd08: the
waits are for the end of a sound) or "no disc error" (+0x1C08, func_0011fec0).

**The loader thread** (host/null/threads.c, new). src/util/thread.c's worker func_0010c0c8 runs the
callbacks func_0010c170 registers once a frame: every func_001204a0 file load reads in func_001201d0 /
func_001202c0 on it. PlatStartThread did nothing, so a load's result stayed -1 for ever (checked: with
PlatStartThread refused, 600 frames and no dktitle.x read). The game's threads now run as coroutines on
ucontext with host stacks of 256 KiB: a thread runs from the main thread's PlatWaitSema until it waits
(the EE runs the worker, priority 40, only while main, 30, waits), a signal marks the waiter ready, and the
main thread's wait then lets a frame pass as before. Semaphores keep counts (initCount, maxCount);
PlatIReferSemaStatus reports the waiters, so func_0010c378 signals the main loop's frame semaphore only when
main waits, as on the EE. src/game/hdd.c's thread runs the same way.

**The run now reaches the overlay call.** tests/host/fake_disc.py's image has a one-sector "dktitle.x" in
KINGDOM.IDX: the boot reads SYSTEM.CNF and KINGDOM.IDX, the loader thread reads dktitle.x into
0xF20000 on frame 2, and func_00109630 calls D_00F20000(0, 0), which faults in the memory map. host/null/main.c
reports it ("fault at PS2 0x00f20000 in the memory map", and the caller from the return address on the
stack). Valgrind: 0 errors up to the fault. This is the stop 5.1c expected for the real disc; that run (the
Mac) should show the same three reads with the real sizes. Next for the host: the native dktitle.x build
(5.2).

### 5.1h Session 68: past the overlay entry (a test stub), the DMAC interrupts, the notice's sprite sets

Static only (the Mac was away). kh1.elf is byte-identical; one PS2 object changed (src/hud/notice.nostrict.c.o,
below), every other out/build object is bit-identical (sha1 before and after).

**indcheck: 0 `?def` left** (117 OK, 42 READ, 70 OVERLAY, 13 CLANG). The 7 rows' targets are assembly or SDK
functions, read by hand into ASM_TAKES (indcheck.py): FlushCache / iFlushCache (syscall 100 / 102, the mode in a0)
and the host's PlatFlushCache / PlatIFlushCache take 1, sceVu0RotMatrixZ / X / Y take 3 (out a0, in a1, the angle
in f12), SyncDCache 2. The flush hook D_00351BC8 is an 8-byte piece whose second word is SyncDCache; the five
`D_00351BC8(0)` calls read the first word only, so a piece called as one pointer (no index, no field) now reaches
its first `.word` entry only (the others are other data).

**KH1_HOST_OVL=stub[:N]** (host/null/main.c, a test switch, nothing in the game code). The jump into the overlay
area faults on its first instruction (the memory map is not executable), so the call's stack is intact: the fault
handler moves EIP to a host function with the entry's convention, which prints the call and returns 0. Every call in
src/ is to the entry D_00F20000 (135 references); a fault further in means the bytes ran, which is what valgrind
does (it does not keep data from running), so the stub does not work under valgrind. With `:N` the title's first
entry call (0, 0) also asks for game state N with func_00109558 (the request roomload.c and gameover.c use: next
state D_00495164, after a 2-frame countdown D_00495160). A guess at what dktitle.x does when the player picks; state
2 is func_00109770's case 2 (func_00109588: D_002BCDD8 = 0, func_00101660, func_001559f0(0, 0x40); then
func_001095b0).

- **`stub` alone**: the main loop stays in state 1 (the title's state; only the overlay moves it on) for 600
  frames with no more reads. Nothing else waits.
- **`stub:2`** reaches **the first room: Dive to the Heart**. After the call the boot loads (func_001204a0's names,
  in order) btltbl.bin, command2/uitex.bin, allset.set, kanji.knj, amusic/se000.dat, allarea.nam, menu/sysfont.bin
  and dktitle.x before the call, and dh.wdt, amusic/sedh.dat, dh00_01.bin, dh00_01.img, dh01.ard after it. So 2 is
  the new game (the game starts at Dive to the Heart). On the fake disc none of these files exist (func_001204a0
  answers a missing name with result 0, size 0, and the load's callback runs on the old bytes), so the run ends in
  func_00132790 (src/obj/roomobj.nostrict.c, the room file's header) reading an offset from data that is not
  there: that is the fake disc's end, not a host cause. **On the real disc** (the Mac session) this run is the next
  step: `KH1_HOST_ISO=... KH1_HOST_OVL=stub:2 KH1_HOST_TRACE=1 out/host/kh1-host`.

Two host-only causes found on the way:

- **The DMAC interrupts** (host/null/plat_null.c). The model renderer's GS task list (src/model/mdlgs*.c,
  func_0015eb78, a task each frame) runs with channels 1 and 2 masked until a task starts a transfer and asks to
  go on in the interrupt (bit 2 of its answer); it then enables both, and the handler func_0015efc0 runs the rest
  one transfer at a time and clears D_00559DB4 at the end. func_0015ef60 (from func_0011eda8, the frame's end)
  waits for D_00559DB4 == 0: with the null PlatEnableDmac doing nothing it waited for ever on the first frame
  after the new game's setup. The null platform now keeps the handlers (PlatAddDmacHandler), a status bit per
  channel (set when a transfer starts: PlatDmaSend on its channel, PlatDmaPutVif1Chcr with STR; cleared by
  PlatDmaPutStat, write 1 to clear) and the enable mask, and runs an enabled channel's handlers when its bit is
  set, after the call that set or enabled it and never inside a handler (a transfer a handler starts runs it again
  once it returns, as the next interrupt would). mdlgs.c is the only user.
- **The notice's sprite sets are one array** (a layout dependency like opdma's, 5.1c). func_00243a90
  (src/hud/notice.c) fills four sprite sets of nine words through func_0024afc0 at &D_00656230[0], [9], [18] and
  [27]; notice.nostrict.c defined the first words of the last three as their own variables (D_00656254,
  D_00656278, D_0065629C) and D_00656230 had no C definition. On the host, census.py sized D_00656230 to the next
  known name (0x24 bytes) and the fill wrote 0x90 bytes over D_006561D0 (the notice queue), which crashed
  func_00243278 on the next frame. notice.nostrict.c now defines `Gm *D_00656230_sets[4][9]` as D_00656230
  (16-aligned) with the four names as `#define` views. kh1.elf byte-identical; the shift build's data names lose
  D_00656254 / D_00656278 / D_0065629C and gain D_00656230 (one 0x90 definition). fcheck: the m12 float ELF's
  loaded bytes and program headers are the same, float_covered / float_reach swap the three names for D_00656230
  (the float build already kept the four sets together at 0x61D2B0), so there is no row for float-untested.md.

### 5.1i Session 69: every layout dependency found and made one definition

Static only (the Mac was away). kh1.elf is byte-identical; 26 PS2 objects changed (the files below), every
other out/build object is bit-identical. portability.md rule 12 is the rule.

**tools/host/layoutcheck.py** (new) finds what session 64's opdma and session 68's notice were found by a crash:
code that reaches past its variable's host definition. It groups the D_ names whose host addresses (nm of
out/host/kh1-host) keep their PS2 distances into host runs (one C definition, a data piece, a census block)
and hands them to tools/shift/reach_check.py as its pieces: every load, store, built address, bounded index
span, memset or argument read from a base in one run to an address outside it is a row. Left out as benign: an
end pointer one past the base's own definition, string arguments (libc and the disc file names), rows whose
functions are all in the SDK, and a REVIEWED table read by hand (10 rows: _gp, crt0's clear, three in the
unmatched drafts or constants, four pointers set by name, eiwind's empty object read only when its range is
above 0). `--all` adds the unbounded index (idx-next) and uncached-alias rows. At the start: **86 rows from 59
base names**; now **0**.

Two host-only causes, fixed in tools/host/census.py:
- Names with no C definition (out/host/defs_host.c) were separate arrays: campath's camera D_00575940 + 0x40
  is D_00575970 + 0x10, the gauge table D_00651E50 runs to +0x4130, D_0061E800's matrices. Now the names
  between two C definitions are one block (`kh1_hostblk_XXXXXXXX`) with each name `.set` at its PS2 distance
  (20 blocks, 50 names).
- A name inside a C definition (D_00575970 inside the camera, the fields left as `extern`) is now
  `PROVIDE(name = object + offset)` in out/host/aliases.ld (47 names).

The objects made one definition (kh1.elf byte-identical; the views and removed field definitions produce the
same code):

| object | was | now (file) |
| --- | --- | --- |
| D_00615E70 ppp object matrix | rows 1-3 D_00615E80 / 90 / A0 own variables, row 0 undefined | `V4F [4]` (pppsys.nostrict.c), rows as views |
| D_00616000 matrix | D_00616010[3] (rows 1-3; written as [-1]) | `PppQv [4]` (bss_0061.c), D_00616010 a view |
| D_0062F6E0, D_0062F790, D_00630300, D_00630460 window records (MsgWin, 0xb0) | only their text at +0x80 defined | `u8 [0xb0]` (bss_0062.c / bss_0063.c), the text a view |
| D_006298F0 message window templates | D_00629920 (template 0's v30) | `MsgWin [8]` (msgwin.c) |
| D_00629E70 open windows | D_0062A130 (entry 4) its own | `Ent176 [5]` (bss_0062.c) |
| D_00575940 path camera (0x70) | D_005759A4 / A6 own, camera undefined | campath.c |
| D_00494310 field cameras (2 x 0x80) | D_00494320 / D_004943A0 / D_004943E4 own | field.c |
| D_00525298 room object table (0x2c) | D_005252A8 (its recs) | bss_0052.c |
| D_00525368 sound channels (7 x 0x1c) | 4 bytes | bss_0052.c |
| D_0052EB50 pool header, D_00551700 trail (0x38), D_005758F0 / D_00575900 camera records, D_006627B0 action mark request, D_00643020 journal model, D_0054C120 effect model (0x90) | one field defined each | the whole record |
| D_00651E50 gauge table (0x4130) | D_00652888 / 98 / D_00654570 own | gauge.c |
| D_00641250[2], D_00575010[2] | [1] its own | arrays |
| D_00647FE8[14] memory card words | 13 words own, [0] undefined (func_00233ac8 clears 14) | bss_0064.c |
| D_006692C0 / F0 / 320 timer sprite sets (0x20) | tag D_006692D8 / 308 / 338 own (timer.nostrict.c) | timer.c |
| D_0062A428 effect instances (EvFx[8]) | 8 bytes, D_0062A430 own | bss_0062.c |
| D_004E39F8 sound requests | [4], flags D_004E3A18 / 1C after | `Pair [5]`: func_0011e1c8 writes [4] when all four are taken, over the flags, as the original does |
| D_0054F438 area groups | D_0054F440 ... 4C and D_0054F450[31] own | `Grp57 [0x20]`: the groups count from 1 (D_0054F438[k]) |

The shift build: shift_ld.py let a name no object defines inside a floated variable fail the link ("points
inside"); it now follows the variable (`name = variable + offset`). The float build's layout changes (row in
docs/float-untested.md). The host run on tests/host/fake_disc.py stops where session 68's did (the overlay
entry, and with `KH1_HOST_OVL=stub:2` func_00132790 on the fake disc's missing room file); valgrind 0 errors
to the fault. abicheck 0, argcheck unchanged.

**indcheck: 0 CLANG rows** (241 rows: 117 OK, 42 READ, 70 OVERLAY, 12 CLANG-READ). The 12 rows of keshptail.nostrict.c,
keshptailx.nostrict.c and kethdraw.nostrict.c are gcc nested functions clang cannot parse; indcheck now reads such a
file's host object (gcc compiles it): none of the three has a `call *` (47, 48 and 131 direct calls), so there is no
call through a pointer to miss (CLANG-READ; abicheck reads their declarations as text). The 13th, the func_001c62a0
draft's `register f32 *d asm("$10")` (an EE register name), is now under `#ifdef KH1_PS2` (the host a plain local),
and clang parses the draft: no new row.

### 5.1j Session 70: names that land on the next variable (relcheck), the unbounded index rows

Static only (the Mac was away). kh1.elf is byte-identical; 7 PS2 objects changed (bss_0054 / 55 / 57 / 63 / 64 / 65
and objslot.c), every other out/build object is bit-identical.

**layoutcheck's 733 `--all` rows** (726 idx-next, 7 uncached) were sorted by what follows the base (`gdb` gave each
name's host type: 556 rows have nothing that hints at a split; the rest are a scalar or one-element base, a next name
of the base's element size, or two arrays of one type). Read by hand: the command menu's sprite arrays (cmdmenu
.nostrict.c, 61 rows) are bounded by the counts func_0023aed0 is passed; the journal / synth / load-menu tables
are indexed within their sizes. An idx-next row is any index the analysis cannot bound, so the list does not
shrink by reading; the useful finding was why the real splits were not rows at all.

**tools/host/relcheck.py** (new): layoutcheck reads the linked PS2 ELF, where `&D_00650120[6]` (cmdmenu.c) is just
0x00650C00, D_00650C00's own address, so it reads as an access to D_00650C00. relcheck reads the host objects'
relocations instead (i386 REL, the addend in the instruction), where the C name stays, and lists every `name +
offset` that falls outside the host run holding the name (layoutcheck's runs: one definition, a data piece, a
census block). At the start: **103 rows** (`--all`: 144 with the references exactly at an end). Most were the
compiler's: a loop's end pointer to a field (`&a[N].f`, compared, never read: 18 objects), an index folded into
the displacement (`a[i - 1]`, wave.c's `(i + 2098) << 4`: 17), and func_0010d470's draft; they are its REVIEWED
table. The `--all` end rows were read too: loop ends and C's `&a[N]`, except the ones below. Now **0 rows**.

Made one definition (portability rule 12):

| object | was | now |
| --- | --- | --- |
| D_00650120 command menus (Ob17, 0x1d0) | [6], D_00650C00 its own; cmdmenu.c draws the second kind-4 menu as D_00650120[6] | [7] (bss_0065.c), D_00650C00 a view |
| D_00550400 object slots (0x48) | [0x34], D_005512A0[12] (objslot.c) its own; func_001557d0 clears 64 | [0x40] (bss_0055.c), D_005512A0 = [52] |
| D_00573AC0 DMA packet area | 0x10 (the call tag), D_00573AD0 a census block; func_0015fa20 builds its packets to +0x104 | u8 [0x380] (bss_0057.c) |
| D_0054C440 hit records (64 x 0xc0, no C definition) + areabox's groups D_0054F438 | a census block of 0x2ff8 and Grp57 [0x20]: record 63's last 8 bytes are group 0's first 8 (groups count from 1) | u8 [0x32f8] (bss_0054.c), both views |
| D_006305C0 list's choice callback (ListCb a, n, fn, d) | a 0xc block, D_006305CC (d, the page) its own s32 | u8 [0x10] (bss_0063.c) |
| D_00642C74 ability counts | a 4-byte block, D_00642C78[4] its own; abilities.nosi.c counts into (&D_00642C74[1])[slot] | D_00642C70 s32 [6] (bss_0064.c): a separate s32 [5] at 0x00642C74 is padded to 8 by ee-gcc and fails the link |

The float build floats 2,041 names (2 newly pinned: D_00642C70, D_00650DD0; float-untested.md row 70). layoutcheck
0, relcheck 0, abicheck 0, indcheck unchanged (241 rows), argcheck unchanged (3 value uses). The fake-disc host run
stops where session 69's did (the overlay entry; with `KH1_HOST_OVL=stub:2`, func_00132790 on the missing room file,
reached from func_001136a8 through the sound and file queue); valgrind 0 errors to the fault.

### 5.1k Session 71: relcheck reads the PS2 objects and the unlinked drafts; the uncached buffers

Static only (the Mac was away). kh1.elf is byte-identical; one PS2 object changed (bss_0057.c), every other
out/build object is bit-identical, and the default float ELF (`make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, no
overlays) loads the same bytes as before (fcheck: float_covered, float_reach, loadhash, phdr all the same), so
there is no float-untested.md row.

**relcheck, two more sources** (`--no-ps2`, `--no-drafts` to skip them; a row now names its source):
- **The PS2 objects** (out/build, 541 game objects; src/sdk and src/asm left out): a MIPS HI16 and the LO16s after
  it give `name + k`, an R_MIPS_32 word its addend. **0 rows, and nothing the host did not already show.** ee-gcc
  2.96 -O2 keeps an offset out of the relocation: it builds `lui/addiu %hi/%lo(name)` and puts the offset in the
  load's displacement (counter.c's loop end, list.c's `a[i - 1]`, wave.c's strip loop all have addend 0 on the PS2;
  3,244 of 22,124 D_ references carry an addend, all inside their definitions). So the host's -O1 folds are the
  ones to look at, and the PS2's displacements are what layoutcheck (reach_check on the linked ELF) reads.
- **The unlinked drafts** (nonmatchings/, the 169 C drafts that shift/drafts.tsv does not link, SDK drafts left
  out): compiled with census.py's flags into out/host/relcheck-drafts (retried with `-include common.h`, for drafts
  pasted without it). 140 compile; the 29 that do not use TImode (`unable to emulate 'TI'`, 11) or include
  scratch headers that are gone. 6 rows, all func_0010d470 drafts' width table end (D_00495280 + 0x42160, as the
  linked draft), now REVIEWED_DRAFTS by function, linked or not.

**layoutcheck `--all`'s 7 uncached rows** (a name whose uncached alias is built: a DMA buffer with no declared size):
- D_00272D94 / D_00272DA4 / D_00272DE4 (func_0015f798's GIF packet words in data_0027.s), D_00351C40
  (func_0015ff78's 0x1d0 packet, data_0035.s) and D_0035C550 (func_00175600, data_0035.s): each sits inside a
  data piece whose host distances are the PS2's, so the packet and the names after it stay together. No change.
- **D_00573AC0** (the packet area, 0x380 since session 70) and **D_00573E40** (Pk2: a call tag to D_00573AC0, an
  end tag, a GIF tag and 18 A+D words; no C definition, a census block): mdlgs.nostrict.c's view D_00573AD0 is
  7 Pk1 of 0x80 from +0x10, so the 7th runs 0x10 into D_00573E40 (its "pad" is packet 6's ref tag and the next
  tag). Every packet is 0x80 (Pk59: a DMA tag, a GIF tag, 4 A+D, the image GIF tag, a ref tag). The chains:
  func_0015fa20 2 packets + end (+0x110); func_00162428 func_0015f8c8's `s->n & 7` packets + end (up to +0x390,
  over D_00573E40's call tag); func_0015ff78 (case 2) func_0015f488's 2 + func_0015f8c8's + ret, sent from
  D_00573E40, so on the PS2 it must stay below +0x380 (Src59 has 4 texture slots: up to +0x310). D_00573E40's
  writers (func_0015f128, func_0015f388, func_0015f488) stay inside its 0xc0. **One definition**:
  `u8 D_00573AC0[0x450]` (bss_0057.c), D_00573AD0 and D_00573E40 views. The last 0x10 (0x00573F00, after Pk2) is
  where motion.nostrict.c's `D_00573F10[n2C - 1][3]` and func_001636d0's `D_00573F10[s1 - 1][3]` fold to (bone
  numbers counted from 1); with D_00573E40 out of the census block before D_00573F10 they became rows (relcheck 2,
  layoutcheck 1) and are REVIEWED.

layoutcheck 0, relcheck 0 (`--all`: the same 38 end rows), abicheck 0, indcheck unchanged (241), argcheck
unchanged (3 value uses). The fake-disc host run stops where session 70's did (the overlay entry; with
`KH1_HOST_OVL=stub:2`, func_00132790 from func_001136a8).

### 5.1l Session 72: the DMA chains and the hand-built DMA addresses

Static only (the Mac was away). kh1.elf is byte-identical and **every out/build object is bit-identical** (the
changes are macros that expand to the PS2's own tokens); the default float ELF loads the same bytes (fcheck: all
same), so there is no float-untested.md row.

**The 181 PlatDmaSend calls** (35 files; `python3 -I tools/host/dmacheck.py --list [--tsv out/host/dmacheck.tsv]`
sorts them by where the chain comes from):

| source | calls | what was checked |
| --- | --- | --- |
| static data (a data piece) | 72 | every name sits in a host run with the PS2's distances (data_0027 / 002B / 0035 / 0037 / 003F), so a chain and the names after it stay together; reach_check already walks the read-only ones (dma-chain / dma-ref) |
| static bss | 13 | D_00573AC0 / D_00573E40 (session 71); the eight 0xb0 image uploads (D_00641080 / 1130, D_00642D30 / DE0, D_00642EB0 / F60, D_00643290 / 3340) are func_0011fbb0's chain, exactly 11 qwords (cnt 6, ref to the image, end 2); D_00631620 (wave.c) is cnt 0x194 + end = 0x1960 bytes of its 0x2020 |
| scratchpad frame | 75 | heap.c's func_00122048 frames (text windows, menus, journal, HUD) and opdma.c's stacks (ppp): see below |
| pointer | 21 | queue entries' +0x10 (texanim / shadow / dmapool's func_0015ed80 callbacks), caller buffers (text.c's `u128 a[11]` on the stack, 11 qwords for func_0011fbb0), drawlist's double buffers, opdma's priority lists D_0061EEA0 (one definition since session 68) |

func_0011fbb0's ref tag reads the image (a7 qwords from a8): the static sources D_003E9660 (0x800 qwords) and
D_003F1660 (0x40) are exactly their definitions; the others are file buffers (pointer variables).

**Found: DMA addresses built with the PS2's masks.** libdma's sceDmaSend turns a 0x7xxxxxxx address into the
scratchpad form itself (func_00266ba8: `(a & 0x0fffffff) | 0x80000000` when a >> 28 == 7), but tags inside a chain
need it written, so the game writes it by hand: 63 places `(p & 0x0fffffff) | 0x80000000` on a scratchpad frame
(winpart 22, wintext 13, textwin 5, text 4, menubg 4, the journal 4, winmenu 4, gauge 2, config, pointer, winlist,
util, ryjkekoto), func_00106b58's `x | 0x80000000`, func_0011fb78's SPR bit in a cnt / end tag when the end is above
0x6fffffff (on a 32-bit host the stack is), and three VIF1 TADR writes `p & 0x0fffffff` (sceneeff.c, dmapool.c,
mdlpkt.c). On the host the masks cut a pointer (the null platform ignores the tag, so nothing showed); the Vita
renderer would walk the wrong address. They are now PLAT_DMA_SPR_ADDR(p), `| PLAT_DMA_SPR`, `(u64)PLAT_DMA_SPR <<
32` and PLAT_DMA_ADDR(p) (platform/dma.h: the PS2's expression on KH1_PS2, the plain pointer elsewhere).
**opdma.c's two scratchpad stacks** (func_001aa918: D_00372EA8 up from 0x70000000, D_00372F30 down from 0x70004000;
func_001aa950 / func_001aa990 push them for the ppp effects' packets: kemat, kemdl, keshptail(x), kelnscls,
keshpdtt, kemdltfd, ryjkekoto) started at literal PS2 addresses: on the host the first ppp draw would have written
to 0x70000000. Now PLAT_SPR_BASE / PLAT_SPR_END. portability.md rule 13; tools/host/dmacheck.py lists any new one
(0 rows; its REVIEWED table holds the end tags and frame counts that look like 0x70000000).

**relcheck's 29 drafts that do not compile**: the 11 TImode ones (`typedef int u128 __attribute__((mode(TI)))`)
do not take census.py's kh1_s128 either (they assign integers to u128, or use EE register asm); all 11 are older
drafts of functions matched since (kelnscls func_00192958, kethcls pppKeThFrame, keshptail(x), ryjkekoto,
drawlist's 7d48), whose matched C is in the host census and checked. The other 18 use EE register names or
scratch headers that are gone. No change.

layoutcheck 0, relcheck 0, abicheck 0, indcheck unchanged (241), argcheck unchanged (3 value uses), dmacheck 0.
The fake-disc host run stops where session 71's did (the overlay entry; with `KH1_HOST_OVL=stub:2`,
func_00132790 from func_00132c70). Valgrind was not run (not installed in this container).

### 5.1m Session 73: the pointer DMA sends and the PS2 addresses as numbers

Static only (the Mac was away). kh1.elf is byte-identical and **every out/build object is bit-identical**; the
default float ELF loads the same bytes (fcheck: all same), so there is no float-untested.md row.

**Found: func_00171078 read PS2 address 0x35BD40 on the host** (src/ai/partyai.c, the party AI's table lookup).
The matched form is `((s32 *)0x35BD40)[*b ^ 3]` (portability.md "Known absolute addresses"); only the shiftable
build used the name, so the host object read `mov 0x35bd40(,%eax,4)`: the first party AI step would have crashed.
Now `#if defined(KH1_SHIFTABLE) || !defined(KH1_PS2)` (portability.md rule 14). The host reads D_0035BD40.

**tools/host/abscheck.py** (new; after `make host-census`): `objdump -dr` of the 550 game objects under out/host
(src, the drafts, data; not the null platform or the port). On the host a name is a relocation and a number is
not, so any memory operand with no relocation whose displacement is a PS2 address (main memory 0x00100000 up,
also through the 0x2 / 0x3 mirrors; the hardware registers 0x1000xxxx-0x1200xxxx; the scratchpad) is a row, and
so is an immediate (mov / push / lea / cmp) that is exactly the address of a PS2 symbol (out/shift's linked ELF;
0x100000 left out: _ftext is also the windows' GS word). **0 rows** after the fix; REVIEWED holds 4 patterns:
objwin's end tag `cnt * 13 + 0x70000001` built with lea, and func_001bfe50's task heap offsets (0x16BC00,
0x170700, 0x171388 from its base). Other immediates in those ranges are tags, GS words, masks (`& 0x7fffff`) and
colours. The source-side search (`0x1000xxxx` / `0x1100xxxx` / `0x1200xxxx` outside src/sdk and include/platform)
finds only DMA tags (sceneeff, drawlist, wave) and pad masks (padrec, selector): no register access outside the
wrappers.

**The 21 pointer sends** (dmacheck `--list`, "pointer"), each followed to its builder:

| send | chain | checked |
| --- | --- | --- |
| dmapool func_00106b18 (arg0) | static packets (fldtext, selector, framectl, objwin) and objwin's func_00121e28 buffer | objwin kind 1: `((w + 2) * (h + 2) * 13 + 2) * 16` bytes, func_0010a780 mode 1 writes the tag, the GIF tag and cnt * 13 qwords: exact |
| dmapool func_00106b98 (+0x10) | func_00106bd8's argument: field.c's D_0029B170 / 1C0 / 200 / 260, texanim's D_002A4310 / 43A0 / 44E0 / 4570 | static data |
| texanim func_001019c8 (+0x10) | func_00101970's 32-byte header: a ref to D_002A4160 / D_002A4180 (2 qwords) then a refe of 4 / 8 qwords at the +0x14 buffer (64 / 128 bytes) | exact |
| texanim func_00101f30 / func_00101f80 | a 16-byte refe of 4 qwords to the 64-byte func_00101fc8 / func_00102070 packet (8 u64); a 48-byte copy of D_002A4230 / 4260 / 4400 / 4430 with word 9 pointing at the frame's image (D_0029BE20) | exact; the image address is a name |
| shadow func_001274c8 | D_004F8270, D_004F7820[k], D_004F7C10[k] | bss |
| shadow func_00127500 | func_00127568's `n * 224 + 16` buffer: 48 bytes a vertex, 32 a batch header, 16 a batch end | a lone front-facing quad needs 256 bytes of 240; func_00121e28 rounds to 128, so 256: fits (on both builds) |
| drawlist func_00237f20 / func_002380c0 | the caller's two buffers, packets from func_002378c8 / 7790 / 7d48 / 7ec0 | the end tag is `*r \|= 0x70000000` on the qword after the last packet (its qwc bits are whatever was there, sent as data on the PS2 too); both set TTE (`*chan \|= 0x40`, word 0 of the channel is CHCR) |
| gspkt func_00237018 | the caller's packet, an end tag of n - 1 | `(u32)p < PLAT_SPR_BASE` picks the SPR bit: the host's PlatSpr, PLAT_DMA_SPR 0 |
| opdma func_001aa008 / 1aa650 / 1aaf30 | D_0061EEA0's priority lists (one definition since session 68) | as 5.1l |
| mdlgs func_0015ff78 | the model file's mesh chain (`table[byte7].x18`), relocated at load by adding the base | fits a 32-bit pointer (host, Vita) |
| objdraw func_00135ed0 (two) | `C02Q buf[128]` on the stack | about 40 and 20 qwords |
| keth func_001a8c40 | `*buf` (D_00616224's cursor), an end tag of the node's packet | the packet's extent is func_001a7718's |
| frame func_001e05a8 | D_003DAE30, D_003DAF60, D_003DB050 | static data |
| text func_001ef950 (three) | `u128 a[11]` / b on the stack: func_0011fbb0's 11 qwords | as 5.1l |

**For the renderer**: word 0 of a PlatDmaChan is the game's CHCR. drawlist sets TTE on the GIF channel and
nothing clears it (libdma's sceDmaSend keeps the struct's bits), shadow's func_00127500 sets chain mode and
clears TTE on VIF1 (renderer-spec §2.1 has the VIF1 cases); the Vita chain walker reads TTE from there.

layoutcheck 0, relcheck 0, abicheck 0, dmacheck 0, abscheck 0, indcheck unchanged (241), argcheck unchanged (3
value uses). The fake-disc host run stops where session 72's did (the overlay entry; with `KH1_HOST_OVL=stub:2`,
func_00132790 from func_00132c70). **Valgrind: 0 errors** up to the overlay entry (the SIGILL).

### 5.1n Session 74: the PS2 addresses as numbers in data, the chain walk

Static only (the Mac was away). Only tools/ and host/ changed: kh1.elf is byte-identical, every out/build object is
bit-identical, and the float ELF the same (fcheck), so there is no float-untested.md row.

**abscheck reads the host data too** (`data` rows; portability.md rule 14). On the host a pointer word in data
is a relocation (`R_386_32`, from a `.word sym` in a piece or a C initializer); the pieces' other words are the
user's original bytes. A row is a 4-byte word of a game object's `.data*` / `.rodata*` (not the string sections)
with no relocation that is a 4-aligned address in the PS2 .text (0x100000-0x272c70) or exactly the start of a
PS2 variable. Words data_relocs.tsv rejected with a reason, and words inside the embedded resource files
(0x308CE0-0x350CE0, `resfile`), are decided, not rows (`--all` prints them). **0 rows**; 1,108 words decided:
resfile 553 (offsets and numbers in the model / motion files), into-func 527 (u16 / s16 pairs such as
D_00351530's 512 flags and the RGBA table D_003E8E30), override-x 13, payload 9, script 4, spawn-tmpl 1, kcode
1. One new REVIEWED_DATA entry: **D_0048CC10**'s 8 words are func_00100670's PS2 jump table (`lui/lw
jtbl_0048CC10; jr`), a compiled rodata block census.py copies into defs_host.c because D_0048CAD4 names it;
the host's switch has its own table, so nothing on the host jumps through it. C data objects: 0 rows (their
initializers are relocations). Left out by design: data words in the hardware, scratchpad and memory-map ranges
(about 3,900 VIF codes, DMA end tags 0x7000xxxx, GS values such as texanim's 0x017F0000): too many s16 pairs
fall in those ranges for a word test, and code that reads such an address is abscheck's `mem` row.

**The chain walk** (renderer-spec 4.4): under `KH1_HOST_TRACE=2` the null platform's PlatDmaSend and
PlatDmaPutVif1Chcr (STR with MOD 1, from the TADR PlatDmaPutVif1Tadr kept) walk the chain the way the DMAC's
source chain mode does and print one line per send (channel, CHCR word 0, tags, qwords, the last id); a tag or
data outside the executable's data / bss, the scratchpad and the stack, a bad id, a call past two deep or 4,096
tags with no end prints each tag. `KH1_HOST_TRACE=3` prints every tag. On the fake disc with
`KH1_HOST_OVL=stub:2`: 86 sends, all GIF (channel 2), 1-3 tags each, none outside; the run ends where it did
(func_00132790 from func_00132c70). Valgrind with TRACE=2: 0 errors up to the overlay entry (23 sends there).
sceDmaSend (func_00266f38) keeps CHCR's other bits and sets `| 0x105` (chain, from memory, start), so TTE is
whatever the last writer of word 0 left: drawlist leaves it set on the GIF channel (renderer-spec 4.4).

layoutcheck 0, relcheck 0, abicheck 0, dmacheck 0, abscheck 0, indcheck unchanged, argcheck unchanged (3 value
uses, waiting for dktitle.x).

### 5.1o Session 75: what the GIF tags' upper words hold, the receiver's read of each chain

Static only (the Mac was away). Only host/ and tests/ changed: kh1.elf is byte-identical, every out/build object is
bit-identical, and the float ELF the same (no PS2 source changed), so there is no float-untested.md row.

**The upper 64 bits of the GIF tags** (renderer-spec 4.4's open question, now 4.5): the tag builders clear the
qword first (`*p = KH1_Q(0)`, then the low word: func_00237018, drawlist's func_00237ec0 / 7790 / 78c8 / 7d48), so
their upper words are 0; the static chains the fake disc sends hold 0 there too. The one exception is
func_0011fbb0's image uploads on the caller's stack (text.c's `u128 a[11]`): the cnt / ref / end tags are written
as 64-bit words and the upper half is **whatever the stack held** (seen: `09bc0000 080967a2`, `ffd53ce0
f7be6915`). Nothing in the main ELF calls drawlist's flushes (func_00237f20 / func_002380c0 / func_00238258: 0
jal, 0 pointer words; nor the push by depth func_002376c8; hud.c's func_00236f18 only gives D_00425F80 its
buckets), so **the main ELF never sets TTE on the GIF channel**: every GIF send seen has CHCR 0 or 4. If an
overlay calls them (item 3's dktitle.x check), the tag qword can not be reaching the GIF: read as a GIFtag,
drawlist's `0x1000000N` is NLOOP N, NREG 16, PACKED with PRIM registers, swallowing 16 x N qwords of a packet
that already starts with its own EOP GIFtag. So the GIF parser drops every tag on channel 2, whatever TTE says
(an inference: confirm with a PCSX2 GS dump if an overlay turns out to run drawlist).

**The receiver's read** (host/null/dmawalk.c, split out of plat_null.c; renderer-spec 4.5): after the walk,
`KH1_HOST_TRACE=2` reads each send's data in chain order as its receiver would: the GIF channel as one stream
of GIF packets (PACKED NLOOP x NREG qwords, REGLIST half that, IMAGE NLOOP), VIF0 / VIF1 as one stream of VIF
codes and their data (each tag's upper words first with TTE; STCYCL's CL / WL for UNPACK sizes, DIRECT and MPG
data aligned, VIF0 without OFFSET / BASE / MSKPATH3 / DIRECT). A chain that ends inside a GIF packet or a VIF
code's data, or a word that is no VIF code, is a problem and prints the tags; `=3` also prints each tag's upper
words. tests/host/dmawalk_test.c (in `make test` when gcc -m32 works) checks 14 made-up chains. Fake disc,
stub:2: **86 sends, every one whole**: 84 GIF (1-4 packets, one EOP each; the 3 image chains have their REF
data inside the IMAGE packet, as expected), and (a correction to 5.1n's "all GIF") **one VIF0 and one VIF1
send**, both from func_0015f018 (mdlgs: TTE set on both, static D_00278680 75 qwords and D_00272C70 7 qwords; the
tag's upper words are `FLUSHE` / `FLUSHA` then `STCYCL 4,4`, then one UNPACK each). Valgrind with TRACE=2: 0
errors up to the overlay entry (23 sends).

layoutcheck 0, relcheck 0, abicheck 0, dmacheck 0, abscheck 0, indcheck unchanged, argcheck unchanged (3 value
uses, waiting for dktitle.x).

### 5.1p Session 76: every static chain walked offline, the GS register census, PATH2

Static only (the Mac was away until 2026-10-26). Only tools/, host/ and tests/ changed: kh1.elf is byte-identical,
every out/build object bit-identical (sha1 of all 677 before and after), and the float ELF the same (no PS2 source
changed), so there is no float-untested.md row.

**tools/host/dmawalk.py** (new; after `make`, reads the user's ELF and out/gen/data.tsv): the Python twin of
host/null/dmawalk.c for the sends whose chain is a name: dmacheck `--list`'s "static data" / "static bss" rows (a
table indexed at run time, `D_00351BE0[v]`, walks each distinct entry) and every call of dmapool's GIF wrappers
func_00106b18 / func_00106bd8 handed a name (the static GS packets gs_packets.py `--callers` decodes). The channel
comes from the source (`PlatDmaGetChan(n)`, or the variable it was stored in: D_002A6B84, D_00372908, D_0055C640 /
644, a local `c`), TTE from `c->tte = 1` before the send. **155 sends: 81 walk whole, 0 rows; 61 are zero in the
ELF and 13 in bss** (built at run time: the host run reads them). `--float ELF` walks each chain again in the m12
float build from where its name floated: same tags at the same name + offset, the same ADDR targets by name, the same
data bytes: **all 81 the same** (every start moved; 264 ADDR words point at moved objects). renderer-spec 4.6 has
the list and the census.

**The receiver's read now follows VIF1 DIRECT into the GIF** (PATH2, host/null/dmawalk.c and the Python twin): a
DIRECT's data is one stream of GIF packets across the chain; a send that ends inside one is `KH1_DMA_PATH2_SHORT`
(0x80). No static chain and no fake-disc send has a DIRECT. tests/host/dmawalk_test.c has two more cases (16).

**The GS register census**: `dmawalk.py --regs [-v]` offline, and `KH1_HOST_TRACE=2` now ends each GIF / PATH2
send's line with the state registers its PACKED / REGLIST / A+D writes touch. Static chains write context 1's
FRAME / ZBUF / TEST / ALPHA / TEX0 / TEX1 / CLAMP / SCISSOR, TEXA, TEXFLUSH and SCANMSK, and of context 2 only ALPHA_2
/ TEST_2 / TEX1_2 / ZBUF_2 / FRAME_2 and FOGCOL; never TEX0_2 / CLAMP_2 (those come from the model data). On the fake
disc (stub:2, 86 sends, all whole) the HUD's 21-qword func_00237018 packets write the whole context-1 environment
(DTHE, COLCLAMP, DIMX, PABE, FBA_1, XYOFFSET_1, PRMODECONT, MIPTBP1_1 / 2_1 too): the only sends that set those.

Valgrind with TRACE=2: 0 errors up to the overlay entry (23 sends). The stub:2 run ends where it did
(func_00132790). layoutcheck 0, relcheck 0, abicheck 0, dmacheck 0, abscheck 0, indcheck and argcheck unchanged (3
value uses, waiting for dktitle.x).

### 5.1q Session 77: the GS state values, the HUD's environment, the run-time census

Static only (the Mac was away until 2026-10-26). Only tools/, host/ and tests/ changed: kh1.elf is byte-identical,
every out/build object bit-identical (sha1 of all 677 before and after), and the float ELF the same (fcheck.sh:
float_covered, float_reach, loadhash, phdr all the same), so there is no float-untested.md row.

**`dmawalk.py --state`**: the renderer's state list from the 81 static chains, each register's distinct values
decoded with the functions that send each (18 registers, 87 values). Checked against renderer-spec 3.2, which it
corrects in five places (func_00106460's destination-alpha mask is a SPRITE, not `POINT|ABE`; a subtractive
`(Cd-Cs)*As` pass in func_00106000; Z-only writes in opdma, `AFAIL=ZB_ONLY ZTST=GREATER`; targets in the Z area
and at 0x3E0000; point sampling in three packets and a static REGION_CLAMP). renderer-spec 4.7.

**The HUD's environment read from the C**: func_002370c8 (src/gfx/gspkt.c) is the 22-qword default context-1
environment every HUD element sends before it draws (17 files in src/hud); its values, decoded in renderer-spec
4.7, agree with the session 15 GS dump (DTHE 0, COLCLAMP 1, PABE 0, PRMODECONT 1). The HUD overrides TEST_1 to
ignore Z and CLAMP_1 to CLAMP; the numbers also switch to additive blending. func_002372e0 and func_00237318 (the
default and a 3D variant, sent from D_006480D0) have no caller in the main ELF: check dktitle.x.

**`KH1_HOST_TRACE=4`** (host/null/dmawalk.c): after each send's line, every distinct GS state value it writes
(`kh1-host:   gs REG VALUE`; vertex registers left out; the tags only at 3 now). `kh1_dma_gs_values()` hands
them to a caller (tests/host/dmawalk_test.c checks PRE, A+D, a vertex write left out, a repeat kept once and
REGLIST: 17 cases). **`tools/host/gsstate.py RUN.txt [--sends]`** turns a run into the same state list as
`dmawalk.py --state`, each chain named by the host symbol at its start. Fake disc, stub:2: 86 sends, 21 chains, 32
registers, 53 values (the HUD's seven environments, renderer B's draw state, the font uploads); opdma's
D_0061E8B0 writes PRIM 0 from two zero A+D qwords (a state write, not a draw: the GIF parser must allow it).
Valgrind with TRACE=4: 0 errors up to the overlay entry. The text windows' chains wait for the real disc.

### 5.1r Session 78: the chains the C builds from constants, opdma's set-up packets, the GS register file

Static only (the Mac was away until 2026-10-26). Only tools/, docs/ and one comment in src/gfx/opdma.c changed:
kh1.elf is byte-identical, every out/build object bit-identical (sha1 of all 677 before and after), and the float
ELF the same (fcheck.sh), so there is no float-untested.md row.

**`dmawalk.py` seeds** (renderer-spec 4.8): 17 chains that were "run time" in the walk are built once by init code
from constants (text.nofill.c's func_001f2eb8: the text windows' four headers and the window font's two uploads;
the menus' image uploads in menubg, config and journal; wave.c's func_001e9670; texspot's tag words). `SEEDS`
copies what that C writes and lays it over the ELF's bytes before the walk: **155 sends, 81 whole + 68 whole from
seeds, 0 problems**, the float build the same chain for all 149; 6 stay run time (grideff's upload, whose size comes
from the run, and mdlgs' renderer B chains). Every seed was compared with the host build's bytes under gdb (after the
boot, and after calling the wave and menubg init functions): all equal. `--no-seeds` gives session 77's numbers.
`--float` now finds a chain by the address its D_ name stands for (aliases the float ELF keeps are not in data.tsv).

**What they add to the state list** (23 registers, 115 values, from 18 / 87): the window font (PSMT4 at `0x3D7C`)
and the message font (**PSMT4HL at `0x1000`: in the Z buffer's top byte**, uploaded with its PSMT4HH half by
func_001ef950); the text headers' `TEST_1 0x4000D` (`ZTE=0`: no depth test); the wave as 100 `LINE|IIP|ABE` lines;
texspot's pass into the off-screen buffer `0x3A0000` (FBW 256, XYOFFSET 0) and its composite with REGION_CLAMP;
the menus' uploads into the `0x3600` slot with CLUTs at `0x3640` / `0x3680` / `0x3700`.

**opdma's set-up packets** (session 77's item 4a): the priority-list insert functions count the DMA tag in their
`qwc`, so `7` sends a GIF tag and 5 A+D, the same 6 qwords func_001aa008 sends: nothing runs short. Three of the
five A+D are PRIM 0 (not two), and the TEX1 / TEXA / CLAMP words written after them are never sent or read in the
main ELF. `D_0061E800` (ZMSK 1, first) and `D_0061E8B0` (ZMSK 0, last) bracket the frame's lists: no Z writes inside,
restored after. Checked against gdb's dump of both packets on the host.

**The GS register file** (renderer-spec 5.1, a draft): which registers the Vita renderer keeps per context, which it
drops (PRMODE, TEXCLUT, SCANMSK, DTHE / DIMX, COLCLAMP, PABE, FBA, MIPTBP: one value each, all inert; TEXFLUSH,
which the upload itself replaces),
and that GS memory itself must be modelled (targets read back as textures, the font in the Z buffer's top byte).

### 5.1s Session 79: the GS register file on the host, the windows' packets and renderer B's state from the C

Static only (the Mac was away until 2026-10-26). Only host/, tests/, tools/ and docs/ changed: kh1.elf is
byte-identical, every out/build object bit-identical (sha1 of all 677 before and after), and the float ELF the same
(fcheck.sh), so there is no float-untested.md row.

**host/null/gsregs.c** (new; renderer-spec 5.1, "On the host"): the first piece of the Vita renderer that runs.
dmawalk.c's GIF reader feeds it every A+D / PACKED / REGLIST write and each tag's PRE; it keeps 5.1's registers per
context (TEX2 into TEX0's PSM and CLUT fields), keeps them across sends, and counts vertex and drawing kicks per draw
state. `KH1_HOST_TRACE=5` prints each send's draw states; `tools/host/gsstate.py RUN.txt --draws` lists a run's.
tests/host/gsregs_test.c (19 checks, in `make test` with dmawalk_test). Fake disc, stub:2: 86 sends as before, **4
draw states, 392 kicks, 196 sprites** (the 3D target's clear and its copy to the display buffer, the Z area read as
CT24, one fill), none blended. Valgrind 0 errors (to the overlay fault).

**The text windows' per-draw packets** (renderer-spec 4.9, from the C; `tools/host/giftags.py` lists the GIF tag
constants of 43 functions): a static header (4.8) then a scratch-frame packet that relies on the header's state;
only SPRITE and TRISTRIP, always ABE, FST when textured; windows clip with a per-draw SCISSOR_1. **The message
font's PSMT4HH half is drawn by every glyph whose table entry has `f7 >> 4 = 1`**: each glyph sprite carries its own
TEX2_1 (PSMT4HL / PSMT4HH by `D_003E8D00`, CSA 0 / 1, CLD 0) after the header's TEX2 loaded the whole 256-entry CLUT
(CLD 2); the 784 default glyphs are 196 cells x 4 layers. The window bevel (`func_00206748`) changes ALPHA_1
between additive and **subtractive** inside one TRISTRIP: the Vita renderer splits a strip at a state change.

**Renderer B's draw state** (renderer-spec 4.9): func_0015f128's 9-A+D template `D_00573E40` behind a CALL to the
upload list `D_00573AC0`; func_0015f488 per draw (TEX0 `0x3600` PSMT8 / CLUT `0x3700`, the opaque pass `ATST GEQUAL
AREF<=120` with Z written and the model's fog colour, the translucent pass `ATST LESS` with ZMSK 1, both blended
`(Cs-Cd)*As+Cd`); func_0015f8c8's sub-rectangle uploads (texture animation); func_0015f388's reset (blending off,
`ATST GEQUAL AREF 128`), placed in the draw list at four keys. 5.1's table has these values without a run.

### 5.1t Session 80: GS memory on the host, the builders giftags.py misses, renderer A's state from the C

Static only (the Mac was away until 2026-10-26). Only host/, tests/, tools/host and docs/ changed: kh1.elf is
byte-identical, every out/build object bit-identical (sha1 of all 677 before and after), no src/ or shift input
touched, so the float ELF is the same and there is no float-untested.md row.

**host/null/gsmem.c** (new; renderer-spec 5.2): 4 MB of GS local memory with the block / page / column swizzle of
CT32, CT24, CT16, T8, T4, T8H, T4HL and T4HH (bit formulas, checked against PCSX2's tables for every pixel of a
page, outside the repo), written by host->local uploads (TRXDIR, then dmawalk.c's IMAGE qwords; HWREG too) and
local->local copies, the GS's 512-halfword CLUT buffer loaded at each TEX0 / TEX2 by CLD (0-5), and a reader that
decodes a TEX0 to RGBA8 (`kh1_gsmem_read_tex`) with page stamps for a texture cache. tests/host/gsmem_test.c (36
checks) in `make test`. `KH1_HOST_TRACE=5` prints each send's uploads, `gsstate.py --uploads` lists them, and
**`KH1_HOST_TEXDUMP=DIR`** writes each drawn texture as a .pam. Fake disc, stub:2: three uploads from
func_001ef950 (src/text/text.c): the message font as PSMT4HL / PSMT4HH 256x256 at `0x1000` and its 16x16 CT32 CLUT
at `0x3FFC`; the font lands inside the Z area's 512x512 at `0x0E00`. Valgrind 0 errors to the overlay fault.

**The boot draw environment reaches the host's register file**: PlatGsPutDrawEnv (null) now feeds
`kh1_dma_gif_direct`, so func_001100a8's 31 A+D (both contexts, renderer-spec 4.11) are in the state: fake disc
87 sends, 22 chains, 40 registers, 61 values.

**renderer-spec 4.10** (from the C): menu rows / lists draw through wintext / winpart only; the list frame
`func_00208458` restarts three strips in one tag with ADC; **the field text and the selector use their own static
headers, REGLIST packets and PRIM as a register write, ZTE 1**; the field text's palettes pick a texel's low / high
2 bits (`func_0010e610`, read from the C); **the HUD gauges draw TRIANGLE pairs and a TRIFAN**, each triangle
re-loading the CLUT with a PSMT8 TEX0 then the real one. Five corrections to 4.9.

**renderer-spec 4.11** (from the C): renderer A writes no GS register in its VIF chains (meshes by XGKICK);
context 2's state is the boot environment plus six PATH3 A+D packets at draw-list keys 10010 (a backdrop pass with
`TEST_2` NEVER / FB_ONLY / ZTST ALWAYS; FOGCOL each frame), 10020 (AREF 16), 40000 (AREF 127 per opaque prop), 50000
(ZMSK 1, translucent) and 50100 (restore), plus the shadow's; mesh TEX0_2 / CLAMP_2 / batch PRIMs come from the
disc files (inferred). Corrections to 4.6, 3.3 and 5.1's FOGCOL row.

### 5.1u Session 81: render targets in the memory model, the order between the paths, REGLIST and ADC

Static only (the Mac was away until 2026-10-26). Only host/, tests/, tools/host and docs/ changed: kh1.elf is
byte-identical, every out/build object bit-identical (sha1 of all 677 before and after), no src/ or shift input
touched, so the float ELF is the same and there is no float-untested.md row.

**Render targets** (renderer-spec 5.2): host/null/gsmem.c now hears each drawing kick (gsregs.c passes the
context's FRAME / ZBUF / SCISSOR / TEST) and each VU1 program start on VIF1 (`kh1_gs_path1`: context 2, renderer
A's), keeps up to 32 targets and, per page, the word bits a draw changed (Z24 / CT24 the low 24, so the message
font in Z's top byte stays a texture), cleared by uploads. `kh1_gsmem_tex_target` names the target a TEX0 reads;
a draw state carries it (`KH1GsDraw.target`), `KH1_HOST_TRACE=5` prints `, reads target N` and each send's
`target` lines, `gsstate.py --targets`, and the texture dump skips them. gsmem_test.c +16 checks. Fake disc
(stub:2): three targets (the 3D target `0x1A00`, the Z24 buffer `0x0E00`, the display buffer at 0) and two
draw states reading one: the frame copy `D_002A6890` (3D target) and the capture `D_002B66B0` (the Z area).
Valgrind 0 errors to the overlay fault (`KH1_HOST_TRACE=5`).

**PATH1 against PATH3, settled** (renderer-spec 4.12, item 4b of the session 81 prompt): the draw-list walk
`func_0015ea98` waits for `sceGsSyncPath(1, 0)` (ch 1, ch 2, VIF1, VU1, GIF all idle) before each node, so the
order is the list's, node by node, and the GIF's path arbitration never needs modelling; the immediate list and
`func_00106b18` wait for the list to drain. **`tools/host/sendorder.py`** (new) lists the tasks that send by
key: only the in-game menu (`func_0020d2f8`, key `0x270FF`, between the list start and the immediate list)
sends before it syncs (the window-font uploads, then the window headers). The port replays the draw list, then
the immediate list, then the main-thread sends in task order.

**REGLIST and ADC** (item 4c): gsregs_test.c +5 checks (renderer-spec 4.10's field text: PRIM as a REGLIST
register, a glyph tag with no PRE; the list frame's 18-vertex tag with ADC on v6 / v7 / v12 / v13 drawing 12
triangles; XYZ3 in a fan). gsregs.c already did what the GS does: no change.

### 5.1v Session 82: the Z formats in the memory model, the draw list's key map, the replay's flush

Static only (Sunday 2026-10-25; the Mac is back from 2026-10-26). Only host/, tests/, tools/host and docs/
changed: kh1.elf is byte-identical, every out/build object bit-identical (sha1 of all 677 before and after), no
src/ or shift input touched, so the float ELF is the same and there is no float-untested.md row.

**The Z formats** (renderer-spec 5.2, item 4a): host/null/gsmem.c's `kh1_gsmem_addr` now has PSMZ32 / Z24 /
Z16 / Z16S (the colour twin's layout with the final block number XORed with `0x18`, as PCSX2 does) and
PSMCT16S (its own block order), reads and writes them, decodes them as textures, takes CT16S CLUTs, and marks a
draw's Z target's pages through the same address function. Inside a page a Z32 / Z24 pixel (x, y) is the CT32
pixel (x ^ 32, y ^ 16); Z16 (x ^ 32, y ^ 32). Checked against PCSX2's tables on 30 M addresses outside the repo;
gsmem_test.c 52 -> 61 checks (fixed Z / CT16S addresses, CT32 vs Z32 of the same block, a Z24 upload read back
as CT24 in the swapped quarter, a Z16S upload). For the port: a CT24 sample of a depth buffer (the capture,
`D_002B66B0`) needs that quarter swap in the shader.

**The draw list's key map** (item 4b): **`tools/host/drawkeys.py`** (new) lists every draw / immediate list
insert with its key, followed through the wrappers to literal keys; the table is in renderer-spec 4.12 (38 rows;
renderer B's per-entry keys are the only data-driven ones). The port's command list is this order.

**sendorder.py** (item 4c): its pattern missed a plain cast on the callback (`(s32) &func_X`): 4 more
registrations (164 -> 168), one sending (brightfade's `func_00106460`, after the immediate list, behind a sync).
No registration has a non-literal key; `--all` now also lists any call the pattern cannot read (none). Still
only the in-game menu sends between the draw list's start and the immediate list.

**How the replay flushes a pending list before a main-thread send** (item 4c): on the Vita the draw list is not
consumed by interrupts; the port records each node as a command and replays them. The rule that keeps the
console's order: **a list is "pending" from task `0x9C40` (`func_0015eb78` hands it over) until its replay has
run, and every main-thread GS send first replays whatever is pending.** Concretely, `PlatGsSyncPath` (any mode)
and every main-thread `PlatDmaSend` on ch 1 / ch 2 / `PlatGsPutDrawEnv` call one `kh1_gs_flush_pending()` that
replays the pending draw list to its end (and, at task `0x27CB8`, the immediate list), then returns; the send
then goes into the command stream after it. That is what the console does for every synced sender (they wait
for the list to drain) and what it nearly always does for the in-game menu's unsynced first send (the list
ends long before task key `0x270FF`; renderer-spec 4.12; session 84: always, the frame-end wait at task
150000 drains it first, 5.1x). The send itself does not wait for the GPU: the
flush only orders commands, so the cost is a function call when nothing is pending. Uploads in such a send
(the window font) go to gsmem.c's model and the texture cache after the replayed draws, so a draw of the
pending list never samples the upload's data, as on the console. The DMAC handlers the null platform runs
(5.1h) become this replay: the port's `func_0015ea98` runs the list in one loop, its `sceGsSyncPath(1, 0)`
answering idle at once.

### 5.1w Session 83: the draw list's nodes as commands, renderer B's keys, the CLUT animations

Static only (Sunday 2026-10-25; the Mac is back from 2026-10-26). host/, tests/, tools/host, docs/ changed,
and two src/include lines: **include/platform/gs.h's new `PlatGsListNode(list, node)` / `PlatGsListEnd(list)`**,
called by src/model/mdlgs.nostrict.c's walks (`func_0015ea98`, `func_0015eea0`) around each node's callback
and at the list's end. On the PS2 build they are `((void)0)`: kh1.elf is byte-identical, **every out/build
object bit-identical** (sha1 of all 677 before and after, mdlgs.nostrict.c.o rebuilt), `make shift` M0 OK, so
the float ELF is the same and there is no float-untested.md row. abicheck, dmacheck, relcheck, layoutcheck,
abscheck 0 rows; indcheck the same 241 rows as before the change.

**The draw list as commands** (item 4a, renderer-spec 4.12 "The draw list on the host"): this is the hook
5.1v asked for. The port records each node (key at +4, callback at +0xC, payload at +0x10) as a command at
`PlatGsListNode` and replays the list; the null platform prints it at `KH1_HOST_TRACE=5` (`kh1-host: node
...`, `node main`, `list ... end`, `vblank N`) and **`gsstate.py --nodes [--frame N]`** prints a frame's
command order and checks every node against drawkeys.py's map (fake disc stub:2: 13 nodes, 6 distinct, 0
outside the map). **`kh1_gs_flush_pending`** (plat_null.c) is 5.1v's rule on the null platform: every
main-thread `PlatGsSyncPath(0)`, ch 1 / 2 `PlatDmaSend`, `PlatDmaPutVif1Chcr` and `PlatGsPutDrawEnv` (outside
a node and a DMAC handler) checks whether the draw list is pending (`D_00559DB4`), counts it and runs the due
DMAC handlers; the run's summary prints the count at `KH1_HOST_TRACE=5`: 0 on the fake disc, as expected
(the null DMAC drains the list as each transfer ends). Mode 1 syncs are the walk's own and not counted.

**Renderer B's keys** (item 4b, renderer-spec 4.12): objects are 20000 (opaque) or 70000 (alpha below 0x80,
and every translucent part) plus their depth rank (0-77, far first), shadows 60000 + 10 n, the menus' models
the immediate list at 0. The key map is now complete: no data-driven key left that the C does not explain.

**The texture animations are CLUT cross-fades** (item 4c, renderer-spec 4.13): seven nodes per animation at
90000 + 10 id upload two palette frames to `0x3600` / `0x3A00` and draw them as point-sampled sprites over
the room CLUT at block `0x3E00 + v` (a copy, then a blend by `f10 + 1`), FBMSK keeping the CLUT's alphas;
the room's draws read it the next frame. host/null/gsmem.c's **`kh1_gsmem_sprite`** now draws such sprites
into the model (gsregs.c calls it for each SPRITE; anything it cannot draw is a target as before), so a CLUT
load after the passes reads the blended palette; tests/host/gsmem_test.c 61 -> 65 checks, valgrind 0 errors
(the test and the fake-disc run). For the port: the palette animation must happen (a CPU blend of the room
CLUT copy, or the same draws into the port's GS memory), and textures that use those CLUTs must be re-read
each frame or kept as index textures with a palette (renderer-spec 5 "PSMT4/8 + CLUT").

### 5.1x Session 84: the replay on the host, the menu's "race" settled, renderer B's depth, the scroll copies

Static only (Sunday 2026-10-25; the Mac is back from 2026-10-26). host/, tests/, tools/host, docs/ changed,
and two src/include lines: **include/platform/gs.h's new `PlatGsListWait()`**, the body of
src/model/mdlgs.c `func_0015ef60`'s spin (`while (D_00559DB4) PlatGsListWait();`), `((void)0)` on the PS2.
kh1.elf is byte-identical, **every out/build object bit-identical** (sha1 of all 677 before and after,
mdlgs.c.o rebuilt), `make shift` M0 OK, so the float ELF is the same and there is no float-untested.md row.
abicheck, dmacheck, relcheck, layoutcheck, abscheck 0 rows; indcheck the same 241 rows; argcheck the same 3
value uses.

**The replay** (item 4a): **`KH1_HOST_DMAC=defer`** (host/null/main.c, plat_null.c `kh1_host_dmac_defer`):
a transfer's end and `PlatEnableDmac` only set the channel's status / mask bit, no DMAC handler runs there,
so after `func_0015eb78`'s hand-over the draw list stays pending (`D_00559DB4 = 1`) until a main-thread GS
call's `kh1_gs_flush_pending` or the frame-end wait's **`PlatGsListWait`** replays it (both run the due
handlers, which walk the list to its end as the interrupts would). The flush now runs before the `node main`
marker, so a replayed list's lines come before the send that caused it. On the fake disc (stub:2):
**`gsstate.py --nodes`' command order is the same with and without the switch** (every frame), 13 nodes;
**0 main-thread sends and 3 frame-end waits found the list pending** (the summary line), one a frame. A list
still pending at the wait with no handler due would spin for ever: the host says so and exits 3. Valgrind
0 errors (the plain fake-disc run with the switch; the stub still cannot run under valgrind).

**Why no send found it pending: the in-game menu cannot race the list** (renderer-spec 4.12). Task
**150000 (`0x249F0`, `func_0011eda8` -> `func_0015ef60`)** is registered with the list's own tasks
(`func_0011edc8` calls `func_0015ec68` and registers it; one task list `D_004E3A48`, run in key order) and
spins until `D_00559DB4` is 0, then `sceGsSyncPath(0, 0)`, then masks DMAC channels 1 / 2. It sits between
the hand-over (`0x9C40`) and the in-game menu (`0x270FF`), so the menu's unsynced sends always come after the
list has drained. `tools/host/sendorder.py` now finds that wait from the C (the first task between the list
and the immediate list whose calls reach `func_0015ef60`, printed as "drained at 0x249f0") and counts RACE
only before it: **0 RACE** (was 3). No task between `0x9C40` and `0x249F0` sends. **For the port:
`PlatGsListWait` is the one place the draw list has to be replayed** each frame; `kh1_gs_flush_pending` in
the main-thread sends stays as a guard (it never fires on the console's order).

**The first texture animation kind** (item 4b, renderer-spec 4.13 "The texture steps"): GS-to-GS copies,
no upload from the EE: kind 0 copies frame k's rectangle from a sheet already in GS memory, kinds 1 / 2
scroll a rectangle vertically with two copies. tests/host/gsmem_test.c checks the scroll's two copies
against gsmem.c (65 -> 67 checks; valgrind 0 errors). For the port: a GPU blit (or a sub-rectangle copy
in the texture cache) before the frame's draws, in the step's list position; textures over the destination
must be re-read.

**Renderer B's depth key** (item 4c, renderer-spec 4.12): settled from the C. `D_002E26C0` is built in
src/camera/view.c `func_00125000` as `D_002E2740 x D_002E2700`: the view-screen matrix (`D_002BBE20`, the
first output of display.c's `func_00110618`, whose w row is (0, 0, 1, 0): w = the camera-space z) times the
camera matrix (`sceVu0CameraMatrix`). objdraw passes it to `func_001606d0`, which stores `D_002E26C0 x
bone 0` as the model's first matrix, so `[3][3]` is the clip w of the model's origin, its depth from the
camera. The sort is far first, as written.

### 5.1y Session 85: the sound commands as an interface, renderer A's grid chains

Static only (Sunday 2026-10-25; the Mac is back from 2026-10-26). Only docs/ and README.md changed: kh1.elf
byte-identical, no object rebuilt, the float ELF the same (no float-untested.md row).

**The sound driver's interface** (item 4a, new **docs/sound-spec.md**): snd_rpc.c's 51 functions sorted
into transport (RPC 0 bind with the status / message block addresses and a mode 0 boot / 1 soft reset / 2
room load; direct calls answer in word 0 of the shared buffer; queued 8-word records flushed as RPC 30
once a frame), the status block (SE voices at +0, four streams at +0x1800, **the disc-error word at
+0x1C08** that io/cdqueue.c turns into the disc-error state after 30 frames, the transfer count at +0x1F00)
and the commands: transfers (`0x26` free, 3 wave, 4 SE tables, `0xB` sequence, `0x28` voice bank), music
(`0xC` start, `0xD` stop, `0xE` fade, `0x2F` / `0x30` the one polled answer), SEs (5 play, 8 volume, 6 stop,
7 fade out, 2), streams (`0x12` voice from a VAG in EE memory, pitch = rate x 4096 / 48000; `0x13`, `0x14`;
object SEs `0x29`, `0x2A`, `0x2B`), settings (`0xF` pause, `0x23` stereo / mono, `0x24` around movies,
`0x27` per room). Two findings for the port: **RPC 30 sends only 0x2000 bytes, the first 256 of the
queue's 1024 records** (the rest are dropped by the refill), and **`func_0011d2d0` searches the static SE
table `D_004E3458`**, not the live pointer, so in a 128-slot room ppp's SE switch finds no slot (a console
quirk to keep), and **`func_001ecb08`'s wildcard loops fall through** into a second pass that reads
24 more 0xB4-byte "entries", up to 0x114 bytes past the 0x2000-byte status block (sound-spec 3: keep the
bytes after the block readable; no layout check follows pointer walks, so none listed it). 16 entry
points have no caller in the main ELF (RPCs 1, `0x16`-`0x19`, `0x1B`, `0x1D`, `0x1F`-`0x22`, `0x32`,
commands 9 and `0x15`, the readers `func_001eced0` / `func_001ecf40`): for the dktitle.x / overlay check
(5.2).

**Renderer A's grid chains** (item 4b, renderer-spec 4.14, open question 6.8): `func_00107d30`'s case 3 is
each visible map cell's second mesh (section 1 entry `i + 1`'s `{w8, w12}` tag), collected by
`func_00107c48`, drawn by P3 at key 50000 after the opaque pass with no Z writes and a static FGE fan
template; cases 0 / 1 are the cells' first meshes at 10020 (P0 / P6 and P2). The fade groups reuse chain
3's head. For the port: one translucent grid pass after the opaque draws.

**Item 4c (make `KH1_HOST_DMAC=defer` the default)**: not done. It waits for the real-disc room run (item
2): the fake disc's stub:2 run has 13 nodes and no room, so it cannot show that the order holds with real
draw lists. **Item 4d** (argcheck's 3 value uses) still waits for dktitle.x.

### 5.1z Session 86: the status block read past its end, pointer walks, the null sound server, frame pacing

Static only (Sunday 2026-10-25; the Mac is back from 2026-10-26). kh1.elf byte-identical; two PS2 objects
changed (src/data/data_0063.s, bss_0063.c), every other out/build object bit-identical; the float ELF
changed (float-untested.md row 86).

**The status block's tail** (item 4a, sound-spec 3): the piece `D_0063D640` (src/data/data_0063.s) now runs
to 0x0063F740 and holds the IOP's message buffer `D_0063F640` at +0x2000 (its C definition in bss_0063.c
removed; RPC 0 sends both addresses, the IOP writes both). `func_001ecb08`'s fall-through reads to +0x2118;
the last 0x18 bytes (entry 47: the text words `D_0063F744` ... `D_0063F754`) cannot join the piece, since
MIPS gas pads a section aligned to 16 or more to 16 and 0x2118 would run into `D_0063F758`; on the PS2
entry 47 cannot match (`D_0063F754` is never written: no `0xF754` displacement in the ELF), so the host
gives the piece 0x18 zero bytes (census.py `HOST_TAIL`, applied to the x86 copy of the piece only).
layoutcheck 0, relcheck 0, abscheck 0.

**tools/host/walkcheck.py** (new, portability rule 12): every pointer a loop steps (`p++`, `p += n`,
`p = p + n`) that a later loop reads with no assignment between, from clang's tree of every game file and
draft (indcheck's flags, 23 s); loops in other branches of one `if` and loops followed by a `return` are
left out, and `p = p->next`, `p = next(p)` and a packet builder's `p = put(..., p)` are not steps. 17
rows, all read (REVIEWED): func_001ecb08's three (the fix above), cmdmenu's sprite index list, the
notice's 9 sprites, two 256-entry CLUT fills (kemat, kemdltfd: entries 0..n-1 then n..255), pppapi's
relocation header, fldtext's 16-word output, task.c's context carving (0x163C00 bytes below the task
table at +0x16BC00), the memset and the strcat in vmath.c. 0 WALK.

**The null sound server** (item 4b, sound-spec 5): host/null/sound.c takes plat_null.c's sound RPCs. It
keeps the SE and stream entries of the status block (`used` set on a play, cleared on a stop, after a
fade, or by time: 60 frames for an SE, the VAG length for a voice), the transfer count (now with
command `0x28`, which session 67's answer left out), and prints each command at `KH1_HOST_SND=trace`;
**tools/host/sndlog.py** sums a run up; tests/host/sound_test.c (18 checks) runs in tests/selftest.sh. The
fake disc's stub:2 run: 43 commands, then func_00132790 as before; valgrind 0 errors to the overlay fault
(the plain run, 23 commands).

**Frame pacing and the system-message band** (item 4c, renderer-spec 4.15, open questions 9 and 10):
the frame end waits for one field and then `D_002BBE0C` more (30 fps in the field, 60 in the pause, game
over and reset); `D_002BBDFC`, the game's time step, is fields x `D_002BBDEC` x the script speed, capped at
5; `D_002BBDEC` is 1.0 (written once) and `func_0010fea0`'s constants are the 100-hour play-time cap at 60
/ 50 Hz. `func_0010f5f8` is a 512 x 128 band on read circuit 1 from block `0x3600`, opaque over the frozen
frame: no controller, the disc error, a read error and its retry, and the pause's strings. The movie copy
from `0x118000` (`func_00106000` case 2) has no main-ELF selector (no store of 2 to `D_002BBE04`): for the
overlay check. Item 4d (`KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses) still waits for
the Mac.

### 5.1aa Session 87: index walks and builder results, a scripted pad, the script's screen spin

Static only (Sunday 2026-10-25; the Mac is back from 2026-10-26). Only tools/host, host/, tests/ and docs/
changed: kh1.elf byte-identical, **every out/build object bit-identical**, the float ELF the same (no
float-untested row).

**walkcheck's two siblings** (item 4a, portability rule 12): tools/host/walkcheck.py now also lists
**index walks** (`idx`: an integer a loop steps and a later loop uses as an array index, `a[i]` or
`p + i`, with no assignment between: `for (i = 0; i < n; i++) ...; for (; i < m; i++) a[i]`) and
**builder results** (`call`: a pointer assigned the result of a builder, a function that returns a pointer
one of its loops stepped or another builder's result, and then stepped by a later loop, also inside the
loop that holds the call). 88 builders. New rows, all read: **21 idx** (IDX_REVIEWED: the Gummi block
table's held / empty runs, checked against the disc's ELF: 64 held, 64 empty, 32 more of 160; the
garage's preset and saved ship lists, up to `D_00623E40[58]` of 64; the journal's three lists on one
count, `D_003F50E0[184]`; the journal grid's 99 cells; the number formatters' `dig[12]`; the message
number's 22 of 32 bytes; the text window list's 24; two CLUT fills that index a 32-entry table with
`i & 0x1F`) and **4 call** (CALL_REVIEWED: pppsys's four section readers after `func_001803c0`'s skip,
the ppp file format). 42 rows, **0 WALK**. Two things to check later: wintext's message code 11 passes a
byte of the message as the digit count (`dig[12]`: more than 12 overruns on the PS2 too; read the real
disc's messages), and:

**The save menu's party fill leaves a byte unset** (savemenu.c `func_00228588`, checked in kh1.elf: the
loop adds 2 to `j`): after keeping the members 1 and 2 (`buf[1..]`), `for (; j < 4; j += 2) buf[j] = -1`
leaves `buf[3]` unset when one member is kept and `buf[2]` unset when none is, and `func_0013c778` writes
a value < 10 into the party. On the PS2 the byte is whatever the stack held (most likely the same every
time); on the host and the Vita it is another stack. Not changed (matching code); the port's fix, if a
boot shows a party member appearing after this save-point choice, is to start `buf` at `0xFF` in a
port-only build.

**The null pad and a scripted controller** (item 4b): host/null/pad.c takes platform/pad.h from
plat_null.c. **The pad is now connected** (state 1, a DualShock 2 profile, nothing pressed, the sticks
centred): before, `PlatPadGetState` never answered 1, so from frame 32 every host run sat in
`func_0010f918`'s "no controller" loop (`D_002C5968.b0`, renderer-spec 4.15; on the fake disc 400 frames:
`func_0010f5f8` once, `func_0010f918` 32 times with no pad, 399 with one). `KH1_HOST_PAD=none` keeps the
old answer; **`KH1_HOST_PAD=FILE`** plays a script, `FRAME BUTTONS [RX RY LX LY]` lines held until the
next (`START`, `CIRCLE+UP`, `0x4000`, `-`, `out`), and `KH1_HOST_TRACE=1` prints `kh1-host: pad FRAME
BUTTONS` at each change. Checked on the fake disc under gdb: START reaches `D_002C5AD0.x4` (the menus'
`D_00425BC8` pad) at the scripted frame, `out` for 60 frames raises `D_002C5968.b0` after 31 and clears it
when the pad is back. tests/host/pad_test.c (18 checks) in tests/selftest.sh. The stub:2 run still ends
in func_00132790; valgrind 0 errors to the overlay fault. Found on the way: `D_002C5BB0` (the decoded pad)
is not the PAD_* bits but **actions** through the 30-entry table `D_002C5990` (func_0011f628: circle and
R3 to 1, cross to 2 and 4, ...); START and SELECT have no action and are read from the raw pad.

**The script's screen spin** (item 4c, renderer-spec 4.16): `D_002BBE04` 1 / 4 (objscmd.c `func_0012b450`,
vm_lib.c `func_001cde38`; vm_lib's `func_001cdea8` makes 1 into 4) draw the frame last shown, turned by
an angle that ramps over a number of frames, blended into the target before the frame copy: a feedback
trail over the live scene (1) or over the frozen last frame (4). A negative angle is used at once; a
record with 0 frames divides by 0 (the EE's `FLT_MAX` vs IEEE's NaN for one frame: clamp in the port).

### 5.1ab Session 88: the other full-screen effects, the input layer, counts kept across functions

Static only (Sunday 2026-10-25; the Mac is back from 2026-10-26). Only docs/, tools/host/, tests/host/ and
one comment in src/gfx/sceneeff.c changed: kh1.elf byte-identical, **every out/build object bit-identical**,
the float ELF the same (no float-untested row).

**The other full-screen effects** (item 4a, renderer-spec 4.17): sceneeff.c's effects read from the C and the
static packets. `func_00102a48` is the **menu blur** (the frame captured at half size when a field menu
opens, drawn back as nine blended copies 1 then 2 px apart; the old "rings of glow" was wrong);
`func_00103058` a **depth blur** (an event's depth-of-field: mode 0 blurs what lies behind a Z value,
mode 1 the near part through an alpha mask); `func_001032b0` a **sway and colour pulse** (the room table's
flag or an event: the picture zoomed by 0.3-3.6 % on two out-of-phase axes, about 4 s a period);
`func_00103c48` VU1 P8's **lens grid** (a 25 x 25 mesh over a copy of the target, bulging toward the
camera); `func_001039f8` the **fades** to black / white (alpha to 255, so the visible fade is half the
count); and the **letterbox** bars of events (`D_002A6208`). Two things for the port: the sway and the
grid copy the target into the Z buffer's memory, so depth tests after them in that frame read colour
(keep a separate texture and depth); and the white fade-in's countdown runs in frames while the fade
runs in time steps, which at 60 fps turns the end of the fade dark (rule 7: tie the two together).
The block `0x1800` PSMT8H rows of §3.1 / §3.2 named `func_00103058` by mistake (it is `func_0010b6c0` /
`func_0010f0d0`).

**The input layer** (item 4b, for the Vita's platform/pad.h). Read from src/pad/, the 50 files that read the
pad (`D_002C5AD0`, `D_00425BC8`, `D_002C5BB0`) and the action table in the ELF.
- **The read** (padread.nostrict.c `func_0011f668`, once a frame from framectl.c `func_0010fd40`): only
  socket 0 is read (the loop stops at `i <= 0`; `D_004E4280` picks which of the two records it fills), so
  the Vita needs one pad. Bytes 0-1 (active low) become the PAD_* bits; when the profile's byte 2 has its
  low four bits set (analog), `func_0011f370` adds the stick directions and vectors. The vibration word
  (`p->b2` / `b3`) goes out every frame unless the config turns it off (`func_00219348`) or
  `D_002C597A & 1`. 31 frames without a stable pad raise the "no controller" band (renderer-spec 4.15).
- **A pad record** (`D_002C5AD0[2]`, 0x70 bytes; `D_00425BC8` points at the one the menus read, padrec.c):
  +4 held, +8 pressed, +0xC released, **+0x10 repeat** (the press, then after `D_002C5C24` = 30 time steps
  every `D_002C5C28` = 4: 0.5 s, then 15 a second), +0x14 a second repeat (the press, then every frame after
  30 steps; **no reader in the main ELF**), +0x30 / +0x40 the right / left stick scaled (x, y, 0, length),
  +0x50 / +0x60 their unit directions. `D_002C5C2C` = 32 is set and never read in the main ELF.
- **The sticks**: each axis `v - 127.5`, a dead zone of `D_002C5C20` = 60 each side (47 % of the half
  range, square), then `(|v| - 60) / 67.5`, the vector's length clamped to 1; a direction bit (right stick
  bits 20-23, left 28-31) once an axis is past the dead zone. **The left stick moves the player**
  (view.c `func_00124e08`: the unit direction at +0x60 and the length at +0x4C, turned by the camera; in the movement
  modes 2 and 11 the left stick's x turns instead, 3 degrees a step); the first-person view pitches with the left stick's y
  (fieldcam.c, 3 degrees a step x y, -80 to +60 degrees). The Vita's sticks report the same 0-255 with 128
  in the middle and 0 up: pass them through; the large dead zone covers their drift.
- **Actions** (`D_002C5BB0`, the same record): `func_0011f628` maps pad 0's held bits through the 30-entry
  table `D_002C5990` (`{mask, action}`, all bits of the mask held), and the press / repeat run on the
  actions. Zero while `D_002C5960.b` (input off); an event masks held and pressed with `D_00389C90.x3148`
  and clears the sticks (script_vm.c); vm_lib.c pushes the held actions, the raw held bits and the pressed
  actions to the script (`func_001d1478` / `func_001d14a0` / `func_001d14c8`). **Session 87's note was half wrong: SELECT has an action
  (0x8000); START has none** and is read raw.

| Button | Action bits | What reads them (main ELF) |
| --- | --- | --- |
| CIRCLE | 0x1, 0x10000, 0x80000 | 0x1 advances text (fldtext.c, selector.c); 0x10000 picks the command menu's entry (cmdmenu.nostrict.c mask); 0x80000 shortcut 1 while L1 is held |
| R3 | 0x1, 0x10000 | the same as CIRCLE (no reader of its own) |
| CROSS | 0x2, 0x4 | 0x2 backs out of a list, a shop, the command menu; 0x4 pressed: the jump command (`D_002E3190` 0x1000000), held 0x8000000 in some states; class11.nostrict.c keeps a rise going while 0x4 is held (a jump height, a guess) |
| TRIANGLE | 0x8, 0x100000 | 0x8 the action command (`D_002E3168 \|= 1`); 0x100000 shortcut 2 |
| SQUARE | 0x10, 0x200000, 0x800000 | 0x10 a command (`0x4000000` pressed, `0x10000000` held; the guard / dodge, a guess); 0x200000 shortcut 3; 0x800000 no reader found; also raw held 0x8000 in plctl.nostrict.c |
| D-pad, right stick | 0x20 up, 0x40 down, 0x80 left, 0x100 right | the command menu's cursor (0x100 opens a submenu, 0x80 backs out) |
| L1 | 0x40000 | held: the shortcut menu |
| R1 | 0x400 | lock-on on / off (cmdmenu.nostrict_nofill.c `func_0012f700`; config: hold or toggle, `func_002192c0`) |
| L2 | 0x2000, 0x800, 0x400000 | 0x2000 held turns the camera; 0x800 the next lock-on target; 0x400000 (L2 or R2) ends the lock-on state 4 of the command menu early (cmdmenu.nostrict.c: after 90 steps or on the press) and is read by view.c's movement mode 11 |
| R2 | 0x1000, 0x20000, 0x400000 | 0x1000 held turns the camera the other way; 0x20000 the previous target |
| L2 + R2 | 0x200 | the camera back behind the player (fieldcam.c `func_001784c8`); leaves the first-person view |
| SELECT | 0x8000 | the first-person view (fieldcam.c `func_00176f08(2)`, when `D_002C5958` bit 13 allows) |
| START, L3 | none | START raw: the pause (pause.c), skipping a movie (gamestate.c state 18; state 13 skips on any button), the menus' close (equip, topmenu, loadframe, textfade); L3 is read nowhere |

The menus (`D_00425BC8`, 30 files under src/menu/, src/shop/, src/text/) read raw bits only: pressed CIRCLE
confirms, pressed CROSS cancels, the d-pad and left stick as `PAD_DIR` through the repeat word (a move on
each repeat; the wrap to the other end only on a fresh press), L1 / R1 page (winmenu.c, journal), TRIANGLE
in the journal; the journal map also reads both sticks' held directions. The name entry folds the left
stick into the d-pad (`press | (press >> 24 & 0xF0)`). **padrec.c's recorder, replay, button script and
idle timer** (`func_00233650` ... `func_002336e8`) have no main-ELF caller: the title overlay's (the demo),
for the dktitle.x check.

**The Vita mapping** (the PlatPad* wrappers fill the libpad2 buffer from `sceCtrlPeekBufferPositive`; the
game above them stays as it is): CROSS, CIRCLE, SQUARE, TRIANGLE, the d-pad, START and SELECT one to one;
L to L1, R to R1; both sticks as bytes 2-5 (right x, y, left x, y); a DualShock 2 profile (byte 2 low
nibble `0xF`) so the sticks are read. The handheld has no L2 / R2 / L3 / R3: **L2 and R2 on the rear touch
pad's left and right halves** (held while touched; both = the camera reset), R3 not needed (it doubles
CIRCLE), L3 unused. A PS TV with a DualShock 3 / 4 reports L2 / R2 / L3 / R3 itself
(`sceCtrlPeekBufferPositiveExt2`): use them when present. Options for the port's menu, outside the game
code: swap CIRCLE / CROSS (the Western layout: the swap in the wrapper changes menus and battle alike, as
the Western releases did), and a "right stick turns the camera" mode that turns the right stick's x past
the dead zone into L2 / R2 and drops its d-pad bits (the journal map then loses its right-stick pan).
Vibration: `sceCtrlSetActuator` on a PS TV pad, nothing on the handheld (`PlatVibSetActParam` returns 0).

**`KH1_HOST_PAD` for the title**: tests/host/pads/title.txt (START at frame 600, CIRCLE at 660 and 720;
the frames are guesses until a real-disc run, since the title is dktitle.x's code). On the fake disc with
`KH1_HOST_OVL=stub` the null pad plays it as written (`kh1-host: pad 600 START` ...).

**Counts kept across functions** (item 4c, portability rule 12): **`tools/host/countcheck.py`** (new, clang
syntax trees like walkcheck): a global one function steps (`G++`, `G += k`, `G[k]++`, a field `G.f++`) and
another indexes an array with (directly or through a local assigned from it), with the array's size and the
largest constant it is compared with. **37 rows from 16 counters, all read** (REVIEWED, keyed by counter and
file). Bounded by the code: the lock-on ring (distinct targets only), the paged list, the customize cursor,
the Gummi kinds (160 into 192), the journal's lists, the name entry, the party models. **Bounded only by the
disc's data, no check, the PS2 the same**: the collision candidate list `D_002BD250[2048]`, renderer A's
grid lists (about 1020 cells), **renderer B's per-frame lists** (`D_0055C698`: 72 models, 78 objects, 480
part draws), **the message pointer table `D_00388480[273]`** (an event file's messages plus those the script
adds; layoutcheck does not see it) and the script's 10 trigger boxes. Two small things: with no party
model loaded, partymdl.c reads `D_003F31D0[-1]` (unused); customize's member lists 0 and 4 are empty
(a NULL `p`: crashes the host, not the PS2, if member 4 ever reaches the customize page). Against
layoutcheck `--all`'s idx-next rows: 12 of the 16 arrays are there as unbounded indexes; the message table,
the trigger boxes and the window lists (inside `D_00389C90`) and `D_003F31D0` are new. Next: count the
DATA rows' high-water marks on the real-disc run (a host-only hook, or gdb watchpoints).

### 5.1ac Session 89: the 2D layers' space, vibration, the CIRCLE / CROSS swap

Static only (Sunday 2026-10-25; the Mac is back from 2026-10-26). Only docs/ and one comment in
src/vm/vm_lib.c changed: kh1.elf byte-identical, every out/build object bit-identical, the float ELF the
same (no float-untested row).

**The 2D layers** (item 4a, renderer-spec 5.3): every 2D drawer of the main ELF (windows, text, field
text, HUD, notices, menus, the markers projected from 3D) works in 1/16 pixels of the 512 x 384 target
at `(0x7000, 0x7400)`; only the flash after the frame copy, the system-message band, the fade.c ending
and the 640-wide movie buffer are outside it. The target is 4:3 with square pixels (448 lines were only
NTSC's), so one uniform scale keeps the art. The plan: **first a 4:3 picture of about 725 x 544 (scale
1.4167) between bars**, the game unchanged and one affine map on every GIF-path draw; later, as an
option, a hor+ 3D view over 960 x 544 with the HUD anchored by a port-side table (full-screen passes
widened, markers over 3D not anchored, renderer A's grid visibility checked first so the sides do not
pop in).

**Vibration** (item 4b; src/pad/padvib*.c, padread.nostrict.c). Two players `D_005757B0[2]` (0x2C bytes:
the pattern and two channels), stepped once a frame by task 20001 (`func_00176ee0`, registered by
pppapi.c `func_00175980`). A pattern is a **type-20 record** `{type 20, flags (bit 0: loop), offset[2],
count[2]}` with, per motor, `count` pairs of bytes `{time, level}`: the first pair (time 0) sets the start
level, each later pair ramps linearly from the previous level to its own over `time` time steps
(`D_002BBDFC`: 1 a 60 Hz field, so 2 a frame at 30 fps), clamped to 0-255. **A first pair with a time
other than 0 holds its level for ever** (the step only advances the time after the first pair; every
pattern in the ELF starts with 0). At the end a looping pattern restarts, else the pad stops
(`func_00176c60`: both levels 0, the player cleared). Levels go to the pad record's bytes 2 / 3
(`D_002C5AD2[i][0]` motor 0, `[1]` motor 1); padread packs them each frame as libvib's two-actuator
profile (`D_002C5A80` = 3, one byte): **bit 0 = motor 0 on when its level >= 128** (the small motor
is on / off), **bits 1-8 = motor 1's level** (the large motor, 0-255), sent with `sceVibSetActParam`
unless the config's vibration option is off (`func_00219348`: `D_003F34B8->f10`) or bit 16 of
`D_002C5978` is set (no writer in the main ELF: an overlay or nothing), then both bytes cleared. Only pad
0 is ever started (every caller passes 0).

| Starter | Pattern |
| --- | --- |
| hitreact.nostrict.c (the player hit, reaction kinds of `func_001347f0`) | the ELF's table `D_00308870` (7 patterns, by `func_00147790`): kind 3 pattern 1, kinds 4 / 5 pattern 0, kind 6 pattern 6, kind 7 pattern 5 |
| vm_lib.c `func_001d39b0` (an event command; not while `D_0037A378` bit 0) | the event file's table (`D_00389C90.x3040 + x3060[n]`): from the disc |
| objscmd.c `func_0012b638` (an object script command) | a pointer in the script: from the disc |

The ELF's 7 patterns (`{time, level}` per motor; motor 0 on only at levels >= 128):

| # | Motor 0 (small) | Motor 1 (large) | Used |
| --- | --- | --- | --- |
| 0 | 128, ramp to 0 in 19 | 255, to 0 in 20 | hit kinds 4 / 5 |
| 1 | 132, to 0 in 10 | 255, to 0 in 10 | hit kind 3 |
| 2 | - | 150, 150 for 5 | none in the main ELF |
| 3 | 196 for 4, to 0 in 6 | 255 for 4, to 0 in 11 | none |
| 4 | 255 for 7, to 8 in 9 | 255, 196 in 6, 255 in 6, 202 in 7, 0 in 10 | none |
| 5 | 255, to 0 in 19 | - | hit kind 7 |
| 6 | 255, to 0 in 10 | - | hit kind 6 |

Stoppers (`func_00176c60(0)`): gamephase.c `func_00122330` / `func_001223b8` (phase changes),
gamestate.c `func_00109658` (the soft reset), objscmd.c `func_0012b2c0` (an object freeze, with the hit
flags) and `func_0012b658`, vm_lib.c `func_001d3a28` (an event command); `func_00176ea8` resets both at
start.

**On the Vita**: the handheld has no motors (`PlatVibSetActParam` returns 0). On a PS TV with a DualShock
3 / 4, `PlatVibSetActParam` unpacks the two bytes into `SceCtrlActuator { small = (b0 & 1) ? 255 : 0, large
= (b0 >> 1 | b1 << 7) & 0xFF }` and calls `sceCtrlSetActuator` on the external pad's port, best only when
the value changes (the game sends every frame). One gap to close in the wrapper: when the config turns
vibration off (or the bit-16 flag is set) the game stops sending, also the zero, so a motor running at that
moment would keep its last value; the wrapper sends a zero when it sees no call for a frame.

**The CIRCLE / CROSS swap** (item 4c). Every confirm and cancel in the main ELF reads the raw bits or the
action table built from them, so **swapping bits 0x2000 and 0x4000 in the live pad's bytes inside
`PlatPadRead`** (before `func_0011f548` makes press / release / repeat) moves all of it together, the way
the Western releases did: the menus' 81 raw `PAD_CROSS` cancels in 28 files (all in src/menu/; the shops and lists back out
through action 0x2, `D_002C5BB8 & 2` in shop.c and list.c), the window confirm (winmenu.c `func_001fe5a0`, the one `PAD_CIRCLE` path every menu's
`func_001fe570` uses) and config.c's own CIRCLE, the value selector's raw cross (selector.c, `press &
0x4000`) and the debug frame-step's raw circle (framectl.c `D_002C5AD0[2] & 0x2000`), and the action table
(`D_002C5990`: text advance 0x1, back 0x2, jump 0x4, the command menu's 0x10000, shortcut 1 0x80000).
Above the wrapper and so unaffected (correctly): padrec.c's replay and button script (their 0x2000 /
0x4000 are the game's confirm / cancel, recorded in the original layout) and the script's pushes of held
bits (vm_lib.c `func_001d14a0`). **What does not follow** (the screen naming a button):
- the **window font in the ELF** (`D_003E9660`, cells `D_003E9138`, decoded this session): no face-button
  icon; only **L1 / R1** (cells 8 / 9: the name entry's page arrows, nameentry.nofill.c), unaffected;
- **message text**: the button glyphs the messages use (tutorials, the help line, "press ..." prompts) are
  in the disc's message font and files, not the ELF; the swap needs a port-side remap of the circle and
  cross glyph codes at the glyph lookup (text.c / wintext.nostrict.c `func_001f94f0`'s glyph branch, the
  field text `func_0010c540`), with the codes read from the real disc;
- **HUD and menu textures** from the disc (TIM2 sheets; the command menu, the action prompt, the menu
  footers if they show buttons): the asset extraction tool writes a second, swapped sheet, or the port
  keeps a per-texture cell swap list. Both lists wait for the real-disc run (`KH1_HOST_TEXDUMP`).

### 5.1ad Session 90: the culls under a wider view, the HUD's anchor table, movies

Static only (Sunday 2026-10-25; the Mac is back from 2026-10-26). Only docs/ changed: kh1.elf
byte-identical, every out/build object bit-identical, the float ELF the same (no float-untested row).

**The culls** (item 4a, renderer-spec 5.4): no CPU cull reads the clip matrix `D_002BC020` (renderer A's
guard box); the grid, props, actors, shadows, ppp effects and the party warp all test the exact 4:3
frustum `D_002BBFA0` / `D_002BBFE0` from `func_00110618`, so a hor+ view needs one constant (the x 320)
changed there, and the markers (`func_00249580`, `D_00469F90` / `D_00469FA0`) and objwin's tail
(`func_0010b390`) need port-side bounds. The actor frustum's "drawn" bit 35 is a gameplay input (motion
of flag-`0x20000` actors, action 25, a script command, the lock-on line of sight). Lock-on has no screen
test. **The HUD** (item 4b, renderer-spec 5.3.1): every HUD part's rectangle reads from the ELF's sprite
files plus the drawer's origin; a first anchor table (Sora's gauge right / bottom, the party's right / top,
the command menu and counter left / bottom, notice and banner centre / bottom, the target's gauge left /
top: **not a marker over 3D**, corrected in 5.3). **Movies** (item 4c) below.

#### Movies on the Vita: the main ELF's side of the player (static, draft)

Read from the C (src/game/dkmovie.c, gamestate.c, vm_lib.c, framectl.c, screen/brightfade.c, objwin.nostrict.c,
movies.c, io/discfile.c, sound/snd_rpc.c, src/sdk/gcc991111/text_00260000_s2.c and text_00260000_s6_28.c) and the
ELF's data. dkmovie.x is not in the container, so everything it does is inferred from what the main ELF calls,
reads and leaves unwritten. Not checked on a console or a host run. "Guess" marks a reading with no direct evidence.

**Loading and entering the overlay.** `func_00111020(n)` stores the movie number in `D_004D9244`, clears the
loaded flag `D_002BCAE0` and queues `func_00120748("dkmovie.x" (D_0048CF30), 0x00F20000, func_00110fc8, 0)`: a
loader-thread task (`func_00120678`: `func_001204a0` looks the name up in KINGDOM.IDX and reads it, then
FlushCache(0), FlushCache(2) and the callback). The callback `func_00110fc8` sets `D_002BCAE0` = 1 and calls the
entry, `int entry(int cmd, int arg)` at the file's first byte, as `entry(0, n)`. Every other call is a wrapper in
dkmovie.c that passes a command and arg 0 (6 passes one). No function table is passed: the overlay calls the main
ELF by absolute address (136 jal, 14 j, 13 %hi/%lo pairs on the user's disc, shiftable-plan "Counts"). It loads
over whatever is at `0x00F20000`; on the title path it replaces dktitle.x, and state 0 loads dktitle.x again after.

| Wrapper | Command | Callers | Meaning (from the use; the command's work is in the overlay) |
| --- | --- | --- | --- |
| `func_00110fc8` | 0, n | the load callback | open movie n (guess: n indexes the names below) |
| `func_00111060` | 1 | gamestate.c states 12 / 17, script command 489 | start: first `func_00113e28(2)` (pause depth +1, sound `0xF`(2): pause all) and sound `0x24`(`0x7B`) |
| `func_00111090` | 2 | gamestate.c, vm_lib.c, framectl.c | status: 0 when not loaded (`D_002BCAE0` = 0), 2 ready to start, 4 ended |
| `func_001110d0` | 3 | brightfade.c `func_00106000` case 2, each frame | the frame width: 512 or 640 |
| `func_00111130` | 4 | only `func_001111b0` | close / free (guess) |
| `func_00111150` | 5 | gamestate.c states 14 / 19, the reset loop | 1 once stopped |
| `func_00111170` | 6, flags | framectl.c `func_0010f8d0` while a movie is loaded | the system-message band's flags (b0 no pad, b1 disc error, b2 read error): pause / resume (guess) |
| `func_00111190` | 7 | the band loop and the reset loop, each frozen frame | step or stop while the main loop is frozen (guess) |
| `func_001110f0` | 8 | gamestate.c states 13 / 18 | the frame count (guess from `cur >= count - 1`) |
| `func_00111110` | 9 | the same | the current frame (guess) |
| `func_001111b0` | none | only the soft reset (`func_00109658`) | the clean-up below |

`func_001111b0` (the clean-up): when in the field (`D_002BBDE0` = 3) and `D_002A3F44` = 1, `func_001017b8` (roombg.c,
reloads the room background); sound `0x24`(9); `func_00114830` (clears the pause lock `D_004D9334`); `D_002BBE04` =
3 (the next frame copy clears to black, then 0); `D_002BBE18` = 0; `entry(4, 0)`; `D_002BCAE0` = 0; `D_002BCB34` = 1
(no reader in the main ELF); `func_00113e28(0)` (resume the sound). Nothing in the normal play path calls it, so
either the overlay calls it at the end of a script movie (guess: it lives among the wrappers and checks the field
state) or a script movie never runs it. To confirm.

**Who starts a movie.**

| Path | Steps |
| --- | --- |
| Title (gamestate.c `func_00109770`) | state 11: once the transition fade ends (`D_002B6774` = 0), `D_002BBE0C` = 1 and `func_00111020(3)`; 12: status 2 then start; 13: play. State 16 / 17 / 18 do the same with `func_00111020(5)`. States 11 and 16 are requested through `func_00109558`, which no main-ELF code calls with 11 or 16: dktitle.x asks for them (inferred). |
| Event script (opcode 24, table `D_003D9FE0`) | 584 `func_001d8b98`: `func_00111020(stk)`, the number from the script; 585 `func_001d8b68`: wait for status 2; 489 `func_001d8be0`: start; 490 `func_001d8c00`: wait for status 4. A function returning 4 is taken to run again next frame (inferred from the waits). |

The names (`D_0046A058`, movies.c): 0 `opn.dat`, 1 `end.dat`, 2 `end2.dat`, 3 `demo.dat`, 4 `end3.dat`, 5 `ffx2.dat`.
If n indexes them (guess), the title plays 3 (`demo.dat`, the attract demo: any held button skips) and 5
(`ffx2.dat`, the Final Fantasy X-2 trailer: START skips), and the scripts play the opening and the three endings.
There are no `.pss` strings in the ELF. Whether the files are in KINGDOM.IMG or loose on the disc is not known.
shiftable-plan reads M1's early crash as dkmovie.x running first at boot; since state 0 loads dktitle.x first, a
boot movie would come from dktitle.x through state 11 or 16 (to confirm).

**The frame buffer.** Case 2 of the end-of-frame copy (`func_00106000(D_002BBE04)`, brightfade.c) takes the width
`v` from `entry(3, 0)`, sets the display to `v` x 448 PSMCT24 (`func_0010fee8(v, 448)`), and draws one sprite from
`TBP0 0x1180` (`0x118000`, `TBW v / 64`, PSMCT24, TW 9 or 10, TH 9) to the display buffer at 0, `v` x 448, 1:1 (no
stretch, unlike cases 0/1/3/4's 384 to 448). Then, while `D_002A6B80` != 0, the `0x80FEFEFE` quad over the display
(renderer-spec 3.1). `0x118000` is `640 x 448 x 4` bytes: the buffer sits right after a 640-wide display buffer
and covers the 3D target at `0x1A0000` (unused while a movie plays). **No main-ELF code stores 2 to `D_002BBE04`**
(renderer-spec 4.15), and nothing in the main ELF writes the pixels: the overlay uploads the decoded frames there
and selects case 2 (inferred). `D_002B73E0` is a 2-quadword packet that sets `FRAME_1` = `0x010A008C` (FBP `0x8C`,
640 wide, PSMCT24); objwin.nostrict.c `func_0010b6c0` sends it instead of `D_002B73B0` (`FRAME_1` = the 3D target)
while `D_002BBE18` != 0, which only the overlay can set (the main ELF stores 0 only). So something the game draws
can be put into the movie picture (guess: subtitles or credits over a movie; which, unknown).

**Pacing.** The title path sets `D_002BBE0C` = 1, so the main loop runs at 30 frames a second (two fields per
`func_001104e0`), and each frame only polls (commands 2, 8, 9, 3) and copies. Nothing in the main loop steps the
decoder, so the overlay decodes on its own thread or from interrupts (guess). The main ELF installs no IPU DMA
handler (only channels 1, 2 and 5). The field parity `D_002BBDE8` has no reader in the main ELF (maybe the
overlay's, guess). At the last frame (`cur >= count - 1`) the title states set `D_002A6B80` = 1.

**Skipping and the end.** State 13 skips while any pad 0 button is held (`D_002C5AD4`, record +4), state 18 on a
START press (`D_002C5AD8 & 8`). A skip does not call the overlay: it sets `D_002A6B80` = 1, `D_002BBE04` = 3,
`D_002BBE18` = 0, resets the display (`func_0010ff60(254)`), then states 14 / 19 wait for `entry(5)` = 1 and go to
state 0. So the overlay notices the skip itself (guess: from `D_002BBDE0` or `D_002BBE04`). Status 4 ends a movie
normally (state 0 again, or the script goes on). The script commands check no button: a skip of the opening or an
ending, if any, is the overlay's. The soft reset (`func_00109658`, `D_002BCA00 & 0xF09`) loops `func_001220d0`,
`entry(7)` and a frame end until `entry(5)` = 1, then `func_001111b0`.

**Main-ELF code that only the overlay can use** (linked, never called by the main ELF):
- `func_00111238`, a stub nothing calls, that calls `sceCdRead`(0, 0, 0, 0), `func_0024b138` (decode.c, the packed
  block unpacker; no other caller), `sceCdStatus`, `sceCdBreak`, `sceCdGetError`, `sceIpuInit`, `sceIpuSync` with no
  arguments: it keeps them linked (portability.md). So `sceIpuInit` / `sceIpuSync` are never called for real.
- libipu (`PsIIlibipu 2500` at `0x46E0A0`): `func_002723c8` / `func_00272430` (fromIPU / toIPU CHCR through
  D_ENABLEW), `func_00272498` (stop both channels and save the state: `sceIpuStopDMA`, guess), `func_00272580`
  (restore it: `sceIpuRestartDMA`, guess), `func_00272738`, the IQ / VQ tables `D_0046E0B0` / `D_0046E100`. There is
  no libmpeg (`sceMpeg*`) in the main ELF: the demuxer and the MPEG-2 decode loop are in dkmovie.x (inferred).
- movies.c's six functions: `func_0024b9a8(i)` the name, `func_0024b9c0` / `func_0024b9e0` the chosen value
  `D_00669A38`, `func_0024b9d0` / `func_0024b9f0` `D_00669A3C`, `func_0024ba00` (store and keep `sceCdGetError`).
- Sound commands with no main-ELF sender (sound-spec 3): 1 (`func_001ed0d0`), `0x16`-`0x19`, `0x1B`, `0x1D`
  (`func_001ed870` ... `func_001eda38`), `0x32` (`func_001eda90`), `0x1F`-`0x22` (`func_001ec9a8` ... `func_001ecab0`);
  some may feed the movie's audio to the IOP (guess). `0x24` is sent with `0x7B` before and 9 after.
- DMA: IPU channels 3 (fromIPU `0x1000B000`) and 4 (toIPU `0x1000B400`) appear only in libipu; the frame upload to
  `0x118000` would go by GIF (channel 2) or PATH3 (guess).

**The port's interface.** Keep every main-ELF function above unchanged and replace dkmovie.x with a host file
(`host/movie.c`) that implements the same `entry(cmd, arg)` on a small platform layer, so no game code learns
about the Vita:

| Call | Covers | Vita side |
| --- | --- | --- |
| `PlatMovieOpen(name, &info)` | command 0 (the name from `func_0024b9a8(n)`), 3 (`info.width`), 8 (`info.frames`) | open the extracted file; 0 width means missing: report status 4 at once |
| `PlatMovieFrame(&tex)` | 1 starts, 2 / 9 poll, the case 2 copy | the newest decoded frame (YUV planes) and its number; the renderer draws it 4:3 in place of the `0x118000` copy (`D_002BBE04` = 2) |
| `PlatMovieAudio(paused)` | 6 and the sound pause `0xF` | the movie's PCM into the mixer as its own voice; paused while the band shows |
| `PlatMovieSkip()` | the title skips, 7 / 5 | stop decoding; status 4, `entry(5)` = 1 |
| `PlatMovieClose()` | 4, `func_001111b0` | free the decoder and the texture |

On the Vita, either (a) the asset extraction tool re-encodes each movie from the user's own disc to H.264 + AAC
MP4 with the user's host ffmpeg (never shipped) and `sceAvPlayer` plays it in hardware (it outputs YUV420 frames
and 48 kHz PCM); or (b) the port decodes the original MPEG-2 in software (libmpeg2 is GPL-2.0+, libavcodec's
MPEG-2 decoder LGPL-2.1+; 640 x 448 at 30 frames a second on the Vita's four A9 cores is plausible, untested). The
licence question (section 6) stays open; (a) keeps the decoder out of the repo. Either way the PSS audio
format (SPU ADPCM or PCM, interleave) must be read from a file first.

**To confirm from dkmovie.x** (inventory.py on the user's Mac): which of the functions above it calls; what each
command does and returns (0-9); that it stores 2 to `D_002BBE04` and non-zero to `D_002BBE18`, and with what;
whether n indexes `D_0046A058`, and how the file is found (KINGDOM.IDX through `func_00120190`, `sceCdSearchFile`, the
HDD path) and read (`sceCdRead` streaming); its threads, IPU DMA handlers and timer (vsync, `D_002BBDE8`?); the
audio path (which sound commands, what `0x24`(`0x7B`) means); how it sees a title skip and whether it calls
`func_001111b0`; the frame size, rate and count read from the files themselves.

### 5.1ae Session 91: the drawn rectangles, the camera matrices in C, the wide switch

Static and host only (Sunday 2026-10-25; the Mac is back from 2026-10-26). kh1.elf byte-identical, **every
out/build object bit-identical** (objwin.nostrict.c's 0 / 512 became `PLAT_VIEW_X0` / `PLAT_VIEW_X1`, the same
literals on the PS2), the float ELF the same (no float-untested row). selftest PASS; abicheck, relcheck,
walkcheck and countcheck 0; indcheck as before (241 rows: 117 OK, 42 READ, 70 OVERLAY, 12 CLANG-READ).

- **`gsstate.py --extents`** (item 4a, renderer-spec 5.3.1): host/null/gsregs.c keeps each draw state's vertex
  extent less `XYOFFSET` (`KH1GsDraw.x0 .. y1`), dmawalk.c prints it on the draw lines (`, xy X0 Y0 X1 Y1`), and
  gsstate.py lists the rectangle per send in target pixels, a send from the HUD's staging buffer `D_00351E10`
  keyed by the environment sent before it (`D_00651C00 ch2 > D_00351E10 ch2`), with 5.3's anchor. Fake disc:
  the clear, the frame copy and the flash, all full screen. gsregs_test.c +1 check.
- **The camera matrices in C** (item 4b, renderer-spec 5.4): host/port/view.c is `func_00110618` for every
  port (the session 12 draft's maths in the SDK's two forms), linked on the host in place of the draft
  (census.py `HOST_TWINS`). **`tools/host/viewcheck.py`** (new) runs the original function's code from the
  user's ELF in an interpreter and compares: **bit-identical** with IEEE rounding on 13 argument sets (2 ulp
  at most with the EE's round-toward-zero). **`KH1_HOST_WIDE=W:H`** (`1` = 960:544): `kh1_view_init` scales the
  320 by `(W / H) / (4 / 3)` (only the two frustums' x scale change), widens the markers' bounds to
  1709.2 .. 2386.8 and objwin's to -82 .. 594 (include/platform/view.h, new: the visible x range wrapper).
- **No other frustum in the main ELF** (item 4c): journal, party menu, objwin, shadow and the lens grid build
  view -> screen matrices only; `D_002BC140` / `D_002BC144` are the effects' and sound listener's camera
  pointers (the Gummi overlay sets them through `func_001bb858`, no main-ELF caller).
- **Bit 35's readers** (item 4d): the plan for the disc (renderer-spec 5.4): records' `flags & 0x20000` in the
  room object lists after `func_00132c70`; the object-script halfword `0xA30B` (table 0 entry 163,
  `func_0012a030`). objcmd2.c's comment on the `0x40000000` flag corrected (the result is pushed back; not a
  float flag).

### 5.1af Session 92: the HUD's anchors in the GIF path, the full-screen passes in C

Static and host only (Sunday 2026-10-25; the Mac is back from 2026-10-26). kh1.elf byte-identical, **all 677
out/build objects bit-identical** (the new `include/platform/view.h` macros fold to the original's literals on
the PS2), the shift M0 check as before, so the float ELF is the same (no float-untested row). selftest PASS
(with viewcheck); abicheck, relcheck, walkcheck, countcheck and layoutcheck 0; indcheck as before (241 rows:
117 OK, 42 READ, 70 OVERLAY, 12 CLANG-READ).

- **The HUD anchor table as port data** (item 4a, renderer-spec 5.4 "Session 92"): `include/platform/hudanchor.h`,
  `host/port/hudanchor.c` (each HUD part's drawing environment and side; markers are not in it). Under
  `KH1_HOST_WIDE` the null platform's chain walk shifts every XYZ X of a listed environment's send and of the
  staging sends (`D_00351E10`) after it by the view's margin (`kh1_dma_hud_anchors`, `kh1_gs_xshift`), so
  `gsstate.py --extents` shows the moved rectangles. gsregs_test.c +5 checks. A renderer must also read the
  HUD environment's full-canvas `SCISSOR_1` as the whole view.
- **The full-screen passes** (item 4b): the menu blur, spin, sway, depth blur, the post-copy flash and
  opdma's full-width band build their x from `PLAT_VIEW_W` / `PLAT_VIEW_GX0` / `PLAT_VIEW_GX1` (512 / `0x7000` /
  `0x9000` on the PS2); the static packets (clear, frame copy, fade, letterbox, the copies into the Z area,
  the spin's copy, the scissor columns) are listed for the renderer's stretch.
- **viewcheck in the self-test** (item 4c): tests/selftest.sh runs `viewcheck.py --round nearest` when the
  ELF is in the repo root and requires 0 ulp; it prints "viewcheck skipped" without it (CI's public runs).
- **Waiting for the Mac** (item 4d): `KH1_HOST_DMAC=defer` as the default (the room run's `--nodes` with it
  first) and argcheck's 3 value uses (dktitle.x's calls).

### 5.1ag Session 93: the full-screen packets' stretch, the HUD table check, the canvas map

Static and host only (Sunday 2026-10-25, the Mac away until 2026-10-26). **No change under src/**: kh1.elf
byte-identical, the float ELF the same (no float-untested row). selftest PASS (with viewcheck, hudcheck and
the new canvas_test); abicheck, relcheck, walkcheck, countcheck and layoutcheck as before.

- **The static full-screen packets' stretch** (item 4a, renderer-spec 5.4 "Session 93"):
  `include/platform/fullscreen.h` + `host/port/fullscreen.c` (nine sends: clear, frame copy, fade, letterbox,
  the copy into the Z area, the spin's copy and strip, the menu capture and the display clear `D_002BC980`,
  new to the list) with X / u / capture-X flags; under `KH1_HOST_WIDE` the chain walk stretches them to the
  view (`kh1_dma_fullscreen`, `kh1_gs_xstretch`), and the scissor rule (the full 4:3 canvas or the display's,
  and the 16 columns) reads as the view's (`kh1_gs_view`, a draw line's `, view scissor`). The fake disc's
  clear, display clear and frame copy draw -82.8 .. 594.8 wide. gsregs_test.c +17 checks.
- **The table check** (item 4b): `tools/host/hudcheck.py` (no build): every environment src/hud builds or sends
  is in `kh1_hud_anchors[]` or `kh1_hud_markers[]` (new in hudanchor.c), no stale rows; in the self-test,
  with a negative case. 17 HUD environments: 11 anchored, 6 markers.
- **The canvas map** (item 4c): `include/platform/canvas.h` + `host/port/canvas.c`: `kh1_canvas_fit` (scale,
  pillarbox / letterbox offsets, the view in canvas sixteenths), `kh1_canvas_map`, the stretch and the scissor
  rule as pure functions for the renderer; tests/host/canvas_test.c (25 checks).
- **Still waiting for the Mac** (item 4d): `KH1_HOST_DMAC=defer` as the default (the room run's `--nodes` with
  it first) and argcheck's 3 value uses (dktitle.x's calls).

### 5.1ah Session 94: the lens grid under the wide view, a host present, the staging-send check

Static and host only (Sunday 2026-10-25, the Mac away until 2026-10-26). One change under src/ (sceneeff.c's
lens grid reads `PLAT_VIEW_SIDE`, `0.0f` on the PS2): **all 677 out/build objects bit-identical**, kh1.elf
byte-identical, the m12 float ELF the same bytes with and without the change (no float-untested row).
selftest PASS (with the new present_test and hudcheck's second negative case); abicheck, relcheck, walkcheck,
countcheck, dmacheck, abscheck and layoutcheck 0, indcheck as before.

- **The lens grid under the wide view** (item 4a, renderer-spec 5.4 "Session 94"): its ST (u 0.125 .. 0.875
  of TW 512, texels 64 .. 448 of the 4:3 canvas) now take the view's margin, `(64 + PLAT_VIEW_SIDE) / 512`
  (`include/platform/view.h`: `256 (wide - 1)`, unrounded, as the stretch; 0 on the PS2, folded), because
  the copy into the Z area it samples starts at the view's left edge; and `D_002A6110`'s `CLAMP_1`
  REGION_CLAMP MAXU 510 grows by the view's added width (676 at 960 x 544) through a new fullscreen.c row and
  flag `KH1_FS_CLAMP` (`kh1_canvas_stretch_clamp`, applied by gsregs.c in a listed send). The mesh and its
  view -> screen matrix stay: the bulge stays the centre square, the sides keep the scene.
- **A host present** (item 4b): `KH1_HOST_SHOT=W:H[:target][:DIR]` (host/null/present.c, `kh1_present_rgb`):
  after each frame copy (`D_002A6890`) the GS memory model's display (the copy's FRAME: FBP 0, CT24, 448
  lines) or the 3D target (its TEX0: 0x1A00) as a W x H PAM `DIR/shot_N.pam`, through `kh1_canvas_unmap`
  (new, the inverse of the canvas map), point-sampled, pillarboxed, the 448 display lines as the canvas's
  384. It turns the chain walk on (the model's only feed) through a new hook `kh1_dma_after_send`. **The
  model draws no 3D, no untextured pass and no copy of a render target**, so the fake disc's 38 frames in 40
  are black; it is for the real-disc run (what the uploads and the point-sampled sprites leave) and for a
  renderer's bring-up to compare against. Under `KH1_HOST_WIDE` the view's sides stay black (the model's
  buffers are 512 wide). tests/host/present_test.c (12 checks: centre, canvas edge, bars, the display's row
  scale, the target, the hook writing a file).
- **The staging-send check** (item 4c): `tools/host/hudcheck.py` also finds each staging send in src/hud
  (`func_00237018(D_x, D_y - D_x, 1)`, and gauge.nostrict.c's `*bp`) and the environment sends that reach it
  (before it in its function, or before the call in a caller, up to 6 callers up), and fails on a staging
  send under none or under environments with different sides. **22 staging sends, each under its own
  part's environment, 0 problems** (the gauges' five through `func_002416a8`, the damage numbers through
  `func_00245da0`, the labels through `func_00247190`, the minigame timer's two through `func_00248380`).
  The self-test removes the timer's environment send in a copy of src/hud and expects the failure.
  `src/gfx/prim.c`'s staging send (`D_00648070`) is outside src/hud and not checked.
- **Still waiting for the Mac** (item 4d): `KH1_HOST_DMAC=defer` as the default and argcheck's 3 value uses.

### 5.1ai Session 95: one margin in sixteenths, the flat sprites in the present, prim.c's send

Static and host only (Sunday 2026-10-25, the Mac away until 2026-10-26). One change under src/ (sceneeff.c's
spin and sway read `PLAT_VIEW_W16`, 8192 on the PS2): **all 677 out/build objects bit-identical**, kh1.elf
byte-identical, the m12 float ELF the same bytes (no float-untested row). selftest PASS (canvas_test 57
checks, gsmem_test and present_test grown, hudcheck's third negative case); abicheck, relcheck, walkcheck,
countcheck, dmacheck, abscheck and layoutcheck 0, indcheck as before.

- **The view's margin, one convention** (item 4a, renderer-spec 5.4 "Session 95"): `kh1_view_side16`,
  rounded once in `kh1_view_init` (1325 sixteenths = 82.8125 px at 960 x 544), replaces `kh1_view_x0 / x1`
  (which truncated to -82 / 594); `PLAT_VIEW_GX0 / GX1 / W16 / X0 / X1 / SIDE` and the markers' bounds are
  exact in it, and the null platform's HUD shift / stretch / scissor rule take it directly, so the C passes
  and the stretched static packets meet on the same sixteenth. canvas_test checks view.c against
  `kh1_canvas_fit` at six screen sizes.
- **The model's flat sprites** (item 4b): `kh1_gsmem_flat_sprite` (host/null/gsmem.c) fills untextured
  SPRITEs (clears, display clear, fade, letterbox) into the model for `KH1_HOST_SHOT`, switched on by the
  present only, without marking pages or moving the trace's counters: the fake disc's `--draws / --targets /
  --uploads / --sends` are identical with the shot on. The fake disc's frames stay black (clear colour 0).
- **prim.c's staging send** (item 4c): 3D lines (kind 1 nodes projected through the caller's matrix), not a
  HUD part, and with no main-ELF caller, like prim.nostrict(_nofill).c's other three senders: an overlay's.
  hudcheck.py now fails on a staging send outside src/hud that its `OTHER_STAGES` does not name.
- **Still waiting for the Mac** (item 4d): `KH1_HOST_DMAC=defer` as the default (it needs the real-disc
  room run to show the same `--nodes` order), argcheck's 3 value uses (dktitle.x's calls into the main ELF),
  and now the callers of prim.c's four senders (dktitle.x / the other overlays).

### 5.1aj Session 96: the frame copy in the present, the counts' high-water marks

Static and host only (Sunday 2026-10-25, the Mac away until 2026-10-26). **No change under src/** (kh1.elf
byte-identical, the float ELF the same, no float-untested row). selftest PASS (gsmem_test +5 checks, the new
counts_test).

- **The frame copy in the present** (item 4a, renderer-spec 5.4 "Session 96"): host/null/gsmem.c's
  `kh1_gsmem_flat_sprite` also draws a textured SPRITE the exact model refused (the frame copy `D_002A6890`:
  the 3D target as a 512 x 512 bilinear texture), point-sampled, under the present's switch only and with
  session 95's no-mark, no-counter rule (`tex_sprites` / `tex_pixels`), so the display shot shows what the
  model holds in the target. Fake disc: `--draws / --targets / --uploads / --sends` identical with
  `KH1_HOST_SHOT`. `texel_rgba` / `tex_ok` factored out of `kh1_gsmem_read_tex` (the same reads).
- **`KH1_HOST_COUNTS=1`** (item 4b, host/null/counts.c): the high-water marks of countcheck.py's DATA rows,
  sampled at each vblank, each `PlatDmaSend` and each `PlatGsListEnd` (where the frame's lists are full) and
  printed at the run's end (main.c's summary, also after a crash) against each array's size, "OVER" past it:
  renderer B's `D_0055C698.x4 / .x8 / .xc` (78 / 480 / 72), the collision candidates `D_002C12C4` (2048; reset
  per query, so a sample sees what the last query left: a lower bound), the message pointers `D_00389C80`
  (273), renderer A's grid count `D_0029B2FC` (about 1020), the trigger boxes `D_00389C90.nbox` (10) and the
  eight window templates' `D_00389C90.cnt[k]` (256). Reads only. Fake disc: all 0 (no room loads). For the
  real-disc run (next-session item 2) instead of gdb watchpoints; a true per-query collision peak would need
  a hook inside mapcoll.c's queries (not done: src/ unchanged).
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1ak Session 97: the frame copy walked, the wide view's shots

Static and host only (Sunday 2026-10-25, the Mac away until 2026-10-26). **No change under src/** (kh1.elf
byte-identical, the float ELF the same, no float-untested row). selftest PASS (present_test 22 -> 30 checks).

- **present_test through the copy** (item 4a): the frame copy's packet shape, read from the ELF's
  `D_002A65D0` (renderer-spec 5.4 "Session 97": 6 x A+D, two REGLISTs, 16 strips, v 0 .. 384 over the
  display's 448 lines), built in the test and walked by the chain walk under a made-up target: the display
  shot shows the target's colours at the canvas map's pixels.
- **The shots under `KH1_HOST_WIDE`** (item 4b): the stretched copy reads u from the view's left edge, so the
  model's 512-wide display holds canvas x d + margin at pixel d (a finding: the session 96 display shot was
  shifted by 82.8 px under the wide view). `kh1_present_wide` (host/null/present.c, set from main.c): the
  display shot is read back by the margin (canvas margin .. 512 shown), the target shot is unchanged with
  black sides, and both shot lines say so. Renderer-spec 5.4 writes down what a renderer draws in the sides
  (its own wide 3D target, not the copy).
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1al Session 98: the other copies walked, the stored frame's row

Static and host only (Sunday 2026-10-25, the Mac away until 2026-10-26). **No change under src/** (kh1.elf
byte-identical, the float ELF the same, no float-untested row). selftest PASS (present_test 30 -> 46 checks).

- **The other copies' shapes** (item 4a): the copy into the Z area `D_002A5FD0`, the spin copy `D_002A4ED0`
  and the spin strip `D_002A4FC0` read from the ELF (renderer-spec 5.4 "Session 98": v ranges, CLAMP,
  SCISSOR). The two sprite copies are built in present_test and walked at 4:3 and under the wide stretch:
  each lands where fullscreen.c's row says for a view-wide renderer; in the 512-wide model the Z-area copy
  shows the frame copy's margin shift and the spin copy shows it twice (it reads the shifted display). The
  Z-area copy never writes the Z area's last column and row (x -1.5 .. 510.5). The stretch scales the
  copies' sub-texel offsets (0.5 / 1.5 / 1 -> 0.66 / 1.99 / 1.32), a third of a texel at most.
- **Correction**: the frame copy's PRIM `0x116` is SPRITE|TME|FST, not ABE (session 97's note): the copy is
  opaque. present_test's packet now matches.
- **The fake-disc wide run** (item 4b): the frame copy's 80 strips, the clear and the display clear at
  -82.8 .. 594.8 with the view's scissor. **A missed full-screen send**: capture.c's `D_002B66B0` (the stored
  frame drawn back over the target as it fades) stayed at 0 .. 512; host/port/fullscreen.c has its row now
  (X and u) and the rerun shows it at the view's width.
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1am Session 99: every full-screen send checked, the model's copies on one canvas

Static and host only (Sunday 2026-10-25, the Mac away until 2026-10-26). Three changes under src/, all off
the PS2 or folding to the original's literal: **all 677 out/build objects bit-identical**, kh1.elf
byte-identical, the float ELF the same (no float-untested row). selftest PASS (present_test 46 -> 47
checks, fscheck with two negative cases).

- **tools/host/fscheck.py** (item 4a, renderer-spec 5.4 "Session 99"): every send through `func_00106b18`
  (37) walked from the ELF; the 21 full-screen ones (a sprite or a column set over the canvas, or a
  half-size capture) checked against host/port/fullscreen.c and the C's writes of their XYZ words. It found
  **8 sends with no row** (the stored frame cross-fade `D_002B65E0`, the menu blur's empty-capture
  `D_002A4DD0` and copies `D_002A4B60`, the depth blur's capture `D_002A5A90`, mask `D_002A5620` and copies
  `D_002A5AC0`, the shaped wipe's `D_002A6A40` / `D_002A6AA0`) and **3 passes left partly 4:3 in C**: the
  menu blur's first copy and the depth blur's alpha fill and capture had their corners in data (now written
  with the view's edges under `#ifndef KH1_PS2`, sceneeff.c / sceneeff.nostrict.c), and brightfade.c's
  colour over the target used `0x7000 / 0x9000` literals (now `PLAT_VIEW_GX0 / GX1`). 19 rows, 3 exempt (the
  movie buffer's copy, the system-message band), 0 problems; in the self-test when the ELF is present.
- **`KH1_FS_UOWN`** (include/platform/fullscreen.h): the blurs' copies read a capture of their own; the
  renderer's stretch is the same, the host model's read-back (below) skips them.
- **The model's copies on one canvas** (item 4b, host only): gsregs.c passes the view's x0 as `uorg` to the
  GS memory model for a stretched copy of a buffer laid out like the target, so the 512-wide model's display
  holds canvas d at pixel d and the spin copy no longer counts the margin twice (present_test: display, Z
  area, spin; a `KH1_FS_UOWN` copy not read back). The registers and the trace keep the renderer's u. The
  present's display shot is no longer shifted (both shots canvas 0 .. 512, the sides black).
- **A port rule for the capture** (renderer-spec 5.4 "Session 99"): `func_0010a3e8`'s 0x24000-byte block
  and `func_00102a48`'s 0x9000-word empty-capture scan are the game's sizes (256 x 192 x 3); a port keeps
  that main-memory copy and scales its own texture to and from it.
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders; and now **a real-disc wide run's `--extents`**: the menu (its blur),
  an event with the depth blur, a world change (the cross-fade `D_002B65E0`) and the shaped wipe should
  each show its full-screen sends at -82.8 .. 594.8 (the captures at the view's half).

### 5.1an Session 100: the other GIF paths' full-screen draws, the captures' `PlatGs` contract

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). One change under src/ (menubg.nostrict.c,
folding to the original's literals): **all 677 out/build objects bit-identical**, kh1.elf byte-identical,
so the m12 float ELF is the same bytes (no float-untested row). selftest PASS (fscheck: two more negative
cases), the host links (570 objects).

- **The draws that are not `func_00106b18` sends** (item 4a, renderer-spec 5.4 "Session 100"): fscheck.py
  also walks the static chains sent through `sceDmaSend`, `func_00237018` and frame.c's `func_001e05a8`,
  and scans src/ for rectangles built in C with both 4:3 edges. Found: **the menu backdrop's four
  full-screen gradients** (menubg.nostrict.c, now `PLAT_VIEW_GX0 / GX1`: the sides show the backdrop) and
  **the stored frame's three path-2 sends** (`D_003DAE30`, `D_003DAF60`, `D_003DB050`: now
  host/port/fullscreen.c rows `KH1_FS_X | KH1_FS_U`; the zoom's corners from C stay in canvas units and the
  row's linear stretch carries them). The menus' full-width rules, the wave band and the staging sends have
  reasons, not rows. `gs_packets.callers` drops a stale argument address and finds a delay-slot one.
  58 sends, 24 full-screen, 22 rows, 3 exempt, 0 problems.
- **The captures' contract** (item 4b, below).
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders, and the wide run's `--extents` (now also the stored frame's three
  sends at -82.8 .. 594.8 in a scene that uses vm_lib's screen effects, and the menu's backdrop).

#### The image transfers from GS memory to main memory, for a port's `PlatGs*`

On the PS2 `PlatGsSetDefStoreImage(sp, sbp, sbw, psm, x, y, w, h)` + `PlatGsExecStoreImage(sp, dst)` copy
a rectangle of GS memory into main memory, and `PlatGsSetDefLoadImage` / `PlatGsExecLoadImage` copy it
back. A port has no GS memory: its `PlatGs*` see the block address and PSM, and map them to its own
buffers. **The rule: main memory always gets the PS2's format and size**, because game code reads and
writes those bytes on the CPU (below); the port's store resamples its own buffer into that shape, and its
load resamples the shape back into its own buffer. Every store in src/ (the loads are the same rectangles
backwards):

| Store (who) | GS source | PSM, rectangle | Into main memory | Read on the CPU by | Loaded back |
| --- | --- | --- | --- | --- | --- |
| capture.c `func_00109d98`, screen.c `func_001e1480` | the 3D target, block `0x1A00`, FBW 8 | CT24 (1), 0, 0, 512 x 384 | `D_00F20000`: **512 x 384 x 3 = 0x90000 bytes, 0x600 a row** | screen.nofill.c's ripple `func_001e1838` (64 x 48 about the centre) and edge filter `func_001e1c20` (rows +-512), screen.c's grey tint `func_001e15a0` (every pixel, `p[2] = p[0] = p[1]`), frame.c's `func_001e06c8(line)` (`+ line x 0x600`: a vertical scroll) | into the Z area as two 512 x 192 halves (`0x0E00`, `0x1400`; `+ 0x48000`): capture.c `func_00109cd0`, frame.c `func_001e0608` / `func_001e06c8`, screen.c `func_001e14e0`; drawn by `D_002B65E0` / `D_003DAE30` / `D_003DAF60` / `D_003DB050` (rows `X \| U`) |
| capture.c `func_0010a058` | the target `0x1A00` | CT24, 512 x 384 | a block from `func_001559f0(62, 2)` (`D_002B677C`), 0x90000 bytes | (none found) | `func_00109f88`, the two halves into the Z area; drawn by `D_002B66B0` (row `X \| U`) |
| capture.c `func_0010a3e8` (after the half-size copy `D_002B6760`) | the capture, block `0x3600`, FBW 4 | CT24, 256 x 192 | `func_00121e28(0x24000)` (`D_002B6778`): **256 x 192 x 3 = 0x24000 bytes** | sceneeff.c `func_00102a48`: the first 0x9000 words scanned for a non-zero (all zero = "no capture", then `D_002A4DD0`) | `func_0010a470`, 256 x 192 back to `0x3600`; drawn by the menu blur `D_002A4B60` (`U \| UOWN`) |
| kelnscls.nostrict.c (the lens flare's occlusion, `pppKeLns*`) | **the Z buffer**, block `zbp << 5`, the frame's FBW | **PSMZ24 (0x31)**, the light's screen box clamped to the scissor, w rounded up to 8, h to 4 | `func_001aa950(0x3060)` + 96 (the scratch stack) | counts the pixels whose 24-bit depth (3 bytes, little-endian) is under the light's; the ratio dims the flare | no |
| menubg.c `func_0020a8f0` | **the display**, block 0, FBW 8 | CT32 (0), 16 x 1 at (256, 4) and at (256, 443) | a stack buffer | the first pixel of each: `D_003F34B0[0] / [1]`, the backdrop gradient's top / bottom colours (the menu takes its colours from the screen behind it) | no |

What a port's `PlatGs*` do with each (the GS block and PSM tell them apart):

1. **The target, 512 x 384 CT24** (block `0x1A00`). The port's 3D target is the view's size (960 x 544
   at k = 1.3235; its canvas is 677.6 x 384 target pixels). The store **resamples the whole view into 512
   x 384** (a horizontal squeeze by k, rows unchanged; RGB, no alpha byte), so the CPU effects keep their
   sizes and offsets: the ripple and the edge filter then act on the squeezed picture (a ripple drawn
   1.32 times wider once unsqueezed, accepted), the tint is per pixel, the scroll per row. The load of
   either 512 x 192 half into `0x0E00 / 0x1400` **stretches it back into a view-wide texture** that the
   port keeps as "the Z area's picture"; the draws read it with the rows' `KH1_FS_U` (u 0 .. 512 -> 0 ..
   the view's width), which lines the picture up with the view again. Doing it as one 512 x 384 image is
   fine: the halves are the PS2's transfer size limit, nothing reads between them.
2. **A picture from the disc into the Z area** (frame.c `func_001e07a8`: `D_003DABD0[1] + line x 0x600`,
   the same two halves). It is 4:3 art, not a squeezed view: **the port's load places it in the canvas's
   4:3 rectangle of the texture, the sides black** (the row's stretch then draws it at its own aspect,
   pillarboxed). The load tells the two apart by the source: an address the port's own store filled
   (`D_00F20000`, `D_002B677C`'s block, between the store and the next write to it) is a squeezed view;
   anything else is 4:3. A simpler first version: always treat the loads into `0x0E00 / 0x1400` from
   `D_00F20000` / `D_002B677C`'s block as squeezed, every other source as 4:3.
3. **The half-size capture, 256 x 192 CT24** (block `0x3600`). The port's capture texture is the view's
   half (338.8 x 192 canvas pixels at 960 x 544, `D_002B6760`'s `KH1_FS_XS`). The store squeezes it to
   256 x 192 x 3 (session 99's rule), so the 0x24000 block and the 0x9000-word empty test keep their
   meaning (an all-black capture is still all zero bytes); the load stretches it back into the capture
   texture, which the blur reads with `KH1_FS_UOWN`.
4. **The Z buffer, PSMZ24** (the lens flare). The rectangle is in the target's pixels (`ox / oy` from the
   light's projected XYZ minus XYOFFSET, clamped to `SCISSOR_1`), so in a port it is in **view** pixels
   once the scissor is the view's (5.4 "Session 92"): the store returns the port's depth for that
   rectangle, **converted to the PS2's 24-bit integer Z** (the game compares it with `v[2] >> 4`, the
   light's own Z from the same projection) as 3 bytes a pixel, `w8` to a row. The Vita's GXM cannot read
   its depth buffer back cheaply: a port can (a) resolve depth to a small colour target over that box only,
   or (b) answer with an occlusion query and return all-visible / all-hidden bytes in the shape the loop
   reads (the flare then dims in steps, not smoothly). The box is `bC0` x `bC1` pixels about the light
   (`r = v -+ bC0 x 8` sixteenths; u8s, so at most 255 x 255; `pppKeLnsLpTDraw` sets them from its key as
   `e << 3` / `f << 2`, if those are the same fields: read a flare's record before choosing). *Session 101 (5.1ao): they are the same fields; the box is at most 4096 pixels by the scratch's size.*
5. **The display, CT32, 16 x 1** (menubg). The display in a port is the presented view. The two rows are
   display lines 4 and 443 (the 448-line display; the target's 3 and 380 after the copy's 384 -> 448
   stretch) at **canvas x 256, the view's centre**: the port maps canvas x 256 to its own centre column and
   the display line l to its row `l x 384 / 448` of the target, and returns 16 CT32 pixels (only the first
   is read; its alpha byte is masked off). A port that never keeps the presented frame can read its target
   at the same place before the frame copy (the menu opens over the last frame either way).

Nothing above changes the PS2 build: these are the port's `PlatGs*` (vita-port-plan 5, step 3); the host's
null platform keeps its GS memory model, where the shapes are the PS2's already.

### 5.1ao Session 101: 5.1an's contract in the null platform, the full-width rules, the lens flare's box

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). One change under src/, inside `#ifndef KH1_PS2`
(winpart.nostrict.c): **all 677 out/build objects bit-identical**, kh1.elf byte-identical, so the m12 float ELF
is the same bytes (no float-untested row). selftest PASS (gsimage_test: 17 checks), the host links (571 objects).

- **The image transfers on the null platform** (item 4a): `PlatGsSetDefLoadImage` / `PlatGsExecLoadImage` /
  `PlatGsSetDefStoreImage` / `PlatGsExecStoreImage` were stubs that did nothing; they are now
  **host/null/gsimage.c**. The SetDef calls fill libgraph's packets (sceGsLoadImage 0x60 bytes: A+D tag,
  BITBLTBUF, TRXPOS, TRXREG, TRXDIR 0, the IMAGE tag; sceGsStoreImage 0x70: 4 VIF codes, A+D tag,
  BITBLTBUF's source half, TRXPOS, TRXREG, FINISH, TRXDIR 1; every caller's buffer is at least that: `s32
  sp[28]`, `GsImagePacket` 14 u64s, kelnscls's 0x70-byte `GsStoreImage`). A load is an upload into gsmem.c's
  model (TRXDIR 0 then the bytes as IMAGE words, counted and logged like a GIF one; only while
  `KH1_HOST_TRACE >= 2` feeds the model, as before). A store copies the rectangle out of the model **in the
  PS2's packed shape** (CT32 / Z32 4 bytes, CT24 / Z24 3, CT16 2, T8 1, T4 a nibble; rows `w` pixels apart),
  whatever the view: the null platform keeps the PS2's GS memory, so the shapes 5.1an names hold by
  construction. **tests/host/gsimage_test.c** asserts them under the 960:544 view (`kh1_gs_view(-1325,
  10842)`) and under 4:3: the target `0x1A00` 512 x 384 CT24 is exactly 0x90000 bytes, 0x600 a row, RGB
  without the alpha byte; the two 512 x 192 halves load back into `0x0E00 / 0x1400` with the same pixels;
  the capture `0x3600` 256 x 192 is 0x24000 bytes (0x300 a row); kelnscls's Z24 box is `w8 x h4 x 3`;
  menubg's 16 CT32 pixels are 64 bytes; a load from an unaligned source works; no trace, no load. What
  changes on a host run: main memory now gets the model's bytes where it got nothing (menubg's backdrop
  colours, the blur's "all zero = no capture" test, the flare's count read real values; with no trace the
  model is empty, so all zero), and `--uploads` now lists the image loads (timload, roombg, objwin, hud,
  fldtext, opimage, mdlpkt, capture's halves).
- **The menus' full-width rules** (item 4b, renderer-spec 5.4 "Session 101"): `func_00206130` widens a
  rule whose x is canvas 0 (`0x7000`) and whose width is 512 to `PLAT_VIEW_GX0 .. PLAT_VIEW_GX1` off the
  PS2, before the window's zoom (which still scales it about the window's centre). Done on the
  recommendation while the user's choice was pending (the card in session 101's thread): **if the user
  picks "keep them 4:3", delete that `#ifndef KH1_PS2` block** (nothing else depends on it).
  nameentry.nofill.c's `func_002078f0(.., 0, 188, y, 200, 512, 1)` goes to `func_00201440` (a textured
  row, `D_003F2C40.s2C40_2[19]`), not `func_00206130`: not covered; read `func_00201440` before deciding.
- **The lens flare's box** (item 4c, 5.1an item 4): `func_00192958` has one caller (`jal` at file offset
  0x92f40), `pppKeLnsLpTDraw`, and `FlareObj` is the same record as its `PppLnsWork` (`+0xC0` / `+0xC1`,
  `+0x8D`): on the key's frame **`bC0 = key->e << 3`, `bC1 = key->f << 2`** (u8 stores: e and f above 31 /
  63 wrap), `b8D = key->g` (the test runs every `g + 1` frames, phase `b8C` from the constructor's counter
  `D_00372708`); the constructor `pppKeLnsLpTCon` zeroes `bC0 / bC1`, so before the first key the box is
  empty and the flare is hidden (`f7C = 0`). The box is **`bC0` x `bC1` target pixels** centred on the
  light (`r = v -+ bC0 x 8` sixteenths), clamped to the scissor; the ratio divides by the unclamped `bC0 x
  bC1`, so a flare at the screen's edge dims by the part off screen. **The store's size is bounded by the
  scratch**: `func_001aa950(0x3060)` and the store at `+96` leave 0x3000 bytes, so `w8 x h4 <= 4096`
  pixels (e.g. 64 x 64, `e <= 8`, `f <= 16`) or the PS2 overruns its scratch stack too: a port can size its
  depth read for 4096 pixels. The keys' e / f values are in the disc's ppp files (not read yet). For a
  port rendering 960 x 544: its target has 544 / 384 = 1.417 pixels per canvas pixel, so the store either
  samples its depth at the PS2-sized box's positions scaled by that, or reads the bigger box and
  downsamples to `w8 x h4`; either way the bytes keep 5.1an's shape and the count's ratio is unchanged.
- **Still waiting for the Mac** (item 4d): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1ap Session 102: the lens flare's depth read on the host, nameentry's row

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). No change under src/: kh1.elf byte-identical,
no float-untested row. selftest PASS (gsimage_test: 21 checks), the host links (571 objects).

- **The menus' full-width rules** (item 4a): the user had not answered session 101's card when this session
  ran, so the "widen" block stays; "keep them 4:3" still means deleting it (5.1ao).
- **nameentry's textured row** (item 4b): `func_002078f0(a0, a1, a2, a3, t0, t1, t2, t3, s0)` calls
  `func_00201440(a0, a2, a3, t0, t1, t2, t3, &D_003F2C40.s2C40_2[a1], s0)`, so nameentry.nofill.c's
  `func_002078f0(a, 19, 2, 0, 188, y, 200, 512, 1)` is a list row of type 2 (`func_00200648`'s frame) at
  window x **188**, **200** wide, with message 1 at x 512 (mode 0). Not a full-width rule: nothing to widen.
- **The lens flare's depth on the host** (item 4c): gsmem.c marks draws, it does not rasterise them, so a
  Z24 store from the Z buffer read whatever an upload or copy left there last (zeros when nothing did). Now
  **`PlatGsExecStoreImage` of a Z format answers 0 for every pixel whose 8 KB page a draw wrote since its
  last upload / copy / pixel write** (new `kh1_gsmem_drawn`, the same page bits as the texture targets,
  session 81). 0 is the farthest depth, so kelnscls's count (`z < v[2] >> 4`) sees the whole box and the
  flare is drawn at full strength: "all visible", the occlusion-query answer (b) of 5.1an item 4 with the
  query always passing. A Z buffer the model does hold (the stored frame loaded into `0x0E00 / 0x1400`,
  renderer-spec 4.17's colour in the Z area) still reads its bytes, as on the PS2. Colour stores are
  unchanged (the model draws sprites into colour targets). gsimage_test checks the drawn box reads 0 and a
  write gives its page back.
- **Still waiting for the Mac** (item 4d): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1aq Session 103: the lens flare's count tested on the host

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). No change under src/: kh1.elf byte-identical,
no float-untested row. selftest PASS (new flare_test: 14 checks).

- **The menus' full-width rules** (item 4a): session 101's card was still unanswered, so the "widen" block in
  winpart.nostrict.c's `func_00206130` stays; "keep them 4:3" still means deleting it (5.1ao).
- **The flare's count on the null platform** (item 4b): tests/host/flare_test.c links the game's own
  kelnscls.nostrict.c (host-compiled: `func_00192958` and its neighbours, their other callees and data
  stubbed) with gsimage.c, gsmem.c and host/port/libvu0.c, and runs `func_00192958` on a made-up `FlareObj`
  (light at screen 256, 192, Z24 0x100000, the box `bC0 x bC1` pixels) under the wide view:
  a Z buffer only the 3D draw wrote (`kh1_gsmem_draw` over an older nearer upload) reads 0 and `f7C` stays
  1.0 (`fAC` 1.0; the store hands back 16 x 16 x 3 zero bytes after the 96-byte header and nothing past
  them); the box's left half uploaded nearer than the light gives 0.5; a skipped frame (`b8D` 1, odd frame)
  multiplies by `fAC` again (0.25, no store); a quarter at the light's own depth in the largest box (64 x 64,
  4096 pixels, ending exactly at the scratch's 0x3060 bytes) gives 0.75 (equal depth is not visible: the
  test is `z < thr`); a box at the screen's left edge is clipped to the scissor (8 of 16 columns seen, 0.5:
  the count divides by the whole box); off screen sets `f7C` and `fAC` to 0. With session 102's "drawn
  reads 0" line reverted, the first three checks fail, so the test holds that answer.
- **A container's host tests need `gcc-multilib`** (`gcc -m32` links): without it selftest skips every host
  C test silently (build.yml installs no multilib, so in CI they run only if the runner image has it).
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1ar Session 104: the other store readers tested on the host

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). Only a comment changed under src/ (menubg.c's
store rectangle): kh1.elf byte-identical, no float-untested row. selftest PASS (new storeread_test: 24 checks).

- **The menus' full-width rules** (item 4a): session 101's card was still unanswered, so "widen" stays (5.1ao).
- **The other `PlatGsExecStoreImage` readers on the null platform** (item 4b): tests/host/storeread_test.c
  links the game's own src/menu/menubg.c, src/screen/capture.c, src/gfx/sceneeff.c and src/screen/screen.c
  with gsimage.c / gsmem.c (`-ffunction-sections -Wl,--gc-sections`, so only the tested functions' callees
  need stubs: 13 symbols) and runs them on made-up pixels in the 4:3 view and the wide one:
  - **menubg.c `func_0020a8f0`** stores 16 x 1 CT32 at **x 256, y 4 and y 443** of FBP 0 / FBW 8 (the old
    header comment said "(4, 16) and (443, 16)": those are y and w) and keeps each row's first pixel
    without its alpha byte. Wide or not it reads the PS2's x 256, never the view's edges. A frame only the
    draws wrote reads black (0, after a reset) or whatever an earlier upload left there (the null platform
    does not rasterise); a flat clear filled for the present (`kh1_gsmem_flat(1)`, `KH1_HOST_SHOT`) reads
    its colour. **So on a host run without `KH1_HOST_SHOT` the menu backdrop's gradient is black or stale**;
    a port's store reads its real frame there (the 4:3 centre column of the view, 5.1an).
  - **capture.c `func_0010a3e8`** sends the half copy `D_002B6760`, asks `func_00121e28` for 0x24000 bytes and
    stores 256 x 192 CT24 from block 0x3600 (FBW 4): exactly 0x24000 bytes, 0x300 a row, wide or not.
  - **sceneeff.c `func_00102a48`** (the menu blur) loads that back (`func_0010a470`) and scans 0x9000 words:
    a captured frame sends the blur `D_002A4B60` (its corners at the view's edges under the wide view, at
    `0x6fe0 - o` on the 4:3); black with only the alpha byte set is empty (the CT24 store drops alpha) and
    sends `D_002A4DD0`; the last pixel alone is enough (the scan covers all 0x24000 bytes). **A half target
    only the draws wrote reads zeros, so on the null platform the menu opens with the empty pass, not the
    blur**: expect `D_002A4DD0` in a host run's `--nodes` / `--draws` when the menu opens (with
    `KH1_HOST_SHOT` the copy may be point-sampled into the model and send the blur; not checked).
  - **screen.c `func_001e1480`** (vm_lib's capture) stores the target 0x1A00 into `D_00F20000`: 0x90000
    bytes, 0x600 a row, wide or not (gsimage_test checks capture.c's twin).
  With gsimage.c's "drawn Z reads 0" widened to every format, the drawn-frame and flat-clear checks fail, so
  the test also holds that only Z formats read 0 when drawn.
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1as Session 105: the half capture filled by the present

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). No change under src/ or host/: kh1.elf
byte-identical, no float-untested row. selftest PASS (storeread_test: 31 checks, 7 new).

- **The menus' full-width rules** (item 4a): session 101's card was still unanswered, so "widen" stays (5.1ao).
- **Does the present fill the half capture?** (item 4b) **Yes, the model does not refuse it.**
  storeread_test now sends the menu capture itself: `D_002B6760` as a refe tag to a made-up 10-qword packet
  with its registers (read from the ELF's data, written in the test as constants: FRAME_1 `0x000401B0`
  (block 0x3600, FBW 4, CT32), TEST_1 ZTE + ZTST ALWAYS, TEX1_1 bilinear, CLAMP_1 CLAMP, TEX0_1 `0x80000006_64020000`
  (TBP0 0, TBW 8, CT32, 512 x 512, TCC, MODULATE), one SPRITE (PRIM `0x116`, RGBAQ 0x80 each) UV (0, 0) ..
  (512, 448) at XYZ2 (0x7000, 0x7400) .. (0x8000, 0x8000)), through `kh1_dma_walk` -> gsregs.c -> gsmem.c,
  with XYOFFSET_1 (0x7000, 0x7400) and SCISSOR_1 512 x 448 in force (an assumption: what the frame's
  environment leaves). **Note the source is the display buffer at block 0** (TBP0 0, as renderer-spec 4.17
  says), not the 3D target 0x1A00 the session 105 plan named.
  - Without `kh1_gsmem_flat` the bilinear 512 x 512 texture is past `kh1_gsmem_sprite`, so the copy only
    marks 0x3600 as drawn: a display the model holds still gives the empty pass `D_002A4DD0` (session 104).
  - With `kh1_gsmem_flat(1)` (what `KH1_HOST_SHOT`'s present turns on) the copy is point-sampled into
    0x3600 (pixel (x, y) = texel (2x, 448y / 192)), the store reads it and **the blur `D_002A4B60` is sent:
    the PS2's path**. A 4:3 copy writes nothing outside the 256 x 192 capture.
  - **A black display still gives the empty pass even then**: the CT24 store drops the alpha byte. On the
    host the display holds what the present filled (the clears, fades, 2D sprites; VU1's meshes are not
    drawn), so a `KH1_HOST_SHOT` run whose 3D clear is black opens the menu with the empty pass. Nothing to
    change: on the PS2 and a port the display holds the rendered frame.
  - **Decided: the null platform does not need to answer drawn colour pixels from the present's fill**; the
    fill already writes the model's pixels, and without `KH1_HOST_SHOT` the empty pass is the expected
    host answer (5.1ar).
  - **New, the wide view in the model**: fullscreen.c's `KH1_FS_XS | KH1_FS_U` row stretches the copy to
    x 0 .. 338.8, but the model's buffer is the PS2's 256 wide (FBW 4). The 83 columns past x 256 wrap to
    the next page row (the GS's own addressing): rows 0 .. 159's land inside the capture and are drawn over
    by the later rows, rows 160 .. 191's land in rows 192 .. 223, **83 x 32 words in blocks 0x3900 ..
    0x393F**, the shared texture slot (renderer-spec 3.1, rewritten per draw). The store reads x 0 .. 255,
    the view's canvas -82.8 .. 429 (the left 41 pixels clamped to texel 0). Host-model only and only with
    `KH1_HOST_SHOT` and `KH1_HOST_WIDE` together; a port's capture buffer is the view's half wide (5.1an),
    so nothing changes for the Vita. The test holds the count and the block range, so a change to the
    model's wide copies shows there. If a wide shot run shows a broken texture right after a menu opens,
    this is the first suspect (clip an `KH1_FS_XS` fill at FBW x 64 in gsregs.c's flat pass).
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1at Session 106: the present's fill kept inside its buffer

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). Host only: kh1.elf byte-identical, no
float-untested row. selftest PASS (storeread_test: 33 checks, 31 before; one replaced, two new).

- **The menus' full-width rules** (item 4a): session 101's card was still unanswered, so "widen" stays (5.1ao).
- **The wide copy's overrun in the model** (item 4b, 5.1as). **Decided: the present's fill clips at the
  frame's width.** host/null/gsmem.c `kh1_gsmem_flat_sprite` now stops a sprite's columns at FBW x 64
  after the scissor, instead of letting the GS's addressing wrap them into the next page row. Only a wide
  stretch into a buffer of the PS2's width reaches past it (the menu capture `D_002B6760`'s `KH1_FS_XS`
  row: x 0 .. 338.8 into FBW 4); the fill is the present's picture, a port's capture buffer holds the
  view's half whole (5.1an), and the wrapped columns had landed in the shared texture slot (blocks 0x3900 ..
  0x393F). Done in the model, not gsregs.c, because the model knows FBW and the rule holds for every fill;
  `kh1_gsmem_sprite` (the exact path the texture animations use, at most 4096 pixels) keeps the GS's wrap.
  storeread_test's wide copy check is now "nothing written past the capture's 256 columns", plus a check
  that the capture holds canvas -82.8 .. 429 (pixel x reads the display's 2x - 82.8, texel 0 left of it).
  So on a `KH1_HOST_SHOT` + `KH1_HOST_WIDE` run the menu blur shows the left 3/4 of the view at full width
  (host model only; the PS2 path and a port are unchanged).
- **The depth blur's capture `D_002A5380`** (read from the ELF: FRAME_1 `0x000801B0`, block 0x3600 **FBW 8**,
  TEX0_1 TBP0 0x1A00 the 3D target, UV 512 x 384, XYZ2 0x7000 .. 0x8000; off the PS2 its right edge is
  0x7000 + `PLAT_VIEW_W16` / 2 from C, row `D_002A5A90` u only). **It does not have the menu capture's
  problem**: its buffer is 512 wide, so under the wide view x 0 .. 338.8 fits; nothing wraps or is clipped,
  and pixel x holds the target's 2x - 82.8 (canvas -82.8 .. 594.8, the whole view), read back by the nine
  copies `D_002A5AC0` (u stretched). storeread_test sends a packet with its registers the same way and
  checks both. On the PS2 its 256 x 192 already spans blocks 0x3600 .. 0x3C00 in FBW 8's page order, over the
  shared texture slot, and the wide one adds page columns 4 and 5 in the same range (transient, both).
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1au Session 107: sends drawn past their frame's width, checked by a tool

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). Tool only: kh1.elf byte-identical, no
float-untested row. selftest PASS (one new negative case).

- **The menus' full-width rules** (item 4a): session 101's card was still unanswered, so "widen" stays (5.1ao).
- **The overrun 5.1as found by hand, now found by tools/host/fscheck.py** (item 4b). For each full-screen
  send it takes the sprites whose packet sets FRAME (context 1 or 2 by PRIM's CTXT bit) and XYOFFSET (else
  0x7000), works out their x under the wide view (`--side16`, default 1325 = 960 x 544's margin, as
  host/port/view.c rounds it): XYZ in data by the send's row (`KH1_FS_X` about the canvas, `KH1_FS_XS` from
  its left edge, neither: unchanged); XYZ written from C by evaluating the x (an `xyz()` / `XYZ()` macro's
  first argument, else the word's low halfword) with `PLAT_VIEW_SIDE16 / W16 / GX0 / GX1` at the margin; when
  the expression also names a local (the blurs' offset `o`), the data's x moved by the expression's own
  change from margin 0 to the margin. The sprites drawn into one frame are taken together (a set of columns
  is one picture). **A send that keeps its buffer's left edge (pixel x0 >= -2) and draws past FBW x 64 + 1
  is a problem** unless it is in `OVER_EXPECTED`; a send stretched over the view (its left edge before the
  buffer's) draws into the view's own target, which a port sizes to the view, and the environment's frame
  (no FRAME in the packet: the target or the display) is not checked.
- **Result: 24 full-screen sends, one drawn past its width: the menu capture `D_002B6760`** (x 0 .. 338.8 into
  FBW 4's 256, `OVER_EXPECTED`: a port's buffer is the view's half wide, 5.1an; the host's fill clips it,
  5.1at). The depth blur's capture (`D_002A5A90`, and inside `D_002A5620`) draws x 0 .. 338.8 into FBW 8's 512:
  fits. The clear, frame copy and copy into the Z area (columns, `KH1_FS_X`) start before their buffer's left
  edge under the stretch, so they are the view's. The summary line now counts "drawn past their frame's
  width (n expected)"; a stale `OVER_EXPECTED` entry is a problem too.
- **selftest**: the depth blur capture's C right edge changed to `0x7000 + PLAT_VIEW_W16` (the view's full
  width into its 512-wide buffer) must give `D_002A5A90 ... x 0.0 .. 677.6, FBW x 64 = 512`.
- **Not covered**: y (the wide view does not stretch it), a buffer's blocks against the memory map inside
  its FBW (session 108, 5.1av), sends outside fscheck's walk (the HUD's, the draw list's).
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1av Session 108: the blocks each send draws, against the PS2's and the memory map

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). Tool only: kh1.elf byte-identical, no
float-untested row. selftest PASS (one new negative case).

- **The menus' full-width rules** (item 4a): session 101's card was still unanswered, so "widen" stays (5.1ao).
- **tools/host/fscheck.py lists the GS memory blocks each send's drawn rectangle covers** (item 4b). Every
  send in its walk whose packet sets FRAME (full-screen or not: 14 of the 58) gets, per FRAME, the pixel
  rectangle its sprites draw (x as 5.1au works it out, at the wide margin and at 0 for the PS2; y from the
  data's XYZ less XYOFFSET's y, default 0x7400, clamped at 0), and from FBP, FBW and the PSM's page and block
  order (CT32 / CT24 64 x 32 pages of 8 x 8 blocks, CT16 / CT16S 64 x 64 of 16 x 8, GS manual 8.3; x past
  FBW x 64 runs into the next pages, as on the GS) the 256-byte blocks it covers. Two rules: **the wide
  view's blocks stay inside the PS2's**, and **inside renderer-spec 3.1's region its FBP is in** (`REGIONS`:
  display 0x0000, Z area 0x0E00, target 0x1A00, room textures 0x2600, texture slot 0x3600, off-screen buffer
  0x3A00, window font 0x3D7C, CLUTs 0x3E00), unless (send, region or "wide") is in `BLOCK_EXPECTED`. Frames
  drawn from before their left edge (stretched over the view: the port sizes that target to the view) and the
  environment's frame are skipped, as in 5.1au. A stale `BLOCK_EXPECTED` entry is a problem; `-v` prints each
  frame's blocks at both margins.
- **Result: 0 problems, 6 expected entries.** On the PS2 too: the depth blur's half capture (`D_002A5620`,
  `D_002A5A90`: 512 x 192 CT32 at 0x3600) covers 0x3600 .. 0x3C00, over the off-screen buffer's first rows
  (rewritten before its next use); case 2's frame copy into a 640 x 448 display runs to block 0x1180, over the
  Z area's first rows (movies). Under the wide view only: the menu capture `D_002B6760` wraps into 0x3900 ..
  0x392E (5.1as, already `OVER_EXPECTED`), and **the depth blur's capture, at x 0 .. 338.8 inside its FBW 8,
  now reaches the right halves of its pages that the PS2's 256 left alone**: 0x3680 .. 0x36AE (the menus'
  CLUT slot 0x3680, uploaded per draw), and the same in each page row down to 0x3B80 .. 0x3BAE (the off-screen
  buffer, redrawn each frame). Both are scratch at that point as the left halves are on the PS2, so expected;
  a port that keeps a separate buffer per capture (5.1an) has no such overlap. The menu capture's buffer
  (0x3600, FBW 4) also covers renderer B's CLUT block 0x3700 on the PS2: same region, not flagged.
- **selftest**: with `("D_002B6760", "wide")` and `("D_002A5620", 0x3A00)` taken out of `BLOCK_EXPECTED`
  (imported, not edited), the capture's 0x3900 .. 0x3924 past the PS2's 0x3600 .. 0x38FF and the blur's
  capture over the off-screen buffer must both be reported.
- **Not covered**: SCISSOR (the rectangles are the sprites', not clipped), a FRAME written from C (the data's
  value is used; `-v` says so: case 2's `D_002A6960`), y written from C, and sends outside fscheck's walk (the
  shadows' `D_004F7820` / `D_004F7C10`, the HUD's, the draw list's).
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

### 5.1aw Session 109: the render-to-texture sends from the C, checked by fscheck

Static only (Sunday 2026-10-25, the Mac away until 2026-10-26). Tool only: kh1.elf byte-identical, no
float-untested row. selftest PASS (two new negative cases).

- **The menus' full-width rules** (item 4a): session 101's card was still unanswered, so "widen" stays (5.1ao).
- **fscheck.py now walks the render-to-texture sends outside its walk** (item 4b, renderer-spec 3.4), with
  5.1av's block check (blocks against the PS2's and the §3.1 region of their FBP):
  - **packets the game's C builds at run time**: tools/host/rtsends.c runs the game's own builders under
    `gcc -m32` (fscheck compiles it with src/gfx/shadow.c, gifpkt.c and src/obj/objdraw.nostrict.c,
    `--gc-sections`, the way flare_test links its function; `--cc` picks the compiler) and prints the chains:
    the shadow windows `D_004F7820[i]` / `D_004F7C10[i]` (`func_001284a0` / `func_00128738` for each of
    `D_002E27E0`'s sizes, read from the ELF: **128, 196, 256**), and the crossfade `func_00135ed0` (its two
    `PlatDmaSend` chains, the GS state carried from the first to the second) for 64 x 64, 128 x 128, 256 x 128,
    128 x 256 and 256 x 256 (`CROSSFADE_SIZES`: the model's texture, from the disc at run time). Without
    `gcc -m32` fscheck says so and skips them (their `BLOCK_EXPECTED` entries are then not stale);
  - **data packets the C finishes**: the eye overlay `D_0035C4A0` + `D_0035C550` (`RT_DATA`): their tags are
    zeros in the ELF; texspot.nostrict.c's `.x0` / `.x3` / `.x4` stores (QWC 10 / 16, ID 7 = end, ADDR 0)
    are read from the C and applied, the two walked as one picture, and the pupil sprite whose XYZ
    `func_00175600` writes (`p->x68` / `p->x78`) is taken as its whole SCISSOR (0 .. 255);
  - **a FRAME written from C**: case 2's frame copy `D_002A6960` (`CVARS`) is checked for each display width
    `func_001110d0` gives (512 and 640): the writes of its words (`D_002A68A0[4]` FRAME, `[22]` / `[23]`) are
    evaluated with the simple `w = v / 64;` / `x = v * 16;` / `y = x + 0x7000;` lines before them: FBW 8,
    blocks 0x0000 .. 0x0DFF (the display exactly) and FBW 10, 0x0000 .. 0x117F (the known Z-area overlap);
  - **SCISSOR**: a sprite the view does not stretch is clipped by its context's SCISSOR when the packets set
    one (the shadow windows' centred w x w); the 58 sends' results are unchanged by it;
  - **PACKED registers** (RGBAQ, UV, XYZ) are now read as the GS reads them (y and z in the second and third
    words); the run-time builders send them so. The 58 sends' results are unchanged by it too.
- **Result: 12 more sends, 0 problems, 3 new expected entries, all PS2 overlaps**: the off-screen buffer's
  256 x 256 CT32 (renderer-spec 3.4) runs to block 0x3DFF, **over the window font (0x3D7C .. 0x3DFB) and its
  CLUT 0x3DFC**; the shadow windows of 196 and 256 clear rows 224 .. 255 there, the eye overlay's copy fills
  it all, and a crossfade of a texture 256 high does too. On the PS2 the windows re-send the font's uploads
  (`func_001f82b0` -> `func_001f8270`, renderer-spec 4.12) before they draw, after the list's
  render-to-texture, so expected; **for the boot**: a window drawn from the font after a shadow, eye overlay or
  crossfade in the same frame without that re-send would show garbled text. The shadows' copy into the texture
  slot (`D_004F7C10`, FBW 4 at 0x3600) stays in the slot; the 128 window clears 0x3B20 .. 0x3CDF only.
  Nothing here stretches under the wide view, so no "wide" entry.
- **Noticed**: `D_004F7820` / `D_004F7C10` are indexed by an actor's `x370` bits 40-41 (`& 3`) but hold 3
  entries; with 3 the shadow pointer `&D_004F7820[3]` is `D_004F7C10[0]` (336 x 3 bytes after it) and
  `D_002E27E0[3]` is 0. Presumably never set; renderer-spec 3.4 notes it.
- **selftest**: with the window font's entries for `D_004F7820` and `D_0035C4A0` taken out (imported, not
  edited), the eye overlay and (when `gcc -m32` builds rtsends.c) the 196 and 256 shadow windows, not the
  128, must be reported; with texspot's `D_0035C550.x3 = 112;` deleted from a copy of src/, the eye
  overlay must be reported unwalked.
- **Not covered**: the shadows' Z16S at 0x3800 and the other ZBUFs (FRAME only), the textures these sends
  read, the HUD's and the draw list's other packets.
- **Still waiting for the Mac** (item 4c): `KH1_HOST_DMAC=defer` as the default, argcheck's 3 value uses,
  the callers of prim.c's four senders.

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
