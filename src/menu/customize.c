/* The customize page of the menu (docs/modules.md "Session 40"),
 * 0x00216180-0x00218020: page 3 of the top menu (message 0x6c; its open
 * function is func_00217f58, set up func_00217fb0, reset func_00217fe8).
 * Its windows are opened from the descriptors D_003F4430 ... D_003F4650.
 * Two halves, picked in the member list (func_002177c8, D_00642CCC):
 * - member 0 (Sora): the three shortcuts.  func_00216640 lists them
 *   (func_0013c288(i), the magic set in Save +0x844), func_00216280 collects
 *   the magic he has (func_0013c188 bits, 7 entries + "none") into
 *   D_00642CA8 (D_00642CC8 of them) for the list that sets one
 *   (func_002163e0, customize.nostrict.c).
 * - the others: the party member's behaviour.  D_003F40F8[member] lists its
 *   settings (p, n), each one of three levels (func_00170d60 / func_00170dd8
 *   keep them two bits each); D_003F41E8[style] / D_003F4200[member] are the
 *   presets and D_003F34B8->a[member] the style chosen (func_00217000,
 *   customize.nostrict.c; func_00216ea8 applies it, func_00216890 edits one
 *   setting, func_00217490 shows them).  func_00216180 resets every member
 *   to its default style (4).
 * D_00642C94 is the page state.  Most likely the customize page; not proved
 * by a boot.
 *
 * Window views: TextWin (include/text/textwin.h) where the types agree.
 * CuWin, CuWinU, CuWin7 and CuWinC stay: their functions read +0xd0 / +0xd2
 * as plain s16 (TextWin's +0xd0 is a union, and a union access reorders) or
 * keep a pointer at +0x24 (as s32 the store moves: the alias set changes). */
#include "common.h"
#include "platform/pad.h"
#include "text/textwin.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_003F34B8.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003F2C40.h"
#include "data/types/text_00210000_b14.h"

typedef struct CuWin {
    u8 pad[0x24];
    struct CuWin *x24; /* holds a byte id; pointer type matches the original aliasing */
    u8 pad28[0xA0 - 0x28];
    f32 xa0;
    u8 pada4[0xBA - 0xA4];
    s16 xba;
    u8 padbc[0xCA - 0xBC];
    s16 xca;
    s16 xcc;
    s16 xce;
    u8 padd0[2];
    s16 xd2;
    u8 padd4[4];
    s16 xd8;
    s16 xda;
} CuWin;
typedef struct CuWinU { u8 pad[0x10]; struct CuWinU *x10; u8 p14[0x10]; union { struct CuWinU *p; s32 i; s16 h; } x24; s32 x28; u8 p2c[0xBA - 0x2C]; s16 xba; u8 pbc[0xCC - 0xBC]; s16 xcc; s16 xce; s16 xd0; s16 xd2; } CuWinU;
typedef struct CuWin7 { u8 pad[0x10]; struct CuWin7 *x10; u8 p14[0x10]; struct CuWin7 *x24; s32 x28; u8 p2c[0xBA - 0x2C]; s16 xba; u8 pbc[0xCC - 0xBC]; s16 xcc; s16 xce; s16 xd0; s16 xd2; } CuWin7;
typedef struct { u8 pad0[0x24]; s32 x24; } CuWinB;
typedef struct { u8 pad0[0xc]; CuWinB *xc; u8 pad10[0x24 - 0x10]; void *x24; } CuWinC;
typedef union { s32 i; u16 h; } U32H;

extern u8 D_003F4430[], D_003F4460[], D_003F44A0[], D_003F44E0[], D_003F4520[], D_003F4550[];
extern u8 D_003F4580[], D_003F45C0[], D_003F45F0[], D_003F4620[], D_003F4650[];
extern PN D_003F40F8[];
extern s32 *D_003F41E8[];
extern s32 D_003F4200[][9];
extern s32 D_003F4368[], D_003F4380[], D_003F43F0[], D_003F4408[], D_003F4488[];
extern s32 D_003F44C8[], D_003F4508[], D_003F45A8[];
extern s32 *D_003F43C8[];
extern void *D_00642C90;
extern s32 D_00642CA0, D_00642CA8[], D_00642CC8;
extern s32 D_00642CCC, D_00642CD0, D_00642CD4, D_00642CD8, D_00642CDC, D_00642CE0;

void func_0011d768(s32);
s32 func_00132f88(s32);
s32 func_00132fe0(s32);
s32 func_0013c188(s32, s32);
s32 func_0013c288(s32);
void func_00170d60(s32, s32, s32);
s32 func_00170dd8(s32, s32);
s32 func_001ee5f0(s32);
s32 func_001ee618(s32);
s32 func_001efbb8(s32);
s32 func_001f0118(s32, s32);
void *func_001f31a8(void *, s32);
s32 func_001f3758(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
s32 func_001f42b8(void *);
s32 func_001f4378(void *);
void *func_001f4468(void *);
void func_001f9010(s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
void func_001ff488(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_00206690(void *, s32, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);
void func_0020bd18(void *, s32);
void func_0020bda8(s32);
void func_002161e8(s32, s32);

void func_00216180(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        D_003F34B8->a[i] = 4;
        func_002161e8(i, 4);
    }
}

void func_002161e8(s32 a0, s32 a1) {
    s32 *p;
    s32 i;
    if (a1 != 4) p = D_003F41E8[a1];
    else p = D_003F4200[a0];
    for (i = 0; i < 9; i++) func_00170d60(a0, i, p[i]);
}

void func_00216280(void) {
    s32 i;
    D_00642CC8 = 0;
    for (i = 0; i < 7; i++) {
        if (func_0013c188(0, i) != 0) {
            D_00642CA8[D_00642CC8++] = i;
        }
    }
    D_00642CA8[D_00642CC8] = 7;
    D_00642CC8++;
}

void func_00216340(TextWin *arg0) {
    s32 var_a4;

    func_001f9010(0x17);
    var_a4 = 0xEA;
    if (D_00642CD4 != (D_00642CC8 - 1)) {
        var_a4 = (D_00642CA8[D_00642CD4] * 3) + func_00132fe0(D_00642CD4) + 0xD4;
    }
    func_001f9438(arg0, 0, 0xAE, 0xC, var_a4, 0x11, 0x80C87850);
}

/* func_002163e0 (the magic list of a shortcut) is in customize.nostrict.c. */

void func_002165e0(TextWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, D_003F4488[D_00642CD0], 0x11, 0x80C87850);
}

void func_00216640(void *a) {
    CuWin *o[2];
    CuWin *p;
    s32 i, y, sel, s;
    s32 *pv;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3758(a);
            func_0011d768(3);
            D_00642C94 = 0;
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            i = func_001fd518(a);
            pv = &D_00642CD0;
            *pv = i;
            if (func_001fe570(a)) {
                func_001f3d58(a, 5);
                func_001f3758(a);
                D_00642C94 = 2;
                D_00642C9C = *pv;
                p = func_001f4468(a);
                if ((o[0] = func_001f31a8(D_003F4460, 6))) {
                    func_001f3e48(o[0], p);
                    o[0]->xcc = o[0]->xce = (u16)D_00642CC8;
                    o[0]->xd2 = (u16)D_00642CD4 << 4;
                    if ((o[1] = func_001f31a8(D_003F4430, 6))) {
                        func_001f3e48(o[1], o[0]);
                        func_001f3dc0(o[0]);
                    }
                }
            }
        }
    }
    y = 0;
    s = func_001fd518(a);
    for (i = 0; i < 3; i++) {
        s32 t;
        sel = i == s;
        func_00207830(a, sel, 2, 0, y, 180, D_003F44C8[i]);
        func_001f9438(a, 0, 86, y + 5, 51, 15, D_003F2C40.e20[sel].x10);
        t = func_00132f88(func_0013c288(i));
        if (!t) t = func_001efbb8(212);
        func_001f94f0(a, 0, 96, y + 5, t, 15, D_003F2C40.e20[sel].x10);
        y += 28;
    }
}

void func_00216890(CuWinC *o) {
    s32 i, y, k, n, sel;
    s32 *pnn;
    s32 *p, ch, j, c, m, v, x, str, w, col, ty;
    u32 b;
    s32 x8, t;
    PN *pn;
    k = D_00304BE8->x48e[D_00642CCC];
    p = D_003F40F8[k].p;
    pnn = &D_003F40F8[k].n;
    n = *pnn;
    if (func_001f42b8(o)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3dc0(o->x24);
            func_0020bda8(16);
            if (o->xc) o->xc->x24 = D_003F43F0[D_00642CD8];
            func_0011d768(3);
        } else {
            t = *pnn;
            ch = 0;
            if (D_00425BC8->x10 & PAD_DIR(PAD_UP)) {
                if (D_00642CDC > 0) {
                    D_00642CDC--;
                    ch = 1;
                } else if (D_00425BC8->x8 & PAD_DIR(PAD_UP)) {
                    D_00642CDC = t - 1;
                    ch = 1;
                }
            } else if (D_00425BC8->x10 & PAD_DIR(PAD_DOWN)) {
                if (D_00642CDC < t - 1) {
                    D_00642CDC++;
                    ch = 1;
                } else if (D_00425BC8->x8 & PAD_DIR(PAD_DOWN)) {
                    D_00642CDC = 0;
                    ch = 1;
                }
            }
            if (ch) {
                D_00642CE0 = 2 - func_00170dd8(k, p[D_00642CDC]);
                if (o->xc) {
                    j = p[D_00642CDC];
                    if (k == 2 && j == 7) o->xc->x24 = 265;
                    else o->xc->x24 = D_003F4408[j];
                }
                func_0011d768(1);
            }
            ch = 0;
            if (D_00425BC8->x10 & PAD_DIR(PAD_LEFT)) {
                if (D_00642CE0 > 0) {
                    D_00642CE0--;
                    ch = 1;
                } else if (D_00425BC8->x8 & PAD_DIR(PAD_LEFT)) {
                    D_00642CE0 = 2;
                    ch = 1;
                }
            } else if (D_00425BC8->x10 & PAD_DIR(PAD_RIGHT)) {
                if (D_00642CE0 < 2) {
                    D_00642CE0++;
                    ch = 1;
                } else if (D_00425BC8->x8 & PAD_DIR(PAD_RIGHT)) {
                    D_00642CE0 = 0;
                    ch = 1;
                }
            }
            if (ch) {
                func_00170d60(k, p[D_00642CDC], 2 - D_00642CE0);
                func_0011d768(1);
            }
            if (func_001fe570(o)) {
                func_001f3d58(o, 5);
                func_001f3d58(o->x24, 5);
                func_001f3758(o->x24);
                func_0020bda8(16);
                func_0011d768(2);
                D_003F34B8->a[k] = 5;
            }
        }
    }
    func_001ff488(o, -148, 28, 490, n * 26 + 12, 0x60000000);
    y = 57;
    sel = func_001f4378(o);
    for (i = 0; i < n; i++) {
        j = p[i];
        if (k == 2 && j == 7) str = 255;
        else str = D_003F4380[j];
        ty = y - 15;
        func_001f9438(o, 0, -136, ty, str, 15, 0x8080C0C0);
        func_002066b0(o, -136, y, 466, 0x80323232, 0x80323232);
        for (m = 0; m < 3; m++) {
            c = D_00642CD8;
            switch (c) {
            case 0:
            default:
                w = 2 - D_003F41E8[c][j];
                break;
            case 4:
                w = 2 - D_003F4200[k][j];
                break;
            case 5:
                w = 2 - func_00170dd8(k, j);
                break;
            }
            str = D_003F43C8[j][m];
            x = D_003F4508[m];
            col = 0x40E6E6E6;
            if (m == w) {
                w = func_001f0118(str, 15) + 2;
                col = (sel && i == D_00642CDC) ? 0x80303080 : 0x80303030;
                func_002053e8(o, x - 2, y - 17, w + 4, 19, col);
                col = 0x80E6E6E6;
            }
            func_001f9438(o, 0, x, ty, str, 15, col);
        }
        y += 26;
    }
}

void func_00216e60(TextWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, arg0->x24, 0x11, 0x80C87850);
}

void func_00216ea8(void) {
    s32 k = D_00304BE8->x48e[D_00642CCC];
    s32 *p, n, i;
    p = D_003F40F8[k].p;
    n = D_003F40F8[k].n;
    D_003F34B8->a[k] = *(u8 *)&D_00642CD8;
    switch (D_00642CD8) {
    case 3:
    default:
        for (i = 0; i < n; i++) {
            func_00170d60(k, p[i], D_003F41E8[D_00642CD8][p[i]]);
        }
        break;
    case 4:
        for (i = 0; i < n; i++) {
            func_00170d60(k, p[i], D_003F4200[k][p[i]]);
        }
        break;
    case 5:
        break;
    }
}

/* func_00217000 (the style list) is in customize.nostrict.c. */

void func_00217490(void *a) {
    s32 i, y, t, k, n, id, c, r;
    s32 *p;
    if (D_00642CCC == 0) {
        y = 0;
        for (i = 0; i < 3; i++) {
            func_00207830(a, 2, 2, 0, y, 180, D_003F45A8[i]);
            func_001f9438(a, 0, 86, y + 5, 51, 15, 0x20E6E6E6);
            t = func_00132f88(func_0013c288(i));
            if (!t) t = func_001efbb8(212);
            func_001f94f0(a, 0, 96, y + 5, t, 15, 0x20E6E6E6);
            y += 28;
        }
    } else {
        k = D_00304BE8->x48e[D_00642CCC];
        n = D_003F40F8[k].n;
        p = D_003F40F8[k].p;
        func_00207830(a, 2, 2, 0, 0, 342, D_003F4368[D_003F34B8->a[k]]);
        func_001ff488(a, 0, 28, 342, n * 28 + 10, 0x40000000);
        y = 57;
        for (i = 0; i < n; i++) {
            id = p[i];
            if (k == 2 && id == 7) c = 255;
            else c = D_003F4380[id];
            func_002066b0(a, 12, y, 318, 0x20E6E6E6, 0x20E6E6E6);
            func_001f9438(a, 0, 12, y - 15, c, 15, 0x20E6E6E6);
            r = func_00170dd8(k, id);
            func_001f9438(a, 0, 191, y - 15, D_003F43C8[id][2 - r], 15, 0x20E6E6E6);
            y += 26;
        }
    }
}

void func_00217750(TextWin *arg0) {
    s32 var_s1;

    var_s1 = 0xCC;
    if (D_00642CCC != 0) {
        var_s1 = 0xCD;
        D_003E8E08[0] = func_001ee618(D_00642CCC);
    }
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, var_s1, 0x11, 0x80C87850);
}

/* The member list.  The table base is read into a pointer first (t, then
 * tn = &t->n) so its lui is the earliest insn after the func_001f3d58 call:
 * sched issues the lowest-LUID insn made ready by a call in the call's own
 * cycle. */
void func_002177c8(CuWinU *a) {
    CuWinU *o[3];
    CuWinU *p;
    s32 *pc;
    u32 i;
    s32 sel, y;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3758(D_00642C90);
            func_0011d768(3);
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            sel = func_001fd518(a);
            pc = &D_00642CCC;
            *pc = sel;
            if (func_001fe570(a)) {
                func_001f3d58(a, 5);
                p = a->x10->x10;
                func_001f3d58(p, 0);
                func_001f3758(a);
                if (*pc == 0) {
                    D_00642C94 = 1;
                    D_00642C98 = D_00304BE8->x48e[0];
                    if ((o[0] = func_001f31a8(D_003F44E0, 0))) {
                        func_001f3e48(o[0], p);
                        func_001f3d58(o[0], 6);
                        o[0]->xd2 = (u16)D_00642CD0 << 4;
                        if ((o[1] = func_001f31a8(D_003F44A0, 6))) {
                            func_001f3e48(o[1], o[0]);
                            func_001f3dc0(o[0]);
                        }
                    }
                } else {
                    if ((o[0] = func_001f31a8(D_003F4580, 0))) {
                        Save_304be8 **b;
                        s32 *pd;
                        func_001f3e48(o[0], p);
                        b = &D_00304BE8;
                        func_001f3d58(o[0], 6);
                        pd = &D_00642CD8;
                        *pd = D_003F34B8->a[D_00304BE8->x48e[D_00642CCC]];
                        if ((o[1] = func_001f31a8(D_003F4550, 6))) {
                            func_001f3e48(o[1], o[0]);
                            o[1]->x24.i = D_003F43F0[*pd];
                            if ((o[2] = func_001f31a8(D_003F4520, 0))) {
                                u8 *q;
                                U32H *pdc;
                                PN *t;
                                s32 *tn;
                                func_001f3e48(o[2], o[1]);
                                func_001f3d58(o[2], 6);
                                t = D_003F40F8;
                                tn = &t->n;
                                pdc = (U32H *)&D_00642CDC;
                                q = (u8 *)(*pc + (u32)*b) + 0x48e;
                                o[2]->xba = tn[*q * 2] * 416;
                                o[2]->xcc = tn[*q * 2];
                                o[2]->xce = tn[*q * 2];
                                pdc->i = 0;
                                ((U32H *)&D_00642CE0)->i = 0;
                                o[2]->xd2 = pdc->h << 4;
                                o[0]->x24.p = o[2];
                                o[2]->x24.p = o[0];
                                func_001f3dc0(o[0]);
                            }
                        }
                    }
                }
            }
        }
    }
    sel = func_001fd518(a);
    y = 0;
    for (i = 0; i < D_003E3D68; i++) {
        func_00207870(a, i == sel, 2, 0, y, 122, func_001ee5f0(D_00304BE8->x48e[i]));
        y += 28;
    }
}

void func_00217b38(void *a) {
    CuWin7 *o[3];
    s32 *p;
    if (func_001f42b8(a)) {
        p = &D_00642C94;
        switch (*p) {
        case 0:
            if ((o[0] = func_001f31a8(D_003F4620, 6))) {
                u32 *n;
                func_001f3e48(o[0], a);
                n = &D_003E3D68;
                o[0]->xcc = o[0]->xce = *n;
                o[0]->xba = *n * 448 - 32;
                o[0]->xd2 = D_00642CCC << 4;
                if ((o[1] = func_001f31a8(D_003F45F0, 6))) {
                    func_001f3e48(o[1], o[0]);
                    if ((o[2] = func_001f31a8(D_003F45C0, 6))) {
                        func_001f3e48(o[2], o[1]);
                        func_001f3dc0(o[0]);
                    }
                }
            }
            break;
        case 1:
        case1:
            if ((o[0] = func_001f31a8(D_003F44E0, 6))) {
                func_001f3e48(o[0], a);
                o[0]->xd2 = (u16)D_00642CD0 << 4;
                if ((o[1] = func_001f31a8(D_003F44A0, 6))) {
                    func_001f3e48(o[1], o[0]);
                    func_001f3dc0(o[0]);
                }
            }
            break;
        case 2:
            if ((o[0] = func_001f31a8(D_003F4460, 6))) {
                func_001f3e48(o[0], a);
                o[0]->xcc = o[0]->xce = D_00642CC8;
                o[0]->xd2 = D_00642CD4 << 4;
                if ((o[1] = func_001f31a8(D_003F4430, 6))) {
                    func_001f3e48(o[1], o[0]);
                    func_001f3dc0(o[0]);
                }
            }
            break;
        case 3:
            if (D_00642CCC == 0) {
                *p = 1;
                goto case1;
            }
            break;
        }
    }
    switch (D_00642C94) {
    default:
    case 0:
        break;
    case 1:
        func_00206690(a, 0, 83, 11);
        func_00207870(a, 11, 0, 11, 71, 122, func_001ee5f0(D_00642C98));
        break;
    case 2:
        func_00206690(a, 0, 83, 11);
        func_00207870(a, 11, 0, 11, 71, 122, func_001ee5f0(D_00642C98));
        func_00206690(a, 133, 83, 26);
        func_00207830(a, 11, 2, 159, 71, 166, D_003F44C8[D_00642C9C]);
        break;
    case 3:
        func_00206690(a, 0, 83, 11);
        func_00207870(a, 11, 0, 11, 71, 122, func_001ee5f0(D_00642C98));
        func_00206690(a, 133, 83, 26);
        func_00207830(a, 11, 2, 159, 71, 166, D_003F44C8[D_00642C9C]);
        func_00206690(a, 325, 83, 26);
        func_00207870(a, 11, 2, 351, 71, 122, D_00642CA0);
        func_00206690(a, 473, 83, 39);
        break;
    }
}

void func_00217f28(TextWin *arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x6C);
}

void func_00217f58(TextWin *arg0) {
    TextWin *temp_v0;

    temp_v0 = func_001f31a8(D_003F4650, 0);
    if (temp_v0 != 0) {
        func_001f3e48(temp_v0, arg0);
    }
    D_00642C90 = arg0;
    D_00642C94 = 0;
}

void func_00217fb0(void) {
    u32 *p = (u32 *)&D_00642CCC;
    u32 n = D_003E3D68 - 1;
    if (n < *p) *p = n;
    func_00216280();
}

void func_00217fe8(void) {
    D_00642CCC = 0;
    D_00642CD0 = 0;
    D_00642CD4 = 0;
    D_00642CD8 = 0;
    D_00642CDC = 0;
    D_00642CE0 = 0;
}
