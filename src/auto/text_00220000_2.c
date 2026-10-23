/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"
extern s32 D_003F34A4;
extern s32 D_003F720C;
void func_0020a8f0(void);
void func_0020b968(void);

void func_0022bc80(void) {
    D_003F34A4 = 1;
    func_0020a8f0();
    func_0020b968();
    D_003F720C = 0;
}
#include "data/data_003F.h"
