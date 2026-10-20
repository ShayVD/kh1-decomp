/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f9010(M2C_UNK);
M2C_UNK func_001f9438(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern s32 D_003E8E08;
extern s32 D_00642CCC;
s32 func_001ee618(s32);

void func_00217750(s32 arg0) {
    M2C_UNK var_s1;

    var_s1 = 0xCC;
    if (D_00642CCC != 0) {
        var_s1 = 0xCD;
        D_003E8E08 = func_001ee618(D_00642CCC);
    }
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, var_s1, 0x11, 0x80C87850);
}
#include "data/bss_0064_mixed.h"
