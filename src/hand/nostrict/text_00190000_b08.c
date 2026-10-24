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
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

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

extern DSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
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
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
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
#include "data/pieces/D_003701D0.h"
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
        func_00267e40(D_00615E68->m2[3], (*(f32 (*)[4])&D_003701D0));
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
#include "data/pieces/D_002E26A0.h"

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
    void *a; /* the actor (D_002E26A0[0]) or pA0 */

    func_0019b460(obj, (BoneKey *) key, e);
    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    a = D_002E26A0[0];
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
#define D_00616224 (*(volatile s32 *) &D_00616224)
#undef D_00616224
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);
extern PppMtx D_00615EB0, D_00616180;

static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);
#define D_00616224 (*(volatile s32 *) &D_00616224)
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
        a = D_002E26A0[0];
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
#include "data/data_0037.h"
