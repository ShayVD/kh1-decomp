/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_001f31a8(M2C_UNK *, M2C_UNK);
extern M2C_UNK D_003F3420;
extern s32 D_006411E0;
extern s32 D_006411FC;
extern s32 D_00641210; /* src/data/bss_0064.c: f32 D_00641210 */
extern s32 D_00641214; /* src/data/bss_0064.c: f32 D_00641214 */
extern s32 D_00641218; /* src/data/bss_0064.c: f32 D_00641218 */
s32 func_001ee7a8();

void func_0020b968(void) {
    D_006411FC = 3;
    D_006411E0 = 0;
    D_00641210 = 0;
    D_00641214 = 0;
    D_00641218 = 0;
}

s32 func_0020bb78(void) {
    return D_006411FC != 3;
}

void func_0020d030(void) {
    func_001f31a8(&D_003F3420, 0);
}

s32 func_0020d6c0(void) {
    return 0;
}

s32 func_0020f260(s32 arg0) {
    return (func_001ee7a8() << 8) | arg0;
}
#include "data/data_003F.h"
