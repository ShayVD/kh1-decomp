# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 33, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-33.
- **Four default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043) and 33 (2,032, the
  current default). docs/float-untested.md lists every change since the last booted build (KH1_F29_N) and the
  switch that undoes each. Sessions 31-33 released nothing; session 33 only pinned (11 names).
- **reach_check idx-span** (worker s33reach, `--no-idx-span`): a bounded index now pins every name to its tight end.
  It fixed session 32's hazard and found a new real one (the script VM's byte variables). docs/shiftable-plan.md
  "Session 33: reach_check" has the verdicts on all 26 names.
- **Modules** (worker s33module): the whole library file 0x001d5408-0x001dcad0 (301 functions) is in
  src/vm/vm_lib*.c, so 0x001cd238-0x001dcad0 is one module ending with the dispatcher. docs/modules.md "Session 33".
- **Types** (worker s33types): VM prototype mismatches 27 -> 1 (h44's func_001e98d0);
  tools/shift/s33types/s33_protodiff.py lists them. View casts still 18.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 34 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s34 and /mnt/project-files/kh1-runtime/s34, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md. If it breaks, bisect with the switches listed there. Move what boots into
   docs/shiftable-plan.md and clear docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: the code after the dispatcher (0x001dcb00 on: auto text_001d0000.c / _2 / _7, h19's four
   with D_0062A640, h44, h67, c10, b11, s6_15 and the 0x001e files), then the 154 later D_003D9FE0 entries
   (0x001ddc78-0x001ec678). Decide by their data whether they are more of vm_lib.c or other files (docs/modules.md
   "Next module moves"). `make` byte-identical and the float layout unchanged after every chunk.
3. **reach_check (static, optional)**: the branch-likely loop bound counts the delay-slot load once too often
   (D_0054C218); tighter bounds could release names, so any release goes into docs/float-untested.md as untested.
   Also the order-dependent names left in "Session 32: reach_check".
4. **Phase 4 types (small)**: h44's func_001e98d0 prototype when h44 moves; the 18 view casts only where a module
   move makes one easy.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=34`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
