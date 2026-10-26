/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00304B78;
extern s32 D_00F3C9D8;
void func_0012cab8(s32);
void func_002414a8(s32, s32);
void func_00242b68(s32);

void func_00f22e88(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0x64:
        func_002414a8(3, 0);
        D_00304B78 &= ~8;
        break;
    case 0x65:
        func_0012cab8(0);
        func_00242b68(3);
        break;
    }
    D_00F3C9D8 = arg0;
}
