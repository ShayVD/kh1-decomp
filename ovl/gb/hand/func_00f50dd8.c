/* gb.x func_00f50dd8: matched by hand. */
#include "ovl.h"

s32 func_001f40c8(void);
void func_001f82b0(void);
void func_0020b998(void);
extern s32 D_00F829E8;
extern s32 D_00F829EC;

s32 func_00f50dd8(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        if (D_00F829E8 != 0) {
            func_0020b998();
        }
        return 0;
    }
    if (D_00F829EC != 0) {
        D_00F829EC = 2;
        return 4;
    }
    return 0;
}
