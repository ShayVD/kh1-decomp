/* ppp component callbacks (frame/draw/con), by hand (worker 40).
 * The ones here match with strict aliasing; the rest of this batch is in
 * src/hand/nostrict/text_00180000_h40.c. */
#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef unsigned int u128 __attribute__((mode(TI)));

/* A 16-byte aligned VU0 vector. */
typedef union {
    f32 f[4];
    u128 q;
} PppQv;

extern PppQv D_00615FC0[4];
extern PppQv D_00616040[4]; /* src/data/bss_0061.c: u8 D_00616040[0x40] */

typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;

typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;

extern s32 D_0061621C;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;

typedef struct { f32 a, b, c; } PppV12;

typedef struct {
    s32 frame;
    PppV12 v;    /* +0x4 */
    f32 x, y;    /* +0x10 */
    f32 d[3];    /* +0x18 */
} PppWindKey;

typedef struct {
    PppV12 v;
    f32 x, y;    /* +0xC */
    f32 r;       /* +0x14 */
    f32 d[3];    /* +0x18 */
} PppWindWork;

static inline f32 vu0Sqrt(f32 x) {
    f32 r;
    __asm__ volatile(
        "mfc1 $2, %1\n"
        "qmtc2 $2, $vf2\n"
        "vsqrt Q, $vf2x\n"
        "vwaitq\n"
        "vaddq.x $vf2x, $vf0x, Q\n"
        "qmfc2 $2, $vf2\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "f"(x) : "$2");
    return r;
}

void pppEiWindFunFrame(PppObject *obj, PppWindKey *key, PppEntry *e) {
    PppWindWork *w = PPP_WORK(PppWindWork, obj, e, 0);
    f32 x, y;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->d[1] += w->d[2];
        w->d[0] += w->d[1];
    }
    if (key->frame != obj->frame)
        return;
    w->v = key->v;
    w->x = x = key->x;
    w->y = y = key->y;
    w->r = x / vu0Sqrt(x * x + y * y);
    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->d[0] += key->d[0];
        w->d[1] += key->d[1];
        w->d[2] += key->d[2];
    }
}
extern s32 D_00616234;

typedef struct { f32 x, y, z; } PppFVec;
typedef struct { s32 x, y, z; } PppIVec;

typedef struct {
    s32 frame;
    PppFVec v; /* +0x4 */
} PppFVecKey;

typedef struct {
    s32 frame;
    PppIVec v; /* +0x4 */
} PppIVecKey;

void pppMoveLoopFrame(PppObject *obj, PppFVecKey *key, PppEntry *e) {
    PppFVec *pos = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *vel = PPP_WORK(PppFVec, obj, e, 1);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        vel->x += key->v.x;
        vel->y += key->v.y;
        vel->z += key->v.z;
    }
    if (D_00616234 == 0) {
        pos->x += vel->x;
        pos->y += vel->y;
        pos->z += vel->z;
    }
}

void pppAngMoveLoopFrame(PppObject *obj, PppIVecKey *key, PppEntry *e) {
    PppIVec *pos = PPP_WORK(PppIVec, obj, e, 0);
    PppIVec *vel = PPP_WORK(PppIVec, obj, e, 1);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        vel->x += key->v.x;
        vel->y += key->v.y;
        vel->z += key->v.z;
    }
    if (D_00616234 == 0) {
        pos->x += vel->x;
        pos->y += vel->y;
        pos->z += vel->z;
    }
}

void pppSclMoveLoopFrame(PppObject *obj, PppFVecKey *key, PppEntry *e) {
    PppFVec *pos = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *vel = PPP_WORK(PppFVec, obj, e, 1);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        vel->x += key->v.x;
        vel->y += key->v.y;
        vel->z += key->v.z;
    }
    if (D_00616234 == 0) {
        pos->x += vel->x;
        pos->y += vel->y;
        pos->z += vel->z;
    }
}

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;

extern PppMtxOwner *D_00615E68;

void func_00183be0(PppMtx, void *);
void func_001a5250(PppMtx, PppFVec *);
void func_001a5370(PppMtx, PppFVec *);
void func_001a52e0(PppMtx, PppFVec *);
void func_001a5400(PppMtx, PppFVec *);
void func_001a5490(PppMtx, void *);

static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}

extern f32 D_00575A00;

typedef struct {
    s32 frame;
    f32 c, a, b;  /* +0x4 */
    s32 slot;     /* +0x10 */
    s32 off;      /* +0x14 */
} PppThTpKey;

typedef struct {
    u8 pad[0x10];
    f32 a, b, c;  /* +0x10 */
    f32 *p;       /* +0x1C */
} PppThTpWork;

void func_001a9098(void *, f32 *);

typedef f32 PppVec4[4] __attribute__((aligned(16)));

/* Keys of the pppKeBornRnd* classes. */
typedef struct {
    s32 frame;
    s16 n;        /* +0x4 */
    s16 pad6;
    f32 speed;    /* +0x8 */
    u8 c;         /* +0xC */
    u8 mask;      /* +0xD */
    u8 b;         /* +0xE */
    u8 padF;
    s32 slot;     /* +0x10 */
    s32 off0;     /* +0x14 */
    s32 off1;     /* +0x18 */
    s32 off2;     /* +0x1C */
} PppBornKey;

u8 *func_00182588(PppSystem *, PppSlot *);
void func_002672f8(PppVec4, f32 *, PppVec4);
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(PppVec4, PppVec4);
void func_00267560(f32 *, PppVec4, f32);
s32 func_001a8f30(void);
void func_001a5520(PppObject *, PppBornKey *, void *, void *, s16, u8, u8);
void func_0018d390(void *owner, PppBornKey *key, s16 *pos);
void func_0018dd08(void *owner, PppBornKey *key, s16 *pos);

void pppKeBornRnd2Frame(PppObject *obj, PppBornKey *key, PppEntry *e) {
    PppObject **pp = &obj;
    if (D_00616234 == 0 && D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL) &&
        key->mask != 0xFF && !((func_001a8f30() >> 8) & key->mask) && key->slot != -1 &&
        key->off1 != -1) {
        func_001a5520(obj, key, func_0018d390, PPP_WORK(void, obj, e, 0), key->n, key->b, key->c);
    }
}

typedef struct {
    s32 frame;
    s16 n;        /* +0x4 */
    u8 c;         /* +0x6 */
    u8 mask;      /* +0x7 */
    u8 b;         /* +0x8 */
    u8 pad9[3];
    s32 slot;     /* +0xC */
    s32 off0;     /* +0x10 */
    s32 off1;     /* +0x14 */
    s32 off2;     /* +0x18 */
} PppBorn3Key;

void func_0018d5c0(void *owner, PppBorn3Key *key, s16 *pos);

void pppKeBornRnd3Frame(PppObject *obj, PppBorn3Key *key, PppEntry *e) {
    PppObject **pp = &obj;
    if (D_00616234 == 0 && D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL) &&
        key->mask != 0xFF && !((func_001a8f30() >> 8) & key->mask) && key->slot != -1 &&
        key->off1 != -1) {
        func_001a5520(obj, (PppBornKey *) key, func_0018d5c0, PPP_WORK(void, obj, e, 0), key->n, key->b, key->c);
    }
}

typedef struct {
    s16 a;
    u8 count; /* +0x2 */
} PppBornCnt;

void pppKeBornRnd5Frame(PppObject *obj, PppBornKey *key, PppEntry *e) {
    PppBornCnt *w;
    u8 n;

    if (D_00616234 != 0 || D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    n = key->mask;
    if (n == 0)
        return;
    w = PPP_WORK(PppBornCnt, obj, e, 0);
    if (w->count == 0) {
        w->count = n;
        if (key->slot == -1 || key->off1 == -1)
            return;
        func_001a5520(obj, key, func_0018dd08, w, key->n, key->b, key->c);
    }
    w->count--;
}

void func_0018e0b0(void *owner, PppBorn3Key *key, s16 *pos);

void pppKeBornRnd6Frame(PppObject *obj, PppBorn3Key *key, PppEntry *e) {
    PppBornCnt *w;
    u8 n;

    if (D_00616234 != 0 || D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    n = key->mask;
    if (n == 0)
        return;
    w = PPP_WORK(PppBornCnt, obj, e, 0);
    if (w->count == 0) {
        w->count = n;
        if (key->slot == -1 || key->off1 == -1)
            return;
        func_001a5520(obj, (PppBornKey *) key, func_0018e0b0, w, key->n, key->b, key->c);
    }
    w->count--;
}

/* pppKeLnsLp: a lens-flare loop. */
typedef struct {
    s32 frame;
    f32 b, a;   /* +0x4 */
    u8 c, d;    /* +0xC */
    u8 e, f, g; /* +0xE (LnsLpT) */
} PppLnsKey;

typedef struct {
    u8 pad00[0x80];
    f32 pos[3];   /* +0x80 */
    u8 pad8C;
    u8 unk8D;     /* +0x8D */
    u8 c, d;      /* +0x8E */
    f32 v[3];     /* +0x90 */
    f32 b;        /* +0x9C */
    u8 padA0[8];
    f32 a;        /* +0xA8 */
    u8 padAC[0x14];
    u8 unkC0, unkC1; /* +0xC0 */
} PppLnsWork;

typedef struct {
    PppLnsWork *w;
    f32 *pos;
    void *m1;
    void *m2;
} PppLnsArg;

void func_001a57c0(PppLnsArg *);

void func_00192958(PppLnsWork *, s32, s32);

typedef struct {
    u8 pad00[0x10];
    u8 unk10[0x10]; /* +0x10 */
    f32 unk20;      /* +0x20 */
    s32 unk24;      /* +0x24 */
    f32 w, h;       /* +0x28 */
} PppSprite;

typedef struct {
    PppSprite *s;  /* +0x0 */
    s32 unk4;      /* +0x4 */
    void *m;       /* +0x8 */
    f32 unkC;      /* +0xC */
    u16 w, h;      /* +0x10 */
    u8 *p;         /* +0x14 */
} PppSpriteArg;

void func_001a62c0(PppSpriteArg *, s32);

void func_00193408(PppSprite *s) {
    PppSpriteArg a;

    a.unk4 = s->unk24;
    a.w = (u32) s->w;
    a.h = (u32) s->h;
    a.p = s->unk10;
    a.s = s;
    a.unkC = s->unk20;
    a.m = D_00616040;
    func_001a62c0(&a, 0);
}

typedef struct {
    s32 frame;
    f32 a, b; /* +0x4 */
} PppKey2f;

typedef struct {
    u8 pad00[0x40];
    f32 m[3][4];   /* +0x40 */
    u128 row3;     /* +0x70 */
    PppIVec prev;  /* +0x80 */
} PppMatSN;

extern PppMatSN *D_00616214; /* src/data/bss_0061.c: s32 D_00616214 */
extern u128 D_003727B0;

void pppKeMatSNFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMatSN *w = PPP_WORK(PppMatSN, obj, e, 0);
    PppIVec *r = PPP_WORK(PppIVec, obj, e, 1);
    PppIVec d;

    D_00616214 = w;
    d = w->prev;
    w->prev.x = r->x;
    w->prev.y = r->y;
    w->prev.z = r->z;
    d.x -= w->prev.x;
    d.y -= w->prev.y;
    d.z -= w->prev.z;
    func_00183be0((void *) w->m, &d);
    w->row3 = D_003727B0;
}

extern PppMtx D_0061E7C0;

void sceVu0UnitMatrix(PppMtx);
void func_002675a8(f32 *, f32 *);

extern PppMtx D_0061E780;
extern f32 D_003701F0[3];

void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);

void pppKeDMatPhtFrFrame(PppObject *obj, void *key, PppEntry *e) {
    func_00267560(D_0061E780[0], D_0061E7C0[0], D_003701F0[0]);
    func_00267560(D_0061E780[1], D_0061E7C0[1], D_003701F0[1]);
    func_00267560(D_0061E780[2], D_0061E7C0[2], D_003701F0[2]);
    func_002672f8(D_0061E780[3], (f32 *) D_00615FC0, D_0061E7C0[3]);
    func_00267560(D_00615E68->m2[0], D_00615E68->m[0], D_003701F0[0]);
    func_00267560(D_00615E68->m2[1], D_00615E68->m[1], D_003701F0[1]);
    func_00267560(D_00615E68->m2[2], D_00615E68->m[2], D_003701F0[2]);
    func_002672f8(D_00615E68->m2[3], (f32 *) D_00615FC0, D_00615E68->m[3]);
    sceVu0MulMatrix(D_00615E68->m2, (f32 (*)[4]) D_00616040, D_00615E68->m2);
}

typedef struct {
    s32 frame;
    s32 pad4;
    f32 d[6]; /* +0x8 */
} PppTs2Key;

/* A shape animation: frames of 8 bytes from +0x10. */
typedef struct {
    s16 unk0;
    s16 dur;   /* +0x2 */
    s8 flags;  /* +0x4 */
    u8 pad5[3];
} PppShapeFrame;

typedef struct {
    u8 pad0[6];
    s16 n;                  /* +0x6 */
    u8 pad8[8];
    PppShapeFrame f[1];     /* +0x10 */
} PppShape;

typedef struct {
    PppShape *shape;
    s32 unk4;
} PppShapeEnt;

typedef struct {
    u8 pad[0x14];
    PppShapeEnt *shapes; /* +0x14 */
} PppRes;

extern PppRes *D_00615E64;

typedef struct {
    s32 frame;
    s32 id;     /* +0x4 */
    u16 speed;  /* +0x8 */
} PppShapeKey;

typedef struct {
    u16 time;   /* +0x0 */
    u16 cur;    /* +0x2 */
    u16 prev;   /* +0x4 */
} PppShapeWork;

extern PppMtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
void func_00267548(f32 *, f32 *, f32 *);

extern f32 D_003701D0[4];
extern PppQv D_00616010[3];
extern PppMtx D_006160C0; /* src/data/bss_0061.c: f32 D_006160C0[4][4] */

void func_002675a8(f32 *, f32 *);
void func_00267370(f32 *, f32 *, f32 *);

void pppRyjDrawMatrixWorldWoodCon(PppObject *obj, PppEntry *e) {
    PppQv u, v, c;
    f32 *w = PPP_WORK(f32, obj, e, 1);

    func_002675a8(w, D_003701D0);
    func_002675a8(w + 4, D_003701F0);
    v.f[0] = D_00615FC0[1].f[0];
    v.f[1] = D_00615FC0[1].f[1];
    v.f[2] = D_00615FC0[1].f[2];
    v.f[3] = 0.0f;
    func_002673b8(v.f, v.f);
    D_00616010[0].q = v.q;
    u.f[0] = v.f[1];
    u.f[1] = -v.f[0];
    u.f[2] = 0.0f;
    u.f[3] = 0.0f;
    func_002673b8(u.f, u.f);
    D_00616010[-1].q = u.q;
    func_00267370(c.f, u.f, v.f);
    func_002673b8(c.f, c.f);
    D_00616010[1].q = c.q;
    D_00616010[2].q = D_00615FC0[3].q;
    sceVu0MulMatrix(D_006160C0, (f32 (*)[4]) D_00616040, (f32 (*)[4]) &D_00616010[-1]);
}

void pppRyjDrawMatrixWorldWoodFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    f32 *w = PPP_WORK(f32, obj, e, 1);

    sceVu0UnitMatrix(m);
    m[3][0] = w[0];
    m[3][1] = w[1];
    m[3][2] = w[2];
    sceVu0MulMatrix(m, D_00615EB0, m);
    sceVu0MulMatrix(m, (f32 (*)[4]) D_00616040, m);
    func_00267560(D_00615E68->m2[0], D_00615E68->m[0], w[4]);
    func_00267560(D_00615E68->m2[1], D_00615E68->m[1], w[5]);
    func_00267560(D_00615E68->m2[2], D_00615E68->m[2], w[6]);
    *(u128 *) D_00615E68->m2[3] = *(u128 *) D_00615E68->m[3];
    sceVu0MulMatrix(D_00615E68->m2, D_006160C0, D_00615E68->m2);
    func_002672f8(D_00615E68->m2[3], (f32 *) m, D_00615E68->m[3]);
}

void func_00267440(PppMtx, PppMtx);

typedef struct {
    u8 pad[0x16];
    u8 h, w, y;  /* +0x16 */
} PppTexMode;

void func_001999f0(PppTexMode *p, s32 *y0, s32 *y1, s32 *x0, s32 *x1) {
    s32 y = 0, w = 4096, h = 4096;

    switch (p->h) {
    case 1:
        h = 2048;
        break;
    case 2:
        h = 1024;
        break;
    }
    switch (p->w) {
    case 1:
        w = 2048;
        break;
    case 2:
        w = 1024;
        break;
    }
    switch (p->y) {
    case 1:
        y = 1024;
        h += 1024;
        break;
    case 2:
        y = 2048;
        h += 2048;
        break;
    case 3:
        y = 3072;
        h += 3072;
        break;
    }
    *y0 = y + 16;
    *y1 = h - 16;
    *x0 = 16;
    *x1 = w - 16;
}

typedef struct {
    u8 pad[0x21];
    u8 h, w, y;  /* +0x21 */
} PppTexMode2;

void func_0019aa60(PppTexMode2 *p, s32 *y0, s32 *y1, s32 *x0, s32 *x1) {
    s32 y = 0, w = 4096, h = 4096;

    switch (p->h) {
    case 1:
        h = 2048;
        break;
    case 2:
        h = 1024;
        break;
    }
    switch (p->w) {
    case 1:
        w = 2048;
        break;
    case 2:
        w = 1024;
        break;
    }
    switch (p->y) {
    case 1:
        y = 1024;
        h += 1024;
        break;
    case 2:
        y = 2048;
        h += 2048;
        break;
    case 3:
        y = 3072;
        h += 3072;
        break;
    }
    *y0 = y + 16;
    *y1 = h - 16;
    *x0 = 16;
    *x1 = w - 16;
}

typedef struct {
    f32 pos[3];
    f32 dist;   /* +0xC */
    u8 pad10[8];
    u64 flags;  /* +0x18 */
} PppLight;

extern PppLight D_0035C710[256];
extern PppLight *D_0061E310[256];
extern s32 D_0061E710;
extern f32 D_002E2780[];

void func_0019d968(s32, s32);

/* Effect instance pools: each slot points back at its source and at the
 * model record func_0019dfc8 finds for the source's id. */
typedef struct {
    u8 pad0[0x10];
    PppQv org;   /* +0x10 */
} PppMdlRec;

typedef struct {
    s32 unk0;
    s32 id;       /* +0x4 */
    u8 pad8[0x18];
    f32 ofs[3];   /* +0x20 */
} PppSrcA;

typedef struct {
    s32 unk0;
    s32 id;       /* +0x4 */
    u8 pad8[0x1C];
    f32 ofs[3];   /* +0x24 */
    u8 pad30[0x10];
    u8 a, b, c;   /* +0x40 */
} PppSrcB;

typedef struct {
    f32 pos[4];
    void *src;        /* +0x10 */
    PppMdlRec *rec;   /* +0x14 */
    u8 pad18[8];
} PppSlotA;

typedef struct {
    f32 pos[4];
    void *src;        /* +0x10 */
    PppMdlRec *rec;   /* +0x14 */
    u8 pad18[4];
    u8 a, b;          /* +0x1C */
    s16 c;            /* +0x1E */
    u8 pad20[0x10];
} PppSlotB;

typedef struct {
    u32 n0;
    u32 n1;
    u32 n2;
    PppSlotA *a;  /* +0xC */
    PppSlotA *b;  /* +0x10 */
    PppSlotB *c;  /* +0x14 */
} PppPool;

PppMdlRec *func_0019dfc8(s32);
