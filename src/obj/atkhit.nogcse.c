/* Attack hits: the 64 hit records D_0054C440 (func_0014a450 takes one,
 * func_0014a4a8 fills one from an attack definition, func_0014bdc0 updates
 * them all) and their mask D_0054F440, the hit timers (func_0014a0f0), a
 * follow offset (func_0014a238). Flag mode: nogcse (the other modes are in
 * the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "common.h"

/* func_0014b550 (from hand/nogcse/text_00140000_s6.c). */
typedef struct {
    u32 pad0 : 7;
    u32 b7 : 1;
    u32 p8 : 2;
    u32 b10 : 1;
    u32 pad11 : 6;
    u32 k17 : 3;
    u32 pad20 : 1;
    u32 b21 : 1;
    u32 rest : 10;
    s32 x4;
    u8 pad8[0x54 - 8];
    u32 x54;
    u8 pad58[0x9c - 0x58];
    u32 x9c;
} __attribute__((aligned(8))) Cb5;
typedef struct { u8 pad[0x3e0]; u32 x3e0; } Pb5;
typedef struct {
    s32 x0;
    Pb5 *x4;
    u8 pad8[4];
    Cb5 *xc;
    u8 x10[0x20];
} Eb5;
extern u8 D_00350D28[];
s32 func_0015b998(void *, void *);
void func_0014ade0(Eb5 *, Eb5 *);
void func_0014b3e0(Eb5 *, Eb5 *);
s32 func_0014b550(Eb5 *a, Eb5 *list, s32 n) {
    s32 cnt = 0;
    Eb5 *e;
    s32 i;
    Cb5 *c, *ac;
    s32 k;
    for (i = 0; i < n; i++) {
        e = &list[i];
        if (e->x0 == a->x0) continue;
        if (e->x4 == a->x4) continue;
        c = e->xc;
        if (c->b21) continue;
        ac = a->xc;
        if (ac && ac->b21) continue;
        if (a->x4 && !ac && (a->x4->x3e0 & c->x54)) continue;
        if (c->b10) continue;
        if (!ac) {
            if (c->x4 & 0x30) continue;
            k = c->k17;
            if (k == 1 || k == 4 || k == 2) continue;
        } else {
            if (c->x9c & ac->x54) continue;
            if (c->x54 & ac->x9c) continue;
            if (!((D_00350D28[c->k17] >> ac->k17) & 1)) continue;
        }
        if (c->b7 && c->x4) continue;
        if (!func_0015b998(e->x10, a->x10)) continue;
        if (a->xc == 0) func_0014ade0(e, a);
        else func_0014b3e0(e, a);
        cnt++;
    }
    return cnt;
}

