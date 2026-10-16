/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK D_00F20000(M2C_UNK, s32);
M2C_UNK func_00101628();
M2C_UNK func_0010b030(s32);
M2C_UNK func_0010e750();
M2C_UNK func_001124f8();
M2C_UNK func_00112928();
M2C_UNK func_0011cdf0(M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_00122198(s32, M2C_UNK *);
M2C_UNK func_00146928(M2C_UNK);
M2C_UNK func_0014a090();
M2C_UNK func_001559f0(M2C_UNK, M2C_UNK);
M2C_UNK func_001ec7d0(M2C_UNK);
M2C_UNK func_001ed128(M2C_UNK, M2C_UNK);
extern M2C_UNK func_00112820;
extern M2C_UNK func_00113688;
extern s32 D_002A3F38;
extern s32 D_002BCDE0;
extern s32 D_002BCDF0;
f32 func_00113518();
s32 func_001137c8(s32, M2C_UNK);

void func_00111170(s32 arg0) {
    D_00F20000(6, arg0);
}

void func_00112840(s32 arg0, s32 arg1, s32 arg2) {
    func_001ec7d0(2);
    func_001ed128(3, -9);
    func_00101628();
    func_001ed128(0, -1);
    func_001ed128(3, -1);
    func_001ed128(0, 0);
    func_001ed128(0, 1);
    func_001ed128(1, 0);
    func_001ed128(1, 1);
    func_0014a090();
    func_00146928(-3);
    func_00146928(-4);
    func_00146928(-5);
    func_00146928(-6);
    func_00146928(-7);
    func_001ed128(0, -8);
    func_001ed128(3, -8);
    func_001ed128(3, -0xA);
    func_0011cdf0(-1, arg2, &func_00112820);
}

void func_00112968(void) {
    func_001124f8();
    func_0010e750();
    func_0010b030(D_002BCDE0);
    D_002A3F38 = D_002BCDE0;
    D_002A3F38 = func_001137c8(D_002BCDE0, 0x40);
    func_00112928();
}

void func_00113008(void) {
    func_001559f0(0x3D, 3);
}

void func_00113028(void) {
    func_001559f0(0, 0x40);
}

void func_001136a8(void) {
    func_00113518();
    func_00122198(D_002BCDF0, &func_00113688);
}
