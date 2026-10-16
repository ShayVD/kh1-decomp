/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001a50d0(M2C_UNK *, s32);
M2C_UNK func_001a5150(M2C_UNK *, s32);
M2C_UNK func_001a51d0(M2C_UNK *, s32);
M2C_UNK func_00267328(M2C_UNK *, M2C_UNK *, M2C_UNK *);

void func_00183be0(M2C_UNK *arg0, void *arg1) {
    s32 sp[64];
    func_001a51d0(sp, M2C_FIELD(arg1, s32 *, 8));
    func_001a5150(&M2C_FIELD(sp, M2C_UNK *, 0x40), M2C_FIELD(arg1, s32 *, 4));
    func_00267328(&M2C_FIELD(sp, M2C_UNK *, 0x80), sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_001a50d0(&M2C_FIELD(sp, M2C_UNK *, 0xC0), M2C_FIELD(arg1, s32 *, 0));
    func_00267328(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x80), &M2C_FIELD(sp, M2C_UNK *, 0xC0));
}
