/* The pppKeMdlTfd3 and pppKeMdlTfdUv3 classes' draws, -fno-strict-aliasing
 * (docs/modules.md "Session 50"): a model whose texture fades (Tfd) or
 * scrolls (TfdUv) by a value with speed and acceleration in the work area;
 * each draw rebuilds a 16x16 texture page with kemdltfd.c's func_001a9460 /
 * func_001a9790, uploads it (sceGsSetDefLoadImage, opdma.c's func_001aa6b0)
 * and draws the model.  Read from the code, not proved by a boot. */

/* pppKeMdlTfd3Draw (from hand/nostrict/text_00190000_h64.c). */
#include "common.h"
#include "platform/gs.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/pieces/D_003701F0.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
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
extern s32 D_00616224;
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, void *);
typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    f32 da, db, dc; /* +0x8 */
    s32 u, v;     /* +0x14 */
    u8 page;      /* +0x1C */
    u8 b1D, b1E, b1F, b20, b21;
} PppTfd3Key;
typedef struct {
    f32 a, b, c;
} PppTfd;
void pppKeMdlTfd3Draw(PppObject *obj, PppTfd3Key *key, PppEntry *e) {
    PppTfd *w = PPP_WORK(PppTfd, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->b += w->c;
        w->a += w->b;
        if (obj->frame == key->frame) {
            w->a += key->da;
            w->b += key->db;
            w->c += key->dc;
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
    PlatGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w->a, key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    {
        void *w0 = PPP_WORK(void, obj, e, 0);
        void *w3 = PPP_WORK(void, obj, e, 3);
        func_001a9790(key->id, w0, n, 0, 0,
                      key->b1D | key->b1E | key->b20 | key->b1F | key->b21, w3);
    }
}

/* pppKeMdlTfdUv3Draw (from hand/nostrict/text_00190000_b08.c). */
typedef struct {
    u8 pad00[0x10];
    DSlot *slots;
    void *shapes;
} DSys_96198;
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
#define D_00615E64 ((DSys_96198 *) D_00615E64)
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
    PlatGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
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
#undef D_00615E64

#include "data/data_0037.h"
