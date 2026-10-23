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
    u8 padb8[0xbe - 0xb8];
    s16 xbe, xc0, xc2, xc4;
    u8 padc6[0xcc - 0xc6];
    s16 xcc;
    u8 padce[0xd2 - 0xce];
    s16 xd2;
    u8 padd4[0xdc - 0xd4];
    u8 xdc[16];
} Wnd2;
typedef struct {
    s32 r, g, b, a;
    s32 u0, v0, p18, p1c;
    s32 x0, y0, z0, f0;
    s32 u1, v1, p38, p3c;
    s32 x1, y1, z1, f1;
} Spr2;
#include "data/pieces/D_003F1E70.h"
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
u64 *func_00122048(s32, s32);
s32 sceGsSyncPath(s32, s32);
void func_001220b8(void *);
s32 func_001f4570(Wnd2 *);
s32 func_001f45e0(Wnd2 *);
f32 sinf(f32);

void func_00201f38(Wnd2 *o) {
    u64 *buf;
    Spr2 *s;
    void *u;
    s32 cx, cy, t, w, c, d, X, Y, xa, ya, k;
    f32 fx, fy, a, b;
    if (o->xcc == 0) return;
    func_00266f38(func_00266c08(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    s = (Spr2 *)(buf + 2);

    ((u64 *)s)[0] = 0x50ab400000000001;
    ((u64 *)s)[2] = 0;
    ((u64 *)s)[1] = 0xeeeee;
    ((u64 *)s)[3] = 63;
    ((u64 *)s)[4] = 0x7bf8621413d7c;
    ((u64 *)s)[5] = 6;
    ((u64 *)s)[7] = 22;
    ((u64 *)s)[6] = 0x4007bf8001300000;
    ((u64 *)s)[8] = 0x407bf8001400000;
    ((u64 *)s)[9] = 22;
    ((u64 *)s)[10] = 72;
    ((u64 *)s)[11] = 66;
    ((u64 *)s)[12] = 0x5000000000008001;
    ((u64 *)s)[13] = 0x43431;

    s = (Spr2 *)(buf + 16);
    t = o->x94;
    w = sinf((f32)(t % 32) * 0.03125f * 3.141592801f) * 240.0f + 480.0f;
    d = o->xd2;
    c = o->xdc[d >> 4] * 2 - 128;
    k = o->xc2;
    xa = o->xb0 + o->xbe + k;
    X = xa - w / 2;
    ya = o->xb4 + o->xc0 + o->xc4 * d / 16;
    s->b = c;
    s->g = c;
    s->r = c;
    s->a = o->x90;
    s->u0 = 3608;
    s->v0 = 920;
    s->f0 = 0x8000;
    s->u1 = 4072;
    s->v1 = 1384;
    s->z0 = 0x100000;
    s->z1 = 0x100000;
    s->f1 = 0;
    Y = ya - w / 2;
    if (o->x48 & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        a = o->sx;
        b = o->sy;
        fx = cx;
        fy = cy;
        s->x0 = fx + (f32)(X - cx) * a;
        s->y0 = fy + (f32)(Y - cy) * b;
        s->x1 = fx + (f32)(X + w - cx) * a;
        s->y1 = fy + (f32)(Y + w - cy) * b;
    } else {
        s->x1 = X + w;
        s->y1 = Y + w;
        s->x0 = X;
        s->y0 = Y;
    }
    s++;
    buf[0] = (((s32)s - (s32)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}
