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

## s13w2: 00265608, 00192958, 00166570, 00200e28, 001c62a0 (no matches)
- 00265608 sceGsDefDispEnv stays 9w in every gcc991111 mode (990721: 24w; 2.96: 68w). sched2: the
  div's trap_if issues no-unit at t=1 with `w+2559`; both off[] loads anti-depend on it and are ready
  at t=2, so div + off[0] load issue at t=2 and the memory unit blocks the second. The original issues
  div + H at t=2, which needs the trap at t=2 (a dependence plain C does not give). Four scalars for
  off[4]: no change.
- 00192958 stays 17w. New finding s13w2__00192958_19w_finding.c: `i = sc->scy0; b[1] = oy + (i << 4);`
  (scy0 truncate in a variable another statement also sets) puts the dsll32/dsra32 at the original's
  0x192adc; registers then swap (a1/a3). TI header constants get regs in birth order on priority ties;
  the original allocates sc before zbuf though zbuf is born first. la4_s12 mispredicts this block.
- 00166570 stays 21w: in the original pa/pb are copies of the CopyMatrix argument pseudos and die by
  the preheader; every post-loop frame address is recomputed (addiu sp,16 both sides of a call).
- 00200e28 (24w) and 001c62a0 (56w) re-verified only.
- Facts: gcc991111 runs flow2, sched2, then jump2 (cross-jumping after sched2). It expands a division
  as div + trap_if, and sched1 moves the trap ahead of the div; the trap counts toward issue rate 2.

## s13w3: 001fd858 112w -> 1w (flagged) / 25w (natural); 00110618 stays 93w
- s13w3__001fd858_1w_flagged.c (hand/nostrict, size 1908 right, CONTEXT_ONLY fe1b8/fe408/fe4e0): a dead
  float test `if ((f32)r < 0.0f) t = 0;` at the join of the 0x300 if/else chain before `goto fade`.
  Last word: 0x654 original `bnezl` (annulled), ours `bnez`: reorg fill_slots_from_thread annul decision
  (fallthrough opposite_needed is [a0,s0,s1,sp], no v0). Pos-clamp variants b-e worse.
- s13w3__001fd858_25w_natural.c (no tricks, 1900 vs 1908): fade cross-jump direction (DE8 into DE4)
  needs the forwarder. Natural changes 112 -> 25: d6>0 smoothing written out in up and down paths;
  `s32 f = o->d0 & 0xf` set in all 4 smoothing places; separate m and m2 masks; `max = o->ce << 4`
  before the `y0 > 0` test; in pos f, t, then max; DE4/DE8 clamp tails written out (no goto clampA).
- 00110618 (one basic block): our fbn (refs 5) fails local-alloc and takes f24 in global-alloc by
  evicting fb's local qty (global.c "kick out poorly used local regs"), so fb lives in memory; global
  sxd gets f31 by copy preference (eviction scan runs top-down). The original likely evicted l's f28.
  Tried libvu0-style inline ViewScreen/ViewClip (172), az in stores (174), no fbn (161), az after
  UnitMatrix (139, climbed 107).
- Facts: in a single-block function sched1 moves long-lived values across calls; temps stay between
  neighbouring calls. local-alloc ties combine pseudo chains into one qty. jump2 cross-jumping of
  duplicated code adds refs before regalloc. One variable for two lives unions their conflicts. A dead
  FP test at an if/else join leaves a forwarder jump2 still sees (flips cross-jump direction); integer
  dead tests are removed too early. find_cross_jump stops i1 at a CODE_LABEL but skips labels on i2.
- gdb tracers: tools/matching/gdb_s13/ (la: local-alloc qtys; ga/ga2: global find_reg incl. FP; rg:
  reorg; cj: cross-jump). The .sh files hard-code /tmp/claude-0/s13/s13w3 paths: edit before use.
