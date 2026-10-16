# Toolchain

Status: **ee-gcc 2.96-ee-001003-1, `-O2 -G0`**, locked as the project compiler by the user in session 1. Identified in session 1 on the
English fan-patched `SLPS_251.98` (see "Confirmed" below). It still has to be
re-checked against the unpatched retail ELF once that is pinned; the patch
replaces the ELF, but the probe functions sit in code the translation is
unlikely to touch.

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

## Confirmed (session 1, on the patched ELF)

Input: `SLPS_251.98` from the crazycatz00 KH1FM English patcher (July 2025),
SHA-256 `53eca29e315f43f6cb63960f32d1737b2ea3f95e3954d6b7027f4054ca64954d`.
**Not the target**: the patcher swaps in a modified ELF. Used only because
the retail ELF was not available yet.

| Item | Value | Evidence |
|---|---|---|
| Compiler | ee-gcc 2.96-ee-001003-1 | 8/8 probe functions byte-identical, objdiff 100% (below). Same probes: ee-gcc 2.9-991111a 5/8, ee-gcc 3.2-040921 1/8. |
| Fingerprints | all point to 2.96 | 684/684 `div.s` preceded by `nop; nop` (rules out 2.9-99xxxx); callee-saved slots 8 bytes apart in 292/296 frames (rules out 2.9); 384 of 610 short loops padded with `nop` (rules out 3.2); temporaries mostly `$v1`, not `$t5-$t7` (rules out 3.2). |
| SCE SDK | 2.5.0 | `PsIIlibkernl2500`, `PsIIlibgraph2500`, `PsIIlibpad2 2500`, … banners. SDK 2.5 shipped ee-gcc 2.96. |
| `.comment` / `GCC:` strings | none | Stripped. No symbol table either. |
| Flags (game code) | `-O2 -G0` | All probes. Small data is not used (globals are addressed with `lui`/offset, never `$gp`). |
| Flags (SCE libraries) | not checked yet | |
| Language | C, probably | Assert-style strings name `.c` files (`ttlib/ui.c`, `ttlib/ui_gauge.c`, `src/decode.c`, `src/sa_task.c`). No gcc2-mangled names found in strings. C++ not ruled out for other modules. |
| Sibling calls | yes | Tail calls as `ld ra` … `j func` occur; 2.96 at -O2 emits them. |

Probe functions (source in `tests/toolchain_probe/probe.c`): `0x0010ef70`
struct field and bit update, `0x00111f70` two global stores, `0x00137418`
float reciprocal into a struct, `0x001882f8` int/float maths, `0x0018ad70`
four stores, `0x001d5f80` counter + array append, `0x0023d1e0` float divide by
constant, `0x002466e8` halve and clamp. Addresses are from the patched ELF.

### Quirk: float literals

ee-gcc 2.96 does not always round decimal float literals to the nearest
float. `0x0023d1e0` divides by `0x3F490FD9` (≈0.785398, a truncated π/4);
writing `0.785398f` or the correctly-rounded `0.78539806f` gives different
bits, while `0.7853981f` gives the original.
When a float constant mismatches by one ULP, try neighbouring literals.
