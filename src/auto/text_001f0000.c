/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_001f4390(s32);
M2C_UNK func_001f43c8(s32);
M2C_UNK func_001f4400(s32);
M2C_UNK func_001f5e10();
M2C_UNK func_001fd858();
M2C_UNK func_001fdfd0(s32);
M2C_UNK func_00266f38(s32, M2C_UNK *);
#include "data/pieces/D_003E9660.h"
#include "data/pieces/D_003F1660.h"
#include "data/pieces/D_003F2670.h"
#include "data/pieces/D_003F2720.h"
s32 func_001f4378();
s32 func_001fe1b8();
s32 func_001fe5a0();
s32 func_00266c08(M2C_UNK);

void func_001f2e98(M2C_UNK **arg0, M2C_UNK **arg1) {
    *arg0 = ((M2C_UNK *)&D_003E9660);
    *arg1 = ((M2C_UNK *)&D_003F1660);
}

void func_001f3648(void *arg0) {
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void **, 0xC);
    M2C_FIELD(arg0, s32 *, 0x8C) = 4;
    if (temp_v1 != NULL) {
        M2C_FIELD(temp_v1, void **, 0x10) = (void *) M2C_FIELD(arg0, void **, 0x10);
    }
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_v1_2 != NULL) {
        M2C_FIELD(temp_v1_2, void **, 0xC) = (void *) M2C_FIELD(arg0, void **, 0xC);
    }
}

void func_001f3e48(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_v1 != NULL) {
        M2C_FIELD(temp_v1, void **, 0x10) = (void *) M2C_FIELD(arg0, void **, 0x10);
    }
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_v1_2 != NULL) {
        M2C_FIELD(temp_v1_2, void **, 0xC) = (void *) M2C_FIELD(arg0, void **, 0xC);
    }
    temp_v0 = M2C_FIELD(arg1, void **, 0x10);
    M2C_FIELD(arg1, void **, 0x10) = arg0;
    M2C_FIELD(arg0, void **, 0xC) = arg1;
    M2C_FIELD(arg0, void **, 0x10) = temp_v0;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0xC) = arg0;
    }
}

void func_001f42b8(s32 arg0) {
    if (func_001f4378() != 0) {
        func_001f4390(arg0);
    }
}

void func_001f42f8(s32 arg0) {
    if (func_001f4378() != 0) {
        func_001f43c8(arg0);
    }
}

void func_001f4338(s32 arg0) {
    if (func_001f4378() != 0) {
        func_001f4400(arg0);
    }
}

void *func_001f4468(void *arg0) {
    void *temp_v0;
    void *var_a0;
    void *var_v1;

    var_a0 = arg0;
    var_v1 = M2C_FIELD(var_a0, void **, 0x10);
    if (var_v1 != NULL) {
        do {
            var_a0 = var_v1;
            temp_v0 = M2C_FIELD(var_a0, void **, 0x10);
            var_v1 = temp_v0;
        } while (temp_v0 != NULL);
    }
    return var_a0;
}

void func_001f8108(void) {
    func_001f5e10();
}

void func_001f8270(void) {
    func_00266f38(func_00266c08(2), ((M2C_UNK *)&D_003F2670));
    func_00266f38(func_00266c08(2), ((M2C_UNK *)&D_003F2720));
}

s32 func_001fd518(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s16 *, 0xD2) + (M2C_FIELD(arg0, u16 *, 0xD0) & 0xF) + 8) >> 4;
}

s32 func_001fd538(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s16 *, 0xDA) + 8) >> 4;
}

void func_001fd610(void *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xCE) = arg1;
}

s32 func_001fd638(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s16 *, 0xD2) + 8) >> 4;
}

void func_001fd648(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xD2) = (s16) (arg1 * 0x10);
}

s16 func_001fd658(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xD8);
}

void func_001fd660(void *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xD8) = arg1;
}

s32 func_001fd668(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s16 *, 0xDA) + 8) >> 4;
}

void func_001fd678(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xDA) = (s16) (arg1 * 0x10);
}

void func_001fe158(s32 arg0) {
    func_001fd858();
    func_001fdfd0(arg0);
}

void func_001fe180(void) {
    if (func_001fe1b8() != 0) {
        func_0011d768(1);
    }
}

s32 func_001fe570(void) {
    s32 var_v0;

    var_v0 = func_001fe5a0();
    if (var_v0 != 0) {
        func_0011d768(2);
        var_v0 = 1;
    }
    return var_v0;
}
