/* gb.x func_00f23098: matched by hand. */
#include "ovl.h"

extern u8 D_00F74280[192];
extern s32 D_00F56FC4;
extern f32 D_00F56FCC;
extern s32 D_00F56FD0;

void func_00f23098(s32 mode, s32 k, f32 f) {
    s32 i;
    for (i = 0; i < 192; i++)
        D_00F74280[i] = 0;
    D_00F56FC4 = mode;
    D_00F56FD0 = 0;
    switch (mode) {
    case 4:
        D_00F56FD0 = 1;
        break;
    case 1:
        D_00F74280[k] = 1;
        break;
    case 2:
        break;
    case 3:
        switch (k) {
        case 0:
            D_00F74280[5] = 1;
            D_00F74280[6] = 1;
            D_00F74280[7] = 1;
            D_00F74280[8] = 1;
            break;
        case 1:
            D_00F74280[52] = 1;
            D_00F74280[53] = 1;
            break;
        case 2:
            D_00F74280[48] = 1;
        case 3:
            D_00F74280[58] = 1;
            break;
        case 4:
            D_00F74280[59] = 1;
            break;
        case 5:
            D_00F74280[60] = 1;
            break;
        case 6:
            D_00F74280[61] = 1;
            break;
        case 7:
            D_00F74280[62] = 1;
            break;
        case 8:
            D_00F74280[63] = 1;
            break;
        case 9:
            D_00F74280[44] = 1;
            D_00F74280[45] = 1;
            D_00F74280[46] = 1;
            D_00F74280[47] = 1;
            break;
        }
        break;
    }
    D_00F56FCC = f;
}
