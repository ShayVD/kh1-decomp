/* xl_limit.x func_00f20228: matched by hand. */
#include "ovl.h"

s32 func_00147be0(s32);
void func_001224c8(s32, void *, void *, f32);
void func_00122768(void);
extern s32 D_002C5958;
extern u8 D_002C5C60[];
extern s32 D_00F23200;
extern s32 D_00F23208;
extern s32 D_00F2320C;
extern s32 D_00F23E00;
s32 func_00f20228(void) {
    if ((D_002C5958 & 0x810000) != 0x10000) {
        return 4;
    }
    if (func_00147be0(D_00F23208) != 0 || D_00F23E00 > 0) {
        return 0;
    }
    if (D_00F2320C != 0) {
        func_001224c8(D_00F2320C, D_002C5C60, func_00122768, 30.0f);
    }
    D_00F23200 = 0;
    return 4;
}
