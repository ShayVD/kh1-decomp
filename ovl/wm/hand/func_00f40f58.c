/* wm.x func_00f40f58: matched by hand. */
#include "ovl.h"

void func_001c0688(s32);
void func_001bfac8(void);
s32 func_00f41448(void);
void func_00114830(void);
extern s32 D_00F9B2F0;
extern s32 D_00F87350;
void func_00f40f58(s32 arg0) {
    func_001c0688(arg0);
    while (D_00F9B2F0 != 0) {
        func_001bfac8();
    }
    if (D_00F87350 == 0 && func_00f41448() == 0) {
        func_00114830();
    }
}
