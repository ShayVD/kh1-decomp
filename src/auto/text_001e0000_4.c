/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0063.h"

M2C_UNK func_0010ef70(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_0011cdf0(M2C_UNK, s32, M2C_UNK *, M2C_UNK);
M2C_UNK func_00146928(M2C_UNK);
extern M2C_UNK D_003DBA68;
extern M2C_UNK D_0062A630;
extern M2C_UNK D_0062F6E0;
extern M2C_UNK func_001dd5c0;
extern M2C_UNK func_001e2810;
extern M2C_UNK func_001e8e38;
extern s32 D_002C5958;
extern s32 D_003DAD38;
extern s32 D_003DC470;
extern s32 D_003DC484;
extern s32 D_003DC490;
extern s32 D_003DD25C;
extern s32 D_003DD260;
extern s32 D_003DD310;
extern s32 D_003DD314;
extern s32 D_003F7A68;
extern s32 D_003F7E98;
extern s32 D_00631560;
extern s32 D_0063F740;
extern s32 D_0063F744;
extern s32 D_0063F748;
s32 func_0011e340(M2C_UNK);
s32 func_001ee768();
void *func_0011f090(M2C_UNK *, M2C_UNK, M2C_UNK *);

s32 func_001e0010(void *arg0) {
    void *temp_v0;

    temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = 0xE;
    M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001e2668(void) {
    D_003DAD38 = 0;
    return 2;
}

void func_001e2a30(s32 arg0) {
    D_003DC484 = arg0;
}

void func_001e31b0(void) {

}

void func_001e32c8(s32 arg0) {
    D_003DC470 = arg0;
}

void func_001e3728(void) {
    func_0010ef70(&D_0062F6E0, &D_003DBA68, &func_001e2810);
    D_003F7A68 = 1;
    D_003DC490 = 1;
}

void func_001e39f0(void) {
    D_003F7E98 = 1;
}

void func_001e3ef0(s32 arg0) {
    D_003DC484 = arg0;
}

void func_001e6578(void) {

}

void func_001e6b70(s32 arg0) {
    if (D_003DD25C == 3) {
        D_003DD260 = arg0 - 1;
        return;
    }
    D_003DD260 = arg0 - 2;
}

void func_001e7928(void) {

}

void func_001e7a60(void) {

}

void func_001e7b48(void) {

}

s32 func_001e8e68(void) {
    if (func_0011e340(0) == 0) {
        func_00146928(-6);
        func_00146928(-7);
        D_002C5958 |= 0x40000;
        func_0011cdf0(-8, D_00631560, &func_001e8e38, 0x40000);
        return 4;
    }
    return 0;
}

void func_001e9650(void) {
    D_003DD310 = -4;
    D_003DD314 = -2;
}

s32 func_001ef370(s32 arg0) {
    if (arg0 != 0) {
        return func_001ee768() == 1;
    }
    return 0;
}

void func_001efb18(s32 arg0, s32 arg1) {
    D_0063F744 = arg0;
    D_0063F748 = arg1;
}

void func_001efb58(s32 arg0) {
    D_0063F740 = arg0 * 0x10;
}

s32 func_001efb68(void) {
    return (s32) D_0063F740 >> 4;
}
