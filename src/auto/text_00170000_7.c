/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
extern M2C_UNK D_0035BE50;
extern M2C_UNK D_00362660;
#include "data/pieces/D_003626F8.h"
extern M2C_UNK func_0014f828;
extern M2C_UNK func_00172028;
extern M2C_UNK func_001732b0;
extern M2C_UNK func_00173360;
extern M2C_UNK func_00173478;
extern f32 D_00362674;
f32 func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK, s32);
void func_0017f178(void);

void func_00172d90(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0x17;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035BE50;
    func_0014f830(0x32, 2, &func_00172028, &func_001732b0, &func_00173360, &func_00173478, &func_0014f828, 0, 0);
}

void func_0017f110(void) {
    M2C_FIELD(&D_00362660, f32 *, 0) = (f32) M2C_FIELD((M2C_UNK *)&D_003626F8, f32 *, 0);
    M2C_FIELD(&D_00362660, f32 *, 0xC) = (f32) M2C_FIELD((M2C_UNK *)&D_003626F8, f32 *, 4);
    D_00362674 = M2C_FIELD((M2C_UNK *)&D_003626F8, f32 *, 8);
    func_0017f178();
}
#include "data/data_0036.h"
#include "data/data_0035.h"
