/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_00232cc0(s32);

void func_001c0e80(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;

    temp_a0 = func_00232cc0(2);
    switch (arg1) {                                 /* irregular */
    case 1:
        *(s8 *)((s32) temp_a0 + (s32) arg0) = *(M2C_UNK *)arg2;
        return;
    case 2:
        *(s16 *)((s32) temp_a0 + (s32) arg0) = (u16) *(M2C_UNK *)arg2;
        break;
    case 4:
        *(M2C_UNK *)((s32) temp_a0 + (s32) arg0) = (s32) *(M2C_UNK *)arg2;
        break;
    }
}
