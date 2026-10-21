/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"

M2C_UNK func_001350d0(void *);
M2C_UNK func_00167978(s32, s32, s32);
M2C_UNK func_00167ac0(s32, s32, s32);
M2C_UNK func_00167fd0(s32, s32, s32);
#include "data/pieces/D_002E31A8.h"
extern s32 D_00304BE8;
s32 func_00135888();

void func_001336b8(void) {
    D_002E31A8 &= ~2;
}

void func_00135658(void *arg0) {
    void *var_s0;

    var_s0 = M2C_FIELD(arg0, void **, 0x3EC);
    if (var_s0 != NULL) {
        do {
            func_001350d0(var_s0);
            var_s0 = M2C_FIELD(var_s0, void **, 0x30);
        } while (var_s0 != NULL);
    }
    M2C_FIELD(arg0, void **, 0x3EC) = NULL;
}

void func_001358b8(Actor *arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0->unk15C;
    func_00167ac0(temp_s0, func_00135888(), arg1 & 0xFFFF);
}

void func_001358f8(Actor *arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0->unk15C;
    func_00167fd0(temp_s0, func_00135888(), arg1 & 0xFFFF);
}

void func_00135938(Actor *arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0->unk15C;
    func_00167978(temp_s0, func_00135888(), arg1 & 0xFFFF);
}

void func_0013c270(s32 arg0, s8 arg1) {
    M2C_FIELD((arg0 + D_00304BE8), s8 *, 0x844) = arg1;
}

s8 func_0013c288(s32 arg0) {
    return M2C_FIELD((arg0 + D_00304BE8), s8 *, 0x844);
}

s32 func_0013c6a8(u32 arg0) {
    return M2C_FIELD((((arg0 >> 2) * 4) + D_00304BE8), s32 *, 0x5CC) & (1 << (arg0 & 3));
}
