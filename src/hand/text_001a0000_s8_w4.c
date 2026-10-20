#include "common.h"
typedef struct {
    u32 totalSize;
    u32 clutSize;
    u32 imageSize;
    u16 headerSize;
    u16 clutColors;
    u8 picFormat;
    u8 mipMaps;
    u8 clutType;
    u8 imageType;
    s16 width;
    s16 height;
    struct { u16 tbp0 : 14; u16 x : 2; u16 y; } t0;
    union { struct { u32 thh : 2; u32 tcc : 1; u32 tfx : 2; u32 cbp : 14; u32 rest : 13; } t1; u32 t1w; };
    u32 tex1[2];
    u8 b28;
    u8 b29;
    u8 b2a;
    u8 b2b;
} PicHdr;
typedef struct {
    u8 hdr[15];
    u8 bF;
    PicHdr ph;
} Tm2;
extern u8 D_003727F0[];
s32 sceGsSetDefLoadImage(void *, s16, s16, s16, s16, s16, s16, s16);
s32 sceGsSyncPath(s32, s32);
s32 FlushCache(s32);
s32 sceGsExecLoadImage(void *, void *);
void func_001aa0e0(Tm2 *t) {
    u8 li[96];
    u8 lc[96];
    PicHdr *ph = &t->ph;
    u8 *img;
    if (ph->imageSize) {
        s32 psm = D_003727F0[ph->imageType];
        s32 tbp = ph->t0.tbp0;
        img = (u8 *)t + 64;
        t->bF = 111;
        sceGsSetDefLoadImage(li, tbp, ph->b28 >> 2, psm, ph->b2a * 16, ph->b2b * 16, ph->width, ph->height);
        sceGsSyncPath(0, 0);
        FlushCache(0);
        sceGsExecLoadImage(li, img);
    }
    if (ph->clutSize) {
        sceGsSetDefLoadImage(lc, ph->t1.cbp, 1, D_003727F0[ph->clutType], 0, 0, 16, ph->clutSize >> 6);
        sceGsSyncPath(0, 0);
        FlushCache(0);
        sceGsExecLoadImage(lc, img + ph->imageSize);
    }
}

#include "data/data_0037.h"
