# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 32, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-32.
- **Three default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047) and 32 (2,043, the current
  default). docs/float-untested.md lists every change since the last booted build (KH1_F29_N), the switch that undoes
  each, the risk, and a hazard to read first (bounded indexes that run past the next name; 26 floating names).
- **reach_check** (worker s32reach): multi-base closed the D_003F4C90 gap; widen-bases, sign-prune, shadow-image and
  arg-drop fixed order dependence and two hangs. 1,362 pinned without overlays, 4 newly pinned, none released.
  docs/shiftable-plan.md "Session 32: reach_check" (what is still order-dependent: widening, not lost bases).
- **Modules** (workers s32module, s32module2): src/msgwin/ (0x001ca9e8-0x001cce38) and src/vm/vm_lib*.c (the
  dispatcher func_001dcad0, the D_003D9FE0 table and 275 library functions 0x001cd238-0x001d5408). docs/modules.md
  "Session 32" and "Next module moves".
- **Phase 4 types**: view casts 56 -> 18; VmMgr's 0x3180 union is gone. docs/shiftable-plan.md "Session 32: Phase 4
  types" lists the 18 and why each stays.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 33 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s33 and /mnt/project-files/kh1-runtime/s33, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md. If it breaks, bisect with the switches listed there. Move what boots into
   docs/shiftable-plan.md and clear docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: the rest of the library file 0x001d5408-0x001dcad0 into src/vm/vm_lib*.c in chunks (next
   0x001d5408-0x001d5b58, then the long h18 and h19 runs), then the code after the dispatcher (0x001dcb00 on) by
   its data. `make` byte-identical and the float layout unchanged after every chunk.
3. **reach_check (static)**: read the 26 floating names in "Session 32: reach_check" whose bounded index overruns
   into them (func_0021cfc8's D_003F5C18[i < 6] first) and decide case by case; a fix that pins is safe, a release
   goes into docs/float-untested.md as untested.
4. **Phase 4 types (small)**: the 18 left are mostly genuine second views; only take the ones the module moves make
   easy. Prototype mismatches of VM functions (docs/modules.md "Next module moves") are a better use of a worker.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=33`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
