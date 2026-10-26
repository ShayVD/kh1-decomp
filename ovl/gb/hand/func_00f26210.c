/* gb.x func_00f26210: matched by hand. */
#include "ovl.h"

void func_001efb18(s32, s32);
u64 *func_001f0670(u64 *, s32, s32, s32, s32, s32);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
u64 *func_00f3fa98(u64 *);
void func_00f3fe80(s32, u64 *);
extern u64 *D_00F56DC8;
extern s32 D_00F56DE0;
extern s32 D_00F56DE4;
extern s32 D_00F7F4DC;

void func_00f26210(void) {
    u64 *p;
    if (D_00F7F4DC > 0) {
        func_001efb18(D_00F56DE0, D_00F56DE4);
        p = func_00f3fa80(func_00f3f9d0(D_00F56DC8));
        p[0] = 0x740000007000; p[1] = 0x18;
        p += 2;
        func_00f3fa98(p);
        p = func_001f0670(p, 1, 0x602ADD65, 0xAC, 0x10, D_00F7F4DC);
        func_00f3fe80(0x2E40, func_00f3f9e8(p));
        D_00F56DC8 = p;
    }
}
