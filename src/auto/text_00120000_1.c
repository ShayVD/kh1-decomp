/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004F.h"

M2C_UNK func_0011fd60(s32, M2C_UNK, M2C_UNK *);
M2C_UNK func_0011fe20();
M2C_UNK func_00120438(s32 *, M2C_UNK *);
M2C_UNK func_00269fd0(M2C_UNK);
M2C_UNK func_0026a530(M2C_UNK);
extern M2C_UNK D_0048D2A0;
extern M2C_UNK D_004F2A00; /* src/data/bss_004F.c: char D_004F2A00[0x800] */
extern s32 D_004F3208;

void func_00120ba0(void) {
    func_0026a530(0);
    func_00120438(&D_004F3208, &D_0048D2A0);
    func_0011fd60(D_004F3208, 1, &D_004F2A00);
    func_00269fd0(0);
    func_0011fe20();
}
#include "data/data_0048.h"
