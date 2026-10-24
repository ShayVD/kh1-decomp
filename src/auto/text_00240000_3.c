/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0066.h"
M2C_UNK func_00123a88(s32, M2C_UNK *);
M2C_UNK func_00124218(s32);
M2C_UNK func_0025dd48(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK (*D_0066AA80)();
#include "data/pieces/D_004919B0.h"
extern M2C_UNK D_0066AA90; /* src/data/bss_0066.c: V4f D_0066AA90 */
extern s32 (*D_0066AA80)();
extern s32 *D_0066AA84;
extern s32 D_0066AAA0;
f32 func_0024ef88();
void func_00131d68(s32, s32);

void func_0024daa0(void) {
    func_0025dd48((M2C_UNK *)&D_004919B0, 0x4807, 0, 0, 0, 0);
}

void func_0024f008(void) {
    func_00124218(*D_0066AA84);
    func_00123a88(*D_0066AA84, &D_0066AA90);
    func_0024ef88();
    if (D_0066AA80 != NULL) {
        D_0066AA80();
    }
}

s32 func_0024f1d0(s32 arg0) {
    s32 (*var_v0)();

    func_00131d68(arg0, D_0066AAA0);
    var_v0 = D_0066AA80;
    if (var_v0 != NULL) {
        var_v0 = var_v0();
    }
    return (s32) var_v0;
}
#include "data/data_0046.h"
