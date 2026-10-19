/* 001cfc28 6w LCS FINDING (hand strict, no context; best stays s11w6's 1w). Mechanism for the last swap (sched2 tie dsll v1 vs li.s, broken by LUID = sched1 order): with `f32 one = 1.0f;` at function top (single use, REG_EQUIV), local-alloc's update_equiv_regs moves the li.s to just before its use AFTER sched1, so li.s takes the sched1 position of the v[3] store; a volatile u8 type + volatile f32 v3 makes that store wait for the stale-tick sb, which puts it after the dsll (dsll v1 / li.s order now right). Left: the moved 1.0 qty is short-lived so local-alloc gives it f0 and the c*2.0f chain f1 (orig f0 chain, f1 for 1.0). Volatile fields are a hack here; needs a non-volatile in-block dependence for the v[3] store. */
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
    volatile u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[3]; volatile f32 v3;
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
        m.v3 = one;
        func_001c4640(&m);
    }
    vm->sp -= 3;
    return 2;
}
