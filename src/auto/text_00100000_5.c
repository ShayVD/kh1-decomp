/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_002675a8(M2C_UNK *, void *);
extern s8 D_00494BC0;

void func_00107e10(void *arg0) {
    func_002675a8(&D_00494BC0, arg0 + 0x10);
    M2C_FIELD(&D_00494BC0, f32 *, 0xC) = (f32) M2C_FIELD(arg0, f32 *, 0xC);
    func_002675a8(&D_00494BC0 + 0x10, arg0 + 0x30);
}
