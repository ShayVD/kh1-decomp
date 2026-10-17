/* func_00214a68: 28 words off in src/hand (best of plain/nogcse/n32 modes; n32 gives 28, goto-loop variants 32-39). Original does not strength-reduce &D_00642C78[k] in the outer loop (recomputes k<<2 each iteration) and the inner loop is unrotated with only the lui of D_00642C78 hoisted (addiu+addu recomputed inside). */
#include "common.h"
typedef struct { u8 x0[0x44]; u8 x44[48]; } Ch74;
typedef struct { union { Ch74 c[1]; struct { u8 pad[0x48e]; u8 ids[8]; } h; } u; } P48E;
extern P48E *D_00304BE8;
extern u32 D_003E3D68;
extern s32 D_00642C78[];
void func_00214a68(void) {
    u32 k;
    s32 i;
    for (k = 0; k < D_003E3D68; k++) {
        Ch74 *c = &D_00304BE8->u.c[D_00304BE8->u.h.ids[k]];
        D_00642C78[k] = 0;
        i = 0;
        if (c->x44[i]) {
            D_00642C78[k] = 1;
            for (;;) {
                i++;
                if (i >= 48 || !c->x44[i]) goto next;
                D_00642C78[k]++;
            }
        }
    next:;
    }
}
