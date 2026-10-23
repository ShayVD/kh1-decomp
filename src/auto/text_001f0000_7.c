/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_001fade0(s32, s32, s32, s32, s32, s32);
extern s32 D_003F1A60;
s32 func_001eff50(s32);
s32 func_001f5e10(s32);
s32 func_001f86e0(s32, s32, s32, s32, s32);
s32 func_001f92f0(s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(s32, s32, s32, s32, s32, s32, s32);
s32 func_001fa840(s32, s32, s32, s32, s32);
s32 func_001fa878(s32, s32, s32, s32, s32);
void func_001f9270(s32, s32, s32, s32, s32, s32);
void func_001f92b0(s32, s32, s32, s32, s32, s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
void func_001f9e48(s32, s32, s32, s32, s32, s32, s32);
void func_001fa808(s32, s32, s32, s32, s32);
void func_001fcdc8(s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fd5e0(s32, s32);
void func_001fd610(s32, s32);
void func_001fd660(s32, s32);
void func_001ff488(s32, s32, s32, s32, s32, s32);

void func_001f52a8(s32 arg0) {
    func_001ff488(arg0, 0, 0, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x14, (s32) (M2C_FIELD(arg0, u16 *, 0xBA) << 0x10) >> 0x14, M2C_FIELD(arg0, s32 *, 0x6C));
}

void func_001f8150(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x80) = (s32) M2C_FIELD(arg0, s32 *, 0x84);
    func_001f5e10(arg0);
}

void func_001f8e18(s32 arg0) {
    func_001f86e0(arg0, (s32) (M2C_FIELD(arg0, u16 *, 0xBE) << 0x10) >> 0x14, (s32) (M2C_FIELD(arg0, u16 *, 0xC0) << 0x10) >> 0x14, (((s32) (M2C_FIELD(arg0, u16 *, 0xC2) << 0x10) >> 0x14) * M2C_FIELD(arg0, s16 *, 0xD8)) - ((s32) (M2C_FIELD(arg0, u16 *, 0xC6) << 0x10) >> 0x14), (((s32) (M2C_FIELD(arg0, u16 *, 0xC4) << 0x10) >> 0x14) * M2C_FIELD(arg0, s16 *, 0xCE)) - ((s32) (M2C_FIELD(arg0, u16 *, 0xC8) << 0x10) >> 0x14));
}

s32 func_001f8e90(s32 arg0) {
    return func_001f86e0(arg0, (s32) (M2C_FIELD(arg0, u16 *, 0xBE) << 0x10) >> 0x14, 0, (((s32) (M2C_FIELD(arg0, u16 *, 0xC2) << 0x10) >> 0x14) * M2C_FIELD(arg0, s16 *, 0xD8)) - ((s32) (M2C_FIELD(arg0, u16 *, 0xC6) << 0x10) >> 0x14), 0x180);
}

void func_001f8ff0(s32 arg0) {
    D_003F1A60 = arg0;
}

void func_001f9210(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001f9270(arg0, arg1, arg2, arg3, arg4, D_003F1A60);
}

void func_001f9230(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001f92b0(arg0, arg1, arg2, arg3, arg4, D_003F1A60);
}

s32 func_001f9250(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_001f92f0(arg0, arg1, arg2, arg3, arg4, D_003F1A60);
}

void func_001f93d8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_001f9438(arg0, arg1, arg2, arg3, arg4, 0x12, arg5);
}

s32 func_001f93f8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    return func_001f94f0(arg0, arg1, arg2, arg3, arg4, 0x12, arg5);
}

void func_001f9418(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_001f9e48(arg0, arg1, arg2, arg3, arg4, 0x12, arg5);
}

void func_001fa7a8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001fa808(arg0, arg1, arg2, 0x12, arg3);
}

s32 func_001fa7c8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_001fa840(arg0, arg1, arg2, 0x12, arg3);
}

s32 func_001fa7e8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_001fa878(arg0, arg1, arg2, 0x12, arg3);
}

void func_001fb248(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_001fade0(arg0, arg1, arg2, func_001eff50(arg3), arg4, arg5);
}

void func_001fd100(s32 arg0, s32 arg1) {
    func_001fcdc8(arg0, arg1, 0, 0, 0x39, 0, 0x64323296, 0x64323296);
    func_001fcdc8(arg0 + 0xE, arg1 + 6, 0, 0, 0x38, 0, 0x64FFFFFF, 0x64FFFFFF);
}

s32 func_001fd248(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s32 *, 0xB0) - 0x7000) >> 4;
}

void func_001fd420(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001fd660(arg0, arg2);
    func_001fd610(arg0, arg3);
    func_001fd5e0(arg0, arg1);
}

void func_001fd478(s32 arg0, s32 arg1, s32 arg2) {
    func_001fd660(arg0, arg2);
    func_001fd610(arg0, 1);
    func_001fd5e0(arg0, arg1);
}

void func_001fd4c0(s32 arg0, s32 arg1, s32 arg2) {
    func_001fd660(arg0, 1);
    func_001fd5e0(arg0, arg1);
    func_001fd610(arg0, arg2);
}
#include "data/data_003F.h"
