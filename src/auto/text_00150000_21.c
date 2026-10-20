/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern f32 D_002BBDFC;
extern s8 D_00551670; /* src/data/bss_0055.c: E551670 D_00551670[0x4] */
f32 atan2f(f32, f32);
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
void func_00105a30(M2C_UNK, u16, s32);
void func_001373f8(s32, f32);
void func_0014f658(void *, M2C_UNK);
void func_001575b0(s32);
void func_00267518(void *, void *, void *);
void func_00267560(void *, s32, f32);

s32 func_00157090(void) {
    s32 var_a1;
    s32 var_v0;
    s8 *var_a0;
    s8 temp_v1;

    var_a1 = 0;
    var_a0 = &D_00551670;
loop_1:
    temp_v1 = *var_a0;
    var_a0 += 0x14;
    var_v0 = 1;
    if (temp_v1 != 0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 4) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

void func_00157668(void) {
    s32 var_s0;

    for (var_s0 = 0; var_s0 < 4; var_s0 += 1) {
        func_001575b0(var_s0);
    }
}

void func_0015abd0(s32 arg0) {
    func_001373f8(arg0, 12.0f);
    *(M2C_UNK *)arg0 = (s32) (*(M2C_UNK *)arg0 | 0x100000);
    func_00130340(arg0, 0x010000DC, 0.0f);
    func_00130578(arg0, 0x40000000, 8.0f);
}

void func_0015d5e8(void *arg0) {
    s32 sp[4];
    void *temp_a0;
    void *temp_v0;

    func_00105a30(-1, M2C_FIELD(arg0, u16 *, 0x30E), M2C_FIELD(arg0, void **, 0x148) + 0xC0);
    if (M2C_FIELD(arg0, s32 *, 0x70) != 0x13) {
        func_00267560(sp, M2C_FIELD(arg0, void **, 0x148) + 0xC0, (25.0f - M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x134), void **, 0x10), f32 *, 0xC)) - 1.5f);
        temp_a0 = arg0 + 0x10;
        func_00267518(temp_a0, temp_a0, sp);
    }
    func_00267560(arg0 + 0x20, M2C_FIELD(arg0, void **, 0x148) + 0xC0, -1.5f / D_002BBDFC);
    temp_v0 = M2C_FIELD(arg0, void **, 0x148);
    M2C_FIELD(arg0, f32 *, 0x150) = atan2f(M2C_FIELD(temp_v0, f32 *, 0xC0), M2C_FIELD(temp_v0, f32 *, 0xC8));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), s32 *, 0xE4) = (s32) M2C_FIELD(arg0, u16 *, 0x30E);
    func_0014f658(arg0, 0x12);
}
