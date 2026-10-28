# Session 144 notes (matching track: the main ELF's last 7)

**No new matches: 6,981 / 6,988 still.** One draft improved (00200e28 24 -> 23, natural types). `make`
byte-identical with 6981 functions, `make test` PASS, `tools/shift/drafts.py build` compiles every draft
(shift/drafts.tsv now points 00200e28 at the 23w draft).

| function | before | after | what decided it |
|---|---|---|---|
| 00200e28 | 24 | **23** | tools/matching/climb_s144.py on s129's natural draft (s144__00200e28_23w_climb.c). Left: the sched1 / local-alloc family s23m2 / s129 list |
| 001c62a0 | 14 | 14 | ~150,000 climb steps (statement moves, declaration swaps, operand swaps): never below 14 |
| 001fd858 | 1 flagged / 25 natural | same | climb: 25 stays 25 with dependency checks. gdb on reorg: two more causes ruled out (below) |
| 00110618 | 90 | 90 | ~40,000 steps, nothing better by the true count (difflib's count went 103 -> 100, the DP count got worse, and the moves crossed sceVu0UnitMatrix) |
| sceGsDefDispEnv | 4 | - | not reworked (sched2: the off[] loads depend only on the trap_if, s23m1 / s128) |
| 0010d470, 001636d0 | 170 / 394 | - | not attempted (jump2 cross-jumping; out of a climber's range) |

## climb_s144.py (a permuter substitute)
decomp-permuter could not be run here (cloning and running it was refused by this container's tool policy), so
I wrote a small climber on the in-repo scorer: `WDIR=DIR python3 tools/matching/climb_s144.py SRC ADDR TAG
STEPS [SEED]`, with SRC copied under a directory whose kh1.toml mode gives the right flags (src/hand/nostrict/
here; delete it afterwards). lro6_s12.check compiles and links in process at ~5 to 30 evaluations a second, so
40,000 steps take about an hour per core. lro6_s12.py and sc6_s12.py now find the repo from their own path
(they had /home/claude/kh1-decomp hard-coded).

**Keep the dependency check.** The first version moved statements by indentation only. On 001fd858's natural
draft it reached 9 words (25 -> 9 in a few minutes) by moving `o->d0 = max;` out of an `if` arm and across
the `clampA:` label: the code was wrong, and the count was low because the wrong code happened to line up
with the original. The committed version only moves a statement past statements of the same block with no
call and no shared variable or field name (`can_move`), and with it the same draft stays at 25. The 23w
00200e28 draft was found with the checked version (its moves are independent stores and one `x <<= 4`).

## 001fd858: the 0x654 bnezl, more of the reorg state
gdb on cc1 (it has symbols), the 1w flagged draft, branch insn 1635, fallthrough insn 2187:
- `find_basic_block(2187)` returns block 88 (found), and mark_target_live_regs gives [a0, s0, s1, sp].
- Forcing `find_basic_block` to return -1 there (the "assume everything is live" case, which a fallthrough
  after a label created after flow would hit) still gives `bnez`: the result is all-live ANDed with the
  live set at the jump target found by find_dead_or_set_registers ([s0, s1, sp] at the fe408 block), so v0
  is dropped again: [a0, s0..s8, sp].
- Forcing `likely = 1` (mostly_true_jump == 2) for that fill does not change the output either.
So neither a stale basic-block lookup nor the branch prediction makes the annul; only v0 live at the end of
the fallthrough's jump chain does, as s13w4 found by forcing opposite_needed. No path from there reads v0 in
the final code, so this stays closed until a source shape is found where the fallthrough's jump, at reorg
time, leads somewhere that reads v0 before a call.
