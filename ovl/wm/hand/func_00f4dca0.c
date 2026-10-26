/* wm.x func_00f4dca0: the twin of gb.x func_00f26ba8 (tools/ovl/twins.py). */
#include "ovl.h"

s32 func_00f4d550(void *, void *, s32);
extern u8 D_00FA5820[];

s32 func_00f4dca0(u64 *p, s32 x, s32 y, s32 z, s32 w, s32 h, s32 u, s32 v, s32 du, s32 dv, u64 a, u64 b) {
    s32 r = func_00f4d550(p, D_00FA5820, 0xD0);
    p[4] = 0x156;
    p[12] = b;
    p[14] = a;
    p[18] = x | ((u64)y << 16) | ((u64)z << 32);
    p[22] = (x + w) | ((u64)(y + h) << 16) | ((u64)z << 32);
    p[16] = u | ((u64)v << 16);
    p[20] = (u + du) | ((u64)(v + dv) << 16);
    return r;
}
