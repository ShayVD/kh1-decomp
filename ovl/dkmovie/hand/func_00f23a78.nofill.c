/* dkmovie.x func_00f23a78: matched by hand. */
#include "ovl.h"

void func_00f23a78(s32 arg0) {
    *(volatile s32 *)0x1000B430 = arg0;
    *(volatile s32 *)0x1000B420 = 0;
    *(volatile s32 *)0x1000B400 = 0x105;
}
