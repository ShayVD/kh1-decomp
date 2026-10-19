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
