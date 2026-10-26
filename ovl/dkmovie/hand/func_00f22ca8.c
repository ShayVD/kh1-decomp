/* dkmovie.x func_00f22ca8: matched by hand. */
#include "ovl.h"

void func_00f22ca8(s32 *p, s64 tag, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    p[0] = (e << 15) | f;
    p[1] = (d << 14) | (c << 15) | (b << 26) | (a << 28);
    p[2] = tag & 0xFFFFFFFF;
    p[3] = tag >> 32;
}
