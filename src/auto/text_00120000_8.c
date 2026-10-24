/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004F.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_0011f090(M2C_UNK *, M2C_UNK, s32);
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
M2C_UNK func_0011fd60(s32, u32, s32);
M2C_UNK func_00120438(void *, s32);
M2C_UNK func_00121748(M2C_UNK *, M2C_UNK *);
M2C_UNK func_00122c08();
M2C_UNK func_00124a28();
M2C_UNK func_00124b90();
M2C_UNK func_00125240();
M2C_UNK func_00128b20();
M2C_UNK func_0012b738();
M2C_UNK func_0012fc58();
M2C_UNK func_0012ff80();
M2C_UNK func_00133520();
M2C_UNK func_00133628();
M2C_UNK func_001356a8();
M2C_UNK func_0013bd08();
M2C_UNK func_0013ce98();
M2C_UNK func_00142340();
M2C_UNK func_00146590();
M2C_UNK func_00148e98();
M2C_UNK func_00148f08();
M2C_UNK func_0014a090();
M2C_UNK func_0014c330();
M2C_UNK func_001561f8();
M2C_UNK func_00157dc8();
M2C_UNK func_001590a8();
M2C_UNK func_0016f548();
M2C_UNK func_00176c60(M2C_UNK);
M2C_UNK func_002672f8(void *, void *, void *);
M2C_UNK func_002674f0(s32, void *, void *, f32);
M2C_UNK func_002675a8(M2C_UNK *, s32);
M2C_UNK func_00267810(void *, M2C_UNK *, f32);
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C5C80.h"
extern M2C_UNK D_004E49E8; /* src/data/bss_004E.c: u8 D_004E49E8[0x18] */
extern M2C_UNK D_004F8270; /* src/data/bss_004F.c: D6 D_004F8270[0x5] */
extern M2C_UNK func_001274c8;
extern f32 D_002BBDFC;
#include "data/pieces/D_002E27A4.h"
extern s32 D_002C5958;
#include "data/pieces/D_002C5C48.h"
extern s32 D_004F82C0;
f32 func_00120c88(f32);
s32 strlen(s32);
void *func_0015ed80(M2C_UNK, M2C_UNK *);

s32 func_001200f8(s32 arg0) {
    s32 temp_v0;
    s32 var_a0;
    s32 var_a3;
    s8 *temp_v0_2;

    temp_v0 = strlen(arg0);
    var_a3 = 0;
    var_a0 = 0;
    if (temp_v0 > 0) {
        do {
            temp_v0_2 = arg0 + var_a3;
            var_a3 += 1;
            var_a0 = (var_a0 * 2) ^ ((s32) (*temp_v0_2 << 0x10) % 69665);
        } while (var_a3 < temp_v0);
    }
    return var_a0;
}

s32 func_00120580(s32 arg0, s32 arg1) {
    s32 sp[12];
    func_00120438(sp, arg0);
    func_0011fd60(M2C_FIELD(sp, M2C_UNK *, 0x0), (u32) (M2C_FIELD(sp, M2C_UNK *, 0x4) + 0x7FF) >> 0xB, arg1);
    D_002C5C48 = M2C_FIELD(sp, M2C_UNK *, 0x4);
    FlushCache(0);
    FlushCache(2);
    return D_002C5C48;
}

void func_001208e0(s32 arg0) {
    func_0011f090(&D_004E49E8, 0, arg0);
}

s32 func_00120908(void) {
    func_0011f130(&D_004E49E8, 0);
    return 0;
}

void func_00121b38(s32 arg0, s32 arg1) {
    s32 sp[8];
    func_002675a8(sp, arg0);
    func_002675a8(&M2C_FIELD(sp, M2C_UNK *, 0x10), arg1);
    M2C_FIELD(sp, s32 *, 0x4) = 0;
    M2C_FIELD(sp, s32 *, 0x14) = 0;
    func_00121748(sp, &M2C_FIELD(sp, M2C_UNK *, 0x10));
}

void func_00122130(void) {
    D_002C5958 = 0;
    func_0013ce98();
    func_00125240();
    func_00124b90();
    func_00128b20();
    func_00133628();
    func_00148f08();
    func_00142340();
    func_00157dc8();
    func_001561f8();
    func_0014a090();
    func_0012ff80();
}

void func_001223b8(void) {
    func_00176c60(0);
    func_0013bd08();
    func_001590a8();
    func_00124a28();
    func_00133520();
    func_00146590();
    func_00148e98();
    func_0012b738();
    func_00122c08();
    func_0014c330();
    func_001356a8();
    func_0012fc58();
    func_0016f548();
}

s32 func_00122430(void *arg0) {
    M2C_UNK (*temp_v0)(s32);
    f32 temp_f0;
    f32 var_f20;
    s32 var_s1;

    var_s1 = 0;
    temp_f0 = M2C_FIELD(arg0, f32 *, 0x44) - D_002BBDFC;
    var_f20 = temp_f0 / M2C_FIELD(arg0, f32 *, 0x40);
    M2C_FIELD(arg0, f32 *, 0x44) = temp_f0;
    if (var_f20 < 0.0f) {
        temp_v0 = M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x48);
        var_f20 = 0.0f;
        if (temp_v0 != NULL) {
            temp_v0(M2C_FIELD(arg0, s32 *, 0x10));
        }
        var_s1 = 4;
    }
    func_002674f0(M2C_FIELD(arg0, s32 *, 0x10) + 0x30, arg0 + 0x20, arg0 + 0x30, var_f20);
    return var_s1;
}

void func_00122c70(void) {
    s8 *var_a0;
    s32 temp_v0;
    s32 var_a1;

    var_a1 = 0x1E;
    var_a0 = &D_002C5C80;
    do {
        if (M2C_FIELD(var_a0, s32 *, 0) != 0) {
            temp_v0 = M2C_FIELD(var_a0, s32 *, 4);
            if (temp_v0 & 8) {
                M2C_FIELD(var_a0, s32 *, 4) = (s32) (temp_v0 | 0x10);
            }
        }
        var_a1 -= 1;
        var_a0 += 0x40;
    } while (var_a1 >= 0);
}

void func_00124d58(void *arg0, void *arg1, f32 fparg0, f32 fparg1) {
    s32 sp[16];
    func_00267810(sp, ((M2C_UNK *)&D_002C58D0), -func_00120c88(D_002E27A4));
    func_002672f8(arg1, sp, arg0);
    M2C_FIELD(arg1, f32 *, 0) = (f32) -M2C_FIELD(arg1, f32 *, 0);
    M2C_FIELD(arg1, f32 *, 0xC) = fparg1;
    func_00267810(sp, ((M2C_UNK *)&D_002C58D0), fparg0);
    func_002672f8(arg1, sp, arg1);
}

s32 func_00128440(void) {
    D_004F82C0 = 0;
    M2C_FIELD(func_0015ed80(0xEC53, &func_001274c8), M2C_UNK **, 0x10) = &D_004F8270;
    M2C_FIELD(func_0015ed80(0xB1BB, &func_001274c8), M2C_UNK **, 0x10) = &D_004F8270;
    return 0;
}
#include "data/bss_0051_mixed.h"
#include "data/data_002C.h"
#include "data/data_0035.h"
#include "data/pieces/D_002BBDFC.h"
