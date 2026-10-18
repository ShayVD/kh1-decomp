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
