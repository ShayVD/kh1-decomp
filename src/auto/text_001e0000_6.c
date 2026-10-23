/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"
M2C_UNK func_001efd20(s32, s32);
#include "data/pieces/D_003E8E28.h"
#include "data/pieces/D_003DC390.h"
extern M2C_UNK D_003E4658;
#include "data/pieces/D_003DACA0.h"
#include "data/pieces/D_003DAD3C.h"
extern s32 D_003E8E2C;
s32 func_001efbb8();
void func_001efaf0(void);
void func_001efb58(s32);
void func_001efb78(s32);
void func_001efb98(s32);

/* func_001e13e8, func_001e25e8, func_001e2628 are in src/screen/screen.c. */

/* func_001e3c08, func_001e44e0 are in src/shop/shop.c. */

/* func_001ec380 is in src/save/flags.c. */

void func_001efaa8(void) {
    (*(M2C_UNK **)&D_003E8E28) = &D_003E4658;
    D_003E8E2C = 0x310;
    func_001efb58(0x14);
    func_001efb78(0);
    func_001efb98(0);
    func_001efaf0();
}

void func_001efbe0(s32 arg0, s32 arg1) {
    func_001efd20(func_001efbb8(), arg1);
}
#include "data/data_003D.h"
#include "data/data_003E.h"
