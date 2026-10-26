/* dkmovie.x func_00f22df8: matched by hand. */
#include "ovl.h"

void func_00f22df8(s32 arg0) {
    *(volatile s32 *)0x1000A030 = arg0;
    *(volatile s32 *)0x1000A020 = 0;
    *(volatile s32 *)0x1000A000 = 0x105;
}
