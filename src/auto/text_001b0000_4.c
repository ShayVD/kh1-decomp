/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00009C00;
extern s8 D_002C5AD0;
s32 func_001ba958(s32);
s32 func_001ba9d8();
s32 func_001baf08(s32);
s32 func_001bb260();
s32 func_00232cc0(s32);
void func_001b9ec0(void);

void func_001b9b30(void) {
    void *temp_v0;

    temp_v0 = func_00232cc0(4);
    if ((M2C_FIELD(temp_v0, s32 *, 0) != 0x494D5547) || (M2C_FIELD(temp_v0, s32 *, 4) != 0x101)) {
        func_001b9ec0();
    }
}

void func_001b9bb0(s32 arg0, s32 arg1) {
    *(s8 *)((s8 *)&D_00009C00 + (arg0 + func_00232cc0(4))) = arg1;
}

void func_001ba2a8(s32 arg0, s32 arg1) {
    s32 var_a1;
    u8 *temp_v0;
    u8 *var_a2;

    var_a2 = func_001ba9d8() + 0x50;
    var_a1 = 0;
    do {
        temp_v0 = arg1 + var_a1;
        var_a1 += 1;
        *var_a2 = *temp_v0;
        var_a2 += 1;
    } while (var_a1 < 0x20);
}

void *func_001ba488(s32 arg0) {
    return &D_002C5AD0 + (arg0 * 0x70);
}

s32 func_001baf70(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_001baf08(arg1);
    return temp_s0 - func_001baf08(arg2);
}

s32 func_001bb3f8(void) {
    if ((func_001ba958(func_001bb260()) < 3) == 0) {
        return 1;
    }
    return 0;
}
#include "data/data_0037.h"
