# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23).
If this session starts before then (sessions 49 to 65 ran without it), do not ask for the Mac or wait on it: skip items 1
to 3, add every float change to docs/float-untested.md as untested, and do the static items. **From Monday 2026-10-26
on, ask for the Mac and PCSX2 at the start** (the connect card in the Claude desktop app) **and make item 1 the first
thing**: six float builds are waiting for a boot. Items 2 and 3 also need the Mac: the user's ISO is in Downloads for the host
run, and the overlay files are in Downloads/kh1-test/ovl.

## Where we stopped (end of session 65, 2026-10-24)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-65.
- **Six default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032), 34
  (2,049, unchanged in 35 to 58) and **59 (2,053, the current default; sessions 60 to 65 kept the float ELF's
  loaded bytes the same: 64's fcheck showed only the name D_0061FFA0 gone, 65 changed no PS2 object)**. docs/float-untested.md lists every
  change since the last booted build (KH1_F29_N) and the switch that undoes each. Session 59 released 4 names
  (`--no-fmt-read`, low risk); session 34 released 19 (bisect order `--no-hix-join`, `--no-widen-heads`,
  `--no-likely-slot`).
- **Register passthrough** (portability.md rule 10; vita-port-plan.md §5.1c-§5.1e): argcheck lists **0 short
  calls and 3 value uses**: func_001ffaf0 (winmenu.c), func_002040a0 and func_00206710 (winpart.c) have no
  caller in the main ELF; check them against dktitle.x's calls into the main ELF. BENIGN keys may name the
  caller (a third field).
- **Calls through pointers** (session 65, new `python3 -I tools/host/indcheck.py [--all] [--tsv
  out/host/indcheck.tsv]`, clang syntax trees): 242 rows, 74 OK, 8 READ by hand, **47 OVERLAY** (pointers
  only an overlay sets: vm_lib.c's 41 hooks D_0037733C ... D_003773E8, the setters func_001c06c0,
  func_001468f8, func_0012cab8, D_00304B6C, and gumisave.c's two no-argument calls of the gummi overlay's
  entry), 7 `?def`, **93 `?`** unresolved. Fixed: objwin.c's close callback (the host passes (w, w), the
  EE's a0 / a1), asin / nan called without their argument. It also checks argument classes from the trees
  (headers, `()` declarations, casts; abicheck missed 10, all fixed) and f32s promoted by unprototyped calls
  (0). Rows to act on print by default (SHORT, ABI, PROMO, CLANG); CLANG rows left are files clang cannot
  parse (gcc nested functions in ppp/keshptail(x), kethdraw).
- **Argument classes** (portability.md rule 11): `python3 -I tools/host/abicheck.py` (text) and indcheck
  (trees) both 0. Run both after any new declaration.
- **Null platform**: PlatMcSync answers done with "no card" (-10) and PlatMcGetInfo writes its outputs (it
  polled forever before); PlatPadRead leaves no button pressed.
- **Host build (phase 5)**: `make host-census` links out/host/kh1-host (all 512 game files + the 8 drafts).
  `KH1_HOST_ISO=PATH out/host/kh1-host` reads the user's own disc image by sector (host/port/cd_image.c;
  `KH1_HOST_TRACE=1` prints the searches and reads, `KH1_HOST_FRAMES=N` caps the run, default 600). On
  tests/host/fake_disc.py's image the boot reads SYSTEM.CNF and KINGDOM.IDX and the main loop runs its frames;
  **under valgrind 60 frames show 0 errors** (rechecked in session 65) (`apt-get install valgrind libc6-dbg:i386`; `valgrind
  --track-origins=yes out/host/kh1-host`). **Not yet run on the real ISO** (it is on the Mac). opdma.c's three
  GS tag lists are one definition now (D_0061EEA0[0x140]; memmap.c's copy is gone).
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
  first edit and after (sessions 62 to 65 did this), or build origin/main in a `git worktree`
  (symlink tools/toolchain, copy the ELF) and `cmp` every out/build .o.
  **`git fetch origin main` first**: the container's origin/main can be stale. A fresh container needs `apt-get
  install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu gcc-multilib gdb` (indcheck needs clang, present in the cloud image) (after `dpkg --add-architecture
  i386`), `make toolchain`, the ELF, a plain `make shift` and tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 66 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s66 and /mnt/project-files/kh1-runtime/s66, patch KH1_BIG.iso, and run the route in
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
2. **Host run on the real disc (with the Mac)**: ask once for the user's ISO (Downloads; the unpatched original,
   not KH1_BIG.iso) to be copied into the container's scratchpad (never into the repo or project files), run
   `KH1_HOST_ISO=... KH1_HOST_TRACE=1 out/host/kh1-host` (and once under valgrind) and record in vita-port-plan
   how far the boot gets and where it stops (expected: the first overlay call D_00F20000(0, 0), which needs §5.2's
   native overlay build). Fix host-only causes the way sessions 63 and 64 did (platform answers, layout
   dependencies in host/port, the PS2 objects bit-identical).
3. **dktitle.x (with the Mac)**: copy Downloads/kh1-test/ovl/dktitle.x into the container (never commit it), run
   `python3 -I tools/ovl/inventory.py dktitle.x --tsv out/ovl/dktitle.layout.tsv`, record the counts (not the bytes)
   in §5.2, then the toolchain check of §5.2 step 2 on 5-8 small leaf functions. Check argcheck's 3 value uses and
   func_002066b0's BENIGN entry against dktitle.x's calls into the main ELF, and indcheck's OVERLAY rows
   (does dktitle.x call the setters func_001c06c0 / func_001468f8 / func_0012cab8 or write vm_lib's hooks? what do
   the targets take?). Without the Mac: skip.
4. **Static, without the Mac**: indcheck's 93 `?` rows: teach it the setters it does not follow (struct
   callbacks stored through a register function: ppp's component tables in pppsys.c / pppsys.nostrict.c,
   partyctl.nostrict.c's cb44 / p1C / p74, mdlgs.nostrict.c's GsTask list, hitreact's Fn6 tables, objmove's
   MvFn / StFn through D_00350D88), or read them by hand into its READ table; a call with fewer arguments than
   a target takes is fixed like objwin.c's (pass what the EE's registers hold; `#ifdef KH1_PS2` when the PS2
   code changes). Then the other null-platform answers the game reads back (PlatPadGetButtonProfile,
   PlatSifCallRpc's receive buffers, PlatMcGetDir / PlatMcRead counts) and what the memory-card "no card" path
   does in a host run that reaches a save.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=66`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
