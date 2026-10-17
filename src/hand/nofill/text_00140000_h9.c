/* Hand-matched functions near 0x155000 built without delay-slot filling (worker 9). */
#include "common.h"

typedef struct {
    union {
        s32 w;
        struct { s8 b0; u8 b1; u8 b2; u8 b3; } b;
    } h;
    u8 pad4[0x24 - 4];
    char name[0x20];
    s32 x44;
} W9Blk;
extern W9Blk D_00550400[];
extern u8 D_00FE0000[];

u8 *func_001559f0(s32 i, s32 n) {
    W9Blk *p = &D_00550400[i];
    s32 j;
    for (j = 0; j < n; j++) {
        p[j].h.b.b0 = -1;
        p[j].h.b.b2 = 0;
    }
    return D_00FE0000 + (i << 18);
}
