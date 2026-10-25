# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is back from Monday 2026-10-26** (the user said on 2026-10-23 it was away until then; sessions 49 to 75
ran without it). **Ask for the Mac and PCSX2 at the start** (the connect card in the Claude desktop app) **and make
item 1 the first thing**: eight float builds are waiting for a boot. Items 2 and 3 also need the Mac: the user's ISO
is in Downloads for the host run, and the overlay files are in Downloads/kh1-test/ovl. If the user says the Mac is
still away, skip items 1 to 3, add every float change to docs/float-untested.md as untested, and do the static
items.

## Where we stopped (end of session 75, 2026-10-25)

- **Session 75** (static, vita-port-plan 5.1o, renderer-spec 4.5): **the GIF tags' upper 64 bits are 0** (the
  builders clear the qword first: func_00237018, drawlist), except func_0011fbb0's image uploads on the caller's
  stack (text.c), where they are stack garbage. **Nothing in the main ELF calls drawlist's flushes**
  (func_00237f20 / func_002380c0 / func_00238258, nor the push func_002376c8: 0 jal, 0 pointer words), so the
  main ELF alone never sets TTE on the GIF channel (every GIF send: CHCR 0 or 4); if an overlay does, the tag
  can not reach the GIF (as a GIFtag it would swallow 16 x qwc qwords), so **the GIF parser drops every tag on
  channel 2** (inference). **The chain walk moved to host/null/dmawalk.c and now reads each send's data as its
  receiver would** (one stream of GIF packets on channel 2, VIF codes on VIF0 / VIF1 with TTE's upper words
  first): a send ending inside a packet or a code's data, or a word that is no VIF code, is a problem.
  tests/host/dmawalk_test.c (14 made-up chains) runs in `make test` when gcc -m32 works. Fake disc, stub:2: 86
  sends, every one whole; **one VIF0 and one VIF1 send** (func_0015f018, mdlgs: TTE, upper words FLUSHE / FLUSHA
  + STCYCL 4,4), which corrects session 74's "all GIF". Valgrind 0 errors. Only host/ and tests/ changed:
  **every out/build object bit-identical**, the float ELF the same (no float-untested row).

- **Session 74** (static, vita-port-plan 5.1n, renderer-spec 4.4): **abscheck now reads the host data**
  (`data` rows: a word of a game object's .data / .rodata with no relocation that is a PS2 .text address or a
  variable's start): **0 rows**, 1,108 words decided by data_relocs.tsv's reasons (resfile 553, into-func 527
  u16 / s16 pairs...), one REVIEWED_DATA entry (D_0048CC10 = func_00100670's PS2 jump table, dead on the host).
  So vita-port-plan §4's "absolute addresses in data" is closed: data_relocs.tsv has no tier 3, abscheck 0.
  **`KH1_HOST_TRACE=2`** walks every DMA chain a send starts (PlatDmaSend, and PlatDmaPutVif1Chcr with STR and
  chain mode from the kept TADR): one line per send, each tag when it leaves host memory (image, scratchpad,
  stack), a bad id, a call too deep or no end; `=3` prints every tag. Fake disc, stub:2: 86 sends, 84 GIF (session 75: and one each on VIF0 / VIF1), none
  outside; valgrind 0 errors. renderer-spec 4.4 has the CHCR rule (sceDmaSend keeps word 0's bits, `| 0x105`;
  drawlist leaves TTE set on GIF). Only tools/ and host/ changed: **every out/build object bit-identical**, the
  float ELF the same (no float-untested row).

- **Session 73** (static, vita-port-plan 5.1m, portability rule 14): **found func_00171078 (src/ai/partyai.c)
  reading PS2 address 0x35BD40 on the host** (the matched literal form was the default; only KH1_SHIFTABLE used
  the name): now `#if defined(KH1_SHIFTABLE) || !defined(KH1_PS2)`. **`tools/host/abscheck.py`** (new, after
  `make host-census`) lists PS2 addresses written as numbers in the host objects (memory operands with no
  relocation at main memory / hardware / scratchpad addresses, immediates equal to a PS2 symbol): **0 rows**, 4
  REVIEWED. No hardware register access outside the wrappers (the 0x1000xxxx literals in src/ are DMA tags and pad
  masks). The 21 pointer DMA sends all fit their builders (table in 5.1m); word 0 of a PlatDmaChan is the game's
  CHCR (drawlist sets TTE on the GIF channel, shadow clears it on VIF1): a renderer note. **Every out/build object
  bit-identical**, the float ELF the same (no float-untested row). Valgrind 0 errors up to the overlay entry.
- **Session 72** (static, vita-port-plan 5.1l, portability rule 13): the 181 PlatDmaSend calls sorted by source
  (`python3 -I tools/host/dmacheck.py --list`: 72 static data, 13 bss, 75 scratchpad frames, 21 pointers); the
  static chains fit their host definitions (func_0011fbb0's image uploads are exactly 0xb0; wave.c's packet
  0x1960 of 0x2020). Found and fixed: 63 scratchpad tag addresses built as `(p & 0x0fffffff) | 0x80000000`, three
  VIF1 TADR masks, func_00106b58's `| 0x80000000`, func_0011fb78's tag SPR bit, and opdma.c's two scratchpad stacks
  starting at literal 0x70000000 / 0x70004000 (the ppp effects' packets would have gone there on the host): now
  PLAT_DMA_SPR_ADDR / PLAT_DMA_ADDR / PLAT_DMA_SPR / PLAT_SPR_BASE / PLAT_SPR_END. **Every out/build object
  bit-identical**, the float ELF the same (no float-untested row). `tools/host/dmacheck.py` (new) keeps it at 0.
  relcheck's 11 TImode drafts are of functions matched since: no change.
- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-75.
- **Eight default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032), 34
  (2,049, unchanged in 35 to 58), 59 (2,053, unchanged in 60 to 68), 69 (2,043) and **70 (2,041, the current
  default; sessions 71 to 75 left the float ELF's bytes the same)**. Session 69 made 21 objects one definition (vita-port-plan 5.1i): 10 objects that floated in place as
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
  `KH1_HOST_TRACE=1` prints the searches and reads, `=2` also walks each DMA chain and reads its data as GIF packets / VIF codes (sessions 74-75, host/null/dmawalk.c), `KH1_HOST_FRAMES=N` caps the run, default 600). On
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

## Session 76 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s76 and /mnt/project-files/kh1-runtime/s76, patch KH1_BIG.iso, and run the route in
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
   DMA chains and reads their data, a chain leaving host memory or ending inside a GIF packet / VIF code is a bug to fix): expected, as on the fake disc,
   SYSTEM.CNF, KINGDOM.IDX and the eight files before dktitle.x, then the fault at D_00F20000(0, 0). Then
   **`KH1_HOST_OVL=stub:2`** on the real disc: the Dive to the Heart files (dh.wdt ... dh01.ard) are there, so the
   room parse (func_00132790) gets real data; record in vita-port-plan how far it gets and where it stops. Fix
   host-only causes the way sessions 63 to 70 did (platform answers, layout dependencies as one definition with
   layoutcheck and relcheck at 0, the PS2 ELF byte-identical).
3. **dktitle.x (with the Mac)**: copy Downloads/kh1-test/ovl/dktitle.x into the container (never commit it), run
   `python3 -I tools/ovl/inventory.py dktitle.x --tsv out/ovl/dktitle.layout.tsv`, record the counts (not the bytes)
   in §5.2, then the toolchain check of §5.2 step 2 on 5-8 small leaf functions. Check argcheck's 3 value uses and
   func_002066b0's BENIGN entry against dktitle.x's calls into the main ELF, and indcheck's OVERLAY rows
   (does dktitle.x call the setters func_001c06c0 / func_001468f8 / func_0012cab8 or write vm_lib's hooks? what do
   the targets take?). Does it call func_00109558, and with which states (session 68 guessed 2 = new game)? Does it call drawlist's
   flushes (func_00237f20 / func_002380c0 / func_00238258) or the push func_002376c8 (session 75: nothing in the
   main ELF does; they are what sets TTE on the GIF channel, renderer-spec 4.5)?
   Without the Mac: skip.
4. **Static, without the Mac**: (a) walk the 72 static-data and 13 bss sends of dmacheck `--list` offline (a
   Python twin of host/null/dmawalk.c over the PS2 ELF's bytes, relocating each tag's ADDR through layout.tsv) so
   the chains the fake disc never reaches are read too (grideff, menubg, pointer, texspot, mdlgs, opdma, pppsys);
   record any that end inside a GIF packet / VIF code. (b) With the GIF stream parsed, list per send which GS
   registers its PACKED A+D / REGLIST writes touch (a census for the renderer's state: renderer-spec 3.2 lists the
   modes), and feed VIF1 DIRECT payloads into the GIF parser (PATH2). (c) argcheck's 3 value uses still wait for
   dktitle.x. Keep every PS2 object the same (kh1.elf byte-identical; run fcheck.sh: a float-untested.md row
   only when the float ELF's bytes change).
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=76`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
