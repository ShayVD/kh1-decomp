/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_002C5C48;
s32 func_0011e248(s32);
s32 func_00146878(void);
s32 func_001ecfd8(void);
void func_00121eb0(s32);
void func_001ed780(s32, s32, s32);

s32 func_001570d0(s32 arg0) {
    M2C_UNK (*temp_v0)();
    s32 temp_a0;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x48);
    temp_a0 = M2C_FIELD(temp_s0, s32 *, 0);
    switch (temp_a0) {                              /* irregular */
    case 0:
        if (D_002C5C48 > 0) {
            if ((func_0011e248(0) == 0) && (func_00146878() != 0)) {
                func_001ed780(M2C_FIELD(temp_s0, s32 *, 4), M2C_FIELD(temp_s0, s32 *, 8), D_002C5C48);
                goto block_7;
            }
        } else {
block_7:
            M2C_FIELD(temp_s0, s32 *, 0) = (s32) (M2C_FIELD(temp_s0, s32 *, 0) + 1);
        }
        return 8;
    case 1:
        if (func_001ecfd8() == 0) {
            temp_v0 = M2C_FIELD(temp_s0, M2C_UNK (**)(), 0x10);
            if (temp_v0 != NULL) {
                temp_v0();
            }
            func_00121eb0((s32) temp_s0);
            return 4;
        }
        /* Duplicate return node #15. Try simplifying control flow for better match */
        return 8;
    default:
        return 8;
    }
}
