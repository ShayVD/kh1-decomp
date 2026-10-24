# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23).
If this session starts before then (sessions 49 to 57 ran without it), do not ask for the Mac or wait on it: skip item 1, add every float change to docs/float-untested.md as
untested, and do the static items. **From Monday 2026-10-26 on, ask for the Mac and PCSX2 at the start** (the connect
card in the Claude desktop app) **and make item 1 the first thing**: five float builds are waiting for a boot.

## Where we stopped (end of session 57, 2026-10-24)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-57.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 57 changed no data names). docs/float-untested.md lists every
  change since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names**
  (bisect order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-57 released nothing.
- **Session 57 wrapped the disc and the files** (docs/portability.md rule 2 "Session 57"; eight commits, each
  byte-identical with the float check and the data names the same): 54 SDK functions named from their RPC
  numbers (docs/sdk.md "Session 57": sifdev's sceOpen ... sceReadlink, loadfile, the IOP reboot, libcdvd;
  0x00269a90 is now sceCdLayerSearchFile and 0x00269da8 sceCdSearchFile) plus qsort; include/platform/cd.h
  (PlatCd*), file.h (PlatFs*) and iop.h's module loads / reboot (PlatSifLoadModule, PlatSifRebootIop ...), with
  include/sce/libcdvd.h and sifdev.h.  No game file calls libcdvd, sifdev, loadfile or the IOP reboot by func_
  address now.  gs.h gained PlatGsPutPmode / PutDispfb1 / PutDisplay1 / PutExtwrite / PlatGsGetCsr for the GS
  privileged registers (framectl.c, fade.c, dispenv.c, display.c), and pad.h the button names (PAD_CROSS ...,
  PAD_DIR / PAD_LSTICK / PAD_RSTICK: the stick directions are the d-pad bits shifted to 28-31 / 20-23), used by
  every `D_00425BC8->xN & 0xV` test (tools/shift/s57pad/padmask.py).  Session 56's wrappers: dma.h, gs.h,
  thread.h, pad.h, iop.h; `python3 -I tools/shift/s56wrap/conv.py HEADER OLD=NEW,.. FILES` does a switch.
  **The trap** (docs/matching-tips.md "Session 56"): `D = f()` changes code whenever f's return type is not
  exactly D's (a typedef of the same struct counts); none of session 57's calls hit it.
- **Still direct** (portability.md rule 2 "Still direct"): the libvu0 calls (about 3,000, most as func_002675a8 /
  func_00267530 ...), dkmovie.c's sceIpuInit / sceIpuSync, src/gfx/opimage.c's two typed libgraph pointers,
  mdlgs*.c's FlushCache hook pointer, the VIF / DMA register pokes of mdlgs.nostrict.c and shadow.c, field.c's
  func_00262c78 (unidentified, libgcc range) and button tests through other pointers than D_00425BC8.
- **Original source names** (docs/elf-notes.md): ttlib/ui_gauge.c, ttlib/ui.c, src/decode.c, src/sa_task.c, with
  their ranges; none below 0x001c08e8 so far.
- **Helpers:** `python3 -I tools/shift/s50move/group.py src/DIR/NAME LO HI` drafts modules per flag mode,
  `tools/shift/s37move/fcheck.sh base|NAME` (compare float_covered.txt as a sorted set; run `base` on a clean tree
  before any edit, and never run `make` while it builds), `tools/shift/cover_check.py | grep NAME`,
  `tools/checkfile.py FILE -v`, `tools/shift/s31types/s31_warndiff.py FILES` (compares with HEAD: commit-free
  check, or `git reset --soft BASE`, run it, reset back). Data definitions: compare `cut -f2 out/gen/data.tsv |
  sort` with the session's base (a `git worktree` of the base commit, symlink the ELF and tools/toolchain, `make`).
  **`git fetch origin main` first**: the container's origin/main can be stale. A fresh container needs `apt-get
  install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu` (after `dpkg --add-architecture i386`), `make
  toolchain`, the ELF, a plain `make shift` and tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 58 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s58 and /mnt/project-files/kh1-runtime/s58, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities,
   customize, status, config and journal pages with each journal section, changing a config option, using an
   item, equipping a weapon, a save point (save to a card, overwrite a save, change the party), loading a save from
   the title screen, a new game's name entry if one is reachable, buying and selling in an item shop and a Gummi
   shop, the Moogle's synthesis, the title screen left idle until its demo, a battle with the HUD (the HP / MP
   gauges, command menu, lock-on and the target's gauge, damage numbers, an "obtained" notice), the world map's
   gauge, a minigame with a timer or score if one is near, a level-up, a Trinity mark if one is near, a summon if
   one is available, enemy drops picked up, the pause (src/game/pause.c), a game over and its continue
   (src/game/gameover.c), a room change and a world change (src/game/roomload.c), a movie (src/game/dkmovie.c), and
   anything using atan: camera, lock-on). If it breaks, bisect with the switches listed there, session 34's first.
   Move what boots into docs/shiftable-plan.md and clear docs/float-untested.md. Note what the boot shows about the
   "(a guess)" modules and rename the ones it settles. Without the Mac: skip.
2. **The vector maths header (static)**: include/platform/vu.h (or math.h's vector part) for the libvu0 calls:
   the game calls libvu0 about 3,000 times, most by func_ address (func_002675a8 sceVu0CopyVector, func_00267530
   sceVu0SubVector ...; the names are in functions.tsv).  `Plat` or plain sceVu0 names over the game's own vector
   types (check include/ for the existing ones), one directory per commit, each byte-identical; watch the
   return-type trap and the argument casts (a float argument through a macro must stay float).
3. **The small remainder (static)**: a libipu wrapper for dkmovie.c (sceIpuInit / sceIpuSync, with the movie
   overlay's needs in mind), src/gfx/opimage.c's typed libgraph pointers, mdlgs*.c's FlushCache hook, the VIF / DMA
   register pokes of mdlgs.nostrict.c and shadow.c as named helpers, and the button tests through other pointers
   (grep for the pad state's other copies, padmask.py's pattern).
4. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=58`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
