/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_0011d790(M2C_UNK, s32);
M2C_UNK func_001f3840(s32);
M2C_UNK func_0020be10(M2C_UNK);
M2C_UNK func_00239368();
M2C_UNK func_0023dd48();
extern s32 D_003F7A64;
extern s32 D_003F7E94;
extern s32 D_0044A820;
extern s32 D_00646A10; /* src/data/bss_0064.c: void *D_00646A10 */
extern s32 D_00647650;
extern s32 D_00647654;
extern s32 D_00647658;
extern s32 D_006477A8;
extern s32 D_00647FD4;
extern s32 D_00647FD8;
extern s32 D_00647FDC;
extern s32 D_00647FE0;
extern s32 D_00647FF4;
extern s32 D_00648004;
extern s32 D_00648008;
extern s32 D_0064800C;
extern s32 D_00648010;

void func_00231958(void) {
    func_001f3840(D_00646A10);
    func_0020be10(0x10);
}

void func_002319c0(void) {
    D_003F7A64 = 0;
}

void func_00232758(void) {
    func_001f3840(D_00647650);
    func_0020be10(0x10);
}

void func_00232780(void) {
    D_003F7E94 = 0;
}

void func_00232790(void) {
    D_003F7E94 = 0;
    D_00647654 = 0;
    D_00647658 = 0;
}

void func_00233ef8(s32 arg0) {
    D_006477A8 = 1;
    D_00647FD4 = arg0;
    D_00647FD8 = 0;
}

void func_00233f18(void) {
    D_006477A8 = 0;
}

void func_00233f28(s32 arg0, s32 arg1) {
    D_00647FDC = arg0;
    D_00647FE0 = arg1;
}

s32 func_00234860(void) {
    return D_00647FF4;
}

s32 func_002348a0(void) {
    return D_00648004;
}

s32 func_002348b0(void) {
    return D_00648008;
}

s32 func_002348c0(void) {
    return D_0064800C;
}

s32 func_002348d0(void) {
    return D_00648010;
}

void func_00236f00(void) {
    func_00239368();
}

void *func_00237008(s64 arg0, s64 arg1, void *arg2) {
    M2C_FIELD(arg2, s64 *, 0) = arg1;
    M2C_FIELD(arg2, s64 *, 8) = arg0;
    return arg2 + 0x10;
}

void func_0023cee8(void) {
    if (D_0044A820 == 0) {
        D_0044A820 = 1;
    }
}

void func_0023cf08(void) {
    if (D_0044A820 == 2) {
        D_0044A820 = 3;
    }
}

void func_0023d128(s32 arg0) {
    func_0011d790(0x2D, arg0);
}

void func_0023dfc0(void) {
    func_0023dd48();
}
#include "data/data_003F.h"
