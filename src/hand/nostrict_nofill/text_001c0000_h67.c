#include "common.h"
typedef struct {
    u8 pad0[0x370];
    u64 f370;
} Ent;
typedef struct {
    s32 x0;
    Ent *ent;
    u8 pad8[0x60];
    f32 f68;
    s32 f6c;
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
void func_001c4640(Msg *m);
double sin(double);
double cos(double);
s32 func_001ce5f0(VM *vm) {
    Msg m;
    f32 a;
    double d;
    Ent *e;
    m.type = 4;
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
    e = vm->ent;
    if (e) e->f370 &= ~0x100000000000ULL;
    vm->sp -= 2;
    return 2;
}
