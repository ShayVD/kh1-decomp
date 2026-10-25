# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is back from Monday 2026-10-26** (the user said on 2026-10-23 it was away until then; sessions 49 to 76
ran without it; sessions 77 to 91 ran on Sunday 2026-10-25, still without it). **Ask for the Mac and PCSX2 at the start** (the connect card in the Claude desktop app) **and make
item 1 the first thing**: nine float builds are waiting for a boot. Items 2 and 3 also need the Mac: the user's ISO
is in Downloads for the host run, and the overlay files are in Downloads/kh1-test/ovl. If the user says the Mac is
still away, skip items 1 to 3, add every float change to docs/float-untested.md as untested, and do the static
items.

## Where we stopped (end of session 91, 2026-10-25)

- **Session 91** (static + host, vita-port-plan 5.1ae, renderer-spec 5.3.1 and 5.4): **the drawn
  rectangles, the camera matrices in C, the wide switch.** **`gsstate.py RUN.txt --extents`**: the drawn
  rectangle per send in target pixels (host/null/gsregs.c keeps each draw state's vertex extent less
  `XYOFFSET`; draw lines end in `, xy X0 Y0 X1 Y1`); a send from the HUD's staging buffer `D_00351E10` is keyed
  by the environment sent before it (`D_00651C00 ch2 > D_00351E10 ch2`), with 5.3's anchor; on the fake disc
  only the clear, frame copy and flash (full screen). **host/port/view.c** = `func_00110618` in C for every
  port (the session 12 draft's maths; session 6's w6_02 has m5 wrong), linked on the host instead of the
  draft (census.py `HOST_TWINS`). **`tools/host/viewcheck.py`** (new) runs the original's 268 instructions
  from the ELF in an interpreter: **bit-identical** to view.c with IEEE rounding on 13 argument sets (2 ulp
  with the EE's round-toward-zero). **`KH1_HOST_WIDE=W:H`** (`1` = 960:544): only the two frustums' x scale
  change (x 0.7556), the markers' bounds 1709.2 .. 2386.8, objwin's -82 .. 594 through
  **include/platform/view.h** `PLAT_VIEW_X0 / X1` (0 / 512 literals on the PS2). **No other frustum in the
  main ELF** (journal, party menu, objwin, shadow, lens grid: view -> screen only; `D_002BC140 / 144` are the
  effects' / sound listener's camera pointers, the Gummi overlay sets them). **Bit 35's plan**: records'
  `flags & 0x20000` in roomobj.c's lists after `func_00132c70`, the object-script halfword `0xA30B` (table 0
  entry 163). **every out/build object bit-identical**, the shift ELF the same (no float-untested row).

- **Session 90** (static, vita-port-plan 5.1ad, renderer-spec 5.3.1 and 5.4): **the culls under a wider
  view, the HUD's anchor table, movies.** renderer-spec 5.4: **no CPU cull reads `D_002BC020`** (it is
  renderer A's 1636 x 303 px guard box, not a frustum; 2.2 and 5.3 corrected). `func_00110618` builds six
  matrices; the culls use the two **exact 4:3 frustums** `D_002BBE60` / `D_002BBEE0` (as `D_002BBFA0` /
  `D_002BBFE0`, 320 x 229 at scrz): the grid (`func_00107548` -> `func_00107ab8`, 8 box corners, no cone),
  props `func_00114a38`, actors `func_00135bb0`, shadows `func_00127c20`, ppp effects `func_001812d0`
  (off-screen ones also stop updating) and the party warp `func_00169f28` (picks an off-screen point) all
  go through `func_0024edf0`. **Hor+ = one constant** (the x 320 times 1.3235 in `func_00110618`); the
  projection stays. **Bit 35 of `x370` ("drawn") feeds gameplay** (flag-`0x20000` actors' motion, action
  25, script command `func_0012a030`, the lock-on line of sight). Lock-on has no screen test.
  `func_00121000` is not a cull (P18 flag). Markers `func_00249580` (`D_00469F90` / `D_00469FA0` =
  1792..2304 x 1856..2240) and objwin `func_0010b390` (0..512 x 0..384) need port-side bounds.
  **renderer-spec 5.3.1**: the HUD's sprite files (`UiFile`, rectangles in target pixels) plus each
  drawer's origin give every part's rectangle without a boot: Sora's gauge (360,257)-(503,375) right /
  bottom (`D_00454600`), the party gauges top right, the command menu (16,260) left / bottom, notice and
  banner (160,344) centre / bottom, pop-ups from (16,16), the counter (25,238), the timer; **the target's
  gauge is fixed at (16, 24 / 65 / 80), not a marker** (5.3 corrected). vita-port-plan 5.1ad **movies**:
  `func_00111020(n)` loads dkmovie.x to `0x00F20000` and calls `entry(0, n)`; commands 1-9 (start, status
  2 ready / 4 ended, width, close, stopped, the band's flags, frozen step, frame count / current);
  started by gamestate.c states 11-13 / 16-18 (asked for by dktitle.x, inferred) and script opcode 24
  entries 584 / 585 / 489 / 490; names `D_0046A058` (opn, end, end2, demo, end3, ffx2 .dat); no libmpeg
  in the main ELF (the decoder is in dkmovie.x); a `PlatMovie*` layer drafted (sceAvPlayer on re-encoded
  files or a software MPEG-2 decoder; licence open). Only docs/ changed: **every out/build object
  bit-identical**, the float ELF the same (no float-untested row).

- **Session 89** (static, vita-port-plan 5.1ac, renderer-spec 5.3): **the 2D layers' space, vibration,
  the CIRCLE / CROSS swap.** renderer-spec 5.3: every 2D drawer (windows, text, field text, HUD, notices,
  menus, markers projected from 3D) draws in 1/16 pixels of the 512 x 384 target at `(0x7000, 0x7400)`;
  outside it only the post-copy flash, the system-message band, fade.c's ending and the 640-wide movie
  buffer. **The target's pixels are square** (448 lines were NTSC's), so the plan is **4:3 at about
  725 x 544 (scale 1.4167) between bars first**, one affine map on every GIF-path draw, and later a hor+
  option (clip matrix `D_002BC020` / viewport `D_002BBF60`, full-screen passes widened, a port-side HUD
  anchor table, markers not anchored; **renderer A's grid visibility `func_00107548` must be checked
  first**). winmenu.c's y getter / setter use 0x7000 (no main-ELF caller). vita-port-plan 5.1ac:
  **vibration**: type-20 patterns, `{time, level}` ramps per motor, small motor on at >= 128, large 0-255,
  libvib's 3-profile packing; **the ELF's 7 patterns decoded** (hit reactions use 0 / 1 / 5 / 6; 2-4
  unused in the main ELF), event and object-script patterns from the disc; vm_lib.c `func_001d39b0` was
  commented as a sound, it starts a vibration (comment fixed); the PS TV wrapper's `SceCtrlActuator`
  mapping and a zero when the game stops sending. **The swap**: swapping 0x2000 / 0x4000 in
  `PlatPadRead` moves every confirm / cancel (81 raw cancels in 28 menu files, the window confirm
  `func_001fe5a0`, the action table, selector, framectl); padrec's replay / script stay right above it.
  **What does not follow**: the ELF's window font has no face-button icon (only L1 / R1, cells 8 / 9;
  font sheet decoded), so the message font's button glyphs and the disc's HUD / menu textures need
  port-side swaps, read from the real disc. Only docs/ and two src comments changed: **every out/build
  object bit-identical**, the float ELF the same (no float-untested row).

- **Session 88** (static, vita-port-plan 5.1ab, renderer-spec 4.17): **the other full-screen effects, the
  input layer, counts kept across functions.** renderer-spec 4.17: `func_00102a48` is the **menu blur**
  (the frame captured at half size when a field menu opens, nine blended copies 1 then 2 px apart; not
  "glow rings"), `func_00103058` a **depth blur** (event commands; mode 0 blurs behind a Z value, mode 1
  the near part), `func_001032b0` a **sway / colour pulse** (room table flag or event: a 0.3-3.6 % zoom on
  two out-of-phase axes), `func_00103c48` VU1 P8's **lens grid** (25 x 25 bulge over a copy of the
  target), the **fades** (alpha to 255: the visible fade is half the count; the white fade-in's countdown
  runs in frames, dark at 60 fps), the event **letterbox** `D_002A6208`; **the sway and the grid copy the
  target into the Z buffer's memory** (later depth tests that frame read colour); the PSMT8H rows of 3.1 /
  3.2 named `func_00103058` by mistake. vita-port-plan 5.1ab: the pad record (repeat 30 then 4 steps, a
  47 % square stick dead zone), only socket 0 read, **the 30-entry action table** decoded (SELECT 0x8000 =
  first person; START has none: session 87 said both), what reads each button, the menus' raw reads, and
  **the Vita mapping** (L / R to L1 / R1, **L2 / R2 on the rear touch halves**, R3 doubles CIRCLE, L3
  unused; PS TV pads native; options: CIRCLE / CROSS swap, right stick camera). tests/host/pads/title.txt
  (a `KH1_HOST_PAD` title script, frames guessed). **tools/host/countcheck.py** (new): globals one function
  steps and another indexes with: **37 rows, 16 counters, all REVIEWED**; DATA-bounded only (no check, the
  PS2 the same): the collision list `D_002BD250[2048]`, renderer A's grid lists, **renderer B's per-frame
  lists** (`D_0055C698`: 72 / 78 / 480), **the message table `D_00388480[273]`** (layoutcheck misses it),
  the 10 trigger boxes. Only docs/, tools/host/, tests/host/ and a sceneeff.c comment changed: **every
  out/build object bit-identical**, the float ELF the same (no float-untested row). layoutcheck / relcheck
  / walkcheck 0.

- **Session 87** (static, vita-port-plan 5.1aa, renderer-spec 4.16): **index walks and builder results,
  a scripted pad, the script's screen spin.** **walkcheck.py** now also lists `idx` rows (an integer a
  loop steps that a later loop indexes with) and `call` rows (a pointer a builder returns, stepped on by a
  later loop; 88 builders): 21 + 4 new rows, all read (IDX_REVIEWED / CALL_REVIEWED), **42 rows, 0
  WALK**. Found: **savemenu.c `func_00228588` steps `j` by 2** when it fills the party (`buf[3]` or
  `buf[2]` left unset, a stack byte < 10 goes into the party; the PS2 does the same, so check on a boot);
  wintext's message code 11 passes a message byte as the digit count of a `dig[12]` (check the real
  disc's messages). **host/null/pad.c** (new, plat_null.c's pad calls moved there): **the null pad is now
  connected** (before, every host run sat in `func_0010f918`'s "no controller" loop from frame 32);
  `KH1_HOST_PAD=none` the old answer, **`KH1_HOST_PAD=FILE`** a script of `FRAME BUTTONS [RX RY LX LY]`
  lines (`START`, `CIRCLE+UP`, `0x4000`, `-`, `out`), `KH1_HOST_TRACE=1` prints `kh1-host: pad FRAME
  BUTTONS`; tests/host/pad_test.c (18 checks). `D_002C5BB0` holds **actions** through the 30-entry table
  `D_002C5990`, not the PAD_* bits (START / SELECT have none). **renderer-spec 4.16**: `D_002BBE04` 1 / 4
  (objscmd.c `func_0012b450`, vm_lib.c) blend the frame last shown, turned by a ramping angle, into the
  target before the frame copy (1 over the live scene, 4 over the frozen last frame: a feedback swirl);
  a negative angle is used at once, a 0-frame record divides by 0 (EE `FLT_MAX` vs IEEE NaN). Only
  tools/host, host/, tests/ and docs/ changed: **every out/build object bit-identical**, the float ELF the
  same (no float-untested row). layoutcheck / relcheck / abscheck / dmacheck / abicheck 0, valgrind 0
  errors to the overlay fault, the stub:2 run ends in func_00132790 as before.


- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-91.
- **Nine default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032), 34
  (2,049, unchanged in 35 to 58), 59 (2,053, unchanged in 60 to 68), 69 (2,043), 70 (2,041; sessions 71 to 85
  left the float ELF's bytes the same; so did 87 to 91) and **86 (2,041, the current default: D_0063F640 inside the floated
  sound status block)**. Session 69 made 21 objects one definition (vita-port-plan 5.1i): 10 objects that floated in place as
  parts of a run now float whole into the float area (the shop / list windows D_0062F6E0 / D_0062F790 / D_00630460,
  the ppp matrices D_00615E70 / D_00616000, D_0052EB50, D_00551700, D_00575900, the timer sets D_006692F0 /
  D_00669320) and 20 neighbours are pinned. Session 70 made 6 more one definition (5.1j: the command menus
  D_00650120[7], the object slots D_00550400[64], the DMA packet area D_00573AC0, the hit records D_0054C440 with
  areabox's groups, the list callback D_006305C0, the ability counts D_00642C70): only 2 newly pinned (D_00642C70,
  D_00650DD0), nothing newly floats. The undo of each is reverting that session's commit (float-untested.md rows 69,
  70, 86). docs/float-untested.md lists every change since the last booted build (KH1_F29_N) and the switch that undoes
  each. Session 59 released 4 names (`--no-fmt-read`, low risk); session 34 released 19 (bisect order
  `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`).
- **Register passthrough** (portability.md rule 10; vita-port-plan.md §5.1c-§5.1e): argcheck lists **0 short
  calls and 3 value uses**: func_001ffaf0 (winmenu.c), func_002040a0 and func_00206710 (winpart.c) have no
  caller in the main ELF; check them against dktitle.x's calls into the main ELF. BENIGN keys may name the
  caller (a third field).
- **Calls through pointers** (`python3 -I tools/host/indcheck.py [--all] [--tsv out/host/indcheck.tsv]`,
  vita-port-plan.md §5.1e-§5.1h): **0 `?`, 0 DATA, 0 OPEN, 0 `?def`** (session 68). 242 rows: 117 OK, 42 READ,
  70 OVERLAY, 13 CLANG (gcc nested functions in ppp/keshptail(x), kethdraw; a draft's `$10`). Session 68:
  ASM_TAKES holds the parameters of assembly / SDK targets read by hand (FlushCache, iFlushCache, the libvu0
  RotMatrix trio, SyncDCache), and a piece called as one pointer reaches its first `.word` only. Session 67: PSys.mods are &D_00370200[id] (the words
  pppRelocProgram relocates), so pppsys.c's system steps call PppClass fn10 (never set) / fn14 / fn18 (all
  take nothing); the Range52 is func_0010f558's choice list (msgwin / list / shop, FIELD_SAME). The 70
  OVERLAY rows (vm_lib's 41 hooks, mcstep's request hook 13, partyctl's cb44 4, textwin's x0 2, the setters
  func_001c06c0 / func_001468f8 / func_0012cab8, D_00304B6C, D_002E27D4, D_00616220, func_0011f228, vmath's
  handler stack, gumisave's two overlay entry calls) are for the dktitle.x / overlay check.
- **Argument classes** (portability.md rule 11): `python3 -I tools/host/abicheck.py` (text) and indcheck
  (trees) both 0. Run both after any new declaration. indcheck: **0 CLANG** (session 69: the three nested-function
  files are CLANG-READ, read from their gcc host objects, which have no `call *`).
- **DMA addresses** (portability.md rule 13): `python3 -I tools/host/dmacheck.py` at **0 rows** (run it after
  touching packet code; `--list` for the sends).
- **PS2 addresses as numbers** (portability.md rule 14): `python3 -I tools/host/abscheck.py` at **0 rows**, code
  and data (after `make host-census` and a `make shift`; run it after matching or editing code that names an
  address, or after a data change; `--all` lists the decided data words).
- **Layout dependencies** (portability.md rule 12, vita-port-plan.md §5.1i-§5.1k): two checks, both at **0 rows**;
  run both after any data change (a new row is a host crash waiting: opdma in 64, the notice in 68 were found by
  crashing). `python3 -I tools/host/layoutcheck.py` (after `make shift` and `make host-census`) reads the linked
  PS2 ELF: code that reaches past its variable's host definition (10 false positives in its REVIEWED table).
  **`python3 -I tools/host/relcheck.py`** (session 70, after `make host-census`) reads the host objects'
  relocations, where the C name is kept (session 71: also the PS2 objects and the unlinked drafts; `--no-ps2`,
  `--no-drafts`): it finds C that names one variable and lands exactly on the next
  (`&D_00650120[6]` = D_00650C00, invisible to layoutcheck); its REVIEWED table holds 39 compiler patterns (loop
  ends to a field, folded `a[i - 1]`); `--all` adds the references exactly at an end (read in 70: loop ends).
  census.py keeps names with no C definition at their PS2 distances (out/host/defs_host.c blocks) and aliases
  names inside a C definition into it (out/host/aliases.ld); shift_ld.py lets such a field name follow its floated
  object. layoutcheck `--all`'s 733 unbounded index rows were sorted in session 70 (5.1j): an idx-next row is any
  index the analysis cannot bound, so reading does not shrink the list; relcheck found the real splits instead.
  An `s32 [5]` at a 4- but not 8-aligned address fails the link (ee-gcc pads it): merge with the name before.
  **`python3 -I tools/host/walkcheck.py`** (session 86, no build needed): pointer walks that run on from one loop
  into the next, which neither check sees, and since session 87 index walks and builder results (0 WALK, 42 REVIEWED); census.py's HOST_TAIL pads a piece on the host only.
  **`python3 -I tools/host/countcheck.py`** (session 88, no build needed): counts kept in a global, stepped in one
  function and used as an index in another (0 COUNT, 37 REVIEWED; the DATA rows wait for high-water marks).
- **Null platform**: PlatMcSync answers done with "no card" (-10) and PlatMcGetInfo writes its outputs;
  **host/null/pad.c** (session 87): one pad connected, nothing pressed (`KH1_HOST_PAD=none`: no pad,
  `KH1_HOST_PAD=FILE`: a script; vita-port-plan 5.1aa). PlatSifCallRpc hands the sound
  RPCs to **host/null/sound.c** (session 86): RPC 0x30 answers 1; RPC 0 keeps the status block's address; a
  frame after a queue (RPC 30) the bank transfers it held (commands 3, 4, 0xB, 0x28) come off the +0x1F00
  count (D_0063F540: boot waits for it non-zero, the sound tasks / summons / soft reset for 0); SE and
  stream `used` entries are set on a play and cleared on a stop, after a fade or by time (sound-spec 5);
  the disc-error word and the message buffer read 0. `KH1_HOST_SND=trace` prints the commands,
  `tools/host/sndlog.py RUN.txt` sums them up.
  **DMAC interrupts** (session 68): the null platform keeps PlatAddDmacHandler's handlers, a status bit per
  channel (set by PlatDmaSend / PlatDmaPutVif1Chcr with STR, cleared by PlatDmaPutStat) and the enable mask, and
  runs an enabled channel's handlers outside any handler: mdlgs.c's GS task list ends (D_00559DB4) and
  func_0015ef60's frame-end wait returns.
  **Threads** (session 67, host/null/threads.c): the game's threads run as ucontext coroutines (a thread runs
  from the main thread's PlatWaitSema until it waits; semaphores count; PlatIReferSemaStatus reports the
  waiters). This runs src/util/thread.c's loader worker: every func_001204a0 file load reads on it (before,
  a load's result stayed -1 for ever).
- **Host build (phase 5)**: `make host-census` links out/host/kh1-host (all 512 game files + the 8 drafts).
  `KH1_HOST_ISO=PATH out/host/kh1-host` reads the user's own disc image by sector (host/port/cd_image.c;
  `KH1_HOST_TRACE=1` prints the searches and reads, `=4` (session 77) each send's GS state values for `tools/host/gsstate.py`, `=5` (session 79) also each send's draw states from host/null/gsregs.c (`gsstate.py --draws`), uploads (`--uploads`, session 80) and render targets (`--targets`, session 81; Z formats decode since session 82; `tools/host/drawkeys.py` lists the draw list's keys, `tools/host/sendorder.py` the sending tasks; session 83: the list nodes, `gsstate.py --nodes`; session 84: `KH1_HOST_DMAC=defer` leaves the draw list to the replay), `=2` also walks each DMA chain and reads its data as GIF packets / VIF codes / PATH2, with each send's GS registers (sessions 74-76, host/null/dmawalk.c; `tools/host/dmawalk.py` is the offline twin for the static chains), `KH1_HOST_FRAMES=N` caps the run, default 600). On
  tests/host/fake_disc.py's image (now with a one-sector "dktitle.x" in KINGDOM.IDX) the boot reads SYSTEM.CNF,
  KINGDOM.IDX and dktitle.x (frame 2, on the loader thread) and calls D_00F20000(0, 0), which faults:
  main.c prints "fault at PS2 0x00f20000 in the memory map" and the caller. **`KH1_HOST_OVL=stub`** (session
  68, a test switch in host/null/main.c) answers the entry with 0 instead (the main loop then stays in the
  title's state 1); **`KH1_HOST_OVL=stub:2`** also asks for state 2 with func_00109558 (a guess at the title's
  "new game"), and the boot then loads dh.wdt, amusic/sedh.dat, dh00_01.bin, dh00_01.img, dh01.ard (Dive to the
  Heart) and, on the fake disc where those files are missing, ends in func_00132790 (roomobj.nostrict.c) on
  data that is not there (reached from func_001136a8 through the sound and file queue; under gdb, `handle SIGSEGV
  nostop pass` skips the stub's own fault). The stub does not work under valgrind (valgrind runs the overlay's bytes). **Valgrind: 0 errors** up to the
  fault (session 73 again; `apt-get install valgrind libc6-dbg:i386`; under valgrind the fault is a SIGILL). **Not yet run on the
  real ISO** (it is on the Mac): it should stop at the same call. opdma.c's three GS tag lists are one
  definition (D_0061EEA0[0x140]); session 68 made the notice's four sprite sets one (src/hud/notice.nostrict.c
  `D_00656230_sets[4][9]`): func_00243a90's fill ran over D_006561D0 on the host. Sessions 69 and 70 found the rest statically
  (layoutcheck, relcheck: 27 more objects one definition); the stub:2 run still ends in func_00132790 on the fake disc.
- **dktitle.x**: tools/ovl/inventory.py is ready (functions, main-ELF calls and data, code / data split;
  `--selftest` on the main ELF finds every layout.tsv start). Not run: the file is on the Mac. §5.2 has the plan
  to decompile it (toolchain check on 5-8 leaves first).
- **Original source names** (docs/elf-notes.md): ttlib/ui_gauge.c, ttlib/ui.c, src/decode.c, src/sa_task.c, with
  their ranges; none below 0x001c08e8 so far.
- **Helpers:** `python3 -I tools/shift/s50move/group.py src/DIR/NAME LO HI` drafts modules per flag mode,
  `tools/shift/s37move/fcheck.sh base|NAME` (compare float_covered.txt as a sorted set; run `base` on a clean tree
  before any edit, and never run `make` while it builds; a syms line naming a func_ alias that went away is
  expected after a rename), `tools/shift/cover_check.py | grep NAME`, `tools/checkfile.py FILE -v`,
  `tools/shift/s31types/s31_warndiff.py FILES` (compares with HEAD: commit-free check). Data definitions: compare
  `cut -f2 out/gen/data.tsv | sort` with the session's base (saved before the first edit). reach_check alone (40 s,
  no build): `python3 -I tools/shift/reach_check.py --elf SLPS_251.98 --overlays EMPTYDIR --out F.txt` (after a
  `make shift`; the anchors come from out/shift/kh1-shift.linked.elf). Host: `make host-census` (or
  `python3 -I tools/host/census.py --exe`), then `out/host/kh1-host` (gdb works: objects have -g; `gdb -batch -ex
  "break kh1_host_vblank if frames >= N" -ex run -ex bt out/host/kh1-host` shows where frame N is); `--files
  CAUSE` / `--show FILE`; out/host/undefined.txt. `python3 -I tools/host/argcheck.py --tsv out/host/argcheck.tsv`
  lists the passthrough calls, `python3 -I tools/host/abicheck.py` the argument-class mismatches. `python3 -I tools/host/vu2c.py FILE LINE` turns one VU0 asm statement into PlatVu0
  calls. `python3 -I tools/host/walkcheck.py` lists pointer walks across loops, `tools/host/countcheck.py` counts across functions, `python3 -I tools/host/viewcheck.py [--wide 960:544]` checks host/port/view.c's camera matrices against the ELF's func_00110618 (needs the ELF and gcc -m32), `python3 -I tools/host/sndlog.py
  RUN.txt` a run's sound commands (with `KH1_HOST_SND=trace`). A quick "did any object change" check: `find out/build -name '*.o' | sort | xargs sha1sum` before the
  first edit and after (sessions 62 to 66 did this), or build origin/main in a `git worktree`
  (symlink tools/toolchain, copy the ELF) and `cmp` every out/build .o.
  **`git fetch origin main` first**: the container's origin/main can be stale. A fresh container needs `apt-get
  install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu gcc-multilib gdb` (indcheck needs clang, present in the cloud image) (after `dpkg --add-architecture
  i386`), `make toolchain`, the ELF, a plain `make shift` and tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 92 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s92 and /mnt/project-files/kh1-runtime/s92, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities (session 70
   merged its counts), customize, status, config and journal pages with each journal section, changing a config
   option, using an item, equipping a weapon, a save point (save to a card, overwrite a save, change the party:
   **session 87: after the save point's party choice, does a member appear who was not chosen?**
   savemenu.c `func_00228588`), loading a save from the title screen, a new game's name entry if one is reachable,
   buying and selling in an item shop and a Gummi shop, the Gummi garage (session 87 read its lists), the Moogle's
   synthesis, a list that pages (session 70 merged the list callback), the title screen left idle until its demo,
   a battle with the HUD (the HP / MP gauges, the command menu including its second kind-4 menu (session 70:
   D_00650120[6]), lock-on and the target's gauge, damage numbers, an "obtained" notice), the world map's gauge, a
   minigame with a timer or score if one is near, a level-up, a Trinity mark if one is near, a summon if one is
   available, enemy drops picked up, the pause, a game over and its continue, a room change and a world change, a
   movie, music and sound effects throughout (session 86 moved the sound status block's message buffer), a
   controller pulled out for a second (the system-message band, renderer-spec 4.15), a scene with the screen
   spin if one is near (renderer-spec 4.16: the picture turning into itself), **session 88's effects** (renderer-spec
   4.17: the blur when the menu opens and closes, an event's letterbox bars and fades to black and white, a room that
   sways (underwater is a guess) and whether anything drawn after it looks wrong (the Z buffer holds colour then),
   a depth blur or lens bulge if one is near), **the controls of 5.1ab's table** (SELECT's first person, L2 / R2
   camera and target cycling while locked on, L1 shortcuts, R3), **session 91: nothing new to see on the PS2 (the float ELF is the same)**, **session 90: an object window whose speaker is off screen (objwin's tail `f6`), a movie (opening or the title's demo: skip it with a button and with START), the party gauges' place (the data say top right)**, **session 89: a pad that vibrates when the player is hit** (PCSX2's force feedback, if the user's pad has it; renderer-spec 5.3 needs nothing from the boot), and anything using atan: camera, lock-on). If it breaks, bisect: session 86's commit first (revert its data_0063.s / bss_0063.c change), then
   session 70's (revert it), then session 69's (the one-definition merges), then session 59's `--no-fmt-read`, then
   session 34's switches. Move what boots into docs/shiftable-plan.md and clear docs/float-untested.md. Note what
   the boot shows about the "(a guess)" modules and rename the ones it settles. Without the Mac: skip.
2. **Host run on the real disc (with the Mac)**: ask once for the user's ISO (Downloads; the unpatched original,
   not KH1_BIG.iso) to be copied into the container's scratchpad (never into the repo or project files), and run:
   `KH1_HOST_ISO=... KH1_HOST_TRACE=1 out/host/kh1-host`, once under valgrind, `KH1_HOST_TRACE=2` (every DMA chain
   walked: a chain leaving host memory or ending inside a packet is a bug; record the windows' per-draw packets),
   `KH1_HOST_TRACE=5` with `gsstate.py RUN.txt --sends --draws --uploads --targets --nodes` (compare with
   renderer-spec 3.2 / 4.7-4.16 and 5.1; every node in drawkeys.py's map; the targets `0x1A00`, Z24 `0x0E00`, the
   display buffer, `0x3A00`), `KH1_HOST_TEXDUMP=DIR` (look at the decoded message font: readable glyphs settle
   gsmem.c's swizzle and 4.9's 2-bits-a-layer inference), then **`KH1_HOST_OVL=stub:2`** (Dive to the Heart's
   files are on the real disc: record how far the room parse func_00132790 gets), and the `KH1_HOST_TRACE=5` room
   run once more with `KH1_HOST_DMAC=defer` (same `--nodes` order expected; pending only at frame-end waits; the
   texture steps' dir-2 copies in `--uploads`; key 50000's P3 upload and chain 3, `D_0047E220` / `D_00482260`,
   with its tags in map section 1). Run each with `KH1_HOST_SND=trace` and `python3 -I tools/host/sndlog.py
   RUN.txt` (the boot's bank transfers, the title / Dive to the Heart music starts, SEs played and ended, no
   frame near 256 records; the transfer count back to 0). **Session 87: the pad is connected by default now**;
   compare one run with `KH1_HOST_PAD=none` (it should sit in the "no controller" band from frame 32), and once
   the room run gets further, try a `KH1_HOST_PAD` script (START at the title, CIRCLE, the menu with
   TRIANGLE?; session 88: start from tests/host/pads/title.txt and move its frames to what the run shows). Read the
   message files' code 11 digit counts (`dig[12]`, 5.1aa). **Session 89: find the message font's button glyph codes** (circle, cross, triangle, square, L1 / R1 ... in the decoded font and the message files) **and the disc's HUD / menu textures that show a button** (`KH1_HOST_TEXDUMP`), for 5.1ac's swap lists; record the HUD draws' rectangles for renderer-spec 5.3.1's anchor table (**`gsstate.py RUN.txt --extents`**, session 91: one row per HUD part keyed `ENV > D_00351E10`; check each row of 5.3.1, the kind-3 gauge, the one-shot and the minigame timer's x / y). **Session 91: run the room once with `KH1_HOST_WIDE=1`** (the culls let more through: compare the draw-list node counts with and without it), and **list the actors with spawn flag `0x20000`** (renderer-spec 5.4 "Bit 35's readers": gdb after `func_00132c70`, each of roomobj.c's four lists' 0x78-byte records with `flags & 0x20000`) and scan the room's object scripts for the halfword `0xA30B` (`func_0012a030`). **Session 88: record the high-water marks of countcheck's
   DATA rows** (gdb watchpoints or a host-only hook: renderer B's `D_0055C698.x4 / .x8 / .xc` against 78 / 480 / 72,
   the collision count `D_002C12C4` against 2048, the message count `D_00389C80` against 273, the trigger boxes). Fix host-only causes the way
   sessions 63 to 70 did (platform answers, layout dependencies as one definition with layoutcheck, relcheck and
   walkcheck at 0, the PS2 ELF byte-identical).
3. **dktitle.x (with the Mac)**: copy Downloads/kh1-test/ovl/dktitle.x into the container (never commit it), run
   `python3 -I tools/ovl/inventory.py dktitle.x --tsv out/ovl/dktitle.layout.tsv`, record the counts (not the bytes)
   in §5.2, then the toolchain check of §5.2 step 2 on 5-8 small leaf functions. Check argcheck's 3 value uses and
   func_002066b0's BENIGN entry against dktitle.x's calls into the main ELF, and indcheck's OVERLAY rows
   (does dktitle.x call the setters func_001c06c0 / func_001468f8 / func_0012cab8 or write vm_lib's hooks? what do
   the targets take?). Does it call func_00109558, and with which states (session 68 guessed 2 = new game)? Does it
   call drawlist's flushes (func_00237f20 / func_002380c0 / func_00238258) or the push func_002376c8, gspkt.c's
   func_002372e0 / func_00237318, and which of the 16 sound entry points with no main-ELF caller (sound-spec 3)?
   Does dkmovie.x (the same folder) store 2 to `D_002BBE04` (the movie copy from `0x118000`, renderer-spec 4.15),
   and does any overlay read the field parity `D_002BBDE8`? Session 87: does any overlay call func_001fb3e0 /
   func_001fbb50 (wintext's number draws with no main-ELF caller) and with which digit counts, or store 1 / 4 to
   `D_002BBE04` (the screen spin)? Session 88: who calls padrec.c's recorder / replay / button script / idle timer
   (`func_00233650` ... `func_002336e8`: the title's demo?), memstack.c's push / pop (`func_001bb480` /
   `func_001bb4b0`, depth 4), pause.c's `func_00114068` (the 2 px menu blur), and does anything read the pad's
   second repeat word (+0x14) or `D_002C5C2C`? Session 89: does any overlay start a vibration (`func_00176ba8`, `func_00147790` with patterns 2-4), set bit 16 of `D_002C5978` (vibration off), or call winmenu.c's y getter / setter `func_001fd268` / `func_001fd278` (0x7000, not 0x7400)? **Session 90: dkmovie.x** (the same folder): run inventory.py on it too and check vita-port-plan 5.1ad's "To confirm" list (commands 0-9 and their returns, its stores of 2 to `D_002BBE04` and to `D_002BBE18`, whether n indexes `D_0046A058`, how a title skip is seen, whether it calls `func_001111b0`, sceIpu / sound commands used); does any overlay build its own frustum (5.4 open; session 91: does the Gummi / world map code call `func_00110a48` or `func_001bb858`, and with which matrices)? Without the Mac: skip.
4. **Static, without the Mac**: (a) **the HUD anchor table as port data** (renderer-spec 5.3 step 2,
   5.3.1): a host-only table keyed by the drawing environment (`D_00651C00` gauges, `D_00655F80` notice, ...,
   gsstate.py's keys) giving each part's side, applied under `KH1_HOST_WIDE` as an x shift of the part's
   vertices in the GIF path (host/null/gsregs.c is the place to try it: shift XYZ when the send's environment
   is in the table; the PS2 build untouched), with a gsregs_test check; (b) **the full-screen passes under
   `KH1_HOST_WIDE`**: list each one's 512-wide constants (the clear's 16 sprites, the fades, flash, letterbox,
   blur, sway, lens grid `D_004949F0`, spin, the frame copy's 16 strips) and route the ones in C through
   include/platform/view.h the way objwin's are (literals on the PS2, objects bit-identical); (c) put
   `viewcheck.py` in tests/selftest.sh when the ELF is there (skip without it); (d) `KH1_HOST_DMAC=defer` as
   the default and argcheck's 3 value uses still wait for the Mac.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=92`, refresh the per-phase table in docs/progress.md (between its
   `<!-- phases -->` markers; the generator keeps it), commit, open a PR, and refresh this prompt (keep the
   Mac note accurate).
7. **Once the PR is merged, message the coordinator to start the next session** (session 93) with this
   prompt: the user wants each session to start the next one without being asked.
