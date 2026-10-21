/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0010ef70(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_0011e9a8(M2C_UNK *, s32);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
extern M2C_UNK D_003DD2F0;
extern M2C_UNK D_00631570; /* src/data/bss_0063.c: Win D_00631570 */
extern M2C_UNK func_001e8628;
extern M2C_UNK func_001e86e8;
extern M2C_UNK func_001e92b8;
#include "data/pieces/D_003DABD4.h"
s32 func_0011e340(M2C_UNK);

void func_001e8728(void) {
    if (func_0011e340(0) == 0) {
        func_0011e9a8(&func_001e8628, ((s32)D_003DABD4));
        return;
    }
    func_0011ef10(0xC352, &func_001e86e8);
}

void func_001e92e0(void) {
    func_0010ef70(&D_00631570, &D_003DD2F0, &func_001e92b8);
}
#include "data/data_003D.h"
