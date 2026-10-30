/* gb.x func_00f35288: matched by hand. */
#include "ovl.h"

/* gb.x func_00f35288: matched by hand. */
#include "ovl.h"

/* gb.x func_00f35288: matched by hand. */
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
extern GbMap *D_00F56DC0;
extern s32 D_00F56DE8;
void func_00f33db8(s32);
void func_00f33c70(s32);
void func_00f33d18(OvlMtx, s32);
void func_00f33da0(s32, s32);
s32 func_00f41678(s32, s32, OvlMtx, s32, s32);

/* An inlined entry lookup (the tile family uses it too): it keeps its own D + k*12 add. */
static inline GbEnt *ent_of(s32 k) {
    GbEnt *e = D_00F56DC0->hdr.ents;
    return &e[k];
}
void func_00f35288(void) {
    OvlMtx m;
    s32 i;
    s32 id;
    func_00f33db8(1);
    func_00f33db8(3);
    func_00f33db8(2);
    for (i = 0; i < D_00F56DC0->hdr.count; i++) {
        u16 b = ent_of(i)->b;
        u16 c = D_00F56DC0->hdr.ents[i].c;
        if ((b & 0xF00) == 0x400) {
            id = -1;
            switch (c) {
            case 5:
                id = 0;
                break;
            case 6:
                id = 4;
                break;
            case 7:
                id = 8;
                break;
            case 8:
                id = 12;
                break;
            case 9:
                id = 16;
                break;
            }
            if (id >= 0) {
                func_00f33d18(m, i);
                func_00f33da0(func_00f41678(id, 1, m, 0, D_00F56DE8), 1);
            }
        }
    }
    func_00f33c70(0);
}
