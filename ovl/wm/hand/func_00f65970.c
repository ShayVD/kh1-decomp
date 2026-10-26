/* wm.x func_00f65970: matched by hand. */
#include "ovl.h"

typedef struct { s32 pad[3]; s32 n1; s32 p1; s32 n2; s32 p2; s32 n3; s32 p3; s32 pad24; s32 p4; s32 pad2c; s32 p5; } WmRelHdr;
typedef struct { s32 pad[3]; s32 a; s32 b; } WmRel1;
typedef struct { s32 pad; s32 a; } WmRel2;
typedef struct { s32 pad[2]; u16 pad8; u16 n; s32 a; } WmRel3;

void func_00f65970(WmRelHdr *h) {
    s32 base = (s32)h;
    s32 i;
    WmRel1 *e1;
    WmRel2 *e2;
    WmRel3 *e3;

    h->p1 += base;
    h->p2 += base;
    h->p3 += base;
    h->p4 += base;
    h->p5 += base;
    e1 = (WmRel1 *)h->p1;
    for (i = 0; i < h->n1; i++) {
        e1->a += base;
        e1->b += base;
        e1 = (WmRel1 *)((u8 *)e1 + 20);
    }
    e2 = (WmRel2 *)h->p2;
    for (i = 0; i < h->n2; i++) {
        e2->a += base;
        e2++;
    }
    e3 = (WmRel3 *)h->p3;
    for (i = 0; i < h->n3; i++) {
        e3->a += base;
        e3 = (WmRel3 *)((u8 *)e3 + e3->n * 4 + 16);
    }
}
