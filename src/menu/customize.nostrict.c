/* The customize page (src/menu/customize.c; docs/modules.md "Session 40"): the
 * two windows that need -fno-strict-aliasing.  func_002163e0 (was
 * src/hand/nostrict/text_00200000_h70.c) is the magic list of a shortcut: it
 * sets shortcut D_00642CD0 to D_00642CA8[cursor] (func_0013c270) or clears
 * it (the last entry, "none").  func_00217000 (was
 * src/hand/nostrict/text_00210000_s11_w35.c) picks a member's style
 * (D_00642CD8, six entries; 5 is the custom one) and applies it
 * (func_00216ea8); left / right change the member.
 *
 * func_00217000: from a 6-word draft.  FLAGGED dead set: `E20 *tbl =
 * D_003F2C40;` at entry is dead (tbl is set again after the third draw call,
 * before its only use); life1 deletes it, but it stops combine folding the
 * la into lui/addu/lw sym+16. */
#include "common.h"
#include "text/textwin.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003F34B8.h"
#include "data/pieces/D_003F2C40.h"
#include "data/types/text_00210000_b14.h"

/* A view of a TextWin (include/text/textwin.h): +0x24 is a pointer here. */
typedef struct CuWin7 { u8 pad[0x10]; struct CuWin7 *x10; u8 p14[0x10]; struct CuWin7 *x24; s32 x28; u8 p2c[0xCE - 0x2C]; s16 xce; s16 xd0; s16 xd2; } CuWin7;

extern s32 D_00642CA0, D_00642CA8[], D_00642CC8;
extern s32 D_00642CCC, D_00642CD0, D_00642CD4, D_00642CD8, D_00642CDC, D_00642CE0;
extern PN D_003F40F8[];
extern s32 D_003F43F0[], D_003F4408[], D_003F4368[];

void func_0011d768(s32);
s32 func_00132f88(s32);
void func_0013c270(s32, s32);
s32 func_00170dd8(s32, s32);
s32 func_001ee5f0(s32);
s32 func_001efbb8(s32);
s32 func_001f3758(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
s32 func_001f42b8(void *);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
void func_001fd858(void *);
s32 func_001fe570(void *);
void func_00206130(void *, s32, s32, s32, s32, s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0020bd18(void *, s32);
void func_0020be10(s32);
void func_00216ea8(void);

void func_002163e0(TextWin *a0) {
    s32 i, y, sel;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a0);
            func_0011d768(3);
            D_00642C94 = 1;
        } else {
            func_001fd858(a0);
            func_0020bd18(a0, 8);
            D_00642CD4 = func_001fd518(a0);
            if (func_001fe570(a0)) {
                func_001f3d58(a0, 5);
                func_001f3758(a0);
                D_00642C94 = 3;
                if (D_00642CD4 == D_00642CC8 - 1) {
                    D_00642CA0 = func_001efbb8(212);
                    func_0013c270(D_00642CD0, -1);
                } else {
                    s32 *q = D_00642CA8;
                    s32 *p = &D_00642CA0;
                    s32 v = func_00132f88(q[D_00642CD4]);
                    *p = v;
                    func_0013c270(D_00642CD0, q[D_00642CD4]);
                }
            }
        }
    }
    sel = func_001fd518(a0);
    for (i = 0, y = 0; i < D_00642CC8; i++, y += 28) {
        s32 t;
        if (i == D_00642CC8 - 1) t = func_001efbb8(212);
        else t = func_00132f88(D_00642CA8[i]);
        func_00207870(a0, i == sel, 2, 0, y, 122, t);
    }
}

void func_00217000(CuWin7 *a) {
    s32 k, cur, ch, sel, c;
    s32 *pn;
    s32 *p, *p2;
    CuWin7 *o;
    PadSt_425bc8 *cfg;
    E20_3F2C40 *tbl = D_003F2C40.e20; /* FLAGGED dead set (see the top) */
    k = D_00304BE8->x48e[D_00642CCC];
    pn = D_003F40F8[k].p;
    sel = 11;
    if (func_001f42b8(a)) {
        sel = 1;
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            func_001f3d58(a, 5);
            func_001f3d58(a->x24, 5);
            func_001f3758(a);
            func_00216ea8();
            goto draw;
        }
        cur = D_00642CCC;
        if (D_003E3D68 >= 3) {
            ch = 0;
            if (D_00425BC8->x10 & 0x10000010) {
                if (cur >= 2) {
                    cur--;
                    ch = 1;
                } else if (D_00425BC8->x8 & 0x10000010) {
                    cur = D_003E3D68 - 1;
                    ch = 1;
                }
            } else if (D_00425BC8->x10 & 0x40000040) {
                if (cur < D_003E3D68 - 1) {
                    cur++;
                    ch = 1;
                } else if (D_00425BC8->x8 & 0x40000040) {
                    cur = 1;
                    ch = 1;
                }
            }
            if (ch) {
                func_00216ea8();
                D_00642CCC = cur;
                { s32 n2 = D_00304BE8->x48e[cur];
                D_00642CD8 = D_003F34B8->a[n2];
                D_00642CDC = 0;
                k = n2;
                pn = D_003F40F8[n2].p; }
                func_0011d768(1);
            }
        }
        func_0020bd18(a, 8);
        ch = 0;
        if (D_00425BC8->x10 & 0x80000080) {
            p = &D_00642CD8;
            if (*p > 0) {
                *p = *p - 1;
                ch = 1;
            } else if (D_00425BC8->x8 & 0x80000080) {
                *p = 5;
                ch = 1;
            }
        } else if (D_00425BC8->x10 & 0x20000020) {
            p2 = &D_00642CD8;
            if (*p2 < 5) {
                *p2 = *p2 + 1;
                ch = 1;
            } else if (D_00425BC8->x8 & 0x20000020) {
                *p2 = 0;

                ch = 1;
            }
        }
        if (ch) {
            if ((o = a->x10)) o->x24 = (CuWin7 *)D_003F43F0[D_00642CD8];
            func_0011d768(1);
        }
        if (func_001fe570(a)) {
            s32 *pd, *pe;
            func_0011d768(2);
            func_00216ea8();
            D_003F34B8->a[k] = 5;
            pd = &D_00642CDC;
            pe = &D_00642CE0;
            c = func_00170dd8(k, pn[*pd]);
            *pe = 2;
            do { } while (0);
            D_00642CD8 = 5;
            *pe -= c;
            if ((o = a->x10)) o->x24 = (CuWin7 *)D_003F4408[pn[*pd]];
            o = a->x24;
            o->xd2 = *(u16 *)pd << 4;
            func_0020be10(16);
            func_001f3dc0(o);
        }
    }
draw:
    func_00206130(a, -223, 12, 76, 2, 0x80FE7266);
    func_00207870(a, 11, 2, -148, 0, 122, func_001ee5f0(k));
    func_00206130(a, -26, 12, 26, 2, 0x80FE7266);
    tbl = D_003F2C40.e20;
    c = tbl[sel].x10;
    func_002078f0(a, sel, 2, 2, 0, 0, 342, 171, D_003F4368[D_00642CD8]);
    func_001fc308(a, 16, 7, 0, 0, 15, 0, c, c);
    func_001fc308(a, 316, 7, 0, 0, 16, 0, c, c);
}
