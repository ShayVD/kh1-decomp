/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_001f82b0();
M2C_UNK func_0020b998();
M2C_UNK func_0020d2a0();
M2C_UNK func_002336f8();
M2C_UNK func_002365e0();
extern f32 D_00641218;
extern s32 D_003F34C8;
extern s32 D_006411FC;
#include "data/pieces/D_003F34B8.h"
s32 func_001f40c8();

void func_00206f20(void) {
    M2C_FIELD(D_003F34B8, s32 *, 0x38) = 0;
}

void func_002071b8(void) {
    M2C_FIELD(D_003F34B8, s32 *, 0x68) = 0;
}

void func_00207358(void) {
    M2C_FIELD(D_003F34B8, s32 *, 0x70) = 0;
}

void func_0020a6b8(void) {

}

void func_0020a8e8(void) {

}

void func_0020bdf0(void) {
    D_006411FC = 1;
    D_00641218 = 128.0f;
}

s32 func_0020d2f8(void) {
    if ((func_001f40c8() != 0) || (D_003F34C8 != 0)) {
        func_002336f8();
        func_002365e0();
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    func_0020d2a0();
    return 4;
}
#include "data/bss_0064_mixed.h"
#include "data/pieces/D_003F34C8.h"
