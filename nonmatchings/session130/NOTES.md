# Session 130 notes (matching track)

**No new matches: 6,981 / 6,988 still.** One draft improved: **00110618 93 -> 90** (true DP LCS words of the
original unmatched; size still 1088 vs 1072). `make` byte-identical with 6981 functions; shift/drafts.tsv
points at the new draft and `tools/shift/drafts.py build` compiles it.

| function | before | after | what decided it / file |
|---|---|---|---|
| 00110618 | 93 | **90** | permuter, PENALTY_REGALLOC 50: `az = -r * n + l * fa; cz = az / (-n + fa);` (the first cz's numerator computed into az first) (s130__00110618_90w_aznum.c) |

## Permuter runs (4 cores, -j3)
| run | base draft | iterations | permuter score base -> best | best by our measure |
|---|---|---|---|---|
| a | s12w6 93w (hand, strict), PENALTY_REGALLOC 5 -> 50 | ~168,500 (1 h 45) | 14510 -> 12890 | **90** (output-12890) |
| b | run a's 90w output, PENALTY_REGALLOC 50 | ~55,000 (45 min) | 12890 -> 12250 | 90 (output-12840; 12250 is 89 but wrong code, below) |

- Run a found its only real gain within the first ~1,000 iterations; ~165k more gave no lower permuter
  score. Of its outputs only 12890 beat 93 by our count (14460 = 93, 14200 = 95; the permuter's own base,
  preprocessed, scores 94 not 93: whitespace / macro expansion moves one word).
- Set-up: `tools/permuter.py import func_00110618 --file <draft> --out-dir src/hand/strict` (strict is the
  plain src/hand/ mode), PENALTY_REGALLOC raised in tools/toolchain/decomp-permuter/src/scorer.py (put back
  to 5 afterwards). No seds or context copies needed for this function (no pins, no callees but
  sceVu0UnitMatrix / sceVu0MulMatrix).
- Scoring: tools/matching/sc6_s12.py and lro6_s12.py have ROOT `/home/claude/kh1-decomp` hard-coded; copy
  them to the scratchpad with ROOT replaced, copy each output's source.c to src/hand/zz_score.c, run
  `sc6.py src/hand/zz_score.c 00110618`, delete the copy. About 20 s per output.
- What is left is as s12w6 / s23m3 said: fb gets no register (three reloads from 256(sp): the 16 bytes), and
  the FP pairs sxd/syd and cz/az are swapped against the original.
- Run b's 89w output (12250) moves `mt[1][1] = px;` after the first `sceVu0MulMatrix(m2, mt, m2)`: the
  multiply then reads 1.0 there, so the matrix changes. Not a valid draft (drafts are linked by SHIFT_DRAFTS
  builds); the permuter does not know the call reads mt. It does hint that the original's issue order around
  that store differs, but a store cannot move past the call without changing the result.
