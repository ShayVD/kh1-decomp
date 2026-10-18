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
