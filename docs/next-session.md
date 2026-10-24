# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 45, 2026-10-24)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-45.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 45 changed no data names). docs/float-untested.md lists every
  change since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names**
  (bisect order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-45 released nothing.
- **Modules** (session 45): 0x00236a58-0x00239558 (43 functions) moved: src/menu/mdlcam.c (the menu models'
  camera D_00425F70 and three matrix builders), **src/gfx/** (gsclip.nofill.c vertex range checks; gspkt.c /
  gspkt.nostrict_nofill.c: GIFtag and A+D helpers, the default drawing environment, the GIF DMA sender
  func_00237018; drawlist.c / .nostrict.c / .nostrict_nofill.c: the depth-sorted draw list of
  include/gfx/drawlist.h and its three flushes; prim.c / .nostrict.c / .nostrict_nofill.c: lines, triangles and
  textured quads sent at once) and **src/hud/** (hud.c: the HUD's set up func_00236f18 and step func_00239488, the
  texture / font uploads, the busy check; hudtex.nofill.c / hudtex.nostrict_nofill.c: "command2/uitex.bin"'s 21
  images). 11 old files gone (h73, h73 nostrict_nofill, h25 nostrict, s8_w1, s8_w6, s9_r2_6, s9_w10, s7_w27, auto
  text_00230000_5 / _7 / _8); objdiff units 774. docs/modules.md "Session 45" has the table and the traps:
  **func_002380c0 failed only at link time** (it needs func_00237790 above it: run `make` after every `mod.py
  remove`), func_00237ec0 is called with a third 0 its definition does not take.
- **libvu0 is named** (session 45): 39 functions in functions.tsv (sceVu0ApplyMatrix ... sceVu0ClipAll,
  _sceVu0ecossin, sceVpu0Reset; docs/sdk.md "Session 45"); the SDK files define them by name, game code still calls
  the func_ names (PROVIDE / shift aliases), the new modules call them by name. Platform wrappers so far:
  include/platform/pad.h, mc.h, math.h.
- **Helpers:** `python3 -I tools/shift/s36move/mod.py draft|remove` drafts and removes module code (it skips `static
  inline` helpers, data definitions, CONTEXT_ONLY copies and multi-name extern lines; it does not call a file with
  only one left EMPTY; it leaves each old file's types side by side in a draft); `python3 -I
  tools/shift/s37move/refs.py LO HI` lists each function's calls and D_ names to split a range;
  `tools/shift/s37move/fcheck.sh base` then `fcheck.sh NAME` after each chunk is the float check (compare
  float_covered.txt as a sorted set: a move can change its line order); `python3 -I tools/shift/s38move/fold.py
  FILE.c TYPE --write` folds a file's window view into TextWin. `tools/checkfile.py FILE -v` lists the differing
  words (relocations of data defined in the same file, jump tables, strings and .rodata doubles show there; `make` is
  the judge). Keep sized externs in .c files: cover_check does not read headers. m2c's no-argument calls take the
  value still in a0: write the argument. A fresh container needs `apt-get install libc6:i386 libstdc++5:i386
  binutils-mips-linux-gnu` (after `dpkg --add-architecture i386`), `make toolchain`, the ELF, a plain `make shift`
  and tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 46 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s46 and /mnt/project-files/kh1-runtime/s46, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities,
   customize, status, config and journal pages with each journal section (the journal's 3D models use
   src/menu/mdlcam.c), changing a config option, using an item, equipping a weapon, a save point (save to a card,
   overwrite a save, change the party), loading a save from the title screen, a card with no save and a full card
   if one is at hand, buying and selling in an item shop and a Gummi shop, the Moogle's synthesis, the title screen
   left idle until its demo, a battle with the HUD (gauges, command menu, lock-on), and anything using atan:
   camera, lock-on). If it breaks, bisect with the switches listed there, session 34's first. Move what boots into
   docs/shiftable-plan.md and clear docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: from 0x00239558 on (docs/modules.md "Next module moves"): the HUD's drawing helpers
   func_00239558 ... func_00239e30 (h48, h74, c17, s6_24, h49), then the HUD parts from 0x0023a318 up to the end of
   the game segment (0x0024f2e0), each with its set up and step (hud.c lists them) into src/hud/<part>.c. Split by
   callers and data; name the parts from their strings and data. `make` byte-identical and the float layout
   unchanged after every chunk (fcheck.sh); run `make`, not only checkfile, after each `mod.py remove`.
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
6. End with `make progress-update SESSION=46`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
