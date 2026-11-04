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

## Session 136: through Dive to the Heart's first stations

- **The weapon choice on the host.** Nothing 3D is drawn on the null platform, so the pedestals'
  places come from the actor table (gdb on `D_002C64A0`, 1200-byte entries; position at +0x10): the
  first station has three pedestals (kind 4) at (0, 580), (-500, -300), (500, -300) with their weapons
  (kind 2) on top, 100 high. Sora stops at a pedestal's edge; CROSS (jump, the "✕でジャンプ!" hint) puts
  him on top and the lines start: (0, 580) is the sword (攻めこむ力 ... 破壊の刃), (500, -300) the staff
  (ふしぎな力 ... 破滅の杖). Choosing the sword, giving up the staff and confirming
  (これがキミのカタチなんだね? うん、そうだ) all run from the C.
- **Pad scripts can walk to a place**: `FRAME BUTTONS goto X Z [R]` (host/null/pad.c) steers the left
  stick to field point (X, Z) and centres it within R. The stick's way is turned the way the game turns
  it (camera/view.c func_00124d58 with the camera angle D_004F77E0, tried at 64 angles), since the
  camera swings round the player; the player is `D_002E26A0[0]` (an index into the actor table that
  changes per room). Estimating the turn from how the player moved did not work: he turns before he
  moves, slides along walls, and the pad is read every other frame. pad_test.c checks the parser and
  the aim. The whole run: tests/host/pads/dive.txt.
- **xs_dh_break.x is native** (the floor breaking into 2,500 falling shards after the confirm): 5 of
  its 9 functions were matched in session 131b; the other 4 have drafts (nonmatchings/session136/
  xs_dh_break/, ovl/xs_dh_break/drafts.tsv: func_00f20b38 the set-up 62 words off, func_00f20820 one
  shard's set-up, func_00f20288 the per-frame task, func_00f20128 never called). Its data has no
  pointers into itself (relocs.tsv is empty); its buffers lie past the file's end up to 0x00FA2400, so
  tools/host/ovlnative.py now renames and places data names anywhere in the overlay area
  (D_00F2xxxx - D_00FDxxxx), not only D_00F2xxxx. host/port/ovl.c prints `kh1-ovl: NAME.x loaded
  (N bytes): no native C` for an overlay without native C (music files load there too: only `.x`).
- **Two kinds of host stack bugs** (the PS2 objects unchanged; portability.md rule 15):
  - The camera's ray casts (`func_00118d78` / `func_00119688` read a record: the start, the way, the
    hit, the hit's id) were given the start's 16-byte local only, with the rest in other locals:
    fieldcam.c func_00177440 / func_00177608 and partyctl.nostrict.c func_001689d0. On the EE the
    locals are adjacent in that order; on x86 the callee wrote past the start (crashed at the attack
    tutorial in sceVu0CopyVector). Now one struct each.
  - `func_0024ac08` (hud/ui.c) writes four words; gauge.c / gauge.nostrict.c func_0023d528,
    popup.c and cmdmenu.nostrict_nofill.c gave it `s32 [2]` (the EE frame has 16 bytes there): the
    HUD gauge's saved register was overwritten at the first Shadow. Now `[4]`.
- **The attack tutorial runs**: 君が手に入れた力 それは「たたかう」力, ○で攻撃!, the command menu
  (たたかう) and Sora's face; with CIRCLE pressed every 30 frames the Shadows (actors 16-20, kind 3)
  come and go, and at frame ~17,800 the next station loads (the player at (-8840, -14304), two kind-4
  actors at (-8670, -15430)). **Open**: what that station wants; a goto to its objects is blocked ~150 short at (-8784, -15336)
  and nothing happens in 5,000 frames of CIRCLE. Next time: read its event script / trigger boxes
  (session 135's VM trace) instead of guessing.
- qemu-arm (`make vita-armcheck`, then the runner on the disc) takes the same path to frame 19,000.

## Session 137: through Dive to the Heart's second station

- **What the station waited on**, read from its scripts rather than guessed: `tools/host/vmdis.py FRAME
  --pad FILE --iso DISC` runs the host under gdb to a frame and disassembles the field's VMs (table
  `D_0038D170`, count `D_0039A570`) label by label, with each VM's pc, entity and position, the
  opcode names (script_vm.c), opcode 1's operations (vm_calc.c) and opcode 24's library functions
  (`D_003D9FE0`). At frame 18,600 VM 0 (the station's master script) was in `waitvm` on VM 1, and VM 1
  in library call 33 (`func_001cc470`, msgwin.c: wait while a message window other than id 7 is
  open): the tutorial window これはフィールアイコンです (the field icon) was up. CIRCLE alone did not close
  it; UP (the command menu wraps from たたかう to its 4th slot) then CIRCLE did.
- **The station's order** (VM 0's loop at pc 107-388, save bytes 780 / 781, D_003C2D30 bytes
  3202 / 3203 / 3205, story byte 2817): しらべる on the door (VM 5, entity 0x40002 at (-8670, -15430)):
  それじゃ あけられないや… (3202 = 1); near the chest (-8670, -14250) the 「?」 command window (3203 = 2);
  開ける opens it (780 = 3); attacking the crate at (-8670, -14880) breaks it, the potion
  (func_001d3610(1), the party's count of item 1, rises above the count saved in variable 2320) runs the
  event that sets 781 = 4 and puts a box at (-9060, -14920) (or (-8280, ...) by variable 2560);
  もちあげる lifts it (なげる while carried) and VM 2's entity going away with 781 = 5 sets 2817 = 49;
  then しらべる on the door opens it, and walking in loads the next area at frame ~28,000 (white, then
  the SELECT look-around tutorial, 「たたかう」コマンドが「はなす」にかわりました, and a Destiny Islands
  question, あなたにとって一番たいせつなものって、何?, answered by a CIRCLE). tests/host/pads/dive.txt
  now runs to frame 32,000. The player is then actor 3 at (-2001, -468, -2810); the kind-4 actors
  6-8 at (-1349, -1040), (-2159, -619), (-1590, -477) are the likely islanders (not checked).
- **Rule 15, statically and with ASan** (portability.md rule 15): `tools/host/localcheck.py` lists
  each call that passes a local's address where the EE callee reaches further (it finds all six of
  session 136's); `tools/host/census.py --exe --asan` builds out/host-asan/kh1-host. Fixed, objects
  unchanged: partyai.nostrict.c's `f32 v[3]` x2 (sceVu0ScaleVectorXYZ writes w), effect.c
  func_001df698, actmark.nostrict.c's `XY` (four words), motion.nostrict.c's `G2Ray` and the
  func_001636d0 draft's `IkRay` (func_00118590 runs to 0x40), fieldcam.nostrict.c func_00177ac0's
  `v80` (a matrix: it was a vector plus `unk[3][4]`), actor.nostrict.c's `t` (read as a quadword).
  The ASan build then runs to frame 19,500 with no report.
- **Register passthrough** (rule 10) found by the ASan build's different stack: pppsys.c
  func_00183878 called `pppStepPrograms()` through a `(void)` prototype, while it takes (sys, draw)
  in a0 / a1, the caller's own two arguments (func_00181b30 passes the draw flag). The plain build
  read whatever the stack held. argcheck.py now checks calls by functions.tsv names too (it
  matched only `func_XXXXXXXX` calls); its one other hit, dkmovie.c's sceIpuSync, is in the
  never-called func_00111238 (BENIGN).
- **An uninitialised read the original has too**: func_0011b6a0 (colobj.c) switches on the flags
  word (+0x28) of the record func_00118868 / func_00118b58 (mapcoll.c) build on the stack, and the
  EE code never stores it (sp+2168 is not written: the PS2 reads its stack's leftover). valgrind
  showed it; the host now gives 0 (the default case) under `#ifdef KH1_HOST`.
- **Open: the ASan build takes another path** from frame ~4,700 (its second room load comes 178
  frames earlier and Sora does not walk at 6,400), with the frame time `D_002BBDFC` the same; not
  traced. A host bug that depends on the stack layout (an uninitialised local) is the likely kind;
  valgrind cannot follow past dkmovie.x (it runs the overlay area's bytes).
  **Traced in session 138**: not an uninitialised local, a task's return value (below).

## Session 138: Dive to the Heart to its end, and the ASan build's other path

- **The islanders** (tests/host/pads/dive.txt, frames 32,200-36,304): the three are script VMs 2-4
  (entities 20000-20002) at (-1412, -2900), (-1489, -2333) and (-2080, -2800); VM 0 loops until VM
  variables 2320 / 2324 / 2328 are all 1 (each islander's label 5 sets its own after the answer).
  はなす (CIRCLE when beside one) asks the question, more CIRCLEs take the first answer. Those VM
  variables are s32 words of `D_0038ACC4` (or `D_0038B4C4` when the VM's flag bit 5 is set) at index
  variable - 2304 (script_vm.c func_001c11d8). Session 137's "Selphie's question answered" was VM
  0's own intro line; no islander had been answered. Then キミの旅は... and the confirm (まあ いっか /
  そんなの イヤだ: CIRCLE takes the first), その日は遠くて近い, and the next station at ~37,800.
- **The station after** (station byte 2817 below 76 on arrival): the menu tutorial (closed by CIRCLE
  presses), 8 Shadows round Sora (actors 1-9 of `D_002C64A0`, kind 3 in the top half of word 1)
  beaten with CIRCLE every 30 frames by ~43,500 (攻撃力アップ!!), the save point tutorial at ~44,500.
  The glass stairs are collision groups 132-160 (byte 11 of the 20-byte triangles `D_002A6238`,
  count `D_002A6258`; vertices `D_002A624C`, 12 bytes): their centres, read from the triangles at
  the station, are the goto points; group 131 is the top station, 130 the start, 100-129 walls
  beside the steps. `func_001057b8(group, on)` sets each triangle's bit 0 (1 = off: VM lib 133 /
  func_001d0500; lib 132 turns a group on). VM 1 turns the walls off a few steps ahead as Sora climbs
  (`func_001059d0`, the group under the player). Trigger box 5 at (-2200, -1750, 7900), 600 wide,
  starts 光に近づけば近づくほど... and Darkside (~49,000); CIRCLE every 30 frames until ~61,000,
  then だけど 恐れないで, キミは世界で一番強い武器を持っている..., and the Destiny Islands opening
  (わわッ!, なぁ カイリ ...) loads; dive.txt runs to 70,000. xl_limit.x is loaded four times on the
  way (41,000-50,800) with no native C; nothing calls into it (its loader's callback only flags it
  loaded), so the run is unaffected.
- **The ASan build's other path** (open since session 137). `census.py --init zero|pattern` builds
  the host with every local zeroed or filled with 0xFE (out/host-init-KIND/; `--init-files` limits
  it to listed files, for a bisection): both followed the plain build exactly to frame 8,000, so no
  uninitialised local. The two builds part at frame 3,133: in the ASan build the task `func_00133a88`
  (objcmd.nostrict.c, the VMs' commands to the game, key 79998) left the main task list, so the
  command that puts Sora at (0, 0, -670) was never run. proc.c's `func_0011f130` drops a task whose
  return value has bit 2 set; `func_00133a88` was `void` (its loop ends when `func_001c45e8` returns
  0, which the EE leaves in v0), so x86 returned whatever eax held. Now `KH1_V0(s32)` with
  `KH1_V0_RETURN(0)` (portability.md rule 10; the object unchanged). Every other function handed to
  `func_0011ef10` / `func_0011f090` (about 170) is defined with an int return.
  Then ASan reported two locals a callee copies a quadword into or out of (rule 15): vm_lib.c
  `func_001d9cb0`'s `v` (read by class1b func_001515d0) and `func_001da2c8`'s `buf` (written by
  mapdata.c func_00105c70), both now four words (objects unchanged). With those, the ASan build runs
  dive.txt to 70,000 with no report.
- **x87 float precision**: the ASan and plain builds still differ slightly (171 / 174 disc reads by
  70,000): positions part by 0.01 from frame ~24,000 and the fight's timing follows. `census.py
  --cflags "-msse2 -mfpmath=sse" --out DIR` builds with single-precision float maths; the plain and
  ASan builds made that way take exactly the same path (182 reads each), and dive.txt still gets
  through Dive to the Heart and into Destiny Islands with it (a Vita-like float model: the script
  does not depend on x87's excess precision).
- tools/host/vmdis.py `--exe` runs another host build (ASan's with its ASAN_OPTIONS).

## Session 139: the English disc, Destiny Islands, single precision by default

- **The English-patched disc on the host** (the default test disc since 2026-10-27; docs/next-session.md
  "The test disc"; en.iso SHA-256 c8ee8c77..., 3,542,579,200 bytes, with PR #149's English mode built
  in). The host logs `kh1-lang: the disc's ELF is the English patch's` and draws English text. Its
  overlays are the pinned ones (ovl/overlays.tsv) except wm.x. tests/host/pads/dive.txt does **not** get
  through it: 90 disc reads by 70,000, stuck at the second station. Two places depend on the run's own
  state rather than the disc's timing alone, so the English disc has its own script,
  **tests/host/pads/dive_en.txt** (dive.txt is left as the Japanese disc's, unchanged):
  - The box after the crate (frame ~25,400) goes to (-9060, -14920) or (-8280, -14920) by the
    collision group Sora stands on when the crate breaks (VM 0 pc 256: lib 379 func_001d3948, the group
    under the player, into VM variable 2560; 105 puts it at -9060). On this disc it went to -8280. New
    pad line **`FRAME BUTTONS goto vm K [R]`** (host/null/pad.c, tested in pad_test.c) steers to script
    VM K's entity (`D_0038D170[K].obj` +0x10) wherever it is that frame; dive_en.txt uses `goto vm 2`.
  - The islanders: the CIRCLEs of 29,100-30,900 already reached the islander beside Sora (VM 4; his
    variable 2328 = 1 by 31,000), so 32,400's CIRCLE opened his talk again and the goto to the next one
    could not move Sora. dive_en.txt drops it.
  With those two, dive_en.txt reaches 70,000 with 182 disc reads (the Japanese SSE run's count).
- **Destiny Islands, the first free roam** (dive_en.txt 70,000-77,500). Sora is free on the beach at
  ~69,500 (player actor 6 at (1997, -79, 2863); VM 0 idles). Kairi is VM 4 (entity 20008, beside Sora);
  her talk (label 5) gives the errand: two logs, one cloth, one rope ("Bring everything back here").
  The pickups are 0x4xxxx entities whose label 6 adds an item (lib 258 func_001d3858, the party's item
  count `D_00304BE8->items[N]`): the logs are item 192, VM 16 (entity 40023 at (2212, 558)) and VM 15
  (40022 at (4782, -219), on the islet); VM 18 (40000 at (-1201, -1093, 401), up on the ledges) gives
  item 193. The other errand item is not in this room. UP + CIRCLE (the command menu's 4th slot,
  Examine) takes a log. Straight north from Kairi is blocked by the shack's round wall at z ~2135:
  the script goes round it at x 2700. The islet's edge needs a jump: CROSS every 40 frames while
  steering (`FRAME CROSS goto vm 15 60`) climbs on. Both logs by ~76,400 (items[192] = 2).
  - A top-down map of the room's collision helps to plan gotos: dump `D_002A6238` (count
    `D_002A6258`, 20-byte entries, `s16 v[4]` vertex indices) and `D_002A624C` (12-byte `Vtx`) with gdb at
    a frame and draw the floors (normal y) and walls (scratch script; not committed).
  - `KH1_HOST_SHOT=640:448::DIR KH1_HOST_SHOT_EVERY=100` gives the 2D layer (text, menus) as PAM images:
    the way to read what the game says on the null platform.
- **Single-precision float maths is the host default** (the user's choice, 2026-10-27).
  tools/host/census.py adds `-msse2 -mfpmath=sse` (`FLOAT_CFLAGS`) unless `--x87`. Before the switch,
  dive_en.txt to 77,500 on the x87, SSE and ASan + SSE builds: 188 disc reads each, positions within 0.1
  (x87 vs SSE). After: the default and ASan builds take the identical path (every goto's start
  position the same) with no ASan report. The Vita build sets its own flags (tools/vita/build.py) and
  is unaffected.
- **A host stack bug ASan found** (rule 15): objfx.nostrict.c func_0012bd98 passed one `V4 m` to
  func_00121a78 (vecutil.nostrict.c), which normalizes three 16-byte rows from it: on the EE m, a and b
  sit at sp+0 / 16 / 32. Now `struct { V4 m, a, b; } r3` (the object unchanged). localcheck.py missed it
  because the callee reaches the rows through a loop index (`addu a1, s2, a0` with `a0 = i << 4`,
  `slti i, 3`); it now follows such an index to its bound and finds this call (the only new hit).
- argcheck.py also lists `task` rows: a void function handed to the task lists (func_0011f090's
  callback, or a wrapper's that passes its parameter on, like func_0011ef10), session 138's kind of bug.
  None today.

## Session 140: the cloth, and the first walk into another room

- **The disc**: the English ISO (en.iso, SHA-256 c8ee8c77..., staged from the Mac's
  ~/Downloads/kh1-test/isoparts-en, read-only, one part per stage call). dive_en.txt to 77,500 still
  takes 188 disc reads.
- **tests/host/pads/dive_en.txt now runs to 91,000** (comments at 77,600 in the script): off the islet
  into the sea, up the lagoon's slope and steps onto the -254 band, round the cliff's foot to its west
  end, up the rocks and along the cliff-top path to the -706 deck, the ladder to the -974 deck, round
  the ring walkway to the long -1055 ledge: walking up to VM 18 (entity 40000 at (-1201, -1093, 401))
  gives **"Obtained Cloth."** at ~87,550 (items[193] = 1; no button). Then back down (a drop from the
  -974 deck's edge onto the band) and south to the exit floor at (-836, 1506): **room 10 loads at
  ~90,110** (D_002BC130 = 10, Sora at (4623, -9003, -1069), 204 disc reads by 91,000). Room 10's VMs:
  VM 2 (entity 40002 at (3175, -8782, -600)) gives item 197 only once story byte 2818 >= 7; VM 3
  (40000 at (3358, -8924, -801)) waits on label 3. The rope (the errand's last item) is not in either
  room seen so far.
- **tools/host/collmap.py** (new): `dump FRAME DIR` saves the room's collision with gdb; `at` (floors
  under a point), `near`, `map` / `slice` (pictures: floors by height, the walls of one height band),
  and **`path`**, a floor-to-floor search (shared vertices walk, a rise of at most 110 jumps, drops of
  any height, rock faces left out). It found the cliff route after straight gotos failed; it knows
  nothing of walls, ladders or exits, so each leg is checked with a run.
  - What the collision showed: floors have normal y > 0.6 in the dump's winding; y grows downwards;
    the sea's surface is a floor at -98 (Sora swims at y ~0); rock faces have attribute & 0x1b0 = 0x1b0
    (Sora slides off; the jump peaks ~110 above the floor and does not grab them); **a ladder is a thin
    wall with attribute 0x000d0120** (t4010 at (-683, 547), y -986..-703: walk into it from its open
    side and Sora climbs); **room exits are floors with attribute bit 0x1000** (t1293 at (-836, 1506)
    on the -254 band, the west bridge t1282 at (-3504..-2631, -652)); the room's entrances (where Sora
    arrives from each room) are `D_002BCDA0` (count `D_002BCDA4`, 64 bytes: the room id, then the
    position and facing; roomload.c func_00113138).
- **host/null/pad.c**: `KH1_HOST_POS=N` prints the player's position every N frames (at pad reads,
  which come every few frames); a goto now stands still while there is no player (the room change
  set `D_002E26A0[0]` to 0 and the steering read through it: a crash in the pad script's code, not the
  game's).
- The Japanese dive.txt (plan item 3) was not run: the old isoparts were not staged.

## Session 142: wm.x (the world map) as native C

Track A of native-plan.md "Beyond speed", the first overlay of the nine: wm.x is 1,105 functions (982
matched, 123 near-miss drafts in ovl/wm/drafts.tsv, three of them new in nonmatchings/wm-native). It now
runs as native C on the host: **from a save in Agrabah to the Gummi ship, the "Select World" screen,
Depart, and back into Agrabah's field with the HUD**, 12,000 frames with no crash
(tests/host/pads/wm_en.txt). wm.elf and gb.elf are byte-identical after every change below; kh1.elf too.

- **The route**: the port has only been played as far as Destiny Islands, so the world map is reached
  from the user's save 04 (Agrabah: Storage, world 8 room 7): load it, the command menu's Save, the Save
  Menu's Gummi Ship, "Board the gummi ship?" yes. wm.x loads at ~6,330 ("kh1-ovl: wm.x loaded: native C
  (1077 pointers fixed up; another pinned file of it)") and its worldmap/*.bin files follow.
  `KH1_HOST_OVL=stub` is still needed: on the way, gumisave.c's func_001b9c60 calls the entry of the
  overlay it is about to replace (xl_limit.x's, no native C) and gets 0.
- **The English disc's wm.x** (ovl/wm/pins.tsv, last commit): the same code, 262 data bytes differ
  (world names at 0xF87BE0-0xF87DF8, offsets at 0xFB4ECC-0xFB4F2D); ovl.c takes more than one pinned
  file per overlay.
- **The synchronous load path** (src/io/discfile.nostrict.c func_001205f0, which wm.x's own loads go
  through) now calls `PlatOvlLoaded` like the queued path; wm.x was never handed to the native hook
  before.
- **VU0 divide by zero** (host/port/libvu0.c): `vdiv` of 1 by 0 gives +-MAX on the VU, so the 0 * MAX
  that follows is 0; the host gave NaN. motion.nostrict.c func_001655e0 divides the zero rows of a
  matrix by their zero lengths after a save load, and the party's positions became NaN.
  sceVu0DivVector / DivVectorXYZ now take the VU's reciprocal (`vu_rcp`).
- **Register passthrough in wm** (portability rules 10 and 11): `tools/host/argcheck.py --ovl NAME`
  (new) checks an overlay's C (hand, auto and the drafts drafts.tsv lists) against its own and src/'s
  definitions. It found 52 calls with too few arguments and 73 value uses of void functions; 116 are
  fixed (the caller's own a0 / a1 passed on, wrappers that tail-call with every argument, the last
  call's value returned, `KH1_V0` where the PS2 object needs void). The other 9 are left: comma
  expressions in a draft's loop condition, tail wrappers whose value nobody reads, and func_00f41c28,
  which never returns. The crash that started it: func_00f2b870 called func_00f64b88() without its
  handle. func_00f68770 (33 callers use its handle) also dropped the matrix its first call takes in a2.
- **Float argument order** (rule 11): 30 prototypes put an f32 where the definition has an int (wm.x's
  curve functions, func_00f4ec30 / f4f188 / f4f6d8, func_001655e0 ...). 16 declarations were reordered
  with their calls; where that changes the PS2 code (14 declarations in 12 files), the file keeps the EE's prototype under `#ifdef KH1_PS2` and the
  host gets the definition's order through an inline `ee_xxxxxxxx` wrapper and a `#define` (a
  function-like macro cannot be used: ovlnative.py's names.h already defines func_X as wm_X).
  abicheck.py reads src/ only; the scan was a one-off (both checks should learn `--ovl`).
- **DMA by register** (include/platform/dma.h): wm.x and gb.x start their draw-list nodes' chains by
  writing D_STAT, VIF1's and GIF's QWC / TADR / CHCR directly. `PlatDmaPutGifChcr / Qwc / Tadr` are new
  (the host walks the chain like PlatDmaSend on channel 2) and the six functions use them with
  `PLAT_DMA_ADDR`. dkmovie.x's IPU registers (0x10002000) are left: it is not on this route.
- **One library call** passed no argument: auto func_00f2c8d8's sceVu0UnitMatrix() (a0 was the
  matrix).
- **Memory card order** (host/port/mc_dir.c): GetDir listed a directory in readdir's order, which
  depends on how the host made the folder; a fresh copy of the card moved save 04 and the pad script
  loaded another save. The entries are now sorted by name.
- **No 3D**: the null platform draws no 3D, so the map's galaxy and ship are missing from the shots; the
  menus and text are drawn.
- **Drafts on the route** (tools/host/draftcov.py, new: a gdb breakpoint on every draft): **31 of the
  123 drafts run** on wm_en.txt's route (function, words its draft differs by): f23550 (2), f32770 (2),
  f43430 (2), f3a030 (3), f7cb60 (3), f436d0 (4), f7ecd8 (5), f42ce0 (12), f79868 (12), f651d0 (13),
  f66b38 (14), f29dc0 (20), f79700 (24), f7a350 (31), f3a860 (32), f78bc0 (50), f2b598 (54), f3f998 (56),
  f7bde0 (59), f66bd0 (61), f78978 (100), f7c880 (107), f344f0 (112), f23628 (130), f2ac98 (165),
  f46cb8 (210), f33e48 (416), f7d0a8 (499), f7ad38 (760), f31430 (810), f7de08 (933). **None is checked
  against PCSX2 yet**: that check (native-plan.md track A) needs the same save loaded in PCSX2 and the
  same pad script, comparing positions, wm.x's data and the menus' text at the same frames. Until then a draft on this list is a suspect for anything
  the world map does wrong.

What is next for wm.x: a world that is not the current one (a Gummi flight, most likely gb.x, which has
no native C yet), Warp Drive, the ship editor, and the PCSX2 check of the 31 drafts above.

## Session 145: gb.x native, and the Gummi flight and garage on the host

Track A's second overlay. gb.x (529 functions: 470 matched, 59 near-miss drafts in ovl/gb/drafts.tsv)
now links as native C on the host (`ovl: native overlays linked: ... gb.x wm.x`; relocs.tsv 795 pointers,
15 of them functions). The English disc's gb.x is the pinned file (no pins.tsv). Run on the Mac in an
x86 Docker container under qemu-user (no ee-gcc or `-m32` gcc on macOS); the notes below on the
emulator matter for anyone else doing that.

- **The Gummi flight and the garage are wm.x's code, not gb.x's.** With gb.x linked, two new pad scripts
  run on the English disc with no crash: **tests/host/pads/gummi_en.txt** (save 04 to the ship, the left
  stick up for 3 frames picks "Warp Hole" on Select World, Depart: the gumi_manual events, the flight's
  radar HUD from ~7,400 to ~10,100, a white flash at ~11,000, Select World again at ~11,400; 12,500
  frames) and **tests/host/pads/garage_en.txt** (SQUARE on Select World: the GUMMI BLOCK MENU and the
  ship editor's screen; 10,000 frames). gb.x loaded in neither. It is game mode 6 (gamestate.c case 6:
  gumisave.c func_001ba7e0 "Run Gumi Edit", which wm.x stores at D_003772FC and gb.x's own code stores
  func_001ba870 back); **the route that starts it is not found yet**. Inputs tried: the Save Menu's other
  rows, START / SELECT / TRIANGLE / SQUARE on Select World, CIRCLE / CROSS / START through the garage.
  The flight route reached so far ends back on the map, so "arrival in another world" is not shown yet:
  the destination the 3-frame stick picks is the warp hole, and longer stick presses pick 21 / 23 / 25,
  whose Depart did not start a flight in 14,000 frames (not read further).
- **Select World's controls** (read from memory dumps, KH1_HOST_DUMP below): the left stick moves the
  destination (the word at 0x00FB6108: Agrabah 8; 22 after 3 frames up, 21 held 100 frames up, 23 down,
  25 up-right), the D-pad UP / DOWN only moves between Normal Drive and Warp Drive, LEFT / RIGHT / L1 / R1
  do nothing there, SQUARE opens the garage.
- **gumisave.c func_001b9c60** loads an overlay and calls it through `fn`, the overlay area's address
  taken before the load. On x86 that faults into the entry trap; on ARM and the Vita nothing redirects
  it (tools/vita/build.py rewrites calls *of* `D_00F20000`, not of a pointer holding it). Ports now
  call `((void (*)(void))D_00F20000)()` by name (`#ifdef KH1_PS2` keeps the EE's `fn()`).
- **Register passthrough in gb** (`argcheck.py --ovl gb`: 21 short calls, 38 void-value uses): every
  hit fixed from the original's asm (the caller's a0 / a1 passed on, seven tail wrappers return their
  call's value, the draft func_00f446d0 passes its `wait`, func_00f4ec88 its D_00F82D94 and a1 = 1) except
  four BENIGN rows in argcheck.py (func_00f40438 / func_00f405c0 are never called; func_00f40830's types
  0-5 set the arguments it was not given; two comma / tail-return uses).
- **EE-only argument order (rule 11) in gb and wm**: `abicheck.py --ovl NAME` (new) found 8 in gb and 14 in
  wm that session 142's one-off scan missed, among them wm.x's func_00f3d4d8 passing func_00f3caf0
  (vec, vec, f32, f32) as (s32, f32, vec, f32), which crashed the host on the first world picked. It now
  also reads CONTEXT_ONLY copies (weak definitions off the EE, so a file's calls use their order: wm
  func_00f3cdd0). Fixed with the rule-11 `#ifdef KH1_PS2` branch and an inline `ee_X` wrapper; two
  drafts' u64 first argument (func_00f377b0, func_00f5e8a8) declared u64; four callers that declared an
  f32 return for a void function (or void for an f32 one) given the definition's class off the EE.
- **Struct returns**: `GbPos func_001bbdf0(...)` (gb and wm, 2 bytes) and util.c's `Col func_001eddc0`
  (choice.nofill.c calls it as returning an int; START on Select World crashed in it) are i386 hidden-
  pointer returns; the host now builds with `-freg-struct-return` (portability.md rule 11), and the
  four GbPos declarations also go through an int-returning wrapper.
- **CONTEXT_ONLY data hid the loaded overlay**: ovlnative.py's data names were `PROVIDE(...)` linker
  symbols, and a weak definition wins over a PROVIDE, so wm.x's `CONTEXT_ONLY W58 D_00F87E98[1]` (11
  such copies in wm / gb) made the native C read a one-element array instead of the file. They are
  plain script assignments now (`wm_D_00F87E98 = kh1_memmap + ...;`), which win over weak and strong
  definitions alike.
- **Open crash**: TRIANGLE then CIRCLE on Select World (the world's picture, worldmap/wi/wp_al.tzb)
  writes through a null packet pointer in wm's draft func_00f22358 (209 words off) via func_00f667b8.
  Not on either route.
- **Not done**: the PCSX2 comparison of these routes (positions, script state, the same frames) and a
  Vita3K run with gb.x linked. The black-screen thread found that linking wm.x natively blacks out the
  Dive on the Vita (2026-11-03); gb.x is linked the same way, so check that thread's fix first.

**Host runner additions** (host/null/main.c):

- `KH1_HOST_FORK=N:PAD[,PAD...]`: at frame N the run forks one child per pad script (output in PAD.log,
  shots in PAD.d/), one after another (they share the disc image's file offset: two at once read each
  other's sectors). Twelve Select World inputs from frame 6,650 took ~75 s.
- `KH1_HOST_DUMP=F[,F...]:ADDR:LEN`: the memory map's bytes at those frames, to diff two inputs' effect.
- `KH1_HOST_SHOT_FROM=N`: shots from frame N without the chain walk before it. Much faster, but a texture
  uploaded before N (the fonts are uploaded at boot) is missing, so menus come out black: not useful for
  text. With the chain walk from the start a shot run is ~50x slower than a plain one under emulation.
- The crash handler runs on its own stack (a broken stack killed it silently) and prints the faulting pc
  and sp first; the overlay entry trap checks the faulting pc rather than si_addr, which qemu-user
  reports differently.

**Building under emulation** (x86 Docker on an Apple-silicon Mac): ee-gcc and gcc crash now and then
(a segfault or a truncated object that `ld` rejects with ".symtab local symbol at index"): retry, and
delete the truncated object. Worse, qemu-user's ee-as / ld writes `lw` for some `%hi` `lui`s: 20
kh1.elf functions, gb func_00f429b0 / func_00f46ee0 and wm func_00f2d308 / f39968 / f69aa8 / f6dfd8
differ from the original only that way, all in files this session did not touch (or touched only under
`#ifndef KH1_PS2`). Byte-identity has to be checked on real x86 Linux. gdb does not work (no ptrace).

## The Vita's save-point route, and where gb.x starts (2026-11-03)

wm_en.txt / gummi_en.txt / garage_en.txt never reached the world map on the Vita: in Agrabah the
command menu's 4th slot read "?" instead of "Save", and UP + CIRCLE did nothing. **Not a port bug: the
pad script's timing.** Found with config.txt's new `padlog=` (vita-build.md):

- The Vita reaches the field from save 04 by ~2,700 (the host by ~3,300), so the script's 2800 and 3100
  CIRCLEs, confirms on the host, are Attacks there: Sora lunges from (-419, 288) to (-431, 359).
- The save point is a command object of kind 1, range 50, at (-456, 282). While the player is in range,
  cmdmenu.nostrict.c func_0012d930 calls its handler (objheal.nostrict.c func_00156d88, case -1), which
  puts Save (id 0x36) in the top list's 4th slot. Out of range the slot keeps id 0, drawn as "?" and
  masked off, so CIRCLE on it does nothing.
- The pad itself is fine: one read a game frame (the field runs at 30 fps, so reads alternate 1 / 0 a
  vblank), each press seen once. The "D-pad skips slots" report was the same confusion.
- **Fix**: the three scripts walk back onto the save point (`3400 - goto -456 282 12`, `4400 -`). On the
  host Sora was already there and steps ~30 units in; wm.x still loads at ~6,300. In Vita3K (main
  f8afa7e1 + this change) the Save Menu, Gummi Ship and "Board the gummi ship?" lead to **native wm.x on
  the Vita** (`wm.x entry (2, 83) returned 1` at frame 6,327) with no crash to 9,180; gummi_en.txt goes on
  into the flight's files (gumi/*, gumi_manual_*.ev) and was still running at 8,760 when the run's time
  ran out (Vita3K slows to ~10 frames/s on the map).
- **On hardware** the user's hand-played run crashed right after that same first entry call (frame 2,122,
  log ends at `wm.x entry (2, 83) returned 1`). Vita3K does not reproduce it, so it is one of the
  hardware-only kinds. **Found and fixed from its psp2core dump**: a data abort in hud/ui.c func_0024a490
  (the command menu's sprite animation) reading through 0xaaeadb48. func_0024aac8 turns a sprite file's
  key indices into pointers and skips entries already done with `(s32)ptr <= 0xfffff`; a Vita pointer
  (0x81xxxxxx) is negative as s32, so the HUD's second set-up on the way to the world map relocated every
  frame pointer again. The test is unsigned off the EE now (the EE's code unchanged). Vita3K did not fault
  on the garbage read. The user's hardware run after the fix: wm.x's first entry passes, the world map's
  files load and the map runs (~3 fps: the watchdog shows the game thread ~2 s of each 2 s, VIF1's walk
  2,060 ms of it, so the map's 3D is on the emulated VU1 path; 7 bad DMA sends a window, 2,400 by frame
  2,624). Its speed is a separate task.

**gb.x (game mode 6) is started only by a field script**: library call 488 (vm_lib.c func_001d8b48,
D_003D9FE0[488]) calls roomload.c func_00112e08, which asks for state 6 (func_00109558(6)); gamestate.c
case 6 then runs gumisave.c func_001ba7e0 ("Run Gumi Edit"). The Save Menu's Gummi Ship is library call
func_00112d80 -> state 4 (wm.x). A VM word is opcode in byte 3, argument in bytes 0-2, so the call is
the word 0x180001E8 (little-endian e8 01 00 18). Decompressing every KINGDOM.IDX file (extract_kingdom.py's
decoder) and searching for it: **the only room script with call 488 is tw01.ard (Traverse Town)**, at
offset 0x28ee3d of the decompressed file (script code sits at offsets 1 mod 4 there, as in the other
rooms). The words around it read as a choice dispatch: `push 2; jump-if 3 ...; push 3; jump-if 4 -> lib 488`,
so it is most likely a conversation menu's third answer that opens the Gummi editor (who says it in
tw01 is not read yet: vmdis.py on the host at that room would show the VM and its entity). The user's
saves (Agrabah, End of the World) are not in Traverse Town: the route to gb.x is a save there, or a
walk from a world's save point via the world map's Traverse Town. Lib 487 (func_001d8b28) is in most
End of the World rooms, cp21, di01 / di03, dh05, pc05, tw03 and iz46 / iz48.

## The route into gb.x, and gb.x running (2026-11-04)

**tests/host/pads/gbx_en.txt** goes from save 04 (Agrabah) to the Gummi editor and back, on the host and in
Vita3K, with no crash:

- **Select World to Traverse Town**: the left stick up for 40 frames (destination 21), back to centre, then
  left for 12 (destination 3); Depart (three CIRCLEs as in gummi_en.txt) lands in **tw01.ard, the First
  District**, with no flight. The destination words seen with KH1_HOST_DUMP (Agrabah 8): up 22 / 21, down
  24 / 23, up-right 10 / 13 (13 = Neverland, pp08.ard), and from 21: left 3, right 4, down-right 4; from 24:
  up 5, left 11; from 13: right 26, down 9. Left / up-left / down-left from Agrabah stay on 8.
- **Who opens the editor**: library call 488 sits in script VM 4's code (entity id 20000, at -603 -640 1400:
  the counter up the stairs from the district's square). Its menu reads the answer from variable 2304:
  1 runs library calls 100 / 101 (the shop), **2 is call 488** (the Gummi menu), 3 sets 126 = 7 (a chat), 4 closes
  (Vita3K's window capture shows the four answers in that order). So it is
  the menu's **second** answer, not the third as read above (the third push/jump pair is answer 3's).
- **The walk** (collmap.py path on a KH1_HOST_COLL dump, below): from the arrival point (65, -3822) north to
  (121, -119) at y -240, then east and up the ramps (960, 190) -> (1150, 515) -> (917, 832) at -480, west
  along the upper walk to (100, 1490) at -640, then `goto vm 4 60`, which stops ~70 units off (the counter).
  The legs' frame spacing is distance / 8 x 1.6 + 40 (Sora runs ~8 units a frame): fixed-frame legs that
  are too short send the next leg off from the wrong place and into a wall.
- **Talk and answer**: CIRCLE (talk), DOWN, CIRCLE: gb.x loads as native C (795 pointers fixed up) at
  ~10,700 on the host, then gumi/gumi_tex.bin, gumi_ini.bin, gumi_bg.bin, systex.tzb, gumi.tzb, gumi.aml /
  .amo and SASAMSG.BIN. **Vita3K** (this branch's VPK): `gb.x entry (2, 55) returned 1` at frame 10,671 and
  the GUMMI BLOCK MENU (Garage, Gummi Ship, Inventory, Help, Tutorial, Exit; the ship's model and Chip's
  picture) drawn by the native renderer, no crash to 16,000.
- **In the editor** (host, KH1_HOST_FORK from 11,900): CIRCLE / CROSS / D-pad / START / TRIANGLE / SQUARE /
  L1-R2 sequences run to 15,500 with no crash; UP (the cursor wraps to Exit) + CIRCLE x3, or DOWN x5 +
  CIRCLE x3, or Garage then CROSS twice and Exit, return to the First District (tw00_01.img, tw01.ard and
  the voice banks load again). gbx_en.txt ends with the Garage-and-Exit sequence and a waitplayer.
- **Vita3K, the whole script** (14,000 frames): wm.x at 6,327, tw01 at ~8,000, gb.x at 10,671, the Garage /
  Exit sequence back to tw01 (the counter's menu shows again), no crash. The First District's 3D is mostly
  dark or missing in Vita3K's window there (the HUD and the menus draw); not looked into.
- Not done: the hardware run, and reading the editor's screens past the menu (the host's shots of gb.x
  need the chain walk, ~50x slower; Vita3K's window capture shows them).

**New host switches / pad steps** (host/null/pad.c):

- `FRAME - waittitle` holds the script's clock, like `waitplayer`, until the title menu takes CIRCLE:
  dktitle.x is the current native overlay, its state D_00F2C708 (func_00f228c8) is 27 (NEW GAME / LOAD)
  and the fade D_002BC07C is 128. State 26 (the logo) skips to 27 on any button or after 240 frames, so no
  START is needed; on the host the menu is up at ~1,209. The save-loading scripts (load_en, wm_en,
  gummi_en, garage_en) and fight_en now start with `1250 - waittitle` in place of `1300 START`, since the
  Vita's title ends 1,000-3,000 frames later and presses before it were lost (fight_en still reaches the
  floor break; gbx_en / wm_en's prefix still reaches wm.x).
- `FRAME - waitcard` / `FRAME - waitslots` (after the first hardware run, 2026-11-04): on the Vita the title
  wait passed but the save never loaded: the load screen's card checks run longer there, so the port's CIRCLE
  (loadframe.c func_0022b410: before the card is seen, D_00425C28[0].x0 3, it opens the "no card" box) and the
  slot list's DOWN / CIRCLE came too early. waitcard holds until D_00425C28[0].x0 is not 3, waitslots until
  loadmenu.c's step D_006437DC is 19 (the list open; on the host 45 frames after the port's CIRCLE). The
  save-loading scripts have `1810 - waitcard` and `2200 - waitslots`; the host's timing is unchanged. With
  KH1_HOST_TRACE the runner also prints "pad wait over at frame N" when a wait ends.
- `KH1_HOST_POS=N` now also prints the field's script VMs whenever their set changes (a room's arrival):
  `vm FRAME K id ID code ADDR pc PC at X Y Z`. A script found at offset O of a decompressed ROOM.ard runs
  in the VM whose code address range holds the "loaded ROOM.ard ... at" address + O. This replaces
  vmdis.py / gdb for `goto vm K` under qemu-user.
- `KH1_HOST_COLL=FRAME` writes the room's collision to coll/tris.bin and coll/verts.bin at that frame
  (relative to the run's directory), the files `collmap.py at / path / map` read, without gdb.
