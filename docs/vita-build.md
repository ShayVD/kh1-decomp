# The first Vita build

Written 2026-10-25 (phase 5, after session 122). Built and packed in a cloud container; **not run on a
Vita or in Vita3K yet** (no hardware or emulator was reachable). What it is, how to build it, what it
does and does not do, and what to check first on a device.

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
  - `display.c`: a 960 x 544 framebuffer showing the GS model's display buffer after each frame copy
    (the host's `KH1_HOST_SHOT` present, point-sampled, 4:3 pillarboxed), plus a status strip;
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
   `kh1.bin`). Without one the app shows a red screen until START.
3. Optional `ux0:data/kh1/config.txt`, `key=value` lines:
   - `iso=ux0:...` another image path;
   - `title=N` the game state asked for at the title overlay's first call (default 2: a new game,
     Dive to the Heart; `-1` stays in the title state);
   - `frames=N` exit after N frames (0, the default: never).
4. `ux0:data/kh1/kh1.log` gets everything the host runner prints: each disc search and read, the
   overlay calls, the end of the run. Send it back after a run.

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

- **No title screen.** The title is the overlay dktitle.x (MIPS code the game loads from the disc to
  0xF20000 and calls); no overlay is decompiled yet (vita-port-plan 5.2). tools/vita/build.py routes
  every call of the overlay entry (29 in 13 files, found in the preprocessed C) to
  `kh1_ovl_entry`, which answers 0 like the host's `KH1_HOST_OVL=stub`, and at the title's first
  call asks for game state 2 (new game). So the boot loads its files and goes straight to Dive to the
  Heart's room loads, which the host has never run past on a real disc: expect it to stop there or
  soon after (the log's last lines say where).
- **No 3D.** The VIF1 / VU1 path (renderer A / B, PATH1) is not replaced: chains are walked but
  their models are not drawn. The picture is the GS model's 2D: clears, fades, uploads, sprites,
  copies (whatever the boot draws on PATH3).
- **Not the GXM renderer.** The picture is software (the model's display buffer copied to the
  framebuffer after each frame copy). The port code from sessions 116 to 122 (palette and texture
  caches, texture formats, TFX, sampler, blend, alpha / destination-alpha tests, depth, fog, primitive
  assembly) is linked and feeds the model's present, but nothing draws with GXM yet.
- **No sound** (host/null/sound.c's null server keeps the status the game polls), **no saves** (no
  card in either slot), **no movies** (dkmovie.x is an overlay too).
- gumisave.c's func_001b9c60 keeps the overlay entry as a pointer and calls it later: on the Vita
  that jumps into data (the Gummi ship editor; not reachable before the world map anyway).

## What next, in order

1. **Boot it** (Monday, the Mac: Vita3K, or a Vita): the log and a photo of the screen. Then the same
   run on the host with the ISO (`KH1_HOST_ISO=... KH1_HOST_OVL=stub:2 KH1_HOST_TRACE=1`) to compare.
2. **A GXM present**: the framebuffer copy through GXM (one textured quad), then the GIF path's
   sprites and triangles drawn by GXM with the state the port code already decides
   (include/platform/{texfmt,texfunc,sampler,blend,atest,depth,fog,primasm}.h).
3. **dktitle.x** (vita-port-plan 5.2): the inventory, the toolchain check, then its C, so the title
   screen and its menu run instead of the stub.
4. Renderer A / B on the CPU (vita-port-plan section 2 step 3), then sound (docs/sound-spec.md).
