/* wm.x func_00f4b258: matched by hand. */
#include "ovl.h"

typedef struct { u8 p[4]; u16 n; u8 q[8]; u16 t; } Cell4b258;
typedef struct { u8 hdr[8]; Cell4b258 c[1]; } Grid4b258;
typedef struct { u8 p[6]; u16 fl; u8 q[4]; } Typ4b258;
typedef struct { u8 p[6]; u16 w; u16 pad; u16 h; } Dim4b258;
typedef struct { u8 pad[0xA0]; Dim4b258 dim; u8 pad3[0x110 - 0xAC]; Typ4b258 typ[1]; } W4b258;
extern W4b258 *D_00F9B540;

Cell4b258 *func_00f4b258(s32 arg0, Grid4b258 *g) {
    u32 pos = arg0 & 0xFFFF;
    W4b258 *w = D_00F9B540;
    Dim4b258 *d = &w->dim;
    Typ4b258 *ty = w->typ;
    s32 i = ((pos >> 4) & 0xF) * (d->w * d->h) + ((pos >> 8) & 0xF) * d->w + (arg0 & 0xF);
    Cell4b258 *c = &g->c[i];

    if (c->n == 0) {
        return NULL;
    }
    i = c->t;
    return (ty[i].fl & 0x20) ? c : NULL;
}
