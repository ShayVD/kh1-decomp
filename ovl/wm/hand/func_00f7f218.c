/* wm.x func_00f7f218: matched by hand. */
#include "ovl.h"

u64 *func_001f15f0(u64 *, s32, s32, s32, s32, s32, s32);
extern s16 D_00FB6568[];

u64 *func_00f7f218(u64 *p, s32 n, s32 x, s32 y) {
    p = func_001f15f0(p, 1, 0x800000F0, x, y, 22, 28);
    x += 24;
    p = func_001f15f0(p, 1, 0x800000F0, x, y, 17, 28);
    x += 56;
    p = func_001f15f0(p, 1, 0x800000F0, x, y, D_00FB6568[(n / 10) % 10], 28);
    return func_001f15f0(p, 1, 0x800000F0, x + 28, y, D_00FB6568[n % 10], 28);
}
