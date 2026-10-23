/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0063.h"

M2C_UNK func_0011cdf0(M2C_UNK, s32, M2C_UNK *, M2C_UNK);
M2C_UNK func_00146928(M2C_UNK);
#include "data/pieces/D_003DBA68.h"
extern M2C_UNK func_001e8e38;
extern s32 D_002C5958;
extern s32 D_003DD310;
extern s32 D_003DD314;
extern s32 D_003F7A68;
extern s32 D_00631560;
extern s32 D_0063F740;
extern s32 D_0063F744; /* src/data/bss_0063.c: u8 *D_0063F744 */
extern s32 D_0063F748; /* src/data/bss_0063.c: u16 *D_0063F748 */
s32 func_0011e340(M2C_UNK);
s32 func_001ee768();

/* func_001e2a30, func_001e31b0, func_001e32c8, func_001e3728, func_001e39f0, func_001e3ef0 are in src/shop/shop.c. */






/* func_001e6578, func_001e6b70, func_001e7928, func_001e7a60, func_001e7b48 are in src/list/list.c. */





s32 func_001e8e68(void) {
    if (func_0011e340(0) == 0) {
        func_00146928(-6);
        func_00146928(-7);
        D_002C5958 |= 0x40000;
        func_0011cdf0(-8, D_00631560, &func_001e8e38, 0x40000);
        return 4;
    }
    return 0;
}

void func_001e9650(void) {
    D_003DD310 = -4;
    D_003DD314 = -2;
}

s32 func_001ef370(s32 arg0) {
    if (arg0 != 0) {
        return func_001ee768() == 1;
    }
    return 0;
}

void func_001efb18(s32 arg0, s32 arg1) {
    D_0063F744 = arg0;
    D_0063F748 = arg1;
}

void func_001efb58(s32 arg0) {
    D_0063F740 = arg0 * 0x10;
}

s32 func_001efb68(void) {
    return (s32) D_0063F740 >> 4;
}
#include "data/data_003D.h"
#include "data/data_003F.h"
#include "data/pieces/D_003F7A68.h"
