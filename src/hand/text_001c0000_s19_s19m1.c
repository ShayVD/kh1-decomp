/* func_001cfc28: MATCHED (session 19, s19m1), hand. From s11w15's 6w finding (nonmatchings/session11/w15__001cfc28_6w_finding.c): `f32 one = 1.0f;` at the top (update_equiv_regs moves the li.s next to its use after sched1) plus volatile Msg.type and Msg.v3, which put the li.s after the dsll as in the original. New: the c*2.0f chain is a local register variable `register f32 t asm("$f0")` set by `t = (f32)c; t = t + t;`, so local-alloc can no longer give f0 to the moved 1.0 (it gets f1 as in the original). FLAGGED: two volatile fields in the stack message (without them 6w) and the pin (`t = c * 2.0f` in one statement: 6w, the pin dissolves). */
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
        {
            register f32 t asm("$f0");
            t = (f32)c;
            t = t + t;
            m.v[0] = t;
        }
        m.v[1] = 0;
        m.v[2] = 0;
        m.v3 = one;
        func_001c4640(&m);
    }
    vm->sp -= 3;
    return 2;
}
