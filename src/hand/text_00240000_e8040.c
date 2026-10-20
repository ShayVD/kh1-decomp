#include "common.h"

/* needs make: uses rodata (jump table). func_00246320 only matches with func_00246020 defined above it. */
typedef struct { u32 state; f32 t; s32 x8; s32 xc; } E8040;
extern E8040 D_00668040[]; /* src/data/bss_0066.c: u8 D_00668040[0x20] */
s32 func_001375d8(s32);
void func_00246020(void) {
    D_00668040[1].state = 0;
    D_00668040[0].state = 0;
}

void func_002461f8(E8040 *, s32, f32);
s32 func_00246320(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        E8040 *e = &D_00668040[i];
        s32 r = 0;
        switch (e->state) {
        case 0:
            continue;
        case 1:
            r = 1;
            e->state++;
            break;
        case 2: case 4:
            e->state++;
            break;
        case 3:
            break;
        case 5:
            e->t -= 0.199999988079071044921875f;
            if (e->t < 0.0f) {
                e->t = 0.0f;
                e->state++;
            }
            break;
        case 6:
            e->state = 0;
            continue;
        }
        if (func_001375d8(e->xc)) {
            func_00246020();
            return 0;
        }
        func_002461f8(e, r, e->t);
    }
    return 0;
}
