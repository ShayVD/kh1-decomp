/* 00214a68: 16w LCS (s7 draft 22), hand. New: the inner loop is a goto loop (no loop notes: loop.c leaves it alone, as the orig's in-loop addiu+addu shows) with an explicit u8 *p, s32 i (slti), and the inner increment goes through a pointer 'cnt' set before the outer loop while the outer stores use D_00642C78[k] directly (outer address no longer strength-reduced; hoisted by loop.c). Left: orig computes the inner &D afresh (lui t0 in the inner preheader = gcse PRE insertion of (high D), then addiu+addu in the loop): at gcse time (high D) must not be available/anticipated from the outer block; ours reuses cnt (t2) and also puts cnt's la before the entry test; beqzl vs beqz at the i>=48 exit. */
#include "common.h"
typedef struct { u8 x0[0x44]; u8 x44[48]; } Ch74;
typedef struct { union { Ch74 c[1]; struct { u8 pad[0x48e]; u8 ids[8]; } h; } u; } P48E;
extern P48E *D_00304BE8;
extern u32 D_003E3D68;
extern s32 D_00642C78[];
void func_00214a68(void) {
    u32 k;
    s32 i;
    u8 *p;
    s32 *cnt = D_00642C78;
    for (k = 0; k < D_003E3D68; k++) {
        Ch74 *c = &D_00304BE8->u.c[D_00304BE8->u.h.ids[k]];
        D_00642C78[k] = 0;
        i = 0;
        if (c->x44[0]) {
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
