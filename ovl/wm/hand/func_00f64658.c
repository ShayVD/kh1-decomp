/* wm.x func_00f64658: the twin of gb.x func_00f3d560 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { s16 lo; s16 hi; s32 val; } Rng;
typedef struct { u8 pad[4]; s16 n; s16 pad6; s32 cnt; Rng *r; } RngTab;
s32 func_00f64658(s32 x, RngTab *t) {
    s32 i;
    Rng *r;

    x = x % (t->n + 1);
    r = t->r;
    for (i = 0; i < t->cnt; i++, r++) {
        if (x >= r->lo && x <= r->hi) {
            return r->val;
        }
    }
    return 0;
}
