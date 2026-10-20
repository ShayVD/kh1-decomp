/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_002E26A0;
extern s32 D_00575894; /* src/data/bss_0057.c: void *D_00575894 */
s32 func_0017d628(void);
s32 func_0017ecf8(void);
void func_00176f08(s32, f32);
void func_0017eaa0(void);

void func_0017eb88(void) {
    D_00575894 = D_002E26A0;
    func_0017eaa0();
    if (func_0017d628() == 0) {
        func_00176f08(1, 0.0f);
    }
    func_0017ecf8();
}
