/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004D.h"

M2C_UNK func_00108a60(s32, M2C_UNK, void *, void *, void *);
extern M2C_UNK D_002A6C60;
extern M2C_UNK D_002AA060;
extern M2C_UNK D_002AD460;
extern M2C_UNK D_002B1C60;
extern s32 D_002A3F50;
extern s32 D_004D936C;
extern s32 D_004D9370;
f32 func_0011c868(M2C_UNK, s32, s32, M2C_UNK, s32);

void func_001148c8(void) {
    s32 temp_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    void *temp_a2;

    D_004D936C = 0;
    D_004D9370 = 0;
    var_s0 = 0;
    var_s1 = 0;
    var_s2 = 0;
    do {
        func_00108a60(var_s1, 1, var_s2 + (s8 *)&D_002A6C60, var_s0 + (s8 *)&D_002AD460, var_s0 + ((s8 *)&D_002AD460 + 0x2400));
        temp_a0 = var_s1;
        temp_a2 = var_s2 + (s8 *)&D_002AA060;
        func_00108a60(temp_a0, 5, temp_a2, var_s0 + (s8 *)&D_002B1C60, var_s0 + ((s8 *)&D_002B1C60 + 0x2400));
        var_s2 += 0xD0;
        var_s1 += 1;
        var_s0 += 0x90;
    } while (var_s1 < 0x40);
}

void func_0011d688(s32 arg0) {
    s32 *var_s1;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_s0;

    var_s0 = 0;
    var_s1 = &D_002A3F50;
    do {
        temp_a1 = *var_s1;
        var_s1 += 1;
        temp_a2 = var_s0;
        var_s0 += 1;
        func_0011c868(-1, temp_a1, temp_a2, -1, arg0);
    } while (var_s0 < 2);
}

void func_0011fb48(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s64 *, 8) = 0xE;
    M2C_FIELD(arg0, s64 *, 0) = (s64) ((((s32) (arg2 - arg0) >> 4) - 1) | ((s64) arg1 << 0xF) | ((s64) 0x8000 << 0x2D));
}
#include "data/data_002A.h"
