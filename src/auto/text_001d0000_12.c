/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00131c28(s32, f32);
extern s32 (*D_003773E8)(s32, void *);
s32 func_00135838(s32);
void *func_001e98d0(s32, s32);
void func_0014ec10(s32);
void func_0014ec38(s32);

s32 func_001d2668(void *arg0) {
    s32 temp_s1;
    s32 temp_v1;

    temp_s1 = arg0 + 4;
    temp_v1 = M2C_FIELD(func_001e98d0((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x328) << 0x1B) >> 0x20) & 1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180)), s32 *, 4);
    if (temp_v1 != 0) {
        func_00131c28(temp_v1, (f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x17C) / 1e+02f);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 2);
    return 2;
}

s32 func_001d40f0(void *arg0) {
    s32 temp_s1;
    void *temp_a0;

    temp_s1 = arg0 + 4;
    temp_a0 = M2C_FIELD(func_001e98d0((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x328) << 0x1B) >> 0x20) & 1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180)), void **, 4);
    if (temp_a0 != NULL) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = (s32) M2C_FIELD(temp_a0, f32 *, 0x10);
    }
    return 2;
}

s32 func_001d4168(void *arg0) {
    s32 temp_s1;
    void *temp_a0;

    temp_s1 = arg0 + 4;
    temp_a0 = M2C_FIELD(func_001e98d0((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x328) << 0x1B) >> 0x20) & 1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180)), void **, 4);
    if (temp_a0 != NULL) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = (s32) M2C_FIELD(temp_a0, f32 *, 0x14);
    }
    return 2;
}

s32 func_001d41e0(void *arg0) {
    s32 temp_s1;
    void *temp_a0;

    temp_s1 = arg0 + 4;
    temp_a0 = M2C_FIELD(func_001e98d0((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x328) << 0x1B) >> 0x20) & 1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180)), void **, 4);
    if (temp_a0 != NULL) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = (s32) M2C_FIELD(temp_a0, f32 *, 0x18);
    }
    return 2;
}

s32 func_001d4258(void *arg0) {
    s32 temp_s1;
    void *temp_v1;

    temp_s1 = arg0 + 4;
    temp_v1 = M2C_FIELD(func_001e98d0((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x328) << 0x1B) >> 0x20) & 1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180)), void **, 4);
    if (temp_v1 != NULL) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = (s32) ((M2C_FIELD(temp_v1, f32 *, 0x3C) * 1.8e+02f) / 3.141592979f);
    }
    return 2;
}

s32 func_001d4358(void *arg0) {
    s32 temp_s1;
    void *temp_v1;

    temp_s1 = arg0 + 4;
    temp_v1 = M2C_FIELD(func_001e98d0((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x328) << 0x1B) >> 0x20) & 1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180)), void **, 4);
    if (temp_v1 != NULL) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = (s32) (M2C_FIELD(temp_v1, f32 *, 0x16C) * 0.5f);
    }
    return 2;
}

s32 func_001d4d68(void *arg0) {
    s32 temp_s1;
    s32 temp_v1;

    temp_s1 = arg0 + 4;
    temp_v1 = M2C_FIELD(func_001e98d0((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x328) << 0x1B) >> 0x20) & 1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180)), s32 *, 4);
    if (temp_v1 != 0) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = func_00135838(temp_v1);
    }
    return 2;
}

s32 func_001d5388(void *arg0) {
    s32 temp_s1;
    void *temp_a0;
    void *temp_v0;

    temp_s1 = arg0 + 4;
    temp_v0 = func_001e98d0((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x328) << 0x1B) >> 0x20) & 1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    if (temp_v0 != NULL) {
        temp_a0 = M2C_FIELD(temp_v0, void **, 4);
        if (temp_a0 != NULL) {
            M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = (s32) M2C_FIELD(temp_a0, s32 *, 0x164);
        }
    }
    return 2;
}

s32 func_001d6080(void) {
    s32 var_s0;

    for (var_s0 = 1; var_s0 < 0x20; var_s0 += 1) {
        func_0014ec10(var_s0);
    }
    return 2;
}

s32 func_001d60c0(void) {
    s32 var_s0;

    for (var_s0 = 1; var_s0 < 0x20; var_s0 += 1) {
        func_0014ec38(var_s0);
    }
    return 2;
}

s32 func_001dc280(s32 arg0) {
    void *temp_a1;

    temp_a1 = (M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0;
    if (!(D_003773E8(M2C_FIELD(temp_a1, s32 *, 0x184), temp_a1) != 0)) {
        return 4;
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
    return 4;
}
