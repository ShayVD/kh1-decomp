# The first Vita build

Written 2026-10-25 (phase 5, after session 122); first run in Vita3K on 2026-10-26 (below, "In
Vita3K"). What it is, how to build it, what it does and does not do.

## What it is

`make vita` (tools/vita/build.py) compiles the same files as the host runner (`make host-census`) for
the Vita's Cortex-A9 with vitasdk and packs `out/vita/kh1-decomp.vpk`:

- all 519 game C files and the 7 drafts of the unmatched functions, unchanged (`-DKH1_VITA`,
  `-fsigned-char` as on the EE, `-ffp-contract=off`, gnu89, `-O2`);
- src/data/*.s's pieces (the user's ELF bytes, cut by the PS2 `make`), assembled for ARM;
- the null platform's GS memory model, register file and DMA chain walk (host/null/ but main.c and
  pad.c), the shared port code (host/port/), and the Vita platform (host/vita/):
  - `main.c`: the entry, the data directory, the log, the frame pacing on the Vita's vblank, the
    overlay stub (below);
  - `display.c`: the GS model's display buffer after each frame copy (the host's `KH1_HOST_SHOT`
    present, 4:3 pillarboxed; since 2026-10-30 16:9 by default, "Wide screen" below), plus a status strip; since session 135 drawn by the GPU through
    vita2d (one bilinear textured quad, "Speed" below);
  - `pad.c`: sceCtrl in libpad2's layout (Vita L / R are L1 / R1; L2 / R2 / L3 / R3 are the rear touch
    pad's quarters: upper left, upper right, lower left, lower right; circle confirms);
  - `context.S` + `include/ucontext.h`: the four ucontext calls threads.c / tasks.c use, as an ARM
    switch of the callee-saved registers (newlib has no ucontext);
  - the disc: host/port/cd_image.c reads the user's image with sceIo (64-bit seeks: the image is
    larger than 2 GiB).

**The VPK holds bytes of your own ELF** (the data pieces and defs_host.c's initial values), as
out/host/kh1-host does. It is build output for your own Vita: never share it, never commit it
(.gitignore has `*.vpk`, `*.velf`, `eboot.bin`). The disc image is never in it.

## Build

1. vitasdk: on a Mac / Linux desktop the usual install (https://vitasdk.org, vdpm), or in a container
   `tools/vita/get_vitasdk.sh` (the vitasdk/vitasdk image's two toolchain layers from mirror.gcr.io,
   sha256-checked, channel 2026.08, gcc 15.2; no docker daemon needed). `export VITASDK=...`
   (default /usr/local/vitasdk).
2. The PS2 build first (`make`: the data pieces and out/gen/symbols.ld), then `make vita`.
   About a minute on 4 cores. Prints `vita: out/vita/kh1-decomp.vpk (... KiB)`.

## Run (on a Vita with HENkaku / Ensō, or Vita3K)

1. Install out/vita/kh1-decomp.vpk with VitaShell (title id KHDC00001, "Kingdom Hearts (kh1-decomp)").
2. Copy your own disc image to `ux0:data/kh1/kh1.iso` (2048-byte sectors; a raw 2352-byte image as
   `kh1.bin`). Without one the app shows a red screen until START. The English fan patch's ISO works
   too: the app sees the patch's ELF on it and runs in English (docs/english-patch.md).
3. Optional `ux0:data/kh1/config.txt`, `key=value` lines:
   - `iso=ux0:...` another image path;
   - `title=N` the game state asked for at the title overlay's first call (default 2: a new game,
     Dive to the Heart; `-1` stays in the title state);
   - `frames=N` exit after N frames (0, the default: never);
   - `mc=ux0:...` memory card 1's folder (default `ux0:data/kh1/mc0`);
   - `vu1=0` skips the VIF1 / VU1 path (session 137v, "The 3D path" below; 1, the default, runs it).
   - `rcam=1` (the default): the right stick's left / right turns the camera. The game itself, Final Mix
     included, turns the camera with L2 / R2 only and gives the right stick the d-pad's command-menu
     cursor, so host/vita/pad.c sends the stick's x past half way as R2 (right) or L2 (left), held while
     pushed (never pulsed: each L2 / R2 press also steps the lock-on target), and centres the x; the y is
     unchanged. `rcam=-1` turns the other way, `rcam=0` sends the stick as the PS2 did.
   - `snd=0` keeps the game silent (the null server); 1, the default, plays the sound through the disc's
     own driver ("Sound" below). `sndcore=N` pins the sound threads to core N (default -1: any core).
   - `wide=1` (the default since 2026-10-30): the picture fills the 960 x 544 screen as a true 16:9 view ("Wide
     screen" below); `wide=2` stretches the 4:3 picture to fill the screen; `wide=0` keeps the 4:3 picture in black
     bars, as before. `strip=1` keeps the status strip over a full-screen picture.
   - `pad=ux0:data/kh1/dive.txt` replays a host pad script (the format of `tests/host/pads/*.txt`, frame numbers counted the same way) in place of the Vita buttons, so an unattended run gets past the title into Dive to the Heart. A file that fails to load leaves the real pad in charge.
4. `ux0:data/kh1/kh1.log` gets what the host runner prints, a line every 60 frames and, from a
   watchdog thread, a line every 2 s of wall time (frame, disc reads, DMA sends, frames shown). It is
   written through sceIoWrite (a funopen FILE): newlib's own fopen'd / freopen'd log stayed empty in
   Vita3K. Send it back after a run.

On screen: the GS model's picture in the middle, and in the left bar a square that changes colour
every 30 frames (the frame loop is alive), a green bar that grows per 256 disc reads and a blue one
per frame copy shown.

## What works and what does not (be direct)

Checked here:

- 519 / 519 game files compile, the link has no undefined name, vita-elf-create / make-fself /
  mksfoex / pack-vpk accept it.
- **The ARM code behaves as the x86 host's**: `make vita-armcheck` builds the same objects (the same
  overlay rewrite, the same context switch) for 32-bit ARM Linux, run under qemu-arm with the fake
  disc (tests/host/fake_disc.py): 600 frames at `KH1_HOST_TRACE=5` (every GS state value, draw-list
  node and vblank) give the x86 run's 22,857 log lines exactly, but for the overlay-call count line
  (the x86 stub counts in main.c, the ARM one in host/armlinux/ovl.c); with `KH1_HOST_OVL=stub:2`
  both end at the same place (func_00132790, the fake disc's missing room file).
- The PS2 build is byte-identical and `make test` passes.

Not checked (needs the device or Vita3K, and the user's disc): that it boots, the framebuffer and
the controls, the speed, the memory budget (160 MiB newlib heap, 37 MiB .bss, `ATTRIBUTE2=12`).

What a run can show, at best:

- **Session 132: the title overlay is native C** (docs/native-overlays.md): when the game loads the
  pinned dktitle.x, `kh1_ovl_entry` runs its C instead of answering 0, so a Vita build made now
  (tools/vita/build.py takes it through census.py's link step) should reach the title screen on the
  real disc; `title=N` only applies when the file is not the pinned one. Not built or run here (no
  vitasdk in the container). The older note:
- **No title screen.** The title is the overlay dktitle.x (MIPS code the game loads from the disc to
  0xF20000 and calls); no overlay is decompiled yet (vita-port-plan 5.2). tools/vita/build.py routes
  every call of the overlay entry (29 in 13 files, found in the preprocessed C) to
  `kh1_ovl_entry`, which answers 0 like the host's `KH1_HOST_OVL=stub`, and at the title's first
  call asks for game state 2 (new game). So the boot loads its files and goes straight to Dive to the
  Heart's room loads, which the host has never run past on a real disc: expect it to stop there or
  soon after (the log's last lines say where).
- **3D since session 137v** ("The 3D path" below), slowly. Before it: **No 3D.** The VIF1 / VU1 path (renderer A / B, PATH1) is not replaced: chains are walked but
  their models are not drawn. The picture is the GS model's 2D: clears, fades, uploads, sprites,
  copies (whatever the boot draws on PATH3).
- **Not the GXM renderer** (before session 136; now it is, "The GPU renderer" below). The picture was software (the model's display buffer; since session 135
  shown as one GXM textured quad through vita2d, "Speed" below). The port code from sessions 116 to 122 (palette and texture
  caches, texture formats, TFX, sampler, blend, alpha / destination-alpha tests, depth, fog, primitive
  assembly) is linked and feeds the model's present, but nothing draws with GXM yet.
- **Sound since 2026-10-29** ("Sound" below; before it the null server kept the status the game polls), **no movies**
  (dkmovie.x is an overlay too). **Saves** (session 140): memory card 1 is the folder
  `ux0:data/kh1/mc0` when it exists ("Memory card" below); card 2 is always empty.
- gumisave.c's func_001b9c60 keeps the overlay entry as a pointer and calls it later: on the Vita
  that jumps into data (the Gummi ship editor; not reachable before the world map anyway).

## Wide screen (2026-10-30)

config.txt's `wide=` picks how the picture covers the Vita's 960 x 544 (16:9) screen; the log says which
(`kh1-vita: screen: ...`).

- **`wide=1`, the default: a 16:9 view.** The renderer-spec 5.3 step 2 / 5.4 design (sessions 90-100), written and
  checked for the host's null model as `KH1_HOST_WIDE` but never turned on for the Vita, now runs there. main.c calls
  `kh1_view_init(960 / 544)` (host/port/view.c: the culls' frustum and the markers' bounds widen by 1.3235, hor+: the
  vertical view stays) and `kh1_null_hud_wide` (host/null/plat_null.c: the HUD's anchors, the full-screen packets'
  stretch, the scissor rule, and now the GPU recorder's view, `kh1_pipes_view`), and display.c draws the GPU's
  display target over the whole screen. The 3D sees more at the sides; the command menu, the gauges and the other
  parts of renderer-spec 5.3.1's table sit at the screen's edges; menus, text windows and the title's art stay in
  the centred 4:3 canvas (the title's white backdrop and the menus' bands are full-screen passes, so they fill the
  sides). Needs the GPU picture: with the software picture (`gpu=0`, or no shader compiler) it falls back to 2.
- **`wide=2`: the 4:3 picture stretched** to the whole screen (everything 1.33 x wider). Works with either picture.
- **`wide=0`: the 4:3 picture pillarboxed**, as before; the GPU's output is bit-identical to before the change
  (gxmcheck's `KH1_HOST_GXM_HASH` over 7,000 frames of dive_en.txt on the English disc: all 56 hashes equal).
- In 1 and 2 the status strip (the alive square, the read and frame bars) is drawn only while no picture is shown
  (the boot), or always with `strip=1`.

What the GPU path needed beyond the host's design (host/null/pipes.c, host/port/cmdbuf.c, host/port/target.c,
host/vita/gxm.c):

- **The targets take the view's width.** pipes.c's recorder made every pass with the PS2's 4:3 canvas; under the
  wide view the 3D, display and Z-colour targets are the view's 678 x 384 (448), canvas x -82.8 .. 594.8, and a
  capture slot half of that (target.h's `wide`), drawn with the existing `ox` margin.
- **A wide target is sampled its whole width.** A texture read from a target was a TW-wide (512) window of it, so
  the frame copy, whose u the full-screen stretch carries to 0 .. 678, clamped at 512 and smeared the right sixth
  of the screen. Now a draw that samples a target whose last pass had the margin (cmdbuf.c `tsw`, `KH1Cmd.wtex`,
  gxmrec's SET_TEXTURE `wtex`) has its s taken over the target's width and gxm.c binds the target that wide.
  Target texels keep the convention of platform/view.h (a copy of the target is addressed from the view's left
  edge), and GS uploads into a target keep their pixel x, so the title's layers (uploaded into the Z-colour target,
  drawn back at u 0 .. 512) land centred.
- **A slot draw away from the canvas's origin is not a capture.** The shadow copies its 256 x 256 window into the
  0x3600 slot with XYOFFSET 0x7800 (shadow.c func_00128738); taking the view's margin there moved Sora's shadow
  off his feet and smeared the floor. target.c gives the slot the margin only at XYOFFSET 0x7000 (the menu and depth
  blur captures).

**Checked** (host, `KH1_HOST_WIDE=1` with tools/vita/gxmcheck.sh's binary, gxm.c on the mock sceGxm, the English
disc, dive_en.txt, `KH1_HOST_VU1=1`): the title, the new-game menus, Dive to the Heart's stations and the first
battle to frame 24,000 draw 16:9 with the 3D wider at both sides, Sora's shadow under him, the command menu at the
left edge and the HP / MP gauge at the right; `KH1_HOST_GXM_PPM` writes the whole wide target now (gxm_mock.c
`gpu_wide_*`). The ARM build under qemu-arm gives the x86 log exactly with `KH1_HOST_WIDE=1` (2,500 frames at trace
5). **Not checked**: a real Vita or Vita3K; the pause menu's blur and the depth blur under the GPU path (no run
reached them); a target sampled with a shader REGION_CLAMP under the wide view (the clamp's texels are still TW's).

## Memory card (session 140)

host/port/mc_dir.c answers include/platform/mc.h from a folder: memory card 1 is
`ux0:data/kh1/mc0` (config.txt `mc=`), the host runner's is `KH1_HOST_MC=DIR`. A save is what the PS2
card holds, one directory per save: `BISLPS-25198-NN/` with `BISLPS-25198-NN` (the 0x16c00-byte
image), `system.bin` (the 60-byte head the load screen lists), `icon.sys`, `mc_icon.bin`,
`mc_copy.bin`, `mc_del.bin`. The game's own src/memcard/ steps read and write them, so saving in the
port writes the same files (run on a copy of the saves you care about). No folder: no card, as before.

**Your PS2 saves**: `python3 -I tools/host/ps2mc.py list Mcd001.ps2` lists a PCSX2 card file
(`~/Library/Application Support/PCSX2/memcards/` on a Mac), `extract Mcd001.ps2 mc0` copies every
`BISLPS-25198-*` save into `mc0/` with the card's times (the load screen opens on the newest). A
PCSX2 folder card needs no tool: copy its `BISLPS-25198-*` directories. Only Kingdom Hearts Final
Mix (SLPS-25198, the English patch included) saves load: the US / European Kingdom Hearts
(`BASLUS-20370`, `BESLES-...`) is another game build with its own directory names and save version
(the head's 0x01317F14), which this one's load screen does not list.

**Checked (2026-10-27)** with the user's card (kh1-test/memcards/KH1_FM_save.ps2: saves 04, 05, 06,
level 100) on the English disc: tests/host/pads/load_en.txt picks LOAD, slot 1 lists the saves with
the newest (06) under the cursor, and it loads into the field (party HUD; the host draws no 3D); the
run reads but writes nothing. **In Vita3K** (the same day, the VPK installed as KHDC00002 beside the
main install, the saves in ux0:data/kh1/mc0, the Japanese ISO): kh1.log says `memory card 1:
ux0:data/kh1/mc0 (found)`; at the title DOWN, CIRCLE (LOAD), CIRCLE (slot 1), CIRCLE (the newest save)
loads into the field at 27-60 fps: the command menu (Attack / Magic / Items / Save) draws, the party's
portraits and the HUD panels are garbled textures, and the Load Menu's windows and text do not draw
(the GPU path's 2D, not the card). The world map (wm.x) and the gummi ship (gb.x), the summons (xs_*.x)
and limits (xl_limit.x) are overlays with no native C yet, so a save there or a call into one still
stops the port.

**The packager's segment pad** (session 140): vita-elf-create puts ~3 KiB of import / export tables
after the code segment; when the code ended 1,168 bytes short of the data's page it failed ("segment 1
overlaps"). tools/vita/build.py now links a `.rodata` pad when less than a page is left.

## In Vita3K (2026-10-26)

Vita3K v0.2.1 4232-92bda548 on an M3 Mac (macOS 14.6.1, MoltenVK), firmware 3.74, the Japan Final
Mix ISO, `Vita3K --frontend sdl -r KHDC00001`, log level ERROR (its TRACE default filled the disk).

- **First runs: a crash in the first second**, in the sound update (sndctl.c vd01 through
  func_0011d7e0, a slot whose position pointer was 0x14). The host runner on the same ISO crashed in
  the same place: the real disc's first room-independent load had never run on any host.
  func_0010fc98 (framectl.c) copies allarea.nam (6112 bytes) to D_004D6B10, whose PS2 extent runs
  through D_004D6B20's table to 0x4D8E40; bss_004D.c defined only its first 16 bytes, so on the host
  the copy ran over the sound slots (D_004E3458). D_004D6B10 is now the whole 0x2330 bytes and
  D_004D6B20 a name inside it (portability.md's rule); kh1.elf is byte-identical. layoutcheck /
  relcheck could not see it: the length comes from the file. Also: the 32-bit host's fopen refuses
  the 3.3 GiB image, so host/port/cd_image.c uses fopen64 / fseeko64 there.
- **After the fix: no faults.** `title=-1` (stay in the title state) and the default (a new game)
  both run with no fault for 30 to 75 s. The new game reads 34 files (3225 sectors) by frame 60 and
  then runs its frame loop: about 22 DMA sends and one frame copy shown a frame. The host runner
  does the same on the ISO for 5000 frames, x86 and ARM (qemu) alike.
- **About 10 frames a second** in Vita3K on the M3 with the new game, 20 at the title: the software
  present (a GS model read per pixel) and the chain walk, emulated. Not a measure of a real Vita.
- **The picture is black**, as expected: no title (the overlay), no 3D. The status strip moves.

## Speed (session 135, 2026-10-26)

Vita3K showed the title at ~20 frames a second, ~6.5 once the large art was up. The game itself is
not the cost: the host runner takes 0.05 s for 600 title frames without the picture. All of it was
the software GS model drawing each frame (host/null/gsmem.c) and the present:

- **Every pixel's address through the swizzle, and two divisions** (the DDA's `lerp_floor`, a
  library call on the Cortex-A9, which has no divide instruction). Each frame draws the frame copy
  (16 strips of 32 x 448 from the 3D target, CT24, bilinear in TEX1 but point-sampled here), the
  3D target's clear (16 strips of 32 x 384) and the art, then the present read 512 x 448 pixels
  again one by one. Now each sprite builds two short tables: the frame's addresses as a column
  part plus a row part (`addr_split`: the CT32 / CT16 / CT16S block and in-block numbers are bit
  fields of x and y that do not overlap, so the address is a sum while the block number does not
  wrap at 0x4000; T8 / T4 and the Z formats keep the per-pixel swizzle), and each column's and
  row's texel. The tables are kept per rectangle, so the 16 strips reading one texture build its
  table once.
- **Three loops of their own** in kh1_gsmem_flat_sprite for the title's shapes, into a CT32 / CT24
  frame with no FBMSK: an unblended untextured fill (the clears), an unblended texel-for-pixel
  copy from a CT32 / CT24 texture with DECAL or MODULATE by 0x80 (the frame copy), and a cached
  texture or an untextured fill with any blend and the alpha test (the art and the fades; the
  texture cache's copy is taken before the draw, as the general loop reads it).
- tex_scan (a textured draw's page stamp, asked twice a draw) remembers its last answer until a
  page mark moves.
- **The log**: the chain walk prints a "dma ch" line per send, ~7 a frame. dmawalk.c's
  `kh1_dma_quiet` drops that line; the Vita sets it unless config.txt says `trace=2` or more (the
  host: `KH1_HOST_QUIET=1`). In Vita3K no printf reaches kh1.log at all (session 134: only main.c's
  `vlog` lines do, the funopen'd stdout never writes), so today this saves only the formatting; it
  is needed before printf is routed to the log.
- **The present is drawn by the GPU** (host/vita/display.c): the display buffer read once with
  `kh1_gsmem_read_rect` into a 512 x 512 GXM texture and drawn as one bilinear quad through the
  canvas map by vita2d (vitasdk's 2D library, whose shaders come compiled; the port's own Cg from
  shadergen.c still has no compiler in vitasdk, docs/vita-port-plan.md). Before, the CPU wrote all 960 x 544 pixels
  point-sampled. The status strip is drawn with it (and redrawn with the last picture when no frame
  copy came for 30 vblanks).

Measured on the fake disc with the user's dktitle.x (the title's frame loop without its art):

| | before | after |
|---|---|---|
| host runner, 600 title frames, KH1_HOST_SHOT=64:36 (x86, -O1) | 9.5 s | 0.77 s |
| one title frame's GS work (clear, copy, present read), ARM -O2 under qemu-arm | 130 ms | 4.7 ms |
| the same plus a full-screen blended T8 art layer (after: through the caches) | ~205 ms | ~16 ms |
| ARM runner under qemu-arm, 600 frames | | 4.3 s, every shot equal to the old x86 code's |

The pixels do not move: tests/host/gsfast_test.c draws 600 random sprites (the title's shapes and
every other) from the same memory with the fast paths on and off (`kh1_gsmem_fast(0)`) and compares
all 4 MB, the answer and the counters, plus kh1_gsmem_read_rect against kh1_gsmem_read_pixel and the
memo against a write and a draw (three deliberate breaks caught). Outside the repo, ~25,000 random
sprites gave the same memory as the session 133 gsmem.c linked side by side (its symbols renamed),
with and without the caches. **Not measured in Vita3K or on a Vita yet**: qemu's numbers are only
relative, the real art's sprites are unknown here (the fake disc has none), and the frame pacing
still waits for the Vita's vblank after each game vblank, so the title reaches 60 only when a
frame's work fits in 16.7 ms.

**In Vita3K** (the same Mac and disc as session 133, two minutes each, frames a second from the
watchdog lines):

| title stage | session 133 VPK | session 135 VPK |
|---|---|---|
| the logo (to frame ~960) | ~20 | ~60 |
| the art starting to fade in | ~8.5 | ~21 |
| the art up (steady) | ~6.7 | ~13 |

No crash in either. The art stage is still far from 60: its draws are not the fake disc's, so they
need profiling on the real disc. The watchdog line now also gives, of each 2 s, the ms spent in the
vblank wait and in the present; the rest is the game and the chain walk (the GS model's drawing).

**On the real disc** (the host runner with the user's image, START at frame 1300, 2000 frames,
KH1_HOST_SHOT=640:362; callgrind over frames 1700-1800, the menu up over the art):

- **The menu text was never drawn.** dktitle.x's menu lines (func_00f201c8: a 4-vertex TRISTRIP, the
  alpha fading to the right) and their bars (func_00f203a8) give TEX0 CPSM 1 (CT24), which the GS
  model refused as a CLUT format. The entries hold the glyphs' coverage in their alpha (CBP 0x38F5:
  black, alpha 0 .. 0x80), so CPSM CT24 is now read as CT32 (`cpsm_of`, gsmem_test checks it), and
  the strips' rectangles fill through gs_quad (gsregs.c) with each pixel's colour between the four
  corners'. NEW GAME / LOAD / SPECIAL MOVIE now show.
- **Every texture and CLUT is uploaded again each frame** with the same bytes (~800,000 pixels:
  two CT32 512 x 192, a T4 512 x 384, the menu's eight 512 x 32, two CT24 512 x 192 into the 3D
  target, the CLUTs). Each moved the pages' stamps, so the present's texture cache read 2.7 million
  texels back a frame to hash them. A write that stores the bits already there now keeps the stamp
  (`mark`): the run's 13,318 textured draws became stamp hits, 0 texels hashed after the first.
  The uploads keep each rectangle's addresses (`trx_addrs`, a 4 MB store) and write CT32 / PSMT8 /
  PSMT4 pieces in one loop (`trx_bulk`).
- One full-screen blended layer reads a render target's CT24 texels (not cacheable) and went through
  the general loop; the art loop now reads CT32 / CT24 texels in place, takes the quads (weights a
  column / row instead of two divisions a pixel), and the art's own blend ((Cs - Cd) x As + Cd from
  a palette or CT32 texels) has a loop of its own.

| real disc, frames 1700-1800 | instructions a frame (callgrind, x86 -O1) |
|---|---|
| before (no text drawn) | ~570 M |
| text drawn, stamps kept | ~277 M before the last two items |
| host run, 2000 frames with shots | 61 s -> 39 s -> 29 s |

Every one of the 1991 shots is byte-identical through each step (old against new binary), and
gsfast_test now also covers quads, uploads in random pieces over drawn pages, and denser texels
(each deliberate break tried is caught). What is left is mostly the four full-screen blended art
layers (~785,000 blended pixels a frame) plus the frame copy and clear: the CPU model's floor. The
real fix for that is the GXM renderer, not more of this model. Not yet measured in Vita3K.

## The GPU renderer (session 136, 2026-10-26)

Since session 136 the picture is drawn by the SGX543 (host/vita/gxm.c), not by the GS model on the CPU.
The recorder (host/null/pipes.c) takes each GIF kick and transfer, include/platform/gxmrec.h turns a
frame of them into GXM calls (scenes on each render target, texture and palette uploads, programs,
uniforms, draws), and gxm.c runs them with sceGxm on vita2d's context; the display target is then drawn
as one quad into vita2d's scene. The GS model keeps GS memory (uploads, page bookkeeping) but draws no
pixels. `gpu=0` in config.txt brings back the software picture.

**Shaders are compiled on the device.** vitasdk has no shader compiler, so the Cg that host/port/shadergen.c
writes is compiled at run time by Sony's SceShaccCg through vitaShaRK (libvitashark, already in vitasdk).
It needs **`ur0:data/libshacccg.suprx`**, which is not in this repository and must never be committed
(Sony's binary). Get it as the PSM runtime's module, decrypted: see
[AnimMouse/SceShaccCg](https://github.com/AnimMouse/SceShaccCg) (thanks) or the ShaRKBR33D plugin. In
Vita3K on a Mac the folder is `~/Library/Application Support/Vita3K/Vita3K/fs/ur0/data/`. Without it,
only shaders already in the cache can be used, and the app falls back to the software picture when the
vertex shaders are missing.

- **The cache**: each compiled program is kept as `ux0:data/kh1/shaders/<FNV-64 of its source>.gxp`, so
  a shader compiles once (the first sight of a new one is a frame hitch, ~0.4 s in Vita3K).
- **vitaShaRK's size argument**: `shark_compile_shader_extended(src, &size, ...)` reads `*size` as the
  source's length (0 gave "fatal internal error" in s136a). The host mock enforces it.
- **Frame reads** (programmable blending: a FETCH blend or a per-bit FBMSK, renderer-spec 4.13 "Session
  128"): SceShaccCg's own diagnostics give the form, `__nativecolor void main(...)` with
  `__regformat unsigned char4 dst : FRAGCOLOR` and `out __regformat unsigned char4 ocolor : COLOR`
  (bytes, not / 255). The `__nativecolor` keyword needs SceShaccCgExt's extensions: gxm.c tries
  `shark_init` (the extensions) first and `shark_init_simple` after (`shacc_ext=0` skips the first).
  When a frame read's shader still fails, it draws a stand-in (FBMSK written whole, and the
  fixed-function blend when blend.h has one); only a true FETCH blend with none (e.g. ALPHA 0x4D,
  Cd x As + Cd) is skipped.
- **The log**: the watchdog's `gpu:` line (ms in gxm.c, frames, scenes, draws, skipped) and `cpu:` line
  (ms recording kicks, building and submitting the frame's commands, presenting, and the slowest frame
  of the 2 s with its vblank wait left out). The rest of the 2 s, less the vblank wait, is the game and
  the chain walk.
- **The host check**: `tools/vita/gxmcheck.sh [ISO] [FRAMES] [EVERY]` builds gxm.c with vitasdk's headers
  against a mock sceGxm (tests/host/gxm_mock.c: shaders run with kh1_shader_run, a software rasteriser
  with GXM's rules) inside the host runner, and compares the display and the 3D target with the GS
  model every EVERY frames. Fake disc, 1500 frames: 15 checks; the 3D target matches on all, the display
  differs in one row (y 1, up to 88 levels) on 3 of them, the same with gxm.c and shadergen.c as of
  0432040 (so not from the changes below; not traced yet).
- **Skips are logged**: each reason's first case in full (`kh1-gxm: first skip, ...`: the ring, the
  target, the depth buffer, the scene, the pipeline, the texture, the range, the state) and the counts
  every 600 frames (`skipped so far`).
- **Memory**: surfaces (targets, depth) take CDRAM's 48 MiB first and LPDDR's 32 MiB when no CDRAM block
  is large enough (the new game's 768 x 1135 depth found none: 3% of draws were drawn, 93% after).
  Render target objects are kept for up to 32 sizes, the least recently used one dropped, never one
  used this frame.
- **Whole pictures only**: the GPU draws a frame's calls at the next vblank, so the display target can
  be shown half drawn (the new game's text flashed). At each frame copy (the game's DISPFB switch,
  display.c's `kh1_vita_frame_copied`) the display target is copied by a GPU scene into a target of its
  own (`kh1_vita_gxm_latch`), and only that one is presented.
- **Palettes at the draw's CSA**: a 4-bit draw reads the CLUT buffer at its own CSA whether or not its
  TEX0 loads (CLD 0 reuses the buffer). The recorder bound only the last load's palette, so the new
  game's menus showed valid but wrong kana; pipes.c now compares each indexed draw's entries
  (kh1_gsmem_clut) with the bound slot's and binds theirs (`kh1_cmd_palette`, a CLUT command never
  read back), as present.c's `pal_for` does for the software picture.

In Vita3K (M3 Mac): the title and its menus hold ~60 fps (slowest frames ~15 ms; was ~20 fps with the
software picture); the new game's settings menus (difficulty, camera, vibration, sound, the summary)
show the right text at ~50-60 fps, and the new game runs on, black where its 3D would be (the VU1 path
is not replaced). The remaining skips (~5% of draws in a 7,000-frame run) are mostly textured points with the "region t"
sampler (no shader yet), a target sampled while drawn into, and one 0-wide target. **Not checked yet**: a real Vita; whether the
frame-read shaders compile with the extensions; colour load behaviour between scenes, the region clip's
granularity, a CT32 target sampled as a texture (its alpha reads back doubled: the shader key has no
"from a target" bit), points and lines. Vita3K logs one `sceGxmTextureSetMinFilter` UNSUPPORTED and an
`EXC_BAD_ACCESS` a frame that it handles itself (its own memory tracking, the game runs on).

## The 3D path (session 137v, 2026-10-27)

The game's 3D (the rooms' meshes, the characters, the lens grid) reaches the GS only through VU1: the
channel 1 chains carry VIF codes that fill VU1's data memory and start its microprograms, which
transform, light, cull and clip and XGKICK GIF packets (PATH1). host/port/vu1.c now runs that machine:

- **VIF1** keeps its registers across sends (CYCLE, MODE, MASK, ROW, COL, BASE / OFST / TOPS / TOP /
  ITOP / DBF) and runs UNPACK in every format (masks, offset and difference modes, skipping and filling
  writes, FLG / USN; V2 sets z = x and w = y, V3's w is the next element), MPG, MSCAL / MSCALF / MSCNT
  (TOP = TOPS, ITOP = ITOPS, DBF toggled, TOPS = BASE or BASE + OFST). The programs are the user's own
  bytes (uploaded by the chains), never this repository's.
- **VU1** is an interpreter with the timing the hand-scheduled programs rely on: a pair a cycle, a
  stall when a VF field written less than 4 cycles before is read, MAC and clip flags seen 4 cycles
  after issue (a FIFO), Q 7 cycles after DIV / SQRT (13 for RSQRT), P 18, a branch on a VI that an
  integer instruction in the pair before it wrote sees the old value, the lower instruction reads the
  registers before the upper one writes, VU floats (no inf / NaN / denormals). vf00 is (0, 0, 0, 1)
  from the start (without it every Q was 0 and every vertex landed at 0, 0).
- **XGKICK** copies the whole packets (to EOP) out of data memory; host/null/dmawalk.c hands them to
  the same GIF reader PATH2 / PATH3 use, so the register file, the GS model and the GPU recorder see the
  meshes as any other draw. `KH1_HOST_VU1=1` turns it on in the host runner (N > 1: verbose levels,
  `KH1_HOST_VU1_FRAME=F` dumps frame F's kicks, `KH1_HOST_VU1_SNAP=R` writes run R's start state to
  vu1_snap.bin), the Vita's `vu1=` (default 1).

Findings, each found on the real disc in Dive to the Heart's first station (frame 6399 of
tests/host/pads/dive.txt; the game draws on odd frames only, 30 fps):

- **The walk padded DIRECT and MPG data to a qword.** Room meshes put DIRECT anywhere (e.g. the code at
  0x95e9808, its data at 0x95e980c): padding desynced the stream ("not a VIF code", runaway programs).
  VIF data follows its code with no padding; the walk no longer pads.
- **The VI backup is for integer instructions only.** PCSX2's rule (a branch reads a VI as it was
  before the pair just before it) applied to FCAND / FCOR / FMAND as well culled nearly every
  triangle: P0 (the stations' floors) tests backfaces with `fmand vi13, vi13` then `ibne vi13` in the
  next pair, and clips with chains of `fcor vi01` / `ibne vi01`; every Dive program has the pattern
  (P0, P1, P2, P3, P4, P6, P7, P11 ... P20). With the flag instructions' VI seen at once the floor,
  Sora, the sword and the effects come out where the GS shows them.
- **Visible vertices have w > 0**: P0's CLIP is against |w|, and a vertex with w < 0 sets -z, so a
  floor strip behind the camera is (correctly) all ADC.
- **Sora's textures stream into the slot capture's pages** (TBP 0x3600, CLUT 0x3700, PSMT8 128 x 128,
  uploaded before each part), the GS memory the shadow's capture pass renders to. The recorder sampled
  the target's pixels (a garbled rainbow) and read the palette back from it; host/port/cmdbuf.c now
  marks GS pages an upload writes after the target's last draw and takes those textures and CLUTs from
  GS memory (the caches).
- **The GPU mock scribbled an unstored depth buffer.** A scene that only tests depth (the walls, ZTST
  ALWAYS) neither loads nor stores it; on the GPU the memory keeps the earlier store, which the next
  scene loads. tests/host/gxm_mock.c now leaves it (it made the platform fail its depth test).
- Program use per drawn frame (frame 6399): 730K instruction pairs (794K VU cycles, 2.6 ms of the PS2's
  VU1): P0 268K (the floor), P18 222K (Sora), P4 86K (the walls, clipped into fans), P11 84K, P10 42K,
  P1 21K, P2 8K. No skinning programs (P13 / P14 / P17) run in Dive.

**Speed: too slow for the Vita as it is.** The interpreter costs ~435 host instructions a pair (callgrind
over P0 / P4 / P18 snapshots; 30 ns a pair on the x86 host), ~0.3 s of CPU a drawn frame on the
Vita's A9 by that count. The plan: (1) VIF1 / VU1 and the GS feed on a second core (the game thread then
only queues the chains), (2) the programs translated to C at build time from the user's own ELF (keyed
by a hash of micro memory at MSCAL, the interpreter as the fallback and the reference that the
translation is checked against, bit for bit, on snapshots). Until then the Vita build shows the 3D at a
few frames a second.

**Vita3K, 2026-10-27** (branch at c53bb99, Japanese disc, `vu1=1`, `pad=ux0:data/kh1/dive.txt`,
`frames=8000`): the first Dive station draws, Sora on the stained-glass platform with both
pedestals and the dialogue. The title and menus run at about 56 fps; the 3D from frame 5000 at
about 11.5 fps, slowest frame 176 ms (189 ms recording, 169 ms the frame's commands). Found there:
the REGION_REPEAT fragment shader read `u_c` without declaring it, so Vita3K's compiler refused it
and its draws were skipped ("no pipeline"); fixed, with a shadergen_test check. Still open: up to
77k "no texture" skips (the first, target 1 sampled by its own scene), one "no render target"
skip (target 5, rt 7, 0 x 448), and Vita3K's write-protect / EXC_BAD_ACCESS messages, which do
not stop the game. Building the VPK needs `out/gen/data.tsv` from the PS2 build, so a Mac without
ee-gcc builds it in a Linux container.

**The programs as C (session 137v).** tools/vu/vu1_translate.py reads the 22 VU1 programs out of the
user's own ELF (tools/vu/find_vu1.py) at build time and writes out/gen/vu1_tr.c (never committed),
which host/port/vu1.c includes under `KH1_VU1_TR` (tools/host/census.py regenerates it when stale).
The interpreter's timing is resolved statically: each node of the generated code is a pc plus an
abstract pipeline state (pending VF writes, the flag FIFO, Q / P and their latencies, the VI backup,
the branch delay and the E bit), with pending writes nothing reads before they land dropped, dead
values forgotten, the MAC flag computed only by the FMACs whose flag a later FMAND / FMEQ / FMOR reads,
and JR targets taken from BAL links and `IADDIU r, vi00, addr` constants. 20 of the 22 programs
translate (P9 and P21 jump outside themselves and stay on the interpreter). At MSCAL micro memory is
matched against each program's words (cached until the next MPG), so a program the chains change is
never run as C. `vu1tr=` (`KH1_HOST_VU1TR` on the host): 0 the interpreter, 1 the C (default), 2 both,
each run compared register for register and memory for memory (`tr_check`): 0 differences over ~800K
runs to frame 8000 on the host. The four lanes of an FMAC are one NEON operation on ARM (`vu_op`; the
scalar code elsewhere), 0 differences over 757 dumped runs under qemu-arm (`KH1_HOST_VU1DUMP=DIR:N`).
On x86 a pair costs ~5 ns translated against ~35 interpreted; i386 builds take `fpmath=sse` for
vu1.c so both paths round as IEEE single.

**Vita3K, English disc, 3d-e (NEON):** 23 to 24 fps from frame 6400 (the interpreter's was 11.5): of
each 2 s, ~515 ms in VU1 programs (~245 of it handing kicks to the recorder), ~600 ms in the frame's
GXM commands, ~140 ms recording, ~500 ms waiting for vblank. Texture skips fell from ~134K to ~1K
(the loose texture slots raised from 8 to 32). One fragment shader (P8, modulate, ST/Q, REGION_REPEAT
on both axes, fog, discard where GREATER fails) stops SceShaccCg with "fatal internal error" at every
optimisation level (~4,900 skipped draws); `shadertest=1` bisects it, and meanwhile its draws use the
plain wrap.

**3d-f to 3d-i (Vita3K, English disc).** `shadertest=1` showed the "failing" shader compiles at start: the 18
fragment shaders SceShaccCg refused later (all "uv discard-fail greater pre 320 as" plus the region one) were
a heap the English disc's stale frees had corrupted (host/null/pipes.c's caches from malloc, PR #153); with
that fix 0 invalid reads / writes and 0 refused shaders, and every texture of the first station is right.
Restarting the compiler after a failure (`shacc_restart=1`, off) hangs Vita3K (a NULL read in the reloaded
module). Uploads into a target are now written once before the target's next use (GS memory is read as the
frame left it, so each upload of a frame wrote the same bytes and waited for the GPU), and a scene that
neither loads nor stores its depth runs on the spare depth buffer. Still open in Vita3K: the stained-glass
floor (the region shader's draws) is black on every other drawn frame (the cause: one-byte enums, "The
flashing floor" below), with the interpreter as with the
translated programs, while tests/host/gxm_mock.c (now running scenes late, at sceGxmFinish, on memory as it
is then) draws it every frame; and ~310 ms of each 2 s in the frame's transfers (texture and palette uploads,
which Vita3K's texture cache watches). Both are to be checked on a Vita.

**Session 140 (Vita3K, English disc, 2026-10-28; branch at 384164c, main with PR #150 merged).**
config.txt `pad=ux0:data/kh1/dive_en.txt` (the host's own English route: its `goto` lines work here too,
since the Vita plays scripts through host/null/pad.c), `frames=91000`. The run was stopped by hand at
frame 75,283 (4,055 s, ~18.6 game frames a wall second), still advancing: Dive to the Heart played
through and Destiny Islands reached on the Vita build, no stall or crash from the game (two earlier
attempts were cut off by the Mac-side watcher, not by the game). 186 disc reads. Each 2 s window: ~1,100
to 1,350 ms in the DMA walks (VU1 and recording), 280 to 460 ms in the frame's GXM commands, 70 to 90 ms
the game's own code, ~330 ms the vblank wait; slowest frame 723 ms (waiting on the GPU). Shay saw the
**low frame rate and flashing ground and scenery** on the island. The likely cause of the flashing:
257,849 draws skipped for "no texture" by the end (of 4,574,777): 140,064 a palette texture with no
palette, 107,522 a 512 x 256 texture whose slot holds another (slot 10), 5,025 a scene sampling its own
target, 4,125 a target used as a texture before it was made, 1,113 a 2 x 8192 texture (too big or no
format). A draw skipped one frame and drawn the next flickers. xl_limit.x loaded 7 times with no native C;
opn.dat ended at once (no movie decoder). Vita3K repeats one `handle_access_violation` write-protect line
(Address=0x61501400, 973 times) and `Unhandled EXC_BAD_ACCESS` (62,064 in its console), one page every
time, the game unaffected. Logs kept on the Mac in ~/Downloads/kh1-test/vita3k-s140/.

**Session 141: the flashing ground (host gxmcheck with dive_en.txt to 33,000 on the English disc).** Both
big skips of the Vita3K run reproduce on the host's gxm_mock from the same frames (the palette one from
~28,500, as in Vita3K's log), and both were the recorder's tables, not the GPU:
- **"no palette (slot -1)"** (tex0 ...665423600, a 512 x 512 T4 at 0x3600 read from the "slot capture"
  target's memory): the island loads a new 4-bit CLUT (CBP 0x3FDC, CLD 1) for each ground and scenery
  draw, up to 105 distinct palettes in one frame (frame 30,712, with the command cap below lifted). The
  palette cache had 64 slots and never refills one a draw of the frame reads, so every draw past the 64th
  got slot -1 and gxm.c skipped it; which draws those were changed from frame to frame (the flashing).
  include/platform/palcache.h has 256 slots now (256 KiB of LPDDR for gxm.c's palettes). Also: a draw
  that rebinds the slot bound from an earlier frame's load (CLD 0, the same entries) did no lookup, so
  the slot was not marked used and a later miss of the frame could refill it under a draw the GPU had
  still to read (wrong colours for a frame); `kh1_palcache_use` marks it (tests/host/palcache_test.c).
- **"the slot holds another" (slot 10, 512 x 256 T4 at 0x3300)** and draws missing with no skip line
  at all: from ~30,700 a frame has up to 1,435 commands, and cmdbuf.h's `KH1_CMD_MAX` was 1,024: the host
  run lost 174,639 commands by 33,000 (~400 a frame), draws and the TEXTURE uploads among them (the
  texture cache counted a decode as uploaded whose command never reached gxm.c, so the GPU's slot kept
  the old texture). Now 4,096 commands, gxmrec.h's 16,384 calls, ring.h's 512 KiB of uniforms (a slot
  for each command and pass). The run's summary line (`commands: ... N lost`) is the check: 0 lost to
  33,000, and 0 "no palette" skips (18,628 before).
Left: 2,808 "target 6 as a texture: not made", 604 "2 x 8192 too big", 185 "the scene's own target"
by 33,000. Not checked yet in Vita3K or on a Vita (VPK s141a).

## On a real Vita: the white screen (session 137v, 2026-10-27)

Vita3K reached the title; a real Vita stopped on the white copyright screen after 10 disc reads and
crashed at frame ~960 (C2-12828-1, a data abort in dktitle_00f20a78 unpacking an unfilled buffer).
Logged step by step (builds 3d-l to 3d-p; the game's printf now writes the log itself, host/vita/main.c,
since pointing newlib's stdout at it never took): the title's code ran and queued its loads, but every
load it queued had an empty file name, so KINGDOM.IDX found nothing and no read was made.

The cause: the Vita loads the data segment away from its link address (seg 2 at 0x81300000, linked at
0x811c0000; Vita3K loads it where linked). The functions.tsv / defs_host.c / native-overlay aliases
(`PROVIDE(X = sym + off)` in aliases.ld) were absolute symbols, because ld makes an expression outside
SECTIONS absolute, and the relocatable link then kept no relocation to them: 217 names (dktitle's
strings among them) pointed 0x140000 off on hardware. tools/host/census.py now heads aliases.ld with
`LD_FEATURE("SANE_EXPR")`, which keeps them section-relative; `readelf -s` shows no absolute symbol
left in the image's range. **Anything tested only in Vita3K can hide this kind of bug**: run on hardware.

## On a real Vita: speed (session 137v, 2026-10-28)

Build 3d-r on a Vita reached Dive to the Heart at ~2 fps, with the title's menus at 4-5 fps. The
watchdog's "split" line (host/vita/main.c) divides each 2 s into DMA walks / the frame's commands /
present / vblank wait / the rest (the game's code, gsimage.c's uploads included).

- **Menus**: the rest took 1.2-1.6 s of every 2 s. dktitle uploads its backdrops through
  PlatGsExecLoadImage every frame, ~840,000 pixels: two 512 x 192 CT24 (into the Z buffer's memory,
  which the frame's Z writes), two 512 x 192 CT32, a 512 x 384 T4 and T8 / CLUT pieces. CT24 had no
  bulk path, so every pixel went trx_pixel -> put_at -> wr32 -> mark (48% of the main thread, profiled
  in Vita3K with -finstrument-functions; 36% of the host's instructions a menu frame). Two changes in
  host/null/gsmem.c, each pixel's stored bits and marks as before (the gxmcheck run to the Dive gives
  the same log, host pointers aside):
  - `trx_bulk24`: CT24 / Z24 three bytes a pixel against the kept addresses, a pixel split across
    two pieces too.
  - `kh1_gsmem_image_same` / `kh1_gsmem_image_kept`: a LoadImage of the bytes the same rectangle's
    last one brought, none of its pages written since (page_seq no newer than that upload's end) nor
    drawn (page_drawn clear), would store nothing, so it is counted and skipped. The T4 / T8 / CT32
    backdrops hit; the CT24 pair never does (the Z writes mark their pages drawn).
  On the host a menu frame went from 91M to 46M instructions. Next there: tex_scan's one
  kh1_gsmem_addr a block (10%), kh1_texfmt_convert (11%), the present's read_rect.
- **Dive**: the DMA walks take 1.3-1.7 s of every 2 s (VU1 ~0.7 s, then recording), the commands
  0.4-0.6 s. Done so far: target_upload in 32-row chunks through kh1_gsmem_read_rect, whose T8 / T4
  rectangles now go block by block. Next: the walk itself (vif_word, unpack, the VU1 programs' fin /
  fo, which the Vita's NEON helpers already shorten), then a second core for VIF1 / VU1 and the GS feed.

## GS memory upkeep in GPU mode (session 141, 2026-10-28)

With the GPU drawing (gxm.c), the GS memory model still takes every upload, because the texture and
palette caches, the "loose" textures and the target uploads read their texels from it. A callgrind
profile of the Dive (frames 5000-5060, dive.txt, 4.95G instructions) had about a quarter of the frame
there: kh1_gsmem_image 9.3% inclusive (T8 streams, mark per pixel), pend_flush 12% (target_upload's
read_rect, and the mock's sceGxmFinish; on the Vita the 324 GPU waits were ~90 ms in all), the texture
cache's reads 4.9%, CLUT loads 2.3%, kh1_gsmem_addr 2.8%. Changes:

- **gsmem.c, same output** (gsfast_test compares each with the fast paths off):
  - `addr_rect`: a new upload rectangle's addresses from each block's start plus a per-PSM table of
    the places inside a block (kh1_gsmem_addr is block number x block size + place, each from its own
    coordinates), not the swizzle for every pixel. AT_KEYS 64 -> 256.
  - `scan_pages`: tex_scan takes a texture of whole pages page by page (a page's 32 blocks are 32
    consecutive block numbers, so they lie in two pages at most); it falls back to the block scan when
    two drawn pages name different targets, since the block order picks the first.
  - T8 / T4 upload pieces mark pages inline, `marks` moved once a piece.
  - An 8-bit CLUT load reads its 16 x 16 through kh1_gsmem_read_rect.
- **gxm.c, a fix**: a pending target upload was a rectangle read in the upload's own layout and
  written at BITBLTBUF's (DSAX, DSAY) of the target. Right only for an upload at the target's own FBP
  in CT32 / CT24. The Dive streams T8 textures and CT32 CLUTs at 0x3700-0x3980 into the pages of
  targets at lower FBPs (256 x 192 and 256 x 256, ~40 uploads a frame), so each landed at the target's
  top left, read as CT32. Now each upload's written words are kept per block (a 64-bit mask, the
  target, CT24 or not) and, at the flush, written to the pixel that holds that word in the target's
  CT32 layout (FBP / FBW from the recorder's target key), whole blocks without a swizzle per pixel.
  `kh1_gsmem_read_block` gives a block's 64 words.
  The first version marked each word with a call and flushed one target whenever a block moved to
  the other (the two Dive targets overlap): +4%. Now a whole block is one mask write, an edge block's
  pixels one mask, and a block both targets wait for is written to both.
- **Measured** (real-disc gxmcheck, dive.txt, callgrind frames 5000-5060): 5.51G -> 5.34G with the
  gsmem.c changes (the log identical apart from host pointers), 5.15G with the target uploads too
  (-6.5% in all; kh1_vita_gxm_frame 608M -> 412M). Three display lines' "pixels differ from the GS
  model" counts drop by 1-2; draws, triangles and pixels drawn are unchanged. Left: pend_flush's
  sceGxmFinish in the mock (small on the Vita: 324 waits, ~90 ms in all, 3d-t), the texture cache's
  T8 reads, and the model's upload stores themselves.

### The GS side on a second core (session 141)

host/null/gsqueue.c runs the GS side on a worker thread: the GIF decode (dmawalk.c's gif_block / gif_qword),
the register file (gsregs.c), the GS memory model (gsmem.c) and the command recorder (pipes.c, cmdbuf.c).
The game thread, which still runs the game's code, the DMA walk, VIF1 and the VU1 programs, puts ops into one
ordered ring (an op is a function, its argument words and a copy of its data qwords: a kick's packets, a
GIF chain's blocks, PATH2's DIRECT qwords, the send's start, the HUD shift / stretch, MSCAL's path1 mark), and
the worker runs them in order. On the Vita the worker is pinned to the second core, the game thread to the
first, the watchdog to the third (config.txt `gsq=0` turns it off; it runs only with the GPU renderer).

- **Sync points**: kh1_gsq_sync waits until every op put so far has run. It is called before anything on the
  game thread reads or writes the model: PlatGsExecLoadImage / StoreImage (gsimage.c), the vblank's
  kh1_pipes_frame (the GPU frame, gxm.c's reads of GS memory), kh1_null_hud_wide, the host's summary, and after
  each send when its line or hook reads the model (`!kh1_dma_quiet`, trace 4 / 5, KH1_HOST_TEXDUMP, an
  after-send hook with `kh1_dma_after_send_reads`; the Vita's GPU hook only counts the send, so it sets 0).
- **The send's line and problem bits** come from a count the game thread keeps of each GIF stream (skim_qword /
  skim_block: the packets and where the stream stands, without the writes), so the walk never waits for that;
  when it syncs anyway it checks its count against the worker's (`kh1-host: gsq: ... differs` if not).
- **Ops are never split or joined differently**: each chain block is its own op (gif_block's whole-IMAGE skip
  depends on the blocks), each kick its own (a kick starts a fresh stream), only PATH2's qwords join (gif_qword
  per qword either way). An op larger than half the ring runs on the game thread after a sync.
- **Checks** (host, title-menu fake disc with the user's dktitle.x, 1500 frames): `KH1_HOST_GSQ=1
  tools/vita/gxmcheck.sh` gives the same log as without it (host pointers aside; trace 5 syncs after each send,
  so this checks the ops and copies); `KH1_HOST_GSQ_CHECK=10` (trace 2, quiet, the Vita's frame order) prints a
  digest of the register file, all 4 MB of GS memory and the frame's commands every 10 frames, the same with
  the worker running alongside the game (KH1_HOST_GSQ=1, and with a 64 KiB and a 4 KiB ring) as without.
- **The frame and the uploads on the worker too** (after Vita3K showed the game waiting ~270 ms per 2 s at
  the vblank's sync): the vblank puts the frame's GPU work (kh1_pipes_frame, gxm.c's commands, the latch, the
  present) as the worker's last op of the frame and goes on with the next frame, waiting only for the frame
  before (`kh1_gsq_wait`, one frame in flight). Every GPU call (gxm.c, vita2d) is then the worker's; its
  stack is 2 MiB for SceShaccCg. PlatGsExecLoadImage copies its bytes into the ring (`kh1_gsq_put_bytes`) instead
  of syncing; StoreImage still syncs. The host's KH1_HOST_GSQ_CHECK runs the same order; the digests are the
  same as single-threaded (title fake disc, 1500 frames, 4 MiB and 64 KiB rings).
- **Large uploads back on the game thread** (3d-w on the Vita): with every upload in the ring, the title
  menus' backdrops (two CT24 512 x 192 and two CT32 512 x 192 a frame, 288-384 KiB each) put their copy,
  compare and pixels on the worker on top of the frame's GPU work; the worker was busy the whole 2 s and the
  game waited ~1.6 s of it, the menus at ~12 fps against ~25-30 in 3d-v. An upload of 64 KiB or more
  (`LOAD_HERE`, gsimage.c) now syncs and runs on the game thread as before; smaller ones still go in the ring.
- **The watchdog** adds `gs worker: N ms busy; the game waited M ms for it (K waits)`. The `cpu: ... recording`
  ms are the worker's now, and `vu1: ... passing their kicks on` is the copy into the ring.

## The VU1 feed's speed (session 141, 2026-10-28)

On a Vita (3d-t, 444 MHz) the Dive ran at ~3.4 fps with ~80% of a frame in VU1 and the chain walk
that feeds it, on one core. This pass makes that work cheaper without changing what it produces (the
second core and the VRAM copy are separate threads):

- **Already in main (session 137v's VIF1 feed):** VIF1 data in blocks (`kh1_vif1_data_n`), UNPACK
  fast paths and XGKICK without the copy. This branch first did the same independently; on the merge
  with main main's versions were kept, and tests/host/vu1feed_test.c now checks main's block reader.
- **The GIF reader.** `gif_qword`'s register index went through `% nreg` every qword, a library call
  on the A9 (it has no divide instruction); it now wraps a counter. A quiet walk (the Vita's) no longer
  keeps the list of distinct state values nor writes the send's text.
- **Draw states by hash.** host/null/gsregs.c's `gs_kick` searched every draw state of the send
  with memcmp after each state write (every VU1 packet's PRE PRIM is one); the states now sit in an
  open-addressed table keyed by a hash of the same bytes, the same index coming out.
- **More of the programs on NEON.** The FMACs out/gen/vu1_tr.c still ran field by field (those whose
  MAC flag a later FMAND / FMEQ / FMOR reads, and OPMULA / OPMSUB) go through `vu_ope` / `vu_opbe`:
  four lanes, exact against the scalar form. Where NEON's flush to zero could differ (a result of 0
  with the MAC flag, which the scalar form may flag U; a MADD / MSUB product of 0 from two non-zero
  factors) they answer 0 and the scalar form runs.

Checked: tests/host/vu1feed_test.c (the block reader against the old word reader, kept verbatim in
the test, 40 random streams with every format, masks, modes, filling and skipping writes, MPG, data
split at random points) and tests/host/vu1neon_test.c (vu_ope against the scalar form, 2M random
operand sets weighted to zeros, denormals and the extremes; it runs under qemu-arm when
arm-linux-gnueabihf-gcc is there, in tests/selftest.sh). Outside the repository, as scratch: the walk
with VIF1 / VU1 over random VIF1 chains (UNPACK, PACKED / REGLIST / A+D packets kicked by a small
program, some wrapping VU1 memory, DIRECT, chains cut at random, TTE on and off) gives the same
primitives, state values and counts before and after (x86: 8.7G instructions to 2.1G on that mix, the
draw-state search most of it); and the translated programs from every entry on 3,480 random states,
old and new translation under qemu-arm with NEON, give the same memory, registers, flags and kicks.
**Not yet checked on the disc**: a host run with `KH1_HOST_VU1TR=2` and the gxmcheck log against the
last one, and the frame rate on a Vita (the split line's DMA-walk share).

## The GS worker's own work (session 142, 2026-10-28)

On a Vita (3d-x) the Dive's GS worker was busy ~1.65 s of every 2 s at ~12 frames per 2 s: ~0.7 s recording
(us_record), ~0.47 s the frame's commands (of them ~0.2 s gxm.c's submit, half of that GPU waits), the rest the
GIF decode, the register file and the GS memory model's upload stores; the game waited ~1 s for it. A host
profile of the worker thread alone (callgrind `--separate-threads=yes` on the gxmcheck binary in the Vita's
order: `KH1_HOST_TRACE=2 KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=1000 KH1_HOST_GXM=1000000 KH1_HOST_VU1=1
KH1_HOST_VU1TR=1 KH1_HOST_PROF=5000:60`, en.iso, dive_en.txt; the worker's file is `cg.PID-02`, and as the
binary's symbols do not load, addresses map back with `nm -n`) gave 1,978M instructions over frames 5000-5060:
gs_kick 730M (kh1_pipes_prim 595M, of it the texture cache 244M), the frame 583M (gxm.c 412M, the mock's
sceGxmFinish 239M of it, which the Vita does not pay; kh1_cmd_frame 137M), kh1_gsmem_image 332M. Two changes,
the output the same:

- **Clears** (host/port/cmdbuf.c `cover_cmd`): each rectangle of a pass's leading draws marked its cells by
  testing every cell of the target's 8 x 8 grid; now only the cells from its own corner on. 133M -> 6M.
- **Texture re-checks** (host/port/texcache.c, `KH1TexRaw`; host/null/gsmem.c `kh1_gsmem_tex_raw`): the Dive
  streams a few T8 textures through one slot every frame, so each lookup was a stamp miss that read all the
  texels back through kh1_gsmem_read_rect, hashed and compared them (a hash hit). An entry now also keeps the
  raw words of the pages its texels lie in; on a stamp miss an entry of the same layout whose pages hold the
  same words is the hit (the texels are read from those words only), and only otherwise the old read. The
  slot found is the one the hash would find (one entry per layout and texels). tests/host/texcache_test.c
  runs a second port cache with it beside the first: the same texels and counts on every case. 244M -> ~12M.

Worker 1,978M -> 1,619M (-18%). Checked on the English disc to frame 6500 (dive_en.txt): the gxmcheck log at
trace 5 (host pointers and paths aside) and its 4,758 shots byte-identical; the GSQ_CHECK digests every 50
frames the same with and without the worker, and the same as before. Left on the worker: the upload stores
(kh1_gsmem_image, ~20%: T8 at ~12 instructions a byte, CT32 pieces of ~8 words), the GIF decode and the
recording's vertex work. The next step is a third core: the frame's GPU work (gxm.c, the latch and the
present) behind the worker, which needs the GS memory it reads (pending target uploads, loose textures) and
the caches' new entries handed over as of the frame's end.

### The GPU frame on the third core (session 142)

3d-z (the changes above) on a Vita: the Dive at ~7.8 fps (14-18 frames per 2 s, from 12), the worker ~1.2 s busy
per 2 s, recording ~0.29 s, the frame's commands ~0.29 s, the game waiting ~0.4 s for it. The frame's GPU work
(gxm.c's commands, the latch, the present) now runs on a thread of its own on the third core (gsqueue.h's
`kh1_gpuq`, with the watchdog, which sleeps), while the worker records the next frame:

- **What it reads is a copy of the frame** (host/null/pipes.c `snap_frame`, at the worker's frame op once the
  last job has ended): the commands, passes and targets; the rings' slots stay, since the next frame writes the
  other and the one after waits for this job; the texels of the frame's texture uploads and the palettes of its
  palette fills (`kh1_pipes_frame_texels` / `_pal`: gxm.c read them from the caches at the frame's end, and the
  worker may now drop or refill those entries); and GS memory (host/null/gsmem.c `kh1_gsmem_snap_take`: the
  pages any store reached since the last copy, `dirty_pg`, and every page's stamp; gxm.c's pending target
  uploads, loose textures and their stamps read the copy through `kh1_gsmem_snap_read_block` / `_read_rect` /
  `_tex_stamp`, which share nothing with the live model). gxm.c read GS memory only as the frame left it (its
  first pend_flush too: the last frame's leftovers as this frame left them), so the copy gives the same bytes.
- **Order**: the worker waits for the last job before it copies, so one frame is on the GPU thread while the
  worker records the next and the game runs the one after (the vblank still waits for the worker's frame op).
- config.txt `gpuq=0` keeps the frame on the worker. The watchdog adds `gpu thread: N ms busy; the GS worker
  waited M ms for it (K waits); P GS memory pages copied`; `cpu: ... the frame's commands` and `present` are the
  GPU thread's now, and kh1_cmd_frame (the passes' loads and stores) stays on the worker.
- **Host**: `KH1_HOST_GPUQ=1` runs the recorder's hook (gxmcheck's stand-in) the same way on a POSIX thread, `=2`
  from the copy on the same thread. `KH1_HOST_GXM_HASH=1` makes the stand-in print a hash of the GPU's display
  and 3D targets at each Nth frame instead of comparing with the model (which is a frame ahead with the thread).
- **Checked** (en.iso, dive_en.txt, to frame 6500): gxmcheck at trace 5 with `KH1_HOST_GPUQ=2` gives the same
  log (host pointers aside) and the same 4,758 shots as without; with the worker in the Vita's order
  (`KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=50 KH1_HOST_GXM=50 KH1_HOST_GXM_HASH=1`) the GPU targets' hashes at every
  50th frame (123 of them, to frame 6150) and the GS digests are the same with `KH1_HOST_GPUQ=1` as without,
  and without the worker too.

## The game thread's walk (session 143)

3d-za on a Vita (the Dive, ~8.4 fps): of each 2 s the game thread spent ~1.36 s in the DMA walks, of them only
~0.32 s in the VU1 programs (`vu1:` line); the GS worker was busy ~1.16 s and the GPU thread ~0.29 s. Two findings
and four changes, the output the same:

- **Broken VIF1 chains, printed from the walk.** The log had ~900 sends with a problem in the Dive (~8 a second):
  `N words no VIF code` after a ref list whose first ref (qwc 2) has nonzero upper words, and a `refe qwc 49154`
  chain (786 KB) whose data is ASCII. dma_walk printed each one's whole tag list (~20 lines) through the unbuffered
  log, one sceIoWrite a line, inside the walk's time. The same disc and dive_en.txt give none on the x86 host and
  none on the ARM Linux build under qemu to frame 5060, so the game built or pointed at a wrong chain only on the
  Vita: the one-byte enums ("The flashing floor" below); with that fix a Vita log of the Dive has none. A quiet walk (the Vita's) now prints the first
  `KH1_DMA_BAD_SHOWN` (16) bad sends in full and counts the rest (`kh1_dma_bad_sends`); the host prints all as
  before. The watchdog adds `log: N writes, M ms in them; K bad DMA sends (T so far, ...)`, every log write timed.
- **An ARM profile.** The x86 callgrind profile is no guide here (fin / fo are scalar there, NEON on the Vita), so
  `make vita-armcheck` now builds with `-mfpu=neon` as vitasdk's gcc does by default, and the walk was measured
  under a qemu-arm 8.2 built with `--enable-plugins` and a small plugin counting each thread's executed
  instructions per translation block (frames 5000-5060 as the difference of a run to 5000 and one to 5060, en.iso,
  dive_en.txt, `KH1_HOST_GSQ=1 KH1_HOST_VU1=1 KH1_HOST_VU1TR=1`). The game thread: 1,110M instructions (the spin of
  its waits aside): the translated programs ~555M (P0 255M, P12 140M), clipw 115M, unpack 106M, vif_word 94M,
  kh1_gsmem_image 84M (the large LoadImages, LOAD_HERE), the ring's put and copies ~90M, kh1_vif1_data 43M.
- **clipw on integers** (host/port/vu1.c `fkey`): fin()'s values are finite and never denormal, so a sign and
  magnitude integer orders as the float does; no VFP compare (each a flag transfer on the A9). 115M -> 75M.
- **UNPACK per format** (`unpack_run`): when every element read is in the data (always but a V3's last w), one
  loop per V1-V4 x 32 / 16 / 8 bits with no test of the format or the data's end per element. 106M -> 46M.
- **DIRECT's data in runs** (dmawalk.c `vif_block`, `direct_qwords`): PATH2's words went through vif_word and
  kh1_vif1_data one at a time and into the ring one qword a put; now a run's whole qwords are counted and put
  together (1,024 at most an op; w_qwords decodes them one at a time as before) and kh1_vif1_data_n takes
  DIRECT's words at once. vif_word 94M -> 6M, kh1_vif1_data 43M -> 8M, put 47M -> 4M.

The game thread: 1,110M -> 772M (-30%) on that profile. Checked: the gxmcheck log at trace 5 to frame 6500 on
the English disc (dive_en.txt, `KH1_HOST_GXM=100`) the same as main's, host pointers aside, and its 4,758 shots
byte-identical; the worker-order digests (`KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=50`, 130 of them) and the VU1
counts the same; the ARM build's digests and VU1 counts the same under qemu. tests/host/vu1feed_test.c also
compares clipw with the float form it replaced over 2M operand sets weighted to zeros, denormals, Inf / NaN and
equal magnitudes (a deliberate break of each change is caught). Left on the game thread: the programs themselves
(their FMACs' operands go through memory: `u32 u[4]` then a field copied out, a NEON store and a core load the
A9 pays for), the large LoadImages, and the ring copy of the kicks.

### The GS worker after the enum fix (session 143)

3d-zc on a Vita (the enum fix and the walk above): the Dive at ~11.4 fps, up from ~7.8; the game thread's walks
~0.71 s per 2 s, and the GS worker now the limit, busy ~1.8 s of every 2 s (~0.4 s of that waiting for the GPU
thread), the game waiting ~0.8 s for it. Each log write took ~6 ms (`log:` line, ~90 ms per 2 s, mostly the
watchdog's own lines on the GPU thread's core). The worker under the qemu instruction counter (as above, its
thread's file): 1,199M over frames 5000-5060 (its idle spin aside): kh1_gsmem_image 355M, ~266M of it the T8 loop
of trx_bulk (~425,000 T8 pixels a frame in ~28 uploads, 88% of them changed bytes: the streamed textures land in
pages the targets draw into, so kh1_gsmem_image_same never holds), libc's memcmp / memset / memcpy ~190M,
kh1_pipes_prim 107M (73M of it prim_sig's FNV a byte), gs_kick 95M, gif_qword 73M. Two changes:

- **T8 uploads a run at a time** (gsmem.c trx_bulk): a row's pixels inside one 16-wide block column are one block,
  so one page; each pixel is stored without a test (an equal byte stored again changes nothing) and the page's
  stamp, dirty bit and marks are set once a run, as the per-pixel tests left them. 8 ARM instructions a pixel.
  tests/host/gsfast_test.c's uploads (every PSM, random pieces, over drawn pages) are the same with the fast
  paths off; dropping the run's stamp is caught.
- **prim_sig a word at a time** (pipes.c): only equal signatures matter to batch.h's column groups.

The worker: 1,199M -> 1,002M (-16%; kh1_gsmem_image 355M -> 210M, kh1_pipes_prim 107M -> 56M).

## The frame pacing: the game, the worker and the GPU thread (session 145)

A Vita log of 3d-zd (the Dive, ~15 vblank calls a second, the game drawing on every other one) per 2 s: the
GS worker busy ~1.7 s (~0.28 s of it waiting for the GPU thread, in ~15 waits), the game waiting ~0.6 s for the
worker, the walks ~0.76 s, the vblank wait ~0.33 s. Those numbers hid a serialization, not a slow function: on
the host (`KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=..`, frames 5000-5060) each drawn frame puts ~390,000 words in the
queue and the vblank call after it none (`0 cmds 0 passes`). host/vita/main.c's vblank waited for the last frame
op, so at that empty call the game waited for the worker to finish the whole drawn frame; and the worker, at that
empty frame's op, waited for the GPU thread to finish the drawn frame's job before it could copy the (empty)
frame. The game's next frame and the worker hardly overlapped. Three changes, the GS side's output the same:

- **The vblank waits for the frame op before the last** (host/vita/main.c `frame_end[2]`; the host's
  `KH1_HOST_GSQ_CHECK` order in host/null/main.c the same): at the empty call the game goes straight on, and at
  the drawn one it waits for the drawn frame before (two frame ops in flight, ~3 MB of the 8 MB ring in the Dive).
- **An empty frame's job is posted without waiting** (host/null/pipes.c `empty_frame`, `w_hook_empty`): a frame op
  with no commands, no passes, nothing in either ring, no frame copy and GS memory as the last copy has it
  (gsmem.c `kh1_gsmem_snap_same`: no page stored to, no stamp moved) is copied into a small KH1CmdRec of its own
  and posted behind the drawn frame's job, which may still run. That job reads nothing the worker changes after
  it: no commands means no texels or palettes, the GS memory copy is not retaken until the next op, which waits
  for both jobs; and the rings now move to their other slot only after a frame that wrote them
  (host/port/ring.c `kh1_ring_frame`), so the next drawn frame writes the slot the empty frame names (empty), not
  the one the drawn frame's job reads. gsqueue.c's `kh1_gpuq` holds two jobs (`kh1_gpuq_put` waits only when two
  are posted and not ended; `kh1_gpuq_wait` for all).
- **A late frame skips the vblank wait** (host/vita/main.c): when a vblank has begun since the last wait ended
  (`sceDisplayGetVcount`), the frame goes on at once; at most one frame a vblank still. config.txt `latewait=1`
  waits for the next vblank always, as before.

Checked on the English disc to frame 6500 (dive_en.txt), against #170's head: the worker-order run with the GPU
thread (`KH1_HOST_TRACE=2 KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=50 KH1_HOST_GXM=50 KH1_HOST_GXM_HASH=1 KH1_HOST_GPUQ=1`,
the gxmcheck binary) gives the same 130 GS digests and the same GPU target hashes; empty frames take the new path
(~1,000 of them by frame 5100); the gxmcheck log at trace 5 is the same but for host pointers (`node draw ... arg`)
and its 4,758 shots byte-identical; tests/host/ring_test.c checks the kept slot. **Not yet measured on a Vita**
(3d-ze): the `split` line's wait for the GS worker and the `gpu thread` line's waits should fall.

## The title's backdrop on the GPU thread (session 146, 2026-10-29)

A Vita log of #171's build (Shay's, English disc): the title ran at 60 fps until the art came up (frame ~1160),
then at ~13 (~30 frames per 2.3 s). The GPU thread was busy the whole window (~2,230 ms of ~2,250), ~1,705 ms of
it in gxm.c's draw part (programs, textures, sceGxmDraw) for only ~57 draws a frame, with 0 GS memory pages
copied (nothing the frame stored changed). The cost was `tex_loose`: the title's full-screen CT24 layer at
0x0E00 lies in the depth buffer's pages, which the frame's Z target marks drawn every frame, and a draw's mark
moves a page's stamp (gsmem.c `kh1_gsmem_draw`). So each frame the loose entry's stamp missed and the layer was
read back from the frame copy and converted again, and `kh1_gsmem_snap_read_rect` had none of read_rect's fast
paths (kh1_gsmem_addr and a PSM switch a pixel: 1.56 ms for 512 x 256 CT24 on the x86 host against 0.10 with
the fast path, so ~25-30 ms a read on the Vita's A9). This came in with session 142's GPU thread: before it,
tex_loose read the live model through read_rect's fast path.

- **The copy's version** (gsmem.c `kh1_gsmem_snap_tex_ver`): each take numbers the pages it copies; a texture's
  version is the newest of its pages'. While it holds, the copy's bytes there are the same, so with the GPU
  thread gxm.c's `gs_tex_stamp` (only tex_loose uses it) keys on it instead of the stamp. Exact: the loose
  texels come only from the copy's bytes. Without the GPU thread (`gpuq=0`) the stamp as before.
- **The copy's read_rect through read_rect's fast paths** (gsmem.c `rect_in` from either memory, its own split
  slot `SPLIT_SNAP` and tables, the T8 / T4 in-block tables made by the GS side's thread before any copy is read).
- tests/host/gsfast_test.c: 200 random rectangles from the copy against the live read_rect (every PSM, the
  0x4000 wrap), and the version: a draw's mark keeps it, a write moves it only at the next take, a write
  elsewhere keeps it.

On a Vita (s146a): the GPU thread ~100 ms busy per 2 s (from ~2,230) and the draws column ~43 ms (from ~1,705),
but the title only ~15 fps (from ~13): the game thread now the limit, ~1.2-1.5 s per 2 s of "the rest" and
~0.8 s waiting for the GS worker (busy ~0.88 s; LoadImage syncs, two a frame).

### The CT24 backdrops' uploads (session 146)

A callgrind profile of the game thread (en.iso, the Vita's order `KH1_HOST_TRACE=2 KH1_HOST_GSQ=1 KH1_HOST_GPUQ=1
KH1_HOST_VU1=1 KH1_HOST_VU1TR=1`, `KH1_HOST_PROF=1260:60`, the gxmcheck binary, `--separate-threads=yes`): 416M
instructions over the 60 frames, 80% kh1_gsmem_image and 12% gsimage.c's load_image: the two 512 x 192 CT24
backdrops through trx_bulk24 every frame (~200,000 pixels). They are the same bytes each frame, but
kh1_gsmem_image_same refused them: their pages are the Z buffer's, which the frame's Z target marks drawn (and
a draw's mark moved page_seq, which the check also read).

- `kh1_gsmem_image_same` now checks `wr_pg` (gsmem.c: seq at each page's last store, set wherever dirty_pg
  is; a draw's mark is not a store) instead of page_seq, and allows a draw's marks: on a skip it clears the
  upload's bits (psm_bits) on each page the rectangle's pixels lie in (`at_key.pg`, a page bitmap made with
  the addresses), with marks moved, as the pixels' stores would (mark with the bytes unchanged: the stamp
  stays). `kh1_gsmem_image_kept` moves seq after it stamps, so any later store is newer.
- tests/host/gsfast_test.c: random uploads (CT24 / CT32 / T8 / T4 / T8H / CT16) of kept bytes or changed
  ones, interleaved with draws over their pages and pixel writes, run with the skip and with every upload
  whole: the same pixels, drawn bits per page and PSM, textures' targets and stamp moves after every 8 ops
  (364 skipped, 92 over a draw's marks). Refusing marked pages (the old rule) or not clearing the marks is
  caught.
- Measured: the game thread 416M -> 40M over those 60 frames (left: libc's memcmp, the skip's byte
  compare of ~2.5 MB a frame). The worker-order run (`KH1_HOST_GSQ_CHECK=50 KH1_HOST_GXM=50
  KH1_HOST_GXM_HASH=1`, dive_en.txt) gives the same GS digests and GPU target hashes as main's.
- **On a Vita (s146b)**: the title with its art up at ~43 fps (~88 frames per 2 s, from ~15): the GS worker
  ~335 ms busy per 2 s (from ~880; its ~30 ms a frame before was not its own instructions, whose host profile is
  ~0.3M a frame, so most likely the game thread's uploads' memory traffic and the LoadImage syncs), the game
  waiting ~285 ms for it in ~175 waits, the GPU thread ~130 ms, no vblank wait: the game thread is still the
  limit (~1.75 s of "the rest" per 2 s, ~20 ms a frame; the skip's ~2.5 MB memcmp a frame is in it).

### The skip's compare on the A9 (session 147)

The x86 profile above showed the skip's compare as small because glibc's memcmp is vectorised. **vitasdk's
newlib memcmp is a C loop** (`arm-vita-eabi-objdump -d` of libc.a's lib_a-memcmp.o): a word every ~10
instructions when both pointers are word aligned, a byte every ~6 when either is not. On the title, the game
thread's large LoadImages (the two CT32 512 x 192, the two CT24 512 x 192, the menu's 512 x 32 strips: ~2 MB a
frame, each over gsimage.c's LOAD_HERE) are all compared that way, so ~5M+ instructions and ~4 MB of reads a
frame, most of the ~20 ms.

- **host/null/bytesame.h** `kh1_bytes_same`: equality only, on ARM with NEON 256 bytes a step (the two runs'
  XORs ORed into one register, moved to a core register once a step, since a NEON -> core move stalls the A9;
  prefetches 512 bytes ahead), the tail through memcmp; elsewhere memcmp itself. kh1_gsmem_image_same uses it,
  and same_pool's runs now start 16-byte aligned (the pool is aligned(16), each run's size rounded up).
  tests/host/bytesame_test.c checks it against memcmp (~200,000 cases: lengths 0-1,300 and ~288 KiB, both
  runs at every alignment mod 16, one byte changed anywhere, at a step's end and in the tail) on the host and,
  in tests/selftest.sh, under qemu-arm with NEON; reading one 16-byte piece of a step twice instead of the
  next is caught. Note that `gcc-multilib` (for the tests' `-m32`) and `gcc-arm-linux-gnueabihf` conflict on
  Ubuntu 24.04; the ARM test can be built with `clang --target=arm-linux-gnueabihf -mcpu=cortex-a9 -mfpu=neon
  -mfloat-abi=hard -fuse-ld=lld -static --sysroot=/usr/arm-linux-gnueabihf` (`libc6-dev-armhf-cross`
  installed), as session 147 did.
- **The watchdog's `large uploads:` line**: of "the rest", the game thread's time in those LoadImages (the sync
  before each is in "waiting for the GS worker"), how many, how many unchanged, their KiB (gsimage.c
  `kh1_gs_load_us` and the counts).
- Checked on the English disc (dive_en.txt to frame 6500): the worker-order run with the GPU thread
  (`KH1_HOST_TRACE=2 KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=50 KH1_HOST_GXM=50 KH1_HOST_GXM_HASH=1 KH1_HOST_GPUQ=1
  KH1_HOST_RECQ=1`, the gxmcheck binary) gives the same GS digests and GPU target hashes as main's. On x86 that
  checks only the pool's alignment (the compare is memcmp there); the NEON form rests on the unit test.
- **On a Vita (s147a)**: the title with its art up, before the menu, at ~58-60 fps (~126 frames per 2.1 s, from
  ~88), with 0.4-1.1 s of vblank wait per 2 s left. The `large uploads:` line: ~470-640 a window, all unchanged,
  ~1.1-1.5 s per 2 s, so the NEON compare still runs at only ~125 MB/s (~2.3 ms per 288 KiB): memory-bound on the
  game's source bytes and the kept copy, still the game thread's largest item. With the menu fading in and up
  (frames ~1400-2000): 27-47 fps (from ~25-28), the GS worker busy ~0.9-1.3 s per 2 s and the game waiting
  ~0.6-1.2 s for it: the worker is the limit there.

### The menu's palette loads (session 147c)

**On a Vita (s147b/c)**: with the menu up, the GS worker is busy ~1.2-1.3 s per 2 s and the game waits ~1.1 s
of it (~190 waits); the `gs worker ops:` line (gsqueue.c's per-op times, the watchdog's) puts ~940 ms of that in
w_block, the GIF decode. The one-frame send dump shows why: the menu's text is ~60 glyph sprites a frame, each
with a TEX2 of CLD=1, so each glyph reloads its 16-entry CLUT and runs the hooks behind it (pipes.c on_clut:
kh1_gsmem_clut, kh1_palcache_get, a recording op; pal_loaded; and pal_of per draw). The menu's own host profile
(callgrind on the gxmcheck binary, `KH1_HOST_PROF`, dive_en.txt frames 2050+, thread 3 the worker): 673M
instructions per 60 frames.

- **gsmem.c's CLUT cache**: kh1_gsmem_tex0 keeps the last 64 loads' source blocks (by CBP, CPSM and 4/8-bit),
  each with a copy of its GS memory words and its converted entries. A load whose blocks still hold the same
  words (kh1_bytes_same in place) takes the kept entries instead of re-reading the rectangle, and a load
  identical to the one already in the CLUT buffer (same entries, same CPSM / CSA) skips the copy. The reset
  drops them; a CLUT version moves with every real change for kh1_gsmem_clut's memo.
- **palcache.c's recent slots**: kh1_palcache_get tries the 4 most recently used slots before its scan; a
  hit updates the slot as the scan's would.
- Host worker on the menu: 673M -> ~233M instructions per 60 frames. What is left: kh1_gsmem_clut (~56M, its
  memo misses since the glyphs alternate palettes), memcmp (~25M), palcache (~21M).
- Tests: gsfast_test's CLUT section (6,000 loads over 4 CBPs, CT32 / CT16 / CT16S, 4- and 8-bit, random pixel
  writes between, repeated and alternated loads, two TEXAs) checks every fast load's kh1_gsmem_clut answers
  against a slow load's; palcache_test runs 200,000 random gets with and without the recent slots and
  checks the results and the cache state stay the same.
- Checked on the English disc (dive_en.txt to frame 6500, the worker-order run above): all 130 GS digests and
  260 GPU target hashes are the same as main's.

### The New Game pages (session 147d)

**On a Vita (s147d)**: the title menu at 60 fps (126-129 frames per 2.1 s, ~0.9 s of vblank wait per 2 s, the
worker ~0.34 s busy). After a choice, the New Game pages (still dktitle.x, nothing loaded until the opening at
~frame 2,500) at 32-53 fps: the worker busy ~1.0-1.3 s per 2 s, ~0.7-0.9 s of it in w_block, and the game waiting
~0.8-1.1 s for it; the game thread's `large uploads:` ~0.65-0.93 s per 2 s, all unchanged. The send dump: ~220
sends a frame, ~140 of them glyph sprites with a CLUT load each (dive_en.txt's frames 2,002-2,400 on the host,
which the 147c profile at 2,050 had already measured: it was this screen).

- **gsmem.c**: each kept CLUT also keeps kh1_gsmem_clut's converted answer (by how it was asked and TEXA), named
  by an id that is never reused (kh1_gsmem_clut_id); the glyphs' alternating palettes each convert once.
- **pipes.c / palcache.c**: the palette slot each id was got in, with the slot's gen (new at each fill, never
  reused): while the gen holds the slot holds those entries, so the lookup is `kh1_palcache_hit`, the state update
  the get's hit makes, without the hash, the 256 slots' scan or a compare; the per-draw check against the bound
  slot likewise.
- **cmdbuf.c cover_cmd**: a rectangle's covered cells by rows (the columns found once), not cell by cell.
- texcache.c's raw and texel compares and pipes.c's palette compare through kh1_bytes_same (NEON on the Vita).
- Host worker on those pages: 232M -> 158M instructions per 60 frames.
- **gsimage.c** (s147f): a large upload's compare (after the sync, the worker idle) shared: its first half on
  the worker, the rest on the game thread, then a sync for the answer. Replaced in s147h (below).
- Tests: gsfast_test checks that every id kh1_gsmem_clut_id gives back comes with the same entries (6,000 loads);
  palcache_test runs a third cache as pipes.c uses it (known slot and gen, kh1_palcache_hit) and checks its answers
  and slot states against the plain gets over 200,000 gets.
- **On a Vita (s147f / s147g)**: the menu at 60 fps with ~1.3 s of vblank wait per 2 s; the game thread's `large
  uploads:` ~0.64 s per 2 s (from ~1.0 s: ~280 MB/s for the two halves together, the worker's half ~0.7 s of its
  time). The New Game pages at 60 fps (126-131 frames per 2.1 s, ~1 s of vblank wait), but for the first ~4-6 s
  after the choice (51-58 fps: ~26,000 w_block a window against ~18,000 once the pages settle, the worker busy
  ~2 s per 2 s; Shay notes that stretch may have been the Load Game screen). The watchdog's new `gpu waits:` line (gxm.c's sceGxmFinish by where) puts all of the pages'
  GPU waits at the frame's start, none at target uploads, CLUT readbacks or blits.
- **The syncs before the large uploads (s147h)**: each of the ~5 a frame waited for the worker to empty its queue,
  so the game and the worker took turns (the game waited ~1 s per 2 s in them on the first New Game page).
  gsimage.c `load_big` now keeps each large upload's bytes on the game thread (8 kept, by BITBLTBUF, TRXPOS, TRXREG
  and size) with a generation. The same bytes again (compared there, no sync) go to the worker as an op naming
  the generation and the kept copy; kh1_gsmem_image_same matches the generation the rectangle's kept bytes came
  with (gsmem.c `kh1_gsmem_image_gen`, kept by kh1_gsmem_image_kept) instead of comparing. New bytes are copied in
  after a sync (no op reads a copy then), with a new generation, and the worker uploads them from the copy.
  gsimage_test loads 12 rectangles 400 times with the queue on (bytes the same, changed, changed after the call,
  pixels written into the rectangles between) and checks GS memory against the bytes loaded; matching any
  generation is caught.
- **On a Vita (s147h)**: the title, the menu and the New Game pages all at 60 fps (128-129 frames per 2.1 s), the
  first New Game page included (the worker busy ~2.0 s per 2 s there, the game waiting ~0.25-0.55 s, still 60).
  The one slow window was s147b's send dump itself (~1.6 s of log writes); s147i takes the dump out.
- Checked on the English disc (dive_en.txt to frame 6500, the worker-order run above), at s147e, s147f and s147h:
  all 130 GS digests and 260 GPU target hashes the same as main's each time.

## The recording on the third core (session 146)

A Vita log of 3d-ze (the Dive) per 2 s: ~18 drawn frames; the GS worker busy ~1.7 s, the game waiting ~0.6 s for it;
the GPU thread busy only ~0.45 s, so the third core sat idle ~75% of the time. An ARM profile of the worker (the qemu
instruction counter of session 143, `KH1_HOST_TRACE=2 KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=1000 KH1_HOST_GPUQ=1
KH1_HOST_VU1=1 KH1_HOST_VU1TR=1`, en.iso, dive_en.txt, frames 5000-5060 as the difference of two runs): 999M
instructions, of them the command recorder ~300M (kh1_pipes_prim and what it calls: the port draw state, the
primitive's GPU vertices, the batcher and the commands, ~3,100 kicks a drawn frame), kh1_gsmem_image 205M, the GIF
decode and register file ~260M, libc's memcmp / memcpy / memset ~190M. Three changes:

- **The recording on the GPU frame's thread** (host/null/gsqueue.h `kh1_recq`, host/null/pipes.c): a second ordered
  queue of the gsq's kind whose ops run on the GPU frame's thread between its jobs (a posted job first, so the frame
  before's GPU work is not held up). The worker's side of a kick (kh1_pipes_prim) builds the draw's registers and
  compares them with the last kick's as before; a change puts a state op (the registers, SCISSOR and XYOFFSET), then
  the kick puts a primitive op (PRIM, the vertex count and the queued vertices; the next kicks of the same PRIM and
  count join it). The recorder's side (r_state, r_prim) does what kh1_pipes_prim did after the compare: the port draw
  state and pass, primitive assembly, the GPU vertices, kh1_cmd_prim. What reads GS memory stays on the worker and
  hands the op its answer: the texture cache lookup (r_texture: the slot, decoded, the texel count), the palette cache
  (r_palette, r_clut, with the bound palette slot kept on the worker's side, `a_pslot`), the transfers (r_upload).
  The ops read only their arguments and the recorder. kh1_pipes_frame (and kh1_pipes_recorder / _batcher / _report)
  first waits for the queue (kh1_recq_sync), so the frame op, its copy and the reset see the recorder as before;
  the GPU frame's job runs on the same thread, so the rings' slots and the commands it reads are never written while
  it runs. gsqueue.c's ring is now a struct (KH1Q) both queues use; the GPU frame's thread sleeps on one semaphore
  for either work, the recording queue's producer on a third. config.txt `recq=0` keeps the recording on the worker;
  with the queue on, the kicks are not timed one by one any more (two clock reads a kick) and the watchdog prints
  `recording: N ms on the gpu thread; the GS worker waited M ms for it (K waits)` (the `cpu:` line's recording is
  then 0). Host: `KH1_HOST_RECQ=1` with `KH1_HOST_GPUQ=1`.
- **PATH2's IMAGE data in one piece** (host/null/dmawalk.c `w_qwords`): the Dive's texture streams come through VIF1
  DIRECT, whose qwords went through gif_qword one at a time, a kh1_gsmem_image call a qword (~285,000 calls a second
  of game); now a packet's IMAGE qwords in the op go in one call, as gif_block already did for the GIF channel.
- **The palette cache's hash a word at a time** (host/port/palcache.c): FNV a byte (1,024 multiplies for a 256-entry
  CLUT, ~22M); the hash only picks which slots `same()` compares.

The worker on that profile: 999M -> ~680M (its idle spin aside: it now waits for the game thread under qemu), the
GPU frame's thread +~270M. tests/host/gsqueue_test.c puts ops of random sizes through both queues (joined runs,
ops past half the ring, wraps, jobs between) and checks their order and data. Checked on the English disc
(dive_en.txt) against #171's head: the worker-order run with the GPU thread (`KH1_HOST_TRACE=2 KH1_HOST_GSQ=1
KH1_HOST_GSQ_CHECK=50 KH1_HOST_GXM=50 KH1_HOST_GXM_HASH=1 KH1_HOST_GPUQ=1`, the gxmcheck binary) to frame 6500 gives
the same 130 GS digests and GPU target hashes with `KH1_HOST_RECQ=1` and without, and the same run with
`KH1_HOST_VU1=1 KH1_HOST_VU1TR=1` (the Dive's 3D, where most kicks are) to frame 5600 the same with the queue as
main's without. **Not yet measured on a Vita** (3d-zf): the `gs worker` line's busy time and the `split` line's
wait for it should fall; the game thread (the VU1 programs, clipw, its LoadImages) is likely the limit next.

On a Vita (3d-zf, the Dive): the game's wait for the GS worker fell from ~740 to ~340 ms per 2 s, the recording
~400 ms on the GPU thread with the worker waiting ~12 ms for it; ~17-20 fps. The game thread is the limit: the VU1
programs ~0.9-1.2 s of every 2 s (`vu1:` line). Bursts of ~6 s at ~7 fps, the GPU thread's draw part ~1.7 s per
2 s for ~300 draws, were the title's loose-texture re-read ("The title's backdrop on the GPU thread", #173): a
count of `tex_loose`'s reads on the host (the gxmcheck binary, dive_en.txt) gives one every frame from the title
through the Dive's opening (frames ~1200-3000), none after.

## The VU1 programs' NEON forms (session 147)

The game thread under the qemu instruction counter (as in session 143, main after #173 and #174, frames 5000-5060):
tr_0 255M and tr_12 140M of its ~800M, most of them in arm_neon.h's `vand` / `vmin` (vu1.c's `vfin` / `vfo`, the
clamp on every operand and result). Three changes in host/port/vu1.c and tools/vu/vu1_translate.py, the output
the same:

- **The clamps in two instructions.** `vfin` (fin(): Inf / NaN patterns to the largest finite of their sign) is a
  signed minimum with 0x7F7FFFFF (the positive words) then an unsigned one with 0xFF7FFFFF (the negative); `vfo`
  is a float minimum and maximum with +-FLT_MAX, exact because its operands are finite (fin()'s, or what the VU
  wrote), so a result is finite or an infinity, never a NaN. Four instructions and a sign mask each before.
- **Results merged on NEON** (`vu_put`): an upper result with a partial dest, or one the pair's lower reads, went
  from the four-lane temporary into the register field by field through core registers; it is now one
  `vbsl` with the dest's lanes. The A9 is slow to read from the core a word NEON just stored.
- **Broadcast operands read by NEON** (`vu_opb` / `vu_opbe` take the field's address, `vld1q_dup`), not loaded
  into a core register and moved across.

The profile: tr_0 255M -> 233M, tr_12 140M -> 128M (qemu counts instructions; the two NEON-to-core changes save
stalls it does not count). Checked: tests/host/vu1neon_test.c now also compares vu_op / vu_opb against their
session 141 form (kept in the test verbatim) bit for bit on every lane over 2M operand sets weighted to the edges,
the operands a translated program passes without fin() made canonical, and vu_put against the field copy;
dropping either new clamp's second instruction is caught. The worker-order run with VU1 (`KH1_HOST_GSQ=1
KH1_HOST_GSQ_CHECK=50 KH1_HOST_GPUQ=1 KH1_HOST_VU1=1 KH1_HOST_VU1TR=1`, dive_en.txt) to frame 6500 gives the same
130 digests and VU1 counts as main's, on x86 and on the ARM build under qemu. **Not yet measured on a Vita**
(3d-zh): the `vu1:` line's time.

On a Vita (3d-zh): the Dive at ~17 fps, stretches at 24-27; the GPU thread's draw bursts gone (#173); the `vu1:`
line ~1.2 s per 2 s, no better than 3d-zf's, so these forms did not measurably help on the A9. The log also had a
bad DMA send about every frame from frame 11 (the logos on): `tag at 84620c40 outside`. The ELF's bss ends at
0x8461e97c, so that is the next pages: the main thread's stack, whose lower part is the coroutines' pool
(host/port/costack.c). plat_null.c's `null_dma_where` only owned the stack above the walking coroutine's own
frame, so a chain on a lower coroutine's stack was refused and the rest of its send dropped (nothing visibly
wrong on screen). It now owns the whole pool too (`kh1_costack_owns`). Not seen on the x86 host or the ARM Linux
build, whose stacks are malloc'd. **Not yet checked on a Vita** (3d-zi): the `log:` line's bad DMA sends.

## The VU1 programs on the Vita, timed (session 147)

The watchdog now prints `vu1 programs:` (host/vita/main.c, from vu1.c's `kh1_vu1_prog_stats`): the four
translated programs that took the most of the window, with their runs, instruction pairs and time per pair.
3d-zj in the Dive, per 2 s: P0 ~420-530 ms at ~73 ns a pair (~32 A9 cycles), P11 / P18 ~160-260 ms at 33-52 ns,
P4 ~100 ms at ~52 ns; VU1 ~750-1,000 ms in all. P0 is over half of it, and twice the cost a pair of the others.

What the A9 pays for in P0's compiled code (`arm-vita-eabi-objdump` of tr_0): every FMAC stored its result with
`vst1q` and the next read it back with `vld1q` (a MULA / MADDA chain through ACC: the NEON load waits for the
store), and a broadcast field or CLIPw's fields were core loads of a word NEON had just stored. Three changes, the
output the same:

- **The registers as plain vector memory** (vu1.c `VU_LD` / `VU_ST`, a `uint32x4_t` with `aligned(4)` and
  `may_alias`) instead of the intrinsics, which gcc cannot see through: a value one FMAC writes stays in its NEON
  register for the next. tr_0: 9,700 instructions to 8,880, its NEON loads / stores of a whole register 1,113 to
  224, core loads 1,083 to 553.
- **A broadcast field from the vector** (`vu_opbl` / `vu_opbel`, `vdupq_lane`): the translator passes the VF and
  the field; Q and I, which the core writes, keep `vu_opb`.
- **CLIPw on NEON** (`vu_clipw`): fkey's magnitude compared unsigned with w's, the sign picking the bit, one
  transfer of the six bits to the core.

Checked: tests/host/vu1neon_test.c adds vu_opbl against the session 141 form on every lane and vu_clipw against
clipw (2M cases each, ties of w with a field among them); the worker-order run with VU1 to frame 6500 gives the
same 130 digests and VU1 counts as main's on x86 and on the ARM build under qemu. **Not yet measured on a Vita**
(3d-zk): the `vu1 programs:` line's ns a pair for P0.

On a Vita (3d-zk): P0 at 64-70 ns a pair, from ~73 (-10%); the Dive at ~17-20 fps as before (the scenes vary;
later in the run P13 takes most, ~740 ms per 2 s at 53 ns a pair). That run also had ~80 bad DMA sends late in
the Dive: `ref` data at 0x846a3c30, in the main thread's stack above the coroutines' pool (its own MAIN_OWN part).
The Vita now hands the whole stack to `kh1_costack_stack` and the walk owns all of it. **Not yet checked on a
Vita** (3d-zl).

### Round 2: moves and the MAC flag on NEON (session 147)

3d-zk's `vu1 programs:` line later in the Dive: P13 ~740 ms per 2 s at 53 ns a pair, P0 at 64 ns, P18 at ~48.
P13's loop (a 4-FMAC transform, an FMAC with the MAC flag, LQ / SQ, a JR table) still crossed between NEON and
the core every pass. Two changes, the output the same:

- **LQ / LQI / LQD, SQ / SQI / SQD and MOVE as one NEON merge** (vu1_translate.py emits `vu_put(dst, src,
  dest)`, a plain store for xyzw): before, a field-by-field copy through core registers, so an SQ of a VF an FMAC
  had just written read NEON's stores from the core.
- **The MAC flag summed on NEON** (vu1.c `vu_ek`): the O and S bits of the fields in dest, weighted, with a lane
  the scalar form must take as 0x10000, added across the lanes and moved to the core once; before, the result
  went to memory and four core loads built the bits.

Checked: vu1neon_test (the same 1,421,531 of 2M cases on four lanes as before, the MAC bits equal; dropping the
O term is caught); the worker-order run with VU1 to frame 6500 the same 130 digests and VU1 counts as main's
on x86 and ARM. **Not yet measured on a Vita** (3d-zm).

## The GS worker's VU1 kicks (session 147)

3d-zm on a Vita: P0 still 66-70 ns a pair, so round 2 of the VU1 programs' NEON forms gained nothing measurable.
The title thread's `gs worker ops:` line (3d-zn, the Dive, per 2 s; addresses mapped with out/vita/kh1.elf): the
worker busy ~1.45 s, of it w_kick (the VU1 programs' XGKICKs) ~750-835 ms in ~6,000-7,000 ops, w_load ~250-300,
w_block ~200-240, w_qwords ~120-150, w_gpu_frame ~50. Counted on the host (dive_en.txt to frame 5100): nearly
every kick packet is PACKED with PRE, NREG 3 and REGS ST, RGBAQ, XYZF2, about 4.4 vertices each (a strip a
packet). Two changes, the output the same:

- **A state write of the value it holds keeps the draw state** (gsregs.c `set`): each packet's PRE PRIM made the
  next vertex look its draw state up again (key, hash, memcmp, the scissor rule). Now it only redoes the render
  target check the lookup made (`relook`); a view change since (`kh1_gs_view`, `view_moved`) still looks again.
- **[ST, RGBAQ, XYZF2] vertices in one loop** (`kh1_gs_packed_stq_xyzf`, from gif_block when the walk keeps no
  values): the same register writes and kick as kh1_gs_packed's 2, 1 and 4, without gif_qword / gif_value /
  kh1_gs_packed / kh1_gs_write per qword.

The worker's thread under the qemu instruction counter (frames 5000-5060): 948M -> 743M; gif_qword, gif_value,
kh1_gs_packed, kh1_gs_write and gif_block (~145M) replaced by ~18M. Checked: the worker-order run with the GPU
thread and VU1 (`KH1_HOST_TRACE=2 KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=50 KH1_HOST_GXM=50 KH1_HOST_GXM_HASH=1
KH1_HOST_GPUQ=1 KH1_HOST_RECQ=1 KH1_HOST_VU1=1 KH1_HOST_VU1TR=1`, the gxmcheck binary) to frame 6500 gives the
same 172 GS digests and GPU target hashes as main's, and the ARM build the same digests under qemu.
**Not yet measured on a Vita** (3d-zo): the `gs worker ops:` line's w_kick.

## The large uploads' syncs and the upload stores (session 148)

**On a Vita (3d-zo):** 3d-zo's log mapped to names with out/vita/kh1.elf: in the Dive, per 2 s, the GS worker's
ops were w_kick ~660 ms (7,700 ops), w_load ~320 (777), w_block ~190 (1,790), w_qwords ~160 (1,150), w_gpu_frame
~55; it was busy ~1.39 s. The game thread waited ~346 ms for the worker in **42 waits**, and the `large uploads:`
line had 42 uploads per 2 s on the game thread, none unchanged, ~267 ms. Counted on the host (dive_en.txt, a
temporary log of each upload's source op, frames 5000-5060): one 256 x 256 CT32 upload at 0x3600 per drawn frame
(the texture area, rewritten each frame by the T8 textures and CT32 CLUTs streamed after it: ~11 T8 128 x 128
through 0x3600 from the GIF channel, ~19 T8 of 32-256 pixels by PlatGsExecLoadImage, CT32 CLUTs and PATH2's
CT32 pieces). Each large upload with new bytes did a full kh1_gsq_sync before it overwrote its kept copy, so the
game thread waited for the whole queue every drawn frame. Two changes:

- **The large upload's copy without a sync** (host/null/gsimage.c `load_big`): new bytes go into the least
  recently used of the 8 kept copies; the game thread waits only until the worker has run the last op that reads
  that copy (`kh1_gsq_wait(pos)`, the position after that op's put), which is long done. The same rectangle's
  older copy, when another, is no longer offered for the compare but is left as it is for ops still in the queue.
  On the ARM profile (below) the game thread's spin in those waits (q_wait_tail, ~24M instructions over 60 frames)
  is gone.
- **T8 and CT32 / Z32 uploads a block at a time** (host/null/gsmem.c `band_t8` / `band_c32`, from trx_bulk): a
  band of whole blocks (16 rows of T8 or 8 of CT32 from a block's top row, the rectangle's x and width whole
  blocks) is stored block by block: a block is 256 bytes in one page, T8's four 64-byte columns each a fixed
  permutation of 4 rows x 16 pixels (two kinds by the column's parity), CT32's four 16-word columns each two rows'
  words interleaved in pairs. The permutations are read from kh1_gsmem_addr once (band_init); on NEON a T8
  column is 8 VTBLs over two rows each, a CT32 column 4 VCOMBINEs, with one compare of the old bytes a block and
  the page's stamp, drawn bits and marks set once a block (marks moved once, as the T8 run loop already did).
  Anything else (a part row, a rectangle not on block edges) goes through the pixel loops as before. gsimage.c's
  load_image now hands a word-aligned source to kh1_gsmem_image in one piece (it went in 256-byte pieces, two rows
  of a 128-wide T8, so no band was ever whole).

The ARM profile (qemu-arm with an instruction-count plugin, `KH1_HOST_TRACE=2 KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=1000
KH1_HOST_GPUQ=1 KH1_HOST_RECQ=1 KH1_HOST_VU1=1 KH1_HOST_VU1TR=1`, en.iso, dive_en.txt, frames 5000-5060 as the
difference of two runs): the worker's kh1_gsmem_image 235M -> 37M instructions, the worker's work ~460M -> ~353M
(it now idles ~79M); the game thread 610M -> 572M. Checked: tests/host/gsfast_test.c's upload runs now include
whole-block CT32 / Z32 / T8 rectangles, some off the block edges, in pieces of up to 8 KiB or whole, against the
model with the fast paths off (and `gsfast_test up` under qemu-arm in tests/selftest.sh for the NEON forms; a
wrong VTBL index, a CT32 column swapped or the changed test dropped is caught); the worker-order run on the ARM
build under qemu to frame 6500 (`KH1_HOST_GSQ_CHECK=50`) gives the same 130 digests as main's; the x86 gxmcheck run
with the GPU thread (`KH1_HOST_GXM=50 KH1_HOST_GXM_HASH=1`) the same digests and GPU target hashes as main's.
**Not yet measured on a Vita** (3d-zp): the `gs worker:` line's waits (from ~42 per 2 s) and the `large uploads:`
time, the `gs worker ops:` line's w_load / w_block / w_qwords.

### The VU1 programs' result clamp (session 148)

The game thread is the limit once the large uploads stop syncing: in 3d-zo's log it spent ~1.28 s per 2 s in the
DMA walks, ~1.0 s of it in the VU1 programs (P0 ~640 ms at ~74 ns a pair). A dynamic instruction mix of tr_0 on
the ARM profile (each translation block's count times its instructions, from objdump): 22% `vldr`, 10% `vstr`,
~17% the clamps' `vmin` / `vmax`, ~5% the arithmetic. Of the `vldr`s, ~21.6M of tr_0's 225M were literal-pool
reloads of constants: gcc keeps rematerialising them under the function's register pressure (no -O level or
scheduling flag changed that). `vfo` (fout()'s clamp to +-FLT_MAX) used two float constants of its own; it is
now vfin's two integer minimums, which give the same bits for every result that is not a NaN (none is: the
operands are finite, so a result is finite or an infinity) and share vfin's constants. tr_0 225M -> 215M,
tr_12 119M -> 116M ARM instructions over frames 5000-5060. vu1neon_test compares vu_op / vu_opb / vu_opbl with
the session 141 form (kept verbatim) and still finds them equal (dropping the clamp is caught); the ARM build's
130 digests to frame 6500 are main's. What is left in tr_0 is mostly the VU registers' own loads and stores
(`vf` / `acc` in memory, ~19%): keeping them in NEON registers would need the translator to emit value-based
code (locals per VF), a larger change.

## Late frames make up the vblanks they lost (session 149)

Shay's 3d-zp log (the Dive, per 2 s): the game waited 0 ms for the GS worker, so the game thread is the whole
limit now. ~24 vblank calls a second in most of the Dive (the game draws on every other one), ~15 in the
heaviest scenes, with ~330 ms of vblank wait per 2 s in the 24-a-second stretches. A drawn frame takes ~4
vblanks; session 145 let it go on without waiting, but the empty frame after it (a few ms) then waited for the
next vblank, since only one frame a vblank could skip. Each game frame is one vblank of the game's time
(host/null/threads.c calls kh1_host_vblank once a frame, the game's vblank handler counts it), so that wait
only slowed the game.

host/vita/main.c now counts the vblanks the frames have used (`vcount`): a frame goes on without waiting while
the display's count is ahead of it, using up one vblank, and waits for the next vblank once it has caught up,
as before. At most `CATCH_UP` (4) lost vblanks are made up, so a long stall (a disc load) does not run the game
fast afterwards. A game faster than the display is paced as before (it is never ahead of the vblanks), and
`latewait=1` still always waits. **Not yet measured on a Vita** (3d-zq): the watchdog's `vblank wait` should
fall to near 0 in the Dive and the vblank calls a second rise by about as much (~24 to ~27-28 in the 24-a-second
stretches, a guess from the wait alone).

### The VU1 FMACs: exact zeros and inlining (session 149)

With the game thread the limit, the VU1 programs are its biggest cost: in 3d-zp's log P13 ~975 ms per 2 s (the
24-a-second stretches), P18 ~1,046 ms and P0 ~440 ms (the 15-a-second ones). Measured offline: the host runner
dumps every Nth run's start (`KH1_HOST_VU1DUMP=DIR:N`, ~2,200 runs over frames 0-21,000 of dive_en.txt), and a
scratch replayer (it includes host/port/vu1.c and out/gen/vu1_tr.c, so it is never committed) runs each dump's
program translated and interpreted and compares the state and the kicks, or runs it N times. Compiled with
vitasdk's gcc (the Vita's code), linked against the Linux libc and counted under qemu-arm with a TB-count plugin.
Two costs stood out:

- **An exact 0 went to the scalar form.** An FMAC whose MAC flag some FMAND reads (vu_ope / vu_opbe / vu_opbel,
  `vu_ek`) answered 0 for any field that came out 0, because NEON's flush makes a denormal 0 where fout() flags U.
  P18's back-face test (an OPMSUB cross product, flagged) has many exact 0s: the scalar form with three fout()
  calls ran ~90 times a run. Now a 0 is told apart: x + y is exactly 0 when x == -y, x - y when x == y, x * y
  when a factor's exponent is 0, ACC + p / ACC - p when ACC == -p / p (p not flushed: a flushed p is bad already).
  NEON's compare reads a denormal as 0, as fin() does. Those get fout()'s Z (and S from the sign) on NEON; a 0
  from a flush still goes to the scalar form (never seen in the dumps after this).
- **The helpers were not inlined.** gcc kept `vu_opbl` / `vu_opbe` as out-of-line clones in tr_13 (tr_13 is too
  big for its inlining limits), each call passing the VF through memory. They are `always_inline` now (the code
  grows ~10 KB). vu_opbl / vu_opbel also take fin() of the whole register before the lane, so four FMACs that
  broadcast x, y, z, w of one register share it.

ARM instructions over the dumps (10 passes each, the replayer's own copying left out): P13 166M -> 98M (-41%),
P18 169M -> 111M (-34%), P0 250M -> 241M (-4%). All 10,090 runs of a second, denser dump set (every 331st run)
give the same state and kicks as the interpreter; vu1neon_test now makes a third of its cases cancel (b = +-a,
c = +-a*b, some a bit off) and catches the Z weights reversed or an "exact" claimed for every ADD or MUL.
**Not yet measured on a Vita** (3d-zr): the `vu1 programs:` line's P13 / P18 ns a pair (~49 / ~51).

## The flashing floor: one-byte enums (2026-10-28)

The Dive's stained-glass floor (and other grid-effect ground) was missing on every other drawn frame on a
Vita and in Vita3K, never on the host, the x86 gxm_mock run or the ARM Linux build under qemu-arm. The
lost draws were not the GPU's: on the bad frames the game's VIF1 stream itself was different (208 VU1
runs, 303 kicks and 29 program loads against 305 runs, ~586 kicks and 13 loads; 47 draws against 54), and
a real-Vita log (3d-za) had the walk's "N words no VIF code" lines with the chain dumped: the grid effect's
two DMA lists (D_004761A0 / D_0047A1E0, src/gfx/grideff.c, swapped by D_00351BD0) with a third tag of
`refe qwc 49154` in one and a `ref` to non-VIF bytes in the other. That tag is the header func_00106ed0
writes through `EntE` / `EntLb`, structs whose second field is `EN`, a one-value enum the matching code uses
for its alias set.

The cause: vitasdk's gcc (arm-vita-eabi, a bare-metal EABI) makes an enum as small as its values,
`-fshort-enums` by default, so `EN` was one byte and the structs' later fields moved; the EE's gcc and
every host compiler make it an int. Not the memory layout (the x86 runner with the Vita's misalignment and
the ARM build linked above 0x80000000 both draw the floor), not the GS worker's timing (an x86 worker
slowed by 30 µs an op), not the VU1 programs.

tools/vita/build.py now compiles the game's files (src/, host/null, host/port, the native overlays) with
`-fno-short-enums`, and host/vita's own files with `-fshort-enums`: SceGxm's and vita2d's structs are laid
out for one-byte enums, and no struct the two sides share has an enum field (include/platform's enums are
unnamed constants). The link takes `--no-enum-size-warning` for the mix; `readelf -A` on an object shows
`Tag_ABI_enum_size: int` for the game's and `small` for host/vita's.

## Sound (2026-10-29)

The game's sound plays through **the disc's own IOP sound driver** (LIBSSL.IRX, read from the image at the
game's sound bind; nothing of it is in the VPK), run by a small IOP and SPU2 in host/port/ (iop.c, spu2.c,
snd.c; docs/sound-spec.md section 6 has the details and what is not modelled). host/vita/audio.c runs it
on three threads. A tick thread runs the driver's 240 Hz ticks up to 33 ms ahead of a mixer, which applies
each tick's SPU2 writes and mixes 64 ms ahead into a ring; both run below the game's threads on any core.
An output thread hands the ring to sceAudioOut's main port (48 kHz stereo, 256-sample buffers) and plays
silence where the mixer has fallen behind. The game thread only copies its per-frame command queue into
a FIFO; the RPCs whose answer the game reads wait on the tick thread's lock.

- `snd=0` in config.txt turns it off (the null server, silence, as before). Without LIBSSL.IRX on the
  image (a wrong or partial image) the log says so and the game runs silent. `sndcore=N` pins the tick
  thread and the mixer to core N (0, 1 or 2); the default, -1, lets them run on any core.
- The log: `kh1-snd: sound driver LIBSSL.IRX (85501 bytes) running, tick 240 Hz`, `kh1-vita: sound: the
  disc's driver ticking and mixing on any cores ...`, and every 2 s a watchdog line, `kh1-vita: sound: K ms
  ticking, N ms mixing, B buffers played (S short), Q frames queued, T ticks, I IOP instructions, V voices
  on, R RPCs (F FIFO full)`. B is about 375 per 2 s (48,000 / 256 x 2). S counts the buffers the mixer had not
  filled in time (the sound breaks up). Q is how far ahead the mixer was (up to 3072). K or N over
  about 2000 means that thread needs more than a core (both count time they were preempted too).
- The first test (one thread on core 2, above the GPU thread) broke up and made the picture lag once
  the title music started: it needed about 80% of core 2 (sound-spec 6). Builds b and c (one mixer
  thread below the game's) stopped the lag but still fell short on the title's music and the New Game
  load; build d splits the ticks and the mix onto two threads.
- Movies have no sound (the core PCM input is not modelled). The real driver also changes timing where
  an event waits for a voice line, so host pad scripts drift when run with sound (sound-spec 6).
- 2026-10-30 (build snd-f): most of the room's and the events' sound effects were silent after the first
  room change, and the battle track never loaded: the IOP model's memory pool allowed only 64 blocks
  (sound-spec 6, "The pool's block limit"). Fixed, and the SPU2's noise generator added. With the SEs
  playing the driver does about 60% more work in Dive on the host (1.30 G IOP instructions over the first
  20,000 frames instead of 0.80 G); watch the "short" count on the sound line in busy rooms.

## What next, in order

1. Booted in Vita3K (above). Next real-disc checks: run the host runner on the ISO for longer and
   with pad scripts, and look for more overruns of the allarea.nam kind (a disc file's length
   copied into a name the host sizes from its PS2 neighbour).
2. **The GXM renderer** (done in session 136, above): next, the real-disc gxmcheck over the menus and
   the new game, the frame reads on a Vita, and the "Not checked yet" list.
3. **dktitle.x** (vita-port-plan 5.2): the inventory, the toolchain check, then its C, so the title
   screen and its menu run instead of the stub.
4. Renderer A / B on the CPU (vita-port-plan section 2 step 3). Sound: started 2026-10-29 ("Sound"
   above); next, its cost on a real Vita and the movies' PCM (BlockTrans).
