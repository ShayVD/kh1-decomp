/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004D.h"

extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
extern s32 D_002BCAE0;
#include "data/pieces/D_002BCDA0.h"
extern s32 D_002BCDA8;
extern s32 D_004D9244;
s32 func_00111660(s32, s32);
s32 func_00112b18(void);
void D_00F20000(M2C_UNK, s32);
void FlushCache(M2C_UNK);

void func_00110fc8(void) {
    D_002BCAE0 = 1;
    FlushCache(2);
    D_00F20000(0, D_004D9244);
}

void func_00112bb8(s32 arg0) {
    s32 temp_v0;

    D_002BCDA8 = arg0;
    temp_v0 = *(M2C_UNK *)((s32) ((arg0 << 6)) + (s32) D_002BCDA0);
    D_002BC130 = temp_v0;
    D_002BC134 = func_00111660(D_002BC128, temp_v0);
    func_00112b18();
}
#include "data/data_002B.h"
#include "data/pieces/D_002BC128.h"
