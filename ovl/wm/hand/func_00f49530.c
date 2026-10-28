/* wm.x func_00f49530: matched by hand. */
#include "ovl.h"

extern s32 D_002BBDE4;
extern s32 D_00F9B560;
extern s32 D_00F9B564;
void func_001bb558(void);
s32 func_001be5d0(s32);
void func_001efb18(s32, s32);
s32 func_001efbb8(s32);
u64 *func_001f0758(u64 *, s32, s32, s32, s32, s32, s32);
void func_00f49458(u8 *, s32);

u64 *func_00f49530(u64 *p, s32 mode, s32 a2, s32 a3, s32 a4) {
    u8 buf[256];
    s32 w1, w2;
    switch (mode) {
    case 1:
        switch (D_002BBDE4) {
        case 0:
        case 5:
        default:
            w1 = 172;
            w2 = 172;
            break;
        case 3:
            w1 = 164;
            w2 = 164;
            break;
        case 1:
        case 2:
        case 4:
        case 6:
            w1 = 172;
            w2 = 164;
            break;
        }
        func_00f49458(buf, a2);
        p = func_001f0758(p, 1, a3, w1, 16, (s32)buf, 16);
        func_001bb558();
        p = func_001f0758(p, 1, a4, w2, 34, func_001efbb8(func_001be5d0(a2)), 16);
        break;
    case 2:
        func_001efb18(D_00F9B560, D_00F9B564);
        p = func_001f0758(p, 1, a3, 172, 16, func_001efbb8(a2), 16);
        break;
    case 3:
        func_001efb18(D_00F9B560, D_00F9B564);
        p = func_001f0758(p, 1, a4, 172, 16, func_001efbb8(a2), 16);
        if (a3)
            p = func_001f0758(p, 1, a4, 172, 34, func_001efbb8(a3), 16);
        break;
    }
    return p;
}
