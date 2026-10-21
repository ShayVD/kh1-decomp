/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f9010(M2C_UNK);
M2C_UNK func_001f9438(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
#include "data/pieces/D_003E8E08.h"

void func_0020ff28(void *arg0) {
    func_001f9010(0x17);
    (*(s32 *)&D_003E8E08) = M2C_FIELD(arg0, s32 *, 0x28);
    func_001f9438(arg0, 0, 0xAE, 0xC, M2C_FIELD(arg0, s32 *, 0x24), 0x11, 0x80C87850);
}
