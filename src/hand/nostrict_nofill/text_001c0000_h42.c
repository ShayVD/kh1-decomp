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

