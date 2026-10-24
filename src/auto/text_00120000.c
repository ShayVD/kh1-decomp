/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004F.h"
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_001247e8(s32);
M2C_UNK func_00124c68();
M2C_UNK func_00127340();
M2C_UNK func_00132e38();
M2C_UNK func_0013cfe8(s32, M2C_UNK, s32);
M2C_UNK func_0013f2c0();
M2C_UNK func_001478e0();
M2C_UNK func_00148e60();
M2C_UNK func_0014f868();
M2C_UNK func_00151b90();
M2C_UNK func_00266f38(s32, s32);
M2C_UNK func_0026a9d0(s32);
M2C_UNK func_0026b978(f32);
M2C_UNK func_0026b9a8(f32, f32);
M2C_UNK func_00270b40();
extern M2C_UNK D_004F6EC0; /* src/data/bss_004F.c: TPool D_004F6EC0 */
M2C_UNK D_004F6ED0[0xa0] ALIGNED(16);
extern M2C_UNK func_00120908;
extern f32 D_002BBDFC;
extern f32 D_002E27A0;
extern f32 D_004F77E4;
extern s32 D_004F6EB8; /* src/data/bss_004F.c: u32 *D_004F6EB8 */
extern s32 D_00514F14;
f32 func_00121748();
s32 func_00120930();
s32 func_00123488();
s32 func_0025ed28(s32, M2C_UNK, M2C_UNK);
s32 func_00266c08(M2C_UNK);
s32 func_0026a530(M2C_UNK);
void *func_0011ef10(M2C_UNK, M2C_UNK *);
void *func_00120190(s32);
void *func_00121de0();

void func_00120038(s32 *arg0) {
    *arg0 = 0;
}

void func_00120888(s32 arg0) {
    void *temp_v0;

    if (func_0026a530(1) == 2) {
        temp_v0 = func_00120190(arg0);
        if (temp_v0 != NULL) {
            func_0026a9d0(M2C_FIELD(temp_v0, s32 *, 8));
        }
    }
}

void func_001209d8(void) {
    s32 temp_a0;
    s32 temp_s0;

    temp_s0 = func_00120930();
    temp_a0 = temp_s0;
    do {

    } while (func_0025ed28(temp_a0, 0, 0) < 0);
}

void func_00120a70(void) {
    M2C_FIELD(func_0011ef10(0x2D2A8, &func_00120908), s16 *, 2) = -1;
}

void func_00121840(void) {
    func_0026b978(func_00121748());
}

f32 func_00121b08(f32 fparg0) {
    f32 var_f12;

    var_f12 = fparg0;
    if (var_f12 > 0.0f) {
        var_f12 -= D_002BBDFC;
        if (var_f12 < 0.0f) {
            var_f12 = 0.0f;
        }
    }
    return var_f12;
}

void func_00121eb0(void) {
    s32 *temp_v1;
    void *temp_v0;

    temp_v0 = func_00121de0();
    temp_v1 = M2C_FIELD(temp_v0, s32 **, 0xC);
    if (temp_v1 != NULL) {
        *temp_v1 = 0;
    }
    M2C_FIELD(temp_v0, s32 **, 0xC) = NULL;
}

void func_001220b8(void) {
    D_004F6EB8 -= 8;
}

void func_001220d0(void) {
    func_00270b40();
}

void func_001220e8(void) {
    func_00148e60();
    func_001478e0();
    func_0013f2c0();
    func_00127340();
    func_0014f868();
    func_00151b90();
    func_00132e38();
}

void func_00122768(s32 *arg0) {
    *arg0 = 0;
}

void func_00122bd8(void) {
    func_0011efa8(&D_004F6EC0, &D_004F6ED0, 0x50, 8);
}

void func_00123460(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x388);
    temp_v1 = temp_v0 - 1;
    if (temp_v0 > 0) {
        M2C_FIELD(arg0, s32 *, 0x388) = temp_v1;
        M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x37C);
    }
}

void func_001248e8(void) {
    s32 temp_v0;

    temp_v0 = func_00123488();
    if (temp_v0 != 0) {
        func_001247e8(temp_v0);
    }
}

void func_00124ce0(void) {
    D_004F77E4 = D_002E27A0;
    func_00124c68();
}

void func_00124d28(void *arg0, void *arg1) {
    func_0026b9a8(M2C_FIELD(arg0, f32 *, 0) - M2C_FIELD(arg1, f32 *, 0), M2C_FIELD(arg0, f32 *, 8) - M2C_FIELD(arg1, f32 *, 8));
}

s32 func_001274c8(void *arg0) {
    func_00266f38(func_00266c08(2), M2C_FIELD(arg0, s32 *, 0x10));
    return 2;
}
#include "data/bss_0051_mixed.h"
#include "data/data_0029.h"
#include "data/data_002B.h"
#include "data/data_002E.h"
#include "data/data_0035.h"
#include "data/pieces/D_002BBDFC.h"
