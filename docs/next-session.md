# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 42, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-42.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 42 changed no names). docs/float-untested.md lists every change
  since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names** (bisect
  order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-42 released nothing.
- **Modules** (session 42): 0x0021dbb8-0x002298e0 (178 functions) moved into src/menu/: page 5's six sections
  journal_s0.c ... journal_s5.c (numbered by their index in the opener table D_003F5A00; s2 has a .nostrict sibling,
  s3 a .nofill one; the shared window view JsWin is in include/menu/journal.h), and page 7 (message 0x70, most likely
  the save point's menu): party.c (the party change, with func_00223e10), savemenu.c / savemenu.nostrict.c (the save
  and load windows; src/save/ is the save data, not this) and page7.c (the frame; window view PtWin in
  include/menu/page7.h). 19 old files gone (h24, h47, h71, c15, cc, ...; two renamed into src/menu/); objdiff units 779. docs/modules.md
  "Session 42" has the table and the traps: **a deleted file's `TYPE D_X[n] ALIGNED(16) = {...}` is lost silently**
  (`make` still passes; only fcheck.sh sees it, so list definitions with a pattern that keeps `ALIGNED(` lines before
  deleting a file), a union alias set at +0x24 in journal_s5.c, and return types (func_001f94f0 s32, func_00233f18
  s32) that change code.
- **Helpers:** `python3 -I tools/shift/s36move/mod.py draft|remove` drafts and removes module code (it skips `static
  inline` helpers, data definitions and CONTEXT_ONLY copies, and does not call a file with only one left EMPTY);
  `python3 -I tools/shift/s37move/refs.py LO HI` lists each function's calls and D_ names to split a range;
  `tools/shift/s37move/fcheck.sh base` then `fcheck.sh NAME` after each chunk is the float check (compare
  float_covered.txt as a sorted set: a move can change its line order); `python3 -I tools/shift/s38move/fold.py
  FILE.c TYPE --write` folds a file's window view into TextWin. `tools/checkfile.py FILE -v` lists the differing
  words (relocations of data defined in the same file, jump tables and .rodata doubles show there; `make` is the
  judge). Keep sized externs in .c files: cover_check does not read headers. m2c's `func_001f42b8()` with no argument
  becomes `func_001f42b8(win)` with the same code.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 43 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s43 and /mnt/project-files/kh1-runtime/s43, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities,
   customize, status, config and journal pages with each journal section, changing a config option, using an item,
   equipping a weapon, a save point (save to a card, change the party), and anything using atan: camera, lock-on).
   If it breaks, bisect with the switches listed there, session 34's first. Move what boots into
   docs/shiftable-plan.md and clear docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: from 0x002298e0 on (docs/modules.md "Next module moves"): the status window D_003F6E40
   (func_002298e0) and the second set of memory card windows on D_00646990 (func_00229928 ... , the slot list
   func_00229ec0 in c16; most likely the title menu's load screen), then on from 0x0022a3a0. Find the openers and the
   window tables in data_003F.s first and split by them. Fold views into TextWin / JsWin / PtWin where the types
   agree. `make` byte-identical and the float layout unchanged after every chunk (fcheck.sh).
3. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
4. **Platform wrappers (static, optional)**: src/sound/snd_rpc.c calls sceSifBindRpc / sceSifCallRpc / FlushCache
   directly; a `Plat` sound/iop wrapper in include/platform/ (docs/portability.md rule 2) must compile to the same
   bytes. The memory card requests of src/menu/savemenu.c / savemenu.nostrict.c (func_00233f28 ... func_00234668,
   on port D_006436D4) are the first memcard wrapper candidates; also src/menu/menubg.c's sceGsExecStoreImage /
   FlushCache / sceGsSyncPath, the GS packets of src/menu/config.nostrict.c, journalfx.nostrict.c and
   journal_s2.nostrict.c (sceGsSyncPath), and the pad masks in src/text/winmenu.c (func_001fd720) and
   src/menu/customize.c (func_00216890) (include/platform/gs.h, pad.h).
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=43`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
