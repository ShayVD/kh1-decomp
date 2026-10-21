#include "common.h"
#include "data/bss_0064.h"
typedef struct { u8 pad0[0x48]; s32 x48; u8 pad4c[0x74 - 0x4c]; f32 sx, sy; u8 pad7c[0x90 - 0x7c]; s32 x90; u8 pad94[0xb0 - 0x94]; s32 xb0, xb4; } Wnd;
typedef struct { s32 u, v; u64 pad; u64 rgba, q; s32 x, y, z, f; } Vx;
typedef struct { u16 uv[8]; s16 w, h; } Spr;
#include "data/pieces/D_003F4CF0.h"
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
u64 *func_00122048(s32, s32);
s32 sceGsSyncPath(s32, s32);
void func_001220b8(void *);
s32 func_001f4570(Wnd *);
s32 func_001f45e0(Wnd *);

s32 func_0021b860(Wnd *o, s32 x, s32 y, s32 w, s32 h, s32 idx) {
    u64 *buf;
    u64 *p;
    void *u;
    Spr *t;
    s32 cx, cy, X, Y, W, H;
    u32 c;
    f32 fx, fy, sx, sy;
    s32 nx, ny, nx2, ny2;
    buf = func_00122048(1024, 128);
    y <<= 4;
    p = buf + 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p[0] = 0x5000000000008001;
    p[1] = 0xEEEEE;
    p[2] = 0x4000D;
    p[4] = 0;
    p[3] = 71;
    p[5] = 63;
    p[6] = 0x2006E00621313600;
    t = &((Spr *)&D_003F4CF0)[idx];
    p[7] = 6;
    p[8] = 97;
    p[9] = 20;
    p[10] = 68;
    p[11] = 66;
    p[12] = 0x30AE400000008004;
    p[13] = 1251;
    p += 14;
    c = (u32)(o->x90 << 24 | 0x808080);
    X = o->xb0 + (x << 4);
    Y = o->xb4 + y;
    W = w ? w << 4 : t->w;
    H = h ? h << 4 : t->h;
    ((Vx *)p)[0].u = t->uv[0];
    ((Vx *)p)[0].v = t->uv[1];
    ((Vx *)p)[0].rgba = c;
    ((Vx *)p)[0].q = 1;
    ((Vx *)p)[0].x = X;
    ((Vx *)p)[0].y = Y;
    ((Vx *)p)[0].z = 0x100000;
    ((Vx *)p)[0].f = 0;
    ((Vx *)p)[1].u = t->uv[2];
    ((Vx *)p)[1].v = t->uv[3];
    ((Vx *)p)[1].rgba = c;
    ((Vx *)p)[1].q = 1;
    ((Vx *)p)[1].x = X + W;
    ((Vx *)p)[1].y = Y;
    ((Vx *)p)[1].z = 0x100000;
    ((Vx *)p)[1].f = 0;
    ((Vx *)p)[2].u = t->uv[4];
    ((Vx *)p)[2].v = t->uv[5];
    ((Vx *)p)[2].rgba = c;
    ((Vx *)p)[2].q = 1;
    ((Vx *)p)[2].x = X;
    ((Vx *)p)[2].y = Y + H;
    ((Vx *)p)[2].z = 0x100000;
    ((Vx *)p)[2].f = 0;
    ((Vx *)p)[3].u = t->uv[6];
    ((Vx *)p)[3].v = t->uv[7];
    ((Vx *)p)[3].rgba = c;
    ((Vx *)p)[3].q = 1;
    ((Vx *)p)[3].x = X + W;
    ((Vx *)p)[3].y = Y + H;
    ((Vx *)p)[3].z = 0x100000;
    ((Vx *)p)[3].f = 0;
    if (o->x48 & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->sx;
        sy = o->sy;
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

typedef struct { u8 pad0[0x24]; s32 x24; s32 x28; s32 x2c; u8 pad30[0x90 - 0x30]; s32 x90; u8 pad94[0xb0 - 0x94]; s32 xb0, xb4; u8 padb8[0xd8 - 0xb8]; s16 xd8, xda; } Obj;
typedef struct { u8 pad0[8]; u32 x8; u8 padc[4]; u32 x10; } Pad;
typedef struct { u8 pad0[0x24]; f32 x24; s32 x28; s32 x2c; s32 x30; } Eff;
typedef struct { u8 pad0[0x10]; s32 x10; } S3110;
#include "data/pieces/D_00425BC8.h"
extern s32 D_00643250;
extern s32 D_00643274;
extern S3110 *D_00643110; /* src/data/bss_0064.c: s32 D_00643110 */
extern s32 D_00643114;
extern s32 D_00643118;
extern u8 D_003F5E30[];
extern f32 D_003F53C0[];
extern u16 D_003F56A0[];
extern s32 D_003F34F8;
#include "data/pieces/D_003E8E08.h"
s32 func_001f42b8(void);
void func_0021e538(void);
void func_0011d768(s32);
void func_0021b5c8(s32, s32, s32, s32, f32);
s32 func_001fd668(Obj *);
s32 func_0021e898(s32);
void func_0021b4c8(s32);
s32 func_0021b7f0(void);
Eff *func_001f31a8(void *, s32);
void func_001f3e48(Eff *, Obj *);
void func_001f3758(s32);
void func_0021b820(void);
void func_0021cba8(Obj *, s32, s32, s32, s32);
void func_0021cb88(Obj *, s32, s32, s32, s32);
s32 func_0021b170(s32);
void func_00203788(Obj *, s32, s32, s32, u32);
void func_0021c9a0(Obj *, s32, s32);
void func_0021cb00(Obj *, s32, s32, s32, s32);
s32 func_0021dc38(s32);
s32 func_001c2df0(s32, s32);
void func_0010edb0(s32, s32, s32, s32, s32, s32);
s32 func_0021b800(s32);
void func_001f94f0(Obj *, s32, s32, s32, s32, s32, u32);
void func_0021e120(Obj *, s32, s32, s32);

void func_0021e8d8(Obj *o) {
    s32 ch, n, k;
    Eff *p;
    s32 t;
    if (func_001f42b8()) {
        func_0021e538();
        if (o->x28 == 0) {
            if (((Pad *)D_00425BC8)->x8 & 0x4000) {
                func_0011d768(3);
                func_0021b5c8(0xC009B, 0, 128, 128, 5.0f);
                o->x28 = 1;
            } else {
                switch (o->x2c) {
                case 0:
                    ch = 0;
                    n = o->xd8;
                    if (((Pad *)D_00425BC8)->x10 & 0x80000480) {
                        if (o->xda > 0) {
                            o->xda -= 16;
                            ch = 1;
                        }
                    } else if (((Pad *)D_00425BC8)->x10 & 0x20000820) {
                        if (o->xda < (n - 1) << 4) {
                            o->xda += 16;
                            ch = 1;
                        }
                    }
                    if (ch) func_0011d768(ch);
                    D_00643250 = func_001fd668(o);
                    if (((Pad *)D_00425BC8)->x8 & 0x1000) {
                        if (func_0021e898(D_00643274)) {
                            func_0011d768(4);
                        } else {
                            func_0011d768(2);
                            func_0021b4c8(D_00643274);
                            o->x2c++;
                        }
                    }
                    break;
                case 1:
                    if (func_0021b7f0()) {
                        p = func_001f31a8(D_003F5E30, 50);
                        if (p) {
                            func_001f3e48(p, o);
                            k = D_00643274;
                            p->x24 = D_003F53C0[k];
                            p->x2c = 256;
                            p->x28 = 0;
                            p->x30 = D_003F56A0[k];
                        }
                        o->x2c++;
                    }
                    break;
                case 2:
                    o->x2c = 0;
                    break;
                }
            }
        } else {
            if (func_0021b7f0()) {
                func_001f3758(D_00643110->x10);
                D_00643114 = 1;
            }
        }
    }
    func_0021b820();
    if (func_0021e898(D_00643274)) {
        func_0021cba8(o, 176, 8, 320, 2);
    } else if (o->x2c != 2) {
        func_0021cb88(o, 176, 8, 320, 2);
    } else if (func_0021b170(D_00643274)) {
        func_0021cba8(o, 176, 8, 320, 3);
    } else {
        func_0021cb88(o, 176, 8, 320, 3);
    }
    func_00203788(o, 372, 40, 486, 0x80C8C8C8);
    func_0021c9a0(o, 16, 72);
    func_0021cb00(o, 32, 108, 9, 30);
    func_0021cb00(o, 280, 108, 9, 30);
    t = func_001c2df0(D_003F34F8, func_0021dc38(D_00643274));
    func_0010edb0(((o->xb0 - 0x7000) >> 4) + 32, ((o->xb4 - 0x7400) >> 4) + 84, 256, D_00643250 * 2, o->x90, t);
    if (((*(s32 *)&D_003E8E08) = o->x24) && o->xd8 - 1 == func_001fd668(o)) {
        func_001f94f0(o, 0, 282, 328, func_0021b800(6), 15, 0x50461E00);
    }
    if (D_00643118 == 2) func_0021e120(o, 416, 88, D_00643274);
}
#include "data/data_003F.h"
