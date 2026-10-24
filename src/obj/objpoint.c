/* The point list D_00551600, default flags (docs/modules.md "Session 52"):
 * func_00156628 finds the n-th entry, func_00156260, func_001566d8 and the
 * small accessors.  The rest is in objpoint.nostrict.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "data/bss_0054.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8.h"

/* func_00156260 (from auto/text_00150000_3.c). */
M2C_UNK func_002673b8(s32, void *);
M2C_UNK func_002675a8(s32, M2C_UNK *);
void func_00156260(void *arg0, void *arg1) {
    func_002675a8(arg0 + 0x3C0, ((M2C_UNK *)&D_002C58B0));
    func_002673b8(arg0 + 0x3F0, arg1);
    M2C_FIELD(arg0, f32 *, 0x3FC) = (f32) (M2C_FIELD(arg1, f32 *, 0xC) * 0.22314355f);
    M2C_FIELD(arg0, s32 *, 0x88) = (s32) (M2C_FIELD(arg0, s32 *, 0x88) | 0x40);
}

/* func_00156628 (from hand/text_00140000_h9.c). */
extern u8 *D_00551600;
u8 *func_00156628(s32 n) {
    u8 *p = D_00551600;
    s32 i;
    for (i = 1; *p; i++) {
        if (i == n) return p;
        p = p + p[1] * 96 + 48;
    }
    return 0;
}

/* func_00156678 (from auto/text_00150000.c). */
#define func_00156628 ((s64 *(*)()) func_00156628)
void func_00156678(void) {
    s64 *temp_v0;

    temp_v0 = func_00156628();
    *temp_v0 |= 0x10000;
}
#undef func_00156628

/* func_001566a8 (from auto/text_00150000_23.c). */
#define func_00156628 ((s64 *(*)()) func_00156628)
void func_001566a8(void) {
  s64 *temp_v0;
  int new_var;
  new_var = 0xFFFEFFFF;
  ;
  *func_00156628() &= new_var;
}
#undef func_00156628

/* func_001566d8 (from hand/text_00140000_h9.c). */
f32 func_00267390(f32 *a, f32 *b);
s32 func_001566d8(f32 (*pl)[4], f32 *pt) {
    s32 i;
    f32 *w = &pl[0][3];
    f32 *p = pl[0];
    for (i = 0; i < 6; i++) {
        if (func_00267390(p, pt) - *w < 0.0f) return 0;
        p += 4;
        w += 4;
    }
    return 1;
}

/* func_00156c18 (from auto/text_00150000.c). */
extern s32 D_00551600_00156c18 __asm__("D_00551600");
#define D_00551600 D_00551600_00156c18
void func_00156c18(s32 arg0) {
    D_00551600 = arg0;
}
#undef D_00551600

