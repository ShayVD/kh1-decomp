/* gb.x func_00f400e0: matched by hand. */
#include "ovl.h"

void FlushCache(s32);
s32 sceDmaGetChan(s32);
s32 sceDmaSync(s32, s32, s32);
s32 sceGsSyncPath(s32, s32);

void func_00f400e0(u32 arg0) {
    *(volatile u32 *)0x10009020 = 0;
    *(volatile u32 *)0x10009030 = arg0 & 0x0FFFFFFF;
    *(volatile u32 *)0x1000E010 = 2;
    FlushCache(0);
    *(volatile u32 *)0x10009000 = 0x145;
    sceDmaSync(sceDmaGetChan(1), 0, 0);
    sceGsSyncPath(0, 0);
}
