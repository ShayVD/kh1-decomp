/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f3840(s32);
M2C_UNK func_00207830(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0020a9b0(s32);
M2C_UNK func_0020ab88(s32);
M2C_UNK func_0020b120(M2C_UNK, s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0020be10(M2C_UNK);
extern M2C_UNK D_003F6360;
extern M2C_UNK D_003F6788;
extern M2C_UNK D_006436F8;
extern M2C_UNK D_00643700;
extern M2C_UNK func_00223de0;
extern s32 D_003F34A4;
extern s32 D_003F34C0;
extern s32 D_003F34C8;
extern s32 D_003F34FC;
extern s32 D_003F3500;
extern s32 D_003F720C;
extern s32 D_006436F0;
s32 func_00132ec8(s32, s32);
s32 func_001f42b8();
void func_00109268(void);
void func_0020a8f0(void);
void func_0020b968(void);

s32 func_00221428(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_003F6360 + (arg0 * 4));
}

s32 func_00223650(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_003F6788 + (arg0 * 4));
}

void func_00223980(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;

    temp_v1 = arg0 * 4;
    D_006436F0 = arg0;
    *(M2C_UNK *)((s8 *)&D_006436F8 + temp_v1) = arg1;
    *(M2C_UNK *)((s8 *)&D_00643700 + temp_v1) = arg2;
}

void func_00223e10(void) {
    if (D_003F34FC == 0) {
        D_003F34FC = 1;
        D_003F34C8 += 1;
        func_00132ec8(D_003F3500, (s32) &func_00223de0);
    }
}

void func_002282f8(void) {
    func_00109268();
    D_003F34C0 &= ~2;
}

void func_00228e18(s32 arg0) {
    if (func_001f42b8() != 0) {
        func_001f3840(arg0);
        func_0020be10(0x10);
    }
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x165);
}

void func_002292a8(void *arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x90);
    func_0020b120(2, temp_s0, 0x80080808, 0x80080808, 0x80080808, 0x80080808);
    func_0020b120(1, temp_s0, 0x80101010, 0x80101010, 0x80101010, 0x80101010);
    func_0020b120(2, temp_s0, 0x80080808, 0x80080808, 0x80080808, 0x80080808);
    func_0020a9b0(temp_s0);
    func_0020ab88(temp_s0);
}

void func_0022bc80(void) {
    D_003F34A4 = 1;
    func_0020a8f0();
    func_0020b968();
    D_003F720C = 0;
}
