/* wm.x func_00f67170: matched by hand. */
#include "ovl.h"

void iFlushCache(s32);

s32 func_00f67170(u32 *arg0) {
    u32 a = arg0[4];
    *(volatile u32 *)0x10009020 = 0;
    *(volatile u32 *)0x10009030 = a & 0x0FFFFFFF;
    *(volatile u32 *)0x1000E010 = 2;
    iFlushCache(0);
    *(volatile u32 *)0x10009000 = 0x145;
    return 2;
}
