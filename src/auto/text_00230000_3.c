/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00239630(s32, s32, s32, s32, f32);
M2C_UNK func_0024ae00(s32);
M2C_UNK func_0024af00(s32);
M2C_UNK func_0024afc0(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_00425B80;
#include "data/pieces/D_00449990.h"
extern M2C_UNK D_0044A800;
extern M2C_UNK D_0044A810;
extern M2C_UNK D_0044A820;
extern M2C_UNK D_00648038; /* src/data/bss_0064.c: s32 D_00648038[0x6] */
extern M2C_UNK D_00648050; /* src/data/bss_0064.c: f32 D_00648050[5] */
extern M2C_UNK D_00651310; /* src/data/bss_0065.c: Slot D_00651310[10] */
extern M2C_UNK D_00651BD8; /* src/data/bss_0065.c: void *D_00651BD8[0x4] */
extern M2C_UNK D_00651BE8; /* src/data/bss_0065.c: void *D_00651BE8[0x6] */
extern M2C_UNK func_0023ceb0;
extern s32 D_00454A24;
#include "data/pieces/D_00425C48.h"
#include "data/pieces/D_00425C68.h"
#include "data/pieces/D_00425C88.h"
s32 func_0011ef38(M2C_UNK *);
s32 func_00237600(s32);
s32 func_0023f0d8(s32, s32);
s32 func_0023f250(s32, s32);

void func_00232de0(void) {
    M2C_FIELD(&D_00425B80, s32 *, 0) = 0x5153484B;
    M2C_FIELD(&D_00425B80, s32 *, 4) = 0x01317F14;
}

s32 func_00233f40(s32 arg0, s32 arg1) {
    s32 *temp_a0;
    s32 temp_v0;

    temp_a0 = ((s8 *)&D_00425C48) + (((arg0 * 4) + arg1) * 4);
    temp_v0 = *temp_a0;
    *temp_a0 = 0;
    return temp_v0;
}

s32 func_00233f88(s32 arg0, s32 arg1) {
    s32 *temp_a0;
    s32 temp_v0;

    temp_a0 = ((s8 *)&D_00425C68) + (((arg0 * 4) + arg1) * 4);
    temp_v0 = *temp_a0;
    *temp_a0 = 0;
    return temp_v0;
}

s32 func_00233fd0(s32 arg0, s32 arg1) {
    s32 *temp_a0;
    s32 temp_v0;

    temp_a0 = ((s8 *)&D_00425C88) + (((arg0 * 4) + arg1) * 4);
    temp_v0 = *temp_a0;
    *temp_a0 = 0;
    return temp_v0;
}

void func_002366a8(s32 arg0, s32 arg1) {
    *(M2C_UNK *)((s8 *)&D_00648038 + (arg0 * 4)) = arg1;
}

s32 func_002366c0(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_00648038 + (arg0 * 4));
}

void func_002368f8(s32 arg0, f32 fparg0) {
    *(f32 *)((s8 *)&D_00648050 + (arg0 * 4)) = fparg0;
}

f32 func_00236910(s32 arg0) {
    return *(f32 *)((s8 *)&D_00648050 + (arg0 * 4));
}

void func_00237660(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 0) = arg2;
    func_00237600(arg0);
}

void func_0023c5a8(s32 arg0) {
    *(M2C_UNK *)((s8 *)&D_00651310 + (arg0 * 0xE0)) = 0;
}

void func_0023cf30(void) {
    memset(&D_0044A820, 0, 8);
    func_0024afc0(&D_0044A800, &D_00651BD8, ((M2C_UNK *)&D_00449990));
    func_0024afc0(&D_0044A810, &D_00651BE8, ((M2C_UNK *)&D_00449990));
    if (func_0011ef38(&func_0023ceb0) == 0) {
        func_0011ef10(0x28489, &func_0023ceb0);
    }
}

s32 func_0023f688(s32 arg0, s32 arg1) {
    s32 var_v1;

    if (M2C_FIELD(arg0, s32 *, 0) == 4) {
        var_v1 = D_00454A24;
    } else {
        var_v1 = M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x6C), s32 *, 0x3C);
    }
    if (var_v1 == 0) {
        return arg1;
    }
    return func_0023f250(arg0, func_0023f0d8(arg0, arg1));
}
#include "data/data_0044.h"
#include "data/pieces/D_00454A20.h"
#include "data/pieces/D_0044A820.h"
