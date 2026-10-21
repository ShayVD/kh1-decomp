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
    s16 c0, c2, c4, c6, c8, ca, cc, ce, d0;
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
#include "data/pieces/D_003F1E70.h"
#include "data/pieces/D_003F1A70.h"
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

static inline s32 inl_sc(s32 v, s32 c, f32 fc, f32 s) { return fc + (f32)(v - c) * s; }

void func_00203a10(Wnd *o, s32 x) {
    s32 ys[2];
    s32 ms[2];
    u64 *buf;
    Q *q;
    u32 ub, al, col;
    s32 t, a, b, X, h;
    s32 u0, v0, u1, v1;
    s32 cx, cy;
    f32 r, sx, sy, fcx, fcy;
    s32 X0, X1, X2, X3, Y0, Y1, Y2, Y3, Y4, Y5, Y6, Y7;
    if (o->cc == 0) return;
    if (!(o->ce < o->cc)) return;
    func_00266f38(func_00266c08(2), D_003F1E70);
    buf = func_00122048(1024, 128);
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    q = (Q *)buf + 1;
    q->a = 0x6000000000008001;
    q->b = 0xeeeeee;
    q++;
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
    t = o->x94;
    al = o->x90;
    al <<= 24;
    r = sinf((f32)(t % 64) * 0.015625f * 3.1415928f);
    a = (s32)(r * 64.0f) + 64;
    b = (s32)(r * 16.0f) + 64;
    col = (a | al) | ((b << 16) | (a << 8));
    q->b = 1;
    q->a = col;
    q++;
    ((P *)q)->tag = 0x40ab400000008002;
    ((P *)q)->regs = 0x4343;
    X = o->xb0 + (x << 4);
    ys[0] = o->xb4 + o->c0;
    ys[1] = ys[0] + (((o->c4 >> 4) * o->ce - (o->c8 >> 4) - 9) << 4);
    if (o->d0 >> 4) {
        ((P *)q)->s[0].u = 1768; ((P *)q)->s[0].v = 1048; ((P *)q)->s[1].u = 1960; ((P *)q)->s[1].v = 1192;
    } else {
        ((P *)q)->s[0].u = 1768; ((P *)q)->s[0].v = 1240; ((P *)q)->s[1].u = 1960; ((P *)q)->s[1].v = 1384;
    }
    if (o->cc != (o->d0 >> 4) + o->ce) {
        ((P *)q)->s[2].u = 1768; ((P *)q)->s[2].v = 1176; ((P *)q)->s[3].u = 1960; ((P *)q)->s[3].v = 1032;
    } else {
        ((P *)q)->s[2].u = 1768; ((P *)q)->s[2].v = 1368; ((P *)q)->s[3].u = 1960; ((P *)q)->s[3].v = 1224;
    }
    ((P *)q)->s[0].x = X; ((P *)q)->s[0].y = ys[0]; ((P *)q)->s[0].z = 0x100000; ((P *)q)->s[0].f = 0x8000;
    ((P *)q)->s[1].x = X + 192; ((P *)q)->s[1].y = ys[0] + 144; ((P *)q)->s[1].z = 0x100000; ((P *)q)->s[1].f = 0;
    ((P *)q)->s[2].x = X; ((P *)q)->s[2].y = ys[1]; ((P *)q)->s[2].z = 0x100000; ((P *)q)->s[2].f = 0x8000;
    ((P *)q)->s[3].x = X + 192; ((P *)q)->s[3].y = ys[1] + 144; ((P *)q)->s[3].z = 0x100000; ((P *)q)->s[3].f = 0;
    ((P *)q)->tag2 = 0x3023400000008002;
    ((P *)q)->regs2 = 0x44e;
    ys[0] += 176;
    ys[1] -= 32;
    ((P *)q)->col2 = al | 0x404040;
    ((P *)q)->q2 = 1;
    ((P *)q)->v[0].x = ((P *)q)->s[0].x; ((P *)q)->v[0].y = ys[0]; ((P *)q)->v[0].z = 0x100000; ((P *)q)->v[0].f = 0;
    ((P *)q)->v[1].x = ((P *)q)->s[1].x; ((P *)q)->v[1].y = ys[1]; ((P *)q)->v[1].z = 0x100000; ((P *)q)->v[1].f = 0;
    h = ys[1] - ys[0];
    ms[0] = ys[0] + (h * o->d0 >> 4) / o->cc;
    ms[1] = ms[0] + h * o->ce / o->cc;
    ((P *)q)->col = col;
    ((P *)q)->q = 1;
    ((P *)q)->w[0].x = ((P *)q)->s[0].x + 48; ((P *)q)->w[0].y = ms[0]; ((P *)q)->w[0].z = 0x100000; ((P *)q)->w[0].f = 0x8000;
    ((P *)q)->w[1].x = ((P *)q)->s[1].x - 48; ((P *)q)->w[1].y = ms[1]; ((P *)q)->w[1].z = 0x100000; ((P *)q)->w[1].f = 0;
    if (o->x48 & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->sx;
        sy = o->sy;
        fcx = cx;
        fcy = cy;
        X0 = inl_sc(((P *)q)->s[0].x, cx, fcx, sx);
        X1 = inl_sc(((P *)q)->s[1].x, cx, fcx, sx);
        Y0 = inl_sc(((P *)q)->s[0].y, cy, fcy, sy);
        Y1 = inl_sc(((P *)q)->s[1].y, cy, fcy, sy);
        Y2 = inl_sc(((P *)q)->s[2].y, cy, fcy, sy);
        Y3 = inl_sc(((P *)q)->s[3].y, cy, fcy, sy);
        Y4 = inl_sc(((P *)q)->v[0].y, cy, fcy, sy);
        Y5 = inl_sc(((P *)q)->v[1].y, cy, fcy, sy);
        X2 = inl_sc(((P *)q)->w[0].x, cx, fcx, sx);
        Y6 = inl_sc(((P *)q)->w[0].y, cy, fcy, sy);
        X3 = inl_sc(((P *)q)->w[1].x, cx, fcx, sx);
        Y7 = inl_sc(((P *)q)->w[1].y, cy, fcy, sy);
        ((P *)q)->s[0].x = X0; ((P *)q)->s[0].y = Y0;
        ((P *)q)->s[1].x = X1; ((P *)q)->s[1].y = Y1;
        ((P *)q)->s[2].x = X0; ((P *)q)->s[2].y = Y2;
        ((P *)q)->s[3].x = X1; ((P *)q)->s[3].y = Y3;
        ((P *)q)->v[0].x = X0; ((P *)q)->v[0].y = Y4;
        ((P *)q)->v[1].x = X1; ((P *)q)->v[1].y = Y5;
        ((P *)q)->w[0].x = X2; ((P *)q)->w[0].y = Y6;
        ((P *)q)->w[1].x = X3; ((P *)q)->w[1].y = Y7;
    }
    buf[0] = ((((s32)((P *)q + 1) - (s32)buf) >> 4) - 1) | 0x70000000;
    func_00266f38(func_00266c08(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_00204d80(Wnd *w, s32 a1, s32 a2, s32 a3, s32 a4) {
    s32 xs[2];
    s32 col[3][4];
    u64 *buf, *p;
    u32 ub;
    s32 y, cx, cy, d;
    f32 f, sx, sy, fcx, fcy;
    func_00266f38(func_00266c08(2), D_003F1A70);
    buf = func_00122048(1024, 128);
    p = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p[0] = 0x1000000000008001;
    p[1] = 14;
    p = func_0011fb38(66, 68, buf + 4);
    p[0] = 0x2026400000008006;
    p[1] = 65;
    p += 2;
    if (func_001f4378(w)) {
        col[0][1] = 64;
        col[0][0] = 192;
        col[1][0] = 192;
        col[2][0] = 192;
        col[1][1] = 192;
        col[2][1] = 192;
    } else {
        col[0][1] = 64;
        col[0][0] = 192;
        col[1][0] = 192;
        col[2][0] = 192;
        col[1][1] = 192;
        col[2][1] = 96;
    }
    f = (f32)((s32)w->x94 % 16) / 16.0f;
    d = sinf(f * 3.1415928f) * 96.0f;
    xs[0] = w->xb0 + a2 * 16;
    xs[1] = w->xb0 + a3 * 16;
    y = w->xb4 + a4 * 16;
    if (a1) {
        xs[0] -= d;
        xs[1] += d;
    }
    if (w->x48 & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->sx;
        sy = w->sy;
        fcx = cx;
        fcy = cy;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[0] + 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y - 96, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[0] - 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[0] + 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y + 96, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[1] - 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y - 96, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0x8000; p += 2;
        ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[1] + 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0x8000; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[1] - 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y + 96, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
    } else {
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[0] + 96; ((XY *)p)->y = y - 96; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[0] - 96; ((XY *)p)->y = y; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[0] + 96; ((XY *)p)->y = y + 96; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[1] - 96; ((XY *)p)->y = y - 96; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0x8000; p += 2;
        ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[1] + 96; ((XY *)p)->y = y; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0x8000; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[1] - 96; ((XY *)p)->y = y + 96; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
    }
    buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
    func_00266f38(func_00266c08(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}
