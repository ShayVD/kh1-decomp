/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0054.h"
M2C_UNK D_00547BC0[0x10] ALIGNED(64);
extern s32 D_0054F44C;

void func_0014ec10(s32 arg0) {
    D_0054F44C &= ~(1 << (arg0 - 1));
}

void func_0014ec38(s32 arg0) {
    D_0054F44C |= 1 << (arg0 - 1);
}
#include "data/bss_0053_mixed.h"
#include "data/data_0030.h"
#include "data/data_0034.h"
