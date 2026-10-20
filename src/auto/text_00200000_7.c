/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_002073b0(M2C_UNK, void *);
M2C_UNK func_00209e18();
M2C_UNK func_0020a9b0(s32);
M2C_UNK func_0020ab88(s32);
M2C_UNK func_0020b120(M2C_UNK, s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0020be10(M2C_UNK);
M2C_UNK func_002660c0(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsExecStoreImage(M2C_UNK *, s32 *);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK D_003F3258;
extern M2C_UNK D_003F34B0;
extern s32 D_00640E24;
extern s32 D_00640E28;
extern u32 D_003E3D68;
s32 func_001f94f0(s32, s32, s32, s32, s32, s32, s32);
s32 func_00202678(s32, s32, s32);
s32 func_00203a10(s32, s32);
s32 func_00207358(void);
s32 func_002079c8(s32);
s32 func_0020ec50(s32);
s32 func_0020f530(s32);
s32 func_0020fc58(s32);
void func_001f9010(s32);
void func_001f9270(s32, s32, s32, s32, s32, s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
void func_001f9e48(s32, s32, s32, s32, s32, s32, s32);
void func_00200648(s32, s32, s32, s32, s32, s32);
void func_00206130(s32, s32, s32, s32, s32, s32);
void func_00206e28(void);
void func_00206f20(void);
void func_00206ff0(void);
void func_002070c0(void);
void func_002071b8(void);
void func_00207288(void);
void func_00208458(s32, s32, s32, s32, s32);
void func_0020be68(s32, s32, s32);
void func_00211398(void);
void func_00213d30(void);
void func_00216140(void);
void func_00217fe8(void);
void func_00219118(void);
void func_0021adc8(void);
void func_0021db30(void);
void func_00229850(void);

void func_00201550(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, s32 arg_sp8) {
    u32 temp_a3;

    func_00200648(arg0, arg1, arg3, arg4, arg5, arg7);
    temp_a3 = 0x1A - arg_sp8;
    func_001f94f0(arg0, arg2, arg6, arg4 + ((s32) (temp_a3 + (temp_a3 >> 0x1F)) >> 1), arg_sp0, arg_sp8, M2C_FIELD(arg7, s32 *, 0x10));
}

void func_00201600(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, s32 arg_sp8) {
    u32 temp_a3;

    func_00200648(arg0, arg1, arg3, arg4, arg5, arg7);
    temp_a3 = 0x1A - arg_sp8;
    func_001f9e48(arg0, arg2, arg6, arg4 + ((s32) (temp_a3 + (temp_a3 >> 0x1F)) >> 1), arg_sp0, arg_sp8, M2C_FIELD(arg7, s32 *, 0x10));
}

void func_00202fc0(s32 arg0) {
    func_00202678(arg0, ((s32) (M2C_FIELD(arg0, u16 *, 0xBE) << 0x10) >> 0x14) - 0x10, 0x80C8C8C8);
}

s32 func_00202ff0(s32 arg0) {
    return func_00202678(arg0, ((s32) (M2C_FIELD(arg0, s16 *, 0xBE) + M2C_FIELD(arg0, s16 *, 0xC2)) >> 4) + 4, 0x80C8C8C8);
}

void func_002040c8(s32 arg0) {
    func_00203a10(arg0, ((s32) (M2C_FIELD(arg0, s16 *, 0xBE) + M2C_FIELD(arg0, s16 *, 0xC2)) >> 4) + 4);
}

void func_00206110(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_00206130(arg0, arg1, arg2, arg3, arg4, 0x80F04646);
}

void func_002066e8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00206130(arg0, arg1, arg2, 2, arg3, 0x80F04646);
}

void func_00207618(void) {
    func_0020be10(0x10);
}

s32 func_00207b38(s32 arg0, s32 arg1) {
    func_001f9270(arg0, 0, 0x10, 0x32, 0xC, 0x801EC8C8);
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xE, 0x22, arg1, 0xF, 0x80E6E6E6);
    return func_002079c8(arg0);
}

s32 func_00207bb0(s32 arg0, s32 arg1) {
    func_001f9270(arg0, 0, 0x10, 0x31, 0xC, 0x801EC8C8);
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xE, 0x22, arg1, 0xF, 0x80E6E6E6);
    return func_002079c8(arg0);
}

void func_0020a8f0(void) {
    s32 sp[184];
    func_002660c0(sp, 0, 8, 0, 0x100, 4, 0x10, 1);
    func_002660c0(&M2C_FIELD(sp, M2C_UNK *, 0x70), 0, 8, 0, 0x100, 0x1BB, 0x10, 1);
    FlushCache(0);
    sceGsExecStoreImage(sp, &M2C_FIELD(sp, s32 *, 0xE0));
    sceGsExecStoreImage(&M2C_FIELD(sp, M2C_UNK *, 0x70), &M2C_FIELD(sp, s32 *, 0x1E0));
    sceGsSyncPath(0, 0);
    M2C_FIELD(&D_003F34B0, s32 *, 0) = (s32) (M2C_FIELD(sp, s32 *, 0xE0) & 0xFFFFFF);
    M2C_FIELD(&D_003F34B0, s32 *, 4) = (s32) (M2C_FIELD(sp, s32 *, 0x1E0) & 0xFFFFFF);
}

void func_0020c100(s32 arg0, s32 arg1) {
    func_00208458(arg0, 0, 0, 0x802020A0, 1);
    func_0020be68(arg0, 0x69, arg1);
}

void func_0020c150(void) {
    func_00209e18();
}

void func_0020c168(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, *(M2C_UNK *)((s8 *)(s8 *)&D_003F3258 + (D_00640E28 * 4)), 0x11, 0x80C87850);
}

void func_0020cf00(void *arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x90);
    func_0020b120(2, temp_s0, 0x80080808, 0x80080808, 0x80080808, 0x80080808);
    func_0020b120(1, temp_s0, 0x80101010, 0x80101010, 0x80101010, 0x80101010);
    func_0020b120(2, temp_s0, 0x80080808, 0x80080808, 0x80080808, 0x80080808);
    func_0020a9b0(temp_s0);
    func_0020ab88(temp_s0);
}

void func_0020d748(void) {
    D_00640E24 = 0;
    D_00640E28 = 0;
    func_00211398();
    func_00213d30();
    func_00216140();
    func_00217fe8();
    func_00219118();
    func_0021adc8();
    func_0021db30();
    func_00229850();
    func_00206e28();
    func_00206f20();
    func_00206ff0();
    func_002070c0();
    func_002071b8();
    func_00207288();
    func_00207358();
}

s32 func_0020fea0(s32 arg0) {
    u32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, u32 *, 0x24);
    if (temp_a1 < (u32) D_003E3D68) {
        return func_0020ec50(arg0);
    }
    if (temp_a1 == D_003E3D68) {
        return func_0020f530(arg0);
    }
    return func_0020fc58(arg0);
}

void func_0020fee8(void *arg0) {
    if (((u32) D_003E3D68 < (u32) M2C_FIELD(arg0, u32 *, 0x24)) && (M2C_FIELD(arg0, s32 *, 0x28) != 0)) {
        func_002073b0(1, arg0);
    }
}
#include "data/bss_0064_mixed.h"
