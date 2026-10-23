/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"
M2C_UNK func_002073b0(M2C_UNK, void *);
#include "data/pieces/D_003E3D68.h"
s32 func_0020ec50(s32);
s32 func_0020f530(s32);
s32 func_0020fc58(s32);

s32 func_0020fea0(s32 arg0) {
    u32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, u32 *, 0x24);
    if (temp_a1 < (u32) D_003E3D68) {
        return func_0020ec50(arg0);
    }
    if (temp_a1 == D_003E3D68) {
        return func_0020f530(arg0);
    }
    return func_0020fc58(arg0);
}

void func_0020fee8(void *arg0) {
    if (((u32) D_003E3D68 < (u32) M2C_FIELD(arg0, u32 *, 0x24)) && (M2C_FIELD(arg0, s32 *, 0x28) != 0)) {
        func_002073b0(1, arg0);
    }
}
#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
