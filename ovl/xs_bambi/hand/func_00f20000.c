/* xs_bambi.x func_00f20000: matched by hand (session 131b). */
#include "ovl.h"

extern u8 *D_00304B70;
extern f32 D_00F20A04, D_00F20A08;
extern s32 D_00F20A00;
extern void *D_00F20900, *D_00F20904, *D_00F20A0C;
void func_00f20270(void);
void func_00f20108(s32);
void func_00f20390(s32);
void func_00137330(void *, void *, s32);
void func_00148968(void *, void *, s32);
s32 func_00f20000(u32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
        func_00f20270();
        return 0;
    case 1:
        return D_00F20A00;
    case 2:
        func_00f20108(101);
        return 0;
    case 5:
        D_00F20A04 += (f32)D_00304B70[2] * 100.0f;
        if (D_00F20A08 <= D_00F20A04) {
            func_00137330(D_00F20904, D_00F20900, 2501);
            D_00F20A04 = 0.0f;
        }
        func_00148968(D_00F20900, D_00F20A0C, 8);
        return 0;
    case 6:
        func_00f20390(arg1);
        break;
    }
    return 0;
}
