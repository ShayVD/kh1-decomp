/* gb.x func_00f2e420: matched by hand. */
#include "ovl.h"

u64 *func_00f26fb8(u64 *, s32, s32);
u64 *func_001f15f0(u64 *, s32, u32, s32, s32, s32, s32);
extern f32 D_00F6156C;

u64 *func_00f2e420(s32 x, s32 y, s32 n, u64 *p) {
    s32 t = n / 10; s32 o = n % 10; s32 a = D_00F6156C * 128.0f; p = func_00f26fb8(p, 0x700, 0x740); if (t > 0) p = func_001f15f0(p, 1, a | (a << 16 | a << 8) | 0x80000000, x, y, t + 1, 15); return func_001f15f0(p, 1, a | (a << 16 | a << 8) | 0x80000000, x + 12, y, o + 1, 15);
}
