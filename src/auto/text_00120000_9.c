/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00122768(M2C_UNK *);
M2C_UNK func_00122bd8();
M2C_UNK func_0024f318(s32, M2C_UNK *, s32, M2C_UNK, M2C_UNK *);
M2C_UNK func_002675a8(s32, s32);
#include "data/pieces/D_002C5C80.h"
extern M2C_UNK D_004E4A00; /* src/data/bss_004E.c: FileEnt D_004E4A00[0xe00] */
extern M2C_UNK func_00120170;
extern s32 D_002C5C30;
s32 func_001200f8();
s32 func_00123488();

void func_00120190(void) {
    func_0024f318(func_001200f8(), &D_004E4A00, D_002C5C30, 0x10, &func_00120170);
}

void func_00122c08(void) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = &D_002C5C80;
    var_s1 = 0x1E;
    do {
        if ((M2C_FIELD(var_s0, s32 *, 0) != 0) && (M2C_FIELD(var_s0, s32 *, 4) & 8)) {
            func_00122768(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x40;
    } while (var_s1 >= 0);
    func_00122bd8();
}

void func_00123b10(s32 arg0, s32 arg1) {
    func_002675a8(func_00123488() + 0x40, arg1);
}
#include "data/data_002C.h"
