/* Hand-matched functions near 0x167000-0x175000 (worker 37), built without strict aliasing. */
#include "common.h"
#include "data/bss_0057.h"

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
#include "data/pieces/D_00351BC8.h"

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

#include "data/pieces/D_0035BD40.h"
typedef ObjBD40_35BD40 ObjBD40;
typedef struct Node57 { s32 id; s32 mask; s32 (*cb)(ObjBD40 *, s32, s32, s32); s32 arg; struct Node57 *next; } Node57;
extern Node57 *D_00575780; /* src/data/bss_0057.c: void *D_00575780 */
extern Node57 *D_00575784; /* src/data/bss_0057.c: void *D_00575784 */

#include "data/pieces/D_002E26A0.h"
extern s32 func_00122ff8(void *); /* an actor (D_002E26A0[k] or an ObjBD40) */
extern void func_0016f3d0(void *, s32);
typedef struct { s32 a, b; } P8;
extern P8 D_00575310[]; /* src/data/bss_0057.c: TalkEA D_00575310 */
extern Node57 D_00575528[]; /* src/data/bss_0057.c: Node6F D_00575528[30] */

extern u32 D_002C5958;
extern f32 D_0048E9EC;
extern s32 func_0012f040(ObjBD40 *, s32);
extern s32 func_0012ee70(ObjBD40 *, s32);
extern f32 func_0012ec60(ObjBD40 *, s32, f32 *);
extern void func_00267530(f32 *, f32 *, f32 *);
extern f32 func_00267390(f32 *, f32 *);

typedef struct { u8 pad[0x10]; f32 pos[4]; } ObjPos;
typedef struct {
    u8 pad[0x38]; u64 w38; u8 pad40[0x50];
    ObjBD40 *tgt; s32 part; s32 w98; f32 f9C; f32 fA0; u8 padA4[0xC];
    f32 vB0[4]; f32 vC0[3]; f32 fCC; f32 vD0[3]; f32 fDC;
} Lock90;

extern f32 D_0048EA6C;

typedef struct { u8 pad[0x21]; u8 n; u8 ids[1]; } ListC8;
typedef struct { u8 pad[0xC8]; ListC8 *pC8; } Sub6Cx;
typedef struct { u8 pad[0x6C]; Sub6Cx *p6C; s32 w70; } Obj14F;
extern s32 func_0012ca98(Obj14F *);

typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x350]; u64 f370; } Ent370;
extern Ent370 *func_00123158(void *, Ent370 *);
extern s32 func_00123368(Ent370 *);

extern f32 func_00162c20(f32 *);

typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x50]; s32 w70; u8 pad74[0x250]; f32 f2C4; } Obj2C4;
extern void func_0016fc60(Obj2C4 *, Lock90 *);
extern void func_002675a8(f32 *, f32 *);

typedef struct { u8 pad[0xB4]; void *cb; void **slot; } Sub2C;
typedef struct { u8 pad[0x2C]; Sub2C *p2C; } Sub14C;
typedef struct { u8 pad[0x14C]; Sub14C *p14C; } Obj14C;
typedef struct { u8 pad[0x3C]; void **slot; Sub2C *p40; } Arg3C;
extern s32 D_00574FB8;
extern void *D_00574FC0[20];
extern s32 func_0013dc10(Obj14C *, s32);
extern void func_00171f38(void);

typedef struct { u8 pad[4]; u32 flags; } Sub74;
typedef struct {
    u8 pad[0x10]; s32 w10; s32 w14; u8 pad18[0x20]; u64 w38; u8 pad40[8];
    void *cb48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[8]; Sub74 *p74; u8 pad78[0x18]; s32 w90;
} Wk171;
typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0x35C]; s32 w3D0; } Obj3D0;
extern void func_00130340(Obj3D0 *, s32, f32);
extern void func_0016df30(void);

typedef struct { u8 pad[0x18]; f32 f18; } Sub130x;
typedef struct { u8 pad[0x130]; Sub130x *p130; } Obj130x;
typedef struct { u8 pad[0x38]; u64 w38; u8 pad40[0x18]; s32 w58; u8 pad5C[4]; s32 w60; u8 pad64[0xC]; f32 f70; } Wk70;
extern s32 D_002E27A8;
extern void func_00124060(Obj130x *, s32);
extern void func_00135800(Obj130x *, f32, f32);
extern void func_001373f8(Obj130x *, f32);

typedef struct { s32 w0; u8 pad4[0x10]; f32 f14, f18, f1C, f20, f24; } Sub170C;
typedef struct { u8 pad[0xC]; Sub170C *pC; } Sub170;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40;
typedef struct { u8 pad[0x38]; u64 w38; Sub40 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144;
typedef struct { u8 pad[0xC]; void *cb; } Task0C;
typedef struct { u8 pad[0x30]; s32 w30; } Res30;
typedef struct { u8 pad[4]; s32 w4; } Res04;
extern u8 D_0035BE40[];
extern Task0C *func_00130578(Obj144 *, s32, f32);
extern void func_00148a40(Obj144 *, s32);
extern void func_00170fa8(Obj144 *, Wk144 *, void *, void *, f32);
extern s32 func_00170f90();
extern void func_001731f8();
extern Res04 *func_0013dbe0(Obj144 *, s32);
extern Res30 *func_001477c8(s32);
extern void func_001412f8(Obj144 *, s32);

extern s32 func_00171a88(Obj144 *, Wk144 *, s32);
extern s32 func_0016b670(Obj144 *, Wk144 *, s32, s32);

extern void func_0014f658(Obj144 *, s32);

extern f32 func_00171aa8(f32, f32);
extern s32 func_00171ae8(Obj144 *, Wk144 *);

extern s32 func_00171118(ObjBD40 *, s32);
extern void func_00171790(Obj2C4 *, Lock90 *);

extern u8 D_0035C080[];
extern void func_00267e90(f32 *, f32 *, f32);

extern u8 D_0035C130[];
extern s32 func_0016ce10(Obj144 *, Wk144 *, s32, s32);
extern s32 func_0016d768(Obj144 *, Wk144 *, s32, s32);

typedef struct { u8 pad[0x38]; u64 w38; Sub40 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0xF4]; Sub170 *p160; s32 w164; } Wk160;
typedef struct { u8 pad[0x144]; Wk160 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj160;
extern s32 func_0016cb98(Obj144 *, Wk144 *, s32, s32);

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
            ObjBD40 *o = D_0035BD40.objBD40[n->id];
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
    if (func_00122ff8(D_002E26A0[1]) && ((ObjBD40 *)D_002E26A0[1])->w144 != 0)
        func_0016f3d0(D_002E26A0[1], ((ObjBD40 *)D_002E26A0[1])->w144);
    if (func_00122ff8(D_002E26A0[2]) && ((ObjBD40 *)D_002E26A0[2])->w144 != 0)
        func_0016f3d0(D_002E26A0[2], ((ObjBD40 *)D_002E26A0[2])->w144);
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

s32 func_00171118(ObjBD40 *t, s32 i) {
    s32 r = 0;
    if (!(D_002C5958 & 1)) return r;
    if (t == 0) return r;
    if (func_00122ff8(t)) {
        if (i >= 0) return func_0012f040(t, i);
        for (i = -1; (i = func_0012ee70(t, i)) >= 0;) {
            if (func_0012f040(t, i)) return 1;
        }
    }
    return 0;
}

s32 func_00171320(ObjPos *self, ObjBD40 *t) {
    f32 a[4];
    f32 b[4];
    s32 i, best;
    f32 bd, d;
    best = -1;
    if (t != 0) {
        bd = D_0048EA6C;
        for (i = -1; (i = func_0012ee70(t, i)) >= 0;) {
            if (func_0012f040(t, i)) {
                func_0012ec60(t, i, a);
                func_00267530(b, a, self->pos);
                d = func_00267390(b, b);
                if (d < bd) {
                    bd = d;
                    best = i;
                }
            }
        }
    }
    return best;
}

s32 func_001714f0(Obj14F *o, s32 id) {
    ListC8 *l;
    s32 i;
    if (!func_0012ca98(o)) return 0;
    switch (o->w70) {
    case 0:
    case 8:
    case 24:
        l = o->p6C->pC8;
        for (i = 0; i < l->n; i++) {
            if (l->ids[i] == id) return 1;
        }
        break;
    }
    return 0;

}

s32 func_001715b0(void *grp, Ent370 *self, f32 r) {
    f32 v[4];
    Ent370 *p = 0;
    s32 n = 0;
    f32 r2 = r * r;
    while ((p = func_00123158(grp, p)) != 0) {
        if (p == self) continue;
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        func_00267530(v, p->pos, self->pos);
        if (func_00267390(v, v) < r2) n++;
    }
    return n;
}

s32 func_00171680(Ent370 *self, Ent370 *tgt) {
    f32 dir[4];
    f32 v[4];
    Ent370 *p = 0;
    s32 n = 0;
    f32 c;
    func_00267530(dir, tgt->pos, self->pos);
    c = 0.7f;
    func_00162c20(dir);
    while ((p = func_00123158(self, p)) != 0) {
        if (p == tgt) continue;
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        func_00267530(v, p->pos, self->pos);
        func_00162c20(v);
        if (c < func_00267390(v, dir)) n++;
    }
    return n;
}

void func_00171790(Obj2C4 *self, Lock90 *l) {
    func_0016fc60(self, l);
    if (l->tgt != 0 && l->part >= 0) {
        l->f9C = func_0012ec60(l->tgt, l->part, l->vB0);
        if (((s32)((s64)(l->w38 << 12) >> 32) & 1) || self->w70 == 8 || self->w70 == 24 || self->w70 == 25)
            l->vB0[1] += self->f2C4;
        func_00267530(l->vC0, l->vB0, self->pos);
        func_002675a8(l->vD0, l->vC0);
        l->fA0 = l->vD0[1];
        l->vD0[1] = 0;
        l->fCC = func_00162c20(l->vC0);
        l->fDC = func_00162c20(l->vD0);
        return;
    }
    l->tgt = 0;
    l->part = -1;
}

s32 func_00171b80(Obj14C *o, Arg3C *l, s32 k) {
    s32 i = D_00574FB8;
    s32 n = 0;
    s32 r;
    Sub2C *p;
    while (D_00574FC0[i] != 0) {
        i++;
        n++;
        if (i >= 20) i = 0;
        if (n >= 20) goto out;
    }
out:

    D_00574FB8 = i + 1;
    if (i + 1 >= 20) D_00574FB8 = 0;
    r = func_0013dc10(o, k);
    p = o->p14C->p2C;
    if (p != 0) {
        void **s = &D_00574FC0[i];
        p->slot = s;
        p->cb = func_00171f38;
        l->slot = s;
        *s = p;
        l->p40 = p;
    } else {
        l->p40 = 0;
    }
    return r;
}

s32 func_00171c80(Obj3D0 *o, Wk171 *w, s32 unused, s32 mode) {
    switch (mode) {
    case 0:
        if (w->w10 <= 0 || !w->w14) return 0;
        if (o->w70 != 0) return 0;
        if (w->w90 == 0) return 0;
        if (w->p74 == 0) return 0;
        if (w->p74->flags & 0xC00) return 0;
        goto ret1;
    case 1:
        return 0;
    case 2:
        w->w4C = 4;
        o->w3D0 = 0;
        func_00130340(o, 0x1000004, 0.0f);
        w->w38 |= 0x8000;
        w->f68 = 4.0f;
        w->cb48 = func_0016df30;
    ret1:
        return 1;
    }
    return 1;
}

void func_00171d80(Obj130x *o, Wk70 *w, s32 k) {
    func_00124060(o, k);
    func_00135800(o, 0.0f, 0.0f);
    func_00135800(o, 1.0f, 30.0f);
    o->p130->f18 = 1.0f;
    func_001373f8(o, 30.0f);
    w->w38 |= 0x40;
    w->w58 = 0;
    w->w60 = 0;
    if (D_002E27A8 == 2) w->f70 = 600.0f;
    else w->f70 = 240.0f;
}

s32 func_00172df8(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 29)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035BE40, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_00172f00(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 30)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035BE40, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_00173008(Obj144 *o, Wk144 *w, Sub170 *k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 31)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (w->w90 == 0) return 0;
        return func_0016b670(o, w, (s32)k, 1);
    case 2:
        w->p170 = k;
        w->w38 |= 0x800;
        func_0014f658(o, 50);
        return 1;
    }
    return 1;
}

s32 func_001730f0(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 29)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035BE40, 30.0f);
        return 1;
    }
    return 1;
}

void func_001731f8(Obj144 *o) {
    Wk144 *w = o->p144;
    Sub170C *c;
    if ((s32)((s64)(w->w38 << 15) >> 32) & 1) {
        w->w38 &= ~0x20000LL;
        return;
    }
    c = w->p170->pC;
    w->f68 = func_00171aa8(c->f14, c->f18);
    w->w4C = *(s16 *)func_00171b80((Obj14C *)o, (Arg3C *)w, c->w0);
    if (func_00171ae8(o, w)) w->p40->f50 = c->f1C;
    w->w174 = 1;
}

void func_00173360(Obj144 *o) {
    Wk144 *w = o->p144;
    s32 st = o->w70;
    if (!func_00171118(w->w90, -1)) {
        st = 0;
    } else {
        w->w38 |= 0x100000;
        func_00171790((Obj2C4 *)o, (Lock90 *)w);
    }
    switch (w->w174) {
    case 0:
        if (!(o->w160 & 1) && o->w164 != 206) st = 0;
        break;
    case 1:
        if ((o->w160 & 1) || o->w164 == w->w4C) {
            if (w->f68 <= 0.0f) st = 0;
        } else {
            st = 0;
        }
        break;
    }
    if (o->w70 != st) func_0014f658(o, st);
}

s32 func_001734f8(Obj144 *o, Wk144 *w, s32 mode) {
    s32 r = 0;
    switch (mode) {
    case 1:
        switch (w->w174) {
        case 0:
            if (!(o->w160 & 1) && o->w164 != 206) r = 1;
            break;
        case 1:
            if (!(o->w160 & 1) && o->w164 != w->w4C) r = 1;
            break;
        }
        break;
    case 2:
        r = w->w48 == 0;
        break;
    }
    if (r == 1) {
        w->w38 = ((w->w38 & ~0x800LL) | 0x20000) & ~0x200LL;
        w->w48 = 0;
        if (o->w164 == 206 || o->w164 == w->w4C) func_00130340((Obj3D0 *)o, w->w178, 8.0f);
    }
    return r;
}

void func_00173610(Obj144 *o, Wk144 *w) {
    f32 v[4];
    Sub170C *c = w->p170->pC;
    if (!func_00171118(w->w90, -1)) {
        w->w48 = 0;
        return;
    }
    w->w38 |= 0x100000;
    func_00171790((Obj2C4 *)o, (Lock90 *)w);
    switch (w->w174) {
    case 0:
        return;
    case 1:
        if (w->f68 <= 0.0f) w->w48 = 0;
        w->w38 |= 0x1000;
        if (o->w70 == 8) w->w38 |= 0x200;
        func_00267e90(v, w->vC0, c->f20);
        w->f124 = v[1];
        v[1] = 0.0f;
        w->f12C = func_00162c20(v);
        w->f120 = v[0];
        w->f128 = v[2];
        break;
    }
}

s32 func_00173758(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 33)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035C080, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_00173860(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 34)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035C080, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_00173968(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 35)) return 0;
        return func_0016ce10(o, w, k, 1);
    case 2:
        func_0016ce10(o, w, k, 2);
        return 1;
    }
    return 1;
}

s32 func_00173a20(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 36)) return 0;
        return func_0016d768(o, w, k, 1);
    case 2:
        func_0016d768(o, w, k, 2);
        return 1;
    }
    return 1;
}

s32 func_00173af0(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 37)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035C130, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_00173bf8(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 38)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035C130, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_00173ec0(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 50)) return 0;
        return func_0016cb98(o, w, k, 1);
    case 2:
        func_0016cb98(o, w, k, 2);
        return 1;
    }
    return 1;
}

s32 func_00173f78(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 51)) return 0;
        return func_0016ce10(o, w, k, 1);
    case 2:
        func_0016ce10(o, w, k, 2);
        return 1;
    }
    return 1;
}

s32 func_00174030(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 52)) return 0;
        return func_0016d768(o, w, k, 1);
    case 2:
        func_0016d768(o, w, k, 2);
        return 1;
    }
    return 1;
}

void func_001740e8(Obj160 *o) {
    Wk160 *w = o->p144;
    Sub170C *c;
    if ((s32)((s64)(w->w38 << 15) >> 32) & 1) {
        w->w38 &= ~0x20000LL;
        return;
    }
    c = w->p160->pC;
    w->f68 = func_00171aa8(c->f14, c->f18);
    w->w4C = *(s16 *)func_00171b80((Obj14C *)o, (Arg3C *)w, c->w0);
    if (func_00171ae8((Obj144 *)o, (Wk144 *)w)) w->p40->f50 = c->f1C;
    w->w164 = 1;
}

s32 func_001741a0(Obj160 *o, Wk160 *w, s32 mode) {
    s32 r = 0;
    switch (mode) {
    case 1:
        switch (w->w164) {
        case 0:
            if (!(o->w160 & 1) && o->w164 != 202) r = 1;
            break;
        case 1:
            if (!(o->w160 & 1) && o->w164 != w->w4C) r = 1;
            break;
        }
        break;
    case 2:
        r = w->w48 == 0;
        break;
    }
    if (r == 1) {
        w->w38 = (w->w38 & ~0x800LL) | 0x20000;
        w->w48 = 0;
        if (o->w164 == 202 || o->w164 == w->w4C) func_00130340((Obj3D0 *)o, 0x40000000, 8.0f);
    }
    return r;
}

/* needs make: uses rodata */
extern void memset(void *, s32, s32);
extern s32 func_0013c968(s32, s32);
extern u8 D_00575788[8];

void func_0016f7b8(void) {
    s32 i;
    s32 k;
    memset(D_00575788, 0, 8);
    for (i = 0; i < 64; i++) {
        switch (i) {
        case 29: case 30: case 31: case 32: case 63:
            k = 2; break;
        case 33: case 34: case 35: case 36:
            k = 3; break;
        case 37: case 38:
            k = 5; break;
        case 39: case 40: case 41: case 42: case 43:
            k = 7; break;
        case 44: case 45: case 46:
            k = 8; break;
        case 47: case 48:
            k = 9; break;
        case 49: case 50: case 51: case 52:
            k = 6; break;
        default:
            k = -1; break;
        }
        if (k >= 0) {
            s32 b = i >> 3;
            s32 m = i & 7;
            if (func_0013c968(i, k)) D_00575788[b] |= 1 << m;
        }
    }
}
#include "data/data_002E.h"
#include "data/data_0035.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C5958.h"
