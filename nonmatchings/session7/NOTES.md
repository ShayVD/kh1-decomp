# Session 7 worker notes (condensed from the workers' reports)

## w1 (near misses, list 1)
- Matched 00245b08 (index loop instead of `q = d - n + 5` pointer walk), 00135bb0 (`goto r1` shared return; tail written twice for cross-jumping; CONTEXT_ONLY func_00135b88), 0018d038 (`else if (++idx >= m->n) idx = 0;` at the loop end).
- 001e3a00: sched1 hoists the then-branch `move a0,s0` (LUID tie), original hoisted the else one.
- 00238258: k/num/bk at 48/52/56(sp) behave like memory variables; `volatile k` gives the base/d split but adds a frame slot.
- 0024bce8: all 5040 declaration orders give 5w.

## w2 (list 2)
- Matched 0023ec88 (float limit in a variable, copy written in both branches), pppKeThDraw 0x18c3f8 (switch assigning both values in every case, avoids jump.c if-conversion hoisting a constant), 0015a348 (callee's real arity), 0017f1c8 (`return &D_00575870;`).
- VM flags as `union { u64 x; s32 i[2]; }` (as in func_001d14f0) bring 001cf960 to 7w.
- 001c99a8/001c95f8: FP local-alloc ties do not respond to source or declaration order.
- 00233168 case 7: original reloads q->n at the increment (gcse would merge); nogcse breaks the rest.

## w3 (list 3)
- Matched 0014cdc8, 001cb738, 001d0380, 0023f250, 0023fad0, 0018e348, 0012d468 (needs -fno-rerun-cse-after-loop: mode hand/nostrict_norcse).
- sched1 interblock motion happens only with <= 10 basic blocks; duplicating a tail in both branches adds blocks and stops it (jump2 re-merges, same size).
- func_001cd2d8 and func_00186ab0 are unchanged by every statement-level variant: look at the struct/asm declarations.

## w4 (list 4)
- Matched 00101048 (func_00108618 returns s32; src/auto declares it void), 001269d8, 00133000, 001e8da0.
- 4 drafts reach 0 words only with an empty `__asm__ volatile("")` barrier (kept as w4__*_asmbarrier.c, not counted): 002695f8, 0026a7f0 (sceCdRead), 002698c8, 001e10f8. The original probably had a real side effect there (a volatile access or an inline helper call).
- The ce pass (if-conversion after combine) hoists a single-predecessor `return K` above its branch; a shared label prevents it. Tail call laid out `bnezl ->call; b exit; move v0,0`: `if (c) goto call; r0: return 0; call: return f(...);`.
- 00103c48: the first division in the source gets div1.
- w4 ran `pkill -f rts2` once (against the rules; it most likely hit only its own sweep job).

## w5 (no-draft C)
- Matched 001aadf0, 001db658, 0010a5d0 (`two = 2;` local reused by CSE for later compares).
- func_00171078 is the only `addu; jr; lw %lo` in the binary: the macro load's last instruction sits in the jr slot. The lead assembled 2.96 output with every installed gas (2.96, 990721, 991111, 991111a, 991111b, 991111-01, dtls13010, SN 2.95.2) and none fills it; -msplit-addresses and n32 do not split it either.
- A dead statement after the last call (`i = 0;`) turns off the tail call.
- func_001ca368 does not match in nogcse (session-5 claim): ours fills the slot after jal func_001c6890, the original has a nop.

## w6 (SDK + mid drafts)
- Matched 00171970, 00104ae0, 00267c10 (libvu0 shadow matrix, sdk/gcc991111_01: declare nx, ny, nz, d separately in each branch so they are block-local).
- sceGsExecStoreImage needs sdk/gcc991111_as296 (991111a reorg never puts a volatile store in a slot; 2.96 gas does): 12w, buf/rest s5/s6 swap.
- An explicit `return 0;` right after an `if (A || B) { ... }` block keeps `move a0,s` before each call (func_00168618).
- goto loops get no loop.c notes: constants stay in the loop (func_00177488).
- The nops inside short loops in func_00105d88 are gas's r5900 short-loop fix.

## w7, w9 (large functions)
- Matched 0019bbf0 (w9): read struct-copy fields through separate s32 locals (`t = v.x; ...; u = v.y; ...; v.z`); the same tail is in 0019f1f0 (28w).
- Duplicate a cross-jumped tail per path with a plain-brace macro (do-while(0) adds a loop-align nop).
- Our 2.96 never if-converts a conditional store; 0x1bd090 has `sw; slt; movn; sw`.
- In o32 a symbol base stays in a register only with 2+ uses at different indices; `addu; move; lw; lw` comes from two separate D[K].x40[3] / [2] expressions (0x212cc0).

## w8 (VU0/MMI triage)
- Matched 001a9c30 (C + one inline asm block, register variables for its operands, `"=m"(buf[0])` output for the 16-byte stack result).
- func_00260d00 is hand-written (exception trampoline): exported to src/sdk/libkernl_exc.s.
- Every other VU0/MMI function in the list is gcc output: the ppp Tail-draw family (00190810, 00197278, 0018fee8, 00196930, 00191248, 00197cf8) uses VU0 helpers that must be `#define` macros; 001830a0 and 00192958 are plain C (their lq/sq are 128-bit caller-saves / TImode constants); 0018f268, 001a12f0, 001166e8, 001636d0 are C with short asm blocks or none.

## w11 (ppp Tail-draw family)
- Matched pppStepPrograms 001830a0, pppKeShpTail2Draw 00190810, Tail2XDraw 00197278, TailDraw 0018fee8, TailXDraw 00196930 (src/hand/nostrict/text_00180000_s7_w11.c): C with VU0 helpers as `#define` macros of inline asm. So whole-function VU0 code in the game can be C; the big renderers exported as .s this session (func_001b8198 ...) may be too.
- A local struct whose address goes to a static inline helper makes the inliner copy sp into a pseudo (`move aN,sp`); CSE folds it back except at blocks starting a new CSE path.
- A BLKmode local's slot is rounded up to 16 bytes. Matrix copies per if/else arm as four u128 assignments give lq/sq (struct assignment gives ld/sd).
- `f(pos, v[i++])` puts i+1 in that call's delay slot. `u32 rnd = (rnd*2061+7) & 0xFFFF; rnd / 65535.0f` gives the unsigned-convert sequence.

## w12 (drafts 98-200 words off)
- Matched 001a09d0 (tail copied into each branch), 001a99e8 (masks before shifts `(r & 0x7ff0000) >> 16` so each AND gets its own andi; block-scoped u64 locals keep daddiu+dsll32/dsra32), 00119ad8 (copy + `return 1` in each branch; branch-local variables).
- CSE swaps equal-valued variables for the longest-lived one (`best = 0`, `i = 0`); a separate variable in the other branch fixed a delay slot.
- `while (!done && ...)` keeps a set-done block inside the loop; `break` lets loop.c move it out.
- A switch on 512/640 gives li 640 + xor/movn; if/else gives xori.
- w12 ran `pkill -f "hill4.py func_00102a48"` once (only its own processes).

## w10 (large no-draft C)
- Matched 001dd5c0 with -fno-rerun-loop-opt (mode hand/norlo).
- **The "n32 mixed addressing" is source shape**: in o32 src/hand a nested sub-struct with a variable index, `D_003E3D70[k].s.d` (sub-struct at 0x40), gives `la; addiu 64; addu; lw 12()`; flat `.a[3]`, pointer temporaries and casts fold it. func_002134c8 is 2w off in plain o32 hand.
- The element type of a local array decides reloads after stores (`s32 w[4]` + casts vs `Ob *w[3]`).
- `(x*14 + 0x7fff) << 5` keeps `lui at,0xf; ori; addu`; `x*448 + 0xfffe0` gets narrowed.
- sched1 moves an insn across calls when all its pseudos live across calls (func_001f1fc8 `h = sc<<4`).
- Prototypes: func_001f40a0 takes 2 args; func_00211da0, func_002127e0 are void(void); func_001f1fc8 returns s32 and recurses for case 10.

## w15 (big far drafts)
- Matched 0020f530 and 0020ff80 (src/hand/text_00200000_s7_w15.c): a goto structure inside `while (1)` reproduces a duplicated exit test (loop.c leaves it alone); a field as `union { s32 i; u16 h[2]; }` makes 32-bit stores alias u16 loads and delays them in sched1.
- A jump2 cross-jump running opposite to ours means the source had an explicit goto to a shared label.
- `if (i < N) { do {...} while (i < N); }` fills delay slots differently from `if (N)`. The `for (i = 0; i < N; i = j) { j = i + 1; ... }` form defeats strength reduction.
- A moving pointer (`qq++`, `qq += k`) keeps in-place `addiu v0,v0,16`.

## w16 (n32-region trio)
- Matched func_002134c8 in plain o32 hand: block locals for the stored values (`s16 a = ...; s16 b = ...; u16 c = ...;`) fix the store order. sched1 tie-break: a store whose value and base register both die there wins.
- 00212cc0 is 7w with the sub-struct trick (`D_003E3D70[k].s.d / .s.c`, 4-int struct at +0x40): only the s6/s7/s8 choice in the final loop is left (global-alloc priority).
- The split `la; lw off(reg)` shape needs CSE of the element address between two field loads; a single access always folds.
- A separate pointer per if-group stops jump2 cross-jumping two tails (00217000, now 56w). `n2 = ...; k = n2;` reproduces a leftover `move sN,v0`.
- tools/matching/hc_checkfile.py: hill-climber scored by checkfile (`ADDR=<addr> SZPEN=0 hc_checkfile.py FILE MODE TAG ITERS SEED`, lines between /*P*/ and /*Q*/, /*FIX*/ keeps order).

## w13 (closest near misses, second look)
- Matched func_00182ec0: read the value tested next into a local before the branch (`void *dr = c->draw;`) so reorg fills the beqz slot from the fall-through.
- 00142e30: a return-value local assigned before an early-exit test gets f0 (non-likely bc1t/beq slots match); left: z/d callee-saved swap.
- 00141608: testing the u16 field directly (no local) stops cse folding m[0].
- tools/matching/batch/ (batch.py, anneal2.py, bf.py): compile 150-300 renamed variants of one function in one file and link them all at the same address; typedefs above the `/*UNIT*/` marker. Paths inside may point at /tmp/claude-0/s7/w13: fix before use.
- Still stuck at 1-4 words after two workers each: 0010ed20, 0025add8, 0020b6a8, 00141608, 0025a560, 001d9268, 001e6038, 00269830, 00126f18, 001502e8, 00140960, 00101bb8, 00237d48.

## w17 (remaining big no-draft C)
- Matched func_00218218 (hand, rodata): func_001f9438 and func_001f94f0 must return s32.
- `t = k < 8;` before calls then `if (t) switch (k)` reproduces an sltiu hoisted above them. A duplicated tail call wrapped in a static inline is not cross-jumped. A macro (not inline) keeps &v sp-based.
- Separate identical case bodies give equality tests instead of a range test. Re-tests in delay slots point to jump threading (-fno-thread-jumps helps 00169688 partly: 9w).
- 0x166xxx-0x169xxx is nostrict.

## w18 (giant functions)
- Matched func_00259698 (libkernl printf engine, sdk/gcc991111, rodata jump table D_004921A0): the two fmt registers come from gcse PRE; one common `fmt++` after the if/else (not one per case) and `fmt[2]` read before the digit test.
- 2.96 gcse moves loads/stores only for fixed-address memory, and no copy propagation runs after PRE, so PRE copies survive.
- Inline helpers that reassign their params (`x = x*16 + K`) give the original's `move` + in-place addiu (combine leaves duplicate shifts, post-reload CSE turns them into moves); for *384 pass `col*24` into a `*16+8` helper.
- Writing the final store twice, with `return;` in one branch, keeps sched2 from mixing it into the epilogue (jump2 merges the copies).
- Near misses: 0010c720 26w (prologue order, beqz/beqzl slots in both switch trees), 00102118 28w (`lw s0,16(s0)` vs `move s0,s3`; every copy variant propagates back), 001ffb30 259w (size 1280 vs 1288, frame 96 vs 112: a direction only; the first stores v[16].y / v[21].x right after the Y/R computations give the 0x0fff spill).
- 001a7c50 is a two-register allocation-priority swap; 0010d470, 001f5fe0, 00110618 not attempted in depth.

## w19 (untouched leftovers)
- Matched 00208ea8, 00209030, 002091b8 (siblings; callees func_001f9438/001f94f0/001f9e48 return s32; 002091b8 reads `rows = o->ce + 1` before `cnt = o->cc`), 00232390 (func_0020dd38 takes 6 args, `y = 63;` before the func_001fc308 call, func_001fc308 is void), 001c8a00 (VM stack pops: read the values into f32 locals first, x=stk[sp-2], y=stk[sp-1], f=stk[sp-3], z=stk[sp]).
- func_001eb7b0 matches only with -fmove-all-movables (new mode src/hand/fmam): the flag changes the order of giv-init copies from the second loop pass; source fix: compare through r (`c < r->s.tbl[a + 1][j]`), not q. 2w without the flag.
- sceGsSyncPath 00265bc0 fits sdk/gcc991111_as296 (right size, 51w left), like sceGsExecStoreImage.
- Near misses: 001cf3e0 2w (nogcse; sched1 puts i++ before addu), 001eb7b0 no-flag 2w, 001f4778 2w (sched2 swaps two stores; 5040 store orders and 1500 declaration orders fail), 001fb428 79w, 00265bc0 51w.
- Stuck: 0016bfe8/0016bb68 (allocation priorities e<t<pointer, 2000 variants), 001cfc28 (sched1 late `sw m.x`, 900 orders), 00135a68 (goto loop; four separate v[i] address copies CSE into one), 00169f28 (size off by 8).
- Tools left in /tmp/claude-0/s7/w19 (combo.py `@{a§b}@` choices, pflip.py prototype flips, dump.py global-alloc priorities) were not copied into the repo.
- w19 ran `pkill -f "anneal2.py f4778.b.c"` once (its own processes only).

## w21 (w18 near misses)
- 0010c720 at 12w (hand): an empty `do { } while (0);` before `p = *pp;` is a full sched1/sched2 barrier (plain C, like a compiled-out assert), which fixes most of the prologue order. Left: `lw s1,0(s8)` before the dli/dsll chain, `move a2,t0` before the saves, and beqz/beqzl in both switch trees (depends on liveness down the call path; removing the func_0010c5c8 call flips tree 2).
- 001ffb30 at 226w (hand/nostrict) with the right size and frame: `ub = (u32)buf & 0x0fffffff; ub |= 0x80000000;` (one variable set twice) gives the original stack slots. Left: store schedule; constants 22/66/67 hoisted into s5-s7 in the original.
- 00102118 still 28w. An extra `move` comes from copying a pointer in an earlier block (`o2 = o;`) and loading through o2: CSE pass 1 misses it, gcse substitutes, CSE pass 2 turns the load into a copy. Here it lands before the float conversion, not after it (CSE does not follow the then-arm's jump).

## w22 (2-3 word near misses)
- Matched 001cf3e0 (hand, not nogcse): `t = base;` once before the loop, and inside it `t = base; func_00155be0((u8 *)t + *(s32 *)((u8 *)t + i * 4 + 8)); t = 0;`. t set twice in the loop stops loop.c hoisting and strength reduction; the mention outside makes cse keep t canonical; the copy fills sched2's first cycle.
- Matched 001f4778 (hand/nostrict): write the packet vertex by vertex, transforming each coordinate in place (`TX(k)`/`TY(k)`), and copy shared coordinates from the vertex already done (`s->v[1].x = s->v[0].x;`); cse turns the reloads into copies and the natural order gives the original store order.
- r5900 dual issue: an insn made ready by a cost-0 anti-dependence issues in the same cycle unless another insn takes that cycle's first slot.
- Every insn after a call depends on the return-value copy, so whatever sched1 moved into that block issues right after it (001e6038, 3w: `return 4` value hoisted into block 0, -fno-sched-interblock fixes it but breaks the lui hoists).
- loop.c hoists a cheap invariant only if threshold*savings*lifetime >= loop insns (threshold about 2*(1+free regs) without calls); in big loops it moves only in the rerun pass, after giv init (001ea268, 3w).
- 0011ab88 (3w, v0/v1 swap) and 001f2630 (3w) unchanged. ee-gcc writes no -d dumps for files with inline-asm helpers like 0011ab88's.

## w14 (Tail3 + VU0 C functions)
- No matches. Near misses (hand/nostrict, right size): 00191248 Tail3Draw 314w (w11's 344w draft has a closer normalised diff; keep both), 0018f268 MdlDttDraw 94w (C + two VU0 asm blocks; `andi v1,a2,0xff` before the mode chain left), 001a12f0 50w (packet-header setup), 001636d0 817w (needs an empty asm at the end of inner case 0 for size: a hack), 001166e8 843w (score with wqb03_rr.py 0048D090; o/fp s2/s3 swap).
- `move aN,sp; lw off(aN)` means a locals struct at sp+0 passed by address to a static inline; size it to keep the frame.
- Address held in a register across blocks: compute the pointer in the entry block. `f32 inv[2]` keeps two floats in stack slots.
- Re-test `i < 4` at each site instead of caching it (001a12f0 176 -> 55w). `n = k - 1;` as its own statement keeps `addiu -1; sll`.
- In switch-heavy code write case bodies in asm order. Jump table 0x48D090 has an empty `case 9:`.
- `ColE *ep = &D_002A6238[i]` in a tail stops the table reload. A bare `sqrt.s` is PlatSqrtf; u32 bitfields keep `== 1` compares, u64 masks give lbu+dsrl.
- wqb03_rr.py runs in ~0.2 s, usable in hill-climb loops for rodata functions.

## w23 (SDK leftovers)
- **The asm-barrier cases were volatile globals**: the libcdvd state words D_0046C610-D_0046C658 are volatile; written as volatile accesses in sdk/gcc991111_as296 (991111a reorg keeps volatile accesses out of delay slots, 2.96 gas fills them), func_002695f8, 00269830, 002698c8, sceCdRead 0026a7f0 and 0026a9d0 match (src/sdk/gcc991111_as296/text_00260000_s7_w23.c). Which accesses are volatile differs per function: see the file. Try this before any barrier.
- lseek64 0025db10 matches unchanged with the header of text_00250000_s6_26.c (volatile D_0046AE58, CONTEXT_ONLY func_0025ad68/0025b218).
- `make rank` lists the libc statics __sbprintf (00251600, 00252370), cvt 00253b10, exponent 00253cd0 as unmatched, but they are placed and matched: the rank scan resolves a function name through the registry, which misses `#define name func_X` renames. Their status in rank is wrong, not the build.
- Near misses: DIntr 0025f338 4w (C + cop0 asm; loop.c hoists the 0x10000 mask), sceDbcCreateSocket 002682a8 7w (`i = 0;` first), sceCdInit 0026a250 7w.
- sceGsExecStoreImage 00266380 12w: buf/rest s5/s6 is global-alloc priority (floor_log2(refs)*refs/live_length; read with -dl -dg); the source probably has one more buf reference that jump2 merges.
- 991111a emits `.p2align 3` before a loop label only with loop notes; a goto loop gets none.

## w24 (smallest game leftovers)
- Matched (hand): 00240910 (`r = 0;` before the range test; each arm `if (D.used[N]) { p = &D.ent[N]; goto set; }`, then `return r; set: r = p; return r;` — a shared `set:` label is not if-converted), 00181fe0 (index loop `e = &D[i]`, not a pointer walk: the `move vX,sN; addiu sN,vX,K` step is loop.c's giv), 001cb3c0 (`extern u8 *D_00388480[]`, a pointer array, drops the strict-alias dependency on later s32 loads; tbl store as `((u16 *)b)[8 + n*256 + k]`), 001763f0 (`base = (s32)h; ...; h = (H63 *)base;` makes base the cse class head).
- Matched (hand/nostrict): 001cf348 (w22's 001cf3e0 shape with `s32 n`), 001cd600 (VM handler family: union view, stack values into f32 locals first, then `o2 = s->obj;` so the reload survives as a copy).
- Near miss 001df9c0 6w (hand/nostrict). Unchanged: 00176c60 18w, 0010ed20 4w, 001e3a00 4w, 00249718 12w, 00113e28 8w, 00125240 8w, 00214a68 22w, 002376c8 37w (k==1/k==3 if-converted, k==2 a branch).

## w25 (VU0 renderers as C)
- Matched func_00115940 (hand) and func_001606d0 (4,332 bytes, hand/nostrict) as C + VU0 `#define` macros with operands (VSUB_MAC, VU_LOAD_MTX, VU_MUL_MTX); both removed from the .s stand-ins.
- func_001b8198: gcc shell, hand-written loop bodies (20 `addi`, dead `paddw` before `lui`, `bnez; nop` where gcc would movz, 36 raw `c2` words, fixed t1-t9 roles, leaf). Not attempted.
- A cfc2 MAC-flag test needs `"=&r"` plus `register s32 r asm("$2")` outputs; either alone fails.
- `d < 0 && d >= -2` folds to sltu; `switch (d) { case -1: case -2: }` gives bgez+slti.
- Only integer form `(i << 6) + (u32)base` gives `addu rd, shift, base`; pointer arithmetic puts the base first.
- A pointer declared inside the loop body stops strength reduction of that giv. An s8 union byte gives one andi; a u8 gives lbu+andi+andi 0xff. A 4-byte u8 struct copied by value gives lwl/lwr/swl/swr.

## w28 (VU0 renderer triage)
- The six other renderers (001b6910, 001ae010, 001b1ab8, 001afac0, 001ab0e0, 001b3870) are hand-written inside a gcc shell, like 001b8198: `addi`/`add`/`sub` and `bne $zero,$x` (gcc writes `bnez`) across >90% of each body, fixed t2/t5-t9 loop roles, unfilled `b; nop` slots, DMA polls of 0x1000A000 with four nops, args copied to t-registers at entry, a doubled `jr $v1; nop; nop`. gcc 2.96 has no asm goto, so the loops cannot be split into C + asm. The .s stand-ins are the final form.
- Raw `c2` words (e.g. 0x4B9C29FF) are vclipw-type ops our disassembler does not decode; on their own they are not evidence of hand-writing.

## w26 (mid-size game leftovers)
- Matched (hand/nostrict file; 00140838 and 00141608 also match in hand): 00140838 (a separate failure tail per failing test, `o->p148->d30 |= (u64)0x8000<<17; return 0;`, even though jump2 later cross-jumps them), 00141608 (the three early-return tests joined into one `||` chain returning `s->xbe`: the shared label starts a new cse block, so the field reload survives), 00144d08 (no register asm: `fb0 <= 0.0f`, and each branch duplicates `fb4 = a; func_00130398(o,k,0.0f); fbc = 4.0f;` so cse reuses the test's 0.0f for $f12; duplicating only the call fails).
- In 2.96 a volatile global store always comes out as `addiu reg; sw 0(reg)` (no lo_sum folding into volatile mems), so it cannot be 001e10f8's barrier (4w without the asm; something stops reorg filling the bgtz slot with `li v0,4`).
- A pointer-returning callee changes argument setup order (f12 li.s before `move a0`).
- Near miss 0010ea70 8w (hand). Unchanged: 001c95f8 15w / 001c99a8 10w (FP regs), 001d9268 2w, 0017b668, 001b9f78 10w, 001aa0e0 7w, 001cf960 7w, 0021b4c8 9w, 00249618 10w, 001effc0 11w, 00107c48.

## w27 (80-125 insn game set)
- Matched 0016fc60 and 0017b4f8 (hand/nostrict, both also in hand), 00238258 (hand/nostrict_nofill).
  - 0016fc60: inline helper tail `if (p == 0 || !func_00122ff8(p)) return 0; return func_0012f040(p, part);` gives bnezl/b.
  - 0017b4f8: `((SegL *)((u8 *)p + 0x2c))[i].len` (a member array at an offset that is not a multiple of the element size folds as (p+12)+(i+2)*16; cast the base instead), block-local `{ s32 f = p->flags & 1; nl = f != 0; }` keeps andi+sltu, `t = *pt; t += dt * inv;` loads straight into t.
  - 00238258: a dead second set of the loop pointer (`o = d;` or `o = 0;` after its uses) stops loop.c making it a giv.
- Global-alloc: a priority difference under 1 (x10000 scale) is a tie, won by the lower pseudo number (0024bce8: y0 vs -10).
- Near miss 001ba520 20w. Unchanged: 00237d48 2w, 001cac98 6w, 00115758 7w, 00120cf8 7w, 00142e30 8w, 00110ce0 9w, 00110e68 15w, 00177488, 001eddc0 27w, 00151e28, 00149c80, 002384e0 (needs src alias base unknown), 00246ed8, 001db718, 001519c0 (nogcse + HImode struct local gives the per-case andi; size 476 vs 464).

## w29 (large near misses)
- 00169688 at 4w (hand/nostrict, no flag): case 10 as `if ((D & 1) || (hi & 1)) {...}`; case 25 tests through `s32 *pd = &D_002C5958;`, which stops the jump threading (so -fno-thread-jumps is not needed). Left: case 10's `b L+4; ld v1; nop` is a jump2 cross-jump of two copies; ours cross-jumps into case 13's tail instead (jump2 takes the first jump with 2+ matching insns, not the longest).
- 00217000 at 25w, right size: `if (a) tbl = D_003F2C40; else tbl = D_003F2C40; c = tbl[sel].x10;` (same pointer in both arms stops combine folding sym+16; jump2 deletes the branch) gives the split `la; addu; lw 16(reg)`.
- 00166570: the `move s6,s2; move s2,s0` are loop-hoisted m40/m80 addresses turned into copies by cse2; naming them in the loop keeps them live after it (gcse), unlike the original. 0019f1f0: the late `li.s 1.0` looks like reload rematerialisation; sched1 always hoists ours.
- A label after a barrier gets `.p2align 3`: a stray `b L; nop; L:` in the original means a jump + barrier before that label. Volatile accesses are never folded by combine, so they cannot block jump threading.

## w30 (125-200 insn game set)
- Matched 00126f18 (callee `f32 func_0014cc88(Obj3d0 *, f32)`), 00172998 (shared `r0: return 0` / `r1: return 1` labels, `r = 0` before the range tests that `goto out`) in hand/nostrict; pppPointRApFrame 00186ab0 in hand (VU0 random helper as a statement macro ending in `qmfc2 %0,$vf1` that writes a local, not a static inline returning f32); 00170170 (rodata jtbl 0x48ea00) needs -fno-optimize-sibling-calls in nostrict: new mode src/hand/nostrict_nosib.
- 001e0ab0 4w (same cause as 001e10f8): reorg's fill_simple_delay_slots scans the bgtz fall-through past the sw and steals `li v0,4`; in the original $2 must be live at the target or the scan stops at the sw.
- pi must be written 3.1415927410125732f (3.1415927f gives 0x40490fda). wqb03_rr.py ignores KH1_EXTRA_CCFLAGS (patched copy /tmp/claude-0/s7/w30/rr.py).
- Near misses: 001ca368 70w (gcse reuses f+f), 001f0148 8w, 001aab98 8w, 00101bb8 2w, 001ca0f8 7w, 0024ddf8 9w (sched1 moves the "SLPS" lui across jalr), 00130660 7w (priority tie), 0013a440 11w, 00152928 12w, 001395d8 18w, 00116368 22w, 001137f8 27w, 0020b6a8 4w.

## w20 (render/window functions)
- Independently matched 00209030/002091b8 (same as w19).
- GS packet builders 0x1ff488-0x200648 (nostrict): stores to the packet stay ordered against loads from o and the table, so the lhu/lw positions in a store flood give the source statement order exactly. Float declaration order (not assignment order) decides FP registers: `f32 fcy, fcx, sy, sx;`.
- Near misses: 001ff488 27w (sx/sy read into locals first, `B = Y + ph*16` before `R = X + pw*16`, `u32 func_001edd88`; left: X in v1 and its v[0].x store before the xb4 load), 00200648 240w at the right size (one `u64 *pk` for header and vertices, `t = D_003F2BD8[type]` late, ad word 0xeeeee, u32 colours; vertices rebuilt with tools/matching/asm_sim.py).
- Not attempted: 001c53c8, 001e1c20 (3x3 filter, >50 spill slots), 001f94f0 (recursive text interpreter), 00208458.
