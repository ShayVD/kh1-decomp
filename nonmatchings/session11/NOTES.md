# Session 11 worker notes (condensed from the workers' reports)

## s11w1 (001c3b10 001c2ec8 001cf960 001c99a8 001c5ee8 001c95f8): 5 matches
- 001c2ec8 (hand): `extern s32 D_002C5950[]; fl = &D_002C5950[2];` for the loop's D_002C5958: a
  different RTL address `(const (plus D_002C5950 8))`, so gcse does not share it with the top
  `D_002C5958 |= 0xc`. Also 0w: `&D_002C5950 + 2`, `&D_002C5910[4][2]`, a struct with `.fl` at +8.
  A cast of D_002C5958 itself keeps the symbol_ref (20w).
- 001c3b10 (hand, strict; was measured in nostrict): x18-loop message fields stored straight from
  `w` in struct order.
- 001cf960 (hand): VM flags at 0x328 as `u64 b0:1, b1:1, rest:62;` directly in the struct.
- 001c99a8 (hand, CONTEXT_ONLY func_001c6890): Cam punning union -> u64 bitfields in Cam.
- 001c95f8 (hand): dur0 at +4 sits inside the flags word, so the union stays; store through
  `{ f32 *p = &D_003C5510.u.s.dur0; *p = d; }`.
- 001c5ee8 11 LCS (w1__001c5ee8_11w.c): identical two-store arms `if (p) lk_init(..) else lk_init(..)`
  lift lk 5 -> 9 refs (B, i*224, lk right); needs 7-8 refs exactly or i >= 10.
- Facts: a u64 bitfield store gets the containing struct's alias set; one-store identical arms
  merge before register allocation (no refs gained), two-store arms survive to jump2.

## s11w4 (001502e8 001b9f78 00169688 00169f28 0019f1f0 00152928 001ba520 00192958): 2 matches
- 001b9f78 (hand): loop 2 reads `D_006202A0.n` / `.e[i].id` directly, no `p = &D_006202A0` local
  (its a0 preference put `i = 0` after the test).
- 00169f28 (hand, rodata 0x48E8E0): each 0.1f `continue` test as identical arms on live `p`:
  `{ f32 a = v; if (p) { if (0.1f < a) continue; } else { if (0.1f < a) continue; } }`: refs on
  the hoisted 0.1f only, so it beats `best` for f20. Other conditions reorder integer priorities.
  D_0048E8D4 (0x7fffffff) is part of 00169f28's own rodata (a static const read as f32).
- 001502e8 2w: local-alloc 3-quantity exchange (needs pri(Q) > pri(C), all block-local); ~10 shapes.
- 00169688 really 4w (LCS 20 = the same 4 words shifting targets): case 10's
  `b L+4; ld v1,48(a2); nop`; probably a block reorg deleted after redirecting into it. 20 shapes.
- 0019f1f0 7 (nostrict, rodata 0x48fcb0): `li s0,2` bltz slot, func_002672f8 arg move order,
  late m[3][3] = 1.0f store. 00152928 9 (nostrict; the stub gain was hand-only): gcse PRE copy.
  001ba520 15: 288 flag-block orders, sibling decls. 00192958 17: TImode constant tie.
- Facts: `do { } while (0)` does not loop-weight REG_N_REFS; plain-global access over a pointer
  local again (sibling-port lesson).

## s11w3 (00101bb8 00120cf8 00102118 00105d88 0011b220 00125240 001137f8 0010b390 00110e68): 1 match
- 00101bb8 (hand, strict; older drafts were nostrict): `Tex` without a u16 member (`u32 n:16`
  bitfield, `u32 spd:16`), so reading n no longer depends on the u16 prev/frame stores; the
  func_0015ed80 object uses 00102118's `union { f32; void * }` fields (alias set 0 keeps loads
  after the h->a/h->b stores); callee prototypes take `void *`.
- 00120cf8 5 (w3__00120cf8_5w.c): &m[i][i] .526 vs divisor constant 3 .484 in global-alloc.
- 00102118 6: `move s0,s3` copy of h after the u32 conversion (cse2 blocked by the branch).
- 00105d88 7: reversed counter j (7/11) loses to giv p (9/13). 0011b220 7: f2 must rank below
  &n2 (w3__0011b220_9w_finding.c). 00125240 8: FP local-alloc, 1e4 life too long (300 orders).
- 001137f8 11: prologue load order (colour words must stay separate symbols). 0010b390 12: branch
  1's conversion in f3 (something holds f2 in the original). 00110e68 14: p needs ~16 refs.
- Facts: a bitfield read gets the containing struct's alias set (no u16 member = no conflict
  with u16 stores); a packed `struct { u32 v:16; }` cast is a quick probe for alias theories;
  an invariant placed after a giv init in the preheader was hoisted by loop pass 2.

## s11w2 (001e0ab0/0d98/10f8 001f1fc8 001f2630 001eddc0 001fb428 001fa8b0 001f31a8 001f18e8): 1 match
- 001f31a8 (hand, rodata 0x490af0): block-1 store order with `c0 = 0` right after the u40 stores
  (c0 word in v1), the two 1.0f stores after `x70 = 1`, block 2 `x90 = 128; state = 1; x94 = 0;`
  after x88, and the fill loop as a count-UP `for (j = 0; j < 16; j++) p->xdc[j] = 64;` (loop.c
  reverses it into the binary's 15..0 count-down, with `li 64` before `li 15`).
- 001eddc0 8 LCS (w2__001eddc0_8w.c): struct params copied `b = b0; a = a0;` (b first) gives the
  original's param-store order; left: conversion temp f (1.76) takes a0.
- 001e0ab0 twins 4w: reorg steal_delay_list_from_fallthrough takes `li v0,4`; only a live label
  between bgtz and sw (fall-through not owned) or v0 live at the target stops it. `&&label` dead
  local does not keep the label.
- 001f1fc8 4w, 001f2630 3-4w: sched2 store order sorts by dependent count (3 for call-clobbered
  registers the call does not set, 2 for v0/s-regs), ties by sched1 order.
- Not attempted: 001fb428, 001fa8b0, 001f18e8 (17w: `tag = p + 5` after the 2nd call: no gain).
- Tools: tools/matching/lc_s11.py (LCS count), ld_s11.py (aligned diff), hc_s11.py (in-process
  hill-climb, ~0.3 s per variant); RO env for rodata, one reused temp dir.

## s11w5 (0025a560 00249718 00202678 00217000 0024c950 00265608 0021e120 00260610 00214a68): 1 match
- sceSifCallRpc 0025a560 (sdk/gcc991111): client fields pkt, end, arg as `volatile u32`; read
  `int id = pk->id;` first, then store arg, pkt, id, end. Volatile orders a store only against
  other volatile accesses, so the plain id store lands between pkt and end. sema/server must not
  be volatile.
- 00214a68 16 -> 8 LCS (w5__00214a68_8w.c): inner counter as `s32 *cnt = &D_00642C74[1];`
  (middle-of-symbol pointer, s11w1's trick) stops gcse sharing the la. Left: loop.c hoists cnt's
  lui out of the outer loop; i>=48 exit beqzl vs beqz.
- 00260610 14 -> 4 LCS (w5__00260610_4w.c, sdk/gcc991111): reuse `n` as the handler index in both
  branches. Left: `size` gets a0 from size+30's preference.
- 00217000 9 (finding file): `off = sel * 20; cd = D_00642CD8 * 4;` before the identical arms
  fixes the `move t2,v0`; tbl/off then swap v0/a0. Best stays s7 w29's 8.
- 00249718 3: all split points, per-arm t2/t3, preloads: global-alloc t3 above t2.
- 00202678 7 (sched1 2-issue, loads prio 5), 0024c950 9 (kk vs load in local-alloc),
  0021e120 12, 00265608 9 (OR tree H chain): no change.

## s11w9 (001fb428 001fa8b0 001f18e8 001ffb30 001fe1b8): 1 match
- 001fb428 (hand/nostrict_nogcse): `t = w*sz/18` as one function-level variable for the neg block
  and the digit loop (a global pseudo, so local-alloc cannot tie it to `x0 + t`); neg block
  declares only `Glyph *g;`, the loop `Glyph *g; s32 x1;` (10 -> 3), then a neg-block hill-climb.
- 001f18e8 16 (w9__001f18e8_16w.c): neg-block climb (`g->x4c = 0` after `g->x40 = cx = i + s`).
  Left: prologue order, `tag = p + 5` hoisted above the 2nd call, `lhu f2` before `sw x34`.
- 001fa8b0 12: loop pass 2 hoists %hi(D_003E8E28) (life 3 counts the deleted lo_sum note);
  sibling func_001f12c0 keeps its la local in v0.
- 001fe1b8 59: find_reg pass 0 skips a0 for `a` because o prefers it; cse canonicalises param
  loads through the longer-lived copy o and combine folds the param copy.
- 001ffb30 31: the 0x0fff0000 lui still issues before `p = buf + 16` (reload gives it v0).
- Facts: after sched1 interblock speculation life info is recomputed, so a variable whose only
  use moved into one block becomes local-alloc's.

## s11w8 (0019ab38 00216890 0023a968 00199ac8 00200e28): no matches
- 0023a968 23 -> 22 LCS (w8__0023a968_22w.c, hand, CONTEXT_ONLY func_0023a720 stub, RO 4914a0):
  case 3 as `if (p.y + h + t >= 349)` (h chain v1, t chain v0); the original also has
  `addiu v0,v1,20`, and putting `+ 20` back swaps the chains.
- 0019ab38 / 00199ac8: the s8 w9 drafts are 22 with rodata placed. Finding files (28): `k = 0;`
  right after `d = seg - same;` gives the original's bgtz + `move t0,zero` slot; then cse1 folds
  `du = k` (the original keeps `move t4,t0`, the ref k needs to beat the hoisted 0x80000000).
  Also: an extra `lw 4184(sp)` reload of `same`, db vs 0.0f f2/f3, a fix_truncsfsi2 scratch
  reload putting the a1 arg move first.
- 00216890 24: sched2 argument-order tie at the first func_001f9438 call (21 variants).
- 00200e28 30: not seriously attempted (nostrict single-block flood).
- Facts: read global-alloc priority straight off .lreg "used R times across L insns"; a reload
  scratch register adds an output dep that reorders argument moves (check "Reloads for insn").

## s11w7 (00103c48 0010ba98 00107c48 00105288 00166570): 1 match
- 00103c48 (hand): z loop with accumulators `a += dy` / `b += dx` instead of `j*dy` / `m*dx`
  (19 -> 11), reusing `i` as the row counter (-> 2), table value read before `sc` (-> 0).
  gcse cprop never propagates a copy into a mult insn, so `dy = tmp; j * dy` kept the copy and the
  divide temp went `mflo v0; move t6,v0`; with an add use it is folded and gets `mflo t6`.
- 00107c48 25 -> 19 LCS (w7__00107c48_19w.c, hand/nostrict, no flags): `s32 func_00107c48(s32 i)
  { Ent16 *arg = (Ent16 *)i; ... for (i = 0; ...)` (param reused as counter) gives the original
  prologue's `move a1,a0` slot. Left: i ends in a2 (the i*16 temp takes a0 in local-alloc).
- 0010ba98 21: cprop pass 2 folds the PRE copy of t->win. 00105288 28: local optimum (4000 moves).
  00166570 21: original recomputes sp+64/sp+128 after the loop; `move s6,s2; move s2,s0` missing.

## s11w10 (00260610 001f2630 001f1fc8 001e0ab0 twins 00214a68 0019f1f0): 1 match
- 00260610 (sdk/gcc991111): one variable `n` for everything: `n = pkt[0]; if (n == 0) return 0;
  n = (n + 15) / 16;`, the copy count, then the handler index; no separate `size` local (it no
  longer inherits a0 from size+30's preference).
- 0019f1f0 finding (w10__0019f1f0_23w_finding.c): case 0 jumps to the shared s->idx[...] load and
  the m[3][3] 1.0f li.s sits in that block: `id = s->idx[...]; goto tl;` reproduces the merge
  point; then the idx base gets one register for both paths (original v0 / a1). Best stays 7.
- 001f2630, 001f1fc8: volatile fields (136 pairs) no gain; volatile through a pointer changes other
  code (26 vs 4 at the same position). 001e0ab0 twins: the state store is lo_sum, not volatile;
  still steal_delay_list_from_fallthrough. 00214a68: real inner loops 24-39; goto loop with
  `{ s32 *q = &D_00642C74[1]; q += k; (*q)++; }` gives the body (12) but loop.c hoists the lui.
- Facts: cross-jumping runs after sched2, so written-out tails merge only if sched2 ordered them
  the same.

## s11w6 (001c5ee8 001cfc28 001fbcd8 001db718 00135a68): no matches, three closer
- 001cfc28 12 -> 1 LCS (w6__001cfc28_1w.c, hand): identical one-statement arms
  `if (vm) m.x = r->x4->x4; else m.x = r->x4->x4;` (a load + store = 2 insns per arm, so they
  survive to sched2): the m.x store gets its own sched1 block and escapes the stale INSN_TICK of
  the func_001e98d0 call. Left: sched2 cycle-5 tie at priority 3, `dsll v1,v1,8` vs `li.s $f1,1.0`.
- 001c5ee8 11 -> 7 (w6__001c5ee8_7w.c): loop.c move_movables stops hoisting the `&ent[i].v[k]`
  invariants once the loop passes ~105 real insns (threshold drops per move); `e->field` forms
  bring it to 103 with s11w1's identical arms kept. Left: i/lk a2/a3 swap (lk .1929 > i .1776).
- 001fbcd8 17 -> 15 (w6__001fbcd8_15w.c, hand/nostrict): neg-block climb; left: global-alloc order.
- 001db718 40: natural loops hoist &stk[sp]; the phony do/while(0) shape is 68. 00135a68 33: the
  four address registers look like gcse PRE copies (stores in separate blocks at gcse time).
- Facts: sched2 ties at equal priority prefer a memory-unit li.s over an ALU insn. Tool:
  tools/matching/cf4_s11.py (identical-arm contents x statement orders, in-process).

## s11w12 (00200e28 001e1838 00110618 001fd858): no matches
- 00200e28 30 -> 27 LCS (w12__00200e28_27w.c, hand/nostrict, hill-climbed) and a natural 38-LCS
  version (w12__00200e28_38w_natural.c: 00200648 types, header in struct order, one pointer `q`
  advanced in place). Left: sched2 ALU order of the shifts and li constants.
- 001e1838 154 -> 110 LCS at the right size (w12__001e1838_110w.c, hand, a probe): byte 0 through
  a flat u8 index, bytes 1-2 through `Px {u8 c[3];} (*)[512]` (132 at size 960 alone), pi as
  3.1415928f (gcc 2.96 turns 3.1415927f into 0x40490fda). Left: loop.c giv structure (listed in
  the file).
- 00110618 136 (w14 probe stays): the original also spills n2. 001fd858 197: a0 still holds o at
  the first func_001fe1b8 call in the original.
- Facts: sched2 hoists insns using only callee-saved registers across calls into the prologue;
  floods want one packet pointer advanced in place; climbers keyed by line text need unique lines.

## s11w11 (001bd090 00106ed0 00107548): no matches; 001bd090 is NOT a compiler difference
- 001bd090 74 -> 68 LCS (w11__001bd090_68w.c, hand): the 69-block is exact with
  `func_001ba3f0(68); do { } while (0); t = func_001ba3f0(69); k = 5; l.a = 3; l.cnt = 0;
  if (t > 0) { l.a = k; i = 1; }` (k and the dead `i = 1` are unnatural). Traced in dumps and gdb:
  2.96 runs if-conversion after jump1, after cse2, and as the "ce" pass after life1/combine. The
  original is ce's output, which needs (1) a one-insn then-arm at ce time (5 already in a pseudo),
  (2) both early passes to fail (a second then-arm insn, dead, that life1 deletes), (3) insn_b not
  right before the jump (the `l.cnt = 0` store between), so noce_try_cmove_arith reloads l.a and
  postreload makes it `li v0,3`, keeping the first store. The `move v1,zero` is ce's fresh zero
  pseudo (no cse after ce). Open: the natural source for "pre-loaded 5 + dead extra arm insn".
  volatile makes ce refuse (side_effects_p).
- 00106ed0 71 -> 70 (w11__00106ed0_70w.c, right size and frame): v[4] as
  `{ s32 o = i * 32 + 16; *(f32 *)(o + (s32)q8) = *p19; }`, v[0] base-first `(s32)q8 + o0`
  (rtx_equal_p is order-sensitive, so reload_cse does not turn the second add into a move).
  Left: i (.85) vs p7 (.80) in global-alloc.
- 00107548 118 -> 114 (w11__00107548_114w.c, hand/nostrict): same address trick for Pt x/y/z.
- tools/matching/hc_s11.py now respects `*p` loads/stores (w11's version).

## s11w14 (00249718 00202678 001eddc0 00217000 0024c950 0021e120 0023a968): no matches
- 0023a968 22 -> 10 LCS (w14__0023a968_10w.c, hand, RO 4914a0, CONTEXT_ONLY func_0023a720 stub):
  one function-level `s32 last2 = p.y + h + t + 20;` used in case 3 and case 4 (global pseudo, no
  call crossing) stops local-alloc tying the +20 to a multiply chain; case 3 exact. Left: case 4's
  three address locals rotated (a3/a2/t0 vs t0/a3/a2), p.y load after the sll.
- 001eddc0 finding (58w, register permutation only): one s32 `f` carries a.r, the channel-0 sum
  and the channel-1/2 conversions: exact opcodes and branch choices. Best stays w2's 8.
- 00217000 finding (12w): `tbl = D_003F2C40;` in the head block, only the x10 load in identical
  arms: the split la in one register as in the original. Best stays 8.
- 00249718 3 (~45 shapes), 00202678 7, 0024c950 9, 0021e120 12: unchanged.
- Facts: -fdelete-null-pointer-checks folds `if (o)` after an o-> dereference (identical arms must
  test an undereferenced pointer); combine folds la + addu + lw into `lw sym+off(reg)` via the
  lo_sum's REG_EQUAL unless a block boundary or a second use intervenes; in identical arms sched1
  counts head-block values as ready at cycle 0.
