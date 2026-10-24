/* Object classes 0xD and 0xE: the handlers func_0013fc80 registers in the
 * class table D_00350D88 (func_0014f830(0xD / 0xE, ...)) and their helpers.
 * Flag mode: nostrict (the other modes are in the sibling files). Read from
 * the code, not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002E27C8.h"
#include "data/types/nostrict_text_00130000_b03_p3.h"
#include "data/pieces/D_002C58B0.h"

/* func_0013f358 (from hand/nostrict/text_00140000_h33.c). */
typedef FVec4 V4f;
typedef struct Eff154 { u8 pad[0x10]; u8 *p10; u32 w14; } Eff154;
typedef struct S130 { u8 pad[0x5C]; u8 b5c; } S130;
typedef struct {
    u8 pad[0x30];
    u64 d30;
    u8 pad38[8];
    V4f p;
    f32 f50;
    f32 f54;
    u8 pad58[4];
    s32 w5c;
    u8 pad60[0x40];
    V4f va0;
    f32 fb0;
    f32 fb4;
    f32 fb8;
    f32 fbc;
    u8 padc0[0x154 - 0xC0];
    Eff154 *p154;
    f32 f158;
} Sub148;
typedef struct {
    u32 flags;
    s32 w4;
    u8 pad8[0x8];
    V4f pos;
    u8 pad20[0x88 - 0x20];
    u32 w88;
    u8 pad8c[0x130 - 0x8C];
    S130 *p130;
    u8 pad134[0x148 - 0x134];
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
    u8 pad316[0x39E - 0x316];
    u8 b39e;
    u8 pad39f[0x3C4 - 0x39F];
    f32 f3c4;
} ObjF3;
void func_00121fc4(V4f *, V4f *);
void func_0013f358(ObjF3 *o) {
    V4f t;
    PlatVu0CopyVector(&o->p148->p, &o->v2f0);
    o->p148->f50 = o->f300;
    o->p148->f54 = o->p148->p.y + o->f304;
    o->p148->w5c = o->h314;
    PlatVu0SubVector(&t, &o->v2f0, &o->pos);
    t.y = 0;
    func_00121fc4(&t, &t);
    PlatVu0ScaleVector(&t, &t, o->p148->f50 + o->f2c0);
    o->pos.x = o->p148->p.x - t.x;
    o->pos.z = o->p148->p.z - t.z;
    o->flags |= 0x200000;
    o->w1cc &= ~1;
}

/* func_0013f510 (from hand/nostrict/text_00140000_h33.c). */
extern f32 D_002BBDFC;
void func_00130578(ObjF3 *, s32, f32);
s32 func_001375f0(ObjF3 *);
s32 func_0013f478(ObjF3 *, s32);
void func_0014f658(ObjF3 *, s32);
s32 func_0013f330(ObjF3 *, s32);
void func_00130398(ObjF3 *, s32, f32);
s32 func_0013f510(ObjF3 *o, s32 a) {
    if (func_001375f0(o) && func_0013f478(o, a)) {
        f32 lim;
        o->p148->f50 += D_002BBDFC;
        lim = 12.0f;
        if (!(o->f300 > 25.0f)) lim = 6.0f;
        if (lim < o->p148->f50) {
            f32 z;
            z = 0.0f;
            func_0014f658(o, 13);
            func_00130398(o, func_0013f330(o, 28) | 0x1000000, z);
            func_00130578(o, func_0013f330(o, 27) | 0x40000000, z);
            return 1;
        }
        return 0;
    }
    o->p148->f50 = 0.0f;
    return 0;
}

/* func_0013f770 (from hand/nostrict/text_00140000_h33.c). */
f32 func_0014cc88(ObjF3 *, f32);
void func_0013f770(ObjF3 *o, V4f *v) {
    V4f t;
    f32 s;
    u32 fl = 0;
    if (v->y < 0.0f) {
        s = 20.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else if (v->w > 0.0f) {
        s = 15.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else {
        s = 5.0f;
        fl = 0x10000;
        func_00130398(o, 6, 12.0f);
    }
    v->y = 0.0f;
    PlatVu0ScaleVector(&t, (V4f *)((u8 *)o + 0x30), -1.0f);
    PlatVu0AddVector(v, v, &t);
    PlatVu0Normalize(v, v);
    v->w = 2.0f;
    func_0014cc88(o, s);
    o->flags |= fl;
}

/* func_0013f910 (from hand/nostrict/text_00130000_b03.c). */
extern f32 D_002C5970;
void func_0013f6d0(B3Ob *, f32 *);
#define func_00130398 ((void (*)(B3Ob *o, s32 a, f32 f)) func_00130398)
#define func_00121fc4 ((void (*)(f32 *, f32 *)) func_00121fc4)
#define func_0014f658 ((void (*)(B3Ob *o, s32 t)) func_0014f658)
#define func_0013f330 ((s32 (*)(B3Ob *, s32)) func_0013f330)
void func_0013f910(B3Ob *o, f32 *v) {
    f32 t[4];
    f32 y, c, f;
    B3Wk *w;
    s32 k;

    PlatVu0ScaleVector(v, v, v[3] * D_002BBDFC);
    if ((o->x2d0 & 0x10) && v[1] > 0.0f) {
        func_0014f658(o, 14);
        func_0013f6d0(o, o->x20);
        return;
    }
    PlatVu0AddVector(t, v, o->x10);
    y = t[1];
    PlatVu0SubVector(t, t, o->x148->x40);
    t[1] = 0.0f;
    PlatVu0Normalize(t, t);
    PlatVu0ScaleVector(t, t, o->x148->x50 + o->x2c0);
    PlatVu0AddVector(t, t, o->x148->x40);
    w = o->x148;
    if (y < w->x54) {
        t[1] = w->x54;
    } else if (w->x40[1] < y) {
        t[1] = w->x40[1];
    } else {
        t[1] = y;
    }
    PlatVu0SubVector(t, t, o->x10);
    func_00121fc4(o->x20, t);
    o->x20[3] *= D_002C5970;
    if (o->x0 & 4) return;
    if (o->x20[1] < 0.0f && 1.0f < o->x20[3]) {
        k = 30;
    } else if (0.0f < o->x20[1]) {
        k = 32;
        if (7.0f < o->x20[3]) k = 31;
    } else {
        PlatVu0SubVector(t, o->x10, o->x148->x40);
        c = t[0] * v[2] - t[2] * v[0];
        if (c < 0.0f) {
            k = 34;
        } else if (0.0f < c) {
            k = 33;
        } else {
            if (o->x1cc & 0x100000) return;
            if (o->x178 > 0) return;
            k = 27;
        }
    }
    if ((o->x164 == 27 || o->x164 == 36) && k == 30) {
        f = 0.0f;
    } else {
        f = 8.0f;
    }
    if (!((s32)(o->x440 >> 33) & 1)) {
        func_00130398(o, func_0013f330(o, k) | 0x40000000, f);
    }
}
#undef func_00130398
#undef func_00121fc4
#undef func_0014f658
#undef func_0013f330

