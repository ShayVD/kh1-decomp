#include "common.h"
typedef struct { u64 a, b; } Q;
typedef struct { u8 pad0[0x48]; s32 x48; u8 pad4c[0x68-0x4c]; u32 *x68; u8 pad6c[0x74-0x6c]; f32 sx, sy; u8 pad7c[0x88-0x7c]; s32 x88; u8 pad8c[0x90-0x8c]; s32 x90; u8 pad94[0xb0-0x94]; s32 xb0, xb4; s16 xb8, xba; } Wnd4;
typedef struct { u64 rgba, q; s32 x, y, z, f; } V3;
typedef struct { u64 h[6]; V3 v[12]; } Pk4;
extern Q D_003F1A70[];
extern u32 D_003E8E30[][12];
extern s32 D_003F1A68;
extern u8 D_003F27D0[];
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
Q *func_00122048(s32, s32);
s32 func_001f4570(Wnd4 *o) { return 0; }
s32 func_001f45e0(Wnd4 *);
s32 sceGsSyncPath(s32, u16);
void func_001220b8(void *);

void func_001f4778(Wnd4 *o) {
    u64 *buf;
    Pk4 *s;
    void *u;
    u32 *t;
    u32 a;
    s32 bx, by, w, h, cx, cy;
    f32 fx, fy, sx, sy;
    s32 X, X128, Xw, X32, X160, Xw32, Y, Y128, Yh, Y32, Y160, Yh32;
    func_00266f38(func_00266c08(2), D_003F1A70);
    if (o->x88 & 0x10) {
        func_00266f38(func_00266c08(2), D_003F27D0);
    }
    buf = (u64 *)func_00122048(1024, 128);
    s = (Pk4 *)(buf + 2);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    s->h[0] = 0x1026400000008001;
    s->h[1] = 14;
    s->h[2] = 68;
    s->h[3] = 66;
    s->h[4] = 0x200000000000800c;
    s->h[5] = 78;
    a = o->x90 << 24;
    t = o->x68;
    bx = o->xb0;
    by = o->xb4;
    w = o->xb8;
    h = o->xba;
    if (t == 0) t = D_003E8E30[D_003F1A68];
    s->v[0].rgba = t[0] | a; s->v[0].q = 1; s->v[0].x = bx; s->v[0].y = by + 128; s->v[0].z = 0x100000; s->v[0].f = 0;
    s->v[1].rgba = t[2] | a; s->v[1].q = 1; s->v[1].x = bx; s->v[1].y = by + h; s->v[1].z = 0x100000; s->v[1].f = 0;
    s->v[2].rgba = t[0] | a; s->v[2].q = 1; s->v[2].x = bx + 128; s->v[2].y = by; s->v[2].z = 0x100000; s->v[2].f = 0;
    s->v[3].rgba = t[2] | a; s->v[3].q = 1; s->v[3].x = bx + 128; s->v[3].y = by + h; s->v[3].z = 0x100000; s->v[3].f = 0;
    s->v[4].rgba = t[1] | a; s->v[4].q = 1; s->v[4].x = bx + w; s->v[4].y = by; s->v[4].z = 0x100000; s->v[4].f = 0;
    s->v[5].rgba = t[3] | a; s->v[5].q = 1; s->v[5].x = bx + w; s->v[5].y = by + h; s->v[5].z = 0x100000; s->v[5].f = 0;
    s->v[6].rgba = t[4] | a; s->v[6].q = 1; s->v[6].x = bx + 32; s->v[6].y = by + 160; s->v[6].z = 0x100000; s->v[6].f = 0x8000;
    s->v[7].rgba = t[6] | a; s->v[7].q = 1; s->v[7].x = bx + 32; s->v[7].y = by + h - 32; s->v[7].z = 0x100000; s->v[7].f = 0x8000;
    s->v[8].rgba = t[4] | a; s->v[8].q = 1; s->v[8].x = bx + 160; s->v[8].y = by + 32; s->v[8].z = 0x100000; s->v[8].f = 0;
    s->v[9].rgba = t[6] | a; s->v[9].q = 1; s->v[9].x = bx + 160; s->v[9].y = by + h - 32; s->v[9].z = 0x100000; s->v[9].f = 0;
    s->v[10].rgba = t[5] | a; s->v[10].q = 1; s->v[10].x = bx + w - 32; s->v[10].y = by + 32; s->v[10].z = 0x100000; s->v[10].f = 0;
    s->v[11].rgba = t[7] | a; s->v[11].q = 1; s->v[11].x = bx + w - 32; s->v[11].y = by + h - 32; s->v[11].z = 0x100000; s->v[11].f = 0;
    if (o->x48 & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->sx;
        sy = o->sy;
        fx = cx;
        fy = cy;
/*P*/
        X = fx + (f32)(s->v[0].x - cx) * sx;
        Y128 = fy + (f32)(s->v[0].y - cy) * sy;
        s->v[0].x = X;
        Yh = fy + (f32)(s->v[1].y - cy) * sy;
        X128 = fx + (f32)(s->v[2].x - cx) * sx;
        Y = fy + (f32)(s->v[2].y - cy) * sy;
        Xw = fx + (f32)(s->v[4].x - cx) * sx;
        X32 = fx + (f32)(s->v[6].x - cx) * sx;
        s->v[2].x = X128;
        Y160 = fy + (f32)(s->v[6].y - cy) * sy;
        Yh32 = fy + (f32)(s->v[7].y - cy) * sy;
        X160 = fx + (f32)(s->v[8].x - cx) * sx;
        s->v[1].y = Yh;
        s->v[6].x = X32;
        s->v[9].x = X160;
        s->v[3].x = X128;
        s->v[0].y = Y128;
        s->v[7].y = Yh32;
        s->v[6].y = Y160;
        s->v[3].y = Yh;
        s->v[7].x = X32;
        s->v[1].x = X;
        s->v[2].y = Y;
        s->v[8].x = X160;
        s->v[5].y = Yh;
        s->v[4].y = Y;
        s->v[11].y = Yh32;
        s->v[4].x = Xw;
        Y32 = fy + (f32)(s->v[8].y - cy) * sy;
        s->v[10].y = Y32;
        Xw32 = fx + (f32)(s->v[10].x - cx) * sx;
        s->v[9].y = Yh32;
        s->v[10].x = Xw32;
        s->v[8].y = Y32;
        s->v[5].x = Xw;
        s->v[11].x = Xw32;
/*Q*/
    }
    buf[0] = (((s32)(s + 1) - (s32)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}
