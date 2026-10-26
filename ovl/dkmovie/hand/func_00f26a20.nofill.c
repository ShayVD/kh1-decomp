/* dkmovie.x func_00f26a20: matched by hand. */
#include "ovl.h"

void func_00f26a20(u32 addr, s32 size) {
    if (addr > 0x6FFFFFFF) {
        addr += 0x80000000;
    }
    *(volatile u32 *)0x1000B010 = addr;
    *(volatile s32 *)0x1000B020 = size / 16;
    *(volatile s32 *)0x1000B000 = 0x100;
}
