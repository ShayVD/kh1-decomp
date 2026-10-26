/* wm.x func_00f68008: matched by hand. */
#include "ovl.h"

void func_0011cbe0(s32, s32, s32, void (*)(void));
void func_001bfac8(void);
void func_00f67fc0(void);
extern s32 D_0108F150;

void func_00f68008(s32 arg0, s32 arg1) {
    D_0108F150 = 0;
    func_0011cbe0(0, arg1, arg0, func_00f67fc0);
    while (D_0108F150 == 0) {
        func_001bfac8();
    }
    func_001bfac8();
}
