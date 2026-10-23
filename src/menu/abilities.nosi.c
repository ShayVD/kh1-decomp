/* The abilities page (src/menu/abilities.c; docs/modules.md "Session 40"; was
 * src/hand/nosi/text_00210000_s11_w44.c): func_00214a68 counts the abilities of
 * each member (Sub_304be8 +0x40, up to 48) into D_00642C78[slot].  It needs
 * -fno-sched-interblock (nosi).
 *
 * func_00214a68: FLAGGED dead set + dead FP test. (1) exit arm `if (i >= 48) { p = 0; break; }` (dead p = 0) turns beqzl into beqz (w41). (2) dead FP test `if ((f32)(i * i) < 0.0f) c = 0;` inside the inner loop (c is dead there): i gets inner-loop-weighted refs so global-alloc takes i before k<<2, and since the test's insns lengthen the ids giv and the inner lui equally, the giv still outranks the lui. flow2 deletes the test. */
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D68.h"
extern s32 D_00642C78[];
extern s32 D_00642C74[];
void func_00214a68(void) {
    u32 k;
    s32 i;
    u8 *p;
    s32 *q;
    for (k = 0; k < D_003E3D68; k++) {
        Sub_304be8 *c = &D_00304BE8->m[D_00304BE8->x48e[k]].sub;
        D_00642C78[k] = 0;
        i = 0;
        if (c->name[0]) {
            D_00642C78[k] = 1;
            p = c->name;
            do {
                i++;
                if ((f32)(i * i) < 0.0f) c = 0; /* FLAGGED dead FP test (flow2 deletes it) */
                if (i >= 48) { p = 0; break; }
                p++;
                q = &D_00642C74[1];
                if (*p == 0) break;
                q += k; (*q)++;
            } while (1);
        }
    }
}
#include "data/bss_0064_mixed.h"
