/* 6w off (nostrict, any mode): flag block lw/li/ld/or/sd regs v1/a1/a0 vs ours a1/a0/v1 at 0x140920; tried temps, bitfields, inline, goto shapes, callee-above stubs */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { u8 pad[0x30]; u64 d30; u8 pad38[8]; V4f p; f32 f50; f32 f54; u8 pad58[4]; s32 w5c; } Sub148;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    V4f pos;
    u8 pad20[0x148 - 0x20];
    Sub148 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    V4f v2a0;
    V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2F0 - 0x2C4];
    V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
} ObjF3;
extern V4f D_002C58A0;
void func_002675a8(V4f *, V4f *);
f32 func_0013fe80(f32);
s32 func_001186a8(V4f *);
void func_00267518(V4f *, V4f *, V4f *);
s32 func_0015bcb8(ObjF3 *, V4f *);

s32 func_00140838(ObjF3 *o, V4f *v) {
    V4f t;
    s32 r;
    func_002675a8(&o->v2a0, &o->pos);
    o->v2a0.y = func_0013fe80(o->pos.y);
    o->v2a0.w = 1.0f;
    func_002675a8(&o->v2b0, &D_002C58A0);
    if (v->y < 0.0f) {
        r = 1;
        o->v2a0.y -= 66.66666412353516f;
    } else {
        r = 2;
        o->v2a0.y += 66.66666412353516f;
    }
    if (func_001186a8(&o->v2a0) != 0xFFFF) {
        func_00267518(&t, &o->pos, &o->v2b0);
        if (!func_0015bcb8(o, &t)) goto ok;
    }
    o->p148->d30 |= (u64)0x8000 << 17;
    return 0;
ok:
    return r;
}
