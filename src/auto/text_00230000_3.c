/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_00239630(s32, s32, s32, s32, f32);
M2C_UNK func_0024ae00(s32);
M2C_UNK func_0024af00(s32);
extern s32 D_00454A24;
s32 func_0023f0d8(s32, s32);
s32 func_0023f250(s32, s32);

s32 func_0023f688(s32 arg0, s32 arg1) {
    s32 var_v1;

    if (M2C_FIELD(arg0, s32 *, 0) == 4) {
        var_v1 = D_00454A24;
    } else {
        var_v1 = M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x6C), s32 *, 0x3C);
    }
    if (var_v1 == 0) {
        return arg1;
    }
    return func_0023f250(arg0, func_0023f0d8(arg0, arg1));
}
#include "data/data_0044.h"
#include "data/pieces/D_00454A20.h"
