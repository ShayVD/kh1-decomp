/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */
extern s32 D_0061621C;
extern void *D_00615E60;
f32 func_0018ac28(s32, s32);
f32 func_0018aeb8(s32, s32);
void func_0018ad70(s32, s32);

void pppPointFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00)) && (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC))) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_v0_2 = temp_v0 + 0xA0;
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
        M2C_FIELD(temp_v0_2, f32 *, 4) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
        M2C_FIELD(temp_v0_2, f32 *, 8) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
    }
}

void pppMoveFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v1, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_a3_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_a3_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(temp_v1, f32 *, 0xA0));
        M2C_FIELD(temp_a5, f32 *, 4) = (f32) (M2C_FIELD(temp_a5, f32 *, 4) + M2C_FIELD(temp_a3_2, f32 *, 4));
        M2C_FIELD(temp_a5, f32 *, 8) = (f32) (M2C_FIELD(temp_a5, f32 *, 8) + M2C_FIELD(temp_a3_2, f32 *, 8));
    }
}

void pppAcceleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v1, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_a3_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_a3_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(temp_v1, f32 *, 0xA0));
        M2C_FIELD(temp_a5, f32 *, 4) = (f32) (M2C_FIELD(temp_a5, f32 *, 4) + M2C_FIELD(temp_a3_2, f32 *, 4));
        M2C_FIELD(temp_a5, f32 *, 8) = (f32) (M2C_FIELD(temp_a5, f32 *, 8) + M2C_FIELD(temp_a3_2, f32 *, 8));
    }
}

void pppAngleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00)) && (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC))) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_v0_2 = temp_v0 + 0xA0;
        M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xA0) + M2C_FIELD(arg1, s32 *, 4));
        M2C_FIELD(temp_v0_2, s32 *, 4) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 4) + M2C_FIELD(arg1, s32 *, 8));
        M2C_FIELD(temp_v0_2, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0xC));
    }
}

void pppAngMoveFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xA0) + M2C_FIELD(arg1, s32 *, 4));
            M2C_FIELD(temp_a3_2, s32 *, 4) = (s32) (M2C_FIELD(temp_a3_2, s32 *, 4) + M2C_FIELD(arg1, s32 *, 8));
            M2C_FIELD(temp_a3_2, s32 *, 8) = (s32) (M2C_FIELD(temp_a3_2, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0xC));
        }
        M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xA0) + M2C_FIELD(temp_v1, s32 *, 0xA0));
        M2C_FIELD(temp_a5, s32 *, 4) = (s32) (M2C_FIELD(temp_a5, s32 *, 4) + M2C_FIELD(temp_a3_2, s32 *, 4));
        M2C_FIELD(temp_a5, s32 *, 8) = (s32) (M2C_FIELD(temp_a5, s32 *, 8) + M2C_FIELD(temp_a3_2, s32 *, 8));
    }
}

void pppAngAcceleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xA0) + M2C_FIELD(arg1, s32 *, 4));
            M2C_FIELD(temp_a3_2, s32 *, 4) = (s32) (M2C_FIELD(temp_a3_2, s32 *, 4) + M2C_FIELD(arg1, s32 *, 8));
            M2C_FIELD(temp_a3_2, s32 *, 8) = (s32) (M2C_FIELD(temp_a3_2, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0xC));
        }
        M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xA0) + M2C_FIELD(temp_v1, s32 *, 0xA0));
        M2C_FIELD(temp_a5, s32 *, 4) = (s32) (M2C_FIELD(temp_a5, s32 *, 4) + M2C_FIELD(temp_a3_2, s32 *, 4));
        M2C_FIELD(temp_a5, s32 *, 8) = (s32) (M2C_FIELD(temp_a5, s32 *, 8) + M2C_FIELD(temp_a3_2, s32 *, 8));
    }
}

void pppScaleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00)) && (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC))) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_v0_2 = temp_v0 + 0xA0;
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
        M2C_FIELD(temp_v0_2, f32 *, 4) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
        M2C_FIELD(temp_v0_2, f32 *, 8) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
    }
}

void pppSclMoveFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v1, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_a3_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_a3_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(temp_v1, f32 *, 0xA0));
        M2C_FIELD(temp_a5, f32 *, 4) = (f32) (M2C_FIELD(temp_a5, f32 *, 4) + M2C_FIELD(temp_a3_2, f32 *, 4));
        M2C_FIELD(temp_a5, f32 *, 8) = (f32) (M2C_FIELD(temp_a5, f32 *, 8) + M2C_FIELD(temp_a3_2, f32 *, 8));
    }
}

void pppSclAcceleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a5;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a5 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v1, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_a3_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_a3_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a3_2, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(temp_v1, f32 *, 0xA0));
        M2C_FIELD(temp_a5, f32 *, 4) = (f32) (M2C_FIELD(temp_a5, f32 *, 4) + M2C_FIELD(temp_a3_2, f32 *, 4));
        M2C_FIELD(temp_a5, f32 *, 8) = (f32) (M2C_FIELD(temp_a5, f32 *, 8) + M2C_FIELD(temp_a3_2, f32 *, 8));
    }
}

void pppColMoveFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a4;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a4 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, u16 *, 0xA0) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xA0) + M2C_FIELD(arg1, u16 *, 4));
            M2C_FIELD(temp_a3_2, u16 *, 2) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 2) + M2C_FIELD(arg1, u16 *, 6));
            M2C_FIELD(temp_a3_2, u16 *, 4) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 4) + M2C_FIELD(arg1, u16 *, 8));
            M2C_FIELD(temp_a3_2, u16 *, 6) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 6) + M2C_FIELD(arg1, u16 *, 0xA));
        }
        M2C_FIELD(temp_v0, u16 *, 0xA0) = (u16) (M2C_FIELD(temp_v0, u16 *, 0xA0) + M2C_FIELD(temp_v1, u16 *, 0xA0));
        M2C_FIELD(temp_a4, u16 *, 2) = (u16) (M2C_FIELD(temp_a4, u16 *, 2) + M2C_FIELD(temp_a3_2, u16 *, 2));
        M2C_FIELD(temp_a4, u16 *, 4) = (u16) (M2C_FIELD(temp_a4, u16 *, 4) + M2C_FIELD(temp_a3_2, u16 *, 4));
        M2C_FIELD(temp_a4, u16 *, 6) = (u16) (M2C_FIELD(temp_a4, u16 *, 6) + M2C_FIELD(temp_a3_2, u16 *, 6));
    }
}

void pppColAcceleFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a4;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg2, void **, 0xC);
    temp_v0 = arg0 + M2C_FIELD(temp_a3, s32 *, 0);
    temp_v1 = arg0 + M2C_FIELD(temp_a3, s32 *, 4);
    temp_a3_2 = temp_v1 + 0xA0;
    temp_a4 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v1, u16 *, 0xA0) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xA0) + M2C_FIELD(arg1, u16 *, 4));
            M2C_FIELD(temp_a3_2, u16 *, 2) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 2) + M2C_FIELD(arg1, u16 *, 6));
            M2C_FIELD(temp_a3_2, u16 *, 4) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 4) + M2C_FIELD(arg1, u16 *, 8));
            M2C_FIELD(temp_a3_2, u16 *, 6) = (u16) (M2C_FIELD(temp_a3_2, u16 *, 6) + M2C_FIELD(arg1, u16 *, 0xA));
        }
        M2C_FIELD(temp_v0, u16 *, 0xA0) = (u16) (M2C_FIELD(temp_v0, u16 *, 0xA0) + M2C_FIELD(temp_v1, u16 *, 0xA0));
        M2C_FIELD(temp_a4, u16 *, 2) = (u16) (M2C_FIELD(temp_a4, u16 *, 2) + M2C_FIELD(temp_a3_2, u16 *, 2));
        M2C_FIELD(temp_a4, u16 *, 4) = (u16) (M2C_FIELD(temp_a4, u16 *, 4) + M2C_FIELD(temp_a3_2, u16 *, 4));
        M2C_FIELD(temp_a4, u16 *, 6) = (u16) (M2C_FIELD(temp_a4, u16 *, 6) + M2C_FIELD(temp_a3_2, u16 *, 6));
    }
}

void pppPObjPointFrame(void *arg0, void *arg1, void *arg2) {
    M2C_UNK *temp_v0_3;
    M2C_UNK *var_v0;
    s32 temp_v0_2;
    void *temp_a2;
    void *temp_v0;

    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_a2 = temp_v0 + 0xA0;
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            temp_v0_2 = M2C_FIELD(arg1, s32 *, 4);
            if (temp_v0_2 != -1) {
                var_v0 = M2C_FIELD(((temp_v0_2 * 0x10) + M2C_FIELD(D_00615E60, s32 *, 0x80)), s32 *, 4) + M2C_FIELD(arg1, s32 *, 8) + 0xA0;
            } else {
                var_v0 = &D_00575A00;
            }
            M2C_FIELD(temp_a2, M2C_UNK **, 0xC) = var_v0;
        }
        temp_v0_3 = M2C_FIELD(temp_a2, M2C_UNK **, 0xC);
        M2C_FIELD(temp_a2, f32 *, 0x0) = (f32) M2C_FIELD(temp_v0_3, f32 *, 0);
        M2C_FIELD(temp_a2, f32 *, 4) = (f32) M2C_FIELD(temp_v0_3, f32 *, 4);
        M2C_FIELD(temp_a2, f32 *, 8) = (f32) M2C_FIELD(temp_v0_3, f32 *, 8);
    }
}

void pppPointLoopFrame(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_s0;
    void *temp_v0;

    temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
    temp_s0 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(temp_s0, s32 *, 0xC) == 0) {
            func_0018ac28(arg1, (s32) temp_s0);
        }
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_s0, f32 *, 4) = (f32) (M2C_FIELD(temp_s0, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_s0, f32 *, 8) = (f32) (M2C_FIELD(temp_s0, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
    }
}

void pppAngleLoopFrame(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_s0;
    void *temp_v0;

    temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
    temp_s0 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(temp_s0, s32 *, 0xC) == 0) {
            func_0018ad70(arg1, (s32) temp_s0);
        }
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xA0) + M2C_FIELD(arg1, s32 *, 4));
            M2C_FIELD(temp_s0, s32 *, 4) = (s32) (M2C_FIELD(temp_s0, s32 *, 4) + M2C_FIELD(arg1, s32 *, 8));
            M2C_FIELD(temp_s0, s32 *, 8) = (s32) (M2C_FIELD(temp_s0, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0xC));
        }
    }
}

void pppScaleLoopFrame(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_s0;
    void *temp_v0;

    temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
    temp_s0 = temp_v0 + 0xA0;
    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        if (M2C_FIELD(temp_s0, s32 *, 0xC) == 0) {
            func_0018aeb8(arg1, (s32) temp_s0);
        }
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xA0) + M2C_FIELD(arg1, f32 *, 4));
            M2C_FIELD(temp_s0, f32 *, 4) = (f32) (M2C_FIELD(temp_s0, f32 *, 4) + M2C_FIELD(arg1, f32 *, 8));
            M2C_FIELD(temp_s0, f32 *, 8) = (f32) (M2C_FIELD(temp_s0, f32 *, 8) + M2C_FIELD(arg1, f32 *, 0xC));
        }
    }
}
#include "data/bss_0061_mixed.h"
