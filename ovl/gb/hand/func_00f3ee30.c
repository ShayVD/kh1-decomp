/* gb.x func_00f3ee30: matched by hand. */
#include "ovl.h"

typedef struct {
    s32 size;
    s32 step;
    s32 bpp;
    u32 count;
    u32 w;
    u32 h;
    u8 *data;
} TexEnt;

typedef struct {
    u8 pad[12];
    TexEnt *ent;
} Tex;

typedef struct {
    u8 b[96];
} LoadImage;

extern s32 D_00F826F8;
void sceGsSetDefLoadImage(LoadImage *, s16, s16, s16, s16, s16, s16, s16);
void FlushCache(s32);
s32 sceGsExecLoadImage(LoadImage *, void *);
s32 sceGsSyncPath(s32, s32);

u64 func_00f3ee30(s32 tbp, Tex *tx, s32 idx) {
    LoadImage li;
    TexEnt *e;
    u8 *data;
    s32 psm;
    s32 clut;
    s32 tbp0;
    s32 tw;
    s32 th;
    u32 i;
    s32 sz;
    u64 tex0;

    if (tbp < 0) {
        tbp = D_00F826F8;
    }
    e = tx->ent;
    e += idx;
    tbp0 = tbp;
    clut = 0;
    data = e->data;
    switch (e->bpp) {
    case 4:
        psm = 20;
        clut = 1;
        break;
    case 8:
        psm = 19;
        clut = 1;
        break;
    case 16:
        psm = 2;
        break;
    case 24:
        psm = 1;
        break;
    case 32:
        psm = 0;
        clut = 1;
        break;
    default:
        return 0;
    }
    i = 1;
    sceGsSetDefLoadImage(&li, tbp, e->w / 64, psm, 0, 0, e->w, e->h);
    FlushCache(0);
    sceGsExecLoadImage(&li, data);
    sceGsSyncPath(0, 0);
    sz = e->size;
    tbp += sz / 256;
    data += sz;
    tw = 0;
    while (i < e->w) {
        do {
            i <<= 1;
        } while (0);
        tw++;
    }
    i = 1;
    th = 0;
    while (i < e->h) {
        i <<= 1;
        th++;
    }
    tex0 = tbp0 | ((u64)(e->w / 64) << 14) | ((u64)psm << 20) | ((u64)tw << 26) | ((u64)th << 30) | ((u64)clut << 34) |
           ((u64)tbp << 37) | ((u64)1 << 61);
    if (e->count != 0) {
        for (i = 0; i < e->count; i++) {
            if (psm == 20) {
                sceGsSetDefLoadImage(&li, tbp++, 64, 0, 0, 0, 16, 2);
                FlushCache(0);
                sceGsExecLoadImage(&li, data);
                sceGsSyncPath(0, 0);
                data += e->step;
            } else {
                sceGsSetDefLoadImage(&li, tbp, 64, 0, 0, 0, 16, 16);
                FlushCache(0);
                sceGsExecLoadImage(&li, data);
                sceGsSyncPath(0, 0);
                data += e->step;
                tbp += (4 << e->bpp) / 256;
            }
        }
    }
    D_00F826F8 = tbp;
    return tex0;
}
