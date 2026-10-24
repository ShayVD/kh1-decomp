/* Object class 0x1E, default flags (docs/modules.md "Session 52"): the
 * handlers func_001598e0 registers in the class table D_00350D88
 * (func_0014f830(0x1E, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1e.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"

/* func_00159148 (from auto/text_00150000.c). */
f32 func_0014cce0(s32, f32);
M2C_UNK func_0014f658(s32, M2C_UNK);
void func_00159148(s32 arg0, f32 f) {
    func_0014cce0(arg0, f);
    func_0014f658(arg0, 0x1F);
}

/* func_001593f8 (from auto/text_00150000_3.c). */
extern u8 D_002E3190;
s32 func_00159178(s32, s32, s32, s32);
void func_001593f8(s32 arg0, s32 arg1, s32 arg2) {
    if (D_002E3190 == 1) {
        func_00159178(arg0, 0x3C, (s32) &D_002E31B0, arg2);
    }
}

/* func_001598c8 (from auto/text_00150000_2.c). */
s32 func_001598c8(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 0x1E;
    if (arg1 != 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

/* func_001598e0 (from auto/text_00150000_8.c). */
void func_0014cee8();
void func_0014f828();
void func_00159350();
void func_00159440();
void func_001595a8();
void func_00159740();
void func_00159808();
void func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
void func_001598e0(void) {
    func_0014f830(0x1E, 0x18, &func_00159350, 0, &func_00159440, &func_001595a8, &func_0014f828, &func_001593f8, &func_00159740);
    func_0014f830(0x1F, 0x19, NULL, 0, &func_00159808, &func_0014cee8, &func_001598c8, &func_001593f8, NULL);
}

