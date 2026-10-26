/* wm.x func_00f77ed0: matched by hand. */
#include "ovl.h"

s32 func_001f40c8(void);
void func_001f82b0(void);
void func_0020b998(void);
extern s32 D_0108F1A8;
extern s32 D_0108F1AC;

s32 func_00f77ed0(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        if (D_0108F1A8 != 0) {
            func_0020b998();
        }
        return 0;
    }
    if (D_0108F1AC != 0) {
        D_0108F1AC = 2;
        return 4;
    }
    return 0;
}
