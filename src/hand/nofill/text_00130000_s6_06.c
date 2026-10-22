#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
typedef W606Mem_304be8 W606Mem;


typedef struct { u8 pad[0x40]; s32 x40; s32 x44; s32 x48; } W606S6c;
typedef struct { u8 pad[0x6c]; W606S6c *x6c; } W606O26a0;
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E27C8.h"

f32 func_0013bb20(void) {
    return (f32)(((*(W606O26a0 **)&D_002E26A0)->x6c->x48 + (s32)(((*(u32 *)&D_002E27C8) >> 10) & 7)) * 3000);
}

s32 func_0013c2f0(s32 b) {
    return D_00304BE8->x878 & ((u64)1 << b);
}

void func_0013c108(s32 i, s32 b) {
    s32 j;
    W606Mem *m = &D_00304BE8->m[i];
    m->bits |= 1 << b;
    if (i == 0) {
        for (j = 0; j < 3; j++) {
            if (D_00304BE8->x844[j] == -1) {
                D_00304BE8->x844[j] = b;
                break;
            }
        }
    }
}
