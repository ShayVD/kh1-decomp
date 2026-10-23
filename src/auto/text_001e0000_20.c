/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0063.h"

extern s64 D_00389C90[];

/* func_001e2498 is in src/screen/screen.c. */

/* func_001e78d8, func_001e7a10, func_001e7b50 are in src/list/list.c. */



/* func_001e7fe0, func_001e8308, func_001e8628, func_001e8770, func_001e87b8, func_001e8e38 are in src/event/sound.c. */






s32 func_001ea438(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xFFBFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
    return 2;
}

s32 func_001ea470(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] | ((s64) 0x8000 << 0x27));
    return 2;
}
