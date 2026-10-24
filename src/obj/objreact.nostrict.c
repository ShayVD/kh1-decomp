/* An object's reactions to commands and hits: the reaction handlers that
 * read the tuning block *D_00308CDC (func_00138a78, func_00138c30,
 * func_00139240 picks a reaction motion, func_00139840), the message loop
 * func_00139da8, the per-state update func_0013a0f0, and the nearest target
 * within a range and level (func_0013a440). Flag mode: nostrict (the other
 * modes are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_004F.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00120000_h54.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_00304AD8.h"
#include "data/pieces/D_00304B84.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_002E3170.h"
#include "data/pieces/D_002E319C.h"
#include "data/pieces/D_002E31A0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E2780.h"
#include "data/types/nostrict_text_00120000_s6_05_p.h"
#include "data/pieces/D_002E3168.h"
#include "data/pieces/D_002C5960.h"
#include "data/types/nostrict_text_00120000_s6_05.h"
#include "data/types/nostrict_text_00130000_h32.h"

/* func_00138a78 (from hand/nostrict/text_00120000_h54.c). */
typedef FVec4 V4;
typedef struct { u8 p0[4]; s32 *rot; u8 p8[4]; f32 *scl; } R3;
extern R3 *func_00147ed8(s32, s32, s32, f32 *);
extern void func_001315c0(void *, s32, f32 *, f32);
typedef FMtx4 Mtx;
extern void func_002672f8(V4 *, Mtx, V4 *);
extern void func_00267518(V4 *, V4 *, V4 *);
extern f32 atan2f(f32, f32);
typedef struct { u8 p0[2]; u16 f2; f32 f4; u8 p8[4]; f32 fc; f32 f10; } R24;
typedef struct { u8 p0[6]; u8 f6; u8 p7[0x18 - 7]; R24 *f18; } T24;
typedef struct { u8 p0[0x134]; T24 *f134; u8 p138[0x3a8 - 0x138]; u32 f3a8; } E24;
typedef struct { u8 p0[0x10]; f32 f10; f32 f14; f32 f18; u8 p1c[0x34 - 0x1c]; s32 f34; s32 f38; } P24;
extern void func_00267810(Mtx, Mtx, f32);
extern void func_00267768(Mtx, Mtx, f32);
extern f32 func_00176850(void);
void func_00138a78(E24 *e, P24 *a) {
    Mtx m;
    V4 v;
    V4 o;
    T24 *t;
    R24 *r;
    u32 msk;
    s32 k;
    if (!a->f34 || a->f38 < 0) return;
    func_00267810(m, D_002C58D0, atan2f(a->f10, a->f18));
    func_00267768(m, m, func_00176850() * 3.1415928f - 1.5707964f);
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 1.0f;
    v.w = 1.0f;
    func_002672f8(&v, m, &v);
    k = (s32)(func_00176850() * (f32)e->f134->f6);
    while (e->f3a8 & (1 << k)) k = (k + 1) % e->f134->f6;
    r = &e->f134->f18[k];
    func_001315c0(e, r->f2, (f32 *)&o, r->f4);
    v.x *= r->fc;
    v.y *= r->f10;
    v.z *= r->fc;
    func_00267518(&o, &o, &v);
    func_00147ed8(a->f34, a->f38, -10000, (f32 *)&o);
}

/* func_00139240 (from hand/nostrict/text_00120000_s6_05.c). */
void func_002675a8(f32 *, f32 *);
typedef struct { u64 f0; u8 p8[8]; f32 f10[2]; f32 f18; } E39;
typedef struct { u8 p0[0x20]; f32 f20[3]; f32 f2c; f32 f30[4]; u8 p40[0x88-0x40]; u32 f88; u8 p8c[0x150-0x8c]; f32 f150; u8 p154[0x3e4-0x154]; f32 f3e4; u8 p3e8[2]; u16 f3ea; } O39;
extern s32 func_0014f600(O39 *);
extern s32 func_00130040(O39 *, s32);
extern void func_00139170(O39 *, E39 *);
extern f32 func_00267390(f32 *, f32 *);
extern s32 func_00130340(O39 *, s32, f32);
extern void *func_00130578(O39 *, s32, f32);
extern void func_00137688(O39 *, f32);
extern void func_00138a20(O39 *, f32, f32 *);
void func_00139240(O39 *o, E39 *e, s32 k, f32 a, f32 b, f32 c) {
    f32 ang;
    if (!k) k = func_0014f600(o) ? 92 : 82;
    if (!func_00130040(o, k)) {
        func_00139170(o, e);
        return;
    }
    o->f3ea = k;
    if (func_00267390(o->f30, e->f10) < 0.0f) {
        func_00130340(o, o->f3ea | 0x1000000, 0.0f);
        func_00130578(o, o->f3ea + 1, 0.0f);
        ang = atan2f(-e->f10[0], -e->f18);
    } else {
        func_00130340(o, (o->f3ea + 5) | 0x1000000, 0.0f);
        func_00130578(o, o->f3ea + 6, 0.0f);
        ang = atan2f(e->f10[0], e->f18);
    }
    func_00137688(o, ang);
    o->f150 = ang;
    func_002675a8(o->f20, e->f10);
    o->f2c = b;
    func_00138a20(o, a, o->f20);
    if (!(o->f88 & 2)) o->f3e4 = c;
    e->f0 |= 2;
}

/* func_001395d8 (from hand/nostrict/text_001395d8_s7_w37.c). */
typedef struct {
    u8 pad0[0x20];
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2c;
    u8 pad30[0x70 - 0x30];
    s32 x70;
    u8 pad74[0x164 - 0x74];
    s32 x164;
    u8 pad168[0x3d4 - 0x168];
    f32 x3d4;
    u8 pad3d8[0x404 - 0x3d8];
    f32 x404;
    u8 pad408[0x480 - 0x408];
    f32 x480;
} O95;
extern f32 D_002BBDFC;
void func_0014f658(O95 *, s32);
#define func_00130340 ((s32 (*)(O95 *, s32, f32)) func_00130340)
#define func_00130578 ((void *(*)(O95 *, s32, f32)) func_00130578)
void func_001395d8(O95 *o) {
    f32 f;
    f32 g;
    if ((u32)(o->x70 - 22) < 2) {
        f = o->x404 - D_002BBDFC;
        o->x404 = f;
        if (f > 60.0f) {
            o->x24 = 1.0f;
            o->x2c = 40.0f;
            o->x20 = 0.0f;
            o->x28 = 0.0f;
            g = (f - 60.0f) / 15.0f;
            o->x480 = g * 0.9f + 0.1f;
        } else if (f > 0.0f) {
            o->x2c = 0.0f;
            o->x480 = 0.1f;
            if (o->x70 == 22 && o->x3d4 > 0.0f) {
                o->x2c = 40.0f;
                o->x404 = f + D_002BBDFC;
            }
        } else {
            func_00130340(o, 103, 0.0f);
            func_00130578(o, 0x40000000, 8.0f);
            switch (o->x70) {
            case 22:
                func_0014f658(o, 0);
                break;
            case 23:
                func_0014f658(o, 4);
                break;
            }
        }
    } else if (o->x164 == 102) {
        f32 h = o->x404 - D_002BBDFC;
        o->x404 = h;
        if (h > 60.0f) {
            g = (h - 60.0f) * 0.125f;
            o->x480 = g * 0.9f + 0.1f;
        } else if (h > 0.0f) {
            o->x480 = 0.1f;
        } else {
            func_00130340(o, 103, 0.0f);
            func_00130578(o, 0x40000000, 8.0f);
        }
    }
    if (o->x164 == 103) o->x480 += (1.0f - o->x480) * 0.3f;
}
#undef func_00130340
#undef func_00130578

/* func_00139cb8 (from hand/nostrict/text_00130000_h32.c). */
typedef struct W32Fig {
    u64 x0;
    u8 pad008[0x7C - 0x8];
    struct W32Fig *x7c;
    u8 pad080[0x144 - 0x80];
    s32 x144;
    u8 pad148[0x370 - 0x148];
    u64 x370;
} W32Fig;
typedef struct {
    u8 pad00[4];
    W32Fig *x4;
} W32Msg;
typedef struct {
    void *p;
    s32 n;
} W32Dsc;
extern u32 D_002C5958;
void func_0012bce0(s32 h, s32 a, s32 b, W32Dsc *d, s32 *r);
void func_001349d0(W32Fig *o);
void func_00139c28(W32Fig *o, W32Msg *m);
s32 func_00139cb8(W32Fig *o, W32Msg *m) {
    if ((o->x0 & 0x1000088) || ((s32)(o->x370 >> 51) & 1)) return 0;
    if (D_002C5958 & 0x4100000) return 0;
    if (m->x4) {
        o->x7c = (((s32)(m->x4->x370 >> 37) & 3) == 1) ? m->x4 : 0;
    }
    if (((s32)(o->x370 >> 48) & 1) && o->x144) {
        W32Dsc d[1];
        d[0].p = &m;
        d[0].n = 4;
        func_0012bce0(o->x144, 0, 1, d, 0);
    } else {
        func_001349d0(o);
    }
    func_00139c28(o, m);
    return 1;
}

/* func_0013a440 (from hand/nostrict/text_00130000_s8_w6.c). */
typedef struct { f32 x, y, z, w; } V4f;
typedef union {
    u64 x;
    struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b;
} B370;
typedef struct Ea4 Ea4;
struct Ea4 {
    u32 flags;
    u8 pad4[0xc];
    V4f x10;
    u8 pad20[0x74 - 0x20];
    Ea4 *x74;
    u8 pad78[4];
    Ea4 *x7c;
    s32 x80;
    u8 pad84[4];
    u32 x88;
    u8 pad8c[0x370 - 0x8c];
    B370 x370;
};
typedef struct { s32 d; Ea4 *e; } Pa4;
void *func_00122048(s32, s32);
void func_001220b8(void *);
Ea4 *func_00123158(Ea4 *, Ea4 *);
s32 func_001375d8(Ea4 *);
void func_00267530(V4f *, V4f *, V4f *);
f32 func_00120bf8(V4f *);
void func_00250360(void *, s32, s32, void *);
s32 func_0013a430();
Ea4 *func_0013a440(Ea4 *o, s32 *w, f32 range, s32 lv) {
    V4f t;
    Pa4 *buf, *p;
    Ea4 *e = 0;
    s32 n, v;
    f32 d;
    buf = func_00122048(0x300, 4);
    p = buf;
    while ((e = func_00123158(o, e)) != 0) {
        if (e->x370.b.kind == 3) continue;
        if (!(e->flags & 0x8000)) continue;
        if (e->x88 & 0x20) continue;
        if (func_001375d8(e)) continue;
        func_00267530(&t, &e->x10, &o->x10);
        d = func_00120bf8(&t);
        if (e->x80 < lv && d < range) {
            p->d = d;
            p->e = e;
            p++;
        }
    }
    n = p - buf;
    func_00250360(buf, n, 8, func_0013a430);
    if (n > 0) e = buf[0].e;
    v = func_00176850() * 100.0f;
    v -= w[0];
    if (v >= 0) {
        v -= w[1];
        if (v < 0) {
            if (n >= 2) e = buf[1].e;
        } else {
            v -= w[2];
            if (v < 0) {
                if (n > 0) e = buf[n - 1].e;
            } else {
                v -= w[3];
                if (v < 0) {
                    if (o->x74) {
                        func_00267530(&t, &o->x74->x10, &o->x10);
                        if (func_00120bf8(&t) < range) e = o->x74;
                    }
                } else {
                    if (o->x7c) {
                        func_00267530(&t, &o->x7c->x10, &o->x10);
                        if (func_00120bf8(&t) < range) e = o->x7c;
                    }
                }
            }
        }
    }
    func_001220b8(buf);
    return e;
}

