/* wm.x func_00f597b0: matched by hand. */
#include "ovl.h"

extern s32 D_00FA5DA0;
extern s32 D_0108CED0[16];
extern s32 D_0108CF10[16];
extern u64 D_0108CF50[16];

void func_00f597b0(void) {
    s32 i;
    D_00FA5DA0 = 0;
    for (i = 0; i < 16; i++) {
        D_0108CF10[i] = 0;
        D_0108CED0[i] = 1;
        D_0108CF50[i] = 0x3F80000080808080;
    }
}
