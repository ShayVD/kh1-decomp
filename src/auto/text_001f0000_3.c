/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern void *D_00640DD8; /* src/data/bss_0064.c: s32 D_00640DD8 */

void *func_001f4260(void) {
    void *temp_v0;
    void *var_a0;
    void *var_v1;

    var_v1 = D_00640DD8;
    if (var_v1 != NULL) {
        var_a0 = M2C_FIELD(var_v1, void **, 0x18);
        if (var_a0 != NULL) {
            do {
                var_v1 = var_a0;
                temp_v0 = M2C_FIELD(var_v1, void **, 0x18);
                var_a0 = temp_v0;
            } while (temp_v0 != NULL);
        }
    }
    return var_v1;
}

void func_001f8170(void *arg0) {
    M2C_UNK (*temp_v0)();
    void *temp_a0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = M2C_FIELD(arg0, M2C_UNK (**)(), 8);
    if (temp_v0 != NULL) {
        temp_v0();
    }
    temp_v1 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    if (temp_v1 != NULL) {
        M2C_FIELD(temp_v1, void **, 0x18) = (void *) M2C_FIELD(arg0, void **, 0x18);
        temp_v1_2 = M2C_FIELD(arg0, void **, 0x18);
        if (temp_v1_2 != NULL) {
            M2C_FIELD(temp_v1_2, void **, 0x14) = (void *) M2C_FIELD(arg0, void **, 0x14);
        }
    } else {
        temp_a0 = M2C_FIELD(arg0, void **, 0x18);
        D_00640DD8 = temp_a0;
        if (temp_a0 != NULL) {
            M2C_FIELD(temp_a0, void **, 0x14) = NULL;
        }
    }
}
