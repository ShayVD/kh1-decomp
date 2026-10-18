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
