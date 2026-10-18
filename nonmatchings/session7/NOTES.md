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
