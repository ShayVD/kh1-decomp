/* The point list D_00551600, without strict aliasing (docs/modules.md
 * "Session 52"): func_00156768 finds the nearest point to a position,
 * func_001568e8, func_001562d0 / func_001563e0 / func_001564e0.  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00150000_h35.h"
#include "data/pieces/D_00304BE8_s.h"
#include "platform/math.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"

/* func_001562d0 (from hand/nostrict/text_00150000_h35.c). */
void func_002675a8(void *, void *);
void func_00267560(void *, void *, f32);
typedef struct { f32 x, y, z, w; } Vec154768;
typedef struct {
    u8 pad[0x2A0];
    u8 x2A0[0x10];
    u8 x2B0[4];
    s32 w2B4;
    u8 pad2b8[4];
    f32 f2BC;
    f32 f2C0;
    u8 pad2c4[4];
    s32 w2C8;
    u8 pad2cc[4];
    s32 w2D0;
    u8 pad2d4[0xC];
    u8 x2E0[0x10];
} Obj1562d0;
f32 func_001427d0(void *, void *);
void func_001166e8(void *);
/* ---- func_001562d0 ---- */
s32 func_001562d0(Obj1562d0 *a, Vec154768 *b) {
    f32 lim = func_001427d0(a, a->x2A0);
    f32 r = b->w + a->f2C0;
    while (r > 0.0f) {
        func_00267560(a->x2B0, b, r < lim ? r : lim);
        a->w2B4 = 0;
        a->f2BC = 1.0f;
        a->w2C8 &= ~1;
        func_001166e8(a->x2A0);
        if (a->w2D0 & 1) return 1;
        r -= lim;
        func_002675a8(a->x2A0, a->x2E0);
    }
    return 0;
}

/* func_001563e0 (from hand/nostrict/text_00150000_h35.c). */
s32 func_001563e0(Obj1562d0 *a, Vec154768 *b) {
    f32 lim = func_001427d0(a, a->x2A0);
    f32 r = b->w + a->f2C0;
    while (r > 0.0f) {
        func_00267560(a->x2B0, b, r < lim ? r : lim);
        a->w2B4 = 0;
        a->f2BC = 1.0f;
        a->w2C8 |= 1;
        func_001166e8(a->x2A0);
        if (!(a->w2D0 & 1)) return 1;
        r -= lim;
        func_002675a8(a->x2A0, a->x2E0);
    }
    return 0;
}

/* func_001564e0 (from hand/nostrict/text_00150000_h58.c). */
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
typedef struct Actor_564e0 { ACT_BODY(S144) } Act;
extern f32 D_002BBDFC;
s32 func_0014f600(void *);
void func_00121fc4(void *, void *);
s32 func_0014f5c8(void *);
f32 powf(f32, f32);
#define func_001562d0 ((s32 (*)(void *, void *)) func_001562d0)
#define func_001563e0 ((s32 (*)(void *, void *)) func_001563e0)
/* ---- func_001564e0 ---- */
void func_001564e0(Act *a, V4 *o) {
    V4 v;
    V4 w;
    f32 *dt = &D_002BBDFC;
    func_00267560(&v, &a->x3f0, a->x3f0.w * *dt);
    a->x3f0.w *= powf(0.7999999523162842f, *dt);
    v.y = 0.0f;
    if (a->x70 == 17) {
        func_00121fc4(&w, &v);
        if (!func_001563e0(a, &w)) func_002675a8(o, &v);
    } else if (func_0014f5c8(a) || func_0014f600(a)) {
        o->x = v.x;
        o->z = v.z;
    } else {
        func_00121fc4(&w, &v);
        if (!func_001562d0(a, &w)) func_002675a8(o, &v);
    }
    if (a->x3f0.w < 1.0f) a->x88 &= ~0x40;
}
#undef func_001562d0
#undef func_001563e0
#undef ACT_BODY

/* func_00156768 (from hand/nostrict/text_00150000_h58.c). */
void func_00267530(void *, void *, void *);
f32 func_00267390(void *, void *);
typedef struct { u8 pad[0x60]; } Sub768;
typedef struct { union { u64 d; struct { u8 b0, n; } s; } u; u8 pad8[8]; V4 pos; u8 pad20[0x10]; Sub768 sub[1]; } Node768;
typedef struct { Node768 *p; u8 pad4[0xc]; V4 v; f32 d; s32 idx; } Out768;
extern Node768 *D_00551600;
s32 func_001566d8(Sub768 *, V4 *);
/* ---- func_00156768 ---- */
/* ---- func_001568e8 (needs func_00156768 defined above) ---- */
Node768 *func_00156768(V4 *pos, Out768 *o) {
    Node768 *p = D_00551600;
    s32 idx;
    s32 i;
    Sub768 *s;
    V4 d;
    f32 dist;
    o->p = 0;
    o->d = 0.0f;
    o->idx = 0;
    for (idx = 1; p->u.s.b0; idx++) {
        if (!(p->u.d & 0x10000)) {
            func_00267530(&d, pos, &p->pos);
            dist = func_00267390(&d, &d);
            if (p->u.s.n) {
                for (i = 0; i < p->u.s.n; i++) {
                    if (func_001566d8(&p->sub[i], pos)) {
                        o->p = p;
                        func_002675a8(&o->v, &d);
                        o->d = PlatSqrtf(dist);
                        o->idx = idx;
                        return p;
                    }
                }
            } else if (!o->p || dist < o->d) {
                o->p = p;
                func_002675a8(&o->v, &d);
                o->d = dist;
                o->idx = idx;
            }
        }
        p = (Node768 *)((u8 *)p + p->u.s.n * 0x60 + 0x30);
    }
    o->d = PlatSqrtf(o->d);
    return o->p;
}

/* func_001568e8 (from hand/nostrict/text_00150000_h58.c). */
void func_00267518(void *, void *, void *);
typedef union { u32 w; struct { u32 b0:1; u32 b1:1; u32 p2:14; u32 b16:1; u32 p17:6; u32 b23:1; u32 b24:1; u32 b25:1; u32 p26:6; } b; } F5958;
extern F5958 D_002C5958;
typedef struct { u8 x0; u8 pad1[7]; f32 x8; f32 xc; u8 pad10[0x10]; f32 x20[3]; f32 x2c_; } B4Q68;
typedef struct { u8 pad[0x160]; f32 x160[4]; } B4H160;
typedef struct B4A68 {
    u8 pad0[0x50]; f32 x50[4]; u8 pad60[0x98 - 0x60]; struct B4A68 *x98; u8 pad9c[0xc0 - 0x9c]; f32 xc0[4];
    u8 padd0[0x148 - 0xd0]; B4H160 *x148;
} B4A68;
extern u32 D_002C5978;
void func_002673b8(void *, void *);
void func_00267370(void *, void *, void *);
void func_00267e90(void *, void *, f32);
f32 sinf(f32);
#define D_002C5958 (*(u32 *)&D_002C5958)
/* ---- func_001568e8 (needs func_00156768 defined above) ---- */
void func_001568e8(B4A68 *e, f32 *out) {
    f32 buf[12];
    f32 d[4];
    f32 c[4];
    B4Q68 *q;
    f32 sp;
    f32 tgt;
    f32 cur;
    f32 t;
    s32 r;
    f32 f;
    func_002675a8(out, (*(f32 (*)[0x4])&D_002C58B0));
    if (!D_00551600) return;
    if ((D_002C5958 >> 15) & 1) return;
    if ((D_002C5978 >> 13) & 1) return;
    if (!e->x148) return;
    if (!e->x98) q = (B4Q68 *)func_00156768((V4 *)e->x50, (Out768 *)buf);
    else q = (B4Q68 *)func_00156768((V4 *)e->x98->x50, (Out768 *)buf);
    if (!q) {
        if (e->x148->x160[3] == 0.0f) return;
        func_002675a8(d, e->x148->x160);
        tgt = 0.0f;
        sp = D_002BBDFC * 0.199999988079071044921875f;
    } else {
        sp = q->x2c_ * D_002BBDFC;
        tgt = q->xc;
        switch (q->x0) {
        case 1:
            func_002675a8(d, q->x20);
            break;
        case 2:
            func_00267530(d, q->x20, e->x50);
            func_002673b8(d, d);
            break;
        }
        if (0.0f < q->x8) {
            f = 1.0f - buf[8] / q->x8;
            if (!(0.0f < f)) f = 0.0f;
            tgt *= sinf(f * 3.1415928f * 0.5f);
        }
    }
    func_00267560(d, d, sp);
    func_00267518(d, e->x148->x160, d);
    cur = e->x148->x160[3];
    if (cur < tgt) {
        cur += sp;
        if (tgt < cur) cur = tgt;
    } else if (tgt < cur) {
        cur -= sp;
        if (cur < 0.0f) cur = 0.0f;
    }
    func_002673b8(d, d);
    d[3] = 1.0f;
    func_00267560(e->x148->x160, d, cur);
    func_00267560(out, e->x148->x160, D_002BBDFC);
    if (func_0014f5c8(e)) return;
    if (func_0014f600(e)) {
        out[1] = 0.0f;
        return;
    }
    out[1] = 0.0f;
    t = out[3];
    func_002673b8(out, out);
    func_00267370(c, e->xc0, out);
    func_002673b8(c, c);
    func_00267370(out, c, e->xc0);
    func_002673b8(out, out);
    func_00267e90(out, out, t);
}
#undef D_002C5958

