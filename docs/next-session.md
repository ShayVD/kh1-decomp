# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 7, 2026-10-18)

- **6,836 / 6,988 functions matched**: 97.8% of functions, 88.6% of code bytes. All are byte-identical and objdiff 100% (docs/progress.md).
  - Game: 6,124 / 6,266.
  - SDK: 712 / 722.
- New this session (docs/workflow.md "Session 7", docs/toolchain.md "Session 7"):
  - Hand-written asm exported as .s: src/asm/vu0_render_{1,2}.s (seven VU0 renderers, hand-written loops inside a C shell: their final form), src/asm/text_001aa1f8.s, src/sdk/libkernl_asm.s, libkernl_exc.s. Two other renderers matched as C + VU0 macros.
  - Eight single-flag build modes (src/hand/nosi, nogcse_nosi, nogcse_nosib, faddr, nostrict_norcse, norlo, fmam, nostrict_nosib), found with tools/matching/flagsweep.py.
  - The n32 "mixed addressing" question is answered: nested sub-struct indexing (`D[k].s.d`) in plain o32, not a compiler. Eight other period ee-gcc builds were tested and match nothing.
  - The libcdvd asm-barrier cases were volatile state words (sdk/gcc991111_as296).
  - Tools: tools/matching/hc_checkfile.py (hill-climb), tools/matching/batch/ (batch.py, anneal2.py, anneal3.py: many variants per compile), tools/matching/asm_sim.py (symbolic store simulator for packet floods).
- **nonmatchings/session7/NOTES.md** has every worker finding (w1-w38); docs/matching-tips.md "Session 7 tips" and "Later in session 7" are the short version. The worker brief is nonmatchings/session7/BRIEF.md.
- Known quirk: `make rank` lists four libc statics (00251600, 00252370, 00253b10, 00253cd0) as unmatched; they are matched and placed (the rank scan misses `#define name func_X` renames).

## What is left (152 functions)

Run `make rank` for the full list (status `wip`/`asm`). Drafts are in nonmatchings/session7/ and session6/ with the word count in the file name.

1. **Within 1-5 words** (each worked by two or more workers): 0025add8 (1w), 00101bb8, 00237d48, 001d9268, 001502e8, 001e32d8 (2w), 0011ab88, 001e6038, 001ea268, 001f2630 (3w), 001e0ab0 / 001e0d98 / 001e10f8 (4w each, the reorg `li v0,4` steal: NOTES w33/w36), 0010ed20, 001e3a00, 0020b6a8, 00169688 (4w), 0025f338 DIntr (4w), 002177c8, 001f1fc8 (5w). Mostly allocation and scheduling ties: try the w34/w37 allocator lever and the w35 sched1 store rule first.
2. **6-30 words**: 001cf960, 001aa0e0, 00212cc0, 001c99a8, 001ca0f8, 002682a8, 0026a250, 0010ea70, 00110ce0, 00249618, 0011b220, 00125240, 00113e28, 00266380 sceGsExecStoreImage (12w), 001c95f8, 001ba520, 001f4778-style floods 001ff488 (27w), 0010a780 (27w), 00217000 (25w), 00166570 (27w), 0019f1f0 (28w), 00102118 (28w), 0010c720 (12w).
3. **Large or far**: func_001f5fe0 (2,122 insns), 0010d470, 001a7c50, 0019ab38, 00219f98, 0022eef8, 002040f8, 001fd858, 00200e28, 00107548, 001ffb30, 00200648, 00208458, 001c3b10, 001cc640, 00191248 Tail3Draw, 00197cf8 Tail3XDraw, 0018f268, 001a12f0, 001166e8, 001636d0.
4. **Unresolved single case**: func_00171078 (macro load split into the jr slot; no gas reproduces it).

## Session 8 plan

1. Work the 1-5 word list with the session-7 levers (allocator choice, return shapes, CONTEXT_ONLY callees, store order).
2. Then the 6-30 word list, starting from the near-miss drafts.
3. Attempt the large functions.
4. End with `make progress-update SESSION=8`, commit, open a PR, and refresh this prompt.
