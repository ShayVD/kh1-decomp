/* wm.x func_00f4df98: matched by hand. */
#include "ovl.h"

extern u8 D_00FA5820[];
void *func_00f4d550(void *, void *, s32);

void *func_00f4df98(u64 *p, s32 x0, s32 y0, s32 z, s32 x1, s32 y1, s32 w, s32 h, u64 tex0, u64 tex1)
{
    void *r = func_00f4d550(p, D_00FA5820, 208);

    p[0xA0 / 8] = (u64)((x1 + w) * 16) | ((u64)((y1 + h) * 16 - 16) << 16);
    p[0x60 / 8] = tex1;
    p[0x70 / 8] = tex0;
    p[0x90 / 8] = (u64)(x0 * 16) | ((u64)(y0 * 16) << 16) | ((u64)(z * 16) << 32);
    p[0xB0 / 8] = (u64)((x0 + w) * 16) | ((u64)((y0 + h) * 16) << 16) | ((u64)(z * 16) << 32);
    p[0x80 / 8] = (u64)(x1 * 16) | ((u64)(y1 * 16) << 16);
    p[0x20 / 8] = 278;
    return r;
}
