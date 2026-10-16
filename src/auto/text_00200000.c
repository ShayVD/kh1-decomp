/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f31a8(M2C_UNK *, M2C_UNK);
M2C_UNK func_00207598();
extern M2C_UNK D_003F3420;
extern s32 D_00640E28;
extern s32 D_006411E0;
extern s32 D_006411FC;
extern s32 D_00641210;
extern s32 D_00641214;
extern s32 D_00641218;
extern void *D_003F34B8;
s32 func_001ee7a8();

void func_00206ff0(void) {
    M2C_FIELD(D_003F34B8, s32 *, 0x3C) = 0;
}

void func_00207288(void) {
    M2C_FIELD(D_003F34B8, s32 *, 0x6C) = 0;
}

void func_002075f8(void) {
    D_00640E28 = 7;
    func_00207598();
}

void func_0020b968(void) {
    D_006411FC = 3;
    D_006411E0 = 0;
    D_00641210 = 0;
    D_00641214 = 0;
    D_00641218 = 0;
}

s32 func_0020bb78(void) {
    return D_006411FC != 3;
}

void func_0020d030(void) {
    func_001f31a8(&D_003F3420, 0);
}

s32 func_0020d6c0(void) {
    return 0;
}

s32 func_0020f260(s32 arg0) {
    return (func_001ee7a8() << 8) | arg0;
}
