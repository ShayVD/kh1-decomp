/* wm.x func_00f24e38: matched by hand. */
#include "ovl.h"

CONTEXT_ONLY s32 func_00f23c20(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8) { return 0; }

s32 func_00f24e38(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    if (arg3 <= 0) {
        return arg4;
    }
    arg0 = arg0 + arg3 * 14 - 14;
    for (i = 0; i < arg3; i++) {
        arg4 = func_00f23c20(arg0, arg1, (arg2 % 10) * 16, 0, 16, 16, 9, 128, arg4);
        arg2 /= 10;
        arg0 -= 14;
    }
    i = arg2 % 10;
    if (i > 0) {
        arg4 = func_00f23c20(arg0, arg1, i * 16, 0, 16, 16, 9, 128, arg4);
    }
    return arg4;
}
