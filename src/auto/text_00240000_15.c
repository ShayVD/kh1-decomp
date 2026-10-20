/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_002E26C0;
extern M2C_UNK D_00431D20;
extern M2C_UNK D_00668060; /* src/data/bss_0066.c: B192 D_00668060 */
f32 func_00237a48(s32, s32, s32, s32);
s32 func_00249580(s32);
void func_001315c0(s32, s32, s32, f32);
void func_00246038(s32, s32, s32, s32, f32);
void func_00249558(s32, s32);
void func_0024ae00(s32);
void func_0024af00(s32);

void func_00246120(s32 arg0, s32 arg1, f32 fparg0) {
    s32 sp[8];    M2C_UNK *var_s1;
    s32 temp_v0;

    var_s1 = NULL;
    if (M2C_FIELD(arg0, s32 *, 8) == 0) {
        var_s1 = &D_00668060;
    }
    if (arg1 != 0) {
        func_0024ae00((s32) var_s1);
    }
    func_0024af00((s32) var_s1);
    func_001315c0(M2C_FIELD(arg0, s32 *, 0xC), 0x8004, (s32) sp, 0.0f);
    if (func_00249580((s32) sp) == 0) {
        func_00237a48((s32) &M2C_FIELD(sp, s32 *, 0x10), (s32) &D_002E26C0, (s32) sp, 1);
        func_00249558((s32) &M2C_FIELD(sp, s32 *, 0x10), (s32) &M2C_FIELD(sp, s32 *, 0x10));
        temp_v0 = M2C_FIELD(sp, s32 *, 0x14) - 0x36;
        M2C_FIELD(sp, s32 *, 0x14) = temp_v0;
        func_00246038((s32) var_s1, (s32) &D_00431D20, M2C_FIELD(sp, s32 *, 0x10), temp_v0, fparg0);
    }
}
