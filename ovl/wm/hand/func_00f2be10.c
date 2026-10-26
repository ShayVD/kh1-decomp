/* wm.x func_00f2be10: matched by hand. */
#include "ovl.h"

extern u8 D_00FBB580[];

u8 *func_00f2be10(s32 n, s32 y) {
    s16 s;
    u8 *p = D_00FBB580;
    s = 4;
    *p++ = 14;
    *p++ = ((u8 *)&s)[0];
    *p++ = ((u8 *)&s)[1];
    *p++ = 12;
    *p++ = y - 4;
    *p++ = 45;
    s = -4;
    *p++ = 14;
    *p++ = ((u8 *)&s)[0];
    *p++ = ((u8 *)&s)[1];
    *p++ = 12;
    *p++ = y;
    *p = n % 10 + 33;
    p[1] = 0;
    return D_00FBB580;
}
