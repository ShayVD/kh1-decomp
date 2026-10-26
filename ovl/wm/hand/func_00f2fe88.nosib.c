/* wm.x func_00f2fe88: matched by hand. */
#include "ovl.h"

void func_00f2d480(void);
void func_00f2d590(void);
extern s32 D_00F850F4;
void func_00f2fe88(s32 arg0) {
    if (D_00F850F4 != 0) {
        if (arg0 != 0) {
            func_00f2d480();
            return;
        }
        func_00f2d590();
    }
}
