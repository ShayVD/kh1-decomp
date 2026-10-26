/* gb.x func_00f267d0: matched by hand. */
#include "ovl.h"

s32 func_00f26458(void *, void *, s32);
extern u8 D_00F60EF0[];

s32 func_00f267d0(u64 *p, s32 tbp, s32 w, s32 x, s32 y, s32 dw, s32 dh) {
    s32 r = func_00f26458(p, D_00F60EF0, 0x130);
    p[16] = tbp | ((u64)(w / 64) << 14) | 0xE20000000; p[26] = (dw * 16) | ((u64)(dh * 16) << 16); p[24] = (x * 16) | ((u64)(y * 16) << 16) | 0x100000000; p[28] = ((x + dw) * 16) | ((u64)((y + dh) * 16) << 16) | 0x100000000; p[22] = 0;
    return r;
}
