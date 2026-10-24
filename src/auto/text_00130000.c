/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
M2C_UNK func_0013ed88();
M2C_UNK func_0013ee40(s32, s32, s32);
M2C_UNK func_0013f770();
M2C_UNK func_0013fd88(f32);
M2C_UNK func_0024ffa4(s32, s32, u32);
#include "data/pieces/D_00304BE8.h"
s32 func_002193f0();

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
