# Native overlays: the overlays' C in a port (phase 5, session 132)

On the PS2 the game loads an overlay's MIPS code from KINGDOM.IMG into the overlay area at
0x00F20000 and calls its first byte (docs/overlays.md lists the 12). A port cannot run those
bytes, so it links each overlay's decompiled C (ovl/NAME/, the C the matching overlay build
verifies) as a native module. dktitle.x (the title screen) is the first; the mechanism is the
same for the others once each has C for every function.

## How it works

| Piece | What |
|---|---|
| `include/platform/ovl.h` | the wrapper: `PlatOvlLoaded(name, buf, size)` (nothing on the PS2), `PlatOvlCall`, `PlatOvlCurrent`, the module table's types |
| `src/io/discfile.c` func_00120678 | the loader task calls `PlatOvlLoaded(t->name, t->buf, r->result)` after a file is read, before its callback (the PS2 bytes are unchanged: the macro is empty) |
| `host/port/ovl.c` | when the buffer is the overlay area and a module of that file name is linked: checks the bytes against the pin (size and SHA-256 of `ovl/overlays.tsv`), rewrites the data's pointers into the overlay, makes it the current overlay; `PlatOvlCall` runs the current module's entry |
| `ovl/NAME/relocs.tsv` | the data words that hold a pointer into the overlay (`tools/ovl/relocs.py NAME`, addresses only): a function's start (rewritten to the native function) or a data address (rewritten to the memory map's). Words pointing inside a function are gcc's jump tables for the PS2 switches and are left alone. Its presence marks the overlay as prepared for a native run |
| `ovl/NAME/drafts.tsv` | optional `func_X<TAB>path` rows: near-miss drafts (under nonmatchings/) the port uses for functions not matched yet, like shift/drafts.tsv for the main ELF |
| `ovl/NAME/platform.tsv` | optional `func_X<TAB>replacement` rows (session 134): overlay functions a port replaces with its own code. Their pointers in relocs.tsv get the replacement, and only the functions the entry and the other pointers reach through the C are compiled (dkmovie.x: 6 of 122) |
| `tools/host/ovlnative.py` | run by tools/host/census.py's link step (so `make host-census`, `tools/vita/build.py` and `make vita-armcheck` all take it): compiles each prepared overlay whose every needed function has C, with `names.h` forced in front |

Names: the same address is other code in each overlay, so `names.h` renames the overlay's
`func_00f2xxxx` to `NAME_00f2xxxx` and its `D_00F2xxxx` to `NAME_D_00F2xxxx` (one module per
overlay). The data names are linker-script symbols at their place in the memory map's overlay area
(`kh1_memmap + addr - 0x6A0000`, aliases.ld), where the game's loader put the file: the C reads its
strings and tables from the user's own file at run time, nothing is extracted or committed, and
the variables past the file's end (D_00F2C6F0 ...) are in the same area as on the PS2.

The entry: x86 (host/null/main.c) faults on the call into the memory map and redirects it to
`ovl_entry`, which asks `PlatOvlCall` first (with or without `KH1_HOST_OVL=stub`); ARM Linux and
the Vita (tools/vita/build.py rewrites the calls of `D_00F20000` to `kh1_ovl_entry`) ask it in
`kh1_ovl_entry`. An overlay with no native C is answered as before (the stub, the Vita's
`title=N`).

The fake disc (tests/host/fake_disc.py) holds a one-sector dktitle.x that is not code, so its runs
are unchanged (the pin check keeps the native C off). `fake_disc.py OUT.iso --dktitle
out/overlays/dktitle.x` puts the user's own file in (never commit that image): the title's C then
runs on the fake disc.

## What a port still has to do

- Every overlay function a data table names must be in relocs.tsv's rows, and every call the
  main ELF makes through a pointer the overlay stored (tasks in `D_00304B6C`, `D_00524F74`, the
  task setter `func_001c06c0`) gets the native function, since the C stores `&func` (a host
  pointer: the host and the Vita are 32-bit, so it fits the game's 32-bit fields).
- Main-ELF data that holds a pointer into the overlay area set by the PS2 code (rather than by
  the overlay's C) would still hold a PS2 address: none found for dktitle.x.
- The overlays call SDK functions directly (sceGsSetDefLoadImage, sceGsExecLoadImage, FlushCache,
  sceGsSyncPath ...): the port's sdk_host.c / platform code must define them (the host link lists
  any it lacks).

## Session 133: on the real disc and in Vita3K

- **Host runner, the user's Final Mix ISO** (KH1_BIG.iso, SHA-256 9ad74868…, which holds the
  KH1_F131 float ELF; staged into the container in 390 MB parts, never committed):
  `kh1-ovl: dktitle.x loaded: native C (6 pointers fixed up)`. With no pad the logo fades in by
  frame ~1100 (the white set-up, then the logo and the small Sora / flag art). A pad script
  (`KH1_HOST_PAD`, frame numbers = shot frames) with START at 1300 and CIRCLE every 200 frames
  from 2000: the large hooded-Sora art fades in, New Game opens the game mode page (Final Mix
  Beginner / Final Mix / Final Mix Proud), then the camera page (auto / manual), the sound page
  (stereo / mono), the summary with "この設定でいいですか? はい / いいえ", and はい fades the title out.
- **The memory map was too short**: the fade-out's capture (src/screen/capture.c func_0010a058,
  `PlatGsExecStoreImage` 512 x 384 CT24 = 0x90000 bytes into func_001559f0(62, 2)'s buffer at
  0x1F60000) wrote 0x10000 bytes past the old map end 0x1FE0000, over the host's `current` (ovl.c)
  and `kh1_vsync_cb`; the next vblank called 0xF5F5F5F5 (the title's white). Without
  `KH1_HOST_SHOT` the model's pixels are 0, so the overwrite went unseen. host/port/memmap.c now
  runs to 0x2000000 (on the PS2 0x1FE0000 up is the main thread's stack area, whose unused bottom
  the capture takes). gdb with a hardware watchpoint on the clobbered word found it in one run:
  `watch -l *(int*)&kh1_vsync_cb` after `handle SIGSEGV nostop noprint pass` (every overlay call
  on x86 is a SIGSEGV redirected by main.c, so stopping on SIGSEGV stops at the first title frame).
- After the confirm the game makes 33 disc reads (3,905 sectors) and loads the next overlay at
  0xF20000 (lsn 99113, 17 sectors: dkmovie.x, the opening movie), called from dkmovie.c's
  func_00110fc8: with no native C it faults (`KH1_HOST_OVL=stub` answers it 0 and the game then
  calls entry (2, 0) every other frame forever: the movie never ends). **The next overlay to make
  native is dkmovie.x.**
- **Vita3K** (v0.2.1 on the Mac, `Vita3K --frontend sdl -l 4 VPK` installs; then `-r KHDC00001`,
  config.txt `frames=2400`; the pref path is ~/Library/Application Support/Vita3K/Vita3K/fs, ux0
  under it): the title draws (the logo, then the hooded-Sora art faded in), no crash in 3 minutes,
  ~20 frames a second, ~6.5 once the large art is up (the software present). No menu: no pad input
  was given. kh1.log has no `kh1-ovl:` line although the native C ran (the picture is the title's):
  open question, the loader's printf may not reach the funopen log on the Vita.
- The Mac had only ~229 MB free after this run: free space before the next Vita3K run (its log at
  TRACE filled the disk once).
