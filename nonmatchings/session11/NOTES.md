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
