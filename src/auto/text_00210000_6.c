/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_001efbb8(s32);
M2C_UNK func_001f9010(M2C_UNK);
M2C_UNK func_001f9438(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_001f94f0(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00206ea8(s32);
M2C_UNK func_00207140(s32);
M2C_UNK func_00219288();
M2C_UNK func_002192c0();
M2C_UNK func_0021b820();
M2C_UNK func_0021c780(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0021cb00(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0021cb88(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK D_003F3AB0;
extern M2C_UNK D_003F3FF0;
extern M2C_UNK D_00642C78; /* src/data/bss_0064.c: s32 D_00642C78[0x4] */
extern s32 *D_003F34B8;
extern s32 D_00304BE8;
extern s32 D_003E3D68;
extern s32 D_003F34C8;
extern s32 D_003F34CC;
extern s32 D_003F34F0;
extern s32 D_003F350C;
extern s32 D_00641220;
extern s32 D_00641224;
extern s32 D_00642C20; /* src/data/bss_0064.c: void *D_00642C20 */
extern s32 D_00642C24;
extern s32 D_00642C28;
extern s32 D_00642C30;
extern s32 D_00642C48;
extern s32 D_00642C88;
extern s32 D_00643110;
extern s32 D_00643114;
extern u16 D_003F5C60;
s32 func_0010ef90(s32, s32);
s32 func_001c2df0(s32, s32);
s32 func_001f31a8(s32, s32);
s32 func_00214b20(s32);
s32 func_00214f50(void);
s32 func_00214fc8(s32);
s32 func_00219440();
void func_0010eee0(s32, s32, s32, s32);
void func_001eb0a0(s32, s32);
void func_001f3e20(s32, s32);
void func_001f3e48(s32, s32);
void func_001f3e90(s32, s32);
void func_00207830(s32, s32, s32, s32, s32, s32, s32);
void func_0020eb98(void);
void func_0020f3c8(void);
void func_0020fbe0(void);
void func_00213e50(s32, s32, s32, s32);
void func_00214a68(void);
void func_0021c450(s32, s32, s32, s32);

void func_002112c8(s32 arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x69);
}

void func_002112f8(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001f31a8((s32) &D_003F3AB0, 0);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
    }
    D_00641220 = arg0;
    D_00641224 = 0;
    func_0020eb98();
    func_0020f3c8();
    func_0020fbe0();
}

void func_00211d28(void *arg0) {
    s32 temp_s1;

    temp_s1 = M2C_FIELD(arg0, s32 *, 0x24);
    if (temp_s1 != 0) {
        func_001f9010(0x17);
        func_001f94f0(arg0, 0, 0xAE, 0xC, temp_s1, 0x11, 0x80C87850);
    }
}

void func_00213c60(s32 arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x6A);
}

void func_00213fb0(void) {
    if (D_00642C28 >= 0) {
        func_00213e50(D_00642C30 + 0x40, 0, *(M2C_UNK *)((s8 *)(s8 *)&D_00642C78 + (D_00642C28 * 4)) - 1, D_00642C48);
        return;
    }
    func_00213e50(D_00304BE8 + 0x599, 0, D_00642C88 - 1, D_00642C48);
}

void func_00214590(void *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, M2C_FIELD(arg0, s32 *, 0x24), 0x11, 0x80C87850);
}

s32 func_00215358(s32 arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x24) != D_003E3D68) {
        return func_00214b20(arg0);
    }
    return func_00214fc8(arg0);
}

void func_00216078(s32 arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x6B);
}

s32 func_002160a8(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001f31a8((s32) &D_003F3FF0, 0);
    if (temp_v0 != 0) {
        func_001f3e90(arg0, temp_v0);
        func_001f3e20(temp_v0, arg0);
    }
    D_00642C20 = arg0;
    D_00642C24 = 0;
    func_00214a68();
    return func_00214f50();
}

void func_00217f28(s32 arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x6C);
}

void func_00218f58(s32 arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x6D);
}

void func_00219298(void) {
    func_00219288();
}

void func_002192b0(s32 arg0) {
    *D_003F34B8 = arg0;
}

void func_002192d0(void) {
    func_002192c0();
}

void func_00219458(void) {
    func_001efbb8(func_00219440());
}

void func_002194d0(void) {
    D_003F34CC += 1;
    D_003F34C8 -= 1;
}

void func_0021ccd0(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 temp_v0;
    u32 temp_a0;

    func_0021c450(arg0, 0x14, 0x59, 0xDC);
    temp_v0 = func_001c2df0(D_003F34F0, arg1);
    temp_a0 = 0xDC - func_0010ef90(temp_v0, (s32) sp);
    func_0010eee0(((s32) (temp_a0 + (temp_a0 >> 0x1F)) >> 1) + 0x14, 0x7F - (M2C_FIELD(sp, M2C_UNK *, 0x0) * 0xE), M2C_FIELD(arg0, s32 *, 0x90), temp_v0);
}

s32 func_0021dbb8(void) {
    s32 temp_v0;
    u16 *var_s0;
    u16 temp_a0;
    u32 var_s1;

    var_s0 = &D_003F5C60;
    var_s1 = 0;
    do {
        temp_a0 = *var_s0;
        var_s0 += 1;
        func_001eb0a0((s32) temp_a0, 1);
        var_s1 += 1;
        temp_v0 = var_s1 < 0x17U;
    } while (temp_v0 != 0);
    return temp_v0;
}

void func_0021e508(void) {
    D_003F350C += 1;
    D_003F34C8 -= 1;
}

void func_0021e890(void) {

}

void func_0021ed48(void *arg0) {
    func_00207140(M2C_FIELD(arg0, s32 *, 0x40));
}

void func_0021f390(s32 arg0) {
    func_0021b820();
    func_0021cb88(arg0, 0xB0, 8, 0x140, 1);
}

void func_0021f3c8(s32 arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_0021f810(s32 arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_0021faf8(s32 arg0) {
    D_00643110 = arg0;
    D_00643114 = 0;
}

void func_0021ff50(void *arg0) {
    func_00206ea8(M2C_FIELD(arg0, s32 *, 0x24));
}
