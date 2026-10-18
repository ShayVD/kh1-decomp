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
