/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00120748(M2C_UNK *, s32, M2C_UNK *, M2C_UNK);
extern M2C_UNK D_0062A328; /* src/data/bss_0062.c: char D_0062A328[0x100] */
extern M2C_UNK func_001ddbf8;
extern s32 D_00389C90[];
extern s32 D_0062A220;

void func_001dce90(void) {
    D_00389C90[3296] = (s32) (D_00389C90[3296] + 1);
}

void func_001ddc48(void) {
    func_00120748(&D_0062A328, D_0062A220, &func_001ddbf8, 0);
}
