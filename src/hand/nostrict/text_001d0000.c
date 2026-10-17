/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern f32 D_002BBDFC;

void func_001d9510(void *arg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f2;
    void *temp_v0;
    void *temp_v1;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x44);
    temp_f0 = M2C_FIELD(arg0, f32 *, 0x48) + D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x48) = temp_f0;
    if (temp_f2 < temp_f0) {
        temp_v1 = M2C_FIELD(arg0, void **, 4);
        M2C_FIELD(temp_v1, f32 *, 0x30) = (f32) M2C_FIELD(arg0, f32 *, 0x38);
        M2C_FIELD(temp_v1, f32 *, 0x34) = (f32) M2C_FIELD(arg0, f32 *, 0x3C);
        M2C_FIELD(temp_v1, f32 *, 0x38) = (f32) M2C_FIELD(arg0, f32 *, 0x40);
        M2C_FIELD(arg0, s64 *, 0x328) = (s64) (M2C_FIELD(arg0, s64 *, 0x328) & ~0x1000);
        return;
    }
    temp_f1 = M2C_FIELD(arg0, f32 *, 0x2C);
    temp_v0 = M2C_FIELD(arg0, void **, 4);
    M2C_FIELD(temp_v0, f32 *, 0x30) = (f32) (temp_f1 + ((M2C_FIELD(arg0, f32 *, 0x38) - temp_f1) * (temp_f0 / temp_f2)));
    temp_f1_2 = M2C_FIELD(arg0, f32 *, 0x30);
    M2C_FIELD(temp_v0, f32 *, 0x34) = (f32) (temp_f1_2 + ((M2C_FIELD(arg0, f32 *, 0x3C) - temp_f1_2) * (M2C_FIELD(arg0, f32 *, 0x48) / M2C_FIELD(arg0, f32 *, 0x44))));
    temp_f1_3 = M2C_FIELD(arg0, f32 *, 0x34);
    M2C_FIELD(temp_v0, f32 *, 0x38) = (f32) (temp_f1_3 + ((M2C_FIELD(arg0, f32 *, 0x40) - temp_f1_3) * (M2C_FIELD(arg0, f32 *, 0x48) / M2C_FIELD(arg0, f32 *, 0x44))));
}
