/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void *func_001760b0(s32);
void *func_001760d0(s32);
void *func_001760f0(s32);

s32 func_001de328(void *arg0) {
    s32 temp_s1;
    void *temp_a0;
    void *temp_v0;

    temp_s1 = arg0 + 4;
    temp_v0 = func_001760d0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x174));
    if (temp_v0 != NULL) {
        temp_a0 = M2C_FIELD(temp_v0, void **, 4);
        M2C_FIELD(temp_a0, s32 *, 0) = (s32) (((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x178) / 360.0f) * 65535.0f);
        M2C_FIELD(temp_a0, s32 *, 4) = (s32) (((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x17C) / 360.0f) * 65535.0f);
        M2C_FIELD(temp_a0, s32 *, 8) = (s32) (((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) / 360.0f) * 65535.0f);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 4);
    return 2;
}

s32 func_001df3a8(void *arg0) {
    s32 temp_s1;
    void *temp_a0;
    void *temp_v0;

    temp_s1 = arg0 + 4;
    temp_v0 = func_001760f0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x174));
    if (temp_v0 != NULL) {
        temp_a0 = M2C_FIELD(temp_v0, void **, 4);
        M2C_FIELD(temp_a0, s32 *, 0) = (s32) (((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x178) / 360.0f) * 65535.0f);
        M2C_FIELD(temp_a0, s32 *, 4) = (s32) (((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x17C) / 360.0f) * 65535.0f);
        M2C_FIELD(temp_a0, s32 *, 8) = (s32) (((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) / 360.0f) * 65535.0f);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 4);
    return 2;
}

s32 func_001dfbb8(void *arg0) {
    s32 temp_s1;
    void *temp_a0;
    void *temp_v0;

    temp_s1 = arg0 + 4;
    temp_v0 = func_001760b0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x174));
    if (temp_v0 != NULL) {
        temp_a0 = M2C_FIELD(temp_v0, void **, 4);
        M2C_FIELD(temp_a0, s32 *, 0) = (s32) (((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x178) / 360.0f) * 65535.0f);
        M2C_FIELD(temp_a0, s32 *, 4) = (s32) (((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x17C) / 360.0f) * 65535.0f);
        M2C_FIELD(temp_a0, s32 *, 8) = (s32) (((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) / 360.0f) * 65535.0f);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 4);
    return 2;
}
