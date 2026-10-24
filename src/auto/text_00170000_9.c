/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00120c18(M2C_UNK *);
M2C_UNK func_0017b250(M2C_UNK *, void *, f32);
M2C_UNK func_0017b308(void *, void *, s32, s32, s32);
M2C_UNK func_00267530(M2C_UNK *, M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_00575970;
#include "data/pieces/D_00362438.h"

void func_0017c110(s32 arg0, f32 fparg0) {
    s32 sp[20];
    func_0017b308(sp, ((void *)D_00362438) + 0x20, M2C_FIELD(D_00362438, s32 *, 0), arg0, M2C_FIELD(D_00362438, s32 *, 0x18) & 1);
    func_0017b250(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, fparg0);
    func_00267530(&M2C_FIELD(sp, M2C_UNK *, 0x40), &D_00575970, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_00120c18(&M2C_FIELD(sp, M2C_UNK *, 0x40));
}
#include "data/data_0035.h"
#include "data/data_0036.h"
