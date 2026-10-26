/* wm.x func_00f7d9e0: matched by hand. */
#include "ovl.h"

s32 func_001f40c8(void);
void func_001f82b0(void);
extern s32 D_0108F6C4;
s32 func_00f7d9e0(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        return 0;
    }
    return D_0108F6C4 != 0 ? 0 : 4;
}
