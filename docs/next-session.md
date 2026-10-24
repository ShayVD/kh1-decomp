# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23).
If this session starts before then (sessions 49 to 59 ran without it), do not ask for the Mac or wait on it: skip item 1, add every float change to docs/float-untested.md as
untested, and do the static items. **From Monday 2026-10-26 on, ask for the Mac and PCSX2 at the start** (the connect
card in the Claude desktop app) **and make item 1 the first thing**: six float builds are waiting for a boot.

## Where we stopped (end of session 59, 2026-10-24)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-59.
- **Six default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032), 34
  (2,049, unchanged in 35 to 58) and **59 (2,053, the current default)**. docs/float-untested.md lists every change
  since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 59 released 4 names**
  (`--no-fmt-read`: libc / libgraph / libcdvd debug message strings, low risk); session 34 released 19 (bisect order
  `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`).
- **Session 59 closed reach_check's two "Left" items** (docs/shiftable-plan.md "Session 59: reach_check"): jt-read
  (an unbounded switch reads its table's words: 8 switches, 86 case entries newly analysed, float set unchanged)
  and fmt-read (a clean format literal reaches its own bytes to the NUL: the four order-dependent libc strings
  float, and the float set is now the same in every `--visit-seed 1..8` order). reach_check pins 1,352 names.
- **Rule 2 is done for phase 4** (portability.md): session 59 added dma.h's scratchpad constants (PLAT_SPR_BASE /
  END, PLAT_DMA_SPR) for src/util/heap.c and the GIF sender.  What stays direct (dkmovie.c's IPU stub, shadow.c's
  CHCR bits, func_00262c78, the hand VU0 asm) is replaced whole by the port.
- **docs/vita-port-plan.md** (new, session 59): phase 5's plan: each include/platform/ header on vitasdk, the
  renderer (GIF parser, GS memory mirror, VU1 programs as GXM shaders, the VU0 asm rewritten in C), sound, movies
  (MPEG-2: transcode or a software decoder), **the 12 MIPS overlays that must be decompiled for the port** (dktitle.x
  first; wm.x and gb.x are large), u128 on 32-bit ARM (50 files), the fixed memory map and the data order pins, and
  the bring-up order (a `-m32` host build with a null platform first).
- **Original source names** (docs/elf-notes.md): ttlib/ui_gauge.c, ttlib/ui.c, src/decode.c, src/sa_task.c, with
  their ranges; none below 0x001c08e8 so far.
- **Helpers:** `python3 -I tools/shift/s50move/group.py src/DIR/NAME LO HI` drafts modules per flag mode,
  `tools/shift/s37move/fcheck.sh base|NAME` (compare float_covered.txt as a sorted set; run `base` on a clean tree
  before any edit, and never run `make` while it builds; a syms line naming a func_ alias that went away is
  expected after a rename), `tools/shift/cover_check.py | grep NAME`, `tools/checkfile.py FILE -v`,
  `tools/shift/s31types/s31_warndiff.py FILES` (compares with HEAD: commit-free check). Data definitions: compare
  `cut -f2 out/gen/data.tsv | sort` with the session's base (saved before the first edit). reach_check alone (40 s,
  no build): `python3 -I tools/shift/reach_check.py --elf SLPS_251.98 --overlays EMPTYDIR --out F.txt` (after a
  `make shift`; the anchors come from out/shift/kh1-shift.linked.elf).
  **`git fetch origin main` first**: the container's origin/main can be stale. A fresh container needs `apt-get
  install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu` (after `dpkg --add-architecture i386`), `make
  toolchain`, the ELF, a plain `make shift` and tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 60 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s60 and /mnt/project-files/kh1-runtime/s60, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities,
   customize, status, config and journal pages with each journal section, changing a config option, using an
   item, equipping a weapon, a save point (save to a card, overwrite a save, change the party), loading a save from
   the title screen, a new game's name entry if one is reachable, buying and selling in an item shop and a Gummi
   shop, the Moogle's synthesis, the title screen left idle until its demo, a battle with the HUD (the HP / MP
   gauges, command menu, lock-on and the target's gauge, damage numbers, an "obtained" notice), the world map's
   gauge, a minigame with a timer or score if one is near, a level-up, a Trinity mark if one is near, a summon if
   one is available, enemy drops picked up, the pause (src/game/pause.c), a game over and its continue
   (src/game/gameover.c), a room change and a world change (src/game/roomload.c), a movie (src/game/dkmovie.c), and
   anything using atan: camera, lock-on). If it breaks, bisect with the switches listed there: session 59's
   `--no-fmt-read` first, then session 34's. Move what boots into docs/shiftable-plan.md and clear
   docs/float-untested.md. Note what the boot shows about the "(a guess)" modules and rename the ones it settles.
   Without the Mac: skip.
2. **Phase 5 groundwork (static)**, from docs/vita-port-plan.md §5 step 1, the host build: start a `KH1_HOST`
   (`-m32`, gcc or clang on Linux) configuration that compiles the game C off the EE without touching the PS2
   build: a null src/vita/ (or src/host/) platform for every include/platform/ header, u128 as a 16-byte struct
   under `#ifndef KH1_PS2` (check the 50 files for arithmetic on it), the `__asm__` uses guarded, the src/asm/
   functions as stubs. Goal for the session: count what fails to compile, by cause, and fix the mechanical
   causes in headers only (the PS2 build must stay byte-identical: `make check` after each commit). Record the
   counts in docs/vita-port-plan.md.
3. **Overlays (static, optional)**: inventory dktitle.x (the title screen overlay, the first one the port needs):
   its functions, calls into the main ELF, data; plan how to decompile it against the overlay file (the same
   toolchain? check with a few functions, as in session 1). Never commit overlay bytes.
4. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
5. End with `make progress-update SESSION=60`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
