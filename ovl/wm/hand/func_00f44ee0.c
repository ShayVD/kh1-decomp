/* wm.x func_00f44ee0: matched by hand. */
#include "ovl.h"

extern s32 D_01080840[];
extern s32 D_01080848[];
extern s32 D_01080850[];
extern s32 D_01080858[];
extern s32 D_01080860[][8];
extern s32 D_010808A0[][8];

void func_00f44ee0(s32 arg0, s32 arg1, s32 arg2) {
    s32 idx;
    if (D_01080858[arg0] >= 8) return;
    if (D_01080858[arg0] == 0 && D_01080840[arg0] == arg1) {
        D_01080848[arg0] = arg2;
        return;
    }
    if (D_01080858[arg0] > 0) {
        idx = (D_01080850[arg0] + D_01080858[arg0] - 1) & 7;
        if (D_01080860[arg0][idx] == arg1 || D_01080860[arg0][idx] == 0) {
            D_01080860[arg0][idx] = arg1;
            D_010808A0[arg0][idx] = arg2;
            return;
        }
    }
    idx = (D_01080850[arg0] + D_01080858[arg0]++) & 7;
    D_010808A0[arg0][idx] = arg2;
    D_01080860[arg0][idx] = arg1;
}
