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
    s16 xb8, xba, xbc, be;
    s16 c0, c2, c4, c6, c8, ca, cc, ce, d0, d2, d4, d6, d8;
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
s32 func_001fd538(Wnd *);

static inline s32 inl_sc(s32 v, s32 c, f32 fc, f32 s) { return fc + (f32)(v - c) * s; }
static inline s32 inl_sc2(s32 v, s32 c, f32 s) { return (f32)c + (f32)(v - c) * s; }

void func_002040f8(Wnd *o) {
    s32 col[3][4];
    u64 *buf, *p, *p0;
    u32 ub;
    s32 x, y, y2, d, k, al, cx, cy;
    f32 f, sx, sy;
    if (o->cc == 0) return;
    if (!(o->ce < o->cc)) return;
    func_00266f38(func_00266c08(2), D_003F1A70);
    buf = func_00122048(1024, 128);
    p = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p[0] = 0x1000000000008001;
    p[1] = 14;
    p = func_0011fb38(66, 68, buf + 4);
    p[0] = 0x2026400000008003;
    p[1] = 65;
    p += 2;
    p0 = p;
    f = (f32)((s32)o->x94 % 32) / 32.0f;
    if (func_001f4378(o)) {
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
    x = o->xb0 + o->be + o->c2 / 2;
    al = o->x90;
    if (o->x48 & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->sx;
        sy = o->sy;
        if (o->d0 >> 4) {
            y = o->xb4 + o->c0 + (s32)(sinf(f * 3.1415928f) * -384.0f);
            ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x, cx, sx);
            ((XY *)p)->y = inl_sc2(y - 400, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x - 240, cx, sx);
            ((XY *)p)->y = inl_sc2(y + 80, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x + 240, cx, sx);
            ((XY *)p)->y = inl_sc2(y + 80, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
            func_00266f38(func_00266c08(2), (void *)ub);
            sceGsSyncPath(0, 0);
        }
        if ((o->d0 >> 4) + o->ce < o->cc) {
            p = p0;
            y2 = o->xb4 + ((s32)(sinf(f * 3.1415928f) * 384.0f) + (((o->ce * 18 + 10) << 4) + o->c0));
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x - 240, cx, sx);
            ((XY *)p)->y = inl_sc2(y2 - 240, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x + 240, cx, sx);
            ((XY *)p)->y = inl_sc2(y2 - 240, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x, cx, sx);
            ((XY *)p)->y = inl_sc2(y2 + 240, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
            func_00266f38(func_00266c08(2), (void *)ub);
            sceGsSyncPath(0, 0);
        }
    } else {
        if (o->d0 >> 4) {
            y = o->xb4 + o->c0 + (s32)(sinf(f * 3.1415928f) * -384.0f);
            ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x; ((XY *)p)->y = y - 400; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            y += 80;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x - 240; ((XY *)p)->y = y; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x + 240; ((XY *)p)->y = y; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
            func_00266f38(func_00266c08(2), (void *)ub);
            sceGsSyncPath(0, 0);
        }
        if ((o->d0 >> 4) + o->ce < o->cc) {
            p = p0;
            d = sinf(f * 3.1415928f) * 384.0f;
            y2 = (o->xb4 + d) + (((o->ce * 18 + 10) << 4) + o->c0);
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x - 240; ((XY *)p)->y = y2 - 240; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x + 240; ((XY *)p)->y = y2 - 240; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x; ((XY *)p)->y = y2 + 240; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
            func_00266f38(func_00266c08(2), (void *)ub);
            sceGsSyncPath(0, 0);
        }
    }
    func_001220b8(buf);
}
