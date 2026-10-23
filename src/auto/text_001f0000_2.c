/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"
extern s32 D_00640DE0;

void func_001fd258(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) ((arg1 * 0x10) + 0x7000);
}

s32 func_001fd268(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s32 *, 0xB4) - 0x7000) >> 4;
}

void func_001fd278(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) ((arg1 * 0x10) + 0x7000);
}

s32 func_001fd288(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xB8) << 0x10) >> 0x14;
}

void func_001fd298(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xB8) = (s16) (arg1 * 0x10);
}

s32 func_001fd2a8(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xBA) << 0x10) >> 0x14;
}

void func_001fd2b8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xBA) = (s16) (arg1 * 0x10);
}

s32 func_001fd2c8(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xBE) << 0x10) >> 0x14;
}

void func_001fd2d8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xBE) = (s16) (arg1 * 0x10);
}

s32 func_001fd2e8(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC0) << 0x10) >> 0x14;
}

void func_001fd2f8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC0) = (s16) (arg1 * 0x10);
}

s32 func_001fd308(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC2) << 0x10) >> 0x14;
}

void func_001fd318(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC2) = (s16) (arg1 * 0x10);
}

s32 func_001fd328(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC4) << 0x10) >> 0x14;
}

void func_001fd338(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC4) = (s16) (arg1 * 0x10);
}

s32 func_001fd348(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC6) << 0x10) >> 0x14;
}

void func_001fd358(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC6) = (s16) (arg1 * 0x10);
}

s32 func_001fd368(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xC8) << 0x10) >> 0x14;
}

void func_001fd378(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xC8) = (s16) (arg1 * 0x10);
}

s16 func_001fd5d0(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xCA);
}

s16 func_001fd5d8(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xCC);
}

s16 func_001fd608(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xCE);
}

s32 func_001fd618(void *arg0) {
    return (s32) (M2C_FIELD(arg0, u16 *, 0xD0) << 0x10) >> 0x14;
}

void func_001fd628(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xD0) = (s16) (arg1 * 0x10);
}

s32 func_001fd848(void) {
    return D_00640DE0;
}
#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
