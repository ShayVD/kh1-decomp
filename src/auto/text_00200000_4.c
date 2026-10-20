/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011fbb0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_001fc308(s32, s32, s32, s32, s32, s32, M2C_UNK, s32, s32);
extern M2C_UNK D_003F2C50;
extern M2C_UNK D_003F2EAC;
extern M2C_UNK D_003F2F88;
extern M2C_UNK D_003F2FB0;
extern M2C_UNK D_003F2FD8;
extern M2C_UNK D_003F3010;
extern M2C_UNK D_003F3530;
extern M2C_UNK D_00641080; /* src/data/bss_0064.c: u8 D_00641080[0xb0] */
extern M2C_UNK D_00641130; /* src/data/bss_0064.c: u8 D_00641130[0xb0] */
extern s32 D_002BCC94;
extern s8 D_003F2C40;
s32 func_001edd88(s32, s32);
s32 func_001ee768(s32);
s32 func_001efc10(s32);
s32 func_001f1fc8(s32, s32, s32, s32, s32, s32);
s32 func_00203a10(s32, s32);
s32 func_00207a38(s32);
void func_00121eb0(s32);
void func_00162110(s32, s32);
void func_001f9010(s32);
void func_001f9270(s32, s32, s32, s32, s32, s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
void func_00200648(s32, s32, s32, s32, s32, s32);
void func_00200e28(s32, s32, s32, s32, s32);
void func_00206130(s32, s32, s32, s32, s32, s32);

void func_002014a0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, s32 arg_sp8) {
    u32 temp_a3;

    func_00200648(arg0, arg1, arg3, arg4, arg5, arg7);
    temp_a3 = 0x1A - arg_sp8;
    func_001f9438(arg0, arg2, arg6, arg4 + ((s32) (temp_a3 + (temp_a3 >> 0x1F)) >> 1), arg_sp0, arg_sp8, M2C_FIELD(arg7, s32 *, 0x10));
}

s32 func_002040a0(s32 arg0) {
    return func_00203a10(arg0, ((s32) (M2C_FIELD(arg0, u16 *, 0xBE) << 0x10) >> 0x14) - 0x10);
}

void func_00206690(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00206130(arg0, arg1, arg2, arg3, 2, 0x80F04646);
}

void func_00207560(s32 arg0, s32 arg1, s32 arg2) {
    func_001f9438(arg0, 0, arg1, arg2, 0x1D1, 0x14, 0x8080FFFF);
}

void func_00207748(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s4;
    void *temp_s0;

    temp_s0 = &D_003F2C40 + (arg0 * 0x14);
    func_00200e28(2, arg1, arg2, arg3, (s32) temp_s0);
    temp_s4 = M2C_FIELD(temp_s0, s32 *, 0x10);
    func_001f1fc8(2, temp_s4, arg1 + ((s32) (arg3 + ((u32) arg3 >> 0x1F)) >> 1), arg2 + 5, func_001efc10(0x2B), 0xF);
}

void func_002077f0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_00200648(arg0, arg2, arg3, arg4, arg5, (s32) (&D_003F2C40 + (arg1 * 0x14)));
}

void func_00207c28(s32 arg0, s32 arg1) {
    func_001f9270(arg0, 0, 0x10, 0x30, 0xC, 0x801EC8C8);
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xE, 0x22, arg1, 0xF, 0x80E6E6E6);
    func_00207a38(arg0);
}

s32 func_00207ca0(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_003F2C50 + (arg0 * 0x14));
}

void func_00208280(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_v0;

    temp_v0 = func_001edd88(*(M2C_UNK *)((s8 *)&D_003F2EAC + (arg4 * 4)), arg5);
    func_001fc308(arg0, arg1, arg2, arg3, arg3, arg4, 0, temp_v0, temp_v0);
}

void func_00208310(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_s1;
    s32 temp_v0;

    temp_s1 = arg4 * 4;
    temp_v0 = func_001edd88(*(M2C_UNK *)((s8 *)&D_003F2FB0 + temp_s1), arg5);
    func_001fc308(arg0, arg1, arg2, arg3, arg3, *(M2C_UNK *)((s8 *)&D_003F2F88 + temp_s1), 0, temp_v0, temp_v0);
}

void func_002083a8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_s0;
    s32 temp_v0;

    if (arg4 != 0) {
        temp_s0 = func_001ee768(arg4) * 4;
        temp_v0 = func_001edd88(*(M2C_UNK *)((s8 *)&D_003F3010 + temp_s0), arg5);
        func_001fc308(arg0, arg1, arg2, arg3, arg3, *(M2C_UNK *)((s8 *)&D_003F2FD8 + temp_s0), 0, temp_v0, temp_v0);
    }
}

void func_0020a1d8(void) {
    s8 *var_s0;
    s32 temp_v0;
    s32 var_s1;

    var_s0 = &D_003F3530;
    var_s1 = 3;
    do {
        if (M2C_FIELD(var_s0, s32 *, 0xCC) != 0) {
            func_00162110(M2C_FIELD(var_s0, s32 *, 0), (s32) (var_s0 + 0x14));
            temp_v0 = M2C_FIELD(var_s0, s32 *, 0xC0);
            if (temp_v0 != 0) {
                func_00121eb0(temp_v0);
            }
        }
        var_s1 -= 1;
        var_s0 += 0xD0;
    } while (var_s1 >= 0);
}

void func_0020b338(void) {
    func_0011fbb0(0x3600, 2, 0x13, 0, 0, 0x68, 0x38, 0x16C, D_002BCC94 + 0x40, &D_00641080);
    func_0011fbb0(0x3640, 1, 0, 0, 0, 0x10, 0x10, 0x40, D_002BCC94 + 0x1700, &D_00641130);
}
#include "data/data_002B.h"
