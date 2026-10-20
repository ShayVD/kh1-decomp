/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00372EA8;
extern s32 D_00372F30;
extern s8 D_00372EA0;
extern s8 D_00372F28;
extern void *D_00615E60;
void func_00267620(s32);

void func_001a5688(void *arg0, void **arg1) {
    M2C_FIELD(arg0, u16 *, 0) = (u16) M2C_FIELD(*arg1, u16 *, 0x12);
    M2C_FIELD(arg0, s8 *, 2) = 0;
}

void func_001a5ca0(s32 arg0) {
    M2C_FIELD(D_00615E60, s8 *, 0xB0) = 2;
    func_00267620(arg0 + 0x40);
    M2C_FIELD(arg0, f32 *, 0xAC) = 1.0f;
}

void func_001a8d78(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 4) = 0;
}

f32 func_001a92f0(s32 arg0, f32 fparg0) {
    f32 var_f0;
    s32 var_a0;

    var_a0 = arg0;
    var_f0 = 1.0f;
    if (var_a0 > 0) {
        do {
            var_a0 -= 1;
            var_f0 *= fparg0;
        } while (var_a0 != 0);
    }
    return var_f0;
}

void func_001aa918(void) {
    D_00372EA8 = 0x70000000;
    D_00372F30 = 0x70004000;
    D_00372EA0 = 0;
    D_00372F28 = 0;
}
#include "data/bss_0061_mixed.h"
#include "data/data_0037.h"
