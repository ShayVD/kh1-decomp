/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
extern M2C_UNK D_004F82D0; /* src/data/bss_004F.c: u8 D_004F82D0[0x40] */
f32 func_0012ed88(s32, s32, s32, s32);
s32 func_00121de0(s32);
s32 func_00122ff8(s32);
s32 func_002675a8(s32, s32);
void func_00127960(void *, void *, s32);
void func_00127b18(void *, void *, s32);
void func_00267328(void *, M2C_UNK *, s32);

void func_00121f30(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_00121de0(arg0);
    *(M2C_UNK *)arg1 = arg0;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg1;
    M2C_FIELD(temp_v0, s32 *, 0) = 0;
}

s32 func_00123118(void *arg0, void *arg1) {
    s32 temp_a1;
    s32 var_v1;

    var_v1 = 0;
    if (!(M2C_FIELD(arg1, s32 *, 0) & 0x200)) {
        temp_a1 = (s32) ((u64) M2C_FIELD(arg1, u64 *, 0x370) >> 0x25) & 3;
        if (temp_a1 != 0) {
            var_v1 = temp_a1 != ((s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x25) & 3);
        }
    }
    return var_v1;
}

void func_00126ba0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    if (func_00122ff8(*(M2C_UNK *)arg1) != 0) {
        func_0012ed88(arg0, arg1, (s32) sp, arg2);
        M2C_FIELD(arg2, s32 *, 4) = 0;
        return;
    }
    func_002675a8(arg2, arg0 + 0x30);
}

void func_00127b98(void *arg0, s32 arg1, f32 fparg0) {
    s32 sp[16];
    func_00267328(sp, &D_004F82D0, arg1);
    if ((s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x27) & 1) {
        func_00127b18(arg0, sp, (s32) fparg0);
        return;
    }
    func_00127960(arg0, sp, (s32) fparg0);
}
#include "data/data_002E.h"
