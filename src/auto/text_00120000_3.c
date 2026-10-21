/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_004F.h"

M2C_UNK func_00121f6c(s32, s32, s32);
M2C_UNK func_00149860(void *);
M2C_UNK func_00162110(s32, void *);
M2C_UNK func_0025ed48(s32, s32, s32, s32);
M2C_UNK func_002675a8(void *, void *);
M2C_UNK func_002676c0(f32);
M2C_UNK func_00267768(s32, s32, f32);
M2C_UNK func_00267810(s32, s32, f32);
#include "data/pieces/D_002C5C80.h"
extern M2C_UNK D_002E2FD8;
extern M2C_UNK D_002E2FEC;
extern M2C_UNK D_004F45B0; /* src/data/bss_004F.c: Block D_004F45B0[0x200] */
extern M2C_UNK func_00122ab0;
extern f32 D_002E27A0;
extern f32 D_004F7650;
extern s32 D_002C5958;
#include "data/pieces/D_002C6440.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_002E319C.h"
extern void **D_00524F40;
extern void *D_002E26A0;
f32 func_00120c88(f32);
f32 func_001315c0(void *, u16, void *, f32);
f32 func_0026b6f8(f32);
f32 func_0026b7d0(f32);
f32 func_0026b8b8(f32);
s32 *func_00123488();
s32 func_0011ef10(s32, s32);
s32 func_0011ef38(s32);
s32 func_00120930();
s32 func_001226f0(s32, s32, s32);
s32 func_00123368();
s32 func_00128c60(s32, s32);
s32 func_0012d930(s32);
s32 func_0012dea0(void *, s32);
s32 func_001334b8(s32, s32, s32, s32, s32);
u8 *func_0015c960(void *, M2C_UNK, u32, s32);
void func_00122bd8(void);
void func_001252f8(void);
void func_0012bbc8(s32, s32, s32, s32, s32);
void func_0012d068(s32, s32);
void func_0012d468(s32, s32);
void func_0012d6c0(s32, s32);
void func_0012d818(void);
void func_0012eba0(s32, s32, s32, s32, s32);

void func_00120a20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0025ed48(func_00120930(), arg1, arg2, arg3);
}

void func_00120c38(s32 arg0, s32 arg1, void *arg2) {
    func_002676c0(M2C_FIELD(arg2, f32 *, 8));
    func_00267768(arg0, arg0, M2C_FIELD(arg2, f32 *, 0));
    func_00267810(arg0, arg0, M2C_FIELD(arg2, f32 *, 4));
}

s32 func_00121b98(void) {
    M2C_UNK *var_a1;
    M2C_UNK *var_s0;
    s32 temp_s1;
    s32 temp_v0;
    u32 temp_a0;
    u32 var_s2;

    var_a1 = &D_004F45B0;
    var_s0 = M2C_FIELD(&D_004F45B0, M2C_UNK **, 0x10);
    var_s2 = 0;
    if (var_s0 != NULL) {
        do {
            temp_a0 = M2C_FIELD(var_s0, u32 *, 0) + 1;
            M2C_FIELD(var_s0, u32 *, 0) = temp_a0;
            if (M2C_FIELD(var_s0, s32 **, 0xC) == NULL) {
                M2C_FIELD(var_s0, s32 *, 4) = 0;
                M2C_FIELD(var_a1, M2C_UNK **, 0x10) = (M2C_UNK *) M2C_FIELD(var_s0, M2C_UNK **, 0x10);
            } else {
                if ((var_s2 <= 0x1FFFFU) && (temp_a0 >= 4U)) {
                    temp_v0 = M2C_FIELD(var_s0, s32 *, 4);
                    temp_s1 = M2C_FIELD(var_a1, s32 *, 4) + M2C_FIELD(var_a1, s32 *, 8);
                    if ((temp_v0 - temp_s1) > 0) {
                        func_00121f6c(temp_v0, temp_s1, M2C_FIELD(var_s0, s32 *, 8));
                        M2C_FIELD(var_s0, s32 *, 4) = temp_s1;
                        *M2C_FIELD(var_s0, s32 **, 0xC) = temp_s1;
                        var_s2 += M2C_FIELD(var_s0, s32 *, 8);
                    }
                }
                var_a1 = var_s0;
            }
            var_s0 = M2C_FIELD(var_s0, M2C_UNK **, 0x10);
        } while (var_s0 != NULL);
    }
    return 0;
}

void func_00122cf0(void) {
    s8 *var_v0;
    s32 temp_v0;
    s32 var_v1;

    var_v1 = 0x1E;
    var_v0 = ((M2C_UNK *)&D_002C5C80);
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s32 *, 0) = 0;
        M2C_FIELD(var_v0, s32 *, 4) = 0;
        var_v0 += 0x40;
    } while (var_v1 >= 0);
    temp_v0 = func_001226f0(2, 7, 0);
    D_002C6440 = temp_v0;
    M2C_FIELD(temp_v0, s32 *, 0x20) = 0;
    M2C_FIELD(D_002C6440, f32 *, 0x24) = 1.0f;
    M2C_FIELD(D_002C6440, s32 *, 0x28) = 0;
    M2C_FIELD(D_002C6440, f32 *, 0x2C) = 1.0f;
    M2C_FIELD(D_002C6440, f32 *, 0x30) = 1.0f;
    M2C_FIELD(D_002C6440, f32 *, 0x34) = 1.0f;
    M2C_FIELD(D_002C6440, f32 *, 0x38) = 1.0f;
    M2C_FIELD(D_002C6440, f32 *, 0x3C) = 1.0f;
    func_00122bd8();
    if (func_0011ef38((s32) &func_00122ab0) != 0) {
        return;
    }
    func_0011ef10(0xEA60, (s32) &func_00122ab0);
}

s32 func_001233e8(Actor *arg0) {
    s32 var_s1;

    var_s1 = 0;
    if (func_00123368() != 0) {
        var_s1 = (arg0->unk000 & 0x01000080) == 0;
    }
    return var_s1;
}

void func_00123648(s32 arg0, s32 arg1) {
    s32 *temp_v0;

    temp_v0 = func_00123488();
    *temp_v0 |= 1 << arg1;
}

void func_00123680(s32 arg0, s32 arg1) {
    s32 *temp_v0;

    temp_v0 = func_00123488();
    *temp_v0 &= ~(1 << arg1);
}

s32 func_001236c0(s32 arg0, s32 arg1) {
    return *func_00123488() & (1 << arg1);
}

void func_001236f8(void *arg0) {
    s32 temp_v0;

    if (!(((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x27) & 1)) {
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x154);
        if (temp_v0 != 0) {
            func_00162110(temp_v0, arg0 + 0x15C);
            if (M2C_FIELD(arg0, s32 *, 0x14C) != 0) {
                func_00149860(arg0);
            }
            M2C_FIELD(arg0, s32 *, 0x154) = 0;
            M2C_FIELD(arg0, s32 *, 0x134) = 0;
        }
    }
}

void func_001238c0(void *arg0, f32 fparg0, f32 fparg1) {
    M2C_FIELD(arg0, f32 *, 0x410) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x414) = fparg1;
}

void func_00124c68(f32 fparg0) {
    D_002E27A0 = fparg0;
    D_004F7650 = 256.0f / func_0026b8b8(((fparg0 * 0.5f) / 180.0f) * 3.141592979f);
}

void func_001259b0(s32 arg0) {
    if (arg0 != 0) {
        D_002C5958 |= 0x400000;
    } else {
        D_002C5958 &= 0xFFBFFFFF;
    }
    func_001252f8();
}

void func_00128cc8(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_00128c60(arg0, M2C_FIELD(arg0, s32 *, 4));
}

void func_00128de0(f32 *arg0) {
    *arg0 = func_0026b7d0(func_00120c88((*arg0 / 180.0f) * 3.141592979f));
}

void func_00128e38(f32 *arg0) {
    *arg0 = func_0026b6f8(func_00120c88((*arg0 / 180.0f) * 3.141592979f));
}

void func_00128f10(f32 *arg0) {
    *arg0 = func_00120c88((*arg0 / 180.0f) * 3.141592979f);
}

void func_00129cf0(void *arg0) {
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x6C), f32 *, 0xCC) = (f32) ((M2C_FIELD(arg0, f32 *, 4) / 180.0f) * 3.141592979f);
}

void func_0012ac98(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = func_001334b8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 0x10));
}

void func_0012bce0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_0012bbc8(arg0, (s32) M2C_FIELD(((arg1 * 2) + arg0), u16 *, 0x724), arg2, arg3, arg4);
}

u8 func_0012ccf8(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_002E2FEC + arg0);
}

void func_0012dc70(void) {
    void *temp_s0;
    void *temp_s1;

    temp_s1 = D_002E26A0;
    temp_s0 = ((s8 *)&D_00350D88) + (M2C_FIELD(temp_s1, s32 *, 0x70) << 5);
    func_0012d068((s32) temp_s1, (s32) temp_s0);
    func_0012d468((s32) temp_s1, (s32) temp_s0);
    func_0012d6c0((s32) temp_s1, (s32) temp_s0);
    func_0012d818();
    func_0012d930((s32) temp_s0);
}

void func_0012e120(void) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a1;

    temp_a0 = *D_00524F40;
    if (func_0012dea0(temp_a0, M2C_FIELD(temp_a0, s32 *, 0xC)) != 0) {
        temp_a1 = *D_00524F40;
        if (temp_a1 == &D_002E2FD8) {
            if (!(*D_002E319C & 0x10)) {
                M2C_FIELD(temp_a1, s32 *, 0xC) = 0;
            }
        }
    } else {
        temp_a0_2 = M2C_FIELD(D_002E26A0, void **, 0x14C);
        M2C_FIELD(temp_a0_2, s32 *, 0x28) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 0x28) & 0xFFFEFFFF);
    }
}

void func_0012ec60(s32 arg0, s32 arg1, s32 arg2) {
    func_0012eba0(arg0, 0, -1, arg1, arg2);
}

f32 func_0012eca8(void *arg0, void *arg1) {
    u8 *var_s0;
    void *temp_a0;
    void *temp_v1;

    var_s0 = func_0015c960(M2C_FIELD(arg0, void **, 0), 0, -1U, M2C_FIELD(arg0, s32 *, 4));
    if (var_s0 != NULL) {
        var_s0 = func_0015c960(M2C_FIELD(arg0, void **, 0), 2, (u8) *var_s0 >> 4, 0);
        if (var_s0 != NULL) {
            goto block_9;
        }
        goto block_4;
    }
block_4:
    temp_a0 = M2C_FIELD(arg0, void **, 0);
    temp_v1 = M2C_FIELD(temp_a0, void **, 0x134);
    if ((temp_v1 != NULL) && (M2C_FIELD(temp_v1, u8 *, 5) != 0)) {
        var_s0 = M2C_FIELD(temp_v1, u8 **, 0x14);
    }
    if (var_s0 == NULL) {
        func_002675a8(arg1, temp_a0 + 0x10);
        return 0.0f;
    }
block_9:
    func_001315c0(M2C_FIELD(arg0, void **, 0), M2C_FIELD(var_s0, u16 *, 2), arg1, M2C_FIELD(var_s0, f32 *, 4));
    M2C_FIELD(arg1, f32 *, 4) = (f32) (M2C_FIELD(arg1, f32 *, 4) - (M2C_FIELD(var_s0, f32 *, 8) * M2C_FIELD(M2C_FIELD(arg0, void **, 0), f32 *, 0x44)));
    return M2C_FIELD(var_s0, f32 *, 0xC);
}
#include "data/bss_0052_mixed.h"
#include "data/data_002E.h"
