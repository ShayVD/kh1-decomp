/* The party members' records in the save data D_00304BE8: abilities, items
 * and equipment by member (func_0013c968 asks whether a member has ability
 * c, func_0013c318, func_0013c598 ...), member stats, and func_0013cb98
 * builds the records from the new-game data D_00351530. Flag mode: nofill
 * (the other modes are in the sibling files). Read from the code, not proved
 * by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"

/* func_0013c108 (from hand/nofill/text_00130000_s6_06.c). */
typedef W606Mem_304be8 W606Mem;
void func_0013c108(s32 i, s32 b) {
    s32 j;
    W606Mem *m = &D_00304BE8->m[i];
    m->bits |= 1 << b;
    if (i == 0) {
        for (j = 0; j < 3; j++) {
            if (D_00304BE8->x844[j] == -1) {
                D_00304BE8->x844[j] = b;
                break;
            }
        }
    }
}

/* func_0013c2f0 (from hand/nofill/text_00130000_s6_06.c). */
s32 func_0013c2f0(s32 b) {
    return D_00304BE8->x878 & ((u64)1 << b);
}

