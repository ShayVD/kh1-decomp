/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

s32 D_00642E90 ALIGNED(16);
extern s32 D_00642EA4;
extern u16 D_003E9104;
s32 func_0021b4a0(void);

s32 func_0021daa0(s32 arg0) {
    M2C_FIELD(arg0, f32 *, 0xA0) = (f32) D_003E9104;
    D_00642E90 = arg0;
    D_00642EA4 = 0;
    return func_0021b4a0();
}
#include "data/data_003E.h"
