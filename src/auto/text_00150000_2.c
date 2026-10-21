/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0055.h"

M2C_UNK func_0012cc38(M2C_UNK, M2C_UNK);
M2C_UNK func_0012ccb0(M2C_UNK);
M2C_UNK func_00157818(s32, s32);
M2C_UNK func_00176310(s32);
M2C_UNK func_00258d10(M2C_UNK);
extern M2C_UNK func_0015efc0;
extern f32 D_00551D74;
extern s32 D_002C5958;
extern s32 D_002E26A0;
extern s32 D_00351BC0;
extern s32 D_00351BC4;
s32 AddDmacHandler(M2C_UNK, M2C_UNK *, M2C_UNK);
s32 func_0013c6a8(s16);
s32 func_00157560();

s32 func_00150cb0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}

s32 func_00151860(void *arg0, void *arg1, s32 arg2) {
    f32 temp_f1;
    s32 temp_a0;

    if (arg2 != -2) {
        if ((arg2 == -1) && (M2C_FIELD(arg1, s32 *, 0x70) == 0) && (func_0013c6a8(M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), s16 *, 0x48)) == 0)) {
            temp_f1 = M2C_FIELD(arg0, f32 *, 0x14) - M2C_FIELD(arg1, f32 *, 0x14);
            if ((temp_f1 > -50.0f) && (temp_f1 < 20.0f)) {
                func_0012cc38(3, 0x37);
                if (D_002C5958 & 1) {
                    func_0012ccb0(3);
                }
            }
        }
    } else {
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x144);
        if (temp_a0 != 0) {
            func_00176310(temp_a0);
        }
    }
    return 0;
}

void func_001524a8(void) {

}

s32 func_00153c38(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 2;
    if (arg1 == 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

void func_00155ee8(void *arg0) {
    M2C_FIELD(arg0, u8 *, 3) = (u8) (M2C_FIELD(arg0, u8 *, 3) + 1);
}

void func_00157910(s32 arg0, s32 arg1, s32 arg2) {
    if (func_00157560() < arg2) {
        func_00157818(arg0, arg1);
    }
}

void func_001580e8(s32 *arg0) {
    *arg0 &= ~0x20;
}

s32 func_001598c8(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 0x1E;
    if (arg1 != 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

void func_0015ca90(s32 *arg0) {
    *arg0 |= 0x200000;
}

void func_0015d5c0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) | 2);
}

void func_0015d5d0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) & ~2);
}

void func_0015e7f8(s32 arg0) {
    if (D_002E26A0 == arg0) {
        D_00551D74 = 30.0f;
    }
}

void func_0015eda8(void) {
    func_00258d10(1);
    func_00258d10(2);
    D_00351BC0 = AddDmacHandler(1, &func_0015efc0, 0);
    D_00351BC4 = AddDmacHandler(2, &func_0015efc0, 0);
}
#include "data/pieces/D_00351BC0.h"
#include "data/pieces/D_00351BC4.h"
