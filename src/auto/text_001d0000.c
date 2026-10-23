/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_0062A630; /* src/data/bss_0062.c: u8 D_0062A630[0x10] */
extern M2C_UNK func_001dd5c0;
extern s32 D_002BC128;
extern s32 D_002BCC1C;
extern s32 D_002BD110;
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_0037A378.h"
extern s32 D_0062A220;
extern s32 D_0062A224;
#include "data/pieces/D_002C6440.h"
void *func_0011f090(M2C_UNK *, M2C_UNK, M2C_UNK *);
void *func_001760b0(s32);
void *func_001760d0(s32);
void *func_001760f0(s32);


s32 func_001de558(void *arg0) {
    void *temp_v0;

    temp_v0 = func_001760d0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001df130(void) {
    void *temp_v0;

    temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = 1;
    M2C_FIELD(temp_v0, s32 *, 0x28) = 0;
    return 2;
}

s32 func_001df268(void) {
    void *temp_v0;

    temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = 4;
    M2C_FIELD(temp_v0, s32 *, 0x28) = 0;
    return 2;
}

s32 func_001df5d8(void *arg0) {
    void *temp_v0;

    temp_v0 = func_001760f0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001dfe50(void *arg0) {
    void *temp_v0;

    temp_v0 = func_001760b0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_003F.h"
#include "data/data_0038.h"
#include "data/data_0042.h"
#include "data/pieces/D_002C5AD0.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002BCC1C.h"
#include "data/pieces/D_002BD110.h"
