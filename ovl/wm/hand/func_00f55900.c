/* wm.x func_00f55900: matched by hand. */
#include "ovl.h"

s32 func_00f4d5f8(s32);
s32 func_00f4dda0(s32, s32, s32, s32, s32, s32, s32, s32, u64, u64);
s32 func_00f4e0b0(s32, s32, s32);
s32 func_00f66ac8(s32);
s32 func_00f66ae0(s32);
void func_00f66f78(s32, s32);

void func_00f55900(s32 *p) {
    u64 t = 0x620013200;
    *p = func_00f66ac8(*p);
    *p = func_00f4d5f8(*p);
    *p = func_00f4e0b0(*p, 0, 0);
    *p = func_00f4dda0(*p, 49, 279, 0, 0, 0, 88, 84, 0x3F80000080808080, t);
    *p = func_00f4e0b0(*p, 0x700, 0x740);
    func_00f66f78(0x2B72, func_00f66ae0(*p));
}
