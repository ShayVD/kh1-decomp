/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00104300(M2C_UNK);
M2C_UNK func_001043f8(M2C_UNK);
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
extern M2C_UNK D_006297F8; /* src/data/bss_0062.c: u8 D_006297F8[0x10] */
extern s32 D_0037A168;
extern s32 D_0037A16C;
extern s64 D_00389C90[];

void func_001c0078(s32 arg0) {
    void *temp_a0;
    void *temp_v1;

    if (arg0 >= 0) {
        temp_a0 = (arg0 * 0x30) + D_0037A16C;
        if (M2C_FIELD(temp_a0, u16 *, 0) != 0) {
            M2C_FIELD(temp_a0, u16 *, 4) = (u16) (M2C_FIELD(temp_a0, u16 *, 4) | 1);
        }
    } else if (D_0037A168 != 0) {
        temp_v1 = (D_0037A168 * 0x30) + D_0037A16C;
        M2C_FIELD(temp_v1, u16 *, 4) = (u16) (M2C_FIELD(temp_v1, u16 *, 4) | 1);
    }
}

s32 func_001c07c8(void) {
    func_0011f130(&D_006297F8, 0);
    return 0;
}

/* func_001ca9f8 is in src/msgwin/msgwin.c. */

s32 func_001ceee8(void) {
    func_00104300(0x10);
    D_00389C90[1551] = (s64) (D_00389C90[1551] | 1);
    return 2;
}

s32 func_001cef80(void) {
    func_001043f8(0x10);
    D_00389C90[1551] = (s64) (D_00389C90[1551] & ~1);
    return 2;
}
#include "data/data_0037.h"
