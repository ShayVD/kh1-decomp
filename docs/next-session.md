# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 41, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-41.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 41 changed no names). docs/float-untested.md lists every change
  since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names** (bisect
  order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-41 released nothing.
- **Modules** (session 41): 0x00219128-0x0021dbb8 (109 functions) moved into src/menu/: settings.c (the D_003F34B8
  accessors, include/menu/settings.h), config.c / config.nostrict.c (page 6, most likely the config page), and page
  5's frame in three parts: journalmdl.c (its model D_00643020, typed JMdl), journalfx.c / journalfx.nostrict.c (the
  sprite frames), journal.c (the section list, the first window, open, set up, reset). 9 old files deleted
  (nostrict/s9_w7, s9_r2_5, s9_w5, nostrict/s6_22, nostrict/c15, auto text_00210000_2 _4 _10 _11); objdiff units
  786. docs/modules.md "Session 41": page 5's set up / reset also call its six sections' (0x0021dbb8 ... 0x00223978,
  not moved yet); D_003F34B8->b112[1] is page 5's "complete" marker. Traps: a body of the callee above the caller
  turns one bne into bnel (func_00219f98 and func_00219870 keep CONTEXT_ONLY stubs), `mod.py remove` can leave a
  caller below the old definition with no prototype (h71's func_0021cd68 / func_0021c5e0: check every moved name),
  and `grep -v NAME` on refs.py output also drops NAME's callers.
- **Helpers:** `python3 -I tools/shift/s36move/mod.py draft|remove` drafts and removes module code (it skips `static
  inline` helpers, data definitions and CONTEXT_ONLY copies, and does not call a file with only one left EMPTY);
  `python3 -I tools/shift/s37move/refs.py LO HI` lists each function's calls and D_ names to split a range;
  `tools/shift/s37move/fcheck.sh base` then `fcheck.sh NAME` after each chunk is the float check (compare
  float_covered.txt as a sorted set: a move can change its line order); `python3 -I tools/shift/s38move/fold.py
  FILE.c TYPE --write` folds a file's window view into TextWin. `tools/checkfile.py FILE -v` lists the differing
  words (relocations of data defined in the same file and jump tables show there; `make` is the judge). Keep sized
  externs in .c files: cover_check does not read headers.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 42 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s42 and /mnt/project-files/kh1-runtime/s42, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities,
   customize, status, config and journal pages, changing a config option, using an item, equipping a weapon, and
   anything using atan: camera, lock-on). If it breaks, bisect with the switches listed there, session 34's first.
   Move what boots into docs/shiftable-plan.md and clear docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: from 0x0021dbb8 on (docs/modules.md "Next module moves"): page 5's six sections, one module
   each, split where each one's opener (D_003F5A00) / set up / reset end it (the first is 0x0021dbb8 to about
   0x0021fbb8: opener func_0021faf8, set up func_0021fb28, reset func_0021fb50), then func_00223e10, then page 7
   (title func_00229088, open func_002293f0, set up func_00229820, reset func_00229850; find where it starts). Fold
   views into TextWin where the types agree (not where +0xd0 is read as plain s16). `make` byte-identical and the
   float layout unchanged after every chunk (fcheck.sh).
3. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
4. **Platform wrappers (static, optional)**: src/sound/snd_rpc.c calls sceSifBindRpc / sceSifCallRpc / FlushCache
   directly; a `Plat` sound/iop wrapper in include/platform/ (docs/portability.md rule 2) must compile to the same
   bytes. src/menu/menubg.c's sceGsExecStoreImage / FlushCache / sceGsSyncPath, the GS packets of
   src/menu/config.nostrict.c and src/menu/journalfx.nostrict.c (sceGsSyncPath), FlushCache in
   src/menu/journalmdl.c / journal.c, and the pad masks in src/text/winmenu.c (func_001fd720) and
   src/menu/customize.c (func_00216890) are the next candidates (include/platform/gs.h, pad.h).
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=42`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
