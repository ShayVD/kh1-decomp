/* xl_limit.x func_00f20690: matched by hand. */
#include "ovl.h"

s32 func_0011f130(void *, s32);
extern s32 D_002C5958;
extern u8 D_00F23490[];
extern s32 D_00F23E00;

s32 func_00f20690(void) {
    if ((D_002C5958 & 0x810000) != 0x10000) {
        return 4;
    }
    D_00F23E00 = func_0011f130(D_00F23490, 0);
    return D_00F23E00 == 0 ? 4 : 0;
}
