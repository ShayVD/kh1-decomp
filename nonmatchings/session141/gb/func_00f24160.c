/* 6 words / score 12; only the cell pointer register differs (orig: idx*16 into a0, map advanced in a1, cell in a0; ours keeps it in a1); shared u32 k temp from permuter cut 13->6; tried map+=idx, u8* offset, idx var, decl orders; permuter 10 min */
typedef struct { u8 pad0[6]; u16 w; u8 pad8[2]; u16 h; } GbDims;
typedef struct { u8 pad0[6]; u16 flags; u8 pad8[4]; } GbKind;
typedef struct {
    u8 pad0[0xA0];
    GbDims dims;
    u8 padac[0x110 - 0xAC];
    GbKind tbl[1];
} GbWorld;
typedef struct { u8 pad0[4]; u16 used; u8 pad6[8]; u16 kind; } GbCell;
typedef struct { u8 pad0[8]; GbCell cells[1]; } GbMap;
typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
extern GbWorld *D_00F56DC0;

GbCell *func_00f24160(GbPos pos, GbMap *map) {
    GbDims *d = &D_00F56DC0->dims;
    GbKind *t = D_00F56DC0->tbl;
    u32 k;
    s32 x = pos.x;
    s32 y = pos.y;
    s32 z = pos.z;
    GbCell *c = &map->cells[y * (d->w * d->h) + z * d->w + x];
    k = c->used;
    if (k == 0)
        return 0;
    k = c->kind;
    if (t[k].flags & 0x20)
        return c;
    return 0;
}
