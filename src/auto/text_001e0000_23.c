/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001ed000(M2C_UNK, s32, s32, s32, s32, s32, M2C_UNK, M2C_UNK);
extern s32 D_003DD28C;
extern s32 D_003E3C80;
extern s32 D_00633640; /* src/data/bss_0063.c: u32 D_00633640[2048] */

/* func_001e6eb0 is in src/list/list.c. */

s32 func_001ed278(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (D_003E3C80 & 2) {
        return D_00633640;
    }
    func_001ed000(5, arg0, arg1, arg2, arg3, arg4, 0, 0);
    return D_00633640;
}
#include "data/data_003E.h"
#include "data/pieces/D_003DD28C.h"
