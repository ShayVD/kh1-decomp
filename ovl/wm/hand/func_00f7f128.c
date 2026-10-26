/* wm.x func_00f7f128: matched by hand. */
#include "ovl.h"

s32 func_001f15f0(s32, s32, s32, s32, s32, s32, s32);
extern s16 D_00FB6548[];

s32 func_00f7f128(s32 p, s32 v, s32 x, s32 y) {
    p = func_001f15f0(p, 1, 0x800000F0, x, y, 1, 28);
    x += 28;
    p = func_001f15f0(p, 1, 0x800000F0, x, y, 37, 28);
    x += 28;
    p = func_001f15f0(p, 1, 0x800000F0, x, y, D_00FB6548[(v & 0xF0) >> 4], 28);
    x += 28;
    return func_001f15f0(p, 1, 0x800000F0, x, y, D_00FB6548[v & 0xF], 28);
}
