/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00111ef0(s32, M2C_UNK *);
M2C_UNK func_00120748(M2C_UNK *, s32, M2C_UNK *, M2C_UNK);
extern M2C_UNK D_0062A328; /* src/data/bss_0062.c: char D_0062A328[0x100] */
extern M2C_UNK func_001d3160;
extern M2C_UNK func_001ddbf8;
extern s32 D_00389C90[];
extern s32 D_0062A220;

s32 func_001d1348(void *arg0) {
    D_00389C90[3154] = (s32) (D_00389C90[3154] | M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d1380(void *arg0) {
    D_00389C90[3154] = (s32) (D_00389C90[3154] & ~M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d31d8(void *arg0) {
    func_00111ef0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), &func_001d3160);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d5fa8(void *arg0) {
    void *temp_a3;

    temp_a3 = arg0 + 4;
    D_00389C90[3164] = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_a3), s32 *, 0x17C);
    D_00389C90[3165] = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_a3), s32 *, 0x180);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 2);
    return 2;
}

void func_001dce90(void) {
    D_00389C90[3296] = (s32) (D_00389C90[3296] + 1);
}

void func_001ddc48(void) {
    func_00120748(&D_0062A328, D_0062A220, &func_001ddbf8, 0);
}
