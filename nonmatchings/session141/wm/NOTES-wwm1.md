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

## Round 3 (wm below f60000, 51-250 insns)

Matched (11): f39b10, f442d8, f48f98, f48aa8, f40d20, f37c08, f5c9b0, f3a268,
f35188, f2f400, f2e960.

Near misses saved here: f2fcf8 (3), f2fa68 (3), f2cfd8 (6), f35c08 (9),
f296d8 (10), f491e0 (7), f5e368 (65), f502e8 (73), f58300 (89), f56538 (115).

### Round 3 tips

- **CONTEXT_ONLY empty bodies** for lower-address callees change delay-slot /
  branch-likely choices (f442d8, f2f400 needed two together, f2e960).
- **Callee return type** changes register choice (`s32 func_001c0310`, f40d20).
- **Switch case bodies** are emitted in source order (f48f98 needed 2,1,0).
- **Reuse the argument** (`arg0 |= old<<8`) instead of a fresh local (f48aa8).
- **abs()** emits bgez/negu; `if (d<0) d=-d` emits movn.
- **Indexed loop** `list[off]` gives strength-reduced givs initialised after
  hoisted invariants (f3a268); writing the mask as `!(x & 0x80000000)` in both
  condition and body keeps the constant in a register.
- **Write `D[idx].field` directly** rather than via a pointer local to get the
  address-CSE copies (f2cfd8 partly; f2fcf8/f2fa68 still 3 words off).
- Unsolved: globals held in s-regs across calls (f204d8, f47610), obj copy into
  a separate pseudo (f5e368/f5e540), word-wise struct copy (f491e0).

## Round 4

Matched (10): f2fcf8, f2fa68, f2d480, f491e0, f21600, f29810, f46a58,
f4e480, f35c08 (nostrict mode), f38bf8.

Near misses added/updated: f42ce0 (15), f387a8 (102), f23628 (128),
f55d78 (120). f2cfd8 unchanged at 6.

### Round 4 tips

- **`(x >> 8) & 0xF` on a u16 is a bitfield.** Declaring
  `u16 lo:8; u16 kind:4; u16 hi:4;` and testing `.kind == 4` removed the
  "address-CSE copy" 3-word diff in f2fcf8, f2fa68 and f2d480 (the bitfield
  read expands its own address, so the two field reads are not CSE'd).
- **A pointer-typed struct field changes alias sets.** f491e0's word copy
  order matched once field `b` was `void *` (s32 fields all alias each other
  and the arg0 stores; a pointer field has its own alias set).
- **m2c invents call args from leftover a2/a3.** func_00f66240 in f21600 is
  2-arg; check whether "args" are just %hi registers before trusting them.
- **Float temps: load matrix elements into locals in target load order**
  (f21600) to fix FP register choice.
- **Pointer increment vs index** for per-iteration buffers (f29810: `buf += 8`
  at the end of the loop gave the pointer giv).
- **One variable for value and packet pointer** (f46a58: `p = *D; ...; p =
  func_00f66b78(...)` keeps it in the same s-reg).
- **Check GS constants by reading the lui/ori/dsll chain**, m2c's expression
  can be wrong (f46a58 SCISSOR = 0x017F000001FF0000).
- **`arg0++` placed where the target does the addiu** (f4e480), then
  CONTEXT_ONLY on the callee fixed the last bnez/bnezl.
- **Run modes.sh on every near miss**: f35c08 matched in nostrict mode without
  `volatile` (int stores must alias the u16 flags field).
- **ctx.py on every close near miss**: f38bf8 needed CONTEXT_ONLY
  func_00f387a8 (an unmatched neighbour).
- Lerp loops (f55d78/f56538) need the m[4] array (gcc 2.96 keeps arrays in
  memory); the remaining gap is spilled induction variables.

## Round 5 (base 9ef986d)

Matched: f21bc8, f4db70, f20950.

Near misses saved (words left): f355a8 (4), f5e178 (4, twin of f355a8),
f4b1e8 (11), f5d498 (13), f4b7d8 (29), f4b258 (31), f5e710 (54),
f4d9c0 (67), f5bba0 (68), f4c610 (69), f27ff0 (71).
Not started: f5e540 (old r3 draft at 80 words), f24ac8/f24c80/f24380/
f24738/f24900 family.

### Round 5 tips

- **Callee return type picks v0/v1.** f21bc8 matched after declaring
  func_00f20a98 as returning s32 (unused result still changes allocation).
- **128-bit args:** func_001c00e8's third arg is `kh1_u128 q`.
- **`(a<<4) + (b<<4)` is not folded like `a*16 + b*16`.** f4db70 needed the
  shift spelling, then source store order fixed register allocation.
- **sprintf-style arg order:** func_001bef40(buf, fmt, name) in f20950;
  the name table is a 2-pointer struct copied into a local.
- **GS packet copies with in-order ld/sd alternating v0/v1** (f5e710) look
  like a MIPS movstr block move, not by-pieces; struct/u64 copies so far get
  scheduled. Unsolved.
- f355a8/f5e178: only the order of two lui differs; worth a fresh idea since
  fixing one fixes both.

## Round 6 (base 32439a0)

Matched (13): f355a8, f5e178, f24738, f24900, f24ac8, f24c80, f4b1e8,
f4b258, f4b7d8, f23fe8, f241b0, f24548, f23df0.
Near misses: f24380 (24, new file), f5e540 (79, new file); headers updated
for f5d498, f3a030, f3a0f0.

### Round 6 tips

- **Index instead of pointer to change pseudo order** (f355a8/f5e178): the
  output pointer `p++` became `D[n]` with `n++`. Strength reduction then
  creates the pointer giv after loop-invariant hoisting, so the two `lui`
  swap. Found by reading the `-dl` lreg dump (pseudo 93 vs 108).
- **Reuse the index variable for the next lookup** (f4b1e8 grid family):
  `j = i; i = g->c[j].t; ty[i]...` (or `i = c->t;` with `c = &g->c[i]`).
  Fixed f4b1e8, f4b258 and f4b7d8, which were 11-31 words off. A
  10-minute permuter run on f4b1e8 found the same thing.
- **Sprite family (D_00FBAA60/64):** use `tw`/`th` locals for the table's
  w/h, write coordinate offsets in place (`x = x + 1792; x0 = x - w / 2;`),
  then try random dependency-respecting statement orders (gen24380.py,
  run.py). Each match came within 1-300 orders. Read the packet order
  from the asm: f241b0 swaps the XYZ vertices, and f24900/f24c80 swap the
  UVs.
- f24380 stays at 24 words: the same s-reg permutation (idx/h) shows up in
  every order, declaration order and form I tried.

## Round 7 (rebased onto origin/claude/project-thread-rl45wv)

Matched (11): f58140, f58300, f41660, f42a38, f42860, f446a0, f204d8,
f39220, f21c48, f5d6b0, f43ae0 (and f58300 replaced its old near miss).
Near misses: f47610 (2), f45e68 (27), f4fba0 (62), f28258 (90),
f3a640 (127).

### Round 7 tips

- **Hill-climb statement order** (hill.py OVL FUNC src secs seed a b [a b]):
  random swaps/moves inside 1-based line blocks, keep when the word count
  does not get worse. f43ae0 went 20 -> 0 in 838 tries (8 min) after 250
  plain random orders had failed; f45e68 went 54 -> 27 together with
  mixed access forms. Use it before the permuter for any ordering-only
  diff.
- **Store-order diffs are not a simple reversal:** GCC's scheduler
  reorders runs of independent stores (f21c48, f5d6b0, f43ae0). Brute-force
  the permutations of the block (24-120 files) instead of reasoning it out.
- **RGBAQ colour components:** pointer copies in the target come from u8
  locals declared in reverse (b2, g, r) (f58140). Strength-reduced givs:
  write `i * 93 / 40` instead of keeping an accumulator (f58300).
- **Globals with addresses in s-registers** come from
  `static inline void alloc(s32 *p, s32 size, s32 align)`, mixed with
  direct stores (f204d8, f47610).
- **An unused local struct** fixes the frame size (f43ae0).
- **Packet pointer updated in place** (`p += 2; p = f(..., p)`) instead of a
  second `q` keeps it in the right register (f5d6b0). Write the GIF header
  through a union `{ kh1_u128 q; u32 w[4]; }`: clear `q`, then store the
  words.
- `x - 100.0f` folds to an add of the stored -100 constant only when you
  write `x + -100.0f` (f5d6b0).
- f39220: a twin of f39708; `arg0->pos[k] = d[k] = ...` keeps the scratch
  vector in memory.

## Round 8

Matched (2): f2a4c0, f206f0 (both GIF packet builders).
Near misses: f3e138 (114), f584d0 (67). Not started: f3d4d8 (large homing
loop with func_00f3caf0/f3cb90) and the rest of the list.

### Round 8 tips

- **Indexed inline put for packets** (f2a4c0, f206f0): when the target
  precomputes every entry address from the packet base (`addiu t4,v0,32`,
  `addiu t5,v0,48`, ... then `sd x,0(tN)`/`sd y,8(tN)`), write
  `static inline void put(u64 *p, u64 a, u64 b) { p[0] = a; p[1] = b; }`
  and call `put(p + 0, ..)`, `put(p + 2, ..)`, ... then `*pp = p + 2n;
  func_00f66b90(p + 2n);`. Chained `p = put(p, ..)` or `p += 2` give
  incremental addresses instead. f2a4c0 went 125 -> 0 words with it.
- **One pointer variable per packet**: when a function builds two packets,
  give the second its own local (`q`). Reusing `p` made gcc copy the
  f66b78 result into a0 (+2 instructions in f206f0).
- **Bare sqrt.s**: `#include "platform/math.h"` and use `PlatSqrtf(x)`;
  `sqrtf`/`__builtin_sqrtf` compile to a call.
- **Sprite element-address copies** (t1 = base+idx*20, copies in a0/v1, and
  a separate t0 = idx*20+base) come out naturally from writing
  `D[idx].field` inside each coordinate expression (f584d0), not from
  loading the fields into locals first.

## Round 9

Matched (2): f2eb78, f22ac8.
Near misses: f43430 (7), f30d48 (13), f41990 (16). f45e68 stays at 27:
hill2 over access forms (D[idx].f, e->f, (D + idx)->f, (&D[idx])->f) x
statement order reached only 28. Not reached: f3d978, f33aa0, f36bc0,
f46750, f2c518, f3d4d8.

### Round 9 tips

- **hill2.py** (`/tmp/claude-0/s141/wwm1/hill2.py OVL FUNC src secs seed
  a b ...`): like hill.py, but the source may hold choice slots
  `{{opt1@@opt2@@...}}`. Each step either swaps lines in a block or
  changes one slot. Use it to search expression forms and order together.
  (The separator is `@@` because options often contain `|`.)
- **Separate variable for a second call result** (f2eb78): reusing `r` for
  both func_00f2cd88 and func_00f2cfd8 added a `move`; a fresh `k`
  matched it.
- **Colour bytes into u8 locals** (f22ac8): `cr = c[0]; cg = c[1]; ...;
  col = cr | (cg << 8) | (cb << 16) | (ca << 24)` matched the target's load
  order. No ordering of the plain inline OR expression did.
- **Single exit**: when the target sets v0 = 0 only in the epilogue, use
  `goto end; ... end: return 0;` instead of early `return 0;` (f22ac8).
- **Division by a power of two that stays div.s**: divide by `(f32)n` with
  an int local `n = 4`. A float constant or `f32 n = 4.0f` becomes a
  multiply by 0.25 at expand time (f41990).
- **Float literals**: gcc 2.96 rounds some decimal literals differently;
  0x40490FDA needed `3.141592503f` (f30d48).
- **A temp computed before a call goes in a callee-saved FPR**: `t = fi /
  60.0f;` before sceVu0UnitMatrix put it in f20 as in the target.

## Round 10

Matched (1): f33aa0 (first draft; nested fill loops into D_00FBBA70).
Near misses: f3d978 (2 instructions off, new file); f30d48 (13) and
f43430 (7) are unchanged, with this round's attempts added to their
headers. Not reached: f36bc0 (looked at: a long state loop with a switch on
lbu-1), f46750, f2c518.

### Round 10 tips

- **hill2.py fixes**: slot choices are now keyed by slot text, so moving a
  line that holds a slot keeps its choice. (Before, a moved slot could pick
  another slot's choice or raise IndexError.) Leave a space before the
  closing braces when an option itself ends in `}` (`... } }}`). Otherwise
  the non-greedy match cuts the option short and the template does not
  compile.
- f30d48's 11-store prologue is not a source-order problem: random orders,
  hill-climbing and chained assignments all bottom out at 13-14 words.
  The fix is probably in how the globals are declared, not the order.
