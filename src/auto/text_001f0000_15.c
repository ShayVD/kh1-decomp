/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_001f9378(s32, s32, s32, s32, s32, s32);
s32 func_001f9398(s32, s32, s32, s32, s32, s32);
s32 func_001f93b8(s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(s32, s32, s32, s32, s32, s32, s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
void func_001f9e48(s32, s32, s32, s32, s32, s32, s32);

void func_001f9138(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 temp_v0;

    temp_v0 = 0x14 - arg2;
    func_001f9438(arg0, 2, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x15, ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) + 2, arg1, arg2, arg3);
}

s32 func_001f9180(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 temp_v0;

    temp_v0 = 0x14 - arg2;
    return func_001f94f0(arg0, 2, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x15, ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) + 2, arg1, arg2, arg3);
}

void func_001f91c8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 temp_v0;

    temp_v0 = 0x14 - arg2;
    func_001f9e48(arg0, 2, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x15, ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) + 2, arg1, arg2, arg3);
}

s32 func_001fa718(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_001f9378(arg0, 2, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x15, arg1, arg2, arg3);
}

s32 func_001fa748(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_001f9398(arg0, 2, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x15, arg1, arg2, arg3);
}

s32 func_001fa778(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_001f93b8(arg0, 2, (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x15, arg1, arg2, arg3);
}
