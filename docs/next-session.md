# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 5, 2026-10-17)

- **6,415 / 6,986 functions matched**: 91.8% of functions, 70.4% of code bytes. All are byte-identical and objdiff 100% (docs/progress.md).
  - Game: 5,749 / 6,264.
  - SDK: 666 / 722.
- Every function of 1-300 instructions has been attempted by hand at least once. Functions of 300-2,000 instructions (lists c00-c18) were attempted once, about 30-50% matched, and some were never reached (below).
- New this session:
  - Build modes: src/hand/nostrict, nofill and nostrict_nofill.
  - SDK compilers: src/sdk/gcc991111_01 (ee-gcc 2.9-991111-01) and src/sdk/nostrict.
  - GNU nested functions now match (func_001a7718).
  - Layout splits for hidden functions.
- **docs/worker-brief.md** is the full list of matching tricks found this session. Read it before hand work; its tool paths point at tools/matching/.
- **docs/matching-tips.md** has the summarised version.

## What is left (about 570 functions)

1. **Near-miss drafts**: nonmatchings/session5/, about 160 files. See nonmatchings/session5/INDEX.md for what each is waiting on. Many are 2-20 words off.
2. **Callers that need a non-matching callee defined above them** (the callee-earlier effect). Implement the "context-only body" build feature from docs/context-only-plan.md (`#define CONTEXT_ONLY __attribute__((weak, section(".ctx")))`, plus fix-obj, split_rodata and kh1.ld changes). That lands func_0019cb88 and func_001a0628 at once, and probably func_00219870, func_0023f250, func_0012e4b0 and func_00130f18 as well.
3. **Giant functions never attempted**:
   - func_001dd5c0, func_001e1c20, func_0010d470, func_001166e8.
   - pppKeShpTail3Draw, pppKeShpTailXDraw, pppKeMdlDttDraw.
   - func_001f1fc8, func_001f94f0, func_001f5fe0.
   - func_001fbcd8, func_001fc750, func_001fd858, func_00200648, func_001ffb30.
   - func_0020ff80, func_002134c8, func_00215838, func_002106b8.
   - func_00202678, func_00208458, func_00218218, func_00219f98, func_00225ea8.
   - func_002307c0, func_00231018, func_00234910, func_0022fcb8, func_00238a70.
   - func_0023bb98, func_0023b570, func_00241d60.
   - `python3 tools/autodecomp.py`-style listing: run `make rank` for the full list.
4. **SDK leftovers**:
   - sceCd* (DiskReady, Read, Init, SearchFile), sceIpuInit, sceGsSyncPath, sceGsDefDispEnv, sceGsExecStoreImage.
   - 0x00259698, 0x00250360, 0x0025be38, 0x0025c0f8, func_0025add8.
   - Near-misses in nonmatchings/session5/s1__* and s2__*.
5. **Hand-written asm (do not force into C)**:
   - VU0 macro renderers: func_001b8198, func_001b6910, func_001b1ab8, func_001afac0, func_001b3870, func_001ab0e0, func_001ae010, func_001606d0, func_001996d0, func_0019a828, func_00115940.
   - Context switch func_001bfac8; `sq $zero` func_001aa1f8 / func_001aa448.
   - SDK COP0, cache and MMI routines listed in docs/sdk.md.
   - These should eventually become `.s` files or documented asm stubs.

## Session 6 plan

1. Implement context-only bodies (item 2 above) and land the waiting callers.
2. Work the near-misses in nonmatchings/session5/, smallest word count first, with the tools in tools/matching/.
3. Attempt the never-tried giant functions.
4. Finish the SDK leftovers.
5. End with `make progress-update`, commit, open a PR, and refresh this prompt.
