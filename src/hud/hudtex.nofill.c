/* The HUD's textures, the nofill part (docs/modules.md "Session 45"):
 * func_002389f0(n) is the address of image n in "command2/uitex.bin"
 * (loaded at D_00440994 by hudtex.nostrict_nofill.c's func_00238a70): the
 * sizes of the images before it summed (0x4440 for 5 and 8, 0x1440 for 9 and
 * 11 to 20, 0x2080 for the others). */
#include "common.h"

extern s32 D_00440994;

s32 func_002389f0(s32 n) {
    s32 i;
    s32 s = 0;
    for (i = 0; i < n; i++) {
        if (i == 5) s += 0x4440;
        else if (i == 8) s += 0x4440;
        else if (i == 9) s += 0x1440;
        else s += (u32)(i - 11) < 10 ? 0x1440 : 0x2080;
    }
    return D_00440994 + s;
}
