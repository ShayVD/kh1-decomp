#include "common.h"
typedef struct {
    u8 pad0[0xce];
    s16 ce;
    s16 d0;
    s16 d2;
    u8 pad_d4[8];
    u8 dc[1];
} Fade;

void func_001fe4e0(Fade *o) {
    s32 i;
    s32 n1 = o->ce + 1;
    s32 cnt = (o->d0 & 0xf) ? n1 : o->ce;
    s32 k = (o->d0 >> 4) % n1;
    for (i = 0; i < cnt; i++) {
        o->dc[k] = 64;
        k = (k + 1) % n1;
    }
}
