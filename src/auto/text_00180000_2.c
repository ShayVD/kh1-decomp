/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK pppDesObject(M2C_UNK *);
M2C_UNK func_00183b20(s32, s32);
extern s32 D_00615E64;

void func_00182788(void *arg0) {
    M2C_UNK *temp_s0;
    M2C_UNK *var_a0;
    s32 temp_a1;

    var_a0 = M2C_FIELD(arg0, M2C_UNK **, 0x74);
    if (var_a0 != NULL) {
        do {
            temp_s0 = *var_a0;
            pppDesObject(var_a0);
            var_a0 = temp_s0;
        } while (var_a0 != NULL);
    }
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x80);
    M2C_FIELD(arg0, M2C_UNK **, 0x74) = NULL;
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(arg0, s32 *, 0x80) = 0;
    }
}

void func_001839f8(void) {

}
