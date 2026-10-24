#include "common.h"
#include "platform/math.h"
/* Hand-matched functions near 0x15b000-0x169000 (worker 59). */
#include "data/pieces/D_00304BE8_s.h"
typedef W606Mem_304be8 Mem59;
typedef struct { void *a; void *b; } Pair59;
extern void *D_00351AC8[][2];//
extern void *D_00351B18[];
u8 *func_001477c8(void *p);
void func_0015ae48(s32, s32);
void *func_0013daf8(s32);
void func_00153e80(void *);
void func_0015b098(void *, s32 *);

void func_0015b268(s32 i) {
    s32 buf[2];
    Mem59 *m = &D_00304BE8->m[i];
    u8 *p;
    void *o, *o2;
    s32 v, j, n, cnt;

    buf[0] = func_001477c8(D_00351AC8[i][0])[m->sub.lv - 1];
    func_0015ae48(i, buf[0]);
    m->sub.lv++;
    o = func_0013daf8(i);
    if (o) func_00153e80(o);
    buf[1] = 0;
    if (i == 0) {
        o2 = D_00351B18[D_00304BE8->x48c];
    } else {
        o2 = D_00351AC8[i][1];
    }
    p = func_001477c8(o2) + m->sub.w34.h.x34 - 1;
    if (!o && (D_00304BE8->x83e >> i & 1)) {
        cnt = 0;
        n = 100 - m->sub.w34.h.x34;
        for (j = 0; j < n; j++) {
            if (p[j]) cnt++;
        }
        if (cnt < 100 - m->sub.lv) return;
    }
    buf[1] = 0;
    n = m->sub.lv - m->sub.w34.h.x34;
    for (j = 0; j < n; j++) {
        m->sub.w34.h.x34++;
        buf[1] = *p++;
        if (buf[1]) {
            func_0015ae48(i, buf[1]);
            break;
        }
    }
    if (o) func_0015b098(o, buf);
}
typedef struct { s32 type; f32 r; f32 h; s32 idx; f32 pos[4] __attribute__((aligned(16))); } Cyl;
void func_00267530(f32 *, f32 *, f32 *);
void func_00267548(f32 *, f32 *, f32 *);
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

#include "data/pieces/D_002C58A0.h"
void func_0015beb0(Cyl *, Cyl *, f32 *);
void func_0015bff8(Cyl *, Cyl *, f32 *);
void func_0015c1f8(Cyl *, Cyl *, f32 *);
void func_0015c128(Cyl *, Cyl *, f32 *);
void func_0015c3a0(Cyl *, Cyl *, f32 *);
void func_0015c508(Cyl *, Cyl *, f32 *);

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

typedef struct { u8 b0; u8 type; u16 bone; f32 off; f32 dy; f32 r; f32 h; } CylSrc;
typedef struct { u8 pad[4]; u8 n4, n5, n6, n7; u8 pad8[0xC]; CylSrc *cyl; } CylHdr;
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4];
    u8 pad20[0x134 - 0x20];
    CylHdr *hdr;
    u8 pad138[0x2c4 - 0x138];
    f32 x2c4;
} Obj59;
s32 func_0014f5c8(Obj59 *);
s32 func_0014f600(Obj59 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
Obj59 *func_001230a0(Obj59 *);
s32 func_00123330(Obj59 *);
void func_0015bad0(Obj59 *, CylSrc *, Cyl *);

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

typedef struct { u8 pad[0xC0]; f32 xC0[4]; f32 xD0[4]; } M59;
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4];
    u8 pad30[0x148 - 0x30];
    M59 *m;
    u8 pad14c[0x164 - 0x14c];
    s32 st;
    u8 pad168[0x30e - 0x168];
    u16 h30e;
} Ob59;
typedef struct { u8 pad[4]; f32 f4; } Tk59;
void func_0015d7b8(Ob59 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267370(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00130398(void *, s32, f32);
Tk59 *func_00130340(Ob59 *, s32, f32);

void func_0015d848(Ob59 *o, f32 *v) {
    f32 d[4];
    f32 t[4];
    f32 c;
    s32 st;
    if (o->h30e == 0xFFFF) {
        func_0015d7b8(o, v);
        return;
    }
    st = 52;
    func_00267530(d, o->m->xD0, o->pos);
    c = d[0] * o->m->xC0[2] - d[2] * o->m->xC0[0];
    if (c > 0.0f) {
    } else if (c < 0.0f) {
        st = 51;
    } else {
        st = 50;
    }
    func_002675a8(o->m->xD0, o->pos);
    if (v[3] > 0.0f) {
        func_00267370(t, v, o->m->xC0);
        func_00267370(t, o->m->xC0, t);
        func_002673b8(v, t);
        func_00267560(v, v, 1.5f);
    } else {
        func_002675a8(v, (*(f32 (*)[0x4])&D_002C58A0));
        st = 50;
    }
    func_00267560(d, o->m->xC0, -1.5f);
    func_00267518(o->x20, v, d);
    switch (st) {
    case 50:
        if ((u32)(o->st - 51) < 2) {
            func_00130398(o, 50, 8.0f);
        } else {
            func_00130398(o, 0x40000032, 0.0f);
        }
        break;
    case 51:
    case 52:
        if (o->st != st && (o->st == 50 || o->st == 52 || o->st == 51)) {
            func_00130340(o, st, 12.0f)->f4 = 12.0f;
        } else {
            func_00130398(o, st, 0.0f);
        }
        break;
    }
}

typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4];
    u8 pad30[0x170 - 0x30];
    f32 x170;
    u8 pad174[4];
    s32 x178;
    u8 pad17c[0x440 - 0x17c];
    u64 x440;
} Ob5e;
void func_002675a8(f32 *, f32 *);
void func_001376e8(Ob5e *, f32 *);
s32 func_001375f0(Ob5e *);
void func_00130398(void *, s32, f32);

void func_0015e438(Ob5e *o, f32 *v) {
    s32 st = 0;
    if (v[1] > 0.0f) st = 125;
    else if (v[1] < 0.0f) st = 124;
    if (v[0] != 0.0f || v[2] != 0.0f) func_001376e8(o, v);
    if (v[3] > 0.0f) {
        if (v[3] > 4.0f) {
            switch (st) {
            case 0: st = 2; break;
            case 125: st = 130; break;
            case 124: st = 129; break;
            }
        } else {
            switch (st) {
            case 0: st = 1; break;
            case 125: st = 128; break;
            case 124: st = 127; break;
            }
        }
    }
    if (func_001375f0(o) && !(o->x440 >> 33 & 1)) {
        if (st == 0) {
            if (o->x178 != 0) goto end;
        } else if (o->x170 > 0.0f) {
            goto end;
        }
        func_00130398(o, st, 16.0f);
    }
end:
    func_002675a8(o->x20, v);
}

typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4];
    u8 pad30[0x3c0 - 0x30];
    f32 x3c0[4];
} Ob5f;
extern f32 D_002BBDFC;
void func_002675a8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267e60(f32 *, f32 *, f32 *, f32);
void func_00121fc4(f32 *, f32 *);

static inline f32 inl_min(f32 a, f32 b) { if (!(a < b)) a = b; return a; }
static inline f32 inl_max(f32 a, f32 b) { if (!(b < a)) a = b; return a; }
void func_0015e5c8(Ob5f *o, f32 *v) {
    f32 tmp[4];
    f32 s, t, y, c, k;
    s = o->x3c0[3];
    k = 0.199999988079071044921875f;
    if (o->x20[3] > 0.0f) {
        func_00267e60(v, o->x20, o->x3c0, k);
        v[1] = 0.0f;
        func_00121fc4(tmp, v);
        if (tmp[3] > 1.0f) func_002675a8(v, tmp);
    } else {
        func_002675a8(v, o->x3c0);
        v[1] = 0.0f;
    }
    if (s < o->x20[3]) {
        t = s + D_002BBDFC * 0.199999988079071044921875f;
        s = inl_min(t, o->x20[3]);
    } else if (o->x20[3] < s) {
        t = s - k * D_002BBDFC;
        s = inl_max(t, o->x20[3]);
    }
    o->x3c0[0] = v[0];
    o->x3c0[2] = v[2];
    o->x3c0[3] = s;
    func_00267560(v, v, s);
    y = o->x3c0[1];
    c = o->x20[1];
    if (y < c) {
        o->x3c0[1] = o->x3c0[1] + D_002BBDFC * 0.35f;
        if (c < o->x3c0[1]) o->x3c0[1] = c;
    } else if (c < o->x3c0[1]) {
        o->x3c0[1] = o->x3c0[1] - D_002BBDFC * 0.35f;
        if (o->x3c0[1] < c) o->x3c0[1] = c;
    }
    o->x20[1] = 0.0f;
    v[1] = o->x3c0[1];
    func_00267560(v, v, D_002BBDFC);
}

typedef unsigned int u128 __attribute__((mode(TI)));

/* 4/7-qword copy through $8-$11 (the caller moves its 5th arg out of $8). */

#include "data/types/nostrict_text_00150000_h59.h"

f32 func_00267390(f32 *, f32 *);
void func_00162cd0(f32 *, f32 *, M64_59 *);

typedef struct { u8 pad[0x1c]; u32 n; s8 **ids; u8 *map; } Tbl59;
typedef struct { u8 id; s8 x1; u8 pad2[2]; s32 busy; f32 x8; f32 xC; u32 *p; } Slot59;
typedef struct { u8 pad[0x10]; Tbl59 *t10; Tbl59 *t14; Slot59 s[1]; } Own59;
typedef struct { u8 pad[8]; s32 x8; } Res59;
Tbl59 *func_001684e0(s32);

static inline Tbl59 *inl_tbl59(Own59 *o, Res59 *r) {
    if (r) {
        if (!o->t14) o->t14 = func_001684e0(r->x8);
        return o->t14;
    }
    return o->t10;
}

typedef struct { u32 tag; u32 size; } Chk59;

static inline s32 inl_known59(u32 t) {
    switch (t) {
    case 0x4A424F4D:
    case 0x41584554:
    case 0x454E4F42:
    case 0x4E544D4D:
    case 0x4C535255:
    case 0x564E454D:
        return 1;
    }
    return 0;
}

static inline Chk59 *inl_next59(Chk59 *c) {
    if (inl_known59(c->tag)) {
        c = (Chk59 *)((u8 *)c + c->size + 8);
        if (inl_known59(c->tag)) return c;
    }
    return 0;
}

/* needs make: uses rodata */
void func_00162cd0(f32 *, f32 *, M64_59 *);
#include "data/bss_0057_mixed.h"
#include "data/bss_0056_typed.h"
#include "data/data_0035.h"
#include "data/pieces/D_002BBDFC.h"
