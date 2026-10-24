# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23).
If this session starts before then (sessions 49 to 62 ran without it), do not ask for the Mac or wait on it: skip items 1
and 3, add every float change to docs/float-untested.md as untested, and do the static items. **From Monday 2026-10-26
on, ask for the Mac and PCSX2 at the start** (the connect card in the Claude desktop app) **and make item 1 the first
thing**: six float builds are waiting for a boot. Item 3 also needs the Mac: the overlay files are in
Downloads/kh1-test/ovl.

## Where we stopped (end of session 62, 2026-10-24)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-62.
- **Six default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032), 34
  (2,049, unchanged in 35 to 58) and **59 (2,053, the current default; sessions 60 to 62 kept every PS2 object
  byte-identical)**. docs/float-untested.md lists every change since the last booted build (KH1_F29_N) and the
  switch that undoes each. Session 59 released 4 names (`--no-fmt-read`, low risk); session 34 released 19 (bisect
  order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`).
- **Host build (phase 5)**: `make host-census` compiles all 512 game files plus the 8 drafts of the unmatched
  functions and now **links out/host/kh1-host** (gcc -m32 -no-pie, no undefined symbol) and **runs the boot to
  the first PlatCdRead** (func_00120ba0's one-sector read at lsn 0; the null platform answers every
  PlatCdSearchFile "found at 0" and stops at the first read; `KH1_HOST_CD=go` carries on). docs/vita-port-plan.md
  §5.1b: host/port/memmap.c (the fixed map as one block; the 13 low D_ are Gummi save-block offsets),
  sdk_host.c (the 20 SDK func_ named: bsearch, memset, libm, `__main`, sceGsSyncVCallback ...; newlib rand and
  `__assert`), asm_c.c (C for the hand asm: the two LZ decoders of decode.c, the normalize with w = length,
  the 8-point box cull, the matrix multiply; the VU0 packet builders and func_001aa1f8 stubbed), tasks.c (both
  cooperative task systems on ucontext, 256 KiB host stacks), host/null/main.c (the runner, a crash backtrace).
- **Register passthrough** (portability.md rule 10): m2c calls that rely on the EE's leftover a0-a7 / $f12 or
  v0 / $f0. tools/host/argcheck.py finds them; session 62 fixed 57 of 119 short calls and 360 of 644 value uses
  (49 functions return their callee's value now), every object bit-identical. **Left: 62 calls (30 callees),
  284 value uses (111 functions)**; method in §5.1b.
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
  `python3 -I tools/host/census.py --exe`), then `out/host/kh1-host` (gdb works: objects have -g); `--files
  CAUSE` / `--show FILE`; out/host/undefined.txt. `python3 -I tools/host/argcheck.py --tsv out/host/argcheck.tsv`
  lists the passthrough calls. `python3 -I tools/host/vu2c.py FILE LINE` turns one VU0 asm statement into PlatVu0
  calls. A quick "did any object change" check: `find out/build -name '*.o' | sort | xargs sha1sum` before the
  first edit and after (session 62 did this: all 677 the same), or build origin/main in a `git worktree`
  (symlink tools/toolchain, copy the ELF) and `cmp` every out/build .o.
  **`git fetch origin main` first**: the container's origin/main can be stale. A fresh container needs `apt-get
  install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu gcc-multilib` (after `dpkg --add-architecture i386`),
  `make toolchain`, the ELF, a plain `make shift` and tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 63 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s63 and /mnt/project-files/kh1-runtime/s63, patch KH1_BIG.iso, and run the route in
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
2. **Host build (static)**, docs/vita-port-plan.md §5.1b "Next for the host build": the rest of argcheck's list
   (read each caller's asm; keep every object bit-identical: sha1sum out/build before and after). Then a disc
   behind the null platform: a host cd platform (host/disc/ or a mode of host/null) that reads KINGDOM.IDX /
   KINGDOM.IMG from a directory the user extracts from their own ISO (tools/shift/extract_kingdom.py; never
   committed, never in the container unless the user puts it there: ask once, from the Mac session), so
   PlatCdSearchFile / PlatCdRead answer with real sectors, and a frame loop that calls kh1_vsync_cb. Run as far
   as it goes and record where it stops (§5.1b).
3. **dktitle.x (with the Mac)**: copy Downloads/kh1-test/ovl/dktitle.x into the container (never commit it), run
   `python3 -I tools/ovl/inventory.py dktitle.x --tsv out/ovl/dktitle.layout.tsv`, record the counts (not the bytes)
   in §5.2, then the toolchain check of §5.2 step 2 on 5-8 small leaf functions. Without the Mac: skip.
4. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
5. End with `make progress-update SESSION=63`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
