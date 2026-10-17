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
