/* 28 words off (src/hand default mode; nogcse gives 35): original does not strength-reduce D_00642C78[k] (recomputes k<<2 each outer iteration) and keeps the inner-loop address add (lui hoisted, addiu+addu inside); ours hoists a reduced pointer. Inner for(;;)+break shape is right. */
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
