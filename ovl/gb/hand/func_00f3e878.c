/* gb.x func_00f3e878: matched by hand. */
#include "ovl.h"

typedef struct { s32 pad[3]; s32 a; s32 b; } EA;
typedef struct { s32 x; s32 p; } EB;
typedef struct { u8 pad[10]; u16 n; s32 p; } EC;
typedef struct { s32 pad[3]; s32 n1; EA *a; s32 n2; EB *b; s32 n3; EC *c; s32 pad36; s32 d40; s32 pad44; s32 d48; } H;
void func_00f3e878(H *h) {
    s32 i;
    EA *a;
    EB *b;
    EC *c;
    h->a = (EA *)((s32)h->a + (s32)h);
    h->b = (EB *)((s32)h->b + (s32)h);
    h->c = (EC *)((s32)h->c + (s32)h);
    h->d40 += (s32)h;
    h->d48 += (s32)h;
    for (i = 0, a = h->a; i < h->n1; i++, a++) {
        a->a += (s32)h;
        a->b += (s32)h;
    }
    for (i = 0, b = h->b; i < h->n2; i++, b++) b->p += (s32)h;
    for (i = 0, c = h->c; i < h->n3; i++) {
        c->p += (s32)h;
        c = (EC *)((u8 *)c + c->n * 4 + 16);
    }
}
