/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00100ae0();
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
extern M2C_UNK func_00112ad8;
extern s32 D_002BBE1C;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
extern s32 D_002BCDA8;
#include "data/pieces/D_002BCB60.h"
s32 func_00111660(s32, s32);

void func_00111830(void) {
    s32 temp_a0;
    s32 temp_v0;

    D_002BBE1C = 1;
    temp_a0 = M2C_FIELD(D_002BCB60, s32 *, 0x40);
    D_002BC128 = temp_a0;
    temp_v0 = M2C_FIELD(D_002BCB60, s32 *, 0x44);
    D_002BC130 = temp_v0;
    D_002BC134 = func_00111660(temp_a0, temp_v0);
    D_002BCDA8 = M2C_FIELD(D_002BCB60, s32 *, 0x48);
}

void func_00112b18(void) {
    func_00100ae0();
    func_0011ef10(0x2E630, &func_00112ad8);
}
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/pieces/D_002BC128.h"
