/* wm.x func_00f65d18: matched by hand. */
#include "ovl.h"

typedef struct {
    s32 size;
    s32 step;
    s32 bpp;
    u32 count;
    s32 w;
    s32 h;
    u8 *data;
} TexEnt;

typedef struct {
    u8 pad[12];
    TexEnt *ent;
} Tex;

extern s32 D_0108EEB8;
void *func_00f66bd0(void *, u8 *, s32, s32, s32, s32, s32, s16, s16);

void *func_00f65d18(void *p, s32 tbp, Tex *tx, s32 idx) {
    TexEnt *e;
    u8 *data;
    s32 psm;
    u32 i;

    if (tbp < 0) {
        tbp = D_0108EEB8;
    }
    e = tx->ent;
    e += idx;
    data = e->data;
    switch (e->bpp) {
    case 4:
        psm = 20;
        break;
    case 8:
        psm = 19;
        break;
    case 16:
        psm = 2;
        break;
    case 24:
        psm = 1;
        break;
    case 32:
        psm = 0;
        break;
    default:
        return 0;
    }
    p = func_00f66bd0(p, data, tbp, e->w / 64, psm, 0, 0, e->w, e->h);
    tbp += e->size / 256;
    data += e->size;
    if (e->count != 0) {
    for (i = 0; i < e->count; i++) {
        if (psm == 20) {
            p = func_00f66bd0(p, data, tbp, 64, 0, 0, 0, 16, 2);
            data += e->step;
            tbp += 1;
        } else {
            p = func_00f66bd0(p, data, tbp, 64, 0, 0, 0, 16, 16);
            data += e->step;
            tbp += (4 << e->bpp) / 256;
        }
    }
    }
    D_0108EEB8 = tbp;
    return p;
}
