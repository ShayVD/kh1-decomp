/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK _puts_r(s32, s32);
M2C_UNK _raise_r(s32, s32);
M2C_UNK func_00255708(s32);
M2C_UNK func_002560b8(s32, s32, s32);
M2C_UNK func_002575b0(s32);
M2C_UNK func_00257620(s32, s32, s32);
M2C_UNK func_00257778(s32, s32);
M2C_UNK func_00258930();
M2C_UNK func_0025f398();
M2C_UNK func_0025f4b0();
M2C_UNK func_0025f6d0();
M2C_UNK func_0025fa88();
M2C_UNK func_0025fc38();
M2C_UNK func_00260938();
extern M2C_UNK D_00491F88;
extern M2C_UNK func_00257910;
extern M2C_UNK func_00257978;
extern M2C_UNK func_002579f8;
extern M2C_UNK func_00257a60;
extern s32 D_0046A9C8;
extern s32 D_0046AE28;
extern s32 D_0046AE2C;
extern s32 D_0046AE44;
extern s32 D_0046AF10;
extern s32 D_00494028;
s32 func_0024f7e8(s32, s32);
s32 func_00255c40();
s32 func_00256510(s32, s32);
s32 func_00258860(s32);
s32 func_00258918(s32, s32);
s32 func_00258938(s32, s32);
s32 sceSifGetReg(M2C_UNK);
void SignalSema(s32);
void func_0025e4f0(s32, s32, s32, s32);
void func_0025eb00(s32, s32, s32, s32, s32);
void memset(s32, s32, s32);

void __malloc_unlock(void) {
    s32 temp_v0;

    temp_v0 = D_0046AE2C - 1;
    D_0046AE2C = temp_v0;
    if (temp_v0 == 0) {
        D_0046AE28 = -1;
        SignalSema(D_0046AF10);
    }
}

s32 func_00250dd0(s32 arg0, s32 arg1) {
    s32 temp_v0;

    D_00494028 = 0;
    temp_v0 = func_00258860(arg1);
    if ((temp_v0 == -1) && (D_00494028 != 0)) {
        *(M2C_UNK *)arg0 = (s32) D_00494028;
    }
    return temp_v0;
}

s32 func_002515b8(s32 arg0, void *arg1) {
    s32 temp_v0;

    if (M2C_FIELD(arg1, s32 *, 8) == 0) {
        M2C_FIELD(arg1, s32 *, 4) = 0;
        return 0;
    }
    temp_v0 = func_00255c40();
    M2C_FIELD(arg1, s32 *, 8) = 0;
    M2C_FIELD(arg1, s32 *, 4) = 0;
    return temp_v0;
}

s32 func_00252328(s32 arg0, void *arg1) {
    s32 temp_v0;

    if (M2C_FIELD(arg1, s32 *, 8) == 0) {
        M2C_FIELD(arg1, s32 *, 4) = 0;
        return 0;
    }
    temp_v0 = func_00255c40();
    M2C_FIELD(arg1, s32 *, 8) = 0;
    M2C_FIELD(arg1, s32 *, 4) = 0;
    return temp_v0;
}

M2C_UNK *func_00256148(void) {
    return &D_00491F88;
}

void func_00256158(s32 arg0, s32 arg1) {
    func_002560b8(D_0046A9C8, arg0, arg1);
}

void func_002565b8(void *arg0, void *arg1) {
    void **temp_v0;

    if (arg1 != NULL) {
        temp_v0 = (M2C_FIELD(arg1, s32 *, 4) * 4) + M2C_FIELD(arg0, s32 *, 0x4C);
        M2C_FIELD(arg1, void **, 0) = (void *) *temp_v0;
        *temp_v0 = arg1;
    }
}

s32 func_00256960(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_00256510(arg0, 1);
    M2C_FIELD(temp_v0, s32 *, 0x14) = arg1;
    M2C_FIELD(temp_v0, s32 *, 0x10) = 1;
    return (s32) temp_v0;
}

void raise(s32 arg0) {
    _raise_r(D_0046A9C8, arg0);
}

void func_00257830(s32 arg0, s32 arg1) {
    func_00257620(D_0046A9C8, arg0, arg1);
}

void func_00257858(void) {
    func_002575b0(D_0046A9C8);
}

void func_00257878(s32 arg0) {
    func_00257778(D_0046A9C8, arg0);
}

s32 func_00257898(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    D_00494028 = 0;
    temp_v0 = func_00258938(arg1, arg2);
    if ((temp_v0 == -1) && (D_00494028 != 0)) {
        *(M2C_UNK *)arg0 = (s32) D_00494028;
    }
    return temp_v0;
}

void func_002578f8(void) {
    func_00258930();
}

s32 func_00257bf0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    D_00494028 = 0;
    temp_v0 = func_00258918(arg1, arg2);
    if ((temp_v0 == -1) && (D_00494028 != 0)) {
        *(M2C_UNK *)arg0 = (s32) D_00494028;
    }
    return temp_v0;
}

void func_002585e0(void) {
    D_0046AE44 = 0;
}

s32 func_00258848(void) {
    return -1;
}

s32 func_00258850(void) {
    return -1;
}

s32 func_00258858(void) {
    return -1;
}

s32 func_00258910(void) {
    return 1;
}

void func_0025eac0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    func_0025e4f0(arg0, arg1, arg2, (s32) sp);
}

void func_0025ed28(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    func_0025eb00(arg0, arg1, arg2, (s32) sp, 0);
}

s32 func_0025f1c8(void) {
    if ((sceSifGetReg(4) & 0x10000) != 0) {
        return 1;
    }
    return 0;
}

void func_0025f5c0(void) {
    func_0025f398();
    func_0025f4b0();
    func_0025fa88();
    func_0025fc38();
    func_0025f6d0();
    func_00260938();
}
