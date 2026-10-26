/* dkmovie.x func_00f22cf8: matched by hand. */
#include "ovl.h"

void func_00f22cf8(s32 *p, s32 a, s64 v) {
    p[2] = a;
    p[1] = v >> 32;
    p[0] = v & 0xFFFFFFFF;
    p[3] = 0;
}
