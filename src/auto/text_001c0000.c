/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00109df8();
M2C_UNK func_00109f48(s32);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_006297F8; /* src/data/bss_0062.c: u8 D_006297F8[0x10] */
M2C_UNK D_00629808[0x3a] ALIGNED(8);
extern M2C_UNK func_001c07c8;
#include "data/pieces/D_0037A378.h"
extern s32 D_0038CCCC;
extern u32 D_002C5958;
s32 func_00123618(s32);

void func_001c07f0(void) {
    func_0011efa8(&D_006297F8, &D_00629808, 0x1C, 8);
    func_0011ef10(0xC352, &func_001c07c8);
}

/* func_001ca790 and func_001ca7c8 are in src/camera/camera.c,
 * func_001cc628 and func_001ccbd8 in src/msgwin/msgwin.c, and the library
 * functions func_001cd238 .. func_001cdea8 in src/vm/vm_lib.c. */

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
