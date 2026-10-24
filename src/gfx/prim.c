/* Primitives sent at once (docs/modules.md "Session 45"), 0x00238440-0x002389f0
 * with prim.nostrict.c and prim.nostrict_nofill.c: draw-list nodes drawn
 * without the list.  func_00238440(items, count, m) sends count lines
 * (80-byte kind 1 nodes, drawlist.nostrict_nofill.c's func_00237790) one by
 * one through the buffer D_00648070. */
#include "common.h"
#include "gfx/gspkt.h"

typedef int u128 __attribute__((mode(TI)));
u128 *func_00237790(u8 *, u128 *, s32);

u128 D_00648070[0x6] ALIGNED(16);

void func_00238440(u8 *items, s32 count, s32 arg2) {
    s32 i;
    for (i = 0; i < count; i++) {
        u128 *end = func_00237790(items, D_00648070, arg2);
        items += 80;
        if (end != D_00648070) {
            *(s32 *)D_00648070 |= 0x70000000;
            func_00237018(D_00648070, end - D_00648070, 1);
        }
    }
}
