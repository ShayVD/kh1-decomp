#include "ppp.h"

/* A sprite record from a count-prefixed list: +2/+4 are its width and
 * height (0 means default), +0x10 its data. */
typedef struct {
    s16 unk00, w, h;
    s16 pad06[5];
    u8 data[1]; /* +0x10 */
} H39Spr;

void func_00180180(void *, H39Spr *, s16, s16);
void func_0017ffd8(void *, H39Spr *, s16, s16);

s32 *func_001805b8(s32 *p, u8 *mask, s16 w, s16 h) {
    s32 n;
    s32 i;
    u8 m;

    i = 0;
    m = 0;
    n = *p++;
    for (; i < n; i++, m >>= 1) {
        H39Spr *s = (H39Spr *) *p++;
        s32 k = i >> 3;

        if (!(i & 7))
            m = mask[k];
        if (m & 1) {
            u8 *d = s->data;

            if (s->w == 0)
                s->w = 0x3800;
            if (s->h == 0)
                s->h = 0x3D40;
            func_00180180(d, s, w, h);
            if (w)
                s->w = w;
            if (h)
                s->h = h;
        }
    }
    return p;
}

s32 *func_001806c8(s32 *p, u8 *mask, s16 w, s16 h) {
    s32 n;
    s32 i;
    u8 m;

    i = 0;
    m = 0;
    n = *p++;
    for (; i < n; i++, m >>= 1) {
        H39Spr *s = (H39Spr *) *p++;
        s32 k = i >> 3;

        if (!(i & 7))
            m = mask[k];
        if (m & 1) {
            u8 *d = s->data;

            if (s->w == 0)
                s->w = 0x3800;
            if (s->h == 0)
                s->h = 0x3D40;
            func_0017ffd8(d, s, w, h);
            if (w)
                s->w = w;
            if (h)
                s->h = h;
        }
    }
    return p;
}

/* sceGsLoadImage packet (0x60 bytes). */
typedef struct {
    u64 q[12];
} H39LoadImage;

/* A texture image header: +2 its VRAM base (>= 0x3D40: relative to the
 * caller's base), +6 its pixel format, +0x18 the offset of its pixels
 * (from +0x20). */
typedef struct {
    s16 unk00, dbp;
    s16 unk04, psm;
    s32 pad08[4];
    s32 off18;
} H39Img;

void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void sceGsSetDefLoadImage(H39LoadImage *, s16, s16, s16, s16, s16, s16, s16);
s32 sceGsExecLoadImage(H39LoadImage *, void *);

typedef struct { s16 dbp, b, c, d, e, f, g, h; s32 pad[4]; u8 data[1]; } AB;
void func_00180ab8(AB *a, s16 base) {
    H39LoadImage li; s16 v = a->dbp;
    if (v >= 0x3800) v = v + base - 0x3800;
    sceGsSetDefLoadImage(&li, v, a->c, a->d, a->e, a->f, a->g, a->h);
    FlushCache(0); sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&li, a->data);
}

s32 *func_001803b8(s32 *);
s32 *func_001803c0(s32 *, s32);
/* needs func_00180ab8 defined above */
void func_00180c20(s32 *data, u8 *mask, s16 base) {
    s32 *p;
    s32 n;
    s32 i;
    u8 m;

    i = 0;
    m = 0;
    p = func_001803c0(func_001803b8(data), 1);
    n = *p++;
    for (; i < n; i++, m >>= 1) {
        void *s = (void *) *p++;
        s32 k = i >> 3;
        s32 j = i & 7;
        if (!j)
            m = mask[k];
        if (m & 1)
            func_00180ab8(s, base);
    }
}

void func_00180b40(H39Img *img, s16 base) {
    H39LoadImage li;
    s16 dbp = img->dbp;

    if (dbp == 0)
        return;
    if (dbp >= 0x3D40)
        dbp = dbp + base - 0x3D40;
    switch (img->psm) {
    case 19:
        sceGsSetDefLoadImage(&li, dbp, 1, 0, 0, 0, 16, 16);
        break;
    case 20:
        sceGsSetDefLoadImage(&li, dbp, 1, 0, 0, 0, 8, 2);
        break;
    default:
        return;
    }
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&li, (u8 *) img + img->off18 + 0x20);
}

s32 *func_001803b8(s32 *);
s32 *func_001803c0(s32 *, s32);

void func_00180d50(s32 *data, u8 *mask, s16 base) {
    s32 *p;
    s32 n;
    s32 i;
    u8 m;

    m = 0;
    if (data == NULL)
        return;
    i = 0;
    p = func_001803c0(func_001803b8(data), 1);
    n = *p++;
    for (; i < n; i++, m >>= 1) {
        H39Img *s = (H39Img *) *p++;
        s32 k = i >> 3;
        s32 j = i & 7;

        if (!j)
            m = mask[k];
        if (m & 1)
            func_00180b40(s, base);
    }
}

/* The effect objects: 256 entries of 0xC0 bytes at D_00364130 (see
 * text_00170000_h11.c's E0C0). */
#include "data/pieces/D_00364130.h"
typedef H39Obj_364130 H39Obj;

void func_0011d3c8(u16, s32, s32);
void func_00182788(H39Obj *);

s32 func_00181368(s32 t) {
    s32 i;

    for (i = 0; i < 256; i++) {
        H39Obj *e = &D_00364130.h39Obj[i];

        if ((e->flags & 1) && !(e->flags & 4) && e->x98 < t) {
            if (e->p8c->xfc)
                func_0011d3c8(e->p8c->xfc, e->xa8, 60);
            func_00182788(e);
            e->flags |= 4;
            return 1;
        }
    }
    return 0;
}

#include "data/types/text_00180000_h39.h"


extern H39Mtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
H39Mtx D_00615EF0 ALIGNED(16);
extern H39Mtx D_00615F30;
extern u128 D_00615F70; /* src/data/bss_0061.c: f32 D_00615F70[4] */
extern u128 D_00615F80;
u128 D_00615F90 ALIGNED(16);
u128 D_00615FA0 ALIGNED(16);
f32 D_00615FB0 ALIGNED(16);
extern H39Mtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern H39Mtx D_00616180;
extern f32 D_002E27A0;
void sceVu0CopyMatrix(H39Mtx *, H39Mtx *);
void sceVu0MulMatrix(H39Mtx *, H39Mtx *, H39Mtx *);
void func_00267440(H39Mtx *, H39Mtx *);

/* Sets the effect camera: keeps the previous view matrix and eye/target,
 * then derives the combined matrix. */
void func_00182148(H39Mtx *view, H39Mtx *world, u128 *eye, u128 *at) {
    H39Mtx unused; /* only takes stack space */

    sceVu0CopyMatrix(&D_00615EF0, &D_00615EB0);
    D_00615EB0.r[0] = view->r[0];
    D_00615EB0.r[1] = view->r[1];
    D_00615EB0.r[2] = view->r[2];
    D_00615EB0.r[3] = view->r[3];
    D_00616040.r[0] = world->r[0];
    D_00616040.r[1] = world->r[1];
    D_00616040.r[2] = world->r[2];
    D_00616040.r[3] = world->r[3];
    D_00615F90 = D_00615F70;
    D_00615FA0 = D_00615F80;
    D_00615F70 = *eye;
    D_00615F80 = *at;
    D_00615FB0 = D_002E27A0;
    func_00267440(&D_00615F30, &D_00615EB0);
    sceVu0MulMatrix(&D_00616180, &D_00616040, &D_00615EB0);
}
typedef struct H39Sys {
    u8 pad00[0x54];
    s32 end;           /* +0x54 */
    s32 time;          /* +0x58 */
    s32 prev;          /* +0x5C */
    u8 pad60[0x14];
    s32 unk74;         /* +0x74 */
    u8 pad78[0xC];
    u8 unk84;          /* +0x84 */
    u8 unk85;          /* +0x85 */
    u8 pad86[0x2A];
    u64 flags;         /* +0xB0 */
} H39Sys;
extern H39Sys *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
extern s32 D_0061621C;
void pppStepPrograms(void);
void func_001823d8(H39Sys *);
/* One step of the effect system; returns whether it has finished. */
s32 func_00183878(H39Sys *s) {
    s32 t;

    D_00615E60 = s;
    pppStepPrograms();
    func_001823d8(s);
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return 0;
    t = s->time;
    s->prev = t;
    s->time = t + 0x1000;
    if (s->unk84) {
        if (s->unk85)
            return s->unk74 == 0;
        if (s->time > 0x6FFFFFFF) {
            s->time = 0x70000000;
            s->prev = 0x6FFFF000;
        }
        return 0;
    }
    return s->time >= s->end;
}
typedef union { f32 f[4]; } H39V4 __attribute__((aligned(16)));
typedef struct {
    s32 a, b, c;
    s32 pad0C, pad10;
    s16 *vtx;      /* +0x14 */
    void *p18;
    void *tex;
    s32 unk20;
} H39VSlot;
typedef struct {
    s16 slot;
    u16 *map;      /* +0x4 */
} H39VMap;
typedef struct {
    u8 pad00[0x10];
    H39VSlot *slots;  /* +0x10 */
    void *p14;
    H39VMap *maps;   /* +0x18 */
} H39VSys;
typedef struct {
    s32 unk00;
    u8 *mtx;        /* +0x4: matrix at +0x10 */
} H39VObj;
typedef struct {
    u8 pad[0xC];
    s16 map;        /* +0xC */
} H39VKey;
/* D_00615E64 as the current texture system: +0x10 the slots, +0x18 the
 * vertex maps. */
extern H39VSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
void func_002672f8(H39V4 *, void *, H39V4 *);
void pppVertexAttendFrame(H39VObj *obj, H39VKey *key, PppEntry *e) {
    H39V4 v;
    H39VMap *m;
    s16 *p;
    f32 *out;

    if (key->map < 0)
        return;
    m = &D_00615E64->maps[key->map];
    p = D_00615E64->slots[m->slot].vtx + m->map[*(u16 *) ((u8 *) obj + e->offsets[0] + 0xA0)] * 3;
    out = (f32 *) ((u8 *) obj + e->offsets[1] + 0xA0);
    v.f[0] = p[0];
    v.f[1] = p[1];
    v.f[2] = p[2];
    v.f[3] = 1.0f;
    func_002672f8(&v, obj->mtx + 0x10, &v);
    out[0] = v.f[0];
    out[1] = v.f[1];
    out[2] = v.f[2];
}
#include "data/bss_0061_typed.h"
#include "data/data_002E.h"
