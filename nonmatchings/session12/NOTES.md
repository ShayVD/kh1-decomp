# Session 12 worker notes

## s12w3: 00125240, 0024c950, 001ba520, 001137f8, 00265608 (no matches)
- 00125240: 6 -> 5 words (s12w3__00125240_5w_flagged.c, hand/strict, flagged dead FP test
  `if (p[-1].x < -10000.0f) y = 0; else y = D_004F77E0;`). Off: second 1.0f store (p->w) gets its
  own pseudo in f4 (reload_cse makes `mov.s f4,f3`), a0/a1 lui order, 1e4 store before -1e4.
  Probably an artifact: original has one 1.0 in f3. Tried ~15 climbs, test at every position,
  chained 1.0 stores, `one` var, dead read of D_004F77E0 before the test (13w), 77E0 store before
  the test (13w).
- 0024c950: stays 8w (w45). Dead tests that ce removes with PRE-able reads in the else arm are a
  dead end (life1 deletes or no refs gained, 9w); tests before the A68/A6C stores break gcse
  address sharing (24w).
- 001ba520: non-volatile sqrt asm gives 72w; the volatile barrier is right.
- 001137f8: 11w re-verified; only prologue order and the 1<<32 register are off. 1<<32 is one RTL
  movdi (gas expands dli): no source route to raise its sched1 priority found.
- Facts: REG_N_REFS is recounted after ce, so a dead FP test removed by ce adds no refs for
  local-alloc (only cse1/gcse block structure changes). A dead read of a symbol in one arm makes
  gcse PRE put the HIGH in both arms; ce then if-converts it away before sched1. cse knows
  `p->x == 0` after a `sw $zero` store, so tests on it fold early; use p[-1].x. A test with no
  else arm survives to flow2 (real split for sched1 and both allocators).

## s12w2: 0019f1f0, 001eddc0, 0021e120, 00120cf8 (no matches)
- 00120cf8: 4 -> 3 words, NATURAL (s12w2__00120cf8_3w.c, hand/strict). Divisor `n` set twice
  (`n = 3;` at the top of the outer and of the inner loop body, used as `k % n`): loop pass 1
  moves the inner set to the inner preheader, the outer loop sees two sets and does not hoist,
  which fixes the outer giv. Left: `li t0,3` stays in the inner preheader; the original has it in
  the outer preheader after `move t2,zero` (loop pass 2 moved it).
- 0019f1f0: 8w finding (s12w2__0019f1f0_8w_finding.c, nostrict, RO=0048FCB0), worse than w57's
  2w but the TAIL insn order matches exactly using three loop-note barriers per TAIL copy.
  Left: local-alloc swaps ft/fu FP regs (ft lives 7 sched1 insns vs fu 5).
- 001eddc0: stays 2w (w64, flagged). In a 9-block shape sched1 already puts the c.r store after
  the fix, but a.r cannot win a0 in global-alloc (~60 variants, 14-16w).
- 0021e120: stays 3w. The sched2 barrier is the 33-ref flush insn (34th ref, sw [2].u at 96); the
  original's flush is in the same place, so the flush lever cannot help. sd 0 loses on LUID.
- Facts: ee-gcc2.96 accepts -fsched-verbose=2 (ready lists in .sched dumps). jump2 cross-jumping
  runs after sched2, so each tail copy is scheduled separately. Between loop passes 1 and 2 only
  delete_trivially_dead_insns and reg_scan run, so a redundant second set survives to pass 2. A
  loop-note barrier is the first insn after the notes in source order; pick a long-latency one.
- Helpers (copied to tools/matching/): dif_s12.py (LCS + word diff), cc_s12.sh (-da dumps, EXTRA
  flags), deps_s12.py (forward deps per insn from a sched2 dump), pref_s12.sh (global-alloc prefs).
