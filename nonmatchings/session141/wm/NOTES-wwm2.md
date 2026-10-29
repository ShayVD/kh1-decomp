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

## Round 5 (wm upper half, continued)

Matched: func_00f681f8 (matrix to Euler angles; float constants spelled from the exact bit patterns, e.g. 1.5707963f,
3.141592503f), func_00f601f0 (mode loop; reuse `p` as the u32 buffer pointer instead of a second local),
func_00f62c98 (Hermite spline; `n = sp->n` local, and an unused `f32 v[8];` declared before m gives the 32 extra frame
bytes), func_00f65d18 (texture upload: `e = tx->ent; e += idx;` instead of `&tx->ent[idx]`, `sz = e->size;` temp with
tbp updated before data, and the copy loop wrapped in `if (e->count != 0)` for the doubled beqz), func_00f65f28 (its immediate-load sibling; found by a
10-minute -j1 permuter run: the first shift loop body is `do { i <<= 1; } while (0);`, which keeps the original's
`move v1,a3` copy of e->w for the loop compare).

Tips:
- GS packet writers: a macro that reassigns one `Qw *q = &p[i]` per qword makes the original's single base register
  (addiu t7,a0,N per qword) and removes the spill frame; separate inline params do not.
- A loop the original does not optimize (address recomputed in the loop, `b` into a shared `jal`) is a goto loop; two
  identical "call; update; test" tails are crossjumped (func_00f78bc0).
- Reusing one counter variable for several loops gives the shared saved register; `n /= 2` in place keeps the register.

- A `do { ... } while (0);` around a loop body changes the loop notes enough to keep an extra register copy; worth a try
  when the only diff is a `move` before a loop.

Near misses saved (headers say what was tried): func_00f78bc0 (59), func_00f676b8 (60, same code as
func_00f67530: the uv copy loop is not reversed in the original and only the dst giv is reduced), func_00f6dfd8 (77),
func_00f79700 (84, was 187; same code as func_00f69278), func_00f60cf0 (138).
func_00f7cb60: one 20-minute -j1 permuter run, no improvement (best non-hack candidate worse than the 3-word draft;
the only lower-scoring output used a volatile index).

## Round 6 (wm upper half, remaining)

No matches this round (about 45 minutes).
- func_00f693e0 is func_00f799e0 without the last stack argument (4) to its draw call, so one fix gives both. A
  15-minute -j1 permuter run found `unsigned long nv; if ((nv = bpp) == 8)`, which stops gcc from reusing cw's
  constant 8 for the compare and fixes the whole bpp branch block. Both near misses are updated: f693e0 111 -> 89,
  f799e0 115 -> 93. Left: y/h are swapped between s3/s4, img lands in t5 instead of t1, and the stores of the vertex
  arrays come in a different order.
- func_00f7c510: complete draft at score 86, saved. The original copies x and y into new registers in each arm of the
  flag `if`, which looks like inline or crossjump structure. Per-arm copies and an inline helper per arm did not
  reproduce it.
- func_00f69fd0: a long run of global initializer stores whose order is set by the scheduler. Not attempted.
- Not reached: f64d48, f639c0, f63d18, f70418, f69aa8.

## Round 7 (wm high half, no near-miss files yet)

Matched: func_00f65bb8, which computes TEX0 only, without uploading. It is the f65f28 code with `cbp = tb + cidx` (or
`* 4`) in the 4/8 cases. The `do { i <<= 1; } while (0);` first shift loop from f65f28 carried over unchanged, so
these texture siblings share one source shape.

Near misses saved:
- func_00f66b38 (15 words, registers only).
- func_00f78458 (score 13; one constant's load placement is left).
- func_00f66bd0 (score 102).

Not reached: f606a0, f60af0, f663a8, f651d0, f64d48, f639c0, f63d18, f70418, f69aa8.

## Round 8

Matched: func_00f606a0, a sibling of func_00f60898 that skips the flag and index checks and always uses
func_001ba060(&D_0108DE90, idx - 71).
- Store order brute-forced, plus a `v[1], v[0], v[2]` vector order.
- The last fix came from a permuter hint: write `xf.pos[3] = 1.0f;` both as the first statement and again at the
  end. Dead-store elimination keeps the last copy, and the scheduler hoists the last independent 1.0f store to the
  top. So when one constant store sits at the wrong end of a run of stores, duplicating it at the other end is
  worth a try.

Near misses saved:
- func_00f60af0 (94): bitfields.
- func_00f663a8 (73, nostrict): VU memory writes. The original reloads every global after each VU store.

Not reached: f651d0 (a large matrix loop; looked at only), f64d48, f639c0, f63d18, f70418, f69aa8.

## Round 9

No matches.
- func_00f651d0: draft saved at score 155. It is a skinned-bone matrix build. The original saves t2..t5 with sq/lq
  around the per-mesh call (caller-save) and keeps the bone pointer on the stack. An unused `f32 u[4][4]`
  reproduces most of the frame.
- func_00f78458: no gain. I tried every position for the -8 store and duplicate stores; it stays at score 13.
- f63d18 and f70418: large packet and menu builders, looked at only. f64d48, f639c0 and f69aa8 not reached.

## Round 10

None of f64d48, f639c0, f69aa8 or f63d18 has a gb twin draft (twins f3dc50, f3c8c8, f429b0, f3cc20).

Matched: func_00f64d48, an animation curve evaluator (pre/post infinity modes, key scan, lerp/Hermite).
- Two switches have a `case 0:` that shares the default (this gives the slti <2 test). Put the post-infinity and
  interpolation switches' `case 0: default:` first, so their return blocks sit right after the dispatch.
- Keep the key times in an f32 `ts` that the cycle loops compare against. Without it, a mov.s copy appears.
- Final step came from the permuter: in pre-infinity linear mode, write `kp = k; k2 = kp + 1; k1 = k2;` with a
  separate `CKey *k2` declared after `dt`. That gives the `move a1,a2` copy and the right a2/a3/t0 registers.

Near misses saved:
- func_00f639c0 (score 5): menu text builder, same type table as f67928. Permuter: `r = 100 + i * 24;` as the
  y argument. An s64 temp for the second qword's y part gets 4 words (score 7). Left: one addiu's position and
  a move/lui swap.
- func_00f69aa8 (score 43, registers only): picture viewer loop. Use `nb++; nb &= 1;`, because (nb+1)&1 becomes
  xori. Load w/h/bpp before the func_00f471a0 call. Not permuted yet: worth a -j1 run.

f63d18 not reached.

## Round 11

Matched: func_00f70418, a menu draw loop (gb twin f49320).
- Index `D_0108F2C8[i]` directly inside the loop, not through a pointer set up earlier. The pointer form lets gcse
  keep the 0x109 high part in a saved register and spills `n`. With the index, loop.c builds the giv's start value
  fresh.
- Use one variable for the 5/6 slot count and the 9..0 loop counter (both s5).
- func_001f8f30 is called with no argument.

Near misses saved:
- func_00f68ec0.nostrict (score 9): ported from the gb f41dc8 draft (15 words), then fixed the n*16+p operand order and
  hoisted the C00A constant into a local `u64 c`. What is left is scheduling in the flag branch.
- func_00f63d18 (score 102): same family as f639c0. The packet qword is strength-reduced as a giv in my build but not
  in the original.
- func_00f69fd0 (score 184): an init function with a long run of global stores; not converging.

f71748 (1040 bytes; reset loops, a link-building loop over 96-byte entries, then layout) was only looked at.

## Round 12

No matches.
- func_00f63d18: the goto loop did not help (score 145, against 102 for the for loop). The loop has to stay a real
  loop, because the original hoists the 1, 5 and 0x8000<<17 constants. The problem is that gcc turns the
  (s64)((y + 1920) << 4) << 16 qword into a 64-bit loop induction variable (daddu by 0x1c00000). The original
  recomputes it each pass. Tried s32 temps, s64 temps, an explicit y, and SCE_GS_SET_XYZ-style u64 casts. The
  saved draft is unchanged.
- func_00f71748: near miss saved at score 62 (see the header). A -j1 permuter run moved the second panel block's `w = ...`
  line above `x = ...` (106 to 62).
- Not reached: f792c8, f77648, f74440, f646c0 (f646c0 is a large texture upload / GIF packet builder; looked at
  only).

## Round 13

Matched:
- func_00f792c8 (nostrict): a sibling of f68ec0 (gb f41dc8) with a vertex count `cnt` and prim types for 3 versus N
  vertices. Built from the f68ec0 template:
  - `do {} while (0);` at the top of the flag branch.
  - The vertex loop is written as `i = 0; if (cnt > 0) { u32 ff = 0xFFFFFF; o = (u32 *)(n * 16 + (s32)p); do {...}
    while (++i < cnt); }`. That puts o's setup after the guard, and the ff local fixes the `lui t0,0xff` position.
  - The store order was brute-forced: s/z, t/z, 0, 1/z, then x, y, 0xFFFFFF, 0.
- func_00f68ec0 (nostrict): the same trick finishes the 3-word twin draft. Write `i = 0; ff = 0xFFFFFF;
  o = (u32 *)(n * 16 + (s32)p);` before the colour loads, then `for (; i < 4; i++)`, and store `o[2] = ff`. The gb
  twin f41dc8 should take the same change.

Near miss saved: func_00f77648 (score 168, first draft; see the header).
f74440 not reached.
f71748: a 30-minute -j1 permuter run from the score-62 draft. Its best output only swaps two statements in the first
panel block, which hand.py scores at 66 (worse), so the saved draft is kept.

## Round 14

No matches. The worktree was rebased onto 4384627, and the build is byte-identical.
- f792c8 gb twin: none exists. gb's asm.json has no 0x9009/0x9029 constant, and gb has no function of size 1080, so
  there is nothing to port by hand.
- func_00f74440: score 4 (saved; the draft is meant for nofill mode, as func_00f74440.nofill.c). What got it there:
  - nofill mode: the original leaves the soft-float libcall delay slots empty, but the ext call keeps sub.s in its
    slot.
  - An inline `DABS(double)` with a local `double z = 0.0`, called as `m = DABS(e[8] - e[4])` and
    `if (m < DABS(d = e[9] - e[5])) { if (d < 0.0) d = 0.0 - d; m = d; }`.
  - `do {} while (0);` after the three scale stores keeps them ahead of the MulMatrix arg moves.
  Left: in the two inner abs blocks, the a0/a1 moves before __cmpdf2 are swapped. The permuter cannot parse OvlMtx
  (an aligned typedef), so it was not run.
- func_00f6edd8: score 186 (saved, see the header). n spills where the original spills p. A 15-minute permuter run
  found nothing useful.
- func_00f72a70: score 139 (saved, see the header). The 224 frame needs a bigger local array. The 256 constant
  CSE and the k/ps/y register rotation are still open.
- Not reached: f646c0, f640e8, f79ca8. None of the Round 14 functions has a gb twin draft (checked f47ce0, f4b978,
  f3d5c8, f3cff0 and f52bb0).

## Round 15

Rebased onto origin/claude/project-thread-rl45wv; build byte-identical (889 -> 891 functions).

Matched:
- func_00f640e8: a 47+47-entry table init. `s32 *p = D_00377648; void **q = D_00377748;` then all `*++p = N;`
  statements, then all `*++q = D_xxx;` statements (written sequentially; gcc interleaves them itself; interleaving
  in the source scores 500). The draft was generated from m2c by a script.
- func_00f79ca8: seven func_00f799e0 texture calls with an `s8 c[4]` colour. The fourth colour condition has to be
  written inverted (`if (!(a||b) || FA70 == 67 || !BB0 || EC8) {48} else {128}`) so the 48 block comes first.

Near misses saved:
- func_00f646c0 (428): GS texture upload builder; the original keeps p in a3 and rebuilds the GIFtag in the inner
  loop. Returns `in` (NULL on failure).
- func_00f69278 (101): GS LoadImage packet in u32[4] qwords with a lo mask (extra high-half pick, 360 bytes).

High-half (>= 0xf4fb14) unmatched functions under 1300 bytes with no hand or near-miss file, after this round:
f67530 (392), f58140 (448), f4fba0 (456), f5d6b0 (560), f584d0 (632), f696a0 (752), f7b9e0 (816), f58748 (856),
f53758 (920), f5f940 (944), f58bd0 (968), f5d8e0 (1048), f5fcf0 (1280), f74a28 (1288), f51008 (1296).
