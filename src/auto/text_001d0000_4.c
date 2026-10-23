/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001008d8(f32);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
extern M2C_UNK func_001dc580;
extern s32 D_002C5958;
#include "data/pieces/D_00304BE8.h"
s32 func_0013bf68();
s32 func_0014efe0(s32, s32);
void *func_00123488(u8);

s32 func_001d4578(void *arg0) {
    s32 temp_s1;
    void *temp_v0;

    temp_s1 = arg0 + 4;
    temp_v0 = func_00123488(M2C_FIELD((M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) + ((s32)D_00304BE8)), u8 *, 0x48E));
    if (temp_v0 != NULL) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = (s32) ((M2C_FIELD(temp_v0, f32 *, 0x3C) * 180.0f) / 3.141592979f);
    }
    return 2;
}

s32 func_001d4ac8(void *arg0) {
    func_001008d8(((f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) * 3.141592979f) / 180.0f);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d5308(void *arg0) {
    s32 *temp_a0;

    temp_a0 = M2C_FIELD(arg0, s32 **, 4);
    if (temp_a0 != NULL) {
        *temp_a0 &= 0xFDFFFFFF;
    }
    return 2;
}

s32 func_001d6930(void) {
    D_002C5958 &= 0xF7FFFFFF;
    return 2;
}

s32 func_001d8638(void) {
    D_002C5958 &= 0xFFFF7FFF;
    return 2;
}

s32 func_001da740(void *arg0) {
    s32 temp_s1;
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    temp_s1 = arg0 + 4;
    if (temp_v0 != 0) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = func_0014efe0(temp_v0, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    } else {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = 0;
    }
    return 2;
}

s32 func_001dbc10(void) {
    D_002C5958 &= 0xFFDFFFFF;
    return 2;
}

s32 func_001dc7c0(void) {
    if (func_0013bf68() == 1) {
        func_0011ef10(0x2E631, &func_001dc580);
    }
    return 2;
}
