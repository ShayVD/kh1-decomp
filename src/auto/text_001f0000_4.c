/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_001f3698(M2C_UNK *, s32);
extern M2C_UNK D_0063F758; /* src/data/bss_0063.c: Obj D_0063F758[24] */
extern f32 D_002BBDFC;
s32 func_001f31a8(s32, s32);
s32 func_001f86e0(s32, s32, s32, s32, s32);
void func_001f5fe0(s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
void func_001fefc8(s32, s32, s32, s32, s32);

s32 func_001f3520(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_001f31a8(arg0, arg1);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s16 *, 0xC6) = (s16) (M2C_FIELD(arg0, u16 *, 0x22) * 0x10);
        M2C_FIELD(temp_v0, u16 *, 0xD8) = (u16) M2C_FIELD(arg0, u16 *, 0x24);
        M2C_FIELD(temp_v0, u16 *, 0xCA) = (u16) M2C_FIELD(arg0, u16 *, 0x28);
    }
    return temp_v0;
}

void func_001f3c90(s32 arg0) {
    s8 *var_s0;
    s32 temp_v1;
    s32 var_s1;

    var_s0 = &D_0063F758;
    var_s1 = 0x18;
    do {
        temp_v1 = M2C_FIELD(var_s0, s32 *, 0x8C);
        if (temp_v1 != 0) {
            if (temp_v1 >= 0) {
                if (temp_v1 < 6) {
                    if (temp_v1 < 4) {
                        goto block_5;
                    }
                } else {
                    goto block_6;
                }
            } else {
block_5:
block_6:
                func_001f3698(var_s0, arg0);
            }
        }
        var_s1 -= 1;
        var_s0 += 0xF0;
    } while (var_s1 > 0);
}

void func_001f3fc8(void *arg0, void *arg1) {
    void *temp_a2;
    void *temp_a3;
    void *temp_v0;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg0, void **, 0xC);
    temp_a2 = M2C_FIELD(arg0, void **, 0x10);
    temp_v1 = M2C_FIELD(arg1, void **, 0xC);
    temp_v0 = M2C_FIELD(arg1, void **, 0x10);
    if (temp_a3 != NULL) {
        M2C_FIELD(temp_a3, void **, 0x10) = arg1;
    }
    if (temp_a2 != NULL) {
        M2C_FIELD(temp_a2, void **, 0xC) = arg1;
    }
    if (temp_v1 != NULL) {
        M2C_FIELD(temp_v1, void **, 0x10) = arg0;
    }
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0xC) = arg0;
    }
    M2C_FIELD(arg0, void **, 0xC) = temp_v1;
    M2C_FIELD(arg0, void **, 0x10) = temp_v0;
    M2C_FIELD(arg1, void **, 0xC) = temp_a3;
    M2C_FIELD(arg1, void **, 0x10) = temp_a2;
}

void func_001f8120(s32 arg0) {
    M2C_FIELD(arg0, f32 *, 0x9C) = (f32) (M2C_FIELD(arg0, f32 *, 0x9C) + D_002BBDFC);
    func_001f5fe0(arg0);
}

void func_001f8ee0(s32 arg0) {
    func_001f86e0(arg0, 0, (s32) (M2C_FIELD(arg0, u16 *, 0xC0) << 0x10) >> 0x14, 0x200, (((s32) (M2C_FIELD(arg0, u16 *, 0xC4) << 0x10) >> 0x14) * M2C_FIELD(arg0, s16 *, 0xCE)) - ((s32) (M2C_FIELD(arg0, u16 *, 0xC8) << 0x10) >> 0x14));
}

void func_001f9270(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u32 temp_v0;

    temp_v0 = 0x14 - arg4;
    func_001f9438(arg0, arg1, arg2, ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) + 2, arg3, arg4, arg5);
}

void func_001fd5e0(s32 arg0, s32 arg1) {
    s16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0xD8);
    M2C_FIELD(arg0, s16 *, 0xCC) = (s16) ((s32) ((arg1 + temp_v1) - 1) / temp_v1);
    M2C_FIELD(arg0, s16 *, 0xCA) = (s16) arg1;
}

void func_001fef40(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0xCC) != 0) {
        temp_v0 = (s32) (M2C_FIELD(arg0, u16 *, 0xC2) << 0x10) >> 0x14;
        temp_v1 = (s32) (M2C_FIELD(arg0, u16 *, 0xC4) << 0x10) >> 0x14;
        func_001fefc8(arg0, (s32) (M2C_FIELD(arg0, s16 *, 0xBE) + (M2C_FIELD(arg0, s16 *, 0xDA) * temp_v0)) >> 4, (s32) (M2C_FIELD(arg0, s16 *, 0xC0) + (M2C_FIELD(arg0, s16 *, 0xD2) * temp_v1)) >> 4, temp_v0 - ((s32) (M2C_FIELD(arg0, u16 *, 0xC6) << 0x10) >> 0x14), temp_v1 - ((s32) (M2C_FIELD(arg0, u16 *, 0xC8) << 0x10) >> 0x14));
    }
}
#include "data/pieces/D_002BBDFC.h"
