/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00267530(M2C_UNK *, void *, s32);
M2C_UNK func_002675a8(void *, void *);
f32 atan2f(f32, f32);
f32 func_00120c18(M2C_UNK *);
void *func_0012bd98(void *, M2C_UNK, M2C_UNK, void *);

s32 func_0012c8e8(void *arg0) {
    s32 sp[8];    s32 var_v0;
    void *temp_v0;

    if ((M2C_FIELD(arg0, f32 *, 0x2D4) - M2C_FIELD(arg0, f32 *, 0x14)) < 5e+01f) {
        func_002675a8(sp, arg0 + 0x10);
        func_00267530(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, M2C_FIELD(arg0, s32 *, 0x148) + 0xF0);
        if (func_00120c18(arg0 + 0x3C0) > 4.0f) {
            if (func_00120c18(&M2C_FIELD(sp, M2C_UNK *, 0x10)) > 1e+02f) {
                M2C_FIELD(sp, f32 *, 0x4) = M2C_FIELD(arg0, f32 *, 0x2D4);
                func_002675a8(M2C_FIELD(arg0, s32 *, 0x148) + 0xF0, sp);
                temp_v0 = func_0012bd98(arg0, 0, 0x08000100, sp);
                var_v0 = 1;
                if (temp_v0 != NULL) {
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 4), s32 *, 0) = 0;
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 4), s32 *, 4) = (s32) ((s32) ((atan2f(M2C_FIELD(arg0, f32 *, 0x3C0), M2C_FIELD(arg0, f32 *, 0x3C8)) / 6.2831855f) * 65536.0f) & 0xFFFF);
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 4), s32 *, 8) = 0;
                    goto block_5;
                }
                /* Duplicate return node #8. Try simplifying control flow for better match */
                return var_v0;
            }
block_5:
            return 1;
        }
    }
    var_v0 = 0;
    return var_v0;
}
