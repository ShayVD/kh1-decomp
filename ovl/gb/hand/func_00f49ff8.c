/* gb.x func_00f49ff8: matched by hand. */
#include "ovl.h"

extern s32 D_00F82B48;

s32 func_00f49ff8(s32 arg0, s32 arg1) {
    if (arg0 < 0) return 0;
    if (arg1 < 0) return 0;
    if (arg0 >= 2) return 0;
    if (arg1 >= (D_00F82B48 + 1) / 2) return 0;
    return arg1 * 2 + arg0 < D_00F82B48;
}
