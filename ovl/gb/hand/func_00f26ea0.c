/* gb.x func_00f26ea0: matched by hand. */
#include "ovl.h"

#include "ovl.h"

s32 func_00f26458(void *, void *, s32);
extern u8 D_00F610A0[];

s32 func_00f26ea0(u64 *p, s32 x0, s32 y0, s32 z, s32 x1, s32 y1, s32 dx, s32 dy, u64 a, u64 b) {
    s32 r = func_00f26458(p, D_00F610A0, 0xD0);
    p[4] = 0x116;
    p[12] = b;
    p[14] = a;
    p[18] = (x0 * 16) | ((u64)(y0 * 16) << 16) | ((u64)(z * 16) << 32);
    p[22] = ((x0 + dx) * 16) | ((u64)((y0 + dy) * 16) << 16) | ((u64)(z * 16) << 32);
    p[16] = (x1 * 16) | ((u64)(y1 * 16) << 16);
    p[20] = ((x1 + dx) * 16) | ((u64)((y1 + dy) * 16 - 16) << 16);
    return r;
}
