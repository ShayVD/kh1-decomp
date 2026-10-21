/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0014aab0(M2C_UNK *);
extern M2C_UNK D_0054C440;
#include "data/pieces/D_00350D88.h"
f32 PlatSqrtf(f32);
s32 func_001375f0();
s32 func_001477c8(M2C_UNK);
s32 func_0014ee88();
void func_00142b30(void *, void *);
void func_0014cc38(s32);
void func_002673b8(void *);
void func_00267560(void *, void *, f32);

s32 func_00140f08(void *arg0, s32 arg1) {
    s32 var_v0;

    if (!((M2C_FIELD(arg0, u16 *, 0x30C) == 0xFFFF) || (func_001375f0() == 0) || (var_v0 = 0xB, !(M2C_FIELD(arg0, f32 *, 0x24) < 0.0f)))) {
        return var_v0;
    }
    var_v0 = 0xA;
    if (arg1 == 0) {
        var_v0 = 0;
        if (M2C_FIELD(arg0, f32 *, 0x24) <= 0.0f) {
            var_v0 = 0xA;
        }
    }
    return var_v0;
}

void func_00142c80(void *arg0) {
    s32 sp[4];    void *temp_v0;

    func_002673b8(sp);
    func_00267560(sp, sp, 2.0f * M2C_FIELD(arg0, f32 *, 0x2C0));
    temp_v0 = M2C_FIELD(arg0, void **, 0x6C);
    M2C_FIELD(sp, f32 *, 0x4) = -M2C_FIELD(temp_v0, f32 *, 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = M2C_FIELD(temp_v0, f32 *, 0x10) * 0.7f;
    func_00142b30(arg0, sp);
}

s32 func_00147808(s32 arg0) {
    return *(M2C_UNK *)((s32) ((arg0 * 4)) + (s32) (func_001477c8(0x258)));
}

void func_0014aaf0(s64 *arg0) {
    s64 temp_v1;

    temp_v1 = *arg0;
    if (!((s32) ((s64) (temp_v1 << 0x18) >> 0x20) & 1)) {
        *arg0 = temp_v1 | 0x200000;
    }
}

void func_0014ab78(s32 arg0) {
    s8 *var_s0;
    s32 var_s2;

    var_s0 = &D_0054C440;
    var_s2 = 0x3F;
    do {
        if (((s32) ((s64) (M2C_FIELD(var_s0, s64 *, 0) << 0x15) >> 0x20) & 1) && ((M2C_FIELD(var_s0, s32 *, 0x34) == arg0) || (M2C_FIELD(var_s0, s32 *, 0x90) == arg0))) {
            func_0014aab0(var_s0);
        }
        var_s2 -= 1;
        var_s0 += 0xC0;
    } while (var_s2 >= 0);
}

void func_0014ac00(void *arg0, s32 arg1) {
    s32 *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 **, 0x60);
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) | arg1);
    if (temp_v1 != NULL) {
        *temp_v1 |= arg1;
    }
    if (!((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x30) << 0x16) >> 0x20) & 1)) {
        M2C_FIELD(arg0, s64 *, 0) = (s64) (M2C_FIELD(arg0, s64 *, 0) | 0x100000);
    }
}

f32 func_0014cce0(s32 arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x3B8) = PlatSqrtf((2.0f * fparg0) / 0.48469386f);
    M2C_FIELD(arg0, f32 *, 0x3BC) = (f32) -fparg0;
    func_0014cc38(arg0);
    return M2C_FIELD(arg0, f32 *, 0x3B8);
}

s32 func_0014efe0(s32 arg0, s32 arg1) {
    s32 var_v0;

    if (!((arg1 <= 0) || (var_v0 = 1, (((func_0014ee88() >> (arg1 - 1)) & 1) == 0)))) {
        return var_v0;
    }
    var_v0 = 0;
    return var_v0;
}

s32 func_0014f5c8(void *arg0) {
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x70);
    var_v0 = 1;
    if (temp_v1 == 0x17) {
        return var_v0;
    }
    var_v0 = (*(M2C_UNK *)((s8 *)(s8 *)((volatile M2C_UNK *)&D_00350D88) + (temp_v1 << 5)) & 3) == 2;
    return var_v0;
}
