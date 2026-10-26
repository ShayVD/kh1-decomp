/* xs_mushu.x func_00f20ff8: matched by hand. */
#include "ovl.h"

extern s32 D_00304B78;
extern s32 D_00F21398;
void func_002414a8(s32, s32);
void func_0012cab8(s32);
void func_00242b68(s32);
void func_00f20ff8(s32 arg0) {
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
    D_00F21398 = arg0;
}
