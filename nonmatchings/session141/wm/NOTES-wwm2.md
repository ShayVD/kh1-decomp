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

## Round 16

Rebased onto origin/claude/project-thread-rl45wv; build byte-identical (891 -> 894 functions).

Matched:
- func_00f67530 and its twin func_00f676b8 (the f676b8 near miss is removed). Three changes did it:
  - The uv copy is a goto loop (no loop notes, so nothing gets strength-reduced or reversed) with split source
    pointers: `pu = &src[1].u; pv = &src[1].v; dd = (f32 *)(base + 500); i = 0; loop: dd[-1] = *(f32 *)((u8 *)pu
    + (i << 3)); dd[0] = *(f32 *)((u8 *)pv + (i << 3)); i++; dd += 4; if (i < 4) goto loop;`.
  - The head is `tex = base; o = tex; tex += 208; d.col = (f32 *)tex; tex = base + 480;` and the call passes `o`.
    That gives the extra `move t8,t3` and the t3 reuse.
  - The argument order differs: f67530 calls func_00f65480(arg, o, tex, &d, a4, a5, &m), while f676b8 calls
    func_00f651d0(arg, o, tex, &d, a4, &m, a5).
- func_00f7b9e0: five or six func_00f7a1a8 quads with `Rgba c[4]` and `s32 x[4], y[4]`. Two things mattered:
  - The function takes an argument and passes it on to func_00f7ad38(arg). That is the only way to keep a0 live, so
    the %hi temps use a1.
  - The third quad is written as pairs: c[0]/c[2] rgb and a, then c[1]/c[3], with x/y stored in [2],[3],[0],[1]
    order.

Near miss saved: func_00f696a0 (182, see the header).

## Round 17

Rebased onto origin/claude/project-thread-rl45wv; the build is byte-identical. No new matches.
- func_00f69278: score 101 -> 41 (saved). Separate s64 locals per qword value stopped gcc copying the shared `v`
  into t8, and p[0] now goes before p[8]. The 4-byte size gap is only the trailing alignment nop. Left: the DMA
  ref tag OR order and width (see the header). A 20-minute -j1 permuter run found nothing.
- func_00f72a70: score 139 -> 128 (saved).
  - The main pad loop needs its test at the bottom, written as a goto.
  - The two-entry clear loop needs to be a goto loop with its own pointer; as a do or for loop it is fully
    unrolled.
  - Left: the k/ps/y register rotation, and 8 bytes too many.
- func_00f696a0: not reworked this round (still 182).
- The only f6/f7 function under 1300 bytes left with no hand or near-miss file is f74a28 (1288). Not started.

## Round 18

Rebased onto origin/claude/project-thread-rl45wv. No matches this round. No gb twin drafts exist; gb has
same-shape functions f4d930 (f74a28), f4be48 (f72f40), f49730 (f70828) and f4e6c0 (f757b8).
- func_00f74a28: score 12 (saved). Only the 21/1 colour-constant registers are swapped; see the header.
- func_00f73eb0: score 358 -> 152 (saved).
  - m2c invents arguments for func_001bc520 (it takes none) and for func_001f31a8 (it takes 2).
  - The pad loop is a goto loop with its test at the bottom.
  - Left: global-store scheduling in the prologue and epilogue.
- func_00f757b8: m2c looked at (same family as f74a28, with an extra D_0108F558 mode); not drafted.
- func_00f72f40, func_00f70828: not started.

## Round 19

Rebased onto origin/claude/project-thread-rl45wv.
- func_00f757b8: MATCH, adapted from the f74a28 draft. Its gb twin func_00f4e6c0 also matches after renaming the
  symbols. Keys: declare `e` before `skip` so they get the right stack slots, write the double store as
  `D_00FB4A58 = D_00FB4A5C = ...`, and use `if (cur == i) {7} else {0}`.
- func_00f70828: MATCH. Its gb twin func_00f49730 also matches; /tmp portmap.py maps the symbols by zipping the m2c token
  lists. Key: the inner pad loop is a gcc 2.96 `for (; n = f(), old = cur, !(pad & 0x4000);)`. A for loop whose
  condition is in the header gets its test at the bottom with an initial jump, and it keeps the loop notes, so
  invariants such as `lui s5,0x2c` get hoisted. This differs from a goto loop, which hoists nothing. The `r == -1`
  exit code lives inside the loop (and runs the function epilogue code before `break`).
- func_00f72f40: score 11 (saved). See its header. It wants goto loops, not for loops.
- func_00f73eb0: the for-loop form made it worse (262 vs 152); still 152.

## Round 20

Rebased onto origin/claude/project-thread-rl45wv.
- func_00f72a70: score 128 -> 39 (saved).
  - The first window loop must be `for (k = 0; k < 2; k++)`; gcc reverses it, and the final k == 2 is reused for the
    constant 2 argument.
  - The clear loop is `for (k = 0; k < 2; k++) w[k]->b4 = 0; D_0108F52C = k;`.
  - Left: where `lui 0x2c` (the pad base) is placed; see the header.
- func_00f625f0: first draft, score 217 (saved). Frame and register-pressure differences remain; see the header.
- func_00f6ae68: m2c fails (jump table); not drafted. Its gb twin is f43d70 (same shape).
- func_00f74f30 (gb twin f4de38, same shape), func_00f6d810 and func_00f6a530: not drafted (m2c and asm dumped
  only).

## Round 21

Rebased onto origin/claude/project-thread-rl45wv.
- func_00f6a530: MATCH. Its gb twin func_00f43438 (same size, 2048 bytes) also matches after portmap plus three
  raw-address symbols (D_00F829C0/C4 for D_0108F180/184, D_00F70684 for D_00FB4E04). The alpha fade is
  `if (a == at) alpha = a * 0.5f; else { ...; alpha = a * 0.5f; }`, which gcc cross-jumps into one mul. Two fixes
  that look unrelated also changed the float register allocation there, so retry the alpha forms after fixing them:
  - case 6 must be `if (x10 != 1) tbl = &D_00FB49F0; else tbl = &D_00FB4A20;`.
  - after the fn3C() call the order must be `x = e->x; o->x90 = alpha; y = e->y;`.
- func_00f6d810: score 322 -> 236 (saved). The up path does `goto win` into the down path's window code, written as
  `(n - 8) << 4` / `(i - n + 8) << 4`, and the whole cursor-search section now matches. Left: in the draw loop,
  &D_00FB4C48 is hoisted into s7 and the loop counter spills, where the original spills n instead. gb f46718 has
  the same size (1992 bytes) and is probably its twin.
- func_00f74f30: first draft, score 290 (saved). Both count loops match, including the empty loop that ee-gcc pads
  with nops. The window calc becomes movn here, while the original uses a branch-likely; see the header.

## Round 22

Rebased onto origin/claude/project-thread-rl45wv.
- gb ports, both near misses at the same score as wm: f46718 (score 236, from f6d810) and f4de38 (score 290,
  from f74f30). For f4de38 the m2c token lists do not line up, so plain zip fails. /tmp/.../wwm3/portmap2.py
  builds the map from prefix plus suffix alignment instead. Hand-mapped: D_00F704FC, D_00F829D4.
- hill.py (line-order hill climber) on f74a28 ran 600 s with blocks of decls, c[] pairs and selx/sely: 2549
  tries, still 5 words. On f72f40 (decls, setup, the call args and clear-loop blocks) it ran 600 s: 2624 tries,
  still 8 words. Statement order alone does not fix either one.
- func_00f6cfa0: first draft, score 216 (saved). Notes in the header. The jump table spans 1..9, so the switch
  needs explicit `case 1: case 2: case 7: case 8:` labels (476 -> 216 together with the other fixes). The
  navigation loop is a for loop with the confirm check in its condition (comma expression).
- func_00f6ae68: first draft, score 245 (saved). The jump table was read from wm.elf at 0x00FBA0A0 (rdw.py in the
  same scratch dir).

## Round 23

Rebased onto origin/claude/project-thread-rl45wv. Three large high-half drafts are saved as near misses; the
headers have the details.
- func_00f73570: score 327 (2372 vs 2368 bytes). Ported to gb f4c478 at the same shape and score 327.
- func_00f7d0a8: score 335 (camera fly-to). A bare `sqrt.s` needs `PlatSqrtf` (include "platform/math.h");
  both `sqrtf` and `__builtin_sqrtf` give a call plus a NaN check. ee-gcc prints the EE `sqrt.s fd, ft` form as
  `c1 0x10504` when ft != 0. Scalar locals rather than `f32 v[3]` stop &v[2] from being hoisted into a register.
- func_00f7a350: score 99 (map icons and the GIF-tagged map name). Case order inside the switch sets the block
  order. Declaration order sets the spill slot order, which counts for a lot here (spill slots sp+176..228
  follow the order of the locals). Chained stores (`a[0] = a[1] = v;`) schedule like the original. Its
  neighbour func_00f792c8 is .nostrict, but this function compiles worse in nostrict mode.
- No gb twins for f7d0a8 or f7a350. The gb functions of similar size (f2cf58, f32a38, f377b0) call different
  routines.

## Round 24

Rebased onto origin/claude/project-thread-rl45wv.
- func_00f7a350: hill2 took it from 58 to 31 words (score 55, saved). /tmp/.../wwm3/hill2b.py is a local copy of
  wwm1's hill2.py that points at this worktree. Two lessons:
  - Choice slots must be on a single line, because the {{a@@b}} regex is not dotall.
  - Block permutation can move statements across a `r = p + N;` re-point and silently change semantics; the first
    run swapped the 0x47 and 0x42 packet constants. Group each re-point with its stores on one line, and only use
    blocks of independent statements.
- func_00f6e278: first draft, score 268 (saved). Two hill2 passes took it from 410 to 268. Its gb twin f47180
  (2824 bytes, with the same 672-byte func_00f46ee0 before it) was ported with portmap2, score 268.
- func_00f7ad38: first draft, score 524 (saved). It is f7a350's sibling. The colour bytes need (s32) truncation,
  and id must be u32. hill2 does not help here, because the 24 extra bytes misalign the word count. No gb twin by
  size.

## Round 25

The last three high-half functions now have structurally complete drafts (time-boxed). All are saved as near
misses.
- func_00f71b68: score 660 (3904 vs 3848 bytes). It is the swap/delete list editor: an empty-list wait, a mode-1
  swap-select, a mode-2 delete and a re-find step, then cleanup. The 4-byte S2 icon pair is copied from
  D_00FBA128 (lwl/lwr). The remaining diffs are block placement (the wait loop and the end block). The gb twin
  f4aa70 was ported with portmap2 and also scores 660.
- func_00f6f2a8: score 835 (4396 vs 4464 bytes). It is the top menu: item count, 3 icons plus a 4th when
  func_00f6cf78() >= 3, a help window, the pad loop with wrapping navigation, a kind-3 guard dialog, and a 4-way
  switch that restarts the menu.
  - Two changes helped. Writing the restart as `for (;;)` with `goto next` instead of a goto label let gcc hoist
    the 0.0f constant (1028 -> 897), because loop.c only sees syntactic loops. Typing the tables as s16 and
    D_00FB4B70 as s32 also helped; gcc narrows that load to lhu itself.
  - What is left: 128.0f is not hoisted into f21 at entry, the original keeps &icons in s8 (an `ip = icons` base
    did not reproduce this), and gcse's sel*2 slot is at sp7C. The gb twin f481b0 was ported, score 837.
- func_00f7de08: score 897 (3868 vs 3792 bytes). It is the panel draw: backdrop, gradient quads, title, name and
  option-list GIF packets, and the selected-row highlight. The logic is complete. Alpha scaling forms:
  - a*10240/12800 compiles to (a*5)<<11 over 12800;
  - u8 b*77/128 compiles to >>7 with no rounding.
  What is left is register allocation, because the original caches a*2, a*4, a*5 and a<<8 in stack slots. No
  gb twin exists (no 3792-byte gb function).

## Round 26 (wm low half)

None of the ten functions matched. All have near-miss drafts, and each header says what is left and what was tried.

| Function | Score | Size (draft vs original) | Source |
| --- | --- | --- | --- |
| f37770 | 24 | 1176, same size | new |
| f33270 | 30 | 1056, same size | new |
| f24fe0 | 39 | 1084 vs 1088 | new |
| f3cdd0 | 49 | the 4 bytes are end padding | new |
| f32df0 | 89 | 1140 vs 1152 | new |
| f23018 | 99 | 1308 vs 1336 | new |
| f46cb8 | 109 | 1100 vs 1088 | new |
| f4bdf8 | 179 | 1084 vs 1088 | ported from the gb near miss f24d00 |
| f4b878 | 267 | 1084 vs 1072 | ported from the gb near miss f24780 |
| f49718 | 327 | 1316 vs 1320 | ported from the gb near miss f22620 |

The three gb near misses were ported to wm with portmap3.py, a copy of portmap2 that takes the target overlay as an argument. Each port keeps the score of its gb draft. In f49718, three raw gb addresses had to be mapped by hand:
- D_00F56D90 -> D_00F9B510
- D_00F56D98 -> D_00F9B518
- D_00F74210 -> D_010809C8

The seven new drafts have no gb twin: no gb function has a matching size or call set. gb f38408 is 1088 bytes but calls nothing, so it is not a twin.

Lessons:
- **Switch case 0 (f37770):** a switch over cases {1, 2} plus default needs `default: case 0:` to reproduce the original's slti tree. This was also seen in gb f22620.
- **Float constant rounding (f37770):** gcc 2.96 rounds the literal 0.01745329f to 0x3C8EFA33, while the original has 0x3C8EFA34; 0.017453291f gives 0x3C8EFA34.
- **Unused locals and frame size:** an unused local array can reproduce the original's frame size. This worked in f46cb8 (`s32 buf[24]`, a 192-byte frame) and in f3cdd0 (`f32 u[4]`).
- **Reused coordinate variables (f24fe0):** assigning new values to the same cx/cy variables, instead of writing the expressions inline, took the score from 218 to 39.
- **Field pointers (f32df0):** when the original keeps a separate register per struct field across calls, explicit field-pointer locals reproduce it. This took the score from 292 to 121.
- **Global array (f23018):** declaring the run of globals D_00FBAA78..8C as one `s32 [6]` array helped (149 -> 99).

## Round 27 (wm)

func_00f44898 matched (its own commit). The other functions are near misses, and each header says what is left and what was tried.

| Function | Score | Size (draft vs original) | Source |
| --- | --- | --- | --- |
| f44898 | MATCH | 1344 | new |
| f33270 | 24 | 1056, same size | Round 26 draft, hill2 (was 30) |
| f37770 | 24 | 1176, same size | hill2 found nothing better |
| f422c0 | 26 | 1368, same size | new, then hill2 (32 -> 26) |
| f46070 | 51 | 1332 vs 1336 | new |
| f2ac98 | 62 | 1360, same size | new |
| f28ed8 | 75 | 1340 vs 1344 (end nop) | new |
| f56780 | 165 | 1372 vs 1376 | ported from the gb near miss f2f688 (153) |
| f55fe0 | 180 | 1368, same size | ported from the gb near miss f2eee8 (168) |
| f26810 | 196 | 1344, same size | new |

wm f55fe0/f56780 are the gb f2eee8/f2f688 pair. The other six have no gb twin.

Lessons:
- **Base-pointer locals for argument tables (f44898):** the last 15 words were the schedule of `func_00f21260(..., D_01080810[*st], D_01080800[*st], ...)`. Loading `q = D_01080810;` into a local first and passing `q[*st]` gave the match.
- **Real loops are aligned:** gcc pads the label of a `while (1) { ... if (!more()) break; ...; }` loop to 8 bytes and does not pad a goto label. f44898 went from 32 to 20 by switching from the goto form. The `do { } while (1)` form rotates the tail call to the loop top, which is wrong.
- **Float literals:** gcc 2.96 truncates when it converts a decimal literal to float. If the m2c literal comes out one ulp low, add digits. These were checked with a compile-only probe (cs.py):

  | Literal | Gives |
  | --- | --- |
  | 0.29999999f | 0x3e999999 |
  | 0.39999998f | 0x3ecccccc |
  | 0.36999998f | 0x3ebd70a3 |
  | 0.47f | 0x3ef0a3d7 |
  | 3.1415926f | 0x40490fda |
  | 1.59999996f | 0x3fcccccc |
  | 0.59999997f | 0x3f199999 |
  | -0.54999997f | 0xbf0ccccc |
- **Local aggregate initializers (f46070):** hand.py cannot place the rodata of a local `s32 t[8] = {...}` until the code matches, so a draft shows score 999. To score while drafting, copy a struct from the extern rodata symbol instead (`typedef struct { s32 v[8]; } A8; extern A8 D_00FB74C0; A8 t = D_00FB74C0;`), which gives the same ldl/sdl copy. Switch back to initializers once it matches.
- **Spill choice (f46070):** gcc spills the variable with fewer uses. Folding the two `done = 1` stores into one, `if (done != 0 || (a() && b())) { if (done == 0) mode = b(); done = 1; }`, kept `done` on the stack as in the original (98 -> 59).
- **Colour joins (f28ed8):** when both branches of an if end in `or s0,v1,v0` at a shared label, write each branch as two halves u/v and one `col = u | v;` after the if.

## Round 28 (wwm2)

The last five undrafted wm functions now have structurally complete drafts. Time-boxed; none match.

| Function | Score | Size (ours vs orig) | Note |
| --- | --- | --- | --- |
| f549d0 | 519 | 1964 vs 1984 | port of the gb f2d8d8 draft (gb also 519) |
| f3e988 | 776 | 2224 vs 2264 | minimap blips; colour table drafted as a struct copy |
| f26e80 | 722 | 2872 vs 2944 | item carousel; call sequence lines up |
| f25918 | 530 | 3808 vs 3832 | main-menu state machine, 5-entry jump table |
| f31430 | 384 | 3848 vs 3816 | world-map player/camera update; frame 16 bytes smaller than orig |

gb twins: only f549d0 has one (gb f2d8d8, already drafted). The other four have no gb function of matching size or call set.

f422c0 hill2: two more runs (init stores 61-73/81-90/92-95, then 81-89/92-95/116-123, 360 s each, about 1500 tries each) found nothing below 26.

Lessons:
- **Soft-float fabs:** write `a = d; if (d < 0) a = 0.0 - d;`. It gives the original's `__cmpdf2` / `__subdf3(0, d)` pair. A ternary or a macro made gcc duplicate the code that follows.
- **Lerps with a variable n:** `v = (0 - 640) * i / n + 640;` with n in a local (not a constant) gives the original's mult/div sequence.
- **Integer temps before float calls (f25918):** computing the integer lerps into locals before the `func_00f21ef0((f32)...)` call, instead of inline in the later call arguments, took it 644 -> 530.
- **More float literals** (checked with cs.py):

  | Literal | Gives |
  | --- | --- |
  | 0.069813165f | 0x3d8efa34 |
  | 0.049999998f | 0x3d4ccccc |
  | 0.5235987f | 0x3f060a90 |
  | 1.9098597f | 0x3ff47648 |
  | 57599.996f | 0x4760ffff |

## Round 29 (wwm2, small overlays)

None of these matched. xs_mushu f20550 was dropped after wwm1 matched it.

| Function | Before | Now | What changed |
| --- | --- | --- | --- |
| xs_dh_break f20820 | 156 | 16 | stack array d[2] for the two distances, separate a/b jitters, `d[1] += 0.0f`, truncated literals, hill2 |
| xs_dh_break f20288 | 173 | 95 | literals 3.2f/0.975f, declaration order (stack slots), header via q, store order, end-test shape |
| xl_limit f225b0 | 60 | 41 | test/store as c->res[i], final read through rp (norlo) |
| xs_dumbo f222f8 | none | 93 | first draft; the row loop as a goto loop |
| xs_dumbo f20570 | (scratch 49) | 49 | saved; %hi s1/s2 swap left |
| xs_genie f218f8 | 3 | 3 | 10 more loop/pointer forms, all modes, s32 return for func_00f21580: no change |
| xs_genie f22078 | 74 | 74 | goto loop gives the right shape but no LICM (75); real loops get strength-reduced (101) |
| xs_tink f20818 | 35 | 35 | direct/global/local create forms; a noreturn __assert gives 33 but is not the original |

Lessons:
- **A loop that loop.c must leave alone:** f222f8's row loop reloads its constants every pass and nothing in it is strength-reduced. Writing it as a goto loop, or as a `goto start;` into a `for (;;)` with the pointer step at the top, gives that. A structured for or while loop hoists the constants out.
- **Stack slots follow declaration order:** for spilled scalars (f20288: n, start, spr, jx, jy at 80-96), declaring them in slot order fixed every slot offset.
- **A value kept in a register and then spilled:** when the original writes through a register first and spills it afterwards, do the writes through a second pointer variable (q), then assign the spilled variable (start = q).
- **hill2 and semantics:** line permutation moves statements across braces and data dependencies (xl_limit gave 38 that way, but the code was wrong). Only trust hill2 results inside blocks of independent statements. Slots `{{a@@b}}` must fit on one line.
- **Truncated literals checked with cs.py:** 3.1415928f gives 0x40490fdb, 0.00088888888f gives 0x3a690452, 2.2049995f gives 0x400d1eb6, 3.2f gives 0x404ccccc, 0.975f gives 0x3f799999.
