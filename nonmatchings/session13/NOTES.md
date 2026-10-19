# Session 13 notes (matching track)

## s13w1: 001cfc28, 001f2630, 001f1fc8, 001f18e8, 001eddc0, 0021e120, 00125240 (no matches)
- Best drafts re-verified unchanged: 001cfc28 1w hand; 001f2630 1w nofill; 001f1fc8 2w nofill
  (RO=00490a80); 001f18e8 2w nofill; 001eddc0 2w hand; 0021e120 3w nostrict; 00125240 5w flagged
  (that draft is 184 bytes vs 180: wrong size; the natural 8w draft has the right size).
- Flag sweep (~45 single extra C->asm flags: -fno-rerun-loop-opt, -fmove-all-movables, -fforce-addr,
  -fno-rerun-cse-after-loop, -fno-expensive-optimizations, -fno-force-mem, -fno-regmove,
  -fno-cse-follow-jumps/skip-blocks, -fno-gcse-lm/sm, -fargument-noalias(-global), -freduce-all-givs,
  -fssa, -fno-schedule-insns(2), -fno-delayed-branch, -O1/-O3, -mno-split-addresses, -mlong-calls...)
  on all 7: none improves any. Do not repeat.
- 001cfc28 (-fsched-verbose=4): at t=5 dsll v1,8 (insn 155) and li.s f1 (178) tie on priority, class
  and dependent count (the call takes an ANTI dep on the last setter of every call-used reg), so LUID
  decides. li.s has no in-block predecessor; dsll cannot issue before t10 (7-cycle dsll32 chain). A
  reload-rematerialised li.s would still get an earlier LUID. Stuck: no plain-C dependence.
- 001f18e8: all registers right, only li 63 / li 1 order. d[0] store must precede d[3] in sched1
  (tag spill store sw 60(sp) sits between and may alias); li 63 must precede 0x4007/22/68/66/1;
  the a0/v1 assignment needs more refs on the 63 pseudo. Tried `d[3] = 63` at all 12 header
  positions, `k3 = 63` before the dead test (24w), k3 global (18-20w).
- 001f2630: hoisted `s32 k8 = 0x8000` before the loop is rematerialised but the spilled pseudo moves
  every parameter reload from a0 to a1/t2 (34-39w).
- 00125240: x has refs 6 and life <= 24; 1e4 would need life < 4 to win f0.
- Facts: EE sched1 gives ashldi3_internal4 (dsll32 of a zero-extend) and movsf constants (li.s) 7-cycle
  latency, sched2 gives li.s 2. In sched2 a call ANTI-depends on the last setter of every call-used
  reg, so that dependent-count tie-break never separates two such insns.
