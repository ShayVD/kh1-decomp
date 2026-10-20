/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0023cc80(s32 *);
extern M2C_UNK D_00425BD0[];
extern s32 D_0044A820;
extern s32 D_00647FB0;

void func_002365e0(void) {
    (*(M2C_UNK (**)())((s32) &D_00425BD0 + (s32) ((D_00647FB0 * 4))))();
}

s32 func_0023ceb0(void) {
    if (D_0044A820 == 0) {
        return 0;
    }
    func_0023cc80(&D_0044A820);
    return 0;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_00234910();
void func_00234f80();
void func_00235228();
void func_002353a8();
void func_00235520();
void func_00235688();
void func_002357f0();
void func_00235950();
void func_00235ab0();
void func_00235d70();
void func_00235ee8();
void func_00236190();
void func_00236450();
void func_00236598();
M2C_UNK D_00425BD0[0xe] ALIGNED(16) = {
    (s32)func_00234910, (s32)func_00234f80, (s32)func_00235228, (s32)func_002353a8,
    (s32)func_00235520, (s32)func_00235688, (s32)func_002357f0, (s32)func_00235950,
    (s32)func_00235ab0, (s32)func_00235d70, (s32)func_00235ee8, (s32)func_00236190,
    (s32)func_00236450, (s32)func_00236598,
};
#include "data/bss_0064_mixed.h"
