# Session 141, worker wwm1: wm.x below 0x00f50000

## Matched (31, each confirmed by `make ovl OVL=wm` "OK ... byte-identical")

f39ef0, f3bb68, f37170, f2b4b8, f45020, f450c0, f222a0, f25420, f323b8,
f3f7c8, f2d630, f203c8, f24e38, f22778, f38a38, f3b8d0, f432f0, f411e0,
f3f5a0, f35a88, f307b0, f3e778, f2f020, f4eaa0, f39968, f3e5d0, f3e408,
f49df8, f23878, f23a58, f23c20

(Commit 5797b13 also fixes `objdump -z` in tools/autodecomp.py.)

## Near misses (in this folder; the first comment line of each file has details)

| func | words left | problem |
|------|-----------:|---------|
| f38bf8 | 2 | `li s2,1` should fill the `beqz s0` delay slot |
| f2c910 | 2 | prologue order `sll s2` vs `sd ra` |
| f3a030 | 3 | |
| f2d480 | 3 | permuter found nothing |
| f3f998 | ~3 instrs | extra `move a1,v0` |
| f22e60 (.norlo) | 4 | movz operand order |
| f3a0f0 | 6 | |
| f3ba08 | 6 | |
| f2c330 | 8 | |
| f326a0 | 9 | |
| f2bfb8 | 9 | size 200 vs 208 |
| f465a8 | 9 | |
| f25660 | 12 | |
| f23fe8 | 12 | sprite family; alpha/v1 s4/s5 swap |
| f23df0 | 14 | sprite family; idx/v0 s5/s6 swap |
| f38630 | 16 | float store order, FP regs |
| f44158 | 27 | arg0/arg4 s0/s1 swap |
| f23550 | 30 | |
| f3fd60 | 34 | |
| f3bc48 | ? | loop GIV split |
| f3dbf8 | 50 | |
| f2b598 | 54 | |
| f241b0 | 58 | sprite family, only 1 order tried |
| f2fa68 | 73 | first loop counts down in target; loop-2 addressing |

Skipped: f47388 and f4b778 (the coordinator did them), f4b060 (gb twin, matched
on main), and the shapes shared with gb unmatched functions.

## Tips

- **Check permuter output with hand.py.** The permuter's score is not
  hand.py's score: a f2f020 output the permuter scored 10 was a full match.
  Test every output-*/source.c with hand.py.
- **Union keeps a "dead" store.** Writing a GIF packet through
  `typedef union { u64 d[2]; u32 w[4]; } QW;` keeps the final `*arg1 = p`
  store, because union access has alias set 0 (f4eaa0).
- **Indexing style changes loop GIVs.** Mixing a local `E *e = &D[i]` for
  some fields with `D[i].field` for others gives different loop GIVs (f3e408).
  Fully indexed `D[i].field` matched f3e778 and f23a58.
- **Try norlo mode for loop-heavy code.** `.norlo.c` (`-fno-rerun-loop-opt`)
  took f22e60 from 86 words to 4.
- **Order of unrelated global stores.** It changes delay-slot filling (f307b0).
- **Callee prototypes.** The argument order and types in a callee's
  prototype set the arg-setup order (f3e5d0 used f3caf0's
  `(void*, f32, f32*, f32)`).
- **Read before a call.** Reading a field before the call (`rad = s[3]`)
  frees a callee-saved register.
- **abs().** `abs()` stored in a variable gives the branchy bltzl/negu form;
  written inside a compare it folds into a range check.
- **Ternary spelling.** `!a ? 2 : 1` and `a ? 1 : 2` pick movn/movz differently.
- **Sprite-packet lq/sq family** (f23a58, f23c20, f23878; f23df0, f23fe8,
  f241b0 near). These are plain C; the lq/sq are only caller-save spills.
  - Compute x0/y0/x1/y1/u0/v0/u1/v1 before `p = func_00f66b78(pk)`. Their
    statement order decides the spill registers, so try many orders.
  - The RGBAQ constant is `0x3F80000000808080LL`.
  - Put a `+1` in the variable expression (`u0 + w + 1`), not in the packing.
  - Write `(x += 1792) - w / 2` to keep the operation order.
  - A local pointer to a global held across calls, declared first, fixed
    the register order in f23878 (`u64 *q = &D_00F87A60;`).
- **vec4 struct copies.** Give the type `__attribute__((aligned(16)))` to
  get ld/sd instead of ldl/ldr.
- **Function-pointer tables.** Function-pointer table setup (f49df8) matched
  with separate `extern void *D_...` globals, one assignment each.
