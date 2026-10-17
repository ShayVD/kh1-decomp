#include "common.h"
#include "platform/math.h"
/* Hand-matched functions near 0x15b000-0x169000 (worker 59). */
typedef struct {
    u8 lv; u8 x1; u8 x2; u8 x3;
    u8 pad04[0x34 - 0x4];
    u8 x34;
    u8 pad35[0x74 - 0x35];
} Mem59;
typedef struct {
    u8 pad000[4];
    Mem59 m[10];
    u8 x48c;
    u8 pad48d[0x83e - 0x48d];
    u16 x83e;
} Save59;
typedef struct { void *a; void *b; } Pair59;
extern Save59 *D_00304BE8;
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

    buf[0] = func_001477c8(D_00351AC8[i][0])[m->lv - 1];
    func_0015ae48(i, buf[0]);
    m->lv++;
    o = func_0013daf8(i);
    if (o) func_00153e80(o);
    buf[1] = 0;
    if (i == 0) {
        o2 = D_00351B18[D_00304BE8->x48c];
    } else {
        o2 = D_00351AC8[i][1];
    }
    p = func_001477c8(o2) + m->x34 - 1;
    if (!o && (D_00304BE8->x83e >> i & 1)) {
        cnt = 0;
        n = 100 - m->x34;
        for (j = 0; j < n; j++) {
            if (p[j]) cnt++;
        }
        if (cnt < 100 - m->lv) return;
    }
    buf[1] = 0;
    n = m->lv - m->x34;
    for (j = 0; j < n; j++) {
        m->x34++;
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

extern f32 D_002C58A0[];
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
    if (sw) func_00267530(out, D_002C58A0, out);
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
extern f32 D_002C58A0[];
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
        func_002675a8(v, D_002C58A0);
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
typedef union {
    u128 q;
    struct {
        u64 nloop : 15;
        u64 eop : 1;
        u64 pad16 : 16;
        u64 id : 14;
        u64 pre : 1;
        u64 prim : 11;
        u64 flg : 2;
        u64 nreg : 4;
        u64 regs : 4;
        u64 regs_hi : 60;
    } b;
} GT59;
typedef struct { u64 d, a; } AD59;
typedef struct { u16 qwc; u8 b2; u8 id; u32 addr; u32 pad[2]; } DT59;
typedef struct { DT59 dma; GT59 tag; AD59 ad[4]; GT59 img; DT59 ref; } Pk59;
typedef struct { u8 x0, x1; u8 pad[2]; u16 w, h; } Img59;
typedef struct { u8 pad[4]; u8 n; u8 pad5[3]; u32 data[4]; Img59 *img[4]; } Src59;
extern Pk59 *D_0055C648;

void func_0015f8c8(Src59 *s, s32 k) {
    s32 i;
    for (i = 0; i < (s->n & 7); i++) {
        u32 d = s->data[i];
        Img59 *im = s->img[i];
        s32 n;
        if (d == 0 || im == 0) continue;
    n = im->w * im->h;
    D_0055C648->dma.id = 0x10;
    D_0055C648->dma.addr = 0;
    n = n / 16;
    D_0055C648->dma.qwc = 6;
    D_0055C648->ad[0].d = (u64)0x13043600 << 32;
        D_0055C648->img.b.nloop = (u32)n;
        D_0055C648->ad[1].d = (u64)im->x0 << 32 | (u64)im->x1 << 48;
        D_0055C648->ad[2].d = im->w | (u64)im->h << 32;
        D_0055C648->ref.id = 0x30;
        D_0055C648->ref.addr = d + n * k * 16;
        D_0055C648->ref.qwc = n;
        D_0055C648++;
    }
}

typedef struct { u32 dir:1; u32 b1:1; u32 mod:2; u32 asp:2; u32 tte:1; u32 tie:1; u32 rest:24; } DmaChcr;
extern DmaChcr *D_0055C644;
void func_00266f38(void *, void *);
extern u8 D_00573AC0[];
typedef struct { u16 n; u8 pad2[2]; u16 w, h; u32 data; u32 clut; } Tex59;

void func_0015fa20(Tex59 *t) {
    __asm__ volatile("sync");
    D_0055C648 = (Pk59 *)((u32)D_00573AC0 | 0x20000000);
    D_0055C648->dma.id = 0x10;
    D_0055C648->dma.addr = 0;
    D_0055C648->dma.qwc = 6;
    D_0055C648->ad[0].d = (u64)0x9b80 << 33;
    D_0055C648->ad[1].d = 0;
    D_0055C648->ad[2].d = (16LL << 32) | 16;
    D_0055C648->img.b.nloop = 64;
    D_0055C648->ref.id = 0x30;
    D_0055C648->ref.addr = t->clut;
    D_0055C648->ref.qwc = 64;
    D_0055C648++;
    D_0055C648->dma.id = 0x10;
    D_0055C648->dma.addr = 0;
    D_0055C648->dma.qwc = 6;
    D_0055C648->ad[0].d = (u64)0x13043600 << 32;
    D_0055C648->img.b.nloop = t->n;
    D_0055C648->ad[1].d = 0;
    D_0055C648->ad[2].d = t->w | (u64)t->h << 32;
    D_0055C648->ref.id = 0x30;
    D_0055C648->ref.addr = t->data;
    D_0055C648->ref.qwc = t->n;
    D_0055C648++;
    D_0055C648->dma.id = 0x70;
    D_0055C648->dma.addr = 0;
    D_0055C648->dma.qwc = 0;
    __asm__ volatile("sync");
    D_0055C644->mod = 1;
    D_0055C644->asp = 0;
    D_0055C644->tte = 0;
    D_0055C644->tie = 0;
    __asm__ volatile("sync");
    func_00266f38(D_0055C644, D_00573AC0);
}

/* 4/7-qword copy through $8-$11 (the caller moves its 5th arg out of $8). */
#define QCOPY4(d, s) __asm__ volatile( \
    "lq $8, 0(%1)\n\tlq $9, 16(%1)\n\tlq $10, 32(%1)\n\tlq $11, 48(%1)\n\t" \
    "sq $8, 0(%0)\n\tsq $9, 16(%0)\n\tsq $10, 32(%0)\n\tsq $11, 48(%0)" \
    : : "r"(d), "r"(s) : "$8", "$9", "$10", "$11", "memory")
#define QCOPY7(d, s) __asm__ volatile( \
    "lq $8, 0(%1)\n\tlq $9, 16(%1)\n\tlq $10, 32(%1)\n\tlq $11, 48(%1)\n\t" \
    "sq $8, 0(%0)\n\tsq $9, 16(%0)\n\tsq $10, 32(%0)\n\tsq $11, 48(%0)\n\t" \
    "lq $9, 64(%1)\n\tlq $10, 80(%1)\n\tlq $11, 96(%1)\n\t" \
    "sq $9, 64(%0)\n\tsq $10, 80(%0)\n\tsq $11, 96(%0)" \
    : : "r"(d), "r"(s) : "$8", "$9", "$10", "$11", "memory")

u32 *func_0015fd20(u32 *p, u8 *src, s32 f1, s32 f2, s32 base) {
    p += 4;
    if (f2 & 2) {
        for (;;) {
            switch (p[0]) {
            case 0: {
                u32 i = p[1];
                p += 4;
                QCOPY4((u32)p | 0x20000000, (i + base) * 64 + (u32)src);
                p += 16;
                break;
            }
            case 1:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 0x8000:
                if (p[1] == 0) goto done;
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 2:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            }
        }
    } else if (f1 & 1) {
        for (;;) {
            switch (p[0]) {
            case 0: {
                u32 i = p[1];
                p += 4;
                QCOPY7((u32)p | 0x20000000, (i + base) * 128 + (u32)src);
                p += 28;
                break;
            }
            case 1:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 0x8000:
                if (p[1] == 0) goto done;
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 2:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            }
        }
    } else {
        for (;;) {
            switch (p[0]) {
            case 0: {
                u32 i = p[1];
                p += 4;
                QCOPY4((u32)p | 0x20000000, (i + base) * 64 + (u32)src);
                p += 28;
                break;
            }
            case 1:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 0x8000:
                if (p[1] == 0) goto done;
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 2:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            }
        }
    }
done:
    return p;
}

typedef struct { f32 a[4], b[4], c[3]; u32 par; } S48_59;
typedef struct { f32 m[4][4]; } M64_59;
typedef struct { s16 n; u8 pad2[2]; S48_59 *src; } Mdl59;
typedef struct {
    void *x0;
    u8 pad4[0x150 - 0x4];
    M64_59 *x150;
    M64_59 *x154;
    M64_59 *x158;
    u8 pad15c[0x170 - 0x15c];
    Mdl59 *x170;
    s32 x174;
    s32 x178;
    s32 x17c;
    void *x180;
    u8 pad184[0x190 - 0x184];
} Ent59;
typedef struct { u8 pad0[8]; s32 x8; u8 padc[0x20 - 0xc]; Mdl59 *x20; u8 pad24[4]; s32 x28; u8 pad2c[4]; s32 x30; } Src17c0;
extern Ent59 D_0056A0F0[96];
void *memset(void *, s32, u32);
s32 func_00121e28(s32, void *);
void func_001626f0(f32 *, f32 *, f32 *, f32 *);

Ent59 *func_001617c0(Src17c0 *o) {
    s32 i, j;
    Ent59 *e;
    Mdl59 *m;
    for (i = 0; i < 96; i++) {
        if (D_0056A0F0[i].x0 == 0) break;
    }
    e = &D_0056A0F0[i];
    m = o->x20;
    memset(e, 0, sizeof(Ent59));
    e->x170 = m;
    e->x174 = o->x30;
    e->x178 = o->x28;
    e->x17c = o->x8;
    e->x180 = o;
    e->x0 = &e->x170;
    func_00121e28(m->n << 6, &e->x154);
    func_00121e28(m->n << 6, &e->x158);
    func_00121e28(m->n << 6, &e->x150);
    for (i = 0; i < m->n; i++) {
        for (j = 0; j < 3; j++) e->x150[i].m[0][j] = m->src[i].a[j];
        for (j = 0; j < 3; j++) e->x150[i].m[2][j] = m->src[i].b[j];
        for (j = 0; j < 3; j++) e->x150[i].m[3][j] = m->src[i].c[j];
        func_001626f0(e->x150[i].m[0], e->x150[i].m[2], e->x150[i].m[3], e->x158[i].m[0]);
    }
    return e;
}

typedef struct { void *a, *b; } Pr59;
typedef struct { u8 b[44]; } E44_59;
typedef struct {
    s32 x0, x4, x8, xC, x10;
    Pr59 pr[2][72];
    u8 pad494[0x3558 - 0x494];
    E44_59 e[2][480];
} G698;
extern G698 D_0055C698;
typedef struct { u8 pad[0x10]; void *x10; s32 x14; } Tk62;
void func_001606d0(void);
Tk62 *func_0015ee78(s32, void *);
s32 func_0015ff78();
s32 func_0015f388(void);
s32 func_0015eea0();
s32 sceGsSyncPath(s32, s32);
void func_00121eb0(void *);

void func_00161de8(void) {
    s32 c8 = D_0055C698.x8;
    s32 c4 = D_0055C698.x4;
    s32 cC = D_0055C698.xC;
    s32 i;
    Tk62 *t;
    E44_59 *e;
    Pr59 *p;
    func_001606d0();
    e = &D_0055C698.e[D_0055C698.x0][c8];
    for (i = c8; i < D_0055C698.x8; i++) {
        t = func_0015ee78(0, func_0015ff78);
        t->x10 = e;
        t->x14 = 0;
        e++;
    }
    func_0015ee78(0, func_0015f388);
    func_0015eea0();
    sceGsSyncPath(0, 0);
    p = &D_0055C698.pr[D_0055C698.x0][cC];
    for (i = cC; i < D_0055C698.xC; i++, p++) {
        if (p->a) {
            func_00121eb0(p->a);
            p->a = 0;
        }
        if (p->b) {
            func_00121eb0(p->b);
            p->b = 0;
        }
    }
    D_0055C698.x4 = c4;
    D_0055C698.x8 = c8;
    D_0055C698.xC = cC;
}

f32 func_00267390(f32 *, f32 *);

s32 func_00162ab8(f32 *p0, f32 *p1, f32 *q0, f32 *q1, f32 *out) {
    f32 m[4];
    f32 n[4];
    f32 a[4];
    f32 b[4];
    f32 da, db;
    func_00267518(m, q0, q1);
    func_00267560(m, m, 0.5f);
    n[0] = q1[1] - m[1];
    n[1] = m[0] - q1[0];
    func_00267530(a, p0, m);
    func_00267530(b, p1, m);
    da = func_00267390(a, n);
    db = func_00267390(b, n);
    if (da * db >= 0.0f) return 0;
    db = fabsf(db);
    da = fabsf(da);
    func_00267560(a, p0, db);
    func_00267560(b, p1, da);
    func_00267518(out, a, b);
    func_00267560(out, out, 1.0f / (da + db));
    return 1;
}

typedef struct {
    Mdl59 **x0;
    u8 pad4[8];
    s32 xC;
    u8 pad10[0x150 - 0x10];
    M64_59 *x150;
    M64_59 *x154;
    M64_59 *x158;
} Ent63;
extern M64_59 D_00351E10[];
extern M64_59 D_00573F10;
void func_001627d0(f32 *, f32 *, f32 *);
void func_00162848(f32 *, M64_59 *, f32 *);
void func_00162cd0(f32 *, f32 *, M64_59 *);
void func_00162c5c(M64_59 *, M64_59 *, M64_59 *);
void func_00267e90(f32 *, f32 *, f32);
void func_00163150(Ent63 *, s32);

void func_00163490(Ent63 *e) {
    s32 i;
    S48_59 *s = (*e->x0)->src;
    f32 tmp[4];
    M64_59 *pm;
    M64_59 *g;
    M64_59 *w;
    M64_59 *d;
    f32 *sc;
    u32 p, q;
    for (i = 0; i < (*e->x0)->n; i++) {
        p = s[i].par & 0x3ff;
        if (p == 0x3ff) {
            pm = &D_00573F10;
            e->x150[i].m[1][0] = e->x150[i].m[0][0];
            e->x150[i].m[1][1] = e->x150[i].m[0][1];
            e->x150[i].m[1][2] = e->x150[i].m[0][2];
        } else {
            pm = &D_00351E10[p];
            func_001627d0(e->x150[i].m[1], e->x150[p].m[1], e->x150[i].m[0]);
        }
        q = s[i].par & 0x3ff;
        g = &D_00351E10[i];
        w = &e->x158[i];
        if (q == 0x3ff) {
            func_00162848(tmp, &D_00573F10, e->x150[i].m[3]);
        } else {
            func_00162848(tmp, &e->x154[q], e->x150[i].m[3]);
        }
        tmp[3] = 1.0f;
        func_00162cd0(e->x150[i].m[2], e->x150[i].m[3], w);
        func_00162c5c(g, pm, w);
        d = (M64_59 *)(i * 64 + (u32)e->x154);
        sc = ((M64_59 *)(i * 64 + (u32)e->x150))->m[1];
        func_00267e90(d->m[0], g->m[0], sc[0]);
        func_00267e90(d->m[1], g->m[1], sc[1]);
        func_00267e90(d->m[2], g->m[2], sc[2]);
        func_002675a8(d->m[3], g->m[3]);
        func_002675a8(e->x154[i].m[3], tmp);
        if (e->xC & 0xC) func_00163150(e, i);
    }
}

typedef struct { u8 pad[0xC]; u32 xC; } E5450;
typedef struct { u8 pad[4]; u8 on; } K5450;
K5450 *func_00164e00(void *, s32, f32);

void func_00165450(E5450 *e, void *a, f32 t) {
    K5450 *k;
    k = func_00164e00(a, 0x10000, t);
    if (k && k->on) e->xC |= 0x10000;
    k = func_00164e00(a, 0x10001, t);
    if (k && k->on) e->xC |= 0x20000;
    k = func_00164e00(a, 0x10002, t);
    if (k && k->on) e->xC |= 0x40000;
    k = func_00164e00(a, 0x10003, t);
    if (k && k->on) e->xC |= 0x80000;
    k = func_00164e00(a, 0, t);
    if (k && k->on) e->xC |= 0x100000;
    k = func_00164e00(a, 0x50000, t);
    if (k && k->on) e->xC |= 0x400000;
    k = func_00164e00(a, 0x70000, t);
    if (k && k->on) e->xC |= 0x800000;
}

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

s32 func_00167978(Own59 *o, Res59 *r, u32 n) {
    Tbl59 *t1 = inl_tbl59(o, r);
    Tbl59 *t;
    s32 id = -1;
    s32 k;
    u32 f;
    u32 *p;
    if (t1) {
        id = n - 1024;
        if (n < 1024) id = t1->map[n] - 1;
    }
    if (id < 0) return 3;
    t = inl_tbl59(o, r);
    if (!t) return 3;
    if ((u32)id >= t->n) return 3;
    k = *t->ids[id];
    p = o->s[k].p;
    if (!p || o->s[k].id != id) return 4;
    f = *p & 0xf;
    if (f == 2) return 2;
    if (!o->s[k].busy) return f == 3 ? 2 : 1;
    return 0;
}

typedef struct { u16 x0; u16 x2; u16 x4; s16 x6; } Hd59;
s32 func_001627e8(s32);

void func_00167ac0(Own59 *o, Res59 *r, u32 n) {
    Tbl59 *t1 = inl_tbl59(o, r);
    Tbl59 *t;
    s32 id = -1;
    s32 k;
    Hd59 *h;
    s32 v;
    if (t1) {
        id = n - 1024;
        if (n < 1024) id = t1->map[n] - 1;
    }
    if (id >= 0) {
    t = inl_tbl59(o, r);
    if (t && (u32)id < t->n) {
    k = *t->ids[id];
    o->s[k].id = id;
    o->s[k].x1 = 1;
    o->s[k].busy = (s32)t->ids[id];
    o->s[k].x8 = 0;
    h = (Hd59 *)(t->ids[id] + 4);
    o->s[k].p = (u32 *)h;
    if (h->x4 == 0) v = h->x2;
    else v = h->x2 + func_001627e8(h->x4 + 1);
    o->s[k].xC = v;
    }
    }
}

void func_00167d70(Own59 *o, f32 dt) {
    s32 i;
    u32 f;
    s32 v;
    Hd59 *h;
    if (dt <= 0.0f) return;
    for (i = 0; i < 5; i++) {
        if (!o->s[i].p) continue;
        f = *o->s[i].p & 0xf;
        if (f == 2) continue;
        if (f == 3) {
            if (o->s[i].busy) {
                o->s[i].p = o->s[i].p + ((Hd59 *)o->s[i].p)->x6 * 2;
            } else {
                o->s[i].p = 0;
                continue;
            }
        }
        if (o->s[i].x1) {
            o->s[i].x1 = 0;
            continue;
        }
        o->s[i].x8 += dt;
        if (o->s[i].xC <= o->s[i].x8) {
            do {
                o->s[i].x8 -= o->s[i].xC;
                o->s[i].p += 2;
                f = *o->s[i].p & 0xf;
                if (f == 3) {
                    if (!o->s[i].busy) {
                        o->s[i].p = 0;
                        break;
                    }
                    o->s[i].p = o->s[i].p + ((Hd59 *)o->s[i].p)->x6 * 2;
                } else if (f == 2) {
                    break;
                }
                h = (Hd59 *)o->s[i].p;
                if (h->x4 == 0) v = h->x2;
                else v = h->x2 + func_001627e8(h->x4 + 1);
                o->s[i].xC = v;
            } while (o->s[i].xC <= o->s[i].x8);
        }
    }
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

Chk59 *func_001681b8(Chk59 *c, u32 tag) {
    for (; c; c = inl_next59(c)) {
        if (c->tag == tag) break;
    }
    if (c) {
        if (c->size == 0) return 0;
    }
    return c;
}
