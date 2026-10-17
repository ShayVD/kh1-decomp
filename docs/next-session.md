# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 6, 2026-10-17)

- **6,729 / 6,988 functions matched**: 96.3% of functions, 80.2% of code bytes. All are byte-identical and objdiff 100% (docs/progress.md).
  - Game: 6,032 / 6,266.
  - SDK: 697 / 722.
- New this session (docs/workflow.md "Session 6"):
  - CONTEXT_ONLY bodies (docs/context-only-plan.md): a callee's copy above its caller, compiled but never placed.
  - Build modes src/hand/nogcse, nostrict_nogcse, n32, n32_nogcse, n32_nostrict and src/sdk/gcc991111_as296, through the new kh1.toml override keys `ccflags` and `as_compiler` (docs/toolchain.md "Session 6").
  - Statement-order search scripts in tools/matching/ (hill4.py, perm.py, popt.py).
- **docs/worker-brief.md** "Session 6" has every worker finding; docs/matching-tips.md "Session 6 tips" is the short version. The session-6 worker brief is nonmatchings/session6/BRIEF.md.

## What is left (259 functions)

About 219 have drafts and about 40 are asm-only. Run `make rank` for the full list (status `wip`).

1. **Near-miss drafts**: nonmatchings/session6/, 200 files with INDEX.md (words off, mode, what is off), plus nonmatchings/session5/. Many are 2-5 words off and resisted mode sweeps, callee stubs, return-type sweeps and the permuter. A fresh look, brute-force statement orders, or a patched-compiler idea are what is left.
2. **Large functions still unmatched** (400+ instructions): func_001f5fe0 (338w off), func_00166570 (59w), func_0019f1f0 (46w), func_0010d470 (180 of 992 by sequence), func_00219f98 (30w), func_0019bbf0, func_001a7c50, func_001a12f0, func_00202678, func_0022eef8 (32w), func_0019ab38, func_0010a780, func_00102118, func_002040f8, func_00199ac8, func_001c53c8, func_0016ea58, func_001fd858, func_0020ff80, func_001fb428 (86w), func_001830a0, func_0018fee8, func_0020f530, func_001c3b10, func_00197278, and sceGsExecStoreImage (func_00266380).
3. **The n32 mixed-addressing functions** 0x212cc0, 0x2134c8 and 0x217000: no flag reproduces folded offset-0 loads plus split symbol+offset addresses (docs/toolchain.md). Probably a patched or differently configured ee-gcc; investigate before hand work.
4. **SDK leftovers**: lseek64 (1w), ioctl (4w), sceGsDefDispEnv, sceGsSyncPath, sceGsExecStoreImage, sceDbcCreateSocket, the libvu0 shadow matrix (nonmatchings/session6/w6_27__*), and the sceCd* functions.
5. **Hand-written asm (do not force into C)**: these should become `.s` files with tools/asm_export.py, as crt0_start.s and libpc.s did this session.
   - VU0 macro renderers: func_001b8198, func_001b6910, func_001b1ab8, func_001afac0, func_001b3870, func_001ab0e0, func_001ae010, func_001606d0, func_001996d0, func_0019a828, func_00115940.
   - Context switch func_001bfac8; `sq $zero` func_001aa1f8 / func_001aa448.
   - SDK: func_00260738, func_002607e4, func_00265190, func_002654f0, DIntr, func_00260b00 (docs/sdk.md "Session 6").
6. **Unresolved single cases**: func_001c1718 matches only with `-fno-sched-interblock` (find the extra source block or add a mode); func_00171078 (gas split a macro load into the `jr` slot).

## Session 7 plan

1. Export the hand-written asm in item 5 as `.s` files so they count, and decide on the n32 mixed-addressing question (item 3).
2. Work nonmatchings/session6/INDEX.md, smallest word count first, brute-forcing statement orders and callee prototypes.
3. Attempt the large functions in item 2, starting from their near-miss drafts.
4. Finish the SDK leftovers.
5. End with `make progress-update SESSION=7`, commit, open a PR, and refresh this prompt.
