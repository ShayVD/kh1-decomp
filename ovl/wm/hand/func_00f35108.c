/* wm.x func_00f35108: matched by hand. */
#include "ovl.h"

extern s32 D_00F8C22C;
extern s32 D_00F8C230;
extern s32 D_00F8C234;
extern s32 D_00F8C238;
extern s32 D_00FCD5F0[8];
extern s32 D_00FCD610[8];

void func_00f35108(s32 arg0, s32 arg1) {
    s32 i;
    if (D_00F8C238 < 8) {
        if (D_00F8C238 == 0 && D_00F8C22C == arg0) {
            D_00F8C230 = arg1;
            return;
        }
        i = D_00F8C234 + D_00F8C238;
        D_00F8C238++;
        i &= 7;
        D_00FCD5F0[i] = arg0;
        D_00FCD610[i] = arg1;
    }
}
