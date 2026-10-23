/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"
#include "data/bss_0063.h"

#include "vm/script_vm.h"
M2C_UNK func_002672f8(void *, void *, void *);
M2C_UNK func_00267620(void *);
M2C_UNK func_00267768(void *, void *, f32);
M2C_UNK func_00267810(void *, void *, f32);
#include "data/pieces/D_003DABD4.h"
extern s32 D_003F7A68;

/* func_001e10c8, func_001e14e0 are in src/screen/screen.c. */


/* func_001e4268 is in src/shop/shop.c. */

/* func_001e4918, func_001e4d20, func_001e6410, func_001e6de0, func_001e7278, func_001e7d58 are in src/list/list.c. */






/* func_001e81c8, func_001e84f0, func_001e86e8 are in src/event/sound.c. */



void func_001e9f18(void *arg0, void *arg1, void *arg2, f32 fparg0) {
    s32 sp[16];
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;

    M2C_FIELD(arg0, f32 *, 0xC) = 1.0f;
    M2C_FIELD(arg0, f32 *, 8) = fparg0;
    M2C_FIELD(arg0, f32 *, 0) = 0.0f;
    M2C_FIELD(arg0, f32 *, 4) = 0.0f;
    func_00267620(sp);
    func_00267768(sp, sp, M2C_FIELD(arg2, f32 *, 0));
    func_00267810(sp, sp, M2C_FIELD(arg2, f32 *, 4));
    func_002672f8(arg0, sp, arg0);
    temp_f1 = -M2C_FIELD(arg0, f32 *, 0);
    temp_f2 = -M2C_FIELD(arg0, f32 *, 4);
    temp_f3 = -M2C_FIELD(arg0, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 0) = temp_f1;
    M2C_FIELD(arg0, f32 *, 4) = temp_f2;
    M2C_FIELD(arg0, f32 *, 8) = temp_f3;
    M2C_FIELD(arg0, f32 *, 0) = (f32) (temp_f1 + M2C_FIELD(arg1, f32 *, 0));
    M2C_FIELD(arg0, f32 *, 4) = (f32) (temp_f2 + M2C_FIELD(arg1, f32 *, 4));
    M2C_FIELD(arg0, f32 *, 8) = (f32) (temp_f3 + M2C_FIELD(arg1, f32 *, 8));
}
#include "data/data_003D.h"
#include "data/data_003E.h"
#include "data/pieces/D_003F7A68.h"
