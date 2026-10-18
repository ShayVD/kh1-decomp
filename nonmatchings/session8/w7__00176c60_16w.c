/* 00176c60 16w (hand, also nostrict; s6 draft 18w): every register now matches the original (i v1, base a1, off v0, e v1). Left: orig computes the b3 address as off+base (addu v1,v0,a1) and the b2 one becomes a reload_cse copy (move v0,v1); here combine gives base+off for D[i].b3 and the p form gives off+base, so the two adds differ and both stay, shifting the schedule. Both p-forms get merged by cse (96 bytes). */
#include "common.h"
typedef struct { u8 b0, b1, b2, b3; u8 pad[108]; } E6C;
typedef struct { u8 pad[44]; } F6C;
extern E6C D_002C5AD0[];
extern F6C D_005757B0[];
void *memset(void *, s32, u32);

void func_00176c60(s32 i) {
    E6C *p = &D_002C5AD0[i];
    D_002C5AD0[i].b3 = 0;
    p->b2 = 0;
    memset(&D_005757B0[i], 0, sizeof(F6C));
}
