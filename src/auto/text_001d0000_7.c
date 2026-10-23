/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"
extern M2C_UNK D_0062A630; /* src/data/bss_0062.c: u8 D_0062A630[0x10] */
extern M2C_UNK func_001dd5c0;
extern s32 D_0029B410;
extern s32 D_0029B414;
#include "data/pieces/D_0037A378.h"
void *func_0011f090(M2C_UNK *, M2C_UNK, M2C_UNK *);


s32 func_001dfaa0(void *arg0) {
    void *temp_v0;

    if ((D_0029B410 != 0) && (D_0029B414 != 0)) {
        temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
        M2C_FIELD(temp_v0, s32 *, 0x2C) = 0xB;
        M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}
#include "data/data_0029.h"
#include "data/data_002B.h"
#include "data/data_0049.h"
