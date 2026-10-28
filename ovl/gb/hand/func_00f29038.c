/* gb.x func_00f29038: matched by hand. */
#include "ovl.h"

typedef struct { u16 a, b, c, flags, d, e; } GbEnt;
typedef struct {
    u8 pad0[0x60];
    u16 x60;
} GbMap;
extern GbMap *D_00F56DC0;
extern s32 D_00F56DE8;
extern GbEnt D_00F806B0;
extern s32 D_00F613AC;
extern s32 D_00F613B0;
void func_00f28ff8(OvlMtx, GbEnt *);
s32 func_00f40fc8(s32);
s32 func_00f41678(s32, s32, OvlMtx, s32, s32);
void func_00f418f8(s32, OvlMtx);
void func_00f41948(s32);

void func_00f29038(GbEnt *e) {
    OvlMtx m;
    GbEnt old;
    s32 id;
    u16 c;
    old = D_00F806B0;
    D_00F806B0 = *e;
    D_00F806B0.a = D_00F56DC0->x60;
    if (D_00F613B0 == 0) {
        D_00F613B0 = 1;
        return;
    }
    func_00f28ff8(m, &old);
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
        if (func_00f40fc8(D_00F613AC)) {
            func_00f418f8(D_00F613AC, m);
            return;
        }
        D_00F613AC = func_00f41678(id, 1, m, 0, D_00F56DE8);
    } else if (func_00f40fc8(D_00F613AC)) {
        func_00f41948(D_00F613AC);
        D_00F613AC = -1;
    }
}
