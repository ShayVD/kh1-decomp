/* Hit reactions, without strict aliasing (docs/modules.md "Session 52"):
 * the reaction handlers by state (func_001542f8 ... func_00154d60, picked by
 * the tables in func_00154e38) using the tuning block *D_00308CDC, and
 * func_00153f88 (an actor's reaction to a hit), and func_001550a0 (a hit
 * taken: the damage, the gauge func_00241948, the reaction func_00157a30).
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "platform/math.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E3168.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"
#include "data/bss_0055.h"
#include "m2c.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_003044E0.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304B78.h"

/* func_00153f88 (from hand/nostrict/text_00150000_h58.c). */
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
typedef struct Actor_53f88 { ACT_BODY(S144) } Act;
extern f32 D_002BBDFC;
void func_00130398(void *, s32, f32);
void func_00157a30(Act *, s32, Act *);
void func_00153e80(void *);
s32 func_00148908(void *);
void func_001358b8(void *, s32);
void func_001586a8(s32);
void func_001373f8(void *, f32);
s32 func_0013c968(s32, s32);
typedef union { u32 w; struct { u32 b0:1; u32 b1:1; u32 p2:14; u32 b16:1; u32 p17:6; u32 b23:1; u32 b24:1; u32 b25:1; u32 p26:6; } b; } F5958;
extern F5958 D_002C5958;
/* ---- func_00153f88 ---- */
void func_00153f88(Act *a) {
    f32 s;
    if (!(a->x88 & 0x30)) return;
    if (a->x6c->x3c > 0) {
        func_00157a30(a, 24, 0);
        func_00153e80(a);
    } else {
    if (!(a->w0 & 4)) {
        switch (a->x70) {
        case 0:
        case 24:
        case 25:
            func_00130398(a, 0x1000043, 16.0f);
            break;
        case 17:
            func_00130398(a, 0x100006c, 16.0f);
            break;
        case 8:
            func_00130398(a, 0x100008d, 16.0f);
            break;
        case 2:
            break;
        default:
            return;
        }
    }
    if (a->x88 & 0x10) {
        a->x3e4 = (*(Cfg_308cdc **)&D_00308CDC)->x7c[a->x130->x4c] * 60.0f;
        a->x88 = (a->x88 & ~0x10) | 0x20;
        if (!a->x400) {
            a->x400 = func_00148908(a);
            func_001358b8(a, 10);
        }
        func_001586a8(14);
    }
    func_001373f8(a, 30.0f);
    s = D_002BBDFC;
    if (!(D_002C5958.b.b0)) s *= (*(Cfg_308cdc **)&D_00308CDC)->x90;
    if (func_0013c968(9, a->x130->x4c) > 0) s += s;
    a->x3e4 -= s;
    if (a->x3e4 <= 0.0f) {
        if ((D_002C5958.b.b0) || ((s32)(a->x370 >> 35) & 1)) func_00157a30(a, 25, 0);
        func_00153e80(a);
    }
    }
}

/* func_001541a8 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0xC4]; f32 fC4; } S6C_1541a8;
typedef struct { u8 pad[0x6C]; S6C_1541a8 *p6C; } Obj1541a8;
typedef struct { u8 pad[0xC]; f32 fC; } Out1541a8;
f32 func_001348e0(void *, void *);
/* ---- func_001541a8 ---- */
void func_001541a8(Obj1541a8 *a, u8 *b, Out1541a8 *o) {
    f32 s;
    f32 v;
    PlatVu0CopyVector(o, b + 16);
    s = a->p6C->fC4;
    if (func_001348e0(a, b) * (*(Cfg_308cdc **)&D_00308CDC)->f20 < (*(Cfg_308cdc **)&D_00308CDC)->f24) {
        v = func_001348e0(a, b) * (*(Cfg_308cdc **)&D_00308CDC)->f20 * s;
    } else {
        v = (*(Cfg_308cdc **)&D_00308CDC)->f24 * s;
    }
    o->fC = v;
}

/* func_001542f8 (from hand/nostrict/text_00150000_h35.c). */
s32 func_00130340(void *, s32, f32);
s32 func_00130578(void *, s32, f32);
typedef struct { u8 pad[0x10]; u8 x10[0x10]; s32 w20; } Arg1542f8;
typedef struct { u8 pad[0x30]; u8 x30[0x390]; u8 x3C0[4]; } Obj1542f8;
typedef struct { s32 w[4]; } Out1542f8;
void func_00156260(void *, void *);
/* ---- func_001542f8 ---- */
void func_001542f8(Obj1542f8 *a, Arg1542f8 *b) {
    Out1542f8 o;
    f32 d = PlatVu0InnerProduct(a->x30, b->x10);
    s32 n;
    switch (b->w20) {
    case 1:
        if (d < 0.0f) n = 0x01000049; else n = 0x0100004B;
        func_00130340(a, n, 0.0f);
        break;
    case 0:
    default:
        func_00130340(a, d < 0.0f ? 0x01000048 : 0x0100004A, 0.0f);
        break;
    }
    func_001373f8(a, 30.0f);
    func_00130578(a, 0x40000000, 8.0f);
    PlatVu0CopyVector(a->x3C0, &D_002C58B0);
    func_001541a8((Obj1541a8 *)a, (u8 *)b, (Out1541a8 *)&o);
    func_00156260(a, &o);
}

/* func_001543f8 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x10]; u8 x10[0x10]; } Arg1543f8;
typedef struct { u8 pad[0x30]; u8 x30[0x390]; u8 x3C0[4]; } Obj1543f8;
f32 func_0014cce0(void *, f32);
void func_00154258(Obj1543f8 *, Arg1543f8 *, void *);
/* ---- func_001543f8 / func_001544a0 ---- */
void func_001543f8(Obj1543f8 *a, Arg1543f8 *b) {
    func_00130340(a, PlatVu0InnerProduct(a->x30, b->x10) < 0.0f ? 0x0100004E : 0x0100004F, 0.0f);
    func_00130578(a, 0x40000006, 8.0f);
    func_001373f8(a, 30.0f);
    func_0014cce0(a, 20.0f);
    func_00154258(a, b, a->x3C0);
}

/* func_001544a0 (from hand/nostrict/text_00150000_h35.c). */
/* ---- func_001543f8 / func_001544a0 ---- */
void func_001544a0(Obj1543f8 *a, Arg1543f8 *b) {
    Out1542f8 o;
    func_00130340(a, PlatVu0InnerProduct(a->x30, b->x10) < 0.0f ? 0x0100004E : 0x0100004F, 0.0f);
    func_00130578(a, 0x40000075, 16.0f);
    func_001373f8(a, 30.0f);
    func_001541a8((Obj1541a8 *)a, (u8 *)b, (Out1541a8 *)&o);
    func_00156260(a, &o);
}

/* func_00154548 (from hand/nostrict/text_00150000_2.c). */
#define func_00130340 ((s32 (*)(s32, s32, f32)) func_00130340)
#define func_00130578 ((s32 (*)(s32, s32, f32)) func_00130578)
#define func_001373f8 ((void (*)(s32, f32)) func_001373f8)
#define func_001541a8 ((void (*)(s32, s32, s32)) func_001541a8)
#define func_00156260 ((void (*)(s32, s32)) func_00156260)
void func_00154548(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_00130340(arg0, 0x0100006A, 0.0f);
    func_00130578(arg0, 0x4000002D, 0.0f);
    func_001373f8(arg0, 3e+01f);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0xB0) = 0.0f;
    PlatVu0CopyVector((s32) (M2C_FIELD(arg0, void **, 0x148) + 0xA0), (s32) &D_002C58B0);
    func_001541a8(arg0, arg1, (s32) sp);
    func_00156260(arg0, (s32) sp);
}
#undef func_00130340
#undef func_00130578
#undef func_001373f8
#undef func_001541a8
#undef func_00156260

/* func_001545f0 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x160]; u8 x160[4]; } S148_1545f0;
typedef struct { u8 pad[0x30]; u8 x30[0x118]; S148_1545f0 *p148; u8 pad14c[0x274]; u8 x3C0[4]; } Obj1545f0;
void func_0014f658(void *, s32);
/* ---- func_001545f0 / func_001546b8 ---- */
void func_001545f0(Obj1545f0 *a, Arg1543f8 *b) {
    func_00130340(a, PlatVu0InnerProduct(a->x30, b->x10) < 0.0f ? 0x0100004E : 0x0100004F, 0.0f);
    func_00130578(a, 0x40000006, 8.0f);
    func_001373f8(a, 30.0f);
    func_0014cce0(a, 20.0f);
    func_0014f658(a, 31);
    func_00154258((Obj1543f8 *)a, b, a->x3C0);
    PlatVu0CopyVector(a->p148->x160, &D_002C58B0);
}

/* func_001546b8 (from hand/nostrict/text_00150000_h35.c). */
/* ---- func_001545f0 / func_001546b8 ---- */
void func_001546b8(Obj1545f0 *a, Arg1543f8 *b) {
    if (PlatVu0InnerProduct(a->x30, b->x10) < 0.0f) {
        func_00130340(a, 0x0100004C, 0.0f);
    } else {
        func_00130340(a, 0x0100004D, 0.0f);
    }
    func_00130578(a, 0x40000000, 8.0f);
    func_001373f8(a, 30.0f);
    PlatVu0CopyVector(a->x3C0, &D_002C58B0);
    PlatVu0ScaleVector(a->p148->x160, a->p148->x160, 0.1f);
}

/* func_00154768 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { f32 x, y, z, w; } Vec154768;
typedef struct { u8 pad[0x10]; Vec154768 v; } Arg154768;
typedef struct { u8 pad[0x30]; Vec154768 v30; u8 pad40[0x110]; f32 f150; u8 pad154[0x26C]; u8 x3C0[4]; } Obj154768;
f32 atan2f(f32, f32);
void func_00137688(void *, f32);
/* ---- func_00154768 / func_00154880 ---- */
void func_00154768(Obj154768 *a, Arg154768 *b, Vec154768 *o) {
    f32 r;
    if (PlatVu0InnerProduct(&a->v30, &b->v) < 0.0f) {
        func_00130340(a, 0x0100004C, 0.0f);
        r = atan2f(-b->v.x, -b->v.z);
    } else {
        func_00130340(a, 0x0100004D, 0.0f);
        r = atan2f(b->v.x, b->v.z);
    }
    func_00130578(a, 0x40000000, 8.0f);
    func_001373f8(a, 30.0f);
    func_00137688(a, r);
    a->f150 = r;
    PlatVu0CopyVector(o, &a->v30);
    o->w = 0.0f;
    PlatVu0CopyVector(a->x3C0, &D_002C58B0);
}

/* func_00154880 (from hand/nostrict/text_00150000_h35.c). */
void func_00138a20(void *, void *, f32);
typedef struct { u8 pad[0x3C]; f32 f3C; } S308CDC_b;
/* ---- func_00154768 / func_00154880 ---- */
void func_00154880(Obj154768 *a, Arg154768 *b, Vec154768 *o) {
    Vec154768 t;
    f32 r;
    s32 n;
    if (PlatVu0InnerProduct(&a->v30, &b->v) < 0.0f) {
        n = 0x50;
        r = atan2f(-b->v.x, -b->v.z);
    } else {
        n = 0x51;
        r = atan2f(b->v.x, b->v.z);
    }
    func_00130340(a, n | 0x01000000, 0.0f);
    func_00130578(a, 0x40000006, 8.0f);
    func_001373f8(a, 30.0f);
    a->f150 = r;
    func_00137688(a, r);
    PlatVu0CopyVector(o, &a->v30);
    o->w = 0.0f;
    PlatVu0CopyVector(&t, &b->v);
    t.w = ((S308CDC_b *)(*(Cfg_308cdc **)&D_00308CDC))->f3C;
    func_00138a20(a, &t, 20.0f);
}

/* func_001549b8 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x1C]; f32 f1C; f32 f20; f32 f24; } S308CDC_c;
typedef struct { u8 pad[0x6C]; S6C_1541a8 *p6C; } Obj6C_1549b8;
/* ---- func_001549b8 / func_00154af8 ---- */
void func_001549b8(Obj154768 *a, Arg154768 *b, Vec154768 *o) {
    Vec154768 t;
    f32 r;
    s32 n;
    if (PlatVu0InnerProduct(&a->v30, &b->v) < 0.0f) {
        n = 0x50;
        r = atan2f(-b->v.x, -b->v.z);
    } else {
        n = 0x51;
        r = atan2f(b->v.x, b->v.z);
    }
    func_00130340(a, n | 0x01000000, 0.0f);
    func_00130578(a, 0x40000075, 16.0f);
    func_001373f8(a, 30.0f);
    a->f150 = r;
    func_00137688(a, r);
    PlatVu0CopyVector(o, &a->v30);
    o->w = 0.0f;
    PlatVu0CopyVector(&t, &b->v);
    t.w = ((S308CDC_c *)(*(Cfg_308cdc **)&D_00308CDC))->f24 * ((Obj6C_1549b8 *)a)->p6C->fC4;
    func_00156260(a, &t);
}

/* func_00154af8 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x29]; u8 b29; } S14C_154af8;
typedef struct { u8 pad[0x30]; Vec154768 v30; u8 pad40[0x10C]; S14C_154af8 *p14C; } Obj154af8;
typedef struct { u8 pad[8]; s32 w8; } Arg154af8;
/* ---- func_001549b8 / func_00154af8 ---- */
void func_00154af8(Obj154af8 *a, Arg154af8 *b, Vec154768 *o) {
    Vec154768 t;
    func_00130340(a, 0x0100006E, 0.0f);
    func_00130578(a, 0x40000000, 0.0f);
    func_001373f8(a, 8.0f);
    a->p14C->b29--;
    if (b->w8 < 0) {
        PlatVu0SubVector(&t, (*(f32 (*)[0x4])&D_002C58A0), &a->v30);
        t.w = (f32)-b->w8 * ((S308CDC_c *)(*(Cfg_308cdc **)&D_00308CDC))->f1C * ((Obj6C_1549b8 *)a)->p6C->fC4;
        func_00156260(a, &t);
    }
    o->w = 0.0f;
}

/* func_00154c60 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { u8 pad[0x1C]; f32 f1C; u8 pad20[0x10]; f32 f30; f32 f34; } S308CDC_d;
typedef struct { u8 pad[0x30]; Vec154768 v30; u8 pad40[0x2C]; S6C_1541a8 *p6C; u8 pad70[0x350]; u8 x3C0[4]; } Obj154c60;
/* ---- func_00154c60 / func_00154d60 ---- */
void func_00154c60(Obj154c60 *a, Arg154af8 *b) {
    f32 f, m, s;
    func_00130340(a, 0x01000070, 0.0f);
    func_00130578(a, 0x40000006, 0.0f);
    func_001373f8(a, 8.0f);
    func_0014cce0(a, 20.0f);
    if (b->w8 < 0) {
        f = (f32)b->w8 / 100.0f * ((S308CDC_d *)(*(Cfg_308cdc **)&D_00308CDC))->f30;
        m = -((S308CDC_d *)(*(Cfg_308cdc **)&D_00308CDC))->f34;
        s = a->p6C->fC4;
        if (m < f) {
            m = f * s;
        } else {
            m = m * s;
        }
        PlatVu0ScaleVector(a->x3C0, &a->v30, m);
    } else {
        PlatVu0CopyVector(a->x3C0, (*(f32 (*)[0x4])&D_002C58A0));
    }
}

/* func_00154d60 (from hand/nostrict/text_00150000_h35.c). */
/* ---- func_00154c60 / func_00154d60 ---- */
void func_00154d60(Obj154c60 *a, Arg154af8 *b) {
    Vec154768 t;
    func_00130340(a, 0x01000070, 0.0f);
    func_00130578(a, 0x40000075, 16.0f);
    func_001373f8(a, 8.0f);
    PlatVu0SubVector(&t, (*(f32 (*)[0x4])&D_002C58A0), &a->v30);
    if (b->w8 < 0) {
        t.w = (f32)-b->w8 * ((S308CDC_d *)(*(Cfg_308cdc **)&D_00308CDC))->f1C * a->p6C->fC4;
    } else {
        t.w = 0.0f;
    }
    func_00156260(a, &t);
}

/* func_00154e38 (from hand/nostrict/text_00150000_h58.c). */
typedef struct Actor_54e38 { ACT_BODY(S144) } Act_54e38;
s32 D_00F20000(s32, s32);
typedef void (*Fn6)(void *, s32, s32);
void func_00154be0();
typedef struct { Fn6 f[4]; } Tbl6;
/* ---- func_00154e38 ---- */
s32 func_00154e38(Act_54e38 *a, s32 k, s32 b, s32 c) {
    Tbl6 t0 = { { func_001542f8, func_00154768, func_00154af8, func_00154be0 } };
    Tbl6 t1 = { { func_001543f8, func_00154880, func_00154c60, func_00154c60 } };
    Tbl6 t2 = { { func_001544a0, func_001549b8, func_00154d60, func_00154d60 } };
    Tbl6 t3 = { { func_00154548, func_00154548, 0, 0 } };
    Tbl6 t4 = { { func_001545f0, func_001545f0, 0, 0 } };
    Tbl6 t5 = { { func_001546b8, func_001546b8, 0, 0 } };
    Tbl6 *t;
    switch (a->x70) {
    case 0: case 1: case 12: case 28: case 32: case 38:
        func_0014f658(a, 0);
        t = &t0;
        break;
    case 24: case 25:
        func_0014f658(a, 24);
        t = &t0;
        break;
    case 8:
        t = &t2;
        break;
    case 17:
        t = &t3;
        break;
    case 30: case 31:
        t = &t4;
        break;
    case 29:
        t = &t5;
        break;
    case 39:
        D_00F20000(10, 0);
        t = 0;
        break;
    default:
        t = &t1;
        break;
    }
    if (t) switch (k) {
    case 0: case 1: case 2:
        break;
    case 3:
        t->f[0](a, b, c);
        return 1;
    case 4: case 5:
        t->f[1](a, b, c);
        return 1;
    case 6:
        t->f[2](a, b, c);
        return 0;
    case 7:
        t->f[3](a, b, c);
        break;
    }
    return 0;
}

/* func_001550a0 (from hand/nostrict/text_00130000_c02.c, session 54). */
typedef struct {
    u32 x0;
    u8 pad4[0x3c - 4];
    s32 x3c;
    s32 x40;
} C02Ab;

typedef struct {
    u8 pad0[0x4c];
    u16 x4c;
} C02Kd;

typedef struct {
    u8 pad0[0x170];
    u64 x170;
} C02Ex;

typedef struct C02Ac C02Ac;

typedef struct {
    union { u64 x0; struct { u32 lo; C02Ac *x4; } w; } u;
    u64 x8;
} C02It;

typedef struct {
    u8 pad0[8];
    f32 *x8;
} C02Fx;

struct C02Ac {
    u32 x0;
    u8 pad4[0x6c - 4];
    C02Ab *x6c;
    u8 pad70[0x88 - 0x70];
    u32 x88;
    u8 pad8c[0x98 - 0x8c];
    void *x98;
    u8 pad9c[0x130 - 0x9c];
    C02Kd *x130;
    u8 pad134[0x148 - 0x134];
    C02Ex *x148;
    u8 pad14c[0x17c - 0x14c];
    u16 x17c;
};

extern u32 D_002C5958_550a0 __asm__("D_002C5958");
#define D_002C5958 D_002C5958_550a0
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
extern u8 D_002E3190[];
#define D_00F20000 ((s32 (*)(s32, void *)) D_00F20000)
s32 func_001349d0(C02Ac *, C02It *);
C02It *func_00134928(C02Ac *);
void func_001350d0(C02It *);
s32 func_001347f0(C02Ac *, C02It *);
#define func_00154e38 ((s32 (*)(C02Ac *, s32, C02It *, s32)) func_00154e38)
s32 func_00141468(C02Ac *, s32);
void func_0013aaa0(void);
void func_001ea498(s32);
#define func_00153f88 ((void (*)(C02Ac *)) func_00153f88)
void func_00147790(s32);
void func_001586a8(s32);
void func_00141608(C02Ac *, s32);
s32 func_00132f20(s32);
C02Fx *func_00148768(s32, s32, C02Ac *, s32, f32);
f32 func_00132f00(C02Ac *);
s32 func_0013c318(s32);
void func_00241948(s32, s32);
void func_00137330(void *, C02Ac *, s32);
#define func_00157a30 ((void (*)(C02Ac *, s32, s32)) func_00157a30)
void *memset(void *, s32, u32);

void func_001550a0(C02Ac *o, s32 arg1)
{
    C02It *it;
    s32 hp;
    s32 max;
    s32 lock;
    s32 best;
    s32 hit;
    s32 k;
    s32 n;
    s32 h;
    C02Fx *fx;
    f32 f;
    f32 r;
    f32 *v;

    it = NULL;
    lock = 0;
    best = -1;
    hit = 0;
    hp = o->x6c->x3c;
    max = hp;
    for (;;) {
        if (it != NULL) {
            func_001350d0(it);
        }
        it = func_00134928(o);
        if (it == NULL) {
            break;
        }
        if ((s32)(it->u.x0 >> 5) & 1) continue;
        if (o->x0 & 0x200) continue;
        if ((o->x6c->x0 >> 2) & 1) continue;
        hp = func_001349d0(o, it);
        if (o->x88 & 0x20) continue;
        if (hp <= 0) {
            if (o->x130->x4c == 0) {
                if (((D_002C5958 >> 13) & 1) && ((*(u32 *)&D_00304B78) & 0xf) == 11) {
                    D_00F20000(4, o);
                    hp = func_00141468(o, o->x6c->x40);
                    func_0013aaa0();
                } else if (!((o->x6c->x0 >> 2) & 1)) {
                    o->x6c->x0 |= 4;
                    lock = 1;
                }
            } else if ((D_002C5958 >> 17) & 1) {
                func_00141468(o, 1);
            } else {
                o->x88 |= 0x10;
            }
        }
        if ((u32)(((s32)(it->x8 >> 38) & 0xf) - 11) < 2 && o->x130->x4c != 0 && it->u.w.x4 != NULL
            && it->u.w.x4 != o && it->u.w.x4->x130->x4c < 10) {
            func_00157a30(o, 23, 0);
        }
        if (lock) {
            k = 4;
        } else {
            k = func_001347f0(o, it);
        }
        if ((o->x0 & 0x1000080) || ((D_002E31A8 >> 1) & 1)) {
            if (k != 6) {
                if (k != 7) continue;
            }
        }
        if (best < k) {
            if (k != 0) {
                if (func_00154e38(o, k, it, arg1)) {
                    hit = 1;
                }
            }
            best = k;
        }
    }
    if (lock) {
        func_001ea498(o->x17c);
        memset(D_002E3190, 0, 12);
        func_00157a30(o, 2, 0);
        return;
    }
    func_00153f88(o);
    if (best < 0) return;
    if (o->x130->x4c == 0) {
        switch (best) {
        case 3:
            func_00147790(1);
            func_001586a8(13);
            break;
        case 4:
        case 5:
            func_00147790(0);
            func_001586a8(13);
            break;
        case 6:
            func_00147790(6);
            break;
        case 7:
            func_00147790(5);
            break;
        }
        memset(D_002E3190, 0, 12);
    }
    if (hp < max) {
        n = (s32)(o->x148->x170 >> 33) & 7;
        if (n > 0) {
            func_00141608(o, (f32)(max - hp) * (f32)n);
        }
        hit = 1;
    }
    if ((o->x88 & 8) && hit) {
        fx = func_00148768(func_00132f20(6), 5, o, 0x8002, 0.0f);
        f = func_00132f00(o);
        v = fx->x8;
        v[2] = f;
        v[1] = f;
        v[0] = f;
    }
    h = func_0013c318(o->x130->x4c);
    if (h >= 0) {
        r = (f32)hp / (f32)max;
        if (r < 1.0f) {
            func_00241948(h, r < 0.5f ? 2 : r < 0.7999999523162842f ? 1 : 0);
        }
    }
    if (hp <= 0) {
        func_00157a30(o, 2, 0);
    } else if (o->x130->x4c != 0 && (n = (f32)o->x6c->x40 * 0.5f) < max && n >= hp) {
        func_00157a30(o, 20, 0);
    } else {
        switch (best) {
        case 3:
            func_00157a30(o, 0, 0);
            break;
        case 4:
        case 5:
            func_00157a30(o, 1, 0);
            break;
        }
    }
    if (o->x98 != NULL) {
        func_00137330(o->x98, o, -3);
    }
}
#undef D_002C5958
#undef D_00F20000
#undef func_00154e38
#undef func_00153f88
#undef func_00157a30
