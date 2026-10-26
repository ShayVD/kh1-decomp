/* wm.x func_00f7f338: matched by hand. */
#include "ovl.h"

u64 *func_001f15f0(u64 *, s32, s32, s32, s32, s32, s32);

u64 *func_00f7f338(u64 *p, s32 bits, s32 x, s32 y, s32 n) {
    s32 i;
    s32 m = 0x80;

    for (i = 0; i < 8; i++) {
        if (m & bits) {
            p = func_001f15f0(p, 1, 0x800000F0, x, y, 2, 28);
        } else {
            p = func_001f15f0(p, 1, 0x800000F0, x, y, 1, 28);
        }
        if (7 - n == i) {
            p = func_001f15f0(p, 1, 0x800000F0, x, y + 25, 12, 28);
        }
        m /= 2;
        x += 28;
        if (i == 3) x += 8;
    }
    return p;
}
