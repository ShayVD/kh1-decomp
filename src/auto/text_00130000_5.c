/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK func_0013f358;
extern M2C_UNK func_0013f450;
extern M2C_UNK func_0013f8a8;
extern M2C_UNK func_0013f910;
extern M2C_UNK func_0013fba0;
extern M2C_UNK func_0013fc08;
extern M2C_UNK func_0013fc28;
extern M2C_UNK func_0013fc68;
extern M2C_UNK func_0014f748;
extern M2C_UNK func_0014f778;
f32 func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
s32 func_00130040(s32, s32);
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
void func_00138c30(s32, s32);

void func_00138ca0(s32 arg0, s32 arg1, f32 fparg0) {
    s32 var_v1;

    if (func_00130040(arg0, 0x48) == 0) {
        func_00138c30(arg0, arg1);
        return;
    }
    if (M2C_FIELD(arg1, s32 *, 0x20) == 0) {
        var_v1 = 0x4A;
        if (fparg0 < 0.0f) {
            var_v1 = 0x48;
        }
    } else {
        var_v1 = 0x49;
        if (!(fparg0 < 0.0f)) {
            var_v1 = 0x4B;
        }
    }
    if (M2C_FIELD(arg0, s32 *, 0x164) == var_v1) {
        var_v1 = ((var_v1 - 0x48) ^ 1) + 0x48;
    }
    func_00130340(arg0, var_v1 | 0x01000000, 0.0f);
    func_00130578(arg0, 0x40000000, 8.0f);
    func_00138c30(arg0, arg1);
}

void func_0013fc80(void) {
    func_0014f830(0xD, 1, &func_0013f358, &func_0013f450, &func_0013f910, &func_0014f748, &func_0013fba0, &func_0013f8a8, &func_0013fc08);
    func_0014f830(0xE, 1, NULL, NULL, &func_0013fc28, &func_0014f778, &func_0013fc68, NULL, NULL);
}
