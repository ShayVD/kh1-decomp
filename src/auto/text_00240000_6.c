/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00248628(s32 *, M2C_UNK, s32 *);
M2C_UNK func_0024aac8(M2C_UNK *);
M2C_UNK func_0024afc0(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK memset(s32 *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_00467410;
extern M2C_UNK D_00468220;
extern M2C_UNK D_00468E10;
extern M2C_UNK D_00469C20;
extern M2C_UNK D_00469C48;
extern M2C_UNK D_00469C70;
extern M2C_UNK D_00669760; /* src/data/bss_0066.c: UiEnt D_00669760[3] */
extern M2C_UNK func_00248e30;
extern s32 D_00669700;
s32 func_0011ef38(M2C_UNK *);

void func_00248ea0(void) {
    memset(&D_00669700, 0, 0x60);
    func_00248628((s8 *)&D_00669700 + 0x14, 5, (s8 *)&D_00669700 + 0x24);
    D_00669700 = 0;
    func_0024aac8(&D_00467410);
    func_0024aac8(&D_00468220);
    func_0024aac8(&D_00468E10);
    func_0024afc0(&D_00469C20, &D_00669760, &D_00467410);
    func_0024afc0(&D_00469C48, (s8 *)&D_00669760 + 0x20, &D_00468220);
    func_0024afc0(&D_00469C70, (s8 *)&D_00669760 + 0x40, &D_00468E10);
    if (func_0011ef38(&func_00248e30) == 0) {
        func_0011ef10(0x29811, &func_00248e30);
    }
}
#include "data/data_0046.h"
