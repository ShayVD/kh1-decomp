#include "common.h"
typedef struct {
    u8 pad0[0x48];
    s32 x48;
    u8 pad4c[0x74 - 0x4c];
    f32 sx, sy;
    u8 pad7c[0x90 - 0x7c];
    s32 x90;
    f32 x94;
    u8 pad98[0xb0 - 0x98];
    s32 xb0, xb4;
    s16 xb8, xba;
    u8 padbc[0xc0 - 0xbc];
    s16 c0, c2, c4, c6, c8, ca, cc, ce, d0, d2, d4, d6, d8, da;
} Wnd;
typedef struct { u64 a, b; } Q;
typedef struct { s32 u, v, p0, p1; s32 x, y, z, f; } UX;
typedef struct { s32 x, y, z, f; } XY;
typedef struct {
    u64 tag, regs;
    UX s[4];
    u64 tag2, regs2;
    u64 col2, q2;
    XY v[2];
    u64 col, q;
    XY w[2];
} P;
typedef struct { u64 tag, regs; UX s[8]; } P2;
typedef struct { u64 tag, regs; UX s[2]; } H2;
extern u8 D_003F1E70[];
extern u8 D_003F1A70[];
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
u64 *func_00122048(s32, s32);
s32 sceGsSyncPath(s32, s32);
void func_001220b8(void *);
s32 func_001f4570(Wnd *);
s32 func_001f45e0(Wnd *);
s32 func_001f4378(Wnd *);
u64 *func_0011fb38(s32, s32, u64 *);
f32 sinf(f32);
u32 func_001edd88(s32, s32);
CONTEXT_ONLY s32 func_001fd538(Wnd *o) { return (o->da + 8) >> 4; }

static inline s32 inl_sc(s32 v, s32 c, f32 fc, f32 s) { return fc + (f32)(v - c) * s; }

void func_00203028(Wnd *o, s32 x0, s32 y, s32 x1, s32 c) {
    s32 xs[2];
    s32 yy[2];
    u64 *buf;
    Q *h;
    Q *q;
    u32 ub;
    s32 Y, n, hf, a, b, cur, i, fl, cx, cy;
    f32 sx, sy, fcx, fcy;
    s32 X0, Y0, X1, Y2, X4, X5;
    if (o->d8 < 2) return;
    func_00266f38(func_00266c08(2), D_003F1E70);
    buf = func_00122048(2048, 128);
    h = (Q *)buf + 1;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    h->a = 0x6000000000008001;
    h->b = 0xeeeeee;
    q = h + 1;
    q->b = 63;
    q->a = 0;
    q++;
    q->a = 0x7bf8621413d7c;
    q->b = 6;
    q++;
    q->b = 22;
    q->a = 0x4007bf8001300000;
    q++;
    q->b = 22;
    q->a = 0x7bf8001400000;
    q++;
    q->a = 68;
    q->b = 66;
    q++;
    q->a = func_001edd88(c, o->x90);
    q->b = 1;
    q++;
    xs[0] = o->xb0 + (x0 << 4);
    xs[1] = o->xb0 + (x1 << 4);
    Y = o->xb4 + (y << 4);
    n = (((xs[1] - xs[0]) >> 4) - 11) / 4 - 2;
    if (n < 0) n = 0;
    else if (n > 50) n = 50;
    hf = n / 2;
    cur = func_001fd538(o);
    a = cur;
    if (n < a) a = n;
    b = o->d8 - cur - 1;
    if (n < b) b = n;
    if (n < a + b) {
        if (a == n) {
            if (hf < b) { b = hf; a = b; }
            else a -= b;
        } else if (b == n) {
            if (hf < a) { b = hf; a = b; }
            else b -= a;
        } else if (!(a < hf)) {
            if (!(b < hf)) { b = hf; a = b; }
            else a = n - b;
        } else if (!(b < hf)) {
            b = n - a;
        }
    }
    ((P2 *)q)->tag = 0x80aa400000008002;
    ((P2 *)q)->regs = 0x43434343;
    if (a) {
        ((P2 *)q)->s[0].u = 2280; ((P2 *)q)->s[0].v = 1064; ((P2 *)q)->s[1].u = 2120; ((P2 *)q)->s[1].v = 1064;
        ((P2 *)q)->s[2].u = 2280; ((P2 *)q)->s[2].v = 1256; ((P2 *)q)->s[3].u = 2120; ((P2 *)q)->s[3].v = 1256;
    } else {
        ((P2 *)q)->s[0].u = 2472; ((P2 *)q)->s[0].v = 1064; ((P2 *)q)->s[1].u = 2312; ((P2 *)q)->s[1].v = 1064;
        ((P2 *)q)->s[2].u = 2472; ((P2 *)q)->s[2].v = 1256; ((P2 *)q)->s[3].u = 2312; ((P2 *)q)->s[3].v = 1256;
    }
    if (b) {
        ((P2 *)q)->s[4].u = 2120; ((P2 *)q)->s[4].v = 1064; ((P2 *)q)->s[5].u = 2280; ((P2 *)q)->s[5].v = 1064;
        ((P2 *)q)->s[6].u = 2120; ((P2 *)q)->s[6].v = 1256; ((P2 *)q)->s[7].u = 2280; ((P2 *)q)->s[7].v = 1256;
    } else {
        ((P2 *)q)->s[4].u = 2328; ((P2 *)q)->s[4].v = 1064; ((P2 *)q)->s[5].u = 2488; ((P2 *)q)->s[5].v = 1064;
        ((P2 *)q)->s[6].u = 2328; ((P2 *)q)->s[6].v = 1256; ((P2 *)q)->s[7].u = 2488; ((P2 *)q)->s[7].v = 1256;
    }

    ((P2 *)q)->s[0].x = xs[0];
    ((P2 *)q)->s[0].y = Y;
    ((P2 *)q)->s[0].z = 0x100000;
    ((P2 *)q)->s[0].f = 0x8000;
    ((P2 *)q)->s[1].x = xs[0] + 144;
    ((P2 *)q)->s[1].y = Y;
    ((P2 *)q)->s[1].z = 0x100000;
    ((P2 *)q)->s[1].f = 0x8000;
    ((P2 *)q)->s[2].x = ((P2 *)q)->s[0].x;
    ((P2 *)q)->s[2].y = Y + 192;
    ((P2 *)q)->s[2].z = 0x100000;
    ((P2 *)q)->s[2].f = 0;
    ((P2 *)q)->s[3].x = ((P2 *)q)->s[1].x;
    ((P2 *)q)->s[3].y = Y + 192;
    ((P2 *)q)->s[3].z = 0x100000;
    ((P2 *)q)->s[3].f = 0;
    ((P2 *)q)->s[4].x = xs[1];
    ((P2 *)q)->s[4].y = Y;
    ((P2 *)q)->s[4].z = 0x100000;
    ((P2 *)q)->s[4].f = 0x8000;
    ((P2 *)q)->s[5].x = xs[1] + 144;
    ((P2 *)q)->s[5].y = Y;
    ((P2 *)q)->s[5].z = 0x100000;
    ((P2 *)q)->s[5].f = 0x8000;
    ((P2 *)q)->s[6].x = ((P2 *)q)->s[4].x;
    ((P2 *)q)->s[6].y = Y + 192;
    ((P2 *)q)->s[6].z = 0x100000;
    ((P2 *)q)->s[6].f = 0;
    ((P2 *)q)->s[7].x = ((P2 *)q)->s[5].x;
    ((P2 *)q)->s[7].y = Y + 192;
    ((P2 *)q)->s[7].z = 0x100000;
    ((P2 *)q)->s[7].f = 0;

    fl = o->x48 & 1;
    if (fl) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->sx;
        sy = o->sy;
        fcx = cx;
        fcy = cy;
        X0 = inl_sc(((P2 *)q)->s[0].x, cx, fcx, sx);
        Y0 = inl_sc(((P2 *)q)->s[0].y, cy, fcy, sy);
        X1 = inl_sc(((P2 *)q)->s[1].x, cx, fcx, sx);
        Y2 = inl_sc(((P2 *)q)->s[2].y, cy, fcy, sy);
        X4 = inl_sc(((P2 *)q)->s[4].x, cx, fcx, sx);
        X5 = inl_sc(((P2 *)q)->s[5].x, cx, fcx, sx);
        ((P2 *)q)->s[0].x = X0; ((P2 *)q)->s[0].y = Y0;
        ((P2 *)q)->s[1].x = X1; ((P2 *)q)->s[1].y = Y0;
        ((P2 *)q)->s[2].x = X0; ((P2 *)q)->s[2].y = Y2;
        ((P2 *)q)->s[3].x = X1; ((P2 *)q)->s[3].y = Y2;
        ((P2 *)q)->s[4].x = X4; ((P2 *)q)->s[4].y = Y0;
        ((P2 *)q)->s[5].x = X5; ((P2 *)q)->s[5].y = Y0;
        ((P2 *)q)->s[6].x = X4; ((P2 *)q)->s[6].y = Y2;
        ((P2 *)q)->s[7].x = X5; ((P2 *)q)->s[7].y = Y2;
    }
    buf[0] = ((((s32)((P2 *)q + 1) - (s32)buf) >> 4) - 1) | 0x70000000;
    func_00266f38(func_00266c08(2), (void *)ub);
    sceGsSyncPath(0, 0);
    yy[0] = ((P2 *)q)->s[0].y;
    yy[1] = ((P2 *)q)->s[2].y;
    ((H2 *)h)->tag = 0x40ab400000008001;
    ((H2 *)h)->regs = 0x4343;
    xs[0] += 176;
    ((H2 *)h)->s[0].u = 2040; ((H2 *)h)->s[0].v = 1064;
    ((H2 *)h)->s[0].y = yy[0]; ((H2 *)h)->s[0].z = 0x100000; ((H2 *)h)->s[0].f = 0x8000;
    ((H2 *)h)->s[1].u = 2056; ((H2 *)h)->s[1].v = 1224;
    ((H2 *)h)->s[1].y = yy[1]; ((H2 *)h)->s[1].z = 0x100000; ((H2 *)h)->s[1].f = 0;
    buf[0] = ((((s32)((H2 *)h + 1) - (s32)buf) >> 4) - 1) | 0x70000000;
    for (i = a; i > 0; i--) {
        ((H2 *)h)->s[0].x = xs[0];
        ((H2 *)h)->s[1].x = xs[0] + 32;
        if (fl) {
            ((H2 *)h)->s[0].x = inl_sc(((H2 *)h)->s[0].x, cx, cx, sx);
            ((H2 *)h)->s[1].x = inl_sc(((H2 *)h)->s[1].x, cx, cx, sx);
        }
        func_00266f38(func_00266c08(2), (void *)ub);
        sceGsSyncPath(0, 0);
        xs[0] += 64;
    }
    xs[1] -= 64;
    for (i = b; i > 0; i--) {
        ((H2 *)h)->s[0].x = xs[1];
        ((H2 *)h)->s[1].x = xs[1] + 32;
        if (fl) {
            ((H2 *)h)->s[0].x = inl_sc(((H2 *)h)->s[0].x, cx, cx, sx);
            ((H2 *)h)->s[1].x = inl_sc(((H2 *)h)->s[1].x, cx, cx, sx);
        }
        func_00266f38(func_00266c08(2), (void *)ub);
        sceGsSyncPath(0, 0);
        xs[1] -= 64;
    }
    func_001220b8(buf);
}
