#include "common.h"
typedef struct {
    u8 pad0[0x10];
    f32 x10, x14, x18;
    u8 pad1c[0x14];
    f32 x30, x34, x38;
} Obj;
typedef struct {
    s32 x0;
    Obj *obj;
    u8 pad8[0xc];
    f32 x14, x18, x1c, x20;
    u8 pad24[0x3c];
    s32 x60, x64;
    u8 pad68[8];
    s8 *code;
    s32 n;
    s32 x78;
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[91];
    s32 x2f0;
    s32 x2f4;
    s32 ret[8];
    s32 rsp;
    u8 pad31c[0xc];
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, brest:22;
    u32 x32c;
    u64 x330;
    u8 pad338[0x18];
} VM;
typedef struct {
    u32 type:8, id:24;
    s32 x4;
    u64 x8;
    f32 x, y, z;
    f32 ang;
} Msg;
double sqrt(double);
double atan2(double, double);
s32 func_001c4640(Msg *);

s32 func_001cd2d8(VM *vm) {
    Msg m;
    f32 d[3];
    f32 len, a, b, f;
    double r;
    s32 type;
    vm->b0 = 1;
    d[0] = (f32)vm->stk[vm->sp - 2] - vm->obj->x10;
    d[1] = (f32)vm->stk[vm->sp - 1] - vm->obj->x14;
    d[2] = (f32)vm->stk[vm->sp] - vm->obj->x18;
    len = sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);

    d[2] /= len;
    d[0] /= len;
    d[1] /= len;

    a = atan2(d[2], d[0]);
    b = atan2(vm->obj->x38, vm->obj->x30);
    r = a - b;
    type = 2;
    if (r < 0.0) r = 0.0 - r;
    f = r;
    if (f > 3.1415928f) f = 3.1415928f - (f - 3.1415928f);
    if (f * 180.0f / 3.1415928f < 0.0) {
    }
    m.type = type;
    m.id = vm->stk[vm->sp - 3];
    m.x4 = vm->x0;
    m.x = vm->stk[vm->sp - 2];
    m.y = vm->stk[vm->sp - 1];
    m.z = vm->stk[vm->sp];
    m.ang = 179.99998f;
    func_001c4640(&m);
    vm->x14 = m.x;
    vm->x18 = m.y;
    vm->x1c = m.z;
    vm->x20 = m.id;
    vm->x60 = 0;
    vm->x64 = 0;
    vm->sp -= 4;
    return 2;
}
