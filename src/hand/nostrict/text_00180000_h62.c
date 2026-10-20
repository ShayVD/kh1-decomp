/* ppp classes and manager helpers, by hand (worker 62). Built without
 * strict aliasing (see src/hand/nostrict). */
#include "ppp.h"
#include "data/bss_0061.h"


#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

typedef struct {
    s32 frame;  /* +0x0 */
    s32 dst;    /* +0x4 */
    f32 amp[3]; /* +0x8 */
    u8 twice;   /* +0x14 */
} PppRandFVKey;

typedef struct {
    u8 pad[0xB0];
    u64 flags; /* +0xB0 */
} PppSystem;

extern s32 D_0061621C;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
extern f32 D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */

f32 func_00187df0(f32, f32);
f32 func_00187f98(f32, f32);
f32 func_00188148(f32, f32);

static inline f32 vu0Rand(void) {
    f32 r;

    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=r"(r)
        :
        : "$8");
    return r;
}

typedef struct {
    s32 frame;
    s32 dst;
    s32 amp[3]; /* +0x8 */
    u8 twice;   /* +0x14 */
} PppRandIVKey;

typedef struct {
    s32 frame;
    s32 dst;
    s8 amp[4]; /* +0x8 */
    u8 twice;  /* +0xC */
} PppRandCVKey;

typedef struct {
    s32 frame;
    s32 dst;
    s16 amp[4]; /* +0x8 */
    u8 twice;   /* +0x10 */
} PppRandHCVKey;

s32 func_001882f8(s32, f32);
s32 func_00188498(s32, f32);
s32 func_00188640(s32, f32);
s8 func_001887e8(s8, f32);
s8 func_001889b0(s8, f32);
s8 func_00188b78(s8, f32);
s16 func_00188d40(s16, f32);
s16 func_00188f08(s16, f32);
s16 func_001890d0(s16, f32);


/* D_00615E64: the current texture/vertex system; D_00615E68: the current
 * program object. */
typedef struct {
    s16 x, y, z;
} VtxS16;

typedef struct {
    s16 slot;  /* +0x0 */
    s16 n;     /* +0x2 */
    u16 *map;  /* +0x4 */
} VtxMap;

typedef struct {
    u32 flags;  /* +0x0 */
    u8 pad04[0x12];
    u16 unk16;  /* +0x16 */
} DMdl;

typedef struct {
    s32 n;       /* +0x0 */
    s32 pad04[4];
    VtxS16 *vtx; /* +0x14 */
    s32 pad18;
    DMdl *mdl;   /* +0x1C */
    s32 unk20;   /* +0x20 */
} VtxSlot;

typedef struct {
    u8 pad00[0x10];
    VtxSlot *slots; /* +0x10 */
    void *p14;
    VtxMap *maps;   /* +0x18 */
} VtxSys;

typedef struct {
    u8 pad00[0x10];
    u8 m10[0x40];   /* +0x10 */
    u8 m50[0x40];   /* +0x50 */
    VtxS16 *vtx;    /* +0x90 */
    s32 unk94;      /* +0x94 */
} VtxCur;

extern VtxSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern VtxCur *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern s32 D_00616234;
void *func_0017f958(VtxSys *, s32);

typedef struct PNode {
    struct PNode *next; /* +0x0 */
    s32 pad[3];
    s32 val;            /* +0x10 */
} PNode;

typedef struct {
    PNode *node; /* +0x0 */
    s32 unk4;    /* +0x4 */
    s32 val;     /* +0x8 */
    s16 unkC;    /* +0xC */
    s8 idx;      /* +0xE */
    u8 padF;
} PSlot;

typedef struct {
    u8 pad[0x108];
    f32 unk108;
} POwner;

typedef struct {
    u8 pad00[0x54];
    s32 end;       /* +0x54 */
    s32 time;      /* +0x58 */
    u8 pad5C[8];
    s32 nmod;      /* +0x64 */
    s32 nslot;     /* +0x68 */
    u8 pad6C[4];
    PNode *list;   /* +0x70 */
    s32 unk74;     /* +0x74 */
    s32 *mods;     /* +0x78 */
    s32 *slotdata; /* +0x7C */
    PSlot *slots;  /* +0x80 */
    u8 unk84;      /* +0x84 */
    u8 unk85;      /* +0x85 */
    u8 pad86[6];
    POwner *owner; /* +0x8C */
    u8 pad90[0xC];
    s32 unk9C;     /* +0x9C */
    u8 padA0[0xC];
    f32 unkAC;     /* +0xAC */
} PSys;

void func_001822f8(PSys *);

void func_00182c10(PSys *o, s32 *d, s32 flag) {
    s32 *p = d;
    s32 a, b, c;
    s32 *q, *r;
    PNode *n;
    PSlot *e;
    u8 i;

    *(PSys **) &D_00615E60 = o;
    o->end = *p++;
    a = *p++;
    b = *p++;
    c = *p++;
    q = (s32 *) ((u8 *) d + b);
    r = (s32 *) ((u8 *) d + c);
    if (a & 1)
        o->unk84 = 1;
    else
        o->unk84 = 0;
    o->nmod = *q++;
    o->mods = q;
    o->nslot = *r++;
    o->slotdata = r;
    if (o->nslot)
        o->slots = func_0017f958(D_00615E64, o->nslot << 4);
    else
        o->slots = 0;
    n = (PNode *) p;
    if (n->next)
        o->list = 0;
    o->time = 0;
    o->unk85 = 0;
    o->list = o->nslot ? n : 0;
    o->unk74 = 0;
    i = 0;
    e = o->slots;
    do {
        e->node = n;
        e->val = n->val; 
        e->idx = i++; 
        e->unk4 = 0; 
        e->unkC = 0; 
        n = n->next;
        e++;
    } while (n);
    if (flag)
        func_001822f8(o);
    o->unk9C = 0;
    o->unkAC = o->owner->unk108;
}

typedef struct {
    s32 frame;
    s16 map;     /* +0x4 */
    u8 count;    /* +0x6 */
    u8 interval; /* +0x7 */
    u8 mode;     /* +0x8 */
} VtxApKey;

typedef struct {
    u16 idx;   /* +0x0 */
    u16 timer; /* +0x2 */
} VtxApWork;

void func_00184918(PppObject *, VtxApKey *, VtxS16 *);


void pppVertexApFrame(PppObject *obj, VtxApKey *key, PppEntry *e) {
    VtxS16 v;
    VtxApWork *w = PPP_WORK(VtxApWork, obj, e, 0);
    VtxMap *m;
    VtxS16 *vtx;
    s32 n;
    u16 i;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL) || D_00616234 != 0)
        return;
    if (key->map < 0)
        return;
    if (w->timer == 0) {
        m = &D_00615E64->maps[key->map];
        vtx = D_00615E68->vtx;
        if (vtx == 0)
            vtx = D_00615E64->slots[m->slot].vtx;
        n = key->count;
        switch (key->mode) {
        case 0:
            while (n--) {
                if (w->idx >= m->n)
                    w->idx = 0;
                i = w->idx++;
                v = vtx[m->map[i]];
                func_00184918(obj, key, &v);
            }
            break;
        case 1:
            while (n--) {
                v = vtx[m->map[(s32) (vu0Rand() * m->n)]];
                func_00184918(obj, key, &v);
            }
            break;
        }
        w->timer = key->interval;
    }
    w->timer--;
}

void func_00184918(PppObject *, VtxApKey *, VtxS16 *);

void func_00184cb8(PppObject *, VtxApKey *, VtxS16 *);

void pppVertexApLcFrame(PppObject *obj, VtxApKey *key, PppEntry *e) {
    VtxS16 v;
    VtxApWork *w = PPP_WORK(VtxApWork, obj, e, 0);
    VtxMap *m;
    VtxS16 *vtx;
    s32 n;
    u16 i;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL) || D_00616234 != 0)
        return;
    if (key->map < 0)
        return;
    if (w->timer == 0) {
        m = &D_00615E64->maps[key->map];
        vtx = D_00615E68->vtx;
        if (vtx == 0)
            vtx = D_00615E64->slots[m->slot].vtx;
        n = key->count;
        switch (key->mode) {
        case 0:
            while (n--) {
                if (w->idx >= m->n)
                    w->idx = 0;
                i = w->idx++;
                v = vtx[m->map[i]];
                func_00184cb8(obj, key, &v);
            }
            break;
        case 1:
            while (n--) {
                v = vtx[m->map[(s32) (vu0Rand() * m->n)]];
                func_00184cb8(obj, key, &v);
            }
            break;
        }
        w->timer = key->interval;
    }
    w->timer--;
}

void func_00184918(PppObject *, VtxApKey *, VtxS16 *);

void func_00185000(PppObject *, VtxApKey *, u16);

void pppVertexApAtFrame(PppObject *obj, VtxApKey *key, PppEntry *e) {
    VtxApWork *w = PPP_WORK(VtxApWork, obj, e, 0);
    VtxMap *m;
    s32 n;
    u16 i;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL) || D_00616234 != 0)
        return;
    if (key->map < 0)
        return;
    if (w->timer == 0) {
        m = &D_00615E64->maps[key->map];
        n = key->count;
        switch (key->mode) {
        case 0:
            while (n--) {
                if (w->idx >= m->n)
                    w->idx = 0;
                i = w->idx++;
                func_00185000(obj, key, i);
            }
            break;
        case 1:
            while (n--) {
                func_00185000(obj, key, (s32) (vu0Rand() * m->n));
            }
            break;
        }
        w->timer = key->interval;
    }
    w->timer--;
}

typedef struct {
    s32 frame;
    s32 from; /* +0x4 */
    s32 to;   /* +0x8 */
} MKey;

typedef struct {
    f32 t;       /* +0x0 */
    f32 y, z;
    VtxS16 *buf; /* +0xC */
} MWork;


void pppVtMimeDraw(PppObject *obj, MKey *key, PppEntry *e) {
    MWork *w;
    VtxSys *sys;
    VtxS16 *a, *b, *o;
    s32 n;

    if (key->from == 0xFFFF && key->to == 0xFFFF)
        return;
    w = PPP_WORK(MWork, obj, e, 0);
    sys = D_00615E64;
    a = sys->slots[key->from].vtx;
    b = sys->slots[key->to].vtx;
    n = sys->slots[key->from].n;
    if (w->buf == 0)
        w->buf = func_0017f958(sys, n * 6);
    o = w->buf;
    while (n--) {
        o->x = (b->x - a->x) * w->t + a->x;
        o->y = (b->y - a->y) * w->t + a->y;
        o->z = (b->z - a->z) * w->t + a->z;
        o++;
        a++;
        b++;
    }
    D_00615E68->vtx = w->buf;
}

/* The pppDrawMdl* draw callbacks fill a DParam and hand it to
 * func_001aaf88 with the slot's model. */
typedef struct {
    s32 flags;  /* +0x00 */
    void *p04;  /* +0x04 */
    u16 h08;    /* +0x08 */
    u8 b0A;     /* +0x0A */
    s32 w0C;    /* +0x0C */
    union {
        u64 d;
        s32 w[2];
    } d10;      /* +0x10 */
    u8 r, g, b, a; /* +0x18 */
    s32 w1C;    /* +0x1C */
    void *p20;  /* +0x20 */
    void *p24;  /* +0x24 */
    void *p28;  /* +0x28 */
    void *p2C;  /* +0x2C */
    s32 w30;    /* +0x30 */
    s32 w34;    /* +0x34 */
    s32 w38;    /* +0x38 */
    s32 w3C;    /* +0x3C */
    s32 w40;    /* +0x40 */
    s32 w44;    /* +0x44 */
    s32 w48;    /* +0x48 */
    u8 b4C;     /* +0x4C */
    u8 b4D;     /* +0x4D */
    u8 pad4E[0x12];
} DParam;

typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u16 h8;   /* +0x8 */
} DKey;

typedef struct {
    u8 pad[8];
    u8 r, g, b, a; /* +0x8 */
} DBSWork;

extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern s32 D_00616224;
s32 func_001aaf88(DMdl *, DParam *, s32);

void pppDrawMdlBSDraw(PppObject *obj, DKey *key, PppEntry *e) {
    DParam p;
    DBSWork *w;
    VtxSlot *s;
    DMdl *m;
    VtxCur *cur;
    u8 r, g, b;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DBSWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    if (m->flags & 1)
        p.flags = 128;
    else
        p.flags = 12;
    if (!(m->flags & 2))
        p.flags |= 16;
/*P*/
    r = w->r;
    p.h08 = m->unk16;
    cur = D_00615E68;
    g = w->g;
    b = w->b;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = (s32) cur->vtx;
    p.w3C = cur->unk94;
    p.p04 = D_00616240;
    p.w0C = 0;
    p.r = r;
    p.g = g;
    p.b = b;
    p.d10.d = 0;
    p.w40 = 0;
    p.p20 = cur->m50;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = cur->m10;
    p.w34 = D_00616224;
    p.w44 = 0;
    p.b4C = 0;
    p.b4D = 0;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

typedef struct {
    u16 r, g, b;
    s16 a;
} DSemiWork;

void pppDrawMdlSemiDraw(PppObject *obj, DKey *key, PppEntry *e) {
    DParam p;
    DSemiWork *w;
    VtxSlot *s;
    DMdl *m;
    VtxCur *cur;
    u16 r, g, b;
    u16 h;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DSemiWork, obj, e, 0);
    p.a = w->a >> 7;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 128;
    if (!(m->flags & 2))
        p.flags = 144;
    h = key->h8;
    p.b0A = 0;
    p.w1C = 0;
    cur = D_00615E68;
    r = w->r;
    g = w->g;
    b = w->b;
    p.h08 = h;
    p.w38 = (s32) cur->vtx;
    p.w3C = cur->unk94;
    p.p04 = D_00616240;
    p.r = r >> 7;
    p.g = g >> 7;
    p.b = b >> 7;
    p.p20 = cur->m50;
    p.p24 = D_00616140;
    p.w0C = 0;
    p.d10.d = 0;
    p.w40 = 0;
    p.w44 = 0;
    p.p28 = D_00616100;
    p.w34 = D_00616224;
    p.p2C = cur->m10;
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

typedef struct {
    f32 a, b, c, d;
} DTsWork2;

void pppDrawMdlTsDraw(PppObject *obj, DKey *key, PppEntry *e) {
    DParam p;
    DBSWork *w;
    VtxSlot *s;
    DMdl *m;
    DTsWork2 *w2;
    VtxCur *cur;
    u8 r, g, b;

    w2 = PPP_WORK(DTsWork2, obj, e, 2);
    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DBSWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    if (m->flags & 1)
        p.flags = 128;
    else
        p.flags = 12;
    if (!(m->flags & 2))
        p.flags |= 16;
    p.h08 = m->unk16;
    r = w->r;
    p.b0A = 0;
    g = w->g;
    cur = D_00615E68;
    p.w1C = 0;
    p.w38 = (s32) cur->vtx;
    p.w3C = cur->unk94;
    p.p04 = D_00616240;
    p.w0C = 0;
    p.r = r;
    p.w40 = 0;
    p.g = g;
    b = w->b;
    p.b = b;
    p.d10.w[0] = w2->a * 65536.0f;
    p.w44 = 0;
    p.d10.w[1] = w2->d * 65536.0f;
    p.p20 = cur->m50;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = cur->m10;
    p.b4C = 0;
    p.b4D = 0;
    p.w34 = D_00616224;
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

void pppRandFVFrame(PppObject *obj, PppRandFVKey *key, PppEntry *e) {
    f32 *w;
    f32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r += vu0Rand();
        else
            r += r;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (f32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (f32 *) &D_00575A00;
    v[0] += func_00187df0(key->amp[0], *w);
    v[1] += func_00187df0(key->amp[1], *w);
    v[2] += func_00187df0(key->amp[2], *w);
}

void pppRandUpFVFrame(PppObject *obj, PppRandFVKey *key, PppEntry *e) {
    f32 *w;
    f32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r = (r + vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (f32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (f32 *) &D_00575A00;
    v[0] += func_00187f98(key->amp[0], *w);
    v[1] += func_00187f98(key->amp[1], *w);
    v[2] += func_00187f98(key->amp[2], *w);
}

void pppRandDownFVFrame(PppObject *obj, PppRandFVKey *key, PppEntry *e) {
    f32 *w;
    f32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        r = -r;
        if (key->twice)
            r = (r - vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (f32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (f32 *) &D_00575A00;
    v[0] += func_00188148(key->amp[0], *w);
    v[1] += func_00188148(key->amp[1], *w);
    v[2] += func_00188148(key->amp[2], *w);
}

void pppRandIVFrame(PppObject *obj, PppRandIVKey *key, PppEntry *e) {
    f32 *w;
    s32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r += vu0Rand();
    else
        r += r;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (s32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (s32 *) &D_00575A00;
    v[0] += func_001882f8(key->amp[0], *w);
    v[1] += func_001882f8(key->amp[1], *w);
    v[2] += func_001882f8(key->amp[2], *w);
}

void pppRandUpIVFrame(PppObject *obj, PppRandIVKey *key, PppEntry *e) {
    f32 *w;
    s32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r = (r + vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (s32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (s32 *) &D_00575A00;
    v[0] += func_00188498(key->amp[0], *w);
    v[1] += func_00188498(key->amp[1], *w);
    v[2] += func_00188498(key->amp[2], *w);
}

void pppRandDownIVFrame(PppObject *obj, PppRandIVKey *key, PppEntry *e) {
    f32 *w;
    s32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    r = -r;
    if (key->twice)
        r = (r - vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (s32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (s32 *) &D_00575A00;
    v[0] += func_00188640(key->amp[0], *w);
    v[1] += func_00188640(key->amp[1], *w);
    v[2] += func_00188640(key->amp[2], *w);
}

void pppRandCVFrame(PppObject *obj, PppRandCVKey *key, PppEntry *e) {
    f32 *w;
    u8 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r += vu0Rand();
    else
        r += r;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u8 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u8 *) &D_00575A00;
    v[0] += func_001887e8(key->amp[0], *w);
    v[1] += func_001887e8(key->amp[1], *w);
    v[2] += func_001887e8(key->amp[2], *w);
    v[3] += func_001887e8(key->amp[3], *w);
}

void pppRandUpCVFrame(PppObject *obj, PppRandCVKey *key, PppEntry *e) {
    f32 *w;
    u8 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r = (r + vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u8 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u8 *) &D_00575A00;
    v[0] += func_001889b0(key->amp[0], *w);
    v[1] += func_001889b0(key->amp[1], *w);
    v[2] += func_001889b0(key->amp[2], *w);
    v[3] += func_001889b0(key->amp[3], *w);
}

void pppRandDownCVFrame(PppObject *obj, PppRandCVKey *key, PppEntry *e) {
    f32 *w;
    u8 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    r = -r;
    if (key->twice)
        r = (r - vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u8 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u8 *) &D_00575A00;
    v[0] += func_00188b78(key->amp[0], *w);
    v[1] += func_00188b78(key->amp[1], *w);
    v[2] += func_00188b78(key->amp[2], *w);
    v[3] += func_00188b78(key->amp[3], *w);
}

void pppRandHCVFrame(PppObject *obj, PppRandHCVKey *key, PppEntry *e) {
    f32 *w;
    u16 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r += vu0Rand();
    else
        r += r;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u16 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u16 *) &D_00575A00;
    v[0] += func_00188d40(key->amp[0], *w);
    v[1] += func_00188d40(key->amp[1], *w);
    v[2] += func_00188d40(key->amp[2], *w);
    v[3] += func_00188d40(key->amp[3], *w);
}

void pppRandUpHCVFrame(PppObject *obj, PppRandHCVKey *key, PppEntry *e) {
    f32 *w;
    u16 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r = (r + vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u16 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u16 *) &D_00575A00;
    v[0] += func_00188f08(key->amp[0], *w);
    v[1] += func_00188f08(key->amp[1], *w);
    v[2] += func_00188f08(key->amp[2], *w);
    v[3] += func_00188f08(key->amp[3], *w);
}

void pppRandDownHCVFrame(PppObject *obj, PppRandHCVKey *key, PppEntry *e) {
    f32 *w;
    u16 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    r = -r;
    if (key->twice)
        r = (r - vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u16 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u16 *) &D_00575A00;
    v[0] += func_001890d0(key->amp[0], *w);
    v[1] += func_001890d0(key->amp[1], *w);
    v[2] += func_001890d0(key->amp[2], *w);
    v[3] += func_001890d0(key->amp[3], *w);
}
