/* wm.x func_00f60548: matched by hand. */
#include "ovl.h"

u64 *func_00f66ac8(u64 *);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void func_00f66fe8(s32, s32);
void func_00f4e3e8(s32);
void func_00f4e480(s32, u64 **, s32, s32, s32, s32, f32, f32);
extern u64 *D_00F9B548;

void func_00f60548(s32 x, s32 y, s32 a2, s32 a3, f32 f) {
    u64 *p;

    p = func_00f66b78(func_00f66ac8(D_00F9B548));
    p[1] = 24;
    p[0] = (u64)((2048 - x) << 4) | ((u64)((2048 - y) << 4) << 32);
    p += 2;
    func_00f66b90(p);
    func_00f66fe8(10, func_00f66ae0(p));
    D_00F9B548 = p;
    func_00f4e3e8(1);
    func_00f4e480(11, &D_00F9B548, a2, 0, a3, 0, f, 1.0f);
    func_00f4e3e8(0);
    p = func_00f66b78(func_00f66ac8(D_00F9B548));
    p[0] = (u64)(0x700 << 4) | ((u64)(0x740 << 4) << 32);
    p[1] = 24;
    p += 2;
    func_00f66b90(p);
    func_00f66fe8(12, func_00f66ae0(p));
    D_00F9B548 = p;
}
