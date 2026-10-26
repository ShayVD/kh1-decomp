/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001c0310(M2C_UNK, M2C_UNK *, s32);
M2C_UNK func_00f28f58();
extern M2C_UNK func_00f26408;
extern f32 D_00F61564;
extern f32 D_00F6156C;
extern s32 D_00F61380;
extern s32 D_00F61384;

void func_00f26430(s32 arg0) {
    func_001c0310(-1, &func_00f26408, arg0);
}

void func_00f29450(s32 arg0) {
    D_00F61384 = arg0;
    func_00f28f58();
}

void func_00f29470(s32 arg0) {
    D_00F61380 = arg0;
}

void func_00f2e238(s32 arg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0 * 0.0078125f;
    D_00F61564 = temp_f0;
    D_00F6156C = temp_f0;
}
