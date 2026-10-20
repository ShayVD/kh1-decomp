/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0054.h"

M2C_UNK func_0011d3c8(u16, s32, M2C_UNK);
M2C_UNK func_001252f8();
M2C_UNK func_0013c458(u16);
M2C_UNK func_00140db8();
M2C_UNK func_00141b10(u16, void *);
M2C_UNK func_00141eb8();
M2C_UNK func_00147260(void *);
M2C_UNK func_00147808(s32);
M2C_UNK func_00148570();
M2C_UNK func_001586f0();
M2C_UNK func_0016f7b8();
M2C_UNK func_001763f0(M2C_UNK *);
M2C_UNK func_00176488(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK *D_00350CE0;
extern M2C_UNK D_00308CE0;
extern M2C_UNK D_00348CE0;
M2C_UNK D_00547BC0[0x10] ALIGNED(64);
extern s32 D_00532B80;
extern s32 D_00547BA0;
extern s32 D_00547BA8;
extern s32 D_00547BAC;
extern s32 D_00547BB0; /* src/data/bss_0054.c: void *volatile D_00547BB0 */
extern s32 D_0054F44C;
s32 func_001477c8(M2C_UNK);
s32 func_001ecfd8(M2C_UNK);

s32 func_00140f88(void) {
    func_00140db8();
    return 0;
}

s32 func_00141200(void *arg0, s32 arg1) {
    return ((s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x70) >> arg1) & 1;
}

void func_00141898(void *arg0) {
    func_0013c458(M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C));
}

void func_00141e68(void *arg0) {
    void *temp_v1;
    void *temp_v1_2;

    func_00141b10(M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C), M2C_FIELD(arg0, void **, 0x6C));
    temp_v1 = M2C_FIELD(arg0, void **, 0x6C);
    M2C_FIELD(M2C_FIELD(temp_v1, void **, 0xC8), u8 *, 1) = (u8) M2C_FIELD(temp_v1, u8 *, 0x3C);
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x6C);
    M2C_FIELD(M2C_FIELD(temp_v1_2, void **, 0xC8), u8 *, 3) = (u8) M2C_FIELD(temp_v1_2, u8 *, 0x44);
}

void func_00142000(void) {
    func_001586f0();
    func_001252f8();
    func_0016f7b8();
    func_00141eb8();
}

s32 func_001425d0(Actor *arg0) {
    s32 var_a1;

    var_a1 = 0;
    if ((arg0->unk000 & 0x200000) || (arg0->unk088 & 1) || (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), f32 *, 0x18) == 0.0f)) {
        var_a1 = 1;
    }
    return var_a1;
}

f32 func_00144368(Actor *arg0) {
    return arg0->unk324 - arg0->unk2D4;
}

s32 func_00146878(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_00532B80 == 0) {
        var_a0 = func_001ecfd8(0) == 0;
    }
    return var_a0;
}

void func_00147300(void *arg0) {
    func_0011d3c8(M2C_FIELD(arg0, u16 *, 8), M2C_FIELD(arg0, s32 *, 4), 0x78);
    func_00147260(arg0);
}

s32 func_00147730(s32 arg0) {
    return func_001477c8(0xC8A8) + (arg0 * 2);
}

void func_00147760(s32 arg0) {
    func_00147808(arg0 + 0x127);
}

s32 func_00147778(s32 arg0) {
    return D_00547BB0 + (arg0 * 2);
}

s32 func_00147840(s32 arg0) {
    return (D_00547BA0 + (arg0 * 0x14)) - 0x14;
}

s32 func_001478a0(s32 arg0) {
    return (D_00547BA8 + ((arg0 & ~0x80) * 0xC)) - 0xC;
}

s32 func_001478c8(s32 arg0) {
    return D_00547BAC + (arg0 * 0x10);
}

s32 func_001486b0(s32 arg0) {
    func_00148570();
    return arg0;
}

M2C_UNK *func_00148e20(void) {
    func_00176488(&D_00348CE0, &D_00547BC0, 0, 0x4E20);
    return &D_00547BC0;
}

void func_00148e60(void) {
    D_00350CE0 = &D_00308CE0;
    func_001763f0(&D_00308CE0);
    func_001763f0(&D_00348CE0);
}

void func_0014ec10(s32 arg0) {
    D_0054F44C &= ~(1 << (arg0 - 1));
}

void func_0014ec38(s32 arg0) {
    D_0054F44C |= 1 << (arg0 - 1);
}
#include "data/bss_0053_mixed.h"
