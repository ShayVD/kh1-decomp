# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 44, 2026-10-24)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-44.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 44 changed no data names). docs/float-untested.md lists every
  change since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names**
  (bisect order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-44 released nothing.
- **Modules** (session 44): 0x002327b0-0x00236a58 (89 functions) moved: src/list/listmenu.c (the list menu
  func_002329a0, ListMenu in include/list/listmenu.h), src/game/saveimage.c (the save image D_003F8380's seven
  blocks), src/save/savefile.c (the save files' names "BISLPS-25198-NN" / system.bin / icon.sys ..., the head
  D_00425B80, the card check task func_00233168), src/game/xsload.c (an overlay run at 0x00F20000),
  src/pad/padrec.c (the pad's record / replay / script stand-ins), **src/memcard/mcqueue.c and mcstep.c** (the
  memory card request queue and its steps) and src/util/rand.c / rand.nofill.c / rand.nostrict_nofill.c (the
  LCG seeds). 9 old files gone (h48, s6_23, sw, b15, s8_w7, s8_w8, c2, auto text_00230000_4, _9); objdiff units
  773. docs/modules.md "Session 44" has the table and the traps: **h48 defined the load screen's D_003F71C8**
  (moved to loadframe.c; grep every file for data definitions before deleting it), listmenu.c keeps `void
  *D_0064770C`, mcqueue.c needs `int sceMcInit(void)` and leaves func_00265b28 undeclared on purpose.
- **First platform wrapper beyond the pad**: include/platform/mc.h (PlatMc*, macros for libmc on the PS2 build)
  and include/sce/libmc.h; functions.tsv names 14 libmc functions (sceMcGetSlotMax ... sceMcUnformat) from their
  mcserv RPC numbers (docs/sdk.md "Session 44"). Only src/memcard/mcstep.c and mcqueue.c call them.
- **Helpers:** `python3 -I tools/shift/s36move/mod.py draft|remove` drafts and removes module code (it skips `static
  inline` helpers, data definitions, CONTEXT_ONLY copies and multi-name extern lines; it does not call a file with
  only one left EMPTY); `python3 -I tools/shift/s37move/refs.py LO HI` lists each function's calls and D_ names to
  split a range; `tools/shift/s37move/fcheck.sh base` then `fcheck.sh NAME` after each chunk is the float check
  (compare float_covered.txt as a sorted set: a move can change its line order); `python3 -I
  tools/shift/s38move/fold.py FILE.c TYPE --write` folds a file's window view into TextWin. `tools/checkfile.py FILE
  -v` lists the differing words (relocations of data defined in the same file, jump tables, strings and .rodata
  doubles show there; `make` is the judge). Keep sized externs in .c files: cover_check does not read headers. m2c's
  no-argument calls take the value still in a0: write the argument. A fresh container needs `apt-get install
  libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu`, `make toolchain`, the ELF, a plain `make shift` and
  tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 45 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s45 and /mnt/project-files/kh1-runtime/s45, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities,
   customize, status, config and journal pages with each journal section, changing a config option, using an item,
   equipping a weapon, a save point (save to a card, overwrite a save, change the party), loading a save from the
   title screen, a card with no save and a full card if one is at hand, buying and selling in an item shop and a
   Gummi shop, the Moogle's synthesis, the title screen left idle until its demo, and anything using atan: camera,
   lock-on). If it breaks, bisect with the switches listed there, session 34's first. Move what boots into
   docs/shiftable-plan.md and clear docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: from 0x00236a58 on (docs/modules.md "Next module moves"): the menu models' camera
   func_00236a58 (h73, D_00425F70, src/menu/journalmdl.c calls it) with the matrix builders func_00236c68 ...
   func_00236de8 and the range checks func_00236e40 / func_00236e80; then func_00236f00 / func_00236f18 and from
   0x00237018 the GS packet senders (h48 / h73 / s9_w10 / h74 nostrict_nofill; FlushCache, sceGsSyncPath). Split by
   callers and data. `make` byte-identical and the float layout unchanged after every chunk (fcheck.sh).
3. **Platform wrappers (static, optional)**: the memory card is done (include/platform/mc.h). Next: src/sound/
   snd_rpc.c's sceSifBindRpc / sceSifCallRpc / FlushCache (a `Plat` sound/iop wrapper, docs/portability.md rule 2),
   src/menu/menubg.c's sceGsExecStoreImage / FlushCache / sceGsSyncPath, the GS packets of src/menu/
   config.nostrict.c, journalfx.nostrict.c and journal_s2.nostrict.c (sceGsSyncPath), and the pad masks in
   src/text/winmenu.c (func_001fd720) and src/menu/customize.c (func_00216890) (include/platform/gs.h, pad.h). Each
   must compile to the same bytes.
4. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=45`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
