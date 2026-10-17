#include "common.h"

typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x68];
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    u64 flags;
} VM;
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4a;
typedef struct {
    union {
        u64 flags;
        struct { s32 lo; f32 f4; f32 f8; f32 fc; f32 f10; f32 f14; } s;
    } u;
    f32 t0;
    f32 t1;
    f32 t2;
    u8 pad24[4];
    f32 f28;
    s32 x2c;
    s32 x30;
    u8 pad34[0xc];
    V4a p40;
    V4a p50;
    V4a p60;
    V4a p70;
    V4a p80;
    V4a p90;
    f32 r[3];
    s32 xac;
    f32 fb0;
    s32 xb4;
    u8 padb8[8];
    V4a v0;
    V4a a, b, c, d, e;
    f32 f120, f124, f128, f12c;
} Cam;
extern Cam D_003C5510;

extern f32 D_0036266C;

s32 func_001c9db0(VM *vm) {
    f32 f, a, b;
    s32 sp;
    D_003C5510.u.flags |= 0x200;
    D_003C5510.f28 = 0;
    f = D_0036266C;
    D_003C5510.p60.z = f;
    D_003C5510.f12c = f;
    sp = vm->sp;
    a = vm->stk[sp - 1];
    b = vm->stk[sp];
    vm->sp = sp - 2;
    D_003C5510.p90.z = b;
    D_003C5510.u.s.f14 = a * 2.0f;
    return 2;
}

s32 func_001c9e20(VM *vm) {
    f32 a;
    s32 sp;
    D_003C5510.u.flags |= 0x200;
    D_003C5510.p90.z = D_003C5510.f12c;
    D_003C5510.p60.z = D_0036266C;
    D_003C5510.f28 = 0;
    sp = vm->sp;
    a = vm->stk[sp];
    vm->sp = sp - 1;
    D_003C5510.u.s.f14 = a * 2.0f;
    return 2;
}
