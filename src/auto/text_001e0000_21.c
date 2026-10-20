/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0063.h"

extern s32 D_002BBBA0;
extern s32 D_002C1364;
extern s32 D_002C5958;
extern s32 D_006314D4;
extern s64 D_00389C90[];
s32 func_0011e340(s32);
s32 func_0011e368(s32, s32);
void func_0011c7d8(s32);
void func_00155878(void);
void func_001e7e78(void);

void func_001e2748(void) {
    D_002BBBA0 = 1;
    D_00389C90[1550] = (s64) (D_00389C90[1550] | ((s64) 0x8000 << 0x1F));
}

s32 func_001e7ea8(s32 arg0) {
    D_006314D4 = M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) - 1;
    func_0011c7d8(D_002C1364);
    func_001e7e78();
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001e9048(s32 arg0) {
    if ((func_0011e340(0) == 0) && (func_0011e368(-1, -1) == 0)) {
        D_002C5958 &= 0xFFFBFFFF;
        func_00155878();
        M2C_FIELD(arg0, s64 *, 0x328) = (s64) (M2C_FIELD(arg0, s64 *, 0x328) | 0x2000);
        return 6;
    }
    return 4;
}
#include "data/data_002B.h"
#include "data/data_002C.h"
