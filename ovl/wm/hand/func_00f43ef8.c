/* wm.x func_00f43ef8: matched by hand. */
#include "ovl.h"

void func_00167fd0(s32, s32, s32);
extern s32 D_01080810[];
extern s32 D_01080838[];
extern s32 D_010809A0[];
extern s32 D_010809A8[];

void func_00f43ef8(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (D_010809A0[i] >= 0 && D_010809A8[i] > 0) {
            if (--D_010809A8[i] <= 0) {
                func_00167fd0(D_01080810[D_01080838[i]], 0, D_010809A0[i]);
                D_010809A0[i] = -1;
                D_010809A8[i] = 0;
            }
        }
    }
}
