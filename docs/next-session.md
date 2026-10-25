# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is back from Monday 2026-10-26** (the user said on 2026-10-23 it was away until then; sessions 49 to 76
ran without it; sessions 77 to 85 ran on Sunday 2026-10-25, still without it). **Ask for the Mac and PCSX2 at the start** (the connect card in the Claude desktop app) **and make
item 1 the first thing**: eight float builds are waiting for a boot. Items 2 and 3 also need the Mac: the user's ISO
is in Downloads for the host run, and the overlay files are in Downloads/kh1-test/ovl. If the user says the Mac is
still away, skip items 1 to 3, add every float change to docs/float-untested.md as untested, and do the static
items.

## Where we stopped (end of session 85, 2026-10-25)

- **Session 85** (static, vita-port-plan 5.1y, renderer-spec 4.14, new docs/sound-spec.md): **the sound
  driver's commands as the Vita audio layer's interface, renderer A's grid chains.** docs/sound-spec.md
  lists snd_rpc.c's transport (RPC 0 bind with mode 0 boot / 1 soft reset / 2 room load; direct calls answer
  in word 0; 8-word records queued and sent as RPC 30 once a frame), the status block (SE voices +0, streams
  +0x1800, **disc error +0x1C08**, transfer count +0x1F00) and every command with its arguments, senders and
  meaning (transfers `0x26` / 3 / 4 / `0xB` / `0x28`, music `0xC` / `0xD` / `0xE` / `0x2F` / `0x30`, SEs 5 /
  8 / 6 / 7 / 2, voices `0x12` / `0x13` / `0x14`, object SEs `0x29`-`0x2B`, settings `0xF` / `0x23` /
  `0x24` / `0x27`). Findings: **RPC 30 sends only the first 256 of the queue's 1024 records**;
  `func_0011d2d0` searches the static SE table, not the live pointer (a 128-slot room's ppp SE switch finds
  nothing); **`func_001ecb08`'s wildcard loops fall through and read up to 0x114 bytes past the status
  block** (into `D_0063F640` on the PS2; on the host whatever follows: no layout check sees pointer
  walks); 16 entry points have no main-ELF caller (for the dktitle.x check). **renderer-spec 4.14**:
  `func_00107d30` case 3 = each visible cell's second mesh (map section 1 entry `i + 1`'s `{w8, w12}` tag,
  `func_00107c48`), P3 at key 50000 after the opaque pass, no Z writes, the static FGE fan template
  `D_004862B0`; cases 0 / 1 the first meshes at 10020; the fade groups reuse chain 3's head (open question
  6.8 answered from the C). Item 4c (defer as default) waits for the real-disc room run. Only docs/ and
  README.md changed: kh1.elf byte-identical, the float ELF the same (no float-untested row).

- **Session 84** (static, vita-port-plan 5.1x, renderer-spec 4.12, 4.13): **the replay on the host, the
  menu's "race" settled, renderer B's depth key, the texture steps.** **`KH1_HOST_DMAC=defer`** (null
  platform): transfer ends and PlatEnableDmac no longer run the DMAC handlers, so the draw list stays
  pending until `kh1_gs_flush_pending` or the new **`PlatGsListWait()`** (include/platform/gs.h, the body of
  mdlgs.c `func_0015ef60`'s spin, nothing on the PS2) replays it. Fake disc stub:2: `gsstate.py --nodes` the
  same with and without it; 0 sends and 3 frame-end waits found the list pending. **The in-game menu cannot
  race the list**: task 150000 (`0x249F0`, `func_0011eda8` -> `func_0015ef60`, same task list) waits for
  `D_00559DB4` = 0 before the menu's `0x270FF`; sendorder.py finds that wait from the C ("drained at
  0x249f0"): **0 RACE** (was 3). **Renderer B's depth key settled**: `D_002E26C0` = view-screen
  (`func_00110618`'s first output, w row (0, 0, 1, 0)) x camera matrix, so the root matrix's `[3][3]` is the
  model origin's camera-space z (shadow models share the ranks). **The first texture animation kind**
  (`func_00101bb8`, keys 10000 + n): GS-to-GS copies (TRXDIR 2): kind 0 a flipbook from a sheet in GS memory,
  kinds 1 / 2 a vertical scroll by two copies (0 rows at frame 0: a one-step hitch at each wrap); the 160-byte
  record layout in renderer-spec 4.13; `D_004945F0` (n) is never reset, so after ten steps the nodes sort
  after 10010 and, after about 30,000 steps, after the room's opaque draws. gsmem_test 65 -> 67. Valgrind 0
  errors. src/ changed only by the one hook: **every out/build object bit-identical**, the float ELF the same
  (no float-untested row).

- **Session 83** (static, vita-port-plan 5.1w, renderer-spec 4.12, 4.13, 5.2): **the draw list as commands,
  renderer B's keys, the CLUT animations.** include/platform/gs.h's new **`PlatGsListNode(list, node)` /
  `PlatGsListEnd(list)`** (nothing on the PS2) are called by mdlgs.nostrict.c's walks around each node's
  callback; the null platform prints `kh1-host: node draw|imm KEY cb CB arg PAYLOAD` / `node main` / `list
  ... end` / `vblank N` at `KH1_HOST_TRACE=5`, and **`gsstate.py --nodes [--frame N]`** prints a frame's
  command order and checks each node against drawkeys.py (fake disc stub:2: 13 nodes, 6 distinct, all in
  the map). `kh1_gs_flush_pending` (plat_null.c) counts main-thread GS calls that find the draw list
  pending (0: the null DMAC drains it). **Renderer B's keys** from the C: objects 20000 (opaque) / 70000
  (alpha < 0x80 and translucent parts) + depth rank 0-77 far first, shadows 60000 + 10 n, menu models on
  the immediate list at 0. **The texture animations (90000 + 10 id) are CLUT cross-fades**: palette frames
  to `0x3600` / `0x3A00`, then two point-sampled sprites over the room CLUT at block `0x3E00 + v` (FBMSK
  keeps its alphas); room draws see it a frame later. host/null/gsmem.c's **`kh1_gsmem_sprite`** draws such
  sprites into the model (gsmem_test 61 -> 65). renderer-spec 3.1 has the room CLUTs (`0x3E00 + i`) and
  background textures (`0x2600 + 256 i`). Valgrind 0 errors. src/ changed only by the two hooks:
  **every out/build object bit-identical**, the float ELF the same (no float-untested row).

- **Session 82** (static, vita-port-plan 5.1v, renderer-spec 4.12, 5.2): **the Z formats in GS memory.**
  host/null/gsmem.c has PSMZ32 / Z24 / Z16 / Z16S (the colour twin with the final block number XOR `0x18`, as
  PCSX2) and PSMCT16S (block order y0 x0 y2 y1 x1); inside a page a Z32 / Z24 pixel (x, y) is CT32's (x ^ 32,
  y ^ 16), Z16's (x ^ 32, y ^ 32): **a CT24 read of the Z24 buffer (the capture `D_002B66B0`) sees each page's
  quarters swapped**. Z uploads / reads / textures decode, CT16S CLUTs load, a Z target's pages are marked
  through the same address function; checked against PCSX2's tables on 30 M addresses outside the repo;
  gsmem_test 52 -> 61 checks. **`tools/host/drawkeys.py`** (new): every draw / immediate list insert by key,
  wrappers followed to literal keys (38 rows; table in renderer-spec 4.12): texanim 10000+n, state packets
  10010 / 10020 / 50000 / 50100, renderer B resets 20499 / 70499, room / objects 40000 (opaque) and 50010
  (translucent), shadow state 45499 / 60499, shadows 60000+n, texanim passes 90000+10id+0..6; renderer B's
  `e->x28` (priority +- depth order, clamped to [prio-500, prio+499], the 59500-60499 band kept) the only
  data-driven keys. **sendorder.py** read 4 more registrations (`(s32) &func_X` casts; 168, all literal keys,
  `--all` lists unreadable calls: none); still only the in-game menu sends unsynced. vita-port-plan 5.1v
  writes the port's rule: a main-thread send (PlatGsSyncPath, ch 1 / 2 PlatDmaSend, PlatGsPutDrawEnv) first
  replays any pending list (`kh1_gs_flush_pending()`). Valgrind 0 errors. Only host/, tests/, tools/host and
  docs/ changed: **every out/build object bit-identical**, the float ELF the same (no float-untested row).

- **Session 81** (static, vita-port-plan 5.1u, renderer-spec 4.12, 5.1, 5.2): **render targets in the GS memory
  model.** Each drawing kick tells host/null/gsmem.c its context's FRAME / ZBUF (`kh1_gsmem_draw`; Z only with ZTE 1
  and ZMSK 0, FRAME unless FBMSK masks all), each VU1 program start on VIF1 marks context 2's (`kh1_gs_path1`,
  renderer A, inferred); per page the word bits a draw changed (Z24 the low 24: **the message font in Z's top byte
  stays a texture**), cleared by uploads. `kh1_gsmem_tex_target` / `KH1GsDraw.target`: a texture in drawn bits is
  "target N", not decoded (`, reads target N` on the draw line, `target` lines at `KH1_HOST_TRACE=5`,
  **`gsstate.py --targets`**, the texture dump skips them). Fake disc stub:2: targets 1 the 3D target `0x1A00`
  (384 rows), 2 Z24 `0x0E00`, 3 the display CT24 at 0; the frame copy `D_002A6890` reads 1, the capture
  `D_002B66B0` reads 2. **PATH1 vs PATH3 settled** (renderer-spec 4.12): `func_0015ea98` waits for
  `sceGsSyncPath(1, 0)` (ch 1 / ch 2 / VIF1 / VU1 / GIF idle) before every draw-list node, so the order is the
  list's, node by node; the immediate list (`0x27CB8`) and `func_00106b18` wait for it to drain. **`tools/host/
  sendorder.py`** (new) lists the sending tasks by key: only the in-game menu `func_0020d2f8` (`0x270FF`) sends
  before syncing (window-font uploads, window headers). REGLIST PRIM and ADC strip restarts: gsregs_test cases
  added, gsregs.c already right. Valgrind 0 errors. Only host/, tests/, tools/host and docs/ changed: **every
  out/build object bit-identical**, the float ELF the same (no float-untested row).

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-85.
- **Eight default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032), 34
  (2,049, unchanged in 35 to 58), 59 (2,053, unchanged in 60 to 68), 69 (2,043) and **70 (2,041, the current
  default; sessions 71 to 85 left the float ELF's bytes the same)**. Session 69 made 21 objects one definition (vita-port-plan 5.1i): 10 objects that floated in place as
  parts of a run now float whole into the float area (the shop / list windows D_0062F6E0 / D_0062F790 / D_00630460,
  the ppp matrices D_00615E70 / D_00616000, D_0052EB50, D_00551700, D_00575900, the timer sets D_006692F0 /
  D_00669320) and 20 neighbours are pinned. Session 70 made 6 more one definition (5.1j: the command menus
  D_00650120[7], the object slots D_00550400[64], the DMA packet area D_00573AC0, the hit records D_0054C440 with
  areabox's groups, the list callback D_006305C0, the ability counts D_00642C70): only 2 newly pinned (D_00642C70,
  D_00650DD0), nothing newly floats. The undo of each is reverting that session's commit (float-untested.md rows 69,
  70). docs/float-untested.md lists every change since the last booted build (KH1_F29_N) and the switch that undoes
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
- **Null platform**: PlatMcSync answers done with "no card" (-10) and PlatMcGetInfo writes its outputs;
  PlatPadRead leaves no button pressed, PlatPadGetButtonProfile answers -1. PlatSifCallRpc answers RPC 0x30
  with 1 (session 66), and (session 67) keeps the sound status block's address from RPC 0 and, a frame after
  a queue (RPC 30), takes the bank transfers it held (commands 3, 4, 0xB) off the block's +0x1F00 count
  (D_0063F540): boot waits for it non-zero, the sound tasks / summons / soft reset for 0; unanswered it stayed
  2. The other status words read 0, which every reader takes as "nothing playing" / "no disc error".
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
  calls. A quick "did any object change" check: `find out/build -name '*.o' | sort | xargs sha1sum` before the
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

## Session 86 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s85 and /mnt/project-files/kh1-runtime/s85, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities (session 70
   merged its counts), customize, status, config and journal pages with each journal section, changing a config
   option, using an item, equipping a weapon, a save point (save to a card, overwrite a save, change the party),
   loading a save from the title screen, a new game's name entry if one is reachable, buying and selling in an item
   shop and a Gummi shop, the Moogle's synthesis, a list that pages (session 70 merged the list callback), the title
   screen left idle until its demo, a battle with the HUD (the HP / MP gauges, the command menu including its
   second kind-4 menu (session 70: D_00650120[6]), lock-on and the target's gauge, damage numbers, an "obtained"
   notice), the world map's gauge, a minigame with a timer or score if one is near, a level-up, a Trinity mark if one
   is near, a summon if one is available, enemy drops picked up, the pause, a game over and its continue, a room
   change and a world change, a movie, and anything using atan: camera, lock-on). If it breaks, bisect: session
   70's commit first (revert it), then session 69's (the one-definition merges), then session 59's `--no-fmt-read`,
   then session 34's switches. Move what boots into docs/shiftable-plan.md and clear docs/float-untested.md. Note
   what the boot shows about the "(a guess)" modules and rename the ones it settles. Without the Mac: skip.
2. **Host run on the real disc (with the Mac)**: ask once for the user's ISO (Downloads; the unpatched original,
   not KH1_BIG.iso) to be copied into the container's scratchpad (never into the repo or project files), run
   `KH1_HOST_ISO=... KH1_HOST_TRACE=1 out/host/kh1-host` (and once under valgrind; `KH1_HOST_TRACE=2` shows the
   DMA chains and reads their data, a chain leaving host memory or ending inside a GIF packet / VIF code / PATH2 packet is a bug to fix; each line ends with the GS registers the send writes, renderer-spec 4.6: the window headers are now in the static walk (session 78's seeds): record the windows' per-draw packets (func_00122048's scratch buffers, read from the C in renderer-spec 4.9) and anything the seeds got wrong; and once with `KH1_HOST_TRACE=5`, then `python3 -I tools/host/gsstate.py RUN.txt --sends --draws`: compare the run-time state list with renderer-spec 3.2 / 4.7 / 4.8 / 4.9 and 5.1's register table, and add what is new; check 4.9's reading of the C against the windows' draw states: glyph TEX2s with PSMT4HH / CSA 1, the windows' SCISSOR_1, the bevel's ALPHA change inside a strip, renderer B's two passes; session 80: also `--uploads`, session 81: `--targets` (session 82: Z24 reads now decode with the Z block order; the capture `D_002B66B0`'s CT24 read of the Z area shows the quarter swap) (the targets the run draws into: expect the 3D target `0x1A00`, Z24 `0x0E00`, the display buffer, the shadow / texspot buffer `0x3A00`; list every draw state that `reads target N` and check it against renderer-spec 3.1's memory map and 3.4), and a run with `KH1_HOST_TEXDUMP=DIR` into the scratchpad:
   **look at the decoded message font** (tex_*1000* with PSMT4HL / HH, CSA 0 / 1): readable glyphs confirm
   gsmem.c's swizzle and CLUT buffer on real data and settle 4.9's 2-bits-a-layer inference; check the boot
   environment line (`D_004D8EF0`) and renderer-spec 4.10 / 4.11 against the run): expected, as on the fake disc,
   SYSTEM.CNF, KINGDOM.IDX and the eight files before dktitle.x, then the fault at D_00F20000(0, 0). Then
   **`KH1_HOST_OVL=stub:2`** on the real disc: the Dive to the Heart files (dh.wdt ... dh01.ard) are there, so the
   room parse (func_00132790) gets real data; record in vita-port-plan how far it gets and where it stops. Session 83: in the `KH1_HOST_TRACE=5`
   runs also run **`gsstate.py RUN.txt --nodes`** (and `--frame N` on a frame inside the room): every node
   should be in drawkeys.py's map (explain or fix any NOT IN THE KEY MAP row); check renderer B's keys
   (objects 20000-20077 / 70000-70077, renderer-spec 4.12) and, if the room has texture animations, their
   seven nodes at 90000 + 10 id (4.13: the +2 / +5 nodes' sprite kicks, now drawn into gsmem.c's pixels;
   `KH1GsMemStats.sprites` under gdb), and in `KH1_HOST_TEXDUMP`
   the room textures whose CBP is `0x3E00 + v` changing colour from frame to frame. Session 84: run the
   `KH1_HOST_TRACE=5` room run once more with **`KH1_HOST_DMAC=defer`** and compare `--nodes` (same order
   expected; the summary's pending count should be all frame-end waits, no sends); if the room has texture
   steps (nodes at 10000 + n, `func_001019c8`), check their copies in the `--uploads` list (dir 2, local ->
   local; renderer-spec 4.13 "The texture steps"). Session 85: in the room's `--nodes`, key 50000 should hold
   the P3 upload and chain 3 (`func_00106db0`, renderer-spec 4.14) when the room has second-layer cells;
   with `KH1_HOST_TRACE=2` walk chain 3 (`D_0047E220` / `D_00482260`) and check its tags land in map
   section 1. Fix
   host-only causes the way sessions 63 to 70 did (platform answers, layout dependencies as one definition with
   layoutcheck and relcheck at 0, the PS2 ELF byte-identical).
3. **dktitle.x (with the Mac)**: copy Downloads/kh1-test/ovl/dktitle.x into the container (never commit it), run
   `python3 -I tools/ovl/inventory.py dktitle.x --tsv out/ovl/dktitle.layout.tsv`, record the counts (not the bytes)
   in §5.2, then the toolchain check of §5.2 step 2 on 5-8 small leaf functions. Check argcheck's 3 value uses and
   func_002066b0's BENIGN entry against dktitle.x's calls into the main ELF, and indcheck's OVERLAY rows
   (does dktitle.x call the setters func_001c06c0 / func_001468f8 / func_0012cab8 or write vm_lib's hooks? what do
   the targets take?). Does it call func_00109558, and with which states (session 68 guessed 2 = new game)? Does it call drawlist's
   flushes (func_00237f20 / func_002380c0 / func_00238258) or the push func_002376c8 (session 75: nothing in the
   main ELF does; they are what sets TTE on the GIF channel, renderer-spec 4.5)? Does it call func_002372e0 / func_00237318
   (gspkt.c's default and 3D environments, session 77: no caller in the main ELF)? Session 85: which of the
   16 sound entry points with no main-ELF caller (docs/sound-spec.md 3) does it call, and with what?
   Without the Mac: skip.
4. **Static, without the Mac**: (a) **The status block read past its end** (sound-spec 3, `func_001ecb08`):
   on the host make the 0x120 bytes after `D_0063D640` the same as on the PS2 (the message buffer
   `D_0063F640` right after it: one host definition or an alias in census.py, the way sessions 69 / 70 did
   layout dependencies), and look for other pointer walks that run past an array (a loop whose pointer
   survives into a second loop, as here): none of layoutcheck / relcheck follows them. Keep kh1.elf
   byte-identical; a float-untested row only if the float ELF changes. (b) **A null mixer on the host**:
   plat_null.c decodes the RPC 30 records (sound-spec 3) into `kh1-host: snd CMD ...` lines at
   `KH1_HOST_TRACE=6` (or a new switch) and keeps the status block's SE / stream `used` entries (set on a
   play, cleared on a stop or after a fixed time), so objse's slots and `func_0011e248` see sounds end as on
   the console; a small tools/host script that summarises a run's commands. This is the Vita audio layer's
   EE half without the audio. (c) renderer-spec open questions 9 (frame pacing: `func_0010fea0`'s
   constants, the 30 / 60 fps switch `D_002BBDEC`, where the main loop waits for the vertical blank) and 10
   (the `0x118000` display area and `func_0010f5f8`'s PMODE / DISPFB1 set-up: which screens use them), from
   the C. (d) `KH1_HOST_DMAC=defer` as the default and argcheck's 3 value uses still wait for the Mac.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=86`, refresh the per-phase table in docs/progress.md (between its
   `<!-- phases -->` markers; the generator keeps it), commit, open a PR, and refresh this prompt (keep the
   Mac note accurate).
7. **Once the PR is merged, message the coordinator to start the next session** (session 87) with this
   prompt: the user wants each session to start the next one without being asked.
