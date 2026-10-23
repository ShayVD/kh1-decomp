/* The item page's frame (docs/modules.md "Session 40"), 0x002106b8-0x002113f0:
 * the end of page 0 of the top menu.  func_002106b8 is the callback of its
 * first window (descriptor D_003F3AB0): by the state D_00641224 it opens the
 * list, slot and stock windows of src/menu/items.c, itemslots.c and
 * itemstock.c (descriptors D_003F3980 ... D_003F3A80) and draws the help
 * lines; func_002112c8 draws the page title (message 0x69), func_002112f8
 * opens the page (topmenu.c's D_003F32E8[0]), func_00211358 sets it up and
 * func_00211398 resets its cursors (func_0020d530's / func_0020d748's lists).
 *
 * PageWin is this file's view of a TextWin (include/text/textwin.h).  It
 * stays: TextWin's +0xd0 is a union (any union access reorders
 * func_002106b8) and its +0x24 / +0x28 / +0x2c are s32 (as s32 the stores
 * there move: the alias set changes). */
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D68.h"

typedef struct PageWin PageWin;
struct PageWin {
    u8 pad0[0x24];
    PageWin *x24, *x28;
    PageWin *x2c;
    u8 pad30[0x70 - 0x30];
    s32 x70;
    u8 pad74[0x88 - 0x74];
    s32 x88;
    u8 pad8c[0xb4 - 0x8c];
    s32 xb4;
    s16 xb8;
    s16 xba;
    u8 padbc[0xc2 - 0xbc];
    s16 xc2;
    u8 padc4[0xc6 - 0xc4];
    s16 xc6;
    u8 padc8[0xcc - 0xc8];
    s16 xcc, xce, xd0, xd2;
    u8 padd4[0xd8 - 0xd4];
    s16 xd8, xda;
};

extern u8 D_003F3980[], D_003F39C0[], D_003F39F0[], D_003F3A20[], D_003F3A50[], D_003F3A80[], D_003F3AB0[];
extern PageWin *D_00641220;
extern s32 D_00641224, D_00641228, D_0064122C, D_00641234, D_00641238, D_0064123C;
extern s32 D_00641240, D_00641248, D_00641388;
extern u32 D_00641250[];
extern s32 D_00641258, D_0064125C, D_00641260, D_00641264, D_00641268, D_0064126C, D_00641270, D_00641274;

s32 func_001ebea8(void);
s32 func_001ee5f0(s32);
s32 func_001efbb8(s32);
PageWin *func_001f31a8(void *, s32);
void func_001f3dc0(PageWin *);
void func_001f3e48(PageWin *, PageWin *);
void func_001f40a0(PageWin *, s32);
s32 func_001f42b8(PageWin *);
s32 func_001fd518(PageWin *);
void func_00206690(PageWin *, s32, s32, s32);
void func_00207830(PageWin *, s32, s32, s32, s32, s32, s32);
void func_00207870(PageWin *, s32, s32, s32, s32, s32, s32);
void func_0020dd38(PageWin *, s32, s32, s32, s32, s32);
void func_0020eb98(void);
void func_0020f3c8(void);
void func_0020fbe0(void);

/* rodata: jump tables at 0x00490e30.  The dead `n = D_003E3D68;` in the case-4 arm gives gcse a partially available hi(D_003E3D68), so PRE puts lui s5 in both arms. */
void func_002106b8(PageWin *o) {
    PageWin *w[3];
    s32 n;
    u32 sel;
    s32 shift;
    s32 *pc;
    s32 v;
    if (func_001f42b8(o)) {
        switch (D_00641224) {
        case 0:
        case 3:
            w[0] = func_001f31a8(D_003F3A80, 6);
            if (w[0] == 0) break;
            func_001f3e48(w[0], o);
            if (D_00641224 == 0) {
                shift = 0;
                n = D_003E3D68 + 1;
                n += func_001ebea8();
                sel = D_00641250[0];
            } else {
                w[0]->xb4 += 448;
                shift = 1;
                if (D_00641228 == -1) n = D_003E3D68;
                else n = D_003E3D68 + 1;
                switch (D_00641238) {
                case 0:
                    if (D_00641228 == -1) D_00641250[1] = 0;
                    else D_00641250[1] = D_00641250[0];
                    n = D_003E3D68;
                    break;
                case 1:
                    D_00641250[1] = 0;
                    break;
                case 2:
                    D_00641250[1] = D_003E3D68;
                    break;
                }
                sel = D_00641250[1];
            }
            w[0]->xd2 = sel * 16;
            w[0]->xcc = n;
            w[0]->xba = n * 448 - 32;
            w[0]->xce = n;
            w[1] = func_001f31a8(D_003F3A50, 6);
            if (w[1] == 0) break;
            func_001f3e48(w[1], w[0]);
            w[1]->x24 = 0;
            if (D_00641224 != 3 || D_00641238 != 0) {
                w[2] = func_001f31a8(D_003F3A20, 6);
                if (w[2] != 0) {
                    func_001f3e48(w[2], w[1]);
                    if (sel < D_003E3D68) {
                        w[2]->xd0 = (u16)D_00641258 * 16;
                        w[2]->xd2 = (u16)D_0064125C * 16;
                        w[2]->xb8 = 0xa60;
                        w[2]->xd8 = 1;
                        w[2]->xc2 = 0xa60;
                        w[2]->x88 &= ~1;
                    } else if (sel == D_003E3D68) {
                        w[2]->xd0 = (u16)D_00641260 * 16;
                        w[2]->xd2 = (u16)D_00641264 * 16;
                        w[2]->xda = (u16)D_00641268 * 16;
                        w[2]->xd8 = 2;
                        w[2]->xb8 = 0x14c0;
                        w[2]->xc2 = 0xa60;
                        w[2]->x88 |= 1;
                        w[2]->x70 = 4;
                        w[2]->xc6 = 0;
                    } else {
                        w[2]->xd0 = (u16)D_0064126C * 16;
                        w[2]->xd2 = (u16)D_00641270 * 16;
                        w[2]->xb8 = 0xa60;
                        w[2]->xd8 = 1;
                        w[2]->xc2 = 0xa60;
                        w[2]->x88 &= ~1;
                    }
                    if (shift) {
                        w[2]->xb4 += 448;
                        w[2]->xba -= 448;
                    }
                    func_001f40a0(w[2], 0x40000000);
                    w[2]->x24 = (PageWin *)sel;
                    w[2]->x2c = (PageWin *)D_00641224;
                }
            }
            func_001f3dc0(w[0]);
            break;
        case 1:
        case 4:
        c1:
            w[0] = func_001f31a8(D_003F3A20, 6);
            if (w[0] == 0) break;
            func_001f3e48(w[0], o);
            if (D_00641224 == 1) {
                shift = 0;
                sel = D_00641250[0];
            } else {
                sel = D_00641250[1];
                n = D_003E3D68;
                shift = 1;
            }
            if (sel < D_003E3D68) {
                w[0]->xd0 = (u16)D_00641258 * 16;
                w[0]->xd2 = (u16)D_0064125C * 16;
                w[0]->xb8 = 0xa60;
                w[0]->xd8 = 1;
                w[0]->xc2 = 0xa60;
                w[0]->x88 &= ~1;
            } else if (sel == D_003E3D68) {
                w[0]->xd0 = (u16)D_00641260 * 16;
                w[0]->xd2 = (u16)D_00641264 * 16;
                w[0]->xda = (u16)D_00641268 * 16;
                w[0]->xd8 = 2;
                w[0]->xb8 = 0x14c0;
                w[0]->xc2 = 0xa60;
                w[0]->x88 |= 1;
                w[0]->x70 = 4;
                w[0]->xc6 = 0;
            } else {
                w[0]->xd0 = (u16)D_0064126C * 16;
                w[0]->xd2 = (u16)D_00641270 * 16;
                w[0]->xb8 = 0xa60;
                w[0]->xd8 = 1;
                w[0]->xc2 = 0xa60;
                w[0]->x88 &= ~1;
            }
            if (shift) {
                w[0]->xb4 += 448;
                w[0]->xba -= 448;
            }
            func_001f40a0(w[0], 0x40000000);
            w[0]->x24 = (PageWin *)sel;
            w[0]->x28 = (PageWin *)1;
            w[0]->x2c = (PageWin *)D_00641224;
            func_001f40a0(w[0], 0x60000000);
            w[1] = func_001f31a8(D_003F39F0, 6);
            if (w[1] == 0) break;
            func_001f3e48(w[1], w[0]);
            func_001f3dc0(w[0]);
            break;
        case 2:
            w[0] = func_001f31a8(D_003F39C0, 6);
            if (w[0] == 0) break;
            func_001f3e48(w[0], o);
            w[0]->xd2 = (u16)D_00641274 * 16;
            w[1] = func_001f31a8(D_003F3980, 6);
            if (w[1] == 0) break;
            func_001f3e48(w[1], w[0]);
            w[1]->x24 = (PageWin *)func_001fd518(w[0]);
            func_001f3dc0(w[0]);
            break;
        case 5:
            func_0020eb98();
            func_0020f3c8();
            func_0020fbe0();
            if (D_00641228 == -2) {
            z5:
                D_00641224 = 0;
                break;
            }
            if (D_00641228 == -1 && D_00641388 == 0) goto z5;
            D_00641224 = 1;
            goto c1;
            break;
        }
    }
    switch (D_00641224) {
    case 0:
        break;
    case 1:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        break;
    case 2:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        func_00206690(o, 133, 83, 26);
        func_0020dd38(o, 11, 159, 71, 166, D_00641234);
        break;
    case 3:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        func_00206690(o, 133, 83, 26);
        pc = &D_00641234;
        func_0020dd38(o, 11, 159, 71, 166, *pc);
        func_00206690(o, 325, 83, 26);
        switch (D_00641238) {
        case 1: v = 148; break;
        case 0: v = 145; break;
        case 2: v = *pc ? 146 : 149; break;
        default: v = 147; break;
        }
        func_00207830(o, 11, 2, 351, 71, 122, v);
        func_00206690(o, 473, 83, 39);
        break;
    case 4:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        func_00206690(o, 133, 83, 26);
        pc = &D_00641234;
        func_0020dd38(o, 11, 159, 71, 166, *pc);
        func_00206690(o, 325, 83, 26);
        switch (D_00641238) {
        case 1: v = 148; break;
        case 0: v = 145; break;
        case 2: v = *pc ? 146 : 149; break;
        default: v = 147; break;
        }
        func_00207830(o, 11, 2, 351, 71, 122, v);
        func_00206690(o, 473, 83, 39);
        func_00207870(o, 11, 1, 11, 99, 122, D_00641240 != -1 ? func_001ee5f0(D_00304BE8->x48e[D_00641240]) : func_001efbb8(56));
        func_00206690(o, 0, 111, 11);
        break;
    case 5:
        func_00206690(o, 0, 83, 11);
        func_00207870(o, 11, 0, 11, 71, 122, D_0064122C);
        func_00206690(o, 133, 83, 26);
        pc = &D_00641234;
        func_0020dd38(o, 11, 159, 71, 166, *pc);
        func_00206690(o, 325, 83, 26);
        switch (D_00641238) {
        case 1: v = 148; break;
        case 0: v = 145; break;
        case 2: v = *pc ? 146 : 149; break;
        default: v = 147; break;
        }
        func_00207830(o, 11, 2, 351, 71, 122, v);
        func_00206690(o, 473, 83, 39);
        switch (D_00641238) {
        case 1:
            func_00206690(o, 0, 111, 11);
            if (D_00641240 != -1) v = func_001ee5f0(D_00304BE8->x48e[D_00641240]);
            else v = func_001efbb8(56);
            func_00207870(o, 11, 1, 11, 99, 122, v);
            func_00206690(o, 133, 111, 26);
            if (D_00641238 == 1) func_0020dd38(o, 11, 159, 99, 166, D_00641248);
            func_00206690(o, 325, 111, 187);
            break;
        case 0:
            if (D_0064123C == 0) break;
            func_00206690(o, 0, 111, 11);
            func_00207870(o, 11, 1, 11, 99, 122, func_001ee5f0(D_00304BE8->x48e[D_00641240]));
            func_00206690(o, 133, 111, 379);
            break;
        case 2:
            break;
        }
        break;
    }
}

void func_002112c8(PageWin *o) {
    func_00207830(o, 4, 2, 0, 0, 0x7A, 0x69);
}

void func_002112f8(PageWin *o) {
    PageWin *w = func_001f31a8(D_003F3AB0, 0);
    if (w != 0) {
        func_001f3e48(w, o);
    }
    D_00641220 = o;
    D_00641224 = 0;
    func_0020eb98();
    func_0020f3c8();
    func_0020fbe0();
}

/* Keeps the list cursor within the party and the stock. */
void func_00211358(void) {
    s32 n = D_003E3D68 + func_001ebea8();
    if (n < (s32)D_00641250[0]) {
        D_00641250[0] = n;
    }
}

void func_00211398(void) {
    D_00641250[0] = 0;
    D_00641250[1] = 0;
    D_00641258 = 0;
    D_0064125C = 0;
    D_00641260 = 0;
    D_00641264 = 0;
    D_00641268 = 0;
    D_0064126C = 0;
    D_00641270 = 0;
    D_00641274 = 0;
}
