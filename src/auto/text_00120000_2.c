/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
f32 func_00120c18();
f32 func_0026b9a8(f32, f32);

void func_001210f0(void *arg0, void *arg1, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg1, f32 *, 0) * fparg0);
    M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = (f32) (M2C_FIELD(arg1, f32 *, 8) * fparg0);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
}

void func_00121a10(void *arg0, void *arg1) {
    f32 temp_f0;

    M2C_FIELD(arg1, f32 *, 0) = func_0026b9a8(-M2C_FIELD(arg0, f32 *, 4), func_00120c18());
    temp_f0 = func_0026b9a8(M2C_FIELD(arg0, f32 *, 0), M2C_FIELD(arg0, f32 *, 8));
    M2C_FIELD(arg1, s32 *, 8) = 0;
    M2C_FIELD(arg1, f32 *, 4) = temp_f0;
    M2C_FIELD(arg1, f32 *, 0xC) = 1.0f;
}
#include "data/bss_0052_mixed.h"
