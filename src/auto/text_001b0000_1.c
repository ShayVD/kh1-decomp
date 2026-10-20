/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001efb18(M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_00378A48;
extern M2C_UNK D_00379C78;
extern s32 D_0062321C;
s32 func_001bb740();
void *func_001ba980();

void func_001baaa8(s32 arg0) {
    M2C_FIELD(func_001ba980(), s32 *, 8) = arg0;
}

s32 func_001baad0(void) {
    return M2C_FIELD(func_001ba980(), s32 *, 8);
}

void func_001bb558(void) {
    func_001efb18(&D_00378A48, &D_00379C78);
}

s32 func_001bb658(s32 arg0) {
    return D_0062321C + (arg0 * 0x1C);
}

s32 func_001be5c8(s32 arg0) {
    return arg0 + 1;
}

s32 func_001be5d0(s32 arg0) {
    return arg0 + func_001bb740() + 1;
}

s32 func_001be600(s32 arg0) {
    return arg0 + (func_001bb740() * 2) + 1;
}
#include "data/bss_0062_mixed.h"
