/* 10 words off (mode hand): register choice only; orig gives copy counter/i a0 and c a2, and reuses s1 (p) as &p->n (addiu s1,s1,4). */
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
