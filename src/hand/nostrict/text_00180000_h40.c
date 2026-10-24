/* ppp component callbacks (frame/draw/con), by hand (worker 40). This
 * region of the game was built without strict aliasing: the originals
 * reload values after stores through other types. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef unsigned int u128 __attribute__((mode(TI)));

/* A 16-byte aligned VU0 vector. */
typedef union {
    f32 f[4];
    u128 q;
} PppQv;

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

#include "data/types/nostrict_text_00180000_h40.h"

typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;

extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */

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
s32 func_001a8f30(void);
void func_001a5520(PppObject *, PppBornKey *, void *, void *, s16, u8, u8);

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

typedef struct {
    s16 a;
    u8 count; /* +0x2 */
} PppBornCnt;

void func_0018e0b0(void *owner, PppBorn3Key *key, s16 *pos);

/* pppKeLnsLp: a lens-flare loop. */

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
    u8 pad00[0x40];
    f32 m[3][4];   /* +0x40 */
    u128 row3;     /* +0x70 */
    PppIVec prev;  /* +0x80 */
} PppMatSN;

extern PppMatSN *D_00616214;
extern u128 D_003727B0;
void func_002675a8(f32 *, f32 *);

extern PppMtx D_0061E780;
#include "data/pieces/D_003701F0.h"

/* A shape animation: frames of 8 bytes from +0x10. */

#include "data/pieces/D_003701D0.h"
extern PppQv D_00616010[3];
extern PppMtx D_006160C0;

void func_002675a8(f32 *, f32 *);
void func_00267370(f32 *, f32 *, f32 *);

typedef struct {
    u8 pad[0x16];
    u8 h, w, y;  /* +0x16 */
} PppTexMode;

typedef struct {
    u8 pad[0x21];
    u8 h, w, y;  /* +0x21 */
} PppTexMode2;

#include "data/pieces/D_003727B0.h"
