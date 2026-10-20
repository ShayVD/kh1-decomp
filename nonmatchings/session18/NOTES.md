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

## s18m1: 001f18e8 MATCHED (local register variable lever); 0021e120 3w other basin; no gain elsewhere

Angle (not tried in sessions 6-18): GNU local register variables in plain C, `register u64 k asm("$3");`
(no inline asm). Chosen because several of the near misses were stuck at "the statement order that gives
the right sched order makes local-alloc pick the wrong register" (001f18e8 li 63, 0021e120 li 66/68,
001f2630/001f1fc8 constants, 001cfc28 1.0). A pin takes that register choice out of local-alloc, so the
order can be climbed freely.

- **MATCH func_001f18e8** (hand/nofill, src/hand/nofill/text_001f0000_s18_s18m1.c; `make` byte-identical,
  6974 functions; objdiff 100%). s11w52's 2w draft plus: `register u64 k3 asm("$3");`, `k3 = 63;` right
  after `d[0] = ...`, `d[3] = k3;` after `k6 = 68;` (2w -> 1w: li 63 now issues in the slot after li 0xeeee),
  then `d[9] = 1;` as the last header store (1w -> 0: li t1,1 after li 66). FLAGGED: the pin and s11w52's
  dead FP test are both needed (without the pin 6w, without the test 6w). `register ... = 63` as an
  initializer at the declaration: 28w; s32 type for k3: 18w; `d[3] = k3 = 63`: 13w.
  Housekeeping: shift/unmatched/func_001f18e8.s removed by export_unmatched.py, its drafts.tsv line removed.
- How the lever behaves (dumps): a pin only survives for **constants** (and values cse cannot see through).
  A pinned copy of a computed value is dissolved: expand loads into a pseudo and copies it to the hard reg,
  cse substitutes the pseudo into every use and the copy dies (001f2630 `f4` pinned to t0: byte-identical
  to unpinned). A pinned constant in a block that also holds call-argument moves of the same hard reg gets
  an output dependence on them, which raises the argument move's sched1 priority. An unused pinned
  declaration changes nothing. A pinned variable set before a call reads garbage after it (the set is dead).
- 0021e120: 3w -> 3w, other basin (nonmatchings/session18/s18m1__0021e120_3w.c): k66 -> $8, k68 -> $4,
  climbed with pclimb_s15 (seed 1, 1500 steps): header li order and every header register now exact.
  Left: the second func_0011fbb0 call's `move t0,zero` issues before move a2/a3 (output dep on the k66 pin,
  see above) and the old sd t1,0(s1) LUID tie. Only 68 pinned: 5w best (66 issues early again).
- 001cfc28 stays 1w: pinning 1.0 to $f1 (set at each block position), x to v0 and 29 to a1 (with and without
  the identical arms) changes nothing: the problem is the li.s's sched1 LUID, and a hard-reg set still has
  no in-block predecessor. With a dead FP test as a block split and the pin: 18-22w at 248 bytes (>10 blocks).
- 001f2630 stays 1w: pins on 0x8000 (a1), 22 (a3), f4, f4+288 over the w65 exact-order finding: 9-23w;
  climbs (gk+22 pinned 13w, gk 15w); gk pinned at every set/store pair in the 1w draft: 22w+ (the hard-reg
  set reshuffles sched1 in the glyph block).
- 001f1fc8 stays 2w: `one` pinned to a1 at all 210 set/store pairs: 200 at 2w, rest 44-60w.
- Not tried: 001eddc0 (a.r is a computed value, a pin would be dissolved) and 001fd858 (reorg).

## s18m2: 00192958 MATCHED (local register variable lever); 00265608 9 -> 7w; 00125240, 00200e28, 001c62a0 unchanged

Same lever as s18m1, applied to the five drafts it had not been tried on. Counts are true DP LCS words
(sc6_s12.py; for sceGsDefDispEnv a copy that takes the first function of the object).

| function | mode | before | after | draft |
|---|---|---|---|---|
| 00192958 | hand/nostrict | 17 (s10 w11) | **0, MATCHED** | src/hand/nostrict/text_00190000_s18_s18m2.c |
| 00265608 | sdk/gcc991111 | 9 (s9 w11) | **7** | s18m2__00265608_7w.c (drafts.tsv updated) |
| 00125240 | hand | 3 | 3 | - |
| 00200e28 | hand | 24 | 24 | - |
| 001c62a0 | hand/nostrict | 39 | 39 | - |

- **MATCH func_00192958** (`make` byte-identical, 6975 functions with the other worker's tree; objdiff 100%).
  s10 w11's 17w draft plus five pins: (1) the scissor and xyoffset TI header constants,
  `register u128 ks asm("$5"); ks = 0x17f000001ff0000ULL; *(u128 *) sc = ks;` and the same for kx in $7
  (17 -> 4: local-alloc no longer breaks the zbuf/xy/sc live-length tie by qty order; ks alone 16, zbuf
  pinned to t0 instead 23-34). (2) b[] lines in order b0, b1, b2, b3 (exhaustive order search of the 7
  lines, 350 legal orders: 4 -> 3). (3) the scy0 chain split into three pins: `e = sc->scy0;` (u64 e in a1),
  `t = e;` (s32 t in a3), `u = t << 4;` (s32 u in a1), `b[1] = oy + u;` (3 -> 0): the truncate is untied
  from its source as in the original, and the o->pos argument move into a1 waits for u's last use.
  FLAGGED (five register variables). Each is needed: without e 7w, without kx 12w, t = sc->scy0 directly 7w,
  `u + oy` 1w, u as u64 6w. Housekeeping: shift/unmatched/func_00192958.s removed by export_unmatched.py,
  its drafts.tsv line removed.
- **Correction to s18m1's rule** "a pinned computed value is dissolved": in 00192958 a pinned truncate
  (`t = e`, DI -> SI) and a pinned shift (`u = t << 4`) survive, and so do they in 00265608
  (`HH = (u64)(h - 1) << 44`): only a pinned *copy* of a value that already has a pseudo is dissolved by cse.
  A pin that is the destination of the operation itself stays.
- 00265608 9 -> 7 (gcc991111 honours local register variables the same way): H = (h-1)<<44 pinned to a3 in both
  h0!=1 blocks (`register u64 HH asm("$7");` set anywhere among magh/ox/dw: all 4 positions identical), EXPR2
  uses HH. Every register is now the original's. Left: the addiu/dsll32 pair still issues after the off[]
  loads instead of right after the div (the s11 w67 sched priority problem; a pin does not change priority
  here because there is no call in the block), and the last OR pairs H|X instead of H|W. All 1680 OR trees of
  EXPR2 with HH: floor 7. Pinning the (H|W) OR result to a3 as well breaks the h2==2/h2==3 cross-jump (37-49w).
- 00200e28 stays 24: 6 (orig t5) and the 0x7bf8001400000 constant (orig t0) are the two wrong-register header
  constants. Pins: k5 alone 25, k8 alone 67, both 72, all ten k-vars at their original registers 132.
  Moving the pinned set to every position of the header (37 positions) changes nothing: in the .sched dump the
  pinned set carries REG_DEP_OUTPUT links on every earlier call (call-clobbered register) and an anti link on
  the func_00122048 call, so it becomes ready right after that call and issues first, whatever its LUID; the
  original issues li 6 after the k4 chain. pclimb_s15 over the header with k5+k8 pinned (3000 steps): 57; with
  k5 pinned (2000 steps): 25. The leftover is sched order, not a register choice the pin can fix.
- 00125240 stays 3: the leftover is the D_004F77E0 HIGH (orig lui a1 early, ours lui v0 after p dies), and a
  HIGH cannot be pinned in C. A pinned full address `register f32 *q asm("$5") = &D_004F77E0` set in the same
  block is dissolved (output identical, 3w); set before the dead FP test it costs an addiu (184 bytes, 8w).
  p pinned to v0 (and 2790 to v1): 22w, 196 bytes (p stays live across the split, p[-1] loads change).
- 001c62a0 stays 39: the leftovers are pointer copies and loop givs, not constants. i pinned to s0 (biv): loop.c
  loses the i*224 giv (194-196w, 1176-1184 bytes); b pinned to s4: 46w (b's address is then built in s4 in the
  prologue instead of `move s4,s1` among the giv inits).
- Helpers (scratch only, not committed): an exhaustive order search between /*P*/ and /*Q*/ with the pclimb_s15
  def-use check, a position sweep of given lines, and the 1680-OR-tree sweep for sceGsDefDispEnv. Each one is
  about 40 lines on top of lro6_s12.check.
