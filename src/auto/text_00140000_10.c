/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
M2C_UNK func_0012ec88(s32, void *);
M2C_UNK func_0013bf20();
M2C_UNK func_0013fc80();
M2C_UNK func_00141138();
M2C_UNK func_00144e38();
M2C_UNK func_0014cb38();
M2C_UNK func_0014cd38(void *);
M2C_UNK func_0014d890();
M2C_UNK func_0014e4b8();
M2C_UNK func_0014e668(void *, u8, s32, f32, f32);
M2C_UNK func_0014e878(void *, u8, s32, f32, f32);
M2C_UNK func_00150cd8();
M2C_UNK func_001524c8();
M2C_UNK func_00153d28();
M2C_UNK func_001556a8();
M2C_UNK func_00158648();
M2C_UNK func_001598e0();
M2C_UNK func_0015a418();
M2C_UNK func_0015d560();
M2C_UNK func_0015dbf8();
M2C_UNK func_0015e128();
M2C_UNK func_0015e7a8();
M2C_UNK func_0015ea40();
M2C_UNK func_002675a8(void *, s32);
M2C_UNK func_00267e90(s32, s32, f32);
#include "data/pieces/D_00350D88.h"
extern f32 D_002BBDFC;
#include "data/pieces/D_002E26A0.h"
s32 func_00122ff8(s32);

void func_0014d6b0(void *arg0, s32 arg1) {
    f32 temp_f3;

    func_00267e90(arg1, arg0 + 0x3C0, D_002BBDFC);
    M2C_FIELD(arg0, f32 *, 0x3C0) = (f32) (M2C_FIELD(arg0, f32 *, 0x3C0) * M2C_FIELD(arg0, f32 *, 0x3CC));
    temp_f3 = M2C_FIELD(arg0, f32 *, 0x3C4) + (M2C_FIELD(arg0, f32 *, 0x3B4) * D_002BBDFC);
    M2C_FIELD(arg0, f32 *, 0x3C8) = (f32) (M2C_FIELD(arg0, f32 *, 0x3C8) * M2C_FIELD(arg0, f32 *, 0x3CC));
    M2C_FIELD(arg0, f32 *, 0x3C4) = temp_f3;
    if (temp_f3 > 20.0f) {
        M2C_FIELD(arg0, f32 *, 0x3C4) = 20.0f;
    }
    M2C_FIELD(arg0, f32 *, 0x3B0) = (f32) (M2C_FIELD(arg0, f32 *, 0x3B0) + D_002BBDFC);
    func_0014cd38(arg0);
}

s32 func_0014d760(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 0;
    if (arg1 != 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

s32 func_0014d878(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 2;
    if (arg1 == 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

void func_0014eab0(void *arg0, s32 arg1) {
    s32 sp[4];    f32 var_f20;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x134);
    if ((temp_v1 != NULL) && (M2C_FIELD(temp_v1, u8 *, 5) != 0)) {
        var_f20 = M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x14), f32 *, 0xC);
    } else {
        var_f20 = 0.0f;
    }
    func_002675a8(sp, (*(s32 *)&D_002E26A0) + 0x10);
    M2C_FIELD(sp, f32 *, 0x4) += -200.0f;
    func_0014e668(sp, M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u8 *, 0x58), arg1, var_f20 + 100.0f, var_f20 + 600.0f);
}

void func_0014eb60(void *arg0, s32 arg1) {
    s32 sp[4];    f32 var_f20;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x134);
    if ((temp_v1 != NULL) && (M2C_FIELD(temp_v1, u8 *, 5) != 0)) {
        var_f20 = M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x14), f32 *, 0xC);
    } else {
        var_f20 = 0.0f;
    }
    func_002675a8(sp, (*(s32 *)&D_002E26A0) + 0x10);
    M2C_FIELD(sp, f32 *, 0x4) += -200.0f;
    func_0014e878(sp, M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u8 *, 0x58), arg1, var_f20 + 100.0f, var_f20 + 600.0f);
}

void func_0014f868(void) {
    s8 *var_v0;
    s32 var_v1;

    var_v1 = 0x3A;
    var_v0 = &D_00350D88;
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s32 *, 0) = 0;
        M2C_FIELD(var_v0, s32 *, 4) = 0;
        M2C_FIELD(var_v0, s32 *, 8) = 0;
        M2C_FIELD(var_v0, s32 *, 0xC) = 0;
        M2C_FIELD(var_v0, s32 *, 0x10) = 0;
        M2C_FIELD(var_v0, s32 *, 0x14) = 0;
        M2C_FIELD(var_v0, s32 *, 0x18) = 0;
        M2C_FIELD(var_v0, s32 *, 0x1C) = 0;
        var_v0 += 0x20;
    } while (var_v1 >= 0);
    func_0015e7a8();
    func_0015ea40();
    func_0015e128();
    func_0014e4b8();
    func_0014cb38();
    func_001524c8();
    func_00150cd8();
    func_00141138();
    func_0015d560();
    func_00153d28();
    func_0015dbf8();
    func_001556a8();
    func_0014d890();
    func_0013fc80();
    func_00158648();
    func_00144e38();
    func_001598e0();
    func_0015a418();
    func_0013bf20();
}

void func_0014f948(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x470) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x470) = arg1;
        if (func_00122ff8(arg1) != 0) {
            func_0012ec88(arg1, arg0 + 0x460);
        }
    }
}
#include "data/pieces/D_002BBDFC.h"
