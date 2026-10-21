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

f32 func_0019baf8(void);

s8 func_0019bb40(u8 a) {
    f32 f = func_0019baf8();

    return (f32) (a * 2) * f - (f32) (a >> 1);
}

typedef struct {
    u8 pad[0x50];
    s32 unk50;
    s32 unk54;
    s32 unk58;
} PppBb98A;

typedef struct {
    u8 pad[0xC9];
    u8 unkC9;
    u8 padCA[2];
    u8 unkCC;
} PppBb98B;

s32 func_0019bb98(PppBb98A *p, PppBb98B *q) {
    if (p->unk50 == 0)
        return 0;
    if ((u8) (q->unkCC - 1) < 2 && p->unk54 == 0)
        return 0;
    if (q->unkC9 != 0 && p->unk58 == 0)
        return 0;
    return 1;
}

extern PppMtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */

void func_0019cfc0(PppMtx out, PppBb98B *q, PppMtx m) {
    if (q->unkCC != 0)
        return;
    sceVu0MulMatrix(out, m, D_00615E68->m);
    sceVu0MulMatrix(out, D_00615EB0, out);
}

typedef unsigned int u128 __attribute__((mode(TI)));

PppMtx D_0061E2D0 ALIGNED(16);
typedef struct {
    PppMtx m;   /* +0x00 */
    u128 q;     /* +0x40 */
    s32 i[4];   /* +0x50 */
    s16 h[2];   /* +0x60 */
} PppMegaBirth;

void pppRyjMegaBirthCon(void *obj, PppEntry *e) {
    PppMegaBirth *w = (PppMegaBirth *) ((u8 *) obj + e->offsets[2] + 0xA0);

    sceVu0UnitMatrix(w->m);
    w->q = 0;
    w->i[0] = 0;
    w->i[1] = 0;
    w->i[2] = 0;
    w->i[3] = 0;
    w->h[0] = 0;
    w->h[1] = 0;
    sceVu0UnitMatrix(D_0061E2D0);
}

#include "data/types/text_00180000_h12_p.h"



#include "data/pieces/D_0035E710.h"

PppTblEnt *func_0019dfc8(s32 key) {
    PppTblEnt *e = D_0035E710.ent;
    PppTblEnt *r = NULL;
    s32 i;

    if (e != NULL) {
        for (i = 0; i < D_0035E710.hdr->n; i++, e++) {
            if (key == e->key) {
                r = e;
                break;
            }
        }
    }
    return r;
}

s32 func_0019e028(void *, void *);
s32 func_0019e108(void *, void *);
s32 func_0019e1e8(void *, void *);

void pppRyjMegaPlaceShapeFrame(void *obj, void *k, PppEntry *e) {
    u8 *w = (u8 *) obj + e->offsets[1] + 0xA0;

    if (*w == 0) {
        if (func_0019e028((u8 *) obj + e->offsets[0] + 0xA0, k))
            *w = 1;
    }
}

void pppRyjMegaPlaceModelFrame(void *obj, void *k, PppEntry *e) {
    u8 *w = (u8 *) obj + e->offsets[1] + 0xA0;

    if (*w == 0) {
        if (func_0019e108((u8 *) obj + e->offsets[0] + 0xA0, k))
            *w = 1;
    }
}

void pppRyjMegaPlaceLampFrame(void *obj, void *k, PppEntry *e) {
    u8 *w = (u8 *) obj + e->offsets[1] + 0xA0;

    if (*w == 0) {
        if (func_0019e1e8((u8 *) obj + e->offsets[0] + 0xA0, k))
            *w = 1;
    }
}

f32 func_0019f100(void);

s8 func_0019f148(u8 a) {
    f32 f;

    func_0019f100();
    f = func_0019f100();
    return (f32) (a * 2) * f - (f32) (a >> 1);
}

typedef struct {
    u8 pad[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
} PppF1a8A;

typedef struct {
    u8 pad[0x101];
    u8 unk101;
    u8 pad102[4];
    u8 unk106;
} PppF1a8B;

s32 func_0019f1a8(PppF1a8A *p, PppF1a8B *q) {
    if (p->unk10 == 0)
        return 0;
    if (q->unk106 != 0 && p->unk14 == 0)
        return 0;
    if (q->unk101 != 0 && p->unk18 == 0)
        return 0;
    return 1;
}

void func_00122768(void *);

void pppRyjLightDes(void *obj, PppEntry *e) {
    void **w = (void **) ((u8 *) obj + e->offsets[2] + 0xA0);

    if (*w) {
        func_00122768(*w);
        *w = NULL;
    }
}

typedef struct {
    PppMtx out;   /* +0x00 */
    PppMtx local; /* +0x40 */
} PppDttWork;

void pppRyjDrawMatrixWorldDttFrame(void *obj, void *k, PppEntry *e) {
    PppDttWork *w = (PppDttWork *) ((u8 *) obj + e->offsets[1] + 0xA0);

    sceVu0MulMatrix(D_00615E68->m2, w->local, D_00615E68->m);
    sceVu0MulMatrix(D_00615E68->m2, D_00615EB0, D_00615E68->m2);
    sceVu0CopyMatrix(w->out, D_00615E68->m2);
    sceVu0MulMatrix(D_00615E68->m2, (f32 (*)[4]) D_00616040, D_00615E68->m2);
}

f32 func_001a2178(void);

s8 func_001a21c0(u8 a) {
    f32 f;

    f = func_001a2178();
    return (f32) (a * 2) * f - (f32) (a >> 1);
}

typedef struct {
    s32 unk0;
    s32 unk4;
} PppA2218A;

typedef struct {
    u8 pad[0xB6];
    u8 unkB6;
} PppA2218B;

s32 func_001a2218(PppA2218A *p, PppA2218B *q) {
    if (p->unk0 == 0)
        return 0;
    if (q->unkB6 != 0 && p->unk4 == 0)
        return 0;
    return 1;
}

f32 func_001a3650(void);

s8 func_001a3698(u8 a) {
    f32 f;

    f = func_001a3650();
    return (f32) (a * 2) * f - (f32) (a >> 1);
}

typedef struct {
    u8 pad[0xF2];
    u8 unkF2;
} PppA36f0B;

s32 func_001a36f0(PppA2218A *p, PppA36f0B *q) {
    if (p->unk0 == 0)
        return 0;
    if (q->unkF2 != 0 && p->unk4 == 0)
        return 0;
    return 1;
}

extern f32 D_003732D0[]; /* sine table, 4096 entries per turn */

void func_001a50d0(f32 m[4][4], u32 a) {
    f32 s = D_003732D0[(a >> 4) & 0xFFF];
    f32 c = D_003732D0[((a + 0x4000) >> 4) & 0xFFF];

    m[0][0] = 1.0f;
    m[1][0] = 0.0f;
    m[2][0] = 0.0f;
    m[3][0] = 0.0f;
    m[0][1] = 0.0f;
    m[1][1] = c;
    m[2][1] = -s;
    m[3][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][2] = s;
    m[2][2] = c;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

void func_001a5150(f32 m[4][4], u32 a) {
    f32 s = D_003732D0[(a >> 4) & 0xFFF];
    f32 c = D_003732D0[((a + 0x4000) >> 4) & 0xFFF];

    m[0][0] = c;
    m[1][0] = 0.0f;
    m[2][0] = s;
    m[3][0] = 0.0f;
    m[0][1] = 0.0f;
    m[1][1] = 1.0f;
    m[2][1] = 0.0f;
    m[3][1] = 0.0f;
    m[0][2] = -s;
    m[1][2] = 0.0f;
    m[2][2] = c;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

void func_001a51d0(f32 m[4][4], u32 a) {
    f32 s = D_003732D0[(a >> 4) & 0xFFF];
    f32 c = D_003732D0[((a + 0x4000) >> 4) & 0xFFF];

    m[0][0] = c;
    m[1][0] = -s;
    m[2][0] = 0.0f;
    m[3][0] = 0.0f;
    m[0][1] = s;
    m[1][1] = c;
    m[2][1] = 0.0f;
    m[3][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][2] = 0.0f;
    m[2][2] = 1.0f;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

typedef struct {
    s16 unk0;
    s16 dur;    /* +0x2 */
    s8 flags;   /* +0x4 */
    u8 pad[3];
} PppAnimKey;

typedef struct {
    s16 pad[3];
    s16 n;              /* +0x6 */
    u8 pad8[8];
    PppAnimKey keys[1]; /* +0x10 */
} PppAnimHdr;

typedef struct {
    PppAnimHdr *hdr;
} PppAnim;

typedef struct {
    u16 time;
    u8 idx;
} PppAnimState;

typedef struct {
    PppAnim *anim;
    PppAnimState *st;
} PppAnimPlayer;

void func_001a56a0(PppAnimPlayer *p) {
    PppAnimState *st = p->st;
    PppAnimKey *k = &p->anim->hdr->keys[st->idx];

    st->time += 512;
    if ((s16) st->time >= k->dur) {
        st->time -= k->dur;
        st->idx++;
        if (st->idx >= p->anim->hdr->n) {
            if (k->flags & 0x80) {
                st->idx = 0;
                st->time = 0;
                return;
            }
            st->time = 0;
            st->idx--;
        }
    }
}
#include "data/data_0037.h"
