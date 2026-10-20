/* ppp draw/frame callbacks around 0x197000-0x1a1000 (worker b08). This
 * region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    s32 unk0;
    u8 *inst;
    s32 time;
    s32 unkC;
} PppSlot;

typedef struct {
    u8 pad[0x80];
    PppSlot *slots;
    u8 pad84[0x2C];
    u64 flags;
} PppSystem;

extern s32 D_0061621C;
extern PppSystem *D_00615E60;

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame;
    u8 pad10[0x8D];
    u8 unk9D;
} PppObject;

typedef struct {
    u32 flags;
    u8 pad04[0x12];
    u16 unk16;
} DMdl;

typedef struct {
    s32 pad0[4];
    u32 tex;
    s32 pad14[2];
    DMdl *mdl;
    s32 unk20;
} DSlot;

typedef struct {
    u8 pad00[0x10];
    DSlot *slots;
    void *shapes;
} DSys;

extern DSys *D_00615E64;
extern s32 D_00616224;
s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, void *);
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
    s32 unk90;
    s32 unk94;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
extern PppMtx D_00615E70;
void func_002672f8(f32 *, PppMtx, f32 *);
void func_002675a8(f32 *, f32 *);
void func_001a9098(void *, void *);
typedef struct {
    s32 flags;
    void *p04;
    u16 h08;
    u8 b0A;
    s32 w0C;
    union { u64 d; struct { s32 u, v; } s; } t10;
    u8 r, g, b, a;
    s32 w1C;
    void *p20;
    void *p24;
    void *p28;
    void *p2C;
    void *p30;
    s32 w34;
    s32 w38;
    s32 w3C;
    s32 w40;
    void *p44;
    s32 w48;
    u8 b4C;
    u8 b4D;
    u8 pad4E[0x12];
} DParam;
typedef struct {
    u8 pad[8];
    u8 r, g, b, a;
} DColWork;
extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern PppMtx D_00615FC0;
s32 func_001aaf88(DMdl *, DParam *, s32);
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
void sceVu0UnitMatrix(PppMtx);
typedef struct {
    u16 unk0;
    u16 flags;
    u8 r, g, b, a;
    u64 d8;
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} DShpParam;
typedef struct {
    s16 off;
    s16 dur;
    s8 flags;
    u8 pad5[3];
} PppShapeFrame;
typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[8];
    PppShapeFrame f[1];
} PppShape;
typedef struct {
    PppShape *shape;
    s32 unk4;
} PppShapeEnt;
typedef struct {
    u8 pad00[0x14];
    PppShapeEnt *shapes;
} DSysS;
s32 func_001b8198(void *, DShpParam *, s32);
extern PppMtx D_00616040;
void func_00267518(f32 *, f32 *, f32 *);

typedef struct {
    PppVec4 pos;   /* +0x00 */
    PppVec4 vel;   /* +0x10 */
    u16 time;      /* +0x20 */
    u16 cur;       /* +0x22 */
    u16 prev;      /* +0x24 */
    u16 live;      /* +0x26 */
    s8 c[4];       /* +0x28 */
    f32 ang;       /* +0x2C */
    f32 angv;      /* +0x30 */
    f32 anga;      /* +0x34 */
    f32 sx, sy;    /* +0x38 */
    f32 svx, svy;  /* +0x40 */
    f32 sax, say;  /* +0x48 */
    f32 spd;       /* +0x50 */
    f32 grav;      /* +0x54 */
    f32 alpha;     /* +0x58 */
    u8 n;          /* +0x5C */
    u8 fin;        /* +0x5D */
    u8 fout;       /* +0x5E */
    u8 pad5F;
} MegaPart;
typedef struct {
    s32 frame;
    s32 id;         /* +0x04 */
    u8 pad8[4];
    u8 bC, bD, bE, bF;
    f32 v10[3];     /* +0x10 */
    u8 pad1C[6];
    u16 h22;
    u8 pad24;
    u8 b25;
    u8 pad26[0x12];
    f32 c38[4];     /* +0x38 */
    u8 pad48[0x1C];
    f32 svx, svy;   /* +0x64 */
    u8 pad6C[0x18];
    f32 angv;       /* +0x84 */
    u8 pad88[0x1C];
    f32 spdv;       /* +0xA4 */
    f32 spda;       /* +0xA8 */
    u8 padAC[8];
    f32 grav;       /* +0xB4 */
    u8 padB8[0x12];
    u8 bCA, bCB, bCC, bCD;
    u8 bCE;
} MegaKey;
typedef struct { u8 b[0x40]; } MegaA;
typedef struct { f32 f[8]; } MegaB;
typedef struct {
    PppMtx m;        /* +0x00 */
    PppVec4 v;       /* +0x40 */
    MegaPart *parts; /* +0x50 */
    MegaA *a;        /* +0x54 */
    MegaB *b;        /* +0x58 */
    s32 n;           /* +0x5C */
    u16 timer;       /* +0x60 */
} MegaObj;

typedef struct {
    s32 frame;
    s32 id;
    f32 da, db, dc;
    s32 u, v;
    u8 page;
    u8 pad1D[3];
    f32 dd, de, df, dg, dh, di;
    u8 b38, b39, b3A, b3B, b3C;
} PppTfdUv3Key;
typedef struct {
    f32 a, b, c, pc;
    f32 d, e, f;
    f32 g, h, i;
} PppTfdUv3;

void pppKeMdlTfdUv3Draw(PppObject *obj, PppTfdUv3Key *key, PppEntry *e) {
    PppTfdUv3 *w = PPP_WORK(PppTfdUv3, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->b += w->c;
        w->e += w->f;
        w->h += w->i;
        w->a += w->b;
        w->d += w->e;
        w->g += w->h;
        if (obj->frame == key->frame) {
            w->a += key->da;
            w->b += key->db;
            w->c += key->dc;
            w->d += key->dd;
            w->e += key->de;
            w->f += key->df;
            w->g += key->dg;
            w->h += key->dh;
            w->i += key->di;
        }
    }
    if (key->id == 0xFFFF)
        return;
    {
        DSlot *r = &D_00615E64->slots[key->id];
        tex = r->tex;
    }
    n = key->page * 4;
    p = (u8 *) D_00616224 + 16;
    sceGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w->a, key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    {
        void *w0 = PPP_WORK(void, obj, e, 0);
        void *w3 = PPP_WORK(void, obj, e, 3);
        func_001a9790(key->id, w0, n, (s32) w->d, (s32) w->g,
                      key->b38 | key->b39 | key->b3B | key->b3A | key->b3C, w3);
    }
}

typedef struct {
    u16 p0[4], p1[4], v0[4], a0[4], v1[4], a1[4];
} PppTail3X;
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[0x18];
    PppTail3X d;
    u8 pad50[3];
    u8 local;
} PppTail3XKey;
typedef struct {
    PppTail3X h;
    PppVec4 v[28];
    u8 padF0[0xA];
    u8 idx;
} PppTail3XWork;

void pppKeShpTail3XFrame(PppObject *obj, PppTail3XKey *key, PppEntry *e) {
    PppTail3XWork *w;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(PppTail3XWork, obj, e, 0);
    if (obj->frame == 0 && obj->unk9D == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local) {
            func_002672f8(v, D_00615E70, D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            func_002675a8(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = 28; n > 0; n--) {
            func_002675a8(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = 28;
    w->idx--;
    if (key->local) {
        func_002672f8(w->v[w->idx], D_00615E70, D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        func_002675a8(w->v[w->idx], D_00615E68->m[3]);
    }
    w->h.v0[0] += w->h.a0[0]; w->h.p0[0] += w->h.v0[0];
    w->h.v0[1] += w->h.a0[1]; w->h.p0[1] += w->h.v0[1];
    w->h.v0[2] += w->h.a0[2]; w->h.p0[2] += w->h.v0[2];
    w->h.v0[3] += w->h.a0[3]; w->h.p0[3] += w->h.v0[3];
    w->h.v1[0] += w->h.a1[0]; w->h.p1[0] += w->h.v1[0];
    w->h.v1[1] += w->h.a1[1]; w->h.p1[1] += w->h.v1[1];
    w->h.v1[2] += w->h.a1[2]; w->h.p1[2] += w->h.v1[2];
    w->h.v1[3] += w->h.a1[3]; w->h.p1[3] += w->h.v1[3];
    if (obj->frame == key->frame) {
        w->h.p0[0] += key->d.p0[0];
        w->h.p0[1] += key->d.p0[1];
        w->h.p0[2] += key->d.p0[2];
        w->h.p0[3] += key->d.p0[3];
        w->h.v0[0] += key->d.v0[0];
        w->h.v0[1] += key->d.v0[1];
        w->h.v0[2] += key->d.v0[2];
        w->h.v0[3] += key->d.v0[3];
        w->h.a0[0] += key->d.a0[0];
        w->h.a0[1] += key->d.a0[1];
        w->h.a0[2] += key->d.a0[2];
        w->h.a0[3] += key->d.a0[3];
        w->h.p1[0] += key->d.p1[0];
        w->h.p1[1] += key->d.p1[1];
        w->h.p1[2] += key->d.p1[2];
        w->h.p1[3] += key->d.p1[3];
        w->h.v1[0] += key->d.v1[0];
        w->h.v1[1] += key->d.v1[1];
        w->h.v1[2] += key->d.v1[2];
        w->h.v1[3] += key->d.v1[3];
        w->h.a1[0] += key->d.a1[0];
        w->h.a1[1] += key->d.a1[1];
        w->h.a1[2] += key->d.a1[2];
        w->h.a1[3] += key->d.a1[3];
    }
}

typedef struct {
    s32 frame;
    s32 slot;
    u8 flags;
    u8 b9, bA, bB, bC;
    u8 padD[8];
    u8 b15;
    u8 pad16[3];
    u8 b19;
} ShipolyDKey;
extern PppMtx D_00616180, D_00616080;
extern f32 D_003701D0[4];
void func_00267e40(f32 *, f32 *);

void pppRyjDrawShipolyDraw(PppObject *obj, ShipolyDKey *key, PppEntry *e) {
    DParam p;
    PppMtx mtx;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 1);
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
    p.p44 = 0;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p04 = D_00616240;
/*Q*/
    if (key->b15) {
        sceVu0UnitMatrix(D_00615E68->m2);
        func_00267e40(D_00615E68->m2[3], D_003701D0);
        sceVu0MulMatrix(D_00615E68->m2, D_00616180, D_00615E68->m2);
        p.p20 = D_00615E68->m2;
    } else {
        p.p20 = D_00616080;
    }
/*P*/
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.w0C = 0;
    p.t10.d = 0;
    p.w40 = 0;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4C = key->bC;
    p.b4D = key->b19;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

typedef struct {
    u8 b0;
    s8 type;
    s16 n;
    u8 pad4[12];
} ShipolyPrim;
typedef struct {
    s32 w0;
    s32 w4;
} ShipolyMdl;
typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 pad[4];
    ShipolyMdl *mdl;
    s32 unk20;
} ShipolySlot;
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[6];
    u8 n;
    u8 padF;
    u16 h10, h12;
    f32 f14;
    u16 h18, h1A;
    f32 f1C;
    u8 pad20[6];
    s16 h26;
    s16 h28;
} BoneKey;
typedef struct {
    u8 pad0[4];
    u8 n;
    u8 pad5[3];
    u8 *buf;
    u8 padC[4];
    PppVec4 v0;
    PppVec4 v1;
} BoneWork;
typedef struct {
    u8 c[4][4];
    u16 idx[4];
} ShipolyVtx;

typedef struct {
    u8 pad[0xA0];
    void *pA0;
    u8 padA4[0x13];
    u8 bB7;
} PppSystemB;
extern void *D_002E26A0;

extern void *D_002E26A0;
typedef struct {
    s32 frame;
    s32 slot;
    u8 flags;
    u8 b9, bA, bB, bC;
    u8 padD[0x17];
    u8 b24;
} BoneDKey;
extern PppMtx D_00616180;
void func_0019b460(PppObject *, BoneKey *, PppEntry *);

void pppRyjDrawShipolyBoneDraw(PppObject *obj, BoneDKey *key, PppEntry *e) {
    DParam p;
    PppMtx mtx;
    DColWork *w;
    DSlot *s;
    DMdl *m;
    u8 *a;

    func_0019b460(obj, (BoneKey *) key, e);
    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    a = D_002E26A0;
    if (((PppSystemB *) D_00615E60)->pA0)
        a = ((PppSystemB *) D_00615E60)->pA0;
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
    p.p44 = 0;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p04 = D_00616240;
/*Q*/
    sceVu0UnitMatrix(D_00615E68->m2);
    func_002675a8(D_00615E68->m2[3], (f32 *) (a + 16));
    sceVu0MulMatrix(D_00615E68->m2, D_00616180, D_00615E68->m2);
/*P*/
    p.p20 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.w0C = 0;
    p.t10.d = 0;
    p.w40 = 0;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4C = key->bC;
    p.b4D = key->b24;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

s32 func_0019bb98(MegaObj *, MegaKey *);
void func_0019cfc0(PppMtx, MegaKey *, MegaObj *);
void func_0019d020(PppMtx, PppMtx, MegaKey *, MegaObj *, MegaPart *, MegaA *, PppMtx, u8);
#define D_00616224 (*(volatile s32 *) &D_00616224)

void pppRyjMegaBirthDraw(PppObject *obj, MegaKey *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppMtx mtx;
    PppVec4 v;
    DShpParam p;
    MegaObj *w = PPP_WORK(MegaObj, obj, e, 2);
    DColWork *c = PPP_WORK(DColWork, obj, e, 1);
    MegaPart *pt = w->parts;
    MegaA *a = w->a;
    MegaB *b = w->b;
    s32 n = w->n;
    PppShapeEnt *s;
    PppShape *sh;
    s32 cr, cg, cb, ca;
    s32 i;

    if (!func_0019bb98(w, key))
        return;
    if (key->id == 0xFFFF)
        return;
    func_0019cfc0(m0, key, w);
    s = &((DSysS *) D_00615E64)->shapes[key->id];
    if (!key->bF)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->bCD == 1)
        p.flags |= 0x10;
    if (key->bC)
        p.flags |= 0x800;
    if (key->bD)
        p.flags |= 0x400;
    if (key->bE) {
        p.p1C = mtx;
        v[0] = key->v10[0];
        v[1] = key->v10[1];
        v[2] = key->v10[2];
        v[3] = 0.0f;
    } else {
        p.p1C = 0;
    }
    p.d8 = 0;
    p.b18 = 0;
    p.p10 = m1;
    sh = s->shape;
    cr = c->r;
    cg = c->g;
    cb = c->b;
    ca = c->a;
    for (i = 0; i < n; i++) {
        if (pt->live) {
            s32 r, g, bl, al;
            u8 *src;
            func_0019d020(m0, m1, key, w, pt, a, mtx, key->bE);
            if (key->bE) {
                func_00267518(mtx[3], mtx[3], v);
                sceVu0MulMatrix(mtx, D_00616040, mtx);
            }
            r = cr + pt->c[0];
            { PppShapeFrame *f = &sh->f[pt->prev]; src = (u8 *) sh + f->off; }
            al = (f32) ca + (f32) pt->c[3] - pt->alpha;
            g = cg + pt->c[1];
            bl = cb + pt->c[2];
            if (b) {
                r += (s32) b->f[0];
                g += (s32) b->f[1];
                bl += (s32) b->f[2];
                al += (s32) b->f[3];
            }
            if (r < 0) r = 0; else if (r >= 256) r = 255;
            if (g < 0) g = 0; else if (g >= 256) g = 255;
            if (bl < 0) bl = 0; else if (bl >= 256) bl = 255;
            if (al < 0) al = 0; else if (al >= 128) al = 127;
            p.r = r;
            p.g = g;
            p.b = bl;
            p.a = al;
            p.w14 = D_00616224;
            D_00616224 = func_001b8198(src, &p, s->unk4);
        }
        if (a)
            a++;
        if (b)
            b++;
        pt++;
    }
}
#undef D_00616224

typedef struct {
    s32 id;
    u8 r, g, b, a;
    f32 scale;
} PrizeEnt;
typedef struct {
    s32 frame;
    PrizeEnt ent[10];  /* +0x04 */
    u8 pad7C[0];
    u16 speed;         /* +0x7C */
    u8 pad7E[2];
    u8 b80, b81;
} PrizeKey;
typedef struct {
    f32 pos[3];
    f32 dist;   /* +0xC */
    f32 scale;  /* +0x10 */
    f32 alpha;  /* +0x14 */
    union {
        u64 flags;
        struct { u8 type; u8 pad[3]; s16 time; s16 frame; } s;
    } u;        /* +0x18 */
} PrizeObj;
extern PrizeObj *D_0061E310[];
extern s32 D_0061E710;
extern PppMtx D_00615EB0;
void func_0019dac8(void);
void func_00267560(f32 *, f32 *, f32);
void sceVu0CopyMatrix(PppMtx, PppMtx);

void pppRyjMegaBirthPrizeDraw(PppObject *obj, PrizeKey *key, PppEntry *e) {
    PppMtx m[10];
    DShpParam p;
    PrizeEnt *ents = key->ent;
    s32 i;

    p.flags = 0;
    if (key->b80)
        p.flags = 0x800;
    if (key->b81)
        p.flags |= 0x400;
    p.p1C = 0;
    p.d8 = 0;
    p.b18 = 0;
    p.p10 = D_00615E68->m2;
    for (i = 0; i < 10; i++) {
        PrizeEnt *pe = &ents[i];
        sceVu0UnitMatrix(m[i]);
        func_00267560(m[i][0], m[i][0], pe->scale);
        func_00267560(m[i][1], m[i][1], pe->scale);
        func_00267560(m[i][2], m[i][2], pe->scale);
    }
    func_0019dac8();
    for (i = 0; i < D_0061E710; i++) {
        PrizeObj *o = D_0061E310[i];
        PrizeEnt *en;
        PppShapeEnt *s;
        PppShape *sh;
        PppShapeFrame *fr;
        u8 *src;
        s32 t;
        f32 al;
        f32 (*mm)[4];
        s32 fi;

        if (o->u.flags & 0x400) {
            o->u.s.time = 0;
            o->u.s.frame = 0;
            o->u.flags &= ~0x400;
        }
        t = o->u.s.type;
        al = o->alpha;
        en = (PrizeEnt *) (t * 12 + (u32) ents);
        fi = o->u.s.frame;
        if (en->id == 0xFFFF)
            continue;
        mm = m[t];
        s = &((DSysS *) D_00615E64)->shapes[en->id];
        p.r = en->r;
        p.g = en->g;
        p.b = en->b;
        p.a = en->a * al;
        sh = s->shape;
        fr = &sh->f[fi];
        src = (u8 *) sh + fr->off;
        sceVu0CopyMatrix(D_00615E68->m2, mm);
        func_002672f8(D_00615E68->m2[3], D_00615EB0, o->pos);
        func_00267560(D_00615E68->m2[0], D_00615E68->m2[0], o->scale);
        func_00267560(D_00615E68->m2[1], D_00615E68->m2[1], o->scale);
        func_00267560(D_00615E68->m2[2], D_00615E68->m2[2], o->scale);
        sceVu0MulMatrix(D_00615E68->m2, D_00616040, D_00615E68->m2);
        {
            s32 *gp = &D_00616224;
            p.w14 = *gp;
            *gp = func_001b8198(src, &p, s->unk4);
        }
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
            continue;
        o->u.s.time += key->speed;
        if (o->u.s.time >= fr->dur) {
            o->u.s.time -= fr->dur;
            o->u.s.frame++;
            if (o->u.s.frame >= sh->n) {
                if (fr->flags & 0x80) {
                    o->u.s.frame = 0;
                    o->u.s.time = 0;
                } else {
                    o->u.s.frame--;
                    o->u.s.time = 0;
                }
            }
        }
    }
}

typedef struct {
    s32 frame;
    s32 unk4;
    s32 id;        /* +0x08 */
    u16 speed;     /* +0x0C */
    u8 padE[2];
    u8 b10, b11, b12, b13;
    f32 ofs[3];    /* +0x14 */
    u8 pad20[0xC];
    f32 sx, sy, sz; /* +0x2C */
    u8 r, g, b, a; /* +0x38 */
    u8 mode;       /* +0x3C */
} RKey;
typedef struct {
    f32 pos[4];
    RKey *key;     /* +0x10 */
    void *p14;     /* +0x14 */
    u16 time;      /* +0x18 */
    u16 frame;     /* +0x1A */
    u8 pad1C[4];
} RItem;
typedef struct {
    u32 n;
    u8 pad4[8];
    RItem *items;  /* +0x0C */
} RList;
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);

void func_0019e3f0(RList *l) {
    DShpParam p;
    PppMtx mtx;
    u32 i;

    i = 0;
    p.d8 = 0;
    p.p10 = D_00615E68->m2;
    p.b18 = 0;
    for (; i < l->n; i++) {
        RItem *it = &l->items[i];
        RKey *k = it->key;
        PppShapeEnt *s;
        PppShape *sh;
        PppShapeFrame *fr;
        u8 *src;
        u32 fi;

        if (k == 0 || it->p14 == 0)
            continue;
        if (!k->a)
            continue;
        p.flags = 0;
        if (k->mode == 1)
            p.flags = 16;
        if (k->b10)
            p.flags |= 0x800;
        if (k->b11)
            p.flags |= 0x400;
        fi = it->frame;
        if (k->id == 0xFFFF)
            continue;
        s = &((DSysS *) D_00615E64)->shapes[k->id];
        p.r = k->r;
        p.g = k->g;
        p.b = k->b;
        p.a = k->a;
        sh = s->shape;
        fr = &sh->f[fi];
        src = (u8 *) sh + fr->off;
        p.p1C = 0;
        sceVu0UnitMatrix(D_00615E68->m2);
        D_00615E68->m2[0][0] = k->sx;
        D_00615E68->m2[1][1] = k->sy;
        D_00615E68->m2[2][2] = k->sz;
        func_002672f8(D_00615E68->m2[3], D_00615EB0, it->pos);
        if (k->b13) {
            sceVu0CopyMatrix(mtx, D_00615E68->m2);
            mtx[3][0] += k->ofs[0];
            mtx[3][1] += k->ofs[1];
            mtx[3][2] += k->ofs[2];
            sceVu0MulMatrix(mtx, D_00616040, mtx);
            p.p1C = mtx;
        }
        sceVu0MulMatrix(D_00615E68->m2, D_00616040, D_00615E68->m2);
        {
            s32 *gp = &D_00616224;
            p.w14 = *gp;
            *gp = func_001b8198(src, &p, s->unk4);
        }
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
            continue;
        it->time += k->speed;
        if (it->time >= fr->dur) {
            it->time -= fr->dur;
            it->frame++;
            if (it->frame >= sh->n) {
                if (fr->flags & 0x80) {
                    it->frame = 0;
                    it->time = 0;
                } else {
                    it->frame--;
                    it->time = 0;
                }
            }
        }
    }
}

typedef struct {
    s32 frame;
    s32 unk4;
    s32 id;        /* +0x08 */
    u8 flags, bD, bE, bF;
    u8 b10, b11, b12, b13;
    f32 ofs[3];    /* +0x14 */
    u8 pad20[0xC];
    f32 rot[3];    /* +0x2C */
    f32 sx, sy, sz; /* +0x38 */
    u8 r, g, b, a; /* +0x44 */
    u8 b48;        /* +0x48 */
} MKey;
typedef struct {
    f32 pos[4];
    MKey *key;     /* +0x10 */
    void *p14;     /* +0x14 */
    u8 pad18[8];
} MItem;
typedef struct {
    u32 unk0;
    u32 n;         /* +0x04 */
    u8 pad8[8];
    MItem *items;  /* +0x10 */
} MList;
extern PppMtx D_00615EB0, D_00616180;
void func_00183be0(PppMtx, f32 *);

static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}

void func_0019e710(MList *l) {
    PppMtx mtx;
    DParam p;
    u32 i;

    p.p2C = 0;
    p.p28 = 0;
    p.p24 = 0;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p04 = D_00616240;
    p.w0C = 0;
    p.t10.d = 0;
    p.p20 = D_00615E68->m2;
    p.w40 = 0;

    for (i = 0; i < l->n; i++) {
        MItem *it = &l->items[i];
        MKey *k = it->key;
        DSlot *s;
        DMdl *m;

        if (k == 0 || it->p14 == 0)
            continue;
        if (!k->a)
            continue;
        if (k->id == 0xFFFF)
            continue;
        func_00183be0(D_00615E68->m, k->rot);
        vu0ScaleRow(D_00615E68->m[0], k->sx);
        vu0ScaleRow(D_00615E68->m[1], k->sy);
        vu0ScaleRow(D_00615E68->m[2], k->sz);
        func_002675a8(D_00615E68->m[3], it->pos);
        if (k->b11) {
            sceVu0MulMatrix(mtx, D_00615EB0, D_00615E68->m);
            mtx[3][0] += k->ofs[0];
            mtx[3][1] += k->ofs[1];
            mtx[3][2] += k->ofs[2];
            sceVu0MulMatrix(mtx, D_00616040, mtx);
            p.p44 = mtx;
        } else {
            p.p44 = 0;
        }
        sceVu0MulMatrix(D_00615E68->m2, D_00616180, D_00615E68->m);
        s = &D_00615E64->slots[k->id];
        m = s->mdl;
        p.flags = 0;
        if (k->flags & 2) {
            p.flags = 4;
            if (!(m->flags & 1))
                p.flags |= 8;
        } else {
            if (k->flags & 1)
                p.flags = 128;
            if (!(m->flags & 1))
                p.flags |= 8;
        }
        if (!(m->flags & 2))
            p.flags |= 16;
        if (k->bD)
            p.flags |= 0x200;
        if (k->bF)
            p.flags |= 0x100;
        p.h08 = m->unk16;
        p.r = k->r;
        p.g = k->g;
        p.b = k->b;
        p.a = k->a;
        p.b4C = k->b10;
        p.b4D = k->b48;
        p.w34 = D_00616224;
        D_00616224 = func_001aaf88(m, &p, s->unk20);
    }
}

typedef struct {
    s32 frame;
    s32 unk4;
    s32 id;        /* +0x08 */
    u16 speed;     /* +0x0C */
    u8 padE[2];
    u8 b10, b11, b12, b13;
    f32 ofs[3];    /* +0x14 */
    u8 pad20[0x10];
    f32 sx, sy, sz; /* +0x30 */
    u8 r, g, b, a; /* +0x3C */
    u8 b40, b41, b42, b43;
    u8 mode;       /* +0x44 */
} FKey;
typedef struct {
    f32 pos[4];
    FKey *key;     /* +0x10 */
    void *p14;     /* +0x14 */
    u16 time;      /* +0x18 */
    u16 frame;     /* +0x1A */
    u8 c0, c1;     /* +0x1C */
    u16 dec;       /* +0x1E */
    s32 val;       /* +0x20 */
    u8 pad24[0xC];
} FItem;
typedef struct {
    u32 unk0;
    u32 unk4;
    u32 n;         /* +0x08 */
    u8 padC[8];
    FItem *items;  /* +0x14 */
} FList;
extern PppMtx D_00615EB0;
extern f32 D_003732D0[];
void sceVu0CopyMatrix(PppMtx, PppMtx);

void func_0019ea58(FList *l) {
    DShpParam p;
    PppMtx mtx;
    u32 i;
    u32 off;

    i = 0;
    p.d8 = 0;
    p.p10 = D_00615E68->m2;
    p.b18 = 0;
    if (i < l->n) {
    off = 0;
    do {
        FItem *it = (FItem *) ((u8 *) l->items + off);
        FKey *k = it->key;
        PppShapeEnt *s;
        PppShape *sh;
        PppShapeFrame *fr;
        u8 *src;
        u32 fi;
        f32 f;
        s32 a;
        FKey *k1, *k2;

        if (k == 0 || it->p14 == 0)
            continue;
        if (--it->c0 == 255) {
            it->c0 = k->b40;
            if (it->val == 0)
                it->val = 32767;
        }
        if (--it->c1 == 255) {
            it->c1 = k->b41;
            if (it->val == 0)
                it->val = 32767;
        }
        if (it->val != 0) {
            s32 v = it->val - it->dec;
            if (v < 0)
                v = 0;
            it->val = v;
        }
        p.flags = 0;
        if (k->mode == 1)
            p.flags = 16;
        if (k->b10)
            p.flags |= 0x800;
        if (k->b11)
            p.flags |= 0x400;
        fi = it->frame;
        if (k->id == 0xFFFF)
            continue;
        s = &((DSysS *) D_00615E64)->shapes[k->id];
        p.r = k->r;
        p.g = k->g;
        p.b = k->b;
        f = D_003732D0[(it->val & 0xFFFF) >> 4];
        if (f < 0.0f)
            f = -f;
        k1 = k;
        k2 = k;
        a = k->a - (u8) (k->b43 * f);
        if (a < 0)
            a = 0;
        p.a = a;
        sh = s->shape;
        fr = &sh->f[fi];
        src = (u8 *) sh + fr->off;
        p.p1C = 0;
        sceVu0UnitMatrix(D_00615E68->m2);
        D_00615E68->m2[0][0] = k2->sx;
        D_00615E68->m2[1][1] = k1->sy;
        D_00615E68->m2[2][2] = k1->sz;
        func_002672f8(D_00615E68->m2[3], D_00615EB0, it->pos);
        if (k1->b12) {
            sceVu0CopyMatrix(mtx, D_00615E68->m2);
            mtx[3][0] += k1->ofs[0];
            mtx[3][1] += k1->ofs[1];
            mtx[3][2] += k1->ofs[2];
            sceVu0MulMatrix(mtx, D_00616040, mtx);
            p.p1C = mtx;
        }
        sceVu0MulMatrix(D_00615E68->m2, D_00616040, D_00615E68->m2);
        {
            s32 *gp = &D_00616224;
            p.w14 = *gp;
            *gp = func_001b8198(src, &p, s->unk4);
        }
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
            continue;
        it->time += k1->speed;
        if (it->time >= fr->dur) {
            it->time -= fr->dur;
            it->frame++;
            if (it->frame >= sh->n) {
                if (fr->flags & 0x80) {
                    it->frame = 0;
                    it->time = 0;
                } else {
                    it->frame--;
                    it->time = 0;
                }
            }
        }
    } while (i++, off += 48, i < l->n);
    }
}

typedef struct {
    u8 pad0[0x10];
    PppVec4 vel;     /* +0x10 */
    u8 pad20[0x10];
    PppVec4 pos;     /* +0x30 */
    u16 live;        /* +0x40 */
    u8 pad42[6];
    s32 ang[3];      /* +0x48 */
    s32 angv[3];     /* +0x54 */
    s32 anga[3];     /* +0x60 */
    f32 sc[3];       /* +0x6C */
    f32 scv[3];      /* +0x78 */
    f32 sca[3];      /* +0x84 */
    f32 spd;         /* +0x90 */
    f32 grav;        /* +0x94 */
    f32 sx, sy;      /* +0x98 */
    f32 svx, svy;    /* +0xA0 */
    f32 alpha;       /* +0xA8 */
    u8 n, fin, fout; /* +0xAC */
} MPart;
typedef struct {
    u8 pad0[0x22];
    u16 h22;
    u8 pad24;
    u8 b25;
    u8 pad26[0x12];
    f32 c38[4];      /* +0x38 */
    u8 pad48[0x1C];
    s32 angv[3];     /* +0x64 */
    u8 pad70[0x24];
    f32 scv[3];      /* +0x94 */
    u8 padA0[0x14];
    f32 svx;         /* +0xB4 */
    u8 padB8[8];
    f32 svy;         /* +0xC0 */
    u8 padC4[0x18];
    f32 spdv;        /* +0xDC */
    f32 spda;        /* +0xE0 */
    u8 padE4[8];
    f32 grav;        /* +0xEC */
    u8 padF0[0x12];
    u8 b102, b103;
    u8 pad104[7];
    u8 b10B;
} MKeyM;

void func_001a0190(f32 *w, MKeyM *key, MPart *pt, DColWork *c, f32 *b) {
    s32 a = c->a;
    s32 i;

    if (b) {
        f32 t;
        b[0] += b[4];
        b[1] += b[5];
        b[2] += b[6];
        b[3] += b[7];
        t = b[3];
        b[4] += key->c38[0];
        b[5] += key->c38[1];
        b[6] += key->c38[2];
        b[7] += key->c38[3];
        a = c->a + (s32) t;
        if (a >= 256)
            a = 255;
    }
    for (i = 0; i < 3; i++)
        pt->ang[i] += pt->angv[i];
    if (key->b103 & 0x10) {
        pt->angv[0] += key->angv[0] + pt->anga[0];
        pt->angv[1] += key->angv[1] + pt->anga[1];
        pt->angv[2] += key->angv[2] + pt->anga[2];
    } else {
        pt->angv[0] += key->angv[0];
        pt->angv[1] += key->angv[1];
        pt->angv[2] += key->angv[2];
    }
    for (i = 0; i < 3; i++) {
        if (pt->ang[i] > 32767) {
            while (pt->ang[i] > 32767)
                pt->ang[i] -= 0x10000;
        } else if (pt->ang[i] < -32768) {
            while (pt->ang[i] > 32767)
                pt->ang[i] += 0x10000;
        }
    }
    for (i = 0; i < 3; i++)
        pt->sc[i] += pt->scv[i];
    if (key->b102 & 0x10) {
        pt->scv[0] += key->scv[0] + pt->sca[0];
        pt->scv[1] += key->scv[1] + pt->sca[1];
        pt->scv[2] += key->scv[2] + pt->sca[2];
    } else {
        pt->scv[0] += key->scv[0];
        pt->scv[1] += key->scv[1];
        pt->scv[2] += key->scv[2];
    }
    pt->spd += key->spda;
    if (!key->b10B) {
        if (0.0f < key->spdv && key->spda < 0.0f) {
            if (pt->spd < 0.0f)
                pt->spd = 0.0f;
        } else if (key->spdv < 0.0f && 0.0f < key->spda) {
            if (0.0f < pt->spd)
                pt->spd = 0.0f;
        }
    }
    pt->grav += key->grav;
    __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf3\n"
        "lqc2 $vf4, 0(%3)\n"
        "lw $9, 0(%4)\n"
        "qmtc2 $9, $vf5\n"
        "vmulx.xyz $vf2xyz, $vf2xyz, $vf3x\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "vadd.xyz $vf1xyz, $vf1xyz, $vf2xyz\n"
        "vadd.xyz $vf1xyz, $vf1xyz, $vf4xyz\n"
        "sqc2 $vf1, 0(%0)\n"
        : : "r"(pt->pos), "r"(pt->vel), "r"(&pt->spd), "r"(w), "r"(&pt->grav)
        : "$8", "$9", "memory");
    pt->sx += pt->svx;
    pt->sy += pt->svy;
    pt->svx += key->svx;
    pt->svy += key->svy;
    if (key->h22)
        pt->live--;
    pt->n++;
    if (pt->fin && pt->n <= pt->fin)
        pt->alpha -= (f32) a / (f32) pt->fin;
    if (pt->fout && pt->fout >= pt->live)
        pt->alpha += (f32) a / (f32) key->b25;
}

typedef struct {
    PppMtx m;        /* +0x00 */
    u16 live;        /* +0x40 */
    s8 c[4];         /* +0x42 */
    u8 pad46[0x52];
    f32 sx, sy;      /* +0x98 */
    u8 padA0[8];
    f32 alpha;       /* +0xA8 */
    u8 padAC[4];
} MdPart; /* 0xB0 */
typedef struct {
    s32 frame;
    s32 id;          /* +0x04 */
    u8 flags, b9, bA, bB, bC, bD, bE, bF;
    f32 v10[3];      /* +0x10 */
    u8 pad1C[0xEE];
    u8 b10A;         /* +0x10A */
} MdKey;
typedef struct {
    PppVec4 v;       /* +0x00 */
    MdPart *parts;   /* +0x10 */
    MegaA *a;        /* +0x14 */
    MegaB *b;        /* +0x18 */
    s32 n;           /* +0x1C */
} MdObj;
s32 func_0019f1a8(MdObj *, MdKey *);
void func_001a0908(PppMtx, MdKey *, MdObj *);
void func_001a09d0(PppMtx, PppMtx, MdKey *, MdPart *, MegaA *, PppMtx, u8);
#define D_00616224 (*(volatile s32 *) &D_00616224)

void pppRyjMegaBirthModelDraw(PppObject *obj, MdKey *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppMtx mtx;
    PppVec4 v;
    DParam p;
    MdObj *w = PPP_WORK(MdObj, obj, e, 2);
    DColWork *c = PPP_WORK(DColWork, obj, e, 1);
    MdPart *pt = w->parts;
    MegaA *a = w->a;
    MegaB *b = w->b;
    s32 n = w->n;
    DSlot *s;
    DMdl *m;
    s32 cr, cg, cb, ca;
    s32 i;

    if (!func_0019f1a8(w, key))
        return;
    if (key->id == 0xFFFF)
        return;
    func_001a0908(m0, key, w);
    s = &D_00615E64->slots[key->id];
    m = s->mdl;
    if (key->bD) {
        p.p44 = mtx;
        v[0] = key->v10[0];
        v[1] = key->v10[1];
        v[2] = key->v10[2];
        v[3] = 0.0f;
    } else {
        p.p44 = 0;
    }
    p.p2C = 0;
    p.p28 = 0;
    p.p24 = 0;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p20 = m1;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
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
    p.h08 = m->unk16;
    cr = c->r;
    cg = c->g;
    cb = c->b;
    ca = c->a;
    p.b4C = key->bC;
    p.b4D = key->b10A;
    for (i = 0; i < n; i++) {
        if (pt->live) {
            s32 r, g, bl, al;
            func_001a09d0(m0, m1, key, pt, a, mtx, key->bD);
            if (key->bD) {
                func_00267518(mtx[3], mtx[3], v);
                sceVu0MulMatrix(mtx, D_00616040, mtx);
            }
            r = cr + pt->c[0];
            g = cg + pt->c[1];
            al = (f32) ca + (f32) pt->c[3] - pt->alpha;
            bl = cb + pt->c[2];
            if (b) {
                r += (s32) b->f[0];
                g += (s32) b->f[1];
                bl += (s32) b->f[2];
                al += (s32) b->f[3];
            }
            if (r < 0) r = 0; else if (r >= 256) r = 255;
            if (g < 0) g = 0; else if (g >= 256) g = 255;
            if (bl < 0) bl = 0; else if (bl >= 256) bl = 255;
            if (al < 0) al = 0; else if (al >= 128) al = 127;
            p.r = r;
            p.g = g;
            p.b = bl;
            p.a = al;
            p.t10.s.u = pt->sx * 65536.0f;
            p.t10.s.v = pt->sy * 65536.0f;
            p.w34 = D_00616224;
            D_00616224 = func_001aaf88(m, &p, s->unk20);
        }
        if (a)
            a++;
        if (b)
            b++;
        pt++;
    }
}
#undef D_00616224

/* needs make: uses rodata */

typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[6];
    u8 n;
} ShipolyKey;
typedef struct {
    u8 pad0[4];
    u8 n;
    u8 pad5[3];
    u8 *buf;
} ShipolyWork;

void *func_0017f958(void *, s32);
void func_00199908(ShipolyKey *, u8 *, u8 *);
s32 func_00199ac8(ShipolySlot *, ShipolyKey *, ShipolyWork *);

void pppRyjDrawShipolyFrame(PppObject *obj, ShipolyKey *key, PppEntry *e) {
    ShipolyWork *w = PPP_WORK(ShipolyWork, obj, e, 2);
    ShipolySlot *r;
    ShipolyPrim *p;
    s32 i, j, k, sz;
    u8 *q;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->id == 0xFFFF)
        return;
    r = &((ShipolySlot *) D_00615E64->slots)[key->id];
    if (w->buf == 0) {
        w->n = key->n;
        if (w->n < 4)
            w->n = 4;
        else if (w->n >= 32)
            w->n = 32;
        w->buf = func_0017f958(D_00615E64, w->n << 5);
        for (i = 0; i < w->n; i++)
            func_00199908(key, w->buf + i * 32, w->buf + i * 32 + 16);
    }
    k = 0;
    p = (ShipolyPrim *) ((u8 *) r->mdl + r->mdl->w4);
    while (p->type != -1) {
        sz = 0;
        switch (p->type) {
        case 4:
            q = (u8 *) p + 16;
            for (j = 0; j < p->n; j++) {
                ((u16 *) (q + 16))[0] = k * 2;
                ((u16 *) (q + 16))[1] = k * 2 + 1;
                ((u16 *) (q + 16))[2] = k * 2 + 2;
                ((u16 *) (q + 16))[3] = k * 2 + 3;
                k++;
                q += 24;
            }
            sz = 24;
            break;
        case 6:
            q = (u8 *) p + 16;
            for (j = 0; j < p->n; j++) {
                ((u16 *) (q + 16))[0] = k * 2;
                ((u16 *) (q + 16))[1] = k * 2 + 1;
                ((u16 *) (q + 16))[2] = k * 2 + 2;
                ((u16 *) (q + 16))[3] = k * 2 + 3;
                k++;
                q += 40;
            }
            sz = 40;
            break;
        case 0: case 1: case 2: case 3: case 5: case 7:
            return;
        }
        p = (ShipolyPrim *) ((u8 *) p + sz * p->n);
        p++;
    }
    if (r->w0 != r->w8 * 2 + 2)
        return;
    func_00199ac8(r, key, w);
}

void *func_0017f958(void *, s32);
s32 func_00122ff8(void *);
void func_001315c0(void *, s32, f32, f32 *);
void func_0019ab38(ShipolySlot *, BoneKey *, BoneWork *);

void func_0019b460(PppObject *obj, BoneKey *key, PppEntry *e) {
    BoneWork *w = PPP_WORK(BoneWork, obj, e, 1);
    ShipolySlot *r;
    ShipolyPrim *p;
    s32 i, j, k, sz;
    u8 *q;

    if (key->id == 0xFFFF)
        return;
    if (w->buf == 0) {
        void *a;
        s32 b0, b1;
        w->n = key->n;
        w->buf = func_0017f958(D_00615E64, w->n << 5);
        a = D_002E26A0;
        if (((PppSystemB *) D_00615E60)->pA0)
            a = ((PppSystemB *) D_00615E60)->pA0;
        if (key->h26 >= 0)
            b0 = (s16) (key->h26 | 0x1000);
        else
            b0 = key->h10 * 4 + key->h12;
        if (key->h28 >= 0)
            b1 = (s16) (key->h28 | 0x1000);
        else
            b1 = key->h18 * 4 + key->h1A;
        if (func_00122ff8(a)) {
            func_001315c0(a, b0, key->f14, w->v0);
            func_001315c0(a, b1, key->f1C, w->v1);
        } else {
            ((PppSystemB *) D_00615E60)->bB7 = 1;
        }
        for (i = 0; i < w->n; i++) {
            func_002675a8((f32 *) (w->buf + i * 32), w->v0);
            func_002675a8((f32 *) (w->buf + i * 32 + 16), w->v1);
        }
    }
    r = &((ShipolySlot *) D_00615E64->slots)[key->id];
    k = 0;
    p = (ShipolyPrim *) ((u8 *) r->mdl + r->mdl->w4);
    while (p->type != -1) {
        sz = 0;
        switch (p->type) {
        case 4:
            q = (u8 *) p + 16;
            for (j = 0; j < p->n; j++) {
                ShipolyVtx *v = (ShipolyVtx *) q;
                v->idx[0] = k * 2;
                v->idx[1] = k * 2 + 1;
                v->idx[2] = k * 2 + 2;
                v->idx[3] = k * 2 + 3;
                k++;
                v->c[0][2] = v->c[1][2] = v->c[2][2] = v->c[3][2] = 0xFF;
                v->c[0][1] = v->c[1][1] = v->c[2][1] = v->c[3][1] = 0xFF;
                v->c[0][0] = v->c[1][0] = v->c[2][0] = v->c[3][0] = 0xFF;
                q += 24;
            }
            sz = 24;
            break;
        case 6:
            q = (u8 *) p + 16;
            for (j = 0; j < p->n; j++) {
                ShipolyVtx *v = (ShipolyVtx *) q;
                v->idx[0] = k * 2;
                v->idx[1] = k * 2 + 1;
                v->idx[2] = k * 2 + 2;
                v->idx[3] = k * 2 + 3;
                k++;
                v->c[0][2] = v->c[1][2] = v->c[2][2] = v->c[3][2] = 0xFF;
                v->c[0][1] = v->c[1][1] = v->c[2][1] = v->c[3][1] = 0xFF;
                v->c[0][0] = v->c[1][0] = v->c[2][0] = v->c[3][0] = 0xFF;
                q += 40;
            }
            sz = 40;
            break;
        case 0: case 1: case 2: case 3: case 5: case 7:
            return;
        }
        p = (ShipolyPrim *) ((u8 *) p + sz * p->n);
        p++;
    }
    if (r->w0 == r->w8 * 2 + 2)
        func_0019ab38(r, key, w);
}
