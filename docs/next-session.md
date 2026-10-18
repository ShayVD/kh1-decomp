# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 7, 2026-10-18)

- **6,792 / 6,988 functions matched**: 97.2% of functions, 87.1% of code bytes. All are byte-identical and objdiff 100% (docs/progress.md).
  - Game: 6,087 / 6,266.
  - SDK: 705 / 722.
- New this session (docs/workflow.md "Session 7", docs/toolchain.md "Session 7"):
  - Hand-written asm exported as .s (VU0 renderers, sq clears, context switch, libkernl asm, the exception trampoline).
  - tools/matching/flagsweep.py (one extra gcc flag per try) and six flag build modes: src/hand/nosi, nogcse_nosi, nogcse_nosib, faddr, nostrict_norcse, norlo.
  - The n32 "mixed addressing" question is answered: nested sub-struct indexing (`D[k].s.d`) in plain o32, not a compiler. Eight other period ee-gcc builds were tested and match nothing.
  - The ppp Tail-draw VU0 family matched as C with VU0 helpers as `#define` inline-asm macros.
  - tools/matching/hc_checkfile.py (fast hill-climb) and tools/matching/batch/ (hundreds of variants per compile).
- **nonmatchings/session7/NOTES.md** has every worker finding; docs/matching-tips.md "Session 7 tips" is the short version. The worker brief is nonmatchings/session7/BRIEF.md.

## What is left (196 functions)

Run `make rank` for the full list (status `wip`/`asm`).

1. **Closest near misses** (1-7 words, each worked by two or three workers): nonmatchings/session7/ and nonmatchings/session6/ for 0025db10, 0025add8, 00101bb8, 00237d48, 00126f18, 001502e8, 00140960, 00269830, 0025a560, 001d9268, 002134c8's siblings, 001f0868 (2w), 001e6038, 0011ab88, 001ea268, 001f2630, 00141608, 0010ed20, 0020b6a8, 00170170, 001fea38, 00212cc0 (7w, s-reg priority only). Mostly register-allocation ties: new structural ideas are needed, not more statement permutation.
2. **asm-barrier cases**: 002695f8, 0026a7f0 (sceCdRead), 002698c8, 001e10f8 reach 0 words only with an empty `__asm__ volatile("")`: find the real side effect (volatile access, inline helper call).
3. **VU0 renderers in src/asm/vu0_render_{1,2,3}.s** (func_001b8198 and 8 others, 1,000-3,100 instructions) are .s stand-ins; the Tail-draw family showed this kind of code is C + inline-asm macros. Rewriting them is the largest byte gain left. Also Tail3Draw 00191248 / Tail3XDraw 00197cf8 (near misses), 0018f268, 001a12f0, 001166e8, 001636d0.
4. **Large functions**: func_001f5fe0 (2,122 insns), func_0010d470, func_001a7c50, func_00102118, func_00166570 (27w), func_0019f1f0 (28w), func_00217000 (56w), func_00169688 (11w), func_0019ab38, func_00219f98, func_0022eef8, func_002040f8, func_0010a780, func_001fd858, func_00200e28, func_00107548, func_00259698 (printf engine), func_001ffb30, 001ff488/00200648/00208458 (GS-packet floods), 001c3b10, 001cc640.
5. **Unresolved single case**: func_00171078 (macro load split into the jr slot; no gas reproduces it).

## Session 8 plan

1. Rewrite one VU0 renderer from vu0_render_{1,2,3}.s as C with the Tail-draw macros; if it works, do the rest.
2. Work the closest near misses with structural rewrites from the asm.
3. Attempt the large functions, starting from the near-miss drafts.
4. End with `make progress-update SESSION=8`, commit, open a PR, and refresh this prompt.
