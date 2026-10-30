/* gb.x func_00f26ca8: matched by hand. */
#include "ovl.h"

/* gb.x func_00f26ca8: matched by hand. */
#include "ovl.h"

s32 func_00f26458(void *, void *, s32);
extern u8 D_00F610A0[];

s32 func_00f26ca8(u64 *p, s32 x, s32 y, s32 z, s32 u, s32 v, s32 w, s32 h, u64 a, u64 b) {
    s32 r = func_00f26458(p, D_00F610A0, 0xD0);
    x <<= 4; y <<= 4; z <<= 4; u <<= 4; v <<= 4; w <<= 4; h <<= 4;
    p[4] = 0x156;
    p[12] = b;
    p[14] = a;
    p[18] = x | ((u64)y << 16) | ((u64)z << 32);
    p[22] = (x + w) | ((u64)(y + h) << 16) | ((u64)z << 32);
    p[16] = u | ((u64)v << 16);
    p[20] = (u + w) | ((u64)(v + h) << 16);
    return r;
}
