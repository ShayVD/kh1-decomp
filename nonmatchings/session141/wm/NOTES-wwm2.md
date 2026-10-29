# Session 141, worker wwm2: wm.x at 0x00f50000 and above (no gb twin)

All matches confirmed by `make ovl OVL=wm` (byte-identical, 755 functions at the end).

## Matched (8)

| Function | Notes |
|---|---|
| func_00f7da20 | `.nosib`: the final `func_001f31a8(&desc, 0)` is a `jal`, not a tail call |
| func_00f7bfb8 | 128-byte clear: `for (i = 0; i < 128; i++)`, gcc reverses it (li 127 / bgez, short-loop nops) |
| func_00f787b0 | v0/v1 swap fixed by a `do { if ... else ... } while (0)` around the sign select (permuter) |
| func_00f78690 | parameter-list reader: `if (func_0024ba28(...) < 0) PlatBreak();` (include platform/thread.h) |
| func_00f781c0 | `if (x) f(2); else f(3);` (crossjumped into one jal), `b = D[2]; b &= 0x2000;` for the v1 temp, store order of a chained pair |
| func_00f7b9a0 | DMA end tag: `union { kh1_u128 q; u32 w[4]; }` so the `sq` zero comes before the `sw` (plain u32 cast reorders it; `.nostrict` also works) |
| func_00f7ef20 | GIF packet: one inline helper per qword (put / rgba / xyz) gives the original's separate `addiu rN,a0,16*k` address registers; colour bytes read once into locals |
| func_00f7c2e8 | 12-argument callee; the two per-index values loaded into locals in declaration order `b` then `c` |

(func_00f781c0 was also matched on the coordinator's branch.)

## Near misses (drafts in this directory, first line says what is left)

| Function | Left |
|---|---|
| func_00f7cb60 | 3 words: reorg fills the &2 arm's `b` slot from before instead of stealing the shared `p[0] = 0` |
| func_00f5c1c8 | 13 words, register allocation in the first loop only (second loop fixed by a CONTEXT_ONLY func_00f5ae10) |
| func_00f7f628 | score 21: debug value editor; structure right, `move s8,a0` placement and a bgezl |
| func_00f5dfd8 | score 38: func_00f65480 family (also f5e368, f5e540, f67530, f676b8): base pointer copied into a fresh pseudo |
| func_00f7c078 | score 45: recursive path search, branch-likely choice in the x/y test |
| func_00f7bde0 | score 66: camera matrices, FP register numbering / load order |
| func_00f7f438 | score 71: GIF qword stores keep strict order in the original |
| func_00f630c0 | score 81: second loop entered at its test, invariant not hoisted |
| func_00f667b8 | score 93: DMA tag + vertex packet scheduling |

Attempted without a useful draft: func_00f78bc0 (thread loop; the `func(4)` / `func(1)` calls share one jal, the
fade counter is re-addressed each iteration), func_00f67530 / func_00f676b8 (src loop not strength-reduced in the original).

Skipped: func_00f77ce0 / f77d50 / f77dc0 (switch cases of func_00f77af0, coordinator), func_00f55ad8 and
func_00f50968 (coordinator), func_00f528f8 / f799e0 and the 200+ insn functions (not reached).

## Tips

- Inline helpers explain "a separate base register per struct": stores like `addiu v1,a0,16; sd x,0(v1); sd y,8(v1)`
  for every qword come from `static inline void put(Qw *q, u64 a, u64 b)` (the inlined parameter is a new pseudo, so
  the offset is not folded). Values read once (`lbu` before the first use, reused later) were locals in the source.
- `sq` of a zero followed by a `sw` of the tag word into the same qword: write both through one union
  (`kh1_u128 q; u32 w[4]`); with a cast, strict aliasing moves the `sw` above the `sq`.
- Two `li a0,K` arms sharing one `jal` were `if (c) f(2); else f(3);` (crossjumping), as the coordinator noted.
- A range check emitted as two compares (`slti 27` then `slti 21`) is nested ifs (`if (x < 27) { if (x >= 21 ...` );
  `x < 27 && x >= 21` becomes one `sltiu` range test.
- A double constant loaded with `lui at / ld a1,%lo(at)` is a literal (`len * 0.01 * 0.1f`), not an extern; while the
  code does not match yet, hand.py refuses to place literal rodata, so diff with `extern double` first.
- tools/autodecomp.py disasm: objdump needs `-z` (applied here too), or diffs past nop runs are shifted.

## Round 2

Matched: func_00f528f8 (16-aligned Col struct, stores r,g,b), func_00f56ce0 (v[2] before v[0]), func_00f574e8 (twin
of f56ce0 with other tables), func_00f5c4e0, func_00f78ff8 (the two global copies swapped), func_00f7cd68 (exit calls
inside the loop's break block keep a constant load below the call), func_00f7da90 (f7bde0 CONTEXT_ONLY stub for bnezl;
zero stores as `FA78 = FA7C = FA68 = FA6C = F6D4 = 0; F6E8 = 0;`: chained assignments fix lui register order).

Near misses saved here (first line gives score and what was tried): func_00f530f8 (6), func_00f7ecd8 (17),
func_00f632e8 (35), func_00f79868 (37), func_00f78978 (45), func_00f7c880 (64), func_00f78d50 (71),
func_00f799e0 (115), func_00f74440 (246, structure right).

Skipped: func_00f69aa8 (gb twin func_00f429b0 unmatched), func_00f69df0 and func_00f5f250 (lead matched them).

More tips:
- A CONTEXT_ONLY empty stub of a callee (`CONTEXT_ONLY void f(void) {}`) can turn bnez into bnezl after its calls.
- `t = w*h; t /= 128; size = t;` keeps the divide-adjust in place (blocks CSE); `(x - w/2 + 1792) << 4` keeps gcc from
  distributing the constant, where `* 16` does not.
- `if (st == 0) continue; switch (st) {...}` gives a linear compare chain where a plain switch gives a binary tree.
- `k = x + 1; if (x == 0xFF) k = 0;` gives movz; the ternary gives branches.
- f78d50 / f74440: the original leaves the delay slots of soft-double libcalls (__cmpdf2, __subdf3, __truncdfsf2) empty
  while __extendsfdf2 slots are filled; no flag mode reproduces this yet.
- `python3 tools/ovl/twins.py` writes ports into other overlays too (it wrote two gb files here); check git status after running it.
- Chained assignments (`a = b = c = 0;`) and how the chain is split change the lui register order of zero stores to globals; brute-force chain orders and splits when only those registers differ.

## Round 3 (small overlays)

Matched: xs_dh_break func_00f20128 (the session 136 draft as is, in nostrict mode: with strict aliasing the u32 vertex
stores do not depend on the u64 GIF-tag sd, so it is scheduled later), xl_limit func_00f20e10 (the >= 60 block sets
kind = 5 itself instead of before the inner if, and the < 40 block is ordered kind, h, n, s; any order that makes the
two blocks identical gets them crossjumped).

Tips:
- Run every old draft through all flag modes (/tmp/claude-0/s141/modes.sh) before hand work; f20128 was one rename away.
- When two blocks end up with the same instructions in a different order, look for an assignment that reorg moved into
  a delay slot from the branch target and brute-force the statement orders of both blocks together.

Still open (headers updated): xs_mushu func_00f20550 (2 words), xs_genie func_00f218f8 (2 words), xs_tink
func_00f20818 (35). Not reached: xs_dh_break func_00f20288 / func_00f20820 (104+ / 142 words), xl_limit func_00f225b0
(60), xs_dumbo func_00f20570 / func_00f222f8 and xs_genie func_00f22078 (no draft in nonmatchings; scratch drafts in
/tmp/claude-0/s141/db and gn2 score 49 and 101+).

## Round 4 (wm upper half)

Matched: func_00f67928 (string builder: `n /= 2; if (r >= n)` keeps n/2 in n's register; `if (r >= n / 2)` uses a new one).
All old upper-half drafts went through every flag mode: none matches; func_00f78d50 improves to score 57 in nofill.
Near misses saved: func_00f67c60 (46), func_00f62440 (98), func_00f79700 (187, same code as func_00f69278).
Tried without progress: func_00f7cb60 (tail-arm variants all worse than the saved 3-word draft).
