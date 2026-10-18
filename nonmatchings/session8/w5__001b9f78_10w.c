/* 001b9f78 10w, mode hand. Session-6 shape (p reassigned before func_001ba9a8). Cause: the loop-2 &p->n giv (p+4, p dies there) gets p's a0 call-argument preference via global.c expand_preferences, so i (allocated earlier) avoids a0 (regs_someone_prefers) and lands in a2. A separate dst pointer for loop 1 drops the a0 pref but then p gets s0 instead of s1. Param k as loop index, &D_006202A0 as the call arg, extra copies: no. Flag sweep: nothing. */
#include "common.h"
typedef struct {
    u16 id;
    u8 pad[10];
} Ent9f78;
typedef struct {
    u8 pad0[4];
    u16 n;
    u8 pad6[0x6E];
    Ent9f78 e[1];
} S9f78;
extern S9f78 D_006202A0;
extern s32 D_00377648[];
extern u8 *D_00377748[];
void func_001be820(void *, s32);
u8 *func_001ba9a8(void);
void func_001b9f78(s32 k) {
    u8 *p = (u8 *)&D_006202A0;
    u8 *s;
    s32 i, n;
    u8 *c;
    func_001be820(p, 0xF70);
    n = D_00377648[k];
    s = D_00377748[k];
    for (i = 0; i < n; i++) *p++ = *s++;
    p = (u8 *)&D_006202A0;
    c = func_001ba9a8();
    for (i = 0; i < ((S9f78 *)p)->n; i++) {
        if (((S9f78 *)p)->e[i].id) { s32 j = ((S9f78 *)p)->e[i].id - 1; c[j]++; }
    }
}
