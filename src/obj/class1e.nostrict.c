/* Object class 0x1E, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_001598e0 registers in the class table D_00350D88
 * (func_0014f830(0x1E, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1e.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00150000_h35.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003519E0.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E2780.h"
#include "platform/math.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00351A30.h"

/* func_00159178 (from hand/nostrict/text_00150000_h35.c). */
s32 func_00130578(void *, s32, f32);
typedef struct { u8 pad[0xC4]; f32 fC4; } S6C_1541a8;
typedef struct { u8 pad[0x160]; u8 x160[4]; } S148_1545f0;
typedef struct { u8 pad[0x30]; u8 x30[0x118]; S148_1545f0 *p148; u8 pad14c[0x274]; u8 x3C0[4]; } Obj1545f0;
typedef struct { f32 x, y, z, w; } Vec154768;
typedef struct { u8 pad[0x30]; Vec154768 v30; u8 pad40[0x2C]; S6C_1541a8 *p6C; u8 pad70[0x350]; u8 x3C0[4]; } Obj154c60;
s32 func_00122ff8(Act1576a8 *);
typedef struct { s32 w0; s32 w4; } Arg159178;
void func_0013dc10(void *, s32);
void func_0012ec60(s32, s32, void *);
void func_00159148(void *, f32);
/* ---- func_00159178 ---- */
void func_00159178(Obj154c60 *a, s32 b, Arg159178 *s, Vec154768 *o) {
    Vec154768 t;
    func_0013dc10(a, b);
    func_00130578(a, 6, 8.0f);
    if (func_00122ff8((Act1576a8 *)s->w0)) {
        func_0012ec60(s->w0, s->w4, &t);
        PlatVu0SubVector(&t, &t, (u8 *)a + 0x10);
        PlatVu0Normalize(o, &t);
    } else {
        PlatVu0CopyVector(o, &a->v30);
    }
    PlatVu0ScaleVector(a->x3C0, o, 8.0f);
    PlatVu0ScaleVector(((Obj1545f0 *)a)->p148->x160, ((Obj1545f0 *)a)->p148->x160, 0.5f);
    func_00159148(a, 20.0f);
    o->w = 0.0f;
}

/* func_00159258 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x30]; f32 f30; f32 f34; } S5516E0;
extern S5516E0 *D_005516F0;
extern u8 D_00351A50[];
extern u8 D_00351A60[];
extern u8 D_00351A70[];
s32 func_0014efe0(void *, s32);
/* ---- func_00159258 / func_00159350 ---- */
s32 func_00159258(void) {
    void *p = D_002E26A0[0];
    S5516E0 **pp;
    if (!func_00122ff8(p)) return 4;
    if (func_0014efe0(p, 1)) {
        pp = &D_005516F0;
        if ((*pp)->f30 > 0.0f) {
            (*pp)->f30 -= 0.003f;
            if ((*pp)->f30 < 0.0f) (*pp)->f30 = 0.0f;
        }
        PlatVu0CopyVector(&D_002E2780, D_00351A50);
    }
    if (func_0014efe0(p, 2)) PlatVu0CopyVector(&D_002E2780, D_00351A60);
    if (func_0014efe0(p, 3)) PlatVu0CopyVector(&D_002E2780, D_00351A70);
    return 0;
}

/* func_00159350 (from hand/nostrict/text_00150000_h35.c). */
void func_0011ef10(s32, void *);
S5516E0 *func_00159ea8(void *, void *, void *);
extern u8 D_00351A90[];
extern u8 D_00351A80[];
typedef struct { u8 pad[8]; f32 f8; } S6C_159350;
typedef struct { u8 pad[0x6C]; S6C_159350 *p6C; } Obj159350;
/* ---- func_00159258 / func_00159350 ---- */
void func_00159350(Obj1545f0 *a) {
    S5516E0 *r;
    ((Obj159350 *)a)->p6C->f8 = 6.0f;
    PlatVu0ScaleVector(a->p148->x160, a->p148->x160, 0.1f);
    if ((void *)a == D_002E26A0[0]) {
        r = func_00159ea8(a, D_00351A80, D_00351A90);
        D_005516F0 = r;
        r->f30 = 0.5f;
        func_0011ef10(0x18894, func_00159258);
    }
}

/* func_00159440 (from hand/nostrict/text_00150000_h58.c). */
typedef S31b0_2e31b0 P8;
typedef struct {
    u32 w0; s32 w4; s32 w8; s32 wC; s32 x10; f32 f14; s32 x18; f32 f1c; s32 x20; u8 pad24[0xc]; V4 v30; f32 f40; f32 f44; s32 x48; s32 x4c;
} S144;
typedef struct {
    u8 pad0[0x10]; V4 pos; u8 pad20[0x10]; V4 v30; u8 pad40[0x30]; s32 x70; u8 pad74[0xf0]; s32 x164;
} S98;
typedef struct { u8 pad0[5]; u8 b5; u8 pad6[0xe]; struct { u8 pad0[1]; u8 b1; } *x14; } S134;
#define ACT_BODY(T144) \
    u32 w0; u8 pad4[4]; s32 x8; u8 padc[4]; V4 pos; V4 x20; V4 x30; V4 x40; u8 pad50[0x18]; s32 x68; struct { u8 pad[0x3c]; s32 x3c; } *x6c; s32 x70; P8 x74; u8 pad7c[0xc]; s32 x88; s32 x8c; u64 x90; S98 *x98; u8 pad9c[0x24]; V4 xc0; f32 xd0[4][4]; u8 pad110[0x10]; V4 x120; \
    struct { u8 pad[0x44]; f32 x44; s16 x48; u8 pad4a[2]; u16 x4c; } *x130; S134 *x134; u8 pad138[0xc]; T144 *x144; \
    struct { u8 pad[0x160]; V4 v160; } *x148; u8 pad14c[0x1d4]; V4 x320; u8 pad330[0x40]; u64 x370; u8 pad378[0x26]; u8 x39e; u8 pad39f[0x11]; f32 x3b0; u8 pad3b4[0xc]; V4 x3c0; u8 pad3d0[0x14]; f32 x3e4; u8 pad3e8[8]; V4 x3f0; s32 x400; u8 pad404[0x9c]; void *x4a0;
typedef struct Actor_59440 { ACT_BODY(S144) } Act;
void func_00130398(void *, s32, f32);
f32 func_001376e8(void *, void *);
s32 func_00137618(void *);
void func_0012bd98(void *, s32, u32, void *);
/* ---- func_00159440 ---- */
void func_00159440(Act *a, V4 *o) {
    V4 m;
    V4 t;
    s32 k = 0;
    u32 fl = 0x80000100;
    PlatVu0CopyVector(&m, &a->x148->v160);
    m.y = 0.0f;
    PlatVu0Normalize(&m, &m);
    if (o->w > 0.0f) {
        o->w = 0.3f;
        PlatVu0OuterProduct(&t, &m, o);
        if (t.y > 0.9f) {
            fl = 0x40000100;
            k = 203;
        } else if (t.y < -0.9f) {
            fl = 0x20000100;
            k = 206;
        }
    }
    if (func_00137618(a)) func_00130398(a, k | 0x40000000, 8.0f);
    func_0012bd98(a, a->x39e, fl, &a->pos);
    PlatVu0CopyVector(&a->x20, o);
    PlatVu0ScaleVector(&t, &m, a->x148->v160.w);
    PlatVu0AddVector(&t, &t, &a->x3c0);
    func_001376e8(a, &t);
}

/* func_001595a8 (from hand/nostrict/text_00150000_h58.c). */
typedef struct Actor_595a8 { ACT_BODY(S144) } Act_595a8;
extern f32 D_002BBDFC;
void func_00121fc4(void *, void *);
f32 func_00121748(void *, void *);
/* ---- func_001595a8 ---- */
void func_001595a8(Act_595a8 *a, V4 *o) {
    V4 m;
    f32 f;
    if (a->x20.w > 0.0f) {
        PlatVu0ScaleVector(o, &a->x20, a->x20.w * D_002BBDFC);
        PlatVu0AddVector(o, o, &a->x3c0);
        func_00121fc4(o, o);
    } else {
        func_00121fc4(o, &a->x3c0);
        if (func_00121748(o, &a->x148->v160) > -0.7f)
            o->w -= D_002BBDFC * 0.05f;
        else
            o->w -= D_002BBDFC * 0.3f;
    }
    if (o->w < 0.0f) f = 0.0f;
    else if (o->w > 6.0f) f = 6.0f;
    else f = o->w;
    PlatVu0ScaleVector(&a->x3c0, o, f);
    PlatVu0OuterProduct(&m, &a->xc0, o);
    PlatVu0Normalize(&m, &m);
    PlatVu0OuterProduct(o, &m, &a->xc0);
    PlatVu0Normalize(o, o);
    PlatVu0ScaleVectorXYZ(o, o, f * D_002BBDFC);
}

/* func_00159740 (from hand/nostrict/text_00150000_h35.c). */
s32 func_00130340(void *, s32, f32);
void func_0014f658(void *, s32);
typedef struct { u8 pad[0x4C]; u16 h4C; } S130_157818;
typedef struct { u8 pad[4]; f32 f4; } Ret157ea8;
typedef struct { u16 a, b; } P159740;
typedef struct { u8 pad[0x54]; P159740 e[1]; } S308CDC_e;
typedef struct { u8 pad[0x100]; f32 f100; u8 pad104[0x5C]; u8 x160[4]; } S148_159740;
typedef struct { u8 pad[0x130]; S130_157818 *p130; u8 pad134[0x14]; S148_159740 *p148; u8 pad14c[0x264]; f32 f3B0; } Obj159740;
/* ---- func_00159740 ---- */
Ret157ea8 *func_00159740(Obj159740 *a, Vec154768 *o) {
    Ret157ea8 *r = (Ret157ea8 *)func_00130340(a, 0x10004, 0.0f);
    r->f4 = 4.0f;
    func_0014f658(a, 1);
    a->f3B0 = 0.0f;
    a->p148->f100 = 0.0f;
    func_00159148(a, ((S308CDC_e *)(*(Cfg_308cdc **)&D_00308CDC))->e[a->p130->h4C].a);
    PlatVu0CopyVector(o, a->p148->x160);
    o->y = 0.0f;
    func_00121fc4(o, o);
    return r;
}

/* func_00159808 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x160]; u8 x160[0xC]; f32 f16C; } S148_159808;
typedef struct { u8 pad[0x20]; Vec154768 v20; u8 pad30[0x118]; S148_159808 *p148; u8 pad14c[0x274]; u8 x3C0[4]; } Obj159808;
#define func_001376e8 ((void (*)(void *, void *)) func_001376e8)
/* ---- func_00159808 ---- */
void func_00159808(Obj159808 *a, Vec154768 *b) {
    Vec154768 t, u;
    if (b->w > 0.0f) b->w = 6.0f;
    PlatVu0CopyVector(&a->v20, b);
    if (func_00137618(a)) {
        PlatVu0CopyVector(&t, a->p148->x160);
        t.y = 0.0f;
        PlatVu0Normalize(&t, &t);
        PlatVu0ScaleVector(&u, &t, a->p148->f16C);
        PlatVu0AddVector(&u, &u, a->x3C0);
        func_001376e8(a, &u);
    }
}
#undef func_001376e8

