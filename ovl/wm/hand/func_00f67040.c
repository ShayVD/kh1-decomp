/* wm.x func_00f67040: matched by hand. */
#include "ovl.h"

void iFlushCache(s32);
s32 sceDmaGetChan(s32);
extern u32 D_0108F03C;

s32 func_00f67040(u32 *arg0) {
    u32 a;
    sceDmaGetChan(2);
    a = arg0[4];
    D_0108F03C = a;
    *(volatile u32 *)0x1000A020 = 0;
    *(volatile u32 *)0x1000A030 = a & 0x0FFFFFFF;
    *(volatile u32 *)0x1000E010 = 4;
    iFlushCache(0);
    *(volatile u32 *)0x1000A000 = 0x145;
    return 2;
}
