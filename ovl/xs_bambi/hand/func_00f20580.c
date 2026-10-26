/* xs_bambi.x func_00f20580: matched by hand (session 131b). */
#include "ovl.h"

extern s32 D_00304B78;
extern s32 D_00F20908;
void func_002414a8(s32, s32);
void func_0012cab8(s32);
void func_00242b68(s32);
void func_00f20580(s32 arg0) {
    switch (arg0) {
    case 100:
        func_002414a8(3, 0);
        D_00304B78 &= ~8;
        break;
    case 101:
        func_0012cab8(0);
        func_00242b68(3);
        break;
    }
    D_00F20908 = arg0;
}
