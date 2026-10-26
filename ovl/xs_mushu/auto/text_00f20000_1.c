/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK sceVu0CopyVector(s32, s32);
extern s32 D_00F21394;
extern s32 D_00F21690;
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
void func_00137318(s32);
void func_00f20098(s32);

s32 func_00f20ba0(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {                                 /* irregular */
    case -2:
        func_00137318(arg0);
        break;
    case -3:
        func_00130340(arg0, 0xCA, 0.0f);
        func_00130578(arg0, 0, 0.0f);
        D_00F21394 = 0;
        func_00f20098(0);
        break;
    case 71:
        D_00F21690 = 2;
        break;
    }
    return 0;
}

void func_00f21078(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg2;
    sceVu0CopyVector(arg1, arg3);
}
