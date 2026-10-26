/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK func_00f200c8;
extern s32 D_002E26A0;
extern s32 D_00F20D84;
extern s32 D_00F20E80;
s32 func_0011ef10(s32, s32);
s32 func_00130340(s32, s32, f32);
void func_001248e8(s32);
void func_0013a810(void);
void func_00f200b0(s32);
void func_00f20958(void);

void func_00f20170(void) {
    D_00F20D84 = D_002E26A0;
    func_00130340(D_002E26A0, 0x40000000, 0);
    func_0013a810();
    func_001248e8(0x70003);
    func_00f20958();
    D_00F20E80 = 1;
    func_00f200b0(0);
    func_0011ef10(0xCB20, &func_00f200c8);
}
