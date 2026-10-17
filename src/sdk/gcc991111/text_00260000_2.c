/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_0046C5D0;
extern s32 D_00670040;
s32 scePad2DeleteSocket(s32);

s32 scePad2End(void) {
    s32 *var_s1;
    s32 temp_v0;
    s32 var_s0;

    var_s1 = &D_00670040;
    var_s0 = 0;
    D_0046C5D0 = 0;
    for (;;) {
        if (*var_s1 != 0) {
            temp_v0 = scePad2DeleteSocket(var_s0);
            if (temp_v0 >= 0) {
                goto block_5;
            }
            return temp_v0;
        }
    block_5:
        var_s0 += 1;
        var_s1 += 204;
        if (var_s0 >= 0x10) {
            return 1;
        }
    }
}
