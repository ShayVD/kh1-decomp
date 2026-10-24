/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

#include "data/pieces/D_00364130.h"
s32 func_00180f18(s32, s32, s32, s32);

void func_00181238(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_00180f18(arg0, 0xA, arg1, (s32) M2C_FIELD(arg1, u8 *, 0x91));
    if (temp_v0 < 0) {
        M2C_FIELD(arg1, s16 *, 0xA4) = 0;
        return;
    }
    M2C_FIELD(arg1, s16 *, 0xA4) = (s16) ((temp_v0 << 7) + 0x3800);
}

s32 func_00181318(void) {
    s8 *var_a0;
    s32 var_a1;
    s32 var_a2;
    u16 temp_v1;

    var_a2 = 0;
    var_a0 = &D_00364130.i;
    var_a1 = 0xFF;
    do {
        temp_v1 = M2C_FIELD(var_a0, u16 *, 0x86);
        if ((temp_v1 & 1 & 0xFFFF) && !(temp_v1 & 4)) {
            var_a2 += M2C_FIELD(M2C_FIELD(var_a0, void **, 0x8C), s32 *, 0xF0);
        }
        var_a1 -= 1;
        var_a0 += 0xC0;
    } while (var_a1 >= 0);
    return var_a2;
}
