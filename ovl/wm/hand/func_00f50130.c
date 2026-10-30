/* wm.x func_00f50130: matched by hand. */
#include "ovl.h"

typedef struct { u16 a, b, c, flags, d, e; } GbEnt;
typedef struct {
    u8 pad0[0x60];
    u16 x60;
} GbMap;
extern GbMap *D_00F9B540;
extern s32 D_00F9B568;
extern GbEnt D_0108CE70;
extern s32 D_00FA5B2C;
extern s32 D_00FA5B30;
void func_00f500f0(OvlMtx, GbEnt *);
s32 func_00f680c0(s32);
s32 func_00f68770(s32, s32, OvlMtx, s32, s32);
void func_00f689f0(s32, OvlMtx);
void func_00f68a40(s32);

void func_00f50130(GbEnt *e) {
    OvlMtx m;
    GbEnt old;
    s32 id;
    u16 c;
    old = D_0108CE70;
    D_0108CE70 = *e;
    D_0108CE70.a = D_00F9B540->x60;
    if (D_00FA5B30 == 0) {
        D_00FA5B30 = 1;
        return;
    }
    func_00f500f0(m, &old);
    c = e->c;
    id = -1;
    if ((old.b & 0xF00) == 0x400) {
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
    }
    if (id >= 0) {
        if (func_00f680c0(D_00FA5B2C)) {
            func_00f689f0(D_00FA5B2C, m);
            return;
        }
        D_00FA5B2C = func_00f68770(id, 1, m, 0, D_00F9B568);
    } else if (func_00f680c0(D_00FA5B2C)) {
        func_00f68a40(D_00FA5B2C);
        D_00FA5B2C = -1;
    }
}
