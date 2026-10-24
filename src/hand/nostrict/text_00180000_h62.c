/* ppp classes and manager helpers, by hand (worker 62). Built without
 * strict aliasing (see src/hand/nostrict). */
#include "ppp.h"
#include "data/bss_0061.h"

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

typedef struct {
    u8 pad[0xB0];
    u64 flags; /* +0xB0 */
} PppSystem;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

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

extern VtxSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
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

void func_00184918(PppObject *, VtxApKey *, VtxS16 *);

void func_00184918(PppObject *, VtxApKey *, VtxS16 *);

void func_00184918(PppObject *, VtxApKey *, VtxS16 *);

/* The pppDrawMdl* draw callbacks fill a DParam and hand it to
 * func_001aaf88 with the slot's model. */
