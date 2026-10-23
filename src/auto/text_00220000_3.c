/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

extern M2C_UNK D_006437C8; /* src/data/bss_0064.c: s32 D_006437C8[0x2] */
extern M2C_UNK D_006437D0; /* src/data/bss_0064.c: s32 D_006437D0[0x2] */
extern s32 D_006437C4;
extern s32 D_006437D8;
s32 func_001efd98(M2C_UNK);

void func_002299b0(void *arg0) {
    s32 temp_v1;

    temp_v1 = func_001efd98(0x1A9) * 0x170;
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) (M2C_FIELD(arg0, s32 *, 0xB4) - temp_v1);
    M2C_FIELD(arg0, u16 *, 0xBA) = (u16) (M2C_FIELD(arg0, u16 *, 0xBA) + temp_v1);
    M2C_FIELD(arg0, u16 *, 0xC0) = (u16) (M2C_FIELD(arg0, u16 *, 0xC0) + temp_v1);
}

void func_00229bd8(void *arg0) {
    s32 temp_v1;

    temp_v1 = func_001efd98(0x1A7) * 0x170;
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) (M2C_FIELD(arg0, s32 *, 0xB4) - temp_v1);
    M2C_FIELD(arg0, u16 *, 0xBA) = (u16) (M2C_FIELD(arg0, u16 *, 0xBA) + temp_v1);
    M2C_FIELD(arg0, u16 *, 0xC0) = (u16) (M2C_FIELD(arg0, u16 *, 0xC0) + temp_v1);
}

void func_00229cf8(void *arg0) {
    s32 temp_v1;

    temp_v1 = func_001efd98(0x19C) * 0x170;
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) (M2C_FIELD(arg0, s32 *, 0xB4) - temp_v1);
    M2C_FIELD(arg0, u16 *, 0xBA) = (u16) (M2C_FIELD(arg0, u16 *, 0xBA) + temp_v1);
    M2C_FIELD(arg0, u16 *, 0xC0) = (u16) (M2C_FIELD(arg0, u16 *, 0xC0) + temp_v1);
}

void func_00229e18(void *arg0) {
    s32 temp_v1;

    temp_v1 = func_001efd98(0x1A8) * 0x170;
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) (M2C_FIELD(arg0, s32 *, 0xB4) - temp_v1);
    M2C_FIELD(arg0, u16 *, 0xBA) = (u16) (M2C_FIELD(arg0, u16 *, 0xBA) + temp_v1);
    M2C_FIELD(arg0, u16 *, 0xC0) = (u16) (M2C_FIELD(arg0, u16 *, 0xC0) + temp_v1);
}

void func_0022bd20(void) {
    D_006437C4 = 0;
    D_006437D8 = 0;
    M2C_FIELD(&D_006437C8, s32 *, 0) = 0;
    M2C_FIELD(&D_006437C8, s32 *, 4) = 0;
    M2C_FIELD(&D_006437D0, s32 *, 0) = 0;
    M2C_FIELD(&D_006437D0, s32 *, 4) = 0;
}
