# Session 8 worker notes (condensed from the workers' reports)

## w1 (1-5 word list A)
- Matched 001d9268 (hand/nofill, also plain hand): strict code, not nostrict. B48 copies as `union { u64 d[6]; s32 w[12]; }`, flags `union { u64 x; s32 i[2]; }`; `f3464` is f32 (`sw zero`), which lowers its store's priority.
- Matched 00237d48 (hand/nostrict_nofill): pointer locals `p1 = &t1; p2 = &t2;`, pre-loop inits in the order pv, pn, pu, p1, p2, `i = 2`, `d = dst + 3`, loop `for (; i >= 0; i--)` (1 of 1680 orders).
- Matched 002177c8 (hand): `PN *t = D_003F40F8; s32 *tn = &t->n;` before pdc and q, then `tn[*q * 2]`.
- Near misses (w1__*.c here): 0025add8 1w (gcse copy-prop removes the `move a2,v0`; `long sema` keeps it but swaps bne operands), 00101bb8 2w (local-alloc priority tie 2 vs 2, the earlier-born `li` wins v0), 001502e8 2w (3-quantity sort), 001e32d8 2w (global-alloc .0759 vs .0750).
- Facts:
  - With exactly 3 block-local quantities local-alloc sorts by fixed exchanges of quantity numbers (0/1, 1/2, 0/1), so the result can be out of priority order; 4+ get a real sort, ties to the earlier-born.
  - local-alloc ties an input to the output only for a plain register operand; a pointer inside a MEM address never ties to the loaded value.
  - In a call's cycle sched1 issues the lowest-LUID insn the call made ready (new ready insns are appended unsorted): source position right after the call decides.
  - A "nostrict" near miss can be strict code with union-of-s32 field types: try plain hand with unions.
  - 991111a gcse copy propagation removes plain register copies; a surviving `move` means a non-copy op or a copy whose source/dest is set again in the block.
  - `-dS -fsched-verbose=5` shows sched1 priorities and the issue table; `-dl` gives global-alloc refs and live lengths.

## w3 (reorg trio and 4w ties)
- No matches. Near misses: w3__0010ed20_4w.c (hand/nostrict: every register right now, only the x10/x13/x4/xc store order from sched1 left), w3__00142e30_8w.c (nostrict_nogcse + CONTEXT_ONLY func_00142cf0: only z/d callee-saved swap; cause below).
- 001e0ab0/0d98/10f8: reorg fill_eager steals `li v0,4` from the bgtz fall-through whenever v0 is dead at the target; only a surviving label between sw and li, a volatile/asm insn, or v0 live at the target stops it. __builtin_expect, goto tails, -g variants: no.
- 001e3a00: sched1 picks the then-branch move on priority (7 vs 4), not LUID; the original scheduled the else move first.
- 0020b6a8: sched2 tie-break goes to the insn with more forward dependences; stores with an extra anti dependence sink late.
- 00169688: right size with rr.py; ours cross-jumps to the tail at 0x169870, original 0x169ef8, and keeps case 10 as `b; ld v1,48(a2); nop`.
- Facts: pass order jump2 (27) after sched2 (25), dbr 29. A pseudo whose REG_EQUAL constant becomes REG_EQUIV in update_equiv_regs gets its live length doubled for global-alloc priority (00142e30: `z = 0.0f` 8/49 -> 8/76, below d). sched1 interblock priorities are computed per block.

## w2 (1-5 word list B)
- Matched 0011ab88 (hand): one function-level `s32 m;` takes the masked VU0 flags in two blocks (`m = vsubflags(...) & 0xe0; if (m != 0xe0) goto one;`), so m goes to global-alloc and the asm output no longer wins v0 through a tie.
- Matched 001ea268 (hand): one counter for the copy loop (`dst[len + i] = src[i]`, `dst[i + len] = 0`); the smaller loop body pushes the dst+len invariant over loop.c's pass-1 hoist threshold.
- Matched 0025c0f8 fio ioctl (sdk/gcc991111): header of text_00250000_s7_w23.c (volatile D_0046AE58, CONTEXT_ONLY func_0025ad68/0025b218) fixes the slot search; the 1 kept in s5 is a local `one = 1` CSE'd into the case-1 compare, kept alive by `if (one) D_0066C744 = arg;` (artificial but plain C, same family as `two = 2` in 0010a5d0).
- Near misses: w2__00246ed8_101w.c (one instruction short: original's `addiu v0,s3,48; move s5,v0` gcse PRE copy), w2__0025f338_3w.c (DIntr; needs an asm `.p2align 3`, hack-adjacent; mfc0/mask registers swapped in the loop).
- Stuck: 001e6038 (sched1: `return 4` v0 set must come after insn 25), 001f2630/001f1fc8 (store-order source orders flip allocation), 0024bce8 (exact global-alloc tie, 3 refs / 56 insns each).
- Facts: a tied local-alloc pair adds refs (floor_log2(n1+n2)*(n1+n2)/len), so it usually beats a short constant; an entry-block constant in an s-register used only in a compare is a CSE'd local `x = K` that needs another use to survive delete_trivially_dead_insns; `-fsched-verbose=4 -dS` prints each cycle's ready list in rank order (last is issued next); checkfile runs in ~0.2 s.

## w5 (8-15 word drafts)
- Matched 001aab98 (hand/nostrict, rodata 0x48fe30): typed destination pointers declared once at function level and reused across six loops (lower global-alloc priority than the per-block sums).
- Matched 001f0148 (hand, jtbl 0x4909c0): each case label gets its own copy of `s += n; break;` (see the loop-depth fact below).
- Matched 002287f8 (hand): `k = D_00643720[D_006436D0]; switch (k)`, k reused so cur^k wins v1.
- Matched 00110ce0 (hand): colour packed by `static inline void mk(u64 *o, ...)` called as `mk(&D_002BC9B0, ...)`; needs an unused `s32 unused[4];` for the 32-byte frame.
- Matched 0024ddf8 (hand, rodata 0x4919d8): `for (i = 0; memcmp("SLPS", p = s + i, 4) != 0; i++);` with `i = 0` after the calls.
- Matched 00249618 (hand/nogcse): `Seg3 *out = dst;` param copy, inner loop `p->v[j]` / `&out->s[j]`, increments `i++, p++, out++`.
- Near misses: w5__0021b4c8_8w.c, w5__0011b220_9w.c (REG_EQUIV fp+16 halves &n's priority), w5__001b9f78_10w.c (giv inherits a0 preference), w5__00177488_18w.c (session-7 9w draft still closer).
- Stuck: 001c99a8/001c95f8 FP local-alloc exact ties; 001fe1b8 is really 124 raw words off (580 vs 588 bytes).
- Facts: every back edge to a loop header counts as a nested loop in 2.96 flow, so a switch dispatch inside a loop gets loop_depth = number of latches and refs are weighted depth+1; splitting merged case labels adds latches (jump2 re-merges the bodies). Copying a param into a local shortens its live length. sched1 prefers an argument copy that kills its source (INSN_REG_WEIGHT) before LUID. A test-at-top `for` keeps hoisted invariants after the pre-header calls.
- Tool: tools/matching/hill_s8.py (dependency-respecting hill-climb over /*P*/../*Q*/ lines with checkfile, or rr.py with `RO FUNC`; set WDIR; the first marker must be inside the target function).

## w6 (11-16 word drafts)
- Matched 0013a440 (hand/nostrict): parameter order `(Ea4 *o, s32 *w, f32 range, s32 lv)`; the f32 entry copy now comes before lv's, so lv's live length is 40 not 41 and its priority (0.250) beats buf (0.2474).
- Matched 002384e0 (hand/nostrict): `u32 srca` parameter cast to `Ent70 *` inside (no alias base, so the lq stays after the stack stores); t[0][3], t[1][3], t[2][3] zeroed in that order.
- Matched 001df9c0 (hand, strict): plain struct `VM { s32 x0; Sub s; }`, not a union with a u8 array; `vm->s.sp = i - 4`.
- Matched 001effc0 (hand, jtbl 0x490960): w5's separate case bodies trick.
- Near miss w6__00152928_13w.c (finding: gcse PRE makes the `move a1,a2` copy but the second copy-prop round removes it).
- Stuck: 0016bb68/0016bfe8 (global-alloc t 0.75 > arr 0.52 > e 0.19), 00110e68 (p needs priority over amp/i), 00266380 (buf needs one more weight-1 ref; jump2 merges four of the five rest computations), 001cd2d8 (REG_EQUIV constant moved next to its use wins v0), 00249718 (FP: 1.0f hoisted by sched1), 0010c720 (sched2 prologue around the barrier; reorg liveness).
- Facts: an f32 parameter's position changes the entry-copy order and so integer params' live lengths. An integer param cast to a pointer has no alias base: its loads stay ordered after stack-local stores. A union containing a u8 array gets char's alias set and conflicts with everything even in strict mode. update_equiv_regs moves a single-use constant set next to its use only across blocks. sched1 checks INSN_REG_WEIGHT before LUID. rr.py needs `--out-dir` under the repo (src/<mode>/.WTAG_rr).

## w4 (6-12 word drafts)
- Matched 001aa0e0 (hand): `s32 sceGsSetDefLoadImage(...)` instead of void. In sched2 a call takes an anti-dependence on the last setter of every register not set since; a callee that sets v0 removes those, the forward-dependence counts change, and the LUID tie-break puts `lw cbp` first.
- Matched sceDbcCreateSocket 002682a8 (sdk/gcc991111): receive buffer as `{ s32 w[5]; u8 name[16]; s32 ret; void *a; void *b; }`, params 2-3 `void *` (pointer stores do not alias the s32 cfg loads).
- Matched sceCdInit 0026a250 (sdk/gcc991111, also gcc991111_as296): init block 640, 638, 648, 644, `64C = -1`, `63C = -1`, `634 = 0`, `650++` last; the case-5 exit as `goto out;` to a shared `out: return r;`.
- Near misses: w4__001ca0f8_8w.c (local-alloc order and sched2 LUID tie want opposite source orders), w4__001cf960_7w.c (sched1: `ld flags` priority 9 loses to `sd m(0)`; needs 13+).
- Stuck (global-alloc): 00212cc0 (sel between lim 2162 and cnt 2222), 00115758 (exact tie 2188), 00120cf8 (constant 3 needs 11 refs or life <= 56); 00113e28 (sched1 interblock hoist of `a1 = D+2`), 00125240 (local-alloc FP), 0010ea70 (sched1 `sw x14` of $0 ranked late).
- Facts: sched ties go priority, then forward-dependence count, then LUID (`-fsched-verbose=5` region table; 991111a spells it `-fsched-verbose-5`). `goto out` to a shared return moves `move v0,sN` into the `b` slot via reorg, removing a v0 anti-dep. `void *` fields do not alias s32 under strict aliasing. Fixing local-alloc by statement order can break a sched2 LUID tie the other way: check both passes.

## w7 (17-22 word drafts)
- Matched 001124f8 (hand): func_001ed170 takes one argument (`s32 func_001ed170(s32)`, called with D_002C1380); the draft had it void(void).
- Matched 00233168 (hand, rodata 0x491350): case 7 as a goto loop with the index in a local (`k = q->n; goto t7; i7: k = q->n + 1; q->n = k; if (k >= 99) goto done; t7: if (!q->flag[k]) goto i7;`).
- Near miss w7__00176c60_16w.c (all registers right; b3/b2 address add order and a reload_cse copy left).
- Stuck: 00149c80 (global-alloc tie 0.403 vs 0.414), 001cfc28 (x load latency; a `do {} while (0)` hack helps), 00219598 (s-register constants come from register pressure, hoisted by sched2), 001fa8b0, 00214a68, 00116368; no new lead on 001f31a8, 001ba520, 001fbcd8, 0021e120, 0010b390.
- Facts: check every callee's arity against its asm (tools/matching/arity_s8.py lists the argument registers a function reads first). cse_around_loop replaces a field reload in a rotated loop test with the latch's stored value: a goto loop testing at the bottom keeps the reload. sched2 hoists constants that got s-registers under pressure to the function start. `do {} while (0)` makes a phony loop with no invariant motion. rr.py --diff prints original on the left, checkfile -v ours first.
- Tools: tools/matching/dump_s8.py SRC [flags] (dumps under $WDIR/d with the file's mode flags), rtl_s8.py (one line per insn view of a dump).

## w8 (25-35 word drafts)
- Matched 001d63e8 (hand): plain `VM { s32 x0; Sub s; }` struct (w6's), `D.n--` written in both arms of `k < D.n`, `k = i + 1;` in both arms of the key compare.
- Matched 00232e08 (hand): one variable reused for both byte-swapped halves (`q = a / 10 + 0x824f; q = ((q & 0xff) << 8) | (q >> 8); D.xda = q; q = a % 10 + 0x824f; ...`).
- Near misses: w8__00105d88_7w.c (was 33w; globals as pointers to one-field structs get hoisted; loop 2 counter/p swap left), w8__001eddc0_13w.c (was 27w), w8__00260610_15w.c (was 25w), w8__001137f8_22w.c (was 27w).
- 0010a780: our jump2 merges two `lo_sum` sets into one `la t2` (nop in the jal slot); the original split it back into `lui; addiu` after jump2 and dbr filled the slot. Points at a split pass between jump2 and dbr in the original compiler, which would also explain func_00171078. Not fixable from source.
- 0025b2f0: every save at priority 12; looks like a compiler difference.
- 00166570: the original recomputes m40[0]/m80[0] after the loop; something keeps gcse from treating them as available. Not found.
- Facts: a value set before a compare written in both arms moves after the branch in RTL and still lands in the delay slot. One variable reused through temp -> store chains serialises them in sched1. In strict mode an `s32 *` global is reloaded every iteration when the loop stores s32; a pointer to a one-field struct is hoisted. `for (i = 0; n != 0; n--, i++)` counts on n with no copy. Four or-ed shifted terms in one expression are regrouped by combine: build in separate statements.

## w9 (large functions A)
- Matched 0022eef8 (hand): generic variables reused across blocks: the item id `D_00646A0C[D_00646A14]` in `idx` (the list loop's variable), the func_001ee708 result and the later `a0->x90` in `id`; `D_00304BE8->items[idx]` instead of a byte offset.
- Matched 00106000 (hand, jtbl 0x48cc80): rgba inline computes `w = r | 1<<32` before `v = b<<16 | g<<8`; the else store via a block-local `u64 *q = &D_002A6658; *q = rgba(&D_002BC070);` in both branches; case 2 order `w=; D[4]=; D[6]=; x=; y=; D[22]=; D[23]=`.
- Near misses: w9__00199ac8_24w.c, w9__0019ab38_24w.c (hand/nostrict_nofill; `k = 0` just before the while loop), w9__00103c48_19w.c (loop index renames fix the packet loop; div/div1 order left), w9__00107c48_29w.c (right size; loop.c strength-reduces i*16, original recomputes it).
- Stuck: 00219f98 (row blocks need `addu a1,k8,base; move v1,a1`; every form gives a `la` macro), 002040f8 (really 19w by LCS), 00202678 (really 7w: one sched1 decision, o->xb4 load priority 5).
- Facts: count large drafts by LCS (tools/matching/lcs_s8.py). One register where two variables seem used means a reused generic name. Brute-force loop index names over all loops. Of two divisions in a row the first gets div1. Statement order inside a static inline decides sched for every caller. A `&sym[k]` pointer is a `la` macro; split lui/addiu/addu needs address legitimization or a separate symbol value. Declaration order of unused locals matters.
- Tools: tools/matching/lcs_s8.py (checkfile with LCS word diff), prio_s8.py (global-alloc priorities from -dl/-dg), cc_s8.py (compile with a mode's flags, dumps in $WDIR/d).

## w10 (callee-prototype sweep over all 130 remaining drafts; 40w set)
- Matched 0016bb68 and 0016bfe8 (hand/nostrict, one file): func_00157a30 takes 3 args `(ObjB *, s32, void *)` (e already in a2), and `if (t != 0 && (EntB *)o != t && e == t) func_00157a30(o, 26, e);`.
- Matched sceGsSyncPath 00265bc0 (sdk/gcc991111_as296): `void scePrintf(...)` (51w -> 21w), each timeout path written out as `scePrintf(msg); DUMP(); return -1;` with DUMP a plain-brace macro of the 10 register prints, `r = 0; if (R(0x10009000) & 0x100) r = 1;`, the VU1 status in one function-level `u32 st` from a `cfc2 %0,$vi29` asm without a register-asm variable.
- Matched 00246ed8 (hand/nostrict, CONTEXT_ONLY 00246cf0/00246ea8): one `Item *it;` reused (`it = &p->unk30; f(a, it); it = &p->unkF0; f(a, it);` and in the draw loop), which keeps the gcse PRE copy alive.
- Sweep drops without a match: 001c62a0 256->243 (`void memcpy`), 001166e8 843->837, 001c2ec8 270->269, 00191248 314->313, 001636d0 817->816 (s32 callees: see the w10 drafts' notes in the report); 00260610 25->23 (already in w8's draft).
- Near miss w10__001cb440_25w.c (was 41w; prologue and all cases match; 768 vs 756 bytes: needs the shared `(k*176 + &D) + off` base and reload_cse copy chain).
- Stuck: 00166248 (rerun-loop givs always init after pass-1 givs), 00135a68 (copy-chain mechanism), 0024c950 (global-alloc: col prefers t1), 00192958.
- Facts: `move a3,a1; move a2,a3; move v0,a2` copy chains come from separate address expressions with the constant inside the index (`s->stk[i - k]`) that combine reassociates and post-reload cse turns into copies; if cse2 relates the addresses first the chain does not form. A pointer local reassigned to several `&p->field` values (or a dead `it = 0;`) keeps a gcse PRE copy alive. A register-asm cfc2 output ties the andi to that register; a plain variable does not. An extra argument register set before a jal means a missing argument. sigs.tsv arity is unreliable for the VU0/sce helpers.

## w12 (large functions C: GS packet builders and near misses)
- Matched 002040f8 (hand/nostrict): in the first scaled branch `y` is declared block-local (`s32 y = o->xb4 + o->c0 + (s32)(sinf(...) * -384.0f);`); the else keeps the function-level y. Try this on the other 0x1ff488-0x2040f8 builders.
- Same drafts with the cause in the first line: w12__00202678_7w.c (o->xb4/c0 loads must be issued before the a/100 divmod in sched1; sched2 keeps them after the spill store), w12__00199ac8_24w.c (fix_truncsfsi2 scratch clobber orders the a0/a1 copies), w12__00103c48_19w.c (div expansion `tmp = div; trap_if; dx = tmp`; dy's temp ties to the dying 2048 constant), w12__00105d88_7w.c (j needs an 8th ref to beat p).
- Stuck: 001ff488 (X's live range needs ~44 insns), 00199ac8 'same' reload (inheritance breaks only at a label or call: the original seems to have a label before `same > 0`), 001ffb30/00200648/00200e28 not reached.
- Facts: in sched2 arg-based loads stay after sp-based spill stores. A divmod feeding another div gets sched1 priority ~38, unused in its block 1. fix_truncsfsi2's reload-chosen GPR scratch adds output deps in sched2. Tool: tools/matching/sbs_s8.py SRC ADDR [lo hi] (LCS-aligned side by side).

## w11 (large functions B)
- Matched 001a7c50 (hand/nostrict, was 134w): the tail reuses function-level `i`/`head` (`i = o->n34; head = o->b36;`); each update of the spilled `fl` its own compound statement (`fl |= 0x40; fl &= 0xf7ff;`); separate early returns instead of `||`; `fl & 0x20` passed straight as the argument; `if (++head == size) {head = 0; v = base;} else v++;`; `a->c->f3c` read directly; list insert through `struct Lnk *ln = &no->link;`; `f = rnd * a->c->f3c; f += prev->f1c;`.
- Matched pppRyjDrawKekotoDraw 001a12f0 (hand/nostrict, was 50w): `{ KkShape *sh = D_00615E64->shapes + key->id; th = sh->tex; }`, tx before kkPush, header order found by hill-climb; kkSqrt is a sqrt.s inline asm wrapped in `.set noreorder` (as in text_00110000_s6_04.c).
- Near misses: w11__0018f268_47w.c (was 94w, right size), w11__001cc640_89w.c (hand strict, jtbl 0x4905F0, right size 1432).
- Stuck: 001c3b10 (loop.c strength-reduces msgs[j]; original keeps `sll 5`), 00197cf8 Tail3XDraw (`move a3,sp; lw 288(a3)` needs a locals-struct pointer CSE does not fold back; 16-byte aggregate padding grows the frame).
- Facts: reload hands out spill registers round-robin (last_spill_reg), so fixing the first reload difference fixes later blocks. Compound statements on a spilled variable give in-place reloads. `if (a || b) return` can inherit a reload across the branch; separate ifs reload. A loop invariant written as a call argument is hoisted after the loop-entry test. `andi 0xff` before a compare: a wider variable converted to u8 (`u8 m = mode`). `T *p = arr + idx;` gives (plus base off), indexing inside an address (plus off base), which decides the tied input. `-dL` "giv of insn N not worth while": reduced when lifetime*threshold*benefit >= loop insns.

## w14 (GS packet builders, re-measured by LCS)
- No matches. LCS counts (position count): 001ffb30 178 (226), 00200648 200 (240), 00200e28 103 (322), 00200038 254 (326), 001fd858 197 (452; 1952 vs 1908 bytes), 001fbcd8 17 (20, nostrict_nogcse), 001fa8b0 12 (17, nostrict_nogcse), 001f31a8 17, 001f18e8 115 (134). All right size except 001fd858.
- w14__001fa8b0_12w.c: loop pass 2 hoists D_003E8E28's lui; sched1 issues its load in cycle 0 beside `c-32`, so the address chain gets v0. The original loads it after the `lhu D_003E8D40[c-32]`.
- 001fbcd8: one `v` for both the sign block and the digit loop gets closest (t0 needs priority < 0.36). 001f31a8: the c0 bitfield `sd` must come early. 00200648: w12's block-local trick does not carry over. 001ffb30/00200e28/00200038 are single-block floods (sched1 store schedule only); 00208458 not attempted.
- Facts: loop.c threshold here is ~63: a single-saving movable is hoisted when 63 x lifetime >= loop insns. Deleted-insn notes count in lifetimes, so pass 2 hoists far more high parts. Unread counters are deleted before loop.c. The r5900 issues two per cycle: a load with no dependences goes in cycle 0 whatever its priority; delaying it needs a dependence.

## w15 (Tail3 and VU0 giants)
- Matched pppKeMdlDttDraw 0018f268 (hand/nostrict, from w11's 47w draft): in nostrict code every load/store order between stack and pointer accesses is the source order, so read the statements off the asm: `buf->test = w.test;` before `buf->test_a = 6;`, `r = w.scissor;` before `buf->clamp_a = 8;`, `flag = w.flag;` before `buf->cache = w.cache;`, then-block `w.use = 1; w.cache = *w0->u.p; w.rd = mode & 8;`, setup `mode, mtx0, mtx1, colA, pkt, colB, shape, flag, scale, verts`.
- Near misses: w15__001166e8_491w.c (LCS 169, was 235; strict, plain hand; function-level `f32 best = 1000000.0f` reused; size 4144 vs 4136, reload takes a3 as a third spill register), w15__00191248_282w.c (t3Col as a do-while macro; w11's draft is closer by LCS: keep both).
- Stuck: 00191248/00197cf8 (the `move a3,sp; lw 288(a3)` reads need buf at offset 288 of a locals struct passed to a static inline, which rounds to 304 bytes and moves the spill slots), 001636d0 (LCS 414) not worked.
- Facts: sbs_s8.py only finds func_ names (match `.f_<NAME>` for named functions). A 3-statement block falls under the 3-quantity sort: try all 6 orders. With -fcaller-saves a call-crossing pseudo gets a call-clobbered register only if refs > 4 x calls. Reload's spill register set is fixed at the first reload. A long-lived float constant in $f20 across an early call is a function-level variable set at the top and reused.

## w13 (40-100 word drafts, re-measured by LCS)
- No matches. Near miss w13__001c5ee8_11w.c (was 67w, right size): `D_003C5500 = *(s32 *)&D_0037A380.ent[256] + 1;` gives the reload_cse `move t0,a0; addiu`; tail copies through an inline copying a 16-byte union `{f32 f[4]; Ent *p[4];}`; left: global-alloc order at loop init (7w with -fno-expensive-optimizations, a probe only).
- Stuck: sceSifCallRpc 0025a560 2w (sched1 INSN_REG_WEIGHT orders arg, id, pkt; original needs pkt < id < end), 0023a968 39w (local-alloc of the x*22 chains), 001ca368 LCS 23 (gcse PRE reuses `f+f`), 0016ea58 LCS 71 (hoisted const-2 at loop depth 4 from three `continue`s; func_001711d0 has the same code and matches in src/hand/nostrict/text_00160000_h60.c), 00237b30 LCS 63 (giv rejected: biv k has 2 increments). LCS of the rest: 00105288 37, 001fb428 65, 00265608 47, 00169f28 64 (size off by 8).
- Facts: re-reading an address through a different expression makes reload_cse emit `move` + `addiu`. A union with pointer members creates sched deps against pointer stores. sched1 ranks INSN_REG_WEIGHT before dependence counts and sched2 inherits the order through LUID ties. Each `continue` adds a loop-test copy at deeper loop depth (raises refs of constants hoisted there). loop.c does not reduce dst+k*16 when biv k has two increments. -fno-expensive-optimizations is a useful probe for global-alloc ties.

## w16 (untouched mid-large set)
- Matched 0017b668 (hand, also nostrict): param copied into a local (`s32 i = start;`) reorders the entry copies.
- Matched 001519c0 (hand/nostrict, jtbl 0x48e4c0): function-level `s32 e` set twice (`e = D_00351530[k].h`, later `e = D_0054F958.xc`), uses written `(u16)e >> 4` and `(e & 0xffff) >> 4`.
- Near misses: w16__001db718_40w.c (right size), w16__0010ba98_41w.c (776 vs 760).
- Stuck: 0012e1b0 and 00106ed0 (loop.c hoists `li 1` and an addiu the original keeps in the loop), 001bd090 (late if-converted store: maybe a compiler difference); 00216890, 0024be88, 001c62a0 not reached.
- Facts: a function-level s32 set twice (second time a full 32-bit value) keeps each block's `andi 0xffff`; mixing `(u16)e` and `(e & 0xffff)` stops gcse merging them. The original's `move aN,aM` copies of a reloaded pointer are gcse PRE copies: write the field read again, not the local. Goto loops avoid loop.c hoisting. Byte arrays as struct arrays indexed `[j + K]` keep j+K as one index.

## w17 (biggest functions)
- No matches. Near misses: w17__001166e8_67w.c (strict hand, rr.py 0048D090: 67w, was 487; 4128 vs 4136; left: local-alloc v0/v1 in both hit tests, tail `ep = idx + D` index first and a best1 reload), w17__001f5fe0_324w.c (LCS 324, 8416 vs 8488, rodata 490c70; scale pairs as `o->x74 = o->x78 = LERP(...)` after the x90 store; then-block tails cross-jump into a shared tail at 0x1f80d8).
- Stuck: 00219f98 (`addu a1,idx,base; move v1,a1` comes from base + (idx+4): combine makes (idx+base)+4 and reload_cse turns the second add into a move; only an unnatural index reproduced it), 001636d0 (LCS 414: cse1 replaces j with i; pp gets REG_EQUIV fp+16 so it is never spilled), 0010d470 (LCS 430, 4088 vs 3968: gcse load PRE keeps the address-taken pos in a register).
- Facts: a bitfield load has its own alias set and moves above s32 stores; reading through `union { u32 w; u8 c[4]; }` keeps it after. `((x>>15)&1)==1` folds to bnez; assign the bit to a variable to keep `li 1; bne`. A pointer whose every set is the same frame address gets REG_EQUIV and is never spilled. `a = b = expr;` fixes store and register order of a pair. `return a|b` vs `b|a` gives different operand orders.

## w18 (second look at the closest near misses)
- Matched 0025add8 (sdk/gcc991111, rodata 004922D0): w1's draft with `int sema` and `i = sema = r.sema = -r.sema;` before `for (i = 0; ...)`. The dead set of i keeps gcse cprop from deleting the `move a2,v0` copy (artificial, same family as `one = 1`).
- Matched 0020b6a8 (hand): packet word [37] written through `typedef union { u64 ul; s32 i[2]; } W64;` as `((W64 *)p)[18].i[1] = y + 0x7310;` (gives it a sched2 dependence on the later `sd buf[0]`, so LUID decides), tail order by hill_s8.
- Near miss w18__001e3a00_3w.c (func_00231b98 takes no arguments; left: `li 1` issues before `addiu s0` in sched1).
- Corrections: 00101bb8 is not a local-alloc tie (the const-1 quantity does not overlap the idx*160 chain; the original issued `li 1` later in sched1). 0010ed20 needs the `li 1` born late in sched1.
- Still stuck: 001502e8, 001e32d8, 0025a560, 001e6038, 001f2630, 0024bce8, 001f1fc8, 00202678, 00105d88, 001c5ee8.
- Facts: a dead set of another variable from a copy in the same block keeps a gcse copy alive. In strict mode a store through a u64/s32[2] union gets output deps on later u64 stores in sched2, which equalises dependence counts. Stores with the same base register and known offsets never conflict whatever the alias sets. In a call's cycle an interblock-hoisted insn takes the slot. In sched1 a pseudo set that does not cross a call gets an anti-dependence on the last call. arity_s8: func_00231b98 and func_001220b8 read no arguments; func_00260590 does not read a0.
