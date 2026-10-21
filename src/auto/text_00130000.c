/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"

M2C_UNK func_0011f090(M2C_UNK *, s32, s32);
M2C_UNK func_00120748(M2C_UNK *, s32, M2C_UNK *, M2C_UNK);
M2C_UNK func_00121fc4(void *, void *);
M2C_UNK func_0012fc58();
M2C_UNK func_00135000(s32, void *);
M2C_UNK func_00135a68(s32, f32, f32);
M2C_UNK func_0013ed88();
M2C_UNK func_0013ee40(s32, s32, s32);
M2C_UNK func_0013f770();
M2C_UNK func_0013fd88(f32);
M2C_UNK func_00147808(s32);
M2C_UNK func_0014cce0();
M2C_UNK func_00176310(s32);
M2C_UNK func_0017e7d8();
M2C_UNK func_0024ffa4(s32, s32, u32);
M2C_UNK func_00267560(s32, void *, f32);
M2C_UNK func_002675a8(s32, s32);
extern M2C_UNK D_0048D628;
extern M2C_UNK D_005267C0; /* src/data/bss_0052.c: QD D_005267C0[0x40] */
extern M2C_UNK D_0052AA58; /* src/data/bss_0052.c: u8 D_0052AA58[0x10] */
extern M2C_UNK func_00132e78;
extern s32 D_002C5958;
#include "data/pieces/D_00304B78.h"
extern s32 D_00525364;
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_00304BE8.h"
f32 func_0026b6f8(f32);
f32 func_0026b7d0();
s32 func_00131ab0();
s32 func_001375d8(s32);
s32 func_001375f0();
s32 func_00138858(u16);
s32 func_00138988();
s32 func_002193f0();
void *func_001320a8();
void *func_00134f80(M2C_UNK *, M2C_UNK);

s32 func_00130000(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x178) > 0;
}

s32 func_00130010(void *arg0) {
    s32 var_v0;

    var_v0 = 1;
    if (!(M2C_FIELD(arg0, f32 *, 0x170) > 0.0f)) {
        var_v0 = 0;
    }
    return var_v0;
}

s32 func_00130030(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x1CC) & 0x400000;
}

s32 func_00131b08(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (func_00131ab0() != 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x178) == 0;
    }
    return var_v0;
}

void func_00131c28(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x284) = fparg0;
}

s32 func_00131c30(void) {
    void *temp_v0;

    temp_v0 = func_001320a8();
    if ((u16) M2C_FIELD(temp_v0, u16 *, 0x4C) >= 0x12CU) {
        return func_00138858(M2C_FIELD(temp_v0, u16 *, 0x4C));
    }
    return 0;
}

void func_00132ec8(s32 arg0, s32 arg1) {
    D_00525364 = arg1;
    func_00120748(&D_0048D628, arg0, &func_00132e78, 0);
}

void func_00132f48(s32 arg0) {
    func_00147808(arg0 + 0x11E);
}

void func_00132f60(s32 arg0, s32 arg1) {
    func_00147808((arg0 * 3) + arg1 + 6);
}

s32 func_001336a0(void) {
    return ((u32) D_002E31A8 >> 1) & 1;
}

void func_001336d8(void) {
    func_0012fc58();
    D_002C5958 |= 2;
    func_0017e7d8();
}

void func_00133920(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg1, void **, 0x50);
    temp_v0 = M2C_FIELD(arg1, void **, 0x54);
    if (temp_v1 == NULL) {
        M2C_FIELD(arg0, void **, 0x440) = temp_v0;
    } else {
        M2C_FIELD(temp_v1, void **, 0x54) = temp_v0;
    }
    temp_v0_2 = M2C_FIELD(arg1, void **, 0x54);
    if (temp_v0_2 != NULL) {
        M2C_FIELD(temp_v0_2, s32 *, 0x50) = 0;
    }
    M2C_FIELD(arg1, s32 *, 0) = 0;
}

void func_00133a00(void *arg0) {
    void *var_v0;

    var_v0 = M2C_FIELD(arg0, void **, 0x440);
    if (var_v0 != NULL) {
        do {
            M2C_FIELD(var_v0, s32 *, 0) = 0;
            var_v0 = M2C_FIELD(var_v0, void **, 0x54);
        } while (var_v0 != NULL);
    }
    M2C_FIELD(arg0, void **, 0x440) = NULL;
}

f32 func_001348e0(void *arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x40);
    if (temp_v0 > 0) {
        return (f32) M2C_FIELD(arg1, s32 *, 8) / (f32) temp_v0;
    }
    return 1.0f;
}

void *func_00135070(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_00134f80(&D_005267C0, 0x40);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x28) = arg1;
        func_00135000(arg0, temp_v0);
    }
    return temp_v0;
}

void func_001350d0(s32 *arg0) {
    *arg0 = 0;
}

void func_00135640(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x3E0) = (s32) (M2C_FIELD(arg1, s32 *, 0x3E0) | M2C_FIELD(arg0, s32 *, 0x54));
}

void func_00135788(void *arg0) {
    func_002675a8(arg0 + 0x10, arg0 + 0x100);
    M2C_FIELD(arg0, s32 *, 0x3A0) = 0;
}

s32 func_00135888(void *arg0, s32 arg1) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x14C);
    if ((temp_v1 != NULL) && (arg1 & 0x10000)) {
        return M2C_FIELD(temp_v1, s32 *, 4);
    }
    return 0;
}

void func_00135b88(Actor *arg0, s32 arg1) {
    func_00135a68(arg1, arg0->unk410, arg0->unk414);
}

void func_00137308(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 0x98) = arg1;
    M2C_FIELD(arg1, void **, 0x98) = arg0;
}

void func_00137318(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x98);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x98) = 0;
    }
    M2C_FIELD(arg0, void **, 0x98) = NULL;
}

void func_00137440(Actor *arg0, s32 arg1) {
    arg0->unk398 = arg1;
}

void func_00137448(Actor *arg0) {
    arg0->unk398 = 0;
}

s32 func_00137618(s32 arg0) {
    s32 var_s1;

    var_s1 = 0;
    if (func_001375f0() != 0) {
        var_s1 = func_001375d8(arg0) == 0;
    }
    return var_s1;
}

void func_00137688(void *arg0, f32 fparg0) {
    f32 temp_f0;

    if (!(((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x2C) & 1)) {
        M2C_FIELD(arg0, f32 *, 0x30) = func_0026b7d0();
        M2C_FIELD(arg0, s32 *, 0x34) = 0;
        temp_f0 = func_0026b6f8(fparg0);
        M2C_FIELD(arg0, f32 *, 0x3C) = fparg0;
        M2C_FIELD(arg0, f32 *, 0x38) = temp_f0;
    }
}

void func_001383d8(s32 arg0, s32 arg1) {
    func_0011f090(&D_0052AA58, arg0, arg1);
}

void func_00138900(Actor *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->unk400;
    if (temp_v0 != 0) {
        func_00176310(temp_v0);
        arg0->unk400 = 0;
    }
    arg0->unk088 = (s32) (arg0->unk088 & ~2);
}

s32 func_001389c0(void) {
    return func_00138988() == 4;
}

void func_00138a20(s32 arg0, void *arg1) {
    f32 temp_f20;

    func_0014cce0();
    temp_f20 = M2C_FIELD(arg1, f32 *, 0xC);
    func_00121fc4(arg1, arg1);
    func_00267560(arg0 + 0x3C0, arg1, temp_f20);
}

void func_0013aaa0(void) {
    (*(s32 *)&D_00304B78) &= ~8;
}

s32 func_0013bf68(void) {
    return func_002193f0() == 2;
}

void func_0013c250(s8 arg0) {
    M2C_FIELD(D_00304BE8, s8 *, 0x48C) = arg0;
}

void func_0013c260(s8 arg0) {
    M2C_FIELD(D_00304BE8, s8 *, 0x48D) = arg0;
}

u32 func_0013cf78(void *arg0, s32 arg1) {
    u32 temp_s0;
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 8);
    temp_s0 = M2C_FIELD(temp_v0, u32 *, -4);
    func_0024ffa4(arg1, (temp_v0 - ((temp_s0 >> 2) * 4)) - 4, temp_s0);
    return temp_s0;
}

void func_0013dfa0(Actor *arg0) {
    arg0->unk000 &= ~0x4000;
}

void func_0013f0c0(s32 arg0, s32 arg1, s32 arg2) {
    func_0013ed88();
    func_0013ee40(arg0, arg1, arg2);
}

s32 func_0013f330(void *arg0, s32 arg1) {
    s32 var_a1;

    var_a1 = arg1;
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0x50) > 25.0f) {
        var_a1 += 9;
    }
    return var_a1;
}

s32 func_0013fc08(void) {
    func_0013f770();
    return 0;
}

void func_0013fe10(Actor *arg0) {
    func_0013fd88(arg0->unk014);
}
#include "data/data_0048.h"
