/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00136d38(void *);
M2C_UNK func_002675a8(void *, s32);
void *func_00123488();

void func_00123ab8(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_00123488();
    M2C_FIELD(temp_v0, s64 *, 0x370) = (s64) (M2C_FIELD(temp_v0, s64 *, 0x370) | ((s64) 0x8000 << 0x1D));
    func_002675a8(temp_v0 + 0x30, arg1);
    func_00136d38(temp_v0);
}
#include "data/data_0035.h"
