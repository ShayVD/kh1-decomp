/* gb.x func_00f3ffd0: matched by hand. */
#include "ovl.h"

void FlushCache(s32);
s32 sceDmaGetChan(s32);
s32 sceDmaSync(s32, s32, s32);
s32 sceGsSyncPath(s32, s32);

void func_00f3ffd0(u32 arg0) {
    s32 ch = sceDmaGetChan(2);
    sceDmaSync(ch, 0, 0);
    *(volatile u32 *)0x1000A020 = 0;
    *(volatile u32 *)0x1000A030 = arg0 & 0x0FFFFFFF;
    *(volatile u32 *)0x1000E010 = 4;
    FlushCache(0);
    *(volatile u32 *)0x1000A000 = 0x145;
    sceDmaSync(ch, 0, 0);
    sceGsSyncPath(0, 0);
}
