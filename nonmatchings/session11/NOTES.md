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

## s11w15 (001cfc28 001c5ee8 001502e8 00169688 001fbcd8): 1 match
- 001c5ee8 (hand): s11w6's 7w draft plus identical arms on `if (i > 0)` (bgtz, no compare insn)
  in the else of `if (i == 0)`: `Ent *q = &D.ent[i-1]; if (i > 0) { D.ent[i-1].lk.next = &D.ent[i];
  e->lk.next = 0; } else { same } e->lk.prev = q;` (i 11 refs beats lk); `e->lk.prev` stays outside
  (the giv would gain refs); e->v[0]/v[1] in e-> form (loop under the movable threshold); the dead
  `i = 0;` at the end is needed.
- 001cfc28 1w (best stays w6): sched2 ties go to the lower LUID (= sched1 order); `f32 one = 1.0f;`
  at the top lets update_equiv_regs move the li.s next to its use; volatile type/v[3] fixes the
  swap (hack) but the 1.0 then gets f0. Finding file w15__001cfc28_6w_finding.c.
- 001502e8 2w: C and Q tie (2 refs, same life); needs an extra insn between their loads or a 3rd
  ref on Q. 00169688 4w: `.p2align 3,,7` label padding plus case 10's two-copy cross-jump.
  001fbcd8 15: 1250-variant share/split sweep; shared v needs live length > ~100.
- Facts: > 10 basic blocks makes sched1 use single-block regions for the whole function.

## s11w13 (00120cf8 00105d88 0011b220 00125240 00107c48 0010b390 00110e68): 2 matches
- 0011b220 (hand): one function-level `RFlg *f` shared by both loops, and the VU0 scale helper
  with separate dst/src operands (`vscale2(n, n, scale)`, the sceVu0ScaleVector form): every extra
  asm "r" operand is a use, &n1 24 -> 32 refs, allocated before f.
- 0010b390 (hand/nostrict): anim branches 2-4 convert into a block-local `f32 c = (f32)...;`, the
  function-level f only in branch 1 (brute force over block-local/function-level per branch).
- 00107c48 19 -> 7 (w13__00107c48_7w.c, hand/nostrict, 8 bytes long): the i*16 temp in the dead
  `arg` variable, `base[n].w0/.w4` with `n++`. Left: the `arg = (Ent16 *)i` copy in both arms.
- 00110e68 14 -> 5 (w13__00110e68_5w.c, hand): identical arms `if (p) { *p *= x; } else { *p *= x; }`
  (p 16 refs). Left: the *p load sits after add.s inside the arm.
- 00120cf8 5, 00105d88 7, 00125240 8: unchanged.
- Facts: set_preference also records (set X (op Y ..)) first-operand preferences; expand_binop
  makes the target op0 (`p = base + p` gives `addu p,p,base`); combine merges `x = $a0; y = x`
  when x dies there (not across blocks).

## s11w17 (001bd090): MATCHED, not a compiler difference
- 001bd090 (hand): the five stack words at 0..16(sp) are plain `s32 num, b, maxid, cnt, flag`
  spilled by global-alloc (all of s0-s8 busy), not a local struct. The first `sw 3` is the spill
  store of `num = 3`, `li v0,3` is reload_cse rewriting its reload; constant s-registers and
  `flag = 1`'s fresh li follow. The 69 arm `if (func_001ba3f0(69) > 0) { num = 5; lv = 2; }` has a
  dead set of `lv` (a variable live elsewhere) that life1 deletes, so jump1-ifcvt fails and the ce
  pass converts with a fresh zero pseudo. A variable used nowhere else is removed too early.
  Order: case 61-63 `flag = 1; cnt++;`, latch `f += it->f24; b += it->b14;`, lv block
  `if (maxid == 0) lv = 0; else { ... }`.
- Facts: bottom-of-frame words read/written at every use in a function with all s-registers busy
  are probably spilled scalars, not a struct; loop-depth weighting (each in-loop use counts 2)
  orders hoisted constants in global-alloc.

## s11w19 (0023a968 001eddc0 00217000 00202678): 1 match
- 0023a968 (hand, rodata 0x4914A0, CONTEXT_ONLY copy of func_0023a720): w14's draft plus case 4 as
  `{ s32 py; x = p[k*2] + 11; h = o->x10 * 22; py = p[k*2+1]; t = a[k] * 22;
  last2 = py + h + t + 20; if (last2 >= 369) y = 348 - h; else y = py + t; }`.
- 00217000 8 (w19__00217000_8w.c): one-block tail `c = D_003F2C40[sel].x10;` also fixes
  `move t2,v0`; combine still folds the table address; li 2 / li 5 order is a ready-list effect.
- 001eddc0 8, 00202678 7: unchanged (~70 / hill-climb).
- Facts: insns made ready in the same cycle as the one just scheduled are appended unsorted
  (RTL-earliest wins over higher priority); INSN_REG_WEIGHT ranks before the dependence class;
  `-fsched-verbose=9` prints dep count / priority / cost per insn.

## s11w16 (00199ac8/0019ab38 00216890 0010ba98 00166570 00105288): no matches, no new bests
- 0010ba98 21: 16384 `w->` vs `t->win->` x reassignment combinations; floor 21. The final gcse
  CPROP rewrites the PRE copy `215 = w` back to w at three uses; cprop only skips a use if the reg
  is set earlier in that block, or the copy's source/destination is set later in its own block.
- 00199ac8/0019ab38 22: cse folds `du = k` within one block; reload_cse does not make `li 0` a
  copy; the original's `move t4,t0` must be created after constant propagation.
- 00216890 24: sched2 argument-move ties: moves reading a register get an extra forward dep on
  the first insn after the next call (constants do not), deciding order and the bnel.
- 00105288 28: sibling pointer types give 69; the original hoists h[12]/h[13] above a store.
- 00166570 21: m40/m80 direct: 56; frame addresses are not PRE expressions (cse or loop keeps them).

## s11w18 (00106ed0 00107548 001c62a0 00200038): no matches, two big drops
- 00106ed0 70 -> 41 LCS (w18__00106ed0_41w.c, hand, right size/frame): then-block offsets
  (k+92, k+44, k+60, k+76) block-local inside the `if` (sched1 interblock lifts them in priority
  order); prologue `D_00494BB0 = h[0]; sub = ...; D_002A6C50 = 0;` then .a/.b/.d/.c;
  `q = D_00494BAC; q8 = q + 8;` assigned after `*p7 = 1.0f` (fixes i vs p7). Left: s0/s1 swap,
  k+60/k+76 swap, early D_00494BA8 load, prologue flood order.
- 001c62a0 238 -> 153 (w18__001c62a0_153w.c, hand/nostrict, right size): j loop as two pointers
  advanced in place `{ f32 *v = &e->v[5]; f32 *d = &D_0037A380.e.x; for (j..) { *v++ += add[j];
  *d++ = set[j]; } }`; `e->` vs `D_0037A380.ent[i].` greedily per field. 120 LCS but 12 bytes
  long: w18__001c62a0_120w_size.c (the original's giv grouping).
- 00107548 114, 00200038 254: unchanged (the original's q+416 giv not reproduced).
- Facts: assigning a pointer local after a store instead of as an initialiser moves an index's
  last use in sched1 (fixed a global-alloc order); tools/matching/togm_s11.py greedy-toggles
  alternative spellings per occurrence.

## s11w20 (00110e68 00107c48 001cfc28 00120cf8 001502e8): no matches, two closer
- 00110e68 5 -> 2 LCS (w20__00110e68_2w.c, hand): `*p` load and `v = *p * x` in the head,
  identical arms on the parameter `a` each holding `*p++ = v`, x as
  `(1.0f - D[i]) * cosf(*ph) + D[i]`. Left: x ties to t (operand 0): `add.s $f20,$f20,$f2` vs
  `add.s $f2,$f2,$f20`. Alternative 2w: x function-level set in block 0 (loop exact, block-0
  compare in f2 vs f0).
- 00107c48 7 -> 3 at the right size (w20__00107c48_3w_deadtest.c, hand/nostrict; uses a dead
  `if ((i << 4) & 8) return 0;` = hack): keeping i live past `arg = (Ent16 *)i` stops combine
  merging the param copy. Left: block-0 `lui v0 / lw v1` swapped.
- 001cfc28 1w, 00120cf8 5 (the 3 is hoisted by loop pass 2 in the original), 001502e8 2: unchanged.
- Facts: combine does not merge `i = a0` into `arg = i` while i is used later; sched1 builds
  interblock regions only for loops; local-alloc ties `x = a + b` to operand 0 when it dies there.

## s11w21 (00110618 001636d0 001fd858 0010d470): no matches, structural findings
- 00110618 natural structure (w21__00110618_163w_natural.c; climbed 158): two written-out
  sceVu0ViewScreenMatrix bodies (SDK expression shapes for az/cz, one work matrix `mt`) and three
  static inline sceVu0ViewClipMatrix calls: identical opcode multiset, right size, exactly the
  original's spill set. Left: all FP pseudos are local-alloc's (one block): fa/d/n/fan order.
  The s10 w14 probe (136, unnatural) is still lower.
- 001636d0 finding (438): update_equiv_regs gives pp REG_EQUIV because every set is sp+16; one set
  copied from another pseudo (`pv = pos; ... pp = pv;`) makes pp spill with the original's
  pattern. Left: j/par swapped. s7's 414 stays best.
- 001fd858 197: no spilled scalars (frame saves only s0-s3/ra); the up-path smoothing tail
  cross-jumps into the down path's copy. 0010d470 330: spill slots already match; case 24 and
  25-31 PUT copies merge ~17 words too early in ours.
- Tools: tools/matching/slt_s11.py (per-slot store/load counts), var_s11.py (string-replacement
  variants, ` | ` separates edits, `@k@` picks the k-th match).

## s11w22 (00102118, 00152928, 001137f8, 001ba520, 00192958)
- MATCH 00152928 (nostrict): `p = a->x144;` hoisted after `f1c +=`; dead `p = 0;` before `if (a->x90 == 0) goto set;` (a cse skip-block join) keeps the gcse PRE copy `move a1,a2` alive, because CPROP pass 2 sees a set of p on one path. Life1 deletes the dead set. Real-body CONTEXT_ONLY func_00152648 for the reorg slot fill.
- Lever: a PRE copy that CPROP2 removes survives if its source gets a dead set on one path, in a block cse1 can't fold (skip_blocks join, multi-use label).
- cse skip_blocks crosses an if-then (no else), not the builtin unsigned-conversion diamond. gcse cprop replaces copies inside store MEM addresses too.
- 001ba520: 10w (was 15), w22__001ba520_10w.c; the original stores w10 first, store weights push it last.
- 00102118: still 6w (s10 w9). w22__00102118_72w_finding.c shows a hand u32 conversion gives the join-block `move s0,s3`, but cse1 then carries the D_002A3E20 address across.
- 001137f8 (11): sched1 priority of the 1<<32 constant (24 vs 26/27) puts it last, in t0. 720 orders tried.
- 00192958 (17): zbuf/scissor u128 constants tie in local-alloc; lower qty wins.

## s11w24 (00106ed0, 001c62a0, 001e1838)
- 001c62a0: 59w (was 153) with an unnatural c4 address probe (w24__001c62a0_59w.c); 80w natural (w24__001c62a0_80w.c), both nostrict at the right size 1148. Inline `rd2(&e->lk, p)` makes the field address one value. Left: the original hoists a second &D_0037A380 pseudo that gets no register and reload rematerialises it (`lui s6`) in the f block. Chaotic: one-line changes swing 60 to 200.
- 001e1838 is a NOFILL function (`move a0,v0; jal; nop` slots; gcc's own fills survive nofill). 107w nofill, right size 960 (w24__001e1838_107w.c). Left: giv for (192+sy)*1536 needs 0x48000 in a hoisted spilled pseudo.
- 00106ed0: in strict code a block of f32 accesses through different bases keeps exact source order, and pointer-global loads wait on earlier f32 stores. True order: `*p7=1; t=*p23; *p23=1; v[0]; v[1]; v[4]; *p11, *p15, *p19, h[27]`, both pointer globals read before `*p23`. w18's 41w draft has v[4]/v[1] and p11/p15 swapped (wrong basin). w24__00106ed0_47w_order.c has the right order and an exact prologue; left: a third s-reg (592 bytes) because the loop-bound copy loses t9.
- Fact: a spilled pseudo with a constant equivalent is rematerialised at its use; an in-loop `la` can be an unallocated hoisted invariant.
- togm_s11.py temp name is now per-pid (was a shared .s11w18_tog.c).

## s11w25 (00110e68, 00107c48, 001cfc28, 00249718), no gains
- 00110e68 (2): x must be a global pseudo (local x ties to the dying D[i] load and outranks *p for $f1). w25__00110e68_2w_xglobal.c is the diagnosis draft.
- 00107c48 (3): any combine-folded test works like the dead test (hack). Left: local-alloc tie between %hi and the load quantity; sched1 priority won't issue the param copy before the lw.
- 001cfc28 (1): sched2 tie between li.s and `dsll v1,8` on every key; sched1 LUID decides; li.s goes at t=2.
- 00249718 (3): inline `cub(Seg3 *s, k, t, t2, t3)` gives the exact schedule but one-block registers (11).
- Facts: global-alloc live lengths follow sched1 order, not RTL order. Inline helpers taking (struct base, const index) give fixed-offset loads; a sub-struct pointer keeps addu bases.

## s11w23 (00265608, 0021e120, 001ffb30, 00135a68, 001db718)
- MATCH 001ffb30 (nostrict): from r2_4's 31w, `p = (PF *)func_00122048(1024, 128); buf = (u64 *)p; p = (PF *)(buf + 2);` (p takes the call value first). That moves p=buf+16 before the 0x0fff0000 constant (29w); a fresh hc_s11 climb of the header gave 2, then swapping the v[1]/v[3] `.u = 424` stores gave 0.
- Lever: after a call's return copy, the RTL-earliest insn depending on it only by a cost-0 anti-dependence issues in the same cycle, ahead of higher-priority dependents. Set the variable from the call value first to change that.
- Lever: fix the head of a flood block, then re-climb from scratch; old optima are built around the wrong head.
- 0021e120: 8w (w23__0021e120_8w.c). Left: the 63 constant li issues after 66 and gets t1; original has 63 right after 0x5000.
- 00265608 (9): original issues H=(h-1)<<44 right after div, before off[] loads; sched2 priority 7 vs 10/9.
- 00135a68 (33, 12 bytes short): original needs separate v+i*16 pseudos that reload_cse makes into moves; cse1 always forms one.
- 001db718 (40): `j = 0; if (X) do {...} while (j < 48 && X);` makes both loops phony like the original, but the X test lands at the loop top (60).

## s11w26 (001f2630, 001f1fc8, twins 001e0ab0/0d98/10f8, 00169688, 001502e8), no gains
- Store floods: sched1 issues stores whose value dies first (weight -1), in source order; in sched2, stores with values in call-clobbered regs keep sched1 order. Read the original's sched2 order to infer which values stayed live.
- 001f2630 (3w best stays w2): the x2c store must leave 0x8000 live. A `k8 = 0x8000` variable gives the right store order except x20, but loop.c hoists it and reload re-creates `li` per use, and allocation of the temporaries shifts (24w). w26__001f2630_41w_finding.c.
- 001f1fc8 (5w best stays w32): same model; u64 k1 constant merges back into li.
- Twins 001e0ab0/0d98/10f8 (4w): no hidden jump table. Reorg's steal is blocked only by a CODE_LABEL between bgtz and sw (or find_basic_block -1); no plain C gives one that survives jump2. Static &&label is the only 0w form (hack).
- 00169688 (4w): gdb on cc1 (has line info) shows find_cross_jump stops at the L_skip label left by the inlined Tail before return; the label is threaded only in jump2's 2nd iteration, after jump_chain is fixed. `if (o->x70 == 2) return 1;` in both copies merges them but moves return-1 into case 10 (424w). w26__00169688_370w_finding.c.
- 001502e8 (2w): needs life(Q) < life(C) under the fixed 3-element exchange in local-alloc; no source found.
- Tool: gdb breakpoints on cc1 statics (find_cross_jump, jump_optimize_1) take typed expressions; the 8th jump_optimize_1 call is jump2.

## s11w28 (00106ed0, 001e1838, 001cfc28), no gains
- 00106ed0: original reuses one register for k+92, k+60, k+28, k+76; only a reused-variable shape (`o` for those then *pd, `w` for k+44 then *pb) gives the original test-block instruction order (w28__00106ed0_86w_order.c, 592 bytes). Registers come out permuted because a variable that dies more than once is never local-alloc'd. That test block + w24's then-block gives 63 at the right size 588 (not saved).
- 001cfc28 (1w): li.s would need to become ready at t>=8 for dsll to win the sched2 tie on register weight; nothing float is available there.
- Facts: multiply-set variables that die more than once go to global-alloc after locals. Reusing one variable for a run of temporaries forces their sched1 order through anti/output deps. In sched1, the insn carrying REG_DEAD of a shared base gets weight 0 and wins equal-priority ties; declaration order decides which insn carries the death. Sched2 tie keys usually tie for reg-reg insns, leaving LUID.

## s11w30 (0021e120, 0024c950, 00217000, 001eddc0, 00265608)
- 0021e120: 6w (w30__0021e120_6w.c), nostrict, right size 1000: fresh hc_s11 climb from plain index order. All header constants now in the original registers; left: li 0x5000..8001 issues after li 66, and the first store.
- 00217000: 6w (w30__00217000_6w.c), size 1164 vs 1168. Tail `c = func_00170dd8(..); *pe = 2; do { } while (0); D_00642CD8 = 5; *pe -= c;` is exact. Left: combine folds the D_003F2C40 la+addu+lw into lui/addu/lw 11344; the original keeps lui/addiu + lw 16(v0). `tbl = D_003F2C40` before a call stops the fold but tbl takes s0.
- 0024c950 (9, nofill): dead set of a live variable moves if-conversion to ce and gives the load v0, but ce adds `xori v0,v0,0` and kk lands in v1 (13w).
- 001eddc0 (8), 00265608 (9): no gain; gcc991111's sched has no RTL-earliest effect and no -fsched-verbose.
- Facts: an empty `do { } while (0)` is a sched1 barrier (loop note), not a block boundary, for ordering constants. In store floods sched1 issues li's in RTL order and local-alloc ranks them by li-to-store distance, so a fresh climb from index order can find a better basin. A pointer to a constant symbol live across a call is not folded into `lw sym+off(reg)` and takes an s-register.

## s11w29 (0019f1f0, 00202678, 00214a68, 001fbcd8, 001f18e8), no gains
- 00214a68: w29__00214a68_14w_loopshape.c (nosi, 192 vs 184) has the original inner-loop shape: a real `do {} while (1);` puts the lui in the inner preheader (outer move refused by moved_once); `q = &D_00642C74[1];` before the `*p == 0` test and `q += k; (*q)++;` after it keeps lo_sum/addu in the loop. Left: i/k<<2 registers swapped; the `i >= 48` exit has REG_BR_PROB 5000 so reorg fills from the target (beqzl).
- 00202678 (7): o loads can't pass the a/100, b/100 spill stores (nostrict); the original needs 6 loads before the first div, sched1 allows 4. Strict gives the right load placement but 148w.
- 0019f1f0 (7): confirmed the empty bltz slot needs a CODE_LABEL right after bltz (own_thread_p fails); no natural source.
- 001f18e8 (16): tag = p+5 hoisted above the 2nd call since its pseudos cross calls; `do {} while (0)` after the call holds it but also the col conversion (32w).
- Facts: sched1 gives insns touching non-call-crossing pseudos an anti-dep on the last call. Loop notes are a full sched1 barrier. loop.c moved_once needs 2x savings in the outer loop. Sets after a loop exit used in another block are never moved. REG_BR_PROB: EQ-zero test of a load 3999, slt vs nonzero constant 5000 (fills from target, beql). Each division gets its own li pseudo and trap_if.

## s11w27 (00120cf8, 00105d88, 00125240, 001fe1b8, 001fa8b0)
- 001fe1b8: 59 -> 2w (w27__001fe1b8_2w.c, hand, right size 588). Param `s32 a` reused; `s32 r = 0; Scr *o = (Scr *)a; ... a = r; return a;` makes a cse's canonical register (lives longest), keeping `move a1,a0`. Mask and temp split per part (f/g, t/u); part-2 limit `a = (o->cc - o->ce) << 4;`. Left: first load `lhu a0,210(a0)` goes through P; original uses o (a1).
- 00120cf8 (5): the original hoists `li 3` in loop pass 2 and `li 1` in pass 1; ours both in pass 1. `j < (n = 3)` with `k % n` gives the right registers but the li stays in the loop.
- 00105d88 (7): global-alloc priority (loop-2 pointer 2.08 vs counter 1.27); original uses one counter register in loops 1 and 2.
- 00125240 (8): FP local-alloc; needed post-sched1 lives: 1e4 < x/6, -1e4 > x/6, 1.0 > x/4 and > 1.5 * (-1e4).
- 001fa8b0 (12): no gain.
- Facts: cse copy swap only fires when the previous insn sets the copy source; canonical register depends on REGNO_LAST_UID. Splitting a many-block mask/temp per region halves refs (global-alloc priority lever). update_equiv_regs doesn't move a constant within one block.

## s11w31 (0010ba98, 00199ac8/0019ab38, 00166570, 00200e28, 00105288)
- 0010ba98: 21 -> 7w with a flagged dead set (w31__0010ba98_7w_hack.c, strict, RO=0048cd30, right size 760). `extern s32 func_0010ea00(P20 *)` called with t->p20 (check callee arity in its asm); `w = t->win;` after cb; join stores f54 then f50; case-1 tail f50, f54, state; hack `w = 0; w = t->win;` at the end of the c==1 arm kills the post-call PRE copy for CPROP2. Each fix only pays off once the kill is in. Left: bb0 PRE copy R = w (`move a0,a1` in the dispatch slot); needs a set of w inside bb0 that cse1 doesn't fold. 2048-combination sweep floor 7.
- 00199ac8/0019ab38 (22): db vs hoisted 0.0f is a global-alloc priority question (db .124 vs zeros .089/.062); `du = k` copy must be created after gcse.
- 00166570 (21): frame addresses do go through PRE (sp+128); the original recomputes after the loop.
- 00105288 (28): lui hoisting decides it; 00200e28 not worked.
- Facts: retry no-gain fixes after the main blocker is fixed. Anchor variant-script edits at `\n` (case 1 matches inside deeper indents).

## s11w33 (001fe1b8, 00120cf8)
- MATCH 001fe1b8 (hand), FLAGGED: w27's 2w draft plus a dead one-path set `if (a <= 0) a = 0;` right after `Scr *o = (Scr *)a;` (then `a = o->d2;`). The test keeps a live past the copy (combine can't merge the param copy), the set stops gcse CPROP pass 1 rewriting the first load from o to a, and life1 deletes it. Counted like the other dead-set matches (00152928, 001bd090), flagged in the file; not a dead test. Identical `{ o = (Scr *)a; r = 0; }` arms without the set give 1w.
- 00120cf8 (5): pass-1 inner and outer loop both move `li 3`; the original needs it unmovable through pass 1. No natural source found.

## s11w32 (001f2630, 001f1fc8, 0021e120, 001137f8, 00192958)
- 001f2630: 3 -> 1w (w32__001f2630_1w.c, nofill, session9/w2 context): fresh hc climb from struct-offset order. Left: x2c=0x8000 store issues right after `sd d[1]`, original after `sw t0,20`. w32__001f2630_7w_order.c has the exact store order (`k8 = 0x8000` in the block plus a dead `k8 = 0x8000;` in the '\n' branch so loop.c won't hoist it) but registers t0/a2/a1 instead of a1/t0/a2.
- 001f1fc8: 4 -> 2w (w32__001f1fc8_2w.c, nofill, RO=00490a80): plain struct-offset store order. Left: one=1 store issues 3rd (original after x38), x30 out of place. w32__001f1fc8_11w_hoist.c: hoisted `u64 k1 = 1` before the loop puts the one store exactly right (block registers off).
- 0021e120 (6): original sched1 order should be 5000 < 63 < 2006 < 97 < 68 < 66; every way of getting it changes local-alloc.
- Facts: `do {} while (0)` inside a for(;;) body is not a usable barrier. To set a constant store's issue order without moving its li: assign the variable early, store late, dead-set it in another branch of the loop (two sets: loop.c won't hoist). Some flood constants in the original were loop-invariant (hoisted, re-created by reload, store weight 0). A constant store issues as soon as its li is ready.

## s11w35 (dead-set sweep: 0021e120, 00217000, 00202678, 0019f1f0, 001eddc0, 00214a68, 0024c950, 00265608)
- MATCH 00217000 (nostrict), FLAGGED dead set: from w30's 6w, `E20 *tbl = D_003F2C40;` at entry (never used) and `tbl = D_003F2C40; c = tbl[sel].x10;` after the third draw call. gcse shares the entry HIGH (reg 96) with the late la; life1 deletes the dead entry LO_SUM; the late LO_SUM reads a HIGH from another block, so combine can't fold it. Gives `lui a0 / addiu a0 / addu / lw s0,16(v0)` at size 1168.
- Fact: dead sets do nothing inside one block (cse folds them); the set must be in a different block from the use so gcse makes the copy.
- No gain on the rest; 0024c950 kk local-alloc priority stands; 001eddc0 has no branches besides fixuns diamonds.

## s11w34 (dead-set sweep: 001cfc28, 00110e68, 001502e8, 00107c48, 00249718, 0010ba98, ...)
- MATCH 00249718 (hand, strict), FLAGGED dead set: plain straight-line t2/t3/rows code with `if (t < 0) t2 = 0;` right before `t2 = t * t;`. EE has no FP cmov, so jump1 can't if-convert an FP test; the empty branch survives sched1 and both allocators (3 blocks, t used across blocks), then flow2 deletes it. Any FP test on t with a dead set of t2/t3 gives 0w; an integer test gives 6w.
- 0010ba98: 7 -> 2w (w34__0010ba98_2w.c, strict, RO=0048cd30): dead `w = 0;` before `func_0010b170(t->win)` in case 0 keeps the bb0 PRE copy; inner switch as `case 1, case 2, case 0: case 3:` (shared label stops cse1 following in) with a real `w = t->win;` ending the shared arm. Left: `lhu v0,16(a0)` comes out 16(a1).
- 00107c48: 3w with a dead SET instead of w20's dead test (w34__00107c48_3w_deadset.c): `if (i != 0) { i = 0; n = 0; }` (two sets survive to combine; one set becomes a cmov in jump1). Left: block-0 lui/lw register swap.
- Facts: an FP-condition dead-set test changes block structure through allocation at no code cost (flow2 deletes it). Integer one-set arms become cmovs in jump1. Shared case labels act as a cse1 kill point. lchkro_s10 and variant runners need RO exported.

## s11w36 (001f2630, 001f1fc8 finishers), no gains
- 001f2630: w36__001f2630_3w_plainfix.c has every block register right, only store order off. x2c must sit in sched1's weight -1 group (LUID order x34 x44 x10 x14 x2c); with a plain constant that order breaks global alloc, with k8 + dead set local-alloc gives f4+288 the a1 (the li fills an idle alu slot right after the call, so k8 lives long).
- 001f1fc8: the one store can follow x38 only if its value stays live (weight 0, hoisted constant); hoisted shape gives cy+h a1 instead of t0.
- Facts: sched1 store rank = priority, reg weight (-1 if value dies), dependents, LUID. A pseudo set after a call depends only on that call, so its li can't be delayed. Same-block vs other-block dead set of a constant variable gives identical code.

## s11w38 (FP dead-set tests)
- MATCH 0010ba98 (hand strict, rodata), FLAGGED: w34's 2w draft, the end-of-arm `w = t->win;` replaced by `if (t->dx < 0.0f) w = t->win;` at the start of the shared `case 0: case 3:` arm (a redundant conditional set kills the copy on one path, so CPROP2 leaves the load on the PRE register: `lhu v0,16(a0)`). w34's dead `w = 0;` stays.
- MATCH 00110e68 (hand strict), FLAGGED: w20's identical arms, w25's `x = D[i] + (1.0f - D[i]) * cosf(*ph);`, plus `if (x < p[-1]) v = 0;` at the end of the loop body: x becomes global (read in a later block), and the p[-1] load gives p its 17th ref so it wins s0.
- 001cfc28 (1), 001502e8 (2), 00125240 (8), 00120cf8 (5), 001eddc0 (8): no gain. FP tests on values cse knows are folded; a new FP quantity in a 3-quantity block switches local-alloc from the 3-element exchange to qsort.
- Facts: a dead FP test's compare operands are free extra refs. A conditional set to the value already held kills a gcse copy on one path. FP tests against a new constant in a loop hoist it into a callee-saved register (+12 bytes).

## s11w39 (block-split sweep: 0021e120, 00202678, 001137f8, 00192958, 00106ed0), no gains
- 0021e120: w39__0021e120_6w_h0.c (6w, other basin): `u64 h0 = 0x5000000000008001;` set first, stored later, makes li 5000 issue first. Left: 66/97/68 order, li 30ae early, first store. Original header is one sched1 block; splits cost 17-115w.
- 00202678: a split before `a100 = a / 100` puts the o-> loads before the divs but makes a, b, ys global (244w).
- 001137f8 (11), 00192958 (17), 00106ed0: splits only made things worse; params/address pseudos live across a split become global.
- Facts: integer two-set dead arms are gone before cse2 (act on cse1/gcse only). `(f32)x < 0.0f` is a free splitter like an f32 variable. Splits pay only where the cross-block pseudos are global in the original anyway. A constant set into a variable first and stored later issues first (one-constant lever).

## s11w37 (dead-set sweep: 001ba520, 001fa8b0, 001fbcd8, 001f18e8, 00166570, 00199ac8/0019ab38), no gains
- 00199ac8: w37__00199ac8_44w_finding.c is the first source keeping the `du = k` copy and the `move zero` bgtz slot (`i3 = 0;` in the first b5 block, `k = i3;` after `d = seg - same;`, `du = k;`). Left: a global-alloc permutation (k outranks the case-loop counter m after sched1 halves k's live length).
- 00166570: w37__00166570_56w_finding.c gives the original preheader (m40/m80 used directly in the loop); PRE also reuses post-loop addresses so address pseudos stay live across the loop.
- 001ba520, 001fa8b0 (nogcse mode), 001fbcd8 (global-alloc needs v's life ~100), 001f18e8: no dead-set angle.
- Facts: $1 (at) is the soft frame pointer; frame addresses are PRE-available everywhere. CPROP ignores a set of the copy source earlier in the same block (kills must be in a predecessor block). Dead sets inside a loop body are seen by loop.c. .lreg live lengths come from after sched1.

## s11w41 (twins, 0019f1f0, 00214a68, 001fa8b0, 00265608, 00125240)
- MATCH 001fa8b0 (nostrict_nogcse), FLAGGED dead FP test: from s9 w6's 12w, `cm = c - 32; k = D_003E8D40[cm];` plus `if ((f32)cm < (f32)n) a = 0;` right after `x40 = xx + a;` (a dead after). cm becomes global, so local-alloc no longer puts the c-32 chain in v0.
- 00214a68: 8 -> 5w (w41__00214a68_5w.c, nosi, right size 184, flagged): exit arm `if (i >= 48) { p = 0; break; }` turns beqzl into beqz (the dead set in the exit arm makes the loop heuristic predict toward the loop; after life1 jump inverts it); three dead tests `if ((f32)(i + n) < 0.0f) p = 0;` give i 17 refs (a1). Left: the tests lengthen the ids giv's life so it swaps a3/t0 with the inner-loop lui.
- Twins: bgtz REG_BR_PROB 6001, dead FP tests vanish with their label in flow2; no route. 00265608: gcc991111 does NOT delete dead FP tests (884 -> 908), so the lever is 2.96-only.
- Facts: REG_BR_PROB EQ 3999, GT0 6001, GE vs nonzero 5000. A dead FP test needs a target variable used elsewhere. Global-alloc priority ~ log2(refs)*refs/live length, refs weighted by loop depth. cse merges repeated (f32)i into one ref. FP compares in a loop body change loop.c decisions.

## s11w40 (allocator-priority dead tests)
- MATCH 001502e8 (nostrict), FLAGGED dead FP test: from session8 w1's 2w, case-0 tail `{ s32 m = a->x130->x48; S144e *q = a->x144; q->x4 = m; if ((f32)(s32)q < q->x8) t = 0; }`. More than 3 local quantities switch local-alloc to qsort; the cvt of q and the q->x8 load give Q extra refs. N v0, Q v1, C a0.
- 00107c48: 2w (w40__00107c48_2w.c, flagged): w34's draft plus `if ((f32)D_00351BD0 < 0.0f) j = 0;` after `arg = (Ent16 *)i;`. Left: `lui v0` vs original `lui v1`.
- 001f2630: w40__001f2630_35w_order_finding.c: plain constants with store order x30(f2+w) x34(f4+288) x44 x10 x14 x2c give the exact store order and loop registers, but `a0 = 2` issues before cy+h and reload picks v1 for h (size 1064).
- 001f1fc8 (2), 0024c950 (9), 00105d88 (7): no gain.
- Facts: `(f32)(s32)ptr < fpload` gives free refs to an int pseudo. A dead FP test survives to the allocators only when an explicit jump follows its empty arm (break, then-arm before else, case end); if the target is just the next label, life1 deletes it. The dead-set variable must be used elsewhere. A store's sched1 weight is -1 only if its value's RTL-last use is that store.

## s11w44 (00214a68, 001ba520)
- MATCH 00214a68 (nosi), FLAGGED dead set + dead FP test: w41's draft without its three tests, keeping `if (i >= 48) { p = 0; break; }`, plus `if ((f32)(i * i) < 0.0f) c = 0;` right after `i++;` in the inner loop (c dead in the loop). Inner-loop refs count with loop-depth weight, so i beats k<<2; the test sits where both the ids giv and the lui are live so their order holds.
- 001ba520: w44__001ba520_15w_volatile.c: volatile on w4/w8/wC/w10 gives the exact store order; left: sched1 ranks ~nw above t. Best stays w22's 10w.
- Facts: a dead FP test in an inner loop is fine for loop.c if its target is dead in the loop. Put dead tests where both rival pseudos are live. `(f32)(i * i)` gives two refs in one insn (cse merges repeated (f32)i).

## s11w45 (00107c48, 0024c950, 001f2630, 001f1fc8)
- MATCH 00107c48 (nostrict), FLAGGED dead FP test + dead set: w40's draft with `if ((f32)(s32)&D_00351BD0 < 0.0f) i = 0; else if (i != 0) { i = 0; n = 0; }`. The else gives the explicit jump so the test survives; the address lo_sum keeps the %hi live into the next block, so global-alloc gives it v1: `lui v1; lw v0,7120(v1)`.
- 0024c950: 9 -> 8w (w45__0024c950_8w.c, nofill, flagged): `if ((f32)D_00669A5C < (f32)(D_00669A5C + 1)) t = 0; else n = 0;` after `D_00669A6C = x;` gives the load 4 refs (v0, kk a0). Left: the branch splits off `p = D_00669A40` and the preheader; several %hi registers off.
- 001f2630/001f1fc8: the x2c constant store is ready when its li issues and outranks the others in the weight -1 group by LUID; no lever without a block split.
- Facts: var.py/ins.py replace the FIRST match, which can be inside a header comment (strip comments before sweeps). A dead-set else arm keeps the explicit jump without changing behaviour. A dead FP test targeting an unused variable is deleted by jump1 even with an else.

## s11w43 (00199ac8 and big permutation targets)
- 00199ac8: 22 -> 19w (w43__00199ac8_19w.c, hand/NOSTRICT fill mode, RO=48fb70, size right, 4 flagged dead FP tests). Left: du (.130) outranks the case-6 hoisted copy of d (.120), swapping t3/t4 everywhere.
- Facts: join one-line ifs with their bodies before insertion sweeps (/tmp/claude-0/s11/s11w43/bin/join.py). Ref weights 1/2/3 by loop depth; a hoisted invariant used once in the loop has 5 refs. A dead FP test before a branch on a spilled pseudo leaves a CODE_LABEL that stops reload reusing its register. `mtc1; b; cvt.s.w` is a gas fill (floatsisf2 is one 8-byte insn), so the function is a fill-mode one.

## s11w42 (001cfc28, 00120cf8, 0019f1f0, 00125240, 001eddc0, 001fbcd8, 001f18e8)
- MATCH 001fbcd8 (nostrict), FLAGGED dead FP test: from s11w6's 15w, one shared v (neg block and digit loop), loop's own x3 instead of x2, `if ((f32)v < 0.0f) i = 0;` at the end of the neg block (lengthens v so it ranks below the loop temps), neg-block loads first in order u, v, gw, gh.
- 00120cf8: 5 -> 4w (w42__00120cf8_4w.c, flagged): `n = 3;` at the top of the outer body, `k % n`, `if ((f32)n < 0.0f) n = 0;` after the inner loop. Left: li 3 not hoisted to the outer preheader; outer giv sll.
- Others no gain: 0019f1f0 needs a used label after bltz (case ranges all group into one node); 001eddc0 priority gap too large.
- Facts: re-climb statement order after a dead test fixes priorities. Under nostrict a store before a load pins the load behind it in sched2; loads first frees sched2.

## s11w46 (00199ac8 19w, 0024c950 8w), no gains
- 00199ac8: copy 407 is inl_alpha's `d` parameter hoisted by loop.c; dead tests on d get cprop'd to reg 101, so they can't add refs to 407. Loop-invariant dead tests get hoisted and cost pseudos (62w). Lengthening du needs +15 insns.
- 0024c950: w45's test splits the loop preheader so the A68 address copy goes global (a1). Without it only the load/kk v0/a0 swap is wrong; local-alloc allocates kk before the load even when kk is global.
- Facts: dead tests can't give refs to an inline parameter copy. A dead test before a loop moves preheader movables after it. ld_s11.py and var.py need RO exported.

## s11w47 (00105288, 00135a68, others not reached)
- 00105288: 28 -> 2w (w47__00105288_2w.c, strict, right size 580): D_002A6280 as a member of `typedef struct { u8 *p; } P1;` (a plain extern global access is alias set 0 and conflicts with every load); h[12]/h[13] read into locals q/m before the D_002A6288 store; store order 6280, 6288, 6298, 62A8. Left: one sched2 cycle, `sw D_002A6288` (prio 67) before `addu a1,a0,a1` (26); needs equal priority via an output dep, which costs an s-register so far.
- 00135a68: w47__00135a68_33w_finding.c at the right size 284: dead FP tests with else between the loop-2 stores keep four separate (plus i16 v) pseudos (the original's move chain), but the tests survive to sched1 and serialise the stores. Needs a split present at cse1/gcse but gone before sched1 (idea: a condition only cse2 can fold).
- Facts: only component refs (struct members) get real alias sets. A pointer-member store conflicts with a load through the same pointer type: a chosen dependence edge. sched2 tie after priority: independent of the last scheduled insn wins.

## s11w48 (00106ed0, 001ba520, 00125240)
- 00106ed0: 41 -> 31w (w48__00106ed0_31w.c, strict, right size 588): w18's loop; prologue one statement per store; `sub = ...` before `D_00494BB0 = h[0]`; h[31] read early into f32 `w31`; `D_002A6C50 = 0;` last (bc1t slot). Left: prologue lui order and 12(a0)/12(a1); test block k+60/k+76; then-block still in w18's basin.
- The 592-byte third s-register is reload's GR scratch for fix_truncsfsi2 when no caller-saved reg is free (i*16 lives long in sched1), not a pseudo losing t9. Check "Reloads for insn" in .greg.
- 001ba520: a dead FP test after `l->s.w4 = nw;` gives the original nor/and order but the split reloads v[] from the stack (472 -> 492+).
- Facts: pointer-typed globals read as alias set 0 in strict mode; a union read also delays a float load to the same ready time. Split chained assignments into one store per statement before climbing.

## s11w50 (alias-member/union sweep)
- MATCH 00202678 (hand, STRICT, no hacks): it was a strict function. From s8 w12's 7w nostrict draft moved to strict (148w), then alias set 0 via unions only where the original keeps nostrict-style ordering: `UQ = union { u64 d; s32 w[2]; }` for Q header stores and H2 tag/regs, `UQ *buf`, Wnd `UF x90` and `UF sx` (`UF = union { s32 i; f32 f; }`). 148 -> 112 -> 26 -> 2 -> 1 -> 0.
- 001f18e8: 16 -> 9w (w50__001f18e8_9w.c, nofill, right size): `((UF *)&g->x34)->i = f4 + 288;` and `((UF *)&g->x44)->i = cy + h;` keep the lhu loads before those stores; `g->x4c = 0;` after x48. Left: `tag = p + 5` issues before `jal 1efb98`.
- No lever for 001f2630/001f1fc8 (same-base different-offset stores never conflict), 001137f8 (distinct globals are proven disjoint before alias sets), 00192958, 0021e120, 00200e28.
- Facts: a "nostrict" function may be strict with union fields; loads stuck behind spill stores in sched2 point to strict. A union-typed store after a load adds exactly one chosen edge.

## s11w51 (strict+union remeasure), no gains
- None of 00200e28, 0021e120, 00199ac8/0019ab38, 00135a68, 001c62a0, 00166570 is a strict-with-unions function: when strict keeps the original order its edges equal nostrict's. 00199ac8/0019ab38 in strict need union ShipolyEnt fields to get back to 19/22w.
- Fact: try unions only where the original issues a load ABOVE a store it would conflict with under nostrict. Under strict, members of two different structs never conflict.

## s11w49 (00105288, 00135a68)
- MATCH 00135a68 (nostrict), FLAGGED dead tests: loops 1 and 2 share counter i; loop 1 uses `k = ((i & 1) << 1) - 1; v[i][0] = r * k;`; `x = (s32)v;` at entry; three `if (x != (s32)v) { k = 2; k = 3; } else k = 1;` between the loop-2 stores (two-set arm stops jump1 if-conversion, else stops cse1 skipping, so cse1/gcse see four blocks and make separate v+i*16 pseudos; gcse cprop turns x into v, cse2 folds the test, the jump pass deletes it before sched1); `o = i * 16; *(f32 *)((s32)v + o)` for v[i][0] gives v+i16 operand order.
- 00105288 (2w): needs a 92->106 dependence (sw 6280 -> lw h[3]) in sched2 only; the same edge in sched1 costs an s-register. The original must differ in sched1 order too.
- Facts: a split that lives through cse1/gcse/cse2 and is gone before life1: compare a copy of a param with the param. Empty-arm conditional jumps survive until flow2 here. `o = i * 16; *(T *)((s32)v + o)` keeps v+o operand order. trap_if is a full sched barrier.

## s11w52 (001f18e8)
- 001f18e8: 9 -> 2w (w52__001f18e8_2w.c, nofill, right size 1288, flagged dead FP test): `u64 cl; cl = col;` between the two calls (keeps lw + dsll32/dsrl32, not lwu); `kk = 0xeeee;` then `if ((f32)nd < 0.0f) neg = 0; else n = 0;` right after `func_001efb98(0)` (keeps `tag = p + 5` after the call); constants k4..k9 assigned early, stored later, so li 63 is born last and gets v1. Left: sched2 li order `li t1,1` vs `li v1,63`; original probably has an extra ref on the 63 pseudo.
- Facts: combine merges a stack-param load with its zero-extension (lwu) only with no call between. Spill stores to sp are ordered against every s1-based store in sched2. 64-bit constants are one insn until gas.

## s11w53 (001f18e8 2w), no gain
- sched2 li order ties go by LUID (sched1 order); 63 can only outrank d0 in local-alloc by being born 3+ insns later, which puts it last in sched2. Confirmed dead end with 2 refs each.
- update_equiv_regs moves a once-set, once-used global constant pseudo's li to just before its use (it becomes local, life 1) — why 0xeeee looks local. cse folds every use of a constant pseudo it sees, so dead tests can't add refs to 63 in its block. Untried: a surviving tied copy `B = A` to give 63 four refs.
- Integer tests with identical multi-set arms split blocks through sched2 and leave no code after jump2 (pseudos set in the arms become global).

## s11w54 (00105288, 001cfc28), no gains
- 00105288: sched2 memory edges are a superset of sched1's (after reload, hard-reg addresses lose reg_base_value). The /12 trap_if is a sched2-only edge route (store -> trap -> load if sched1 moves the load after the trap) but sched1 can't place the trap first with w47's types.
- 001cfc28: w54__001cfc28_7w_finding.c: `f32 one = 1.0f; ... m.v[3] = one;` (no volatile) gives the right dsll/li.s order, but update_equiv_regs moves the li next to its use, so 1.0 lives 1 insn and takes f0. Needs the li.s after the dsll but 4+ insns before its swc1.
- Facts: anti/output deps cost 0 on MIPS. sched2 tie keys: class vs last insn, dependents, LUID. A call's stale INSN_TICK applies only to insns with an in-block predecessor.

## s11w55 (reorg label problems)
- MATCH 001e0ab0, 001e0d98, 001e10f8 (hand, one file), FLAGGED dead test with duplicated arms: `{ s32 t = TIMER; if (t <= 0) { STATE = 0; return 4; } if (t == (s32)&TIMER) { REST } else { REST } }` where REST is the whole rest of the body. flow2 counts the read of t (v0) at the bgtz target, so reorg's stale liveness stops it stealing `li v0,4` into the bgtz slot; jump2 cross-jumps the arms and deletes the test. The compare must need no constant and must not fold in cse (`(s32)&global` is free when the address is already in a register).
- 0019f1f0 (7): the stolen insn is `li s0,2` (i); the same trick needs a dead read of i on a path from the bltz target; tried placements break allocation. 00169688: the original case 10 has a jump-to-next left by jump2's last iteration; untested.
- Facts: reorg's target liveness is the stale flow2 live_at_start (scan stops at the first call). 0-use CODE_LABELs never survive to mach.

## s11w56 (00102118, 00105d88, 00216890)
- MATCH 00105d88 (hand), FLAGGED dead tests: loop 2 reuses n as its counter; after the loop-1 body, four `if (n < 0) { m = 1; m = 2; } else { m = 1; m = 2; }` tests with different conditions (<, >, >=, <=) add loop-weighted refs to n with no temps (jump2 deletes them), so n gets a1 in both loops.
- 00102118: 6 -> 1w (w56__00102118_1w.c, flagged): `x = (s32)t;` at entry and `if (x != (s32)t) h = 0;` / `if (x < (s32)t) h = 0;` right after `hh = h;` in each conversion join keep the gcse copy (`move s0,s3`). Left: in section 2 sched1 issues `sw zero,12(s3)` before `addiu a1,s7,8064` in the same cycle.
- Facts: two such cse2-folded tests need different comparisons (else PRE shares them and one survives as movz). Integer identical multi-set dead arms add refs with no temps and no code; identical conditions merge.

## s11w57 (0019f1f0, 00169688)
- 0019f1f0: 7 -> 2w (w57__0019f1f0_2w.c, nostrict, RO=0048FCB0, flagged empty do-while). ORTHO as a plain `{ }` block instead of `do { } while (0)` fixes the empty bltz slot and the func_002672f8 arg order together; the 1.0f store goes into both TAIL copies after an empty `do { } while (0);` barrier. Left: li.s issues right after lhu/sll at the merge; original after cvt.s.w f3 (70 placements tried).
- 00169688: w57__00169688_64w_finding.c explains case 10's `b L998; ld v1,48(a2); nop`: both paths load p = o->x148; jump2's cross-jump label lands after the D&1 path's load S, so the hi copy's b is not a jump-to-next; reorg then steals S into the bnez slot and redirects. Needs both B copies to allocate identically (ld v1, mask v0, 0x40000 a0, 2 a1).
- Facts: `do { } while (0)` loop notes flush sched2 deps, so argument moves after them tie by LUID (check these macros when arg moves are out of order). With no BARRIER before a branch target, reorg target liveness is a linear scan from function start: regs die only at CODE_LABELs and REG_DEAD notes in filled delay slots are not seen. A normal cross-jump's jump-to-next is deleted in the next jump2 iteration (jump.c:411).

## s11w58 (00102118, 00216890)
- MATCH 00102118 (hand), FLAGGED (w56's cse2-folded dead tests): in section 2 `{ s32 four = 4; do { } while (0); hh->a = four; }` puts the li before the loop notes, so the hh->a store is the barrier insn and h->b, h->c, h->d and both call args come ready together; sched1 then orders them by register weight then LUID, as in the original.
- 00216890: 24 -> 13w (w58__00216890_13w.c, hand): removing the `do { } while (0);` after func_002066b0 fixes the first func_001f9438 arg order, the bnel and the D_00642CD8 lui register. Left: loop pass 2 hoists D_003F4508's lo_sum (life 2), its high part becomes a 4th local quantity and takes v1 (original keeps the lo_sum in the loop); swapping `str = (*q)[m];` before `x = ...` keeps it in the loop but leaves exactly 3 local quantities (26w). Also m = 0 floats above the calls.
- Facts: sched1 tie-break is priority, register weight (lower wins), forward-dependent count (more wins), then LUID; a loop-note barrier takes a forward dep from every earlier reg reader/setter still on the last-uses lists; local-alloc's 3-quantity exchange compares quantity numbers, not positions; loop.c moves an invariant only if threshold*savings*lifetime >= insn_count; reload picks reload registers round-robin from the last spill register.

## s11w59-s11w62 (lost)
- The container was restarted twice under load (~48) while these ran; only w60's near miss survived: w60__00125240_6w.c (8 -> 6w, strict, flagged dead FP test `if (p[-1].x < -1e4f) y = 0;`; all FP registers match; left: the D_004F77E0 store's lui takes v0 instead of a1 and the sched2 store order differs).

## s11w60 (00125240, 001eddc0, 001137f8), resumed after the restart
- 00125240: 6w (w60__00125240_6w.c, above). D_004F77E0 itself as the test operand with if/else gives the lui a1 (gcse shares the HIGH, the 2nd use stops update_equiv_regs) but breaks the FP side (10w).
- 001eddc0: w60__001eddc0_9w_finding.c: ch0's conversion in its own variable g with `if ((f32)(s32)g < t) pa = 0;` before g's first set makes g live from entry, so a.r gets a0 as in the original; but g then conflicts with the incoming a0/a1 and takes a2 (orig a1), so reorg fills bc1f from the fall-through. Best stays s11w2's 8.
- 001137f8 (11): sched1 ranks the 1<<32 movdi (insn 29) low, it issues last and takes t0 (orig a2); all 60 orders, barriers, temporaries, split statements: no gain.
- Facts: a dead test's target must stay non-trivially-dead until cse (`v = const; f(v)` folds; `y = 53.0f; f(y)` works); an FP test on a value with REG_EQUAL folds at jump; a test comparing against a stored constant makes that constant cross blocks; a single-use HIGH that gcse shared is moved back down by update_equiv_regs, a second use keeps it global; with if/else cse doesn't carry an address across the join (gcse still shares the HIGH), with if-then cse shares the lo_sum; reading a variable before its first set makes it live from entry (lower priority, but conflicts with incoming parameter registers).

## s11w59 (00200e28, 001db718), resumed after the restart
- 00200e28: 27 -> 26w (w59__00200e28_26w.c, nostrict, hc_s11 climb of w12's 27w; unnatural order). All diffs trace to local-alloc: original needs slti in a0 (cmov then inherits the e[2] load's priority ~222 and sll w issues first), C[0] and 832 both in v1 (needs the v[0].col store before li 832 in sched1), X0 in t3 (needs the d11 store before X0 is born). Tried: sibling 00200648's shape, d7/d9 orders, ub/w clamp moves, do-while barriers, dead FP tests (harmful in a single-block store flood), climbs (floor 26).
- 001db718 (40, best stays s8 w16): a natural `for (j = 0; j < 48 && X; j++)` gives the original loop layout (body first, bnezl with the D reload in the slot, aligned label), but loop.c hoists &stk[sp] and the D address that the original keeps in the loop (gcse PRE's reaching reg for vm->s.sp is set only on edge blocks outside the loop). do-while forms are phony but `&&` makes expand_end_loop rotate the test to the top.
- Facts: a loop is phony (loop.c skips it) when a non-label insn sits right after LOOP_BEG; gcse puts an edge insertion after LOOP_BEG only when the target block already sits there. 2.96 expand_end_loop rotates a do-while with an `A && B` condition (A's false jump to alt_end_label counts as an exit); single-condition while does not. For store floods the sched dependent counts come from hard-register reuse (WAR on the next occupant of a store's source register).

## s11w62 (00166570, 00199ac8, 0019ab38)
- MATCH 00199ac8 and 0019ab38 (hand/nostrict, fill, rodata 48fb70 / 48fbb0), FLAGGED dead FP tests. 00199ac8 (from w43's 19w): extra case-4 loop tests `(f32)(m >> 1) < a`, `(f32)u < a`, `(f32)(s32)q < a`, `(f32)(u >> 1) < a` lengthen du (185 -> 202 insns) so case 6's hoisted d outranks it; `if ((f32)u < a) i = 0;` before the p advance lengthens k so m outranks it; m must stay at 31 refs (32 bumps floor(log2)). 0019ab38: copy 00199ac8's whole matched middle section (key->b20, func_0019aa60), then `if (out[0] < 0.0f) sz = 0;` after the func_0019a9e0 call lengthens the out-address pseudo so segs gets s7.
- 00166570 (21w, best stays session7 w7 27w / w37 finding): gcse PRE/CPROP rewrites post-loop vsv+128 / vsv+64 into the pre-loop CopyMatrix pseudo; the original's look like fresh single-use pseudos merged into the arg moves by combine. No shape found that kills availability; nogcse modes 327-471w, inline helpers 148-350w.
- Facts: global-alloc ties can be steered by live length alone (dead FP tests placed where the pseudo to drop is live and its rival is not); `a < db` FP-only tests add refs to db, use `(f32)intvar < a` to keep FP priorities; do-while(0) loop notes don't change REG_N_REFS; port a matched twin's whole section, not single statements.

## s11w61 (0021e120, 001ba520, 00192958)
- 0021e120: 6 -> 3w (w61__0021e120_3w.c, nostrict, right size): header constants p[0], p[5], p[6], p[3], p[9] split into `kN = C;` set early and `p[N] = kN;` stored later, order from tools/matching/gclimb_s11.py. Left: li 66 issues before li 97/68, `sd t1,0(s1)` after `sd t0,88`. gdb: the six li with reused registers have priority 15 and 3 dependents and tie by sched1 LUID, so the original needs sched1 order 5000 < 63 < 2006 < 97 < 68 < 66, which puts 66's life inside 68's; both 2 refs, local-alloc gives 66 a0 (orig t0, 68 a0). Needs a third ref on 68 or 66 global-allocated after the locals; set-once global 66 is moved by update_equiv_regs (v0); dead FP tests on k11 fold; dead sets in another block die in life1.
- 001ba520 (10w, best w22): constrained climbs of flag/v[] statements, volatile and plain: floors 10/11. sched1 ranks ~nw above t; anti/output deps cost 0.
- 00192958 (17w, best s10 w11): local-alloc priority floor_log2(refs)*refs*size/life (TI size 2); zbuf, xyoffset and scissor all live 28 so the lowest qty (zbuf) wins; original needs scissor, xyoffset, zbuf. sched1 fixes TI births by priority; moving DI statements only permutes DI registers. k-split climb and annealing: nothing below 17.
- Facts: sched2 ties: priority, dependents (a li whose register is reused has one more, the output dep), LUID. update_equiv_regs moves only global set-once constant pseudos; local ones stay even across calls. gdb Python breakpoints on find_free_reg (qty[]) and schedule_block (h_i_d[uid]) trace local-alloc and sched2 (scripts in /tmp/claude-0/s11/s11w61: ffr.py, ffrrun.sh, prio.py).
- The container restarts were caused by this worker's helper named glob.py (it shadowed the stdlib module and recursively launched checks).

## s11w63 (00120cf8, 0024c950, 00106ed0), no gains
- 00120cf8 (4w): the original's chain order means `li 3` is moved by loop pass 2, so pass 1 must refuse it; no source found that trips a scan_loop refusal in pass 1 only (biv-cancelling divisors 14-49w, n placements 5-39w).
- 0024c950 (8w): the D_00669A5C load needs 4 refs or a 1-insn life to outrank kk and the A68 pair; dead tests on kk/yy/L 15w; integer dead tests 9-14w. Only the FP form (w45) adds refs to the load.
- 00106ed0 (31w): w63__00106ed0_54w_finding.c puts w28's reused o/w test block into w48: exact original order at right size 588 but registers permuted (o, w die more than once so go to global-alloc after the locals take v0/v1). The original reuses v0 for k+92/60/28/76, which needs sched1 to issue p15 before k+28; their priorities rule it out. A natural `h[i*32+N]` computes (h+k)+N, not h+(k+N).
- Facts: 2.96 loop.c records no MULT_VAL==0 givs (cancelling biv terms fold in cse2); sched1 register weight beats the in-block preference (an interblock last use, weight 0, beats an in-block insn at +1); store->store and load->store memory deps add 0 to sched1 priority; a scalar-global load has no dep on struct-member stores.

## s11w64 (001eddc0, 00169688, 001c62a0)
- MATCH 00169688 (hand/nostrict, rodata jtbl_0048E870), NATURAL: case 10 as `if (!(D & 1)) { p = o->x148; if (hi & 1) goto c10b; goto r1; } p = o->x148; c10b: B; Tail(o, w); r1: return 1;`. The hi path's goto is not a jump-to-next (the D path's p load sits between), survives jump2, and reorg fills it from c10b; r1 must follow B's fall-through or jump.c hoists `li v0,1` above the hi test.
- 001eddc0: 8 -> 2w (w64__001eddc0_2w.c, strict, flagged): five integer dead tests `if (a.r == k) { pc = 0; pc = pa; } else { same }` between the ch0 conversion and the sum add refs to a.r's QI pseudo, so every register matches. Left: join block issues the sw before c.le.s (orig addiu a2,sp,8 early, sw in the bc1f slot): with 9 basic blocks haifa uses one interblock region where the sw inherits the bc1f's stale INSN_TICK; a 10th block (any test) falls back to single-block regions.
- 001c62a0: 59 -> 56w (w64__001c62a0_56w.c, flagged): `if (add[0] < 0.0f) i = 0; else j = 0;` after the i loop. Rest is loop.c giv structure and a rematerialised second &D_0037A380.
- Facts: a 10th basic block switches a loop-free function from one interblock sched1 region to single-block regions; interblock stores anti-dependent on another block's branch inherit its INSN_TICK; integer tests on a QImode pseudo add one ref each (a (s8) cast makes a new pseudo); global-alloc's first find_reg pass avoids regs preferred by conflicting allocnos; a `return 1` arm right after a test lets jump.c put `v0 = 1` before the condjump. lchkro_s10.py leaves /tmp/tmpXXXX dirs: set TMPDIR.

## s11w65 (001f2630, 001f1fc8, 001f18e8), no gains (bests stay 1w / 2w / 2w)
- 001f2630: w65__001f2630_9w_finding.c has the exact store order (gk = 0x8000 at the 1w li spot, store after x14, dead set in the '\n' branch) but local-alloc order cy+h v1, f4+288 a1, 22 a2, f4 a3, gk t0. gk would need a life <= f4+288's (7 insns): its li must issue at/after the d0 store, but the 2-issue cycles t19-t23 have alu slots only for li22, li8000, f4+288, cy+h, $4=2, so the li always lands at t20.
- 001f1fc8: w65__001f1fc8_13w_finding.c: plain constants in order d0 d1 col x3c x40 x44 x50 x54 x58 x20 x24 x38 one x30 x34 x5c put `one` after x38 with no hoisted k1; x58 then issues after x30. The original's sched1 order needs both 0x100000 stores in the weight -1 group, impossible while cse merges them; x30 has an extra anti-dependent from `cx += adv`. volatile chains raise store priority (14-17w).
- 001f18e8: sched2's li 1 / li 63 tie on priority, class and dependents and falls to sched1 order; the tag spill (sw v0,60(sp)) splits the stores into {d0, d1} and the rest, so d0 must stay before the tag add; 63 then can't be born second and still beat d0's life. 63 as a global constant set before the FP test: 24w.
- Facts: s1 stores before a reload sp spill in sched1 order get higher sched2 priority (output deps around the spill); a store's sched1 weight is -1 when it is the RTL-last use of its value; moving a li's LUID inside a full 2-issue window does nothing; loop.c hoists a user-variable constant set once in a loop but not a plain constant (a dead set in another branch stops it); volatile on flood stores raises their priority. Helpers: /tmp/claude-0/s11/s11w65/bin (kenum.py, pmove.py, vis.py, ffr65.py).
