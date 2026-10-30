/* wm.x func_00f4b668: matched by hand. */
#include "ovl.h"

/* gb.x func_00f4b668: matched by hand. */

typedef struct { u16 a, b, c, flags, d, e; } GbEnt;
typedef struct {
    u8 pad0[4];
    u16 count;
    u16 w;
    u16 pad8;
    u16 h;
    u8 padc[0x70 - 0xC];
    GbEnt ents[1];
} GbHdr;
typedef struct {
    u8 pad0[0xA0];
    GbHdr hdr;
} GbMap;
typedef struct { u8 pad0[4]; u16 used; u8 pad6[8]; u16 ent; } GbCell;
typedef struct { u8 pad0[8]; GbCell cells[1]; } GbGrid;
extern GbMap *D_00F9B540;
void func_00f4af50(s32);

void func_00f4b668(s32 code, GbGrid *g) {
    GbHdr *h = &D_00F9B540->hdr;
    u16 c = code;
    s32 idx = ((c >> 4) & 0xF) * (h->h * h->w) + ((c >> 8) & 0xF) * h->w + (code & 0xF);
    s32 i;
    if (g->cells[idx].used == 0) return;
    idx = g->cells[idx].ent;
    func_00f4af50(D_00F9B540->hdr.ents[idx].c - 1);
    for (i = idx; i < h->count - 1; i++) {
        h->ents[i] = h->ents[i + 1];
    }
    h->count--;
}
