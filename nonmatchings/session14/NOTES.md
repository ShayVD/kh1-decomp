# Session 14 notes (matching track)

## s14m: 0010d470 179 -> 170w natural / 129w finding; 00110618 stays 93w (no matches)

Counts are true DP LCS words of the original left unmatched (tools/matching/sc6_s12.py), as in
sessions 12-13. Both s12w6 baselines re-verified first: 0010d470 179, 00110618 93.

### 0010d470 (hand strict, RO=48cdf0)
- s14m__0010d470_170w_natural.c (4120 vs 3968): both case-24 byte reads split as `c = str[pos]; c -= 25;`
  and `c = sub[k]; c -= 25;` (the original loads the byte straight into c = t0). 179 -> 170.
- s14m__0010d470_129w_finding.c (3928 vs 3968, UNNATURAL): the above, plus s13's `c2 = sub[k];` in the
  copy loop (alone 253w), plus the copy-loop sc store through a byte-offset biv
  (`off = n * 16 + 16;` at `m = n`, `*(f32 *)((u8 *)b + 12 + off) = scale; off += 16;` in both arms).
- Why it works: with `n++; b->g[n - 1].sc` the preheader computes n*16 and b+12 into block-local temps,
  local-alloc gives them v0/v1, the three HIGHs (59E4, WD, 59E8) get a2/a3/a0 and the lo_sum
  invariants inherit them as preferences (WD base = a3, the s13 lever). With the off biv the
  HIGHs get v0, v1, a0 as in the original, and global-alloc then gives &D_004D59E8 = a0, c = t0,
  pos = t1, k = t2, 0x40080 = t3 exactly as the original, with c2 = a3 in the copy loop.
- Left in the probe: loop.c reduces the sc address to one giv (b+12+off); the original keeps
  t4 = b+12 as an invariant and a2 = 16n+16 as the reduced giv (`addu v0,t4,a2` per store), so WD,
  0x80000000 and &59E4 sit one register low (t4/t5/t6 vs t5/t6/t7). Also: size 40 bytes short
  (cross-jump), entry `lui a1/a2` HIGH for D_004D59E4, main-path &g[n] form (orig
  `addiu v1,a1,16; addu a0,b,v1; move v1,a0`).
- loop.c facts (dumps): the sc address forms tried all end as one reduced DEST_ADDR giv. A DEST_REG
  giv used once never roots a combination (combine_givs skips single-use DEST_REG g1), and
  `n++; b->g[n-1].sc` gives n*16 (1546) and n*16 + (b+12) (1556) DEST_REG givs that are "not worth
  while" while the address giv is reduced. The original needs the opposite: the 16n+16 giv reduced
  and the address left as invariant + giv.
- Tried, no gain (words): sc store `b->g[n].sc = scale; n++;` both arms 198, only else-arm 178,
  `b->g[n++]` 198, `b->g[m].sc` 254, `g = &b->g[n]; n++; g->sc` 301, `(b->g + n - 1)->sc` 251,
  `m = n` at the loop bottom 277-288, in the c2 variant: `(u8 *)b + 12 + n * 16` 222, `off = n * 16`
  per store 293, `&b->g[0].sc + off` 251, f32 index biv 239, glyph index biv `b->g[off].sc` 221.
  PUT/PUT_TAIL as `((TGl *)b)[n + 1]` or `(b->g + n)->` on the 129 probe: 140-155.

### 00110618 (hand strict)
- No gain. Tried: sxd shared with syd separate 147, syd shared with sxd separate 186 (s12 has both
  shared, 93); separate cz2/az2 for the second ViewScreen body 177, only cz2 175, only az2 168.
- Allocation picture (gdb, tools/matching/gdb_s13-style tracers with a find_reg FinishBreakpoint
  that prints reg_renumber; see below). Ours: local-alloc gives d f20, n f21, fa-n f22, fa chain f23,
  fb chain f24, a f25, 1.0 f26, fa*n chain f27, l chain f28, -r*n chain f29, syd*2 chain f30,
  sxd*2 chain f31; globals sxd -> f31 and syd -> f30/f29 by copy preference, cz evicts l (f28),
  az evicts 1.0 (f26), fbn evicts fb (f24).
- Inferred original: fa*n f22 is NOT tied to `fa*n * -2` (f4) or the clip az (f0) although it dies
  there, so the fa*n chain qty most likely failed local-alloc (all 12 callee-saved FP regs busy over
  its life) and its pseudos went to global-alloc separately; fb*n's chain is tied in f22. Locals by
  priority: d f20, n f21, fb*n chain f22, fa chain f23, fb chain f24, a f25, sxd*2 chain f26, fa-n f27,
  l f28, syd*2 chain f29, {-r*n, 1.0} in f30/f31; globals: sxd evicts l (f28), syd takes f29 by
  preference, cz/az evict f30/f31, fbn then gets f28 free (no conflict with sxd's two lives). Our
  order differs mainly in sxd*2 (priority .075, last) vs fa-n (.096) and 1.0 (.113).
- Not reached from source; a sched1-order search toward that local-alloc order (la3_s12/osrch_s12)
  is the next step.

### Tools
- tools/matching/gdb_s14/ga3.py + gt.sh: global-alloc trace with the hard reg each find_reg call chose
  (s13's ga2.py plus a gdb.FinishBreakpoint reading reg_renumber); gt.sh finds the repo from its own
  path. `tools/matching/gdb_s14/gt.sh $PWD/tools/matching/gdb_s14/ga3.py x.c | grep ^FR`.
- sc6_s12.py/lro6_s12.py hard-code /home/claude/kh1-decomp as ROOT: in a worktree run scratch copies
  with ROOT edited (the scratch variant runner used here was not kept; var_s11.py does the same job).
