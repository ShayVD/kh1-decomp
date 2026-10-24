/* Object class 0x04, default flags (docs/modules.md "Session 52"): the
 * handlers func_001556a8 registers in the class table D_00350D88
 * (func_0014f830(0x04, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. Read from the code, not proved by a
 * boot. */
#include "m2c.h"
#include "platform/vu.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"

/* func_00155630 (from auto/text_00150000_3.c). */
extern f32 D_002BBDFC;
void func_00155630(void *arg0, void *arg1) {
    s32 temp_s2;

    temp_s2 = arg0 + 0x3C0;
    PlatVu0ScaleVector(arg1, arg0 + 0x20, M2C_FIELD(arg0, f32 *, 0x2C));
    PlatVu0InterVector(temp_s2, arg1, temp_s2, M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0x14));
    M2C_FIELD(arg0, f32 *, 0x3C4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    PlatVu0ScaleVectorXYZ(arg1, temp_s2, D_002BBDFC);
}

/* func_001556a8 (from auto/text_00150000_6.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32);
void func_0014f828();
void func_001556a8(void) {
    func_0014f830(4, 2, 0, 0, 0, &func_00155630, &func_0014f828, 0, 0);
    func_0014f830(7, 1, 0, 0, 0, &func_00155630, &func_0014f828, 0, 0);
}

