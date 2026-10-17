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

typedef struct { f32 x, y, z, w; } V4;
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
extern V4 D_002C58A0;
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
