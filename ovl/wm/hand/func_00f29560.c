/* wm.x func_00f29560: matched by hand. */
#include "ovl.h"

s64 *func_001f0798(s64 *, s32, s32, s32, s32, s32, s32);
s64 *func_00f66ac8(s64 *);
s32 func_00f66ae0(s64 *);
void func_00f66f78(s32, s32);
extern s64 **D_00F85160;

void func_00f29560(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s64 *p = func_00f66ac8(*D_00F85160);
    p[0] = ((s64) 0x10000000 << 32) | 0x8001;
    p[1] = 14;
    p[2] = ((s64) 0x7400 << 32) | 0x7000;
    p[3] = 24;
    p = func_001f0798(p + 4, 1, arg4, arg1, arg2, arg5, arg3);
    func_00f66f78(arg0, func_00f66ae0(p));
    *D_00F85160 = p;
}
