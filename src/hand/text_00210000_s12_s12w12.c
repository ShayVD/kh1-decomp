#include "common.h"
#include "data/bss_0064.h"
typedef struct { u8 pad0[0x24]; s32 x24; } Ob2;
typedef struct { u8 pad0[0xc]; Ob2 *xc; u8 pad10[0x24 - 0x10]; void *x24; } Ob1;
typedef struct { s32 *p; s32 n; } PN;
typedef struct { s32 x0; s32 x4; s32 x8; u8 padc[0x20 - 0xC]; u8 x20[1]; } S34B8;
typedef struct { u8 pad[0x44]; u8 name[116 - 0x44]; } Rec74;
typedef struct { Rec74 r[10]; u8 pad[6]; u8 x48e[1]; } S4BE8;
typedef struct { u8 pad[8]; s32 x8; u8 padc[4]; u32 x10; } Cfg;
extern Cfg *D_00425BC8;
extern S4BE8 *D_00304BE8;
extern s32 D_00642CCC;
extern S34B8 *D_003F34B8;
extern s32 D_00642CD8;
extern s32 D_00642CDC;
extern s32 D_00642CE0;
extern PN D_003F40F8[];
extern s32 *D_003F41E8[];
extern s32 D_003F4200[][9];
extern s32 D_003F43F0[];
extern s32 D_003F4408[];
extern s32 D_003F4380[];
extern s32 *D_003F43C8[];
extern s32 D_003F4508[];
s32 func_001f42b8(void *);
void func_001f3dc0(void *);
void func_0020bda8(s32);
void func_0011d768(s32);
s32 func_00170dd8(s32, s32);
void func_00170d60(s32, s32, s32);
s32 func_001fe570(void *);
void func_001f3d58(void *, s32);
s32 func_001f3758(void *);
void func_001ff488(void *, s32, s32, s32, s32, s32);
s32 func_001f4378(void *);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
s32 func_001f0118(s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);

void func_00216890(Ob1 *o) {
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
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3dc0(o->x24);
            func_0020bda8(16);
            if (o->xc) o->xc->x24 = D_003F43F0[D_00642CD8];
            func_0011d768(3);
        } else {
            t = *pnn;
            ch = 0;
            if (D_00425BC8->x10 & 0x10000010) {
                if (D_00642CDC > 0) {
                    D_00642CDC--;
                    ch = 1;
                } else if (D_00425BC8->x8 & 0x10000010) {
                    D_00642CDC = t - 1;
                    ch = 1;
                }
            } else if (D_00425BC8->x10 & 0x40000040) {
                if (D_00642CDC < t - 1) {
                    D_00642CDC++;
                    ch = 1;
                } else if (D_00425BC8->x8 & 0x40000040) {
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
            if (D_00425BC8->x10 & 0x80000080) {
                if (D_00642CE0 > 0) {
                    D_00642CE0--;
                    ch = 1;
                } else if (D_00425BC8->x8 & 0x80000080) {
                    D_00642CE0 = 2;
                    ch = 1;
                }
            } else if (D_00425BC8->x10 & 0x20000020) {
                if (D_00642CE0 < 2) {
                    D_00642CE0++;
                    ch = 1;
                } else if (D_00425BC8->x8 & 0x20000020) {
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
                D_003F34B8->x20[k] = 5;
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
#include "data/bss_0064_mixed.h"
