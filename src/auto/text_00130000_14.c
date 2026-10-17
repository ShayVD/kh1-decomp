/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern void *D_00308CDC;
f32 atan2f(f32, f32);
s32 func_00130040(s32, s32);
void func_00130340(s32, s32, f32);
void func_00130578(s32, s32, f32);
void func_00137688(s32, f32);
void func_00138a20(s32, s32, f32);
void func_00138d88(s32, s32, f32);
void func_00139408(s32, s32);
void func_002675a8(s32, s32);

void func_00139040(s32 arg0, s32 arg1, f32 fparg0) {
    s32 sp[4];    f32 var_f0;

    if (func_00130040(arg0, 0x50) == 0) {
        if (func_00130040(arg0, 0x5C) != 0) {
            func_00139408(arg0, arg1);
            return;
        }
        func_00138d88(arg0, arg1, fparg0);
        return;
    }
    if (fparg0 < 0.0f) {
        func_00130340(arg0, 0x01000050, 0.0f);
        var_f0 = atan2f(-M2C_FIELD(arg1, f32 *, 0x10), -M2C_FIELD(arg1, f32 *, 0x18));
    } else {
        func_00130340(arg0, 0x01000051, 0.0f);
        var_f0 = atan2f(M2C_FIELD(arg1, f32 *, 0x10), M2C_FIELD(arg1, f32 *, 0x18));
    }
    func_00130578(arg0, 6, 8.0f);
    M2C_FIELD(arg0, f32 *, 0x150) = var_f0;
    func_00137688(arg0, var_f0);
    func_002675a8((s32) sp, arg1 + 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = M2C_FIELD(D_00308CDC, f32 *, 0x3C);
    func_00138a20(arg0, (s32) sp, 2e+01f);
}
