/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"

M2C_UNK func_001038b0(s32);
M2C_UNK func_00111d90(s32);
M2C_UNK func_001248e8(s32);
M2C_UNK func_00137330(s32, M2C_UNK, s32);
M2C_UNK func_0013df40(s32, s32);
M2C_UNK func_0013dfa0(s32);
extern M2C_UNK D_002E26A0;
extern M2C_UNK D_0062A630; /* src/data/bss_0062.c: u8 D_0062A630[0x10] */
extern M2C_UNK func_001dd5c0;
extern s32 D_002A61F0;
extern s32 D_0038D160;
extern s32 D_0062A210;
s32 func_00123488(s32);
s32 func_0013bf68();
s32 func_0014e510(s32);
void *func_0011f090(M2C_UNK *, M2C_UNK, M2C_UNK *);
void *func_001230a0(void *);
void *func_001760b0(s32);
void *func_001760d0(s32);
void *func_001760f0(s32);

s32 func_001d0868(void *arg0) {
    if (M2C_FIELD(&D_002E26A0, s32 *, 0) != 0) {
        func_0013df40(M2C_FIELD(&D_002E26A0, s32 *, 0), M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    }
    if (M2C_FIELD(&D_002E26A0, s32 *, 4) != 0) {
        func_0013df40(M2C_FIELD(&D_002E26A0, s32 *, 4), M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    }
    if (M2C_FIELD(&D_002E26A0, s32 *, 8) != 0) {
        func_0013df40(M2C_FIELD(&D_002E26A0, s32 *, 8), M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d0938(void) {
    if (M2C_FIELD(&D_002E26A0, s32 *, 0) != 0) {
        func_0013dfa0(M2C_FIELD(&D_002E26A0, s32 *, 0));
    }
    if (M2C_FIELD(&D_002E26A0, s32 *, 4) != 0) {
        func_0013dfa0(M2C_FIELD(&D_002E26A0, s32 *, 4));
    }
    if (M2C_FIELD(&D_002E26A0, s32 *, 8) != 0) {
        func_0013dfa0(M2C_FIELD(&D_002E26A0, s32 *, 8));
    }
    return 2;
}

s32 func_001d1010(void *arg0) {
    s32 temp_v0;

    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) + 1);
    temp_v0 = func_00123488(M2C_FIELD(arg0, s32 *, 0));
    M2C_FIELD(arg0, s32 *, 4) = temp_v0;
    if (temp_v0 != 0) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = 1;
        return 2;
    }
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = 0;
    return 2;
}

s32 func_001d3118(void *arg0) {
    func_00111d90(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d35a0(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    func_00137330(func_00123488(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x17C)), 0, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 2);
    return 2;
}

s32 func_001d5010(void *arg0) {
    D_002A61F0 = 0;
    func_001038b0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d5060(void) {
    s32 temp_v0;

    temp_v0 = D_0062A210 - 1;
    D_0062A210 = temp_v0;
    if (temp_v0 < 0) {
        D_002A61F0 = 0;
        return 4;
    }
    return 0;
}

s32 func_001d6c80(void) {
    void *var_s0;

    var_s0 = func_001230a0(NULL);
    if (var_s0 != NULL) {
        do {
            if ((((u64) M2C_FIELD(var_s0, u64 *, 0x370) >> 0x25) & 3) == 2) {
                func_001248e8(M2C_FIELD(var_s0, s32 *, 4));
            }
            var_s0 = func_001230a0(var_s0);
        } while (var_s0 != NULL);
    }
    return 2;
}

s32 func_001d7548(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = func_0014e510(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    return 2;
}

void func_001d99f0(void) {

}

s32 func_001d9d30(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) + 1);
    return 2;
}

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
