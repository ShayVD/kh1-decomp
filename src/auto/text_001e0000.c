/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0063.h"

M2C_UNK func_00111b10();
M2C_UNK func_00111b48();
M2C_UNK func_00111b90();
M2C_UNK func_00147808(u16);
M2C_UNK func_001478a0();
M2C_UNK func_001ba1e8();
M2C_UNK func_001ba208();
M2C_UNK func_001ee6d0();
M2C_UNK func_001efb18(M2C_UNK *, M2C_UNK *);
M2C_UNK func_001efc10(M2C_UNK);
M2C_UNK func_001efdb8(s32);
M2C_UNK func_001effc0(s32);
M2C_UNK func_002583e0(M2C_UNK);
extern M2C_UNK D_003E5ED8;
extern M2C_UNK D_003E8910;
extern s32 D_003E3C80;
extern s32 D_003E8E00;
extern s32 D_003E8E04;
extern s32 D_0063F248;  /* src/data/data_0063.s: inside the IOP block D_0063D640 */
extern s32 D_0063F540;
#include "data/pieces/D_003F34B8.h"
s32 func_001ee768();
s32 func_001efbb8();
u16 *func_00147840();
u32 func_001ee118();
void *func_001496c8();

/* func_001e05a8, func_001e1418 are in src/screen/screen.c. */


/* func_001e2800 is in src/shop/shop.c. */

/* func_001e7488 is in src/list/list.c. */

/* func_001e8010, func_001e8338, func_001e8658, func_001e89e0, func_001e8a10, func_001e8a30, func_001e8b08, func_001e8bc0, func_001e90c8, func_001e90d0, func_001e9108, func_001e9150, func_001e9170, func_001e9190, func_001e91f0 are in src/event/sound.c. */















void func_001ea430(void) {

}

/* func_001eafd8, func_001eaff8, func_001eb018, func_001eb5f0, func_001eb640 are in src/save/flags.c. */





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
