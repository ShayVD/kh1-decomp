# Toolchain

Status: **ee-gcc 2.96-ee-001003-1, `-O2 -G0`**, locked as the project compiler by the user in session 1 and **confirmed on the
pinned retail ELF**: all 8 probe functions are byte-identical and objdiff
reports 100% (they now live in `src/anon/session1_probes.c` and are rebuilt by
every `make verify`). The fingerprint survey below was first run on the
fan-patched ELF before the retail one was available.

## Components

| Piece | Source | Notes |
|---|---|---|
| ee-gcc (cc1/cc1plus + driver + ee-as 2.10) | decomp.me compiler releases, fetched by `tools/setup_toolchain.sh`, pinned by SHA-256 in `tools/toolchains.tsv` | 32-bit Linux binaries. Need `libc6:i386` (+ `libstdc++5:i386` for 3.x). |
| ld, objcopy, objdump, nm, as (for objdiff units) | Ubuntu `binutils-mips-linux-gnu` 2.42 | Supports `-march=r5900`. Used with `-EL`. |
| objdiff-cli 3.7.0 | GitHub release, pinned by SHA-256 | Same version as the kh2 project. |

The kh2 project ships a full ee-gcc 3.2-040921 toolchain through git LFS. That
archive cannot be fetched from Claude's sandbox (LFS host blocked), and it is
the wrong compiler era for a 2002 game anyway, so kh1-decomp does not depend
on it.

### Quirk: ee-as 2.10 symbol tables

The assembler bundled with ee-gcc 2.9x writes `.symtab` with local symbols
after global ones (e.g. function-local `static` variables) and a wrong
`sh_info`. Modern GNU ld rejects such objects ("local symbol at index N (>=
sh_info of M)"). `kh1tool.py fix-obj` runs after every compile: it reorders the
table locals-first, remaps relocation symbol indexes and fixes `sh_info`. Code
bytes are untouched.

## Candidate compilers and how to tell them apart

KH1 JP shipped March 2002 and Final Mix December 2002. The earliest ee-gcc 3.2
build (030210-beta2) is from February 2003, so **every 3.2 build is ruled out
by date**. The bundled ee-gcc 2.96 binaries are dated January 2002, which fits.
Metrowerks CodeWarrior for PS2 (mwcps2 3.0, 2002) is also a period-correct
candidate; it is Windows-only and would need wibo/wine.

Fingerprints measured in session 1 by compiling the same C with each
compiler at `-O2 -G0` (sample: `int Call2(int a,int b){int x=ext(a);return ext(b)+x+g;}`,
a float divide, a 5-case switch):

| Fingerprint | ee-gcc 2.9-990721 / 991111x | ee-gcc 2.96-ee-001003-1 | ee-gcc 3.2-0409xx |
|---|---|---|---|
| Callee-saved register slots | 16 bytes apart (`sd $16,0` / `sd $17,16` / `sd $31,32`, frame 48) | 8 bytes apart (`0/8/16`, frame 32) | 8 bytes apart, different save order (`$16,$31,$17`) |
| `div.s` | no padding | `nop; nop` before `div.s` (R5900 erratum workaround) | `nop; nop` before `div.s` |
| Short loops | 991111: `nop`s padded into loops shorter than 6 instructions; 990721: none | `nop`s padded into short loops | none |
| Jump tables | `lui/addiu/addu/lw` | `lw $3,$Lnn($2)` macro (assembler expands to `lui $at` / `addu` / `lw`) | `lui/addiu/addu/lw`, temps in `$13-$15` |
| Temporaries | `$2`, `$3`, `$4` | `$2`, `$3`, `$4` | `$13`, `$14`, `$15` (t5-t7) first |
| Function alignment | 8 bytes | 8 bytes | 8 bytes |
| Markers in unstripped objects | `gcc2_compiled.` label | `gcc2_compiled.` label | none |
| C++ mangling | gcc2 (`init__5SOUND`) | gcc2 | Itanium (`_ZN5SOUND4initEv`) |

Plan for step 3, once the ELF is here:

1. Look for version strings (`strings -a` for `GCC:`, `ee-gcc`, `2.96`,
   `001003`, `CodeWarrior`, `Metrowerks`, SCE library banners such as
   `PsIIlibsd`/`libpad` version strings) and a `.comment` section.
2. Sample prologues and short loops across the ELF and score them against the
   table above.
3. Pick 3-5 small functions (getters, memset-like loops, a leaf with a float
   divide), write C for them, and require a byte-identical build with each
   candidate. The candidate that matches all of them, with the simplest flags,
   becomes the pinned compiler.

## Mangling

`tools/mangle_gcc2.py` turns C++ signatures in `functions.tsv` into gcc 2.9x
mangled names. Verified against ee-gcc 2.96 output by
`tools/test_mangle_gcc2.py` (14 cases: methods, const methods, nested classes,
ctors/dtors, `T`/`N` back-references). Operators and templates must be
written already mangled.

## Confirmed (session 1)

Fingerprints were measured on the fan-patched ELF (SHA-256 `53eca29e…`), then
the probes were re-run on the retail ELF (SHA-256 `1993a4da…`) with the same
8/8 result.

| Item | Value | Evidence |
|---|---|---|
| Compiler | ee-gcc 2.96-ee-001003-1 | 8/8 probe functions byte-identical, objdiff 100% (below). Same probes: ee-gcc 2.9-991111a 5/8, ee-gcc 3.2-040921 1/8. |
| Fingerprints | all point to 2.96 | 684/684 `div.s` preceded by `nop; nop` (rules out 2.9-99xxxx); callee-saved slots 8 bytes apart in 292/296 frames (rules out 2.9); 384 of 610 short loops padded with `nop` (rules out 3.2); temporaries mostly `$v1`, not `$t5-$t7` (rules out 3.2). |
| SCE SDK | 2.5.0 | `PsIIlibkernl2500`, `PsIIlibgraph2500`, `PsIIlibpad2 2500`, … banners. SDK 2.5 shipped ee-gcc 2.96. |
| `.comment` / `GCC:` strings | none | Stripped. No symbol table either. |
| Flags (game code) | `-O2 -G0` | All probes. Small data is not used (globals are addressed with `lui`/offset, never `$gp`). |
| Flags (SCE libraries) | `-O2 -G0`; SCE code: ee-gcc 2.9-991111a; newlib: 2.96 with `-fno-builtin` and no_fill | session 5, docs/sdk.md |
| Language | C, probably | Assert-style strings name `.c` files (`ttlib/ui.c`, `ttlib/ui_gauge.c`, `src/decode.c`, `src/sa_task.c`). No gcc2-mangled names found in strings. C++ not ruled out for other modules. |
| Sibling calls | yes | Tail calls as `ld ra` … `j func` occur; 2.96 at -O2 emits them. |

Probe functions (source in `src/anon/session1_probes.c`): `0x0010ef70`
struct field and bit update, `0x00111f70` two global stores, `0x00137418`
float reciprocal into a struct, `0x001882f8` int/float maths, `0x0018ad70`
four stores, `0x001d5f80` counter + array append, `0x0023d1e0` float divide by
constant, `0x002466e8` halve and clamp. Addresses are identical in the retail ELF.

### Quirk: float literals

ee-gcc 2.96 does not always round decimal float literals to the nearest
float. `0x0023d1e0` divides by `0x3F490FD9` (≈0.785398, a truncated π/4);
writing `0.785398f` or the correctly-rounded `0.78539806f` gives different
bits, while `0.7853981f` gives the original.
When a float constant mismatches by one ULP, try neighbouring literals.

## Codegen patterns learned in session 3 (ee-gcc 2.96 -O2 -G0)

Each of these was the cause of many near misses; tools/permute.py now tries
them automatically (docs/workflow.md).

- **`volatile` globals**: `lui; addiu; lw/sw 0(reg)` (full address, then
  offset 0) instead of `lui; lw %lo(sym)(reg)`, and the store is not moved.
  Many KH1 globals are declared `volatile`.
- **Independent stores are emitted with the last one first**: source
  `a=…; b=…; c=…;` comes out as `c, a, b`. To match an asm order, rotate the
  run left by one.
- **`if (x) return 1; return 0;`** keeps an `sltu v0,zero,v0`;
  `return x != 0;` is folded away when `x` is already 0/1 (`x & 1`).
- **Arguments 5-8** go in registers 8-11 (`a4`-`a7` in EABI names,
  `t0`-`t3` in objdump's o32 names). Float arguments use `f12`-`f19`
  independently of the integer ones, so int/float order in a prototype does
  not change the code.

## Codegen patterns learned in session 4

- **Arrays vs pointer arithmetic.** `D[3] = x` on `extern s32 D[]` keeps one
  `lui/addiu` base and stores at `0/4/8/12(base)`; the same stores written as
  `*(s32 *)((char *)&D + 12)` on a scalar `D` get a base of `D+12` and
  negative offsets. Globals used like arrays should be declared as arrays.
- **Wider locals change the load.** An `s8` global decremented through an
  `int` local loads with `lb`; directly (`D -= 1`) with `lbu`. A `u32` field
  kept in a `u64` local loads with `lwu`; a `u8` kept in a `u64` and shifted
  uses `dsrl`. Casting in place (`(u64) *p >> 4`) does not reproduce this.
- **64-bit constants** (`li v1,0x8000; dsll32 v1,v1,N`) come from 64-bit
  constant expressions (`(s64) 0x8000 << 0x22`, i.e. 1ULL << 49).
- **Stack locals** sit at `sp+0` up to the lowest callee-saved slot; there
  is no outgoing-argument area (EABI: 8 integer + 8 float argument
  registers).

## Session 5: SDK flags and no_fill

The SCE libraries (libkernl, libgraph, libpad2...) were built with ee-gcc
2.9-991111 (48 matches with `ee-gcc2.9-991111a` that 2.96 could not
produce). newlib's libc and libm and libgcc2's `_*.c` objects match 2.96
`-O2 -G0 -fno-builtin` once **no_fill** is applied: their assembler left
every branch and call delay slot it did not get from the compiler as a
`nop` (gcc 2.96's own `.set noreorder` blocks are untouched).
`no_fill()` in tools/kh1tool.py rewrites the compiler's assembly that way; kh1.toml
turns it on per path (`no_fill = true` in a `[[toolchain.override]]`,
longest prefix wins). fp-bit (`dp-bit.c`) fills normally.

ee-gcc 2.96 calls double-precision helpers by their GOFAST names
(`dpadd`, `dpmul`...); the retail build linked libgcc's `__adddf3` etc.
`LIBCALL_ALIASES` in kh1tool.py resolves each GOFAST name to the original
routine (same calling convention).

## Session 6: more build modes

| Directory | Flags | Where |
|---|---|---|
| src/hand/nogcse | `-fno-gcse` | ~0x10c720-0x10ed20, 0x142e30-0x14b550, 0x2114f0-0x214f50 |
| src/hand/nostrict_nogcse | `-fno-strict-aliasing -fno-gcse` | 0x156e88, 0x1cf348, 0x1f9e48-0x1fbcd8, 0x24f098 |
| src/hand/n32 (+ _nogcse, _nostrict) | ccflags `-mabi=n32 -DKH1_N32` (C -> asm only) | 0x20dd38-0x2173xx |
| src/sdk/gcc991111_as296 | 991111a cc1, 2.96 driver's gas | some libkernl (0x259380, 0x2594a0) |

- **gcse sign**: the original repeats a load, a global base `lui/addiu`, or
  a constant (0.0f) across branches that gcse would merge.
- **n32 sign**: the original keeps `lui; addiu; addu` for symbol+register
  where 2.96 o32 folds to `lw sym(reg)`. Under n32 `long` is 32-bit, so
  common.h makes u64/s64 `long long` when `KH1_N32` is set. n32 saves only
  even FP registers, so a function saving `$f21` is not n32 (0x1f9xxx).
  0x212cc0, 0x2134c8 and 0x217000 mix folded offset-0 loads with split
  addresses for symbol+offset; no flag reproduces both (tried
  -msplit-addresses, o64, 64, long64, half-pic, embedded-data, older
  ee-gcc): probably a patched compiler.
- **as296**: 991111a's gas leaves `jr` delay slots empty; 2.96's fills them.
  All existing 991111/libkernl files also match with 2.96 gas, so the
  group could be switched wholesale (not done).
- func_001c1718 matches only with `-fno-sched-interblock` (sched1 does
  interblock motion only in functions with <= 10 basic blocks); no mode was
  added, the source probably has one more block.
- More region facts: 0x11f000-0x127xxx nostrict; 0x13bb20-0x13c2f0 nofill;
  0x152c28-0x159c10 strict, 0x15ad08 and 0x15ea98-0x15f128 nostrict;
  0x17b000-0x183b20 nostrict; 0x186000-0x19a000 nostrict except
  0x18e348-0x18e588 nostrict_nofill; 0x1a2d40, 0x1a5740 nostrict;
  nofill 0x1d5b58-0x1e0xxx; 0x1fade0-0x1fcdc8 nostrict; 0x1ff488-0x2040f8
  nostrict; 0x225ea8 nostrict; 0x22f000-0x234910 strict; 0x238768-0x2412xx
  nostrict; 0x249xxx-0x24bxxx strict; 0x24d618 nofill.

## Session 7: extra flags, other compilers, the n32 question

**Single extra flags.** `tools/matching/flagsweep.py` retries a draft under each
build mode with one of ~35 gcc 2.96 flags added (`KH1_EXTRA_CCFLAGS`, honoured by
tools/checkfile.py). Over all 203 drafts it found 4 matches, and workers found
two more; each became a mode:

| Directory | Flags | Functions |
|---|---|---|
| src/hand/nosi | `-fno-sched-interblock` | func_001c1718 (`-fno-sched-spec` / `-fno-schedule-insns` also work) |
| src/hand/nogcse_nosi | `-fno-gcse -fno-sched-interblock` | func_0010ec08 |
| src/hand/nogcse_nosib | `-fno-gcse -fno-optimize-sibling-calls` | func_0010cf38 (no tail call; the flag only changes return-path layout) |
| src/hand/faddr | `-fforce-addr` | func_00231ea0 |
| src/hand/nostrict_norcse | `-fno-strict-aliasing -fno-rerun-cse-after-loop` | func_0012d468 |
| src/hand/norlo | `-fno-rerun-loop-opt` | func_001dd5c0 |
| src/hand/fmam | `-fmove-all-movables` | func_001eb7b0 |
| src/hand/nostrict_nosib | `-fno-strict-aliasing -fno-optimize-sibling-calls` | func_00170170 |

These are the simplest flags that reproduce the bytes, not proven makefile flags.
sched1 interblock motion only happens in functions with <= 10 basic blocks, and a
source-level alternative exists (duplicate a tail in both branches: func_001d0380
matched that way without a flag), so a flag mode may hide a source shape.
Flags gcc 2.96 rejects: -fno-crossjumping, -fno-if-conversion, -fno-loop-optimize,
-fno-merge-constants, -mbranch-likely, -mno-mmi.

**Other period compilers.** decomp.me also ships ee-gcc 2.9-991111 (plain),
991111b-r4 (Windows), 991111-01-dtls13010 and the SN Systems builds 2.95.2-273a,
2.95.2-274, 2.95.3-107/114/136 (Windows; they run under wibo 0.7.0,
github.com/decompals/wibo). None reproduces the six functions that match in
src/hand/n32 under 2.96 `-mabi=n32` (all 40-70 words off, n32 flags or not). Not
wired into setup_toolchain.sh: they matched nothing.

**The n32 "mixed addressing" question is answered: it is source shape, not a
compiler.** In plain o32 src/hand, a nested sub-struct with a variable index,
`D_003E3D70[k].s.d` (a struct at +0x40), gives `la D; addiu 64; addu; lw 12()`,
because the element address is CSE'd between two field loads; a single flat
access always folds into `lw sym+off(reg)`. func_002134c8 matches in plain hand;
func_00212cc0 is 7 words off (only an s-register choice) and func_00217000 56.

**func_00171078** (`lui; addu; jr; lw %lo` with the macro load's last word in the
jr slot) is the only such case in the binary. Assembling 2.96's output with every
installed gas (2.96, 990721, 991111, 991111a, 991111b, 991111-01, dtls13010, SN
2.95.2) leaves the slot empty; -msplit-addresses and n32 do not split the load.
Unresolved.

## Session 9: the original assembler is not stock 2.96 gas (corrected in session 10)

Two delay-slot facts from the binary (docs/workflow.md "Session 9"): the original assembler
filled an empty `jal` slot with the `addiu %lo` tail of an `la` macro (0010a780; no
`lui;addiu;jal;nop` anywhere in the ELF), and did not fill a `b` slot with the `addu` of
`la rd,K(rs)` (0024c950). Stock 2.96 gas fills slots only with relocation-free macro tails
(so `((T *)0xADDR)[i]` gets its `lw` in the `jr` slot: func_00171078), and 991111a/-01 gas
differ elsewhere. No installed assembler reproduces both; tools/matching/pp_la_s9.py shows
a post-pass that does the first. Not adopted as a build mode yet: only one function needs it.

**Session 10 correction: it is stock 2.96 gas.** Both facts have a plain explanation, so no
post-pass build mode is needed (pp_la_s9.py is obsolete):
- ee-as 2.96 fills a reorder-mode jal/jr/b slot with the last word of an `la sym`/`lw sym`
  macro only when `sym` is already known at that point in the file: defined earlier (even weak
  in `.ctx`), `.comm` before use, `.extern sym,size`, or absolute. An undefined extern of unknown
  size (it might be small data), a later definition or a trailing `.comm` leaves the slot empty.
  So 0010a780's original file defined D_002B67F0 above the function; the repo does it with a
  zero-initialised CONTEXT_ONLY definition (src/hand/nostrict/text_00100000_s10_w1.c).
- Stock ee-as given `-g` (the driver passes it for any `-g` compile) sets mips_optimize=1 and
  fills no reorder-mode slot at all: the same output as kh1tool's `no_fill`, and as 991111a gas
  on these drafts. So 0024c950 is simply a nofill function, and "nofill" translation units were
  probably built with `-g`. 0012e1b0, 001c53c8 and 0024c950 turned out to be nofill functions
  (two of them matched in nofill modes).
- 0025b2f0's "prologue save order" (991111) was a type (a Hook struct), not a compiler difference.
  001bd090 is the last compiler-difference suspect (a post-combine if-conversion that keeps an
  earlier store).

### Session 11 correction

- 001bd090 is a real match (src/hand/text_001b0000_s11_w17.c), not a compiler difference. The
  late if-conversion that keeps the earlier store is the ce pass (after life1/combine) working on
  spilled scalar locals; the session-10 drafts used stack structs, which the ce pass leaves alone.
  A dead set of a variable that is live elsewhere also delays if-conversion to the ce pass.
  No compiler-difference suspects remain: every unmatched function is a source-shape problem.
