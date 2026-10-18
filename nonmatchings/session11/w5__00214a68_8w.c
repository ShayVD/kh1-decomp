/* 00214a68: LCS 8 words (12 pos, right size), hand, no context (s9 draft 16). New: inner counter through a pointer into the middle of the previous word, `s32 *cnt = &D_00642C74[1];` declared in the if-block (a different symbol expression than the outer D_00642C78[k] stores, so gcse does not share the la; outer k<<2 stays unreduced and the outer la/1/n hoist exactly). Left: (1) loop.c hoists cnt's lui out of the outer loop (lui t5 at entry) and leaves addiu t0,t5 in the inner preheader; orig has lui t0 in the inner preheader and addiu+addu in the inner body; (2) reorg fills the i>=48 exit from its target (beqzl ...; addiu t1) where the orig uses beqz with the fall-through p++ in the slot. A real inner loop (for/while/do) is worse (24-31). */
#include "common.h"
typedef struct { u8 x0[0x44]; u8 x44[48]; } Ch74;
typedef struct { union { Ch74 c[1]; struct { u8 pad[0x48e]; u8 ids[8]; } h; } u; } P48E;
extern P48E *D_00304BE8;
extern u32 D_003E3D68;
extern s32 D_00642C78[];
extern s32 D_00642C74[];
void func_00214a68(void) {
    u32 k;
    s32 i;
    u8 *p;
    for (k = 0; k < D_003E3D68; k++) {
        Ch74 *c = &D_00304BE8->u.c[D_00304BE8->u.h.ids[k]];
        D_00642C78[k] = 0;
        i = 0;
        if (c->x44[0]) {
            s32 *cnt = &D_00642C74[1];
            D_00642C78[k] = 1;
            p = c->x44;
        loop:
            i++;
            if (i >= 48) goto next;
            p++;
            if (*p == 0) goto next;
            cnt[k]++;
            goto loop;
        }
    next:;
    }
}
