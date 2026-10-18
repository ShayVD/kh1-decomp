# Session 9 worker notes (condensed from the workers' reports)

## w2 (00166248 001e3a00 001e6038 001f2630 0025f338)
- Matched 001e3a00 (hand): plain sibling-style source, `void func_00231b98(void)`, `void func_0010bd90`; same global expr D_0062F810 in both branches gets hoisted by gcse (fixes sched1 li 1 vs addiu s0).
- Matched 001e6038 (hand): plain globals, no p/q pointer locals; `if (D_003DD284 == 0) return 4; if (--D_003DD288 < 0) { D_003DD284 = 0; ...; return 4; } return 0;`.
- DIntr 0025f338 (sdk/gcc991111_as296) reaches 0 words only with `__asm__ volatile(".p2align 3")` before the loop label: kept as near miss (hack). eie at function level, `res = eie != 0;` inside `if (eie)`, loop mfc0 in a block-local.
- Stuck 001f2630 3w (hand/nofill): x2c store needs a source position after x14 (sched1: reg weight, fwd-dep count, LUID), but moving it changes the first "Spilling for insn" reload register for the whole function.
- Stuck 00166248: loop.c giv init order; original's j-loop test giv is a pass-1 giv, ours rerun.
- Facts: try sibling style (plain globals like matched neighbours) before dumps. The first insn that needs a spill reg (-dg "Spilling for insn N") fixes the reload reg for the function; big jumps after a small reorder usually mean this. sched2 store tie-break: fwd-dep count, then sched1 order.
## w6 (0010c720 00152928 001fa8b0 00249718 00266380 001eddc0 00110e68 001c95f8 00260610)
- Matched 0010c720 (hand): CONTEXT_ONLY func_0010c410 and func_0010c5c8 above (each fixes reorg beqz/beqzl in one switch tree), param `s32 a` used as `(u64)a << 24`, no do-while barrier.
- Matched sceGsExecStoreImage 00266380 (sdk/gcc991111_as296, rodata jtbl 0x492d70): cases 0,2,19,20 do `x = w*hh >> N; x = x - full - part; goto calc;` sharing `calc: rest = x - 1;` (cuts rest's refs so buf ranks above it).
- Near misses with diagnoses: 00152928 13w (gcse PRE copy needs CPROP2 to see p set on a path), 001fa8b0 12w (local-alloc puts c-32 chain in v0; sched2 zero-cost anti-dep), 00249718 12w (1.0f const issued early in sched1), 00260610 15w (sched1 prio tie size+15 vs li -1), 001c95f8 15w (LUID tie on 3 FP loads).
- Stuck: 001eddc0 13w (fixuns result set in 2 blocks -> global), 00110e68 15w (p prio .30 vs .57/.41).
- Facts: s32 param as `(u64)a << N` keeps dsll out of sched2 cycle 0. Shared `goto calc` tail recomputing only the final var cuts its refs. sched2 issues a zero-cost anti-dependent insn in the same cycle. A dead division leaves its trap_if, a memory barrier in sched1. wqb03_rr.py works unmodified with --file and --out-dir src/<mode>.
## w10 (large A)
- Matched 002376c8 (hand/nostrict_nofill, CONTEXT_ONLY func_00237680): `p = 0; if (k == 2) p = &n->pos; else if (k == 3) p = &n->pos; else if (k == 1) { V4 *t = &n->pos; p = t; }` (two-insn arm blocks if-conversion at jump1; arm order picks which tests become movz).
- LCS before -> after: 0024c950 29->15, 0010ba98 35->27, 0023a968 36->25, 00105288 37->35, 001edfb8 20, 00135a68 33, 001db718 40, 00192958 43, 00169f28 52.
- 0024c950: abs()/N in its own temp; end-section k reuses `col` (a1 copy preference). Left: v0/a0 swap, unfilled slot + align nop before else.
- 0010ba98: `t->dy = t->dx = 1.0f / n;` without an f local fixes f0/f1 of five divides. Left: gcse copy of t->win folded by cprop2.
- 0023a968: `a[k]*22` in its own var t. Left: original adds (p.y + h) first.
- 00105288: loop 1 loads b before q (s3/s4).
- Stuck: 001edfb8 (sched1 prio 15 vs 14), 00135a68 (cse1 merges v+i*16; copies maybe from reload splitting), 001db718, 00192958 (TImode const local-alloc order).
- Facts: if an arg reg looks wrongly preferred, a later call passing the same var in another slot + reusing one variable gives the copy preference. Reordering statements in one basic block often changes nothing: change expression shape. `do {} while (0)` around an else arm gives an aligned label but stops cse1 after it.
## w5 (00113e28 00125240 0021b4c8 0011b220 00177488 001b9f78 001c99a8 001fe1b8 001c5ee8)
- Matched 00113e28 (hand, CONTEXT_ONLY func_00113df8): printf takes only the format (D_0048D010 has no %d); tail `if (++D_004D9328 != 0) return; D_004D9328++; printf(D_0048D010);`.
- Matched 0021b4c8 (hand): `c = 256; ... D_00643108 = c;` then hill_s8 statement order.
- Near miss 00177488 4w (2 by LCS; hand/nostrict): func_00118608 takes one argument. Left: `lim = 20.0f` must issue between the a1/a0 argument copies in a one-block sched1 region.
- Stuck: 00125240 8w (FP local-alloc 1e4 vs x), 001c99a8 10w (load order), 0011b220 9w, 001b9f78 9w (global-alloc: e beats i for a0), 001c5ee8 11w (global-alloc refs at loop setup), 001fe1b8 65 LCS.
- Facts: read printf format strings before adding args. Labels after a barrier get `.p2align 3,,7`: a nop after b/j is padding. A constant through a local moves its li in sched1. `*(volatile s32 *)&D` probes whether a value is reloaded. Run arity_s8 on "obvious" callees too.
## w9 (00217000 0010a780 00171078 00166570 001ff488 00102118 0019f1f0 00107c48 00219f98)
- Matched 00171078 (hand): `return ((s32 *)0x35BD40)[*b ^ 3];` hard-coded address; gas expands the large offset and fills the jr slot with the relocation-free tail. Not a compiler difference. (Portability: absolute address to replace in phase 4.)
- 0010a780: 0 words only with an assembler post-pass (pp_la.py moves a `%lo` la tail into an unfilled jal slot): a real toolchain/assembler difference; no installed gas does it. Near miss 0w_asmpp (stock 8 LCS). Binary has zero `lui;addiu;jal;nop`.
- 00107c48: 23 LCS with hand/nostrict_nogcse + -fno-strength-reduce (loop body exact; only register order left).
- Stuck: 00217000 8 LCS (la split into lui/addiu in sched2, as 0x212cc0/0x2134c8), 0019f1f0 15 (reorg own_thread_p: needs a used label after bltz), 00102118 17 (cse across u32 conversion join), 00219f98 32 (combine operand order base+k8), 001ff488 20 (store flood), 00166570 21 (pa/pb copies).
- Facts: `lui;addu;lw;jr` with the lw in the slot = hard-coded address + index. Stock gas moves a macro's last insn into an empty slot only without a relocation. sched1: insns made ready together after a call issue in reverse source order. reorg fills a non-likely branch from the fall-through only when no used label follows.
## w7 (001166e8 00176c60 001cd2d8 001f31a8 00219598 001cfc28 00103c48 001ba520 001fbcd8)
- Matched 001cd2d8 (hand/nofill): rewritten after matched sibling func_001d5b58 (Msg2 `u32 val:24` aligned(8), constant `m.type = 2`, stores type,val,v[0],x,v[1],v[2],v[3]=179.99998f, dead `d = f*180/pi; if (d<0.0) d=-d; g=d;` tail), plus `vm->f60 = 0; vm->f64 = 0;` before `vm->sp -= 4;`.
- Matched 00219598 (hand/nostrict): copy of sibling func_0020b3d8 (`u64 *p = buf + 2`, p[0..15] in index order, `q = (s32 *)p`, q[32..47]).
- Matched 00176c60 (hand): `extern u8 D_002C5AD0[][112]` and `D_002C5AD0[i][2] = D_002C5AD0[i][3] = 0;`.
- Stuck: 001cfc28 18w (sched1 stale INSN_TICK in a 6-block region; -fno-sched-interblock fixes the block but merges a tail), 001166e8 16w (id*5 pair 20 refs vs 25), 00103c48 19w, 001ba520 20w (struct needs aligned(8)), 001f31a8 17w, 001fbcd8 20w (not attempted).
- Facts: grep matched src/ for siblings (same globals/callees/message type) before hand-tuning: 2 of 3 matches were ports. Chained `a = b = v` computes a's address, then b's, stores b then a. `u8 X[][112]` gives off+base addu; struct field form gives base+off. In a multi-block sched1 region an insn made ready later inherits INSN_TICK from earlier blocks. do{}while(0) does not raise loop ref weights.
## w3 (0010ed20 00169688 001e0ab0 001e0d98 001e10f8 001f1fc8 0024bce8)
- Matched 0024bce8 (hand): drop `x0 = x; y0 = y;` copies, re-read `*px`/`*py` in the final tests (gcse copy pseudos numbered after the loop's -10 pseudo win the exact global-alloc tie).
- 00169688 4w (hand/nostrict, rodata 0048E870): case 13 as `Tail(o, w);` makes jump2 merge returns like the original; left: case 10's two-copy cross-jump blocked by the sibling pass's `(use (const_int 0))` after a block-ending call.
- 001e0ab0/0d98/10f8: reorg steal of `li v0,4` blocked only if the fall-through is not owned (live label), v0 live at target start, or find_basic_block -1; no plain-C shape found. Not the 991111 compilers. Static `&&label` remains the only 0w form (near miss).
- 0010ed20: one-block local-alloc; sched1 issues `li 1` at cycle 2 (LUID tie with call-arg lui). 001f1fc8: w32's 5w draft stays best.
- Facts: re-reading a pointer arg instead of a local copy gives a late gcse copy pseudo (global-alloc tie lever). jump2: a jump preceded by a label needs one matching insn and the first jump_chain candidate (the last jump to the label) wins.
## w1 (00101bb8 00142e30 001502e8 001e32d8 0025a560)
- Matched 00142e30 (hand; also nostrict/nogcse): CONTEXT_ONLY func_00142cf0 and func_00142c80 above; no `r` return local: `goto end` from the x70/flags tests to one `end: return d;`, plain `return -1.0f;`/`return z;` elsewhere (d's refs 4->3, z wins f21).
- 001502e8: new 6w near miss (one shared `void *q` for case 0's x130 and the dispatch a->x144 pointer); 2w draft stands (local-alloc 3-qty fixed-exchange sort).
- Stuck: 00101bb8 2w (sched1 li 1 at t=0 before sll), 001e32d8 2w (REG_EQUIV live doubling: pD needs +3 insns of life), 0025a560 2w (gcc991111 INSN_REG_WEIGHT; 2304 variants).
- Facts: a return through a shared label with 3+ uses keeps its mov f0 copy. REG_EQUIV constants' live lengths are doubled (even). global-alloc pass 0 avoids a reg preferred by a conflicting pseudo. prio_s8.py needs the source path first.
## w8 (0021e120 0010b390 001137f8 00116368 00149c80 00214a68 00199ac8 0019ab38)
- Matched 00116368 (hand): session-6 w6_02 draft with the inline helper `each` written out; both id loops share function-level `s32 id; s32 *fl;`.
- Matched 00149c80 (hand/nostrict): func_001477c8's result in its own local before the sprintf.
- Near misses: 0010b390 22->12w (function-level f32 W in branches 2-4; left: anim branch int-to-float f2 vs f3), 00199ac8 32->24 LCS (`k = 0` just before the while loop; left: `same` reload into t3, arg move order, f2/f3, gcse const-prop drops `move t4,t0`).
- Stuck: 001137f8 22w (local-alloc of prologue his and 1<<32), 0021e120 20w (four header constants rotate), 00214a68 22w (only the lui hoisted in the inner loop), 0019ab38 not attempted (twin of 00199ac8: start from the k change).
- Facts: a function-level variable shared by two written-out loops becomes a global pseudo. A call result in its own local extends other live ranges. Moving `= 0` next to its loop raises a counter's priority over hoisted constants. Step 0 (prototypes) gave nothing on this list; func_00106b18 is void; arity_s8 misses func_001220b8's a0.
## w4 (0025b2f0 00105d88 00115758 00120cf8 001ca0f8 001cf960 00202678 00212cc0 0010ea70)
- Matched 00115758 (hand): `b->cz = (maxz + minz) * 0.5f`; init `miny = 1e6; maxy = -1e6; maxx = maxy; minx = miny; maxz = maxy; minz = minx;`; `b->top = maxy;` after b->cz.
- Matched 001ca0f8 (hand): `D_00389C90.f3070` as `union { u64 x; u32 i[2]; }` then hill_s8 over the tail (union alone went 8w -> 33w).
- Near miss 0010ea70 6w: chain `B->x30 = B->x34 = B->x70 = B->x74 = O->x18`; left: sched2 fwd-dep tie on `sw x14`.
- Stuck: 0025b2f0 6w (prologue sd s1/s0 LUID tie in sched2; same in every 991111 mode: likely compiler difference), 00105d88 7w, 00120cf8 7w (hoisted const 3 seems from a later loop pass), 001cf960 7w; 00202678, 00212cc0 not reached.
- Facts: cse turns `a = x; b = x;` into `b = a`: keep same-source copies apart. cse's canonical reg becomes the newer copy when its last use is later. sched2 issues insns ready in the same cycle lowest-LUID first. A u64 field as union{u64; u32[2]} makes its sd alias later s32 loads.
## w13 (large D; LCS before -> after)
- No matches. 00191248 Tail3Draw 76->40, 0012e1b0 85->46, 002106b8 163->76, 001c53c8 150->81, 00107548 196->118, 0010d470 430->338 (same session-6 draft measured in plain hand), 001fd858 197, 00200038 254, 001f5fe0 324, 001636d0 414.
- 00191248: T3CPY as plain-brace macro, `extern const f32 D_0048FB68`, `r = 1.0f - r*key->rs; tmp[0] = size*r`. 002106b8: branch store orders found by full permutation (rodata 00490e30). 00107548: `k = j*4` declared first (spill slot order).
- Stuck: 001fd858 (a0 = o alive to the first call), 00200038 (loop.c base giv choice: original rebases on q0+416), 001f5fe0 (jump2 cross-jump direction for x74/x78 tails), 001636d0.
- Facts: re-measure old drafts in every mode. Spill slots follow declaration order. `b = &D->field; p = b + i*4` gives (base+off)+idx; `&D[i].field` gives (base+idx)+off. jump2 cross-jumping walks the jump chain latest-first.
## w11 (large B; LCS before -> after)
- Matched 001ca368 and 001ca0f8 together (hand, one file): `D_00389C90.f3070.b37 = 0` with `struct { u64 lo:37, b37:1, hi:26; } f3070;` (a union with s32[2] is too strong), `dur[k] = n * 2.0f` at each use (no f local: gcse PRE reuses f+f), `3.1415928f`, hill-climbed tail store orders. (w4 matched 001ca0f8 separately with the union + hill climb; the w11 file was kept.)
- 00265608 sceGsDefDispEnv 47->9 (sdk/gcc991111; OR-tree shapes brute-forced, 1680 trees of 5 leaves), 00237b30 63->24 (three `dst[k++]` per inner iteration make k a biv), 00106ed0 103->71 (`G = arr; G[i].c = 0` clear loop; `c = 1; c <<= (s32)t;` keeps li in the loop), 00200e28 103->44 (prologue exact), 001c3b10 104->96.
- Stuck: 0016ea58 52 (global-alloc: hoisted const 2 prio .130 needs ~.09), 001fb428 65, 001bd090 77 (original uses a movn noce if-conversion keeping the earlier store; ours never: likely compiler difference), 001f18e8 115 (val 1.76 beats p 1.53).
- Facts: gcc 2.9x reassociates OR chains: brute-force OR trees with a toy compile. Loop reversal happens only when the counter only counts. loop.c keeps a constant in the loop if its register is set twice there. `-dl` .lreg "used N times across M insns" gives global-alloc priorities directly. Helpers: /tmp/claude-0/s9/w11/bin (not kept).
## w12 (large C; LCS before -> after)
- 00197cf8 Tail3XDraw reaches 0 words only with a frame-overlay inline `t3Init((T3Loc *) m0, key)` that reads other locals through a struct cast of the first local (undefined behaviour, depends on the frame layout, would break on any other target): filed as a near miss (w12__00197cf8_0w_frameoverlay.c), not counted. Other changes in it are real: T3CPY without do-while(0) (its LOOP note blocks sched1), loads `base, rnd, dur, nfr`, `r = 1.0f - r*key->rs`, `w = obj+off+0xA0` before the alloc call.
- 001c2ec8 165->2 (hand): r&8 block ends in `break` with `done = 1; D &= ~8; do { D &= ~4; } while (0);`, separate scan pointer, forward init loops, `i = e->lbl[0]; e->pc = i;`. Left: lw e->lbl[0] issued before two hoisted luis (t0 vs a0).
- 001bc530 151->98, 00216890 96->62, 001ffb30 155->127, 00200648 200->177 (movz vs movn clamp), 00110618 175->167. Stuck: 0024be88 119, 001e1838 161, 001c62a0 242.
- Facts: do{}while(0) inside an if-block ending in break stops find_and_verify_loops moving the exit block out of the loop. A forward init loop reversed by loop.c changes the outer insn count and so which constants the rerun pass hoists. An expression repeated inline in both branches makes gcse PRE create the original's move copies. REG_N_REFS weights loop refs x2. sched2 moves FP divides across calls when their regs are callee-saved. cse-follow-jumps needs a BARRIER before the target label.
## r2_3 (round 2: 00249718 001eddc0 00110e68 001c95f8 00260610 001166e8 001f31a8 001cfc28 00103c48 001ba520 001fbcd8)
- No matches. 00260610 15->14w (`if (n > 0) { i = n; dst = buf; do ... }`; left: size takes a0 from size+30). 00249718 12w and 001c95f8 15w rewritten in sibling style, same counts.
- 00249718: the original's FP regs are exactly what gcc gives when t2/t3 live across a basic-block boundary (`if (D_X) D_X = 0;` after t3 reproduces every register): the original source had a boundary at flow1 that leaves no code. No plain-C boundary found that survives without blocking scheduling.
- Stuck: 001ba520 20w (sched1: ~nw prio 26 beats t = nw & ~old 25), 001fbcd8 20w (x2 in different regs per block in the original), 001166e8 16w, 00110e68 15w (sibling port worse), 001cfc28 18w, 00103c48 20w, 001f31a8 17w, 001eddc0 13w.
- Facts: wqb03_rr.py --diff left column is the original; sbs_s8.py left is ours. sched2 loads from the un-copied base first, so final load order hides sched1's. EE sched1 issues at most 2 insns per cycle.
## r2_1 (round 2: 00101bb8 001502e8 001e32d8 0025a560 00166248 001f2630 00125240 0011b220 001b9f78 001c99a8 001c5ee8)
- Matched 001e32d8 (hand): pointer inits in order pA=&D_003F7A68, pB, pC, pD; both early branches share one tail `*pA = one; dz: *pD = 0;` via `goto dz` (pD 8 refs -> 7 crosses a floor_log2 step, drops below pC).
- 00166248 4 LCS (s6 while-loop draft): only reorg differs (our entry test becomes bltzl; original bltz with `move s1,zero` in the slot).
- 001c99a8 10w: source order Z,Y,X gives the original FP regs; reload_cse keeps the first-scheduled copy of the repeated sp*4 add.
- Stuck: 00101bb8 2w (real prototypes func_00101970(s32, DmaHdr*, s32), func_00101a18(Tex*, u8, Q*)), 001502e8 2w, 0025a560 2w, 001f2630 3w, 00125240 8w, 0011b220 9w (f would need 4 refs), 001b9f78 9w, 001c5ee8 11w (refs from loop.c inits).
- Facts: a shared goto tail can cut a tied pseudo's refs across a floor_log2 step. A sched1 store whose value dies at it (weight -1) beats a weight-0 store whatever the source order. An unlikely branch can still become branch-likely when fall-through regs look live at the target.
## r2_5 (round 2, large A + 6-30w; LCS before -> after)
- Matched 00219f98 (hand, rodata 0x490f20, CONTEXT_ONLY func_00219380): flat `extern s32 D_003F4C68[], D_003F4C78[]` read as `[k*2]` and `[k*2+1]`, p0 before p1 (reload_cse turns the second add into a move).
- Matched 001edfb8 (hand): sibling port of func_001f86e0's GS packet tail (src/hand/text_001f0000_s6_17.c): `Q {u64 a,b;}`, `p = func_00122048(1024,128); buf = p; p = buf + 1;`, uncached ub pointer, `func_0011fb38(64, packed, p+1)` returning the end pointer. Look for this packet idiom in other 0x1e/0x1f near misses.
- 00105288 35->28 (func_00115d18 is `void(void)`; `D_002A6284 = (s32)h + h[16]; func_00115d18();`), 00192958 43->34 (`j = o->b8D + 1;` reusing the loop counter j), 0024c950 15 (9 at the right size with the 991111a assembler), 0023a968 25.
- Stuck: 0019f1f0 15, 00107c48 29, 0010ba98 27, 00135a68 33, 001db718 40, 00169f28 52.
- Facts: reusing an existing long-lived local (a loop counter) for a short temp changes global-alloc order; a fresh local does not. The original assembler does not move the addu of `la rd,K(rs)` into a b slot (binary has `lui;ori;addu;b;nop`, never `ori;b;addu`); 991111a gas behaves like this but is worse elsewhere, so the original gas is neither. In 2.96 jump2 runs after sched2.
## r2_4 (round 2: 0019ab38 00199ac8 0021e120 0010b390 001137f8 00214a68 00217000 00166570 001ff488 00102118)
- Matched 001ff488 (hand/nostrict): threw away the hill-climbed store order; vertex flood in plain index order v[0]..v[23], fields u,v,x,y,z,f per vertex, each corner coordinate computed just before its first use, header and tag2/regs2 before the flood.
- Near misses: 00214a68 22->16 (inner goto loop with explicit `u8 *p`, `s32 i`; `s32 *cnt = D_00642C78;` before the outer loop), 0021e120 14->12 LCS (LCS-scored hill-climb of the header).
- Stuck: 0019ab38/00199ac8 (cse1 folds `du = k` to 0; the `same` reload needs a label at reload time), 0010b390 12w, 001137f8 11, 00217000 8, 00102118 17 (cse2 load-to-copy needs a followable join), 00166570 21.
- Facts: a long-hill-climbed store order can be a local optimum: try plain index order first. A lui hoisted into an inner preheader with addiu/addu left in the loop means a goto loop plus gcse PRE of the high part. LCS hill-climb helper hl.py (tools/matching/hl_s9.py).
## r2_2 (round 2: 0010ed20 00169688 001e0ab0 001e0d98 001e10f8 001f1fc8 00177488 001fe1b8 00152928 001fa8b0)
- Matched 00177488 (hand/nostrict): w5's 4w draft plus a compiled-out assert after the join call: `#define ASSERT(x) do { } while (0)`, `lim = 20.0f; func_002675a8(out, a); ASSERT(hit); goto test;`.
- 001fe1b8 65 -> 59 LCS, right size (588): reuse one generic local for v then lim (combine loses the zero-extension: `li -16; and` and the nop come back). Left: o/a argument registers.
- Stuck: 0010ed20 4w, 001e0ab0/0d98/10f8 4w (likely the original's bgtz target label was not a BLOCK_HEAD, so find_basic_block returns -1), 00169688 4w, 001f1fc8 5w (sched2 groups stores by fwd-dep count first), 00152928, 001fa8b0.
- Facts: `do { } while (0)` right after a call starts a new block, so gcse's hoisted setups go there and the call's sched1 priority drops. jump2 does not cross-jump a block ending in a fall-through call (sibling pass USE). hill_s8.py bugs: rr form is `FILE MODE ITERS SEED ADDR FUNC`; its validity check counts struct field names as variables (rename such locals).
## r2_6 (round 2, large B; LCS before -> after)
- Matched 00237b30 (hand/nostrict_nofill, CONTEXT_ONLY func_002378c8): one function-level `i` for both loops (outranks the dst giv), header `((u64 *)h)[0]` before `[1]`, `pn = o->nrm[j];` after `dst[k++] = o->col[j];`.
- 001c2ec8 2->1 (`fn = D_0037A198;` before a plain `e->pc = e->lbl[0];`; left: hoisted lui 0x2c LUID tie). 0012e1b0 46->39 (0x20 case `goto one;` into the 0x40 case). 0016ea58 52->31 (search loop `if (!inl_ok2(p)) continue;` with a bool helper: 2 latches).
- 00191248 Tail3Draw also reaches 0 only with w12's frame-overlay inline (r2_6__00191248_0w_frameoverlay.c): not counted. A real `T3Loc L;` local gives the a3 reads but BLKmode locals round to 16 bytes (304, spill slots move); the original's a3 base is a pseudo equal to &m0 with buf a scalar at 288.
- Stuck: 00265608 9 (each div's trap_if is a full sched1 barrier; original issues H first), 00200e28 44.
- Facts: each edge into a rotated loop's test block is a separate natural loop; every `continue` raises hoisted constants' refs. An empty do{}while(0) before the loop test collapses skip edges into one latch. Merging two loops' counters into one function-level variable changes its rank against givs.
## r2_7 (round 2, large C/D; LCS before -> after)
- No matches. 00216890 62->24 (case order 4/(0,default)/5; switch result in the same `w` as the later width for the a3 preference; `y = 57` after the func_001ff488 call; `s32 func_001f9438`), 002106b8 76->38 (case 5 `goto` into a shared `D_00641224 = 0; break;`; empty `case 2: break;` in the inner switch), 0024be88 119->58 (reuse `col = x + 127`, `row = row*32 + 156` so the hoisted li 7 loses s8).
- Unchanged: 00106ed0 71, 001c53c8 81, 001c3b10 96 (loop.c reduces msgs[j]), 001bc530 98, 00110618 167.
- Facts: writing a second value into an existing variable changes which pseudos win s-registers against hoisted constants. loop.c `life` counts NOTE_INSN_BASIC_BLOCK notes. Case body order sets the loop.c movable order. An empty `case N: break;` reproduces the dispatch-tree shape. Reload picks spill regs round-robin. `if (A) ... else if (B)` reloads B's global; `if (!A && B)` reuses the earlier load.
