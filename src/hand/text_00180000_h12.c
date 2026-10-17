/* ppp manager and component callbacks, by hand (worker 12). */
#include "common.h"

/* D_00364130: 256 effect managers of 0xC0 bytes. */
typedef struct {
    u8 pad[0xFC];
    u16 unkFC;
} PppOwner;

typedef struct PppMng {
    u8 pad00[0x86];
    u16 st;          /* +0x86 */
    u8 pad88[4];
    PppOwner *owner; /* +0x8C */
    u8 pad90[4];
    s32 link;        /* +0x94: a PppLink *, typed s32 (see func_001827f0) */
    s32 unk98;       /* +0x98 */
    u8 pad9C[0xC];
    s32 unkA8;       /* +0xA8 */
    u8 padAC[0x14];
} PppMng;

typedef struct {
    u8 pad00[0x14];
    s32 flags;
} PppLink;

extern PppMng D_00364130[256];
void func_0011d3c8(s32, s32, s32);
void func_00182788(PppMng *);
void func_00182840(PppMng *);

s32 func_00181410(void) {
    PppMng *m = D_00364130;
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
    u8 pad00[0x54];
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
extern PppSys *D_00615E60;

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
