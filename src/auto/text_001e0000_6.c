/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"

M2C_UNK func_001ed000(M2C_UNK, s32, s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_001efc10(u16);
M2C_UNK func_001efd20(s32, s32);
M2C_UNK func_0021dbb8();
M2C_UNK sceSifCallRpc(M2C_UNK *, M2C_UNK, M2C_UNK, s32 *, M2C_UNK, s32 *, M2C_UNK, M2C_UNK, s32);
#include "data/pieces/D_003E8E28.h"
#include "data/pieces/D_003DC390.h"
extern M2C_UNK D_003E3C88;
extern M2C_UNK D_003E3CB8;
#include "data/pieces/D_003E3CF8.h"
#include "data/pieces/D_003E3E50.h"
extern M2C_UNK D_003E4658;
extern M2C_UNK D_0062F6E0;
extern M2C_UNK func_001e4268;
#include "data/pieces/D_003DACA0.h"
#include "data/pieces/D_003DAD3C.h"
extern s32 D_003DC470;
extern s32 D_003DC474;
extern s32 D_003DC480;
extern s32 D_003DC488;
extern s32 D_003DC490;
extern s32 D_003E8E2C;
extern s32 D_00633640; /* src/data/bss_0063.c: u32 D_00633640[2048] */
extern s8 D_0062F810; /* src/data/bss_0062.c: u8 D_0062F810[0x30] */
#include "data/pieces/D_003F34B8.h"
s32 func_0010e3f0(s32);
s32 func_00147840(s32);
s32 func_001ee768();
s32 func_001efbb8();
s32 func_00232cc0(s32);
u32 func_001ee118();
void func_0010bdd0(s32, s32);
void func_0010ef70(s32, s32, s32);
void func_001e2778(void);
void func_001efaf0(void);
void func_001efb58(s32);
void func_001efb78(s32);
void func_001efb98(s32);
void func_00216180(void);
void func_00219128(void);
void func_0022fc88(s32);
void func_00231958(void);
void func_00232de0(void);


/* func_001e13e8, func_001e25e8, func_001e2628 are in src/screen/screen.c. */



void func_001e3c08(s32 arg0) {
    D_003DC470 = arg0;
    if (arg0 != D_003DC474) {
        D_003DC474 = arg0;
        func_0010e3f0((s32) &D_0062F810);
        func_0010ef70((s32) (&D_0062F810 - 0x80), (s32) (M2C_UNK *)&D_003DC390, 0);
    }
}

void func_001e44e0(s32 arg0) {
    D_003DC490 = 0;
    if (D_003DC488 == arg0) {
        func_001e2778();
        func_00231958();
        return;
    }
    D_003DC480 = arg0;
    func_0022fc88(arg0 - 1);
    func_0010bdd0((s32) &D_0062F6E0, (s32) &func_001e4268);
    D_003DC470 = 0;
    D_003DC474 = 0;
}

void func_001ec380(s32 arg0) {
    M2C_FIELD(func_00232cc0(1), s8 *, 0xDD0) = (s8) arg0;
}

s32 func_001ec9a8(void) {
    sceSifCallRpc(&D_003E3C88, 0x1F, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001eca00(void) {
    sceSifCallRpc(&D_003E3C88, 0x20, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001eca58(void) {
    sceSifCallRpc(&D_003E3C88, 0x21, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ecab0(void) {
    sceSifCallRpc(&D_003E3C88, 0x22, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ed0d0(s32 arg0) {
    D_00633640 = arg0;
    sceSifCallRpc(&D_003E3C88, 1, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ed128(s32 arg0, s32 arg1) {
    func_001ed000(0x26, arg0, arg1, 0, 0, 0, 0, 0);
    return D_00633640;
}

s32 func_001ed170(s32 arg0) {
    D_00633640 = arg0;
    sceSifCallRpc(&D_003E3C88, 0x27, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ed1c8(s32 arg0) {
    D_00633640 = arg0;
    sceSifCallRpc(&D_003E3C88, 0xF, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ed5a8(s32 arg0) {
    D_00633640 = arg0;
    sceSifCallRpc(&D_003E3C88, 0x2F, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ed600(s32 arg0) {
    D_00633640 = arg0;
    sceSifCallRpc(&D_003E3C88, 0x30, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ed828(s32 arg0, s32 arg1) {
    func_001ed000(0x2B, arg0, arg1, 0, 0, 0, 0, 0);
    return D_00633640;
}

s32 func_001ed870(void) {
    sceSifCallRpc(&D_003E3C88, 0x16, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ed8c8(s32 arg0) {
    D_00633640 = arg0;
    sceSifCallRpc(&D_003E3C88, 0x17, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ed920(void) {
    sceSifCallRpc(&D_003E3C88, 0x18, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001ed9e0(void) {
    sceSifCallRpc(&D_003E3C88, 0x1B, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001eda38(s32 arg0) {
    D_00633640 = arg0;
    sceSifCallRpc(&D_003E3C88, 0x1D, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001edaf0(s32 arg0) {
    D_00633640 = arg0;
    sceSifCallRpc(&D_003E3C88, 0x23, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

s32 func_001edb48(s32 arg0) {
    D_00633640 = arg0;
    sceSifCallRpc(&D_003E3C88, 0x24, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return D_00633640;
}

f32 func_001edcd8(f32 fparg0) {
    f32 var_f12;

    var_f12 = fparg0;
    if (var_f12 >= 3.141592979f) {
        var_f12 -= 2.0f * ((f32) ((s32) (var_f12 / 6.2831855f) + 1) * 3.141592979f);
    } else if (var_f12 < -3.141592979f) {
        var_f12 += 2.0f * ((f32) ((s32) (var_f12 / -6.2831855f) + 1) * 3.141592979f);
    }
    return var_f12;
}

u32 func_001ee198(void) {
    return func_001ee118() / 216000U;
}

u32 func_001ee2d0(void) {
    return func_001ee118() / 216000U;
}

void func_001ee4e8(void) {
    func_00232de0();
    func_00219128();
    M2C_FIELD(D_003F34B8, s32 *, 0x1C) = 0;
    func_00216180();
    func_0021dbb8();
}

void func_001ee5f0(s32 arg0) {
    func_001efc10(*(M2C_UNK *)((s8 *)&D_003E3CB8 + (arg0 * 2)));
}

s32 func_001ee6d0(s32 arg0) {
    if ((u32) (arg0 - 1) < 0xFFU) {
        return M2C_FIELD(func_00147840(arg0), s32 *, 0xC);
    }
    return 0;
}

s32 func_001ef270(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        return func_001ee768() == *(M2C_UNK *)((s8 *)(M2C_UNK *)&D_003E3CF8 + (arg1 * 4));
    }
    return 0;
}

s32 func_001ef658(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_003E3E50 + (arg0 * 0xE4));
}

void func_001efaa8(void) {
    (*(M2C_UNK **)&D_003E8E28) = &D_003E4658;
    D_003E8E2C = 0x310;
    func_001efb58(0x14);
    func_001efb78(0);
    func_001efb98(0);
    func_001efaf0();
}

void func_001efbe0(s32 arg0, s32 arg1) {
    func_001efd20(func_001efbb8(), arg1);
}
#include "data/data_003D.h"
#include "data/data_003E.h"
