/* dkmovie.x func_00f26a80: matched by hand. */
#include "ovl.h"

void func_00f26a80(s32 arg0, s32 arg1, s32 size) {
    *(volatile s32 *)0x1000E030 = 0xFF0000;
    *(volatile s32 *)0x1000E000 &= 0x7CF;
    *(volatile s32 *)0x1000D410 = arg1;
    *(volatile s32 *)0x1000D480 = arg0;
    *(volatile s32 *)0x1000D420 = size / 16;
    *(volatile s32 *)0x1000D400 = 0x101;
}
