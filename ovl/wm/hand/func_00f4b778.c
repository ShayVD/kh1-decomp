/* wm.x func_00f4b778: the twin of gb.x func_00f24680 (tools/ovl/twins.py). */
#include "ovl.h"

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
extern GbMap *D_00F9B540;
void func_00f4b778(GbEnt *e) {
    GbHdr *h = &D_00F9B540->hdr;
    s32 n = h->count;
    h->ents[n] = *e;
    h->ents[n].flags = 0x21;
    h->count++;
}
