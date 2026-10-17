/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void func_00134998(void *arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x3EC);
    if (temp_a0 != NULL) {
        M2C_FIELD(temp_a0, s64 *, 8) = (s64) (M2C_FIELD(temp_a0, s64 *, 8) & (((((s64) 0xFFFF0FFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
    }
}

void func_00135848(void *arg0) {
    M2C_FIELD(arg0, s64 *, 0x370) = (s64) (M2C_FIELD(arg0, s64 *, 0x370) & (((((s64) 0xFFFDFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}
