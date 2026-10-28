/* 11 words / score 23: register allocation in the cell address (original: idx*16 in v1, cell in a1 then copied to a3). ent_of() helper did not help here. permuter 10 min. */
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
typedef struct { u8 pad0[4]; u16 used; u8 pad6[8]; u16 kind; } GbCell;
typedef struct { u8 pad0[8]; GbCell cells[1]; } GbGrid;
extern GbMap *D_00F56DC0;
static inline s32 cell_index(s32 x, s32 y, s32 z) {
    GbMap *m = D_00F56DC0;
    return y * (m->hdr.w * m->hdr.h) + z * m->hdr.w + x;
}
s32 func_00f240f0(s32 x, s32 y, s32 z, GbGrid *g) {
    s32 i = cell_index(x, y, z);
    if (g->cells[i].used == 0)
        goto no;
    if (D_00F56DC0->hdr.ents[g->cells[i].kind].flags & 0x20)
        return 1;
no:
    return 0;
}
