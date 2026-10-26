/* xs_genie.x func_00f205c8: matched by hand. */
#include "ovl.h"

s32 func_00148968(s32, s32, s32);
extern s32 D_00FC1728[];
extern s32 D_00F22E94;
extern s32 D_00F22E98;
void func_00f205c8(void) {
    s32 i;
    for (i = 0; i < 7; i++) {
        D_00FC1728[i] = func_00148968(D_00F22E94, D_00F22E98, i + 24);
    }
}
