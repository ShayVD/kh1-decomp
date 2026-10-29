/* 29 words (164 vs 160). Sets 0x20 flag if on, else toggles it. Tried set/clear/xor spellings and bitfields. */
typedef struct { u8 p[6]; u16 fl; u8 q[4]; } Typ;
typedef struct { u8 p[4]; u16 n; u8 q[8]; u16 t; } Cell;
typedef struct { u8 hdr[8]; Cell c[1]; } Grid;
typedef struct { u8 p[6]; u16 w; u16 pad; u16 h; } Dim;
typedef struct { u8 pad[0xA0]; Dim dim; u8 pad3[0x110 - 0xAC]; Typ typ[1]; } W;
extern W *D_00F9B540;

void func_00f4b7d8(s32 on, s32 pos, Grid *g) {
    W *w = D_00F9B540;
    Dim *d = &w->dim;
    Typ *ty = w->typ;
    s32 i = (((u16)pos >> 4) & 0xF) * (d->w * d->h) + (((u16)pos >> 8) & 0xF) * d->w + (pos & 0xF);

    if (g->c[i].n != 0) {
        if (on) {
            ty[g->c[i].t].fl |= 0x20;
        } else {
            ty[g->c[i].t].fl ^= 0x20;
        }
    }
}
