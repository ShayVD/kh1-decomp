/* wm.x func_00f502e8: matched by hand. */
#include "ovl.h"

/* gb.x func_00f502e8: matched by hand. */

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
    u8 pad0[0x4C];
    u16 kind;
    u8 pad4e[0xA0 - 0x4E];
    GbHdr hdr;
} GbMap;
extern GbMap *D_00F9B540;
s32 func_001ba3f0(s32);
s32 func_001be680(void);
s32 func_001be6c8(s32);
s32 func_001be710(s32);

s32 func_00f502e8(void) {
    GbMap *m = D_00F9B540;
    GbHdr *h = &m->hdr;
    s32 n4 = 0;
    s32 n0 = 0;
    s32 n58 = 0;
    s32 i, k;
    if (h->count >= func_001be680())
        return func_001be680() >= 200 ? 29 : 28;
    for (i = 0; i < h->count; i++) {
        k = m->hdr.ents[i].c - 1;
        switch (k) {
        case 0: case 1: case 2: case 3:
            n0++;
            break;
        case 4: case 5: case 6: case 7: case 8:
            n4++;
            break;
        case 58: case 59: case 60: case 61: case 62: case 63:
            n58++;
            break;
        }
    }
    k = D_00F9B540->kind - 1;
    switch (k) {
    case 0: case 1: case 2: case 3:
        if (n0 > 0)
            return 234;
        break;
    case 4: case 5: case 6: case 7: case 8:
        if (n4 < func_001be6c8(k))
            break;
        return func_001ba3f0(70) ? 230 : 26;
    case 58: case 59: case 60: case 61: case 62: case 63:
        if (n58 < func_001be710(k))
            break;
        return func_001ba3f0(70) ? 231 : 27;
    }
    return 0;
}
