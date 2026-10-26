/* wm.x func_00f55518: matched by hand. */
#include "ovl.h"

u64 *func_00f4e0b0(s32, s32, s32);
u64 *func_001f15f0(u64 *, s32, s32, s32, s32, s32, s32);
extern f32 D_00FA5CEC;

u64 *func_00f55518(s32 x, s32 y, s32 n, s32 arg3) {
    s32 hi = n / 10;
    s32 lo = n % 10;
    s32 c = D_00FA5CEC * 128.0f;
    u64 *p = func_00f4e0b0(arg3, 0x700, 0x740);

    if (hi > 0) {
        p = func_001f15f0(p, 1, c | ((c << 16) | (c << 8)) | 0x80000000, x, y, hi + 1, 15);
    }
    return func_001f15f0(p, 1, c | ((c << 16) | (c << 8)) | 0x80000000, x + 12, y, lo + 1, 15);
}
