# Decompiling: tools and workflow (session 2)

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
