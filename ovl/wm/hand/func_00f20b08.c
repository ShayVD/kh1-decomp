/* wm.x func_00f20b08: matched by hand. */
#include "ovl.h"

extern s32 D_00F85120;
extern s32 D_00F85124;
extern s32 D_00F85128;
extern s32 D_00F8512C;
extern s32 D_00FBAA18[8];
extern s32 D_00FBAA38[8];
extern s32 D_00FBAA58;

void func_00f20b08(s32 arg0, s32 arg1) {
    s32 i;
    if (D_00F8512C < 8) {
        if (D_00F85124 >= 0 && D_00F8512C == 0 && D_00F85120 == arg0) {
            D_00F85124 = arg1;
            return;
        }
        i = D_00F85128 + D_00F8512C;
        D_00F8512C++;
        D_00FBAA58 = 0;
        i &= 7;
        D_00FBAA18[i] = arg0;
        D_00FBAA38[i] = arg1;
    }
}
