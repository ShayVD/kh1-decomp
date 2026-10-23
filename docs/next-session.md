# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 30, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-30.
- **reach_check** (worker s30reach): path-step, arg-bound and wr-span (`--no-path-step`, `--no-arg-bound`,
  `--no-wr-span`). 29 names released, D_003728C0 / D_00372908 newly pinned; the default float build floats
  2,100 names. **Not booted yet** (the Mac was not reachable): docs/shiftable-plan.md "Session 30: reach_check"
  lists the riskiest releases. `stored` (func_0023aed0's Out records) is confirmed unprovable statically.
- **Phase 4 types** (worker s30types): view casts 275 -> 217 (FMtx4 for D_002C58D0, D_00304BE8 down to 1,
  D_002A6238's union Fl20_2a6238, b11 on VmRec). docs/shiftable-plan.md "Session 30: Phase 4 types".
- **First named module** (worker s30module): src/vm/script_vm.c holds all 60 functions of 0x001c08e8-0x001c4ed0
  (the script VM). Flag modes per file via `<name>.<mode>.c`; docs/modules.md has the mechanism and a checklist.
- **PCSX2 loop**: device access needs the connect card approved in the Claude desktop app on the Mac; ask for it
  at the start. Without device_bash, patch_iso.py runs via Remote Control or the user in Terminal
  (docs/workflow.md "Session 29").

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 31 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot session 30's default float build first** (ask for the Mac and PCSX2 at the start): run
   tools/shift/data_owners.py, stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12
   SHIFT_FLOAT=1`, copy the ELF to Downloads/kh1-test/s31 and /mnt/project-files/kh1-runtime/s31, patch
   KH1_BIG.iso, and run the usual route: load menu, save 06 with Donald and Goofy, test T, the desert fight, the
   in-game menu, save 05 End of the World, and the warp drive to Neverland. If anything breaks, bisect with the
   three `--no-*` switches (SHIFT_REACH_FLAGS) before anything else.
2. **reach_check arg-join**: analyse's arg-join drops addresses held on one path only, so whether an access is
   seen depends on visit order (how D_003728C0 / D_00372908 surfaced). Make it order-independent; `--no-*`
   reproduces the session 30 list byte for byte; boot any new release.
3. **Phase 4 modules**: continue docs/modules.md "Next moves": the far handlers func_001cd208 / func_001dcad0,
   func_001e98d0, and whether the code after 0x001c4ed0 extends script_vm.c; retype the 15
   `void func_001c4640(Msg *)` users to script_vm.h one file at a time. Then pick a second subsystem with shared
   types for its own module. `make` must stay byte-identical.
4. **Phase 4 types**: the remaining 217 view casts (D_002E26A0 24, D_002C5968 15, D_00308CDC 15, D_002E31B0 14,
   D_00351E10 10, ...).
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=31`, commit, open a PR, and refresh this prompt.
