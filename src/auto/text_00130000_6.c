/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"

f32 func_0026b9a8(f32, f32);
s32 func_00130040(s32, s32);
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
void func_00137688(s32, f32);
void func_00138ca0(s32, s32, f32);
void func_00139408(s32, s32);

void func_00138f28(Actor *arg0, s32 arg1, f32 fparg0) {
    f32 var_f0;

    if (func_00130040(arg0, 0x4C) == 0) {
        if (func_00130040(arg0, 0x52) != 0) {
            func_00139408(arg0, arg1);
            return;
        }
        func_00138ca0(arg0, arg1, fparg0);
        return;
    }
    if (fparg0 < 0.0f) {
        func_00130340(arg0, 0x0100004C, 0.0f);
        var_f0 = func_0026b9a8(-M2C_FIELD(arg1, f32 *, 0x10), -M2C_FIELD(arg1, f32 *, 0x18));
    } else {
        func_00130340(arg0, 0x0100004D, 0.0f);
        var_f0 = func_0026b9a8(M2C_FIELD(arg1, f32 *, 0x10), M2C_FIELD(arg1, f32 *, 0x18));
    }
    arg0->unk150 = var_f0;
    func_00137688(arg0, var_f0);
    func_00130578(arg0, 0x40000000, 8.0f);
    arg0->unk3CC = 0;
}
