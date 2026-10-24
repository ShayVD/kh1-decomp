/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_0011d790(M2C_UNK, s32);
M2C_UNK func_0023dd48();
extern s32 D_0044A820;

void func_0023cee8(void) {
    if (D_0044A820 == 0) {
        D_0044A820 = 1;
    }
}

void func_0023cf08(void) {
    if (D_0044A820 == 2) {
        D_0044A820 = 3;
    }
}

void func_0023d128(s32 arg0) {
    func_0011d790(0x2D, arg0);
}

void func_0023dfc0(void) {
    func_0023dd48();
}
#include "data/data_003F.h"
#include "data/pieces/D_0044A820.h"
