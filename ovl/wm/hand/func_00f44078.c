/* wm.x func_00f44078: matched by hand. */
#include "ovl.h"

void func_00167ac0(s32, s32, s32);
void func_00167fd0(s32, s32, s32);
extern s32 D_01080810[];
extern s32 D_01080838[];
extern s32 D_010809A0[];
extern s32 D_010809A8[];

void func_00f44078(s32 arg0, s32 arg1, s32 arg2) {
    if (D_010809A0[arg0] >= 0) {
        func_00167fd0(D_01080810[D_01080838[arg0]], 0, D_010809A0[arg0]);
    }
    func_00167ac0(D_01080810[D_01080838[arg0]], 0, arg1);
    D_010809A0[arg0] = arg1;
    D_010809A8[arg0] = arg2;
}
