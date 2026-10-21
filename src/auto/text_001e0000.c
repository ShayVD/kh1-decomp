/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0063.h"

M2C_UNK func_00101728(M2C_UNK);
M2C_UNK func_00111b10();
M2C_UNK func_00111b48();
M2C_UNK func_00111b90();
M2C_UNK func_0011c7d8(M2C_UNK);
M2C_UNK func_0011c7f0(s32);
M2C_UNK func_0011c9a0();
M2C_UNK func_0011c9b0();
M2C_UNK func_0011d448();
M2C_UNK func_0011d588();
M2C_UNK func_0011d688(s32);
M2C_UNK func_0011e518();
M2C_UNK func_0011e528();
M2C_UNK func_0011e9a8(M2C_UNK *, M2C_UNK *);
M2C_UNK func_0011eb88(s32, M2C_UNK *, s32, M2C_UNK *);
M2C_UNK func_0011ec08(s32, M2C_UNK *, s32, M2C_UNK *);
M2C_UNK func_00147808(u16);
M2C_UNK func_001478a0();
M2C_UNK func_001557b0(s32);
M2C_UNK func_001ba1e8();
M2C_UNK func_001ba208();
M2C_UNK func_001ee6d0();
M2C_UNK func_001efb18(M2C_UNK *, M2C_UNK *);
M2C_UNK func_001efc10(M2C_UNK);
M2C_UNK func_001efdb8(s32);
M2C_UNK func_001effc0(s32);
M2C_UNK func_002583e0(M2C_UNK);
M2C_UNK func_00265bc0(M2C_UNK, M2C_UNK);
M2C_UNK func_00266f38(s32, s32);
extern M2C_UNK D_003E5ED8;
extern M2C_UNK D_003E8910;
extern M2C_UNK D_00F20000;
extern M2C_UNK func_001e7fe0;
extern M2C_UNK func_001e8308;
extern M2C_UNK func_001e8628;
extern s32 D_003DACB8;
extern s32 D_003DACBC;
extern s32 D_003DD260;
extern s32 D_003E3C80;
extern s32 D_003E8E00;
extern s32 D_003E8E04;
extern s32 D_006314CC;
extern s32 D_006314D0;
extern s32 D_006314D8;
extern s32 D_006314DC;
s32 D_0063F248 ALIGNED(8);
extern s32 D_0063F540;
#include "data/pieces/D_003F34B8.h"
s32 func_0011e340(M2C_UNK);
s32 func_001ee768();
s32 func_001efbb8();
s32 func_00232cc0(M2C_UNK);
s32 func_00266c08(M2C_UNK);
u16 *func_00147840();
u32 func_001ee118();
void *func_001496c8();

void func_001e05a8(s32 arg0) {
    s32 temp_s0;

    temp_s0 = func_00266c08(2);
    func_002583e0(0);
    func_00265bc0(0, 0);
    func_00266f38(temp_s0, arg0);
    func_00265bc0(0, 0);
}

void func_001e1418(s32 arg0, s32 arg1) {
    D_003DACB8 = arg0 * 0x10;
    D_003DACBC = arg1 * 0x10;
}

s32 func_001e2800(s32 arg0) {
    return (u32) (arg0 - 1) < 0x10U;
}

s32 func_001e7488(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_003DD260;
    return 2;
}

s32 func_001e8010(void) {
    if (func_0011e340(0) == 0) {
        func_0011ec08(D_006314D0, &D_00F20000, D_006314D8, &func_001e7fe0);
        return 4;
    }
    return 0;
}

s32 func_001e8338(void) {
    if (func_0011e340(0) == 0) {
        func_0011eb88(D_006314CC, &D_00F20000, D_006314DC, &func_001e8308);
        return 4;
    }
    return 0;
}

s32 func_001e8658(void) {
    if (func_0011e340(0) == 0) {
        func_0011e9a8(&func_001e8628, &D_00F20000);
        return 4;
    }
    return 0;
}

s32 func_001e89e0(void) {
    func_0011e518();
    func_0011c7d8(0);
    func_0011c7d8(1);
    return 2;
}

s32 func_001e8a10(void) {
    func_0011e518();
    return 2;
}

s32 func_001e8a30(void) {
    func_0011e528();
    return 2;
}

s32 func_001e8b08(void *arg0) {
    func_0011c7f0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) - 1);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001e8bc0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 4);
    return 2;
}

s32 func_001e90c8(void) {
    return 2;
}

s32 func_001e90d0(void *arg0) {
    func_0011d588();
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001e9108(void *arg0) {
    func_0011d688(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) * 8);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001e9150(void) {
    func_0011c9a0();
    return 2;
}

s32 func_001e9170(void) {
    func_0011c9b0();
    return 2;
}

s32 func_001e9190(void) {
    func_0011c9b0();
    func_00101728(0);
    func_0011d448();
    return 2;
}

s32 func_001e91f0(void *arg0) {
    func_001557b0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

void func_001ea430(void) {

}

s32 func_001eafd8(void) {
    return func_00232cc0(1) + 0xAD1;
}

s32 func_001eaff8(void) {
    return func_00232cc0(1) + 0x904;
}

s32 func_001eb018(void) {
    return func_00232cc0(1) + 0x909;
}

s32 func_001eb5f0(s32 arg0, s32 arg1) {
    return M2C_FIELD(((((arg0 * 5) + arg1) * 4) + func_00232cc0(1)), s32 *, 0xB14);
}

void func_001eb640(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(((((arg0 * 5) + arg1) * 4) + func_00232cc0(1)), s32 *, 0xB14) = arg2;
}

void func_001ec7c0(s32 arg0) {
    D_003E3C80 = arg0;
}

s32 func_001ecfb0(void) {
    func_002583e0(0);
    return D_0063F248;
}

s32 func_001ecfd8(void) {
    func_002583e0(0);
    return D_0063F540;
}

u32 func_001ee1d0(void) {
    return func_001ee118() / 3600U;
}

u32 func_001ee200(void) {
    return func_001ee118() / 60U;
}

u32 func_001ee308(void) {
    return (u32) (func_001ee118() / 3600U) % 60U;
}

u32 func_001ee348(void) {
    return (u32) (func_001ee118() / 60U) % 60U;
}

void func_001ee428(void) {
    func_00111b10();
}

void func_001ee440(void) {
    func_00111b48();
}

void func_001ee458(void) {
    func_00111b90();
}

void func_001ee698(s32 arg0) {
    if (arg0 != 0) {
        func_00147808(*func_00147840());
        return;
    }
    func_001efc10(0x97);
}

s32 func_001ee9b8(void) {
    return func_001ee768() != 0xD;
}

s32 func_001ee9e0(void) {
    return func_001ee768() == 0;
}

void func_001eeaf0(void) {
    func_001ba208();
}

void func_001eeb08(void) {
    func_001ba1e8();
}

void func_001eebd8(s32 arg0) {
    if (arg0 != 0) {
        func_001ee6d0();
        return;
    }
    func_001efc10(0xA8);
}

void func_001eec00(s32 arg0) {
    if (arg0 != 0) {
        func_001ee6d0();
        return;
    }
    func_001efc10(0xA8);
}

s8 func_001eec28(void) {
    return M2C_FIELD(func_001496c8(), s8 *, 0x30);
}

s32 func_001ef250(void) {
    return func_001ee768() - 2;
}

void func_001ef528(void) {
    func_001478a0();
}

s32 func_001ef7a0(void) {
    return M2C_FIELD(D_003F34B8, s32 *, 0x1C);
}

void func_001ef948(void) {

}

void func_001efaf0(void) {
    func_001efb18(&D_003E5ED8, &D_003E8910);
}

void func_001efb78(s32 arg0) {
    D_003E8E00 = arg0;
}

s32 func_001efb88(void) {
    return D_003E8E00;
}

void func_001efb98(s32 arg0) {
    D_003E8E04 = arg0;
}

s32 func_001efba8(void) {
    return D_003E8E04;
}

void func_001efd98(void) {
    func_001efdb8(func_001efbb8());
}

void func_001effa0(void) {
    func_001effc0(func_001efbb8());
}
#include "data/data_003D.h"
#include "data/data_003E.h"
#include "data/pieces/D_003E46A0.h"
