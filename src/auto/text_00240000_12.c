/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK D_006627E0[0x58] ALIGNED(32);
extern s32 D_00662A30; /* src/data/bss_0066.c: E860 D_00662A30[10] */
s32 sceGsSyncPath(s32, s32, s32, s32, s32, s32, s32, s32);
void func_00237018(s32, s32, s32);
void func_002370c8(s32);
void func_00245918(void);
void func_00245cd0(s32);

s32 func_00245da0(void) {
    s32 *var_s0;
    s32 var_s1;

    func_002370c8((s32) &D_006627E0);
    M2C_FIELD(&D_006627E0, s64 *, 0xE0) = 5;
    M2C_FIELD(&D_006627E0, s64 *, 0x60) = 0x30003;
    M2C_FIELD(&D_006627E0, s64 *, 0x70) = (s64) (((s64) 0x80 << 0x20) | 0x48);
    var_s1 = 9;
    func_00237018((s32) &D_006627E0, 0x16, 1);
    func_00245918();
    var_s0 = &D_00662A30;
    do {
        if (*var_s0 != 0) {
            func_00245cd0((s32) var_s0);
        }
        var_s1 -= 1;
        var_s0 += 536;
    } while (var_s1 >= 0);
    return 0;
}

void func_002499f0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 sp[12];
    sceGsSyncPath(0, 0, arg2, arg3, arg4, arg5, arg6, arg7);
    M2C_FIELD(sp, s64 *, 0x10) = ((s64) 0x10000000 << 0x20) | 0x8001;
    M2C_FIELD(sp, s64 *, 0x18) = 0xE;
    M2C_FIELD(sp, s64 *, 0x28) = 0x3F;
    M2C_FIELD(sp, s64 *, 0x20) = 0;
    func_00237018((s32) sp, 3, 1);
}
