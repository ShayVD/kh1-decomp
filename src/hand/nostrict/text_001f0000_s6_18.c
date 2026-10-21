#include "common.h"

#include "data/pieces/D_003E8E28.h"
typedef Glyph_3e8e28 Glyph;
typedef struct {
    u8 pad0[0x48];
    s32 x48;
    u8 pad4c[0x74 - 0x4c];
    f32 x74;
    f32 x78;
    u8 pad7c[0x90 - 0x7c];
    s32 x90;
    u8 pad94[0xb0 - 0x94];
    s32 xb0;
    s32 xb4;
} Txt9;
typedef struct {
    u64 tex0, reg;
    s32 u0, v0; u64 pad18;
    s32 x0, y0, z0, f0;
    s32 u1, v1; u64 pad38;
    s32 x1, y1, z1, f1;
} GSpr;
typedef struct { u64 h[12]; GSpr g; } Pkt;
extern s32 D_003E8E00;
extern s32 D_003E8D00[];
#include "data/pieces/D_003F2270.h"
extern s32 D_003F2BD0;
extern s32 D_003F2BD4;
u64 *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(s32, s32);
s32 func_001f4570(Txt9 *);
s32 func_001f45e0(Txt9 *);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 sceGsSyncPath(s32, s32);
typedef struct { s32 u, v; u64 pad; u64 rgba, q; s32 x, y, z, f; } Vx;
#include "data/types/nostrict_text_001f0000_s6_18.h"
extern Spr D_003E9138[];
#include "data/pieces/D_003F1E70.h"
typedef struct { s32 w, h, idx, a; s32 c[4]; u32 rot; } SprPrm;
void func_001f8270(void);

void func_001fade0(Txt9 *o, s32 x, s32 y, s32 idx, s32 sz, s32 col) {
    u64 *buf;
    Pkt *p;
    void *u;
    Glyph *gl;
    s32 X, Y, ox, w, a, b, cx, cy;
    f32 sx, sy, fx, fy;
    s32 gu, gv, ww, z;
    u64 tex;
    s32 k = 22;
    func_00266f38(func_00266c08(2), (*(u8 (*)[0x400])&D_003F2270));
    buf = func_00122048(1024, 128);
    p = (Pkt *)(buf + 2);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->h[0] = 0x4000000000000001;
    p->h[1] = 0xEEEE;
    p->h[3] = 63;
    p->h[4] = 0x4007FF8001300000;
    p->h[2] = 0;
    p->h[6] = 68;
    p->h[5] = k;
    p->h[7] = 66;
    p->h[8] = func_001edd88(col, o->x90);
/*P*/
    p->h[9] = 1;
    p->h[10] = 0x50AB400000008001;
    z = 0x100000;
    p->h[11] = 0x4343E;
    gl = &D_003E8E28[idx];
    ox = o->xb0;
    Y = o->xb4 + (y << 4);
    gu = gl->f2;
    w = gl->w << 4;
    gv = gl->f4;
    X = ox + (x << 4);
    ww = w + D_003E8E00;
    a = w * sz / 18;
    b = ww * sz / 18;
    tex = ((u64)D_003E8D00[gl->f7 >> 4] << 20) | ((u64)(gl->f7 & 0xf) << 56) | (0xfff0ULL << 35);
    p->g.u0 = gu;
    p->g.v0 = gv;
    p->g.x1 = X + a;
    p->g.tex0 = tex;
    p->g.x0 = X;
    p->g.reg = k;
    p->g.f0 = 0x8000;
    p->g.y0 = Y;
    p->g.u1 = gu + w;
    p->g.v1 = gv + 288;
    p->g.y1 = Y + (sz << 4);
    p->g.z0 = z;
    p->g.f1 = 0;
    p->g.z1 = z;
/*Q*/
    if (o->x48 & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
        p->g.x0 = fx + (f32)(p->g.x0 - cx) * sx;
        p->g.y0 = fy + (f32)(p->g.y0 - cy) * sy;
        p->g.x1 = fx + (f32)(p->g.x1 - cx) * sx;
        p->g.y1 = fy + (f32)(p->g.y1 - cy) * sy;
    }
    buf[0] = (((s32)(p + 1) - (s32)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
    D_003F2BD0 = (X + b - ox) >> 4;
    D_003F2BD4 = y;
}

s32 func_001fc330(Txt9 *o, s32 x, s32 y, s32 w, s32 h, s32 idx, s32 a, s32 c0, s32 c1, s32 c2, s32 c3) {
    u64 *buf;
    u64 *p;
    void *u;
    Spr *t;
    s32 X, Y, W = w << 4;
    s32 al;
    s32 one, z;
    s32 cx, cy, nx, ny, nx2, ny2;
    f32 fx, fy, sx, sy;
    func_00266f38(func_00266c08(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p[0] = 0x4000000000000001;
    p[1] = 0xEEEE;
    p[2] = 0;
    p[3] = 63;
    p[4] = 0x4007BF8001300000;
    p[5] = 22;
    p[6] = ((u64)a << 56) | 0x0007BF8001400000;
    p[7] = 22;
    p[8] = 68;
    p[9] = 66;
    p[10] = 0x30AE400000008004;
    p[11] = 1251;
/*P*/
    p += 12;
    one = 1;
    al = o->x90;
    X = o->xb0 + (x << 4);
    t = &D_003E9138[idx];
    Y = o->xb4 + (y << 4);
    W = !w ? t->w : W;
    h = h ? h << 4 : t->h;
    z = 0x100000;
/*Q*/
    ((Vx *)p)[0].u = t->uv[0];
    ((Vx *)p)[0].v = t->uv[1];
    ((Vx *)p)[0].rgba = func_001edd88(c0, al);
    ((Vx *)p)[0].q = one;
    ((Vx *)p)[0].x = X;
    ((Vx *)p)[0].y = Y;
    ((Vx *)p)[0].z = z;
    ((Vx *)p)[0].f = 0;
    ((Vx *)p)[1].u = t->uv[2];
    ((Vx *)p)[1].v = t->uv[3];
    ((Vx *)p)[1].rgba = func_001edd88(c1, al);
    ((Vx *)p)[1].q = one;
    ((Vx *)p)[1].x = ((Vx *)p)[0].x + W;
    ((Vx *)p)[1].y = ((Vx *)p)[0].y;
    ((Vx *)p)[1].z = z;
    ((Vx *)p)[1].f = 0;
    ((Vx *)p)[2].u = t->uv[4];
    ((Vx *)p)[2].v = t->uv[5];
    ((Vx *)p)[2].rgba = func_001edd88(c2, al);
    ((Vx *)p)[2].q = one;
    ((Vx *)p)[2].x = ((Vx *)p)[0].x;
    ((Vx *)p)[2].y = ((Vx *)p)[0].y + h;
    ((Vx *)p)[2].z = z;
    ((Vx *)p)[2].f = 0;
    ((Vx *)p)[3].u = t->uv[6];
    ((Vx *)p)[3].v = t->uv[7];
    ((Vx *)p)[3].rgba = func_001edd88(c3, al);
    ((Vx *)p)[3].q = one;
    ((Vx *)p)[3].x = ((Vx *)p)[1].x;
    ((Vx *)p)[3].y = ((Vx *)p)[2].y;
    ((Vx *)p)[3].z = z;
    ((Vx *)p)[3].f = 0;
    if (o->x48 & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
        nx = fx + (f32)(((Vx *)p)[0].x - cx) * sx;
        ny = fy + (f32)(((Vx *)p)[0].y - cy) * sy;
        nx2 = fx + (f32)(((Vx *)p)[1].x - cx) * sx;
        ny2 = fy + (f32)(((Vx *)p)[2].y - cy) * sy;
        ((Vx *)p)[2].x = ((Vx *)p)[0].x = nx;
        ((Vx *)p)[1].y = ((Vx *)p)[0].y = ny;
        ((Vx *)p)[3].x = ((Vx *)p)[1].x = nx2;
        ((Vx *)p)[3].y = ((Vx *)p)[2].y = ny2;
    }
    buf[0] = (((s32)((Vx *)p + 4) - (s32)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
    return x + (W >> 4);
}

/* rodata */
s32 func_001fc750(Txt9 *o, s32 x, s32 y, SprPrm *pr) {
    u64 *buf;
    u64 *p;
    void *u;
    Spr *t;
    s32 X, Y, W, H, al;
    s32 cx, cy;
    f32 fx, fy, sx, sy;
    func_00266f38(func_00266c08(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p[0] = 0x4000000000000001;
    p[1] = 0xEEEE;
    p[2] = 0;
    p[3] = 63;
    p[4] = 0x4007BF8001300000;
    p[5] = 22;
    p[6] = ((u64)pr->a << 56) | 0x0007BF8001400000;
    p[7] = 22;
    p[8] = 68;
    p[9] = 66;
    p[10] = 0x30AE400000008004;
    p[11] = 1251;
    p += 12;
    t = &D_003E9138[pr->idx];
    X = o->xb0 + (x << 4);
    Y = o->xb4 + (y << 4);
    al = o->x90;
    W = pr->w ? pr->w << 4 : t->w;
    H = pr->h ? pr->h << 4 : t->h;
    switch (pr->rot) {
    case 0:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[0].x = X;
        ((Vx *)p)[0].y = Y;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[1].x = xr;
        ((Vx *)p)[1].y = Y;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[2].x = X;
        ((Vx *)p)[2].y = yb;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[3].x = xr;
        ((Vx *)p)[3].y = yb;
        }
        break;
    case 1:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[0].x = xr;
        ((Vx *)p)[0].y = Y;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[1].x = X;
        ((Vx *)p)[1].y = Y;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[2].x = xr;
        ((Vx *)p)[2].y = yb;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[3].x = X;
        ((Vx *)p)[3].y = yb;
        }
        break;
    case 2:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[0].x = X;
        ((Vx *)p)[0].y = yb;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[1].x = xr;
        ((Vx *)p)[1].y = yb;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[2].x = X;
        ((Vx *)p)[2].y = Y;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[3].x = xr;
        ((Vx *)p)[3].y = Y;
        }
        break;
    case 3:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[0].x = X;
        ((Vx *)p)[0].y = yb;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[1].x = X;
        ((Vx *)p)[1].y = Y;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[2].x = xr;
        ((Vx *)p)[2].y = yb;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[3].x = xr;
        ((Vx *)p)[3].y = Y;
        }
        break;
    case 4:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[0].x = xr;
        ((Vx *)p)[0].y = Y;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[1].x = xr;
        ((Vx *)p)[1].y = yb;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[2].x = X;
        ((Vx *)p)[2].y = Y;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[3].x = X;
        ((Vx *)p)[3].y = yb;
        }
        break;
    }
    ((Vx *)p)[0].u = t->uv[0];
    ((Vx *)p)[0].v = t->uv[1];
    ((Vx *)p)[0].q = 1;
    ((Vx *)p)[0].z = 0x100000;
    ((Vx *)p)[0].f = 0;
    ((Vx *)p)[1].u = t->uv[2];
    ((Vx *)p)[1].v = t->uv[3];
    ((Vx *)p)[1].q = 1;
    ((Vx *)p)[1].z = 0x100000;
    ((Vx *)p)[1].f = 0;
    ((Vx *)p)[2].u = t->uv[4];
    ((Vx *)p)[2].v = t->uv[5];
    ((Vx *)p)[2].q = 1;
    ((Vx *)p)[2].z = 0x100000;
    ((Vx *)p)[2].f = 0;
    ((Vx *)p)[3].u = t->uv[6];
    ((Vx *)p)[3].v = t->uv[7];
    ((Vx *)p)[3].q = 1;
    ((Vx *)p)[3].z = 0x100000;
    ((Vx *)p)[3].f = 0;
    if (o->x48 & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
        ((Vx *)p)[0].x = fx + (f32)(((Vx *)p)[0].x - cx) * sx;
        ((Vx *)p)[0].y = fy + (f32)(((Vx *)p)[0].y - cy) * sy;
        ((Vx *)p)[1].x = fx + (f32)(((Vx *)p)[1].x - cx) * sx;
        ((Vx *)p)[1].y = fy + (f32)(((Vx *)p)[1].y - cy) * sy;
        ((Vx *)p)[2].x = fx + (f32)(((Vx *)p)[2].x - cx) * sx;
        ((Vx *)p)[2].y = fy + (f32)(((Vx *)p)[2].y - cy) * sy;
        ((Vx *)p)[3].x = fx + (f32)(((Vx *)p)[3].x - cx) * sx;
        ((Vx *)p)[3].y = fy + (f32)(((Vx *)p)[3].y - cy) * sy;
    }
    buf[0] = (((s32)((Vx *)p + 4) - (s32)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
    return x + (W >> 4);
}

s32 func_001fcdc8(s32 x, s32 y, s32 w, s32 h, s32 idx, s32 a, s32 c0, s32 c1) {
    u64 *buf;
    u64 *p;
    void *u;
    Spr *t;
    s32 X, Y, W, H;
    func_001f8270();
    func_00266f38(func_00266c08(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p[0] = 0x4000000000000001;
    p[1] = 0xEEEE;
    p[2] = 0;
    p[3] = 63;
    p[4] = 0x4007BF8001300000;
    p[5] = 22;
    p[6] = ((u64)a << 56) | 0x0007BF8001400000;
    p[7] = 22;
    p[8] = 68;
    p[9] = 66;
    p[10] = 0x30AE400000008004;
    p[11] = 1251;
    p += 12;
    X = (x << 4) + 0x7000;
    t = &D_003E9138[idx];
    Y = (y << 4) + 0x7400;
    W = w ? w << 4 : t->w;
    H = h ? h << 4 : t->h;
    ((Vx *)p)[0].u = t->uv[0];
    ((Vx *)p)[0].v = t->uv[1];
    ((Vx *)p)[0].rgba = c0;
    ((Vx *)p)[0].q = 1;
    ((Vx *)p)[0].x = X;
    ((Vx *)p)[0].y = Y;
    ((Vx *)p)[0].z = 0x100000;
    ((Vx *)p)[0].f = 0;
    ((Vx *)p)[1].u = t->uv[2];
    ((Vx *)p)[1].v = t->uv[3];
    ((Vx *)p)[1].rgba = c0;
    ((Vx *)p)[1].q = 1;
    ((Vx *)p)[1].x = X + W;
    ((Vx *)p)[1].y = Y;
    ((Vx *)p)[1].z = 0x100000;
    ((Vx *)p)[1].f = 0;
    ((Vx *)p)[2].u = t->uv[4];
    ((Vx *)p)[2].v = t->uv[5];
    ((Vx *)p)[2].rgba = c1;
    ((Vx *)p)[2].q = 1;
    ((Vx *)p)[2].x = X;
    ((Vx *)p)[2].y = Y + H;
    ((Vx *)p)[2].z = 0x100000;
    ((Vx *)p)[2].f = 0;
    ((Vx *)p)[3].u = t->uv[6];
    ((Vx *)p)[3].v = t->uv[7];
    ((Vx *)p)[3].rgba = c1;
    ((Vx *)p)[3].q = 1;
    ((Vx *)p)[3].x = X + W;
    ((Vx *)p)[3].y = Y + H;
    ((Vx *)p)[3].z = 0x100000;
    ((Vx *)p)[3].f = 0;
    buf[0] = (((s32)((Vx *)p + 4) - (s32)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
    return x + (W >> 4);
}
#include "data/data_003E.h"
#include "data/data_003F.h"
#include "data/pieces/D_003E9138.h"
