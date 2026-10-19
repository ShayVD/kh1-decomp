/* 001cfc28 7w LCS FINDING (hand strict, no context, size 264 right; best stays s11w6 1w). s11w6 draft plus `f32 one = 1.0f;` at the top and `m.v[3] = one;`, NO volatile (s11w15 needed volatile u8 type / f32 v3): update_equiv_regs moves the li.s to just before the v[3] swc1 after sched1, and that swc1 already sits after dsll v1,8 in this draft, so the dsll / li.s order is now the original one. Left: only f0/f1 swapped (1.0 gets f0, the c*2.0f chain f1): the moved 1.0 qty lives 1 insn, so local-alloc (priority floor_log2(refs)*refs/life) allocates it before the 16-insn cvt/add.s qty. Needs the li.s >= ~4 insns before its swc1 but after the dsll in sched1 output, i.e. an in-block predecessor for the li.s (its only dep is the cross-block "do not cross a call" anti dep on func_001e98d0, whose stale INSN_TICK is applied only to insns with an in-block predecessor). Tried: one in the block, v[0]/v[3] reordered, f temp for c*2, f = c; f + f, identical arms on the v[3] store, 0.0f*one: all 7w or worse. */
#include "common.h"
typedef struct {
    s32 x0;
    void *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, brest:26;
    u32 hi;
    u64 q;
} VMd;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
typedef struct { s32 x0; s32 x4; } R4;
typedef struct { s32 x0; R4 *x4; } R;
void func_001c4640(Msg *m);
R *func_001e98d0(s32 a, s32 b);
s32 func_001cfc28(VMd *vm) {
    Msg m; f32 one = 1.0f;
    s32 a = vm->stk[vm->sp - 2];
    s32 b = vm->stk[vm->sp - 1];
    s32 c = vm->stk[vm->sp];
    R *r = func_001e98d0(vm->b5, a);
    if (r == 0) {
        vm->sp -= 3;
        return 2;
    }
    if (r->x4) {
        if (vm) m.x = r->x4->x4; else m.x = r->x4->x4;
        m.type = 29;
        m.val = (u32)b;
        m.v[0] = c * 2.0f;
        m.v[1] = 0;
        m.v[2] = 0;
        m.v[3] = one;
        func_001c4640(&m);
    }
    vm->sp -= 3;
    return 2;
}
