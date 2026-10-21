/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"

M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
M2C_UNK func_0012ec88(s32, void *);
M2C_UNK func_0013bf20();
M2C_UNK func_0013fc80();
M2C_UNK func_00141138();
M2C_UNK func_001418b8(M2C_UNK *);
M2C_UNK func_00144e38();
M2C_UNK func_0014a1b0(s32, s32, void *);
M2C_UNK func_0014a238(s32, s32, void *);
M2C_UNK func_0014a908(s32, s32, s32);
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
M2C_UNK func_00267560(s32, s32, f32);
M2C_UNK func_002675a8(void *, s32);
M2C_UNK func_00267e90(s32, s32, f32);
extern M2C_UNK D_00304C70;
extern M2C_UNK D_00350D88;
extern M2C_UNK D_0054B808; /* src/data/bss_0054.c: u8 D_0054B808[0x10] */
extern M2C_UNK func_001468b0;
extern f32 D_002BBDFC;
extern s32 D_002E26A0;
extern s32 D_0052CB18; /* src/data/bss_0052.c: u32 D_0052CB18 */
extern s32 D_0054F440; /* src/data/bss_0054.c: u32 D_0054F440 */
extern volatile M2C_UNK D_00304D64;
s32 func_00122ff8(s32);
s32 func_001477e0(s32);
s32 func_00148438(s32, s32);
s32 func_00149170(s32, s32);
s32 func_0014aa50(s32);
s32 func_002675b8(s32, s32);
void *func_001208e0(M2C_UNK *);
void func_001315c0(s32, s32, s32, f32);
void func_001318e8(s32, s32, s32);
void func_001417a0(s32, s32);
void func_00147e08(s32, s32);
void func_001487f8(s32, s32, s32, s32);

void func_00140ee0(s32 arg0, s32 arg1) {
    func_00267560(arg1, arg0 + 0x20, D_002BBDFC);
}

void func_00141858(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_001315c0(arg0, 0x8004, (s32) sp, 0.0f);
    func_001417a0((s32) sp, arg1);
}

void func_00142030(void) {
    D_0052CB18 = 0;
    func_001418b8(&D_00304C70);
}

f32 func_00144378(Actor *arg0) {
    return (arg0->unk014 - arg0->unk2D4) - *(f32 *)((s8 *)(s8 *)&D_00304D64 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 8));
}

void func_00144ce0(s32 arg0, s32 arg1) {
    func_00267e90(arg1, arg0 + 0x20, D_002BBDFC);
}

void func_001468f8(s32 arg0) {
    M2C_FIELD(func_001208e0(&func_001468b0), s32 *, 0x38) = arg0;
}

s32 func_00148570(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[16];
    s32 temp_v0;

    func_001318e8(arg1, arg2 & 0xFFFEFFFF, (s32) sp);
    func_00147e08(arg0, (s32) sp);
    temp_v0 = func_00148438(arg0, arg1);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 8) = arg2;
        M2C_FIELD(temp_v0, s8 *, 4) = 2;
        func_002675b8(temp_v0 + 0x30, (s32) sp);
    }
    return temp_v0;
}

void func_00148b98(s32 arg0, s32 arg1, s32 arg2) {
    func_001487f8(M2C_FIELD(arg0, s32 *, 0x68), arg1, arg0, arg2);
}

s32 func_00148df8(void) {
    func_0011f130(&D_0054B808, 0);
    return 0;
}

void func_00149660(s32 arg0, s32 arg1) {
    func_00149170(arg0, M2C_FIELD(arg1, s32 *, 4));
}

void func_0014a330(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    func_0014a238(arg2, arg3, sp);
    func_0014a1b0(arg0, arg1, sp);
}

void func_0014aa10(s32 arg0, s32 arg1, s32 arg2) {
    func_0014a908(arg0, arg1, func_001477e0(arg2));
}

s32 func_0014ab18(s32 arg0) {
    M2C_FIELD(arg0, s64 *, 0) = (s64) (M2C_FIELD(arg0, s64 *, 0) | 0x400);
    return func_0014aa50(M2C_FIELD(arg0, s32 *, 0x54));
}

void func_0014ab48(void *arg0) {
    M2C_FIELD(arg0, s64 *, 0) = (s64) (M2C_FIELD(arg0, s64 *, 0) & ~0x400);
    D_0054F440 |= M2C_FIELD(arg0, s32 *, 0x54);
}

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
    func_002675a8(sp, D_002E26A0 + 0x10);
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
    func_002675a8(sp, D_002E26A0 + 0x10);
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
