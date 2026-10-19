/* 00135a68: 33w LCS (same count as s6 w6_05 34w draft) but RIGHT SIZE 284 (draft 272), hand/nostrict, no context. Finding: the original's four address registers in loop 2 (addu a2,a1,a3 / addu v0,a3,a1 / move v1,a2 / move a1,v1) are four separate (plus i16 v) pseudos that reload_cse turns into moves. They appear when each v[i][k] store is in its own block at cse1/gcse time: here three dead FP tests `if (h < r) k = 0; else k = 1;` between the stores (k = loop-1 counter, dead in loop 2; the else keeps an explicit jump so cse1 cannot skip-block across): gcse makes the i<<4 copies, cse2 substitutes them, the adds stay separate (sched1 interblock hoists all four into the first block), reload_cse makes the copy chain. Left: the FP tests survive to flow2, so the stores stay in separate sched1 blocks (serialised, one FP register); needed: a block split that exists at cse1/gcse but is gone before life1/sched1 (integer two-set dead arms vanish too early, one-set FP tests are skipped by cse1). v[0] also needs operand order v+i16 (original addu v0,a3,a1). */
#include "common.h"
void func_00135a68(f32 (*v)[4], f32 r, f32 h) {
    s32 i, k;
    if (0.0f <= h) {
        h = -h;
        for (k = 0; k < 8; k++) {
            v[k][0] = r * (((k & 1) << 1) - 1);
            v[k][1] = h * ((k & 2) >> 1);
            v[k][2] = r * (((k & 4) >> 1) - 1);
            v[k][3] = 1.0f;
        }
    } else {
        for (i = 0; i < 8; i++) {
            v[i][0] = r * (((i & 1) << 1) - 1);
            if (h < r) k = 0; else k = 1; /* dead FP test (flagged) */
            v[i][1] = h * ((i & 2) - 1);
            if (h < r) k = 0; else k = 1; /* dead FP test (flagged) */
            v[i][2] = r * (((i & 4) >> 1) - 1);
            if (h < r) k = 0; else k = 1; /* dead FP test (flagged) */
            v[i][3] = 1.0f;
        }
    }
}
