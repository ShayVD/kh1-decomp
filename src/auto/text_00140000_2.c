/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001374a8(void *);
extern M2C_UNK (*D_0054C210)();
extern f32 D_00306844;
s32 func_001471e8();
s32 func_001499a0(void *);
void *func_00123488(s32);

void func_00142fe0(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v0_2;

    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) == 0) {
        func_001374a8(arg1);
    }
    temp_v0 = M2C_FIELD(arg0, void **, 8);
    if ((temp_v0 == NULL) || ((u16) M2C_FIELD(M2C_FIELD(arg1, void **, 0x130), u16 *, 0x4C) < (u16) M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x130), u16 *, 0x4C))) {
        M2C_FIELD(arg0, void **, 8) = arg1;
    }
    temp_v0_2 = M2C_FIELD(arg1, void **, 8);
    if ((temp_v0_2 == NULL) || ((u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) < (u16) M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 0x130), u16 *, 0x4C))) {
        M2C_FIELD(arg1, void **, 8) = arg0;
    }
}

s32 func_001464a0(void *arg0) {
    return ((s32) ((f32) M2C_FIELD(arg0, s32 *, 4) * D_00306844) * 5) + ((s32) ((f32) M2C_FIELD(arg0, s32 *, 8) * D_00306844) * 0x14) + (s32) ((f32) M2C_FIELD(arg0, s32 *, 0) * D_00306844);
}

s32 func_00147240(void) {
    return func_001471e8() != 0;
}

void func_00147260(s64 *arg0) {
    *arg0 &= ~1;
}

void func_00149e60(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_00123488(arg0 | 0x10000);
    M2C_FIELD(temp_v0, s32 *, 0x14C) = func_001499a0(temp_v0);
    if (D_0054C210 != NULL) {
        D_0054C210();
    }
    D_0054C210 = NULL;
}

s32 func_0014d778(void *arg0, s32 arg1) {
    if ((M2C_FIELD(arg0, f32 *, 0x3C4) >= 0.0f) && ((M2C_FIELD(arg0, f32 *, 0x3D4) <= M2C_FIELD(arg0, f32 *, 0x3BC)) || (arg1 == 0))) {
        return 4;
    }
    return M2C_FIELD(arg0, s32 *, 0x70);
}

s32 func_0014f828(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}
