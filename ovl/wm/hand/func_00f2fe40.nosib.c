/* wm.x func_00f2fe40: matched by hand. */
#include "ovl.h"

void func_00f2fc50(void);
void func_00f2fcf8(void);
extern s32 D_00F850F4;
extern s32 D_00F8C1EC;
void func_00f2fe40(s32 arg0) {
    if (D_00F850F4 != 0) {
        if (arg0 != 0) {
            D_00F8C1EC = 0;
            func_00f2fcf8();
            return;
        }
        func_00f2fc50();
    }
}
