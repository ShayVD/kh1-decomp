#include "common.h"
typedef union { struct { u64 a, b; } d; s32 w[4]; } QW;
extern s32 D_002E27E0[];
extern QW *func_0011fb38(s32, u64, QW *);
extern void func_0011fb48(QW *, s32, QW *);
extern void func_0011fb78(QW *, s32, QW *);
void func_001284a0(QW *buf, s32 idx) {
    QW *d;
    s32 w = D_002E27E0[idx];
    QW *t;
    s32 a, b, c;
    u64 r;
    d = buf;
    buf++;
    t = buf;
    buf++;
    buf = func_0011fb38(0x18, 0x0000780000007800ULL, buf);
    a = (256 - w) / 2;
    b = (256 + w) / 2;
    buf = func_0011fb38(0x40, (u64)a | (u64)(b - 1) << 16 | (u64)a << 32 | (u64)(b - 1) << 48, buf);
    buf = func_0011fb38(0x4c, 0x1000401d0ULL, buf);
    buf = func_0011fb38(0x4e, 0x3a0001c0, buf);
    buf = func_0011fb38(0x47, 0x30000, buf);
    buf = func_0011fb38(0x19, 0x0000780000007800ULL, buf);
    a += 2;
    b -= 3;
    r = (u64)a | (u64)b << 16 | (u64)a << 32 | (u64)b << 48;
    buf = func_0011fb38(0x41, r, buf);
    buf = func_0011fb38(0x4d, 0x1000401d0ULL, buf);
    buf = func_0011fb38(0x4f, 0x3a0001c0, buf);
    buf = func_0011fb38(0x16, 0x100000, buf);
    buf = func_0011fb38(0x3b, 0x80, buf);
    func_0011fb48(t, 0, buf);
    buf->d.a = 0x3003400000000001ULL;
    buf->d.b = 0x551;
    buf++;
    c = w / 2;
    buf->w[0] = 0;
    buf->w[3] = 0;
    buf->w[1] = 0;
    buf->w[2] = 0;
    buf++;
    buf->w[0] = (2048 - c) << 4;
    buf->w[1] = (2048 - c) << 4;
    buf->w[3] = 0x8000;
    buf->w[2] = 0;
    buf++;
    buf->w[0] = (2048 + c) << 4;
    buf->w[1] = (2048 + c) << 4;
    buf->w[2] = 0;
    buf->w[3] = 0;
    buf++;
    t = buf;
    buf = func_0011fb38(0x40, r, t + 1);
    buf = func_0011fb38(0x47, 0x5000d, buf);
    buf = func_0011fb38(0x48, 0x5000d, buf);
    func_0011fb48(t, 1, buf);
    func_0011fb78(d, 7, buf);
}

void func_00128738(QW *buf, s32 idx) {
    QW *d;
    s32 w = D_002E27E0[idx];
    QW *t;
    s32 a, b, c, m, n;
    d = buf;
    buf++;
    t = buf;
    buf++;
    buf = func_0011fb38(0x4c, 0x1000401b0ULL, buf);
    buf = func_0011fb38(0x18, 0x0000780000007800ULL, buf);
    m = 256 - w; n = 256 + w; b = n / 2; a = m / 2;
    buf = func_0011fb38(0x40, (u64)a | (u64)(b - 1) << 16 | (u64)a << 32 | (u64)(b - 1) << 48, buf);

    buf = func_0011fb38(6, 0x2000000620013a00ULL, buf);
    buf = func_0011fb38(0x14, 0x61, buf);
    buf = func_0011fb38(0x3f, 0, buf);
    buf = func_0011fb38(0x47, 0x30000, buf);
    buf = func_0011fb38(0x42, 0x8000000044ULL, buf);
    buf = func_0011fb38(0x3b, 0x8000000000ULL, buf);
    buf = func_0011fb38(0x4e, 0x100000000ULL, buf);
    func_0011fb48(t, 0, buf);
    buf->d.a = 0x508b400000000001ULL;
    buf->d.b = 0x53531;
    buf++;
    c = w / 2;
    buf->w[0] = 128;
    buf->w[1] = 128;
    buf->w[2] = 128;
    buf->w[3] = 128;
    buf++;
    buf->w[0] = m << 3;
    buf->w[1] = m << 3;
    buf++;
    buf->w[0] = (2048 - c) << 4;
    buf->w[1] = (2048 - c) << 4;
    buf->w[3] = 0x8000;
    buf->w[2] = 0;
    buf++;
    buf->w[0] = n << 3;
    buf->w[1] = n << 3;
    buf++;
    buf->w[0] = (2048 + c) << 4;
    buf->w[1] = (2048 + c) << 4;
    buf->w[2] = 0;
    buf->w[3] = 0;
    buf++;
    t = buf;
    buf++;
    buf = func_0011fb38(0x18, 0x0000740000007000ULL, buf);
    buf = func_0011fb38(0x40, 0x017F000001FF0000ULL, buf);
    buf = func_0011fb38(0x4c, 0x800d0, buf);
    buf = func_0011fb38(0x4e, 0x31000070, buf);
    buf = func_0011fb38(0x19, 0x0000740000007000ULL, buf);
    buf = func_0011fb38(0x41, 0x017F000001FF0000ULL, buf);
    buf = func_0011fb38(0x4d, 0x800d0, buf);
    buf = func_0011fb38(0x4f, 0x31000070, buf);
    func_0011fb48(t, 0, buf);
    t = buf;
    buf++;
    buf = func_0011fb38(0x48, 0x5000d, buf);
    buf = func_0011fb38(7, 0x2000000620013600ULL, buf);
    buf = func_0011fb38(0x15, 0x61, buf);
    buf = func_0011fb38(9, (u64)(a + 1) << 4 | (u64)(b - 1) << 14 | 10 | (u64)(a + 1) << 24 | (u64)(b - 1) << 34, buf);
    buf = func_0011fb38(0x3f, 0, buf);
    buf = func_0011fb38(0x43, 0x4000000044ULL, buf);
    func_0011fb48(t, 1, buf);
    func_0011fb78(d, 7, buf);
}

#include "data/pieces/D_002C58A0.h"
typedef V4_2c58a0 V4;
typedef union { u64 x; struct { u32 b0:2; u32 b2:1; u32 b3:1; u32 b4:1; u32 b5:1; u32 b6:1; u32 b7:4; u32 b11:1; u32 b12:1; u32 r13:19; s32 hi; } b; } F160;
typedef union { u64 x; struct { u32 lo; u32 r0:13; u32 b45:1; u32 r46:4; u32 b50:1; u32 r51:13; } b; } F370;
typedef struct { s32 f0; f32 f4; f32 f8; f32 fc; } Q8e;
typedef struct {
    u32 f0;
    u8 p4[0x40 - 4];
    V4 f40;
    u8 p50[0x160 - 0x50];
    F160 f160;
    s32 f168;
    s32 f16c;
    f32 f170;
    s32 f174;
    s32 n;
    Q8e q[8];
    u8 p1fc[0x210 - 0x1fc];
    V4 f210;
    V4 f220;
    V4 f230;
    u8 p240[0x370 - 0x240];
    F370 f370;
} Ob8;
typedef struct { u8 p0[0x30]; V4 f30; } Ct8;
extern u32 D_002C5958;
extern void func_00267518(V4 *, V4 *, V4 *);
extern void func_002675a8(V4 *, V4 *);
extern void func_002673f8(f32 (*)[4], V4 *);
extern void func_002672f8(V4 *, f32 (*)[4], V4 *);
extern void func_001219c8(V4 *, V4 *, V4 *);
extern s32 func_00130190(Ob8 *, s32);
extern void func_00131500(Ob8 *);
extern void func_0013df40(Ob8 *, s32);
extern void func_0013dfa0(Ob8 *);
extern void func_00130660(Ob8 *, Ct8 *, s32, f32, f32);
extern void func_00130210(Ob8 *, s32);
void func_00130898(Ob8 *o, Ct8 *c) {
    V4 a;
    f32 b[4][4];
    Q8e *s = o->q;
    s32 r, hi, i;

    if (o->f160.b.b2) {
        if (s->f8 == 0.0f) {
            func_00267518(&c->f30, &c->f30, &o->f210);
            func_002675a8(&o->f220, &D_002C58A0);
        } else {
            func_002673f8(b, &o->f230);
            func_002675a8(&a, &o->f210);
            a.w = 0.0f;
            func_002672f8(&o->f220, b, &a);
            if (o->f370.b.b45) func_001219c8(&o->f220, &o->f220, &o->f40);
        }
    } else {
        func_002675a8(&o->f220, &D_002C58A0);
    }
    func_002675a8(&o->f210, &D_002C58A0);
    if ((o->f160.b.hi = *(u16 *)s)) o->f370.b.b50 = D_002C5958 & 1;
    r = func_00130190(o, s->f0);
    if (o->f160.b.b5 && (r & 0x200000)) {
        func_00131500(o);
        r = func_00130190(o, s->f0);
    }
    hi = r & 0xffff0000;
    r &= 0xffff;
    if (hi & 0x10000000) {
        func_0013df40(o, 1);
        if (!(hi & 0x80000)) o->f370.b.b50 = 1;
    } else if (hi & 0x8000000) {
        func_0013dfa0(o);
    }
    if (hi & 0x40000000) o->f0 &= ~4;
    if (hi & 0x800000) o->f0 |= 0x1000;
    else o->f0 &= ~0x1000;
    o->f160.b.b12 = o->f160.b.b2;
    if (hi & 0x4000000) o->f160.b.b2 = 1;
    else o->f160.b.b2 = 0;
    o->f160.b.b3 = (hi >> 16) & 1;
    o->f160.b.b11 = (hi >> 18) & 1;
    o->f160.b.b6 = 0;
    func_00130660(o, c, r, s->f4, s->f8);
    for (i = 1; i < o->n; i++) o->q[i - 1] = o->q[i];
    o->n--;
    if (o->f170 == 0.0f) func_00130210(o, o->f160.b.hi);
}

typedef struct { u8 p0[0x54]; s8 b54; } Y12;
typedef struct { u8 p0[0x4c]; u16 h4c; } Z12;
typedef struct { u8 p0[0x130]; Y12 *f130; } X12;
typedef struct { u8 p0[0x14]; s32 f14; u8 p18[8]; s32 f20; s32 f24; u8 p28[0x44 - 0x28]; s32 f44; s32 f48; s32 f4c; s32 f50; } P12;
typedef struct {
    u8 p0[0x2c];
    s32 f2c;
    union { u64 d; struct { s32 f30; X12 *f34; } s; } u30;
    u8 p38[0x5c - 0x38];
    P12 *f5c;
    u8 p60[0x94 - 0x60];
    f32 f94;
    s32 f98;
    u8 p9c[0xac - 0x9c];
    f32 fac;
} A12;
typedef struct {
    u8 p0[0x3c];
    s32 f3c;
    u8 p40[0x50 - 0x40];
    s32 f50;
    u8 p54[0x78 - 0x54];
    f32 f78[8];
    f32 f98;
    u8 p9c[0xc0 - 0x9c];
    u16 hc0;
    u16 hc2;
} Q12;
typedef struct { u8 p0[0x170]; union { u64 d; struct { u32 lo; u32 b0 : 4; u32 b36 : 1; } b; } f170; } R12;
typedef struct {
    u8 p0[6];
    u8 f6;
    u8 p7[0x6c - 7];
    Q12 *f6c;
    u8 p70[0x88 - 0x70];
    s32 f88;
    u8 p8c[0x148 - 0x8c];
    R12 *f148;
    u8 p14c[0x370 - 0x14c];
    u64 f370;
} B12;
#include "data/pieces/D_003044A0.h"
extern f32 func_00176850(void);
extern s32 func_00122ff8(X12 *);
extern void func_001586a8(s32);
extern s32 func_0013bf68(void);
#define CALC12(q, v) ((s32)((f32)(q)->f3c * ((f32)(v) / 100.0f) * (q)->f98))
s32 func_00134ba8(A12 *a, B12 *b, u32 *fl) {
    s32 v;
    s32 hi;
    s32 lo;
    s32 m;
    Q12 *q;
    s32 i;

    switch (b->f6) {
    case 4:
    case 5:
    case 9:
    case 10:
        if (a->u30.s.f34 && a->u30.s.f34->f130->b54 == 1) return 0;
        return a->f5c->f44;
    }
    if (((b->f370 >> 37) & 3) == 2) {
        v = a->f2c + a->f5c->f48;
        lo = a->f5c->f4c;
        hi = a->f5c->f50;
    } else {
        v = a->f2c + a->f5c->f14;
        lo = a->f5c->f20;
        hi = a->f5c->f24;
    }
    if (!b->f6c || !v) return 0;
    if (func_00176850() < a->f94) {
        v += a->f98;
        *fl |= 0x20;
        if (func_00122ff8(a->u30.s.f34) && !((Z12 *)a->u30.s.f34->f130)->h4c) func_001586a8(8);
    }
    m = (s32)(a->u30.d >> 6) & 0xf;
    switch (m) {
    case 9:
    case 11:
    case 12:
        return v;
    case 8:
        m = CALC12(b->f6c, v) < (b->f6c->hc0 > 1 ? b->f6c->hc0 : 1) ? (b->f6c->hc0 > 1 ? b->f6c->hc0 : 1) : CALC12(b->f6c, v);
        return m;
    }
    q = b->f6c;
    i = v - q->f50;
    if (i < 0) i = 0;
    else if (i >= (*(u16 **)&D_003044A0)[0]) i = (*(u16 **)&D_003044A0)[0] - 1;
    v = (*(u16 **)&D_003044A0)[i + 1];
    if (lo) {
        lo = (f32)lo * a->fac;
        if (v < lo) v = lo;
    }
    if (hi) {
        hi = (f32)hi * a->fac;
        if (hi < v) v = hi;
    }
    if (q->hc0 && v < q->hc0) v = q->hc0;
    else if (q->hc2 && q->hc2 < v) v = q->hc2;
    v = (f32)v * q->f78[(s32)(a->u30.d >> 6) & 0xf];
    if (b->f88 & 8) v /= 2;
    if (((b->f370 >> 37) & 3) == 1) {
        if (func_0013bf68()) v *= 2;
    }
    if (b->f148 && b->f148->f170.b.b36) {
        if (v >= b->f6c->f3c) v = b->f6c->f3c - 1;
    }
    return v ? v : 1;
}

/* needs make: uses rodata */
typedef struct { u8 p0[5]; u8 f5; u8 p6[0xe]; s32 f14; } Md9;
typedef struct { u8 p0[2]; u16 f2; f32 f4; f32 f8; } Bn9;
typedef struct { u8 p0[0x24]; f32 f24; f32 f28; } Rg9;
typedef struct { u8 p0[0x18]; Rg9 *f18; } Ln9;
typedef struct {
    u8 p0[0x10];
    V4 f10;
    u8 p20[0x24];
    f32 f44;
    u8 p48[8];
    V4 f50;
    u8 p60[0x70];
    f32 fd0[4][4];
    u8 p110[0x134 - 0x110];
    Md9 *f134;
    u8 p138[0x14c - 0x138];
    Ln9 *f14c;
    u8 p150[0x15c - 0x150];
    s32 f15c;
    u8 p160[0x370 - 0x160];
    u64 f370;
} Ob9;
typedef struct { f32 a[4]; V4 pos; } Tm9;
extern void func_002675a8(V4 *, V4 *);
extern void func_00267518(V4 *, V4 *, V4 *);
extern void func_002672f8(V4 *, f32 (*)[4], V4 *);
extern Bn9 *func_0015c960(Ob9 *, s32, s32, s32);
extern void func_0015bad0(Ob9 *, s32, Tm9 *);
extern void func_0012ec88(Ob9 *, V4 *);
extern s32 func_00131558(Ob9 *, s32);
extern void func_00162218(s32, s32, V4 *, f32);
void func_001315c0(Ob9 *o, s32 id, V4 *out, f32 t) {
    V4 v;
    Tm9 tm;
    s32 mdl;
    Bn9 *b;
    Ln9 *ln;
    Rg9 *rg;
    Md9 *md;

    if (!o || !((s32)(o->f370 >> 32) & 1)) {
        func_002675a8(out, &D_002C58A0);
        return;
    }
    if (id & 0x8000) {
        md = o->f134;
        mdl = (md && md->f5) ? md->f14 : 0;
        switch (id) {
        case 0x8005:
            b = func_0015c960(o, 1, -1, 0);
            if (!b) b = func_0015c960(o, 0, -1, 0);
            if (!b) b = (Bn9 *)mdl;
            if (!b) {
                func_002675a8(out, &o->f10);
                break;
            }
            func_001315c0(o, b->f2, out, b->f4);
            out->y -= b->f8 * o->f44;
            break;
        case 0x8003:
            if (mdl) {
                func_0015bad0(o, mdl, &tm);
                func_002675a8(out, &tm.pos);
            } else {
                func_002675a8(out, &o->f50);
            }
            break;
        case 0x8004:
            if (mdl) {
                func_0015bad0(o, mdl, &tm);
                func_002675a8(out, &tm.pos);
                out->y -= tm.a[2];
            } else {
                func_002675a8(out, &o->f50);
            }
            break;
        case 0x8007:
            func_0012ec88(o, out);
            break;
        case 0x8006:
            if (mdl) {
                func_0015bad0(o, mdl, &tm);
                func_002675a8(out, &tm.pos);
                out->y -= tm.a[2] * 1.5f;
            } else {
                func_002675a8(out, &o->f50);
            }
            break;
        default:
            *(s32 *)&v.x = 0;
            *(s32 *)&v.y = 0;
            *(s32 *)&v.w = 0;
            v.z = t * 100.0f;
            switch (id) {
            case 0x8002:
                func_002675a8(out, &o->f50);
                break;
            case 0x8008:
                v.x = v.z;
                *(s32 *)&v.z = 0;
                func_002675a8(out, &o->f50);
                break;
            default:
                func_002675a8(out, &o->f10);
                break;
            }
            func_002672f8(&v, o->fd0, &v);
            func_00267518(out, out, &v);
            break;
        }
    } else {
        if (id == 48) {
            ln = o->f14c;
            if (ln) {
                rg = ln->f18;
                t = rg->f28 + t * (rg->f24 - rg->f28);
            }
        }
        id = func_00131558(o, id);
        if (id <= 0) func_002675a8(out, &o->f10);
        else func_00162218(o->f15c, id, out, t);
    }
    out->w = 1.0f;
}
#include "data/data_002E.h"
#include "data/pieces/D_002C5958.h"
