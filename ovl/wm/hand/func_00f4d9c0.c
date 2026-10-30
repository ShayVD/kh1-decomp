/* wm.x func_00f4d9c0: matched by hand. */
#include "ovl.h"

void *func_00f4d550(void *, void *, s32);
extern u8 D_00FA5670[];

void *func_00f4d9c0(u8 *p, s32 a, s32 b, s32 c, s32 x, s32 y, s32 w, s32 h) {
    void *r;
    s32 w2, h2;

    r = func_00f4d550(p, D_00FA5670, 0x130);
    *(u64 *)(p + 0x60) = ((u64)a << 32) | 100;
    *(u64 *)(p + 0x70) = ((u64)b << 1) | ((u64)c << 4) | 0x30001;
    w2 = x + w;
    h2 = y + h;
    *(u64 *)(p + 0xB0) = (x << 4) | ((u64)(y << 4) << 16);
    *(u64 *)(p + 0xD0) = (w2 << 4) | ((u64)(h2 << 4) << 16);
    *(u64 *)(p + 0xC0) = ((x + 1792) << 4) | ((u64)((y + 1856) << 4) << 16) | ((u64)1 << 32);
    *(u64 *)(p + 0xE0) = ((w2 + 1792) << 4) | ((u64)((h2 + 1856) << 4) << 16) | ((u64)1 << 32);
    return r;
}
