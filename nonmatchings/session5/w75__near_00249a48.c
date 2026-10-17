#include "common.h"
typedef struct {
    u32 total;
    u32 clutSize;
    u32 imageSize;
    u16 hdrSize;
    u16 clutColors;
    u8 fmt;
    u8 mip;
    u8 clutType;
    u8 imageType;
    s16 w;
    s16 h;
    u64 tex0;
    u64 tex1;
    u32 flags;
    u32 clut;
} TimPic;
typedef struct { u8 pad[0x10]; TimPic pic; u8 data[1]; } Tim;
typedef struct { s16 psm; s16 pad; } PsmEnt;
extern PsmEnt D_00469FB0[];
void sceGsSetDefLoadImage(void *, s16, s16, s16, s16, s16, s16, s16);
s32 sceGsExecLoadImage(void *, void *);
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void func_00237018(void *, s32, s32);

void func_00249a48(Tim *t, s32 sync) {
    u8 li[0x60];
    u64 pk[6];
    TimPic *p = &t->pic;
    u8 *img = NULL;
    u8 *clut;
    s16 psm, cbp, cpsm;
    if (p->imageSize) {
        img = t->data;
        sceGsSetDefLoadImage(li, p->tex0 & 0x3FFF, p->tex0 >> 14 & 0x3F, p->tex0 >> 20 & 0x3F, 0, 0, p->w, p->h);
        FlushCache(0);
        sceGsSyncPath(0, 0);
        sceGsExecLoadImage(li, img);
    }
    sceGsSyncPath(0, 0);
    pk[3] = 14;
    pk[2] = 0x1000000000008001;
    pk[5] = 0x3F;
    pk[4] = 0;
    func_00237018(pk, 3, 1);
    if (p->clutSize) {
        psm = D_00469FB0[p->imageType].psm;
        cbp = p->tex0 >> 37 & 0x3FFF;
        cpsm = D_00469FB0[p->clutType].psm;
        clut = img + p->imageSize;
        if (psm == 19) {
            sceGsSetDefLoadImage(li, cbp, 1, cpsm, 0, 0, 16, 16);
        } else if (psm == 20) {
            sceGsSetDefLoadImage(li, cbp, 1, cpsm, 0, 0, 8, 2);
        }
        FlushCache(0);
        sceGsSyncPath(0, 0);
        sceGsExecLoadImage(li, clut);
    }
    sceGsSyncPath(0, 0);
    pk[2] = 0x1000000000008001;
    pk[3] = 14;
    pk[5] = 0x3F;
    pk[4] = 0;
    func_00237018(pk, 3, 1);
    if (sync) sceGsSyncPath(0, 0);
}
