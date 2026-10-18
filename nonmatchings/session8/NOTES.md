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
