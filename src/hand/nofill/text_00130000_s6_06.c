#include "common.h"
typedef struct {
    u8 lv;
    u8 x1;
    u8 x2;
    u8 x3;
    u8 pad04[0x38 - 0x4];
    s16 x38;
    u8 pad3a[2];
    s32 exp;
    u8 name[0x30];
    u8 bits;
    u8 pad71[3];
} W606Mem;

typedef struct {
    u8 pad000[4];
    W606Mem m[10];
    u8 x48c;
    u8 x48d;
    u8 party[4];
    u8 pad492[0x599 - 0x492];
    u8 list599[0x30];
    u8 pad5c9[0x5CC - 0x5C9];
    u32 bits5cc[(0x7D0 - 0x5CC) / 4];
    s8 x7d0[7];
    u8 pad7d7[0x844 - 0x7D7];
    s8 x844[3];
    u8 pad847[0x878 - 0x847];
    u64 x878;
} W606Save;
#include "data/pieces/D_00304BE8.h"

typedef struct { u8 pad[0x40]; s32 x40; s32 x44; s32 x48; } W606S6c;
typedef struct { u8 pad[0x6c]; W606S6c *x6c; } W606O26a0;
extern W606O26a0 *D_002E26A0;
#include "data/pieces/D_002E27C8.h"

f32 func_0013bb20(void) {
    return (f32)((D_002E26A0->x6c->x48 + (s32)(((*(u32 *)&D_002E27C8) >> 10) & 7)) * 3000);
}

s32 func_0013c2f0(s32 b) {
    return ((W606Save *)D_00304BE8)->x878 & ((u64)1 << b);
}

void func_0013c108(s32 i, s32 b) {
    s32 j;
    W606Mem *m = &((W606Save *)D_00304BE8)->m[i];
    m->bits |= 1 << b;
    if (i == 0) {
        for (j = 0; j < 3; j++) {
            if (((W606Save *)D_00304BE8)->x844[j] == -1) {
                ((W606Save *)D_00304BE8)->x844[j] = b;
                break;
            }
        }
    }
}
