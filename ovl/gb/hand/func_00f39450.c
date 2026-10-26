/* gb.x func_00f39450: matched by hand. */
#include "ovl.h"

u64 *func_00f3f9d0(u64 *);
s32 func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
void func_00f3fef0(s32, s32);
void func_00f272f0(s32);
void func_00f27388(s32, u64 **, s32, s32, s32, s32, f32, f32);
extern u64 *D_00F56DC8;

void func_00f39450(s32 x, s32 y, s32 a2, s32 a3, f32 f) {
    u64 *p;

    p = func_00f3fa80(func_00f3f9d0(D_00F56DC8));
    p[1] = 24;
    p[0] = (u64)((2048 - x) << 4) | ((u64)((2048 - y) << 4) << 32);
    p += 2;
    func_00f3fa98(p);
    func_00f3fef0(10, func_00f3f9e8(p));
    D_00F56DC8 = p;
    func_00f272f0(1);
    func_00f27388(11, &D_00F56DC8, a2, 0, a3, 0, f, 1.0f);
    func_00f272f0(0);
    p = func_00f3fa80(func_00f3f9d0(D_00F56DC8));
    p[0] = (u64)(0x700 << 4) | ((u64)(0x740 << 4) << 32);
    p[1] = 24;
    p += 2;
    func_00f3fa98(p);
    func_00f3fef0(12, func_00f3f9e8(p));
    D_00F56DC8 = p;
}
