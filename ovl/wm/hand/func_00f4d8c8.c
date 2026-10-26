/* wm.x func_00f4d8c8: matched by hand. */
#include "ovl.h"

extern u8 D_00FA5670[];
void *func_00f4d550(void *, void *, s32);

void *func_00f4d8c8(u64 *p, s32 fbp, s32 w, s32 x, s32 y, s32 dx, s32 dy) {
    void *r = func_00f4d550(p, D_00FA5670, 0x130);

    p[0x80 / 8] = (s64)fbp | ((s64)(w / 64) << 14) | ((s64)0xE200 << 20);
    p[0xD0 / 8] = (s64)(dx << 4) | ((s64)(dy << 4) << 16);
    p[0xC0 / 8] = (s64)(x << 4) | ((s64)(y << 4) << 16) | ((s64)0x8000 << 17);
    p[0xE0 / 8] = (s64)((x + dx) << 4) | ((s64)((y + dy) << 4) << 16) | ((s64)0x8000 << 17);
    p[0xB0 / 8] = 0;
    return r;
}
