/* func_00214a68: 22 words off in hand (s6 draft 28): u8 inner counter i fixes the outer block (sll a2,k,2 + addu with the hoisted base, lbu 68(v1)). Left: inner loop. orig hoists only lui %hi(D_00642C78) out of the inner loop and recomputes addiu %lo + addu a2 (k*4) per iteration, and walks c->x44 with a0 = c+68, a0++ and slti i,48 (s32 compare); ours (u8 i) hoists the whole &D_00642C78[k], uses andi/sltiu and indexes 64(v1). s32 i gives the right inner compare but the whole address hoisted too. goto loops kill the inner giv. nogcse/nostrict no better. */
#include "common.h"
typedef struct { u8 x0[0x44]; u8 x44[48]; } Ch74;
typedef struct { union { Ch74 c[1]; struct { u8 pad[0x48e]; u8 ids[8]; } h; } u; } P48E;
extern P48E *D_00304BE8;
extern u32 D_003E3D68;
extern s32 D_00642C78[];
void func_00214a68(void) {
    u32 k;
    u8 i;
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
