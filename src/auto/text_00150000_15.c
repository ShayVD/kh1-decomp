/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00551670;
extern u32 D_002C5958;
void func_00157648(s32, f32, f32, f32, f32, f32, f32, f32, f32);

void func_00157978(s32 arg0, s32 arg1, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7) {
    void *temp_v0;

    func_00157648(arg0, fparg0, fparg1, fparg2, fparg3, fparg4, fparg5, fparg6, fparg7);
    if (!(((u32) D_002C5958 >> 0x14) & 1)) {
        temp_v0 = (s8 *)&D_00551670 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s8 *, 0xBD) * 0x14);
        M2C_FIELD(temp_v0, s8 *, 0) = 1;
        M2C_FIELD(temp_v0, s32 *, 4) = arg0;
        M2C_FIELD(temp_v0, s8 *, 3) = (s8) arg1;
        M2C_FIELD(temp_v0, f32 *, 8) = fparg0;
    }
}
