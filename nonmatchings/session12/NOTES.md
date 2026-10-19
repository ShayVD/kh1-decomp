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

## s12w1: 001cfc28, 001f2630, 001f1fc8, 001f18e8 (no matches, no better drafts)
- Re-verified: 001cfc28 w6 1w (strict), 001f2630 w32 1w LCS (nofill), 001f1fc8 w32 2w (nofill,
  RO=00490a80), 001f18e8 w52 2w (nofill, flagged dead FP test).
- 001cfc28: in sched1, insns with no in-block predecessor issue at t=0-4 and ignore the call's
  tick; the li.s 1.0 gets a low LUID and wins the sched2 tie with `dsll v1,8`. A dead FP test plus
  the identical arms makes 11 blocks (> the 10-block interblock limit: single-block regions,
  23-60w); without arms, all 40320 orders give 11w at best. `do {} while (0)` barrier: 3w at best
  (5040 orders). w54's f0/f1 swap: the 1.0 qty (2 refs / 2 insns) always outranks r140/r141.
- 001f18e8: kk=0xeeee is a REG_EQUIV constant with no hard reg; reload re-creates it before its
  single use and it ranks first in sched2. `k3 = 63` before `k9 = 1` fixes li order but lengthens
  63's life (20 vs 18 insns) and local-alloc gives it t0 (19w). Climbs bottom at 2w.
- 001f2630 / 001f1fc8: any dead FP test anywhere in the loop changes global-alloc for the whole
  function (205w+ / 183w+); the split lever is unusable in these glyph renderers. Memory typing
  cannot help (one base, different offsets, never conflict).
- Helpers: tools/matching/permx_s12.py (full or random statement permutations),
  hcx_s12.py (hill-climb keeping each set before its use).

## s12w4: 00216890, 00192958, 00166570, 00200e28 (no matches)
- 00216890: 13 -> 11 words (s12w4__00216890_11w.c, hand, size 1484). `str = (*q)[m];` before
  `x = D_003F4508[m];`; `s32 **tb = D_003F41E8;` right after q (loop.c hoists its lo_sum, leaving
  2 local quantities in block 42); cases ordered `case 0: default:`, 4, 5 (chain pointer born
  late, beats ty for s7). Left: reload round-robin one step behind in the preheader, `move s2,zero`
  misplaced. Cause (gdb on reload): the original needs the D_003F43C8 HIGH as a local quantity in
  block 42, i.e. gcse PRE did not hoist it; ours PRE-copies it onto the outer-loop entry edge.
- 00192958 stays 17: TI constants need live lengths 5000d < 1 < sc < xy < zbuf < frame; ours tie
  zbuf/xy/sc at 28. Permutations, early local defs, two climbs: no gain.
- 00166570 stays 21: gcse PRE reuses pre-loop sp+64/sp+128 after the loop; original recomputes.
- 00200e28 stays 25: all diffs before the 33-ref flush (local-alloc family).
- Facts: local-alloc with exactly 3 quantities allocated qty 0 first even when qty 1 had 3x the
  priority (gdb); dropping to 2 quantities fixes the exchange. After a call issues, anti-dependent
  local sets fill the call's cycle in source order. Global-alloc priority is an integer (ties go to
  the lower regno). Reload never uses the insn's own output reg for an input reload, so
  `lui rX; addiu rX,rX,lo` feeding the same output reg means a local HIGH tied to its lo_sum.
  Switch case order changes which invariants loop.c hoists in pass 2 and their LUID order.
- gdb helpers: tools/matching/gdb_s12/ (la.sh/laall.sh FILE BLOCK: local-alloc quantities;
  rl*.sh: reload register per insn and last_spill_reg).

## s12w5: 001db718 MATCHED (natural), 001c62a0 stays 56w
- 001db718 (40w before): src/hand/text_001d0000_s12_s12w5.c. Each table scan is
  `j = 0; if (X) { for (;;) { b = ...; if (match) { arr[..] = (u8)(b << 1) >> 1; goto end; }
  if (++j >= 48) goto end; if (!X) break; } }`. expand_end_loop rotates it; the leftover
  `jump start` block takes gcse PRE's insertion, so loop.c treats the loop as phony and hoists
  nothing (as in the original). `(u8)(b << 1) >> 1` (plain C, clears bit 7) gives the stored value
  its own pseudo, making `b & 0x7f` block-local (4 qtys).
- 001c62a0: 56w re-verified (hand/nostrict, size 1148); ~12 attempts no better. Most of the gap is
  the f/lk block: original uses an i*224 giv plus a second &D_0037A380 base rematerialised as
  `lui s6`. One-line edits swing it 56 -> 150w.
- Facts: **local-alloc sort bug with exactly 3 qtys in a block**: the hand-sort compares qty
  numbers 0/1/2 instead of qty_order entries, so qty 1 is never allocated first; 2 or 4+ qtys use
  qsort by priority. Fix by adding/removing one block-local pseudo. Trace: break on find_free_reg
  (tools/matching/gdb_s12/gtrace.sh + ffr_gdb.py). expand_end_loop (2.9x) does not rotate a loop
  whose last condition is one conditional jump followed by `goto end`; it only finds exits in the
  first ~30 insns; `goto label_after_loop` is not an exit, `break` is. Phony-loop recipe:
  `if (X) for (;;) { body; if (++j >= N) goto out; if (!X) break; }`.

## s12w8: 0019f1f0 MATCHED (flagged), 3-qty lever swept
- 0019f1f0: src/hand/nostrict/text_00190000_s12_s12w8.c (rodata RO=0048FCB0). FLAGGED: two empty
  `do { } while (0)` sched barriers per TAIL copy (after the int loads, before the stores), from
  s12w2's 8w finding. The ft/fu FP swap (a 13-qty block, qsort) is fixed by making fz, fu and one
  function-level variables set in both TAIL copies and multiplied in place (`fu *= key->sc[1]`):
  they become global pseudos, local-alloc handles only ft (f1), global-alloc gives fu f2, fz f3,
  one f4.
- The 3-qty sort bug had nothing to work on in 001cfc28 (7 qtys; 1w is a sched2 LUID tie),
  00125240 (10-11 qtys; x outranks 1e4), 00120cf8 (registers already match), 00200e28 (one block,
  96 qtys), 00192958 (only 3-qty block already matches).
- Inverse lever: move block-local temps into function-level variables set in two blocks to take
  them out of local-alloc (global-alloc assigns them after all local qtys, by global priority).
- Helper: tools/matching/gdb_s12/blkq.sh FILE [flags] (+ blkq_gdb.py): every block's qty count,
  first_reg, priority, phys reg, birth/death in one gdb run.

## s12w6: 00110618, 0010d470 (no matches, both improved; true LCS words of the original unmatched)
- 00110618: 149 -> 93 (s12w6__00110618_93w_tlcs.c, hand/strict, size 1088 vs 1072). sx2/sy2 are
  the same variables as sxd/syd (one pseudo set twice: f28/f29 in the original); an early
  `f32 fbn = -n + fb;` used by the second ViewScreen body. Matrix-store order is hill-climbed
  (not natural). Off: fb gets no register (global-alloc's find_reg hands f24 to fbn, fb reloads
  from 256(sp) 3x); fbn's local alloc fails (l chain takes f28, a long-lived 1.0f takes f26);
  swapped pairs sxd/syd, cz/az. The rest is local-alloc priority in one ~150-insn block.
- 0010d470: 196 -> 179 (s12w6__0010d470_179w_tlcs.c, hand/strict, RO=48cdf0, size 4120 vs 3968),
  all natural: case 10 reads its middle byte into c2; `if (str[pos] == 0) {...} else scale =
  o->x14;` (bnezl + lwc1); PUT_TAIL stores y, col, a, sc; final stores n, nl, w, x8. Off: c2 in
  a1 instead of a3 (one global c2 for every byte read in cases 9-15, 25 and the copy loop; it
  needs global priority below the copy-loop givs, ~1.7), so case 24's PUT copy is not
  cross-jumped into case 25 (52 words); case 9 address form; copy-loop registers.
- Facts: `objdump -d` hides zero words ("...") unless given -z: nops drop out of LCS counts built
  on its output. Global-alloc's find_reg steals a hard reg from local pseudos with lower refs per
  live length when a global finds none (they go to memory). Local qty priority =
  floor_log2(refs)*refs/(death-birth) exactly. Two values sharing one register across separate
  live ranges in the original: try one variable set twice.
- Helpers: tools/matching/sc6_s12.py (true-LCS scorer, -d aligned diff), clb6_s12.py
  (statement-order climber with true LCS, dependency/call constraints, optional TEMP annealing).
  Both use $WDIR for scratch.
