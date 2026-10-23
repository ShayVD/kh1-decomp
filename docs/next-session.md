# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 38, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-38.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: sessions 35 to 38 changed no names). docs/float-untested.md lists every change
  since the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names** (bisect
  order `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35-38 released nothing.
- **Modules** (session 38): 0x001fd248-0x00209d48 (179 functions) moved into src/text/winmenu*.c (the text area
  accessors of a TextWin, the pad masks, the cursor movers, the cursor bar / frame), src/text/winpart*.c (row
  highlights, list frames, scroll arrows and bars, page tabs), src/game/bitsets.c (the bit sets of D_003F34B8),
  src/text/winrow.c (rows in the colour sets D_003F2C40, tabs, titles) and src/text/winlist*.c (list cells).
  28 files deleted (h23, h46, h69 among them); objdiff units 801. TextWin has a union `ud0` at +0xd0 now and
  D_0063F758 is TextWin[24]. docs/modules.md "Session 38" (with two traps: func_001fea38's `((s16 *)&o->ud0)[1]`
  and func_00202678's own view WinUF).
- **Helpers:** `python3 -I tools/shift/s38move/fold.py FILE.c TYPE --write` folds a file's window view into TextWin
  by offset and type (then `make`); `python3 -I tools/shift/s37move/refs.py LO HI` lists each function's calls and
  D_ names to split a range; `tools/shift/s37move/fcheck.sh base` then `fcheck.sh NAME` after each chunk is the float
  check; `python3 -I tools/shift/s36move/mod.py draft|remove` drafts and removes module code (it skips `static
  inline` helpers and does not call a file with only one left EMPTY). Keep sized externs in .c files: cover_check
  does not read headers.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 39 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s39 and /mnt/project-files/kh1-runtime/s39, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, a menu with text windows and lists, and anything using atan: camera,
   lock-on). If it breaks, bisect with the switches listed there, session 34's first. Move what boots into
   docs/shiftable-plan.md and clear docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: from 0x00209d48 on (docs/modules.md "Next module moves"): the party / D_003F3530 group
   func_00209d48 ... func_0020a8f0, the GS image and window code to 0x0020c1c8, then the menus' open / update
   functions to 0x00210000 (s6_20, h70, h24, h47, c14, s7_w15, n32/s6_n32). Fold each old file's window view with
   fold.py first. `make` byte-identical and the float layout unchanged after every chunk (fcheck.sh).
3. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
4. **Platform wrappers (static, optional)**: src/sound/snd_rpc.c calls sceSifBindRpc / sceSifCallRpc / FlushCache
   directly; a `Plat` sound/iop wrapper in include/platform/ (docs/portability.md rule 2) must compile to the same
   bytes. The pad masks in src/text/winmenu.c (func_001fd720) and the pad reads through D_00425BC8 are the next
   candidates for include/platform/pad.h.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=39`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
