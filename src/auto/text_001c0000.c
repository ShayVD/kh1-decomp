/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00106780(s32);
M2C_UNK func_00106880(s32);
M2C_UNK func_00106978(s32);
M2C_UNK func_00106a58(s32);
M2C_UNK func_00109df8();
M2C_UNK func_00109f48(s32);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_001336b8();
M2C_UNK func_0017e768();
M2C_UNK func_0017e8c8();
M2C_UNK func_0017e910();
#include "data/pieces/D_003DABD0.h"
extern M2C_UNK D_006297F8; /* src/data/bss_0062.c: u8 D_006297F8[0x10] */
M2C_UNK D_00629808[0x3a] ALIGNED(8);
extern M2C_UNK func_001c07c8;
extern s32 D_002BBE04;
#include "data/pieces/D_0037A378.h"
extern s32 D_0038CCCC;
extern u32 D_002C5958;
s32 func_0011e340(M2C_UNK);
s32 func_00123618(s32);
s32 func_001559f0(M2C_UNK, M2C_UNK);

void func_001c07f0(void) {
    func_0011efa8(&D_006297F8, &D_00629808, 0x1C, 8);
    func_0011ef10(0xC352, &func_001c07c8);
}

s32 func_001ca790(void) {
    if (!(((u32) D_002C5958 >> 1) & 1)) {
        func_0017e8c8();
    }
    return 2;
}

s32 func_001ca7c8(void) {
    if (!(((u32) D_002C5958 >> 1) & 1)) {
        func_0017e910();
    }
    return 2;
}

s32 func_001cc628(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001ccbd8(void) {
    func_0017e768();
    return 2;
}

void func_001cd238(void) {
    M2C_FIELD(&D_003DABD0, s32 *, 0) = func_001559f0(0x34, 4);
    M2C_FIELD(&D_003DABD0, s32 *, 4) = func_001559f0(0x38, 4);
}

s32 func_001cd2c0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001cd740(void) {
    return 2;
}

s32 func_001cd748(void) {
    D_0037A378 |= 2;
    func_001336b8();
    return 2;
}

s32 func_001cd7e0(void) {
    return 2;
}

s32 func_001cd7e8(void) {
    if (func_0011e340(0) == 0) {
        D_0037A378 &= ~2;
        return 2;
    }
    return 4;
}

s32 func_001cdd18(void *arg0) {
    func_00106780(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001cdd60(void *arg0) {
    func_00106880(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001cdda8(void *arg0) {
    func_00106a58(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001cddf0(void *arg0) {
    func_00106978(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001cdea8(void) {
    if (D_002BBE04 == 1) {
        D_002BBE04 = 4;
    }
    return 2;
}

s32 func_001ce298(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) + 1);
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) = func_00123618(D_0038CCCC);
    return 2;
}

s32 func_001cfa58(void) {
    func_00109df8();
    return 2;
}

s32 func_001cfa78(void *arg0) {
    if (!(D_0037A378 & 1)) {
        func_00109f48(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}
#include "data/data_0038.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBE04.h"
