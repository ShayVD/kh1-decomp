# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23).
If this session starts before then (sessions 49 to 58 ran without it), do not ask for the Mac or wait on it: skip item 1, add every float change to docs/float-untested.md as
untested, and do the static items. **From Monday 2026-10-26 on, ask for the Mac and PCSX2 at the start** (the connect
card in the Claude desktop app) **and make item 1 the first thing**: five float builds are waiting for a boot.

## Where we stopped (end of session 58, 2026-10-24)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-58.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 58 changed no data names). docs/float-untested.md lists every
  change since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names**
  (bisect order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-58 released nothing.
- **Session 58 wrapped the vector maths** (docs/portability.md rule 2 "Session 58"; one commit per directory, each
  byte-identical with the float check and the data names the same): include/platform/vu.h (PlatVu0CopyVector ...
  PlatVu0ClipAll, PlatVpu0Reset) over include/sce/libvu0.h; 2,633 calls in 192 files, no game file calls libvu0 by
  func_ address or its own prototype now.  The macros cast every argument to libvu0's type and are the same on every
  target (the Vita port links a C / NEON libvu0 under the sceVu0 names).  `python3 -I tools/shift/s58vu/conv.py
  FILES` did the switch and prints ARITY for calls m2c wrote with the wrong argument count (fixes in
  docs/matching-tips.md "Session 58").  Also: dma.h's VIF1 chain / VIF register helpers (PlatDmaPutStat,
  PlatDmaPutVif1Chcr / Qwc / Tadr, PlatVifPutErr, PlatVif1GetStat), thread.h's PlatFlushCacheFn /
  PlatIFlushCacheFn (mdlgs's flush hook), opimage.c through gs.h, and tools/shift/s57pad/padvar.py's button names
  where a local holds the pad state.  Earlier wrappers: dma.h, gs.h, thread.h, pad.h, iop.h (56), cd.h, file.h (57).
  **The trap** (docs/matching-tips.md "Session 56"): `D = f()` changes code whenever f's return type is not
  exactly D's (a typedef of the same struct counts).
- **Still direct** (portability.md rule 2 "Still direct"): dkmovie.c's no-argument sceIpuInit / sceIpuSync stub,
  shadow.c's CHCR bit pokes through the channel pointer, field.c's func_00262c78 (unidentified, libgcc range) and
  the hand VU0 macro code (renderer-spec.md).  Rule 2 is close to done; what remains of phase 4 is the boot test
  and reach_check.
- **Original source names** (docs/elf-notes.md): ttlib/ui_gauge.c, ttlib/ui.c, src/decode.c, src/sa_task.c, with
  their ranges; none below 0x001c08e8 so far.
- **Helpers:** `python3 -I tools/shift/s50move/group.py src/DIR/NAME LO HI` drafts modules per flag mode,
  `tools/shift/s37move/fcheck.sh base|NAME` (compare float_covered.txt as a sorted set; run `base` on a clean tree
  before any edit, and never run `make` while it builds; a syms line naming a func_ alias that went away is
  expected after a rename), `tools/shift/cover_check.py | grep NAME`, `tools/checkfile.py FILE -v`,
  `tools/shift/s31types/s31_warndiff.py FILES` (compares with HEAD: commit-free check). Data definitions: compare
  `cut -f2 out/gen/data.tsv | sort` with the session's base (saved before the first edit).
  **`git fetch origin main` first**: the container's origin/main can be stale. A fresh container needs `apt-get
  install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu` (after `dpkg --add-architecture i386`), `make
  toolchain`, the ELF, a plain `make shift` and tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 59 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s59 and /mnt/project-files/kh1-runtime/s59, patch KH1_BIG.iso, and run the route in
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
2. **reach_check (static)**: jump tables whose index has no bound fall back to branch-target labels and skip case
   entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as
   untested.
3. **Phase 4 wrap-up (static)**: with rule 2 nearly done, write docs/vita-port-plan.md for phase 5: the list of
   include/platform/ headers and what each needs on the Vita (vitasdk calls, the C libvu0, the GIF / VIF1 chain
   walker of docs/renderer-spec.md), what still pins the original layout (docs/shiftable-plan.md), and the order
   to bring them up.  Optionally rule 1 (portability.md): the gameplay files that still write a hardware address
   outside include/platform/ (`grep -rnE "\*\)\s*0x1[0-2]0[0-9a-f]{5}" src` came back empty for game code in
   session 58 apart from the wrappers' users; check 0x7000xxxx scratchpad uses).
4. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
5. End with `make progress-update SESSION=59`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
