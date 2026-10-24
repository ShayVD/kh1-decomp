/* Cylinder hits between objects, without strict aliasing (docs/modules.md
 * "Session 52"): overlap and push-out tests of two cylinders by shape
 * pair (func_0015b4a8 ... func_0015b8e0, dispatched by func_0015b998 and
 * func_0015c5d0), func_0015bad0 places an object's cylinder from its bone,
 * func_0015bb88 / func_0015bcb8 test an object against the others, and
 * func_0015c738 finds the object under a point.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/math.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_00304BE8_s.h"

/* func_0015b4a8 (from hand/nostrict/text_00150000_h36.c). */
typedef struct { s32 type; f32 r; f32 h; s32 idx; f32 pos[4] __attribute__((aligned(16))); } Cyl;
void func_00267530(f32 *, f32 *, f32 *);
void func_00267548(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
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

/* func_0015b550 (from hand/nostrict/text_00150000_h36.c). */
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

/* func_0015b6c0 (from hand/nostrict/text_00150000_h36.c). */
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

/* func_0015b7e8 (from hand/nostrict/text_00150000_h36.c). */
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

/* func_0015b8e0 (from hand/nostrict/text_00150000_h36.c). */
typedef struct { f32 x, y, z, w; } V4;
typedef struct { s32 type; f32 r; f32 h; u8 padc[4]; V4 pos; } CylV;
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

/* func_0015b998 (from hand/nostrict/text_00150000_h36.c). */
s32 func_0015b628(Cyl *, Cyl *);
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

/* func_0015bad0 (from hand/nostrict/text_00150000_h36.c). */
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

/* func_0015bb88 (from hand/nostrict/text_00150000_h36.c). */
s32 func_00122ff8(void *);
s32 func_00123330(void *);
Cyl *func_00122048(s32, s32);
void func_001220b8(void *);
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

/* func_0015bcb8 (from hand/nostrict/text_00150000_h36.c). */
void *func_001230a0(void *);
s32 func_001425d0(void *);
void func_00267518(f32 *, f32 *, f32 *);
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

/* func_0015bd78 (from hand/nostrict/text_00150000_h36.c). */
s32 func_001233e8(void *);
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

/* func_0015beb0 (from hand/nostrict/text_00150000_h59.c). */
void func_00267560(f32 *, f32 *, f32);
void func_0015beb0(Cyl *a, Cyl *b, f32 *out) {
    f32 res[4];
    f32 sc[4];
    f32 d[4];
    f32 len;
    sc[0] = sc[2] = 1.0f / (a->r + b->r);
    sc[1] = 1.0f / (a->h + b->h);
    func_00267530(d, b->pos, a->pos);
    func_00267548(res, d, sc);
    d[1] = 0.0f;
    len = res[0] * res[0] + res[2] * res[2];
    if (d[1] < len) {
        func_00267560(out, res, (PlatSqrtf((1.0f - res[1] * res[1]) / len) - 1.0f) * (a->r + b->r + 5.0f));
    } else {
        out[0] = a->r + b->r + 5.0f;
        out[2] = d[1];
    }
    out[1] = 0;
}

/* func_0015bff8 (from hand/nostrict/text_00150000_h36.c). */
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

/* func_0015c128 (from hand/nostrict/text_00150000_h36.c). */
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

/* func_0015c1f8 (from hand/nostrict/text_00150000_h59.c). */
void func_0015c1f8(Cyl *a, Cyl *b, f32 *out) {
    f32 d[4];
    f32 e[4];
    f32 r, rr;
    func_00267530(d, a->pos, b->pos);
    d[1] = fabsf(d[1]);
    r = b->h;
    if (r < d[1]) {
        r = (d[1] - r) / a->h;
        r = PlatSqrtf(1.0f - r * r) * a->r;
    } else {
        r = a->r;
    }
    e[0] = fabsf(d[0]);
    e[2] = fabsf(d[2]);
    if (e[2] < e[0]) {
        if (b->r < e[2]) {
            rr = (e[2] - b->r) / r;
            rr = PlatSqrtf(1.0f - rr * rr) * r + b->r;
        } else {
            rr = r + b->r;
        }
        rr += 5.0f;
        if (d[0] > 0.0f) out[0] = d[0] - rr;
        else out[0] = d[0] + rr;
        out[2] = 0;
    } else {
        if (b->r < e[0]) {
            rr = (e[0] - b->r) / r;
            rr = PlatSqrtf(1.0f - rr * rr) * r + b->r;
        } else {
            rr = r + b->r;
        }
        rr += 5.0f;
        if (d[2] > 0.0f) out[2] = d[2] - rr;
        else out[2] = d[2] + rr;
        out[0] = 0;
    }
    out[1] = 0;
    out[3] = 1.0f;
}

/* func_0015c3a0 (from hand/nostrict/text_00150000_h59.c). */
void func_0015c3a0(Cyl *a, Cyl *b, f32 *out) {
    f32 d[4];
    f32 e[4];
    f32 r;
    func_00267530(d, a->pos, b->pos);
    e[0] = fabsf(d[0]);
    e[2] = fabsf(d[2]);
    e[1] = fabsf(d[1]);
    if (e[2] < e[0]) {
        if (b->r < e[2]) {
            r = (e[2] - b->r) / a->r;
            r = PlatSqrtf(1.0f - r * r) * a->r + b->r;
        } else {
            r = a->r + b->r;
        }
        r += 5.0f;
        if (d[0] > 0.0f) out[0] = d[0] - r;
        else out[0] = d[0] + r;
        out[2] = 0;
    } else {
        if (b->r < e[0]) {
            r = (e[0] - b->r) / a->r;
            r = PlatSqrtf(1.0f - r * r) * a->r + b->r;
        } else {
            r = a->r + b->r;
        }
        r += 5.0f;
        if (d[2] > 0.0f) out[2] = d[2] - r;
        else out[2] = d[2] + r;
        out[0] = 0;
    }
    out[1] = 0;
    out[3] = 1.0f;
}

/* func_0015c508 (from hand/nostrict/text_00150000_h36.c). */
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

/* func_0015c5d0 (from hand/nostrict/text_00150000_h59.c). */
void func_0015c5d0(Cyl *a, Cyl *b, f32 *out) {
    s32 sw = 0;
    if (a->type > b->type) {
        Cyl *t = a;
        a = b;
        b = t;
        sw = 1;
    }
    switch (a->type) {
    case 1:
        switch (b->type) {
        case 1: func_0015beb0(a, b, out); break;
        case 2: func_0015bff8(a, b, out); break;
        case 3: func_0015c1f8(a, b, out); break;
        }
        break;
    case 2:
        switch (b->type) {
        case 2: func_0015c128(a, b, out); break;
        case 3: func_0015c3a0(a, b, out); break;
        }
        break;
    case 3:
        if (b->type == 3) func_0015c508(a, b, out);
        break;
    }
    if (sw) func_00267530(out, (*(f32 (*)[0x4])&D_002C58A0), out);
}

/* func_0015c738 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { u8 pad[4]; u8 n4, n5, n6, n7; u8 pad8[0xC]; CylSrc *cyl; } CylHdr_5c738;
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4];
    u8 pad20[0x134 - 0x20];
    CylHdr_5c738 *hdr;
    u8 pad138[0x2c4 - 0x138];
    f32 x2c4;
} Obj59;
s32 func_0014f5c8(Obj59 *);
s32 func_0014f600(Obj59 *);
#define func_001230a0 ((Obj59 *(*)(Obj59 *)) func_001230a0)
#define func_00123330 ((s32 (*)(Obj59 *)) func_00123330)
#define func_0015bad0 ((void (*)(Obj59 *, CylSrc *, Cyl *)) func_0015bad0)
Obj59 *func_0015c738(Obj59 *self, f32 *pos) {
    f32 d[4];
    f32 p[4];
    Cyl c;
    f32 hi, lo, y;
    Obj59 *o;
    CylSrc *s;
    s32 i;

    if (func_0014f5c8(self)) return 0;
    hi = (pos[1] < self->x2c4 * 0.5f) ? self->x2c4 * 0.5f : pos[1];
    lo = 0.0f;
    if (!func_0014f600(self)) lo = -hi;
    func_00267518(p, self->pos, pos);
    o = 0;
    while ((o = func_001230a0(o)) != 0) {
        if (o == self) continue;
        if (!func_00123330(o)) continue;
        s = o->hdr->cyl;
        for (i = 0; i < o->hdr->n5; i++, s++) {
            switch (s->type) {
            case 2:
                func_0015bad0(o, s, &c);
                func_00267530(d, p, c.pos);
                y = d[1] + c.h;
                if (lo <= y && y < hi) {
                    d[1] = 0.0f;
                    if (func_00267390(d, d) < c.r * c.r) {
                        pos[1] -= y;
                        return o;
                    }
                }
                break;
            case 3:
                func_0015bad0(o, s, &c);
                func_00267530(d, p, c.pos);
                y = d[1] + c.h;
                if (lo <= y && y < hi) {
                    d[1] = 0.0f;
                    if (fabsf(d[0]) < c.r && fabsf(d[2]) < c.r) {
                        pos[1] -= y;
                        return o;
                    }
                }
                break;
            }
        }
    }
    return 0;
}
#undef func_001230a0
#undef func_00123330
#undef func_0015bad0

