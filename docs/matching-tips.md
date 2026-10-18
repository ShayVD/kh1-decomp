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

## Large functions (81+ instructions), session 5

- From batch 51: keep `(x+40)*16` unfolded with a local `x2 = px + 40`.
  A global loop bound reloaded every iteration: the stores in the loop are
  raw pointer stores, not struct members. `for (i = 0; i < n; i = j) { j =
  i + 1; ... }` gives the `t7 = i+1 ... i = t7` copy pattern. switch beats
  if/else chains for beqz/beq/b test order.
- From batch 52: cross-jumped code (one shared call/tail in the asm): write the whole block in every case/branch. Keep an out-param's address in a saved reg: make it an array element (`f32 h[2]`, &h[1]).
- From batch 55: 0x13b000-0x143000 nostrict. Shared fail label `if (a || b) { fail: return 0; }` turns bnel into bne. One constant register stored several times: stores come out in reverse source order. Use `break` instead of `return` to avoid a tail call.
- From batch 56: a branch-likely (bnezl/bc1tl) where the original has a plain branch with a filled slot is usually the callee-defined-earlier effect: check which call precedes it and whether that callee is (or can be) defined above in the same file. Switch on {1,2} lowered as ==1,<2,==2: add a dummy `case 0:` next to `default:`.
- A function can need nofill even inside a filled region (sign: `b` + nop slot, nops before div.s). Try src/hand/nofill.
- `lbu; andi 1; beqz` without `andi 0xff`: declare the field s8 and test `x & 1`.
- Switch case order changes jump-table block layout; permute cases with var.py {{P:...}}. `||` inside {{...}} alternatives breaks the split.
- `o->x = p->y = 2.0f` stores p->y first. `(f32)(u32)` gives srl/bltzl/add.s sequence. Pi = 3.1415928f.
- Clamps with movz/movn: use static inline min/max helpers, `min(max(1,t),m)`.
- Range test `(u32)(x - 9) < 2` instead of `x==9||x==10`.
- Locals get stack slots in declaration order; declare an arg block at sp+0 first.
- Clearing 2 bits of a u64 field: two separate `&=` statements through a local pointer.
- Float literal off by an ulp: write value + 1/4 ulp (0.99f->0x3f7d70a3 needs extra digits).
- Shared `return 0` block: `goto end`. Zero block before main body: `if (!n) { zero: r = 0; } else {...}`.
- Switch needs >=5 cases for a jump table; add empty cases.
- Chained `a = b = 0.0f` gives one mtc1 zero; chain order matters.
- A float arg loaded before a0 means the callee takes the float first.
- `volatile` stops delay-slot filling; prefer non-volatile globals / `f32 *dt = &D_x;` for addiu+lwc1 0(reg).
- Local tables copied with ldl/sdl are aggregate initializers; read contents from the ELF.
- Byte clamp movz form: `s->b = s->b + 2 > 100 ? 100 : s->b + 2;`.
- An unprototyped float-returning callee silently becomes an int call: always prototype f32 callees.
- `p = (T *)((u8 *)p + n); p++;` as two statements can fix registers.
- lq/sq copies through $8-$11 need inline asm (struct copy gives ld/sd).
- Single-exit `move v0,zero` epilogue: `goto end; end: return 0;` plus direct `return 1;` (a ret variable lands in a saved reg).
- Callee return type s32 vs void changes caller register allocation.
- 8-byte unaligned copies via `*(P8 *)&...` give ldl/ldr/sdl/sdr.
- `if (X) return 0; break;` + final `return 1` gives branch-likely shape.
- `x == 0` vs `!x` on a pointer can change register allocation and beqzl/beqz; try both.
- Early-return on a test giving wrong branch-likely: nest the rest as `if (!t) {...} return 0;`.
- `func(...) >= expr` evaluates call before load; swap sides to reverse.
- Table lookups: go through an element-pointer temp (`T *r = &tbl[i]; x = r->f;`) to fix v0/v1 swaps.
- u8 = u8 * f32 gives the 0x4f000000 compare / or 0x80000000 sequence.
- Shared store in a delay slot: write the shared statement in both if/else branches.
- Self tail recursion compiles to a goto loop (`if (j+1 < hi) f(j+1, hi);`).
- Loop pointer moved into a saved reg before the loop: two variables (`T *base = D_x; T *e; ... e = base;` before the loop).
- Switch assigning one var: `k = -1; switch (x) {...}` with no default gives li in the range-check delay slot.
- Several stores of one value: the last store of each value is scheduled first.
- `fl = 0; if (b) fl |= 1;` gives sltu/movn. abs() gives bltzl/negu.
- addu operand order: arithmetic on (u32) keeps it; pointer arithmetic reorders.
- Keep `li 1; bne` compare: `(... & 1) == 1U`. Plain `== 1` folds to beqz.
- Callee-saved reg for a global's address: `void **pp = &D_x;` before the first call.
- A u64 flag word as `union { u64 x; s32 i[2]; }` stops s32 loads moving above the flag store.
- Inline helper called twice rebuilds its constants per call like the original.
- EABI varargs: `ap = (char*)__builtin_next_arg(fn) - 8*(8 - __builtin_args_info(2));` then `{char *p = ap; ap += 8; x = *(s32*)p;}`.
- Several layouts of one global in a file: `extern u8 D_X[];` once, then `#define D_X (*(T *)&D_X)` / `#undef` around each function.
- Spill-slot order follows declaration order; declare locals in slot order. `(n-1) << 4` vs `* 16` can differ.
- `i = 0x10000; while (i--);` gives the 4x-unrolled countdown.
- Switch range check then redundant beqzl+nops: `if (c < N) { switch (c) {...; default: s++;} } else {...}`.
- `default: return;` first in a switch avoids a tail call.
- `a + (b - 0x7000)` folds; write `x = a + (u32)(b - 0x7000);` to keep the addiu separate.
- A global pointer read inside a loop gets hoisted with its own lui; pre-loading into a local shares the lui across loops.
- `lhu` after `sw` to the same s32 global: `*(u16 *)&D_x`.
- Global counter kept in a register through a loop: write plain global code (`D = 0; for (...) D++;`); a local counter breaks it.
- `jal f; lui; addiu s0; sw v0,0(s0)`: write `t = f(a); p = &G; *p = t;`.
- Tail call returning a value: make the function s32 and `return f(...)`.
- Stop `(n-1)*16` folding with a separate local `m = n - 1`.
- Loop ending `li sN,2 ... bgez sN`: write `for (i = 2; i >= 0; i--)`.
- Stop GCSE merging an address: spell it as another symbol + offset (`D_x[-2]`).
- Bucket list walk: `if (bk->head) { p = bk->head; do { ...; if (p->next == 0) break; p = p->next; } while (1); }`.
- Same constant loaded in both branches before a shared compare: assign inside each branch.
- `volatile u64` packet arrays keep sd store order.
- `for (j = 0; j < n; j++)` with j unused gives blezl + countdown register loop.
- Write the compare with the global first (`G >= x`) to load the global first.
- `python3 tools/checkfile.py FILE -v` lists every differing word (ours vs orig).
- `sb; jal; nop` with other slots filled: volatile global + nofill dir (func_0024d7b0).
- f(D_x = 20) shares one register for arg and store. Rodata strings already used by an earlier function: `extern char D_xxx[]`.
- Hidden function boundary: layout size bigger than ours by a tail after `jr ra` (N vs M bytes, 0 words differ) = separate function; write it in a comment block and report the split.
- `b` into loop body + early-out then-block before the loop top: `do { ...; if (x) break; ... } while (0);`.
- Wrong bc1f/bc1fl or arg-move order before a call can mean the callee's arg count is wrong.
- A 15-byte ldl/ldr copy + index loop = local `struct {s8 k,a,b;} tbl[5] = {...}` walked with `for (i = 0; tbl[i].k >= 0; i++)`.
- Shared non-tail call after an if block: `else goto call; ... goto end; call: f(...); end:;`.
- `(tb->x - 1)[id]` gives `lhu -2(v0)`; `tb->x[id-1]` does not.
- `break` vs `return 0` inside switch cases changes registers/scheduling.
- u32 bitfields directly in an 8-byte-aligned struct (holds a u64) are accessed with ld/sd (dsll/dsra32 reads); a nested bitfield struct gives lw.
- Shared float var across switch cases leaks f12 preference; use a block-local result per case.
- Float -> u8 store needs an explicit (s32) cast to avoid the unsigned 0x4f000000 sequence.
- `if (!p || !v) return 0;` vs two ifs changes v0/v1.
- Short-loop nops before a closing bnez are gcc padding; write the bare loop.
- Several zero stores in the wrong order: try a chained `a = b = c = 0;` placed after other stores.
- Brute-force the order of zero-initialisations when s-regs swap (120 orders is cheap).
- Reloc loops over 16-byte entries: take a field pointer inside the loop (`pp = &t->e[i].xc; *pp = (s32)t + *pp;`), separate pointer per loop.
- Two out-params reloaded in wrong order: make them one local struct `struct {s32 idx; f32 t;} q;` and pass `&q.idx, &q.t`.
- `li 4; cvt.s.w` divisor: `s32 n = 4; ... (f32)i / (f32)n`.
- Big setup blocks: hill-climb each block of stores/loads separately, then combine the .best results.
- Stack-param functions: which params get s-registers follows use counts; extra references to one param change spills.
- Inline result assigned in a plain statement shares one stack slot across expansions; inside an if-condition/void inline/return each gets its own slot.
- Cross-jumped switch case bodies: write them as an inline taking constant index args.
- `x >= K` emits c.le.s with swapped operands; `!(x < K)` becomes `x < K`.
- 16-byte GIF register packet: struct of u64 bitfield regs, write data words with `*(u128 *)&D.field = K` (por/lui/sq then sd).
- `(X + 1) << 4` keeps the addiu before the shift; `* 16` folds.
- Byte-to-float from a u32 colour: cast to (s32) first.
- Float param position in a prototype affects caller scheduling; check the callee's real arg order.
- Double literal equal to (double)(float)pi: write `3.1415927410125732421875`.
- Static chain in $v0 (`move v0,sp` before calling a local helper) = GNU C nested function; write the helper inside its parent's body.
- Chained slti range checks: `switch (t) { case 4 ... 8: ... }` with GNU case ranges.
- `lhu; srl 8; andi 0xf` in a loop: u16 bitfield (`u16 r0:8, r1:4, r2:4`).
- Run of single-bit `and`s on one u64 with one ld/sd: 1-bit u64 bitfield assignments in increasing bit order.
- 64 unexplained frame bytes: an unused local array.
- Unexpected `jal __extendsfdf2`: a callee lacks a prototype above that point.
- `python3 tools/checkfile.py FILE -v` lists each differing word.

Flagged (hand-written asm, not C): func_001996d0 and func_0019a828 (whole-function VU0, matched with inline asm), func_00115940 (VU0 macro mode), func_001bfac8 (context switch), func_001aa1f8/func_001aa448 (sq $zero). func_001a67f0 and func_001a72c8 are GNU nested functions of func_001a7718.

## Session 6 tips (full list: docs/worker-brief.md "Session 6")

- **Callee above**: a one-word `bnel`/`bne` or register difference near a
  call means a callee was defined above the caller. Put a CONTEXT_ONLY copy
  (or `{}` stub) of each callee above it in turn; the one that matters is
  often not the nearest call.
- **Callee return type**: void vs s32 on a callee changes the caller's
  register allocation and slot filling even when the result is unused.
  Sweep callee return types on every near miss (several matches this way).
- **Mode first**: before reshaping C, try nogcse (repeated loads/constants),
  n32 (unfolded `lui; addiu; addu` symbol bases, 0x20dxxx-0x217xxx) and
  the nostrict/nofill combinations.
- **Statement order**: when only store/assignment order is off, permute or
  hill-climb the statements (tools/matching/perm.py, hill4.py, popt.py)
  instead of reasoning about the scheduler.
- **Shared tails**: a store or return shared by several paths just before
  the epilogue is the last source statement reached by `goto`; duplicating
  an early `if (c) return G;` lets gcc merge return paths.
- **Extra variables** raise reference counts: a separate variable for a
  repeated sum, a local holding a shared divisor or a constant set before a
  branch, or a local array plus pointer can reproduce the original's
  spills and delay slots.
- **Real loops**: a symbol base hoisted into a register (then rebuilt at the
  use) comes from loop.c on a real `for` loop; goto loops do not do it.

## Session 7 tips (full list: nonmatchings/session7/NOTES.md)

- **Sweep flags** on any near miss (tools/matching/flagsweep.py); six functions
  matched with one extra flag, and a flag that fixes a draft points at the source
  shape to look for (e.g. -fno-sched-interblock: duplicate the tail per branch).
- **Duplicate shared tails per path** (plain-brace macro, not do-while(0)):
  cross-jumping re-merges them, but registers and spills follow the original.
- **Block-local variables**: declare a variable separately in each branch (or per
  case) to make it a local pseudo; this changes FP/GPR choice (func_00267c10,
  00119ad8). Block-local copies of stored values fix sched1 store order
  (002134c8).
- **Shared `goto` return labels** stop if-conversion (`bnez; move v0,zero; li v0,1`
  instead of sltiu) and the ce pass hoisting `return K` blocks.
- **Callee prototypes** keep paying: void vs s32 return, real arity (00218218,
  00101048, 0015a348).
- **Struct-copy fields**: read them through separate s32 locals (0019bbf0).
- **Masks before shifts** for u64 fields: `(r & 0x7ff0000) >> 16` gets its own andi.
- **Nested sub-struct indexing** `D[k].s.d` keeps `la; addiu K; addu` split.
- **Read the next-tested value into a local** before a branch to steer reorg's
  delay-slot fill (00182ec0).
- **VU0 code in game C**: helpers as `#define` macros of inline asm, not static
  inline; `"=m"(buf[0])` outputs for 16-byte stack results; lq/sq around calls
  are 128-bit caller-saves.
- An empty `__asm__ volatile("")` barrier reaching 0 words is a hint, not a match.
