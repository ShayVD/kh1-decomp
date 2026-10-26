/* gb.x func_00f43c38: matched by hand. */
#include "ovl.h"

s32 func_001f40c8(void);
void func_001f82b0(void);
void func_0020b998(void);
extern s32 D_00F70734;
extern u8 D_00F70739;
extern u8 D_00F7073A;
extern s32 D_00F829C4;

s32 func_00f43c38(void) {
    s32 r = func_001f40c8(); if (r != 0) { func_001f82b0(); func_0020b998(); return 0; } if (D_00F829C4 == 0) { D_00F70734 = -1; D_00F70739 = D_00F7073A; return 4; } return r;
}
