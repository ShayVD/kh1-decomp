/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00492380;
extern s32 D_0046C208;
void ExecOSD(s32, s32);
void func_0025f7d0(M2C_UNK *, s32, s32);
void func_0025f8e8();

void func_0025f9d0(s32 arg0, s32 arg1) {
    func_0025f7d0(&D_00492380, arg0, arg1);
    func_0025f8e8();
    ExecOSD(arg0, D_0046C208 + 4);
}
