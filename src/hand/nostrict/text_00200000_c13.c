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
} Wnd2;
typedef struct { s32 x, y, z, w; } V4;
extern u8 D_003F1A70[];
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
u64 *func_00122048(s32, s32);
s32 sceGsSyncPath(s32, s32);
void func_001220b8(void *);
s32 func_001f4570(Wnd2 *);
s32 func_001f45e0(Wnd2 *);
s32 func_001f4378(Wnd2 *);
u64 *func_0011fb38(s32, s32, u64 *);
f32 sinf(f32);

static inline s32 inl_sc(s32 v, s32 c, f32 fc, f32 s) { return fc + (f32)(v - c) * s; }

void func_00204d80(Wnd2 *w, s32 a1, s32 a2, s32 a3, s32 a4) {
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
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = inl_sc(xs[0] + 96, cx, fcx, sx);
        ((V4 *)p)->y = inl_sc(y - 96, cy, fcy, sy);
        ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][0]; ((V4 *)p)->y = col[1][0]; ((V4 *)p)->z = col[2][0]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = inl_sc(xs[0] - 96, cx, fcx, sx);
        ((V4 *)p)->y = inl_sc(y, cy, fcy, sy);
        ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = inl_sc(xs[0] + 96, cx, fcx, sx);
        ((V4 *)p)->y = inl_sc(y + 96, cy, fcy, sy);
        ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = inl_sc(xs[1] - 96, cx, fcx, sx);
        ((V4 *)p)->y = inl_sc(y - 96, cy, fcy, sy);
        ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0x8000; p += 2;
        ((V4 *)p)->x = col[0][0]; ((V4 *)p)->y = col[1][0]; ((V4 *)p)->z = col[2][0]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = inl_sc(xs[1] + 96, cx, fcx, sx);
        ((V4 *)p)->y = inl_sc(y, cy, fcy, sy);
        ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0x8000; p += 2;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = inl_sc(xs[1] - 96, cx, fcx, sx);
        ((V4 *)p)->y = inl_sc(y + 96, cy, fcy, sy);
        ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
    } else {
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = xs[0] + 96; ((V4 *)p)->y = y - 96; ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][0]; ((V4 *)p)->y = col[1][0]; ((V4 *)p)->z = col[2][0]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = xs[0] - 96; ((V4 *)p)->y = y; ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = xs[0] + 96; ((V4 *)p)->y = y + 96; ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = xs[1] - 96; ((V4 *)p)->y = y - 96; ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0x8000; p += 2;
        ((V4 *)p)->x = col[0][0]; ((V4 *)p)->y = col[1][0]; ((V4 *)p)->z = col[2][0]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = xs[1] + 96; ((V4 *)p)->y = y; ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0x8000; p += 2;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = xs[1] - 96; ((V4 *)p)->y = y + 96; ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
    }
    buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
    func_00266f38(func_00266c08(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}
