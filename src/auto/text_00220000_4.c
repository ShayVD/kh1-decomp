/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"
M2C_UNK func_001efb78(M2C_UNK);
M2C_UNK func_001f36b8(void *);
M2C_UNK func_001f94f0(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_001fade0(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);
extern f32 D_002BBDFC;
extern f32 D_006469B8[]; /* src/data/bss_0064.c: s32 D_006469B8[0x6] */
s32 func_001efc10(M2C_UNK);
s32 func_001f4400();

void func_0022d140(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[1] != 0.0f)) {
        temp_f0 = D_006469B8[1] - D_002BBDFC;
        D_006469B8[1] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x1D, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022d1b8(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[2] != 0.0f)) {
        temp_f0 = D_006469B8[2] - D_002BBDFC;
        D_006469B8[2] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0xE, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022d230(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[3] != 0.0f)) {
        temp_f0 = D_006469B8[3] - D_002BBDFC;
        D_006469B8[3] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x22, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022d2a8(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[4] != 0.0f)) {
        temp_f0 = D_006469B8[4] - D_002BBDFC;
        D_006469B8[4] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x20, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022d320(void *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[5] != 0.0f)) {
        temp_f0 = D_006469B8[5] - D_002BBDFC;
        D_006469B8[5] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x12, 0x12, M2C_FIELD(arg0, s32 *, 0x24));
}

void func_0022e2c0(s32 arg0) {
    func_001f94f0(arg0, 2, 0x100, 0x90, func_001efc10(0x1D8), 0x12, 0x801E4696);
}

void func_0022eaa0(void) {
    func_001efb78(0);
}
#include "data/data_003F.h"
#include "data/pieces/D_002BBDFC.h"
