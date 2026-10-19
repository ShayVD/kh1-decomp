/* 001cfc28 1w LCS (3 positional; hand strict, no context; was 12 LCS). New: identical one-statement arms `if (vm) m.x = r->x4->x4; else m.x = r->x4->x4;` (load+store = 2 insns per arm, survives to sched2, merged later; odd source) put the x load/store in their own sched1 blocks, so the m.x store is no longer queued behind the stale INSN_TICK of the func_001e98d0 call: x gets v0, 29 gets a1, mask a2 like the original. Left: sched2 cycle 5 tie between `dsll v1,v1,8` (val<<8, prio 3) and `li.s $f1,1.0` (memory unit, prio 3): ours issues li.s first, the original dsll. Needs dsll at prio 4 or li.s at 2. Tried: all 720 statement orders x arm positions, arm conditions (vm/!vm/b/r/c/fields), paired arms (x+type/val/v[k], x+f=c*2), val/b type variants. */
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
    Msg m;
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
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
    vm->sp -= 3;
    return 2;
}
