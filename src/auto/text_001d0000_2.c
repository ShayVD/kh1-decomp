/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"

#include "data/pieces/D_002E26A0.h"
extern M2C_UNK D_0062A630; /* src/data/bss_0062.c: u8 D_0062A630[0x10] */
extern M2C_UNK func_001dd5c0;
extern s32 D_0038D160;
s32 func_0013bf68();
void *func_0011f090(M2C_UNK *, M2C_UNK, M2C_UNK *);
void *func_001760b0(s32);
void *func_001760d0(s32);
void *func_001760f0(s32);

s32 func_001dbc90(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) D_0038D160;
    return 2;
}

s32 func_001dc800(void *arg0) {
    s32 temp_v0;

    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) + 1);
    temp_v0 = func_0013bf68();
    if (temp_v0 == 1) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = temp_v0;
        return 2;
    }
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = 0;
    return 2;
}

s32 func_001de4e8(void *arg0) {
    s32 temp_s1;
    void *temp_v0;

    temp_s1 = arg0 + 4;
    temp_v0 = func_001760d0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x17C));
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s32 **, 0x28) = M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 2);
    return 2;
}

s32 func_001df2a8(void *arg0) {
    void *temp_v0;

    temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = 5;
    M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001df568(void *arg0) {
    s32 temp_s1;
    void *temp_v0;

    temp_s1 = arg0 + 4;
    temp_v0 = func_001760f0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x17C));
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s32 **, 0x28) = M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 2);
    return 2;
}

s32 func_001df630(void *arg0) {
    void *temp_v0;

    temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = 6;
    M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001dfa38(void *arg0) {
    void *temp_v0;

    temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = 9;
    M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001dfd78(void *arg0) {
    void *temp_v0;

    temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = 0xC;
    M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001dfde0(void *arg0) {
    s32 temp_s1;
    void *temp_v0;

    temp_s1 = arg0 + 4;
    temp_v0 = func_001760b0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x17C));
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s32 **, 0x28) = M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 2);
    return 2;
}

s32 func_001dffa0(void *arg0) {
    void *temp_v0;

    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
        M2C_FIELD(temp_v0, s32 *, 0x2C) = 0xD;
        M2C_FIELD(temp_v0, void **, 0x14) = arg0;
        M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}
#include "data/data_002A.h"
#include "data/data_0038.h"
