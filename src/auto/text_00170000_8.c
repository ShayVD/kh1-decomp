/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_00122768(s32);
M2C_UNK func_001386f8(s32);
M2C_UNK func_0016f548();
M2C_UNK func_001784c8();
M2C_UNK func_00267530(void *, M2C_UNK *, M2C_UNK *);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_00575010; /* src/data/bss_0057.c: s32 D_00575010 */
extern M2C_UNK D_005758D0; /* src/data/bss_0057.c: f32 D_005758D0[4] */
extern M2C_UNK D_005758E0; /* src/data/bss_0057.c: f32 D_005758E0[4] */
extern M2C_UNK D_005759B0;
extern f32 D_00362680;
extern s32 D_00575310; /* src/data/bss_0057.c: TalkEA D_00575310 */
f32 func_00120c18(void *);
s32 func_001770b8();

void func_00170e98(void) {
    s32 *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s0 = &D_00575310;
    var_s1 = 2;
    do {
        temp_a0 = *var_s0;
        var_s1 -= 1;
        if (temp_a0 != 0) {
            func_00122768(temp_a0);
            *var_s0 = 0;
        }
        var_s0 += 2;
    } while (var_s1 >= 0);
    func_0016f548();
    func_001386f8(M2C_FIELD(&D_00575010, s32 *, 0));
    func_001386f8(M2C_FIELD(&D_00575010, s32 *, 4));
}

void func_00178d90(void) {
    s32 sp[4];
    func_00267530(sp, &D_005758D0, &D_005758E0);
    if ((func_00120c18(sp) < 40.0f) && (D_00362680 < 1.0471975f) && (func_001770b8() != 0)) {
        func_001784c8();
    }
}

void func_0017dee0(void) {
    memset(&D_005759B0, 0, 0x50);
}
#include "data/data_0035.h"
#include "data/data_0036.h"
