/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00372EA8;
extern M2C_UNK D_00372F34;
extern s8 D_00372F28;

s32 func_001aaa00(s32 arg0) {
    return (*(M2C_UNK *)((s8 *)(s8 *)&D_00372F34 + (D_00372F28 * 4)) >= (s32) ((s8 *)&D_00372EA8 + arg0)) ? 0 : -1;
}
