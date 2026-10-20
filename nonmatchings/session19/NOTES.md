# Session 19 notes

## s19m1: 001cfc28, 0021e120, 001eddc0 MATCHED (register-pin lever on older drafts and findings); 001f2630 stays 1w

Counts are true DP LCS words (sc6_s12.py with ROOT patched to the worktree).

| function | mode | before | after | where |
|---|---|---|---|---|
| 001cfc28 | hand | 1 | **0, MATCHED** (1e3ad5e) | src/hand/text_001c0000_s19_s19m1.c |
| 0021e120 | hand/nostrict | 3 | **0, MATCHED** (c84570f) | src/hand/nostrict/text_00210000_s19_s19m1.c |
| 001eddc0 | hand | 2 | **0, MATCHED** (3686f2c) | src/hand/text_001e0000_s19_s19m1.c |
| 001f2630 | hand/nofill | 1 | 1 | - (no better draft) |
| 001f1fc8 | hand/nofill | 2 | 2 | - (11w finding probed only) |

All three matches are FLAGGED (local register variables; 001cfc28 also keeps two volatile Msg fields).
Housekeeping as in session 18: export_unmatched.py removed the three shift/unmatched/*.s files, and their
drafts.tsv lines are gone.

### The angle: go back to the old findings and hacked drafts, not the best drafts
Each of the three had an earlier draft or finding whose schedule was already right and whose only fault was
a register choice. Before session 18 nothing could fix that. A pin can.
- 001cfc28: s11w15's 6w finding (`f32 one = 1.0f;` at the top plus volatile `type`/`v3`) already had the
  original's dsll / li.s order. Its only fault: the moved 1.0 got f0 and the c*2.0f chain f1. Pinning the
  chain with `register f32 t asm("$f0"); t = (f32)c; t = t + t; m.v[0] = t;` gives a match. As one statement,
  `t = c * 2.0f`, it stays at 6w (the pin dissolves). Without the volatile fields: 6w.
- 001eddc0: s11w67 had shown that WITHOUT the dead tests (9 blocks, so sched1 uses one interblock region) the
  schedule and the bc1f delay slot are right, and only global-alloc is wrong (g takes a0, a.r a1). Fix:
  remove the dead tests and pin the a.r load, `register s32 ar asm("$4"); ar = a.r;`, used for both g and c.r.
  The same pin as u32 gives 416 bytes: the u32 subtract makes the float conversion unsigned.
- 0021e120: s18m1's leftover (1) was the output dependence of the 2nd func_0011fbb0 call's `move t0,zero`
  argument on the pinned k66 set. That dependence raises the argument move's sched1 priority. Pinning the
  header's a2 and a3 constants too (63 -> $6, 0x2006D0059D30B600 -> $7; both are the original's registers)
  puts the same output dependence on the a2/a3 argument moves. All three rise together and keep source
  order: 3 -> 2w. Then an exhaustive two-line position search (`p[0] = k0;` x `k66 = 66;`, 552 compiles,
  about 100 s) found 0 at p[0] after the k6 set (k66 position unchanged). pclimb_s15 from the 2w state
  stopped at 1w (moved k66 too early).

### When does a pin survive? (refines the session 18 rules)
Pins of these held: constants (0021e120), a u8 load converted to s32 whose uses lie in a LATER basic block
(001eddc0: c.r = ar + g sits after the unsigned-conversion branch), and a float chain written as two
statements into the pinned reg (001cfc28).
Pins of these were dissolved (byte-identical to unpinned): in the 001f2630 and 001f1fc8 glyph loop blocks,
`ch = cy + h` (also `ch = h; ch = cy + ch;`), `p288 = f4 + 288`, and the halfword loads `f2 = gl->f2` /
`f4 = gl->f4`. The 00.rtl dump shows expand computing into a pseudo and copying it to the hard reg
(`(set (reg/v:SI 4 a0) (reg:SI 224))`). cse then replaces every use in the same extended block, so the copy
dies. Working rule: a pin on a computed value survives only when cse cannot see all its uses (a use in a
later block) or the value is built in place in the pinned reg (`t = x; t = t + t;`).

### 001f2630 (stays 1w) and 001f1fc8 (stays 2w): closed for pins
- 001f2630, 1w draft: 0x8000 pinned to a1 (`register s32 k asm("$5")`), with the set and the x2c store at every
  position pair in the glyph block (153 compiles): all 22w (the hard-reg set at block entry reshuffles sched1).
- 001f2630, w65 9w finding: pins p288 -> a2, 22 -> a3, f4 -> t0, gk -> a1 in all subsets: 9w (the
  computed/load pins dissolve, see above) or 21-23w (the constant pins).
- 001f2630, w40 35w finding (exact store order, wrong reload register for h): cy+h pinned to v1 or a0 in
  three spellings: identical output (dissolved).
- 001f1fc8, s12w19 11w finding (3 wrong block registers): f2 -> t4, cy+h -> t0, f4+288 -> t2, alone and
  together: identical output (all dissolved).
- For both, the leftover is sched1 store order inside one big block. Pins that survive there (constants)
  only make that order worse. They look unreachable with this lever.

### Not tried
001fd858 (reorg annul proof in s13w4/s15: a v0 reader would add code), 00125240 (s18m2: a HIGH), 001636d0 and
0010d470 (no time left after the three matches).
