/* wm.x func_00f4a190: matched by hand. */
#include "ovl.h"

extern u8 D_01080A38[192];
extern s32 D_00F9B744;
extern f32 D_00F9B74C;
extern s32 D_00F9B750;

void func_00f4a190(s32 mode, s32 k, f32 f) {
    s32 i;
    for (i = 0; i < 192; i++)
        D_01080A38[i] = 0;
    D_00F9B744 = mode;
    D_00F9B750 = 0;
    switch (mode) {
    case 4:
        D_00F9B750 = 1;
        break;
    case 1:
        D_01080A38[k] = 1;
        break;
    case 2:
        break;
    case 3:
        switch (k) {
        case 0:
            D_01080A38[5] = 1;
            D_01080A38[6] = 1;
            D_01080A38[7] = 1;
            D_01080A38[8] = 1;
            break;
        case 1:
            D_01080A38[52] = 1;
            D_01080A38[53] = 1;
            break;
        case 2:
            D_01080A38[48] = 1;
        case 3:
            D_01080A38[58] = 1;
            break;
        case 4:
            D_01080A38[59] = 1;
            break;
        case 5:
            D_01080A38[60] = 1;
            break;
        case 6:
            D_01080A38[61] = 1;
            break;
        case 7:
            D_01080A38[62] = 1;
            break;
        case 8:
            D_01080A38[63] = 1;
            break;
        case 9:
            D_01080A38[44] = 1;
            D_01080A38[45] = 1;
            D_01080A38[46] = 1;
            D_01080A38[47] = 1;
            break;
        }
        break;
    }
    D_00F9B74C = f;
}
