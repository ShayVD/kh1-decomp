# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 9, 2026-10-18)

- **6,900 / 6,988 functions matched**: 98.7% of functions, 92.0% of code bytes. All are byte-identical and objdiff 100% (docs/progress.md).
  - Game: 6,182 / 6,266.
  - SDK: 718 / 722.
- Session 9 matched 24 with two rounds of parallel workers (docs/workflow.md "Session 9", docs/matching-tips.md "Session 9 tips"). Every worker finding is in nonmatchings/session9/NOTES.md; the brief (with its "Round 2" section) is nonmatchings/session9/BRIEF.md. Best drafts are in nonmatchings/session9/ (newest), then session8/7/6.
- Main levers: **sibling ports** (rewrite in the style of a matched function with the same globals, callees or packet type), plain index order for store floods, shared `goto` tails to cut refs, reusing an existing long-lived local, one counter for two loops, compiled-out `do { } while (0)` asserts as block boundaries, callee prototypes (arity_s8.py).
- New tools in tools/matching/: hl_s9.py (LCS hill-climb), gentrees_s9.py / ortree_s9.py (OR-tree shapes), pp_la_s9.py + lcs_pp_s9.py (assembler post-pass for 0010a780).
- Known quirk: `make rank` lists libc statics (00251600, 00252370 as `wip`; 00253b10, 00253cd0) as unmatched; they are matched and placed.

## What is left (86 functions)

Run `make rank` for the full list (status `wip`/`asm`). Counts below are LCS words from the latest draft.

1. **0 words only with a hack** (decide whether to accept, or find the real shape): 0025f338 DIntr (`.p2align` asm), 00191248 Tail3Draw and 00197cf8 Tail3XDraw (frame-overlay struct cast), 0010a780 (needs the assembler post-pass).
2. **Within 1-5 words**: 001c2ec8 (1w), 00101bb8, 001502e8, 0025a560 (2w), 001f2630 (3w), 00166248, 0010ed20, 00169688, 001e0ab0 / 001e0d98 / 001e10f8 (4w, the reorg `li v0,4` steal), 001f1fc8 (5w).
3. **6-31 words**: 0025b2f0, 0010ea70 (6); 00105d88, 00120cf8, 001cf960, 00202678, 00212cc0 (7); 00217000, 00125240 (8); 0011b220, 001b9f78, 00265608 (9); 001c99a8 (10); 001c5ee8, 001137f8 (11); 0021e120, 0010b390, 001fa8b0, 00249718 (12); 00152928, 001eddc0 (13); 00260610 (14); 0024c950, 0019f1f0, 00110e68, 001c95f8 (15); 001166e8, 00214a68 (16); 001f31a8, 00102118 (17); 001cfc28 (18); 00103c48 (19); 001ba520, 001fbcd8 (20); 00166570 (21); 00199ac8, 0019ab38, 00216890 (24); 0023a968 (25); 0010ba98 (27); 00105288 (28); 00107c48 (29; 23 with nogcse + -fno-strength-reduce); 0016ea58 (31).
4. **Large** (32+): 00135a68 (33), 00192958 (34), 002106b8 (38), 0012e1b0 (39), 001db718 (40), 00200e28 (44), 001f18e8 (48), 00169f28 (52), 0024be88 (58), 001fe1b8 (59), 001fb428 (65), 00106ed0 (71), 001bd090 (77), 001c53c8 (81), 001c3b10 (96), 001bc530 (98), 001ffb30 (106), 00107548 (118), 001e1838 (161), 00110618 (167), 00200648 (177), 001fd858 (197), 001c62a0 (242), 00200038 (254), 001f5fe0 (324), 0010d470 (338), 001636d0 (414).
5. **Suspected compiler/assembler differences**: 0010a780 (assembler, now shown), 0025b2f0 (prologue save order in every 991111 mode), 001bd090 (movn if-conversion keeping the earlier store).

## Session 10 plan

1. Sibling-port sweep over every remaining draft first (grep src/ for the same globals and callees), then the 1-5 word list with the session-8/9 levers.
2. Then the 6-31 word list, closest first, and the large functions by LCS.
3. Decide on the four hack-only functions (accept, or keep looking for the real shape) and on an assembler post-pass build mode for 0010a780.
4. End with `make progress-update SESSION=10`, commit, open a PR, and refresh this prompt.
