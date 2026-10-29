/* gb.x func_00f240f0: matched by hand. */
#include "ovl.h"

typedef struct { u8 p[4]; u16 n; u8 q[8]; u16 t; } Cell4b1e8;
typedef struct { u8 hdr[8]; Cell4b1e8 c[1]; } Grid4b1e8;
typedef struct { u8 p[6]; u16 fl; u8 q[4]; } Typ4b1e8;
typedef struct { u8 pad[0xA6]; u16 w; u16 pad2; u16 h; u8 pad3[0x110 - 0xAC]; Typ4b1e8 typ[1]; } W4b1e8;
extern W4b1e8 *D_00F56DC0;

s32 func_00f240f0(s32 x, s32 z, s32 y, Grid4b1e8 *g) {
    W4b1e8 *w = D_00F56DC0;
    s32 i = z * (w->w * w->h) + y * w->w + x;
    s32 j;

    if (g->c[i].n != 0) {
        j = i;
        i = g->c[j].t;
        if (w->typ[i].fl & 0x20) {
            return 1;
        }
    }
    return 0;
}
