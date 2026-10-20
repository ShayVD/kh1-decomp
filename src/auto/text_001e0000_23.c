/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0010bd90(M2C_UNK *, M2C_UNK);
M2C_UNK func_001ed000(M2C_UNK, s32, s32, s32, s32, s32, M2C_UNK, M2C_UNK);
extern M2C_UNK D_00630460;
extern M2C_UNK D_00630510; /* src/data/bss_0063.c: u8 D_00630510[0xb0] */
extern s32 D_002C5BB8;
extern s32 D_003DD28C;
extern s32 D_003E3C80;
extern s32 D_00633640; /* src/data/bss_0063.c: u32 D_00633640[2048] */

s32 func_001e6eb0(void) {
    s32 var_v0;

    var_v0 = 4;
    if (D_003DD28C == 0) {
        return var_v0;
    }
    if (D_002C5BB8 & 2) {
        func_0010bd90(&D_00630510, 0);
        func_0010bd90(&D_00630460, 0);
        D_003DD28C = 0;
        return 4;
    }
    var_v0 = 0;
    /* Duplicate return node #5. Try simplifying control flow for better match */
    return var_v0;
    return var_v0;
}

s32 func_001ed278(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (D_003E3C80 & 2) {
        return D_00633640;
    }
    func_001ed000(5, arg0, arg1, arg2, arg3, arg4, 0, 0);
    return D_00633640;
}
#include "data/data_003E.h"
