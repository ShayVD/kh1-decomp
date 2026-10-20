/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0054.h"

M2C_UNK func_0011d350(M2C_UNK, s32);
M2C_UNK func_001477c8(s32);
M2C_UNK func_001ed128(M2C_UNK, s32);
extern M2C_UNK D_00304C70;
extern M2C_UNK D_00308C70;
extern M2C_UNK D_00531B70; /* src/data/bss_0053.c: LdEnt D_00531B70[128] */
extern M2C_UNK D_0054B808; /* src/data/bss_0054.c: u8 D_0054B808[0x10] */
extern M2C_UNK func_0013fd10;
extern M2C_UNK func_0013fd20;
extern M2C_UNK func_0013fd38;
extern M2C_UNK func_0013fd60;
extern M2C_UNK func_001406d0;
extern M2C_UNK func_00140960;
extern M2C_UNK func_00140ee0;
extern M2C_UNK func_00140f08;
extern M2C_UNK func_00140f88;
extern M2C_UNK func_00141018;
extern M2C_UNK func_00141078;
extern M2C_UNK func_0014f778;
extern M2C_UNK func_0014f828;
extern s32 D_002C5958;
extern s32 D_002E26A0;
extern s32 D_00304BE8;
extern s32 D_00350CE0;
extern s32 D_0054C438;
extern s32 D_0054C43C;
f32 func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK *);
f32 func_00176310(s32);
s32 func_0011f090(s32, s32, s32);
s32 func_00130340(s32, s32, f32);
s32 func_00130398(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
s32 func_00147c98(s32, s32, s32);
s32 func_00148600(s32, s32, s32, f32);
s32 func_00148768(s32, s32, s32, s32, f32);
s32 func_00148968(s32, s32, s32);
s32 func_00148cb0(s32, f32);
s32 func_001496c8(s32, s32);
s32 func_00149fa0(void);
s32 func_0014f658(s32, s32);
s32 func_002675a8(s32, s32);
void func_0011d1e0(s32, s32, s32, s32);
void func_001412f8(s32, s32);
void func_00141ab8(s32);
void func_00149968(void);

void func_00140d50(s32 arg0, s32 arg1) {
    func_00130398(arg0, 0x01000007, 8.0f);
    func_00130578(arg0, 0x40000000, 8.0f);
    func_002675a8(arg1, arg0 + 0x30);
}

void func_00141138(void) {
    func_0014f830(9, 0x101, &func_0013fd10, &func_0013fd20, &func_001406d0, NULL, NULL, 0, NULL);
    func_0014f830(0xA, 0x101, &func_0013fd38, &func_0013fd60, &func_00140960, &func_00140ee0, &func_00140f08, 0, &func_00140f88);
    func_0014f830(0xB, 0x101, &func_00141018, NULL, &func_00141078, &func_0014f778, &func_0014f828, 0, NULL);
}

void func_00145240(Actor *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), s32 *, 0x154);
    if (temp_v1 != 0) {
        func_00176310(temp_v1);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), s32 *, 0x154) = 0;
        func_0011d350(0xA8, arg0->unk004 + 1);
    }
}

void func_00146928(s32 arg0) {
    s8 *var_v1;
    s32 var_a0;

    func_001ed128(0, arg0);
    func_001ed128(3, arg0);
    var_v1 = &D_00531B70;
    var_a0 = 0x7F;
    do {
        if (M2C_FIELD(var_v1, s32 *, 0) == arg0) {
            M2C_FIELD(var_v1, s32 *, 4) = 0;
        }
        var_a0 -= 1;
        var_v1 += 8;
    } while (var_a0 >= 0);
}

void func_001477e0(s32 arg0) {
    func_001477c8(*(M2C_UNK *)((s8 *)&D_00308C70 + (arg0 * 4)));
}

s32 func_00147d18(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_0011f090((s32) &D_0054B808, 0, arg0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 0x1C) = 0;
    }
    return temp_v0;
}

s32 func_00148878(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_00147c98(arg0, arg1, 0x4E20);
    if (temp_v0 != 0) {
        temp_v0_2 = func_00148600(temp_v0, arg2, arg3, fparg0);
        if ((temp_v0_2 != 0) && (arg1 & 0x800)) {
            M2C_FIELD(temp_v0_2, s16 *, 6) = -1;
        }
    }
    return temp_v0;
}

s32 func_00148a40(s32 arg0, s32 arg1) {
    return func_00148968(arg0, M2C_FIELD(arg0, s32 *, 0x68), arg1);
}

s32 func_00148b70(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    return func_00148768(M2C_FIELD(arg0, s32 *, 0x68), arg1, arg0, arg2, fparg0);
}

void func_00148d18(s32 arg0, s32 arg1, f32 fparg0) {
    s32 temp_v0;

    temp_v0 = func_00148cb0(arg0, fparg0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 5) = (s8) arg1;
        M2C_FIELD(temp_v0, s8 *, 4) = 0;
    }
}

void func_00148db0(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    s32 temp_v0;

    temp_v0 = func_00148cb0(arg0, fparg0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 8) = arg2;
        M2C_FIELD(temp_v0, s8 *, 5) = (s8) arg1;
        M2C_FIELD(temp_v0, s8 *, 4) = 2;
    }
}

s32 func_00149740(s32 arg0) {
    return func_001496c8(arg0, (s32) M2C_FIELD(((arg0 * 0x74) + D_00304BE8), u8 *, 0x36));
}

s32 func_0014a058(s32 arg0) {
    func_00149968();
    D_0054C438 = arg0;
    D_0054C43C = 0;
    return func_00149fa0();
}

void func_0014a380(s32 arg0, s32 arg1) {
    func_001412f8(arg0, M2C_FIELD(arg1, s32 *, 0x30));
}

void func_0014cc38(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    M2C_FIELD(arg0, s32 *, 0x3D0) = 0;
    M2C_FIELD(arg0, f32 *, 0x3B4) = (f32) M2C_FIELD(arg0, f32 *, 0x14);
    func_0014f658(arg0, 2);
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFFEFFFF);
}

void func_0014cd38(s32 arg0) {
    s32 temp_v0;

    if (!(M2C_FIELD(arg0, f32 *, 0x3B8) <= (M2C_FIELD(arg0, f32 *, 0x3B0) + 6.0f))) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x178) != 0) {
        return;
    }
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x3D0);
    if (M2C_FIELD(arg0, s32 *, 0x164) != (temp_v0 + 4)) {
        return;
    }
    func_00130340(arg0, temp_v0 + 5, 6.0f);
    func_00130578(arg0, M2C_FIELD(arg0, s32 *, 0x3D0) + 6, 0.0f);
}

void func_0014dcd8(Actor *arg0) {
    if (arg0->unk3D4 > 100.0f) {
        func_00130398(arg0, 0x75, 8.0f);
        func_0014f658(arg0, 8);
        arg0->unk3C4 = (f32) (arg0->unk3C4 * 0.3f);
        M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    }
}

void func_0014f398(s32 arg0) {
    func_00141ab8(M2C_FIELD(arg0, s32 *, 0x6C));
    M2C_FIELD(arg0, s32 *, 0x6C) = (s32) &D_00304C70;
}
#include "data/data_0030.h"
