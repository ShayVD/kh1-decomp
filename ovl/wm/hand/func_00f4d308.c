/* wm.x func_00f4d308: matched by hand. */
#include "ovl.h"

void func_001efb18(s32, s32);
u64 *func_001f0670(u64 *, s32, s32, s32, s32, s32);
s32 func_00f66ac8(u64 *);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);
void func_00f66f78(s32, s32);
extern u64 *D_00F9B548;
extern s32 D_00F9B560;
extern s32 D_00F9B564;
extern s32 D_0108BC9C;

void func_00f4d308(void) {
    u64 *p;
    if (D_0108BC9C > 0) {
        func_001efb18(D_00F9B560, D_00F9B564);
        p = func_00f66b78(func_00f66ac8(D_00F9B548));
        p[0] = (u64)(0x700 << 4) | ((u64)(0x740 << 4) << 32);
        p[1] = 0x18;
        p += 2;
        func_00f66b90(p);
        p = func_001f0670(p, 1, 0x602ADD65, 0xAC, 0x10, D_0108BC9C);
        func_00f66f78(0x2E40, func_00f66ae0(p));
        D_00F9B548 = p;
    }
}
