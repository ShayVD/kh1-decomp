/* wm.x func_00f65bb8: matched by hand. */
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

u64 func_00f65bb8(s32 tbp, Tex *tx, s32 idx, s32 cidx) {
    TexEnt *e;
    s32 psm;
    s32 clut;
    s32 cbp;
    s32 tb;
    s32 tw;
    s32 th;
    u32 i;

    e = tx->ent;
    e += idx;
    cbp = 0;
    clut = 0;
    tb = tbp + e->size / 256;
    switch (e->bpp) {
    case 4:
        cbp = tb + cidx;
        psm = 20;
        clut = 1;
        break;
    case 8:
        cbp = tb + cidx * 4;
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
    return tbp | ((u64)(e->w / 64) << 14) | ((u64)psm << 20) | ((u64)tw << 26) | ((u64)th << 30) | ((u64)clut << 34) |
           ((u64)cbp << 37) | ((u64)1 << 61);
}
