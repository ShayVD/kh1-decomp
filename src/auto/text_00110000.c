/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"

M2C_UNK func_00102a48(M2C_UNK, M2C_UNK);
M2C_UNK func_001104e0();
M2C_UNK func_001112b8();
M2C_UNK func_001116b0(s32, s32);
M2C_UNK func_00112b18();
M2C_UNK func_001137f8();
M2C_UNK func_00113a00();
M2C_UNK func_0011c898(M2C_UNK);
M2C_UNK func_00120748(M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK func_00122330();
M2C_UNK func_0013cb98();
M2C_UNK func_0015f108();
M2C_UNK func_0017f290(s32);
M2C_UNK func_001b9ec0();
M2C_UNK func_001eacd0();
M2C_UNK func_001ed1c8();
M2C_UNK func_001ee4e8();
M2C_UNK func_00232ad0(M2C_UNK);
M2C_UNK func_00232d60();
M2C_UNK func_00266a10(M2C_UNK *);
extern M2C_UNK D_0048CF30;
extern M2C_UNK D_00F20000;
extern M2C_UNK func_00110218;
extern M2C_UNK func_00110fc8;
extern M2C_UNK func_00113fa8;
extern s32 D_002A6B80;
extern s32 D_002B6474;
extern s32 D_002BBE1C;
#include "data/pieces/D_002BC0A8.h"
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
extern s32 D_002BCAE0;
extern s32 D_002BCB34;
#include "data/pieces/D_002BCB60.h"
extern s32 D_002BCC1C;
extern s32 D_002BCC20;
extern s32 D_002BCC24;
extern s32 D_002BCC98;
extern s32 D_002BCDA8;
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
extern s32 D_002BD11C;
extern s32 D_002C596C;
extern s32 D_004D9244;
s32 D_004D9248 ALIGNED(8);
extern s32 D_004D925C;
extern s32 D_004D9274;
extern s32 D_004D92E0;
extern s32 D_004D9328;
extern s32 D_004D932C;
extern s32 D_004D9334;
extern s32 D_004D936C;
extern s32 D_004D9370;
extern s64 D_12000000;
void *func_0011ef10(M2C_UNK, M2C_UNK *);

void func_001104c0(void) {
    func_00266a10(&func_00110218);
}

void func_00111000(void) {
    D_002A6B80 = 0;
    D_002BCAE0 = 0;
    D_002BCB34 = 0;
}

void func_00111020(s32 arg0) {
    D_004D9244 = arg0;
    D_002BCAE0 = 0;
    func_00120748(&D_0048CF30, &D_00F20000, &func_00110fc8, 0);
}

void func_001115e0(void) {
    func_0017f290(((s32)D_002BCB60) + 0x4C);
}

void func_00111778(s32 arg0) {
    func_001116b0(D_002BC128, arg0);
}

void func_001117e0(void) {
    D_002BBE1C = 0;
    func_00232ad0(-1);
    func_001ee4e8();
    func_0015f108();
    func_0013cb98();
    func_001eacd0();
    func_001b9ec0();
    func_001112b8();
}

void func_001118a0(void) {
    D_004D9248 = 0;
}

void func_001118b0(void) {
    D_004D9248 = 1;
}

void func_001118c0(void) {
    if (D_004D9248 == 0) {
        func_00232d60();
    }
}

s32 func_00111b08(s32 arg0) {
    return arg0;
}

void func_00111f58(void) {
    D_004D925C = 1;
    D_002BCC24 = 1;
}

s32 func_00111f88(void) {
    D_004D925C = 2;
    return D_002BCC1C;
}

void func_00111fa0(s32 arg0) {
    D_002BCC1C = arg0 * 0x3C;
}

void func_00111fb8(s32 arg0) {
    D_004D9274 = arg0;
    D_002BCC20 = 0;
}

void func_00111fd0(s32 arg0) {
    D_002BCC20 = arg0;
}

s32 func_00111fe0(s32 arg0) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = D_002BCC20 + arg0;
    D_002BCC20 = temp_v0;
    if ((D_004D9274 == 0) || (var_v0 = 1, ((temp_v0 < D_004D9274) != 0))) {
        var_v0 = 0;
    }
    return var_v0;
}

void func_00112498(void) {
    D_002BCC98 = M2C_FIELD(((D_002BC130 << 6) + (*(s32 *)&D_002BCDAC)), s32 *, 4);
}

void func_001124c0(void) {
    D_002BC0A8.i |= 0x20;
}

void func_001124d8(void) {
    D_002BC0A8.i &= ~0x20;
}

void func_00112b80(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_002BCDA8 = arg3;
    D_002BC128 = arg0;
    D_002BC130 = arg1;
    D_002BC134 = arg2;
    func_00112b18();
}

s32 func_00112cf8(void) {
    func_0011c898(0);
    D_002B6474 = 0;
    func_00122330();
    return 4;
}

void func_00112e90(void) {

}

void func_00112fd0(s32 arg0) {
    D_004D92E0 = arg0;
}

s32 func_001137c8(s32 arg0, s32 arg1) {
    s32 var_a0;

    var_a0 = arg0;
    if ((var_a0 % arg1) != 0) {
        var_a0 = ((var_a0 / arg1) * arg1) + arg1;
    }
    return var_a0;
}

void func_00113ab0(s32 arg0) {
    if (arg0 == 0) {
        func_001104e0();
        D_12000000 = 0x22;
        return;
    }
    func_00113a00();
    func_001137f8();
}

void func_00113de0(void) {
    D_004D9328 = 0;
    D_004D932C = 0;
}

void func_00113df8(s32 arg0) {
    func_001ed1c8();
    D_004D932C = arg0;
}

s32 func_00114028(void) {
    func_00102a48(0x80, 0x10);
    M2C_FIELD(func_0011ef10(0x2E643, &func_00113fa8), s16 *, 2) = -1;
    return 4;
}

s32 func_00114068(void) {
    func_00102a48(0x80, 0x20);
    return 4;
}

void func_00114090(void) {
    D_002BD118 = 1;
}

void func_00114200(void) {
    D_002C596C = 1;
}

void func_00114210(void) {
    D_002C596C = 0;
}

void func_00114800(void) {
    D_002BD11C = 1;
}

void func_00114810(void) {
    D_002BD11C = 0;
}

void func_00114820(void) {
    D_004D9334 = 1;
}

void func_00114830(void) {
    D_004D9334 = 0;
}

void func_00114c00(void) {
    D_004D936C = 0;
    D_004D9370 = 0;
}
#include "data/bss_004D_mixed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_0048.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002BCC1C.h"
#include "data/pieces/D_002BCC24.h"
