/* gb.x func_00f33bf8: matched by hand. */
#include "ovl.h"

CONTEXT_ONLY s32 D_00F61668[5][4] = {0};

s32 func_00f33bf8(s32 arg0, s32 arg1) {
    s32 i;
    switch (arg1) {
    case 4: i = 0; break;
    case 5: i = 1; break;
    case 6: i = 2; break;
    case 7: i = 3; break;
    case 8: i = 4; break;
    default: return -1;
    }
    return D_00F61668[i][arg0];
}
