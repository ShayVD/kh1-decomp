/* 25 words / score 49: only s0/s1 swapped (target keeps the entry pointer in s0, dbp in s1). Tried local copy of dbp, decl orders, e = tex->ents + idx, do-while, all flag modes. */
#include "ovl.h"

typedef struct {
    s32 size;
    s32 step;
    s32 bpp;
    u32 count;
    s32 w;
    s16 h;
    u8 pad16[2];
    u32 addr;
} GbTexEnt;
typedef struct { u8 pad0[0xC]; GbTexEnt *ents; } GbTex;
extern s32 D_00F826F8;
u32 *func_00f3fad8(u32 *p, u32 addr, s32 dbp, s32 dbw, s32 dpsm, s32 dsax, s32 dsay, s32 w, s32 h);

u32 *func_00f3ec20(u32 *p, s32 dbp, GbTex *tex, s32 idx) {
    GbTexEnt *e;
    u32 addr;
    s32 psm;
    u32 j;
    if (dbp < 0)
        dbp = D_00F826F8;
    e = &tex->ents[idx];
    addr = e->addr;
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
    p = func_00f3fad8(p, addr, dbp, e->w / 64, psm, 0, 0, (s16)e->w, e->h);
    dbp += e->size / 256;
    addr += e->size;
    if (e->count != 0) {
        for (j = 0; j < e->count; j++) {
            if (psm == 20) {
                p = func_00f3fad8(p, addr, dbp, 64, 0, 0, 0, 16, 2);
                dbp += 1;
                addr += e->step;
            } else {
                p = func_00f3fad8(p, addr, dbp, 64, 0, 0, 0, 16, 16);
                addr += e->step;
                dbp += (4 << e->bpp) / 256;
            }
        }
    }
    D_00F826F8 = dbp;
    return p;
}
