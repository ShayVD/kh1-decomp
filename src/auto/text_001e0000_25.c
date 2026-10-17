/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern void *D_003F34B8;

void func_001ef778(u32 arg0) {
    M2C_FIELD(D_003F34B8, u32 *, 0x1C) = (u32) ((arg0 <= 0x1869FU) ? arg0 : 0x1869FU);
}
