/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
void func_001fefc8(s32, s32, s32, s32, s32);

void func_001fef40(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0xCC) != 0) {
        temp_v0 = (s32) (M2C_FIELD(arg0, u16 *, 0xC2) << 0x10) >> 0x14;
        temp_v1 = (s32) (M2C_FIELD(arg0, u16 *, 0xC4) << 0x10) >> 0x14;
        func_001fefc8(arg0, (s32) (M2C_FIELD(arg0, s16 *, 0xBE) + (M2C_FIELD(arg0, s16 *, 0xDA) * temp_v0)) >> 4, (s32) (M2C_FIELD(arg0, s16 *, 0xC0) + (M2C_FIELD(arg0, s16 *, 0xD2) * temp_v1)) >> 4, temp_v0 - ((s32) (M2C_FIELD(arg0, u16 *, 0xC6) << 0x10) >> 0x14), temp_v1 - ((s32) (M2C_FIELD(arg0, u16 *, 0xC8) << 0x10) >> 0x14));
    }
}
