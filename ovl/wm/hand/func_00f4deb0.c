/* wm.x func_00f4deb0: the twin of gb.x func_00f26db8 (tools/ovl/twins.py). */
#include "ovl.h"

s32 func_00f4d550(void *, void *, s32);
extern u8 D_00FA5820[];

s32 func_00f4deb0(u64 *p, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, s32 u0, s32 v0, s32 u1, s32 v1, u64 a, u64 b) {
    s32 r = func_00f4d550(p, D_00FA5820, 0xD0);
    p[4] = 0x156;
    p[12] = b;
    p[14] = a;
    p[18] = x0 | ((u64)y0 << 16) | ((u64)z << 32);
    p[22] = x1 | ((u64)y1 << 16) | ((u64)z << 32);
    p[16] = u0 | ((u64)v0 << 16);
    p[20] = u1 | ((u64)v1 << 16);
    return r;
}
