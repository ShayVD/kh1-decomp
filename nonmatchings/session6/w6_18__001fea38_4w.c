/* 001fea38: 4 words off (nostrict). Only lw o->x/o->y (176/180) vs lh xbe/xc0 (190/192) load order swapped by sched. Same in nostrict_nogcse/nofill. Transform block in sibling style (sx/sy/fx/fy locals) fixed the rest. */
#include "common.h"

typedef struct {
    u8 pad0[0x48];
    s32 flags;
    u8 pad4c[0x74 - 0x4c];
    f32 sx;
    f32 sy;
    u8 pad7c[0x90 - 0x7c];
    s32 col;
    f32 t;
    u8 pad98[0xb0 - 0x98];
    s32 x;
    s32 y;
    u8 padb8[0xbe - 0xb8];
    s16 xbe;
    s16 xc0;
    s16 xc2;
    s16 xc4;
    s16 xc6;
    s16 xc8;
    s16 xca;
    s16 xcc;
    s16 xce;
    s16 xd0;
    s16 xd2;
    s16 xd4;
    s16 xd6;
    s16 xd8;
    s16 xda;
} WinA;

extern u8 D_003F1A70[];
s32 sceGsSyncPath(s32, u16);
f32 sinf(f32);
u64 *func_0011fb38(s32, u64, u64 *);
u64 *func_00122048(u32, u32);
void func_001220b8(void *);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 func_001f4378(WinA *);
s32 func_001f4570(WinA *);
s32 func_001f45e0(WinA *);

void func_001fea38(WinA *o) {
    s32 x[2];
    s32 y[3];
    s32 r[2];
    s32 g[2];
    s32 b[2];
    u64 *p;
    u64 *q;
    void *u;
    s32 col;
    f32 s;
    s32 h;

    if (o->xcc == 0) return;
    func_00266f38(func_00266c08(2), D_003F1A70);
    p = func_00122048(0x400, 0x80);
    q = p + 2;
    u = (void *)(((u32)p & 0x0fffffff) | 0x80000000);
    q[0] = 0x1000000000008001;
    q[1] = 0xe;
    q = func_0011fb38(0x42, 0x48, q + 2);
    q[0] = 0x2026400000008006;
    q[1] = 0x41;
    q += 2;
    s = sinf((f32)((s32)o->t % 64) * 0.015625f * 3.1415928f);
    if (func_001f4378(o)) {
        r[0] = (s32)(s * 20.0f) + 32;
        b[0] = g[0] = (s32)(s * 60.0f) + 96;
    } else {
        r[0] = (s32)(s * 20.0f) + 32;
        g[0] = (s32)(s * 60.0f) + 96;
        b[0] = (s32)(s * 30.0f) + 48;
    }
    r[1] = r[0] >> 1;
    g[1] = g[0] >> 1;
    b[1] = b[0] >> 1;
    x[0] = o->x + o->xbe + o->xda * o->xc2;
    x[1] = x[0] + o->xc2 - o->xc6;
    y[0] = o->y + o->xc0 + (o->xd2 * o->xc4 >> 4);
    h = o->xc4 - o->xc8;
    y[1] = y[0] + h / 2;
    y[2] = y[0] + h;
    col = o->col;
    if (o->flags & 1) {
        s32 cx = func_001f4570(o);
        s32 cy = func_001f45e0(o);
        f32 sx = o->sx;
        f32 sy = o->sy;
        f32 fx = cx;
        f32 fy = cy;
        x[0] = fx + (f32)(x[0] - cx) * sx;
        x[1] = fx + (f32)(x[1] - cx) * sx;
        y[0] = fy + (f32)(y[0] - cy) * sy;
        y[1] = fy + (f32)(y[1] - cy) * sy;
        y[2] = fy + (f32)(y[2] - cy) * sy;
    }
    ((s32 *)q)[0] = r[1]; ((s32 *)q)[1] = g[1]; ((s32 *)q)[2] = b[1]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[0]; ((s32 *)q)[1] = y[0]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[1]; ((s32 *)q)[1] = g[1]; ((s32 *)q)[2] = b[1]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[1]; ((s32 *)q)[1] = y[0]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[0]; ((s32 *)q)[1] = g[0]; ((s32 *)q)[2] = b[0]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[0]; ((s32 *)q)[1] = y[1]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[0]; ((s32 *)q)[1] = g[0]; ((s32 *)q)[2] = b[0]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[1]; ((s32 *)q)[1] = y[1]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[1]; ((s32 *)q)[1] = g[1]; ((s32 *)q)[2] = b[1]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[0]; ((s32 *)q)[1] = y[2]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[1]; ((s32 *)q)[1] = g[1]; ((s32 *)q)[2] = b[1]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[1]; ((s32 *)q)[1] = y[2]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    p[0] = ((s32)((u8 *)q - (u8 *)p) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(p);
}
