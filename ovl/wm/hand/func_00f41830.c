/* wm.x func_00f41830: matched by hand. */
#include "ovl.h"

u64 *func_001f0868(u64 *, s32, s32, s32, s32, s32, s32, s32);
u64 *func_00f41660(s32, s32, s32, s32, u64 *);
s32 func_00f66ac8(s32);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);
void func_00f66fb0(s32, s32);
extern u64 **D_00F85160;

void func_00f41830(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u64 *p = func_00f66b78(func_00f66ac8((s32)*D_00F85160));
    p[1] = 20;
    p[0] = 0;
    p += 2;
    p[0] = 0x30000;
    p[1] = 71;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    func_00f66b90(p);
    p = func_00f41660(arg0, arg1, arg2, arg3, p);
    if (arg5 != 0) {
        p = func_001f0868(p, 1, 1, (arg4 << 24) | 0xFFFFFF, arg0 + 170, arg1 + 24, arg5, 16);
    }
    func_00f66fb0(33, func_00f66ae0(p));
    *D_00F85160 = p;
}
