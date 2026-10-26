/* wm.x func_00f51518: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f52ab0(void *, s32, s32);
extern s32 D_00F9B518;
extern s32 D_00F9B544;
extern u8 D_00F9B548[];

void func_00f51518(void) {
    while (1) {
        if (D_00F9B518 == 0) {
            func_00f52ab0(D_00F9B548, D_00F9B544, 1);
        }
        func_001bfac8();
    }
}
