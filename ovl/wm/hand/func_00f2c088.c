/* wm.x func_00f2c088: matched by hand. */
#include "ovl.h"

extern s32 D_00FBDBB8[256];
void func_00f2c088(void) {
    s32 i;
    for (i = 255; i >= 0; i--) {
        D_00FBDBB8[i] = 0;
    }
}
