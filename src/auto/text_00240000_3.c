/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00123a88(s32, M2C_UNK *);
M2C_UNK func_00124218(s32);
M2C_UNK func_0023d1a0();
M2C_UNK func_00240810(void *);
M2C_UNK func_00241d60();
M2C_UNK func_002432d8(s32, s32, s32, s32);
M2C_UNK func_00248798(s32, s32, s32, s32);
M2C_UNK func_00249a48(void *, M2C_UNK);
M2C_UNK func_0024aac8(M2C_UNK *);
M2C_UNK func_0024ae00(s32);
M2C_UNK func_0024af00(s32);
M2C_UNK func_0024afc0(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_0025dd48(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_00267620();
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK (*D_0066AA80)();
extern M2C_UNK D_0044A830;
extern M2C_UNK D_0044C5A0;
extern M2C_UNK D_0044DFD0;
extern M2C_UNK D_0044F380;
extern M2C_UNK D_0044F4D0;
extern M2C_UNK D_00451040;
extern M2C_UNK D_00469CA0;
extern M2C_UNK D_00469F50;
extern M2C_UNK D_004919B0;
extern M2C_UNK D_00651E50;
extern M2C_UNK D_00652888;
extern M2C_UNK D_00669350;
extern M2C_UNK D_00669930;
extern M2C_UNK D_00669A10;
extern M2C_UNK D_00669A40;
extern M2C_UNK D_0066AA90;
extern M2C_UNK func_002416a8;
extern M2C_UNK func_002491f8;
extern s32 (*D_0066AA80)();
extern s32 *D_0066AA84;
extern s32 D_00469F60;
extern s32 D_0046A53C;
extern s32 D_00669920;
extern s32 D_00669A5C;
extern s32 D_0066AAA0;
extern s8 D_00431F30;
extern s8 D_00651E70;
extern u32 D_002C5958;
f32 func_0024ef88();
s32 func_0011ef38(M2C_UNK *);
s32 func_001eafd8(void);
s32 func_001f40c8(void);
s32 func_002388b8(s32, s32, s32);
void func_00114830(void);
void func_00131d68(s32, s32);
void func_001ba2a8(s32, s32);
void func_001efaf0(void);
void func_001f82b0(void);
void func_0024aa48(s32, s32, s32);
void func_0024ce80(s32, s32);

void func_002408d8(s32 arg0) {
    func_00240810(&D_00651E70 + (arg0 * 0xD00));
}

void func_00241a10(s32 arg0, s32 arg1) {
    *(M2C_UNK *)((s8 *)&D_00652888 + (arg0 * 0xD00)) = arg1;
}

void func_00242a38(void) {
    func_0024aac8(&D_0044A830);
    func_0024aac8(&D_0044C5A0);
    func_0024aac8(&D_0044DFD0);
    func_0024aac8(&D_0044F380);
    func_0024aac8(&D_0044F4D0);
    func_0024aac8(&D_00451040);
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

void func_002432c8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

void func_00243380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 != 0) {
        func_0024ae00(arg1);
    }
    func_0024af00(arg1);
    func_002432d8(arg1, arg2, arg3, arg4);
}

void func_00247cc8(s32 arg0) {
    func_00249a48(&D_00431F30 + (arg0 * 0x1770), 1);
}

void func_002485b8(s32 arg0) {
    M2C_FIELD(&D_00669350, s32 *, 0) = 1;
    M2C_FIELD(&D_00669350, s32 *, 4) = arg0;
}

void func_00248788(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

void func_00248840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 != 0) {
        func_0024ae00(arg1);
    }
    func_0024af00(arg1);
    func_00248798(arg1, arg2, arg3, arg4);
}

void func_00248fb8(s32 arg0, s32 arg1) {
    func_0024aa48(arg0, (s32) &D_00669930, arg1);
    D_00669920 = func_002388b8((s32) &D_00669930, 1, D_00669920);
}

void func_00249250(void) {
    D_00469F60 = 0;
    func_0024aac8(&D_00469CA0);
    func_0024afc0(&D_00469F50, &D_00669A10, &D_00469CA0);
    if (func_0011ef38(&func_002491f8) == 0) {
        func_0011ef10(0x28489, &func_002491f8);
    }
}

void func_00249518(void *arg0, f32 fparg0) {
    func_00267620();
    M2C_FIELD(arg0, f32 *, 0x28) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x14) = fparg0;
    M2C_FIELD(arg0, f32 *, 0) = fparg0;
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
    func_0025dd48(&D_004919B0, 0x4807, 0, 0, 0, 0);
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
