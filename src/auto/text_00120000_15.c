/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0012eba0(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_00138a78(s32, void *);
M2C_UNK func_00138c30(s32, void *);
M2C_UNK func_00138e58(s32, void *);
M2C_UNK func_00139170(s32, void *);
M2C_UNK func_00139240(s32, void *, s32, f32, f32, f32);
extern M2C_UNK D_002E2FCF;
extern M2C_UNK D_002E3170;
extern M2C_UNK D_004F82D0; /* src/data/bss_004F.c: u8 D_004F82D0[0x40] */
extern M2C_UNK func_0012c0e8;
extern s32 D_00350CE0;
extern u32 D_00524F40; /* src/data/bss_0052.c: void **D_00524F40 */
extern void *D_002E26A0;
extern void *D_00514F10; /* src/data/bss_0051.c: s32 D_00514F10 */
f32 func_0012ed88(s32, s32, s32, s32);
s32 func_00121de0(s32);
s32 func_00121e28(M2C_UNK, void *);
s32 func_00122ff8(s32);
s32 func_0012b930(s32, s32);
s32 func_00142388(s32, s32);
s32 func_00147ed8(s32, u8, M2C_UNK, s32);
s32 func_002675a8(s32, s32);
void *func_00147d18(M2C_UNK *);
void func_00127960(void *, void *, s32);
void func_00127b18(void *, void *, s32);
void func_0012ba30(s32, s32, s32);
void func_001315c0(s32, s32, s32, f32);
void func_00142470(s32, s32);
void func_00157a30(s32, s32, s32);
void func_001ea498(s32);
void func_00267328(void *, M2C_UNK *, s32);
void func_00267530(s32, s32, s32);

void func_00121f30(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_00121de0(arg0);
    *(M2C_UNK *)arg1 = arg0;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg1;
    M2C_FIELD(temp_v0, s32 *, 0) = 0;
}

s32 func_00123118(void *arg0, void *arg1) {
    s32 temp_a1;
    s32 var_v1;

    var_v1 = 0;
    if (!(M2C_FIELD(arg1, s32 *, 0) & 0x200)) {
        temp_a1 = (s32) ((u64) M2C_FIELD(arg1, u64 *, 0x370) >> 0x25) & 3;
        if (temp_a1 != 0) {
            var_v1 = temp_a1 != ((s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x25) & 3);
        }
    }
    return var_v1;
}

void func_00126ba0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    if (func_00122ff8(*(M2C_UNK *)arg1) != 0) {
        func_0012ed88(arg0, arg1, (s32) sp, arg2);
        M2C_FIELD(arg2, s32 *, 4) = 0;
        return;
    }
    func_002675a8(arg2, arg0 + 0x30);
}

void func_00127b98(void *arg0, s32 arg1, f32 fparg0) {
    s32 sp[16];
    func_00267328(sp, &D_004F82D0, arg1);
    if ((s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x27) & 1) {
        func_00127b18(arg0, sp, (s32) fparg0);
        return;
    }
    func_00127960(arg0, sp, (s32) fparg0);
}

s32 func_00128c60(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_v0;

    temp_v0 = func_0012b930((s32) D_00514F10, M2C_FIELD(D_00514F10, s32 *, 4) + (arg1 * 2));
    temp_a0 = temp_v0;
    if (*(M2C_UNK *)arg0 != 0) {
        func_0012ba30(temp_a0, arg0, 4);
    }
    return temp_v0;
}

void func_0012a390(s32 arg0) {
    s32 sp[8];    s32 temp_s0;

    temp_s0 = *(M2C_UNK *)arg0;
    func_001315c0(temp_s0, 0x8003, (s32) sp, 0.0f);
    func_00142388((s32) sp, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x10));
    func_00142470(temp_s0, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x10));
    M2C_FIELD(temp_s0, s64 *, 0x370) = (s64) (M2C_FIELD(temp_s0, s64 *, 0x370) | ((s64) 0x8000 << 0x25));
}

void func_0012a9d0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 4);
    if ((s32) ((u64) M2C_FIELD(temp_v1, u64 *, 8) >> 0x2B) & 1) {
        func_00138a78(M2C_FIELD(arg0, s32 *, 0), temp_v1);
    }
    func_00139240(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, void **, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, f32 *, 0xC), M2C_FIELD(arg0, f32 *, 0x10), M2C_FIELD(arg0, f32 *, 0x14));
    M2C_FIELD(arg0, s32 *, 0) = 0;
}

void func_0012aa38(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 4);
    if ((s32) ((u64) M2C_FIELD(temp_v1, u64 *, 8) >> 0x2B) & 1) {
        func_00138a78(M2C_FIELD(arg0, s32 *, 0), temp_v1);
    }
    func_00138e58(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, void **, 4));
}

void func_0012aa88(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 4);
    if ((s32) ((u64) M2C_FIELD(temp_v1, u64 *, 8) >> 0x2B) & 1) {
        func_00138a78(M2C_FIELD(arg0, s32 *, 0), temp_v1);
    }
    func_00138c30(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, void **, 4));
}

void func_0012abe0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 4);
    if ((s32) ((u64) M2C_FIELD(temp_v1, u64 *, 8) >> 0x2B) & 1) {
        func_00138a78(M2C_FIELD(arg0, s32 *, 0), temp_v1);
    }
    func_00139170(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, void **, 4));
}

void func_0012b358(s32 arg0) {
    s32 *temp_a3;

    temp_a3 = M2C_FIELD(D_002E26A0, s32 **, 0x6C);
    *temp_a3 |= 4;
    func_00157a30((s32) D_002E26A0, 2, 0);
    func_001ea498(*(M2C_UNK *)arg0);
}

void func_0012c180(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_v0_2;
    void *temp_v0;

    temp_v0 = func_00147d18(&func_0012c0e8);
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg1;
    temp_v0_2 = func_00121e28(0x40, temp_v0 + 0x20);
    temp_s0 = temp_v0_2 + 0x10;
    func_0012eba0(arg1, 1, -1, 0, temp_s0);
    func_00267530(temp_v0_2 + 0x20, temp_s0, arg1 + 0x50);
    M2C_FIELD(temp_v0, s32 *, 0x14) = func_00147ed8(D_00350CE0, *(M2C_UNK *)((s8 *)(s8 *)&D_002E2FCF + arg0), 0x4E20, temp_s0);
}

s32 func_0012dd38(void) {
    u32 temp_a1;
    u32 var_a0;

    var_a0 = D_00524F40;
    temp_a1 = var_a0 - 4;
    if ((u32) &D_002E3170 < var_a0) {
        *(M2C_UNK *)var_a0 = 0;
        D_00524F40 = temp_a1;
        var_a0 = temp_a1;
    }
    return *(M2C_UNK *)var_a0;
}
#include "data/data_002E.h"
