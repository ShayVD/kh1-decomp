/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"
M2C_UNK func_0021b800(s32);
extern M2C_UNK D_003F5C90;
#include "data/pieces/D_003F5FF0.h"
extern s32 D_003F5C20;
extern s32 D_0064311C;
extern s32 D_00643120;

u16 func_0021dc08(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_003F5C90 + (arg0 * 2));
}

void func_0021fb28(void) {
    D_003F5C20 = 1;
    D_0064311C = -1;
    D_00643120 = -1;
}

void func_0021fd60(s32 arg0) {
    func_0021b800(*(M2C_UNK *)((s8 *)(M2C_UNK *)&D_003F5FF0 + (arg0 * 4)) + 0x20);
}
#include "data/data_003F.h"
