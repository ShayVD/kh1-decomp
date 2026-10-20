/* Hand-matched functions near 0x130000 (worker 6). */
#include "common.h"
#include "data/bss_0052.h"

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
    s32 x8;
    s32 xc;
    s32 x10;
    u32 x14;
    s32 x18;
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
    u8 pad12[0x14 - 0x12];
    u16 h14;
    u16 h16;
    f32 f18;
    u8 pad1c[0x2C - 0x1C];
    f32 f2c;
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
W6Pair D_0052A110[0x8] ALIGNED(16);

void func_001350d0(W6Cell *c);

typedef struct {
    u8 pad000[0x38C];
    u32 x38c;
    u32 x390;
    u32 x394;
} W6Ch2;

typedef struct {
    s32 x0;
    s32 x4;
    s32 id;
    union {
        u32 w;
        struct {
            u32 b0 : 1;
            u32 b1 : 8;
            u32 rest : 23;
        } f;
    } xc;
} W6Ent16;

typedef struct {
    u32 flags;
    u8 pad04[0x2C - 0x4];
    f32 f2c;
    u8 pad30[0x88 - 0x30];
    u32 x88;
} W6Flg;

extern f32 D_002BC0F0[];
extern f32 D_002BC120;
extern f32 D_002BC124;
extern s32 D_003044D0;
extern W6Ent16 D_003044D8[];

typedef struct {
    u32 flags;
    u8 pad004[0x40 - 0x4];
    f32 v40[3];
    u8 pad04c[0x4A4 - 0x4C];
    f32 f4a4;
} W6Fade;

typedef struct {
    u8 pad00[0xF];
    u8 b0f;
} W6Col;

typedef struct {
    u8 pad000[0x14C];
    W6Col *col;
} W6ColOwner;

typedef struct {
    u32 flags;
    u8 pad004[0xD0 - 0x4];
    u8 x0d0[0x154 - 0xD0];
    s32 x154;
    u8 pad158[0x39D - 0x158];
    u8 b39d;
} W6Reg;

typedef struct {
    u8 pad00[0x4C];
    u16 h4c;
} W6Sub2;

typedef struct {
    u8 pad00[0x48];
    s32 x48;
    u8 pad4c[0xC4 - 0x4C];
    f32 fc4;
    u8 pad0c8[0xD2 - 0xC8];
    u16 hd2;
} W6Stat;

typedef struct {
    u8 pad000[4];
    s32 x4;
    u8 pad008[0x10 - 0x8];
    u8 x10[0x6C - 0x10];
    W6Stat *p6c;
    u8 pad070[0x130 - 0x70];
    W6Sub2 *sub;
    u8 pad134[0x164 - 0x134];
    s32 x164;
    u8 pad168[0x39C - 0x168];
    u8 b39c;
    u8 pad39d[0x3EA - 0x39D];
    u16 h3ea;
} W6Unit;

typedef struct {
    u64 bits;
    u8 pad08[8];
    f32 v10[4];
} W6Cmd;

typedef struct {
    u8 x0;
    u8 x1;
    u8 x2;
    u8 x3;
    u8 pad04[0x38 - 0x4];
    u16 h38;
    u8 pad3a[0x74 - 0x3A];
} W6SEnt;

typedef struct {
    u8 pad000[4];
    W6SEnt ent[10];
    u8 pad48c[0x492 - 0x48C];
    u8 b492[8];
    u8 pad49a[0x7D8 - 0x49A];
    u16 cnt[51];
    u8 pad83e[0x880 - 0x83E];
    u8 b880;
} W6Save;

typedef struct {
    u8 pad00[0x40];
    u8 b40;
    u8 pad41[0x48 - 0x41];
    s32 w48;
    u8 pad4c[0xF0 - 0x4C];
} W6Info;

extern f32 D_002BBDFC;
extern W6Save *D_00304BE8;

void func_001247e8(W6Fade *o);
void func_001dce90(s32 a);
void func_001586a8(s32 a);
void func_002675a8(f32 *d, f32 *s);
void func_00156260(W6Unit *u, f32 *v);

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
} W6Blob;

extern u32 D_00304B78;
extern f32 D_00304B7C;
extern W6Blob *D_0052AE5C; /* src/data/bss_0052.c: void *D_0052AE5C */
extern s32 D_0052AE54;
extern u32 D_002C5978;

f32 func_00176850(void);
void func_00139240(W6Unit *u, s32 a, s32 b, f32 x, f32 y, f32 z);
void func_001473a8(s32 a, s32 b, void *c);
void func_00155be0(void *p);
void func_001763f0(void *p);
void FlushCache(s32 mode);
s32 D_00F20000(s32 a, s32 b);
void func_0013a810(void);

u8 D_0052AD58[0x10] ALIGNED(8);
extern u8 D_0052AD68[];
extern u8 D_00304B48[];

void func_0013bde8(void *a, void *b, s32 n);
void func_0011f130(void *a, s32 b);
s32 func_0013be00(void *a);
void func_00141b10(s32 i, W6Info *info);
void func_0013bef0(void);
void func_0014f778(void);
void func_0014f828(void);
void func_0014f830(s32 a, s32 b, s32 c, s32 d, void (*e)(void), void (*f)(void), void (*g)(void), s32 h, s32 i);

extern W6Chan D_00525368[]; /* src/data/bss_0052.c: M2C_UNK D_00525368 */
extern s32 D_003041E4[][3][3];
extern u32 D_00304318[];
extern u8 D_00720000[];

s32 func_00120748(s32 a, s32 b, void (*c)(void), s32 d);
void func_001330e8(void);
void func_0011ef10(s32 a, void (*b)(void));
void func_001334f8(void);
void func_00133520(void);

s32 func_00130040(W6Obj *o, s32 i) {
    if (o->s1d0.p == 0) {
        return 0;
    }
    return (o->s1d0.p[i] & 0xFFF) != 0xFFF;
}

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

W6Ent *func_00130340(W6Obj *o, f32 x) {
    W6Ent *e;
    o->count = 0;
    e = func_001302d0(o, func_00130270(o), 0.0f, x);
    o->u160.f.b0 = 1;
    return e;
}

void func_00131438(W6Obj *o) {
    o->f170 = 0.0f;
    o->f284 = 1.0f;
    o->u160.w = 0;
    o->count = 0;
    o->s1e0.a = 0;
    func_00130660(o, o->x0d0, 0, o->f170, o->f170);
    o->u160.f.b1 = 0;
}

void func_00131498(W6Obj *o) {
    if (o->s1e0.a == 0) {
        o->s1e0 = o->s1d0;
    }
    func_001321a0(&o->s1d0);
    o->u160.f.b5 = 1;
}

void func_00131500(W6Obj *o) {
    if ((s32)(o->u160.bits >> 5) & 1) {
        o->s1d0 = o->s1e0;
        o->s1e0.a = 0;
        o->u160.f.b5 = 0;
    }
}
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
void func_00131c78(s32 a, s32 b) {
    W6Node *n = func_001320a8(a);
    if (b) {
        n->flags &= ~2;
    } else {
        n->flags |= 2;
    }
}

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

s32 func_00131f40(s32 a, s32 b) {
    D_0052535C = a;
    D_00525354 = D_005252A8;
    D_00525360 = b;
    return func_00131e40(-1);
}
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

s32 func_001331d8(s32 i, s32 j, void (*cb)(void)) {
    W6Chan *c = &D_00525368[i];
    s32 r;
    if (c->x0 == j) {
        if (cb) {
            cb();
        }
        r = -1;
    } else {
        c->x18 = (s32)cb;
        c->x0 = j;
        D_00304BE8->b492[i] = j;
        r = func_00120748(D_003041E4[i][j][0], c->x8, func_001330e8, 0);
    }
    return r;
}

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

void func_00133628(void) {
    s32 p = (s32)D_00720000;
    s32 i;
    for (i = 0; i < 7; i++) {
        D_00525368[i].x8 = p;
        D_00525368[i].x0 = 0;
        D_00525368[i].xc = 0;
        D_00525368[i].x14 = D_00304318[i];
        p += (D_00304318[i] >> 4) << 4;
    }
    func_0011ef10(0x21728, func_001334f8);
    func_00133520();
}
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

void func_00133978(W6Mgr *m, s32 id) {
    W6Link *l;
    for (l = m->links; l != 0; l = l->next) {
        if (l->id == id) {
            func_00133920(m, l);
            break;
        }
    }
}
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

W6Pair *func_001357b8(void) {
    s32 v = D_0052A150;
    D_0052A150 = (v + 1) % 8;
    return &D_0052A110[v];
}

void func_00135800(W6Ch *c, f32 x, f32 t) {
    if (0.0f < t) {
        c->x64 = (x - c->x60) / t;
    } else {
        c->x60 = x;
        c->x64 = 0.0f;
    }
}

void func_00135978(W6Ch *c, s32 a, s32 b) {
    if (a-- > 0) {
        c->x38c |= 1 << a;
    }
    if (b-- > 0) {
        c->x390 |= 1 << b;
    }
}
void func_001359c0(W6Ch2 *c, s32 a, s32 b) {
    if (a-- > 0) {
        c->x38c &= ~(1 << a);
    }
    if (b-- > 0) {
        c->x390 &= ~(1 << b);
    }
}

void func_00135a10(W6Ch2 *c, s32 a) {
    if (a-- > 0) {
        c->x394 |= 1 << a;
    }
}

void func_00135a38(W6Ch2 *c, s32 a) {
    if (a-- > 0) {
        c->x394 &= ~(1 << a);
    }
}

f32 func_00135ca0(f32 x) {
    f32 r;
    if (D_002BC0F0[0] <= x) {
        return D_002BC120;
    }
    if (D_002BC0F0[1] < x) {
        r = D_002BC120 + D_002BC124 / x;
        if (r < 0.0f) {
            r = 0.0f;
        } else if (255.0f < r) {
            r = 255.0f;
        }
    } else {
        r = 255.0f;
    }
    return r;
}

s32 func_00137450(s32 id) {
    s32 i;
    for (i = 0; i < D_003044D0; i++) {
        if (D_003044D8[i].id == id) {
            return i;
        }
    }
    return -1;
}

s32 func_001375f0(W6Flg *f) {
    return !(f->flags & 4) && !(f->x88 & 0x20);
}

s32 func_00137718(W6Flg *f) {
    if (f->flags & 4) {
        return 0;
    }
    if (f->f2c == 0.0f) {
        return 0;
    }
    return 1;
}
void func_00137a20(W6Fade *o) {
    f32 d;
    s32 i;
    if (0.0f < o->f4a4) {
        d = o->f4a4 * D_002BBDFC;
        for (i = 0; i < 3; i++) {
            o->v40[i] -= d;
            if (o->v40[i] <= 0.0f) {
                o->v40[i] = 0.0f;
                o->f4a4 = 0.0f;
            }
        }
        if (o->f4a4 == 0.0f && (o->flags & 8)) {
            func_001247e8(o);
        }
    }
}

void func_00137c70(W6Reg *o) {
    W6Ent16 *e = &D_003044D8[D_003044D0++];
    e->x0 = (s32)o->x0d0;
    e->x4 = o->x154;
    e->id = (s32)o;
    if (o->flags & 0x20) {
        e->xc.w |= 1;
    } else {
        e->xc.w &= ~1;
    }
    e->xc.f.b1 = o->b39d;
}

void func_00137cf8(W6ColOwner *o) {
    W6Col *c = o->col;
    s32 v;
    if (c != 0 && (*(u32 *)o & 0x4000)) {
        v = c->b0f;
        if (v < 255) {
            v += 16;
            if (v > 255) {
                v = 255;
            }
            c->b0f = v;
        }
    }
}

void func_00138870(W6Unit *u) {
    u16 v = u->sub->h4c;
    u32 k;
    func_001dce90(v);
    k = v - 300;
    if (k < 200) {
        func_001586a8(7);
    }
    if (k < 51) {
        if (D_00304BE8->cnt[k] < 9999) {
            D_00304BE8->cnt[k]++;
        }
    }
}

s32 func_00138988(W6Unit *u) {
    s32 d = u->x164 - u->h3ea;
    if ((u32)d >= 10) {
        return 0;
    }
    return d % 5 + 1;
}

void func_00138c30(W6Unit *u, W6Cmd *c) {
    f32 v[4];
    func_002675a8(v, c->v10);
    v[3] = D_00308CDC->f2c * u->p6c->fc4;
    func_00156260(u, v);
    c->bits |= 2;
}
void func_00139408(W6Unit *u, s32 a) {
    W6Lim *c = D_00308CDC;
    f32 lo = c->h14;
    f32 t = lo + (c->h16 - lo) * u->p6c->fc4;
    f32 k = c->f18;
    func_00139240(u, a, 0, t * k, t, func_00176850() * 30.0f);
}

void func_00139c28(W6Unit *u, W6Kind *k) {
    u64 bits = k->bits;
    s32 n;
    s32 m;
    if (((bits >> 38) & 0xF) == 1) {
        n = u->p6c->hd2;
        if (n > 0) {
            m = (s32)(bits >> 32) & 0x1F;
            if (m != 0) {
                if (m >= 4) {
                    if (m >= 6) {
                        return;
                    }
                    n += 2;
                }
                u->b39c = (u->b39c + 1) & 1;
                func_001473a8(n + u->b39c, u->x4 + 1, u->x10);
            }
        }
    }
}

s32 func_0013aa60(void) {
    if (!((D_00304B78 >> 3) & 1)) {
        return 1;
    }
    return D_00304B7C <= 0.0f;
}

void func_0013b1a0(void) {
    if (D_0052AE5C->x8 - D_0052AE5C->x4 > 0) {
        func_00155be0((u8 *)D_0052AE5C + D_0052AE5C->x4);
    }
    if (D_0052AE5C->xc - D_0052AE5C->x8 > 0) {
        func_00155be0((u8 *)D_0052AE5C + D_0052AE5C->x8);
    }
    if (D_0052AE5C->x10 - D_0052AE5C->xc > 0) {
        func_001763f0((u8 *)D_0052AE5C + D_0052AE5C->xc);
    }
    FlushCache(2);
    D_0052AE54 = 4;
}

s32 func_0013b8f0(void) {
    if (((D_002C5978 >> 8) & 3) != 1) {
        if (D_00F20000(1, 0) != 0) {
            return 0;
        }
    }
    func_0013a810();
    D_002C5958 &= ~0x2000;
    D_00304B78 = 0;
    return 1;
}
s32 func_0013b958(u16 *p) {
    if (*p & 0x10) {
        func_0013bde8(D_0052AD58, D_00304B48, 4);
    }
    func_0011f130(D_0052AD68, 0);
    return func_0013be00(D_0052AD58) ? 0 : 4;
}

void func_0013bf20(void) {
    func_0014f830(40, 256, 0, 0, func_0013bef0, func_0014f778, func_0014f828, 0, 0);
}

void func_0013bf90(s32 on) {
    if (on) {
        D_00304BE8->b880 = 1;
    } else {
        D_00304BE8->b880 = 0;
    }
}

void func_0013c078(void) {
    W6Info info;
    W6SEnt *e;
    s32 i;
    for (i = 0; i < 10; i++) {
        e = &D_00304BE8->ent[i];
        func_00141b10(i, &info);
        e->x1 = info.b40;
        if (e->x3 < info.w48) {
            e->h38 = 0;
            e->x3 = info.w48;
        }
    }
}
