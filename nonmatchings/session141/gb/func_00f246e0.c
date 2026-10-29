/* 30 words / score 37; sibling of f24160 (same grid lookup); orig has three uncoalesced copies (move t0,a0 for on; move v1,a0 twice) giving 160 vs 148 bytes; tried static inline getters, all flag modes */
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

void func_00f246e0(s32 on, GbPos pos, GbMap *map) {
    GbDims *d = &D_00F56DC0->dims;
    GbKind *t = D_00F56DC0->tbl;
    s32 x = pos.x;
    s32 y = pos.y;
    s32 z = pos.z;
    GbCell *c = &map->cells[y * (d->w * d->h) + z * d->w + x];
    GbKind *k;
    if (c->used == 0)
        return;
    k = &t[c->kind];
    if (on) {
        k->flags |= 0x20;
        return;
    }
    k->flags ^= 0x20;
}
