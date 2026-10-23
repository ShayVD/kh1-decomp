# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is away until Monday 2026-10-26** (the user said so on 2026-10-23). Before then, do not ask for the Mac
or wait on it: skip item 1, add every float change to docs/float-untested.md as untested, and do the static items.
From Monday on, ask for the Mac and PCSX2 at the start (the connect card in the Claude desktop app) and make item 1
the first thing.

## Where we stopped (end of session 35, 2026-10-23)

- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-35.
- **Five default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032) and 34
  (2,049, still the current default: session 35 changed no names). docs/float-untested.md lists every change since
  the last booted build (KH1_F29_N) and the switch that undoes each. **Session 34 released 19 names** (bisect order
  `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`); sessions 31-33 and 35 released nothing.
- **Modules** (session 35): 0x001e4918-0x001ec7c0 (204 functions) moved into new src/list/list.c,
  src/event/sound.c, src/screen/wave*.c, src/vm/vm_util*.c, src/vm/vm_ent.c and src/save/flags*.c, with shared
  types VmSub (include/vm/vm_sub.h) and Save1 (include/save/save1.h). docs/modules.md "Session 35". objdiff units
  860. Keep sized externs in .c files: cover_check does not read headers.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 36 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s36 and /mnt/project-files/kh1-runtime/s36, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop and anything using atan: camera, lock-on). If it breaks, bisect with the
   switches listed there, session 34's first. Move what boots into docs/shiftable-plan.md and clear
   docs/float-untested.md. Without the Mac: skip.
2. **Phase 4 modules**: 0x001ec7c0-0x001f0000 next (about 170 functions, the rest of the 0x001e files), starting
   with the D_003E3C80 users (func_001ec7c0 sets it), then the short commands in auto _6 to _13 by data and calls
   (docs/modules.md "Next module moves"). `make` byte-identical and the float layout unchanged after every chunk.
3. **Types (static, optional)**: switch EvVmSub / ScrVmSub / ShopVmSub to VmSub, and fold list.c's ListSave and
   vm_lib's VmSave1 into Save1, each with `make` and the float build.
4. **reach_check (static, optional)**: jump tables whose index has no bound fall back to branch-target labels and
   skip case entries nothing branches to (can miss accesses); and the four libc string arguments still order-dependent
   (docs/shiftable-plan.md "Session 34: reach_check", "Left"). Any release goes into docs/float-untested.md as untested.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=36`, commit, open a PR, and refresh this prompt (keep the Mac note
   accurate).
