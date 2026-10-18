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
