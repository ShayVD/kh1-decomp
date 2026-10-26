/* wm.x func_00f42c08: matched by hand. */
#include "ovl.h"

s32 func_00f42a38(s32, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_00f42c08(s32 x, s32 y, s32 c, s32 num, s32 n, s32 pkt) {
    s32 i;
    if (n <= 0) return pkt;
    x = x + n * 14 - 14;
    for (i = 0; i < n; i++) {
        pkt = func_00f42a38(x, y, (num % 10) * 16, 0, 16, 16, 0, c, pkt);
        x -= 14;
        num /= 10;
    }
    return pkt;
}
