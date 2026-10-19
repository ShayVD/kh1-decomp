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

## s12w7: 001636d0, 001fd858 (no matches)
- 001fd858: 186 -> 112 true-LCS words (s12w7__001fd858_112w_tlcs.c, hand/nostrict, size 1908
  right). Shared `call:` tail written out at each of its 3 gotos (`r = func_001fe1b8((Scr*)o);
  goto done;`; cse1 deletes the `move a0,s0`, 186 -> 123); `o->d6 = 0; goto done;` in the d0<=0
  and d0=t arms (115); in DE8 `o->d0 = max; goto clampA;` with clampA before `r = 1; o->d6 = 0;`
  in DE4 (112). Off: entry global-alloc priority (cc copy .435 > (s16)ce .29, pad .326 > d0 .22);
  DE4/DE8 tail 2 cross-jumped the wrong way (a dead set fixes it, 108w, but jump1 store-flag
  converts DE8, size 1924); clampA sched2 order; smoothing-tail registers; 0x2c HIGH PRE copies.
- 001636d0 stays 410 (s7 draft, hand/nostrict, 4248): opcode sequence identical, every word off
  is a register or spill slot. The original lacks gcse cprop of `j = i` (keeps a j*64 giv copy
  spilled at 364(sp)), gcse PRE sharing `(s2 & 3)` with the switch index, and pp REG_EQUIV.
  -fno-gcse reproduces the first two but breaks the entry (429-439). Open: the original does not
  cross-jump the asm-identical inner case 0/1 tails (0xe78-0xeb4 vs 0xf54-0xf8c).
- Facts: a shared call tail written out per goto lets cse1 follow-jumps delete the arg move.
  jump2 cross-jumping needs >= 2 matching insns for jump-to-jump tails. Cross-jump direction
  follows jump_chain order (earlier jumps lose their tail). Stray nops before labels after
  barriers are `.p2align 3,,7`. Spill slots are assigned in regno order. gcse records a copy only
  if neither side is modified later in the block; cprop skips regs set earlier in the block.

## s12w9: allocator levers on 001f18e8, 001eddc0, 0024c950, 00216890, 001ba520, 00166570
- 0024c950: 8 -> 5w (s12w9__0024c950_5w_flagged.c, hand/nofill, size 1172, flagged dead FP test).
  All 5040 orders of the kk block + test: `t = 11; if (D_00669A5C) t = 0; D_00669A6C = x;
  D_00669A68 = x; p = D_00669A40; yy = y + t; if ((f32)D_00669A5C < (f32)(D_00669A5C + 1)) c = 0;
  else n = 0;`. Left: the test's int temp `D_00669A5C + 1` (local, life 2, prio 5000) takes v1
  before the A68 lui/addiu pair (2000), so A68 a1 / A40 high v1 (original A68 v1, A40 a1);
  `sw A68` issues after the p spill.
- 00216890: finding only (s12w9__00216890_19w_finding.c, 19w; best stays s12w4's 11w). `s32 **q;`
  at outer level, `q = &D_003F43C8[j];` at the top of the inner loop body: loop.c hoists it with
  REG_EQUIV, gcse PRE leaves the HIGH alone, reload emits the original's tied lui/addiu. Left:
  reload handles insn 1270 (k loads) before 1263 (q); ty/chain swap s7/s8.
- 001f18e8 stays 2w (sched2 order li 1 / li 63; registers right). A constant set before a dead FP
  test and used once after is update_equiv_regs-moved next to its use (life 2); two such
  constants never overlap and share a register.
- 001eddc0 stays 2w: local qtys allocated while a global is live go into its conflict set, so a
  merged a.r/sum global loses a0 to join-block locals.
- 001ba520 stays 10w (sched1 store order, not allocation). 00166570 not retried (gcse PRE).
- Helper: tools/matching/gdb_s12/rlall.gdb (every insn's reload regs and last_spill_reg).

## s12w12: 00216890 MATCHED (natural), 0024c950 stays 5w
- 00216890: src/hand/text_00210000_s12_s12w12.c. From s12w9's finding, but with no q or tb locals:
  index directly in the inner loop (`c = D_00642CD8; switch (c) { case 0: default: w = 2 -
  D_003F41E8[c][j]; ... } str = D_003F43C8[j][m];`). loop.c still hoists &D_003F43C8[j] to the
  inner preheader as REG_EQUIV (HIGH stays tied). Without the hoisted tb lo_sum, q's insn issues
  before `k*8 + k` in sched1, so reload and global-alloc follow the original.
- 0024c950: ~25 more attempts, stays 5w. The A40 HIGH must find v0/v1/a0 busy when allocated;
  every test form puts its int temp in v1 over [10,18], overlapping the A68 HIGH [6,20]. Closest
  structure: `(f32)D_00669A5C < (f32)(D_00669A5C + t)` (6w; temp ties into the load's qty).
- Facts: in sched1 an insn setting a pseudo that crosses no call depends on the last call; a
  call-crossing invariant hoisted into the same preheader has priority 1 and loses slots by LUID
  to earlier hoisted insns, so dropping one hoisted insn can reorder reload for the whole
  preheader. A dead-test temp that is its source's last use ties into that qty (refs without a
  new GPR temp). Local-alloc conflict ranges run born_index..dead_index (about 2 indices past
  birth/death each side); qtys sharing an endpoint conflict.

## s12w11: 00265608, 001f2630, 001f1fc8, 0021e120 (no matches)
- 00265608: finding s12w11__00265608_26w_finding.c (sdk/gcc991111, size 884; best stays s9 w11 9w).
  The source tree `((M|X)|(Y|H))|W` (inline or u64 leaf locals) folds to the original's OR shape
  with the right cross-jump (98 of 1680 ordered trees). Only allocation is off: the original
  needs Y > W > X > mult > H priority (the H-first order `div, addiu a3, lw a1, dsll32, lw v1`);
  ours issues both off[] loads first because the trap_if at t=1 is a barrier with anti-dep cost
  1, so they are ready at t=2. No source shape found for that.
- 001f2630 1w: stores in a big flood wait on the last s32 load, then issue by LUID; constant li's
  fill stall slots in LUID order. The original's store positions need impossible lives
  (cy+h < 0x8000 < f4+288 < 22). 001f1fc8 2w: same mechanism for `one`.
- 0021e120 3w: 22 positions of `p[0] = k0;`: earlier fixes sd-0 vs 88 but swaps k0/66 (t0/t1)
  because 66's store then dies at 170, conflicting with the 0x100000 qty born at 172.
- Facts: gcc991111 reassociates OR trees of local-variable leaves like inline expressions (search
  by produced shape). gcc991111 local-alloc traced without debug info: break block_alloc
  (0x08111ef0); statics next_qty 0x082233f8, qty_phys_reg 0x082233fc (short*), qty_n_refs
  0x08223410, qty_birth 0x08223418, qty_death 0x0822341c, qty_size 0x08223420, qty_first_reg
  0x08223434 (tools/matching/gdb_s12/bq9.sh + bq9.py).

## s12w10: 001137f8 MATCHED (natural); 00200e28, 00192958, 001c62a0 unchanged
- 001137f8: src/hand/text_00110000_s12_s12w10.c. Store base as a pointer local initialised first
  (`u64 *p = D_002BCE00;`), then `a =`, `col = 934C`, `col |= 9358`, `b =`, `col |= 9354/9350`
  (4 of 120 orders with p first reach 0). Sched1 HIGHs all have priority 27 and the base HIGH ties
  at 24 with the 1<<32 / 0x100D17A88 constants; ties go to the lowest LUID, so p first puts the
  base HIGH ahead of both constants and local-alloc gets the original's registers.
- 00200e28 stays 25: two single-statement moves give 5 of 6 role values the original's register
  (d8 after the tag statement; `v[0].u.z = e[0];` before regs2), but TLCS rises to 35 (climbed
  order); clb6 from there bottoms at 31.
- 00192958 stays 17: the swapped TI constants (zbuf/scissor) are REG_EQUIV constants that reload
  substitutes with spill registers ("Using reg 9 for reload 1"), so it is reload spill rotation,
  not local-alloc priority.
- **Local-alloc simulator** tools/matching/la2.py: reads a .lreg dump and reproduces local-alloc
  exactly on single-block functions (107/107 pseudos on 00200e28). Rules: two passes (qtys with
  suggestions try only suggested regs on their exact interval; the rest try a widened interval
  [b-2+b%2, d+2-d%2) then the exact one; the widened one is marked busy); lifetimes
  [2n_set, 2n_death); outputs tie to a dying direct operand of the same size (not inside mem or
  sign_extend); order v0..t7, s0..s7, t8, t9, s8; call-crossing qtys get s regs only; an unused
  v0 call result does not block v0.
- tools/matching/osrch_s12.py DUMP LO HI '{reg:"name"}': anneals a minimal change to the sched1
  order that reaches a target allocation (found 001137f8: 5 swaps pointing at the base HIGH LUID).
- Base-pointer lever: a pointer local set at the top gives the base HIGH a low LUID, so it wins
  sched1 priority ties against constants.

## s12w13: 00120cf8 MATCHED (flagged); 00125240, 00166570 unchanged
- 00120cf8: src/hand/text_00120000_s12_s12w13.c. FLAGGED: a no-op save/restore of the divisor in
  the inner body (`n = 3;` top of outer body, `s32 e = n;` top of inner body, `n = e;` at its end).
  gcse cprop rewrites `n = e` to `(set n n)`, which survives loop pass 1 as a second set (outer
  loop refuses to hoist n), then delete_trivially_dead_insns removes it between the passes and
  pass 2 hoists `li 3` after the giv inits. The `== 1` test stores in both arms (plain C): one more
  inner-loop insn at sched1 makes n and &m[i][i] tie in global-alloc (lower regno wins); jump2
  merges the stores.
- 00125240 stays 5w: chaining the 1.0 stores shares the pseudo but x/1e4 swap f0/f1; a no-else
  test with a climbed order gets every FP reg right but leaves the 77E0 lui late (6w).
- 00166570 stays 21w: at -O2 expand_call puts every `(plus sp N)` call arg in a pseudo, so gcse
  always sees these addresses; no source change keeps PRE away.
- Facts: loop.c refuses to move regs created during the same pass (REGNO >= max_reg_before_loop).
  update_equiv_regs doubles REG_LIVE_LENGTH for pseudos with a REG_EQUIV constant (hoisted
  constants lose half their global priority). sched1 recomputes REG_LIVE_LENGTH per region
  (real insns only); .lreg numbers are post-sched1. Inner-loop `do {} while (0)` wrappers do not
  change REG_N_REFS loop depth.

## s12w14: 0024c950 MATCHED (natural, the dead test is gone); 00200e28 25 -> 24
- 0024c950: src/hand/nofill/text_00240000_s12_s12w14.c. `h = 11; if (D_00669A5C) h = 0;`, no yy
  variable, the call takes `y + h + 1` inside the loop (loop.c hoists `y + h` to the end of the
  preheader, so t lives longer: load v0, t a0, A68 HIGH v1, A40 HIGH a1; la3 + osrch pointed at
  this); stores `D_00669A68 = x;` then `D_00669A6C = x;`; loop indexes `D_00669A40[i]` instead of
  pointer p (a loop giv gets a higher pseudo number, and spill slots follow pseudo number).
- 00200e28: 24w true LCS (s12w14__00200e28_24w_tlcs.c, hand/strict): every header constant a u64
  variable set at the top in the original's li order, then a store-order climb; li sequence now
  exact. Off: d8 and 68 li early, sd80/sd48 order, `sll w`/`slti` late, local-alloc group.
- 0021e120 stays 3w: with all-local allocation the target looks unreachable (store classes by
  overlap with later Vx stores; sd 0 first makes 5000 die earliest, it takes a2 not t1).
- 001f18e8 stays 2w: needs a filler insn between li 4000 and li 63; sched1 always puts
  `tag = p + 5` in the free ALU slot of the sd 8 cycle.
- tools/matching/la3_s12.py: la2 with fixes (hard regs are regno < 80 so $fcc0 is not a pseudo;
  SF/DF/CC qtys left out of the GPR pool; int/float operands never tie; .lreg refs lines have no
  ";;" prefix). Exact on 0024c950's join block, 0021e120 block 0 (37/37), 00200e28 (96/96).
- Levers: write an invariant expression at its use inside the loop to delay it in sched1 (loop.c
  hoists it to the end of the preheader); index arrays in the loop instead of pointer locals to
  move spill slots; set header constants in u64 variables at the top to fix li order independent
  of store order. With one memory unit, the second issue slot of each store cycle goes to the
  best-ranked ready ALU insn. REG_EQUIV constant sets move next to their use after sched1.
