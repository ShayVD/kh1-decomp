#include "common.h"
extern u64 *func_00122048(s32, s32);
extern u64 *func_0011fb38(s32, u64, u64 *);
extern s32 func_00266c08(s32);
extern void func_00266f38(s32, u32);
extern s32 sceGsSyncPath(s32, s32);
extern void func_001220b8(u64 *);

void func_001edfb8(s32 x, s32 y, s32 w, s32 h)
{
    s32 x2;
    s32 y2;
    u64 *p;
    u64 *e;
    u64 *q;
    u32 a;
    x2 = x + w - 1;
    y2 = y + h - 1;

    if (x >= 512 || y >= 384 || x2 < 0 || y2 < 0) return;
    if (x2 >= 512) x2 = 511;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (y2 >= 384) y2 = 383;
    p = func_00122048(1024, 128);

    q = p + 2;
    q[0] = 0x1000000000008001;
    q[1] = 14;
    a = ((u32)p & 0x0fffffff) | 0x80000000;

    e = func_0011fb38(64, (u64)x | ((u64)x2 << 16) | ((u64)y << 32) | ((u64)y2 << 48), q + 2);
    p[0] = (((s32)((u32)e - (u32)p) >> 4) - 1) | 0x70000000;
    func_00266f38(func_00266c08(2), a);
    sceGsSyncPath(0, 0);
    func_001220b8(p);
}
