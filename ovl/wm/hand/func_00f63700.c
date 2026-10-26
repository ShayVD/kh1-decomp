/* wm.x func_00f63700: matched by hand. */
#include "ovl.h"

u64 *func_001f0798(u64 *, s32, s32, s32, s32, s32, s32);
s32 func_00f66ac8(s32);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);
void func_00f66f78(s32, s32);
s32 func_00f632d0(s32);

u64 *func_00f63700(s32 id, s32 a1, s32 a2, s32 a3, s32 a4, s32 pk) {
    u64 *p;

    p = func_00f66b78(func_00f66ac8(pk));
    p[0] = (u64)(0x700 << 4) | ((u64)(0x740 << 4) << 32);
    p[1] = 0x18;
    p += 2;
    func_00f66b90(p);
    p = func_001f0798(p, 1, a3, a1, a2, func_00f632d0(a4), 20);
    func_00f66f78(id, func_00f66ae0(p));
    return p;
}
