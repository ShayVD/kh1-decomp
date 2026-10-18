#include "common.h"

/* func_001cd2d8: written like its matched sibling func_001d5b58 (text_001d0000_s6_15.c):
   Msg2 with a u32 val:24 bitfield and aligned(8), m.type = 2 as a constant, the dead
   `d = f * 180 / pi; if (d < 0) d = -d; g = d;` tail (only the libcall compare stays),
   and vm->sp -= 4 after the f60/f64 stores. */

typedef struct { u8 type; u32 val:24; s32 x; s32 a8; s32 ac; f32 v[4]; } __attribute__((aligned(8))) Msg2;
typedef struct { u8 pad0[0x10]; f32 pos[3]; u8 pad1c[0x14]; f32 f30; f32 f34; f32 f38; } Obj5;
typedef struct {
    s32 x0;
    Obj5 *obj;
    u8 pad8[0xc];
    f32 f14[3];
    f32 f20;
    u8 pad24[0x3c];
    s32 f60;
    s32 f64;
    u8 pad68[0x118];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
} VM5;
double sqrt(double);
double atan2(double, double);
s32 func_001c4640(Msg2 *m);
s32 func_001cd2d8(VM5 *vm) {
    Msg2 m;
    f32 v[3];
    f32 len, a, f, g;
    double d;
    vm->flags.x |= 1;
    v[0] = (f32)vm->stk[vm->sp - 2] - vm->obj->pos[0];
    v[1] = (f32)vm->stk[vm->sp - 1] - vm->obj->pos[1];
    v[2] = (f32)vm->stk[vm->sp] - vm->obj->pos[2];
    len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    v[2] /= len;
    v[0] /= len;
    v[1] /= len;

    a = atan2(v[2], v[0]);
    d = a - (f32)atan2(vm->obj->f38, vm->obj->f30);
    if (d < 0.0) d = -d;
    f = d;
    if (3.1415928f < f) f = 3.1415928f - (f - 3.1415928f);
    d = f * 180.0f / 3.1415928f;
    if (d < 0.0) d = -d;
    g = d;

    m.type = 2;
    m.val = vm->stk[vm->sp - 3];
    m.v[0] = vm->stk[vm->sp - 2];
    m.x = vm->x0;
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    m.v[3] = 179.99998f;

    func_001c4640(&m);
    vm->f14[0] = m.v[0];
    vm->f14[1] = m.v[1];
    vm->f14[2] = m.v[2];
    vm->f20 = m.val;
    vm->f60 = 0;
    vm->f64 = 0;
    vm->sp -= 4;
    return 2;
}
