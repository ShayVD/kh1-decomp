/* 001b9f78 9w (hand): second loop through D_006202A0 directly gives the original i=a0 / c=a2 (draft's p+4 giv inherits p's a0 call-arg preference via expand_preferences, so global-alloc steers i away from a0). Left: the original keeps p=&D_006202A0 in s1 across func_001ba9a8 and reuses s1 for &p->n; here the base is recomputed after the call. */
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
    c = func_001ba9a8();
    for (i = 0; i < D_006202A0.n; i++) {
        if (D_006202A0.e[i].id) { s32 j = D_006202A0.e[i].id - 1; c[j]++; }
    }
}
