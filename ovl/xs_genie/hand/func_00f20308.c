/* xs_genie.x func_00f20308: matched by hand. */
#include "ovl.h"

s32 func_0013aa60(void);
CONTEXT_ONLY void func_00f200a0(s32 a) {}
s32 func_00122ff8(s32);
void func_00f21878(void);
void func_00f20eb8(void);
s32 func_00f214b8(void);
s32 func_00147be0(s32);
extern f32 D_002BBDFC;
extern s32 D_002E31B0;
extern s32 D_002E31B8;
extern u8 *D_00304B70;
extern f32 D_00304B7C;
extern s32 D_00F22E98;
extern s32 D_00FC0E48;
extern s32 D_00FC0F00;
s32 func_00f20308(void) {
    D_00304B7C -= D_00304B70[1] * D_002BBDFC;
    switch (D_00FC0E48) {
    case 2:
        break;
    case 0:
        if (func_0013aa60() == 0) {
            if (D_002E31B8 == 3) {
                func_00f200a0(1);
            }
        } else {
            func_00f200a0(100);
        }
        break;
    case 1:
        if (func_0013aa60()) {
            func_00f200a0(100);
        } else if (D_002E31B8 != 3 || func_00122ff8(D_002E31B0) == 0) {
            func_00f21878();
            func_00f200a0(0);
        } else {
            func_00f20eb8();
        }
        break;
    case 100:
        if (func_00f214b8() == 0 && func_00147be0(D_00F22E98) == 0) {
            func_00f200a0(101);
        }
        break;
    case 101:
        D_00FC0F00 = 0;
        return 4;
    }
    return 0;
}
