/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
extern M2C_UNK D_0035BD50;
extern M2C_UNK D_0035BFC0;
extern M2C_UNK D_0035C090;
extern M2C_UNK D_0035C140;
extern M2C_UNK D_0035C1F0;
extern M2C_UNK D_0035C2C0;
extern M2C_UNK D_0035C360;
extern M2C_UNK D_005758D0;
extern M2C_UNK D_005758E0;
#include "data/pieces/D_003626C0.h"
extern void *D_00575780;
extern void *D_00575784;
f32 func_002675a8(M2C_UNK *, M2C_UNK *);
s32 func_00130340(s32, s32, f32);

void func_00170f50(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_v0;

    temp_v0 = D_00575784;
    D_00575784 = M2C_FIELD(temp_v0, void **, 0x10);
    M2C_FIELD(temp_v0, s32 *, 0) = (s32) *arg1;
    M2C_FIELD(temp_v0, s32 *, 8) = arg2;
    M2C_FIELD(temp_v0, s32 *, 4) = arg3;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg4;
    M2C_FIELD(temp_v0, void **, 0x10) = (void *) D_00575780;
    D_00575780 = temp_v0;
}

s32 func_00171890(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 3) || (var_v0 = 1, (arg2 < 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

s32 func_001718b8(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 0x7C) || (var_v0 = 1, ((arg2 < 0x75) != 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

s32 func_00171920(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 0x31) || (var_v0 = 1, ((arg2 < 0x2D) != 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

s32 func_00171948(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 0xD) || (var_v0 = 1, ((arg2 < 3) != 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

void func_00171e90(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) | 0x10);
}

void func_00171ea8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) & ~0x10);
}

void func_00171ec0(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) | 0x20);
}

void func_00171ed8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) & ~0x20);
}

void func_00172010(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xF;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035BD50;
}

void func_001732b0(s32 arg0) {
    s32 temp_v1;
    s32 temp_v1_2;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x144);
    if (M2C_FIELD(arg0, s32 *, 0x70) == 8) {
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x164);
        if ((temp_v1 == 0xCE) || (temp_v1 == M2C_FIELD(temp_s0, s32 *, 0x4C))) {
            func_00130340(arg0, 0x40000075, 8.0f);
        }
    } else {
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x164);
        if ((temp_v1_2 == 0xCE) || (temp_v1_2 == M2C_FIELD(temp_s0, s32 *, 0x4C))) {
            func_00130340(arg0, M2C_FIELD(temp_s0, s32 *, 0x178), 8.0f);
        }
    }
    M2C_FIELD(temp_s0, s64 *, 0x38) = (s64) ((M2C_FIELD(temp_s0, s64 *, 0x38) & ~0x800) | 0x20000);
}

void func_00173740(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xC;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035BFC0;
}

void func_00173ad8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xA;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C090;
}

void func_00173ea8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xA;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C140;
}

void func_00174398(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xC;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C1F0;
}

void func_00174950(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 9;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C2C0;
}

void func_00174d98(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xB;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C360;
}
#include "data/data_002B.h"
#include "data/data_002E.h"
#include "data/data_0035.h"
#include "data/data_0036.h"
#include "data/data_0027.h"
