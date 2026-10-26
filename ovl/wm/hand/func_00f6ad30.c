/* wm.x func_00f6ad30: matched by hand. */
#include "ovl.h"

s32 func_001f40c8(void);
void func_001f82b0(void);
void func_0020b998(void);
extern s32 D_00FB4EB4;
extern u8 D_00FB4EB9;
extern u8 D_00FB4EBA;
extern s32 D_0108F184;

s32 func_00f6ad30(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    if (D_0108F184 == 0) {
        D_00FB4EB4 = -1;
        D_00FB4EB9 = D_00FB4EBA;
        return 4;
    }
    return 0;
}
