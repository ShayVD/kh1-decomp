/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00304B78;
extern s32 D_00F23208;
extern s32 D_00F233F0;
s32 func_00147ed8(s32, s32, s32, s32);
s32 func_00148968(s32, s32, s32);
s32 func_0014f658(s32, s32);
void func_0012cab8(s32);
void func_001315c0(s32, s32, s32, f32);
void func_002414a8(s32, s32);
void func_00242b68(s32);

s32 func_00f20ac8(s32 arg0) {
    return func_0014f658(arg0, 2);
}

s32 func_00f216f8(s32 arg0) {
    return func_0014f658(arg0, 0);
}

s32 func_00f21a98(s32 arg0) {
    s32 sp[4];
    func_001315c0(arg0, 0x30, (s32) sp, 0.0f);
    return func_00147ed8(D_00F23208, 2, 0x4E20, (s32) sp);
}

s32 func_00f21ad8(s32 arg0) {
    return func_00148968(arg0, D_00F23208, 3);
}

s32 func_00f21af8(s32 arg0) {
    return func_0014f658(arg0, 0);
}

void func_00f22e68(s32 arg0) {
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
    D_00F233F0 = arg0;
}
