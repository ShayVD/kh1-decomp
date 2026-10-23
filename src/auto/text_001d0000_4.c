/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
extern M2C_UNK func_001dc580;
extern s32 D_002C5958;
#include "data/pieces/D_00304BE8.h"
s32 func_0013bf68();

s32 func_001dbc10(void) {
    D_002C5958 &= 0xFFDFFFFF;
    return 2;
}

s32 func_001dc7c0(void) {
    if (func_0013bf68() == 1) {
        func_0011ef10(0x2E631, &func_001dc580);
    }
    return 2;
}
