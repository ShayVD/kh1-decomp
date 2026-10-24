/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_002672f8();
extern M2C_UNK D_004F6EC0; /* src/data/bss_004F.c: TPool D_004F6EC0 */
extern M2C_UNK func_00122430;
s32 func_0011f090(s32, s32, s32);
s32 func_002675a8(s32, s32);

f32 func_00120ef0(f32 *arg0, s32 arg1, void *arg2) {
    f32 *var_v0;
    f32 temp_f20;
    s32 var_v1;

    M2C_FIELD(arg2, f32 *, 0xC) = 1.0f;
    func_002672f8();
    temp_f20 = 1.0f / M2C_FIELD(arg0, f32 *, 0xC);
    var_v0 = arg0;
    var_v1 = 2;
    do {
        var_v1 -= 1;
        *var_v0 *= temp_f20;
        var_v0 += 1;
    } while (var_v1 >= 0);
    M2C_FIELD(arg0, f32 *, 0xC) = 1.0f;
    return temp_f20;
}

void func_001224c8(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    void *temp_v0;

    if (fparg0 <= 0.0f) {
        func_002675a8(arg0 + 0x30, arg1);
        return;
    }
    temp_v0 = func_0011f090((s32) &D_004F6EC0, 0, (s32) &func_00122430);
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
    M2C_FIELD(temp_v0, f32 *, 0x44) = fparg0;
    M2C_FIELD(temp_v0, f32 *, 0x40) = fparg0;
    M2C_FIELD(temp_v0, s32 *, 0x48) = arg2;
    func_002675a8((s32) (temp_v0 + 0x20), arg0 + 0x30);
    func_002675a8((s32) (temp_v0 + 0x30), arg1);
}
