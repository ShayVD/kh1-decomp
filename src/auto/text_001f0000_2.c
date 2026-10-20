/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_001f3698(void *, s32);
M2C_UNK func_001f5fe0();
M2C_UNK func_001f8170(void *);
extern M2C_UNK D_00490AE0;
extern M2C_UNK D_0063F758;
extern f32 D_002BBDFC;
extern s32 D_003E8E28;
extern s32 D_003F1A60;
extern s32 D_003F1A64;
extern s32 D_003F1A68;
extern s32 D_00640DD8;
extern s32 D_00640DDC;
extern s32 D_00640DE0;

u8 func_001f05e8(s32 arg0) {
    return M2C_FIELD(((arg0 * 8) + D_003E8E28), u8 *, 6);
}

s32 func_001f38d0(void *arg0, s32 arg1) {
    s32 temp_v1;
    s32 var_v0;
    void *temp_v0;
    void *var_s0;
    void *var_v1;

    var_v0 = -1;
    var_s0 = arg0;
    if (var_s0 != NULL) {
        var_v1 = M2C_FIELD(var_s0, void **, 0xC);
        if (var_v1 != NULL) {
            do {
                var_s0 = var_v1;
                temp_v0 = M2C_FIELD(var_s0, void **, 0xC);
                var_v1 = temp_v0;
            } while (temp_v0 != NULL);
        }
        do {
            temp_v1 = M2C_FIELD(var_s0, s32 *, 0x8C);
            if (temp_v1 != 0) {
                if (temp_v1 >= 0) {
                    if (temp_v1 < 6) {
                        if (temp_v1 < 4) {
                            goto block_8;
                        }
                    } else {
                        goto block_9;
                    }
                } else {
block_8:
block_9:
                    func_001f3698(var_s0, arg1);
                }
            }
            var_s0 = M2C_FIELD(var_s0, void **, 0x10);
        } while (var_s0 != NULL);
        var_v0 = 0;
    }
    return var_v0;
}

void func_001f3d58(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x84) = arg1;
}

void func_001f3d60(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x84) = (s32) M2C_FIELD(arg0, s32 *, 0x80);
}

void func_001f3e20(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
}

void func_001f3e28(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x10) = 0;
        M2C_FIELD(arg0, void **, 0xC) = NULL;
    }
}

void func_001f3e90(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x10) = arg1;
}

void func_001f3e98(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0xC) = 0;
        M2C_FIELD(arg0, void **, 0x10) = NULL;
    }
}

void func_001f3eb8(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_v1 != NULL) {
        M2C_FIELD(temp_v1, void **, 0x10) = (void *) M2C_FIELD(arg0, void **, 0x10);
    }
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_v1_2 != NULL) {
        M2C_FIELD(temp_v1_2, void **, 0xC) = (void *) M2C_FIELD(arg0, void **, 0xC);
    }
    temp_v0 = M2C_FIELD(arg1, void **, 0xC);
    M2C_FIELD(arg1, void **, 0xC) = arg0;
    M2C_FIELD(arg0, void **, 0x10) = arg1;
    M2C_FIELD(arg0, void **, 0xC) = temp_v0;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0x10) = arg0;
    }
}

void func_001f3f00(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v0_2;
    void *var_a1;
    void *var_v1;

    var_a1 = arg1;
    var_v1 = M2C_FIELD(var_a1, void **, 0x10);
    if (var_v1 != NULL) {
        do {
            var_a1 = var_v1;
            temp_v0 = M2C_FIELD(var_a1, void **, 0x10);
            var_v1 = temp_v0;
        } while (temp_v0 != NULL);
    }
    temp_v0_2 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_v0_2 != NULL) {
        M2C_FIELD(temp_v0_2, s32 *, 0x10) = 0;
    }
    M2C_FIELD(var_a1, void **, 0x10) = arg0;
    M2C_FIELD(arg0, void **, 0xC) = var_a1;
}

void func_001f3fa8(void *arg0) {
    void *temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0xC);
    temp_v0 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_v1 != NULL) {
        M2C_FIELD(temp_v1, void **, 0x10) = temp_v0;
    }
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0xC) = temp_v1;
    }
}

M2C_UNK *func_001f4010(void *arg0) {
    M2C_UNK *var_v0;

    var_v0 = M2C_FIELD(arg0, M2C_UNK **, 0x64);
    if (var_v0 == NULL) {
        var_v0 = &D_00490AE0;
    }
    return var_v0;
}

void func_001f4030(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x64) = arg1;
}

s32 func_001f4038(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}

void func_001f4040(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x70) = arg1;
}

void func_001f4048(s32 arg0) {
    D_003F1A68 = arg0;
}

void func_001f4090(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x68) = arg1;
}

void func_001f4098(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x68) = 0;
}

void func_001f40a0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x6C) = arg1;
}

void func_001f40a8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x6C) = 0x60000000;
}

M2C_UNK *func_001f40b8(void) {
    return &D_0063F758;
}

s32 func_001f4250(void) {
    return D_00640DD8;
}

s32 func_001f42a8(void) {
    return D_00640DDC;
}

void *func_001f4430(void *arg0) {
    void *temp_v0;
    void *var_a0;
    void *var_v1;

    var_a0 = arg0;
    var_v1 = M2C_FIELD(var_a0, void **, 0xC);
    if (var_v1 != NULL) {
        do {
            var_a0 = var_v1;
            temp_v0 = M2C_FIELD(var_a0, void **, 0xC);
            var_v1 = temp_v0;
        } while (temp_v0 != NULL);
    }
    return var_a0;
}

s32 func_001f4558(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x7C);
}

void func_001f4560(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x7C) = arg1;
}

void func_001f4568(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
}

void func_001f81e8(void *arg0) {
    f32 temp_f0;

    temp_f0 = M2C_FIELD(arg0, f32 *, 0x9C) - D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x9C) = temp_f0;
    if (temp_f0 <= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0x9C) = 0.0f;
    }
    func_001f5fe0();
    if ((M2C_FIELD(arg0, f32 *, 0x9C) <= 0.0f) || (M2C_FIELD(arg0, s32 *, 0x8C) >= 6)) {
        func_001f8170(arg0);
    }
}

s32 func_001f9000(void) {
    return D_003F1A60;
}

void func_001f9010(s32 arg0) {
    D_003F1A64 = arg0 * 0x10;
}

s32 func_001f9020(void) {
    return (s32) D_003F1A64 >> 4;
}

void func_001fd258(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) ((arg1 * 0x10) + 0x7000);
}

s32 func_001fd268(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s32 *, 0xB4) - 0x7000) >> 4;
}

void func_001fd278(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) ((arg1 * 0x10) + 0x7000);
}

s32 func_001fd288(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x14;
}

void func_001fd298(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xB8) = (s16) (arg1 * 0x10);
}

s32 func_001fd2a8(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xBA) << 0x10) >> 0x14;
}

void func_001fd2b8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xBA) = (s16) (arg1 * 0x10);
}

s32 func_001fd2c8(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xBE) << 0x10) >> 0x14;
}

void func_001fd2d8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xBE) = (s16) (arg1 * 0x10);
}

s32 func_001fd2e8(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC0) << 0x10) >> 0x14;
}

void func_001fd2f8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC0) = (s16) (arg1 * 0x10);
}

s32 func_001fd308(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC2) << 0x10) >> 0x14;
}

void func_001fd318(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC2) = (s16) (arg1 * 0x10);
}

s32 func_001fd328(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC4) << 0x10) >> 0x14;
}

void func_001fd338(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC4) = (s16) (arg1 * 0x10);
}

s32 func_001fd348(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC6) << 0x10) >> 0x14;
}

void func_001fd358(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC6) = (s16) (arg1 * 0x10);
}

s32 func_001fd368(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC8) << 0x10) >> 0x14;
}

void func_001fd378(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC8) = (s16) (arg1 * 0x10);
}

s16 func_001fd5d0(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xCA);
}

s16 func_001fd5d8(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xCC);
}

s16 func_001fd608(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xCE);
}

s32 func_001fd618(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xD0) << 0x10) >> 0x14;
}

void func_001fd628(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xD0) = (s16) (arg1 * 0x10);
}

s32 func_001fd848(void) {
    return D_00640DE0;
}
#include "data/bss_0064_mixed.h"
