#include "common.h"
typedef struct {
    u8 pad0[0x30];
    f32 rot[3];
} Ent;
typedef struct {
    s32 x0;
    Ent *ent;
    u8 pad8[0x60];
    f32 f68;
    f32 f6c;
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    u64 flags;
} VM;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
s32 func_001c4640(Msg *);
double sin(double);
double cos(double);
s32 func_001ce750(VM *vm) {
    Msg m;
    f32 a;
    double d;
    m.type = 21;
    m.val = (u32)(vm->stk[vm->sp] * 2);
    m.x = vm->x0;
    vm->f68 = vm->stk[vm->sp - 1];
    a = vm->f68 * 3.1415928f / 180.0f;
    d = a;
    m.v[0] = sin(d);
    m.v[1] = 0.0f;
    m.v[2] = cos(d);
    m.v[3] = 1.0f;
    vm->flags |= 2;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}

s32 func_001ce880(VM *vm) {
    Msg m;
    f32 a;
    double d;
    m.type = 22;
    m.val = (u32)(vm->stk[vm->sp] * 2);
    m.x = vm->x0;
    vm->f68 = vm->stk[vm->sp - 1];
    a = vm->f68 * 3.1415928f / 180.0f;
    d = a;
    m.v[0] = sin(d);
    m.v[1] = 0.0f;
    m.v[2] = cos(d);
    m.v[3] = 1.0f;
    vm->flags |= 2;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}


/* needs make: uses rodata */
double atan2(double, double);
void func_001ce4b8(VM *vm) {
    Ent *e = vm->ent;
    Msg m;
    f32 a = atan2(e->rot[0], e->rot[2]) * 180.0 / 3.1415927410125732421875;
    if ((vm->f6c < 0.0f && a < vm->f68) || (0.0f < vm->f6c && vm->f68 < a)) {
        vm->flags &= ~2;
    } else {
        m.type = 4;
        m.val = 1;
        m.x = vm->x0;
        m.v[0] = 0.0f;
        m.v[1] = a + vm->f6c;
        m.v[2] = 0.0f;
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
}
