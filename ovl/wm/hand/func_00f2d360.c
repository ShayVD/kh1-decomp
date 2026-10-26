/* wm.x func_00f2d360: the twin of gb.x func_00f33bf8 (tools/ovl/twins.py). */
#include "ovl.h"

CONTEXT_ONLY s32 D_00F8C198[5][4] = {0};

s32 func_00f2d360(s32 arg0, s32 arg1) {
    s32 i;
    switch (arg1) {
    case 4: i = 0; break;
    case 5: i = 1; break;
    case 6: i = 2; break;
    case 7: i = 3; break;
    case 8: i = 4; break;
    default: return -1;
    }
    return D_00F8C198[i][arg0];
}
