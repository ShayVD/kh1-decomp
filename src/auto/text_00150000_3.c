/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"

M2C_UNK RemoveDmacHandler(M2C_UNK, s32);
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_00148768(s32, M2C_UNK, s32 *, M2C_UNK, f32);
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_00176310(s32);
M2C_UNK func_00258d10(M2C_UNK);
M2C_UNK func_002673b8(s32, void *);
M2C_UNK func_002674f0(s32, void *, s32, f32);
M2C_UNK func_002675a8(s32, M2C_UNK *);
M2C_UNK func_00267e90(void *, s32, f32);
extern M2C_UNK D_002C58B0;
extern M2C_UNK D_002E31B0;
extern M2C_UNK D_00351B60;
extern M2C_UNK D_00351B88;
extern M2C_UNK D_0054F970;
extern M2C_UNK D_0054F980;
extern M2C_UNK D_00551608;
extern M2C_UNK func_00150660;
extern M2C_UNK func_00150b70;
extern M2C_UNK func_00150bf8;
extern M2C_UNK func_00150c18;
extern M2C_UNK func_00150cb0;
extern M2C_UNK func_00150cb8;
extern M2C_UNK func_00156188;
extern f32 D_002BBDFC;
extern s32 D_00350CE0;
extern s32 D_005516E8;
extern s8 D_00550400;
extern s8 D_00FE0000;
extern u8 D_002E3190;
extern volatile s32 D_00351BC0;
extern volatile s32 D_00351BC4;
f32 func_00267560(void *, s32, f32);
f32 func_0026b9a8(f32, f32);
s32 *func_0013daf8();
s32 func_0011ef38(M2C_UNK *);
s32 func_00122ff8(s32 *);
s32 func_0012cc38(s32, s32);
s32 func_0012ccb0(s32);
s32 func_00130340(s32, s32, f32);
s32 func_00130398(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
s32 func_001354b8(s32, s32);
s32 func_001375f0(s32);
s32 func_00137618(s32);
s32 func_001477e0(s32);
s32 func_0014a4a8(s32, s32, s32);
s32 func_00155730(s32);
s32 func_00159178(s32, s32, s32, s32);
s32 func_0015d6c8(s32, s32);
void *func_0011ef10(M2C_UNK, M2C_UNK *);
void func_00121eb0(s32);
void func_00131498(s32, s32);
void func_001315c0(s32, s32, s32, f32);
void func_001373f8(s32, f32);
void func_0014aab0(s32);
void func_00153c50(s32, s32);
void func_0015dcc8(s32, s32);

s32 func_00150208(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;

    switch (arg2) {                                 /* switch 1; irregular */
    case -1:                                        /* switch 1 */
        if (M2C_FIELD(arg1, s32 *, 0x98) == arg0) {
            func_0012cc38(0, 0x44);
            func_0012ccb0(0);
        } else if ((func_00137618(arg0) != 0) && (M2C_FIELD(arg0, s32 *, 0x164) == 1)) {
            temp_a1 = M2C_FIELD(arg1, s32 *, 0x70);
            switch (temp_a1) {                      /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                func_0012cc38(3, 0x45);
                break;
            case 26:                                /* switch 2 */
                func_0012cc38(0, 0x44);
                break;
            }
        }
        break;
    case -2:                                        /* switch 1 */
        func_00121eb0(M2C_FIELD(arg0, s32 *, 0x144));
        break;
    }
    return 0;
}

void func_00150cd8(void) {
    func_0014f830(0x1A, 5, 0, &func_00150660, &func_00150bf8, &func_00150c18, &func_00150cb0, &func_00150b70, &func_00150cb8);
}

void func_00152520(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x98) = arg1;
    M2C_FIELD(arg1, s32 *, 0x98) = arg0;
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) | 0x200);
}

void func_00152648(s32 arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), s32 *, 0x40);
    if (temp_v1 != 0) {
        func_0014aab0(temp_v1);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), s32 *, 0x40) = 0;
    }
}

s32 func_00153d08(s32 arg0) {
    func_00153c50(arg0, 0);
    return 0;
}

void func_00154be0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v1;

    func_00130340(arg0, 0x0100006F, 0.0f);
    func_00130578(arg0, 0x40000000, 0.0f);
    func_001373f8(arg0, 8.0f);
    temp_v1 = M2C_FIELD(arg0, void **, 0x14C);
    M2C_FIELD(temp_v1, u8 *, 0x29) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x29) + 0xFF);
    M2C_FIELD(arg2, f32 *, 0xC) = 0.0f;
}

void func_00155630(void *arg0, void *arg1) {
    s32 temp_s2;

    temp_s2 = arg0 + 0x3C0;
    func_00267560(arg1, arg0 + 0x20, M2C_FIELD(arg0, f32 *, 0x2C));
    func_002674f0(temp_s2, arg1, temp_s2, M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0x14));
    M2C_FIELD(arg0, f32 *, 0x3C4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    func_00267e90(arg1, temp_s2, D_002BBDFC);
}

void func_00155760(s32 arg0) {
    s32 *temp_v1;
    s8 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s8 *, 0x55);
    temp_v1 = &D_00550400 + (temp_v0 * 0x48);
    *temp_v1 |= 0x10000;
    func_00155730((s32) (&D_00FE0000 + (temp_v0 << 0x12)));
}

void func_001561f8(void) {
    func_0011efa8(&D_0054F970, &D_0054F980, 0x1C, 0x60);
    if (func_0011ef38(&func_00156188) == 0) {
        M2C_FIELD(func_0011ef10(0x15F90, &func_00156188), s16 *, 2) = -1;
    }
}

void func_00156260(void *arg0, void *arg1) {
    func_002675a8(arg0 + 0x3C0, &D_002C58B0);
    func_002673b8(arg0 + 0x3F0, arg1);
    M2C_FIELD(arg0, f32 *, 0x3FC) = (f32) (M2C_FIELD(arg1, f32 *, 0xC) * 0.22314355f);
    M2C_FIELD(arg0, s32 *, 0x88) = (s32) (M2C_FIELD(arg0, s32 *, 0x88) | 0x40);
}

void func_001574b0(s32 arg0) {
    s8 *var_v1;
    s32 var_a1;

    var_a1 = 2;
    var_v1 = &D_00551608;
    do {
        var_a1 -= 1;
        if (M2C_FIELD(var_v1, s8 *, 0) == arg0) {
            M2C_FIELD(var_v1, u8 *, 1) = (u8) (M2C_FIELD(var_v1, u8 *, 1) & 0xFE);
        }
        var_v1 += 0x22;
    } while (var_a1 >= 0);
}

void func_001574f0(void) {
    s8 *var_v1;
    s32 var_a0;

    var_a0 = 2;
    var_v1 = &D_00551608;
    do {
        var_a0 -= 1;
        M2C_FIELD(var_v1, u8 *, 1) = (u8) (M2C_FIELD(var_v1, u8 *, 1) & 0xFE);
        var_v1 += 0x22;
    } while (var_a0 >= 0);
}

void func_00158050(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0xCC) = 0.19634955f;
}

void func_00158ad0(s32 arg0) {
    func_00131498(arg0, D_005516E8);
}

void func_001593f8(s32 arg0, s32 arg1, s32 arg2) {
    if (D_002E3190 == 1) {
        func_00159178(arg0, 0x3C, (s32) &D_002E31B0, arg2);
    }
}

s32 func_0015a470(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 == -2) {
        func_00176310(M2C_FIELD(arg0, s32 *, 0x144));
    }
    return 0;
}

s32 func_0015a498(Actor *arg0, s32 arg1) {
    s32 temp_v0;

    if (arg0->unk008 != 0) {
        temp_v0 = func_0014a4a8(arg0, 0, func_001477e0(arg1));
        func_001315c0(arg0, 0x8003, temp_v0 + 0x10, 0.0f);
        func_001354b8(temp_v0, arg0->unk008);
        arg0->unk000 = (s32) (arg0->unk000 | 0x20);
        return 1;
    }
    return 0;
}

void func_0015b438(void) {
    s32 *temp_v0;

    temp_v0 = func_0013daf8();
    if ((func_00122ff8(temp_v0) != 0) && (*temp_v0 & 0x8000)) {
        func_00148768(D_00350CE0, 0x15, temp_v0, 0x8003, 0);
    }
}

f32 func_0015ca50(void *arg0) {
    return *(f32 *)((s8 *)&D_00351B60 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 4));
}

f32 func_0015ca70(void *arg0) {
    return *(f32 *)((s8 *)&D_00351B88 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 4));
}

void func_0015caa8(s32 *arg0) {
    *arg0 &= 0xFFDFFFFF;
}

void func_0015d4e0(s32 arg0, s32 arg1, void *arg2) {
    M2C_FIELD(arg2, f32 *, 0xC) = 0.0f;
    if (M2C_FIELD(arg2, f32 *, 4) < M2C_FIELD(arg2, f32 *, 0xC)) {
        M2C_FIELD(arg2, f32 *, 4) = -1.0f;
        M2C_FIELD(arg2, f32 *, 0xC) = 1.0f;
    }
}

s32 func_0015d770(s32 arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = func_0015d6c8(arg0, arg1);
    if (var_v0 != 0) {
        func_00130398(arg0, 0x40000032, 8.0f);
        var_v0 = 1;
    }
    return var_v0;
}

void func_0015de88(s32 arg0) {
    func_0015dcc8(arg0, arg0 + 0x20);
    if (func_001375f0(arg0) != 0) {
        func_00130398(arg0, 0x40000035, 8.0f);
        M2C_FIELD(arg0, f32 *, 0x150) = func_0026b9a8(M2C_FIELD(arg0, f32 *, 0x20), M2C_FIELD(arg0, f32 *, 0x28));
    }
}

void func_0015ee10(void) {
    func_00258d10(1);
    func_00258d10(2);
    RemoveDmacHandler(1, D_00351BC0);
    RemoveDmacHandler(2, D_00351BC4);
    D_00351BC0 = -1;
    D_00351BC4 = -1;
}
