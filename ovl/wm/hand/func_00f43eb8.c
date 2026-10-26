/* wm.x func_00f43eb8: matched by hand. */
#include "ovl.h"

extern s32 D_010809A0[];
extern s32 D_010809A8[];
void func_00f43eb8(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        D_010809A0[i] = -1;
        D_010809A8[i] = 0;
    }
}
