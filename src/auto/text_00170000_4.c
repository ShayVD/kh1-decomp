/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00175be0(M2C_UNK *, s32, s32, M2C_UNK, s32, s32, M2C_UNK);
extern M2C_UNK D_00278B50;
extern M2C_UNK D_0035BD50;
extern M2C_UNK D_0035BFC0;
extern M2C_UNK D_0035C090;
extern M2C_UNK D_0035C140;
extern M2C_UNK D_0035C1F0;
extern M2C_UNK D_0035C2C0;
extern M2C_UNK D_0035C360;
#include "data/pieces/D_0035E710.h"
extern M2C_UNK D_0035FB20;
extern M2C_UNK D_00360F30;
extern M2C_UNK D_00362660;
extern M2C_UNK D_00362680;
extern M2C_UNK D_005758D0;
extern M2C_UNK D_005758E0;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002C5958;
extern s32 D_002E26A0;
extern s32 D_002E27A8;
extern s32 D_0035C700;
extern s32 D_003623F0;
extern s32 D_00362420;
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362450.h"
#include "data/pieces/D_00362454.h"
extern s32 D_00575890;
#include "data/pieces/D_003626C0.h"
extern void *D_00575780;
extern void *D_00575784;
f32 func_00120c18(s32);
f32 func_0017b0e0(void);
f32 func_002675a8(M2C_UNK *, M2C_UNK *);
s32 func_00130340(s32, s32, f32);
s32 func_001375d8();
void func_00176f08(s32, f32);
void func_00177a98(void);
void func_001784b0(void);
void func_00179d08(void);
void func_0017b120(void);
void func_0017b148(void);
void func_0017dee0(void);
void func_00180540(s32);
void func_00180aa8(s32);

void func_00170f50(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_v0;

    temp_v0 = D_00575784;
    D_00575784 = M2C_FIELD(temp_v0, void **, 0x10);
    M2C_FIELD(temp_v0, s32 *, 0) = (s32) *arg1;
    M2C_FIELD(temp_v0, s32 *, 8) = arg2;
    M2C_FIELD(temp_v0, s32 *, 4) = arg3;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg4;
    M2C_FIELD(temp_v0, void **, 0x10) = (void *) D_00575780;
    D_00575780 = temp_v0;
}

s32 func_00171890(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 3) || (var_v0 = 1, (arg2 < 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

s32 func_001718b8(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 0x7C) || (var_v0 = 1, ((arg2 < 0x75) != 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

s32 func_00171920(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 0x31) || (var_v0 = 1, ((arg2 < 0x2D) != 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

s32 func_00171948(s32 arg0, void *arg1, s32 arg2) {
    s32 var_v0;

    if ((arg2 >= 0xD) || (var_v0 = 1, ((arg2 < 3) != 0))) {
        var_v0 = arg2 == M2C_FIELD(arg1, s32 *, 0x4C);
    }
    return var_v0;
}

void func_00171e90(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) | 0x10);
}

void func_00171ea8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) & ~0x10);
}

void func_00171ec0(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) | 0x20);
}

void func_00171ed8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x38) = (s64) (M2C_FIELD(arg1, s64 *, 0x38) & ~0x20);
}

void func_00172010(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xF;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035BD50;
}

void func_001732b0(s32 arg0) {
    s32 temp_v1;
    s32 temp_v1_2;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x144);
    if (M2C_FIELD(arg0, s32 *, 0x70) == 8) {
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x164);
        if ((temp_v1 == 0xCE) || (temp_v1 == M2C_FIELD(temp_s0, s32 *, 0x4C))) {
            func_00130340(arg0, 0x40000075, 8.0f);
        }
    } else {
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x164);
        if ((temp_v1_2 == 0xCE) || (temp_v1_2 == M2C_FIELD(temp_s0, s32 *, 0x4C))) {
            func_00130340(arg0, M2C_FIELD(temp_s0, s32 *, 0x178), 8.0f);
        }
    }
    M2C_FIELD(temp_s0, s64 *, 0x38) = (s64) ((M2C_FIELD(temp_s0, s64 *, 0x38) & ~0x800) | 0x20000);
}

void func_00173740(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xC;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035BFC0;
}

void func_00173ad8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xA;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C090;
}

void func_00173ea8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xA;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C140;
}

void func_00174398(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xC;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C1F0;
}

void func_00174950(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 9;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C2C0;
}

void func_00174d98(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0xB;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035C360;
}

void func_00175a98(void) {
    if (D_0035C700 == 0) {
        func_00180540((s32) &D_00278B50);
        func_00180aa8((s32) &D_00278B50);
        D_0035C700 = 1;
    }
}

void func_00176008(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00175be0(((M2C_UNK *)&D_0035E710), arg0, arg1, -1, arg3, arg2, 1);
}

void func_00176040(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00175be0(&D_0035FB20, arg0, arg1, -1, arg3, arg2, 2);
}

void func_00176078(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00175be0(&D_00360F30, arg0, arg1, -1, arg3, arg2, 3);
}

s32 func_0017dbb8(void) {
    if (D_002E27A8 == 9) {
        (*(s32 *)&D_0036244C) = ((s32)D_00362434);
        (*(s32 *)&D_00362450) = ((s32)D_00362438);
        (*(s32 *)&D_00362454) = D_0036243C;
        func_00176f08(0, 0.0f);
        return 1;
    }
    (*(s32 *)&D_0036244C) = 0;
    (*(s32 *)&D_00362450) = 0;
    (*(s32 *)&D_00362454) = 0;
    return 0;
}

void func_0017de80(void) {
    if (D_002E27A8 != 0xA) {
        if ((D_002BC128 == 6) && (D_002BC130 == 0xA)) {
            func_00176f08(0xA, 0.0f);
        }
    }
}

void func_0017eaa0(void) {
    D_002E27A8 = 0;
    D_00575890 = 0;
    D_003623F0 = 0;
    func_00177a98();
    func_001784b0();
    func_0017b0e0();
    func_0017b120();
    func_0017b148();
    func_00179d08();
    func_0017dee0();
    D_00362420 = 0;
    (*(s32 *)&D_0036244C) = 0;
    (*(s32 *)&D_00362450) = 0;
    (*(s32 *)&D_00362454) = 0;
}

void func_0017f178(void) {
    M2C_FIELD(&D_00362680, f32 *, 0) = (f32) M2C_FIELD(&D_00362660, f32 *, 0);
    M2C_FIELD(&D_00362680, f32 *, 0xC) = (f32) M2C_FIELD(&D_00362660, f32 *, 0xC);
}

f32 func_0017f440(s32 arg0) {
    f32 temp_f0;
    f32 var_f0;
    f32 var_f1;
    f32 var_f20;

    var_f20 = 1.0f;
    if ((arg0 == D_002E26A0) && (func_001375d8() == 0)) {
        var_f0 = 1.0f;
        if (!(D_002C5958 & 0x104000)) {
            temp_f0 = func_00120c18(arg0 + 0x110);
            var_f0 = 1.0f;
            if (temp_f0 < 150.0f) {
                var_f1 = temp_f0 - 100.0f;
                if (var_f1 < 0.0f) {
                    var_f1 = 0.0f;
                }
                var_f20 = var_f1 / 50.0f;
                if (var_f20 < 0.19999999f) {
                    var_f20 = 0.19999999f;
                }
                goto block_8;
            }
        }
    } else {
block_8:
        var_f0 = var_f20;
    }
    return var_f0;
}
#include "data/data_002B.h"
#include "data/data_002E.h"
#include "data/data_0035.h"
#include "data/data_0036.h"
#include "data/data_0027.h"
#include "data/pieces/D_002BC128.h"
