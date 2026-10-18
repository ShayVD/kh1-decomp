/* 3w, hand (no context). s10 w6: (1) call arg &D_006202A0 with p = &D set after the first call drops the a0 preference (giv inherits it) so the &n giv gets s1 and c a2; (2) guard + do-while for loop 2 puts i = 0 after the n test: i live 24 beats the e-giv (1.75 vs 1.59) so i gets a0. Left: orig has i = 0 (move a0,zero) in the beqz delay slot (from before the branch); here i = 0 is in the fall-through block and reorg fills the slot from the target (ld s0). With i = 0 before the test (for loop) i's live is 26 and the e-giv wins a0 (9w). */
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
/* guard + dowhile */
/* arg D, p after */
    u8 *p;
    u8 *s;
    s32 i, n;
    u8 *c;
    func_001be820(&D_006202A0, 0xF70);
    p = (u8 *)&D_006202A0;
    n = D_00377648[k];
    s = D_00377748[k];
    for (i = 0; i < n; i++) *p++ = *s++;
    c = func_001ba9a8();
    p = (u8 *)&D_006202A0;
    if (((S9f78 *)p)->n) { i = 0; do { if (((S9f78 *)p)->e[i].id) { s32 j = ((S9f78 *)p)->e[i].id - 1; c[j]++; } } while (++i < ((S9f78 *)p)->n); }
}
