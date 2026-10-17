/* 18w off (nostrict): register allocation only (orig v1=e,a1=&D,v0=e copy; ours v0/a3) */
#include "common.h"
typedef struct { u8 b0, b1, b2, b3; u8 pad[108]; } E6C;
typedef struct { u8 pad[44]; } F6C;
extern E6C D_002C5AD0[];
extern F6C D_005757B0[];
void *memset(void *, s32, u32);

void func_00176c60(s32 i) {
    D_002C5AD0[i].b3 = 0;
    D_002C5AD0[i].b2 = 0;
    memset(&D_005757B0[i], 0, sizeof(F6C));
}
