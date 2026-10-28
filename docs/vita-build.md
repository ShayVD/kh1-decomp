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
    present, 4:3 pillarboxed), plus a status strip; since session 135 drawn by the GPU through
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
- **No sound** (host/null/sound.c's null server keeps the status the game polls), **no movies**
  (dkmovie.x is an overlay too). **Saves** (session 140): memory card 1 is the folder
  `ux0:data/kh1/mc0` when it exists ("Memory card" below); card 2 is always empty.
- gumisave.c's func_001b9c60 keeps the overlay entry as a pointer and calls it later: on the Vita
  that jumps into data (the Gummi ship editor; not reachable before the world map anyway).

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
floor (the region shader's draws) is black on every other drawn frame, with the interpreter as with the
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

## What next, in order

1. Booted in Vita3K (above). Next real-disc checks: run the host runner on the ISO for longer and
   with pad scripts, and look for more overruns of the allarea.nam kind (a disc file's length
   copied into a name the host sizes from its PS2 neighbour).
2. **The GXM renderer** (done in session 136, above): next, the real-disc gxmcheck over the menus and
   the new game, the frame reads on a Vita, and the "Not checked yet" list.
3. **dktitle.x** (vita-port-plan 5.2): the inventory, the toolchain check, then its C, so the title
   screen and its menu run instead of the stub.
4. Renderer A / B on the CPU (vita-port-plan section 2 step 3), then sound (docs/sound-spec.md).
