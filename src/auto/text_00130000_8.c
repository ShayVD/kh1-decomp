/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"

M2C_UNK func_0011a0a0();
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
M2C_UNK func_0011f320(M2C_UNK *, s32);
M2C_UNK func_00132790(M2C_UNK *, M2C_UNK, M2C_UNK *);
M2C_UNK func_00135df0(void *, void *);
M2C_UNK func_00136428(void *, s32, s32, void *, f32);
M2C_UNK func_00137688(s32, f32);
M2C_UNK func_001763f0(void *);
M2C_UNK func_001c4808(s32, s32);
M2C_UNK func_001c48c8(s32, s32, s32);
M2C_UNK func_00267548(void *, void *, s32);
extern M2C_UNK D_002E31F0;
extern M2C_UNK D_003031F0;
extern M2C_UNK D_005252C8; /* src/data/bss_0052.c: W32Tbl D_005252C8 */
extern M2C_UNK D_005252F8; /* src/data/bss_0052.c: W32Tbl D_005252F8 */
M2C_UNK D_00525430[0x180] ALIGNED(16);
extern M2C_UNK D_00525A30; /* src/data/bss_0052.c: u8 D_00525A30[0x10] */
extern M2C_UNK D_00526640; /* src/data/bss_0052.c: W32E12 D_00526640[32] */
extern M2C_UNK D_0052A100; /* src/data/bss_0052.c: u8 D_0052A100[0x10] */
extern M2C_UNK D_0052AA58; /* src/data/bss_0052.c: u8 D_0052AA58[0x10] */
extern f32 D_002BBDFC;
extern s32 D_002C5958;
extern s32 D_0052AE54;
f32 func_00135ca0(f32);
f32 func_001376e8();
s32 func_00130340(s32, s32, f32);
s32 func_001332f0(s32, s32, s32, s32, s32, s32, s32);
s32 func_00167f68(s32, s32);
s32 func_0017e840(void);
void func_00121a78(s32, s32);
void func_001318e8(s32, s32, s32);

void func_00131a30(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[16];
    func_001318e8(arg0, arg1, (s32) sp);
    func_00121a78((s32) sp, arg2);
}

s32 func_00131ab0(void *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (!(M2C_FIELD(arg0, s32 *, 0x160) & 1) && (M2C_FIELD(arg0, f32 *, 0x170) == 0.0f) && (M2C_FIELD(arg0, f32 *, 0x280) <= (M2C_FIELD(arg0, f32 *, 0x16C) + (D_002BBDFC * M2C_FIELD(arg0, f32 *, 0x284))))) {
        var_v1 = 1;
    }
    return var_v1;
}

void func_00132220(s32 arg0, s32 arg1) {
    func_00167f68(arg0, arg1 + M2C_FIELD(arg1, s32 *, 4));
}

void func_00132e38(void) {
    func_00132790(&D_002E31F0, 0, &D_005252C8);
    func_00132790(&D_003031F0, 0, &D_005252F8);
}

void func_001330c8(void *arg0) {
    func_001763f0(arg0 + M2C_FIELD(arg0, s32 *, 8));
}

s32 func_001334b8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a7;

    temp_a7 = M2C_FIELD(arg0, s32 *, 0x13C);
    return func_001332f0(arg0, arg2, 0, M2C_FIELD(arg0, s32 *, 0x68), temp_a7 + M2C_FIELD(((arg1 * 4) + temp_a7), s32 *, 4), arg3, arg4);
}

s32 func_001334f8(void) {
    func_0011f130(&D_00525A30, 0);
    return 0;
}

void func_00133520(void) {
    func_0011efa8(&D_00525A30, &D_00525430, 0x30, 0x20);
}

s32 func_00133550(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(M2C_UNK), 0x48)(-1);
    return 4;
}

void func_00133708(void) {
    D_002C5958 &= ~2;
    func_0017e840();
}

s32 func_00133738(void) {
    s8 *var_s0;
    s32 temp_a1;
    s32 var_s1;

    var_s0 = &D_00526640;
    var_s1 = 0x1F;
    do {
        temp_a1 = M2C_FIELD(var_s0, s32 *, 0);
        switch (temp_a1) {                          /* irregular */
        case -1:
            break;
        case -2:
            func_001c4808(M2C_FIELD(M2C_FIELD(var_s0, void **, 4), s32 *, 4), M2C_FIELD(var_s0, s32 *, 8));
            break;
        default:
            func_001c48c8(M2C_FIELD(M2C_FIELD(var_s0, void **, 4), s32 *, 4), temp_a1, M2C_FIELD(var_s0, s32 *, 8));
            break;
        }
        var_s1 -= 1;
        M2C_FIELD(var_s0, s32 *, 0) = -1;
        var_s0 += 0xC;
    } while (var_s1 >= 0);
    return 0;
}

void func_001366d8(Actor *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    f32 temp_f20;

    temp_f20 = func_00135ca0(arg0->unk118);
    func_00135df0(arg0, sp);
    func_00267548(sp, sp, arg2);
    func_00136428(arg0, ~(1 << (arg1 - 1)), arg0->unk394, sp, temp_f20);
}

s32 func_00136c98(void) {
    func_0011f130(&D_0052A100, 0);
    return 0;
}

void func_001386f8(s32 arg0) {
    func_0011f320(&D_0052AA58, arg0);
}

s32 func_00138718(void) {
    func_0011a0a0();
    return 0;
}

void func_001394a8(s32 arg0) {
    func_00130340(arg0, 0x01000066, 0.0f);
    M2C_FIELD(arg0, f32 *, 0x404) = 68.0f;
}

void func_0013ba08(void) {
    D_0052AE54 = 2;
}

void func_0013bef0(s32 arg0) {
    func_00137688(arg0, func_001376e8());
}
#include "data/data_0030.h"
