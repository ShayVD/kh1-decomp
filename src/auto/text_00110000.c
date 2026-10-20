/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"

M2C_UNK func_00102a48(M2C_UNK, M2C_UNK);
M2C_UNK func_00104528();
M2C_UNK func_001047c8();
M2C_UNK func_001104e0();
M2C_UNK func_001112b8();
M2C_UNK func_001116b0(s32, s32);
M2C_UNK func_00112b18();
M2C_UNK func_001137f8();
M2C_UNK func_00113a00();
M2C_UNK func_00118060(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0011c898(M2C_UNK);
M2C_UNK func_0011e1c8(s32);
M2C_UNK func_0011f130(M2C_UNK *, s32);
M2C_UNK func_0011f2e0(M2C_UNK *, s32);
M2C_UNK func_00120748(M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK func_001220d0();
M2C_UNK func_00122330();
M2C_UNK func_0013cb98();
M2C_UNK func_0015ef60();
M2C_UNK func_0015f108();
M2C_UNK func_0017f290(s32);
M2C_UNK func_001b9ec0();
M2C_UNK func_001eacd0();
M2C_UNK func_001ecc68();
M2C_UNK func_001ecfd8();
M2C_UNK func_001ed1c8();
M2C_UNK func_001ed278();
M2C_UNK func_001ed2d8();
M2C_UNK func_001ed370();
M2C_UNK func_001ed3c0();
M2C_UNK func_001ed4b8();
M2C_UNK func_001ed520();
M2C_UNK func_001ed560();
M2C_UNK func_001ed5a8();
M2C_UNK func_001ed600();
M2C_UNK func_001ee4e8();
M2C_UNK func_00232ad0(M2C_UNK);
M2C_UNK func_00232d60();
M2C_UNK func_00266a10(M2C_UNK *);
extern M2C_UNK D_0048CF30;
extern M2C_UNK D_004E3A48; /* src/data/bss_004E.c: u8 D_004E3A48[0x10] */
extern M2C_UNK D_004F2A00; /* src/data/bss_004F.c: char D_004F2A00[0x800] */
extern M2C_UNK D_00F20000;
extern M2C_UNK func_00110218;
extern M2C_UNK func_00110fc8;
extern M2C_UNK func_00113fa8;
extern f32 D_002BBDFC;
extern f32 D_002C5970;
extern s32 D_002A6B80;
extern s32 D_002B6474;
extern s32 D_002BBE1C;
extern s32 D_002BC0A8;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
extern s32 D_002BCAE0;
extern s32 D_002BCB34;
extern s32 D_002BCB60;
extern s32 D_002BCC1C;
extern s32 D_002BCC20;
extern s32 D_002BCC24;
extern s32 D_002BCC98;
extern s32 D_002BCDA8;
extern s32 D_002BCDAC;
extern s32 D_002BD118;
extern s32 D_002BD11C;
extern s32 D_002C1308;
extern s32 D_002C130C;
extern s32 D_002C1390;
extern s32 D_002C1394;
extern s32 D_002C5950;
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
extern s32 D_004E3A40;
extern s64 D_12000000;
s32 func_0011e248();
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
    func_0017f290(D_002BCB60 + 0x4C);
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
    D_002BCC98 = M2C_FIELD(((D_002BC130 << 6) + D_002BCDAC), s32 *, 4);
}

void func_001124c0(void) {
    D_002BC0A8 |= 0x20;
}

void func_001124d8(void) {
    D_002BC0A8 &= ~0x20;
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

void func_00118d78(s32 arg0) {
    func_001047c8();
    func_00118060(arg0, 3, 0, -1);
    func_00104528();
}

void func_0011c768(s32 arg0) {
    D_002C1308 = arg0;
}

void func_0011c778(void) {
    D_002C1308 = 0;
}

void func_0011c788(void) {
    D_002C130C = 1;
}

void func_0011c798(void) {
    D_002C130C = 0;
}

void func_0011c7a8(void) {
    func_001ed4b8();
}

void func_0011c7c0(void) {
    func_001ed560();
}

void func_0011c7d8(void) {
    func_001ed520();
}

void func_0011c7f0(void) {
    func_001ed5a8();
}

void func_0011c808(void) {
    func_001ed600();
}

void func_0011c820(void) {
    func_001ecfd8();
}

void func_0011c838(void) {
    func_001ed278();
}

void func_0011c850(void) {
    func_001ed2d8();
}

void func_0011c868(void) {
    func_001ed370();
}

void func_0011c880(void) {
    func_001ed3c0();
}

void func_0011c9a0(void) {
    D_004E3A40 = 0;
}

void func_0011c9b0(void) {
    D_004E3A40 = 1;
}

void func_0011e220(s32 arg0) {
    func_001ecc68();
    func_0011e1c8(arg0);
}

void func_0011e340(void) {
    D_002C1394 = func_0011e248();
}

void func_0011e518(void) {
    D_002C1390 = 1;
}

void func_0011e528(void) {
    D_002C1390 = 0;
}

s32 func_0011eda8(void) {
    func_0015ef60();
    return 0;
}

void func_0011eeb0(void) {
    D_002C5970 = 1.0f / D_002BBDFC;
    func_0011f130(&D_004E3A48, D_002C596C);
    D_002C5950 ^= 1;
}

void func_0011ef38(s32 arg0) {
    func_0011f2e0(&D_004E3A48, arg0);
}

void *func_0011f058(void *arg0, s32 arg1) {
    void *var_v0;
    void *var_v1;

    var_v1 = M2C_FIELD(arg0, void **, 8);
    var_v0 = NULL;
    if ((var_v1 != NULL) && (var_v1 != arg1)) {
loop_2:
        var_v0 = var_v1;
        var_v1 = M2C_FIELD(var_v0, void **, 8);
        if (var_v1 != NULL) {
            if (var_v1 != arg1) {
                goto loop_2;
            }
        }
    }
    return var_v0;
}

s32 func_0011f2d0(u16 *arg0) {
    return *arg0 & 1;
}

void *func_0011fb38(s64 arg0, s64 arg1, void *arg2) {
    M2C_FIELD(arg2, s64 *, 0) = arg1;
    M2C_FIELD(arg2, s64 *, 8) = arg0;
    return arg2 + 0x10;
}

M2C_UNK *func_0011fd30(void) {
    return &D_004F2A00;
}

void func_0011fd40(void) {
    func_001220d0();
    func_001104e0();
}
#include "data/bss_004D_mixed.h"
