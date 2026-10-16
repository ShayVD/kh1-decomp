/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00110c30();
M2C_UNK func_002675b8(M2C_UNK *, void *);
extern M2C_UNK D_002E26C0;
extern M2C_UNK D_002E2700;
extern M2C_UNK D_002E2740;
extern M2C_UNK D_004F7660;
extern M2C_UNK D_004F76E0;
extern M2C_UNK D_004F7760;
extern s32 D_002C5950;

s32 func_001251a0(void) {
    func_002675b8(&D_002E2700, (s8 *)&D_004F76E0 + ((D_002C5950 ^ 1) << 6));
    func_002675b8(&D_002E26C0, (s8 *)&D_004F7660 + ((D_002C5950 ^ 1) << 6));
    func_002675b8(&D_002E2740, (s8 *)&D_004F7760 + ((D_002C5950 ^ 1) << 6));
    func_00110c30();
    return 0;
}
