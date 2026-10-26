/* gb.x func_00f3f7d8: matched by hand. */
#include "ovl.h"

void iFlushCache(s32);
void FlushCache(s32);

void func_00f3f7d8(u32 arg0, s32 arg1) {
    *(volatile u32 *)0x10009020 = 0;
    *(volatile u32 *)0x10009030 = arg0 & 0x0FFFFFFF;
    *(volatile u32 *)0x1000E010 = 2;
    if (arg1 != 0) {
        iFlushCache(0);
    } else {
        FlushCache(0);
    }
    *(volatile u32 *)0x10009000 = 0x145;
}
