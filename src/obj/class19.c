/* Object class 0x19, default flags (docs/modules.md "Session 52"): the
 * handlers func_0015ea40 registers in the class table D_00350D88
 * (func_0014f830(0x19, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class19.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002E26A0.h"
#include "actor.h"
#include "data/pieces/D_002C58A0.h"
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"

/* func_0015e7f8 (from auto/text_00150000_2.c). */
void func_0015e7f8(s32 arg0) {
    if ((*(s32 *)&D_002E26A0) == arg0) {
        D_00551D74 = 30.0f;
    }
}

/* func_0015e820 (from auto/text_00150000_16.c). */
M2C_UNK func_00267e40(s32, s32);
void func_0015e820(s32 arg0) {
    func_00267e40(arg0 + 0x3C0, arg0 + 0x30);
}

/* func_0015e840 (from hand/text_00150000_h10.c). */
typedef union { u8 b; u32 w; } U2E3190;
extern U2E3190 D_002E3190;
void func_0014f658(void *, s32);
f32 func_00121b08(void *, f32);
void func_0015e840(void *a) {
    if (D_002E3190.w & 0x18000000) D_00551D74 = 30.0f;
    D_00551D74 = func_00121b08(a, D_00551D74);
    if (D_00551D74 == 0.0f) func_0014f658(a, 24);
}

/* func_0015e9c8 (from hand/text_00150000_h10.c). */
extern f32 D_002BBDFC;
void func_00267560(void *, void *, f32);
typedef struct { u8 pad[0x30]; f32 pos[4]; u8 pad40[0x38C]; f32 f3CC; } ObjE9;
void func_0015e9c8(ObjE9 *a, void *b) {
    f32 f = a->f3CC;
    if (f < 18.0f) {
        f = a->f3CC = (f + D_002BBDFC * 0.5f < 18.0f) ? f + D_002BBDFC * 0.5f : 18.0f;
    }
    func_00267560(b, a->pos, f * D_002BBDFC);
}

/* func_0015ea38 (from auto/text_00150000_16.c). */
s32 func_0015ea38(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}

/* func_0015ea40 (from auto/text_00150000_4.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, s32);
void func_0015e8d8();
void func_0015ea40(void) {
    func_0014f830(0x19, 0xE, &func_0015e7f8, &func_0015e820, &func_0015e8d8, &func_0015e9c8, &func_0015ea38, &func_0015e840, 0);
}

