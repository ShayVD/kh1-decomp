/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

extern M2C_UNK D_006437C8; /* src/data/bss_0064.c: s32 D_006437C8[0x2] */
extern M2C_UNK D_006437D0; /* src/data/bss_0064.c: s32 D_006437D0[0x2] */
extern s32 D_006437C4;
extern s32 D_006437D8;

void func_0022bd20(void) {
    D_006437C4 = 0;
    D_006437D8 = 0;
    M2C_FIELD(&D_006437C8, s32 *, 0) = 0;
    M2C_FIELD(&D_006437C8, s32 *, 4) = 0;
    M2C_FIELD(&D_006437D0, s32 *, 0) = 0;
    M2C_FIELD(&D_006437D0, s32 *, 4) = 0;
}
