/* The depth-sorted draw list, its set up (docs/modules.md "Session 45"):
 * func_00237660(l, tbl, bits) gives the list l its 1 << bits buckets at tbl
 * and func_00237600 empties them.  The rest is in drawlist.nostrict.c and
 * drawlist.nostrict_nofill.c. */
#include "common.h"
#include "gfx/drawlist.h"

void *memset(void *, s32, u32);

void func_00237600(DrawList *l) {
    s32 n = 1 << l->bits;
    DrawBucket *b = l->tbl;
    s32 i;
    for (i = 0; i < n; i++) {
        memset(b, 0, 8);
        b++;
    }
}

void func_00237660(DrawList *l, DrawBucket *tbl, s32 bits) {
    l->tbl = tbl;
    l->bits = bits;
    func_00237600(l);
}
