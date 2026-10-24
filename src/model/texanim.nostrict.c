/* Texture animation data ("TEXA" chunks), without strict aliasing
 * (docs/modules.md "Session 52"): func_001681b8 finds a chunk by tag,
 * func_001680d8 relocates a TEXA block in place, func_001676f8 finds a key in
 * a time window, func_00167840 ... func_00167fd0 query and step an
 * animation.  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/bss_0057.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_0035BD40.h"
#include "data/pieces/D_002E26A0.h"
#include "platform/math.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h59.h"

/* func_001676f8 (from hand/nostrict/text_00160000_h37.c). */
typedef union { s32 w; struct { u16 lo, hi; } h; } Key677;
typedef struct { f32 t; s32 a, b, c; } Key16;
typedef struct { Key677 k; s32 n; Key16 *keys; } Ent677;
typedef struct { u8 pad[0x3C]; Ent677 *tbl; } Obj677;
static inline Ent677 *inl_001677e0(Obj677 *o, u32 key) {
    Ent677 *e = o->tbl;
    u32 hi = key >> 16;
    key &= 0xFFFF;
    for (; e->k.w != -1; e++) {
        if (e->k.h.hi == hi && (key == 0xFFFF || e->k.h.lo == key)) return e;
    }
    return 0;
}
Key16 *func_001676f8(Obj677 *o, u32 key, s32 *idx, f32 lo, f32 hi) {
    Ent677 *e = inl_001677e0(o, key);
    s32 i;
    if (e == 0) return 0;
    for (i = *idx; i < e->n; i++) {
        if (lo <= e->keys[i].t && e->keys[i].t < hi) {
            *idx = i;
            return &e->keys[i];
        }
    }
    return 0;
}

/* func_00167840 (from hand/nostrict/text_00160000_h37.c). */
typedef struct { u8 pad[0x10]; u32 w10; u32 n1; u32 *list1; u32 n; s8 **list; u8 *map; } Dat684;
typedef struct { u8 b0; u8 b1; u8 pad[2]; s32 w4; u8 pad8[8]; u32 *w10; } Ent67F;
typedef struct { u8 pad[0x10]; Dat684 *w10; Dat684 *w14; Ent67F e[4]; } Obj67F;
typedef struct { u8 pad[8]; s32 w8; } Arg67F;
extern Dat684 *func_001684e0(s32);
static inline Dat684 *inl_get684(Obj67F *o, Arg67F *a) {
    if (a != 0) {
        if (o->w14 == 0) o->w14 = func_001684e0(a->w8);
        return o->w14;
    }
    return o->w10;
}
s32 func_00167840(Obj67F *o, Arg67F *a, u32 id) {
    Dat684 *d, *d2;
    s32 k;
    s32 j;
    s32 m;
    d = inl_get684(o, a);
    k = -1;
    if (d != 0) {
        k = id - 0x400;
        if (id < 0x400) k = d->map[id] - 1;
    }
    if (k < 0) return 0;
    d2 = inl_get684(o, a);
    if (d2 == 0) return 0;
    if (!((u32)k < d2->n)) return 0;
    j = *d2->list[k];
    if (o->e[j].w10 == 0 || (m = *o->e[j].w10 & 0xF) == 2) return 1;
    if (o->e[j].w4 == 0 && m == 3) return 1;
    return 0;
}

/* func_00167978 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { u8 pad[0x1c]; u32 n; s8 **ids; u8 *map; } Tbl59;
typedef struct { u8 id; s8 x1; u8 pad2[2]; s32 busy; f32 x8; f32 xC; u32 *p; } Slot59;
typedef struct { u8 pad[0x10]; Tbl59 *t10; Tbl59 *t14; Slot59 s[1]; } Own59;
typedef struct { u8 pad[8]; s32 x8; } Res59;
static inline Tbl59 *inl_tbl59(Own59 *o, Res59 *r) {
    if (r) {
        if (!o->t14) o->t14 = func_001684e0(r->x8);
        return o->t14;
    }
    return o->t10;
}
#define func_001684e0 ((Tbl59 *(*)(s32)) func_001684e0)
s32 func_00167978(Own59 *o, Res59 *r, u32 n) {
    Tbl59 *t1 = inl_tbl59(o, r);
    Tbl59 *t;
    s32 id = -1;
    s32 k;
    u32 f;
    u32 *p;
    if (t1) {
        id = n - 1024;
        if (n < 1024) id = t1->map[n] - 1;
    }
    if (id < 0) return 3;
    t = inl_tbl59(o, r);
    if (!t) return 3;
    if ((u32)id >= t->n) return 3;
    k = *t->ids[id];
    p = o->s[k].p;
    if (!p || o->s[k].id != id) return 4;
    f = *p & 0xf;
    if (f == 2) return 2;
    if (!o->s[k].busy) return f == 3 ? 2 : 1;
    return 0;
}
#undef func_001684e0

/* func_00167ac0 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { u16 x0; u16 x2; u16 x4; s16 x6; } Hd59;
s32 func_001627e8(s32);
#define func_001684e0 ((Tbl59 *(*)(s32)) func_001684e0)
void func_00167ac0(Own59 *o, Res59 *r, u32 n) {
    Tbl59 *t1 = inl_tbl59(o, r);
    Tbl59 *t;
    s32 id = -1;
    s32 k;
    Hd59 *h;
    s32 v;
    if (t1) {
        id = n - 1024;
        if (n < 1024) id = t1->map[n] - 1;
    }
    if (id >= 0) {
    t = inl_tbl59(o, r);
    if (t && (u32)id < t->n) {
    k = *t->ids[id];
    o->s[k].id = id;
    o->s[k].x1 = 1;
    o->s[k].busy = (s32)t->ids[id];
    o->s[k].x8 = 0;
    h = (Hd59 *)(t->ids[id] + 4);
    o->s[k].p = (u32 *)h;
    if (h->x4 == 0) v = h->x2;
    else v = h->x2 + func_001627e8(h->x4 + 1);
    o->s[k].xC = v;
    }
    }
}
#undef func_001684e0

/* func_00167c40 (from hand/nostrict/text_00160000_h37.c). */
void func_00167c40(Obj67F *o, Arg67F *a, u32 id) {
    Dat684 *d, *d2;
    s32 k;
    d = inl_get684(o, a);
    k = -1;
    if (d != 0) {
        k = id - 0x400;
        if (id < 0x400) k = d->map[id] - 1;
    }
    if (k < 0) return;
    d2 = inl_get684(o, a);
    if (d2 == 0) return;
    if (!((u32)k < d2->n)) return;
    if (o->e[*d2->list[k]].b0 == k) {
        o->e[*d2->list[k]].w4 = 0;
        o->e[*d2->list[k]].w10 = 0;
    }
}

/* func_00167d70 (from hand/nostrict/text_00150000_h59.c). */
void func_00167d70(Own59 *o, f32 dt) {
    s32 i;
    u32 f;
    s32 v;
    Hd59 *h;
    if (dt <= 0.0f) return;
    for (i = 0; i < 5; i++) {
        if (!o->s[i].p) continue;
        f = *o->s[i].p & 0xf;
        if (f == 2) continue;
        if (f == 3) {
            if (o->s[i].busy) {
                o->s[i].p = o->s[i].p + ((Hd59 *)o->s[i].p)->x6 * 2;
            } else {
                o->s[i].p = 0;
                continue;
            }
        }
        if (o->s[i].x1) {
            o->s[i].x1 = 0;
            continue;
        }
        o->s[i].x8 += dt;
        if (o->s[i].xC <= o->s[i].x8) {
            do {
                o->s[i].x8 -= o->s[i].xC;
                o->s[i].p += 2;
                f = *o->s[i].p & 0xf;
                if (f == 3) {
                    if (!o->s[i].busy) {
                        o->s[i].p = 0;
                        break;
                    }
                    o->s[i].p = o->s[i].p + ((Hd59 *)o->s[i].p)->x6 * 2;
                } else if (f == 2) {
                    break;
                }
                h = (Hd59 *)o->s[i].p;
                if (h->x4 == 0) v = h->x2;
                else v = h->x2 + func_001627e8(h->x4 + 1);
                o->s[i].xC = v;
            } while (o->s[i].xC <= o->s[i].x8);
        }
    }
}

/* func_00167fd0 (from hand/nostrict/text_00160000_h37.c). */
void func_00167fd0(Obj67F *o, Arg67F *a, u32 id) {
    Dat684 *d, *d2;
    s32 k;
    d = inl_get684(o, a);
    k = -1;
    if (d != 0) {
        k = id - 0x400;
        if (id < 0x400) k = d->map[id] - 1;
    }
    if (k < 0) return;
    d2 = inl_get684(o, a);
    if (d2 == 0) return;
    if (!((u32)k < d2->n)) return;
    if (o->e[*d2->list[k]].b0 == k) o->e[*d2->list[k]].w4 = 0;
}

/* func_001680d8 (from hand/nostrict/text_00160000_h37.c). */
void func_001680d8(s32 id) {
    Dat684 *d = func_001684e0(id);
    u32 i;
    if (d != 0) {
        d->w10 = (u32)d + d->w10;
        d->list1 = (u32 *)((u32)d + (u32)d->list1);
        for (i = 0; i < d->n1; i++) d->list1[i] = (u32)d + d->list1[i];
        d->list = (s8 **)((u32)d + (u32)d->list);
        for (i = 0; i < d->n; i++) d->list[i] = (s8 *)((u32)d + (u32)d->list[i]);
        d->map = (u8 *)((u32)d + (u32)d->map);
    }
    D_00351BC8(0);
}

/* func_001681b8 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { u32 tag; u32 size; } Chk59;
static inline s32 inl_known59(u32 t) {
    switch (t) {
    case 0x4A424F4D:
    case 0x41584554:
    case 0x454E4F42:
    case 0x4E544D4D:
    case 0x4C535255:
    case 0x564E454D:
        return 1;
    }
    return 0;
}
static inline Chk59 *inl_next59(Chk59 *c) {
    if (inl_known59(c->tag)) {
        c = (Chk59 *)((u8 *)c + c->size + 8);
        if (inl_known59(c->tag)) return c;
    }
    return 0;
}
Chk59 *func_001681b8(Chk59 *c, u32 tag) {
    for (; c; c = inl_next59(c)) {
        if (c->tag == tag) break;
    }
    if (c) {
        if (c->size == 0) return 0;
    }
    return c;
}

/* func_001683b0 (from hand/nostrict/text_00160000_h37.c). */
static inline s32 inl_00168318(u32 *p) {
    switch (*p) {
    case 0x4A424F4D:
    case 0x41584554:
    case 0x454E4F42:
    case 0x4E544D4D:
    case 0x4C535255:
    case 0x564E454D:
        return 1;
    }
    return 0;
}
u32 *func_001683b0(u32 *p) {
    if (inl_00168318(p)) {
        u32 *q = (u32 *)((u8 *)p + p[1] + 8);
        if (inl_00168318(q)) return q;
    }
    return 0;
}

