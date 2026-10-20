/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

extern f32 D_00641200;
extern f32 D_00641208;
extern f32 D_0064120C;
extern f32 D_00641218;
extern s32 D_003F34B8;
extern s32 D_006411FC;
extern s32 D_00641204;

void func_002070c0(void) {
    s32 *var_v0;
    s32 var_a0;

    var_a0 = 9;
    var_v0 = D_003F34B8 + 0x40;
    do {
        var_a0 -= 1;
        *var_v0 = 0;
        var_v0 += 1;
    } while (var_a0 >= 0);
}

void func_0020bda8(s32 arg0) {
    D_006411FC = 0;
    D_00641200 = (f32) arg0;
    D_00641204 = 0;
    D_00641208 = D_00641218;
    D_0064120C = 128.0f;
}
