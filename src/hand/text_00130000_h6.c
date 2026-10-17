/* Hand-matched functions near 0x130000 (worker 6). */
#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    u32 *p;
    s32 d;
} W6Slot;

typedef struct {
    u32 flags;
    f32 a;
    f32 b;
    s32 d;
} W6Ent;

typedef struct {
    u32 flags0;
    u8 pad004[0xD0 - 0x4];
    u8 x0d0[0x15C - 0xD0];
    s32 x15c;
    union {
        u64 bits;
        struct {
            u64 b0 : 1;
            u64 b1 : 1;
            u64 b2 : 1;
            u64 b3 : 1;
            u64 b4 : 1;
            u64 b5 : 1;
            u64 rest : 58;
        } f;
        s32 w;
    } u160;
    u8 pad168[0x170 - 0x168];
    f32 f170;
    u8 pad174[0x178 - 0x174];
    s32 count;
    W6Ent ent[5];
    u8 pad1cc[4];
    W6Slot s1d0;
    W6Slot s1e0;
    u8 pad1f0[0x284 - 0x1F0];
    f32 f284;
} W6Obj;

s32 func_00130270(W6Obj *o);
void func_00130660(W6Obj *o, void *p, s32 c, f32 a, f32 b);
void func_001321a0(W6Slot *s);
W6Ent *func_001302d0(W6Obj *o, u32 flags, f32 a, f32 b);

typedef struct {
    u8 pad00[4];
    u32 flags;
    u8 pad08[0x1C - 0x8];
    f32 v1c[3];
    u8 pad28[4];
    f32 scale;
    u8 pad30[0x38 - 0x30];
    f32 v38[3];
} W6Node;

typedef struct {
    s32 id;
    u8 pad04[0x4E - 0x4];
    u16 key;
    u8 pad50[0x5B - 0x50];
    u8 group;
    u8 pad5c[0x78 - 0x5C];
} W6Rec;

typedef struct {
    u8 pad00[0xC];
    s32 n;
    W6Rec *recs;
} W6RecTbl;

typedef struct {
    s32 x0;
    s32 x4;
    void *x8;
    s32 xc;
    s32 x10;
    u32 x14;
    void (*x18)(void);
} W6Chan;

typedef struct {
    u8 pad000[0x370];
    u64 x370;
} W6Actor;

typedef struct {
    u8 pad00[0x10];
    W6Actor *actor;
    u8 pad14[0x2C - 0x14];
    s32 x2c;
} W6Task;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} W6Trip;

typedef struct W6Link {
    u8 pad00[0x10];
    u8 id;
    u8 pad11[0x54 - 0x11];
    struct W6Link *next;
} W6Link;

typedef struct W6Pend {
    u8 pad00[8];
    union {
        u64 bits;
        struct {
            u64 lo : 44;
            u64 cnt : 4;
            u64 hi : 16;
        } f;
    } u;
    u8 pad10[0x30 - 0x10];
    struct W6Pend *next;
} W6Pend;

typedef struct {
    u8 pad000[0x3EC];
    struct W6Pend *pend;
    u8 pad3f0[0x440 - 0x3F0];
    W6Link *links;
} W6Mgr;

typedef struct {
    u8 pad00[8];
    u64 bits;
} W6Kind;

typedef struct {
    u8 pad00[0x10];
    u8 lim0;
    u8 lim1;
} W6Lim;

typedef struct {
    union {
        u64 bits;
        struct {
            u64 used : 1;
            u64 rest : 63;
        } f;
    } u;
    u8 pad08[0x40 - 0x8];
} W6Blk;

extern W6RecTbl D_00525298;
extern s32 D_005252A8;
extern s32 D_0052535C;
extern s32 D_00525360;
extern s32 D_00525354;
extern f32 D_002C58D0[];

s32 func_00162348(s32 a, u32 b);
W6Node *func_001320a8(s32 a);
void func_00120c38(f32 *m, f32 *a, f32 *v);
void func_00121958(f32 *d, f32 *s, f32 *v);
s32 func_00131e40(s32 a);
extern u32 D_002C5958;
s32 func_00123488(s32 id);
s32 func_0012ba98(s32 a);
extern W6Trip D_00526640[];
extern W6Lim *D_00308CDC;
void func_00133920(W6Mgr *m, W6Link *l);
f32 func_001348e0(W6Mgr *m, W6Kind *k);
void *memset(void *d, s32 c, u32 n);


typedef struct W6Q {
    u8 pad00[0x24];
    s32 seq;
    u32 mask;
    u8 pad2c[0x30 - 0x2C];
    struct W6Q *next;
} W6Q;

typedef struct {
    u8 pad000[0x3E0];
    u32 mask;
    u8 pad3e4[0x3E8 - 0x3E4];
    u16 n;
    u8 pad3ea[0x3EC - 0x3EA];
    W6Q *head;
} W6QMgr;

typedef struct {
    u8 pad[0x40];
} W6Cell;

typedef struct {
    u8 pad000[0x3EC];
    s32 x3ec;
    u8 pad3f0[0x4B0 - 0x3F0];
} W6Big;

typedef struct {
    u8 pad00[0x50];
    s16 h50;
} W6Sub;

typedef struct {
    u8 pad000[0x60];
    f32 x60;
    f32 x64;
    u8 pad068[0x130 - 0x68];
    W6Sub *sub;
    u8 pad134[0x38C - 0x134];
    u32 x38c;
    u32 x390;
    u8 pad394[0x3A0 - 0x394];
    s32 x3a0;
} W6Ch;

typedef struct {
    s32 a;
    s32 b;
} W6Pair;

extern W6Cell D_005267C0[];
extern W6Cell D_005277C0[];
extern W6Big D_002C64A0[];
extern s32 D_0052A150;
extern W6Pair D_0052A110[];

void func_001350d0(W6Cell *c);

//@ func_00130040
s32 func_00130040(W6Obj *o, s32 i) {
    if (o->s1d0.p == 0) {
        return 0;
    }
    return (o->s1d0.p[i] & 0xFFF) != 0xFFF;
}

//@ func_001302d0
W6Ent *func_001302d0(W6Obj *o, u32 flags, f32 a, f32 b) {
    W6Ent *e;
    if (flags & 0x1000000) {
        o->flags0 |= 4;
        flags &= ~0x1000000;
    }
    e = &o->ent[o->count++];
    e->flags = flags;
    e->a = a;
    e->b = b;
    e->d = 0;
    o->u160.f.b4 = 0;
    return e;
}

//@ func_00130340
W6Ent *func_00130340(W6Obj *o, f32 x) {
    W6Ent *e;
    o->count = 0;
    e = func_001302d0(o, func_00130270(o), 0.0f, x);
    o->u160.f.b0 = 1;
    return e;
}

//@ func_00131438
void func_00131438(W6Obj *o) {
    o->f170 = 0.0f;
    o->f284 = 1.0f;
    o->u160.w = 0;
    o->count = 0;
    o->s1e0.a = 0;
    func_00130660(o, o->x0d0, 0, o->f170, o->f170);
    o->u160.f.b1 = 0;
}

//@ func_00131498
void func_00131498(W6Obj *o) {
    if (o->s1e0.a == 0) {
        o->s1e0 = o->s1d0;
    }
    func_001321a0(&o->s1d0);
    o->u160.f.b5 = 1;
}

//@ func_00131500
void func_00131500(W6Obj *o) {
    if ((s32)(o->u160.bits >> 5) & 1) {
        o->s1d0 = o->s1e0;
        o->s1e0.a = 0;
        o->u160.f.b5 = 0;
    }
}
//@ func_00131558
s32 func_00131558(W6Obj *o, s32 x) {
    s32 r = x;
    if (r & 0x4000) {
        r &= 0xFFF;
    } else if (o->s1d0.a == 0 || (r & 0x8000)) {
        r = -1;
    } else if (r & 0x1000) {
        r &= 0xFFF;
    } else {
        r = func_00162348(o->x15c, x);
    }
    return r;
}
//@ func_00131c78
void func_00131c78(s32 a, s32 b) {
    W6Node *n = func_001320a8(a);
    if (b) {
        n->flags &= ~2;
    } else {
        n->flags |= 2;
    }
}

//@ func_00131cc8
void func_00131cc8(s32 a, f32 *m) {
    W6Node *n = func_001320a8(a);
    f32 v[4];
    f32 s;
    v[0] = n->v38[0];
    v[1] = n->v38[1];
    v[2] = n->v38[2];
    func_00120c38(m, D_002C58D0, v);
    v[0] = v[1] = v[2] = n->scale;
    func_00121958(m, m, v);
    m[12] = n->v1c[0];
    m[13] = n->v1c[1];
    m[14] = n->v1c[2];
    m[15] = 1.0f;
}

//@ func_00131de0
s32 func_00131de0(s32 id, s32 key) {
    W6Rec *r = D_00525298.recs;
    s32 i;
    for (i = 0; i < D_00525298.n; i++, r++) {
        if (id == -1) {
            if (r->key == key) {
                return r->id;
            }
        } else if (r->id == id) {
            id = -1;
        }
    }
    return -1;
}

//@ func_00131f40
s32 func_00131f40(s32 a, s32 b) {
    D_0052535C = a;
    D_00525354 = D_005252A8;
    D_00525360 = b;
    return func_00131e40(-1);
}
//@ func_00131f78
s32 func_00131f78(s32 key) {
    W6Rec *r = D_00525298.recs;
    s32 i;
    for (i = 0; i < D_00525298.n; i++, r++) {
        if (r->key == key && func_00123488(r->id) == 0) {
            return r->id;
        }
    }
    return -1;
}

//@ func_00132040
W6Rec *func_00132040(W6Rec *p) {
    s32 i;
    s32 g;
    if (p == 0) {
        g = 0;
    } else {
        g = p->group + 1;
    }
    p = D_00525298.recs;
    for (i = 0; i < D_00525298.n; i++, p++) {
        if (p->group == g) {
            return p;
        }
    }
    return 0;
}

//@ func_00133278
s32 func_00133278(W6Task *t) {
    s32 v;
    t->actor->x370 |= 0x80000000000000;
    if ((D_002C5958 >> 14) & 1) {
        return 0;
    }
    v = t->x2c;
    if (v == 0) {
        return 4;
    }
    if (func_0012ba98(v) < 0) {
        t->x2c = 0;
    }
    return 0;
}

//@ func_001337e0
void func_001337e0(s32 a, s32 b, s32 c) {
    W6Trip *e = D_00526640;
    s32 i;
    for (i = 0; i < 32; i++, e++) {
        if (e->a == -1) {
            e->a = a;
            e->b = b;
            e->c = c;
            break;
        }
    }
}

//@ func_00133978
void func_00133978(W6Mgr *m, s32 id) {
    W6Link *l;
    for (l = m->links; l != 0; l = l->next) {
        if (l->id == id) {
            func_00133920(m, l);
            break;
        }
    }
}
//@ func_001347f0
s32 func_001347f0(W6Mgr *m, W6Kind *k) {
    s32 r = (s32)(k->bits >> 32) & 0x1F;
    s32 v;
    if (r == 1) {
        v = func_001348e0(m, k) * 100.0f;
        if (v < D_00308CDC->lim0) {
            r = 3;
        } else if (v < D_00308CDC->lim1) {
            r = 4;
        } else {
            r = 5;
        }
    }
    return r;
}

//@ func_00134928
W6Pend *func_00134928(W6Mgr *m) {
    W6Pend *p = m->pend;
    if (p != 0) {
        s32 c = (s32)(p->u.bits >> 44) & 0xF;
        if (c > 0) {
            p->u.f.cnt = c - 1;
            p = 0;
        } else {
            m->pend = p->next;
            p->next = 0;
        }
    }
    return p;
}

//@ func_00134f80
W6Blk *func_00134f80(W6Blk *b, s32 n) {
    s32 i;
    for (i = 0; i < n; i++, b++) {
        if (!((s32)b->u.bits & 1)) {
            memset(b, 0, 64);
            b->u.f.used = 1;
            return b;
        }
    }
    return 0;
}
//@ func_00135000
void func_00135000(W6QMgr *m, W6Q *q) {
    W6Q *p = m->head;
    if (p == 0) {
        m->head = q;
    } else {
        while (p->next != 0) {
            p = p->next;
        }
        p->next = q;
    }
    m->mask |= q->mask;
    q->seq = ++m->n;
}

//@ func_001356a8
void func_001356a8(void) {
    W6Big *p;
    s32 i;
    for (i = 0; i < 64; i++) {
        func_001350d0(&D_005267C0[i]);
    }
    for (i = 0; i < 128; i++) {
        func_001350d0(&D_005277C0[i]);
    }
    p = D_002C64A0;
    for (i = 0; i < 96; i++, p++) {
        p->x3ec = 0;
    }
}

//@ func_001357b8
W6Pair *func_001357b8(void) {
    s32 v = D_0052A150;
    D_0052A150 = (v + 1) % 8;
    return &D_0052A110[v];
}

//@ func_00135800
void func_00135800(W6Ch *c, f32 x, f32 t) {
    if (0.0f < t) {
        c->x64 = (x - c->x60) / t;
    } else {
        c->x60 = x;
        c->x64 = 0.0f;
    }
}

//@ func_00135978
void func_00135978(W6Ch *c, s32 a, s32 b) {
    if (a-- > 0) {
        c->x38c |= 1 << a;
    }
    if (b-- > 0) {
        c->x390 |= 1 << b;
    }
}
