/* dkmovie.x func_00f27568: matched by hand. */
#include "ovl.h"

s32 sceIpuSync(s32, s32);
void func_00f27568(void) {
    *(volatile s32 *)0x1000F590 = 0x10000;
    *(volatile s32 *)0x1000B000 &= ~0x100;
    *(volatile s32 *)0x1000F590 = 0;
    *(volatile s32 *)0x10002010 = 0x40000000;
    sceIpuSync(0, 0);
    *(volatile s32 *)0x10002000 = 0;
    sceIpuSync(0, 0);
}
