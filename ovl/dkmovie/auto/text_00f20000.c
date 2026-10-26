/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001559f0(M2C_UNK, M2C_UNK);
M2C_UNK func_0024b9e0(M2C_UNK);
M2C_UNK func_0024b9f0(M2C_UNK);
M2C_UNK func_0024e468(M2C_UNK);
M2C_UNK func_002694f8();
M2C_UNK func_00f255f0();
M2C_UNK sceClose();
M2C_UNK sceGsSyncV();
extern M2C_UNK D_0003DF44;
extern M2C_UNK D_00F283D0;
extern M2C_UNK D_00F283E0;
extern M2C_UNK D_00F28420;
extern s16 D_00F28610;
extern s32 D_00F28464;
extern volatile s16 D_00F28478[];
s32 func_0024b9c0();
s32 func_0024b9d0();
s32 func_00f22cf8(s32, s32, s64);

void func_00f20388(void) {
    func_001559f0(0xF, 0x14);
}

void func_00f20aa8(s32 arg0) {
    if (D_00F28610 < *(M2C_UNK *)((s8 *)(s8 *)&D_0003DF44 + arg0)) {
        D_00F28610 = (u16) D_00F28610 + 1;
    }
}

M2C_UNK *func_00f21b88(void) {
    return &D_00F283D0;
}

void func_00f21b98(void) {
    func_0024b9e0(0);
    func_0024b9f0(0);
}

void func_00f21bb8(void) {
    func_0024b9e0(-1);
    func_0024b9f0(-1);
}

void func_00f220b8(void) {
    func_002694f8();
}

s32 func_00f220d0(void) {
    if (func_0024b9d0() == 0) {
        return ((func_0024b9c0() ^ 1) == 0) ? 0 : -1;
    }
    return func_0024b9d0();
}

void func_00f22db0(s32 arg0, s32 arg1, s32 arg2) {
    func_00f22cf8(arg0, 0x52, ((s64) arg2 << 0x20) | ((u64) ((s64) arg1 << 0x20) >> 0x20));
}

void func_00f23140(s64 *arg0, s64 arg1, s64 arg2, s64 arg3) {
    *arg0 = (arg1 << 0x20) | ((u64) (arg2 << 0x20) >> 4) | ((u64) (arg3 << 0x20) >> 0x20);
}

void func_00f23168(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = (s32) (arg1 | 0x10000000);
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

void func_00f23188(s32 arg0) {
    D_00F28464 = arg0;
}

void func_00f23480(void) {
    func_0024e468(1);
}

void func_00f23ae0(void) {

}

void func_00f24fe0(s32 arg0) {
    if (arg0 == 0) {
        sceGsSyncV();
        return;
    }
    func_00f255f0();
    func_0024e468(1);
}

void func_00f255e8(void) {

}

void func_00f26968(s32 arg0, s32 arg1, s32 arg2) {
    s8 *var_a3;
    s32 var_a2;
    u8 *temp_a1;
    u8 temp_v1;

    if (arg2 == 0) {
        var_a3 = &D_00F283E0;
    } else {
        var_a3 = &D_00F28420;
    }
    var_a2 = 0;
    do {
        temp_a1 = arg0 + var_a2;
        temp_v1 = *(var_a3 + var_a2);
        var_a2 += 1;
        *temp_a1 = *(M2C_UNK *)((s32) arg1 + (s32) temp_v1);
    } while (var_a2 < 0x40);
}

void func_00f27670(void) {

}

void func_00f27678(void) {

}

void func_00f279f8(s32 arg0, s32 arg1) {
    D_00F28478[13] = (s16) arg1;
    D_00F28478[12] = (s16) arg0;
}

s32 func_00f27ec8(void) {
    sceClose();
    return 1;
}
