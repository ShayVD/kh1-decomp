/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_00122768(s32);
M2C_UNK func_001386f8(s32);
M2C_UNK func_0016f548();
extern M2C_UNK D_00575010; /* src/data/bss_0057.c: s32 D_00575010 */
extern s32 D_00575310; /* src/data/bss_0057.c: TalkEA D_00575310 */

void func_00170e98(void) {
    s32 *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s0 = &D_00575310;
    var_s1 = 2;
    do {
        temp_a0 = *var_s0;
        var_s1 -= 1;
        if (temp_a0 != 0) {
            func_00122768(temp_a0);
            *var_s0 = 0;
        }
        var_s0 += 2;
    } while (var_s1 >= 0);
    func_0016f548();
    func_001386f8(M2C_FIELD(&D_00575010, s32 *, 0));
    func_001386f8(M2C_FIELD(&D_00575010, s32 *, 4));
}
#include "data/data_0035.h"
#include "data/data_0036.h"
