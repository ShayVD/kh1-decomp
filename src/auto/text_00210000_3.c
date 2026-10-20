/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_0011fbb0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_001f9010(M2C_UNK);
M2C_UNK func_001f9438(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_001f94f0(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00206130(s32, s32, s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0021b800(s32);
extern M2C_UNK D_003F47A8;
extern M2C_UNK D_003F5C90;
extern M2C_UNK D_003F5FF0;
extern M2C_UNK D_00642D30; /* src/data/bss_0064.c: u8 D_00642D30[0xb0] */
extern M2C_UNK D_00642DE0; /* src/data/bss_0064.c: u8 D_00642DE0[0xb0] */
extern M2C_UNK D_00642EB0;
extern M2C_UNK D_00642F60;
extern s32 D_003F34D0;
extern s32 D_003F34E0;
extern s32 D_003F5C20;
s32 D_006430EC ALIGNED(4);
extern s32 D_006430F0;
extern s32 D_006430F8;
extern s32 D_00643100;
extern s32 D_0064311C;
extern s32 D_00643120;
s32 func_00207f80(s32, s32, s32, s32, s32);
void func_002114f0(s32, s32, s32, s32, s32, s32);

void func_002115e0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_002114f0(arg0, arg1, arg2, arg3, arg4, arg5);
    if (arg5 != 0) {
        if (arg6 >= 2) {
            func_00207f80(arg0, arg1, arg2 + arg4 + 4, arg3, arg6);
        }
    }
}

void func_00212768(void *arg0) {
    s32 temp_s1;

    temp_s1 = M2C_FIELD(arg0, s32 *, 0x24);
    if (temp_s1 != 0) {
        func_001f9010(0x17);
        func_001f94f0(arg0, 0, 0xAE, 0xC, temp_s1, 0x11, 0x80C87850);
    }
}

void func_002149f0(void *arg0) {
    s32 temp_s1;

    temp_s1 = M2C_FIELD(arg0, s32 *, 0x24);
    if (temp_s1 != 0) {
        func_001f9010(0x17);
        func_001f94f0(arg0, 0, 0xAE, 0xC, temp_s1, 0x11, 0x80C87850);
    }
}

void func_00216e60(void *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, M2C_FIELD(arg0, s32 *, 0x24), 0x11, 0x80C87850);
}

s32 func_00219440(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_003F47A8 + (arg0 * 4));
}

void func_00219500(void) {
    func_0011fbb0(0x3600, 4, 0x13, 0, 0, 0x8A, 0x58, 0x2F7, D_003F34D0, &D_00642D30);
    func_0011fbb0(0x3680, 1, 0, 0, 0, 0x10, 0x10, 0x40, D_003F34D0 + 0x2F70, &D_00642DE0);
}

void func_0021b4a0(void) {
    D_006430F0 = 0;
    D_006430F8 = -1;
    D_00643100 = 0;
    D_006430EC = 0;
}

void func_0021cb00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg3;
    var_s1 = arg2;
    if (var_s0 > 0) {
        do {
            var_s0 -= 1;
            func_00206130(arg0, arg1, var_s1, 0xC8, 2, 0x40202020);
            var_s1 += arg4;
        } while (var_s0 > 0);
    }
}

void func_0021d188(void) {
    func_0011fbb0(0x3600, 4, 0x13, 0, 0, 0x100, 0x100, 0x1000, D_003F34E0, &D_00642EB0);
    func_0011fbb0(0x3700, 1, 0, 0, 0, 0x10, 0x10, 0x40, D_003F34E0 + 0x10000, &D_00642F60);
}

u16 func_0021dc08(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_003F5C90 + (arg0 * 2));
}

void func_0021fb28(void) {
    D_003F5C20 = 1;
    D_0064311C = -1;
    D_00643120 = -1;
}

void func_0021fd60(s32 arg0) {
    func_0021b800(*(M2C_UNK *)((s8 *)&D_003F5FF0 + (arg0 * 4)) + 0x20);
}
