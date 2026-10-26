/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK sceVu0RotMatrix(M2C_UNK *, M2C_UNK *, void *);
M2C_UNK sceVu0TransMatrix(s32, M2C_UNK *, s32 *);
M2C_UNK sceVu0UnitMatrix(M2C_UNK *);

void func_00f7cae0(s32 arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    s32 sp[24];
    M2C_FIELD(sp, f32 *, 0x0) = fparg0;
    M2C_FIELD(sp, f32 *, 0x4) = fparg1;
    M2C_FIELD(sp, f32 *, 0x8) = fparg2;
    M2C_FIELD(sp, f32 *, 0x1C) = 1.0f;
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    M2C_FIELD(sp, f32 *, 0x18) = fparg3;
    M2C_FIELD(sp, s32 *, 0x10) = 0;
    M2C_FIELD(sp, s32 *, 0x14) = 0;
    sceVu0UnitMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x20));
    sceVu0RotMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x20), &M2C_FIELD(sp, M2C_UNK *, 0x20), sp);
    sceVu0TransMatrix(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x20), &M2C_FIELD(sp, s32 *, 0x10));
}
