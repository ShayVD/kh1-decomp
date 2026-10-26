/* wm.x func_00f22d70: matched by hand. */
#include "ovl.h"

void func_00f68a40(s32);
s32 func_00f68b40(s32);
extern s32 D_00FBAA84;
extern s32 D_00FBAA90;
extern s32 D_00FBAA98[];
extern s32 D_00FBB320;
extern s32 D_00FBB324;

void func_00f22d70(void) {
    s32 i, n;
    if (D_00FBB324 != 0 && D_00FBAA98[0] >= 0) {
        n = func_00f68b40(D_00FBAA84);
        for (i = 0; i < n; i++) {
            if (D_00FBAA98[i] >= 0) func_00f68a40(D_00FBAA98[i]);
        }
        D_00FBAA98[0] = -1;
    }
    D_00FBB324 = 0;
    D_00FBAA90 = 0;
    D_00FBB320 = 0;
}
