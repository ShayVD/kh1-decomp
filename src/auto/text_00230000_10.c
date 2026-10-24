/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
extern s32 D_002C5958;
void func_0024ae00(s32);
void func_0024af00(s32);

void func_0023a8d0(s32 arg0) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;

    var_a1 = 0;
    temp_v1 = arg0 + 0x40;
    temp_a0 = arg0 + 0x100;
    if (D_002C5958 & 1) {
        if (M2C_FIELD(arg0, s32 *, 0x1C0) != temp_v1) {
            M2C_FIELD(arg0, s32 *, 0x1C0) = temp_v1;
            func_0024ae00(temp_v1);
            var_a1 = 1;
            M2C_FIELD(arg0, s32 *, 0x1C4) = 0;
        }
    } else if (M2C_FIELD(arg0, s32 *, 0x1C0) != temp_a0) {
        M2C_FIELD(arg0, s32 *, 0x1C0) = temp_a0;
        func_0024ae00(temp_a0);
        var_a1 = 1;
        M2C_FIELD(arg0, s32 *, 0x1C4) = 1;
    }
    if (var_a1 != 0) {
        return;
    }
    func_0024af00(M2C_FIELD(arg0, s32 *, 0x1C0));
}
#include "data/data_0042.h"
