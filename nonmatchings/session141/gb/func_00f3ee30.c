/* 30 words / score 59: the same s0/s1 swap as func_00f3ec20 (entry pointer vs dbp) plus a missing move v1,a3 before the tw loop. Sibling of f3ec20; fix that one first. */
#include "ovl.h"

typedef struct {
    s32 size;
    s32 step;
    s32 bpp;
    u32 count;
    u32 w;
    u32 h;
    u32 addr;
} GbTexEnt;
typedef struct { u8 pad0[0xC]; GbTexEnt *ents; } GbTex;
typedef struct { u8 data[96]; } GbLoadImage;
extern s32 D_00F826F8;
void sceGsSetDefLoadImage(GbLoadImage *, s16, s16, s16, s16, s16, s16, s16);
s32 sceGsExecLoadImage(GbLoadImage *, void *);
s32 sceGsSyncPath(s32, s32);
s32 FlushCache(s32);

u64 func_00f3ee30(s32 dbp, GbTex *tex, s32 idx) {
    GbLoadImage li;
    GbTexEnt *e;
    u32 addr;
    s32 psm;
    s32 tcc;
    s32 tbp;
    u32 i;
    s32 tw, th;
    u64 tex0;
    if (dbp < 0)
        dbp = D_00F826F8;
    e = &tex->ents[idx];
    tbp = dbp;
    tcc = 0;
    addr = e->addr;
    switch (e->bpp) {
    case 4:
        psm = 20;
        tcc = 1;
        break;
    case 8:
        psm = 19;
        tcc = 1;
        break;
    case 16:
        psm = 2;
        break;
    case 24:
        psm = 1;
        break;
    case 32:
        psm = 0;
        tcc = 1;
        break;
    default:
        return 0;
    }
    sceGsSetDefLoadImage(&li, dbp, e->w / 64, psm, 0, 0, e->w, e->h);
    FlushCache(0);
    sceGsExecLoadImage(&li, (void *)addr);
    sceGsSyncPath(0, 0);
    dbp += e->size / 256;
    addr += e->size;
    for (tw = 0, i = 1; i < e->w; i <<= 1)
        tw++;
    for (th = 0, i = 1; i < e->h; i <<= 1)
        th++;
    tex0 = tbp | ((u64)(e->w / 64) << 14) | ((u64)psm << 20) | ((u64)tw << 26) | ((u64)th << 30) |
           ((u64)tcc << 34) | ((u64)dbp << 37) | (1LL << 61);
    if (e->count != 0) {
        for (i = 0; i < e->count; i++) {
            if (psm == 20) {
                sceGsSetDefLoadImage(&li, dbp++, 64, 0, 0, 0, 16, 2);
                FlushCache(0);
                sceGsExecLoadImage(&li, (void *)addr);
                sceGsSyncPath(0, 0);
                addr += e->step;
            } else {
                sceGsSetDefLoadImage(&li, dbp, 64, 0, 0, 0, 16, 16);
                FlushCache(0);
                sceGsExecLoadImage(&li, (void *)addr);
                sceGsSyncPath(0, 0);
                addr += e->step;
                dbp += (4 << e->bpp) / 256;
            }
        }
    }
    D_00F826F8 = dbp;
    return tex0;
}
