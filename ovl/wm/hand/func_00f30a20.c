/* wm.x func_00f30a20: matched by hand. */
#include "ovl.h"

extern s32 D_00F8C28C;
extern s32 D_00FBBA50;
extern s32 D_00FBBA54;

void func_00f30a20(void) {
    if (D_00F8C28C == 1) {
        D_00FBBA50 += 6;
    } else {
        D_00FBBA50 += 4;
    }
    if (D_00FBBA50 > D_00FBBA54) {
        D_00FBBA50 = D_00FBBA54;
    }
}
