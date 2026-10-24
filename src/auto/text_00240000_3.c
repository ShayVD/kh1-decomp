/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0066.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00123a88(s32, M2C_UNK *);
M2C_UNK func_00124218(s32);
M2C_UNK func_0023d1a0();
M2C_UNK func_00240810(void *);
M2C_UNK func_00241d60();
M2C_UNK func_0024aac8(M2C_UNK *);
M2C_UNK func_0025dd48(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK (*D_0066AA80)();
#include "data/pieces/D_0044A830.h"
#include "data/pieces/D_0044C5A0.h"
#include "data/pieces/D_0044DFD0.h"
#include "data/pieces/D_0044F380.h"
#include "data/pieces/D_0044F4D0.h"
#include "data/pieces/D_00451040.h"
#include "data/pieces/D_004919B0.h"
extern M2C_UNK D_00651E50;
M2C_UNK D_00652888[0x4] ALIGNED(8);
extern M2C_UNK D_00669A40; /* src/data/bss_0066.c: s16 D_00669A40[0xc] */
extern M2C_UNK D_0066AA90; /* src/data/bss_0066.c: V4f D_0066AA90 */
extern M2C_UNK func_002416a8;
extern s32 (*D_0066AA80)();
extern s32 *D_0066AA84;
extern s32 D_0046A53C;
extern s32 D_00669A5C;
extern s32 D_0066AAA0;
extern s8 D_00651E70;
extern u32 D_002C5958;
f32 func_0024ef88();
s32 func_0011ef38(M2C_UNK *);
s32 func_001eafd8(void);
s32 func_001f40c8(void);
void func_00114830(void);
void func_00131d68(s32, s32);
void func_001ba2a8(s32, s32);
void func_001efaf0(void);
void func_001f82b0(void);
void func_0024ce80(s32, s32);

void func_002408d8(s32 arg0) {
    func_00240810(&D_00651E70 + (arg0 * 0xD00));
}

void func_00241a10(s32 arg0, s32 arg1) {
    *(M2C_UNK *)((s8 *)&D_00652888 + (arg0 * 0xD00)) = arg1;
}

void func_00242a38(void) {
    func_0024aac8(((M2C_UNK *)&D_0044A830));
    func_0024aac8(((M2C_UNK *)&D_0044C5A0));
    func_0024aac8(((M2C_UNK *)&D_0044DFD0));
    func_0024aac8(((M2C_UNK *)&D_0044F380));
    func_0024aac8(((M2C_UNK *)&D_0044F4D0));
    func_0024aac8(((M2C_UNK *)&D_00451040));
    memset(&D_00651E50, 0, 0x4130);
    M2C_FIELD(&D_00651E50, s32 *, 0x4124) = (s32) (((u32) D_002C5958 >> 3) & 1);
    func_00241d60();
    if (func_0011ef38(&func_002416a8) == 0) {
        func_0011ef10(0x29811, &func_002416a8);
    }
}

void func_00242b68(s32 arg0) {
    *(M2C_UNK *)((s8 *)&D_00651E50 + (arg0 * 4)) = 0;
    if (arg0 == 4) {
        func_0023d1a0();
    }
}

s32 func_00242bf0(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_00651E50 + (arg0 * 4));
}

s32 func_0024d138(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        return 0;
    }
    func_0024ce80(func_001eafd8(), (s32) &D_00669A40);
    if (D_00669A5C != 0) {
        func_001ba2a8(0, func_001eafd8());
    }
    D_0046A53C = 1;
    func_00114830();
    func_001efaf0();
    return 4;
}

void func_0024daa0(void) {
    func_0025dd48((M2C_UNK *)&D_004919B0, 0x4807, 0, 0, 0, 0);
}

void func_0024f008(void) {
    func_00124218(*D_0066AA84);
    func_00123a88(*D_0066AA84, &D_0066AA90);
    func_0024ef88();
    if (D_0066AA80 != NULL) {
        D_0066AA80();
    }
}

s32 func_0024f1d0(s32 arg0) {
    s32 (*var_v0)();

    func_00131d68(arg0, D_0066AAA0);
    var_v0 = D_0066AA80;
    if (var_v0 != NULL) {
        var_v0 = var_v0();
    }
    return (s32) var_v0;
}
#include "data/data_0046.h"
#include "data/pieces/D_002C5958.h"
