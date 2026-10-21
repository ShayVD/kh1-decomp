/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00152880(void *);
#include "data/pieces/D_002C58A0.h"
extern f32 D_002BBDFC;
s32 func_0014f600(s32);
void func_002675a8(void *, M2C_UNK *);

void func_00151148(void *arg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    void *temp_s0;

    temp_f1 = M2C_FIELD(arg0, f32 *, 0x24);
    temp_s0 = M2C_FIELD(arg0, void **, 0x144);
    if (temp_f1 < 0.0f) {
        M2C_FIELD(arg0, f32 *, 0x24) = (f32) (temp_f1 + M2C_FIELD(temp_s0, f32 *, 0x30));
        goto block_4;
    }
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & ~0x20);
    temp_f1_2 = M2C_FIELD(temp_s0, f32 *, 0x30) + -0.05f;
    M2C_FIELD(temp_s0, f32 *, 0x30) = temp_f1_2;
    temp_f0 = M2C_FIELD(arg0, f32 *, 0x24) + temp_f1_2;
    M2C_FIELD(arg0, f32 *, 0x24) = temp_f0;
    if (temp_f0 < 0.0f) {
        func_002675a8(arg0 + 0x20, ((M2C_UNK *)&D_002C58A0));
        M2C_FIELD(temp_s0, s32 *, 0) = 1;
        return;
    }
block_4:
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) (M2C_FIELD(arg0, f32 *, 0x20) * 0.95f);
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) (M2C_FIELD(arg0, f32 *, 0x28) * 0.95f);
}

void func_00153210(void *arg0) {
    s32 temp_v0;
    void *temp_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 8);
    if ((temp_v0 != 0) && (func_0014f600(temp_v0) != 0)) {
        temp_v1 = M2C_FIELD(arg0, void **, 0x144);
        M2C_FIELD(temp_v1, f32 *, 0x10) = (f32) (M2C_FIELD(temp_v1, f32 *, 0x10) + D_002BBDFC);
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), f32 *, 0x10) >= 1.2e+02f) {
            func_00152880(arg0);
            return;
        }
        goto block_6;
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), f32 *, 0x10) = 0.0f;
block_6:
    if (M2C_FIELD(arg0, s32 *, 0x8C) >= 2) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), f32 *, 0x18) = 12.0f;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), s32 *, 4) = 5;
    }
}
#include "data/pieces/D_002BBDFC.h"
