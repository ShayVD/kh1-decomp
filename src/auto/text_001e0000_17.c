/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"
#include "data/bss_0063.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_0010bd90(M2C_UNK *, M2C_UNK);
M2C_UNK func_0010bdd0(M2C_UNK *, M2C_UNK *);
M2C_UNK func_0010ef70(M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK func_00111be8();
M2C_UNK func_0011c7a8(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0011e9a8(M2C_UNK *, M2C_UNK *);
M2C_UNK func_0011eb88(s32, M2C_UNK *, s32, M2C_UNK *);
M2C_UNK func_0011ec08(s32, M2C_UNK *, s32, M2C_UNK *);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00147840();
M2C_UNK func_001e2778();
M2C_UNK func_001e61c0(M2C_UNK, M2C_UNK *);
M2C_UNK func_001e9650();
M2C_UNK func_001ef948();
M2C_UNK func_001efaa8();
M2C_UNK func_001efc10(u16);
M2C_UNK func_001efd20(s32, s32);
M2C_UNK func_001f2eb8();
M2C_UNK func_0020d748();
M2C_UNK func_0022bd20();
M2C_UNK func_0022d138();
M2C_UNK func_0022d728();
M2C_UNK func_0022db90();
M2C_UNK func_0022dfd0();
M2C_UNK func_0022e458();
M2C_UNK func_0022ebe8();
M2C_UNK func_0022ebf0();
M2C_UNK func_002319c0();
M2C_UNK func_00232790();
M2C_UNK func_00232ac8();
M2C_UNK func_00233610();
M2C_UNK func_00233a80();
M2C_UNK func_002660c0(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_002672f8(s32, void *, s32);
M2C_UNK func_00267518(s32, s32, s32);
M2C_UNK func_00267620(void *);
M2C_UNK func_002676c0(void *, void *, f32);
M2C_UNK func_00267768(void *, void *, f32);
M2C_UNK func_00267810(void *, void *, f32);
M2C_UNK sceGsExecLoadImage(M2C_UNK *, s32);
M2C_UNK sceGsExecStoreImage(void *, M2C_UNK *);
M2C_UNK sceGsSetDefLoadImage(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
#include "data/pieces/D_003DC390.h"
extern M2C_UNK D_003E1CB0;
extern M2C_UNK D_003E3700;
extern M2C_UNK D_003E3CB8;
extern M2C_UNK D_0062F670;
extern M2C_UNK D_0062F790;
extern M2C_UNK D_0062FB00; /* src/data/bss_0062.c: s32 D_0062FB00[0x100] */
extern M2C_UNK D_0062FF00; /* src/data/bss_0062.c: s32 D_0062FF00[0x100] */
extern M2C_UNK D_00630510; /* src/data/bss_0063.c: u8 D_00630510[0xb0] */
extern M2C_UNK D_00631570; /* src/data/bss_0063.c: Win D_00631570 */
extern M2C_UNK D_00F20000;
extern M2C_UNK func_001e0ab0;
extern M2C_UNK func_001e0d98;
extern M2C_UNK func_001e15a0;
extern M2C_UNK func_001e1838;
extern M2C_UNK func_001e1c20;
extern M2C_UNK func_001e72a0;
extern M2C_UNK func_001e7fe0;
extern M2C_UNK func_001e8010;
extern M2C_UNK func_001e8308;
extern M2C_UNK func_001e8338;
extern M2C_UNK func_001e8628;
extern M2C_UNK func_001e8658;
extern f32 D_003DACB0;
extern f32 D_003DACB4;
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_003DABD0.h"
extern s32 D_003DAD38;
extern s32 D_003DC470;
extern s32 D_003DC474;
extern s32 D_003DC484;
extern s32 D_003DD258;
extern s32 D_003DD28C;
extern s32 D_003F7A64;
extern s32 D_0062F6D0;
extern s32 D_006314CC;
extern s32 D_006314D0;
extern s32 D_006314D4;
extern s32 D_006314D8;
extern s32 D_006314DC;
extern s64 D_00389C90[];
extern s8 D_0062FA00; /* src/data/bss_0062.c: u8 D_0062FA00[0x100] */
f32 func_001edc50(s32);
f32 func_001edcd8(f32);
s32 func_0011e340(M2C_UNK);
s32 func_00123488(s32);
s32 func_001efc68();
#include "vm/script_vm.h"
void memset(s32, s32, s32);

void func_001e07a8(s32 arg0) {
    s32 temp_s0;

    sceGsSetDefLoadImage(&D_0062F670, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    temp_s0 = arg0 * 0x600;
    sceGsExecLoadImage(&D_0062F670, (s32)D_003DABD0[1] + temp_s0);
    sceGsSetDefLoadImage(&D_0062F670, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, (s32)D_003DABD0[1] + temp_s0 + 0x48000);
}

void func_001e0d68(s32 arg0) {
    D_0062F6D0 = arg0;
    func_0011ef10(0x2E630, &func_001e0ab0);
}

void func_001e1088(s32 arg0) {
    D_0062F6D0 = arg0;
    func_0011ef10(0x2E630, &func_001e0d98);
}

s32 func_001e10b8(void) {
    D_003DAD38 = 0;
    return 4;
}

void func_001e1438(s32 arg0, s32 arg1) {
    D_003DACB0 = (f32) arg0 / 100.0f;
    D_003DACB4 = (f32) arg1 / 100.0f;
}

void func_001e1480(void) {
    s32 sp[28];
    func_002660c0(sp, 0x1A00, 8, 1, 0, 0, 0x200, 0x180);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecStoreImage(sp, &D_00F20000);
}

void func_001e1688(void) {
    func_0011ef10(0x280A0, &func_001e15a0);
}

void func_001e1bf8(void) {
    func_0011ef10(0x280A0, &func_001e1838);
}

void func_001e2470(void) {
    func_0011ef10(0x280A0, &func_001e1c20);
}

void func_001e27b0(void) {
    s32 sp[4];
    func_001c2d20((s8 *) &D_003E1CB0, sp, (s8 **) &D_0062FB00);
    func_001c2d20((s8 *) &D_003E3700, sp, (s8 **) &D_0062FF00);
    D_0062FA00 = 0;
}

void func_001e2f88(s32 arg0) {
    D_003DC484 = arg0;
}

s32 func_001e3178(void) {
    if (D_003F7A64 == 0) {
        func_001e2778();
        return 4;
    }
    return 0;
}

void func_001e3a98(s32 arg0) {
    D_003DC484 = arg0;
}

void func_001e3b28(void) {
    func_001e2778();
}

void func_001e3da8(void) {
    func_0010ef70(&D_0062F790, (M2C_UNK *)&D_003DC390, 0);
}

void func_001e4048(s32 arg0) {
    D_003DC470 = arg0;
    if (D_003DC474 == 0) {
        D_003DC474 = arg0;
    }
}

void func_001e4250(void) {
    func_001e2778();
}

void func_001e4558(void) {
    func_0010bd90(&D_0062F790, 0);
}

void func_001e6388(void) {
    func_001e61c0(0, &D_00630510);
}

void func_001e6438(s32 arg0) {
    D_003DD28C = 0;
    D_003DD258 = arg0;
}

void func_001e64e0(void) {
    D_00389C90[1551] = (s64) (D_00389C90[1551] & ~0x10);
}

void func_001e6c68(void) {
    func_0010bdd0(&D_00630510, &func_001e72a0);
}

void func_001e6e08(s32 arg0) {
    D_003DD28C = 0;
    D_003DD258 = arg0;
}

void func_001e7d80(s32 arg0) {
    D_003DD258 = arg0;
}

void func_001e7e78(void) {
    func_0011c7a8(D_006314D4, 0, 0x3000, 0, 0, 0);
}

void func_001e8060(s32 arg0) {
    D_006314D8 = arg0;
    if (func_0011e340(0) == 0) {
        func_0011ec08(D_006314D0, &D_00F20000, D_006314D8, &func_001e7fe0);
        return;
    }
    func_0011ef10(0xC352, &func_001e8010);
}

void func_001e8388(s32 arg0) {
    D_006314DC = arg0;
    if (func_0011e340(0) == 0) {
        func_0011eb88(D_006314CC, &D_00F20000, D_006314DC, &func_001e8308);
        return;
    }
    func_0011ef10(0xC352, &func_001e8338);
}

void func_001e86a0(void) {
    if (func_0011e340(0) == 0) {
        func_0011e9a8(&func_001e8628, &D_00F20000);
        return;
    }
    func_0011ef10(0xC352, &func_001e8658);
}

void func_001e92b8(void) {
    func_0010bd90(&D_00631570, 0);
    func_001e9650();
}

void func_001e9dc8(s32 arg0, void *arg1, s32 arg2) {
    s32 sp[16];
    func_00267620(sp);
    func_00267768(sp, sp, M2C_FIELD(arg1, f32 *, 0));
    func_00267810(sp, sp, M2C_FIELD(arg1, f32 *, 4));
    func_002676c0(sp, sp, M2C_FIELD(arg1, f32 *, 8));
    func_002672f8(arg2, sp, arg2);
    func_00267518(arg0, arg0, arg2);
}

s32 func_001ea580(void *arg0) {
    u8 temp_v0;

    M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    temp_v0 = M2C_FIELD(arg0, u8 *, 2);
    if (temp_v0 == 1) {
        M2C_FIELD(arg0, u8 *, 2) = 0U;
    } else if (temp_v0 == 0) {
        M2C_FIELD(arg0, u8 *, 2) = 1U;
    }
    M2C_FIELD(arg0, s32 *, 4) = func_00123488(M2C_FIELD(arg0, s32 *, 0));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

void func_001ee470(void) {
    func_00111be8();
}

s32 func_001ee488(u32 arg0) {
    s32 temp_v1;
    s32 var_a1;
    s32 var_lo;
    u32 var_a0;

    var_a0 = arg0;
    var_lo = 0;
    var_a1 = 1;
    do {
        temp_v1 = var_a0 & 0xF;
        var_a0 = var_a0 >> 4;
        var_lo += temp_v1 * var_a1;
        var_a1 *= 0xA;
    } while (var_a0 != 0);
    return var_lo;
}

void func_001ee520(void) {
    func_00233610();
    func_00233a80();
    func_001efaa8();
    func_001f2eb8();
    func_001ef948();
    func_0020d748();
    func_0022bd20();
    func_0022d138();
    func_0022d728();
    func_0022db90();
    func_0022dfd0();
    func_0022e458();
    func_0022ebe8();
    func_0022ebf0();
    func_002319c0();
    func_00232790();
    func_00232ac8();
}

void func_001ee5b8(void) {
    s32 sp[4];
    memset((s32) sp, 0, 0x10);
    func_001edc50((s32) sp);
    func_001edcd8(0.0f);
}

void func_001ee618(s32 arg0) {
    func_001efc10(*(M2C_UNK *)((s8 *)(s8 *)&D_003E3CB8 + (M2C_FIELD((arg0 + ((s32)D_00304BE8)), u8 *, 0x48E) * 2)));
}

void func_001ee680(void) {
    func_00147840();
}

void func_001efc80(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001efd20(func_001efc68(), arg3);
}
#include "data/data_003D.h"
#include "data/data_003F.h"
#include "data/data_003E.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
