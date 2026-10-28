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
