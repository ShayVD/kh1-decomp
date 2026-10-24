/* ppp component callbacks (frame/draw/con), by hand (worker 40).
 * The ones here match with strict aliasing; the rest of this batch is in
 * src/hand/nostrict/text_00180000_h40.c. */
#include "common.h"
#include "ppp.h"

#include "data/types/shared.h"

/* A 16-byte aligned VU0 vector. */
#include "data/types/text_00180000_h40.h"

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

typedef struct { f32 x, y, z; } PppFVec;
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

u8 *func_00182588(PppSystem *, PppSlot *);
void func_00267530(f32 *, f32 *, f32 *);

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
    s32 frame;
    f32 a, b; /* +0x4 */
} PppKey2f;
void func_002675a8(f32 *, f32 *);

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
void func_00267548(f32 *, f32 *, f32 *);

void func_002675a8(f32 *, f32 *);

void func_00267440(PppMtx, PppMtx);

typedef struct {
    f32 pos[3];
    f32 dist;   /* +0xC */
    u8 pad10[8];
    u64 flags;  /* +0x18 */
} PppLight;

#include "data/pieces/D_0035C710.h"
extern PppLight *D_0061E310[256];
extern s32 D_0061E710;
#include "data/pieces/D_002E2780.h"

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
