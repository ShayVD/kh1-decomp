/* dkmovie.x func_00f269c0: matched by hand. */
#include "ovl.h"

void func_00f269c0(u32 addr, s32 size) {
    if (addr > 0x6FFFFFFF) {
        addr += 0x80000000;
    }
    *(volatile u32 *)0x1000B410 = addr;
    *(volatile s32 *)0x1000B420 = size / 16;
    *(volatile s32 *)0x1000B400 = 0x101;
}
