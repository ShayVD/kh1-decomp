/* The ppp loop classes, -fno-strict-aliasing (docs/modules.md "Session
 * 50"): pppMatrixLoop and pppMatrixLoopXYZ ... ZYX build the owner's matrix
 * from the work area's position, angles (one per rotation order, pppmtx.c)
 * and scale; pppDrawMdlLoop / DrawMdlLoopZ step a model's animation
 * (func_0018b030 / func_0018b470 wrap the frame) and draw it through
 * opdma.c's func_001aaf88.  ppploop.c has the rest.  Read from the code,
 * not proved by a boot. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/types/nostrict_text_00180000_h40.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"

/* pppMatrixLoopFrame (from hand/nostrict/text_00180000_h40.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
typedef struct { f32 x, y, z; } PppFVec;
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
void func_00183be0(PppMtx, void *);
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
#undef PPP_WORK

/* func_0018b030 (from hand/nostrict/text_00180000_s6_11.c). */
typedef struct {
    s32 x0;
    f32 x4, x8;
    f32 xC, x10, x14, x18;
} B030Out;
typedef struct {
    u8 pad[8];
    f32 x8;
    u8 padC[8];
    f32 x14;
} B030In;
void func_0018b030(B030In *a, B030Out *b) {
    f32 z;

    b->x4 = a->x8;
    b->x10 = a->x14;
    z = 0.0f;
    b->x18 = z;
    b->x14 = z;
    b->xC = z;
    b->x8 = z;
    b->x0 = (s32)a;
}

/* pppDrawMdlLoopFrame (from hand/nostrict/text_00190000_h63.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;
typedef struct {
    u8 pad[0x30];
    f32 col[4];     /* +0x30 */
    u8 pad40[0x40];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;
extern PppSystem *D_00615E60;
extern s32 D_0061621C;
extern s32 D_00616234;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_8b0a8;
f32 fmodf(f32, f32);
typedef struct {
    s32 frame;
    s32 unk4, unk8;
    f32 da, dda;   /* +0xC */
    s32 unk14;
    f32 db, ddb;   /* +0x18 */
} PppMdlLoopKey;
typedef struct {
    s32 init;
    f32 a, da, dda;  /* +0x4 */
    f32 b, db, ddb;  /* +0x10 */
} PppMdlLoop;
void pppDrawMdlLoopFrame(PppObject_8b0a8 *obj, PppMdlLoopKey *key, PppEntry *e) {
    PppMdlLoop *w = PPP_WORK(PppMdlLoop, obj, e, 2);

    if (w->init == 0)
        func_0018b030(key, w);
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        w->da += key->da;
        w->dda += key->dda;
        w->db += key->db;
        w->ddb += key->ddb;
    }
    if (D_00616234 != 0)
        return;
    w->da += w->dda;
    w->db += w->ddb;
    w->a += w->da;
    w->b += w->db;
    w->a = fmodf(w->a, 32768.0f);
    w->b = fmodf(w->b, 32768.0f);
}

/* pppDrawMdlLoopDraw (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_8b200;
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
    s32 unk90, unk94;
} PppMtxOwner_8b200;
extern PppMtx D_00615FC0;
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
typedef struct {
    u8 pad[0x10];
    u32 tex;    /* +0x10 */
    u8 pad14[8];
    s32 *mdl;   /* +0x1C */
    s32 arg;    /* +0x20 */
} PppMdlRes; /* 0x24 */
typedef struct {
    s16 unk0;
    s16 len;    /* +0x2 */
    s8 flags;   /* +0x4 */
    u8 pad5[3];
} PppAnimFrame;
typedef struct {
    u8 pad[6];
    s16 n;      /* +0x6 */
    u8 pad8[8];
    PppAnimFrame frames[1]; /* +0x10 */
} PppAnim;
typedef struct {
    PppAnim *anim;
    s32 unk4;
} PppAnimRef;
typedef struct {
    u8 pad[0x10];
    PppMdlRes *res; /* +0x10 */
    PppAnimRef *anims; /* +0x14 */
} PppMdlBank;
extern PppMdlBank *D_00615E64;
extern s32 D_00616224;
typedef struct {
    u32 flags;     /* +0x00 */
    void *p04;     /* +0x04 */
    u16 h08;       /* +0x08 */
    u8 b0A;
    s32 i0C;       /* +0x0C */
    s32 u, v;      /* +0x10 */
    u8 col[4];     /* +0x18 */
    s32 i1C;       /* +0x1C */
    void *m2;      /* +0x20 */
    void *p24;
    void *p28;
    void *m;       /* +0x2C */
    void *mtx;     /* +0x30 */
    s32 i34;
    s32 i38, i3C;  /* +0x38 */
    s32 i40, i44;  /* +0x40 */
    s32 i48;
    u8 b4C, b4D;   /* +0x4C */
    u8 pad4E[0x12];
} PppMdlDraw;
typedef struct {
    s32 frame;
    s32 id;      /* +0x4 */
    u8 pad8[0x18];
    union { u8 b; u16 h; } tex; /* +0x20 */
    u8 mode;     /* +0x22 */
    u8 f23, f24, f25;
} PppMdlKey;
typedef struct {
    u8 pad[8];
    u8 col[4];
} PppColWork;
s32 func_001aaf88(s32 *, PppMdlDraw *, s32);
#define D_00615E68 ((PppMtxOwner_8b200 *) D_00615E68)
void pppDrawMdlLoopDraw(PppObject_8b200 *obj, PppMdlKey *key, PppEntry *e) {
    PppMdlDraw d;
    PppMtx mtx;
    PppMdlLoop *w = PPP_WORK(PppMdlLoop, obj, e, 2);
    PppColWork *c;
    s32 *mdl;

    if (key->id == 0xFFFF)
        return;
    c = PPP_WORK(PppColWork, obj, e, 0);
    mdl = D_00615E64->res[key->id].mdl;
    d.col[0] = c->col[0];
    d.col[1] = c->col[1];
    d.col[3] = c->col[3];
    d.col[2] = c->col[2];
    if (d.col[3] == 0)
        return;
    d.flags = 0;
    if (key->mode & 2)
        d.flags = 4;
    else if (key->mode & 1)
        d.flags = 0x80;
    if (!(*mdl & 1))
        d.flags |= 8;
    if (!(*mdl & 2))
        d.flags |= 0x10;
    if (key->f23)
        d.flags |= 0x200;
    if (key->f24)
        d.flags |= 0x100;
    if (key->f25) {
        d.flags = (d.flags & ~0x10) | 0x2000;
        d.mtx = mtx;
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    } else {
        d.mtx = 0;
    }
    d.p04 = D_00616240;
    if (key->tex.b == 0xFF)
        d.h08 = ((u16 *) mdl)[11];
    else
        d.h08 = key->tex.h;
    d.b0A = 0;
    d.i0C = 0;
    d.i1C = 0;
    d.u = w->a * 65536.0f;
    d.v = w->b * 65536.0f;
    d.m2 = D_00615E68->m2;
    d.p24 = D_00616140;
    d.p28 = D_00616100;
    d.m = D_00615E68->m;
    d.i34 = D_00616224;
    d.i44 = 0;
    d.i38 = D_00615E68->unk90;
    d.i3C = D_00615E68->unk94;
    d.i40 = 0;
    d.b4C = 0;
    d.b4D = 0;
    D_00616224 = func_001aaf88(mdl, &d, D_00615E64->res[key->id].arg);
}
#undef D_00615E68

/* func_0018b470 (from hand/nostrict/text_00180000_s6_11.c). */
void func_0018b470(B030In *a, B030Out *b) {
    f32 z;

    b->x4 = a->x8;
    b->x10 = a->x14;
    z = 0.0f;
    b->x18 = z;
    b->x14 = z;
    b->xC = z;
    b->x8 = z;
    b->x0 = (s32)a;
}

/* pppDrawMdlLoopZFrame (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_8b4e8;
void pppDrawMdlLoopZFrame(PppObject_8b4e8 *obj, PppMdlLoopKey *key, PppEntry *e) {
    PppMdlLoop *w = PPP_WORK(PppMdlLoop, obj, e, 2);

    if (w->init == 0)
        func_0018b470(key, w);
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        w->da += key->da;
        w->dda += key->dda;
        w->db += key->db;
        w->ddb += key->ddb;
    }
    if (D_00616234 != 0)
        return;
    w->da += w->dda;
    w->db += w->ddb;
    w->a += w->da;
    w->b += w->db;
    w->a = fmodf(w->a, 32768.0f);
    w->b = fmodf(w->b, 32768.0f);
}

/* pppDrawMdlLoopZDraw (from hand/nostrict/text_00180000_b07.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_8b640;
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
    s32 unk90, unk94;
} PppMtxOwner_8b640;
typedef struct {
    s16 x, y, z;
} VtxS16;
typedef struct {
    s16 slot;  /* +0x0 */
    s16 n;     /* +0x2 */
    u16 *map;  /* +0x4 */
} VtxMap;
typedef struct {
    u8 pad[0x10];
    u32 tex;      /* +0x10 */
    VtxS16 *vtx;  /* +0x14 */
    s32 pad18;
    s32 *mdl;     /* +0x1C */
    s32 arg;      /* +0x20 */
} PppMdlRes_8b640; /* 0x24 */
typedef struct {
    u8 pad[0x10];
    PppMdlRes_8b640 *res; /* +0x10 */
    void *p14;
    VtxMap *maps;   /* +0x18 */
} PppMdlBank_8b640;
typedef struct {
    u32 flags;     /* +0x00 */
    void *p04;     /* +0x04 */
    u16 h08;       /* +0x08 */
    u8 b0A;
    s32 i0C;       /* +0x0C */
    s32 u, v;      /* +0x10 */
    u8 col[4];     /* +0x18 */
    s32 i1C;       /* +0x1C */
    void *m2;      /* +0x20 */
    void *p24;
    void *p28;
    void *m;       /* +0x2C */
    void *mtx;     /* +0x30 */
    s32 i34;
    s32 i38, i3C;  /* +0x38 */
    s32 i40;
    void *i44;     /* +0x44 */
    s32 i48;
    u8 b4C, b4D;   /* +0x4C */
    u8 pad4E[0x12];
} PppMdlDraw_8b640;
typedef struct {
    s32 frame;
    s32 id;      /* +0x4 */
    u8 pad8[0x18];
    union { u8 b; u16 h; } tex; /* +0x20 */
    u8 mode;     /* +0x22 */
    u8 f23, f24, f25, f26;
} PppMdlKey_8b640;
#define D_00615E68 ((PppMtxOwner_8b640 *) D_00615E68)
#define D_00615E64 ((PppMdlBank_8b640 *) D_00615E64)
void pppDrawMdlLoopZDraw(PppObject_8b640 *obj, PppMdlKey_8b640 *key, PppEntry *e) {
    PppMdlDraw_8b640 d;
    PppMtx mtx;
    PppMdlLoop *w = PPP_WORK(PppMdlLoop, obj, e, 2);
    PppColWork *c;
    s32 *mdl;

    if (key->id == 0xFFFF)
        return;
    c = PPP_WORK(PppColWork, obj, e, 0);
    mdl = D_00615E64->res[key->id].mdl;
    d.col[0] = c->col[0];
    d.col[1] = c->col[1];
    d.col[3] = c->col[3];
    d.col[2] = c->col[2];
    if (d.col[3] == 0)
        return;
    d.flags = 0;
    if (key->mode & 2)
        d.flags = 4;
    else if (key->mode & 1)
        d.flags = 0x80;
    if (!(*mdl & 1))
        d.flags |= 8;
    if (!(*mdl & 2))
        d.flags |= 0x10;
    if (key->f23)
        d.flags |= 0x200;
    if (key->f24)
        d.flags |= 0x100;
    if (key->f25) {
        d.flags = (d.flags & ~0x10) | 0x2000;
        d.mtx = mtx;
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    } else {
        d.mtx = 0;
    }
    d.p04 = D_00616240;
    if (key->tex.b == 0xFF)
        d.h08 = ((u16 *) mdl)[11];
    else
        d.h08 = key->tex.h;
    d.b0A = 0;
    d.i0C = 0;
    d.u = w->a * 65536.0f;
    d.v = w->b * 65536.0f;
    if (key->f26)
        d.i44 = PPP_WORK(u8, obj, e, 3);
    else
        d.i44 = 0;
    d.i1C = 0;
    d.m2 = D_00615E68->m2;
    d.p24 = D_00616140;
    d.p28 = D_00616100;
    d.m = D_00615E68->m;
    d.i34 = D_00616224;
    d.i38 = D_00615E68->unk90;
    d.i3C = D_00615E68->unk94;
    d.i40 = 0;
    d.b4C = 0;
    d.b4D = 0;
    D_00616224 = func_001aaf88(mdl, &d, D_00615E64->res[key->id].arg);
}
#undef D_00615E68
#undef D_00615E64

/* pppMatrixLoopXYZFrame (from hand/nostrict/text_00180000_h40.c). */
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

/* pppMatrixLoopXZYFrame (from hand/nostrict/text_00180000_h40.c). */
void func_001a5250(PppMtx, PppFVec *);
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

/* pppMatrixLoopYXZFrame (from hand/nostrict/text_00180000_h40.c). */
void func_001a5370(PppMtx, PppFVec *);
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

/* pppMatrixLoopYZXFrame (from hand/nostrict/text_00180000_h40.c). */
void func_001a52e0(PppMtx, PppFVec *);
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

/* pppMatrixLoopZXYFrame (from hand/nostrict/text_00180000_h40.c). */
void func_001a5400(PppMtx, PppFVec *);
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

/* pppMatrixLoopZYXFrame (from hand/nostrict/text_00180000_h40.c). */
void func_001a5490(PppMtx, void *);
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

