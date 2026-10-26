/* wm.x func_00f63500: matched by hand. */
#include "ovl.h"

u64 *func_001f0798(u64 *, s32, s32, s32, s32, s32, s32);
u64 *func_00f66ac8(u64 *);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void func_00f66f78(s32, s32);
s32 func_00f632d0(s32);
extern u64 **D_00FA66D8;
extern s32 D_00FA66DC;

void func_00f63500(s32 a0, s32 a1, s32 a2) {
    u64 *p;

    p = func_00f66b78(func_00f66ac8(*D_00FA66D8));
    p[0] = (u64)(0x700 << 4) | ((u64)(0x740 << 4) << 32);
    p[1] = 0x18;
    p += 2;
    func_00f66b90(p);
    p = func_001f0798(p, 1, 0x80808080, a0, a1, func_00f632d0(a2), D_00FA66DC);
    func_00f66f78(0x9C40, func_00f66ae0(p));
    *D_00FA66D8 = p;
}
