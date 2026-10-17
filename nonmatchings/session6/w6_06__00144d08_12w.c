/* 12w off (nostrict): uses register f32 z asm("$f12") (not acceptable as final) to keep 0.0 in f12 across the if/else (plain local gets const-propagated: 52w). Remaining: constants a(f1)/s(f20) materialized in wrong order in both branches, fbc=4.0 store scheduled into jal slot. */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { u8 pad[0x30]; u64 d30; u8 pad38[8]; V4f p; f32 f50; f32 f54; u8 pad58[4]; s32 w5c; u8 pad60[0x40]; V4f va0; f32 fb0; f32 fb4; f32 fb8; f32 fbc; } Sub148;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    V4f pos;
    u8 pad20[0x88 - 0x20];
    u32 w88;
    u8 pad8c[0x148 - 0x8C];
    Sub148 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    V4f v2a0;
    V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2D0 - 0x2C4];
    u32 w2d0;
    u8 pad2d4[0x2F0 - 0x2D4];
    V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
    u8 pad316[0x3C4 - 0x316];
    f32 f3c4;
} ObjF3;
extern u32 D_002E27C8;
void func_00130398(ObjF3 *, s32, f32);
void func_00130578(ObjF3 *, s32, f32);
void func_002675a8(V4f *, V4f *);
void func_00121fc4(V4f *, V4f *);
void func_00267560(V4f *, V4f *, f32);

s32 func_00144d08(ObjF3 *o) {
    V4f t;
    register f32 z asm("$f12") = 0.0f;
    if (o->p148->fb0 <= z) {
        s32 k;
        f32 a, s;
        if ((D_002E27C8 >> 6) & 1) {
            k = 48;
            o->p148->fb0 = 75.0f;
            a = 45.0f;
            s = 12.0f;
        } else {
            k = 47;
            o->p148->fb0 = 45.0f;
            a = 30.0f;
            s = 9.0f;
        }
        o->p148->fb4 = a;
        func_00130398(o, k, z);
        o->p148->fbc = 4.0f;
        func_00130578(o, 46, 16.0f);
        func_002675a8(&t, &o->p148->va0);
        t.y = 0;
        func_00121fc4(&t, &t);
        if (t.w == 0.0f) func_002675a8(&t, (V4f *)((u8 *)o + 0x30));
        func_00267560(&o->p148->va0, &t, s);
        o->p148->fb8 = s;
    }
    return 0;
}
