/* Prizes, the HP / MP balls and munny an enemy drops (a guess from the
 * code): the drop table of an object (func_00144e88, func_00144eb0 spawns
 * d->cnt[i] of each of 7 kinds), the 0x3000-byte pool D_0052EB60 with its
 * per-prize records D_0035C710 and free list D_0052EB50 / D_0052EB58
 * (func_00146188 spawns one, func_00145ce8 updates one), the ground probe
 * D_00531B60, the drop rate D_00306844 / D_00306848, and an object's
 * attached effect (func_00145188, func_00145240). Flag mode: nostrict (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/pieces/D_0035C710.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_00304DB0.h"
#include "data/pieces/D_003044A0.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00130000_b03_p3.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00130000_b03_p2.h"
#include "data/types/nostrict_text_00130000_b03.h"
#include "data/pieces/D_002C58D0.h"

/* func_00144eb0 (from hand/nostrict/text_00140000_h56.c). */
typedef struct { u8 cnt[7]; struct { u8 pct; u8 id; } drop[3]; } DropDef;
extern f32 D_00306844;
extern f32 D_00306848;
extern s32 D_002C5C4C;
DropDef *func_00144e88(void *);
void func_00146188(s32, f32 *, s32);
void func_001515d0(u8, void *, s32);
f32 func_00176850(void);
void func_00144eb0(void *o, void *pos) {
    DropDef *d;
    s32 i, j, n, c;
    s32 flag = D_002C5C4C != 0;

    d = func_00144e88(o);
    for (i = 0; i < 7; i++) {
        n = d->cnt[i] * D_00306844;
        for (j = 0; j < n; j++) {
            func_00146188(i, pos, flag);
        }
    }
    for (i = 0; i < 3; i++) {
        c = d->drop[i].pct * D_00306848;
        if ((s32)(func_00176850() * 100.0f) < c) {
            func_001515d0(d->drop[i].id, pos, flag);
        }
    }
}

/* func_00145080 (from hand/nostrict/text_00140000_h33.c). */
extern Snd *D_0052EB58;
extern f32 D_00306840;
void func_00150de0(s32);
void func_00145080(s32 on, s32 n) {
    f32 f = n;
    Snd *p;
    D_00531B64 = on;
    D_00306840 = f;
    p = D_0052EB58;
    if (on) {
        for (; p; p = p->next) {
            if (p->st < 2) {
                p->st = 4;
                p->f18 = f;
            }
        }
    } else {
        for (; p; p = p->next) {
            if (p->st == 4) {
                p->st = 5;
                p->f18 = f;
            }
        }
    }
    func_00150de0(on);
}

/* func_00145188 (from hand/nostrict/text_00140000_h56.c). */
extern u32 D_002C5958;
#define FLD(p, T, off) (*(T *)((u8 *)(p) + (off)))
s32 func_00148768(s32, s32, void *, s32, f32);
void func_0011d1e0(s32, s32, void *, s32);
void func_00145188(void *a, f32 f) {
    void *t = FLD(FLD(a, void *, 0x148), void *, 0x154);
    if ((t == 0 || *FLD(t, u8 *, 0x10) != 0) && !(D_002C5958 & 0x104000)) {
        FLD(FLD(a, void *, 0x148), s32, 0x154) = func_00148768(D_00350CE0, 0x16, a, 0x8003, 0.0f);
        if (a == D_002E26A0[0]) {
            func_0011d1e0(0xA8, FLD(a, s32, 4) + 1, (u8 *)a + 0x10, 0);
        }
    }
    FLD(FLD(a, void *, 0x148), f32, 0x158) = f;
}
#undef FLD

/* func_001452a0 (from hand/nostrict/text_00140000_h33.c). */
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
void func_00176310(Eff154 *);
f32 func_00121b08(f32);
void func_0011d3c8(s32, s32, s32);
void func_001452a0(ObjF3 *o) {
    Eff154 *e = o->p148->p154;
    s32 k;
    if (e == 0) return;
    k = e->w14 & 3;
    if (k != 1) {
        o->p148->p154 = 0;
        return;
    }
    if (!(o->flags & 1)) {
        func_00176310(e);
        o->p148->p154 = 0;
        func_0011d3c8(168, o->w4 + 1, 60);
        return;
    }
    o->p148->f158 = func_00121b08(o->p148->f158);
    if (!(o->p148->f158 <= 0.0f) && !(D_002C5958 & 0x104000)) return;
    *o->p148->p154->p10 = k;
    func_0011d3c8(168, o->w4 + 1, 120);
}

/* func_001453a8 (from hand/nostrict/text_00130000_s6_na_3.c). */
typedef struct { f32 x, y, z, w; } V4f_453a8;
typedef struct { u8 pad[0x4c]; u16 x4c; } T5i;
typedef struct {
    u32 flags;
    u8 pad4[0x50 - 4];
    V4f_453a8 x50;
    u8 pad60[0x70 - 0x60];
    s32 x70;
    u8 pad74[0x88 - 0x74];
    u32 x88;
    u8 pad8c[0x130 - 0x8c];
    T5i *info;
} T5o;
void func_001315c0(T5o *o, s32 k, void *buf, f32 f);
void func_00267530(V4f_453a8 *, V4f_453a8 *, V4f_453a8 *);
s32 func_0013c968(s32, s32);
f32 func_00267390(V4f_453a8 *, V4f_453a8 *);
s32 func_001453a8(T5o *o, V4f_453a8 *p, s32 mode) {
    V4f_453a8 t;
    f32 lim;
    s32 n;
    if (!(o->flags & 0x8000) || (o->x88 & 0x20)) return 0;
    switch (mode) {
    case 1:
        func_001315c0(o, 0x8003, &t, 0.0f);
        func_00267530(&t, &t, p);
        lim = 14400.0f;
        break;
    case 2:
        func_001315c0(o, 0x8003, &t, 0.0f);
        func_00267530(&t, &t, p);
        lim = 40000.0f;
        break;
    case 0:
    default:
        func_00267530(&t, p, &o->x50);
        t.y = fabsf(t.y);
        if (o->x70 == 33) t.y -= 50.0f;
        if (t.y > 30.0f) return 0;
        t.y = 0;
        lim = 6400.0f;
        break;
    }
    n = func_0013c968(5, o->info->x4c);
    if (n > 0) {
        lim = 40000.0f;
        if (n != 1) lim = 160000.0f;
    }
    if (lim < func_00267390(&t, &t)) return 0;
    return 1;
}

/* func_00145528 (from hand/nostrict/text_00130000_b03.c). */
void func_002675a8(f32 *, f32 *);
typedef struct {
    u8 pad0[0x10];
    union {
        u64 x;
        struct { u16 lo; u16 x12; u16 x14; u8 x16; u8 x17; } s;
        struct { u64 b0:2; u64 kind:16; u64 rest:46; } b;
    } x10;
    f32 x18;
    s32 x1c;
    f32 x20[4];
} B3Pj;
extern B3Col *D_00531B60;
void func_00116660(B3Col *);
void func_001166e8(B3Col *);
void func_00121fc4(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_001473a8(s32, s32, f32 *);
f32 fabsf(f32);
#define func_00267530 ((void (*)(f32 *, f32 *, f32 *)) func_00267530)
void func_00145528(B3Pj *o, f32 *v) {
    f32 t[4];
    f32 f;

    if (o->x10.s.x12) {
        o->x10.s.x12--;
        return;
    }
    f = D_00304DB0.b3PjInf[o->x10.s.x14].x0;
    func_00116660(D_00531B60);
    D_00531B60->x20 = 55.0f;
    D_00531B60->x24 = 60.0f;
    func_002675a8(D_00531B60->x0, v);
    D_00531B60->x0[1] += f;
    D_00531B60->x28 = 33;
    if (o->x10.x & 0x10) {
        func_002675a8(D_00531B60->x10, (*(f32 (*)[0x4])&D_002C58A0));
        o->x10.x &= ~0x10;
    } else {
        func_00121fc4(t, o->x20);
        if (45.0f < t[3]) func_00267560(o->x20, t, 45.0f);
        func_002675a8(D_00531B60->x10, o->x20);
        D_00531B60->x10[3] = 1.0f;
    }
    func_001166e8(D_00531B60);
    if (0.0f <= o->x20[1] && !(D_00531B60->x30 & 1)) {
        if (5.0f < o->x20[1]) {
            o->x20[1] *= -0.8f;
            if (++o->x10.s.x17 < 3) func_001473a8(D_00304DB0.b3PjInf[o->x10.s.x14].xc, 0, D_00531B60->x40);
        } else {
            func_002675a8(o->x20, (*(f32 (*)[0x4])&D_002C58A0));
            if (D_00531B60->x2c == -1) {
                o->x10.s.x16 = 1;
            } else {
                o->x10.s.x12 = 30;
            }
        }
    } else {
        func_00267530(t, D_00531B60->x40, D_00531B60->x0);
        if (0.1f < fabsf(t[0] - o->x20[0])) o->x20[0] = -o->x20[0];
        if (0.1f < fabsf(t[2] - o->x20[2])) o->x20[2] = -o->x20[2];
    }
    func_002675a8(v, D_00531B60->x40);
    v[1] -= f;
    v[3] = 1.0f;
    o->x20[1] += 3.0f;
    o->x20[0] *= 0.95f;
    o->x20[2] *= 0.95f;
    if (0.0f < o->x20[1]) o->x10.x |= 2;
}
#undef func_00267530

/* func_00145858 (from hand/nostrict/text_00140000_h56.c). */
typedef struct { f32 p[4]; f32 d[4]; f32 r20; f32 r24; s32 w28; u8 pad2c[0x14]; f32 out[4]; } Hit;
typedef struct {
    u8 pad0[0x10];
    union {
        u64 d;
        struct { u16 h10; u16 h12; u16 idx; u8 b16; u8 b17; } s;
        struct { u64 b0:2; u64 mode:2; u64 f4:1; u64 rest:59; } b;
    } u;
    f32 f18;
    s32 w1c;
    f32 vel[4];
} Bo;
#define func_00267530 ((void (*)(f32 *, f32 *, f32 *)) func_00267530)
#define D_00531B60 (*(Hit *(*)) &D_00531B60)
#define func_00116660 ((void (*)(Hit *)) func_00116660)
#define func_001166e8 ((void (*)(Hit *)) func_001166e8)
void func_00145858(Bo *o, f32 *pos) {
    f32 t[4];
    Hit **pp = &D_00531B60;
    f32 h = D_00304DB0.htTab[o->u.s.idx].h;

    func_00116660((*pp));
    (*pp)->r20 = 55.0f;
    (*pp)->r24 = 60.0f;
    func_002675a8((*pp)->p, pos);
    (*pp)->p[1] += h;
    func_00121fc4(t, o->vel);
    if (t[3] > 45.0f) {
        func_00267560(o->vel, t, 45.0f);
    }
    func_002675a8((*pp)->d, o->vel);
    (*pp)->d[3] = 1.0f;
    (*pp)->w28 = 33;
    func_001166e8((*pp));
    func_00267530(t, (*pp)->out, (*pp)->p);
    if (fabsf(t[0] - o->vel[0]) > 0.0999999940395355224609375f) {
        o->vel[0] = -o->vel[0];
    }
    if (fabsf(t[2] - o->vel[2]) > 0.0999999940395355224609375f) {
        o->vel[2] = -o->vel[2];
    }
    func_002675a8(pos, (*pp)->out);
    pos[1] -= h;
    pos[3] = 1.0f;
    if (o->vel[1] < 0.0f) {
        o->vel[1] += o->vel[3];
    } else {
        o->vel[3] += -0.05f;
        o->vel[1] += o->vel[3];
        if (o->vel[1] < 0.0f) {
            func_002675a8(o->vel, (*(f32 (*)[0x4])&D_002C58A0));
            o->u.s.b16 = 1;
        }
    }
    o->vel[0] *= 0.95f;
    o->vel[2] *= 0.95f;
    if (o->vel[1] > 0.0f) {
        o->u.d |= 2;
    }
}
#undef func_00267530
#undef D_00531B60
#undef func_00116660
#undef func_001166e8

/* func_00145aa0 (from hand/nostrict/text_00140000_h56.c). */
typedef struct { u8 pad[0xa0]; f32 va0[3]; f32 fac; f32 fb0; f32 fb4; f32 fb8; } Cam148;
typedef struct {
    u32 flags;
    u8 pad4[0x88 - 4];
    u32 w88;
    u8 pad8c[0x148 - 0x8c];
    Cam148 *c148;
    u8 pad14c[0x2d4 - 0x14c];
    f32 f2d4;
    u8 pad2d8[0x39e - 0x2d8];
    u8 b39e;
    u8 pad39f[0x3c0 - 0x39f];
    f32 v3c0[4];
} Pk;
void func_001ef7b0(s32);
void func_00141468(void *, s32);
void func_00141608(void *, s32);
void func_00244a10(void *, s32);
#define func_00267530 ((void (*)(f32 *, f32 *, f32 *)) func_00267530)
#define func_001315c0 ((void (*)(Pk *, s32, f32 *, f32)) func_001315c0)
#define func_001453a8 ((s32 (*)(void *, f32 *, s32)) func_001453a8)
void *func_00145aa0(Bo *o, f32 *pos) {
    f32 t[4];
    f32 d[4];
    s32 i;
    void *e;
    f32 h = D_00304DB0.htTab[o->u.s.idx].h;

    func_002675a8(t, pos);
    t[1] += h;
    for (i = 0; i < 3; i++) {
        e = D_002E26A0[i];
        if (e == 0) continue;
        if (!func_001453a8(e, t, (u16)(o->u.d >> 2) & 3)) continue;
        switch (o->u.s.idx) {
        case 0: func_001ef7b0(1); break;
        case 1: func_001ef7b0(5); break;
        case 2: func_001ef7b0(20); break;
        case 3: func_00141468(e, 1); break;
        case 4: func_00141468(e, 5); break;
        case 5: func_00141608(e, 2); break;
        case 6: func_00141608(e, 15); break;
        }
        func_001315c0(e, 0x8003, t, 0.0f);
        func_00267530(d, pos, t);
        func_00121fc4(o->vel, d);
        if (D_00304DB0.htTab[o->u.s.idx].f4 > 0.0f) {
            func_00145188(e, D_00304DB0.htTab[o->u.s.idx].f4);
        }
        if (D_00304DB0.htTab[o->u.s.idx].f10 > 0) {
            func_00244a10(e, D_00304DB0.htTab[o->u.s.idx].f10);
        }
        func_001473a8(D_00304DB0.htTab[o->u.s.idx].f8, 0, (f32 *)((u8 *)e + 0x50));
        return e;
    }
    return 0;
}
#undef func_00267530
#undef func_001315c0
#undef func_001453a8

/* func_00145ce8 (from hand/nostrict/text_00130000_b03.c). */
extern f32 D_002BBDFC;
typedef W8Ent35 B3PjE;
extern B3Pj D_0052EB60[];
extern f32 *D_00531B68;
void func_00267810(f32 *, f32 *, f32);
void func_002672f8(f32 *, f32 *, f32 *);
void func_00267e40(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
#define func_00145858 ((void (*)(B3Pj *, B3PjE *)) func_00145858)
#define func_00145aa0 ((s32 (*)(B3Pj *, B3PjE *)) func_00145aa0)
#define func_001315c0 ((void (*)(s32, s32, f32, f32 *)) func_001315c0)
s32 func_00145ce8(B3Pj *o) {
    f32 t[4];
    f32 u[4];
    f32 m[16];
    f32 s, r, a;
    B3PjE *e = &D_0035C710[o - D_0052EB60];

    switch (o->x10.s.x16) {
    case 0:
        switch ((u16)(o->x10.x >> 2) & 3) {
        case 0:
            func_00145528(o, e->v);
            break;
        case 1:
            func_00145858(o, e);
            break;
        case 2:
            o->x10.x |= 2;
            o->x10.s.x16 = 1;
            break;
        }
    case 1:
        if (o->x10.x & 2) {
            if ((o->x1c = func_00145aa0(o, e))) {
                o->x10.s.x16 = 2;
                o->x18 = 40.0f;
                break;
            }
        }
        if (0.0f < o->x18) {
            o->x18 -= D_002BBDFC;
            if (o->x18 <= 0.0f || (D_00531B68 && e->v[1] > D_00531B68[2])) {
                o->x10.s.x16 = 3;
                o->x18 = 12.0f;
            }
        }
        break;
    case 2:
        r = o->x18 / 40.0f;
        s = o->x20[3] * r;
        a = 30.0f / s;
        func_00267810(m, D_002C58D0[0], (a < 0.59341193735599518f) ? a : 0.59341193735599518f);
        func_002672f8(u, m, o->x20);
        func_00267e40(o->x20, u);
        func_00267e90(u, o->x20, s);
        func_001315c0(o->x1c, 0x8003, 0.0f, t);
        func_00267518(e->v, t, u);
        e->x10 = r;
        o->x18 -= D_002BBDFC;
        if (o->x18 <= 0.0f) {
            e->u.w &= ~0x100;
            return 4;
        }
        break;
    case 3:
        r = o->x18 / 12.0f;
        e->x10 = r;
        o->x18 -= D_002BBDFC;
        if (o->x18 <= 0.0f) {
            e->u.w &= ~0x100;
            return 4;
        }
        break;
    case 4:
        if (o->x18 < 0.0f) {
            e->u.w |= 0x200;
        } else {
            r = o->x18 / D_00306840;
            e->x10 = r;
        }
        o->x18 = o->x18 - 1.0f;
        break;
    case 5:
        e->u.w &= ~0x200;
        if (o->x18 < 0.0f) {
            e->x10 = 1.0f;
            o->x18 = 900.0f;
            o->x10.s.x16 = 0;
        } else {
            r = o->x18 / D_00306840;
            e->x10 = 1.0f - r;
            o->x18 = o->x18 - 1.0f;
        }
        break;
    }
    return 0;
}
#undef func_00145858
#undef func_00145aa0
#undef func_001315c0

/* func_001460b8 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { u8 pad[0x80]; s32 w80; } Blk;
extern Snd D_0052EB50;
Blk *func_00122048(s32, s32);
s32 func_0011f130(Snd *, s32);
void func_001220b8(Blk *);
#define D_00531B60 (*(Blk *(*)) &D_00531B60)
s32 func_001460b8(void) {
    Snd *p;
    Blk *b = func_00122048(160, 16);
    *(Blk *volatile *)&D_00531B60 = b;
    b->w80 = 1;
    if (func_0011f130(&D_0052EB50, 0) >= 205) {
        for (p = D_0052EB50.next; p; p = p->next) {
            if (p->st == 1) {
                p->st = 3;
                p->f18 = 12.0f;
                break;
            }
        }
    }
    func_001220b8(D_00531B60);
    return 0;
}
#undef D_00531B60

/* func_00146188 (from hand/nostrict/text_00140000_h56.c). */
typedef W8Ent35 Spr;
Bo *func_0011f090(void *, s32, void *);
extern Bo D_0052EB60_00146188[] __asm__("D_0052EB60");
#define D_0052EB60 D_0052EB60_00146188
extern u8 D_0052EB50_00146188[] __asm__("D_0052EB50");
#define D_0052EB50 D_0052EB50_00146188
void func_00146188(s32 id, f32 *pos, s32 mode) {
    Bo *b;
    Spr *e;

    b = func_0011f090(D_0052EB50, 0, func_00145ce8);
    if (b == 0) return;
    e = &D_0035C710[b - D_0052EB60];
    func_002675a8(e->v, pos);
    e->v[3] = 1.0f;
    e->u.id = id;
    e->x10 = 1.0f;
    e->x14 = 1.0f;
    e->u.b.f8 = 1;
    e->u.b.f10 = 1;
    e->u.b.f9 = 0;
    b->u.s.h10 = 0;
    b->u.b.mode = mode;
    b->u.b.f4 = 1;
    b->u.s.idx = id;
    b->u.s.b16 = 0;
    b->u.s.b17 = 0;
    b->vel[0] = func_00176850() * 40.0f - 20.0f;
    b->vel[2] = func_00176850() * 40.0f - 20.0f;
    b->f18 = 900.0f;
    b->w1c = 0;
    b->u.s.h12 = 0;
    switch (mode) {
    case 0:
        b->vel[1] = func_00176850() * 20.0f + -40.0f;
        break;
    case 1:
        {
            f32 r = func_00176850() * 10.0f;
            b->vel[3] = 1.0f;
            b->vel[1] = r + -20.0f;
        }
        break;
    case 2:
        b->f18 = -1.0f;
        break;
    }
}
#undef D_0052EB50
#undef D_0052EB60

/* func_00146380 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { f32 p; s32 id; } Drop;
typedef struct { s32 n[7]; Drop d[3]; } DropTbl;
#define func_00146188 ((void (*)(s32, s32, s32)) func_00146188)
#define func_001515d0 ((void (*)(s32, s32, s32)) func_001515d0)
void func_00146380(DropTbl *t, s32 a, s32 b) {
    s32 i, j, n;
    if (D_00531B64) return;
    for (i = 0; i < 7; i++) {
        n = t->n[i] * D_00306844;
        for (j = 0; j < n; j++) {
            func_00146188(i, a, b);
        }
    }
    for (i = 0; i < 3; i++) {
        f32 p = t->d[i].p * D_00306848;
        if (func_00176850() < p) {
            func_001515d0(t->d[i].id, a, b);
        }
    }
}
#undef func_00146188
#undef func_001515d0

