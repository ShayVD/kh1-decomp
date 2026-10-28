/* wm.x func_00f45020: matched by hand. */
#include "ovl.h"

extern s32 D_01080840[];
extern s32 D_010808E0[];
CONTEXT_ONLY void func_00f45000(s32 arg0) {
    D_010808E0[arg0] = 1;
}

s32 func_00f45020(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
    case 0:
        if (D_01080840[arg0] != arg1) {
            break;
        }
        return 1;
    case 1:
        if (D_01080840[arg0] == arg1) {
            break;
        }
        return 1;
    case 2:
        func_00f45000(arg0);
        return 1;
    }
    return 0;
}
