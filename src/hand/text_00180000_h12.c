/* ppp manager and component callbacks, by hand (worker 12). */
#include "common.h"

extern u8 D_00616040[];

/* D_00364130: 256 effect managers of 0xC0 bytes. */
#include "data/pieces/D_00364130.h"
typedef PppOwner_364130 PppOwner;
typedef PppMng_364130 PppMng;

typedef struct {
    u8 pad00[0x14];
    s32 flags;
} PppLink;

void func_0011d3c8(s32, s32, s32);
void func_00182788(PppMng *);
void func_00182840(PppMng *);

s32 func_00181410(void) {
    PppMng *m = D_00364130.pppMng;
    s32 i;

    for (i = 0; i < 256; i++, m++) {
        if ((m->st & 1) && !(m->st & 4) && m->unk98 < 0) {
            if (m->owner->unkFC != 0)
                func_0011d3c8(m->owner->unkFC, m->unkA8, 60);
            func_00182788(m);
            func_00182840(m);
            return 1;
        }
    }
    return 0;
}

void func_001827f0(PppMng *m) {
    if (m->link) {
        ((PppLink *) m->link)->flags &= ~1;
        ((PppLink *) m->link)->flags |= 2;
    }
    if (m->st & 1)
        m->st = (m->st & ~1) | 2;
}

/* A system with a table of modules; each module is a table of hooks. */
typedef struct PppSys PppSys;
typedef void (*PppSysFn)(PppSys *);
typedef struct {
    void *fn[8];
} PppModule;

typedef struct {
    u8 pad[0x9C];
    u8 unk9C;
} PppInst;

typedef struct {
    s32 unk0;
    PppInst *inst;  /* +0x4 */
    s32 time;       /* +0x8 */
    s32 unkC;
} PppSlotE;

struct PppSys {
    u8 pad00[0x44];
    f32 scale;         /* +0x44 */
    u8 pad48[0xC];
    s32 end;           /* +0x54 */
    s32 time;          /* +0x58 */
    s32 prev;          /* +0x5C */
    u8 pad60[4];
    s32 nmod;          /* +0x64 */
    s32 nslot;         /* +0x68 */
    u8 pad6C[8];
    s32 unk74;         /* +0x74 */
    PppModule **mods;  /* +0x78 */
    s32 pad7C;
    PppSlotE *slots;   /* +0x80 */
    u8 unk84;          /* +0x84 */
    u8 unk85;          /* +0x85 */
    u8 pad86[0x2A];
    u64 unkB0;         /* +0xB0 */
};

void func_001822f8(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nmod; i++) {
        PppSysFn fn = (PppSysFn) s->mods[i]->fn[4];
        if (fn)
            fn(s);
    }
}

void func_00182368(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nmod; i++) {
        PppSysFn fn = (PppSysFn) s->mods[i]->fn[5];
        if (fn)
            fn(s);
    }
}

void func_001823d8(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nmod; i++) {
        PppSysFn fn = (PppSysFn) s->mods[i]->fn[6];
        if (fn)
            fn(s);
    }
}

#include "ppp.h"

typedef void (*PppCompFn)(void *, PppEntry *);

/* A loaded program header: +0x20 is the offset in the object of the
 * per-component data pointers, +0x26 the component count, entries from
 * +0x28. */
typedef struct {
    u8 pad00[0x20];
    s32 dataoff;       /* +0x20 */
    s16 pad24;
    s16 n;             /* +0x26 */
    PppEntry ent[1];   /* +0x28 */
} PppProg;

typedef struct {
    s32 unk00, unk04;
    PppProg **prog;    /* +0x08 */
} PppObj;

/* The data pointer slots: the store must be able to alias the s16 count
 * (the original reloads it after the store). */
typedef union {
    void *p;
    s16 h;
} PppSlot;

void pppResetComponents(PppObj *obj) {
    PppProg *p = *obj->prog;
    PppSlot *d = (PppSlot *) ((u8 *) obj + p->dataoff);
    s32 i;

    for (i = 0; i < p->n; i++) {
        PppEntry *e = &p->ent[i];
        PppClass *c = e->cls;
        d->p = e->data;
        d++;
        if (c && c->reset)
            ((PppCompFn) c->reset)(obj, e);
    }
}

void pppConComponents(PppObj *obj) {
    PppProg *p = *obj->prog;
    PppSlot *d = (PppSlot *) ((u8 *) obj + p->dataoff);
    s32 i;

    for (i = 0; i < p->n; i++) {
        PppEntry *e = &p->ent[i];
        PppClass *c = e->cls;
        d->p = e->data;
        d++;
        if (c && c->con)
            ((PppCompFn) c->con)(obj, e);
    }
}

PppInst *func_00182588(PppSys *, PppSlotE *);

void func_001837a8(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nslot; i++) {
        PppSlotE *e = &s->slots[i];
        if (e->time <= s->time) {
            e->time = 0x7FFFFFFF;
            e->inst = func_00182588(s, e);
            e->inst->unk9C = 0;
        }
    }
}

extern s32 D_0061621C;
extern PppSys *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

s32 func_00183958(PppSys *s) {
    s32 t;

    D_00615E60 = s;
    if (D_0061621C != 0 || (s->unkB0 & 0xFF0000FF00ULL))
        return 0;
    t = s->time;
    s->prev = t;
    s->time = t + 0x1000;
    if (s->unk84 != 0) {
        if (s->unk85)
            return s->unk74 == 0;
        if (s->time > 0x6FFFFFFF) {
            s->time = 0x70000000;
            s->prev = 0x6FFFF000;
        }
        return 0;
    }
    return s->time >= s->end;
}

/* A block heap: blocks are linked both ways; "used" and the byte count at
 * +0xC are typed as pointers so their stores order like the original. */
typedef struct PppBlk {
    struct PppBlk *next;  /* +0x0 */
    struct PppBlk *prev;  /* +0x4 */
    struct PppBlk *used;             /* +0x8 */
    s32 pad;
} PppBlk;

typedef struct {
    PppBlk *unk0;
    PppBlk *first;  /* +0x4 */
    PppBlk *last;   /* +0x8 */
    PppBlk *unkC;
} PppHeap;

void func_00183a00(PppHeap *h, PppBlk *mem, s32 size) {
    h->first = mem;
    h->unk0 = NULL;
    h->last = (PppBlk *) ((u8 *) mem + size - 16);
    mem->prev = NULL;
    mem->next = h->last;
    mem->used = NULL;
    {
        PppBlk *l = h->last;
        PppBlk *f = h->first;
        l->used = (PppBlk *) 1;
        l->prev = f;
        l->next = NULL;
    }
    h->unkC = NULL;
}

void func_00183b20(PppHeap *h, u8 *p) {
    PppBlk *b = (PppBlk *) (p - 16);
    PppBlk *q;

    b->used = NULL;
    h->unk0 = b;
    h->unkC = (PppBlk *) ((s32) h->unkC - ((s32) b->next - (s32) b));
    q = b->prev;
    if (q != NULL && q->used == NULL) {
        q->next = b->next;
        b->next->prev = q;
        b = q;
    }
    {
        PppBlk *n = b->next;
        if (n->used == NULL) {
            b->next = n->next;
            n->next->prev = b;
        }
    }
}

#include "data/types/text_00180000_h12.h"

typedef struct {
    s32 unk0;
    s32 arg;     /* +0x4 */
} PppHookData;

extern PppHookFn *D_00616220;

void pppDrawHookDraw(PppHookObj *obj, PppHookData *data, PppEntry *e) {
    *(s32 *) ((u8 *) obj + e->offsets[0] + 0xA0) = data->arg;
    if (D_00616220) {
        PppHookFn fn = D_00616220[obj->hdr->hook];
        if (fn)
            fn(obj, data->arg);
    }
}

/* The object a program runs in: +0x0C is its frame counter. */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

/* A work-area word: float stores through it may alias the int frame
 * counters (the original reloads them after the stores). */
typedef union {
    f32 f;
    s32 i;
} PppWord;

typedef struct {
    s32 frame;
    s32 pad[2];
    f32 x, y, z;  /* +0xC */
} PppVtMimeKey;

typedef struct {
    PppWord x, y, z;
    s32 n;
} PppVtMime;

void pppVtMimeFrame(PppObject *obj, PppVtMimeKey *k, PppEntry *e) {
    PppVtMime *w = (PppVtMime *) ((u8 *) obj + e->offsets[0] + 0xA0);

    if (D_0061621C != 0 || (D_00615E60->unkB0 & 0xFF0000FF00ULL))
        return;
    w->y.f += w->z.f;
    w->x.f += w->y.f;
    if (k->frame == obj->frame) {
        w->x.f += k->x;
        w->y.f += k->y;
        w->z.f += k->z;
    }
}

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

void sceVu0UnitMatrix(PppMtx);
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
void sceVu0CopyMatrix(PppMtx, PppMtx);

typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;

extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */

typedef struct {
    s32 frame;
    f32 scale;  /* +0x4 */
    f32 max;    /* +0x8 */
} PppYSclKey;

void pppChrYSclXYZMatrixFrame(void *obj, PppYSclKey *k, PppEntry *e) {
    PppMtx m;
    f32 s;

    sceVu0UnitMatrix(m);
    s = D_00615E60->scale;
    m[1][1] = s + s * k->scale;
    if (k->max < m[1][1])
        m[1][1] = k->max;
    m[0][0] = m[1][1] = m[2][2];
    sceVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
}

typedef struct {
    s32 pad[3];
    PppWord w0;  /* +0x0C */
    s32 w1;      /* +0x10 */
    s32 pad2;
    f32 a, b, c; /* +0x18 */
} PppWind;

void pppEiWindFunCon(void *obj, PppEntry *e) {
    PppWind *w = (PppWind *) ((u8 *) obj + e->offsets[0] + 0xA0);

    w->w0.i = 0;
    w->w1 = 0;
    w->a = w->b = w->c = w->w0.f;
}

/* Pointer-valued fields below are typed s32 so that loads and stores
 * through them alias like the original. */
typedef struct {
    u8 pad[0x12];
    u16 unk12;
} PppAnmHdr;

typedef struct {
    s32 hdr;   /* a PppAnmHdr * */
    s32 unk4;
} PppAnmEnt;

typedef struct {
    u8 pad[0x14];
    PppAnmEnt *anms;   /* +0x14 */
} PppAnmSet;

extern PppAnmSet *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */

typedef struct {
    s32 frame;
    s32 id;    /* +0x4 */
} PppAnmKey;

typedef struct {
    s32 p0;
    s32 cur;  /* +0x4 */
    u16 unk8;
    u8 unkA;
} PppAnmWork;

void func_00191fc8(PppObject *obj, PppAnmKey *k, PppEntry *e) {
    PppAnmWork *w = (PppAnmWork *) ((u8 *) obj + e->offsets[0] + 0xA0);
    PppAnmEnt *a;

    if (k->frame != obj->frame)
        return;
    w->p0 = (s32) obj + e->offsets[1] + 0xA0;
    if (k->id == 0xFFFF) {
        w->cur = 0;
        return;
    }
    a = &D_00615E64->anms[k->id];
    if ((s32) a != w->cur) {
        u16 t;

        w->cur = (s32) a;
        t = ((PppAnmHdr *) a->hdr)->unk12;
        w->unkA = 0;
        w->unk8 = t;
    }
}

void func_001a6518(PppAnmWork *, PppAnmEnt *);

void func_001924a8(PppObject *obj, PppAnmKey *k, PppEntry *e) {
    PppAnmWork *w = (PppAnmWork *) ((u8 *) obj + e->offsets[0] + 0xA0);
    PppAnmEnt *a;

    if (k->frame != obj->frame)
        return;
    w->p0 = (s32) obj + e->offsets[1] + 0xA0;
    if (k->id == 0xFFFF) {
        w->cur = 0;
        return;
    }
    a = &D_00615E64->anms[k->id];
    if ((s32) a == w->cur)
        return;
    func_001a6518(w, a);
}

void func_00192708(PppObject *obj, PppAnmKey *k, PppEntry *e) {
    PppAnmWork *w = (PppAnmWork *) ((u8 *) obj + e->offsets[0] + 0xA0);
    PppAnmEnt *a;

    if (k->frame != obj->frame)
        return;
    w->p0 = (s32) obj + e->offsets[1] + 0xA0;
    if (k->id == 0xFFFF) {
        w->cur = 0;
        return;
    }
    a = &D_00615E64->anms[k->id];
    if ((s32) a != w->cur) {
        u16 t;

        w->cur = (s32) a;
        t = ((PppAnmHdr *) a->hdr)->unk12;
        w->unkA = 0;
        w->unk8 = t;
    }
}

typedef struct {
    u8 pad[0x10];
    u8 unk10[0x10];
    f32 unk20;
    s32 unk24;
    f32 unk28;
    u16 unk2C;
} PppCbSrc2;

typedef struct {
    PppCbSrc2 *src;
    s32 unk4;
    void *tbl;
    f32 unkC;
    u16 unk10;
    u16 unk12;
    void *sub;
} PppCbArg2;

void func_001a6550(PppCbArg2 *, s32);

void func_001936c0(PppCbSrc2 *p) {
    PppCbArg2 a;

    a.unk4 = p->unk24;
    a.unkC = p->unk20;
    a.unk10 = (u32) p->unk28;
    a.src = p;
    a.unk12 = p->unk2C;
    a.tbl = D_00616040;
    a.sub = p->unk10;
    func_001a6550(&a, 0);
}

typedef struct {
    s32 frame;
    PppWord a, b;
} PppKeyF2;

typedef struct {
    PppWord a;
    s32 tgt;
} PppHitBall;

typedef struct {
    PppWord a, b;
    s32 tgt;
} PppGrvTgt;

void pppKeGrvTgtFrame(PppObject *obj, PppKeyF2 *k, PppEntry *e) {
    if (obj->frame == k->frame) {
        PppGrvTgt *w = (PppGrvTgt *) ((u8 *) obj + e->offsets[1] + 0xA0);
        w->a.f = k->a.f;
        w->b.f = k->b.f;
        w->tgt = (s32) obj + e->offsets[0] + 0xA0;
    }
}

void pppKeHitBallFrame(PppObject *obj, PppKeyF2 *k, PppEntry *e) {
    if (obj->frame == k->frame) {
        PppHitBall *w = (PppHitBall *) ((u8 *) obj + e->offsets[1] + 0xA0);
        w->tgt = (s32) obj + e->offsets[0] + 0xA0;
        w->a.f = k->a.f;
    }
}

extern PppMtx D_00615FC0;

void pppKeDMatFrame(void *obj, void *k, PppEntry *e) {
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[1] + 0xA0);

    sceVu0MulMatrix(D_00615E68->m2, D_00615FC0, D_00615E68->m);
    sceVu0CopyMatrix(w, D_00615E68->m2);
    sceVu0MulMatrix(D_00615E68->m2, (f32 (*)[4]) D_00616040, D_00615E68->m2);
}

#include "data/types/text_00180000_h12_p.h"
#include "data/data_0037.h"
