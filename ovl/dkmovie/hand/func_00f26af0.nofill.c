/* dkmovie.x func_00f26af0: matched by hand. */
#include "ovl.h"

void func_00f26af0(s32 arg0, s32 arg1, s32 size) {
    *(volatile s32 *)0x1000E030 = 0xFF0000;
    *(volatile s32 *)0x1000E000 &= 0x7CF;
    *(volatile s32 *)0x1000D010 = arg0;
    *(volatile s32 *)0x1000D080 = arg1;
    *(volatile s32 *)0x1000D020 = size / 16;
    *(volatile s32 *)0x1000D000 = 0x100;
}
