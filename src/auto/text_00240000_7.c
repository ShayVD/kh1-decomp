/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
extern M2C_UNK D_004919A8;
extern M2C_UNK D_004919C8;
extern s32 D_0046A688[];
extern volatile s32 D_00668040[];
s32 func_0025daf0(M2C_UNK *);
void *func_00120190(M2C_UNK *);

s32 func_0024d9a0(void) {
    s32 temp_v0;

    if (D_0046A688[4] != 0) {
        temp_v0 = func_0025daf0(&D_004919A8);
        if (temp_v0 == 0) {
            D_0046A688[4] = 0;
            return temp_v0;
        }
    }
    return 1;
}

s32 func_0024dd98(s32 *arg0) {
    s32 var_s1;
    void *temp_v0;

    var_s1 = 0;
    if (arg0 != NULL) {
        *arg0 = 0;
    }
    temp_v0 = func_00120190(&D_004919C8);
    if (temp_v0 != NULL) {
        var_s1 = M2C_FIELD(temp_v0, s32 *, 0xC);
        if (arg0 != NULL) {
            *arg0 = M2C_FIELD(temp_v0, s32 *, 8);
        }
    }
    return var_s1;
}

#include "data/data_0046.h"
#include "data/data_0049.h"
