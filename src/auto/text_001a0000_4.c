/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"
M2C_UNK func_002675a8(s32, M2C_UNK *);
M2C_UNK func_002675b8(s32, M2C_UNK *);
#include "data/pieces/D_003701D0.h"
#include "data/pieces/D_003701F0.h"
extern M2C_UNK D_00615E70;

void pppRyjDrawMatrixWorldDttCon(s32 arg0, PppEntry *arg1) {
    func_002675b8(arg0 + arg1->offsets[1] + 0xE0, &D_00615E70);
}

void pppRyjDrawMatrixWorldDttFrCon(s32 arg0, PppEntry *arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + arg1->offsets[1];
    func_002675a8(temp_s0 + 0xE0, ((M2C_UNK *)&D_003701D0));
    func_002675a8(temp_s0 + 0xF0, (M2C_UNK *)&D_003701F0);
}
