/* Hand-matched functions near 0x159000-0x165000 (worker 36). */
#include "common.h"
#include "platform/math.h"

typedef struct { f32 v[3]; f32 len; } Seg16;
typedef struct { s32 w0; void *obj; s32 pad[2]; f32 a[4]; f32 b[4]; f32 f30; f32 f34; } Tr700;
typedef union { u64 d; struct { s32 lo; s32 head; s32 w8; s32 wC; } s; } TrHdr;
typedef struct { TrHdr h; Seg16 e[32]; } Trail;
typedef struct { u8 pad[0x10]; f32 pos[4]; } ObjP;
typedef struct { s32 type; f32 r; f32 h; s32 idx; f32 pos[4] __attribute__((aligned(16))); } Cyl;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { s32 type; f32 r; f32 h; u8 padc[4]; V4 pos; } CylV;

extern Tr700 D_00551700;
extern Trail D_00551740;
extern u32 D_002C5958;

void func_002675a8(void *, void *);
s32 func_0011ef38(void *);
typedef struct { u16 h0; s16 h2; } TaskReg;
TaskReg *func_0011ef10(s32, void *);
s32 func_00159cd8();
s32 func_0013f510(void *, s32);
s32 func_001401d8(void *, s32);
s32 func_001404d8(void *, s32);
s32 func_00144410(void *, s32);
void func_0014f658(void *, s32);
void func_00159f78(void *, s32, s32);
s32 func_0015d770(void *, s32);
s32 func_0015dd50(void *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267548(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
s32 func_0015b628(Cyl *, Cyl *);
typedef struct { u8 b0; u8 type; u16 bone; f32 off; f32 dy; f32 r; f32 h; } CylSrc;
typedef struct { u8 pad[4]; u8 n4, n5, n6, n7; u8 pad8[0xC]; CylSrc *cyl; CylSrc *cyl2; } CylHdr;
typedef struct { u8 pad[0xD0]; f32 m[4][4]; } Mtx0D0;
typedef struct { u8 pad[0x60]; f32 v60[4]; f32 v70[4]; f32 v80[4]; s32 x90; Mtx0D0 *mtx; u8 pad98[0x78]; f32 x110[4]; s32 x120; } Sub148;
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4]; f32 vel[4]; f32 sx, sy; u8 pad48[0x24]; struct { u8 pad[4]; f32 f4, f8; } *p6C; s32 x70; u8 pad74[0xC0];
    CylHdr *hdr; u8 pad138[0x10]; Sub148 *p148; u8 pad14c[4]; f32 rot; u8 pad154[0xC]; union { u64 d; u32 w; } x160; u8 pad168[0x1A6];
    u16 h30E; u8 pad310[0x60]; u64 flags; u8 pad378[0x2C]; u32 mask; u32 mask2;
    u8 pad3ac[0x14]; f32 x3C0[4];
} CylObj;
void func_001315c0(void *, s32, void *, f32);
s32 func_00122ff8(void *);
s32 func_00123330(void *);
Cyl *func_00122048(s32, s32);
void func_001220b8(void *);
s32 func_001233e8(void *);
void *func_001230a0(void *);
s32 func_001425d0(void *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_002672f8(f32 *, void *, f32 *);
void func_0015cac0(void *, f32 *, f32 *, f32 *);
void func_00137688(void *, f32);
s32 func_00137450(void *);
s32 func_00105b10(s32, s32);
f32 func_0015ca50(void *);
typedef struct { u8 pad[0xC]; void *cb; } Task;
void func_00130398(void *, s32, f32);
Task *func_00130578(void *, s32, f32);
void func_0015db80(void *);
void func_0015d1d0(void *, f32 *);
void func_0015d248();
void func_00105a30(s32, s32, f32 *);
void func_002673b8(f32 *, f32 *);
void func_0015d5e8(void *);
void func_0014cce0(void *, f32);
f32 func_00120c88(f32);
extern s32 D_002C5C54;
extern f32 D_002BBDFC;
#include "data/pieces/D_002C58A0.h"
s32 func_001375f0(void *);
s32 func_0015dc50(void *);
void func_0015dcc8(void *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_0014cc88(void *, f32);
void func_00121fc4(f32 *, f32 *);
void func_00156260(void *, f32 *);
f32 atan2f(f32, f32);
s32 func_001375d8(void *);
typedef struct GsTask { u16 h0; u8 pad2[6]; struct GsTask *next; s32 (*cb)(struct GsTask *); } GsTask;
extern GsTask *D_00551D80;
extern volatile s32 D_00559DB8;
extern volatile s32 D_00559DB4;
typedef struct { u8 pad[8]; GsTask *x8; s32 xC; u8 data[0x1000]; } GsBuf2;
GsBuf2 D_00559DC0[0x2] ALIGNED(64);
extern volatile s32 D_00559DBC;
s32 func_0015ea98(void);
s32 DisableDmac(s32);
s32 EnableDmac(s32);
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"
typedef S2BC0F0_2BC0F0_2 S2BC0F0;
void func_0015f128(void);
typedef struct { u32 w0; u8 pad[396]; } E56A0F0;
extern E56A0F0 D_0056A0F0[];
extern u32 D_005739F8[];
extern u8 D_0055C698[];
void *memset(void *, s32, u32);
s32 func_00160370();
extern u8 D_00277E40[], D_00278210[];
extern void *D_00351BE0[];

Tr700 *func_00159ea8(ObjP *obj, void *a, void *b) {
    D_00551700.obj = obj;
    func_002675a8(D_00551700.a, a);
    func_002675a8(D_00551700.b, b);
    if (func_0011ef38(func_00159cd8) == 0) {
        D_00551700.f30 = 1.0f;
        D_00551700.f34 = 300.0f;
        D_00551700.w0 = 0;
        D_00551740.h.s.head = 0;
        func_002675a8(&D_00551740.e[0], obj->pos);
        D_00551740.e[0].len = 0;
        D_00551740.h.s.w8 = 0;
        D_00551740.h.d |= 1;
        func_0011ef10(0x18894, func_00159cd8);
    }
    return &D_00551700;
}

void func_0015a258(void *a, s32 b) {
    if (func_001404d8(a, b)) return;
    if (func_001401d8(a, b)) return;
    if (func_0013f510(a, b)) return;
    if (func_0015d770(a, b)) return;
    if (func_00144410(a, b)) return;
    if (func_0015dd50(a, (f32 *)b)) return;
    if ((D_002C5958 >> 17) & 1) {
        func_0014f658(a, 30);
        return;
    }
    func_00159f78(a, b, 0);
}

s32 func_0015b4a8(Cyl *a, Cyl *b) {
    f32 d[4];
    f32 s[4];
    f32 one = 1.0f;
    s[0] = s[2] = one / (a->r + b->r);
    s[1] = one / (a->h + b->h);
    func_00267530(d, b->pos, a->pos);
    func_00267548(d, d, s);
    return func_00267390(d, d) < one;
}

s32 func_0015b550(Cyl *a, Cyl *b) {
    f32 d[4];
    f32 ad, rr;
    func_00267530(d, b->pos, a->pos);
    ad = fabsf(d[1]);
    if (a->h + b->h <= ad) return 0;
    if (b->h < ad) {
        ad = (ad - b->h) / a->h;
        rr = PlatSqrtf(1.0f - ad * ad) * a->r + b->r;
    } else {
        rr = a->r + b->r;
    }
    d[1] = 0;
    return func_00267390(d, d) < rr * rr;
}

s32 func_0015b6c0(Cyl *a, Cyl *b) {
    f32 d[4];
    f32 r, rr, s;
    func_00267530(d, a->pos, b->pos);
    d[1] = fabsf(d[1]);
    if (a->h + b->h <= d[1]) return 0;
    if (b->h < d[1]) {
        r = (d[1] - b->h) / a->h;
        r = PlatSqrtf(1.0f - r * r) * a->r;
    } else r = a->r;
    d[0] = fabsf(d[0]);
    d[2] = fabsf(d[2]);
    if (d[0] < d[2]) {
        d[1] = d[0];
        d[0] = d[2];
        d[2] = d[1];
    }
    s = r + b->r;
    if (s <= d[2]) return 0;
    if (b->r < d[2]) {
        rr = (d[2] - b->r) / r;
        rr = PlatSqrtf(1.0f - rr * rr) * r + b->r;
    } else rr = s;
    return d[0] < rr;
}

s32 func_0015b7e8(Cyl *a, Cyl *b) {
    f32 d[4];
    f32 r, rr;
    func_00267530(d, a->pos, b->pos);
    d[1] = fabsf(d[1]);
    rr = a->h + b->h;
    if (rr <= d[1]) return 0;
    d[0] = fabsf(d[0]);
    d[2] = fabsf(d[2]);
    if (d[0] < d[2]) {
        d[1] = d[0];
        d[0] = d[2];
        d[2] = d[1];
    }
    r = a->r + b->r;
    if (r <= d[2]) return 0;
    if (b->r < d[2]) {
        rr = (d[2] - b->r) / a->r;
        rr = PlatSqrtf(1.0f - rr * rr) * a->r + b->r;
    } else rr = r;
    return d[0] < rr;
}

s32 func_0015b8e0(CylV *a, CylV *b) {
    V4 d;
    f32 s;
    func_00267530((f32 *)&d, (f32 *)&a->pos, (f32 *)&b->pos);
    s = a->r + b->r;
    if (s < d.x) return 0;
    if (d.x < -s) return 0;
    if (s < d.z) return 0;
    if (d.z < -s) return 0;
    s = a->h + b->h;
    if (s < d.y || d.y < -s) return 0;
    return 1;
}

s32 func_0015b998(Cyl *a, Cyl *b) {
    s32 r;
    if (a->type > b->type) {
        Cyl *t = a;
        a = b;
        b = t;
    }
    r = 0;
    switch (a->type) {
    case 1:
        switch (b->type) {
        case 1: r = func_0015b4a8(a, b); break;
        case 2: r = func_0015b550(a, b); break;
        case 3: r = func_0015b6c0(a, b); break;
        }
        break;
    case 2:
        switch (b->type) {
        case 2: r = func_0015b628(a, b); break;
        case 3: r = func_0015b7e8(a, b); break;
        }
        break;
    case 3:
        if (b->type == 3) r = func_0015b8e0((CylV *)a, (CylV *)b);
        break;
    }
    return r;
}

void func_0015bad0(CylObj *o, CylSrc *src, Cyl *c) {
    func_001315c0(o, src->bone, c->pos, src->off);
    c->type = src->type;
    if ((s32)(o->flags >> 45) & 1) {
        c->pos[1] -= src->dy * o->sy;
        c->r = src->r * o->sx;
        c->h = src->h * o->sy;
    } else {
        c->pos[1] -= src->dy;
        c->r = src->r;
        c->h = src->h;
    }
}

s32 func_0015bb88(Cyl *target, CylObj *o, Cyl *out) {
    Cyl *tmp;
    CylSrc *e;
    s32 i;
    if (!func_00122ff8(o)) goto fail;
    if (!func_00123330(o)) goto fail;
    tmp = func_00122048(32, 16);
    e = o->hdr->cyl;
    for (i = 0; i < o->hdr->n5; i++, e++) {
        if (!(o->mask & (1 << i))) {
            func_0015bad0(o, e, tmp);
            if (func_0015b998(target, tmp)) {
                if (out) *out = *tmp;
                func_001220b8(tmp);
                return 1;
            }
        }
    }
    func_001220b8(tmp);
fail:
    return 0;
}

s32 func_0015bcb8(CylObj *o, f32 *at) {
    Cyl c;
    f32 v[4];
    CylObj *p = 0;
    func_0015bad0(o, o->hdr->cyl, &c);
    func_00267530(v, at, o->pos);
    func_00267518(c.pos, c.pos, v);
    while ((p = func_001230a0(p)) != 0) {
        if (p == o) continue;
        if (!func_001425d0(p)) continue;
        if (func_0015bb88(&c, p, 0)) return 1;
    }
    return 0;
}

s32 func_0015bd78(Cyl *target, CylObj *o, Cyl *out) {
    Cyl *tmp;
    CylSrc *e;
    s32 i;
    if (!func_00122ff8(o)) goto fail;
    if (!func_001233e8(o)) goto fail;
    tmp = func_00122048(32, 16);
    e = o->hdr->cyl2;
    for (i = 0; i < o->hdr->n6; i++, e++) {
        if (!(o->mask2 & (1 << i))) {
            func_0015bad0(o, e, tmp);
            if (func_0015b998(target, tmp)) {
                if (out) {
                    *out = *tmp;
                    out->idx = i;
                }
                func_001220b8(tmp);
                return 1;
            }
        }
    }
    func_001220b8(tmp);
fail:
    return 0;
}

void func_0015bff8(Cyl *a, Cyl *b, f32 *out) {
    f32 d[4];
    f32 ad, l, r;
    func_00267530(d, b->pos, a->pos);
    ad = fabsf(d[1]);
    d[1] = 0;
    l = func_00267390(d, d);
    if (0.0f < l) {
        if (b->h < ad) {
            ad = (ad - b->h) / a->h;
            r = PlatSqrtf(1.0f - ad * ad) * a->r + b->r;
        } else {
            r = a->r + b->r;
        }
        r += 5.0f;
        l = PlatSqrtf(l);
        func_00267560(out, d, (r - l) / l);
    } else {
        out[0] = a->r + b->r + 5.0f;
        out[2] = 0.0f;
    }
    out[1] = 0;
}

void func_0015c128(Cyl *a, Cyl *b, f32 *out) {
    f32 d[4];
    f32 l, s;
    func_00267530(d, b->pos, a->pos);
    d[1] = 0;
    l = func_00267390(d, d);
    if (0.0f < l) {
        s = a->r + b->r + 5.0f;
        l = PlatSqrtf(l);
        func_00267560(out, d, (s - l) / l);
    } else {
        out[0] = a->r + b->r + 5.0f;
        out[2] = 0.0f;
    }
    out[1] = 0;
}

void func_0015c508(Cyl *a, Cyl *b, f32 *out) {
    f32 d[4];
    f32 s;
    func_00267530(d, a->pos, b->pos);
    s = a->r + b->r + 5.0f;
    if (fabsf(d[0]) > fabsf(d[2])) {
        if (0.0f < d[0]) out[0] = d[0] - s; else out[0] = d[0] + s;
        out[2] = 0;
    } else {
        if (0.0f < d[2]) out[2] = d[2] - s; else out[2] = d[2] + s;
        out[0] = 0;
    }
    out[1] = 0;
    out[3] = 1.0f;
}

s32 func_0015cb48(CylObj *o) {
    f32 v0[4], v1[4], v2[4];
    if (o->p148->mtx == 0) {
        func_002675a8(v0, o->p148->v70);
        func_002675a8(v1, o->p148->v80);
        func_002675a8(v2, o->p148->v60);
    } else {
        func_002672f8(v0, o->p148->mtx->m, o->p148->v70);
        func_002672f8(v1, o->p148->mtx->m, o->p148->v80);
        func_002672f8(v2, o->p148->mtx->m, o->p148->v60);
    }
    func_0015cac0(o, v0, v1, o->pos);
    o->rot = atan2f(v1[2], -v1[0]);
    func_00137688(o, o->rot);
    return v2[1] < -0.5f;
}

s32 func_0015d2c8(CylObj *o) {
    Cyl c;
    CylObj *p;
    if (func_00105b10(func_00137450(o->p148->mtx), o->p148->x90) != 1) return 0;
    p = 0;
    func_0015bad0(o, o->hdr->cyl, &c);
    func_00267560(c.pos, o->vel, 85.0f);
    c.pos[1] = -func_0015ca50(o);
    func_00267518(c.pos, c.pos, o->pos);
    while ((p = func_001230a0(p)) != 0) {
        if (p == o) continue;
        if (func_0015bb88(&c, p, 0)) return 0;
    }
    return 1;
}

void func_0015d3b8(CylObj *o, f32 *s) {
    f32 t;
    if (o->p148->x90 != 0xFFFF && func_0015cb48(o)) {
        func_002675a8(o->x20, o->vel);
        o->x20[3] = 0;
        t = o->x20[3];
        if (!(t < s[3])) return;
        if (!(s[1] < t)) return;
        if (func_0015d2c8(o)) {
            func_0015db80(o);
            return;
        }
        func_00130398(o, 0x100000F, t);
        func_00130578(o, 0x40000006, t)->cb = func_0015d248;
        func_0014f658(o, 16);
        return;
    }
    func_0015d1d0(o, s);
}

s32 func_0015d6c8(CylObj *o, f32 *v) {
    f32 a[4], b[4];
    f32 z = 0.0f;
    if (v[3] == z || o->h30E == 0xFFFF) return 0;
    func_00105a30(-1, o->h30E, a);
    func_002673b8(b, v);
    if (z < func_00267390(a, b)) return 0;
    func_0015d5e8(o);
    return 1;
}

void func_0015dac0(CylObj *o) {
    f32 z;
    if (o->h30E != 0xFFFF) {
        func_0015d5e8(o);
        func_00137688(o, o->rot);
        return;
    }
    z = 0.0f;
    func_0014cce0(o, z);
    o->w0 &= ~0x400;
    o->rot = func_00120c88(o->rot + 3.1415928f);
    func_00130398(o, 6, z);
    func_00137688(o, o->rot);
    func_00267560(o->x3C0, o->vel, 4.0f);
}

typedef struct { u8 pad[8]; f32 f8; } EntDC;
/* the union keeps the p10 reload after the float store */
typedef struct { u8 pad[0x10]; union { EntDC *p; f32 f; } p10; } HdrDC;
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x114]; HdrDC *h; } ObjDC;
typedef struct { f32 a[4]; f32 b[4]; u8 pad[0x10]; s16 r; u8 pad2[0xE]; } Ray;
void func_00118548(Ray *);
s32 func_0015dc50(void *vo) {
    ObjDC *o = vo;
    Ray r;
    HdrDC *h;
    func_002675a8(r.a, o->pos);
    h = o->h;
    r.a[1] -= h->p10.p->f8;
    r.b[0] = r.b[2] = 0.0f;
    r.b[1] = h->p10.p->f8;
    r.b[3] = 1.0f;
    func_00118548(&r);
    return r.r;
}

s32 func_0015dd50(void *vo, f32 *v) {
    CylObj *o = vo;
    s32 r;
    f32 z, d[4], dd;
    if (D_002C5C54 == 0) {
        if ((func_001375f0(o) || !((s32)(o->x160.d >> 2) & 1)) && !(o->x160.w & 1)) {
            r = func_0015dc50(o);
            o->p148->x120 = r;
            if (r >= 0) {
                func_002675a8(o->p148->x110, (*(f32 (*)[0x4])&D_002C58A0));
                z = 0.0f;
                if (z < v[3]) {
                    func_0015dcc8(o, d);
                    dd = func_00267390(d, v);
                    if (z < dd) {
                        f32 f;
                        if (0.7999999523162842f < v[3]) f = o->p6C->f8; else f = o->p6C->f4;
                        func_00267e90(o->p148->x110, d, f * dd);
                    }
                }
                func_0014f658(o, 12);
                return 1;
            }
        }
    }
    return 0;
}

s32 func_0015dff8(CylObj *o, s32 flag) {
    s32 r;
    f32 d[4];
    if (flag) {
        func_0014cc88(o, 0.0f);
        func_002675a8(o->x3C0, o->p148->x110);
        return 2;
    }
    r = func_0015dc50(o);
    o->p148->x120 = r;
    if (r < 0) {
        func_002675a8(d, o->p148->x110);
        d[1] = 0;
        func_00121fc4(d, d);
        d[3] *= 5.0f;
        func_0014f658(o, 0);
        func_00156260(o, d);
    }
    return o->x70;
}

void func_0015e8d8(CylObj *o, f32 *v) {
    f32 a;
    if (0.0f < v[3]) {
        a = func_00120c88(atan2f(v[0], v[2]) - o->vel[3]);
    } else a = 0.0f;
    if (0.008726646f < a) a = 0.008726646f;
    else if (a < -0.008726646f) a = -0.008726646f;
    a = func_00120c88(a * D_002BBDFC + o->vel[3]);
    func_00137688(o, a);
    o->rot = a;
    if (func_001375d8(o)) {
        func_0014f658(o, 24);
        return;
    }
    func_00130398(o, 126, 16.0f);
}
#include "data/data_002C.h"
#include "data/data_0035.h"
#include "data/data_0027.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
