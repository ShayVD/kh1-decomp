/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_001f3e20(s32, s32);
M2C_UNK func_001f3e48(s32, s32);
M2C_UNK func_001f3e90(s32, s32);
M2C_UNK func_001f9010(M2C_UNK);
M2C_UNK func_001f9438(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00211698();
extern M2C_UNK D_003F3D80;
extern M2C_UNK D_003F4650;
extern M2C_UNK D_00642CA8;
extern s32 D_00641BA0;
extern s32 D_00641BA4;
extern s32 D_00642C90;
extern s32 D_00642C94;
extern s32 D_00642CC8;
extern s32 D_00642CD4;
s32 func_00132fe0(s32);
s32 func_001f31a8(M2C_UNK *, M2C_UNK);

void func_00213c90(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001f31a8(&D_003F3D80, 0);
    if (temp_v0 != 0) {
        func_001f3e90(arg0, temp_v0);
        func_001f3e20(temp_v0, arg0);
    }
    D_00641BA0 = arg0;
    D_00641BA4 = 0;
    func_00211698();
}

void func_00216340(s32 arg0) {
    s32 var_a4;

    func_001f9010(0x17);
    var_a4 = 0xEA;
    if (D_00642CD4 != (D_00642CC8 - 1)) {
        var_a4 = (*(M2C_UNK *)((s8 *)(s8 *)&D_00642CA8 + (D_00642CD4 * 4)) * 3) + func_00132fe0(D_00642CD4) + 0xD4;
    }
    func_001f9438(arg0, 0, 0xAE, 0xC, var_a4, 0x11, 0x80C87850);
}

void func_00217f58(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001f31a8(&D_003F4650, 0);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
    }
    D_00642C90 = arg0;
    D_00642C94 = 0;
}
