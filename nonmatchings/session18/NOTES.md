# Session 18 notes

## s18w: loop insn-count lever on 001636d0, 0010d470 and the small loop drafts (no matches)

Counts are true DP LCS words of the original left unmatched (sc6_s12.py, same as sessions 12-17). Every
baseline was re-measured first and reproduced.

| function | mode | before | after | draft |
|---|---|---|---|---|
| 001636d0 | hand/nostrict | 410 (s7 w14) | **400** | s18w__001636d0_400w.c (natural, keeps the s7 `__asm__("")` flag) |
| 0010d470 | hand, RO=48cdf0 | 170 natural / 129 probe | unchanged | s18w__0010d470_243w_t4shape_finding.c (finding only) |
| 001f2630 | hand/nofill | 1 | 1 | - |
| 001f18e8 | hand/nofill | 2 | 2 | - |
| 001fd858 | hand/nostrict | 1 | 1 | - |
| 001cfc28 | hand | 1 | 1 | - |
| 001f1fc8 | hand/nofill, RO=00490a80 | 2 | 2 | - |
| 001eddc0 | hand | 2 | 2 | - |
| 0021e120 | hand/nostrict | 3 | 3 | - |
| 00125240 | hand | 4 (5 total) | 4 | - |

shift/drafts.tsv now points func_001636d0 at the 400w draft (`drafts.py build` compiles it).

### What the lever can and cannot do (facts from the -dL dumps)
- Inline helper / statement-expression copies survive into both loop passes: about 1 insn per wrap
  (`c = rdw(*str)`), 1.5 per wrap for `rdw(sub[k])`. They only raise insn_count, so they can only
  remove hoists (movables need `threshold * savings * lifetime >= insn_count`) and stop giv
  reductions (`lifetime * threshold * benefit < insn_count` is "not worth while"; threshold was 66 in
  0010d470's copy loop: 2 * (1 + 32)). They cannot make loop.c hoist more.
- Loop pass 2 re-hoists movables that pass 1 refused (0010d470: three life-2 movables refused at 519
  insns in pass 1 were moved in pass 2), but a giv reduced in pass 1 stays reduced. So the giv test of
  pass 1 is the lever's real handle.
- A wrap far from any threshold still renumbers pseudos; jumps in the score at a fixed loop
  decision set (0010d470 at 216 wraps: 129 -> 155 with identical loop decisions) are allocation ties.
- loop.c sees no loop at all in 001fd858, 001cfc28, 001f1fc8 (the for(;;) + switch), 001eddc0,
  0021e120, 00125240. Only 001f2630 and 001f18e8 among the small ones have loops it processes.

### 001636d0: 410 -> 400 (structural, not the lever)
- Inner case 2 copy loop through a row pointer: `src = &D_00573F10[s1 - 1]; (*tm)[k][s0] = (*src)[k][s0];`
  (410 -> 401). The original computes &D[s1-1] once before the outer loop (`sll v0,s1,6; lui/addiu
  D-64; addu a0`) and the inner loop uses one offset giv k*16+j*4 for both the load and the store.
  Fresh variables for the counters or the pointer change nothing (401).
- Inner switch on a signed index, `switch ((s32)f & 3)` (401 -> 400): the original's balanced tree
  (`beq 1; slti 2; beqzl; beqz 0; b default`). Unsigned gives a shorter chain.
- Lever: main loop is 1123 insns; +3, +12, +20 ... +320 copies (wrapping `f = an->fl[i]`) give
  exactly the same output. The two inner loops match in shape already.
- Left: pp spill (the original stores sp+16 to 372(sp) four times; pp still gets REG_EQUIV). The s11
  `pv` probe on top gives 399 but size 4276 (+28) and needs pv; `f32 *pp = pos;` 402/4272; `pp = 0`
  inits and `pp = ikp(pos)` inline identity change nothing. Removing the asm flag: 410. Case 1
  if/else swapped (`(f & 3) != 3` first): 407. Switch on `(f >> 21) & 3` instead of `s2 & 3`: no change.

### 0010d470: no gain
- Natural draft (170) and every natural sc-store form tried here are insensitive to the count up to
  +200 wraps (~500 insns): `b->g[n].sc = scale; n++;` 195, `((TGl *)b)[n + 1].sc`, `n++;
  ((TGl *)b)[n].sc`, `((TGl *)b + n)->sc`, `(u8 *)b + 12 + n * 16`, `(n << 4)`, `((f32 *)b)[n*4+7]`:
  all 249 (with c2 = sub[k]: 213 / 219).
- s14 129w probe (off biv): count changes nothing up to 212 wraps (519 insns); 216 -> 155 (allocation
  only), 256 -> 163, 600 -> 305. At 600 the sc address giv is no longer reduced (needs > 66*8*2 = 1056
  insns while the two store sites are combined) but b+12 folds into the store offset (`addu v0,s1,t1;
  swc1 12(v0)`).
- Single sc store after the if/else (one site, so the address giv is worth 264): 130 at 0 wraps; at
  70 wraps the address giv is not reduced (`addu v0,s1,t3; addiu t3,16; swc1 12(v0)`) but the score is
  259, and b+12 is still folded.
- `u8 *bp = (u8 *)b + 12` as an invariant (before the loop, at the loop top, or per store) gives the
  original store shape exactly (`addiu t4,s1,12` last in the preheader, `addu v0,t4,off; swc1 0(v0)`)
  but 243-270: off as a user biv is set before the while test, while the original's a2 is the reduced
  16n+16 giv set in the preheader. Kept as s18w__0010d470_243w_t4shape_finding.c.
- Why the natural form cannot get the original's split: the 16n+16 DEST_REG givs of the two store
  sites have benefit 2 - 2 (biv n has two increments) = 0, and combine_givs never roots a single-use
  DEST_REG giv, so they are never reduced, at any count. The original needs a 16n+16 reg with more
  than one use before loop.c.

### Small drafts: no gain
- Brute force (tools/matching/wsites_s18.py): every simple assignment in the function wrapped 1 and 2
  times (also 4 and 8 for 001f18e8) with `W(x) = ({ __typeof__(x) _w = (x); _w; })`. Best stays the
  baseline for all eight (001f2630 45 sites, 001f18e8 86, 001fd858 117, 001cfc28 12, 001f1fc8 66,
  001eddc0 31, 0021e120 78, 00125240 14). 001f18e8 is fully insensitive (343/344 variants = 2w).
- 001f2630 count sweep (`c = rdw(...rdw(*str))`, 0-40 wraps): 1w up to +5; at +6 (126 insns)
  pass 1 stops hoisting `sc << 8` (life 2, savings 1), which the original hoists and spills to
  24(sp): 32w (the x2c store lands in the original's position there, but only by reshuffling); +11 on 26w.
  So the original's count is at most ours; the lever goes the wrong way. 0x8000 is not hoisted in
  either.

### Tools
- tools/matching/sweep_s18.py: wrap one expression n times with an inline helper for a list of n and
  score each (parallel). tools/matching/wsites_s18.py: the same over every simple assignment of a
  function with a type-generic statement-expression wrapper. Both call sc6_s12.py (set SC6 to a copy
  whose lro6_s12.py has ROOT = this checkout and takes the compile flags from $MODE).
