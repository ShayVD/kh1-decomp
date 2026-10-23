/* The equipment page's item row (src/menu/equip.c; docs/modules.md "Session 40"):
 * func_002114f0 draws one row of a list (the frame D_003F2C40[a1], the item's
 * name and its icon).  It matches only with -mabi=n32 on the gcc -S step:
 * the original never folds a symbol into a register add, it keeps lui/addiu
 * base + addu (was src/hand/n32/text_00210000_s6_21.c). */
#include "common.h"
#include "data/pieces/D_003F2C40.h"

s32 func_001ee698(s32);
s32 func_001efbb8(s32);
void func_00201550(void *, s32, s32, s32, s32, s32, s32, void *, s32, s32);
void func_002083a8(void *, s32, s32, s32, s32, u32);

void func_002114f0(void *a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    S2C40_3F2C40 *e = &D_003F2C40.s2C40[a1];
    u32 c = e->e;
    s32 s;
    if (t1 != 0) s = func_001ee698(t1);
    else s = func_001efbb8(167);
    func_00201550(a0, 2, 0, a2, a3, t0, a2 + 24, e, s, 15);
    func_002083a8(a0, a2 + 6, a3 + 4, 18, t1, c >> 24);
}
