/* gb.x func_00f3c408: matched by hand. */
#include "ovl.h"

u64 *func_001f0798(u64 *, s32, s32, s32, s32, s32, s32);
u64 *func_00f3f9d0(u64 *);
s32 func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
void func_00f3fe80(s32, s32);
s32 func_00f3c1d8(s32);
extern u64 **D_00F61F58;
extern s32 D_00F61F5C;

void func_00f3c408(s32 a0, s32 a1, s32 a2) {
    u64 *p;

    p = func_00f3fa80(func_00f3f9d0(*D_00F61F58));
    p[0] = (u64)(0x700 << 4) | ((u64)(0x740 << 4) << 32);
    p[1] = 0x18;
    p += 2;
    func_00f3fa98(p);
    p = func_001f0798(p, 1, 0x80808080, a0, a1, func_00f3c1d8(a2), D_00F61F5C);
    func_00f3fe80(0x9C40, func_00f3f9e8(p));
    *D_00F61F58 = p;
}
