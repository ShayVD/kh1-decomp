# Decompiling: tools and workflow (sessions 2-5)

## Picking functions: `make rank`

`kh1tool.py rank` (or `make rank ARGS="..."`) scores every function in
layout.tsv and writes `out/rank.tsv`; the console shows the easiest
undecompiled ones first.

- `score` = instructions + 2×branches + 4×calls + 2×tail calls + 10×jump tables
  + 50 if "hard".
- `category`: `stub` (≤2 instructions, no memory access), `getter`, `setter`,
  `thunk` (only a tail call), `wrapper` (one call, no branches), `loop` (leaf
  with a backward branch), `leaf`, `other`, and `hard`: anything with VU0
  macro instructions (COP2, lqc2/sqc2), 128-bit `lq`/`sq`, MMI (`p*`
  instructions), COP0 or `syscall`. Hard functions are hand-written assembly,
  inline asm or platform code; leave them for `.s` files or platform wrappers.
- `twins`: how many functions share the same shape (instructions with call
  targets and `%hi`/`%lo` halves masked). One C body often matches all twins.
- Options: `--segment game|sdk|all`, `--category setter,getter`, `--leaf`,
  `--max-insns N`, `--summary`, `--all` (include functions already in src/).

Game segment at the start of session 2: 5,141 functions; 243 are `hard`.

## Looking at a function: `kh1tool.py asm` / `kh1tool.py m2c`

`asm func_00123456` prints the original in decomp.me / m2c syntax: `$`
registers, `.L` labels, `func_`/`D_` (or functions.tsv) names for calls and
`%hi`/`%lo` pairs, and jump tables as `jtbl_` data. Paste it into a
decomp.me scratch (platform ps2, compiler ee-gcc 2.96, flags `-O2 -G0`).

`m2c func_00123456` runs m2c (fetched by `make toolchain` into
tools/toolchain/m2c, pinned commit) with `-t mipsee-gcc-c` for a first draft.
m2c output is a starting point, never a match.

## Bulk matching: `tools/autodecomp.py`

For each selected function: m2c draft (4 option variants), compile it alone
with the project compiler, link it at the original address with every
placeholder resolved, compare bytes. Exact matches are kept.

```sh
python3 tools/kh1tool.py rank --limit 0             # refresh out/rank.tsv
python3 tools/autodecomp.py try func_00123456 --show
python3 tools/autodecomp.py batch --max-insns 24 --write      # all non-hard game functions ≤24 insns
python3 tools/autodecomp.py batch --min-insns 25 --max-insns 60 --write
make && make report                                 # the build is still the judge
```

`--write` groups matches into `src/auto/text_XXXX0000.c` (one file per 64 KiB
of address space, `_1`, `_2`… when m2c's extern declarations conflict). The
original translation units are unknown, so these files are provisional;
phase 4 moves functions into real modules. The code uses `M2C_FIELD(ptr,
type *, offset)` and `M2C_UNK` from `include/m2c.h` for fields and types not
recovered yet. Replacing them with real structs must keep the match.

Results per run go to `out/autodecomp.tsv` (match / mismatch / why).
Mismatches are the hand-work queue; most differ only in register allocation
or instruction order.

Session 2 results (game segment): first pass ≤24 instructions 938/2,107;
after the layout fixes, a pass over everything ≤60 instructions added 308
more (of 3,087 tried). Of the 2,779 failures: 1,996 compile but mismatch
(384 of them by only 1-3 words, the best hand-work queue), 563 are m2c
output gcc 2.96 rejects (mostly pointer/int type clashes, easy to fix by
hand), 212 had m2c errors, 7 need rodata. `out/autodecomp.tsv`-style reports
are not committed; rerun `batch` (without `--write`) to regenerate one.

## Session 3: what autodecomp does now

Per function: m2c drafts (4 option variants, each with and without
`--context out/sigs.h`), fixed up by `tools/permute.py`, then a greedy
search over single edits of the closest draft. A draft's distance is the
number of words not matched in order against the original
(`score` in the report; 0 = byte-identical). Defaults: search only drafts
with score ≤ 16 (`--max-score`), 60 compiles per function (`--budget`), up
to 3 moves to an equally close draft when stuck.

Fixes applied to every draft (all were systematic causes of mismatches):

- **EABI register names.** The asm handed to m2c used objdump's o32 names,
  so `$t0-$t3` (registers 8-11, arguments 5-8 on the EE) looked like
  temporaries. `function_asm(..., eabi=True)` renames 8-15 to
  `a4-a7`/`t0-t3`, as m2c's mipsee target expects.
- **Constants are not symbols.** `lui`/`ori` pairs, and `lui`/`addiu` pairs
  outside EE RAM (`0x00100000`-`0x02000000`), were printed as `%hi/%lo(D_…)`
  and m2c wrote `&D_F7FFFFFF` for a mask or float bits. Now they stay
  numbers.
- **Prototypes.** `tools/sigs.py` guesses every function's argument count
  (EE ABI: ints in a0-a3, t0-t3; floats in f12-f19, numbered separately)
  from the registers it reads before writing, with callees' arguments
  counted at call sites, to a fixpoint; return type from whether any caller
  reads v0/f0 after the call. Written to `out/sigs.tsv` and `out/sigs.h`
  (m2c context). Missing declarations are added from it.
- **Dropped parameters.** m2c omits unused leading parameters
  (`f(void *arg1)`); they are put back so the others stay in their registers.
- **Float literals.** ee-gcc 2.96's decimal conversion is off by one ULP for
  some spellings. Each literal is respelled with one that ee-gcc turns into
  the original bits (found by compiling candidate spellings once).
- **Byte-counted pointer arithmetic.** m2c means bytes in `*(&D_X + n)` and
  in `p += n` on typed pointers; variants rewrite these.

Mutations tried by the search, in order: `volatile` on one extern (gcc then
emits `lui/addiu` + offset 0 and keeps access order; many globals in KH1 are
volatile), rotating a run of ≥3 independent statements by one (gcc emits
the *last* of a run of independent stores first, so the source order is the
asm order rotated), all orders of 3-4 adjacent statements, swapping two
adjacent statements or declarations, signedness of one type, a concrete
type for one `M2C_UNK`, dropping one cast, inlining a temp used once,
`return a != b;` → `if (a != b) return 1; return 0;` (keeps the `sltu`),
value → void return.

Speed: m2c runs inside the worker process (`run_m2c`), so the prototype
context is parsed once; a pass over ~2,900 functions takes about 8 minutes
on 4 cores. The closest failing draft of every function is saved to
`out/autodecomp/fail/XXXXXXXX.c` (first line: the result) for hand work:

```sh
python3 tools/autodecomp.py try func_00123456 --diff            # search, then show original vs ours
python3 tools/autodecomp.py try func_00123456 --file my.c --diff  # test a hand-written candidate
```

Session 3 results: 1,254 → 1,793 matched (+539: 518 from the passes over
everything ≤100 instructions, 2 by hand in `src/hand/`, the rest from
re-passes after each new rule). The last pass over the 2,886 functions
still unmatched at ≤100 instructions: 2,072 compile but differ (
94 by a score of 1-3, the hand-work queue in `out/autodecomp/fail/`), 580
drafts gcc rejects (mostly `sp` used as a value: struct copies through the
stack, which m2c cannot express; and pointer/int clashes), 189 unusable m2c
output, 19 need rodata, 10 call libgcc helpers or `MULT_HI` m2c cannot
write. Functions of 61-100 instructions rarely match automatically (16 of
630): m2c's control flow and temporaries diverge too much; they need hand
work or decomp-permuter.

Remaining near-miss patterns seen while hand-matching (not automated yet):
`*f() = x` where m2c drops the store offset of a struct-returning call;
stores after a call that m2c turned into a tail call (original returns a
field in the `jr ra` delay slot); epilogue `ld s0`/`ld ra` order; a 64-bit
field narrowed on assignment needs an explicit `(s32)` cast
(`func_0012a030`); `(u32)` on a `u8` before `>>` picks `srlv` over `srav`
(`func_00171a88`).

## Session 4: what changed

Two bugs in the asm handed to m2c caused many of session 3's "patterns":

- **`%hi` tracking across calls.** `function_asm` kept a `lui` live in a
  caller-saved register across a `jal`, so `sw s0,16(v0)` after a call
  became `%lo(func_00100010)(v0)` and m2c wrote `*f() = x`, dropping the
  offset (the "dropped store offsets on struct-returning calls" and "lost
  delay-slot returns" near misses). Calls now clobber caller-saved
  registers (after the delay slot).
- **Random registers forgotten.** The "this instruction overwrites rt"
  check read `rt` out of `jal` targets and FPU/VU instructions, so a live
  `%hi` was dropped when a call target's bits happened to name it
  (`lui a0` + `jal` + `addiu a0,a0,%lo` became a plain number). Only
  instructions that really write a GPR count now.

New handling in autodecomp/permute.py:

- **Stack locals (`sp`).** m2c treated the bottom of the frame as outgoing
  stack arguments when its address is taken (`move a0, sp`), turning stores
  into extra call arguments and printing the address as a bare `sp`. EE
  code passes 8+8 arguments in registers and KH1 has no stack arguments, so
  `run_m2c` sets m2c's subroutine-argument area to empty, and
  `permute.stack_buffer` declares the locals area (frame below the
  callee-saved slots, `autodecomp.locals_size`) as `s32 sp[N]` and rewrites
  `spXX` to `M2C_FIELD(sp, T *, 0xXX)`. Compile errors: 580 → 209.
- **64-bit constants.** m2c prints `li; dsll32` constants as
  `(0x8000 << 0x22)` (an int shift); `wide_consts` makes them `(s64)`.
- **Global arrays.** A global used only as `M2C_FIELD(&D_X, T *, off)` or
  byte-indexed `*(&D_X + i * 4)` is declared `extern T D_X[]` and indexed:
  gcc addresses array elements from one base, not symbol+offset each time.
- **Store order from the original.** `STORE_HINT` holds the original's
  store offsets in order; runs of stores through one base are reordered to
  that order (as is, and rotated: gcc emits the last independent store
  first). `rebase` first rewrites `M2C_FIELD(p, T *, 0xA0)` to
  `M2C_FIELD(q, T *, 0)` when `q = p + 0xA0` (sub-struct stores).
- **Widened loads.** `x = *p` read into a wider local first: an `s8` kept in
  an `int` gives `lb` (not `lbu`), a `u32` kept in a `u64` gives `lwu`, and a
  `u8` in a `u64` gives `dsrl` (`func_001162f8`, `func_0012a8c0`).
- **Returned arrays.** A void function that ends with `move v0, base` really
  returns the global array it filled (`retarray`).
- Others: narrowing casts on 64-bit fields, `(u32)` before `>>`, reversed
  store runs, `volatile` removed as well as added, and the search restarts
  from the closest draft with the other `volatile` choice.

**Layout.** A tail call (`j` outside the function, then its delay slot)
now ends a function like `jr $ra` when no earlier branch jumps past it, and
its delay slot is kept even when it is a `nop`. 580 functions that were
glued to the function before them are now separate (6,331 → 6,911); no
already-matched function changed boundaries.

Results: 1,793 → 2,570 matched (see docs/progress.md): 710 from the first
pass over everything ≤100 instructions with the asm fixes, 61 from the new
rules on reruns of the drafts scoring ≤8, 1 from a pass over 101-150
instructions (327 functions: m2c drafts that big are rarely close), 5 from
decomp-permuter. Left at the end of session 4 (≤150 instructions): 91
drafts with score 1-3, 471 with score ≤8, 280 drafts gcc rejects, 246
unusable m2c output, 34 that need rodata.

Still open (not automated, seen in the score 1-3 queue):
- `jr ra` delay slot vs a `%lo`-indexed load or `la` macro
  (`lw v0,%lo(D)(v0)` left out of / put into the slot differently from the
  original; `func_00171078`, `func_00144e88`). Probably a different source
  shape for array indexing; not found yet.
- A value kept in `s0` and moved to `a0` (`move s0,zero; move a0,s0`) where
  m2c propagated the constant (`func_00157668`, `func_001d6080`).
- `sqrt.s` inline where m2c calls `sqrtf` (`func_00162978`): the original
  probably used an inline-asm or builtin sqrt.
- Arguments dropped because tools/sigs.py guessed too few (`func_0021cb88`
  passes a 6th argument in `t1`).

### decomp-permuter: `tools/permuter.py`

```sh
python3 tools/permuter.py import func_00123456 [--file draft.c]  # out/permuter/func_00123456/
python3 tools/permuter.py run func_00123456 -j4 --stop-on-zero
python3 tools/autodecomp.py try func_00123456 --file out/permuter/func_00123456/output-0-1/source.c
```

`import` takes the closest autodecomp draft (or `--file`), preprocesses it
(the permuter parses C with pycparser), assembles the original from
`kh1tool.py asm` with modern binutils (`-march=r5900`; ee-as 2.10 does not
take `$`-named registers) and writes a `compile.sh` running ee-gcc 2.96 +
fix-obj. `run` clones decomp-permuter into tools/toolchain/ on first use.
`batch queue.txt --seconds 120 --write` runs each function in turn and
writes the verified matches to src/auto/. Session 4: the 40 closest drafts
of 61-150 instructions, 2 minutes each with 4 jobs: 5 matched (all from
drafts scoring ≤6 by our measure; the permuter mostly moved statements),
none from drafts scoring 8 or more. Worth running longer on the
score ≤8 group only.

The permuter's score is its own (it ignores stack offsets and weights
register differences lightly): a score-0 output still has to pass
`autodecomp.py try --file` (which accepts its preprocessed source) and
`make`.

Hand-matched code goes in `src/hand/text_XXXX0000.c` (same grouping as
src/auto/, with names and comments where the meaning is clear).

## Structs: `tools/structs.py`

Groups functions that pass their own first argument unchanged to another
function's first argument (from the machine code; callees reached from
more than two 64 KiB regions, and SDK code, are treated as generic helpers
and do not join groups). `tools/structs.py` lists the biggest groups and the
offsets/types their matched code accesses through `arg0`;
`tools/structs.py apply --seed func_X --struct Name --header include/name.h --write`
writes a struct (most common type per offset, overlaps dropped, unmatched
drafts in `out/autodecomp/fail/` count as evidence) and rewrites the
group's matched functions whose `arg0` is only used as a field base, a call
argument or compared with NULL. Accesses with a different type keep their
`M2C_FIELD`. `make` must stay byte-identical. See docs/structs.md.

## Rodata (switch tables, strings, float/double constants)

gcc 2.96 emits a function's string literals and constants just before the
function and its jump tables inside it, all into one `.rodata` per object.
The build now:

1. compiles C to assembly (`ee-gcc -S`),
2. `kh1tool.py split-rodata` moves each piece into `.rodata.<function>`
   (constants between functions belong to the next `.ent`),
3. assembles with the same driver (byte-identical to direct `-c`),
4. `link-script` infers each `.rodata.<function>`'s original address from
   the function's `%hi`/`%lo` pairs (our pair gives the offset inside the
   section, the original pair at the same offset gives the address) and pins
   it there (`.r_XXXXXXXX` output sections, listed in `out/gen/rodata.tsv`),
5. `patch` writes those bytes into the image and `verify` reports
   `RODATA MISMATCH` for any block that differs.

So a function with a `switch` or string literals can be written naturally.
Inference needs the code to match in shape; while it does not, the warning
"references disagree on its original address" is expected. Rodata that no
placed function references stays out of the image. File-scope `const`
tables are attributed to the next function in the file; if that is wrong,
declare the table as an `extern D_XXXXXXXX` instead. The self-test covers a
jump table and string literals.

The batch matcher skips candidates that produce rodata (m2c refers to
strings and constants as `D_` symbols anyway).

## Session 5: what changed

**Layout.** A function entered only by a tail jump (`j`, no `jal`) is now
its own function (35 more entries, 6,911 → 6,946).

**tools/sigs.py** (argument counts) now builds a CFG with delay slots and
runs a liveness pass over it instead of a linear scan, so an argument read
on one path only counts (`func_0021cb88`'s 6th argument in `t1`). It also
follows jump tables (`lui`/`lw %lo(T)(b)` bounded by `sltiu`), counts the
named arguments of variadic functions (the ones they do not spill), and
takes kernel syscall stubs' argument counts from ps2sdk's kernel.h.

**permute.py rules added** (each found in the score 1-3 queue):
- integer dereferences m2c writes (`*(s32 *) x` on an `int`): the rejected
  lines are rewritten and recompiled (`fix_compile_errors`);
- callees called with differing argument counts are declared without a
  prototype (unless they take floats);
- float spellings (`0.0f` no longer stops the other rules);
- the game's inline square root: a bare `sqrt.s`, which `sqrtf` would wrap
  in a NaN check, is `PlatSqrtf` (include/platform/math.h);
- counter loops m2c split into a counter and a copy; extern results never
  used are declared `void` (v0 free after the call, `func_00157668`);
- early returns (`if (c) { ...; return; }` instead of the inverse);
- `(s32) (x >> n) & m` on 64-bit values (truncate before `andi`) and a
  64-bit constant kept for a 64-bit callee argument (`func_001dbcd8`).

**autodecomp.py.** `usable()` rejected every draft containing `?:` (it
took the ternary for m2c's unknown type `?`); 3 matches and 138 new
scored drafts after the fix. `--out-dir DIR` (batch and try) compiles
drafts with that directory's kh1.toml flags (compiler, `-fno-builtin`,
no_fill), so the same run can target `src/sdk/gcc991111/`. `try --file`
sees the file's own directory's headers.

**decomp-permuter** on the 172 drafts scoring ≤4: 50 matched (commit
`auto: 50 permuter matches`).

**Why m2c output is unusable** (the ~200 left): about 150 hit unknown
types (`?`, m2c could not decide between pointer and int); most of the
rest are instructions m2c does not model, mainly the unaligned 64-bit
`ldl/ldr` and `sdl/sdr` pairs (copies of unaligned structs).

**Hand work on the SDK** (docs/sdk.md "Session 5"): libm complete,
libgcc fp-bit and libgcc2, the libkernl syscall stubs as assembly
(`src/sdk/libkernl/syscall.s`, one `.section .text.<name>` per stub: the
build accepts `.s` sources), and most of newlib's libc. Static functions
need a functions.tsv entry like any other (the build places functions by
`.text.<name>`).

Results: 2,570 → 3,216 matched; game segment 2,821 / 6,224, SDK 395 / 722.
A full-game autodecomp pass (`--max-insns 5000`) found few new matches
(the easy ones are done): the rest needs permuter time or hand work.

### Session 5, second half

- **permute.py**: `goto_loops()` turns m2c's `goto` loops into real loops
  (both compilers align a real loop head, `.p2align 3`, which shows as a
  nop before it; m2c's goto loops get none); `chain_stores()` writes
  consecutive float-constant stores as one chained assignment
  (`a = b = 0.0f` keeps 0 in an FPU register, `mtc1 zero`/`swc1`, where
  separate stores give `sw zero`).
- **kh1tool.py split_rodata** names a function's inner rodata blocks
  `.rodata.<fn>.<n>` (`_dtoa_r` has several).
- **Strict aliasing**: the game was built with it (gcc 2.96's -O2 default).
  `-fno-strict-aliasing` breaks 7 matched functions; drafts that need the
  original's reloads need the real field types instead.
- **tools/asm_export.py** writes functions as `.word` assembly (libvu0).
- **VU0 code in game C**: inline asm assembles with ee-as if written in its
  syntax: `vrxor R, $vf2x` and `vrnext.x $vf1x, R` (no `$` on R; the other
  macro instructions take `$vfN`). The pppRand*Frame classes and their
  helpers (src/hand/ppp_rand.c) inline one `vu0Rand()` asm block and match
  in C, so game VU0 code should be tried in C with inline asm before
  exporting it as assembly.

### Session 5, hand-matching at scale

About 1,700 functions were matched by hand in session 5, by parallel
workers each given a list of 25-50 functions of one size band. What they
found that the next session needs:

- **Build modes by directory** (kh1.toml overrides). The game was not
  built with one set of flags; each original source file had its own:
  - `src/hand/` : `-O2 -G0`, strict aliasing, gcc fills delay slots.
  - `src/hand/nostrict/` : `-fno-strict-aliasing`. Loads stay after stores
    through other types. Large parts of the game: 0x13c000-0x149000,
    ~0x150de0-0x165000, 0x167000-0x174300, 0x18a000-0x1a1000, the script
    VM around 0x1c08f0-0x1cc208, 0x23f000-0x245a00.
  - `src/hand/nofill/` : gcc's delay-slot filling off (the assembler
    fills only what it can: `move a0,v0; jal; nop`). E.g. 0x1d17d0-0x1d1ef0,
    0x1d5168-0x1d5974, `jal sqrt; nop` code.
  - `src/hand/nostrict_nofill/` : both (0x236970-0x23d4xx).
  When a draft is close but loads/stores are reordered, or a fillable slot
  is a nop, try the other directories before changing the C.
- **Callee defined earlier in the same file** changes the caller: gcc 2.96
  knows the callee's register use, so `bnel`/`beqzl` after a call become
  `bne`/`beqz`. A one-word branch-likely mismatch right after a call means
  the callee must be defined above the caller, i.e. both were in one
  original file. Several functions were moved next to their callers for
  this (e.g. src/hand/text_00240000_gs.c, text_00240000_e8040.c).
- **`tools/checkfile.py FILE`** compiles a whole file and links every
  function at its real address, so it sees the callee effect and catches
  shared-type breakage. `autodecomp.py try` links other functions at
  0x40000000 (a callee in the same file fails with "relocation truncated").
- **layout.tsv splits**: some layout symbols were several original
  functions (a caller ending in `j` to the next, or runs of 8-byte
  accessors after a switch); split them by hand in layout.tsv (17 split
  around 0x1efcd8-0x1fd720). Still to split: func_00249c48, func_00233610.
- **Assembly vs C**: gcc aligns every function to 8 (`.p2align 3`), so a
  function starting at addr%8==4 came from a .s file (18 of them;
  src/asm/text_0024e0a4.s). `tools/asm_to_c.py` turns frameless VU0 leaf
  helpers into C with one `__asm__ volatile` block (src/hand/vu0.c).
- **Matching idioms** collected by the workers (store order, float
  literals, u64 flag bitfields, tail-call control, loop shapes) are in
  docs/matching-tips.md.

## Session 6: what changed

- **CONTEXT_ONLY bodies** (docs/context-only-plan.md): a callee copied above
  its caller with `CONTEXT_ONLY` gives gcc its register use without placing
  it. Unmatched drafts and `{}` stubs both work. Dozens of session-5
  "needs X above" callers landed this way. Probe *every* callee, not only
  the call before the bad branch.
- **Build modes added** (docs/toolchain.md "Session 6"): `src/hand/nogcse`,
  `nostrict_nogcse`, `n32`, `n32_nogcse`, `n32_nostrict`, and
  `src/sdk/gcc991111_as296`. kh1.toml overrides gained `ccflags` (flags for
  the C -> asm step only) and `as_compiler` (the toolchain whose driver
  assembles the compiled C). checkfile and `autodecomp.py try` honour both.
- **Layout splits**: func_001136d8 (0x1136d8 + 0x113768), func_001dd5c0
  (0x1dd5c0 + 0x1ddbf8); func_00100558 is 40 bytes.
- **Assembly**: crt0's `func_00100008` (src/asm/crt0_start.s) and libpc's
  scePcStart/scePcStop (src/sdk/libpc.s), exported with tools/asm_export.py.
- **Near misses**: nonmatchings/session6/INDEX.md (one line per draft: words
  off, mode, what is off). NOTES.md there is the raw worker log.
- **tools/matching/** gained hill4.py (hill-climb statement order scored by
  words differing), perm.py (exhaustive permutation of a small block) and
  popt.py (greedy permutation of statement runs). Fix their hard-coded
  /tmp paths before use. wqb03_rr.py is not safe to run in parallel.
- `autodecomp.py --diff` uses objdump without `-z`, which hides nop runs;
  for big functions count differences with an LCS, not difflib.
- Results: 6,415 -> 6,729 / 6,988 functions (96.3%), 70.4% -> 80.2% of code bytes; game 6,032 / 6,266, SDK 697 / 722.

## Session 7: what changed

- **Hand-written asm exported** with tools/asm_export.py: src/asm/vu0_render_{1,2}.s
  (VU0 renderers func_001b8198, 001b6910, 001b1ab8, 001afac0, 001b3870, 001ab0e0,
  001ae010, 001606d0, 00115940), src/asm/text_001aa1f8.s (sq $zero clears, the
  func_001bfac8 context switch), src/sdk/libkernl_asm.s, src/sdk/libkernl_exc.s.
  Caveat found later in the session: the ppp Tail-draw functions, which look just
  like the renderers (gcc frame, VU0 runs between C), matched as **C with VU0
  helpers as `#define` macros of inline asm** (src/hand/nostrict/text_00180000_s7_w11.c).
  Later still, func_00115940 and func_001606d0 matched as C + VU0 macros
  (src/hand/text_00110000_s7_w25.c, src/hand/nostrict/text_00160000_s7_w25.c) and
  left the .s. func_001b8198 is different: only its shell is gcc; its ~10 render
  loop bodies are hand-written (`addi`, dead MMI writes, unfilled delay slots, raw
  `c2` words, fixed t1-t9 roles), probably register-asm variables plus large
  `__asm__` blocks. w28 triaged the other six (001b6910, 001ae010, 001b1ab8,
  001afac0, 001ab0e0, 001b3870) the same way: all hand-written inside (`addi`/`add`/`sub`
  and `bne $zero,$x` across >90% of the body, fixed t2-t9 loop roles, unfilled slots,
  DMA polling loops, args copied to t-registers). Their .s stand-ins are the final form.
- **tools/matching/flagsweep.py**: single-flag sweep over drafts and modes
  (docs/toolchain.md "Session 7"). `KH1_EXTRA_CCFLAGS` in tools/checkfile.py.
  The draft's file name must contain the 8-digit address.
- **tools/matching/hc_checkfile.py**: fast hill-climb scored by checkfile
  (`ADDR=<addr> SZPEN=0 hc_checkfile.py FILE MODE TAG ITERS SEED`; lines to permute
  between `/*P*/` and `/*Q*/`, `/*FIX*/` keeps relative order).
- **tools/matching/batch/**: compiles 150-300 renamed variants of one function in
  one file and links them all at one address (batch.py; anneal2.py for
  multi-group permutation annealing). Fix the scratch paths inside before use.
- New build modes: src/hand/nosi, nogcse_nosi, nogcse_nosib, faddr,
  nostrict_norcse, norlo, fmam, nostrict_nosib (docs/toolchain.md).
- Workers: nonmatchings/session7/BRIEF.md (brief) and NOTES.md (findings per
  worker); near misses are nonmatchings/session7/<worker>__<addr>_<N>w.c.
- Drafts of functions that are now matched were removed from nonmatchings/
  (many session-5 drafts were stale).

## Session 8: what changed

- **40 matches** (6,836 -> 6,876 / 6,988; 88.6% -> 91.0% of code bytes), by 20 parallel
  workers (brief: nonmatchings/session8/BRIEF.md; findings: nonmatchings/session8/NOTES.md;
  short version: docs/matching-tips.md "Session 8 tips"). No new build modes or flags.
- **Method**: read gcc 2.96's own dumps to find the pass that differs (local-alloc,
  global-alloc priority, sched1/sched2 rank, reorg, jump2, loop.c, gcse PRE/cprop) and
  change that pass's input from the source. Statement-order brute force alone had
  stalled most of these drafts in sessions 6-7.
- **Callee-prototype sweep** over all 130 remaining drafts (arity read from each callee's
  asm, return types toggled): 3 direct matches and several drops. Run it on any new draft.
- **New tools** in tools/matching/ (set `WDIR` and `WTAG` in the environment):
  lcs_s8.py (checkfile with an LCS word count: use it for big drafts, position counts
  overstate them), sbs_s8.py (LCS-aligned side-by-side, func_ names only), cc_s8.py
  (compile with a mode's flags, dumps in $WDIR/d), dump_s8.py and rtl_s8.py (dumps and a
  one-line-per-insn view), prio_s8.py (global-alloc priorities from -dl/-dg), arity_s8.py
  (argument registers each function reads first), hill_s8.py (dependency-aware
  hill-climb over `/*P*/`..`/*Q*/` lines, checkfile or rr.py scoring).
- **Artificial but plain-C shapes** kept as matches (flagged in their file comments):
  a CSE'd `one = 1` kept alive by `if (one)` (0025c0f8), a dead `i = sema = ...` set that
  keeps a gcse copy (0025add8), an unused `s32 unused[4];` for the frame (00110ce0), a
  noreorder-wrapped sqrt.s inline (001a12f0, as in text_00110000_s6_04.c).
- **Compiler-difference suspects**: 0010a780 and func_00171078 both look like the original
  compiler split a `la` macro after jump2 and let dbr fill the slot (no 2.96 pass does);
  0025b2f0 (save order at equal priority); 001bd090 (a late if-converted store).
- Stale drafts of matched functions were removed from nonmatchings/.

## Session 9: what changed

- **24 matches** (6,876 -> 6,900 / 6,988; 91.0% -> 92.0% of code bytes), by 13 round-1 workers
  (one per list band) and 8 round-2 workers that retried the leftovers with fresh eyes
  (brief: nonmatchings/session9/BRIEF.md; findings per worker: nonmatchings/session9/NOTES.md;
  short version: docs/matching-tips.md "Session 9 tips"). No new build modes or flags.
- **Biggest lever: sibling ports.** About a third of the matches came from rewriting a draft in
  the style of an already-matched function that touches the same globals, callees or packet
  type (plain globals instead of pointer locals, the sibling's array/struct declarations, its
  store order). `grep -rl D_XXXXXXXX src/` before reading dumps.
- **Plain index order for store floods**: 001ff488 matched only after throwing away a
  hill-climbed order and writing the GS vertex flood in index/field order.
- **Callee-prototype sweep** (arity_s8.py on every callee) found three more real prototypes
  (printf with one argument in 00113e28, one-argument func_00118608, `void func_00115d18(void)`).
- **0w only with a hack** (kept in nonmatchings/session9 as near misses, not counted):
  DIntr 0025f338 (`__asm__(".p2align 3")` before the loop label), Tail3Draw 00191248 and
  Tail3XDraw 00197cf8 (an inline reading other locals through a struct cast of the first local:
  undefined behaviour tied to the frame layout), 0010a780 (needs an assembler post-pass).
- **Assembler/compiler differences, now with evidence**: the original assembler moved a `%lo`
  `la` tail into an empty `jal` slot (0010a780; the binary has no `lui;addiu;jal;nop`) but did
  not move the `addu` of `la rd,K(rs)` into a `b` slot (0024c950: `lui;ori;addu;b;nop`, never
  `ori;b;addu`). Stock 2.96 gas does the opposite on both counts and 991111a gas matches the
  second but is worse elsewhere, so the original gas is neither. tools/matching/pp_la_s9.py
  and lcs_pp_s9.py reproduce 0010a780 with a post-pass (a candidate build-mode feature, not
  used by the build). func_00171078 was not a compiler difference: it reads a table through a
  hard-coded address (`((s32 *)0x35BD40)[i]`), so gas fills the slot with the reloc-free tail.
  0025b2f0 (prologue save order) and 001bd090 (a movn if-conversion keeping the earlier store)
  are still suspects.
- **New tools** in tools/matching/: hl_s9.py (dependency-aware hill-climb scored by LCS; cheap,
  ~0.1 s per compile), gentrees_s9.py / ortree_s9.py (enumerate OR-tree shapes of a packed
  constant; gcc reassociates OR chains), pp_la_s9.py + lcs_pp_s9.py (assembler post-pass
  proof for 0010a780). hill_s8.py: its rr form is `FILE MODE ITERS SEED ADDR FUNC`, and its
  validity check counts struct field names as variables (rename a local that shares a field
  name).
- Stale drafts of the 24 matched functions were removed from nonmatchings/.

## Session 10: what changed

- **16 matches** (6,900 -> 6,916 / 6,988; 92.0% -> 93.7% of code bytes) by 14 round-1 workers (one per list band) and 10 round-2 workers that used the new
  levers (brief: nonmatchings/session10/BRIEF.md; findings: nonmatchings/session10/NOTES.md; short
  version: docs/matching-tips.md "Session 10 tips"). Two container losses with 14 workers at once:
  run at most about 5 workers together on this machine.
- **The four hack-only functions are real matches**: DIntr (C shape of its `_sbrk` inline copy),
  Tail3Draw/Tail3XDraw (GNU C nested inline helper; flagged), 0010a780 (CONTEXT_ONLY data
  definition, values zeroed). The session-9 assembler-difference theory was wrong (docs/toolchain.md
  "Session 10 correction"); no post-pass build mode is needed.
- **New tools** in tools/matching/: mchk_s10.py (checkfile for many files after one warm init,
  ~0.2 s each), lchk_s10.py (same, scored by LCS, ~0.04 s), lchkro_s10.py (LCS with rodata at
  $RO), hcf_s10.py and hl2_s10.py (statement hill-climbs; hl2 keeps calls fixed and stores inside
  their call interval), slot_s10.py (delay-slot / gas-symbol sweep), ctxsweep_s10.py (CONTEXT_ONLY
  stub and callee-return sweep). Set WDIR; edit hard-coded paths in hcf/ctxsweep before use.
  checkfile.py itself can take minutes under load: iterate with these.
- Stale drafts of matched functions were removed from nonmatchings/.

## Session 11: what changed

- **46 matches** (6,916 -> 6,962 / 6,988; 93.7% -> 97.2% of code bytes) by about 75 workers, at most
  5 at a time (brief: nonmatchings/session11/BRIEF.md; every finding: nonmatchings/session11/NOTES.md;
  short version: docs/matching-tips.md "Session 11 tips").
- **Flagged matches**: 23 of the 46 rely on source that does nothing and is deleted by the
  compiler. Each file says so in a comment; they are byte-identical, but probably not the original
  source:
  - dead stores: 00152928, 001fe1b8, 00217000, 001c5ee8, 001bd090;
  - dead float tests such as `if ((f32)x < 0.0f) v = 0;`: 00249718, 00110e68, 0010ba98, 001fa8b0,
    001502e8, 00214a68, 00107c48, 001fbcd8, 00135a68, 00199ac8, 0019ab38 (live-length steering), 00107548 (loop test), 00105d88 (integer identical-arm tests), 00102118 (cse2-folded
    `if (x != (s32)t)` tests);
  - a never-true test with the whole body copied into both arms (reorg sees stale flow2 liveness):
    001e0ab0, 001e0d98, 001e10f8;
  - identical if/else arms (as in session 10): 00169f28.
- **00200038** is counted as natural but uses an unusual shape: strip-loop stores through
  `s32 *p = &blk[i].v[11].x;` with negative indices, to get loop.c's blk+416 giv base.
- **001bd090 is a real match**, not a compiler difference (docs/toolchain.md "Session 11 correction").
- **00202678 is a strict function** with union-typed fields, not a nostrict one: re-measure
  "nostrict" drafts in strict mode when the original issues a load above a store it would conflict
  with under nostrict.
- **New tools** in tools/matching/: modesweep_s11.py (every mode x flag combo for a draft),
  lc_s11.py / ld_s11.py (LCS scorers; export RO for rodata), hc_s11.py (statement hill-climb that
  respects loads/stores), var_s11.py (variant runner), togm_s11.py (toggle sweep; temp file is now
  per-pid), cf4_s11.py, slt_s11.py. Worker helper scripts (insertion sweeps, priority dumps,
  side-by-side listings) were left in /tmp and are described in NOTES.md; rewrite as needed.
- **Resource limit**: 5 workers with background hill-climbs and side-by-side builds pushed the
  container to load ~48 with 1.7 GB of 16 GB free, and it was restarted twice (all in-flight work lost;
  `make progress-update` was OOM-killed in objdiff before that). Run at most 3 workers at once, each with
  one compile or hill-climb process in the foreground, and check /proc/loadavg and MemAvailable before
  spawning more. Commit worker results as soon as they report. The trigger was a worker helper
  named `glob.py` in its work directory: every python started there imported it instead of the stdlib
  module, and it launched more checks, so processes multiplied (load ~98). Never name a helper after a
  stdlib module; run helpers with `python3 -I`.
- tools/matching/gclimb_s11.py: token climb that moves each constant's set (`kN = C;`) and its store
  separately, so li order and store order change independently (took 0021e120 from 6 to 3 words).
- tools/matching/jt_s11.py: per-case block sizes ours vs original from both jump tables, the fastest way
  to spot over- or under-merged switch cases (matched the 8.5 KB 001f5fe0; edit the address constants).
- **Tool traps**: variant scripts replace the first match, which can be inside a header comment
  (strip comments first); join one-line `if`s with their bodies before insertion sweeps.
- A container restart mid-session lost no work because every match was pushed as it landed.

## Session 12: what changed

- **Flagged matches count** (user decision, 2026-10-19): byte-identical matches that rely on a dead
  store, a dead float test, identical if/else arms or a never-true test stay in src/ and count as
  matched. Each keeps a comment naming the trick so a later pass can replace it with cleaner source.
- Flagged in session 12: 0019f1f0 (empty `do { } while (0)` sched barriers), 00120cf8 (no-op
  save/restore of a loop divisor that gcse turns into a self-copy).
