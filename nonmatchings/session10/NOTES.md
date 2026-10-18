# Session 10 worker notes (condensed from the workers' reports)

## w3 (001e0ab0 001e0d98 001e10f8 001f1fc8 00166248): no matches
- Twins 001e0ab0/0d98/10f8 4w: reorg fill_eager steals `li v0,4` into the bgtz slot; original leaves nop there and puts li in the `b` slot. ~12 control-flow shapes, static inline helper, 990721/991111a/991111-01: all steal. Sibling func_001e08d8 only covers the draw body (already exact).
- 001f1fc8 5w: sched2 glyph-packet store order (orig d0,col,x3c,x44,x54,x58,x20,x24,x38,one,x30,d1,x40,x34,x5c,x50). Sibling func_001f0868 order 9w; original order as source 22w; hill-climbed best stays.
- 00166248 LCS 4: entry bltz becomes bltzl because our first giv init is `move s5,zero`; original's is `move s1,zero`. Needs the j-loop test giv to be a loop.c pass-1 giv (not rerun). No sibling with this loop shape.
- Facts: adjacent used labels merge before flow2 (a jump2-deleted BLOCK_HEAD can't come from plain labels). The original fills a slot with a register set again only in a later call's delay slot, so reorg's live scan seems to run past filled calls. checkfile.py is slow (>2 min) under load; iterate with cc_s8.py/lcs_s8.py.
## w2 (001c2ec8 00101bb8 001502e8 0025a560 001f2630): no matches
- 001c2ec8 1w: sched1 tie in the pre-loop block between lw e->lbl[0] and the hoisted lui 0x2c (equal priority, weight, class, fwd deps); lw wins on LUID since loop.c puts movables after it. Explicit `fl = &D_002C5958` is merged by gcse (111w); nogcse breaks the frame.
- 00101bb8 2w: nostrict makes the prev store a dependence of the x->n lhu, so `li 1` gets priority 6 and takes v0. const on struct/field/pointer does nothing in 2.96 nostrict. Original's two separate `li 1` may be one constant pseudo reloaded per use (unconfirmed).
- 001502e8 2w: local-alloc order (C must lose to Q and N); block boundary or reusing p/r/t: worse.
- 0025a560 sceSifCallRpc 2w: sibling port to sceSifBindRpc/func_0025a138 100w; all 24 orders of the four cd stores, best 2w; any first store with a ready value fills the beqz slot (bnezl). Original's first insn must be the earg stack reload.
- 001f2630 3w: siblings func_001f0ea8/001f12c0 hill-climb to 3w. Original x2c store likely had weight 0 (0x8000 still live after it): look for a pseudo live past the store.
- Tools: tools/matching/mchk_s10.py (check many files after one warm init, ~0.2 s each), hcf_s10.py (in-process statement hill-climb over /*P*/../*Q*/).
## w5 (001cf960 00202678 00212cc0 00217000 00125240 0011b220): no matches
- 0011b220 9 -> 7w (w5__0011b220_7w.c): loop-2 `f` reuses dead `hd` (`hd = (u16 *)&rec[id].f`, `((RFlg *)hd)->type`) puts &n in s2. Left: merged hd+f pseudo takes s4, list1 giv s3 (swapped).
- 001cf960 7w: sched1, `ld flags` prio 9 loses the 2nd slot at t=12 to the v[2] cvt (prio 12 via store-v[1] -> load-pos[2] alias chain). Siblings func_001d14f0, func_001ce750/ce880; 4 modes; u64 vs union.
- 00202678 7 LCS: divmod a/100 issues at t=33 with a+ce; xb4/c0 loads (prio 5) land after it. Sibling func_00202300 (flat p[k]/q[k]) not yet ported: try it.
- 00212cc0 7w: global-alloc, `sel` needs 4 refs/37 live or 5/46 (has 3/47); sharing partners all wrong.
- 00125240 8w: local-alloc, 1e4 needs a ~6x shorter life than x to get f0; 1,500 random orders, none beat 8.
- 00217000 8 LCS: not really attempted (split la, move t2,v0 in a slot, li order after func_00170dd8).
- Facts: a loop-local pointer can reuse a dead earlier variable of another type to change global-alloc slots. EE 2-issue width is often the binding sched1 limit.
## w6 (001b9f78 00265608 001c99a8 001c5ee8 001137f8 0025b2f0)
- Matched 0025b2f0 (sdk/gcc991111): D_0066DAC0 is the Hook `{ void (*func)(int); int arg; }` that func_0025b2c0 takes, not `Pair {int a, b}`. Different alias sets drop the sched2 store-store dependence, so `sd s0` outranks `sd s1`. Not a compiler difference after all.
- 001b9f78 9 -> 3w (w6__001b9f78_3w.c): `func_001be820(&D_006202A0, 0xF70); p = &D_006202A0;` (removes p's a0 preference), loop 2 as `if (n) { i = 0; do ... while (++i < n); }`. Left: original has `move a0,zero` in the beqz slot from before the branch.
- 001c99a8 10w (w6__001c99a8_10w.c): order X,Y,Z with `* 3.1415928f / 180.0f` fixes the add order; loads then issue x,y,z, original needs z,x,y. All 1260 orders swept.
- 00265608 9w: off[] loads ready at t=2 prio 10/9 vs 7 for H; trap_if is only a memory barrier.
- 001c5ee8 11w: hoisted &ent[0].lk has 5 refs, needs 7 (a third use in the loop).
- 001137f8 11 LCS: one sched1 block with calls; prologue order from load priorities.
- Facts: real struct types for globals (fn pointer + int) change alias sets and remove store-store deps; a giv set from `p + 4` where p dies inherits p's call-arg preference; `if (n) { i = 0; do..while }` shortens the counter's life by two insns vs for.
