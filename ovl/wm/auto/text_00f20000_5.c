/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001efaf0();
M2C_UNK func_001efb18(M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_00F87CE0;
extern M2C_UNK D_00F87DE0;
extern M2C_UNK func_00f20328;
extern s32 D_00F850D8;
extern s32 D_00FBA800;
extern s32 D_00FBAA10;
s32 func_0010a0d8(void);
s32 func_001efbb8(s32);
void func_0010a320(void);
void func_00176c60(s32);
void func_001ba910(s32);
void func_001bfac8(void);
void func_00248b00(void);
void func_00f680a0();

void func_00f20360(void) {
    func_00248b00();
    D_00FBAA10 = D_00F850D8;
    func_00f680a0();
    func_0010a0d8();
    func_0010a320();
    func_00176c60(0);
    func_001ba910(&func_00f20328);
    D_00FBA800 = 4;
    for (;;) {
        func_001bfac8();
    }
}

s32 func_00f2b6f0(s32 arg0) {
    s32 temp_s0;
    s32 var_s1;
    s32 var_v0;

    var_s1 = 0;
    func_001efb18(&D_00F87CE0, &D_00F87DE0);
    switch (arg0) {
    case 2:
        var_s1 = 0xD;
        break;
    case 3:
        var_s1 = 6;
        break;
    case 4:
        var_s1 = 0xC;
        break;
    case 5:
        var_s1 = 0xB;
        break;
    case 8:
        var_s1 = 4;
        break;
    case 9:
        var_s1 = 3;
        break;
    case 10:
        var_s1 = 0xA;
        break;
    case 11:
        var_s1 = 5;
        break;
    case 15:
        var_s1 = 7;
        break;
    case 16:
        var_s1 = 1;
        break;
    case 12:
    case 17:
        var_s1 = 2;
        break;
    case 13:
    case 18:
        var_s1 = 8;
        break;
    }
    var_v0 = 0;
    if (var_s1 != 0) {
        temp_s0 = func_001efbb8(var_s1);
        func_001efaf0();
        var_v0 = temp_s0;
    }
    return var_v0;
}
