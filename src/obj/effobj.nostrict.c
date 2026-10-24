/* Effect objects: the 256 records D_00547C00 (0x3C bytes each) handed out
 * round-robin from D_0054B800 (func_00147c30), their tasks (func_00147d18,
 * func_001480d0, func_00148438), func_00148768 starts an effect on an
 * object, func_00147e08 sets one's rotation from a matrix, func_00148e98
 * frees them all. Flag mode: nostrict (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002E27C8.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0035C710.h"
#include "data/types/nostrict_text_00130000_b03_p3.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00130000_b03_p2.h"
#include "data/types/nostrict_text_00130000_b03.h"
#include "data/pieces/D_00304DB0.h"

/* func_00147b08 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { s16 h0; s16 h2; } Prc;
typedef struct { f32 m[4][4]; u8 buf[0x3C]; s32 w7c; s32 w80; s32 w84; } MdlBlk;
u8 D_0054C160[0x50] ALIGNED(32);  /* moved from hand/nostrict/text_00140000_h33.c (session 53) */
Prc *func_0011ef10(s32, void (*)(void));
void *func_00176488(s32, u8 *, s32, s32);
s32 func_001765f8(void *);
s32 func_00162368(s32, s32);
s32 func_001320a8(s32);
u8 *func_001623e0(s32);
void func_00147a68(void);
void *func_00147b08(s32 a, s32 b, s32 c) {
    s32 r;
    if (!func_00176488(a, D_0054C160, 0, 20000)) return 0;
    r = func_001765f8(D_0054C160);
    if (r >= 0) {
        MdlBlk *m = (MdlBlk *)(D_0054C160 - 0x40);
        r = func_00162368(c, r & 0xFFF);
        m->w80 = r;
        m->w7c = c;
        m->w84 = func_001320a8(b);
        PlatVu0CopyMatrix(m, func_001623e0(c) + (r << 6));
        func_0011ef10(0x21728, func_00147a68)->h2 = -1;
    }
    return D_0054C160;
}

/* func_00147d50 (from hand/nostrict/text_00140000_h33.c). */
typedef FVec4 V4f;
typedef struct { s32 x, y, z; } V3i;
typedef struct { V4f *pos; V3i *rot; } RotObj;
void func_00121a10(s32, V4f *);
void func_00147d50(RotObj *o, s32 m) {
    V4f r;
    func_00121a10(m, &r);
    o->rot->x = (u16)(s32)(r.x / 6.2831855f * 65536.0f);
    o->rot->y = (u16)(s32)(r.y / 6.2831855f * 65536.0f);
    o->rot->z = (u16)(s32)(r.z / 6.2831855f * 65536.0f);
}

/* func_00147e08 (from hand/nostrict/text_00140000_h33.c). */
void func_00121a78(V4f *, V4f *);
void func_00147e08(RotObj *o, V4f *m) {
    V4f r;
    func_00121a78(m, &r);
    o->rot->x = (u16)(s32)(r.x / 6.2831855f * 65536.0f);
    o->rot->y = (u16)(s32)(r.y / 6.2831855f * 65536.0f);
    o->rot->z = (u16)(s32)(r.z / 6.2831855f * 65536.0f);
    PlatVu0CopyVector(o->pos, m + 3);
}

/* func_00147ff0 (from hand/nostrict/text_00130000_s6_06.c). */
typedef struct { u8 pad[0xc]; f32 xc; } W606T7v;
typedef struct { u8 pad[0xc]; W606T7v *xc; u8 pad10[4]; u32 x14; } W606T7a;
typedef struct { u8 pad[0x14]; W606T7a *x14; u8 pad18[4]; f32 x1c; } W606T7o;
extern f32 D_002BBDFC;
void func_00176310();
s32 func_00147ff0(W606T7o *o) {
    W606T7a *a = o->x14;
    W606T7v *v;
    f32 f;
    if (a != 0) {
        if ((a->x14 & 3) == 1) {
            v = a->xc;
            f = v->xc - o->x1c * D_002BBDFC;
            if (!(f <= 0.0f)) goto st;
            func_00176310(a, o);
        } else {
            return 4;
        }
    }
    return 4;
st:
    v->xc = f;
    return 0;
}

/* func_001480d0 (from hand/nostrict/text_00130000_b03.c). */
typedef struct {
    u8 pad0[0x88];
    u32 x88;
    u8 pad8c[0x160 - 0x8c];
    union {
        struct { u64 b0:8; s64 b8:32; u64 b40:24; } f;
        struct { u32 lo; s32 hi; } w;
        u64 x;
    } x160;
    u8 pad168[0x370 - 0x168];
    u8 x370[3];
} C3Ob;
typedef struct {
    void *x0;
    u8 pad4[0xc - 0x4];
    f32 *xc;
    u8 pad10[0x14 - 0x10];
    u32 x14;
    u8 pad18[0x20 - 0x18];
    u8 *x20;
} C3Lk;
typedef struct {
    u32 x0;
    u8 x4;
    u8 pad5;
    s16 x6;
    u32 x8;
    f32 xc;
    f32 x10[4];
    f32 x20[4];
    f32 x30[12];
    f32 x60[4];
} C3D;
typedef struct {
    u8 pad0[0x10];
    C3Ob *x10;
    C3Lk *x14;
    u8 pad18[0x20 - 0x18];
    C3D *x20;
} C3S;
s32 func_00122ff8(C3Ob *);
void func_00121eb0(C3D *);
void func_001315c0(s32, s32, f32, f32 *);
void func_001318e8(C3Ob *, u32, f32 *);
#define func_00176310 ((void (*)(C3Lk *)) func_00176310)
#define func_00147e08 ((void (*)(C3Lk *, f32 *)) func_00147e08)
s32 func_001480d0(C3S *s) {
    s32 f = 0;
    C3D *d = s->x20;
    f32 *v;
    u32 m;
    s32 i;

    if (!s->x14 || (s->x14->x14 & 3) != 1) {
        s->x14 = 0;
        goto fail;
    }
    if (!func_00122ff8(s->x10)) goto fail;
    if (d->x6 == -1) {
        d->x6 = s->x10->x160.w.hi;
    } else if (d->x6 >= 0) {
        if (s->x10->x160.w.hi != d->x6) f = 1;
        else if (((s32)((s64)(s->x10->x160.x << 24) >> 32) & 1)) {
        fail:
            f = 1;
        }
    }
    if (f) {
        if (s->x14) func_00176310(s->x14);
        func_00121eb0(d);
        return 4;
    }
    if (s->x10->x88 & 1) s->x14->x20[0] |= 4;
    else s->x14->x20[0] &= ~4;
    if (d->x0 & 1) {
        for (i = 0; i < 3; i++) s->x14->xc[i] = s->x10->x370[i] * (1.0f / 128.0f);
    }
    if (s->x14->x14 & 0x10) return 0;
    if (d->x8 & 0x10000) {
        m = d->x8 & ~0x10000;
        switch (d->x4) {
        case 1:
            v = d->x20;
            func_001315c0((s32)s->x10, m, d->xc, v);
            PlatVu0AddVector(v, v, d->x10);
            PlatVu0CopyVector(s->x14->x0, v);
            break;
        case 2:
            v = d->x30;
            func_001318e8(s->x10, m, v);
            func_00147e08(s->x14, v);
            break;
        case 3:
            v = d->x30;
            func_001318e8(s->x10, m, v);
            func_001315c0((s32)s->x10, m, d->xc, d->x60);
            func_00147e08(s->x14, v);
            break;
        }
        func_00121eb0(d);
        return 4;
    }
    switch (d->x4) {
    case 1:
        v = d->x20;
        PlatVu0CopyVector(s->x14->x0, v);
        func_001315c0((s32)s->x10, d->x8, d->xc, v);
        PlatVu0AddVector(v, v, d->x10);
        break;
    case 2:
        v = d->x30;
        func_00147e08(s->x14, v);
        func_001318e8(s->x10, d->x8, v);
        break;
    case 3:
        v = d->x30;
        func_00147e08(s->x14, v);
        func_001318e8(s->x10, d->x8, v);
        func_001315c0((s32)s->x10, d->x8, d->xc, d->x60);
        break;
    }
    return 0;
}
#undef func_00176310
#undef func_00147e08

/* func_001484c8 (from hand/nostrict/text_00140000_h33.c). */
typedef struct {
    union { u64 d; struct { u32 lo; u8 b4; u8 b5; s16 h6; } s; } u;
    s32 w8;
    f32 fc;
    V4f v10;
    V4f v20;
} Eff;
Eff *func_00148438(void *, s32);
#define func_001315c0 ((void (*)(s32, s32, V4f *, f32)) func_001315c0)
Eff *func_001484c8(V4f **o, s32 a, s32 b, f32 f) {
    Eff *e = func_00148438(o, a);
    if (!e) return 0;
    e->w8 = b;
    e->u.s.b4 = 1;
    e->fc = f;
    PlatVu0CopyVector(&e->v10, &D_002C58A0);
    func_001315c0(a, b, &e->v20, f);
    PlatVu0CopyVector(*o, &e->v20);
    return e;
}
#undef func_001315c0

/* func_00148968 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { u8 pad[0x18]; void **p18; } Blk7c;
Blk7c *func_00147c98(s32, s32, s32);
Eff *func_00148570(Blk7c *, s32, s32);
Blk7c *func_00148968(s32 a, s32 b, s32 fl) {
    Blk7c *k = func_00147c98(b, fl, 20000);
    s32 r;
    Eff *e;
    if (k) {
        *k->p18 = (void *)a;
        r = func_001765f8(k);
        if (r >= 0) {
            e = func_00148570(k, a, r);
            if (e) {
                if (fl & 0x800) e->u.s.h6 = -1;
                if (fl & 0x1000) e->u.d |= 1;
            }
        } else if (fl & 0x800) {
            e = func_00148438(k, a);
            e->u.s.h6 = -1;
            e->u.s.b4 = 0;
        }
    }
    return k;
}

/* func_00148a60 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { u8 pad[0x68]; s32 w68; u8 pad6c[0x1C]; u32 w88; } Act;
#define func_001318e8 ((void (*)(Act *, s32, V4f *)) func_001318e8)
Blk7c *func_00148a60(Act *o, s32 fl) {
    Blk7c *k = func_00147c98(o->w68, fl, 20000);
    s32 r;
    Eff *e;
    V4f m[4];
    if (k) {
        *k->p18 = o;
        r = func_001765f8(k);
        if (r >= 0) {
            if (o->w88 & 1) {
                func_001318e8(o, r & 0xFFFEFFFF, m);
                func_00147e08((RotObj *)k, m);
                return k;
            }
            e = func_00148570(k, (s32)o, r);
            if (e) {
                if (fl & 0x800) e->u.s.h6 = -1;
                if (fl & 0x1000) e->u.d |= 1;
            }
        } else if (fl & 0x800) {
            e = func_00148438(k, (s32)o);
            e->u.s.h6 = -1;
            e->u.s.b4 = 0;
        }
    }
    return k;
}
#undef func_001318e8

