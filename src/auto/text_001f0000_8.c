/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f1fc8(M2C_UNK, s32, s32, s32, s32, s32);
M2C_UNK func_001f2630(M2C_UNK, s32, s32, s32, s32, s32);
M2C_UNK func_001f31a8(s32, s32);
M2C_UNK func_001f3520(s32, s32);
M2C_UNK func_001fcdc8(s32, s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
s32 func_001edd88(M2C_UNK, s32);
s32 func_001f94f0(s32, s32, s32, s32, s32, s32, s32);
s32 func_002366d8(M2C_UNK, M2C_UNK);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
void func_001f9e48(s32, s32, s32, s32, s32, s32, s32);

void func_001f1ed8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001f1fc8(0, arg0, arg1, arg2, arg3, arg4);
}

void func_001f1f18(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001f2630(0, arg0, arg1, arg2, arg3, arg4);
}

void func_001f34d0(s32 arg0) {
    func_001f31a8(arg0, func_002366d8(4, 0x36) + 1);
}

void func_001f3570(s32 arg0) {
    func_001f3520(arg0, func_002366d8(4, 0x36) + 1);
}

void func_001f92b0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u32 temp_v0;

    temp_v0 = 0x14 - arg4;
    func_001f94f0(arg0, arg1, arg2, ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) + 2, arg3, arg4, arg5);
}

void func_001f92f0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u32 temp_v0;

    temp_v0 = 0x14 - arg4;
    func_001f9e48(arg0, arg1, arg2, ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) + 2, arg3, arg4, arg5);
}

void func_001fa808(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001f9438(arg0, 2, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x15, arg1, arg2, arg3, arg4);
}

s32 func_001fa840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_001f94f0(arg0, 2, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x15, arg1, arg2, arg3, arg4);
}

void func_001fa878(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001f9e48(arg0, 2, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x15, arg1, arg2, arg3, arg4);
}

void func_001fd170(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s3;
    s32 temp_s3_2;

    temp_s3 = func_001edd88(0x64323296, arg2);
    func_001fcdc8(arg0, arg1, 0, 0, 0x39, 0, temp_s3, func_001edd88(0x64323296, arg2));
    temp_s3_2 = func_001edd88(0x64FFFFFF, arg2);
    func_001fcdc8(arg0 + 0xE, arg1 + 6, 0, 0, 0x38, 0, temp_s3_2, func_001edd88(0x64FFFFFF, arg2));
}
