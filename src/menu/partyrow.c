/* The rows of the party in the menus (docs/modules.md "Session 39"),
 * 0x0020be68-0x0020c1c8: the draw callbacks of the menu tables D_003F3200 /
 * D_003F3230 / D_003F3280 (data_003F.s): func_0020be68 draws a member's
 * name, level, HP / max HP and MP / max MP (D_003E3D70) at x in window a0,
 * func_0020c070 all the members, func_0020c100 one, func_0020c150 the
 * models (src/menu/partymdl.c), func_0020c168 the title D_003F3258[D_00640E28]. */
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003E3D70.h"

typedef E3D70_3E3D70 E3D70;
extern s32 D_003F3258[];
extern s32 D_00640E28;
s32 func_001ee5f0(s32);
void func_001f9010(s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(s32, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00208458(s32, s32, s32, u32, u32);
void func_00209e18(void *);
void func_0020be68(s32, s32, u32);

void func_0020be68(s32 a0, s32 x, u32 k) {
    s32 n = D_00304BE8->x48e[k];
    u8 *t = &D_00304BE8->m[n].sub.lv;
    E3D70 *e = &D_003E3D70.e3D70[n];
    func_001f94f0(a0, 2, x - 39, 5, func_001ee5f0(n), 13, 0x80808080);
    func_001fb428(a0, 1, 3, 0, x - 2, 25, *t, 11, 0x80208080);
    func_001fb428(a0, 1, 3, 0, x - 43, 39, e->x3c, 11, 0x8040a040);
    func_001f9438(a0, 0, x - 41, 39, 84, 11, 0x80308030);
    func_001fb428(a0, 1, 3, 0, x - 2, 39, e->x40, 11, 0x80308030);
    func_001fb428(a0, 1, 3, 0, x - 43, 53, e->x44, 11, 0x80b05050);
    func_001f9438(a0, 0, x - 41, 53, 84, 11, 0x80943e3e);
    func_001fb428(a0, 1, 3, 0, x - 2, 53, e->x48, 11, 0x80943e3e);
}

void func_0020c070(s32 a0) {
    u32 i;
    s32 x = 105;
    func_00208458(a0, 0, 0, 0x80602020, D_003E3D68);
    for (i = 0; i < D_003E3D68; i++) {
        func_0020be68(a0, x, i);
        x += 79;
    }
}

void func_0020c100(s32 a0, s32 k) {
    func_00208458(a0, 0, 0, 0x802020A0, 1);
    func_0020be68(a0, 0x69, k);
}

void func_0020c150(void *a0) {
    func_00209e18(a0);
}

void func_0020c168(s32 a0) {
    func_001f9010(0x17);
    func_001f9438(a0, 0, 0xAE, 0xC, D_003F3258[D_00640E28], 0x11, 0x80C87850);
}
