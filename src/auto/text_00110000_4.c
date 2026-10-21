/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00102a48(M2C_UNK, M2C_UNK);
M2C_UNK func_0010a3e8();
extern M2C_UNK func_00113f18;
#include "data/pieces/D_002BCB60.h"
s32 func_0013c318(M2C_UNK);
void *func_0011ef10(M2C_UNK, M2C_UNK *);

void func_001118f0(void) {
    if (func_0013c318(3) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 8);
    }
    if (func_0013c318(5) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x20);
    }
    if (func_0013c318(6) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x40);
    }
    if (func_0013c318(7) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x80);
    }
    if (func_0013c318(8) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x100);
    }
    if (func_0013c318(9) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x200);
    }
}

s32 func_00113f60(void) {
    M2C_FIELD(func_0011ef10(0x2E643, &func_00113f18), s16 *, 2) = 1;
    func_0010a3e8();
    func_00102a48(0x80, 0x10);
    return 4;
}
