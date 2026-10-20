/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_003F6C90;
extern M2C_UNK D_00643720; /* src/data/bss_0064.c: s32 D_00643720[0x4] */
extern s32 D_003F6E2C;
extern s32 D_006436D0;
void func_001f9010(s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);

void func_00228760(s32 arg0) {
    s32 var_s0;

    var_s0 = *(M2C_UNK *)((s8 *)(s8 *)&D_003F6C90 + (*(M2C_UNK *)((s8 *)(s8 *)&D_00643720 + (D_006436D0 * 4)) * 4));
    if (var_s0 == 0x16A) {
        var_s0 = ((D_003F6E2C ^ 3) != 0) ? 0x16C : var_s0;
    }
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, var_s0, 0x11, 0x8078C850);
}
