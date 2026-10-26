/* wm.x func_00f35018: matched by hand. */
#include "ovl.h"

extern s32 D_00F8508C;
extern s32 D_00F85090;
extern s32 D_00FBDFB8[128];
void func_00f35018(void) {
    s32 i;
    for (i = 127; i >= 0; i--) {
        D_00FBDFB8[i] = 0;
    }
    D_00F8508C = 0;
    D_00F85090 = 0;
}
