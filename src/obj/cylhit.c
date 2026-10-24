/* Cylinder hits between objects, default flags (docs/modules.md "Session
 * 52"): func_0015b628 and the header helpers func_0015c960 (find a hit
 * entry by kind) and func_0015c9f8 (set up the entry lists of a header).
 * The rest is in cylhit.nostrict.c.  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"

/* func_0015b628 (from hand/text_00150000_h10.c). */
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
typedef struct { u8 pad[4]; f32 r; f32 h; u8 padc[4]; f32 pos[4]; } Coll;
s32 func_0015b628(Coll *a, Coll *b) {
    f32 d[4];
    f32 r;
    func_00267530(d, b->pos, a->pos);
    if (a->h + b->h <= fabsf(d[1])) return 0;
    r = a->r + b->r;
    d[1] = 0.0f;
    if (func_00267390(d, d) < r * r) return 1;
    return 0;
}

/* func_0015c960 (from hand/text_00150000_h10.c). */
typedef struct { u8 b0; u8 pad[19]; } Ent20;
typedef struct { u8 pad[4]; u8 n4, n5, n6, n7; u8 pad8[8]; Ent20 *p10, *p14, *p18, *p1C; Ent20 data[1]; } Hdr;
typedef struct { u8 pad[0x134]; Hdr *h; u8 pad138[0x274]; u32 mask; } ObjC9;
Ent20 *func_0015c960(ObjC9 *a, s32 lo, s32 hi, s32 i) {
    Hdr *h = a->h;
    Ent20 *e;
    if (h == 0) return 0;
    e = &h->p1C[i];
    for (; i < h->n7; i++, e++) {
        if (!(a->mask & (1 << i))) {
            u32 v = e->b0;
            if ((v & 0xF) == lo && (hi < 0 || (v >> 4) == hi)) return e;
        }
    }
    return 0;
}

/* func_0015c9f8 (from hand/text_00150000_h10.c). */
void func_0015c9f8(Hdr *h) {
    Ent20 *p = h->data;
    h->p10 = p;
    p += h->n4;
    h->p14 = p;
    p += h->n5;
    h->p18 = p;
    p += h->n6;
    h->p1C = p;
}

