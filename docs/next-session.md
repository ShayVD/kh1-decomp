# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 10, 2026-10-18)

- **6,916 / 6,988 functions matched**: 98.97% of functions, 93.74% of code bytes. All are byte-identical and objdiff 100% (docs/progress.md).
  - Game: 6,197 / 6,266.
  - SDK: 719 / 722.
- Session 10 matched 16 (plus DIntr moved from asm to C) with 14 round-1 and 10 round-2 workers, at most about 5 at a time: 14 at once crashed the container twice (docs/workflow.md "Session 10", docs/matching-tips.md "Session 10 tips"). Every worker finding is in nonmatchings/session10/NOTES.md; the brief is nonmatchings/session10/BRIEF.md. Best drafts are in nonmatchings/session10/ (newest), then session9/8/7/6.
- The four hack-only functions are real matches now (DIntr, Tail3Draw/Tail3XDraw with a GNU C nested inline helper, 0010a780 with a CONTEXT_ONLY data definition). The original assembler is stock 2.96 gas after all: "nofill" functions are probably `-g` builds (docs/toolchain.md "Session 10 correction"). No post-pass build mode is needed.
- Main levers this session: real types for alias sets (struct type a callee takes, bitfield structs for packed words, no punning unions, f32 zero fields), callee return types per file, CONTEXT_ONLY `{}` stubs (they work through REG_EH_REGION 0, try subsets), writing `goto` tails out as duplicates and identical if/else arms (jump2 re-merges them, refs stay), inline helpers, block-local reloads, dead global reads for PRE, re-measuring in nofill modes.
- New tools in tools/matching/: mchk_s10.py / lchk_s10.py (fast warm checkers), lchkro_s10.py (LCS with rodata), hl2_s10.py, hcf_s10.py, slot_s10.py, ctxsweep_s10.py. checkfile.py can take minutes under load; iterate with these.
- Known quirk: `make rank` lists libc statics (00251600, 00252370 as `wip`; 00253b10, 00253cd0) as unmatched; they are matched and placed.

## What is left (69 functions)

Run `make rank` for the full list (status `wip`). Counts are LCS words from the best draft (NOTES.md has the diagnosis for each).

1. **Within 1-6 words**: 001c2ec8 (1w; 0w only with an asm-alias symbol), 00101bb8, 001502e8, 0025a560 (2w), 001f2630, 001b9f78 (3w), 001e0ab0 / 001e0d98 / 001e10f8 (4w, reorg `li v0,4` steal), 00169688 (4w), 001c3b10 (4), 001f1fc8 (5w), 00102118 (6), 00169f28 (6w, only an f20/f21 swap).
2. **7-17 words**: 0011b220, 00105d88, 00120cf8, 001cf960, 00202678 (7); 00217000, 00125240 (8); 00265608, 0024c950 (9, hand/nofill); 001fb428 (10); 001c99a8 (10); 001c5ee8, 001137f8 (11); 0021e120, 0010b390, 001fa8b0 (12); 00152928, 001eddc0 (13); 00260610 (14); 0019f1f0, 00110e68, 001c95f8 (15); 001ba520, 00214a68 (16); 001f31a8, 00192958, 001f18e8 (17).
3. **18-60 words**: 001cfc28 (18); 00103c48 (19); 001fbcd8 (20); 0010ba98, 00166570 (21); 00199ac8, 0019ab38, 00216890 (24); 0023a968, 00107c48 (25); 00105288 (28); 00200e28 (30); 001ffb30 (31); 00135a68 (33); 001db718 (40); 001fe1b8 (59).
4. **Large**: 00106ed0 (71), 001bd090 (74), 00107548 (118), 00110618 (136, probe), 001e1838 (161), 001fd858 (197), 001c62a0 (242), 00200038 (254), 001f5fe0 (276 hand/nofill), 0010d470 (330), 001636d0 (414).
5. **Suspected compiler difference**: 001bd090 only (a post-combine if-conversion that keeps an earlier store; 2.96 and the 99xxxx compilers all keep a branch or drop the store).

## Session 11 plan

1. Re-run the cheap sweeps on every draft first: tools/matching/ctxsweep_s10.py (stubs and callee returns), nofill-mode re-measure, then the session-10 type levers (bitfields, struct types, no punning unions).
2. Then the 1-6 word list with the session-10 levers (written-out tails, identical arms, block-local reloads, inline helpers), then 7-17, closest first, then the larger ones by LCS. Run at most about 5 workers at once.
3. Look again at 001bd090 with fresh eyes, or record it as a compiler difference.
4. End with `make progress-update SESSION=11`, commit, open a PR, and refresh this prompt.
