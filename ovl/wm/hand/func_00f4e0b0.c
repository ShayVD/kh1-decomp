/* wm.x func_00f4e0b0: matched by hand. */
#include "ovl.h"

u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);

u64 *func_00f4e0b0(s32 arg0, s32 arg1, s32 arg2) {
    u64 *p;

    p = func_00f66b78(arg0);
    p[1] = 0x18;
    p[0] = (u64)(arg1 << 4) | ((u64)(arg2 << 4) << 32);
    p += 2;
    func_00f66b90(p);
    return p;
}
