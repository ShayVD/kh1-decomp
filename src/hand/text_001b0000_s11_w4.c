#include "common.h"

/* ---- func_001b9f78 (s11 w4): loop 2 reads the global struct directly (no p alias); hand, no context ---- */
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
    for (i = 0; i < D_006202A0.n; i++) { if (D_006202A0.e[i].id) { s32 j = D_006202A0.e[i].id - 1; c[j]++; } }
}
