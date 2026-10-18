# Hand-matching brief (kh1-decomp)

Repo: /home/claude/kh1-decomp. A matching decompilation of Kingdom Hearts
Final Mix (PS2, EE MIPS r5900). Game code is built with ee-gcc 2.96,
`-O2 -G0` (strict aliasing on). A function is done only when the compiled
bytes are identical to the original.

## Your job
Your list of functions (name TAB instruction count) is in YOUR_LIST. For
each one, write C that compiles to the identical bytes, and put every
matching function in YOUR_FILE (create it; start it with
`#include "common.h"` and declare your own types and externs in it). Work
through the list in order; give each function a fair try (several
variants), but move on after ~15 attempts without progress. Aim to match as
many as you can.

## Tools (run from /home/claude/kh1-decomp)
- `python3 tools/kh1tool.py asm NAME` - the original's disassembly
  (labels, D_XXXXXXXX data symbols, func_XXXXXXXX callees).
- `python3 tools/kh1tool.py m2c NAME` - an m2c draft (often wrong types;
  use as a starting point only).
- `out/autodecomp/<addr>.c` may hold an earlier draft for some addresses.
- Test one function: put it in a scratch file INSIDE src/hand/ (so the
  compiler flags are right), e.g. `src/hand/.wN_try.c` (dot name, so the
  build ignores it), then
  `python3 tools/autodecomp.py try NAME --file src/hand/.wN_try.c --out-dir src/hand --diff`
  It prints MATCH, or the differing words (ours on the right). Delete your
  scratch files when done.
- `try` refuses functions that use rodata (float/double constants in
  memory, switch jump tables, strings): put those in YOUR_FILE anyway at the
  end under a comment `/* needs make: uses rodata */` if you are confident,
  otherwise skip them.

## Rules
- Do not run `make`, `git`, or edit anything outside YOUR_FILE and your
  scratch files (other workers share this repo and its build).
- Keep the original names: `func_XXXXXXXX` for unnamed functions, and the
  existing name when the list gives one. Do not invent function names.
  Callees: declare them as `func_XXXXXXXX` prototypes (match argument
  counts to how they are called). Data: `extern` declarations named
  `D_XXXXXXXX` exactly as the asm shows them (a field access at +N on
  D_X is `D_X.field` or `((u8*)&D_X)[N]`, never a new symbol name).
- No copying from other decomp projects (e.g. github ethteck/kh1): write
  the code yourself.
- No inline-asm bodies for ordinary C. Inline asm only where C cannot
  produce the instruction (VU0 macro instructions, MMI, `sync`, cop0);
  ee-as syntax for VU0 is `vrxor R, $vf2x`, `vmulax.xyzw ACC, $vf4, $vf8x`
  (`R`, `Q`, `I`, `ACC` without `$`).
- A bare `sqrt.s` is `PlatSqrtf(x)` from `#include "platform/math.h"`.

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

## Report back
At the end, reply with: how many matched (list names), which you skipped
and why (one short phrase each), and any patterns that would help the
other functions (e.g. a struct layout you found).

## Extra tips (added while running)
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
  Put such matches in a second file src/hand/nofill/<YOUR_FILE's name>
  (same name as YOUR_FILE, in that directory).
- Whole-file check: `python3 /tmp/claude-0/s/tools/check.py YOUR_FILE` (if
  present) compiles each function with only its own body kept.
- `m2c` sometimes adds an argument from a leftover temporary register; drop
  it if the call matches without. gcc merges `v < 131 && v >= 124` into one
  `sltiu`; compare a copy to keep two `slti`.
- From batch 11: a callee DEFINED EARLIER in the same file changes the
  caller's codegen (plain `beqz` with `ld ra` in the slot instead of
  `beqzl`). If the callee is in your own list, define it above the caller
  in YOUR_FILE. If it is defined in another file, report the case (with
  your matching code) instead of copying the callee.
  A shared `goto` return label can fix block layout. `k = *p++; p += k;`
  for count-prefixed lists.
- IMPORTANT (found in batch 14): some game files (e.g. the script VM around
  0x1c08f0-0x1cc208) were built WITHOUT strict aliasing. If a function's only
  problem is loads that the original keeps after stores through other types
  (reloads), test it with `--out-dir src/hand/nostrict` (scratch file in
  src/hand/nostrict/). Put such matches in src/hand/nostrict/<YOUR_FILE's
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
  Whole-file checker linking at real addresses: /tmp/claude-0/s/w26/full.py
  FILE; rodata-tolerant try: /tmp/claude-0/s/w26/ro.py.
- Callee-defined-earlier cases: if the callees sit in src/auto/*.c, report
  them; the coordinator moves the callees next to the caller.
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
- From batch 44: inlined lw/lhu/lbu copies are strcpy(buf, "literal") (memcpy gives signed lh/lb). String literals are fine in YOUR_FILE under the rodata comment.
- From batch 41: if m2c shows `(s64)(f() << 0x20) >> 0x20` at a call site, the callee returns s64. K&R definitions with u8 params give the andi sequence (avoid unless needed; checkers miss them).
- From batch 43: `jal sqrt; nop` / `jal __truncdfsf2; nop` with a fillable slot: nofill. Distance helpers: static inline double inl_dist(...) { return sqrt(dx*dx+dy*dy); }.
- From batch 42: an unexpected jal+epilogue instead of a tail j: wrap the final call in `do { f(); } while (0);`.
- From batch 45: gcc 2.96 sched1 moves stores whose register dies ahead of
  stores of 0/live registers; within each group source order holds. Search
  one field order against several sibling functions at once:
  /tmp/claude-0/s/w45/patsearch.py; sched dumps: /tmp/claude-0/s/w45/dump.py.
- From batch 46: if one layout symbol is really several original functions
  (a caller ends in `j` to the next, or small accessors follow), REPORT the
  split addresses; the coordinator splits layout.tsv. Write each function
  separately (no section attributes).
- From batch 49: 0x239xxx-0x23dxxx is nofill; 0x23f700-0x245a00 nostrict. A register never set before a call is usually a pass-through argument (the callee takes more args).
- From batch 48: 0x236970-0x23d4xx is nostrict_nofill. GIF tag stores: source order is the reverse of the store order.
- Whole-file check (preferred): `python3 tools/checkfile.py YOUR_FILE`.
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
- Under nostrict a load can't move above an earlier store it may alias: derive statement order from where each load sits among the stores. hill climb: /tmp/claude-0/s/w62/hill.py (parallel-safe).
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
- Whole-function VU0 asm with sq-saved frame: unused local `u128 buf[N]`, `register u128 *c asm("$2")`, inputs incl. "m"(buf[0]), clobber $8-$19 + memory. Generator: /tmp/claude-0/s/w64/gen_vu.py NAME start end. Flag such functions with a /* VU0 */ comment.
- pos.py (/tmp/claude-0/s/w64/pos.py) tries every position of given lines in a /*P*/../*Q*/ block.
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
- Callee-earlier cases: SAVE the matching code to /tmp/claude-0/s/<you>/ and name the file in your report.
- Spill-slot order follows declaration order; declare locals in slot order. `(n-1) << 4` vs `* 16` can differ.
- `i = 0x10000; while (i--);` gives the 4x-unrolled countdown.
- Switch range check then redundant beqzl+nops: `if (c < N) { switch (c) {...; default: s++;} } else {...}`.
- `default: return;` first in a switch avoids a tail call.
- Jump-table functions can be checked with /tmp/claude-0/s/w68/rotry.py <rodata_addr> try ... (links .rodata at the table address).
- `a + (b - 0x7000)` folds; write `x = a + (u32)(b - 0x7000);` to keep the addiu separate.
- A global pointer read inside a loop gets hoisted with its own lui; pre-loading into a local shares the lui across loops.
- `lhu` after `sw` to the same s32 global: `*(u16 *)&D_x`.
- Global counter kept in a register through a loop: write plain global code (`D = 0; for (...) D++;`); a local counter breaks it.
- `jal f; lui; addiu s0; sw v0,0(s0)`: write `t = f(a); p = &G; *p = t;`.
- Tail call returning a value: make the function s32 and `return f(...)`.
- Stop `(n-1)*16` folding with a separate local `m = n - 1`.
- Loop ending `li sN,2 ... bgez sN`: write `for (i = 2; i >= 0; i--)`.
- Stop GCSE merging an address: spell it as another symbol + offset (`D_x[-2]`).
- Rodata functions in a multi-function file: /tmp/claude-0/s/w73/road.py.
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
- /tmp/claude-0/s/wqb03/rr.py places rodata and all file funcs at real addresses (callee-above + rodata).
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
- Pi 0x40490fdb: `3.141592801f`. Literal helper: /tmp/claude-0/s/b06/lit.py.
- Big setup blocks: hill-climb each block of stores/loads separately, then combine the .best results.
- Stack-param functions: which params get s-registers follows use counts; extra references to one param change spills.
- Inline result assigned in a plain statement shares one stack slot across expansions; inside an if-condition/void inline/return each gets its own slot.
- Cross-jumped switch case bodies: write them as an inline taking constant index args.
- `x >= K` emits c.le.s with swapped operands; `!(x < K)` becomes `x < K`.
- Never `pkill -f` (kills your own shell); kill by PID.
- 16-byte GIF register packet: struct of u64 bitfield regs, write data words with `*(u128 *)&D.field = K` (por/lui/sq then sd).
- `(X + 1) << 4` keeps the addiu before the shift; `* 16` folds.
- Byte-to-float from a u32 colour: cast to (s32) first.
- s-register swaps: diagnose with gcc -dg -dl dumps (/tmp/claude-0/s/b07/dump.py) to see global-alloc priority.
- Find which callee needs to be defined earlier: /tmp/claude-0/s/cons2/probe.py FILE CALLER DIR (stubs each callee above the caller).
- Float param position in a prototype affects caller scheduling; check the callee's real arg order.
- Double literal equal to (double)(float)pi: write `3.1415927410125732421875`.
- Static chain in $v0 (`move v0,sp` before calling a local helper) = GNU C nested function; write the helper inside its parent's body.
- Chained slti range checks: `switch (t) { case 4 ... 8: ... }` with GNU case ranges.
- `lhu; srl 8; andi 0xf` in a loop: u16 bitfield (`u16 r0:8, r1:4, r2:4`).
- Run of single-bit `and`s on one u64 with one ld/sd: 1-bit u64 bitfield assignments in increasing bit order.
- 64 unexplained frame bytes: an unused local array.
- Fixed ad.py (callee stubs regex): /tmp/claude-0/s/wqb09/ad.py; variant tester vt.py and hill.py there too.
- Argument-move order mismatch before a call: run /tmp/claude-0/s/cons2/fperm.py FILE CALLER DIR (tries float-param positions in callee prototypes).
- Unexpected `jal __extendsfdf2`: a callee lacks a prototype above that point.
- Constant in an s-reg loaded before the first call: a local initialised at declaration (`u64 k = 22;`).
- Each call result its own variable (`n`, `n2`) when s-regs swap.
- `X == 0 ? 171 : 172` vs `X ? 172 : 171` flips movn/movz.
- Array base hoisted wrongly: split the index (`k = f(a); v = D[k];`).
- First try natural source order: statements in struct field order, each value computed just before use.
- Latch loop `bnez s1; addiu s1,-1`: `n--; for (;;) { ...; if (n == 0) break; n--; }`.
- `(s32)(v + 4) - (s32)buf` stops packet-size folding. `X = xs; X += bx;` in a loop avoids PRE merging.
- The permuter drops __attribute__((aligned)) in preprocessing; force alignment with a real u64 member instead.
- Read `x = stk[sp]` before calls when the original loads it in a jal delay slot.
- `n = D_X = e->b1;` chained assignment for u16 bitfield values used untruncated.
- If GCSE merges a repeated expression the original computes twice, note it (func_001ca368 matches with -fno-gcse).

- (b15) Callee return type changes regalloc even when the result is unused: declaring a callee `s32` instead of `void` keeps v0 busy, so it changes which registers other code gets and whether cases are cross-jumped. Try both.
- (b15) Shared tails (one copy that several branches jump into): write `X = K; goto tail;` with a `tail:` label inside the case that owns the copy. Writing the tail out in full in each branch fails.
- (b15) A switch variable reused in two cases can land in a0 instead of a1: give one case its own local.
- (b15) In nested switches the source case order sets the block layout. Groups of 3 stores come out "last store first", so permute them.

- (b11) Nofill tell: a call that ends `mflo; jal; nop` means a nofill region, even outside the known ranges (0x1f0ea8 and 0x1f15f0 are nofill).
- (b11) Loop rotation: gcc moves a loop's leading exit test to the bottom. If the original keeps the test at the top, write `if (!c) goto done;` with `done:` after the loop.
- (b11) `case 0: default:` sharing one body gives the `beq 1; slti 2; bnez default; beq 2` tree.
- (b11) A `sltiu` loop bound comes from `i < sizeof(tmp)`. A 10-byte local copied from rodata (ldl/ldr + lb/sb) is a struct assignment: `typedef struct { char s[10]; } Str10; Str10 tmp = D_xxx;`.
- (b11) A `bnezl` where the original has a plain `bnez` depends on the reload register choice. Reordering later statements can move it.

- (cons) **Try implicit declaration.** Deleting an all-int callee's prototype, so it is implicitly declared, changes argument load order and register choice. This fixed 3 near-misses with an argument-load swap or v0/v1 swap. On any such near-miss, delete each callee's prototype in turn.
- (cons) A `void *` struct field instead of s32 changes the strict-aliasing alias set, so the scheduler may move its load above an s32 store. Try this on load/store order swaps.
- (cons) If two functions with double literals land far apart in .rodata, putting them in one file fails `make` even when checkfile looks fine. Keep them in separate files.
- (cons) For random statement-order search use `/tmp/claude-0/s/cons2/blkperm.py SRC FN DIR N`: mark the region with `/*P*/ ... /*Q*/`. For named variants use `/tmp/claude-0/s/cons2/rtry.py`.

- (b16) Out-params: separate locals `s32 a, b;` passed as `&a, &b` stay off saved registers. An array `d[2]` or a struct hoists the address into s7/s8.
- (b16) Running coordinate: write `x = o->x; x += 73;` rather than `x = o->x + 73`, which makes gcc fold the later steps into offsets.
- (b16) A float in the middle of a prototype, for example `(s32, s32, u8*, f32, char*, s32)`, changes argument evaluation order even though the registers stay the same. Use fperm.
- (b16) `if (n==0) .. else if (n==1)` stops gcc merging the tests into one sltiu. A 1-bit bitfield `== 1` keeps `li 1; bne`. `z = y = x = 128` gives the 8,0,4 store order.
- (b16) Nostrict global reload: assigning a pointer twice (`g = 0; g = &S.sub;`) forces the global to be reloaded after stores through it.

- (c00) On huge functions where the size differs, word-count scoring misleads. Score with an instruction-sequence diff that ignores branch targets instead: /tmp/claude-0/s/c00/sdiff.py, vt2.py (variants and PERM blocks) and hill2.py (hill-climb between /*P*/ and /*Q*/).
- (c00) Volatility can be mixed: make some globals volatile and leave others plain.
- (c00) Two switch cases that share a tail: write both with one static inline helper so gcc cross-jumps them.
- (c00) A u64 GIF tag stored as two 32-bit words: keep it in a `u64 tag` variable and store `(u32)tag` and `tag >> 32`.
- (coord) When a string literal sits in rodata before this function's own strings, an earlier function owns it. Check with `llvm-objdump -s -j main SLPS_251.98 | grep "^ 4917"` and use `extern char D_xxx[]` for it.
- NEVER kill processes you did not start (no `ps | grep | xargs kill`, no pkill). Other workers share the machine.

- (b17) Count a callee's real arguments from its asm. A leftover extra argument from m2c changes register choice across the whole function (it caused 7 of 8 wrong words in one case).
- (b17) A local reused for an unrelated constant blocks loop-invariant hoisting. Use separate locals. The first assignment of a stack-spilled local gets the lower slot, so declaration order sets the stack layout.
- (b17) rr.py shares one temp dir. Run it with `-j 1`, never inside parallel vt.py runs.

- (b14) A 64-bit header constant used only once: write it straight into the store (`p[12] = 0x30AE400000008004;`) with the stores in natural order. Don't hold it in a variable assigned before the call.
- (b14) Packet builders: use one header pointer `u64 *p = buf + 2; ... p += 14;` and index vertices as `((Vx *)p)[i]`. Declare the colour as `u32 c`.
- (b14) Removing an unused local can change codegen. Confirm any parallel-search hit with a serial checkfile run.
- (b14) 0x219000-0x21f000 is nostrict.

- (c01) 0x120000-0x133fff is nostrict. Sign: a load placed after a store of an unrelated type, for example `lwc1 c->f` after `sw a->flags`.
- (c01) Switch case bodies are emitted in source order, so order the cases by their address in the asm, not by case value.
- (c01) A u32 bitfield converted to f32 needs an explicit `(u32)` cast to get the unsigned bltz/srl/or/add.s sequence.
- (c01) `x.b ^= 1` gives xori, while `x.b = !x.b` gives sltiu. Chaining `A = B = 1.0f;` fixes the global store order.
- (c01) Passing a call result straight as an argument stops cross-jumping with a sibling case that uses a temp.

- (c04) A flag word tested with ld/and/sd and dsll/dsra32/andi is u32 bitfields declared directly in an 8-aligned struct. Shift-and-mask on a u64 gets the scheduling wrong.
- (c04) A float constant kept in a callee-saved FP register across a loop needs a local assigned before the loop (`lim = 20.0f; do {..} while (d >= lim)`).
- (c04) A shared `goto r0` instead of repeated `return 0` stops gcc hoisting v0=0 above the first test. `if (d) { r: return 0; }` placed in the last test gives the jump-over shape.

- (c05) Nostrict: a store to a plain scalar global may not force reloads of struct fields. Declaring the global as a one-element array (`extern s32 D_x[1];`) brings the reload back.
- (c05) To stop gcc cross-jumping two identical inline-asm VU0 blocks, give the second helper slightly different whitespace in its asm string. In inline asm, write `ACCxyzw` and `Q` without `$`.
- (c05) sq/lq of t-registers around calls are compiler caller-saves (TImode), not hand-written asm.

- (c02) VM interpreters: `(u16)op >> 8` gives `andi 0xffff; srl`. `for (i=0;i<n;i++) pop(vm,&args[n-1-i]);` gives the countdown loop.
- (c02) A switch on a 2-bit field compiled with signed slti means the field is a u32 bitfield.
- (c02) Writing `n = kk - 1; D[n].m[3][k]` as separate statements stops gcc folding n into the base address.
- (cons) The callee-earlier effect needs an emitted callee body in the same file. A `{}` stub works for probing. `extern inline`, attributes and K&R prototypes do not.

- (c07) GNU nested functions: a function that receives a static chain in $v0 (`move v0,sp`) is nested inside its parent. Declare them in the parent as `auto void func_X(void) asm("func_X");`. This builds and matches; func_001a7718 and its 5 nested functions are done. Wrapping the parent's scalars in one struct pins their stack layout.
- (c07) Spill slots are assigned in declaration order of the spilled variables. `fl & ~8` with s32 fl gives `li -9; and`; with u16 fl it gives andi.

- (c08) Duplicate identical case bodies (cross-jumping merges them back) to make the loop bigger. The second loop pass stops hoisting case constants once the loop is large enough, which frees registers. This took one function from 134 words to 43.
- (c08) An unrolled `a[k]` run addressed through `addiu reg,sp,N` comes from a separate index variable `j = k; a[j]`. In nested switches, copy each sub-switch's case-body order from the asm.
- (c08) `p = f(); while (p) { ...; p = f(); }` gives the rotated loop with the call at the bottom. `srl; nor; andi 1` is `~(x >> 23) & 1` with x as u32.

- (c06) Two separate arrays `s32 ca[4]; s32 cb[4];` instead of `s32 ci[2][4]` give two loop pointers hoisted out of the loop. A 2-D array strength-reduces to one pointer.
- (c06) `r0 = r1 = sqrt(..)` instead of `r1 = ..; r0 = r1;` changes FP callee-saved register priority. Test `i < 4` at each site rather than caching the comparison in a flag.
- (c06) If gas fills an empty `b` slot from a preceding inline-asm `sqrt.s`, wrap the asm in `.set noreorder ... .set reorder`.

- (c05b) An inline asm's clobber list changes CSE. A volatile asm with no outputs and no clobbers flushes CSE's hash table, so addresses get recomputed after it. `"memory"` changes hoisting differently. Try each helper with and without "memory".
- (c05b) A `goto` into the middle of a loop gives it multiple entry points, so nothing is hoisted out of it. Use /tmp/claude-0/s/c05b/prio.py FILE to see each variable's register-allocation priority (from -dl/-dg dumps). /tmp/claude-0/s/c05b/sd.py -n -v separates structural differences from register differences.

- (c10) Menu string-builder family (0x1e4xxx-0x1e7xxx): copy the types and style of the matched siblings in src/hand/text_001d0000_b11.c and text_001c0000_c10.c.
- (c10) Shared tail after a switch: write the whole tail inside a `default:` placed first in the switch. Script-VM handlers returning 2: use an early `{ vm->sp -= 2; return 2; }` inside the loop rather than `goto end`.

- (c09) `__builtin_memcpy(dst, p, 16)` into a 16-aligned Vec gives ldl/ldr + sdl/sdr pairs.
- (c09) Each invariant gcc's loop pass moves lowers the bar for the next one, so one extra instruction in a loop can flip a store from the invariant base register to the walker register.
- (c09) A tail call inside a switch case needs `f(); return;`, not `break`. Declaring locals inside case blocks avoids nostrict reloads.

- (c03) `PlatSqrtf()` from platform/math.h gives a bare sqrt.s; plain sqrtf adds a NaN check. Float literals parse one unit low: 0x40490FDA needs `3.14159251f`.
- (c03) Repeated groups of calls with arguments held in s-registers are an inline helper; making it one took a function from 654 to 275 words.
- (c03) Declare a spilled loop-local pointer inside the loop body, not as a reused outer variable. A `bnel` to an out-of-line block means the source condition is inverted.
- (c03) Separate `x = 0.0f;` statements give `sw zero`; a chained assignment gives mtc1 + swc1. `(u32)w->w38 & 1` reads the low word of a u64 with one lw.

- (c11) A parameter reused as an accumulator (`val = x*16 + 0x7000; ... val += adv;`) instead of a separate local fixed every s-register swap in the text drawers.
- (c11) Window drawers that call func_001f4570 or func_001f45e0 need the callee defined above them: test them with a stub. /tmp/claude-0/s/c11/hill3.py NAME FILE DIR ITERS SEED is a hill climb that keeps dependencies intact (set CHK=1 to score with checkfile).
- Do not delete dot-files in src/hand that you did not create; other workers' hill-climb files live there.

## Session 6: facts and tricks from the workers

Raw notes, one line per finding, grouped by worker list. The session-6 worker brief (CONTEXT_ONLY, output layout) is nonmatchings/session6/BRIEF.md. Region/mode facts are also in docs/toolchain.md "Session 6", SDK facts in docs/sdk.md.

### Lists L00-L28, N32
- (L06) -fno-gcse modes: func_0014b550; signs: repeated `ld` reloads or 0.0f held across branches that gcse merges. Region 0x142e30-0x14b550 maybe. 0x13bb20-0x13c2f0 nofill.
- (L06) Address in s-reg: `pp = &D; *pp = f(...);` right before the store.
- (L04) 0x11f000-0x127xxx nostrict (fill on). Callee-above effect may need a callee at a join point, not the obvious one: probe every callee. `goto done` instead of break rotates a while loop like the original.
- (L04) `if (k == 3) idx = j; else idx = ...;` stops constant hoisting; constants in if/else chain give bnel+lui/ori, a variable gives movn.
- (L03) Callee returning u64 (`hit << n`) changes callers; cast at call site when one caller treats it as s32. `"=&r"` early-clobber on VU0 asm outputs fixes register choice. Unused 16-byte local fixes frame size.
- (L02) Layout: func_001136d8 is two functions (0x1136d8, 0x113768). Callee return type void vs s32 toggles register allocation: try per callee. `h = t/216000; t = t%216000;` (h unused) keeps an extra move.
- (L08) Locals declared inside a static inline are not hoisted by the loop pass; move stack arrays into an inline helper when the original recomputes `addiu aN,sp,K` in the loop. Rodata floats as `extern f32 D_0048xxxx` resolve via symbols.ld.
- (L05) Unmatched drafts work as CONTEXT_ONLY context (0012e4b0 over the e1b0 draft, 00130f18 over the 0660 draft). 8-aligned union for a u64 queue word gives ld/dsrl32 + ld/and/or/sd.
- (L00) Layout: func_00100558 is 40 bytes (b delay-slot nop). Implicit declaration of callees fixed two functions. Inline helper that modifies its own params gives "sll; move; addiu" copies.
- (L09) A redundant explicit `else` makes loop.c move `found = 1; break;` exit stubs ahead of the loop (213w -> match). nostrict reaches at least 0x1784c8. func_00171078: gas split a macro `lw sym(reg)` into the jr slot (lui; addu; jr; lw %lo); not reproduced in C.
- (L07) autodecomp --diff hides nop runs (objdump shows `...`); use objdump -z. 0x156e88 nostrict_nogcse. Volatile function-pointer member stops jalr slot filling. Loop-invariant constants get registers in statement order. 0x152c28-0x159c10 strict; 0x15ad08, 0x15ea98-0x15f128 nostrict. lq/sq u128 zero stores are C (func_0015f128).
- (L01) nogcse region ~0x10c720-0x10ed20 (func_0010e610 nostrict_nogcse; c f38/ec08 near in nogcse). Sign: global base lui/addiu recomputed before each loop. ee-gcc does not unroll: unrolled code is in the source. sched1 interblock can hoist a compare above a branch (no source fix found).
- (L12) '=r' constraint on an f32 asm output makes gcc emit the mtc1 itself. 0x1a2d40/0x1a5740 nostrict. func_001aadf0 (21 insns) never attempted.
- (L10) 0x17b000-0x183b20 nostrict. Separate byte counter (off += sizeof(E)) for two induction vars. A constant hoisted before a loop means the return tail was inside the loop (for(;;){...; return;}).
- (L11) 0x186000-0x19a000 nostrict except 0x18e348-0x18e588 nostrict_nofill. VU0 helper asm needs .set noreorder/.set reorder or gas pulls sqc2 into jr ra slot. Entry-pointer lookups for shape tables.
- (L15) Layout: func_001dd5c0 contains func_001ddbf8 (split). Nofill 0x1d5b58-0x1e0xxx. func_001c4640 prototype must return s32. Loop form for(...; i = k){ k = i+1; ...} stops strength reduction.
- (L13) Unused local array gives bigger frame and stops a tail call. sched1 does interblock motion only in functions with <=10 basic blocks (func_001c1718 matches with -fno-sched-interblock; probably the source has one more block). jump2 cross-jumping runs after sched2.
- (L14) Script-VM 3-value stack pops (95f8, 99a8, cd600, c8a00) share one open problem: address copy chain vs FP register order. cf348/cf3e0 near in nostrict_nogcse. D_003C5510+0x28 is f32.
- (L21) n32 mode for the no-`la rd,sym(rs)` region 0x20dd38-0x2173xx. nogcse region 0x2114f0-0x214f50. Check callee arg counts in the callee asm. `case 2: default:` for beq1/slti2 trees. Cross-jumped tails come from duplicated source.
- (L16) message builders need `s32 func_001c4640(Msg *)`. Copy a var to stop fold_range_test merging `a==-2||a==-3||a==-4`. Global-pointer locals in s-regs give full lui+addiu.
- (L24) `G = *f()` keeps G's address in an s-reg across the call; `h = f(); G = *h;` puts lui/addiu after it. 0x238768-0x2412xx nostrict. Separate id counter to get countdown loops.
- (L18) 0x1fade0-0x1fcdc8 nostrict. Locals declared inside case blocks get s-registers first. func_001f9e48/001fa8b0 show the unfolded table base (lui+addiu) sign: try n32 mode.
- (L23) Several layouts of one symbol in a file: #define X X_sN + __asm__("X") label. 0x22f000-0x234910 strict. Draw-call callees as s32 not void. Writing an indexed global expression out in full per argument gives pointer-copy move chains.
- (L25) Strings used in a static inline are emitted where the helper is defined (sets rodata order). 0x249xxx-0x24bxxx strict, 0x24d618 nofill, 0x24f098 nostrict_nogcse. Dead statements (unused loads, dead divides) can fix scheduling.
- (N32) 0x20dd38-0x20e27c fully n32 (6 matched). 0x212cc0, 0x2134c8, 0x217000 mix folded offset-0 symbol loads (lw sym(reg)) with split addresses for symbol+offset; no mode gives both: probably a patched compiler. Tried -msplit-addresses, o64, 64, long64, half-pic, embedded-data, older ee-gcc.
- (L19) 0x1ff488-0x2040f8 nostrict. Leftover dead li 100/li 10 from div-by-zero checks count the source's div/mod expressions. Object pointer in s8 makes sched2 treat its loads as frame loads (ordered against spills).
- (L28 SDK) libcdvd: scePrintf/sceSifInitRpc return void; globals D_0046C628/630/634/654/624 often volatile. strtol (0x272a00) is ee-gcc 2.96 with fill (src/sdk/auto), not newlib no_fill. ctype table indexed (D_00491A18 + 1)[c].

### L22
- Callee return type changes caller regalloc even when unused: declare s32 func_001f9438, 001fc308, 0011d768, 002345a0, 001fb428.
- Crossjump: shared error store before epilogue = last source statement reached by goto; `bnel` w/ code in slot from `if (q==1){...} D=-4; return;`.
- Permuting store statements finds scheduler-bound store order (a698).
- Passing incoming a0 to a no-param call keeps a0 live (eef8).
- func_0021d860 standalone replaces the #if 0 copy in text_00210000_c15.c.
- Save struct D_00304BE8: party idx +0x48E, item counts +0x499 (max 99); members 0x74 bytes from +4, item count +0x21, slots +0x22.
### L26
- New mode sdk/gcc991111_as296 (as_compiler override): 991111a cc1 + 2.96 gas, which fills jr delay slots. Worker says all existing gcc991111/libkernl files still match with 2.96 gas.
- newlib vfprintf built with _NO_LONGLONG; tty regs are volatile.
### L27
- frame.c unwind (0x263840-0x264258) matches in sdk/auto (2.96 strict).
- __muldf3/__divdf3 match once __pack_d is not defined in the same file (callee-above from dp-bit.c was the session-5 mismatch).
- __pack_f: `normal_exp >= EXPBIAS + 2` for beqzl.
- 991111 struct store order follows alias sets: declare SIF struct fields all u32/int.
- 991111 reorg never puts a volatile load in a delay slot; sceGsSyncPath cfc2 needs `register u32 r asm("$6")`.
- sceGsDefDispEnv smode2: nested if with separate stores (ternary gives movn/movz).
- Asm-only: func_00260738 (cache loop), func_002607e4 (jr ra stub), func_00265190 (MMI strncpy), func_002654f0 (VU0 cfc2/ctc2).
### G1
- nostrict: reusing one pointer var across different globals loses its alias base -> conservative load-after-store order (241d60).
- autodecomp --diff objdump lacks -z (hides nop runs); difflib misaligns big functions, use LCS.
- D_004D5300 = D_00495280 + 0x40080 (s8 glyph width table).
- 0010d470 glyph stores: `g = &b->g[n++]; g->x = ...`.
### NB
- void->s32 callee return type matched 1cdcb8 (func_001c4640) and 24d1c8 (func_001f31a8): sweep callee return types on every near miss.
- Wrong epilogue lw v0/ld ra or arg-move order: duplicate the early `if (c) return G;` before the call.
- Shared constant divisor in a local set before the branch moves the li into the delay slot (1f0448).
- 1e0ab0/1e0d98/1e10f8 (2w): shared `r4: return 4;` label + volatile store fixes slots; volatile costs the %lo fold.
- First sched pass moves `$2=const` return sets across blocks (e6038).
- permuter scores mislead with CONTEXT_ONLY copies and rodata.
### F9
- 0x1f9e48-0x1fbcd8 is nostrict_nogcse; fd858 hand/nostrict with gcse. n32 does not apply here (saves $f21, lui at float consts).
- "Unfolded table base" = loop.c hoisting a symbol address out of a real for loop (goto loops don't).
- Digit loops: `dig[n] = val % 10; val /= 10; n++;`.
- Extra separate variables raise ref counts and can force the original's spills (fbcd8 179->58w).
- s16 vs u16 for masked fields: s16 gives `li -16; and`.
- hill4.py (hill-climb statement order by words-differ) and perm.py (exhaustive small blocks) in tools/matching (paths may need fixing).
- Cross-jumping after reload is active at -O2; missed merges hint at a different regalloc.
### G2
- 0x225ea8 nostrict; 0x2524a0 = newlib _vfprintf_r with FLOATING_POINT + _NO_LONGLONG (keeps `_double || flags & ALT == 0` bug).
- func_00233ef8 takes 1 arg; request functions near 0x234018 return s32.
- Stack slots that look like locals may be caller-save spills; local array + pointer reproduced them.
- 0x1f5fe0: LERP macro; inline per-case temps fixed FP regalloc; popt.py greedy permutation 663->338.
- wqb03_rr.py is not parallel-safe with RO set.
### NA
- void->s32 callee return types fixed 1cdc58 (func_001c4640), 1369e8 (func_00114a38), 137330 (func_0012bce0); the permuter finds these by mutating prototypes, so read its prototypes.
- `for (i = 0; i < 2; i++) f("lit");` is fully unrolled: sign is %hi of the string kept in an s-reg with `addiu a0,s0,%lo` repeated (0x11ecd8, nofill).
- One chained assignment of six -1 stores in a brute-forced order (104908). Brute-forcing orders with many copies of a function in one compile is cheap (~5000 variants in 3 s).
- Moving a constant assignment after calls (1453a8), a float argument in a temp (179d30), a zero variable for a loop test (14b9e0) all change scheduling.
- `if (...) goto r0;` instead of `return 0` (144810); `if ((b || a) && f())` (177ac0); u16 var gives dsrl (1bb6d0).
- 0x1429f8, 0x144810, 0x179d30, 0x1369e8 match in strict as well as nostrict.

## Session 7


The session-7 brief is nonmatchings/session7/BRIEF.md and every worker's findings
are in nonmatchings/session7/NOTES.md (condensed); docs/matching-tips.md "Session 7
tips" is the short version.

## Session 8

The session-8 brief is nonmatchings/session8/BRIEF.md and every worker's findings are in
nonmatchings/session8/NOTES.md; docs/matching-tips.md "Session 8 tips" is the short version.
