#include "common.h"

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
typedef struct H39Obj {
    u8 pad0[0x86];
    u16 flags; /* 0x86: bit 0 in use, bit 2 stopping */
    u8 pad88[4];
    struct {
        u8 pad[0xfc];
        u16 xfc;
    } *p8c;   /* 0x8C */
    u8 pad90[4];
    s32 key;  /* 0x94 */
    s32 x98;  /* 0x98 */
    u8 pad9c[0xc];
    s32 xa8;  /* 0xA8 */
    u8 padac[0xc0 - 0xac];
} H39Obj;

extern H39Obj D_00364130[256];
void func_0011d3c8(u16, s32, s32);
void func_00182788(H39Obj *);

s32 func_00181368(s32 t) {
    s32 i;

    for (i = 0; i < 256; i++) {
        H39Obj *e = &D_00364130[i];

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

typedef int u128 __attribute__((mode(TI)));

typedef struct {
    u128 r[4];
} H39Mtx;

extern H39Mtx D_00615EB0;
extern H39Mtx D_00615EF0;
extern H39Mtx D_00615F30;
extern u128 D_00615F70;
extern u128 D_00615F80;
extern u128 D_00615F90;
extern u128 D_00615FA0;
extern f32 D_00615FB0;
extern H39Mtx D_00616040;
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
