/* Hand-matched functions near 0x167000-0x175000 (worker 37), built without strict aliasing. */
#include "common.h"

/* ---- shared types ---- */
typedef union { s32 w; struct { u16 lo, hi; } h; } Key677;
typedef struct { f32 t; s32 a, b, c; } Key16;
typedef struct { Key677 k; s32 n; Key16 *keys; } Ent677;
typedef struct { u8 pad[0x3C]; Ent677 *tbl; } Obj677;

typedef struct { u8 pad[0x10]; u32 w10; u32 n1; u32 *list1; u32 n; s8 **list; u8 *map; } Dat684;
typedef struct { u8 b0; u8 b1; u8 pad[2]; s32 w4; u8 pad8[8]; u32 *w10; } Ent67F;
typedef struct { u8 pad[0x10]; Dat684 *w10; Dat684 *w14; Ent67F e[4]; } Obj67F;
typedef struct { u8 pad[8]; s32 w8; } Arg67F;

extern Dat684 *func_001684e0(s32);
extern void (*D_00351BC8)(s32);

/* inline copy of func_001677e0 */
static inline Ent677 *inl_001677e0(Obj677 *o, u32 key) {
    Ent677 *e = o->tbl;
    u32 hi = key >> 16;
    key &= 0xFFFF;
    for (; e->k.w != -1; e++) {
        if (e->k.h.hi == hi && (key == 0xFFFF || e->k.h.lo == key)) return e;
    }
    return 0;
}

static inline Dat684 *inl_get684(Obj67F *o, Arg67F *a) {
    if (a != 0) {
        if (o->w14 == 0) o->w14 = func_001684e0(a->w8);
        return o->w14;
    }
    return o->w10;
}

/* inline copy of func_00168318 */
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

typedef struct { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40;
typedef struct Node57 { s32 id; s32 mask; s32 (*cb)(ObjBD40 *, s32, s32, s32); s32 arg; struct Node57 *next; } Node57;
extern Node57 *D_00575780;
extern Node57 *D_00575784;
extern ObjBD40 *D_0035BD40[];

extern ObjBD40 *D_002E26A0[];
extern s32 func_00122ff8(ObjBD40 *);
extern void func_0016f3d0(ObjBD40 *, s32);
typedef struct { s32 a, b; } P8;
extern P8 D_00575310[];
extern Node57 D_00575528[];

/* ---- functions ---- */

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

u32 *func_001683b0(u32 *p) {
    if (inl_00168318(p)) {
        u32 *q = (u32 *)((u8 *)p + p[1] + 8);
        if (inl_00168318(q)) return q;
    }
    return 0;
}

void func_0016e0d0(s32 mask) {
    Node57 *n = D_00575780;
    Node57 *prev = 0;
    Node57 *next;
    while (n != 0) {
        s32 r = 1;
        next = n->next;
        if (n->cb != 0 && (u32)(n->id - 1) < 2) {
            ObjBD40 *o = D_0035BD40[n->id];
            if (o != 0) {
                r = 0;
                if ((o->flags & 0x8000) && (n->mask & mask)) {
                    r = n->cb(o, o->w144, mask, n->arg);
                }
            }
        }
        if (r == 1) {
            if (prev == 0) D_00575780 = n->next;
            else prev->next = n->next;
            n->cb = 0;
            n->next = D_00575784;
            D_00575784 = n;
        } else {
            prev = n;
        }
        n = next;
    }
}

void func_0016f548(void) {
    s32 i;
    Node57 **pp;
    if (func_00122ff8(D_002E26A0[1]) && D_002E26A0[1]->w144 != 0)
        func_0016f3d0(D_002E26A0[1], D_002E26A0[1]->w144);
    if (func_00122ff8(D_002E26A0[2]) && D_002E26A0[2]->w144 != 0)
        func_0016f3d0(D_002E26A0[2], D_002E26A0[2]->w144);
    { s32 j; for (j = 2; j >= 0; j--) D_00575310[j].a = 0; }
    pp = &D_00575784;
    for (i = 0; i < 30; i++) {
        D_00575528[i].cb = 0;
        *pp = &D_00575528[i];
        pp = &D_00575528[i].next;
    }
    *pp = 0;
    D_00575780 = 0;
}
