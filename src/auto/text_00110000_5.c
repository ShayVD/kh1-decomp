/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00109558(M2C_UNK);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0022bcb8(M2C_UNK);
extern M2C_UNK func_0011c630;
extern s32 D_003F7774;
extern s32 D_003F7778;

s32 func_0011c698(void) {
    if (D_003F7774 == 0) {
        switch (D_003F7778) {                       /* irregular */
        case 0:
            func_00109558(0xA);
            return 4;
        case 1:
            func_0022bcb8(0xFFFF);
            func_0011ef10(0x7530, &func_0011c630);
            return 4;
        default:
            return 0;
        }
    } else {
        return 0;
    }
}
