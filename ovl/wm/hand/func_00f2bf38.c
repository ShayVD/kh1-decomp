/* wm.x func_00f2bf38: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
extern s32 D_00FBBA50;
void func_00f2bf38(s32 arg0) {
    s32 i;
    for (i = 1; i <= 25; i++) {
        D_00FBBA50 = arg0 * i / 25;
        func_001bfac8();
    }
}
