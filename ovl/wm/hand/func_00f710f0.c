/* wm.x func_00f710f0: the twin of gb.x func_00f49ff8 (tools/ovl/twins.py). */
#include "ovl.h"

extern s32 D_0108F308;

s32 func_00f710f0(s32 arg0, s32 arg1) {
    if (arg0 < 0) return 0;
    if (arg1 < 0) return 0;
    if (arg0 >= 2) return 0;
    if (arg1 >= (D_0108F308 + 1) / 2) return 0;
    return arg1 * 2 + arg0 < D_0108F308;
}
