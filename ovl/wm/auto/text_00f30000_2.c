/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK sceVu0RotMatrix(s32, s32, s32);
M2C_UNK sceVu0TransMatrix(s32, s32, s32);
M2C_UNK sceVu0UnitMatrix(s32);
extern M2C_UNK D_00FDFFE0;
extern s32 D_00F9A530;
extern s32 D_00F9A534;
extern s32 D_00F9A538;
extern void *D_00FDFFD8;

void func_00f3b490(void) {
    s32 temp_a2;
    s32 temp_v1;

    temp_a2 = D_00F9A534;
    temp_v1 = D_00F9A530 ^ 1;
    D_00F9A534 = 0;
    D_00F9A538 = temp_a2;
    D_00F9A530 = temp_v1;
    D_00FDFFD8 = (s8 *)&D_00FDFFE0 + (temp_v1 * 0x44000);
}

void func_00f3bbf8(s32 arg0) {
    s32 temp_s0;

    temp_s0 = arg0 + 0x40;
    sceVu0UnitMatrix(temp_s0);
    sceVu0RotMatrix(temp_s0, temp_s0, arg0 + 0x90);
    sceVu0TransMatrix(temp_s0, temp_s0, arg0 + 0x80);
}
