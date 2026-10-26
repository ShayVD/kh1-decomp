/* wm.x func_00f55bc0: matched by hand. */
#include "ovl.h"

extern s32 D_00FA5CE0;
void func_00f55ad8(void);
void func_001bfac8(void);
void func_00f55bc0(void) {
    while (1) {
        if (D_00FA5CE0 != 0) {
            func_00f55ad8();
        }
        func_001bfac8();
    }
}
