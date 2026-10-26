/* wm.x func_00f4e1b8: the twin of gb.x func_00f270c0 (tools/ovl/twins.py). */
#include "ovl.h"

s32 func_00f4d550(void *, void *, s32);
extern u8 D_00FA59D0[];

s32 func_00f4e1b8(u64 *p, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, s32 z, s32 u0, s32 v0, s32 u1, s32 v1, s32 u2, s32 v2, s32 u3, s32 v3, u64 a, u64 b) {
    s32 r = func_00f4d550(p, D_00FA59D0, 0x110);
    p[4] = 0x154;
    p[12] = b;
    p[14] = a;
    p[16] = u0 | ((u64)v0 << 16);
    p[18] = x0 | ((u64)y0 << 16) | ((u64)z << 32);
    p[20] = u1 | ((u64)v1 << 16);
    p[22] = x1 | ((u64)y1 << 16) | ((u64)z << 32);
    p[24] = u2 | ((u64)v2 << 16);
    p[26] = x2 | ((u64)y2 << 16) | ((u64)z << 32);
    p[28] = u3 | ((u64)v3 << 16);
    p[30] = x3 | ((u64)y3 << 16) | ((u64)z << 32);
    return r;
}
