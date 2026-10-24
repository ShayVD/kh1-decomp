/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004D.h"

M2C_UNK func_00108a60(s32, M2C_UNK, void *, void *, void *);
#include "data/pieces/D_002A6C60.h"
#include "data/pieces/D_002AA060.h"
extern M2C_UNK D_002AD460;
#include "data/pieces/D_002B1C60.h"
extern s32 D_004D936C;
extern s32 D_004D9370;

void func_001148c8(void) {
    s32 temp_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    void *temp_a2;

    D_004D936C = 0;
    D_004D9370 = 0;
    var_s0 = 0;
    var_s1 = 0;
    var_s2 = 0;
    do {
        func_00108a60(var_s1, 1, var_s2 + (s8 *)&D_002A6C60, var_s0 + (s8 *)&D_002AD460, var_s0 + ((s8 *)&D_002AD460 + 0x2400));
        temp_a0 = var_s1;
        temp_a2 = var_s2 + (s8 *)&D_002AA060;
        func_00108a60(temp_a0, 5, temp_a2, var_s0 + (s8 *)&D_002B1C60, var_s0 + ((s8 *)&D_002B1C60 + 0x2400));
        var_s2 += 0xD0;
        var_s1 += 1;
        var_s0 += 0x90;
    } while (var_s1 < 0x40);
}
#include "data/data_002A.h"
