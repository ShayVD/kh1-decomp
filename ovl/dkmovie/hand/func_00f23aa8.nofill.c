/* dkmovie.x func_00f23aa8: matched by hand. */
#include "ovl.h"

void func_00f23aa8(s32 arg0, s32 arg1) {
    *(volatile s32 *)0x1000B010 = arg0;
    *(volatile s32 *)0x1000B020 = arg1 << 6;
    *(volatile s32 *)0x1000B000 = 0x100;
}
