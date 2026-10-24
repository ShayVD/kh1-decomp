/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void pppMoveCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

void pppAcceleCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

void pppScaleCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

void pppSclMoveCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

void pppSclAcceleCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}

void pppVtMimeReset(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xA0) = M2C_FIELD(temp_a0_2, f32 *, 4) = M2C_FIELD(temp_a0_2, f32 *, 8) = 0.0f;
}
