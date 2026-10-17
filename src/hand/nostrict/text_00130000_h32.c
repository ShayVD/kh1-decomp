/* Hand-matched functions near 0x130000 built without strict aliasing (worker 32). */
#include "common.h"

typedef struct {
    s32 a, b, c, d, e, f, g;
} W32Args;
typedef struct {
    u8 pad00[0x10];
    W32Args args;
    u8 pad2c[0x2C - 0x2C];
    s32 x2c;
} W32Task;
extern u8 D_00525A30[];
void func_00133278(void);
W32Task *func_0011f090(void *a, s32 b, void (*c)(void));
s32 func_0012b888(s32 a);
void func_0012ba30(s32 a, void *b, s32 c);
W32Args *func_001332f0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    W32Task *t = func_0011f090(D_00525A30, 0, func_00133278);
    W32Args *p;
    s32 h;
    p = &t->args;
    p->a = a0;
    p->b = a1;
    p->c = a2;
    p->d = a3;
    p->e = a5;
    p->f = a6;
    p->g = 0;
    h = func_0012b888(a4);
    func_0012ba30(h, &p, 4);
    t->x2c = h;
    return p;
}
typedef struct { u64 a, b, c, d; } W32V32;
typedef struct W32Node {
    s32 used;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    W32V32 v;
    u8 pad30[0x50 - 0x30];
    struct W32Node *prev;
    struct W32Node *next;
    u8 pad58[0x60 - 0x58];
} W32Node;
typedef struct {
    u8 pad000[0x440];
    W32Node *head;
} W32List;
extern W32Node D_00525A40[32];
W32Node *func_00133868(W32List *l, W32V32 *v) {
    W32Node *n = D_00525A40;
    W32Node *p;
    s32 i;
    for (i = 0; i < 32; i++, n++) {
        if (n->used == 0) {
            if (l->head == 0) {
                l->head = n;
                n->prev = 0;
            } else {
                for (p = l->head; p->next; p = p->next);
                p->next = n;
                n->prev = p;
            }
            n->used = 1;
            n->v = *v;
            n->next = 0;
            n->x4 = 0;
            return n;
        }
    }
    return 0;
}
typedef struct W32Fig {
    u64 x0;
    u8 pad008[0x7C - 0x8];
    struct W32Fig *x7c;
    u8 pad080[0x144 - 0x80];
    s32 x144;
    u8 pad148[0x370 - 0x148];
    u64 x370;
} W32Fig;
typedef struct {
    u8 pad00[4];
    W32Fig *x4;
} W32Msg;
typedef struct {
    void *p;
    s32 n;
} W32Dsc;
extern u32 D_002C5958;
void func_0012bce0(s32 h, s32 a, s32 b, W32Dsc *d, s32 *r);
void func_001349d0(W32Fig *o);
void func_00139c28(W32Fig *o, W32Msg *m);
s32 func_00139cb8(W32Fig *o, W32Msg *m) {
    if ((o->x0 & 0x1000088) || ((s32)(o->x370 >> 51) & 1)) return 0;
    if (D_002C5958 & 0x4100000) return 0;
    if (m->x4) {
        o->x7c = (((s32)(m->x4->x370 >> 37) & 3) == 1) ? m->x4 : 0;
    }
    if (((s32)(o->x370 >> 48) & 1) && o->x144) {
        W32Dsc d[1];
        d[0].p = &m;
        d[0].n = 4;
        func_0012bce0(o->x144, 0, 1, d, 0);
    } else {
        func_001349d0(o);
    }
    func_00139c28(o, m);
    return 1;
}
