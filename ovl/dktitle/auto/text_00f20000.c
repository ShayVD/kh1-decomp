/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_0010c150();
M2C_UNK func_0010c1b8(void (*)());
M2C_UNK func_001116b0(M2C_UNK, M2C_UNK);
M2C_UNK func_0011c7c0(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0011cbe0(M2C_UNK, s32, M2C_UNK, M2C_UNK *);
M2C_UNK func_0011cdf0(M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_0011d1a8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_001f9438(s32, M2C_UNK, s32, s32, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0024e640(s32, M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_00f21068();
M2C_UNK func_00f21928();
M2C_UNK func_00f21ca0();
M2C_UNK func_00f22238();
M2C_UNK func_00f237f8();
M2C_UNK func_00f23990(s32, s32, s32);
M2C_UNK sceGsExecLoadImage(M2C_UNK *, s32);
M2C_UNK sceGsSetDefLoadImage(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK (*D_0046A6A0)();
extern M2C_UNK D_002BC1B0;
extern M2C_UNK D_002BC210;
extern M2C_UNK D_00F27600;
extern M2C_UNK D_00F27680;
extern M2C_UNK func_00f236b0;
extern M2C_UNK func_00f23760;
extern M2C_UNK func_00f26378;
extern s32 D_0046A614;
extern s32 D_00F26E30;
extern s32 D_00F26E38;
extern s32 D_00F2C6F0;
extern s32 D_00F2C6F4;
extern s32 D_00F2C708;
extern s32 D_00F2C898;
extern s32 D_00F2C8A0;
extern s32 D_00F2C8EC;
extern s32 D_00F2C8F0;
extern s32 D_00F2C8F4;
extern s32 D_00F2C8FC;
extern u32 D_002C5AD8;
extern u32 D_002C5AE0;
extern volatile s32 D_002BC060[];
s32 func_001efe68(s32);
u32 func_001f0118(s32, M2C_UNK);

s32 func_00f20000(void) {
    func_00f237f8();
    return 0;
}

void func_00f20020(void) {
    D_00F2C6F0 = 0;
    D_00F2C6F4 = 0;
}

void func_00f20198(void) {
    func_0011c7c0(0, 0, 0xA0);
    func_0011d1a8(0x4E49, 0, 0xA0);
}

void func_00f208f0(s32 arg0) {
    sceGsSetDefLoadImage(&D_002BC1B0, 0x2600, 8, 0, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_002BC1B0, arg0);
    sceGsSetDefLoadImage(&D_002BC210, 0x2C00, 8, 0, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_002BC210, arg0 + 0x60000);
}

void func_00f209b0(s32 arg0) {
    sceGsSetDefLoadImage(&D_00F27600, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_00F27600, arg0);
    sceGsSetDefLoadImage(&D_00F27680, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_00F27680, arg0 + 0x48000);
}

void func_00f20a78(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_a0;
    void *temp_v0;

    temp_a0 = arg0 + 0x10;
    temp_v0 = temp_a0 + M2C_FIELD(temp_a0, u16 *, 0xC);
    *(M2C_UNK *)arg1 = temp_v0;
    *(M2C_UNK *)arg2 = (void *) (temp_v0 + M2C_FIELD(temp_a0, s32 *, 8));
}

void func_00f20da0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

void func_00f227b0(void) {
    func_00f21068();
    func_00f21ca0();
    func_00f21928();
    func_00f22238();
}

void func_00f227e0(void) {
    D_00F2C708 += 1;
}

void func_00f227f8(void) {
    func_001116b0(1, 0);
    func_001116b0(3, 0);
    func_001116b0(4, 0);
    func_001116b0(0xB, 0);
    func_001116b0(5, 0);
    func_001116b0(9, 0);
    func_001116b0(0xC, 2);
    func_001116b0(0xA, 0);
    func_001116b0(0xF, 0);
    func_001116b0(8, 2);
}

void func_00f22880(void) {
    D_002BC060[3] = 0x80;
    D_002BC060[2] = 0;
    D_002BC060[1] = 0;
    D_002BC060[0] = 0;
}

void func_00f228a0(void) {
    D_002BC060[3] = 0x80;
    D_002BC060[0] = 0xF5;
    D_002BC060[2] = 0xF5;
    D_002BC060[1] = 0xF5;
}

void func_00f23738(s32 arg0, s32 arg1, s32 arg2) {
    func_0011cbe0(0, arg2, 0x6E, &func_00f236b0);
}

void func_00f23790(s32 arg0, s32 arg1, s32 arg2) {
    func_0011cdf0(-8, arg2, &func_00f23760);
}

void func_00f23838(s32 arg0, s32 arg1, s32 arg2) {
    D_00F2C8EC = arg0;
    D_00F2C8F0 = arg1;
    D_00F2C8F4 = arg2;
}

void func_00f23d28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s0_2;
    u32 temp_s0;
    u32 temp_v0;

    temp_s0 = (func_001efe68(arg1) * 0x1E) - 0xF;
    temp_s0_2 = temp_s0 + (temp_s0 >> 0x1F);
    func_00f23990(arg0, arg2, arg4);
    temp_v0 = func_001f0118(arg1, 0xF);
    func_001f9438(arg0, 0, 0x100 - ((s32) ((temp_v0 >> 0x1F) + temp_v0) >> 1), 0xBF - (temp_s0_2 >> 1), arg1, 0xF, 0x80FFFFFF);
}

s32 func_00f24a58(void) {
    return D_002C5AD8 | (((u32) D_002C5AD8 >> 0x18) & 0xF0);
}

s32 func_00f24a70(void) {
    return D_002C5AE0 | (((u32) D_002C5AE0 >> 0x18) & 0xF0);
}

void func_00f24b28(void) {
    D_0046A6A0();
    D_00F2C8FC = 1;
    func_0010c1b8(func_00f24b28);
}

s32 func_00f25500(void) {
    return (((u32) (D_00F26E38 + 0xFFFFF) >> 0x14) + 0x7F) & 0x1F80;
}

void func_00f25c28(void) {
    func_0010c150();
}

void func_00f26520(void) {
    func_0024e640(D_00F26E30, 0x20000, &func_00f26378, 0);
    D_0046A614 = 0x1F4;
    func_0010c1b8(func_00f26520);
    D_00F2C898 = 1;
}

void func_00f26638(s32 arg0) {
    D_00F2C8A0 = arg0;
}

void func_00f26c88(void) {

}

s32 func_00f26c90(void) {
    return 3;
}
