/* wm.x func_00f7c7e0: matched by hand. */
#include "ovl.h"

extern s32 D_0108FA98[2];
extern u8 D_0108FAA0[2][4];

void func_00f7c7e0(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        D_0108FA98[i] = 0;
        D_0108FAA0[i][0] = 0;
        D_0108FAA0[i][1] = 0;
        D_0108FAA0[i][2] = 0;
        D_0108FAA0[i][3] = 0;
    }
}
