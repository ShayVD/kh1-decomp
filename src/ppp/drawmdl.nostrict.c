/* The ppp model draw classes, -fno-strict-aliasing (docs/modules.md "Session
 * 50"): pppDrawMdl2 / DrawMdlSemi2 / DrawMdlTs2 and their "3" versions draw
 * a model through opdma.c's func_001aaf88 with the owner's matrix (the 3s
 * times the parent matrix; Semi is translucent; Ts scrolls the texture by
 * the work area's UV speeds, stepped in its frame), and pppKeZCrct /
 * KeZCrctShp correct the owner's matrix (scale, then an offset in one of
 * several spaces: world, camera, parent).  Each section names the file its
 * code came from.  Read from the code, not proved by a boot. */

/* pppDrawMdl2Draw (from hand/nostrict/text_00190000_h64.c). */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/pieces/D_003701F0.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
typedef struct {
    u32 flags;  /* +0x0 */
    u8 pad04[0x12];
    u16 unk16;  /* +0x16 */
} DMdl;
typedef struct {
    s32 pad0[4];
    u32 tex;    /* +0x10 */
    s32 pad14[2];
    DMdl *mdl;  /* +0x1C */
    s32 unk20;  /* +0x20 */
} DSlot; /* 0x24 */
typedef struct {
    s16 off;   /* +0x0 */
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
    u8 pad00[0x10];
    DSlot *slots;        /* +0x10 */
    PppShapeEnt *shapes; /* +0x14 */
} DSys;
extern DSys *D_00615E64;
typedef struct {
    s32 flags;  /* +0x00 */
    void *p04;  /* +0x04 */
    u16 h08;    /* +0x08 */
    u8 b0A;     /* +0x0A */
    s32 w0C;    /* +0x0C */
    union { u64 d; struct { s32 u, v; } s; } t10; /* +0x10 */
    u8 r, g, b, a; /* +0x18 */
    s32 w1C;    /* +0x1C */
    void *p20;  /* +0x20 */
    void *p24;  /* +0x24 */
    void *p28;  /* +0x28 */
    void *p2C;  /* +0x2C */
    void *p30;  /* +0x30 */
    s32 w34;    /* +0x34 */
    s32 w38;    /* +0x38 */
    s32 w3C;    /* +0x3C */
    s32 w40;    /* +0x40 */
    void *p44;  /* +0x44 */
    s32 w48;    /* +0x48 */
    u8 b4C;     /* +0x4C */
    u8 b4D;     /* +0x4D */
    u8 pad4E[0x12];
} DParam;
typedef struct {
    u8 pad[8];
    u8 r, g, b, a; /* +0x8 */
} DColWork;
extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern s32 D_00616224;
s32 func_001aaf88(DMdl *, DParam *, s32);
typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u8 flags; /* +0x8 */
    u8 b9, bA;
} DMdl2Key;
void pppDrawMdl2Draw(PppObject *obj, DMdl2Key *key, PppEntry *e) {
    DParam p;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
    p.p44 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p20 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4C = key->b9;
    p.b4D = key->bA;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

/* pppDrawMdlSemi2Draw (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u16 h8;   /* +0x8 */
    u8 flags; /* +0xA */
} DSemi2Key;
void pppDrawMdlSemi2Draw(PppObject *obj, DSemi2Key *key, PppEntry *e) {
    DParam p;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
/*P*/
    p.h08 = key->h8;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
    p.p44 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p20 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

/* pppDrawMdlTs2Frame (from hand/nostrict/text_00180000_h40.c). */
#include "data/types/nostrict_text_00180000_h40.h"
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

/* pppDrawMdlTs2Draw (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u8 pad8[0x18];
    u8 flags; /* +0x20 */
    u8 b21;
} DTs2Key;
void pppDrawMdlTs2Draw(PppObject *obj, DTs2Key *key, PppEntry *e) {
    DParam p;
    DColWork *w;
    f32 *t = PPP_WORK(f32, obj, e, 2);
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.s.u = t[0] * 65536.0f;
    p.t10.s.v = t[3] * 65536.0f;
    p.w40 = 0;
    p.p44 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p20 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4D = key->b21;
    p.b4C = 0;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

/* pppKeZCrctFrame (from hand/nostrict/text_00190000_h64.c). */
extern PppMtx D_00615FC0;
extern PppMtx D_00616000;
extern PppMtx D_00615EB0;
extern PppMtx D_00615E70;
extern PppMtx D_00616040;
void func_002675a8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
typedef struct {
    s32 frame;
    f32 x, y, z;     /* +0x4 */
    f32 sx, sy, sz;  /* +0x10 */
    u8 mode;         /* +0x1C */
} PppZCrctKey;
void pppKeZCrctFrame(PppObject *obj, PppZCrctKey *key, PppEntry *e) {
    PppMtx m;
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[0] + 0xA0);

    func_00267560(m[0], D_00615E68->m[0], key->sx);
    func_00267560(m[1], D_00615E68->m[1], key->sy);
    func_00267560(m[2], D_00615E68->m[2], key->sz);
    func_002675a8(m[3], D_00615E68->m[3]);
    switch (key->mode) {
    case 0:
        m[3][0] += key->x;
        m[3][1] += key->y;
        m[3][2] += key->z;
        sceVu0MulMatrix(m, D_00615FC0, m);
        break;
    case 1:
        sceVu0MulMatrix(m, D_00615FC0, m);
        m[3][0] += key->x;
        m[3][1] += key->y;
        m[3][2] += key->z;
        break;
    case 2:
        sceVu0MulMatrix(m, D_00615E70, m);
        m[3][0] += key->x * D_003701F0[0];
        m[3][1] += key->y * D_003701F0[1];
        m[3][2] += key->z * D_003701F0[2];
        sceVu0MulMatrix(m, D_00615EB0, m);
        break;
    case 3:
        sceVu0MulMatrix(m, D_00616000, m);
        m[3][0] += key->x;
        m[3][1] += key->y;
        m[3][2] += key->z;
        break;
    }
    sceVu0MulMatrix(w, D_00616040, m);
}

/* pppKeZCrctShpFrame (from hand/nostrict/text_00190000_h64.c). */
typedef f32 PppVec4[4] __attribute__((aligned(16)));
void func_002672f8(f32 *, PppMtx, f32 *);
void pppKeZCrctShpFrame(PppObject *obj, PppZCrctKey *key, PppEntry *e) {
    PppMtx m;
    PppVec4 v;
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[0] + 0xA0);

    func_00267560(m[0], D_00615E68->m[0], D_003701F0[0]);
    func_00267560(m[1], D_00615E68->m[1], D_003701F0[1]);
    func_00267560(m[2], D_00615E68->m[2], D_003701F0[2]);
    func_002675a8(v, D_00615E68->m[3]);
    v[0] *= key->sx;
    v[1] *= key->sy;
    v[2] *= key->sz;
    switch (key->mode) {
    case 0:
        v[0] += key->x;
        v[1] += key->y;
        v[2] += key->z;
        func_002672f8(m[3], D_00615FC0, v);
        break;
    case 1:
        func_002672f8(m[3], D_00615FC0, v);
        m[3][0] += key->x;
        m[3][1] += key->y;
        m[3][2] += key->z;
        break;
    case 2:
        func_002672f8(m[3], D_00615E70, v);
        m[3][0] += key->x * D_003701F0[0];
        m[3][1] += key->y * D_003701F0[1];
        m[3][2] += key->z * D_003701F0[2];
        func_002672f8(m[3], D_00615EB0, m[3]);
        break;
    }
    sceVu0MulMatrix(w, D_00616040, m);
}

/* pppDrawMdl3Draw (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u8 flags; /* +0x8 */
    u8 b9, bA, bB, bC, bD, bE;
} DMdl3Key;
void pppDrawMdl3Draw(PppObject *obj, DMdl3Key *key, PppEntry *e) {
    DParam p;
    PppMtx mtx;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
    if (key->b9)
        p.flags |= 0x200;
    if (key->bB)
        p.flags |= 0x100;
    if (key->bA) {
        p.flags |= 0x2000;
        p.p30 = mtx;
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    }
    if (key->bC)
        p.p44 = PPP_WORK(u8, obj, e, 2);
    else
        p.p44 = 0;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
    p.p20 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4C = key->bD;
    p.b4D = key->bE;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

/* pppDrawMdlSemi3Draw (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u16 h8;   /* +0x8 */
    u8 flags; /* +0xA */
    u8 bB, bC, bD, bE;
} DSemi3Key;
void pppDrawMdlSemi3Draw(PppObject *obj, DSemi3Key *key, PppEntry *e) {
    DParam p;
    PppMtx mtx;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
    if (key->bB)
        p.flags |= 0x200;
    if (key->bD)
        p.flags |= 0x100;
    if (key->bC) {
        p.flags |= 0x2000;
        p.p30 = mtx;
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    }
    if (key->bE)
        p.p44 = PPP_WORK(u8, obj, e, 2);
    else
        p.p44 = 0;
/*P*/
    p.h08 = key->h8;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p20 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

/* pppDrawMdlTs3Frame (from hand/nostrict/text_00180000_h40.c). */
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

/* pppDrawMdlTs3Draw (from hand/nostrict/text_00180000_b07.c). */
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_95cc0;
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
    s32 unk90, unk94;
} PppMtxOwner_95cc0;
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
} PppMdlRes; /* 0x24 */
typedef struct {
    u8 pad[0x10];
    PppMdlRes *res; /* +0x10 */
    void *p14;
    VtxMap *maps;   /* +0x18 */
} PppMdlBank;
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
} PppMdlDraw;
typedef struct {
    u8 pad[8];
    u8 col[4];
} PppColWork;
typedef struct {
    u32 flags;  /* +0x0 */
    u8 pad04[0x12];
    u16 unk16;  /* +0x16 */
} Ts3Mdl;
typedef struct {
    s32 frame;
    s32 slot;     /* +0x4 */
    u8 pad8[0x18];
    u8 flags;     /* +0x20 */
    u8 f21, f22, f23, f24, f25;
} PppTs3Key;
#define D_00615E68 ((PppMtxOwner_95cc0 *) D_00615E68)
#define D_00615E64 ((PppMdlBank *) D_00615E64)
/* --- pppDrawMdlTs3Draw --- */
void pppDrawMdlTs3Draw(PppObject_95cc0 *obj, PppTs3Key *key, PppEntry *e) {
    PppMdlDraw p;
    PppMtx mtx;
    PppColWork *w;
    f32 *t = PPP_WORK(f32, obj, e, 2);
    PppMdlRes *s;
    Ts3Mdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(PppColWork, obj, e, 0);
    p.col[3] = w->col[3];
    if (p.col[3] == 0)
        return;
    s = &D_00615E64->res[key->slot];
    m = (Ts3Mdl *) s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
    if (key->f21)
        p.flags |= 0x200;
    if (key->f23)
        p.flags |= 0x100;
    if (key->f22) {
        p.flags |= 0x2000;
        p.mtx = mtx;
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    }
    if (key->f24)
        p.i44 = PPP_WORK(u8, obj, e, 3);
    else
        p.i44 = 0;
    p.h08 = m->unk16;
    p.b0A = 0;
    p.i1C = 0;
    p.i38 = D_00615E68->unk90;
    p.i3C = D_00615E68->unk94;
    p.i0C = 0;
    p.p04 = D_00616240;
    p.u = t[0] * 65536.0f;
    p.v = t[3] * 65536.0f;
    p.i40 = 0;
    p.col[0] = w->col[0];
    p.col[1] = w->col[1];
    p.col[2] = w->col[2];
    p.m2 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.m = D_00615E68->m;
    p.i34 = D_00616224;
    p.b4D = key->f25;
    p.b4C = 0;
    D_00616224 = func_001aaf88((s32 *) m, &p, s->arg);
}
#undef D_00615E68
#undef D_00615E64

#include "data/pieces/D_003701D0.h"
#include "data/pieces/D_003727B0.h"
#include "data/data_0037.h"
