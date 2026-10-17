#include "common.h"

/* nofill: sqrt/atan2 libcall sequences keep their delay-slot nops. */
typedef struct {
    u8 pad0[0x10];
    f32 x10, x14, x18;
    u8 pad1c[0x14];
    f32 x30, x34, x38;
} Obj;
/* Script VM instance (0x350 bytes). */
typedef struct {
    s32 x0;
    Obj *obj;
    u8 pad8[0xc];
    f32 x14, x18, x1c, x20;
    u8 pad24[0x3c];
    Obj *x60;
    s32 x64;
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
    u8 pad32c[0x24];
} __attribute__((aligned(8))) VM;
typedef struct {
    u32 type:8, id:24;
    s32 x4;
    u8 pad8[8];
    f32 x, y, z;
    f32 ang;
} __attribute__((aligned(16))) Msg;
double sqrt(double);
double atan2(double, double);
s32 func_001c4640(Msg *);
typedef struct { s32 x0; Obj *obj; } Ref;
Ref *func_001e98d0(s32, s32);

s32 func_001d4798(VM *vm) {
    Msg m;
    f32 d[3];
    f32 len, a, b, f;
    double r;
    Ref *rf;
    s32 type;
    rf = func_001e98d0(vm->b5, vm->stk[vm->sp]);
    vm->b0 = 1;
    d[0] = rf->obj->x10 - vm->obj->x10;
    d[1] = rf->obj->x14 - vm->obj->x14;
    d[2] = rf->obj->x18 - vm->obj->x18;
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
    m.id = vm->stk[vm->sp - 1];
    m.x4 = vm->x0;
    m.x = rf->obj->x10;
    m.y = rf->obj->x14;
    m.z = rf->obj->x18;
    m.ang = 179.99998f;
    func_001c4640(&m);
    vm->x14 = rf->obj->x10;
    vm->x18 = rf->obj->x14;
    vm->x1c = rf->obj->x18;
    vm->sp -= 2;
    vm->x20 = m.id;
    vm->x60 = rf->obj;
    vm->x64 = 0;
    return 2;
}
