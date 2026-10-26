/* dktitle.x func_00f21928: matched by hand. */
#include "ovl.h"

extern s32 D_002B6478;
extern s32 D_00F2C700, D_00F2C70C, D_00F2C710, D_00F2C714, D_00F2C718, D_00F2C71C, D_00F2C720, D_00F2C724;
extern s32 D_00F2C728, D_00F2C72C, D_00F2C730, D_00F2C854, D_00F2C858, D_00F2C85C;
void func_00f21928(void) {
    if (D_002B6478 == 0) {
        D_00F2C70C = 276;
        D_00F2C710 = 312;
        D_00F2C854 = 348;
        switch (D_00F2C700) {
        case 0:
            D_00F2C730 = 274;
            D_00F2C718 = 6; D_00F2C71C = 274;
            D_00F2C720 = 8; D_00F2C724 = 310;
            D_00F2C858 = 8; D_00F2C85C = 346;
            break;
        case 1:
            D_00F2C730 = 310;
            D_00F2C718 = 8; D_00F2C71C = 274;
            D_00F2C720 = 6; D_00F2C724 = 310;
            D_00F2C858 = 8; D_00F2C85C = 346;
            break;
        case 2:
            D_00F2C730 = 346;
            D_00F2C718 = 8; D_00F2C71C = 274;
            D_00F2C720 = 8; D_00F2C724 = 310;
            D_00F2C858 = 6; D_00F2C85C = 346;
            break;
        }
    } else {
        D_00F2C70C = 272;
        D_00F2C710 = 298;
        D_00F2C854 = 324;
        D_00F2C714 = 350;
        switch (D_00F2C700) {
        case 0:
            D_00F2C730 = 270;
            D_00F2C718 = 6; D_00F2C71C = 270;
            D_00F2C720 = 8; D_00F2C724 = 296;
            D_00F2C858 = 8; D_00F2C85C = 322;
            D_00F2C728 = 8; D_00F2C72C = 348;
            break;
        case 1:
            D_00F2C730 = 296;
            D_00F2C718 = 8; D_00F2C71C = 270;
            D_00F2C720 = 6; D_00F2C724 = 296;
            D_00F2C858 = 8; D_00F2C85C = 322;
            D_00F2C728 = 8; D_00F2C72C = 348;
            break;
        case 2:
            D_00F2C730 = 322;
            D_00F2C718 = 8; D_00F2C71C = 270;
            D_00F2C720 = 8; D_00F2C724 = 296;
            D_00F2C858 = 6; D_00F2C85C = 322;
            D_00F2C728 = 8; D_00F2C72C = 348;
            break;
        case 3:
            D_00F2C730 = 348;
            D_00F2C718 = 8; D_00F2C71C = 270;
            D_00F2C720 = 8; D_00F2C724 = 296;
            D_00F2C858 = 8; D_00F2C85C = 322;
            D_00F2C728 = 6; D_00F2C72C = 348;
            break;
        }
    }
}
