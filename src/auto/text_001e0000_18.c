/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_0010bd90(M2C_UNK *, M2C_UNK *);
M2C_UNK func_0011e9a8(M2C_UNK *, s32);
M2C_UNK func_0011eb88(s32, s32, s32, M2C_UNK *);
M2C_UNK func_0011ec08(s32, s32, s32, M2C_UNK *);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_001c2d20(M2C_UNK *, void *, M2C_UNK *);
M2C_UNK func_002672f8(void *, void *, void *);
M2C_UNK func_00267620(void *);
M2C_UNK func_00267768(void *, void *, f32);
M2C_UNK func_00267810(void *, void *, f32);
M2C_UNK sceGsExecLoadImage(M2C_UNK *, M2C_UNK *);
M2C_UNK sceGsSetDefLoadImage(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK D_003DBD68;
extern M2C_UNK D_003E0D20;
extern M2C_UNK D_003E0F40;
extern M2C_UNK D_003E1150;
extern M2C_UNK D_003E12E0;
extern M2C_UNK D_0062F670;
extern M2C_UNK D_0062F6E0;
extern M2C_UNK D_006303B0;
extern M2C_UNK D_00630460;
extern M2C_UNK D_00630510;
extern M2C_UNK D_006310C8;
extern M2C_UNK D_00631148;
extern M2C_UNK D_006311C8;
extern M2C_UNK D_00631248;
extern M2C_UNK D_00F20000;
extern M2C_UNK func_001e10b8;
extern M2C_UNK func_001e4990;
extern M2C_UNK func_001e61c0;
extern M2C_UNK func_001e6d20;
extern M2C_UNK func_001e6f28;
extern M2C_UNK func_001e7ba8;
extern M2C_UNK func_001e7fe0;
extern M2C_UNK func_001e8178;
extern M2C_UNK func_001e8308;
extern M2C_UNK func_001e84a0;
extern M2C_UNK func_001e8628;
extern s32 D_003DABD4;
extern s32 D_003DC48C;
extern s32 D_003DC490;
extern s32 D_003DD264;
extern s32 D_003F7A68;
extern s32 D_0062F6D0;
extern s32 D_006314CC;
extern s32 D_006314D0;
extern s32 D_006314D8;
extern s32 D_006314DC;
s32 func_0011e340(M2C_UNK);
void func_0010ef70(s32, s32, s32);

void func_001e10c8(s32 arg0) {
    D_0062F6D0 = arg0;
    func_0011ef10(0x2E630, &func_001e10b8);
}

void func_001e14e0(void) {
    sceGsSetDefLoadImage(&D_0062F670, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, &D_00F20000);
    sceGsSetDefLoadImage(&D_0062F670, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, (s8 *)&D_00F20000 + 0x48000);
}

void func_001e4268(void) {
    D_003DC490 = 1;
    D_003F7A68 = 1;
    D_003DC48C = 0;
    func_0010ef70((s32) &D_0062F6E0, (s32) &D_003DBD68, 0);
}

void func_001e4918(void) {
    s32 sp[4];
    func_001c2d20(&D_003E0D20, sp, &D_006310C8);
    func_001c2d20(&D_003E0F40, sp, &D_00631148);
    func_001c2d20(&D_003E1150, sp, &D_006311C8);
    func_001c2d20(&D_003E12E0, sp, &D_00631248);
}

void func_001e4d20(void) {
    D_003DD264 = 0;
    func_0010bd90(&D_006303B0, &func_001e4990);
}

void func_001e6410(void) {
    func_0010bd90(&D_00630510, &func_001e61c0);
}

void func_001e6de0(void) {
    func_0010bd90(&D_00630510, &func_001e6d20);
}

void func_001e7278(void) {
    func_0010bd90(&D_00630510, &func_001e6f28);
}

void func_001e7d58(void) {
    func_0010bd90(&D_00630460, &func_001e7ba8);
}

void func_001e81c8(s32 arg0) {
    D_006314D8 = arg0;
    if (func_0011e340(0) == 0) {
        func_0011ec08(D_006314D0, D_003DABD4, D_006314D8, &func_001e7fe0);
        return;
    }
    func_0011ef10(0xC352, &func_001e8178);
}

void func_001e84f0(s32 arg0) {
    D_006314DC = arg0;
    if (func_0011e340(0) == 0) {
        func_0011eb88(D_006314CC, D_003DABD4, D_006314DC, &func_001e8308);
        return;
    }
    func_0011ef10(0xC352, &func_001e84a0);
}

s32 func_001e86e8(void) {
    if (func_0011e340(0) == 0) {
        func_0011e9a8(&func_001e8628, D_003DABD4);
        return 4;
    }
    return 0;
}

void func_001e9f18(void *arg0, void *arg1, void *arg2, f32 fparg0) {
    s32 sp[16];
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;

    M2C_FIELD(arg0, f32 *, 0xC) = 1.0f;
    M2C_FIELD(arg0, f32 *, 8) = fparg0;
    M2C_FIELD(arg0, f32 *, 0) = 0.0f;
    M2C_FIELD(arg0, f32 *, 4) = 0.0f;
    func_00267620(sp);
    func_00267768(sp, sp, M2C_FIELD(arg2, f32 *, 0));
    func_00267810(sp, sp, M2C_FIELD(arg2, f32 *, 4));
    func_002672f8(arg0, sp, arg0);
    temp_f1 = -M2C_FIELD(arg0, f32 *, 0);
    temp_f2 = -M2C_FIELD(arg0, f32 *, 4);
    temp_f3 = -M2C_FIELD(arg0, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 0) = temp_f1;
    M2C_FIELD(arg0, f32 *, 4) = temp_f2;
    M2C_FIELD(arg0, f32 *, 8) = temp_f3;
    M2C_FIELD(arg0, f32 *, 0) = (f32) (temp_f1 + M2C_FIELD(arg1, f32 *, 0));
    M2C_FIELD(arg0, f32 *, 4) = (f32) (temp_f2 + M2C_FIELD(arg1, f32 *, 4));
    M2C_FIELD(arg0, f32 *, 8) = (f32) (temp_f3 + M2C_FIELD(arg1, f32 *, 8));
}
