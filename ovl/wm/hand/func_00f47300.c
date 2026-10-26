/* wm.x func_00f47300: the twin of gb.x func_00f20208 (tools/ovl/twins.py). */
#include "ovl.h"

extern s32 D_010809E0[16];
void func_00f47300(void) {
    s32 i;
    s32 v = -1;
    for (i = 15; i >= 0; i--) {
        D_010809E0[i] = v;
    }
}
