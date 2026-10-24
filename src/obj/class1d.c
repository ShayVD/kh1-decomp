/* Object class 0x1D, default flags (docs/modules.md "Session 52"): the
 * handlers func_00158648 registers in the class table D_00350D88
 * (func_0014f830(0x1D, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1d.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"

/* func_00158050 (from auto/text_00150000_3.c). */
void func_00158050(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0xCC) = 0.19634955f;
}

/* func_00158068 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0xC]; void *cb; } Task;
typedef union { u8 b; u32 w; } U2E3190;
extern U2E3190 D_002E3190;
void func_0013dc10(void *, s32);
Task *func_00130578(void *, s32, f32);
typedef struct { u8 pad[0xC]; f32 fC; } F158068;
void func_00158068(void *a, s32 b, F158068 *c) {
    if (D_002E3190.b == 1) {
        f32 f;
        func_0013dc10(a, 13);
        f = 0.0f;
        func_00130578(a, 0x40000000, 0.0f);
        c->fC = f;
    } else {
        f32 f = c->fC;
        PlatVu0Normalize(c, c);
        c->fC = f;
    }
}

/* func_001580e8 (from auto/text_00150000_2.c). */
void func_001580e8(s32 *arg0) {
    *arg0 &= ~0x20;
}

/* func_00158648 (from auto/text_00150000_7.c). */
void func_0014f828();
void func_00157f70();
void func_00158100();
void func_001581d8();
void func_001584c0();
f32 func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
void func_00158648(void) {
    func_0014f830(0x1D, 0x1E, &func_00157f70, &func_00158050, &func_001581d8, &func_001584c0, &func_0014f828, &func_00158068, &func_00158100);
}

