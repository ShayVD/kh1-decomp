/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_001f3840(s32);
M2C_UNK func_00207830(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0020a9b0(s32);
M2C_UNK func_0020ab88(s32);
M2C_UNK func_0020b120(M2C_UNK, s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0020be10(M2C_UNK);
extern s32 D_003F34A4;
extern s32 D_003F34C0;
extern s32 D_003F720C;
s32 func_001f42b8();
void func_00109268(void);
void func_0020a8f0(void);
void func_0020b968(void);

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
#include "data/data_003F.h"
