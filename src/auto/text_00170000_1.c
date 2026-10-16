/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001759e8();
M2C_UNK func_00175e38(M2C_UNK *);
M2C_UNK func_0017b120(void *);
extern M2C_UNK D_00360F30;
extern s32 D_002E27A8;
extern s32 D_0036244C;
extern s32 D_00362450;
extern s32 D_00362454;
extern s32 D_00575894;
extern void *D_00362438;

void func_001761b0(void) {
    func_00175e38(&D_00360F30);
    func_001759e8();
}

void func_0017d208(void) {
    if (!(M2C_FIELD(D_00362438, s32 *, 0x18) & 0x10)) {
        func_0017b120(D_00362438);
    }
}

void func_0017ebd0(void) {
    D_00575894 = 0;
    D_002E27A8 = 0;
    D_0036244C = 0;
    D_00362450 = 0;
    D_00362454 = 0;
}
