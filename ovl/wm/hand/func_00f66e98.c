/* wm.x func_00f66e98: the twin of gb.x func_00f3fda0 (tools/ovl/twins.py). */
#include "ovl.h"

void func_0011ef10(s32, void (*)());
void func_001be820(void *, s32);
extern u8 D_00FB11E8[];
extern u8 D_00FB19E8[];
extern s32 D_0108F040;
extern s32 D_0108F044;
void func_00f66d60();
void func_00f66e98(void) {
    func_001be820(D_00FB11E8, 0x800);
    func_001be820(D_00FB19E8, 0x3000);
    D_0108F040 = 0;
    D_0108F044 = 1;
    func_0011ef10(0x2C01A, func_00f66d60);
}
