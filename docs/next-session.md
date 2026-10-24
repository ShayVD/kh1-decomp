# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23; sessions 49 and 50 ran without it).
Before then, do not ask for the Mac or wait on it: skip item 1, add every float change to docs/float-untested.md as
untested, and do the static items. **From Monday 2026-10-26 on, ask for the Mac and PCSX2 at the start** (the connect
card in the Claude desktop app) **and make item 1 the first thing**: five float builds are waiting for a boot.

## Where we stopped (end of session 50, 2026-10-24)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-50.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 50 changed no data names). docs/float-untested.md lists every
  change since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names**
  (bisect order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-50 released nothing.
- **Modules** (session 50): 446 functions moved, and **the game segment is in modules from 0x00183c70 to its end
  0x0024f2e0** (except the VU0 routines in src/hand/vu0.c, two probes in src/anon/session1_probes.c and the hand
  asm). All of it was ppp, the effect system: 25 class groups in src/ppp/ (pppcomp, pppvertex, pppmatrix, pppdraw,
  ppppoint, ppprand, eiwind, ppploop, kethcls, kebornrnd, kemdl, keshptail, keshpdtt, kelnscls, kemove, kemat,
  drawmdl, kemdltfd3, keshptailx, ryjmtxworld, ryjshipoly, ryjmb, ryjmbprize, ryjmplace, plus ryjmbmodel's helpers),
  one file per flag mode each, named from the class table D_00370200 (docs/structs.md). docs/modules.md "Session
  50" has the tables and the traps: **view a scalar by value** `((T) D_X)`, an array by address, and use a memory
  view `(*(T *)&D_X)` only where the address is taken (a memory view reorders loads in strict-aliasing files);
  **check new modules for implicit declarations** (three slipped through and still matched); a function view
  `#define F ((RET (*)(ARGS)) F)` for prototypes that disagree; files left with only static inline helpers must
  be `git rm`'d by hand.
- **2,653 functions are still in src/auto and src/hand**, all in 0x001001f8-0x00183c70 (out/gen/placements.tsv):
  73 in 0x0018 (the ppp manager core), 324 in 0x0017, 117 in 0x0016, 313 in 0x0015, 315 in 0x0014, 325 in 0x0013,
  471 in 0x0012, 391 in 0x0011.
- **Original source names** (docs/elf-notes.md): ttlib/ui_gauge.c, ttlib/ui.c, src/decode.c, src/sa_task.c, with
  their ranges; none below 0x001c08e8 so far (session 48 used the Gummi strings, sessions 49 and 50 the renderer's op_* strings
  and the ppp class table).
- **libvu0 is named** (session 45): 39 functions in functions.tsv (sceVu0ApplyMatrix ... sceVu0ClipAll,
  _sceVu0ecossin, sceVpu0Reset; docs/sdk.md "Session 45"); the SDK files define them by name, game code still calls
  the func_ names (PROVIDE / shift aliases), the new modules call them by name. Platform wrappers so far:
  include/platform/pad.h, mc.h, math.h.
- **Helpers:** `python3 -I tools/shift/s50move/group.py src/ppp/NAME LO HI [--skip f,...]` (session 50) drafts
  one module per flag mode for a whole address range with assemble.py (each function gets what it saw above it
  in its old file; clashing types, tags and inline helpers renamed NAME_<addr>; clashing externs and prototypes
  viewed per function), prunes it (prune.py) and runs checkfile on each file, calling each FAIL "same as its old
  file (rodata)" or "NEW DIFF"; then `mod.py remove` the functions, `make`, fcheck.sh. Session 50 moved 446
  functions this way. `python3 -I tools/shift/s36move/mod.py draft|remove` drafts and removes module code (it skips `static
  inline` helpers, data definitions, CONTEXT_ONLY copies and multi-name extern lines; it does not call a file with
  only one left EMPTY; it leaves each old file's types side by side in a draft; its NOTE lines name matching notes
  in deleted files: copy them above the moved function); `python3 -I tools/shift/s37move/refs.py LO HI` (addresses
  without 0x) lists each function's calls and D_ names to split a range; `tools/shift/s37move/fcheck.sh base` then
  `fcheck.sh NAME` after each chunk is the float check (compare float_covered.txt as a sorted set: a move can change
  its line order; for a DIFF, `python3 -I tools/shift/cover_check.py | grep NAME` says which extern lost its size);
  `python3 -I tools/shift/s38move/fold.py FILE.c TYPE --write` folds a file's window view into TextWin; `python3 -I
  tools/shift/s31types/s31_warndiff.py FILE.c ...` lists new warnings (old files only: it compares with HEAD).
  `tools/checkfile.py FILE -v` lists the differing words (relocations of data defined in the same file, jump
  tables, strings and .rodata doubles show there; it stops at a section overlap when a file's size changed, so a
  local copy with `--no-check-sections` added to its ld line helps for drafts; `make` is the judge). Keep sized
  externs in .c files: cover_check does not read headers. m2c's no-argument calls take the value still in a0: write
  the argument. A fresh container needs `apt-get install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu` (after
  `dpkg --add-architecture i386`), `make toolchain`, the ELF, a plain `make shift` and tools/shift/data_owners.py
  before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 51 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s51 and /mnt/project-files/kh1-runtime/s51, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities,
   customize, status, config and journal pages with each journal section, changing a config option, using an
   item, equipping a weapon, a save point (save to a card, overwrite a save, change the party), loading a save from
   the title screen, a new game's name entry if one is reachable, buying and selling in an item shop and a Gummi
   shop, the Moogle's synthesis, the title screen left idle until its demo, a battle with the HUD (the HP / MP
   gauges, command menu, lock-on and the target's gauge, damage numbers, an "obtained" notice), the world map's
   gauge, a minigame with a timer or score if one is near, and anything using atan: camera, lock-on). If it breaks,
   bisect with the switches listed there, session 34's first. Move what boots into docs/shiftable-plan.md and clear
   docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules** (docs/modules.md "Next module moves"): go on downwards from 0x00183c70, the top of what is
   left in src/auto and src/hand. First the ppp manager core, 0x00180000-0x00183c70 (73 functions: pppStepPrograms,
   pppRelocProgram, pppDesObject, func_00182588 which makes an instance, the depth sort func_00181608, the texture
   slots func_001808f8 ...; in hand h12, h39 and nostrict h39, h11, h38, s6_10, b07 and auto text_00180000*):
   make it src/ppp/pppsys*.c with `python3 -I tools/shift/s50move/group.py src/ppp/pppsys 00180000 00183c70`, then
   go on into 0x0017 (324 functions; list them with `python3 -I tools/shift/s37move/refs.py 00170000 00180000` and
   group them by what they do or by original-name strings). Leave whole-VU0 functions where they are. `make`
   byte-identical and the float layout unchanged after every chunk (fcheck.sh), and scan the new files with
   `-Wimplicit-function-declaration`; run `make`, not only checkfile, after each `mod.py remove`.
3. **Platform wrappers (static, optional)**: include/platform/gs.h for src/gfx/gspkt.nostrict_nofill.c's
   func_00237018 (FlushCache, sceGsSyncPath, libdma's func_00266c08 / func_00266f38: name them sceDmaGetChan /
   sceDmaSend from their code first, as libvu0 and libmc were), src/menu/menubg.c's sceGsExecStoreImage, hud.c's
   sceGsSetDefLoadImage / sceGsExecLoadImage; src/sound/snd_rpc.c's sceSifBindRpc / sceSifCallRpc (a `Plat`
   sound/iop wrapper, docs/portability.md rule 2); the pad masks in src/text/winmenu.c (func_001fd720) and
   src/menu/customize.c (func_00216890). Each must compile to the same bytes.
4. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=51`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
