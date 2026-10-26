/* wm.x func_00f55670: matched by hand. */
#include "ovl.h"

s32 func_00f4d618(s32, s32, s32, s32, s32);
s32 func_00f4d780(s32, s32, s32, s32, s32, s32, s32);
s32 func_00f4dda0(s32, s32, s32, s32, s32, s32, s32, s32, u64, u64);
s32 func_00f4e0b0(s32, s32, s32);
s32 func_00f66ac8(s32);
s32 func_00f66ae0(s32);
void func_00f66f78(s32, s32);
extern u8 *D_00F9B540;
extern s32 D_00FA6000[];

void func_00f55670(s32 *p) {
    *p = func_00f66ac8(*p);
    *p = func_00f4d618(*p, 400, 256, 256, 1);
    *p = func_00f4e0b0(*p, 0, 0);
    *p = func_00f4dda0(*p, 0, 0, 0, D_00FA6000[6], D_00FA6000[7], D_00FA6000[8], D_00FA6000[9], 0x3F80000080000000, *(u64 *)(D_00F9B540 + 0x2208));
    *p = func_00f4d780(*p, 400, 256, 0, 0, 0, 255);
    func_00f66f78(0x2B70, func_00f66ae0(*p));
}
