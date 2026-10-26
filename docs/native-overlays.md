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

## Session 134: dkmovie.x, past the opening movie

- **dkmovie.x is two parts.** Its front end (6 functions: the entry func_00f20000, the open
  func_00f20258, the per-frame callback func_00f20140 that func_00f20258 installs with
  `func_0011ef10(0x2E630, ...)`, the display set-up func_00f20320 and clean-up func_00f200f8, the
  status func_00f20230) reaches the player only through the function table `D_00F28478`
  (relocs.tsv's 7 function rows; layout in include/platform/movie.h). The player (the other 116:
  the KINGDOM.IMG stream reader, two sa_task tasks func_00f23750 / func_00f23ae8 that demux and
  decode through the IPU, the MMI colour conversion func_00f203a4 ..., SPU audio over SIF DMA) is
  PS2 hardware code. So the port links only the front end and points the table at
  `PlatMovie*` (ovl/dkmovie/platform.tsv, tools/host/ovlnative.py); the 27 unmatched functions
  other than func_00f20140 / func_00f20258 (drafts, 29 and 3 words) are never needed by a port.
- **The PS2 player's ending**, which host/port/movie.c copies: the decoder task sets flag 0x8000
  (status 4, ended), then on each later step 0x40000 (status 5); on 5 the front end runs
  `func_001111b0` (the clean-up: entry(4), `D_002BCB34` = 1) and returns 4 so its callback is
  dropped. A player that stays at 4 keeps the callback alive after the game reuses the overlay
  area: it then calls a zeroed table (the first host run crashed that way 900 frames later).
- host/port/movie.c has no decoder: open = status 2 (ready), start = 3, the next frame 4, then 5.
  The table's width (+0x18) stays the file's 0, so the frame copy (brightfade.c case 2) draws a
  0-wide picture while the movie "plays". A real player sets +0x14 / +0x18 / +0x28.
- **Real disc** (KH1_BIG.iso again, the session 133 pad script: START 1300, CIRCLE every 200
  frames from 2000): `kh1-ovl: dkmovie.x loaded: native C (8 pointers fixed up)`,
  `kh1-movie: open 0 (opn.dat)` (the opening movie, from the event script: commands 584 / 585 /
  489 / 490), then the opening's black screen with the monologue text fading in and out, 9,000
  frames with no crash. Two register passthroughs (portability.md rule 10) crashed it on the way,
  both fixed with unchanged objects: ppploop.c's three `*MoveLoopReset` called their constructor
  with no arguments (now `(arg0, arg1)`), and fldtext.c's func_0010c540 was void although
  func_0010e4f0 sends the DMA tag it leaves in $v0 (now returns func_00106cd0's result). Neither
  was in argcheck's list: both calls went through m2c's `#define f ((M2C_UNK (*)()) f)` casts.
- **Open: the monologue shows one glyph per line** (shots from frame ~3300: 残 over 僕, fading
  together). func_0010d0c0 returns the full count (10 of 10, gdb) and func_0010c540 builds a
  REGLIST packet of n glyphs (TEX0 RGBAQ UV XYZ2 UV XYZ2), so the glyphs are sent; either their
  positions / textures (func_0010cb80, the session 12 draft of func_0010d470 which lays the
  glyphs out) or the GS model's handling of them. **No disc read follows the movie**, in 15,000
  frames with CIRCLE every 200 frames up to 14,000 either: the game does not leave the monologue.
  The next question is what it waits on. `KH1_HOST_SND=trace` from the movie to frame 5,000:
  music 0 starts, sound effects 20208-20210 (bank -8) and 21102 (bank -1) are played and the
  null IOP ends them at once (`end se`), and then **se-volume of 21102 every other frame for the
  rest of the run** (917 times): something keeps adjusting a voice the game believes is still
  playing, or waits for its end in a way the null IOP's answer does not give (a guess: 21102 is
  the monologue's voice or ambience; read who sends 0x08 for it).
- **Vita3K: why kh1.log has no `kh1-ovl:` line.** Session 133's log (Downloads/kh1-test/vita3k-s133)
  has no printf line at all, not even plat_null.c's `PlatCdRead` lines at trace 2: only main.c's
  `vlog` lines (straight sceIoWrite) arrive. The funopen'd stdout never reaches the file in
  Vita3K. Routing printf through vlog would also bring the DMA walk's line per send at trace 2
  (main.c forces 2), so a fix needs a quiet DMA log first (another thread's change, 2026-10-26).

## Session 135: past the monologue (Dive to the Heart)

- **The "monologue" is Dive to the Heart, and it was waiting for the player.** Script VM trace (gdb
  `dprintf` on the 32 opcode handlers of `D_0037A198`, `func_001dcad0` for the library calls): after
  the movie the event VM shows the lines and ends (`func_001cd7e8` waits for the SEs, `func_001cd830`
  messages the field); the game is in the field (`D_002BBDE0` = 3) with 9 VMs, and VM 0 adds trigger
  box 2 (`func_001d6250`: centre (0, -127, 0), size 255) then loops at pc 697-753 until save byte
  0x901 (script variable 0xB01 = 2817, op 12) is 4 (with 0xC81 = 0) or 10. The last line on screen
  is さあ 歩き出してごらん / ここまで来られるかい――? ("step forward"): the game waits for Sora to walk.
  He is invisible because the null platform draws no 3D (no VU1). With the stick held (pad script
  `FRAME - 128 128 128 0`) the footstep SEs 11038 / 11046 play.
- **Two host bugs made the player's facing and position NaN** (found with hardware watchpoints on
  the player at `D_002C64A0 + 1200`, `D_002E26A0[0]`):
  - objutil.c `func_00137688` sets the facing (+0x30) to (sin a, 0, cos a). m2c had read the sinf
    call (`func_0026b7d0`) as `func_0026b7d0()` with no argument: on the EE `a` is still in $f12, on
    x86 sinf read garbage. Now `func_0026b7d0(fparg0)` (object unchanged). The NaN facing went into
    the player's matrix (objdraw `func_00136d38`), the camera's targets (`func_00177900` ->
    `func_001ca0f8`), the camera angle `D_004F77E0` and the stick's move direction (view.c
    `func_00124e08`), and so into the position from frame 4,681.
  - `PlatVu0Normalize3` (include/platform/vu.h, the host's sceVu0Normalize): the VU's `vdiv`
    1 / 0 is +max, so a zero vector normalizes to 0; the host's 1 / 0 was infinity and 0 x inf NaN.
    Now q = FLT_MAX for a zero length (a still pad's direction is a zero vector each frame).
  With both, Sora walks: script variable 2817 goes 0 -> 1 -> 4 at frame ~6,400 (position z 462),
  he moves around the platform, and the game reads the disc again (lsn 107050 and 78094). The
  shots (pad script: START 1300, CIRCLE every 200 frames 2000-4600, stick up from 4800, right from
  7000, down from 8000) then show the doves' SEs (35207 / 35208, frame ~6,200) and the next lines,
  キミの中に眠る力―― and カタチは力を与える (the weapon pedestals), and the tutorial's ✕でジャンプ!
  (frame ~7,000): Dive to the Heart runs on. Choosing a weapon needs the pedestals' positions (the
  3D is not drawn: read them from the trigger boxes / objects with gdb, or draw the 3D).
- **The one glyph a line**: fldtext.c `func_0010c720` (one glyph's GS packet) was void, but
  `func_0010cb80` stores the cursor it leaves in $v0 (`sw v0, 0(sp)` after the `jal`; the callee's
  last act is `addiu v0, s1, 48; sw v0, 0(s8)`). On x86 the caller kept a garbage cursor, so each
  glyph of a line overwrote the same slot. Now it returns `*pp = p + 6` (object unchanged); the
  whole lines draw (残された時間は少ない, 僕はもう戻れない, けれど急がないで, 恐れないで,
  扉はまだ閉ざされている, さあ 歩き出してごらん).
- **tools/host/argcheck.py** finds both kinds now: definitions in src/sdk count (sinf is defined there
  under its name; functions.tsv maps it to func_0026b7d0), and a value use of a void function in its
  own file is checked when the call goes through m2c's `#define f ((T (*)()) f)` cast. One more real
  hit fixed: objdraw `func_00136428` returns the model draw's result (mdldraw.c `func_001621e0` ->
  `func_001606d0`'s `DObj25 *`), which `func_00136768` passes to `func_0012bce0` (objects unchanged).
  Left, read but not fixed (each `return f(...)` of a void f, its value passed on): memberitem.c
  `func_0014a058` and roomobj.c `func_00131f40` (their callers drop it), class1b `func_00152140`
  (an object step function, objtask.nostrict.c case 9: whether the task reads its value is not
  checked), atkhit.c `func_0014ab18` (no caller found in src/), and the three winmenu / winpart hits
  from before.
