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

## Round 11

Matched (9): f46750, f2c518, f39448, f27d18, f2e0b8, f218e8, f3d4d8,
f2a1e0, f371d8.
Near misses: f36bc0 (3 words, new file), f4c238 (70 words, a port of the gb
twin's near miss with the same diff, new file), f3d978 (score 48 -> 40,
header updated).

### Round 11 tips

- **gcc 2.96 rounds float literals down**: `1.2f` gives 0x3F999999, and
  `6.283185006f` gives 0x40C90FDA (f2c518, f218e8). Check the constant bits
  before blaming anything else.
- **`if (arg != 0 && n > 0)` around a for loop** gives the duplicated
  `blez` guard (f39448).
- **Continue a loop index into the next loop** with `for (; i < 3; i++)`
  (f27d18). Hoist a repeated expression such as `y + 128` into a local.
- **Pure function-pointer-store functions** can be generated straight from
  the asm with a short script (f46750, mk467.py).
- **Argument evaluation order follows temps**: when the target sets a later
  argument register before an earlier one, load that argument into a temp
  first. `g = D_00F864C0->f1344;` before the `&=` store moved obj to a3
  (f2e0b8). `t = func_00f20048(...); id += 20001; f294a0(id, 13824, t);`
  put `li a1` in the delay slot (f2a1e0).
- **Prototype parameter order for float args**: with EE floats in f12/f13,
  `func_00f3caf0(s32, f32, f32 *, f32)` and
  `func_00f3cb90(s32, f32, f32 *, f32 *, f32 (*)[4])` matched f3d4d8. The
  (ptr, ptr, f32, f32) order compiles but schedules f12 after a1.
- **A dead store can be real**: f218e8 stores 0 to rot[1] and then the
  computed value. Writing `rot[3] = 1; rot[0] = rot[1] = rot[2] = 0;` and
  then `rot[1] = ...` (as separate statements) matched.
- **A switch with case bodies that only fall to a common store**: in
  f218e8, `switch (x) { case 0: f(); break; case 1: g(); break; } x = -1;`
  matched. Per-case `x = -1` did not.
- **Inner struct members are not the same as pointer to them**: in f371d8
  the loop induction pointer was based on a mid-struct field (base+224).
  `q = &D[i].s;` (a pointer to a sub-struct starting at that field) and
  `q->field` accesses matched. `D[i].s.field` with no pointer did not.
- **Duplicated `b; lui` after an if-then** came from `id += 20001` written
  in both arms of the if (f2a1e0).

## Round 12

Matched: f2e510, f2d738, f35e10 (wm 927 -> 928 after the rebase, byte-identical).
Near misses saved: f21260 (2 words), f3ff98 (3), f32770 (6), f2dc50 (15),
f2ba68 (48), f53758 (152), f47b60 (146), f58748 (202), f42f20 (205), f58bd0 (206).
Not drafted: f5f940 (looks like f53758). gb twins: twins.py gb and near.py found none.

- **`c1 0x10044` in a listing is EE `sqrt.s f1,f1`**: use PlatSqrtf.
  In f2d738 the dot product is divided by `PlatSqrtf(|d|^2 * |z|^2)`.
- **A local element pointer inside the loop** (`p = &D_00FBB5D0[idx];
  p->a &= 0xFD; id = p->b;`) removed an extra spill (f2e510).
- **Read xori and ori carefully**: the end of f2e510 is `^= 2`.
- **Restore store order matters**: after the MulMatrix in f2d738,
  m[3][0], m[3][1], m[3][2] in that order.
- **A switch needs enough cases to become a jump table.** f35e10's table
  covers 1..6 with only 4 and 5 doing work. With `case 1:` and `case 6:` only,
  gcc used compares and also hoisted the float constants (0.5, 1.0) into
  f20/f21. Adding `case 1: case 2: case 3: break;` gave the jump table and
  stopped the hoisting.
- **Load a shared value into a local before an if/else** when the target
  loads it in the branch delay slot: `t = k->f0;` before
  `if (dir == 0) { ... t ... } else { ... t ... }` (f35e10, last 3 words).
- **The `(i*0x590+0x540)+base` address shape** (as in f3fb28) appears in
  f3ff98 and f42f20. `static inline Sub *ssf(s32 idx) { s32 b_ =
  (s32)D_00F86500; return (Sub *)((u8 *)(Sub *)(idx * 0x590 + 0x540) +
  b_); }` reproduces it. The permuter can parse it, but not a GNU
  statement expression. Use it as an expression each time; a `Sub *s` local
  lets gcc CSE everything.
- **`dir = D[idx].s.dir = k->b8 & 1;`** gave the `move s7,v0` plus a store
  of v0 (f3ff98). Writing it as two statements did not.
- **u16 bitfields in an 8-aligned struct** are read and written with ld/sd
  (f47b60). In a 4-aligned struct they give lw/sw. Add
  `__attribute__((aligned(8)))` to the struct.
- **`k->kind == 1 && !(k->flag & 0x80)`** folds into one word load and
  `& 0x8000FF` (f3ff98).
- **gcc rounds float literals down** (0.17453292f is 0x3E32B8C1). The
  constants 0x44bb6000/0x44bba000/0x453b7000 are 1499/1501/2999.
- **A permuter "win" can change behaviour**: the f32770 outputs moved
  cnt++ before the o store. Check each output against the source before
  using it.

## Round 13

No new matches. hill2 passes on f21260 (2 words), f3ff98 (3) and f32770 (6)
found nothing; their headers now say what was tried. New near misses:
f3be50 (135 words by address, about 8 after alignment), f5f940 (214),
f34998 (387 by address, 173 aligned). Not drafted: f33e48 and f36498
(420+ instructions each).

- **Look for the matched callee's prototype before drafting.** f3be50 called
  func_00f62ea0 with k->f0 in f12, and the dead-looking `lwc1 f12` loads
  before the join were that argument. The matched source has
  `func_00f62ea0(f32 t, f32 *out, ...)`.
- **A vector at matrix+48 is usually m[3]**: in f3be50 (func_00f3c4d8) and
  f34998 (sceVu0ApplyMatrix output and func_00f3d978 input), the "local"
  at sp80 is row 3 of the matrix at sp32. A separate local makes the frame
  16 bytes larger.
- **A struct array gives one pointer per field**: when the target keeps
  separate loop-invariant pointers for e+4, e+8, e+12 and e+16, declare
  the table as `struct { s32 w0..w4; } D[]` and write `D[idx].wN` in the
  loop, instead of `s32 *e = &D[idx*5]` (f5f940).
- **Check what follows the last loop.** f3be50 ends with a call
  (func_00f3bde8) after the loop exit label. It is easy to miss.
- **Aligned diff**: /tmp/claude-0/s141/wwm1/adiff.py OVL FUNC draft.c runs
  difflib over the target and our instructions, with branch targets masked.
  When one inserted instruction shifts every address after it, it shows
  the real handful of differences.

## Round 14

Five matches: f326a0, f3dbf8, f2c910, f2bfb8 and f25660. f38630 went
from 16 to 2 words. RANKING.md ranks every wm near miss by aligned diff;
the five matched rows are now removed from it. f3be50 is unchanged at 6
aligned words after a 10-minute permuter run (no gain over the base).

- **Check callee return types against their definitions.** Declaring a
  callee `void` when it really returns a value changes scheduling, even
  when the result is ignored. func_001c0310 and func_001c01b0 return s32
  (src/util/task.nostrict.c), and func_001bb658 returns a GumiBlock pointer
  (src/gummi/ship.c). This fixed f2bfb8 (the separate `li v0,1` after
  the store) and f2c910 (the prologue `sll s2` / `sd ra` order; the
  permuter found it by declaring the callee `unsigned int`). It also took
  f25660 from 12 to 2 words, and one store swap matched it. f38630 went
  from 16 to 12 this way. /tmp/claude-0/s141/wwm1/protofix.py compares
  every prototype in the drafts with the definitions in src/ and
  ovl/*/hand and retries each draft that differs. No other draft gained.
- **`(base + idx)->f` and `base[idx].f` give different operand order.**
  f326a0: `return (D + idx)->val` computes the base first (addiu, then
  sll). Then putting `best` before `idx` in the declarations fixed the
  last two registers.
- **A big raw count can still be a one-line fix.** f3dbf8 had 50 raw
  words but 5 aligned. Writing `if (q == NULL || q->h2 >= 2) return 0;`
  instead of nesting the body under `q != NULL && q->h2 < 2` matched it.
- **Open the aligned diff before trying variants.** In f38630 the
  target's own store order compiles worse (16) than the order hill.py
  found (2). The scheduler moves stores, so use the hill climb, not the
  source order.
- Dead ends this round (written in each header): f3ba08 (the
  materialised 1 is hoisted out of the outer loop), f465a8 (a double load
  through one shared lui), f3fd60 (`v - 1` is not folded into the table
  offset), f7cb60 (crossjumping), f3a0f0 (FP registers).

## Round 15

protofix2.py (`OVL DIR...`) runs the round 14 prototype check on any
overlay. It looks callees up in src/, in that overlay's ovl/OVL/hand, and,
for main-ELF addresses only, in the other overlays' hand dirs. Overlay
addresses repeat between overlays, so the round 14 script could pick up
a wrong definition from another overlay. Unknown typedefs are replaced
with `void *` or `s32`. When more than one prototype changes, it also
tries each change on its own.

- gb (79 drafts in session141/gb; session131b has none): no matches.
  f37270 went from 17 to 14 (func_00f3e388 returns MdlWork *). The other
  callees it re-typed, such as func_001c01b0, func_001f3840 and the
  wintext ones, changed nothing.
- Small overlays: xs_mushu f20550 matched. func_00148968 returns a
  pointer (src/obj/effobj.nostrict.c); declared void, it swapped two
  loads. dktitle f26710 is 2 words with the s32 func_0011ef10, the same
  as the session132 draft. xs_genie f218f8 stays at 2 words. dkmovie
  f207a0/f20140, dktitle f228c8 and xl_limit f225b0 did not change.
  xs_tink, xs_dh_break, xs_bambi, xs_dumbo and xs_simba have no
  candidates.
- Before `hand.py try` works on the xs_* and xl_limit overlays, run
  `python3 tools/ovl/build.py wrap NAME...` to write the target
  out/ovl/NAME.elf. Without it, the objdump step fails with a
  CalledProcessError.
- nonmatchings/session141/gb/RANKING.md ranks gb by aligned diff. Its
  top rows are f350d0 (1), f2c000 and f35a80 (3), f4d348.nofill and
  f3c8c8 (4), and f34aa8 (5 aligned, 65 raw). f350d0 and f34aa8 differ
  on branch-likely use (bltz vs bltzl, beql), not on statement shape.

## Round 16

The top of the gb ranking: no matches, so nothing to port to wm twins.

- f350d0 (1 word): the bltz vs bltzl delay slot. A 10 min permuter run
  found nothing.
- f363a0: `if (sel >= func_001bb720())` reproduces the target's
  `slt s0,v0` / `bnezl`. Aligned went from 6 to 4; raw went from 15 to 28,
  because the target has an extra nop that shifts addresses. Left: the
  sd ra position in the prologue and two nops the target has (one after
  the join's slti, one after the loop's b). The prologue problem is not a
  prototype problem: every callee matches its definition.
- f34aa8 (5 aligned): reorg predicts the case-44 beq differently (the
  target uses beql and steals from the case body). Switch shape variants
  did not change it.
- f51360 (6): more hill seeds and 72 chained-assignment variants made no
  gain. The target store order is now in the header.
- f20518 and f36ee0 (11 to 12 aligned): giv / register-copy problems.
  I looked at them and did not change them.

## Round 17 (branch-likely study)

The findings are in docs/overlays.md, under "Branch-likely vs plain branch". In short:
reorg puts a stolen target insn in a plain slot only when its register is dead on the
fallthrough. A call kills the call-clobbered registers in that scan only when it is
nothrow (REG_EH_REGION 0), and gcc 2.96 marks a call nothrow only when the callee was
already defined earlier in the file. So a CONTEXT_ONLY definition of the first callee on
the path after the branch flips `b*l` to `b*` (and, in gb func_00f34aa8, `b*` to `b*l`).
I found this with gdb on cc1 (/tmp/claude-0/s141/wwm1/bl/rg2.py: the fill_slots_from_thread /
mark_target_live_regs / find_dead_or_set_registers trace) and minimal tests (bl/t1.py,
t2.py). const, pure, noreturn and nothrow attributes do not give it; a definition below
the function does not either.

Eight matches came from running /tmp/claude-0/s141/wwm1/ctx2.py (greedy CONTEXT_ONLY
search) over all 258 drafts: gb f350d0, f35a80, f34aa8; wm f5cb78, f31118, f3ff98,
f3be50 (two stubs, found one after the other) and f5bba0 (one stub plus gb f34aa8's vector
store order). Closer: wm f3d978 (99 -> 8), f3cdd0 (24 -> 17), f43430 (7 -> 6). In every
hit the stub callee sits at a lower address than the function.

- hand.py keep adds its own "matched by hand" header in front of one that does not start
  with that text. /tmp/claude-0/s141/wwm1/fixhdr.py merges the two.

## Round 18 (ctx2 everywhere, ctx2 + climbing, main ELF read-only)

- ctxbatch.py with k=2 over every draft in nonmatchings/session141/{gb,wm,dkmovie,dktitle,
  xs_dh_break,xs_dumbo,xs_genie,xs_tink} and session140/xl_limit: no direct match. Closer:
  gb f50550 and its wm twin f77648 (253 -> 228, now the right size), wm f42f20 (205 -> 170),
  f29dc0 (24 -> 23), f7d0a8 (507 -> 499), f7ad38 (756 -> 732, with cosf/sinf defined),
  xs_dumbo f20570 (27 -> 26). The two xs_dh_break drafts do not compile any more
  (`D_00F317F0` undeclared), so they were not tested.
- The reverse direction (moving a CONTEXT_ONLY definition that is already above the function
  below it, /tmp/claude-0/s141/wwm1/omrm.py) changed none of the five wm drafts that have one.
- hill2.py with free line swaps is useless here: it reached "2 words" on gb f363a0 by moving
  statements across the loop and the returns. /tmp/claude-0/s141/wwm1/sclimb.py instead toggles
  CONTEXT_ONLY definitions per callee and moves statements only with climb_s144's dependency
  check (same block, no calls, no shared names), plus declaration swaps. 300 s per function
  on the top 30 of both rankings and the small-overlay drafts under 60 words (not the
  permuter-reserved dkmovie f207a0 / f212c0 and dktitle f26710 / f241c8).
- Matched: wm f2cfd8 (6 -> 0: CONTEXT_ONLY func_00f2ccb8, `idx` declared last, the a9 store
  after f12) and wm f2c330 (8 -> 0: `g->x8 = t / 10;` right after `g->xc = u;`). portall wm -> gb
  ported nothing.
- Closer (saved): gb f37448 (77 -> 65), f4a650 (35 -> 27, three stubs plus moves), f25518
  (62 -> 44), f36ee0 (81 -> 78).
- Main ELF, read-only (/tmp/claude-0/s141/wwm1/mctx.py and mrm.py, scored with lro6_s12.check):
  adding definitions changed none of 001c62a0, 00200e28, 00110618, sceGsDefDispEnv, 0010d470,
  001636d0. But 001fd858 is this same mechanism the other way round: its draft defines
  CONTEXT_ONLY func_001fe408 above the function, which makes the fe408 call nothrow, which
  kills v0 in reorg's scan, which gives `bnez` where the original has `bnezl`. Moving that
  definition below the function gives 0 difflib words on the 1w flagged draft
  (/tmp/claude-0/s141/wwm1/mrm_001fd858_flagged_0.c) and 25 -> 24 on the natural draft
  (mrm_001fd858_natural_24.c). Not committed; it needs `make` and a decision about the
  flagged dead float test.
- Careful: an earlier mctx.py removed src/hand (it holds the tracked src/hand/vu0.c) when it
  cleaned up. It was restored with git checkout; the scripts now remove only the directory
  they made.

## Round 19 (sclimb.py on wm rows 130+ and the small overlays)

- Matched: wm f4b878 (202 -> 17 with sclimb.py: CONTEXT_ONLY func_001bb740 and dependency-checked
  reorders; -> 4 with the grid index as `yy * (h->w * h->h) + zz * h->w + xx`; -> 0 with the
  seven zero locals assigned after the declarations in the order x0, y0, z0, first, x1, y1, z1).
  No order of the initializer list (`s32 x0 = 0, ...`, all 5040) gave the 32/20/24/28 stack-slot
  store order; one order of plain assignments did. gb f24780 matched as its portall port.
- /tmp/claude-0/s141/wwm1/i2a.py OVL draft.c [N] does that conversion (initializers to
  assignments, source order plus N random orders). It finds f4b878 from the 4-word draft. No
  other draft in my range has two or more constant initializers.
- Raw word counts mislead when the size differs. The first raw-word pass "improved" dkmovie f23750,
  f25288, f23ae8, f245c0 and wm f646c0, f7ad38, f71b68, f6f2a8, f7de08, f60fa8, f6b7c8, f75d80
  while hand.py's score got worse. Those were not saved. sclimb.py now takes OBJ=score, and
  r19save.py saves only when the score is not worse.
- Saved (hand.py score): dkmovie f270c8 148 -> 96, f245c0 608 -> 538, f23ae8 675 -> 629,
  f26d90 211 -> 206, f25978 262 -> 256; wm f6f2a8 835 -> 713, f60fa8 1210 -> 1062, f71b68
  660 -> 584, f7ad38 675 -> 628, f47f40 -> 249, f5e8a8 935 -> 901, f7de08 897 -> 855, f51d18
  -> 460, f54050 -> 294, f49718 -> 303, f58748 (raw 202 -> 191), f6b7c8, f75d80 (small).
- The xs_dh_break drafts compile only with nonmatchings/session136/xs_dh_break/shard.h pasted
  in (as their headers say). f20820 stays at 8 words, f20288 210 -> 206 raw (not saved).
- No change: dkmovie f20b48, f25180, f22d28, f275e0, f23750; xs_genie f218f8 (2), f22078;
  xs_tink f20818; xs_dumbo f20570, f222f8; xl_limit f225b0. Reserved (not climbed): dkmovie
  f207a0, f212c0; dktitle f26710, f241c8.

## Round 20 (i2a.py everywhere, sclimb OBJ=score on wm rows 130+)

- tools/ovl/i2a.py (moved from scratch; docs/overlays.md has a paragraph on it) over every near-miss draft in gb, wm,
  dkmovie, dktitle, xs_* (xs_dh_break with shard.h pasted) and xl_limit, skipping wwm2's functions. Only 12 drafts have
  two or more constant initializers at the top of the body. One gain: wm f7c880 111 -> 107 words, score 64 -> 50
  (saved). No change: gb f24240, f363a0, f40b68, f429b0, f50550; wm f4b338, f5d498, f69aa8, f77648, f7f628;
  xs_genie f218f8.
- sclimb.py OBJ=score, seed 5, 300 s each on wm rows 130+: wm f58748 352 -> 331, f7de08 855 -> 807 (saved). The rest
  moved by 4 or less or not at all. No match.

## Round 21 (small overlays, closest first)

- Matched: xs_dh_break f20820 (8 words, the 50.0f / 25.0f constants in $f21 / $f20 the wrong way round). It matched
  when the first jitter was written inline (`s->c[0] = (...) + func_00f20020() * 50.0f - 25.0f;`), and the local `a`
  was dropped. The -dl/-dg dump showed why statement moves could not fix it: sched1 hoists both constant loads (50 is
  live across 6 calls, 25 across 4), so the order comes from live lengths that the source order barely touches. Its
  ovl/xs_dh_break/drafts.tsv line is removed. /tmp/claude-0/s141/wwm1/inl.py tries each single-use temp inline; it
  finds this match and nothing else in my range. It also inlines global stores, which is wrong, so check its output.
- xs_genie f218f8 (2 words: lui s4 / move s0,sp order): the gcse-inserted %hi of D_00FC1DD0 lands after `p = a` at the
  end of the preheader block. Tried every compile mode, address temps before and after the early return, for/while/goto
  loop forms, declaration orders, n/m set late, array types. Still 2 words; no movable blocks for w3.
- dkmovie f20140 (score 29): the packet address is built in a2 and copied to a1; pointer temps, store order, `|`
  operand order and every mode leave it. f25180 (8 words): h and ht swap a1/a2 (local-alloc; h 3 refs / 12 insns,
  ht 3 / 4); 14 variants, no change. f20b48: register allocation only, no movable blocks.
- Saved (hand.py score): xs_dh_break f20288 95 -> 57 (w3.py, wwm2's r35 hill3 reorderer made per overlay), dktitle
  f21808 59 -> 45, f21ca0 207 -> 187, f23aa8 144 -> 138, f228c8 408 -> 398, f24b60 410 -> 358 (sclimb OBJ=score
  and w3), dkmovie f270c8 96 -> 76, f25288 115 -> 107, f25658 72 -> 70.

## Round 22 (inl.py on gb/wm, w3 on the small overlays, ifswap)

- inl.py now inlines only temps declared as locals in the function (no global stores). Its new form finds f20820 again.
  Over all gb and wm drafts it found no candidate that lowers the score, so there was nothing to review or save.
- xs_genie f218f8: CONTEXT_ONLY definitions of each callee (empty and with a body), prototype changes (u8 / s8 / s16
  returns, no prototype, void -> s32) and the extern order all stay at 2 words. The %hi insertion does not move.
- w3.py seeds 3 and 5: dkmovie f270c8 76 -> 52, f25288 107 -> 103; the others did not move (f25180, f20140, f25658,
  f23750, f26d90, f25978, f245c0, f23ae8; xl_limit f225b0; xs_dumbo f222f8; xs_dh_break f20288).
- /tmp/claude-0/s141/wwm1/ifswap.py: for each `if (C) {A} else {B}` it tries `if (!C) {B} else {A}`, with the
  condition negated directly where it is a simple comparison. This decides beqz vs bnezl and the order of the arms. Run
  over every draft: wm f78978 39 -> 19 (then `D_00FB5EC0 == 1 ? 3 : 2` -> 13), dkmovie f270c8 52 -> 38 (then w3 ->
  30), dktitle f228c8 398 -> 378, wm/gb f6edd8/f47ce0 186 -> 167, wm f6d810 234 -> 228, gb f46718 236 -> 230,
  dkmovie f26d90 206 -> 200, wm f63d18 102 -> 100, f23628 83 -> 81. All saved; each one compiles and has its score
  in its header. (gb f377b0 935 -> 929 and wm f60cf0 136 -> 133 were dropped at the rebase: the upstream versions
  score 901 and 42, and ifswap does not improve those.)
- f270c8 (score 30) left: the call to func_00219380 keeps an empty delay slot in the original (`sw; jal; nop`)
  where ours puts the f3DF28 store in it. Tried: a temp for the result, a volatile store, the store after the if,
  and the order with f3DF58. The tail: f3DD5C[0] / [2] are built in a2 / t0 the other way round.
- f78978 (score 13): the original keeps the loads of the dead `D_00FB5ED0 && D_00FB5EC4 == 0 && D_0108FA74 == 66`
  test (li a0,66 with no compare). My guess is that the x = 1 store became dead only after reload, so jump2 deleted
  the branch and left its operands. A volatile read of D_0108FA74 gives the right size (564 vs 568, 22 words) but the
  same score.

## Round 23

- w4 (scratch, /tmp/claude-0/s141/wwm1/w4.py): w3 (dependency-checked statement order) plus a move that flips one
  if/else polarity at a time (swap arms, negate the condition; one move in four is a flip). Ran over 91 drafts (wm,
  gb, dkmovie drafts scoring 60 or less, plus the drafts ifswap improved), 150 s each, seed 7. No matches. Gains
  saved (score only improves): wm f5dfd8 30->26, f23628 81->73, f696a0 35->33, f69278 41->37, f7c880 50->48,
  f78d50 59->41, f45e68 44->36; gb f425a8 35->33, f46718 230->228, f36ee0 30->26; dktitle f228c8 (session141
  copy) 378->374. Some of these fall outside my range; the coordinator settles overlaps by score.
  After the rebase, upstream already had equal or better versions of all but two (gb f425a8 31, wm f696a0 31; wm
  f78d50 is now matched in ovl/wm/hand). This commit carries only wm f7c880 50->48 and dktitle f228c8 378->374.
- tools/ovl/ifswap.py and tools/ovl/inl.py are committed (241571eb), with a docs/overlays.md paragraph each.
- f78978 "real but redundant" dead test: tried x = 1 before the test, no initializer, testing D_00FB5EC4 first, a
  flag variable, the same value on both paths, nested ifs, goto, and an empty if body. None beat 13. The best was
  `|| flag`, which gives the right size but scores 24.

## Round 24

- dkmovie f270c8 MATCH (nofill), commit "Overlays: dkmovie func_00f270c8". The tail stores were the only problem. I
  tried every order of the last six stores (scratch /tmp/claude-0/s141/wwm1/tperm.py). The one that matches is
  f3DF0C, f3DF10, f3DD5C[0], [1], [2], then f3DF08. With the nofill mode, the empty `jal; nop` slot already matched.
- dktitle f21808 (session141 copy, nofill): 39 -> 31 with three w4 runs.
- dkmovie f25180 (16): the lreg dump shows a priority tie. ht (pseudo 89) and ht*16 (pseudo 94) both have 3 refs
  over 4 insns, so ht is allocated first and takes a1, and h falls to a2. In the target, ht*16 must win the tie. None
  of these changed the tie: statement orders, h removed, u8 pointer, shifts, a separate ht16 variable, and inline
  helpers with constant arguments (setdim(bw, bh) and others; the forms that take arguments break the schedule, 28).
  Every mode gives 16 or worse. w4 also found nothing.
- dkmovie f20b48 (14): temps for the else-branch call arguments, a pointer or temp for the join store, a return
  variable and an early return all gave no gain. Every mode gives 14, and w4 found nothing.
- xs_genie f218f8 (3): an address local before or after p = a, inline helpers for the fetch/put/data/check (the
  orphaned-check form), goto or nested entry, and moving the init statements all gave no gain. The lui s4 hoist always
  lands after move s0,sp.
- xs_dh_break f20288: hand.py needs the shard.h include rewritten to ../nonmatchings/session136/xs_dh_break/shard.h.
  It then scores 55, and a 10-minute w4 run found nothing.
- The v0-after-call fix did not apply to any of these: none of the differing spots follows a call whose result is
  ignored.

## Round 25

- tools/ovl/storeperm.py (store-order sweep, docs/overlays.md paragraph). Swept 33 drafts: dkmovie, dktitle
  (session141 copies), xs_*, xl_limit, wm RANKING rows 130+. Three runs at a time; TLIM 3600 s when the score is
  under 200, 600 s otherwise. The whole sweep hit its 2-hour limit. dkmovie f23ae8 and wm f6f2a8 were cut off
  mid-sweep, and five high-score wm drafts never started. No matches. Saved gains: dkmovie f26d90 193->192, wm f47f40
  249->241, f58748 331->329, f646c0 428->426, f71b68 584->580. After the rebase, upstream already had better or equal versions of f47f40 (215), f646c0 (426) and
  f71b68 (551), so only f26d90 and f58748 are committed. A gain on wm f51d18
  (408->390) was dropped: it reordered the one-line `if (nz < 0) nz = 0;` / `if (nz > max) nz = max;` clamps, which
  changes behaviour. storeperm now treats one-line ifs, labels, case lines and control statements as barriers.
- f25180 ht*16 tie: ht*16 as its own variable used twice (double store, `| h16`, `+ (h16 & 0)`, `h16 - h16`,
  st2 inline) stays at 16. cse folds the extra uses before local-alloc, so the ref counts do not change.
- hill3 hole audit (w3.py, w4.py, sclimb's cmoves.py). w3/w4 already kept if/return/break/goto/case/default/else
  lines out of the movable blocks (BAD), but they took `x = y++;` and `a[i++] = v;` as reading y / i only, and a
  `L: x = 1;` label line was movable. sclimb's checker let a one-line `if (c) x = y;` move, and missed embedded
  ++/-- too. All three are fixed: embedded ++/-- makes the line a barrier, and labels and one-line ifs never move.
  The audit (/tmp/claude-0/s141/wwm1/r25/ordcheck.py) checked every git version step of the 31 session141 drafts
  whose headers name w3, w4, sclimb or the dependency-checked reorderer. It looked for pairs of lines that changed
  order where one is control flow or a label, or where an embedded ++/-- writes a name the other line uses.
  - My saves: only two one-line ifs crossed another line, both from sclimb in round 19 and both independent: wm
    f51d18 `if (nx < 0) nx = 0;` vs `oy = ...h1;`, and wm f75d80 `if (D_0108F1B8 > 0) ...` vs `v = 1;`. The other
    hits were ifswap arm swaps, which are valid (dktitle f228c8, wm f7c880). Nothing to restore.
  - wwm2's hill3o saves did move break, case, default and a label. dkmovie f23ae8 (d6d14605) moved `next_packet:`
    past `D_00F283C8 = 0;` and moved case/default/break lines. wm f7ad38 (6ff9b223) moved case/break lines and
    one-line `if (...) goto/continue` lines. Both are wwm2's saves, so I left them for wwm2.

## Round 26

- tools/ovl/ordcheck.py is committed with a docs/overlays.md paragraph. It audits each git version step of a draft
  and flags pairs of lines that changed order across control flow, a label, an embedded ++/--, or a plain-variable
  dependency. Lines in opposite arms of an if/else are never flagged, so ifswap's arm swaps pass. Duplicate lines
  whose count changed are left out, and steps with more than 6 added or dropped lines count as rewrites and are
  skipped. A flip is reported only while the current file still differs from the first version that had both lines.
  Run on origin at b93d9837 over every session141 gb, wm, dkmovie, dktitle and xs draft, it flags 33 drafts. All
  33 come from wwm2's hill3o and its ports (rounds 45-47); none come from wgb or from me. The list went to the
  coordinator.
- storeperm reruns. wm f60fa8 1054->1042, f6b7c8 1272->1226 and f7de08 799->765 are saved and checked by hand (only
  distinct fields or elements are reordered). An f5e8a8 gain (871->860) was dropped at rebase: wwm2 reverted that
  draft's invalid hill3o order (now 891), so the run's base was not valid. wm f6f2a8 had no gain. Two drafts are not saved because they are on the audit list and wwm2 is repairing
  them: dkmovie f23ae8 (596->592 by swapping `m->f3DD94` / `m->f3DD98` at line 64) and wm f75d80 (skipped). f7de08
  ran in three parts: runs before line 257 in one process, [250, 284) and [284, end) in two more, then combined.
  storeperm now takes TO=line as well as FROM=line for that.
- ordcheck second pass. The first pass missed f5e8a8 (8b136dc8, found by wwm2) because duplicate lines whose count
  changed were dropped from the pairing. Now identical lines pair in order and difflib pairs the rest; each version
  is read at its own path (a session132 copy got mixed in before); a pair counts as still flipped when it was
  flagged an odd number of times; and a call class (call vs call or memory/D_ store), chained assignments and `&x`
  were added. On origin after wwm2's round 48 reverts, no clearly unsafe move remains. Flagged but judged fine:
  gb f22620 / wm f49718 (`show = 0` moved into the case 0/default arm, every case sets show), gb f2d8d8 / wm f549d0
  (PlatVu0MulMatrix vs stores to a local), wm f29dc0 (lod rewrite, deliberate), wm f60fa8 and f6b7c8 (call vs local
  or `lab[7]` stores), and wm f3a640.nostrict (`sp->f8` stored before func_00f64c38, deliberate per wwm2's round 51
  header; worth a check by wwm2).

## Round 27

- valaudit --scan wm over the 58 low-half drafts (below 0xf50000): one real value bug. wm f42f20.norlo passed
  *D_00F85160 to func_00f29aa0, whose second parameter is the packet-pointer cell itself (u64 **, as wm f23018
  passes it). With that fixed, D_002C5958 as u32 (srl, as in f33270/f3e988) and s.a of the D_00F850E0 calls read
  through ssf(), 84 -> 26 at exact size. The other flags were address forms, spill choices or scheduling: f49718's
  lui 0x108 is a hoisted delay-slot load, f32df0's a3/t0 swap is x/y spill choice, f4b338's missing a2 setter is id
  living on the stack, f2ba68 case 43 (sltiu vs xori) does not move with four forms of the test.
- wm f23550 20 -> 5: the tail as `if (r != 0) return -1; if (m.sel >= n) return -2; return vals[m.sel];`. Left: the
  target loads 10 once (li a3,10) for the m.x30 store and the 4th argument. Ours keeps two li: cse turns every form
  of the argument (literal, m.x30, a t = 10 local, `m.x30 = 10` as the argument, chains) back into the constant, so
  local-alloc never gets the a3 copy preference. storeperm over the three stores gave nothing.
- Bucket lever: an end-of-function empty-asm count scan (0-16 asms) over the 21 drafts at 2-26 never moved a score,
  and a 1/2/3/5-asm scan before every top-level statement (wwm2's asmscan3) found one hint: wm f37770 reaches 0 with
  2 or more asms before func_001bf888(q0, ...), before the type switch or before the anim test (bucket count
  unchanged at 129, so not the bucket lever). Cause, from the -dl/-dg dumps: global-alloc priority
  floor_log2(refs) * refs / live_length. n (pseudo 89: 7 refs, 181 insns) scores 773 and the hoisted `mode < 2`
  (pseudo 267: 3 refs, 39 insns) 769, so n is allocated first and takes s5. Two more insns in n's range give 765
  and the target's order. 182 insns is an exact tie (14/182 = 3/39), which goes to the lower pseudo, so n before
  the type load (+1) changes nothing. Hoisting (f32)n out of the loop (one ref fewer) fixes both registers but moves
  the cvt out of the loop (still 24). No plain-C form found: statement orders before and after n, loop and
  condition forms, case orders of the loop switch, address forms of the loop's arguments, type load placement.
  The priority script is /tmp/claude-0/s141/wwm1/r27/sc/prio.py (prints the allocation order with each pseudo's
  refs, live length and priority).
- Same priority reading for f44158 (arg4 4 refs/11 insns = 7272 against arg0 4 refs/19 = 4210; the target needs
  arg0 first, and both keep the `arg0 != arg4` compare in case 1) and f20d08 (the D_00F8512C address pseudos have
  3 refs over 14 insns against 3 over 4 for the values). Neither has a plain-C fix yet.
- Field type as a store-order lever: wm f387a8 with c, f24 or f54 retyped (void *, f32) and wm f32770's C32770
  fields (s32 o / u32 id / int x): no gain. f3ba08's split constant 1 (guarded do-while and for forms with `one`
  inside the guard) hoists the literal out of the outer loop (18-22). f465a8 with D_00F9B2E0 in either read keeps
  two lui (16), and volatile still builds the full address (10). f43430's buf-loop moves do not change with
  count-down, do-while or for-init loops.
- dkmovie f23ae8 (storeperm, task 3): 624 -> 620 from storeperm (f3DD9C, f3DD94, f3DD98 store order), then 620 -> 538
  by dropping the 2nd-4th `m = D_00F28460;` copies: the target reloads the global in those blocks (valaudit's
  repeated target-only lw D_00F28460), so they read D_00F28460-> directly, func_00f208b8(D_00F28460) included.
  A storeperm rerun on the 538 version is in the round report.
- wm f23018 85 -> 47 -> 19 (1332 vs 1336): the valaudit flag was a storage form. D_00FBAA78..8C are separate s32
  globals, not an array, and the target stores the first two through pointer locals (pa = &D_00FBAA78 before
  func_001bb7c8, pb = &D_00FBAA7C right before the stores). Then xc/x10 stored before `if (id == 0) id = 2;`,
  x98 before xac (the target stores xac after the jal; ordcheck flags both moves, deliberate), p = *D_00F85160
  before D_00F873F0 = 1, and D_00F878F0 cleared a, b, c, d. Left: one word of size and the lim[] store pair.
- wm f23628 (71, not saved): the target makes one func_00f23018 call with a1 set 1/0 by if/else; ours makes two
  (596 vs 568). Six single-call forms (`!= 0`, ternaries, `!!`, a local set by if/else or default-then-if) all
  give 576 bytes and score 142, worse in the aligned diff too (83 vs 51 lines). A lead, not a fix: the shape is
  right but the prologue and registers move.
