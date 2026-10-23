# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 34, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-34.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, the current default). docs/float-untested.md lists every change since the last booted build (KH1_F29_N) and
  the switch that undoes each. **Session 34 released 19 names** (the first releases since session 30; bisect order
  `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 released nothing.
- **reach_check** (worker s34reach): likely-slot, widen-heads, hix-join, align-end, neg-keep. Verdicts in
  docs/shiftable-plan.md "Session 34: reach_check". D_00551600 is a real hazard, kept in float_keep.txt.
- **Modules** (worker s34module): 0x001dcb00-0x001e4918 (159 functions) moved: 5 into src/vm/vm_lib*.c, the rest into
  new src/event/effect*.c, src/event/voice*.c, src/screen/{frame,screen}*.c and src/shop/shop.c. docs/modules.md
  "Session 34". objdiff units 866. s33_protodiff lists nothing now.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 35 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s35 and /mnt/project-files/kh1-runtime/s35, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop and anything using atan: camera, lock-on). If it breaks, bisect with the
   switches listed there, session 34's first. Move what boots into docs/shiftable-plan.md and clear
   docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: 0x001e4918-0x001e7e78 next (about 56 functions, bss D_00630300-D_006314C8, data
   D_003DC498-D_003DD28C, init func_001e4918), then the D_006314CC counters, the D_00631560 users and
   0x001e9d00-0x001ec678 by call graph (docs/modules.md "Next module moves"). `make` byte-identical and the float
   layout unchanged after every chunk.
3. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
4. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
5. End with `make progress-update SESSION=35`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
