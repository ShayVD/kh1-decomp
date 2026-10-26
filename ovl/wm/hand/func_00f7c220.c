/* wm.x func_00f7c220: matched by hand. */
#include "ovl.h"

s32 func_00f7c078(s32, s32, s32);

s32 func_00f7c220(s32 pad, s32 cur) {
    s32 d;
    s32 r;

    if (!(pad & 0xF0)) {
        return cur;
    }
    if (cur >= 28) {
        return cur;
    }
    d = -1;
    if (pad & 0x10) d = 0;
    if (pad & 0x40) d = 1;
    if (pad & 0x80) d = 2;
    if (pad & 0x20) d = 3;
    if ((pad & 0x90) == 0x90) d = 4;
    if ((pad & 0x30) == 0x30) d = 5;
    if ((pad & 0xC0) == 0xC0) d = 6;
    if ((pad & 0x60) == 0x60) d = 7;
    if (d == -1) {
        return cur;
    }
    r = func_00f7c078(cur, cur, d);
    if (r == 0) {
        r = cur;
    }
    return r;
}
