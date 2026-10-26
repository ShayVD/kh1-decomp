/* dkmovie.x func_00f26be0: matched by hand. */
#include "ovl.h"

void FlushCache(s32);
void func_00f26968(u8 *, void *, s32);
void func_00f269c0(u8 *, s32);
s32 func_00f27568(void);
s32 sceGsSyncPath(s32, s32);
void sceIpuInit(void);
extern u8 *D_00F28460;
extern s32 D_00F28690;
extern s32 D_00F286D0;
void func_00f26be0(void) {
    sceGsSyncPath(0, 0);
    sceIpuInit();
    func_00f27568();
    func_00f26968(D_00F28460, &D_00F28690, 0);
    func_00f26968(D_00F28460 + 64, &D_00F286D0, 0);
    FlushCache(0);
    func_00f269c0(D_00F28460, 64);
    *(volatile u32 *)0x10002000 = 0x50000000;
    while ((*(volatile u32 *)0x1000B000 >> 8) & 1) {
    }
    while (*(volatile s32 *)0x10002010 < 0) {
    }
    func_00f269c0(D_00F28460 + 64, 64);
    *(volatile u32 *)0x10002000 = 0x58000000;
    while ((*(volatile u32 *)0x1000B000 >> 8) & 1) {
    }
    while (*(volatile s32 *)0x10002010 < 0) {
    }
}
