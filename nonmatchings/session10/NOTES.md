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
## w4 (0010ed20 00169688 0010ea70 00105d88 00120cf8)
- Matched 0010ed20 (hand/nostrict): `extern s32 func_00106b18(void *);` (the matched siblings already had s32) plus a hill-climbed store order. When the call sets v0, sched2 sinks `sb v0` (the constant 1) to the end of the store group.
- 0010ea70 6 -> 2w (w4__0010ea70_2w.c): same prototype, `f32 x14 = 0.0f` (extra fwd deps make `sw x14` issue after `sb x13`). Left: sched2 issues `sh h4` (9 fwd deps) where the original has `sw x1c`.
- 00169688 4w: jump2 cross-jumping (needs `b L+4; ld v1,48(a2); nop`). Siblings func_00169008/00169210.
- 00105d88 7w: loop-2 pointer 9 refs/13 live beats counter j 7/11; needs <=7 refs or an 8th j ref.
- 00120cf8 7w: constant 3 at 10 refs/62 live vs &m[i][i] 5/19; needs 11 refs or life <=57.
- Facts: f32-typed zero fields add fwd deps in strict mode; `void *` fields get true deps on later void* stack loads.
## w8 (0024c950 0019f1f0 00110e68 001c95f8 001166e8 00214a68 001f31a8): no matches
- 0024c950 15 LCS stock (9 with 991111a gas): local-alloc ranks kk (movn counts read+write: 4 refs) above the D_00669A5C load, so kk takes v0. Making kk global gives the load v1. A `yy += kk` fold reaches 13 LCS by coincidence (not the shape).
- 00110e68 15w: global-alloc amp .57, i .41, p .30; p needs 16+ weighted refs.
- 00214a68 16 LCS: original hoists only the lui into the inner preheader; exits filled from fall-through suggest a real loop. Conflict unresolved.
- 001f31a8 17w: local-alloc, c0 word needs v1 (sd c0 early in sched1). Siblings func_001f3110/001f3dc0.
- 001c95f8 15w: separate address pseudos for x,y,z; local-alloc ties. Sibling func_001c8878.
- 0019f1f0 15 LCS: m[3][3] = 1.0f inside the cross-jumped tail breaks cross-jumping.
- 001166e8 16w: id*5 qty prio 26.7 beats element qty 25; one more element ref would flip it.
- Fact: lcs_s8.py with the assembler path swapped (ASC=compiler) measures other gas versions.
## w7 (0021e120 0010b390 001fa8b0 00249718 00152928 001eddc0 00260610): no matches
- 00249718 12 -> 3 LCS (w7__00249718_3w_samearms.c): `t2 = t * t; if (o) { X } else { X }` with identical arms (jump2 merges them after sched2, size unchanged) makes t2/t3 global: every FP register right. Left: `mul t3` issues before the four row-0 loads. Identical arms are odd source (maybe an #ifdef'd debug difference). w7__00249718_8w.c: schedule exact, t2/t3 swap f5/f6.
- 0021e120 12w: header constants 0x5000..8001 and 63 swap registers in local-alloc. Siblings func_00219598, func_0021b860: worse.
- 001fa8b0 12w: loop pass 2 hoists %hi(D_003E8E28); original keeps it local (would need 129+ real insns in the loop).
- 00260610 14w: `size` takes a0 from size+30's preference; 9 shapes, all sdk modes.
- 0010b390 12w: D needs f4; `if (o)` folded by -fdelete-null-pointer-checks after a deref.
- 001eddc0 13w: conversion result f (1.76) beats a.r (0.2) for a0.
- Facts: identical `if (c) {X} else {X}` arms survive to sched2 and are merged by jump2 at no cost: a way to make local pseudos global. loop.c pass 2 gives each hi/lo_sum load life 2; with calls the hoist threshold is ~64*life*savings vs real insns.
## w9 (00102118 001cfc28 00103c48 001ba520 001fbcd8 00166570 00199ac8): no matches
- 00102118 17 -> 6 LCS (w9__00102118_6w.c): Task2 with plain f32 fields (only Obj keeps the unions): field access through a union member gets alias set 0 and conflicted with the D_002A3E20 loads; plus `do { } while (0);` between `h->c = 0` and `h->d = 0`. Left: original has `move s0,s3` (hh copy of h surviving gcse cprop).
- 001ba520 20 -> 16w (w9__001ba520_16w.c): Lt as a plain struct aligned(8) instead of a union with u64 d[14]. Left: flags-block issue order/registers and store order w10,w4,wC,w8.
- 001cfc28 18w: the late `sw m.x` inherits the stale INSN_TICK of the func_001e98d0 call group; a do{}while(0) after it fixes the store but gives constant 29 v1.
- 00103c48 19 LCS: div temps (mflo into v1 plus a copy). 001fbcd8 20w: x2/v register choice; 160 reuse combinations. 00166570 21 LCS: block-local pa/pb gives `move s2,s0` but loses m40's address. 00199ac8 24 LCS (session8 w9 draft is the real best; session9 w8 measures 30).
- Facts: unions used for type punning make every access alias set 0: split the types and keep the union only where punning happens. A store that becomes ready inside a block inherits the stale INSN_TICK of the last call group. A gcse-surviving copy: `o2 = o` in an earlier cse1 path and a load through it after a store (cse2 makes it a move).
## w10 (0019ab38 00216890 0023a968 0010ba98 00105288 00107c48 0016ea58): no matches
- 00107c48 29 -> 25 LCS stock (w10__00107c48_25w.c, hand/nostrict, no flags): q and r computed inside `if (*p != 0)` stops strength reduction ("not every iteration") while sched1 still hoists the sll/addu: loop body exact. Left: allocation order (original allocates i first). -fno-rerun-cse-after-loop gives the original prologue (cse2 decides it).
- 0010ba98 27w (finding file 32w): `w = t->win;` after `w->cb(e, f24)` + `func_0010b6c0(w)` in case 2 fixes the cb arg order, but the final cprop then folds the top PRE copy.
- 0019ab38 24w: original's `move t4,t0` is a real RTL copy cse1/gcse missed; no shape found.
- 00216890 24w: arg order from sched2. 0023a968 25w: `P.y + h + t + 20` gives the add order but swaps the multiply chains.
- 00105288 28w: EE sched1 keeps lw;op;sw chains in source order even when they cannot alias; retyping globals changes nothing.
- 0016ea58 31w: the loop is exactly matched func_001711d0's body (three `continue` tests): probably a non-static `inline` func_001711d0 (gcc defers inline output; it sits after 0016ea58). Pasting it in gives 65 LCS (global-alloc moves). Promising direction.
- Facts: 2.96 gcse PRE runs once then one cprop; a PRE copy survives only if w or R is modified later in the same block.
## w11 (00135a68 00192958 002106b8 0012e1b0 001db718 00200e28 001f18e8)
- Matched 002106b8 (hand, rodata 0x00490e30): r2_7 draft plus a dead `n = D_003E3D68;` in the case-4 arm: gcse PRE then puts `lui s5,0x3e` in both arms as the original does (fixes size and an s4/s5 swap). Plain C dead read, flagged in the file comment.
- 00192958 34 -> 17 LCS (w11__00192958_17w.c): b[] computed b0,b2,b1,b3; `i = sc->scy0 << 4; b[1] = oy + i;` reusing the loop counter. Left: zbuf/scissor u128 constants swapped (local-alloc tie, lower qty wins), which shifts reload's rotation.
- 001f18e8 48 -> 17 LCS (w11__001f18e8_17w.c): `Glyph *gl; s32 s;` block-local per glyph block; neg block in the same order as the loop block (one macro body); `g->x40 = cx = i + s;`; pad loop `dig[n] = val % 10; val /= 10; n++;`. Left: sched1 hoists `tag = p + 5` above the second call.
- 0012e1b0 (finding, 49 LCS): `do { pretest; loop: ...; goto loop; } while (0);` makes loop.c call the loop phony: nothing hoisted, label aligned, like the original; but the pretest moves and the prologue is 16 bytes short. 001db718's loops look phony too (but D_00304BE8 must still reload each iteration).
- 00135a68 33: four address registers (addu operand order + two move copies), probably post-cse copies. 00200e28 44: one-block store flood, sched1 order.
- Facts: a dead read of a global in one arm makes PRE place its lui in both arms. loop.c skips a loop as phony when the first real insn after LOOP_BEG is not a label. Two code copies that should allocate identically should be written in identical order. `x = cx = a + b` with an otherwise unused cx stops local-alloc tying the sum to a dying operand.
## w1 (the four 0-word-only-with-a-hack functions): all four matched with plain C and stock tools
- DIntr 0025f338 (sdk/gcc991111_as296): the shape of the DIntr copy inlined into `_sbrk` (src/sdk/libkernl/kernl.c): `eie &= 0x10000; if (eie) { do { di; sync.p; mfc0 t; t &= 0x10000; } while (t); } return eie != 0;`, no `res` local. eie live after the loop keeps the lui inside it; the do-while gives the loop alignment. Its .s stand-in was removed from libkernl_asm.s.
- Tail3Draw 00191248 / Tail3XDraw 00197cf8 (hand/nostrict): a GNU C nested function `inline void t3Init(T3Key *k)` reading the enclosing `buf` through its static chain; inlined, the chain is a frame pointer copy (`move a3,sp; lw 288(a3)`), and `buf` stays in the frame. A real struct of the locals rounds the frame 292 -> 304.
- 0010a780 (hand/nostrict, CONTEXT_ONLY func_0010a550): a CONTEXT_ONLY definition of D_002B67F0 above the function. ee-as 2.96 moves the `addiu %lo` of an `la` into an empty jal slot only when the symbol is already known (defined earlier in the file, .comm before use, `.extern sym,size`, absolute). The values do not matter (zero-initialised in the repo). No assembler post-pass needed: the session 9 "original gas is not stock 2.96" conclusion was wrong; such slot differences mean data defined above the function in the original file.
- Facts: real BLKmode struct locals are rounded to 16 bytes; nested functions inlined give "ptr = sp, lw off(ptr)" reads.
## w13 (001c3b10 001bc530 001ffb30 00107548 001e1838): no matches
- 001c3b10 96 -> 8 LCS (w13__001c3b10_8w.c, hand/nostrict, right size): scan loop with two j increments (`goto hit`; j++ on both paths) stops strength reduction of msgs[j]; per-case `*d = 1`; `d = done` inside `if (n > 0)`; `w->fl.b.b0 == 1` u32 bitfield; RESTORE as the mirror of the save in text_001c0000_b10.c. Left: `x316c = t` store order (sched1 prio 1), x18-loop `and 0xffffff` vs lwc1 in sched2, `move a1,v1` placement in the scan preheader.
- 001bc530 98: global-alloc order of six min/max (orig x1,y1,z0,y0,x0,z1). 00107548 118: tail copies are word copies through `E16 *e = &w->t1[...]` (right shape, but LCS 150). 001ffb30 106: spills. 001e1838 161: byte 0 built as (base+row)+col, bytes 1-2 as base+(col+row)+k (siblings func_001e15a0, 001e06c8, flat u8 D_00F20000[] 0x600 stride).
- Facts: two increments of a counter stop reduction of a 2-insn giv; hoisted constants tie in global-alloc by creation order; a u32 bitfield `== 1` keeps `li 1; bne`. Tool: tools/matching/lchk_s10.py (in-process LCS checker, ~0.04 s per variant).
## w12 (00169f28 0024be88 001fe1b8 001fb428 00106ed0 001bd090 001c53c8)
- Matched 0024be88 (hand): list entries as a bitfield struct `{ s32 dx:4; u32 col:4; u32 row:4; u32 pad:4; s32 id:16; }` (LCS 46 -> 1: the whole loop register permutation was the type), `do { } while (0);` at the start of the `D_0046A54C != 0` else branch (found via -fno-cse-follow-jumps), store order `D_0046A544 = 0; D_0046A548 = 4; D_0046A554 = 4;`.
- 00169f28 52 -> 12w (w12__00169f28_12w.c): tail calls in an inline function (constant args go straight into $f12/$f13, no shared f20/f21), one `r0: return 0;` label for most early returns, `x130` declared s32 and cast at use (waits for the b6 bitfield store). Left: the inline's early failures `move v0,zero; b test`; best/0.1f swapped f20/f21.
- 001fb428 65 -> 54 LCS (w12__001fb428_54w.c): tail order `hdr[0]; hdr[1]; base[0];`. Left: glyph-block local-alloc (try w11's block-local Glyph/s fix from 001f18e8).
- 001fe1b8 59: `a` needs to be the parameter pseudo to prefer a0. 001bd090 74: still looks like a compiler difference (movn keeping the first store). 00106ed0 71: CSE shares q8+i*32. 001c53c8 81: the original leaves the `jal func_001c5168` slot empty after a large-offset `s.s` macro; stock gas fills it (check the w1 symbol-known rule).
- Facts: bitfield structs for packed words fix global-alloc permutations; single cse/gcse flag sweeps locate compiled-out asserts; inline functions put constant args straight into hard regs; in strict mode a COMPONENT_REF's alias set is the field's type.
## w14 (00110618 00200648 001fd858 001c62a0 00200038 001f5fe0 0010d470 001636d0)
- Matched 00200648 (hand/nostrict, LCS 177 -> 0): (a) 24-vertex flood in plain index order, fields in struct order (col,q,u,v,x,y,z,f); (b) `W = pw << 4; if (W < 832) W = 832;` (the shift keeps W spilled and gives `li a0,832; slti; movn`); (c) `t = D_003F2BD8[type]` after the colour calls, then X, Y, Y1, W, XR, X1, X2, then the tag2/regs2 stores (nostrict: o-> loads stay after earlier stores); (d) scale block nX, nY, nY1, nX1, nX2, nXR (all 720 tried).
- 00110618 167 -> 136 LCS (w14__00110618_136w_probe.c, unnatural order: a probe): separate `sxd2`/`syd2` temps pinned between calls. Left: FP registers in the prologue, fb never gets f24.
- 00200038 254: loop.c base giv (ours b+0, original b+416). 001fd858 197: needs a second pseudo for o that crosses no call (a0 still o at the first fe1b8 call). 001c62a0 242: loop.c giv choice. 001f5fe0 is 278 in hand/nofill (vs 324 hand): mode unsettled.
- Facts: sched1 never moves an insn past a call if it uses/sets a pseudo with REG_N_CALLS_CROSSED == 0 (pin temps between calls). `x << 4` vs `x * 16` change later clamps. Tool: tools/matching/hl2_s10.py (hill-climb with calls fixed, stores free within their call interval; lines need unique text).
