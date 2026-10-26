# Session 128 notes (matching track, one worker)

**Two new matches: func_001f1fc8 and func_001f2630, 6,979 -> 6,981 / 6,988** (commit "Session 128: match
func_001f1fc8 and func_001f2630", both in src/text/text.nofill.c). `make` byte-identical with 6981 functions,
`make report` 6981 at 100%, `make shift` M0 OK, host census links, `make test` selftest PASS.

| function | before | after | matched | what decided it |
|---|---|---|---|---|
| 001f1fc8 | 2 | 0 | yes | decomp-permuter (about 1,300 iterations) moved `cx += adv;` after `sceGsSyncPath(0, 0);` |
| 001f2630 | 1 | 0 | yes | the same change by hand (`cx += a;` after the sync call) |
| 001fd858 | 1 flagged | see below | no | reorg's annul decision (v0 liveness on the fallthrough), as s13w4 proved |
| sceGsDefDispEnv | 4 | see below | no | sched2: the off[] loads depend only on the trap_if, as s23m1 showed |
| 00125240 | - | - | (already matched in session 22) | the brief listed it, but it is in src/camera/view.c since s22m1 |

The nine holdouts are now seven: 0010d470, 00110618, 001636d0, 001c62a0, 001fd858, 00200e28, sceGsDefDispEnv.

## The match: why `cx += adv` after the sync call
In both glyph loops the pen advance sat between the two DMA calls (s11w32's drafts). Written after
`sceGsSyncPath` the leftover words (1fc8's `one` (sd 24) and x30 stores, 2630's x2c store, each issued a
few slots early in the glyph block) are gone and nothing else changes. I did not trace which pass this
goes through (cx is live across the calls either way; the add's position changes the insn numbering of
the loop body and cx's life inside the store block). Earlier sessions climbed the store order and
per-store volatile inside the /*P*/../*Q*/ block only and never moved the statements after it; the
permuter's statement reorder pass did.

Bookkeeping that came with it: 1fc8's jump table at 0x00490a80 is compiled rodata now, so the data piece
D_00490A80 (the table plus 12 zero bytes of padding, src/data/data_0049.s) is gone (the shift build stopped
on the overlap); shift/drafts.tsv rows and shift/unmatched exports of both are removed
(tools/shift/export_unmatched.py; its rewrites of the other exports were stale renames and were left out).

## decomp-permuter recipe for drafts with CONTEXT_ONLY callees (tools/permuter.py does not do this)
The permuter's extract_fn turns every other function *definition* in base.c into a prototype unless it is
`inline`, so CONTEXT_ONLY copies are silently dropped (2630 / 1fc8 then compile with a `bnezl` / `bnel`
instead of `bnez` / `bne`, so score 0 is impossible). What worked (out/permuter/func_001f2630/compile.sh):
- mark the CONTEXT_ONLY copies `inline` in base.c and compile with `-fno-inline -ffunction-sections`
  (same code as the real CONTEXT_ONLY build for 2630, 1fc8 and 001fd858);
- in the .s, rename every other `.section .text.X,"ax"` to `.section .ctx.X,"a"` (sed) so objdump
  disassembles only the target, and `.weak` the context names so calls keep symbol relocations;
- rename callees to their registry names (func_00266c08 -> sceDmaGetChan, func_00266f38 -> sceDmaSend,
  func_002654e0 -> sceGsGetGParam), and fix target.s lines that `kh1tool.py asm` left as raw numbers
  (`lui $v1,0x64` / `-2240($v1)` for D_0063F740, `3560(`, `23496(`, `-16900(`, a jump table as
  `%hi(.rodata.func_X.1)` declared with `.section .rodata.func_X.1`), then reassemble target.o;
- pins (`register T v asm("$r")`) do not parse in pycparser: write `T v;` in base.c and turn it back
  into the pin with sed in compile.sh (00125240, sceGsDefDispEnv).
With that the base scores were 50 (2630), 100 (1fc8), 200 (fd858), about 10 iterations a second on two
threads (the brief's "several million iterations" is not reachable here: ~35k an hour per function).

## 00125240 (already matched): a second lever, recorded for the scheduler
Before seeing that s22m1 had matched it I found another source of the HIGH-order problem. sched1's
rank_for_schedule after priority and reg weight prefers the insn with more *forward* dependences, and a
store of a pinned hard register (`register f32 k asm("$f0")`) gets extra anti-dependences from every later
call (calls clobber f0..f3), so pinned-value stores outrank the scalar-global stores regardless of LUID.
Pinning x as well (`register f32 x asm("$f1")`) gives every store the same count, and then reg weight
(a store where the value *and* the base register die weighs -2) plus LUID decide; the order
P0 M O X GY GZ A PY K PZ B PW GX GW Y matches too (no `f32 *q` needed). gdb on cc1:
`break schedule_insn`, `p h_i_d[uid]` prints luid, priority, dep_count, reg_weight.

## 001fd858 and sceGsDefDispEnv (no change; no new draft)
- 001fd858: permuter on s13w3's 1w flagged draft (hand/nostrict, CONTEXT_ONLY copies kept as above; the
  three callee copies do not change the output here), 3 threads, ~17,500 iterations in 25 minutes: never
  below the base (the `bnez` / `bnezl` word). Re-read the asm: the fallthrough of the 0x654 branch is
  `b L1FDE24` -> `b L1FDF94` -> `jal func_001fe408`, so v0 is dead there in the final layout, as s13w4's
  gdb proof says. Stays: reorg's annul decision (mark_target_live_regs) needs a v0 reader on the
  fallthrough that the final code does not have.
- sceGsDefDispEnv: permuter on s21m1's 4w pins draft (src/sdk/gcc991111, pins restored by sed), 1 thread,
  ~12,000 iterations: never below the base. The forward-dependence tie-break above does not help: the off[]
  loads win t=2 on priority (10/9 against 7 for the `addiu a3`), which comes before every tie-break, and
  sched2 has no reg weight. Stays: the loads depend only on the trap_if (cost 1), as s23m1 showed.
- Not tried this session: 0010d470, 00110618, 001636d0, 001c62a0, 00200e28 (outside this brief; 001c62a0's
  draft uses `aligned` and static inline helpers, which the permuter's preprocessing drops or rewrites).
