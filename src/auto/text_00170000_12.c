/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00120bf8(M2C_UNK *);
M2C_UNK func_00177900();
M2C_UNK func_002672f8(void *, s32, void *);
M2C_UNK func_00267530(M2C_UNK *, s32, void *);
M2C_UNK func_002675a8(void *, M2C_UNK *);
extern M2C_UNK D_00362670;
#include "data/pieces/D_002E26A0.h"
s32 func_00177488(M2C_UNK *, void *, void *);

void func_001779e8(void *arg0, s32 arg1) {
    s32 sp[8];
    func_00177900();
    func_002675a8(sp, &D_00362670);
    M2C_FIELD(sp, f32 *, 0x0) = M2C_FIELD(sp, f32 *, 0x8) = 0.0f;
    func_002672f8(sp, (*(s32 *)&D_002E26A0) + 0xD0, sp);
    if (func_00177488(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, arg0) != 0) {
        func_002675a8(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    }
    func_00267530(&M2C_FIELD(sp, M2C_UNK *, 0x10), arg1, arg0);
    func_00120bf8(&M2C_FIELD(sp, M2C_UNK *, 0x10));
}
