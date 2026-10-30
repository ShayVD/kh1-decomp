/* wm.x func_00f2d630: matched by hand. */
#include "ovl.h"

typedef struct { u16 h0; u16 kind; u16 h4; u16 flags; } K2d630;
typedef struct { s32 x0; s32 id; u8 pad8[0x14]; K2d630 *k; u8 pad20[0x30]; u8 sub[0x10]; } E2d630;
E2d630 *func_00f3b460(s32);
s32 func_00f3b480(void);
f32 func_001beef8(void *, void *);

E2d630 *func_00f2d630(void *arg0, s32 arg1) {
    s32 i;
    s32 found = 0;
    E2d630 *best = NULL;
    f32 bd;
    f32 d;
    for (i = 0; i < func_00f3b480(); i++) {
        E2d630 *e = func_00f3b460(i);
        K2d630 *k;
        if (e == NULL) continue;
        k = e->k;
        if (k == NULL) continue;
        if (e->id == arg1) continue;
        if (k->kind == 0 || (k->kind == 1 && (u16)(k->flags & 1))) {
            d = func_001beef8(e->sub, arg0);
            if (!found || d < bd) {
                bd = d;
                best = e;
                found = 1;
            }
        }
    }
    return best;
}
