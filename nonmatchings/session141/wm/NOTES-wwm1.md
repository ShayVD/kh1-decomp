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

# Round 2: dkmovie.x and dktitle.x

## Matched (6, each confirmed by `make ovl` "OK ... byte-identical")

- dktitle func_00f25528 (from session 133's 6-word draft). The 512 constant
  became a fresh local `o = 512; h.e[0].off = o; o += ALIGN512(n);
  h.e[1].off = o;`. Its dying register then takes the sum, the way the
  original does.
- dkmovie func_00f22290. The 150-tick counter is a nested
  `for (;;) { for (cnt = 0; cnt < 150; cnt++) {...} call(); }`.
- dkmovie func_00f224b0.
  - `volatile u8 *cf = &D_002C5968;` is assigned after the first call.
  - `u32 t = *cf; if (!((t >> 1) & 1) && ...)`.
  - The arguments are stored in the order buf, lsn, n.
  - The u8 shift without the temporary gave an extra `andi 0xff`. Without
    volatile, reorg stole the lbu into the loop branch's delay slot.
- dkmovie func_00f21da0.
  - The 2048-byte `memcpy` expands inline as both the ldl/ldr and the ld/sd
    loops.
  - The assert call is wrapped in `do { } while (0)`, so it is not a sibcall.
  - A CONTEXT_ONLY body for func_00f21b98 turns `bnel` into `bne`.
- dkmovie func_00f27b90.
  - The 32-line deinterleave uses indexed C (loop.c makes the pointers and
    the countdown).
  - The condition is `(h & 0xF) != 0 || ((h / 2) & 0xF) == 0` with that
    branch first.
  - `src2 = arg0 + w * ((h / 2) & ~0xF)` in branch B reads the incoming
    argument rather than its copy.

## Skipped

- **Hand-written asm in dkmovie:** f205f4, f205a4, f2052c, f2061c, f206c8 and
  f203a4. These are lq/sq/MMI loops with explicit nop padding and daddiu
  counters, libmpeg-style. Most likely dktitle f24330 (lq/sq/MMI) is the same.

## Near misses

| Function | Draft | Left | What was tried |
|---|---|---|---|
| dkmovie f23750 | new, session141/dkmovie | 824 vs 808 bytes | structure done; the inner search must be a goto loop; allocation of the spill differs |
| dkmovie f25288 | new, session141/dkmovie | 844 vs 864 bytes | structure done; the IPU wait loop's address must be hoisted (EE short-loop nop padding) |
| dkmovie f22d28 | lead's draft | 15–22 words | about 20 cast and OR-grouping variants plus all modes; the original does not CSE `dbp << 32` and has an extra `move t4,t1` |
| dkmovie f275e0 | lead's draft | score 15–20 | every `while`/`for`/do-while is rotated by jump.c; the original is a real loop (alignment nop) moved by stmt.c and loop-hoisted; a goto loop gets the shape but not the hoisted `move a1,v0` |
| dkmovie f25180 | lead's draft | 8 words | 15 local and type variants all give the same a1/a2 swap |
| dkmovie f207a0 | lead's draft | 7 words | 138 placements of the global stores, chained stores and a `-1` local: no change |
| dkmovie f20140 | session 134 draft | unchanged | packet-pointer forms, temporaries and store orders; a 10-minute permuter run only gave semantics-changing outputs |
| dktitle f241c8 | session 132 draft | 2 words | sched swap of `dsra32 t1` and `dsll32 a3`; ~20 source and type variants and all modes leave it |
| dktitle f26710 | session 132 draft | 2 words | all 672 dependency-valid orders of the store block; best is still 2 words (`lui v0` vs `v1` for D_00F26E30) |
| dktitle f21808 | session 132 draft | not reworked | store-scheduling puzzle |

## Tips

- **A fresh local for a constant** that is reused in a later sum ties the
  sum's result to the constant's register (`addu a0,v0,a0`) (f25528).
- **A volatile byte pointer** stops reorg from stealing the load into a loop
  branch delay slot. A u32 temporary avoids the QImode narrowing that adds
  `andi 0xff` (f224b0).
- **Loop shape from the asm:**
  - A loop with no alignment nop and an unhoisted invariant is a goto loop
    (f23750).
  - "b test" with an alignment nop and the test at the bottom comes from
    stmt.c `expand_end_loop`, not jump.c. Every plain while/for we tried was
    duplicated by jump.c instead (f275e0, unsolved).
- **EE short-loop padding:** the nops inside short wait loops are added by
  gas/gcc's r5900 short-loop fix, not by inline asm. The count depends on
  whether the branch delay slot was filled (f25288).
- **ptest.py marker:** ptest.py's marker (the first line of the draft) can
  match inside ovl.h. pt2.py cuts at the function signature instead.
