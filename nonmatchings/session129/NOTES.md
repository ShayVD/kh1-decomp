# Session 129 notes (matching track, one worker)

**No new matches: 6,981 / 6,988 still.** One draft improved (001c62a0 15 -> 14), one tie with natural
types (00200e28 24). `make` byte-identical with 6981 functions, `make report` 100% for all 6981,
`make shift` M0 OK, `make test` selftest PASS. shift/drafts.tsv: 001c62a0 now points at the 14w draft
(drafts.py build compiles it); 00200e28 stays on s12w14.

| function | before | after | matched | what decided it / file |
|---|---|---|---|---|
| 001c62a0 | 15 | **14** | no | permuter: a `struct Lk *lk0 = &ent[0].lk` local set before the guard (s129__001c62a0_14w_lk0.c). Left: global-alloc order of base/b and loop.c's d hoist (s22/s23) |
| 00200e28 | 24 | 24 (natural types now 24 too) | no | permuter moved v[0].z after v[0].f on s23m2's 25w natural draft (s129__00200e28_24w_natural_perm.c). Left: sched1 tie-breaks + knock-on local-alloc in the one 390-insn block |
| 001fd858 | 1 flagged | - | no | not reworked: reorg's annul decision (s13w4, s128) |
| sceGsDefDispEnv | 4 | - | no | not reworked: sched2, the off[] loads depend only on the trap_if (s23m1, s128) |
| 0010d470 | 170 | - | no | not attempted: jump2 cross-jump of cases 24/25 (s14m, s23) |
| 00110618 | 93 | - | no | not attempted: one-block FP global-alloc permutation, draft 16 bytes long (s12-s19) |
| 001636d0 | 394 | - | no | not attempted: 394 words is out of permuter range |

Scores are true DP LCS words (tools/matching/sc6_s12.py with ROOT patched to /home/user/kh1-decomp).

## Permuter runs (about 4 hours, 4 cores, two runs of -j2 at a time)
| run | base draft | iterations | permuter score base -> best | best by our measure |
|---|---|---|---|---|
| 62a0 a | s22m1 15w (nostrict) | ~36,600 | 1030 -> 740 | 15 (the 740 / 760 outputs are 20-24w, size 1156) |
| 0e28 a | s23m2 25w natural (nostrict) | ~18,100 | 3060 -> 2910 | **24** (2910 output) |
| 62a0 b | s23m2 35w cfirst_cn | ~23,000 | 695 -> 695 | 35 |
| 0e28 b | s12w14 24w k-vars (strict) | ~11,000 | 2500 -> 1525 | 24 (all lower permuter scores are 26-39w) |
| 62a0 c | s22m1 15w, PENALTY_REGALLOC 5 -> 50 | ~30,000 | 2560 -> 1960 | **14** (output-2420-2) |
| 0e28 c | 0e28 a's 24w output, PENALTY_REGALLOC 50 | ~14,500 | 4620 -> 3920 | 24 |

- The permuter's score does not follow ours on these two: its regalloc penalty (5) is tiny next to
  reordering (60) and insertion/deletion (100), and what is left in both functions is register
  allocation and issue order. Most "improvements" it reports are worse by word count. Raising
  PENALTY_REGALLOC to 50 (src/scorer.py of the clone in tools/toolchain/decomp-permuter; put back to 5
  afterwards) is what found the 14w. With the default weights, score every output with the real pipeline.
- For 001c62a0 the permuter weights look like 1030 (15w) vs 695 (35w): it rates the s23m2 shape higher
  (structure right, registers wrong), which agrees with s23m2's reading. 23k iterations on that shape
  found nothing better.

## 001c62a0: 15 -> 14
`struct Lk *lk0;` declared before `Cam *c;`, `lk0 = &D_0037A380.ent[0].lk;` right after
`D_0037A380.n = *p++;` (before the `n > 0` guard), and the i == 0 arm as `lk_init(lk0);`. &ent[0].lk now
gets t8 like the original. It is issued in the prologue (`addiu t8,v1,448` before the guard, original
`addiu t8,s1,448` after it), but the preheader's t6/t8/s4/t5 sequence lines up better. Placement: after
the guard 15, after `b =` or `i = 0` 20, as the first statement 28 (size 1172). The rest is unchanged
from s22m1: b s1 / base s4 (orig base s1, b s4), i's `move s0,zero` after the guard, d as `lui/addiu
t2` remat (orig `addiu t2,s1,80`). The permuter's other change in that output (`j = 2;` and
`ent[0].f[j]`) does nothing (14 with or without it).

## 00200e28: natural types reach 24
On s23m2's 25w natural draft (plain u64 PH/PQ, the sibling 00200648's types), writing the
`v[0].z = 0x100000` store after `v[0].f = 0x8000` gives 24, the same count as s12w14's union/k-var draft.
The leftovers are the s23m2 list (li eeeee / 66 / 6 order, sd 48 vs 56, `sll w` + `slti` late with slti
in a1, C[0] / e[0] registers). No permuter output got below 24 in ~43,000 iterations on three bases.
Since the natural shape is the likely source, it is the better base for future work. Not put in
drafts.tsv (same count).

## Recipe details (on top of session 128's)
- `tools/permuter.py import func_X --file draft.c --out-dir src/hand/nostrict` gets the nostrict flags.
  It clones decomp-permuter into tools/toolchain/ on first use.
- 001c62a0: the `V4` typedef's `__attribute__((aligned(16)))` is stripped by the import's
  `-D__attribute__(x)=`. That changes the inl_cpy copies, so compile.sh puts it back with sed
  (`s/} V4;/} __attribute__((aligned(16))) V4;/`). The d pin is written `f32 *dpin;` in base.c, and
  compile.sh turns it back into `register f32 *dpin asm("$10");`.
- 001c62a0 target.s: `kh1tool.py asm` writes the &D+0xE0F0 field accesses (`lui $at,1; addu; sw
  -7952($at)`) as `%hi(D_0000E0F0)` / `%lo(D_0000E0F0)` (also E0F4, E0F8, E0FC). Replace them with the
  numbers 1 / -7952.. and reassemble target.o. One `addiu v0,t9,-23680` (a bare %lo(D_0037A380)) stays
  numeric in target.s, so the permuter base never reaches 0 on that word (+1 constant penalty, harmless).
- 00200e28: rename func_00266c08 / func_00266f38 to sceDmaGetChan / sceDmaSend in base.c (target.s uses
  the registry names). A second directory (func_X_b, func_X_c) with a copied target.o / compile.sh /
  settings.toml and a base.c preprocessed the same way (`ee-gcc -E -P -x c -Iinclude -I<mode dir>
  -D__attribute__(x)=` on `#include "m2c.h"` + the draft) runs another base next to the first.
- Scoring outputs: copy source.c into src/hand/nostrict/ (or another path whose kh1.toml mode gives the
  right flags), apply the same seds, and run sc6_s12.py; delete the copy afterwards.
  About 4-5 iterations a second per -j2 run here (faster than s128's estimate for these files).
