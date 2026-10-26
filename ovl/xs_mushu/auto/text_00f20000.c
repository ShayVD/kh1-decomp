/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_001247e8(s32);
M2C_UNK func_00135978(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00137318(s32);
M2C_UNK func_00f20ff8(s32);
M2C_UNK sceVu0AddVector(s32, s32, M2C_UNK *);
M2C_UNK sceVu0CopyVector(void *);
M2C_UNK sceVu0ScaleVectorXYZ(M2C_UNK *, void *, f32);
extern M2C_UNK *D_00304B6C;
extern M2C_UNK D_00F21400;
extern M2C_UNK func_00f20978;
extern M2C_UNK func_00f20c58;
extern s32 D_00F21388;
extern s32 D_00F21394;
extern s32 D_00F21680;
extern s32 D_00F21690;

void func_00f20098(s32 arg0) {
    if (arg0 == 0x65) {
        func_00137318(D_00F21388);
        func_001247e8(D_00F21388);
    }
    func_00f20ff8(arg0);
}

void func_00f204e8(s32 arg0, f32 fparg0) {
    s32 sp[8];
    sceVu0CopyVector(sp);
    M2C_FIELD(sp, s32 *, 0xC) = 0;
    sceVu0ScaleVectorXYZ(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, fparg0);
    sceVu0AddVector(arg0, arg0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
}

void func_00f20778(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x30);
    M2C_FIELD(arg0, s32 *, 0) = 0;
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
        M2C_FIELD(arg0, void **, 0x30) = NULL;
    }
}

s32 func_00f20a98(void) {
    return D_00F21680 > 0;
}

void func_00f20aa8(void) {
    s8 *var_v0;
    s32 var_v1;

    var_v1 = 9;
    var_v0 = &D_00F21400;
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s32 *, 0) = 0;
        M2C_FIELD(var_v0, s32 *, 0x30) = 0;
        var_v0 += 0x40;
    } while (var_v1 >= 0);
    func_0011ef10(0x21728, &func_00f20978);
}

void func_00f20fb0(void) {
    func_00135978(D_00F21388, 3, 0);
    D_00304B6C = &func_00f20c58;
    D_00F21690 = 0;
    D_00F21394 = 0;
}
