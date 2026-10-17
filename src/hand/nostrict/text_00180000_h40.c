/* ppp component callbacks (frame/draw/con), by hand (worker 40). This
 * region of the game was built without strict aliasing: the originals
 * reload values after stores through other types. */
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
extern PppQv D_00616040[4];

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
extern PppSystem *D_00615E60;

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

void pppMatrixLoopFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_00183be0(D_00615E68->m, r);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
}

void pppMatrixLoopXYZFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_00183be0(D_00615E68->m, r);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
}

void pppMatrixLoopXZYFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5250(D_00615E68->m, r);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
}

void pppMatrixLoopYXZFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5370(D_00615E68->m, r);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
}

void pppMatrixLoopYZXFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a52e0(D_00615E68->m, r);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
}

void pppMatrixLoopZXYFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5400(D_00615E68->m, r);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
}

void pppMatrixLoopZYXFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5490(D_00615E68->m, r);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
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

void pppKeThTpFrame(PppObject *obj, PppThTpKey *key, PppEntry *e) {
    PppThTpWork *w = PPP_WORK(PppThTpWork, obj, e, 0);

    if (obj->frame == key->frame) {
        f32 *p;
        w->a = key->a;
        w->c = key->c;
        w->b = key->b;
        if (key->slot != -1)
            p = (f32 *) (D_00615E60->slots[key->slot].inst + key->off + 0xA0);
        else
            p = &D_00575A00;
        w->p = p;
        if (p == &D_00575A00)
            w->p = 0;
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    func_001a9098((void *) w, D_00615E68->m[3]);
}

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

void func_0018d390(void *owner, PppBornKey *key, s16 *pos) {
    PppVec4 v;
    PppSlot *slot = &D_00615E60->slots[key->slot];
    u8 *inst = 0;
    f32 *a, *b;

    if (slot) {
        inst = func_00182588(D_00615E60, slot);
        *(void **) (inst + 4) = owner;
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    v[3] = 1.0f;
    a = (f32 *) (inst + key->off0 + 0xA0);
    b = (f32 *) (inst + key->off2 + 0xA0);
    func_002672f8(v, D_00615E68->m[0], v);
    func_001a9098((void *) a, v);
    func_00267530(v, v, D_00615E68->m[3]);
    func_002673b8(v, v);
    func_00267560(v, v, key->speed);
    func_001a9098((void *) b, v);
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

void func_0018d5c0(void *owner, PppBorn3Key *key, s16 *pos) {
    PppVec4 v;
    PppSlot *slot = &D_00615E60->slots[key->slot];
    u8 *inst = 0;
    f32 *a, *b;

    if (slot) {
        inst = func_00182588(D_00615E60, slot);
        *(void **) (inst + 4) = owner;
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    v[3] = 1.0f;
    a = (f32 *) (inst + key->off0 + 0xA0);
    b = (f32 *) (inst + key->off2 + 0xA0);
    func_002672f8(v, D_00615E68->m[0], v);
    func_001a9098((void *) a, v);
    func_00267530(v, v, D_00615E68->m[3]);
    func_002673b8(v, v);
    func_001a9098((void *) b, v);
}

void func_0018dd08(void *owner, PppBornKey *key, s16 *pos) {
    PppVec4 v;
    PppSlot *slot = &D_00615E60->slots[key->slot];
    u8 *inst = 0;
    f32 *a, *b;

    if (slot) {
        inst = func_00182588(D_00615E60, slot);
        *(void **) (inst + 4) = owner;
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    v[3] = 1.0f;
    a = (f32 *) (inst + key->off0 + 0xA0);
    b = (f32 *) (inst + key->off2 + 0xA0);
    func_002672f8(v, D_00615E68->m[0], v);
    func_001a9098((void *) a, v);
    func_00267530(v, v, D_00615E68->m[3]);
    func_002673b8(v, v);
    func_00267560(v, v, key->speed);
    func_001a9098((void *) b, v);
}

typedef struct {
    s16 a;
    u8 count; /* +0x2 */
} PppBornCnt;

void func_0018e0b0(void *owner, PppBorn3Key *key, s16 *pos);

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

void pppKeLnsLpDraw(PppObject *obj, PppLnsKey *key, PppEntry *e) {
    PppVec4 v;
    PppLnsArg arg;
    PppLnsWork *w = PPP_WORK(PppLnsWork, obj, e, 0);

    if (key->frame == obj->frame) {
        w->a += key->a;
        w->c = key->c;
        w->b += key->b;
        w->d = key->d;
    }
    if (w->d) {
        *(u128 *) v = 0;
        v[3] = v[2] = 1.0f;
        func_002672f8(v, D_00615E68->m[0], v);
        func_001a9098(w->v, v);
    }
    w->pos[0] = D_00615E68->m[3][0];
    w->pos[1] = D_00615E68->m[3][1];
    w->pos[2] = D_00615E68->m[3][2];
    arg.m1 = D_00615FC0;
    arg.m2 = D_00616040;
    arg.w = w;
    arg.pos = D_00615E68->m[3];
    func_001a57c0(&arg);
}

void func_00192958(PppLnsWork *, s32, s32);

void pppKeLnsLpTDraw(PppObject *obj, PppLnsKey *key, PppEntry *e) {
    PppVec4 v;
    PppLnsWork *w;
    f32 one;

    pppKeLnsLpDraw(obj, key, e);
    w = PPP_WORK(PppLnsWork, obj, e, 0);
    if (key->frame == obj->frame) {
        w->unkC0 = key->e << 3;
        w->unkC1 = key->f << 2;
        w->unk8D = key->g;
    }
    one = 1.0f;
    v[3] = one;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    func_002672f8(v, D_00615E68->m2[0], v);
    func_00267560((f32 *) ((u8 *) w + 0xB0), v, one / v[3]);
    func_00192958(w, 0, 0);
}

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

typedef struct {
    s32 frame;
    f32 a, b; /* +0x4 */
} PppKey2f;

void pppKeLnsLpSftFrame(PppObject *obj, PppKey2f *key, PppEntry *e) {
    f32 *v;
    PppLnsWork *w;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    v = PPP_WORK(f32, obj, e, 0);
    w = PPP_WORK(PppLnsWork, obj, e, 1);
    if (obj->frame == key->frame) {
        v[0] += key->a;
        v[1] += key->b;
        if (obj->frame == 0 && obj->unk9D == 0)
            return;
    }
    w->b += v[0];
    w->a += v[1];
}

typedef struct {
    u8 pad00[0x40];
    f32 m[3][4];   /* +0x40 */
    u128 row3;     /* +0x70 */
    PppIVec prev;  /* +0x80 */
} PppMatSN;

extern PppMatSN *D_00616214;
extern u128 D_003727B0;

extern PppMtx D_0061E7C0;

void sceVu0UnitMatrix(PppMtx);
void func_002675a8(f32 *, f32 *);

void pppKeMatPhtFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5490(D_0061E7C0, r);
    vu0ScaleRow(D_0061E7C0[0], s->x);
    vu0ScaleRow(D_0061E7C0[1], s->y);
    vu0ScaleRow(D_0061E7C0[2], s->z);
    D_0061E7C0[3][0] = t->x;
    D_0061E7C0[3][1] = t->y;
    D_0061E7C0[3][2] = t->z;
    sceVu0UnitMatrix(D_00615E68->m);
    D_00615E68->m[0][0] = s->x;
    D_00615E68->m[1][1] = s->y;
    D_00615E68->m[2][2] = s->z;
    func_002675a8(D_00615E68->m[3], D_0061E7C0[3]);
}

extern PppMtx D_0061E780;
extern f32 D_003701F0[3];

void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);

typedef struct {
    s32 frame;
    s32 pad4;
    f32 d[6]; /* +0x8 */
} PppTs2Key;

void pppDrawMdlTs2Frame(PppObject *obj, PppTs2Key *key, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w[1] += w[2];
    w[4] += w[5];
    w[0] += w[1];
    w[3] += w[4];
    if (key->frame != obj->frame)
        return;
    w[0] += key->d[0];
    w[1] += key->d[1];
    w[2] += key->d[2];
    w[3] += key->d[3];
    w[4] += key->d[4];
    w[5] += key->d[5];
}

void pppDrawMdlTs3Frame(PppObject *obj, PppTs2Key *key, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w[1] += w[2];
    w[4] += w[5];
    w[0] += w[1];
    w[3] += w[4];
    if (key->frame != obj->frame)
        return;
    w[0] += key->d[0];
    w[1] += key->d[1];
    w[2] += key->d[2];
    w[3] += key->d[3];
    w[4] += key->d[4];
    w[5] += key->d[5];
}

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

void pppDrawShapeXFrame(PppObject *obj, PppShapeKey *key, PppEntry *e) {
    PppShapeWork *w;
    PppShape *s;
    PppShapeFrame *f;
    u16 cur, t;
    s8 fl;
    s32 id, off;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(PppShapeWork, obj, e, 0);
    id = key->id;
    off = id * 8;
    if (id == 0xFFFF)
        return;
    s = *(PppShape **) ((u8 *) D_00615E64->shapes + off);
    f = &s->f[w->prev];
    w->prev = w->cur;
    w->time += key->speed;
    if (w->time < f->dur)
        return;
    w->time -= f->dur;
    w->cur++;
    if (w->cur < s->n)
        return;
    fl = f->flags;
    w->time = 0;
    if (fl & 0x80)
        w->cur = 0;
    else
        w->cur--;
}

extern PppMtx D_00615EB0;
void func_00267548(f32 *, f32 *, f32 *);

void pppRyjDrawMatrixWorldNoRotFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    f32 *w = PPP_WORK(f32, obj, e, 1);

    sceVu0UnitMatrix(m);
    m[3][0] = w[0];
    m[3][1] = w[1];
    m[3][2] = w[2];
    sceVu0MulMatrix(m, D_00615EB0, m);
    func_00267560(D_00615E68->m2[0], D_00615E68->m[0], w[4]);
    func_00267560(D_00615E68->m2[1], D_00615E68->m[1], w[5]);
    func_00267560(D_00615E68->m2[2], D_00615E68->m[2], w[6]);
    func_00267548(D_00615E68->m2[3], D_00615E68->m[3], &w[4]);
    D_00615E68->m2[3][0] += m[3][0];
    D_00615E68->m2[3][1] += m[3][1];
    D_00615E68->m2[3][2] += m[3][2];
    sceVu0MulMatrix(D_00615E68->m2, (f32 (*)[4]) D_00616040, D_00615E68->m2);
}

extern f32 D_003701D0[4];
extern PppQv D_00616010[3];
extern PppMtx D_006160C0;

void func_002675a8(f32 *, f32 *);
void func_00267370(f32 *, f32 *, f32 *);

void func_00267440(PppMtx, PppMtx);

void pppRyjMatrixNoRotFrame(PppObject *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_00267440(D_00615E68->m, D_00615EB0);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
}

typedef struct {
    u8 pad[0x16];
    u8 h, w, y;  /* +0x16 */
} PppTexMode;

typedef struct {
    u8 pad[0x21];
    u8 h, w, y;  /* +0x21 */
} PppTexMode2;

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

void func_0019dac8(void) {
    PppQv d;
    PppLight *p = D_0035C710;
    s32 i;

    D_0061E710 = 0;
    for (i = 0; i < 256; i++, p++) {
        if (!(p->flags & 0x100))
            continue;
        if (p->flags & 0x200)
            continue;
        {
            func_00267530(d.f, D_002E2780, p->pos);
            func_00267548(d.f, d.f, d.f);
            D_0061E310[D_0061E710] = p;
            D_0061E710++;
            p->dist = d.f[0] + d.f[1] + d.f[2];
        }
    }
    if (D_0061E710 >= 2)
        func_0019d968(0, D_0061E710 - 1);
    for (i = 0; i < D_0061E710; i++)
        D_0061E310[i]->dist = 1.0f;
}

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

s32 func_0019e028(PppPool *pool, PppSrcA *src) {
    u32 i;
    PppSlotA *s;

    if (!pool->a)
        return 0;
    for (i = 0; i < pool->n0; i++) {
        s = &pool->a[i];
        if (s->src == 0) {
            s->src = src;
            s->rec = func_0019dfc8(src->id);
            func_002675a8(s->pos, s->rec->org.f);
            s->pos[0] += src->ofs[0];
            s->pos[1] += src->ofs[1];
            s->pos[2] += src->ofs[2];
            s->pos[3] = 1.0f;
            break;
        }
    }
    return 1;
}

s32 func_0019e108(PppPool *pool, PppSrcA *src) {
    u32 i;
    PppSlotA *s;

    if (!pool->b)
        return 0;
    for (i = 0; i < pool->n1; i++) {
        s = &pool->b[i];
        if (s->src == 0) {
            s->src = src;
            s->rec = func_0019dfc8(src->id);
            func_002675a8(s->pos, s->rec->org.f);
            s->pos[0] += src->ofs[0];
            s->pos[1] += src->ofs[1];
            s->pos[2] += src->ofs[2];
            s->pos[3] = 1.0f;
            break;
        }
    }
    return 1;
}

s32 func_0019e1e8(PppPool *pool, PppSrcB *src) {
    u32 i;
    PppSlotB *s;

    if (!pool->c)
        return 0;
    for (i = 0; i < pool->n2; i++) {
        s = &pool->c[i];
        if (s->src == 0) {
            s->src = src;
            s->rec = func_0019dfc8(src->id);
            s->a = src->a;
            s->b = src->b;
            s->c = 32767 / src->c;
            func_002675a8(s->pos, s->rec->org.f);
            s->pos[0] += src->ofs[0];
            s->pos[1] += src->ofs[1];
            s->pos[2] += src->ofs[2];
            s->pos[3] = 1.0f;
            break;
        }
    }
    return 1;
}

/* needs make: uses rodata */
typedef struct {
    u8 pad[0x26];
    u8 mode;   /* +0x26 */
} PppMdlMode;

typedef struct {
    u8 pad[0x14];
    s32 parent; /* +0x14 */
} PppMdlOwn;

void func_001a0908(PppMtx m, PppMdlMode *p, PppMdlOwn *o) {
    s32 parent = o->parent;

    sceVu0UnitMatrix(m);
    switch (p->mode) {
    case 0:
    case 2:
    case 4:
    case 6:
    case 8:
    default:
        if (parent == 0)
            sceVu0MulMatrix(m, (f32 (*)[4]) D_00615FC0, D_00615E68->m);
        return;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        sceVu0MulMatrix(m, (f32 (*)[4]) D_00615FC0, D_00615E68->m);
        return;
    }
}
