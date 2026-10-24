# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23).
If this session starts before then (sessions 49 to 55 ran without it), do not ask for the Mac or wait on it: skip item 1, add every float change to docs/float-untested.md as
untested, and do the static items. **From Monday 2026-10-26 on, ask for the Mac and PCSX2 at the start** (the connect
card in the Claude desktop app) **and make item 1 the first thing**: five float builds are waiting for a boot.

## Where we stopped (end of session 55, 2026-10-24)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-55.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 55 changed no data names). docs/float-untested.md lists every
  change since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names**
  (bisect order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-55 released nothing.
- **The module moves are done** (session 55): 576 functions in 0x001001f8-0x0011c768 went into 28 modules in four
  commits, and the 36 src/hand files left from earlier sessions with no function in them were deleted. **src/auto is
  gone and src/hand holds only vu0.c** (33 VU0 routines). Every matched C function of the game segment is in a
  module except those and the probes in src/anon/session1_probes.c (func_0018ad70, func_001882f8, func_00137418,
  func_00111f70, func_0010ef70). New modules: src/coll/ (a new directory) colobj, mapcoll, mapdata; src/game/ gameover,
  pause, roomload, gametimer, progress, dkmovie, gamestate, framectl, roombg, field; src/screen/ display, dispenv,
  fade, brightfade, capture; src/gfx/ roommdl, texanim, sceneeff, dmapool, grideff, mdlpkt, objwin; src/text/ fldtext,
  selector; src/util/thread. Most names are guesses read from the code ("(a guess)" in each file's top comment).
  docs/modules.md "Session 55" has the table and the traps: **a `#define D_X (*(T *(*)) &D_X)` view of a pointer
  global cost func_00107548 220 words (an `__asm__` alias view matches)**, beq/beql from a callee defined above or
  not, assemble.py crashing on D_00F20000 (a function and a variable), a sized extern leaving with its file (cover_check
  then keeps the next name: D_004E2458 / D_004E3430), and **51 data definitions that left with deleted files, every one
  caught only by the names check of out/gen/data.tsv** (a grep for `T D_X ALIGNED(n);` missed some).
- **Platform code found so far** (docs/portability.md rule 2): src/pad/padread*.c, src/io/discfile.c, cdqueue.c
  (session 54); src/util/thread.c, src/gfx/dmapool.c, src/game/dkmovie.c (the IPU), src/screen/dispenv.c, display.c,
  capture.c, src/game/framectl.c's func_0010f658 (session 55). Wrappers so far: include/platform/pad.h, mc.h, math.h.
- **Original source names** (docs/elf-notes.md): ttlib/ui_gauge.c, ttlib/ui.c, src/decode.c, src/sa_task.c, with
  their ranges; none below 0x001c08e8 so far.
- **libvu0 is named** (session 45; docs/sdk.md "Session 45"); the new modules call it by name.
- **Helpers:** `python3 -I tools/shift/s50move/group.py src/DIR/NAME LO HI` drafts modules per flag mode (sessions 50
  to 55; do not let it append to an existing module, start a new file), `tools/shift/s36move/mod.py remove`,
  `tools/shift/s37move/fcheck.sh base|NAME` (compare float_covered.txt as a sorted set), `tools/shift/cover_check.py |
  grep NAME` for a DIFF, `tools/checkfile.py FILE -v` (relocations of data defined in the same file, jump tables,
  strings and .rodata doubles differ there; `make` is the judge), `tools/shift/s31types/s31_warndiff.py`. Data
  definitions: compare `cut -f2 out/gen/data.tsv | sort` with the base after every change. A fresh container needs
  `apt-get install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu` (after `dpkg --add-architecture i386`), `make
  toolchain`, the ELF, a plain `make shift` and tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 56 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s56 and /mnt/project-files/kh1-runtime/s56, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities,
   customize, status, config and journal pages with each journal section, changing a config option, using an
   item, equipping a weapon, a save point (save to a card, overwrite a save, change the party), loading a save from
   the title screen, a new game's name entry if one is reachable, buying and selling in an item shop and a Gummi
   shop, the Moogle's synthesis, the title screen left idle until its demo, a battle with the HUD (the HP / MP
   gauges, command menu, lock-on and the target's gauge, damage numbers, an "obtained" notice), the world map's
   gauge, a minigame with a timer or score if one is near, a level-up, a Trinity mark if one is near, a summon if
   one is available, enemy drops picked up, the pause (session 55's src/game/pause.c), a game over and its continue
   (src/game/gameover.c), a room change and a world change (src/game/roomload.c), a movie (src/game/dkmovie.c), and
   anything using atan: camera, lock-on). If it breaks, bisect with the switches listed there, session 34's first.
   Move what boots into docs/shiftable-plan.md and clear docs/float-untested.md. Note what the boot shows about the
   "(a guess)" modules and rename the ones it settles. Without the Mac: skip.
2. **Platform wrappers (static)**, now the main Phase 4 work (docs/portability.md rule 2): include/platform/gs.h for
   src/gfx/gspkt.nostrict_nofill.c's func_00237018 (FlushCache, sceGsSyncPath, libdma's func_00266c08 / func_00266f38:
   name them sceDmaGetChan / sceDmaSend from their code first, as libvu0 and libmc were; src/gfx/dmapool.c and
   src/obj/objdraw.nostrict.c's func_00135ed0 call them too), the GS image calls (src/menu/menubg.c's
   sceGsExecStoreImage, hud.c's sceGsSetDefLoadImage / sceGsExecLoadImage, src/screen/capture.c, src/gfx/mdlpkt.c),
   the display environment (src/screen/dispenv.c, display.c, and the GS CSR writes at 0x12000000 / 0x12001000 in
   display.c and framectl.c), the threads of src/util/thread.c, the IPU of src/game/dkmovie.c, src/sound/snd_rpc.c's
   sceSifBindRpc / sceSifCallRpc (a `Plat` sound/iop wrapper), the pad calls of src/pad/padread*.c and the libcdvd
   calls of src/io/discfile.c / cdqueue.c; the pad masks in src/text/winmenu.c (func_001fd720) and
   src/menu/customize.c (func_00216890). Each must compile to the same bytes; one wrapper header per commit.
3. **The probes (static)**: move src/anon/session1_probes.c's five functions into their neighbours' modules (by
   address and callers, as group.py would) and delete the file if nothing else is in it.
4. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=56`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
