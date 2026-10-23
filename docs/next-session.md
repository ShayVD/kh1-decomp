# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until after the weekend of 2026-10-24/25** (the user said so on 2026-10-23). Before Monday
2026-10-26, do not ask for the Mac or wait on it: skip item 1, keep every float candidate marked untested, and do
the static items. From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app).

## Where we stopped (end of session 31, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-31.
- **Two default float builds are unbooted**: session 30's (2,100 names float) and session 31's (2,047 names: the
  arg-join fix pinned 54 more and released none). Session 31's is the current default and the one to boot.
- **reach_check** (worker s31reach): arg-keep, join-keep, stored-idx (`--no-arg-keep`, `--no-join-keep`,
  `--no-stored-idx`); 1,358 pinned without overlays. `--visit-seed N` shuffles visit order; the one real gap left
  is D_003F4C90 (func_00219f98: a loop join keeps only the lower of two bases). docs/shiftable-plan.md "Session 31".
- **Modules** (worker s31module): src/vm/vm_calc.c, src/vm/vm_find.nofill.c, and a second module src/camera/
  (0x001c5168-0x001ca9e8). docs/modules.md "Session 31".
- **Phase 4 types** (worker s31types): view casts 214 -> 52 (22 pieces). docs/shiftable-plan.md "Session 31: Phase 4 types".

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 32 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run tools/shift/data_owners.py, stage out/overlays
   from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to Downloads/kh1-test/s32
   and /mnt/project-files/kh1-runtime/s32, patch KH1_BIG.iso, and run the usual route: load menu, save 06 with
   Donald and Goofy, test T, the desert fight, the in-game menu, save 05 End of the World, and the warp drive to
   Neverland. If it breaks, rebuild with `SHIFT_REACH_FLAGS="--no-arg-keep --no-join-keep --no-stored-idx"`
   (= session 30's default) and bisect session 30's releases with `--no-path-step`, `--no-arg-bound`,
   `--no-wr-span` (riskiest list in docs/shiftable-plan.md "Session 30: reach_check"). Without the Mac: skip.
2. **reach_check**: the D_003F4C90 gap (an IDX with several bases, or an unbounded `idx` from each base a join
   folds in); `--no-*` must reproduce session 31's list byte for byte. Any new release is untested until booted.
3. **Phase 4 modules**: docs/modules.md "Next module moves": split the D_003D9FE0 script-function library
   (0x001c6d08-0x001ec678) group by group, starting with the VmMgr functions 0x001ca9e8-0x001cce38; then move
   func_001dcad0 and D_003D9FE0; retype h42 to script_vm.h and drop its CONTEXT_ONLY func_001c4640. `make` must
   stay byte-identical.
4. **Phase 4 types**: the last 52 view casts (D_002E26A0 8, the VM-area views D_003C5510 / D_00389C90 /
   D_0037A380 13 now that the VM and camera modules exist, D_002C5C80 4, D_002E3170 3, D_002E31A0 3).
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=32`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
