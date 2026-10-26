/* xs_bambi.x func_00f20188: matched by hand (session 131b). */
#include "ovl.h"

extern u8 *D_00304B70;
extern f32 D_00304B7C;
extern f32 D_002BBDFC;
extern s32 D_00F20908, D_00F20A00;
extern void *D_00F20A0C;
s32 func_0013aa60(void);
void *func_00123488(s32);
s32 func_00147be0(void *);
void func_00f20108(s32);
s32 func_00f20188(void) {
    D_00304B7C -= (f32)D_00304B70[1] * D_002BBDFC;
    switch (D_00F20908) {
    case 0:
        if (func_0013aa60() != 0) {
            func_00f20108(100);
        }
        break;
    case 100:
        if (func_00123488(0x70001) == 0 && func_00147be0(D_00F20A0C) == 0) {
            func_00f20108(101);
        }
        break;
    case 101:
        D_00F20A00 = 0;
        return 4;
    }
    return 0;
}
