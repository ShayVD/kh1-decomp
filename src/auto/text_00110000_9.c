/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/pieces/D_002BCB40.h"
#include "data/pieces/D_002BCB50.h"

void func_00110e38(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    M2C_FIELD((M2C_UNK *)&D_002BCB40, f32 *, 0) = fparg0;
    M2C_FIELD((M2C_UNK *)&D_002BCB40, f32 *, 4) = fparg1;
    M2C_FIELD((M2C_UNK *)&D_002BCB40, f32 *, 8) = fparg2;
    M2C_FIELD((M2C_UNK *)&D_002BCB40, f32 *, 0xC) = fparg3;
    M2C_FIELD((M2C_UNK *)&D_002BCB50, s32 *, 0) = 0;
    M2C_FIELD((M2C_UNK *)&D_002BCB50, s32 *, 4) = 0;
    M2C_FIELD((M2C_UNK *)&D_002BCB50, s32 *, 8) = 0;
}
#include "data/bss_004E_mixed.h"
