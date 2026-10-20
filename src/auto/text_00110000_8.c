/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
extern s32 D_002BCDA8;
s32 func_00112b18(void);
void func_00111600(s32, s32, s32);

void func_00112b48(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_002BCDA8 = arg3;
    D_002BC128 = arg0;
    D_002BC130 = arg1;
    D_002BC134 = arg2;
    func_00111600(arg0, arg1, arg2);
    func_00112b18();
}
#include "data/data_002B.h"
