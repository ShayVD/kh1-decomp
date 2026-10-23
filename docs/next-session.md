# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 39, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-39.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 39 changed no names). docs/float-untested.md lists every change
  since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names** (bisect
  order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-39 released nothing.
- **Modules** (session 39): 0x00209d48-0x00210000 (81 functions) moved into a new src/menu/: partymdl.c (the party
  models, D_003F3530 is PartyMdl[4] in include/menu/partymdl.h), menubg*.c (the gradients), pointer.c (the menu
  pointer, its bss defined there), partyrow.c, topmenu.c (the page list D_00640E00 and the page tables D_003F32C8 /
  D_003F32E8) and the item page items.c, items.n32.c, itemslots.c (was c14), itemstock.c (was s7_w15). 14 files
  deleted (every src/auto/text_00200000*.c, c3, s6_20, s8_w18, nostrict/b13, n32/s6_n32); objdiff units 795.
  docs/modules.md "Session 39" (traps: PartyMdl +0x14 must be `void *`, func_0011fbb0 returns s32,
  `(u16)D_00640E24` for an lhu).
- **Helpers:** `python3 -I tools/shift/s38move/fold.py FILE.c TYPE --write` folds a file's window view into TextWin
  by offset and type (then `make`); `python3 -I tools/shift/s37move/refs.py LO HI` lists each function's calls and
  D_ names to split a range; `tools/shift/s37move/fcheck.sh base` then `fcheck.sh NAME` after each chunk is the float
  check; `python3 -I tools/shift/s36move/mod.py draft|remove` drafts and removes module code (it skips `static
  inline` helpers and CONTEXT_ONLY copies, and does not call a file with only one left EMPTY). A function that
  matches when its file is copied under another name in src/menu/ (default flags) can leave its flag directory.
  Keep sized externs in .c files: cover_check does not read headers.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 40 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s40 and /mnt/project-files/kh1-runtime/s40, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item page with its three tabs, using
   an item, and anything using atan: camera, lock-on). If it breaks, bisect with the switches listed there, session
   34's first. Move what boots into docs/shiftable-plan.md and clear docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: from 0x00210000 on (docs/modules.md "Next module moves"): the rest of page 0 (the item page:
   its open func_002112f8, set up func_00211358, reset func_00211398; find where page 1 starts with refs.py) into
   src/menu/items*.c, then one module per page. The page open
   functions are in topmenu.c's D_003F32E8. Fold each old file's window view into TextWin first where the types
   agree. `make` byte-identical and the float layout unchanged after every chunk (fcheck.sh).
3. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
4. **Platform wrappers (static, optional)**: src/sound/snd_rpc.c calls sceSifBindRpc / sceSifCallRpc / FlushCache
   directly; a `Plat` sound/iop wrapper in include/platform/ (docs/portability.md rule 2) must compile to the same
   bytes. src/menu/menubg.c's sceGsExecStoreImage / FlushCache / sceGsSyncPath and the pad masks in
   src/text/winmenu.c (func_001fd720) are the next candidates (include/platform/gs.h, pad.h).
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=40`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
