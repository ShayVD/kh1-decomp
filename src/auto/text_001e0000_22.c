/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001ed000(M2C_UNK, s32, s32, s32, s32, M2C_UNK, M2C_UNK, M2C_UNK);
#include "data/pieces/D_003DCD70.h"
extern s32 D_003DD28C;
extern s32 D_003E3C80;
extern s32 D_00633640; /* src/data/bss_0063.c: u32 D_00633640[2048] */
void *func_00147840();

/* func_001e0898 is in src/screen/screen.c. */

/* func_001e6500, func_001e6c90 are in src/list/list.c. */


s32 func_001ece70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_003E3C80 & 8) {
        return D_00633640;
    }
    func_001ed000(0x29, arg0, arg1, arg2, arg3, 0, 0, 0);
    return D_00633640;
}

s32 func_001eeac0(s32 arg0) {
    s32 var_v0;

    if (!((arg0 == 0) || (var_v0 = 1, (M2C_FIELD(func_00147840(), u8 *, 2) != 0)))) {
        return var_v0;
    }
    var_v0 = 0;
    return var_v0;
}
#include "data/data_003D.h"
#include "data/data_003E.h"
#include "data/pieces/D_003DD28C.h"
