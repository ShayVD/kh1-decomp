/* Object class 0x00, default flags (docs/modules.md "Session 52"): the
 * handlers func_0015a418 registers in the class table D_00350D88
 * (func_0014f830(0x00, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class00.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"

/* func_0015a348 (from hand/text_00150000_s7_w2.c). */
typedef struct {
    u32 w0;
    u8 pad4[0xc];
    f32 pos[4];
    u8 pad20[0x70 - 0x20];
    s32 x70;
    u8 pad74[0x164 - 0x74];
    s32 x164;
    u8 pad168[0x320 - 0x168];
    f32 x320[4];
} A348;
void func_0015ac58(A348 *);
/* session 7 w2: func_0015a348 (strict). func_0015ac58 takes the object in a0; passing it fixes the beqzl/alignment layout. */
s32 func_0015a348(A348 *a, s32 f) {
    if (f != 0 || (a->w0 & 0x1000)) {
        if (a->w0 & 0x100) { PlatVu0CopyVector(a->pos, a->x320); return a->x70; }
        if (a->x164 == 220) func_0015ac58(a);
        return 2;
    }
    return a->x70;
}

/* func_0015a3d8 (from auto/text_00150000.c). */
M2C_UNK func_0014cb90(s32);
s32 func_0013db30();
void func_0015a3d8(s32 arg0) {
    if (func_0013db30(arg0) != 0) {
        func_0014cb90(arg0);
    }
}

/* func_0015a418 (from auto/text_00150000_9.c). */
void func_00126e80();
void func_0014f798();
void func_0015a258();
void func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
void func_0015a418(void) {
    func_0014f830(0, 0xFC, 0, 0, &func_0015a258, &func_0014f798, &func_0015a348, &func_00126e80, &func_0015a3d8);
}

