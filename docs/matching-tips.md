# Matching tips (gcc 2.96 / ee-gcc, this game)

Collected by the hand-matching workers in session 5. Each line is a
pattern that fixed real mismatches. Helper scripts named with /tmp paths
were scratch tools of that session and are gone; tools/checkfile.py
replaces the whole-file checkers, decomp-permuter (tools/permuter.py)
the store-order searches.

## Matching tips for this compiler
- Register-allocation differences usually come from expression shape:
  try temporaries (`Ent *e = &tbl[i]; ... e->x`), operand order of `&`,
  `|`, `+`, splitting or merging statements, `if (c) return;` vs nested
  `if`, signed vs unsigned types, `s32` vs `u8`/`s16` locals and params.
- Loads/stores order follows source order; the struct field types decide
  `lb`/`lbu`/`lh`/`lhu`/`lw`/`ld`. 64-bit `ld`/`sd` are `u64`/`s64`.
- A loop with a nop before its head is a real `for`/`while` (the compiler
  aligns loop heads); `goto` loops get no alignment.
- `a = b = 0.0f` (chained float stores) keeps 0 in an FPU register
  (`mtc1 zero`), separate stores give `sw zero`.
- Tail calls: `j func` at the end means `return func(...)` or a final
  call with no frame.
- Strict aliasing: the compiler may reorder loads/stores through different
  types; if order differs, the field types are probably wrong.
- Struct types: make a struct with the offsets you see (pad with
  `u8 pad[N]`), and reuse it across functions that share a data symbol.

## More tips, by batch
- `ldl`/`ldr` pairs (+ `lw`), `sdl`/`sdr` (+ `sw`): a struct assignment
  `*dst = *src` of a 12-byte struct of three s32 (4-byte aligned, so the
  first 8 bytes are copied as an unaligned 64-bit pair). E.g.
  `typedef struct { s32 a, b, c; } V12; q->buf[q->n] = *v;` matched first try.
- Store order mismatches: try permuting the order of independent
  assignments (struct field fills before a call often need an odd order).
- From batch 5: when the original keeps a store before a load gcc would
  reorder, the two must alias: type the field as a union (with a char
  member) or a pointer of the same type. Script handlers take
  `typedef union { s32 i; u32 u; f32 f; void *p; } Arg;` arrays. 64-bit
  flag words: `(s32)(x >> 37) & 3` reads; stores via u64 bitfields.
  abs.s is `fabsf()`. 0x3f4ccccc is `0.7999999523162842f`.
- Check your whole file at the end: each function must still match with
  the file's shared types (compile the file once per function).
- From batch 6: a `jal` where you expected a tail `j`: gcc 2.96 skips tail
  calls when the call is in a loop ending with `break`, in nested ifs with a
  `return`, or when the result goes through a variable. Load/store or `lui`
  order wrong: declare fields s32 and cast pointers. Countdown loops
  (`li s0,N-1 ... bgez`) are plain `for (i = 0; i < N; i++)`; index form
  `D[i].f` often beats pointer increments. `if (a-- > 0)` gives
  `move v0,a1; blez v0; addiu a1,a1,-1`. A bare `lui/addiu` address with no
  symbol is its own `extern u8 D_<addr>[]`.
- From batch 4: `addiu` + `lw 0(reg)` on a global means `volatile`.
  gcc 2.96 rounds decimal float literals down: write pi as `3.1415928f`
  (0x40490fdb). Bits 37-38 of a u64 read as `ld; dsrl32 5; andi 3` match u32
  bitfields in a union `{ u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b; }`.
  `d[1].w = d[0].w = 1.0f` stores d[0].w first.
- From batch 3: to stop a tail call gcc would make (`jal; ld ra; jr ra`),
  take the address of a parameter feeding the call (`T **pp = &a;`). Nops
  inside short loops are the compiler's padding: get the C loop shape right
  (plain `for` over a 2-D array, `goto found` exits). A register set up but
  unused at a call means the callee takes more arguments. Flat counters:
  `k++` in the inner loop indexing `D[i][j][k]`.
- From batch 2: chains of `move` copies come from repeating the same indexed
  expression in every statement (no temporary). `lui; addiu; sw 0(reg)` on a
  global: `volatile`, or a local pointer `T *p = &D`. Hardware registers
  (`lui 0x1200`): `*(volatile u64 *)0x12000000`, no symbol. The last store
  before a return/tail call often goes last in source.
- Keep your own helper scripts in /tmp/claude-0/s/<your worker id>/ (the
  scratchpad is shared). Test one function per scratch file.
- From batch 7: to get a global reloaded after a store, store through a
  plain pointer (`s32 *p = &e[i].key; *p = k;`). Clamp
  `if (max < v) v = max; else if (v < 0) v = 0;` gives movn. Float constants
  with full digits (`66.66666412353516f`).
- Skip any function in your list that is already defined somewhere under
  src/ as a DEFINITION (`grep -rlE "^[a-zA-Z].*\bNAME\([^;]*$" src --include=*.c`
  finds definitions, not prototypes; or `.text.NAME` in a .s file).
- IMPORTANT (found in batch 8): some game files were built with gcc's
  delay-slot filling off. If the original leaves a `jr ra` (or call/branch)
  delay slot as `nop` where ours fills it, test it with
  `--out-dir src/hand/nofill` (scratch file in src/hand/nofill/.wN_*.c).
  Put such matches in a second file src/hand/nofill/<the file's name>
  (same name as the file, in that directory).
- Whole-file check: `python3 /tmp/claude-0/s/tools/check.py the file` (if
  present) compiles each function with only its own body kept.
- `m2c` sometimes adds an argument from a leftover temporary register; drop
  it if the call matches without. gcc merges `v < 131 && v >= 124` into one
  `sltiu`; compare a copy to keep two `slti`.
- From batch 11: a callee DEFINED EARLIER in the same file changes the
  caller's codegen (plain `beqz` with `ld ra` in the slot instead of
  `beqzl`). If the callee is in your own list, define it above the caller
  in the file. If it is defined in another file, report the case (with
  your matching code) instead of copying the callee.
  A shared `goto` return label can fix block layout. `k = *p++; p += k;`
  for count-prefixed lists.
- IMPORTANT (found in batch 14): some game files (e.g. the script VM around
  0x1c08f0-0x1cc208) were built WITHOUT strict aliasing. If a function's only
  problem is loads that the original keeps after stores through other types
  (reloads), test it with `--out-dir src/hand/nostrict` (scratch file in
  src/hand/nostrict/). Put such matches in src/hand/nostrict/<the file's
  name>. Both no-strict and no-fill: src/hand/nostrict_nofill/.
- Pop handlers: read every stack slot into a local before writing `sp`.
  `volatile` globals keep stores exactly in source order.
- Msg builders for func_001c4640 (h15/h18) with two stores swapped after
  trying all orders: try an initializer (`Msg m = { ... };`) or a compound
  struct assignment instead of field-by-field stores.
- From batch 23: counting loops over global arrays often need a pointer walk
  (`Obj *p = D; ... p++`). A `slt; addu` count guarded by a range can be
  `switch (s) { case 1: case 2: n++; }`. Bit arrays: single-word fields as
  `u32 x[1]`. Wrappers with >8 args: extra args at 0(sp),8(sp)...; a `sw`
  to the caller's 40(sp) then `j` is `return f(..., 15)` (10 params).
- From batch 20: pop stack slots into locals in ascending order
  (`x = s->stk[i-2], y = s->stk[i-1], z = s->stk[i]`). 64-bit OR packing:
  `r = a | K; r |= ...;` not one expression. `v1` result where you expect
  `v0`: the function returns an earlier call's result through a variable.
- `try` now resolves ee-gcc's soft-float libcall names (dptoli, litodp...).
- From batch 22: a wrong `bnez`/`bnezl` at a return can be fixed by moving
  the success return to the end (`if (p && f(p)) goto ok; return 0; ok:
  return p;`). 1.6666667f is 0x3fd55555.
- From batch 24: permuting store order: /tmp/claude-0/s/w24/perm.py. To see
  the compiled asm of any file with project flags (rodata functions, callee-
  earlier tricks): /tmp/claude-0/s/w24/S.py. Index a global pointer's array
  as a struct field (`D->a[i]`), not raw u8*, for the original addu order.
  A tail `j` with a frame: the 9th stack arg is passed straight through.
- From batch 27: to test a function whose callee is defined above it in the
  same file (no "relocation truncated" error), use
  `python3 /tmp/claude-0/s/w27/ad.py try NAME --file F --out-dir src/hand`
  (places each defined func_ at its real address); whole file:
  `/tmp/claude-0/s/w27/chk.sh FILE`. A bare `break` insn:
  `__asm__ volatile("break")`. `sltiu v0,v0,1` result: `if (x < n) return 0;
  return 1;`. Fill loops `for (i=0;i<9;i++) buf[i]=-1;` become countdowns.
- From batch 25: gcc reorders stores to different globals: permute them.
  128-bit copies (`lq`/`sq`): `typedef int u128 __attribute__((mode(TI)));`.
  Region 0x236970-0x23d4xx is a nofill file.
- From batch 26: 0x23f000-0x24b000 looks like a nostrict file. A local
  filled from a 16-byte rodata initializer: `Col q = D_00491610;` with an
  aligned(16) struct. `n*32 + n*K` as two statements stops a merged multiply.
  Whole-file checker linking at real addresses: tools/checkfile.py
  FILE; rodata-tolerant try: /tmp/claude-0/s/w26/ro.py.
- Callee-defined-earlier cases: move the callee (rewritten as clean C if it
  is m2c output in src/auto/) above the caller in one file.
- From batch 28: callee return types change register choice: try `s32`
  instead of `void` for callees. An unexpected `bnel` means the callee
  reads a0 (takes an argument). Check callee asm for real arg counts.
  Helper: /tmp/claude-0/s/w28/rtry.py (rodata-tolerant, real addresses).
- From batch 30: a 9-byte ld/sd + lbu/sb copy is `__builtin_memcpy(d, s, 9)`
  (aligned(8) externs; an inlined strcpy of a literal). A (sp)-saved param
  that gets reloaded: pass `&param` (and try nostrict). VU0 helpers that
  return a float: `qmfc2 $2; mtc1 $2,%0` inside the asm, "=f" output.
- From batch 32: 0x130000-0x13c000 is partly nostrict; try it early there.
  Compare direction matters (`p->x > q->x` vs `q->x < p->x` swap regs).
- From batch 31: a switch on 0/1/2 compiled as ==1, ==0, ==2 tests means
  the value is unsigned. `if (a && b) r = n+1;` gives movn; `r = b ? n+1 : n`
  gives sltu+addu. An s0/s1 swap nothing fixes: try nostrict. When
  counting diff lines, read the MATCH/FAIL line (a compile error prints 0).
- From batch 33: 0x13c000-0x149000 is nostrict. 0.3f is 0x3e999999; 2pi is 6.2831855f.
- From batch 34: a float constant one unit low in the last bit needs the
  full decimal expansion (0.199999988079071044921875f). A callee called with
  different arg counts: declare it unprototyped `void f();`. To get a tail
  call from a void-looking caller: make it `s32` and `return callee(o)`.
  From ~0x150de0 on is nostrict.
- From batch 36: 0x159000-0x165000 is nostrict. DMA CHCR bitfield globals: plain (non-volatile) pointers under nostrict.
- From batch 37: 0x167000-0x174300 is nostrict too. Many regions are: if a
  function nearly matches strict, ALWAYS also try nostrict. Inlined copies
  of nearby functions: write `static inline` helpers (`inl_<addr>`).
  `if (a || !b) return 0;` first gives branches; separate returns give sltu.
- From batch 38: a symbol name shown as D_X+0 may really be a pointer's field (D_0036001C = D_00362434->x1c). Switch cases with identical returns: give each case its own return.
- From batch 40: 0x18a000-0x1a1000 is nostrict. Inline-asm VU0 blocks that must not kill CSE of a global: asm volatile with no outputs/clobbers. `D[cnt] = p; cnt++;` vs `D[cnt++] = p` differ.
- From batch 44: inlined lw/lhu/lbu copies are strcpy(buf, "literal") (memcpy gives signed lh/lb). String literals are fine in the file under the rodata comment.
- From batch 41: if m2c shows `(s64)(f() << 0x20) >> 0x20` at a call site, the callee returns s64. K&R definitions with u8 params give the andi sequence (avoid unless needed; checkers miss them).
- From batch 43: `jal sqrt; nop` / `jal __truncdfsf2; nop` with a fillable slot: nofill. Distance helpers: static inline double inl_dist(...) { return sqrt(dx*dx+dy*dy); }.
- From batch 42: an unexpected jal+epilogue instead of a tail j: wrap the final call in `do { f(); } while (0);`.
- From batch 45: gcc 2.96 sched1 moves stores whose register dies ahead of
  stores of 0/live registers; within each group source order holds. Search
  one field order against several sibling functions at once:
  /tmp/claude-0/s/w45/patsearch.py; sched dumps: /tmp/claude-0/s/w45/dump.py.
- From batch 46: if one layout symbol is really several original functions
  (a caller ends in `j` to the next, or small accessors follow), split it in
  layout.tsv and write each function separately.
- From batch 49: 0x239xxx-0x23dxxx is nofill; 0x23f700-0x245a00 nostrict. A register never set before a call is usually a pass-through argument (the callee takes more args).
- From batch 48: 0x236970-0x23d4xx is nostrict_nofill. GIF tag stores: source order is the reverse of the store order.
