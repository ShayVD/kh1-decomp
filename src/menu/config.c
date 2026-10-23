/* The config page of the menu (docs/modules.md "Session 41"),
 * 0x00219440-0x0021ade8: page 6 of the top menu (message 0x6f; its open
 * function is func_0021ad08, set up func_0021adb0, reset func_0021adc8).
 * func_00219f98 is the option list: eight rows (D_00642D24 the cursor),
 * seven settings of D_003F34B8 (src/menu/settings.c's func_00219158 /
 * func_002191f0 step them up to D_003F4C18[n]), and row 7 resets them;
 * the first three rows open a two-choice window each (func_00219a88,
 * func_00219c18, func_00219da8 from D_003F4B40 / D_003F4B70 / D_003F4BA0).
 * func_00219500 loads two textures (func_0011fbb0 into D_00642D30 /
 * D_00642DE0) that config.nostrict.c's func_00219598 draws behind
 * func_00219870's twelve-box frame (when D_003F34CC is 2).  Most likely
 * the config page; not proved by a boot.
 *
 * Window views: CfWin (plain s16 at +0xd2 / +0xda: TextWin's +0xd0 union
 * reorders) and topmenu.c's N_3f34c4 (D_003F34C4.h). */
#include "common.h"
#include "menu/settings.h"
#include "data/bss_0064.h"
#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_003F34B8.h"
#include "data/pieces/D_003F34C4.h"
#include "data/pieces/D_003F34C8.h"
#include "data/pieces/D_003F47A8.h"
#include "data/pieces/D_003F4AA8.h"
#include "data/pieces/D_00425BC8.h"

typedef struct CfWin {
    u8 pad[0xD2];
    s16 xd2;
    u8 padd4[0xDA - 0xD4];
    s16 xda;
} CfWin;
typedef struct { s32 p0; s32 p1; } P2;
typedef struct { u8 pad0[0x48]; s32 x48; u8 pad4c[0x74 - 0x4c]; f32 sx, sy; u8 pad7c[0x90 - 0x7c]; s32 x90; u8 pad94[0xb0 - 0x94]; s32 xb0, xb4; } CfBg;
typedef struct { s32 a, b, c, d; } CfRect;

extern s32 D_003F4818[], D_003F4848[], D_003F4878[], D_003F48A8[];
extern CfRect *D_003F4A48[];
extern s32 D_003F4A78[];
extern s32 D_003F4790[];
extern s32 D_003F4798[];
extern s32 D_003F47A0[];
extern char D_00490F10[];
extern u8 D_003F4B10[];
extern u8 D_003F4B40[];
extern u8 D_003F4B70[];
extern u8 D_003F4BA0[];
extern u8 D_003F47F0[];
extern u8 D_003F4BF0[];
extern u8 D_003F4C90[];
extern s32 D_003F4C18[];
extern s32 D_003F4C38[];
extern s32 D_003F4C58[];
extern s32 D_003F4C68[];
extern s32 D_003F4C78[];

void func_0011d768(s32);
void *func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, s32, void *);
s32 func_00120748(char *, s32, void (*)(void), s32);
void func_001edaf0(s32);
s32 func_001efbb8(s32);
void *func_001f31a8(void *, s32);
void *func_001f3520(void *, s32);
s32 func_001f3758(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
s32 func_001f42b8(void *);
void *func_001f4468(void *);
void func_001f9010(s32);
void func_001f9270(void *, s32, s32, s32, s32, s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, u32, u32);
s32 func_001fd518(void *);
s32 func_001fd538(void *);
void func_001fd858(void *);
void func_001fdfd0(void *);
s32 func_001fe570(void *);
void func_00206130(void *, s32, s32, s32, s32, u32);
void func_00206690(void *, s32, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0020bd18(void *, s32);

#define ROW(n) if (D_00642D24 == n) { t.p0 = D_003F4C68[k * 2]; t.p1 = D_003F4C68[k * 2 + 1]; } else { t.p0 = D_003F4C78[k * 2]; t.p1 = D_003F4C78[k * 2 + 1]; }

s32 func_00219440(s32 arg0) {
    return ((s32 *)D_003F47A8)[arg0];
}

s32 func_00219458(s32 arg0) {
    return func_001efbb8(func_00219440(arg0));
}

void func_00219478(N_3f34c4 *a) {
    func_001f9010(0x17);
    func_001f9438(a, 0, 0xAE, 0xC, (&D_003F47B8)[a->x24], 0x11, 0x80C87850);
}

void func_002194d0(void) {
    D_003F34CC += 1;
    D_003F34C8 -= 1;
}

void func_00219500(void) {
    func_0011fbb0(0x3600, 4, 0x13, 0, 0, 0x8A, 0x58, 0x2F7, D_003F34D0, D_00642D30);
    func_0011fbb0(0x3680, 1, 0, 0, 0, 0x10, 0x10, 0x40, D_003F34D0 + 0x2F70, D_00642DE0);
}

/* func_00219598 is in config.nostrict.c; func_00219870 matches only with a
 * body of it above (one branch-likely), as func_00219f98 with func_00219380. */
CONTEXT_ONLY void func_00219598(void *o, s32 x, s32 y) { }

void func_00219870(CfBg *o) {
    s32 i, n;
    CfRect *r;
    P2_q0 *q;
    s32 *np;
    CfRect **rp;
    func_001f9270(o, 0, 16, 325, 15, 0x801EC8C8);
    for (i = 0; i < 12; i++) {
        func_001f9438(o, D_003F4878[i], D_003F4818[i], D_003F4848[i], D_003F48A8[i], 15, i == D_00642D28 ? 0x80B4B4B4 : 0x40808080);
    }
    if (D_003F34CC == 2) func_00219598(o, 176, 61);
    rp = D_003F4A48;
    np = D_003F4A78;
    for (i = 0; i < 12; i++) {
        n = *np;
        r = *rp;
        for (; n > 0; n--) {
            func_00206130(o, r->a, r->b, r->c, r->d, i == D_00642D28 ? 0x80F35054 : 0x33F35054);
            r++;
        }
        np++;
        rp++;
    }
    q = &D_003F4AA8[D_00642D28];
    func_001fc308(o, q->x, q->y, 0, 0, 10, 0, 0x33F35054, 0x33F35054);
    func_001fc308(o, q->x, q->y + 15, 0, 0, 11, 0, 0x33F35054, 0x33F35054);
}

void func_00219a88(N_3f34c4 *a) {
    N_3f34c4 *o;
    s32 v, s, i, y;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
        } else {
            func_001fdfd0(a);
            func_0020bd18(a, 8);
            D_003F34B8->f0 = func_001fd538(a);
            if ((o = a->x10)) {
                func_001fd858(o);
                v = func_001fd518(o);
                D_00642D28 = v;
                if ((o = o->x10)) o->x24 = v;
            }
            if (func_001fe570(a)) func_001f3758(a);
        }
    }
    func_00206690(a, -75, 12, 76);
    func_002078f0(a, 11, 0, 2, 0, 0, 142, 71, 294);
    s = func_001fd538(a);
    y = 148;
    for (i = 0; i < 2; i++) {
        func_002078f0(a, i == s, 2, 2, y, 0, 106, y + 53, D_003F4790[i]);
        y += 112;
    }
}

void func_00219c18(N_3f34c4 *a) {
    N_3f34c4 *o;
    s32 v, s, i, y;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
        } else {
            func_001fdfd0(a);
            func_0020bd18(a, 8);
            D_003F34B8->f4 = func_001fd538(a);
            if ((o = a->x10)) {
                func_001fd858(o);
                v = func_001fd518(o);
                D_00642D28 = v;
                if ((o = o->x10)) o->x24 = v;
            }
            if (func_001fe570(a)) func_001f3758(a);
        }
    }
    func_00206690(a, -75, 12, 76);
    func_002078f0(a, 11, 0, 2, 0, 0, 142, 71, 299);
    s = func_001fd538(a);
    y = 148;
    for (i = 0; i < 2; i++) {
        func_002078f0(a, i == s, 2, 2, y, 0, 106, y + 53, D_003F4798[i]);
        y += 112;
    }
}

void func_00219da8(N_3f34c4 *a) {
    N_3f34c4 *o;
    s32 v, s, i, y;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
        } else {
            func_001fdfd0(a);
            func_0020bd18(a, 8);
            D_003F34B8->f8 = func_001fd538(a);
            if ((o = a->x10)) {
                func_001fd858(o);
                v = func_001fd518(o);
                D_00642D28 = v;
                if ((o = o->x10)) o->x24 = v;
            }
            if (func_001fe570(a)) func_001f3758(a);
        }
    }
    func_00206690(a, -75, 12, 76);
    func_002078f0(a, 11, 0, 2, 0, 0, 142, 71, 303);
    s = func_001fd538(a);
    y = 148;
    for (i = 0; i < 2; i++) {
        func_002078f0(a, i == s, 2, 2, y, 0, 106, y + 53, D_003F47A0[i]);
        y += 112;
    }
}

void func_00219f38(void *a) {
    func_001f9010(0x17);
    func_001f9438(a, 0, 0xAE, 0xC, (&D_003F4BD0)[D_00642D24], 0x11, 0x80C87850);
}

/* func_00219f98 (rodata jtbl 0x490f20) matches only with a body of
 * func_00219380 above it (one branch-likely); settings.c defines it.  Key:
 * D_003F4C68/78 as flat s32 arrays read [k*2] then [k*2+1] (base + (k*8+4)
 * gives the addu/move copy pair). */
CONTEXT_ONLY s32 func_00219380(void) { return D_003F34B8->f14; }

void func_00219f98(void *a) {
    P2 t;
    CfWin *o[3];
    CfWin *p;
    s32 v, k, i, y, ch;

    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758((void *)D_00642D20);
            func_0011d768(3);
        } else if (D_00425BC8->x8 & 0x2000) {
            switch (D_00642D24) {
            case 0:
                p = func_001f4468(a);
                func_001f3d58(a, 5);
                func_001f3758(a);
                func_0011d768(2);
                if (D_003F34CC == 0) {
                    D_003F34CC = 1;
                    D_003F34C8++;
                    func_00120748(D_00490F10, D_003F34D0, func_002194d0, 0);
                }
                if ((o[0] = func_001f3520(D_003F4B40, 6))) {
                    func_001f3e90(p, o[0]);
                    func_001f3e20(o[0], p);
                    o[0]->xda = (u16)D_003F34B8->f0 * 16;
                    if ((o[1] = func_001f31a8(D_003F4B10, 6))) {
                        func_001f3e90(o[0], o[1]);
                        func_001f3e20(o[1], o[0]);
                        o[1]->xd2 = 96;
                        if ((o[2] = func_001f31a8(D_003F47F0, 6))) {
                            func_001f3e90(o[1], o[2]);
                            func_001f3e20(o[2], o[1]);
                            func_001f3dc0(o[0]);
                        }
                    }
                }
                break;
            case 1:
                p = func_001f4468(a);
                func_001f3758(a);
                func_0011d768(2);
                if (D_003F34CC == 0) {
                    D_003F34CC = 1;
                    D_003F34C8++;
                    func_00120748(D_00490F10, D_003F34D0, func_002194d0, 0);
                }
                if ((o[0] = func_001f3520(D_003F4B70, 6))) {
                    func_001f3e90(p, o[0]);
                    func_001f3e20(o[0], p);
                    o[0]->xda = (u16)D_003F34B8->f4 * 16;
                    if ((o[1] = func_001f31a8(D_003F4B10, 6))) {
                        func_001f3e90(o[0], o[1]);
                        func_001f3e20(o[1], o[0]);
                        o[1]->xd2 = 96;
                        if ((o[2] = func_001f31a8(D_003F47F0, 6))) {
                            func_001f3e90(o[1], o[2]);
                            func_001f3e20(o[2], o[1]);
                            func_001f3dc0(o[0]);
                        }
                    }
                }
                break;
            case 2:
                p = func_001f4468(a);
                func_001f3758(a);
                func_0011d768(2);
                if (D_003F34CC == 0) {
                    D_003F34CC = 1;
                    D_003F34C8++;
                    func_00120748(D_00490F10, D_003F34D0, func_002194d0, 0);
                }
                if ((o[0] = func_001f3520(D_003F4BA0, 6))) {
                    func_001f3e90(p, o[0]);
                    func_001f3e20(o[0], p);
                    o[0]->xda = (u16)D_003F34B8->f8 * 16;
                    if ((o[1] = func_001f31a8(D_003F4B10, 6))) {
                        func_001f3e90(o[0], o[1]);
                        func_001f3e20(o[1], o[0]);
                        o[1]->xd2 = 0;
                        if ((o[2] = func_001f31a8(D_003F47F0, 6))) {
                            func_001f3e90(o[1], o[2]);
                            func_001f3e20(o[2], o[1]);
                            func_001f3dc0(o[0]);
                        }
                    }
                }
                break;
            case 3:
            case 4:
                if (func_00219158(D_00642D24) < D_003F4C18[D_00642D24])
                    func_002191f0(D_00642D24, func_00219158(D_00642D24) + 1);
                else
                    func_002191f0(D_00642D24, 0);
                func_0011d768(1);
                if (D_00642D24 == 4)
                    func_001edaf0(func_00219380() == 0);
                break;
            case 5:
                if (func_00219428()) {
                    if (func_00219158(5) <= 0)
                        func_002191f0(5, func_00219158(5) + 1);
                    else
                        func_002191f0(5, 0);
                    func_0011d768(1);
                    break;
                }
            case 6:
                func_0011d768(4);
                break;
            case 7:
                func_0011d768(2);
                D_003F34B8->f0 = 0;
                D_003F34B8->f4 = 0;
                D_003F34B8->f8 = 0;
                D_003F34B8->f10 = 0;
                D_003F34B8->f14 = 0;
                D_003F34B8->f18 = 0;
                func_001edaf0(1);
                break;
            }
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            v = func_001fd518(a);
            D_00642D24 = v;
            ch = 0;
            if ((u32)(v - 6) >= 2 && (v != 5 || func_00219428())) {
                if (D_00425BC8->x10 & 0x80000080) {
                    if (func_00219158(D_00642D24) > 0) {
                        ch = 1;
                        func_002191f0(D_00642D24, func_00219158(D_00642D24) - 1);
                    } else if (D_00425BC8->x8 & 0x80000080) {
                        ch = 1;
                        func_002191f0(D_00642D24, D_003F4C18[D_00642D24]);
                    }
                } else if (D_00425BC8->x10 & 0x20000020) {
                    if (func_00219158(D_00642D24) < D_003F4C18[D_00642D24]) {
                        ch = 1;
                        func_002191f0(D_00642D24, func_00219158(D_00642D24) + 1);
                    } else if (D_00425BC8->x8 & 0x20000020) {
                        func_002191f0(D_00642D24, 0);
                        ch = 1;
                    }
                }
                if (ch) {
                    func_0011d768(1);
                    if (D_00642D24 == 4)
                        func_001edaf0(func_00219380() == 0);
                }
            }
        }
    }
    y = 71;
    for (i = 0; i < 8; i++) {
        k = 0;
        if (i == D_00642D24) {
            if (i < 7) {
                s32 yy = y + 12;
                k = 11;
                func_00206690(a, -64, yy, 75);
                func_00206690(a, 153, yy, 6);
                if (D_00642D24 != 6) {
                    func_00206690(a, 321, yy, 6);
                    func_00206690(a, 489, yy, 23);
                } else {
                    func_00206690(a, 489, yy, 23);
                }
            } else {
                k = 1;
            }
        }
        func_002078f0(a, k, 2, 0, 11, y, 142, 27, D_003F4C38[i]);
        y += 28;
    }
    k = D_003F34B8->f0;
    ROW(0);
    func_002078f0(a, t.p0, 2, 2, 159, 71, 162, 240, 295);
    func_002078f0(a, t.p1, 2, 2, 327, 71, 162, 408, 296);
    k = D_003F34B8->f4;
    ROW(1);
    func_002078f0(a, t.p0, 2, 2, 159, 99, 162, 240, 300);
    func_002078f0(a, t.p1, 2, 2, 327, 99, 162, 408, 301);
    k = D_003F34B8->f8;
    ROW(2);
    func_002078f0(a, t.p0, 2, 2, 159, 127, 162, 240, 304);
    func_002078f0(a, t.p1, 2, 2, 327, 127, 162, 408, 305);
    k = D_003F34B8->f10;
    ROW(3);
    func_002078f0(a, t.p0, 2, 2, 159, 155, 162, 240, 312);
    func_002078f0(a, t.p1, 2, 2, 327, 155, 162, 408, 313);
    k = D_003F34B8->f14;
    ROW(4);
    func_002078f0(a, t.p0, 2, 2, 159, 183, 162, 240, 316);
    func_002078f0(a, t.p1, 2, 2, 327, 183, 162, 408, 317);
    k = D_003F34B8->f18;
    ROW(5);
    func_002078f0(a, t.p0, 2, 2, 159, 211, 162, 240, 452);
    func_002078f0(a, t.p1, 2, 2, 327, 211, 162, 408, 453);
    k = D_003F34B8->f2c;
    if (D_00642D24 == 6) t.p0 = D_003F4C68[0]; else t.p0 = D_003F4C78[0];
    func_002078f0(a, t.p0, 2, 2, 159, 239, 330, 324, D_003F4C58[k]);
    v = D_00642D24;
    if (v < 5) {
        y = v * 28 + 78;
        if (func_00219158(v) == 0)
            func_001fc308(a, 304, y, 0, 0, 16, 0, 0x80808080, 0x80808080);
        else
            func_001fc308(a, 335, y, 0, 0, 15, 0, 0x80808080, 0x80808080);
    }
}

void func_0021ac38(void *a0) {
    CfWin *b[2];
    if (func_001f42b8(a0) != 0) {
        b[0] = func_001f31a8(D_003F4C90, 6);
        if (b[0] != 0) {
            func_001f3e90(a0, b[0]);
            func_001f3e20(b[0], a0);
            b[0]->xd2 = *(u16 *)&D_00642D24 * 16;
            b[1] = func_001f31a8(D_003F4BF0, 6);
            if (b[1] != 0) {
                func_001f3e90(b[0], b[1]);
                func_001f3e20(b[1], b[0]);
                func_001f3dc0(b[0]);
            }
        }
    }
    func_00207830(a0, 4, 2, 0, 0, 122, 111);
}

void func_0021ad08(void *a0) {
    CfWin *b[2];
    b[0] = func_001f31a8(D_003F4C90, 6);
    if (b[0] != 0) {
        func_001f3e90(a0, b[0]);
        func_001f3e20(b[0], a0);
        b[0]->xd2 = *(u16 *)&D_00642D24 * 16;
        b[1] = func_001f31a8(D_003F4BF0, 6);
        if (b[1] != 0) {
            func_001f3e90(b[0], b[1]);
            func_001f3e20(b[1], b[0]);
            func_001f3dc0(b[0]);
        }
    }
    D_00642D20 = (s32)a0;
}

void func_0021adb0(void) {
    func_00219500();
}

void func_0021adc8(void) {
    D_00642D24 = 0;
}

s32 func_0021add8(void) {
    return D_003F34B8->b112[1];
}

/* func_00219870's boxes per frame (phase 4, tools/shift/define_ptr_tables.py;
 * moved from s6_22 in session 41). */
extern u8 D_003F48D8[];
extern u8 D_003F4908[];
extern u8 D_003F4918[];
extern u8 D_003F4928[];
extern u8 D_003F4948[];
extern u8 D_003F4968[];
extern u8 D_003F4988[];
extern u8 D_003F49A8[];
extern u8 D_003F49C8[];
extern u8 D_003F49E8[];
extern u8 D_003F4A08[];
extern u8 D_003F4A28[];
CfRect *D_003F4A48[0xc] ALIGNED(8) = {
    (void *)D_003F48D8, (void *)D_003F4908, (void *)D_003F4918, (void *)D_003F4928,
    (void *)D_003F4948, (void *)D_003F4968, (void *)D_003F4988, (void *)D_003F49A8,
    (void *)D_003F49C8, (void *)D_003F49E8, (void *)D_003F4A08, (void *)D_003F4A28,
};
