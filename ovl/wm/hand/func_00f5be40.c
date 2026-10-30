/* wm.x func_00f5be40: matched by hand. */
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
extern s32 D_00F9B568;
void func_00f5aeb0(s32);
void func_00f5ae10(OvlMtx, s32);
void func_00f5ae98(s32, s32);
s32 func_00f68770(s32, s32, OvlMtx, s32, s32);

/* An inlined entry lookup (the tile family uses it too): it keeps its own D + k*12 add. */
static inline GbEnt *ent_of(s32 k) {
    GbEnt *e = D_00F9B540->hdr.ents;
    return &e[k];
}
void func_00f5be40(s32 alt) {
    OvlMtx m;
    s32 i;
    s32 id;
    func_00f5aeb0(1);
    func_00f5aeb0(3);
    func_00f5aeb0(2);
    for (i = 0; i < D_00F9B540->hdr.count; i++) {
        u16 b = ent_of(i)->b;
        u16 c = D_00F9B540->hdr.ents[i].c;
        if ((b & 0xF00) == 0x400) {
            id = -1;
            switch (c) {
            case 5:
                id = !alt ? 2 : 3;
                break;
            case 6:
                id = !alt ? 6 : 7;
                break;
            case 7:
                id = !alt ? 10 : 11;
                break;
            case 8:
                id = !alt ? 14 : 15;
                break;
            case 9:
                id = !alt ? 18 : 19;
                break;
            }
            if (id >= 0) {
                func_00f5ae10(m, i);
                func_00f5ae98(func_00f68770(id, 1, m, 0, D_00F9B568), 3);
            }
        }
    }
}
