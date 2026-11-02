/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001bb7c8(M2C_UNK *, s32);
M2C_UNK func_001c0310(M2C_UNK, M2C_UNK *, s32, s32);
M2C_UNK func_001c0688();
M2C_UNK func_00f309d0(M2C_UNK);
M2C_UNK func_00f44000();
M2C_UNK func_00f44078();
M2C_UNK func_00f50548(s32);
M2C_UNK func_00f50568(s32);
M2C_UNK func_00f50610(s32);
M2C_UNK func_00f55330(s32);
M2C_UNK func_00f59848(M2C_UNK, M2C_UNK);
M2C_UNK func_00f59870(M2C_UNK, s32, s32, s32, s32);
extern M2C_UNK *D_003773A4;
extern M2C_UNK *D_003773A8;
extern M2C_UNK *D_003773D0;
extern M2C_UNK *D_003773D4;
extern M2C_UNK *D_003773D8;
extern M2C_UNK *D_003773E8;
extern M2C_UNK D_00F9B548;
extern M2C_UNK D_00FB7668;
extern M2C_UNK D_00FB7678;
extern M2C_UNK D_00FB7688;
extern M2C_UNK D_01080838;
extern M2C_UNK D_01080B10;
extern M2C_UNK D_0108BD00;
extern M2C_UNK func_00f45508;
extern M2C_UNK func_00f45c90;
extern M2C_UNK func_00f4d038;
extern M2C_UNK func_00f4d058;
extern M2C_UNK func_00f4d0e0;
extern M2C_UNK func_00f4d108;
extern M2C_UNK func_00f4d138;
extern M2C_UNK func_00f4d218;
extern s32 D_00F9B2EC;
extern s32 D_00F9B500;
extern s32 D_00F9B504;
extern s32 D_010809C8;
extern s32 D_01080B04;
extern s32 D_01080B08;
s32 func_00f40c98();
s32 func_00f41448();
s32 func_00f43fd8(s32);
s32 func_00f4cfb8(M2C_UNK);
s32 func_00f62b90(s32);
s32 func_00f64c38(s32, s32);
void func_001bfac8(void);
void func_00f471f8(void);
void func_00f59930(M2C_UNK *, s32);
void func_00f5e178();
void func_00f680a0(void);

s32 func_00f43d88(s32 arg0) {
    if (func_00f40c98() < 2) {
        return func_00f62b90(arg0);
    }
    return 0;
}

s32 func_00f44e78(s32 arg0, s32 arg1) {
    *(M2C_UNK *)((s8 *)(s8 *)&D_01080838 + (arg0 * 4)) = arg1;
    return func_00f43fd8(arg0);
}

void func_00f451f8(s32 arg0, s32 arg1, s32 arg2) {
    func_00f44078(arg0, arg1, arg2);
}

void func_00f45210(s32 arg0, s32 arg1) {
    func_00f44000(arg0, arg1);
}

void func_00f45520(s32 arg0, s32 arg1) {
    func_001c0310(-1, &func_00f45508, arg1, arg0);
}

void func_00f45dc8(s32 arg0, s32 arg1) {
    func_001c0310(-1, &func_00f45c90, arg0, arg1);
}

void func_00f46c78(s32 arg0) {
    func_001c0688(arg0);
    if ((func_00f41448() == 0) && (D_00F9B2EC == 0)) {
        func_00f309d0(0);
    }
}

s32 func_00f471c0(void) {
    func_00f59930(&D_00F9B548, D_010809C8);
    return (D_00F9B500 != 0) ? 0 : 4;
}

void func_00f487a8(void *arg0) {
    func_00f59870(1, 0x80, 0x80, 0x80, M2C_FIELD(arg0, s32 *, 0x24));
    if (M2C_FIELD(arg0, s32 *, 0x24) == 0) {
        func_00f59848(1, 0);
    } else {
        func_00f59848(1, 1);
    }
    func_00f59870(4, M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), 0x80);
    func_00f59870(7, M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, s32 *, 0x14), 0x80);
    func_00f59870(6, M2C_FIELD(arg0, s32 *, 0x18), M2C_FIELD(arg0, s32 *, 0x1C), M2C_FIELD(arg0, s32 *, 0x20), 0x80);
    func_00f55330(M2C_FIELD(arg0, s32 *, 0x28));
    func_00f50610(M2C_FIELD(arg0, s32 *, 0x2C));
    func_00f50548(M2C_FIELD(arg0, s32 *, 0x30));
    func_00f50568(M2C_FIELD(arg0, s32 *, 0x34));
}

void func_00f48c98(void) {
    func_00f471f8();
    D_00F9B500 = 0;
    D_00F9B504 = 0;
    func_00f680a0();
    for (;;) {
        func_001bfac8();
    }
}

s32 func_00f4a958(s32 arg0) {
    return func_00f64c38(arg0, D_01080B04);
}

s32 func_00f4a978(s32 arg0) {
    return func_00f64c38(arg0, D_01080B04) + 0xB0;
}

s32 func_00f4aa00(s32 arg0) {
    return func_00f64c38(arg0, D_01080B08);
}

void func_00f4cb10(void) {
    func_00f5e178();
    M2C_FIELD(&D_01080B10, s32 *, 0) = 0;
    M2C_FIELD(&D_01080B10, s32 *, 4) = 0;
    M2C_FIELD(&D_01080B10, s32 *, 8) = 0;
    M2C_FIELD(&D_01080B10, f32 *, 0xC) = 1.0f;
    M2C_FIELD(&D_01080B10, s32 *, 0x10) = 0;
    M2C_FIELD(&D_01080B10, s32 *, 0x14) = 0;
    M2C_FIELD(&D_01080B10, s32 *, 0x18) = 0;
    M2C_FIELD(&D_01080B10, f32 *, 0x1C) = 1.0f;
}

void func_00f4cfd0(void) {
    func_001bb7c8(&D_00FB7668, func_00f4cfb8(0));
    func_001bb7c8(&D_00FB7678, func_00f4cfb8(1));
    func_001bb7c8(&D_00FB7688, func_00f4cfb8(2));
}

void func_00f4d278(void) {
    D_003773A4 = &func_00f4d058;
    D_003773A8 = &func_00f4d0e0;
    D_003773D8 = &func_00f4d108;
    D_003773D0 = &func_00f4d038;
    D_003773D4 = &func_00f4d138;
    D_003773E8 = &func_00f4d218;
}

void func_00f4fd68(void) {
    s8 *var_v0;
    s32 var_v1;

    var_v1 = 0x13F;
    var_v0 = &D_0108BD00;
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s32 *, 0) = 0;
        M2C_FIELD(var_v0, s32 *, 4) = 0;
        M2C_FIELD(var_v0, s16 *, 8) = 0;
        var_v0 += 0xC;
    } while (var_v1 >= 0);
}
