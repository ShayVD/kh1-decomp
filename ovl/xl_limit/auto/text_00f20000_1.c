/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0012cab8(M2C_UNK);
M2C_UNK func_00131500();
M2C_UNK func_00135848(s32 *);
M2C_UNK func_00f20208();
M2C_UNK func_00f202b8();
M2C_UNK func_00f20940(s64);
M2C_UNK func_00f21b10(s32);
M2C_UNK func_00f22870(s32);
extern M2C_UNK D_00F23290;
extern s32 D_002E26A0;
extern s32 D_002E31B0;
extern s32 D_00F23208;
extern s32 D_00F23E04;
f32 func_00120c88(f32);
s32 func_00122ff8(s32);
s32 func_00147c98(s32, s32, M2C_UNK);
s32 func_00f21208(s32);
s32 func_00f21240(s32, s32);
s32 sceVu0CopyVector(s32, s32);
void func_0013ecf8(s32, s32, s32);
void func_00f21710(s32, f32);

void func_00f20a78(s32 *arg0) {
    func_00131500();
    *arg0 &= 0xFEDFFFFF;
    func_00f20940((s64) 0x807C << 0x2F);
    func_0012cab8(0);
    func_00f202b8();
}

s32 func_00f212f0(s32 arg0, s32 arg1, s32 arg2) {
    if (D_00F23E04 < 7) {
        return func_00f21240(arg0, arg2);
    }
    return func_00f21208(arg0);
}

void func_00f217d0(void) {
    s32 sp[4];
    s32 temp_s1;

    temp_s1 = D_002E26A0;
    if (func_00122ff8(D_002E31B0) != 0) {
        func_0013ecf8(temp_s1, (s32) &D_002E31B0, (s32) sp);
    } else {
        M2C_FIELD(temp_s1, f32 *, 0x150) = func_00120c88(M2C_FIELD(temp_s1, f32 *, 0x3C) + 3.141592979f);
    }
    func_00f21710(temp_s1, 8.0f);
}

void func_00f21a20(s32 *arg0) {
    func_0012cab8(0);
    *arg0 &= 0xFEDFFF7F;
    func_00135848(arg0);
    func_00f20208();
}

void func_00f21d70(void) {
    func_00f21b10(D_002E26A0);
}

void func_00f22540(s32 *arg0) {
    func_00131500();
    *arg0 &= 0xFEDFFF7F;
    func_00f20208();
}

void func_00f22968(s32 arg0) {
    void *temp_s0;

    temp_s0 = (s8 *)&D_00F23290 + (arg0 << 5);
    M2C_FIELD(temp_s0, s32 *, 8) = func_00147c98(D_00F23208, M2C_FIELD(temp_s0, s32 *, 0), 0x4E20);
    func_00f22870(arg0);
}

s32 func_00f23120(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_hi;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 8);
    temp_hi = (s32) ((M2C_FIELD(arg0, s32 *, 0xC) - arg1) + temp_v1) % temp_v1;
    M2C_FIELD(arg0, s32 *, 0x10) = temp_hi;
    return sceVu0CopyVector(arg2, M2C_FIELD(arg0, s32 *, 0) + (temp_hi * 0x10));
}
