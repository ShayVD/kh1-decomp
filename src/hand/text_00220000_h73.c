#include "common.h"
typedef struct { u8 pad[8]; s32 x8; } F8;
#include "data/pieces/D_00425BC8.h"
typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[6]; s16 xbe; s16 xc0; s16 xc2; s16 xc4; s16 xc6; u8 p2[0xd2-0xc8]; s16 xd2; u8 p3[4]; s16 xd8; s16 xda; } O;
extern s32 D_006469B0, D_006469B4;
extern s32 D_003F7308[];
extern u8 D_003F7210[];
#include "data/pieces/D_003F47A8.h"
s32 func_001f42b8(void *);
void func_001f3708(void *, s32);
void func_0011d768(s32);
s32 func_00219428(void);
void func_00219418(s32);
void func_0020bc48(s32, s32, s32);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fd518(void *);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
s32 func_001fa808(void *, s32, s32, s32, s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_00209820(void *, s32, s32, s32, void *);


void func_0022c960(O *a0) {
    s32 i, y; s32 *p;
    if (func_001f42b8(a0) != 0) {
        if (((F8 *)D_00425BC8)->x8 & 0x4000) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            if ((D_006469B4 = D_006469B0, func_00219428()) != 0) {
                D_006469B0--;
            } else {
                D_006469B0 = 0;
            }
        } else {
            func_0020bc48(8, (a0->xb0 + a0->xc2 + a0->xbe - 0x7000) >> 4,
                          (a0->xb4 + a0->xc4 * a0->xd2 / 16 + a0->xc0 - 0x7400) >> 4);
            func_001fd858(a0);
            if (func_001fe570(a0) != 0) {
                func_001f3708(a0, 11);
                func_00219418(func_001fd518(a0));
                D_006469B4 = D_006469B0;
                D_006469B0++;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80C2726E, 0x80C2726E);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80C2726E, 0x80C2726E);
    func_001fa808(a0, 161, 88, 15, 0x80E6E6E6);
    y = 166;
    p = D_003F7308;
    for (i = 0; i < 3; i++) {
        func_001f9438(a0, 0, 211, y, *p++, 15, 0x80E6E6E6);
        y += 28;
    }
    func_00209820(a0, 2, 2, 111, D_003F47A8);
}

void func_001fdfd0(void *);
s32 func_001fd538(void *);
void func_002193e0(s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);

void func_0022cba8(O *a0) {
    s32 v;
    if (func_001f42b8(a0) != 0) {
        if (((F8 *)D_00425BC8)->x8 & 0x4000) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0--;
        } else {
            func_001fdfd0(a0);
            func_0020bc48(8, (a0->xb0 + a0->xc2 + (a0->xbe - 0x7000) + a0->xda * 202 - a0->xc6) >> 4,
                          (a0->xb4 + a0->xc4 * a0->xd2 / 16 + a0->xc0 - 0x7400) >> 4);
            if (func_001fe570(a0) != 0) {
                func_001f3708(a0, 11);
                func_002193e0(func_001fd538(a0));
                D_006469B4 = D_006469B0;
                D_006469B0++;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80C2726E, 0x80C2726E);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80C2726E, 0x80C2726E);
    func_001fa808(a0, 161, 449, 15, 0x80E6E6E6);
    v = func_001fd538(a0);
    func_002078f0(a0, v == 0, 2, 2, 85, 174, 140, 155, 447);
    func_002078f0(a0, v == 1, 2, 2, 231, 174, 196, 329, 448);
}

typedef struct { u8 pad0[0xA0]; f32 xa0; } Ob;
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
s16 *func_0011ef10(s32, void *);
s32 func_0022d498(void);
extern u8 D_003F74D0[], D_003F74A0[], D_003F73B0[], D_003F73E0[], D_003F7410[], D_003F7440[], D_003F7470[];
extern s32 D_003F34A4;
extern s32 D_006469B8[];

void func_0022d4d8(s32 arg0) {
    Ob *o[7];
    s32 i;
    func_001f3110();
    o[0] = func_001f31a8(D_003F74D0, 48);
    if (o[0] != NULL) {
        func_001f3d58(o[0], 0);
        o[1] = func_001f31a8(D_003F74A0, 46);
        if (o[1] != NULL) {
            func_001f3e90(o[0], o[1]);
            func_001f3e20(o[1], o[0]);
            func_001f3d58(o[1], 47);
            o[2] = func_001f31a8(D_003F73B0, 48);
            if (o[2] != NULL) {
                func_001f3e90(o[1], o[2]);
                func_001f3e20(o[2], o[1]);
                func_001f3d58(o[2], 49);
                o[3] = func_001f31a8(D_003F73E0, 48);
                if (o[3] != NULL) {
                    func_001f3e90(o[2], o[3]);
                    func_001f3e20(o[3], o[2]);
                    func_001f3d58(o[3], 49);
                    o[3]->xa0 = 1.0f;
                    o[4] = func_001f31a8(D_003F7410, 48);
                    if (o[4] != NULL) {
                        func_001f3e90(o[3], o[4]);
                        func_001f3e20(o[4], o[3]);
                        func_001f3d58(o[4], 49);
                        o[4]->xa0 = 2.0f;
                        o[5] = func_001f31a8(D_003F7440, 48);
                        if (o[5] != NULL) {
                            func_001f3e90(o[4], o[5]);
                            func_001f3e20(o[5], o[4]);
                            func_001f3d58(o[5], 49);
                            o[5]->xa0 = 3.0f;
                            o[6] = func_001f31a8(D_003F7470, 48);
                            if (o[6] != NULL) {
                                func_001f3e90(o[5], o[6]);
                                func_001f3e20(o[6], o[5]);
                                func_001f3d58(o[6], 49);
                                o[6]->xa0 = 4.0f;
                                func_001f3dc0(o[0]);
                            }
                        }
                    }
                }
            }
        }
    }
    D_003F34A4 = 1;
    for (i = 5; i >= 0; i--) D_006469B8[i] = 0;
    func_0011ef10(0x2BFE9, func_0022d498)[1] = arg0;
}

typedef struct { u8 p0[4]; u8 r[0x48e - 4]; u8 sel[0x499 - 0x48e]; u8 cnt[1]; } Base4BE8;
extern Base4BE8 *D_00304BE8;
#include "data/pieces/D_003E3D6C.h"
extern u32 D_00646A24;
extern s32 D_00647630;
extern u8 *D_00647634; /* src/data/bss_0064.c: s32 D_00647634 */
extern s32 D_00646A30[];
extern s32 D_00646E30[];
extern s32 D_00647230[];
s32 func_001ee728(s32);
s32 func_001ef0c0(s32);
void func_0020f290(s32 *, s32, s32);

void func_0022f818(void) {
    u32 sel = D_00646A24;
    s32 i, n, k, c;
    if (sel == -1) {
        D_00647630 = 0;
        return;
    }
    if (sel < D_003E3D6C) {
        D_00647634 = &D_00304BE8->r[D_00304BE8->sel[sel] * 116];
        n = D_00647634[0x21];
        D_00647630 = 0;
        for (i = 0; i < n; i++) {
            k = *(u8 *)(i + (s32)D_00647634 + 0x22);
            if (k != 0 && func_001ee728(k) != 0) {
                D_00646A30[D_00647630] = k;
                D_00646E30[D_00647630] = 1;
                D_00647230[D_00647630++] = i;
            }
        }
        return;
    }
    D_00647630 = 0;
    for (i = 1; i < 256; i++) {
        if (func_001ef0c0(i) != 0 && func_001ee728(i) != 0) {
            c = D_00647630; D_00647630 = c + 1; D_00646A30[c] = i;
        }
    }
    if (D_00647630 == 0) return;
    func_0020f290(D_00646A30, 0, D_00647630 - 1);
    for (i = 0; i < D_00647630; i++) {
        k = D_00646A30[i];
        D_00646E30[i] = func_001ef0c0(k);
        D_00647230[i] = k;
    }
}

extern s32 D_00646A1C;
extern s32 D_00646A28;
extern s32 D_00647638;
void func_001ef7b0(s32);
void func_0011d768(s32);

void func_0022fba8(void) {
    s32 *p = &D_00646A1C;
    if (*p > 0) {
        s32 *q = &D_00646A28;
        func_0011d768(8);
        func_001ef7b0(func_001ee728(*p) * *q);
        if (D_00646A24 < D_003E3D6C) {
            s32 o = (s32)D_00647634;
            ((u8 *)(D_00647638 + o))[0x22] = 0;
        } else {
            D_00304BE8->cnt[*p] -= *q;
        }
        func_0022f818();
    } else {
        func_0011d768(4);
    }
    D_00646A28 = 1;
}

extern s32 D_003F7A64;
extern s32 D_003F7A68;
extern s32 D_00646A00, D_00646A04;
extern s32 *D_00646A08; /* src/data/bss_0064.c: u16 *D_00646A08 */
extern s32 *D_00646A0C;
extern void *D_00646A10;
extern s32 D_00646A28;
extern s32 D_00647640, D_00647644;
extern u8 D_003F78B0[], D_003F79E0[], D_003F7A10[], D_003F7A40[];
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001ef830(void);
void func_0022eee0(s32);
void func_0022fc88(s32);
void func_0011d768(s32);
void func_0020bb90(s32, s32);
void func_0020bda8(s32);
s32 func_001eeb20(void);
s16 *func_0011ef10(s32, void *);
s32 func_002316f8(void);

void func_00231740(s32 mode, s32 *p, s32 a2, s32 a3) {
    if (D_003F7A64 != 0) return;
    func_001f3110();
    D_003F7A64 = 1;
    D_003F7A68 = 1;
    func_001ef830();
    func_0022eee0(-1);
    func_0022fc88(-1);
    D_00646A00 = a2;
    D_00646A04 = a3;
    D_00646A28 = 1;
    D_00647644 = 0;
    func_0011d768(16);
    func_0020bb90(544, -32);
    func_0020bda8(16);
    switch (mode) {
    case 0:
        D_00646A08 = p;
        D_00646A0C = p + 1;
        D_00646A10 = func_001f31a8(D_003F78B0, 6);
        break;
    case 1:
        D_00646A10 = func_001f31a8(D_003F79E0, 6);
        break;
    case 2:
        D_00646A08 = p;
        D_00646A0C = p + 1;
        D_00647640 = func_001eeb20();
        D_00646A10 = func_001f31a8(D_003F7A10, 6);
        break;
    case 3:
        D_00647640 = func_001eeb20();
        D_00646A10 = func_001f31a8(D_003F7A40, 6);
        break;
    }
    func_0011ef10(0x2BF84, func_002316f8);
}

extern s32 D_00425CD0[];
extern s32 D_00425C08[];
extern s32 D_00647FB0, D_00647FB4, D_00647FB8, D_00647FBC, D_00647FC0, D_00647FC4, D_00647FC8;
extern s32 D_00647FD4, D_00647FD8;
extern s32 D_00425C10, D_00425C14, D_00425C18, D_00425C20;
#include "data/pieces/D_00425C1C.h"
extern s32 D_006477A8;
extern s32 D_00647FE8[];
#include "data/pieces/D_00425C28.h"
#include "data/pieces/D_00425C48.h"
#include "data/pieces/D_00425C68.h"
#include "data/pieces/D_00425C88.h"
s32 func_00270e40(s32);
s32 func_002716d8(s32, s32, s32 *, s32 *, s32 *);
s32 func_002715a0(s32, s32, s32 *);

void func_00233ac8(void) {
    s32 i, j;
    s32 *p, *q;
    for (i = 0; i < 2; i++) {
        D_00425CD0[i] = 1;
        D_00425C08[i] = func_00270e40(i);
    }
    D_00647FB0 = 0;
    D_00647FB4 = 0;
    D_00647FB8 = 0;
    D_00647FBC = 0;
    D_00647FC0 = 1;
    D_00647FC4 = 1;
    D_00425C10 = 0;
    D_00425C14 = 0;
    D_006477A8 = 0;
    D_00647FD4 = 300;
    D_00647FD8 = 300;
    for (i = 0; i < 14; i++) D_00647FE8[i] = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            (*(s32 (*)[2][4])&D_00425C28)[i][j] = 3;
            D_00425C48[i][j] = 0;
            D_00425C68[i][j] = 0;
            D_00425C88[i][j] = 0;
        }
    }
    q = &D_00647FC8;
    p = D_00425C48[-2];
    for (i = 0; i < 2; p += 4) {
        func_002716d8(i++, 0, &D_00425C18, &D_00425C1C, &D_00425C20);
        func_002715a0(0, 0, q);
        switch (*q) {
        case 0: *p = 0; break;
        case -1: *p = 1; break;
        case -2: *p = 2; break;
        default: *p = 3; break;
        }
    }
}

extern s32 D_00647FF4;
extern s32 D_00647FB4, D_00647FB0, D_00647FC4, D_00647FC8, D_00647FD4, D_00647FD8, D_00647FF4;
extern s32 D_00425C10, D_00425C14, D_00425CA8, D_00425CAC;
extern void (*D_00648034)(s32);
extern s32 D_00648020;
s32 func_002718d0(s32, s32, s32, s32, s32, s32);

s32 func_002715a0(s32, s32, s32 *);

s32 func_002353a8(void) {
    s32 *pc = &D_00647FB4;
    s32 v, r;
    switch (*pc) {
    case 0:
        r = func_002718d0(D_00425C10, D_00425C14, D_00648020, 0, D_00425CAC, D_00425CA8);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        v = D_00647FC8;
        if (v >= 0) {
            D_00425CAC = v;
            D_00647FF4 = 0;
        } else if (v == -2) {
            D_00425CAC = -1;
            D_00647FF4 = 2;
        } else if (v == -4) {
            D_00425CAC = -1;
            D_00647FF4 = 3;
        } else {
            D_00425CAC = -1;
            D_00647FF4 = 4;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}

extern s32 D_00647FCC, D_00647FD0, D_00647FF8;
s32 func_00271c00(s32, s32);

void func_00235520(void) {
    s32 *pc = &D_00647FB4;
    s32 n;
    switch (*pc) {
    case 0:
        func_00271c00(D_00425C10, D_00425C14);
        (*pc)++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        if (D_00647FC8 != 0) {
            n = D_00647FCC;
            if (n != 0) {
                D_00647FCC = n - 1;
                D_00647FD0 = 60;
                *pc = 3;
                break;
            }
            D_00647FF8 = 1;
        } else {
            D_00647FF8 = 0;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    case 3:
        if (D_00647FD0 != 0) D_00647FD0--;
        else *pc = 0;
        break;
    }
}

extern s32 D_00647FFC;
s32 func_002721e8(s32, s32);
void func_00235688(void) {
    s32 *pc = &D_00647FB4;
    s32 n;
    switch (*pc) {
    case 0:
        func_002721e8(D_00425C10, D_00425C14);
        (*pc)++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        if (D_00647FC8 != 0) {
            n = D_00647FCC;
            if (n != 0) {
                D_00647FCC = n - 1;
                D_00647FD0 = 60;
                *pc = 3;
                break;
            }
            D_00647FFC = 1;
        } else {
            D_00647FFC = 0;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    case 3:
        if (D_00647FD0 != 0) D_00647FD0--;
        else *pc = 0;
        break;
    }
}

extern s32 D_00648000;
extern s32 D_00425CB0;
s32 func_00271ab0(s32, s32, s32, s32 *);

s32 func_002357f0(void) {
    s32 *pc = &D_00647FB4;
    s32 r;
    switch (*pc) {
    case 0:
        r = func_00271ab0(D_00425C10, D_00425C14, D_00648020, &D_00425CB0);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        switch (D_00647FC8) {
        case 0:
            D_00648000 = 0;
            break;
        case -2:
            D_00648000 = 1;
            break;
        case -4:
            D_00648000 = 2;
            break;
        default:
            D_00648000 = 3;
            break;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}


extern s32 D_00648004;
s32 func_00271038(s32, s32, s32);

s32 func_00235950(void) {
    s32 *pc = &D_00647FB4;
    s32 r;
    switch (*pc) {
    case 0:
        r = func_00271038(D_00425C10, D_00425C14, D_00648020);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        switch (D_00647FC8) {
        case 0:
            D_00648004 = 0;
            break;
        case -2:
            D_00648004 = 1;
            break;
        case -3:
            D_00648004 = 2;
            break;
        case -4:
            D_00648004 = 3;
            break;
        default:
            D_00648004 = 4;
            break;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}


extern s32 D_00648018;
extern s32 D_00648024;
s32 func_00272080(s32, s32, s32, s32);

s32 func_00236450(void) {
    s32 *pc = &D_00647FB4;
    s32 r, v;
    switch (*pc) {
    case 0:
        r = func_00272080(D_00425C10, D_00425C14, D_00648020, D_00648024);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        v = D_00647FC8;
        if (v == 0) {
            D_00648018 = 0;
        } else if (v == -2) {
            D_00648018 = 1;
        } else if (v == -4) {
            D_00648018 = 2;
        } else {
            D_00648018 = 3;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}

#include "platform/math.h"
#include "data/bss_0064.h"
typedef f32 MTX[4][4] __attribute__((aligned(16)));
typedef f32 VEC[4] __attribute__((aligned(16)));
typedef struct {
    MTX m0;
    MTX m40;
    MTX m80;
    MTX mc0;
    u8 p100[0x40];
    f32 px, py, pz, pw;
    f32 tx, ty, tz, tw;
    VEC v160;
    VEC v170;
    f32 rx, ry, rz, rw;
    VEC v190;
    u8 p1a0[0x40];
    s32 x1e0;
    f32 dist;
} Cam;
#include "data/pieces/D_00425F70.h"
#include "data/pieces/D_00425CE0.h"
f32 atan2f(f32, f32);
void func_00236d48(void *, void *, void *);
void func_002672f8(void *, void *, void *);
void func_00267768(void *, void *, f32);
void func_00267810(void *, void *, f32);
void func_00267930(void *, void *, void *, void *);
void sceVu0UnitMatrix(void *);
void sceVu0MulMatrix(void *, void *, void *);
void func_002673b8(void *, void *);

#define C ((Cam *)D_00425F70)
void func_00236a58(void) {
    MTX m;
    VEC v;
    VEC a;
    VEC b;
    f32 dx, dy, dz;
    if (C->x1e0 == 0) {
        dx = C->tx - C->px;
        dz = C->tz - C->pz;
        dy = C->ty - C->py;
        C->rz = 0;
        C->rx = atan2f(-dy, PlatSqrtf(dx * dx + dz * dz));
        C->ry = atan2f(dx, dz);
    } else {
        func_00236d48(m, D_00425CE0, &C->rx);
        v[0] = 0;
        v[1] = 0;
        v[2] = C->dist;
        v[3] = 1.0f;
        func_002672f8(v, m, v);
        C->px = C->tx + v[0];
        dx = C->tx - C->px;
        C->py = C->ty + v[1];
        dy = C->ty - C->py;
        C->pz = C->tz + v[2];
        dz = C->tz - C->pz;
    }
    func_00267768(m, D_00425CE0, C->rx);
    func_00267810(m, m, C->ry);
    func_002672f8(a, m, C->v160);
    func_002672f8(b, m, C->v170);
    func_00267930(C->m80, &C->px, a, b);
    sceVu0UnitMatrix(C->mc0);
    func_00236d48(C->mc0, C->mc0, &C->rx);
    sceVu0MulMatrix(C->m0, C->m40, C->m80);
    C->v190[0] = dx;
    C->v190[1] = dy;
    C->v190[2] = dz;
    C->v190[3] = 1.0f;
    func_002673b8(C->v190, C->v190);
}
#undef C


void func_002370c8(u64 *p) {
    p[2] = 0xF000000000000001ULL;
    p[3] = 0xEEEEEEEEEEEEEEEEULL;
    p[4] = 0x800D0ULL;
    p[5] = 0x4CULL;
    p[6] = 0x31000070ULL;
    p[7] = 0x4EULL;
    p[8] = 0x740000007000ULL;
    p[9] = 0x18ULL;
    p[10] = 0x17F000001FF0000ULL;
    p[11] = 0x40ULL;
    p[12] = 0x50003ULL;
    p[13] = 0x47ULL;
    p[14] = 0x8000000044ULL;
    p[15] = 0x42ULL;
    p[16] = 0;
    p[17] = 0x4AULL;
    p[18] = 0x20000045DD308002ULL;
    p[19] = 6;
    p[20] = 0x60ULL;
    p[21] = 0x14ULL;
    p[22] = 0x2000000001300000ULL;
    p[23] = 0x16ULL;
    p[24] = 0;
    p[25] = 0x34ULL;
    p[26] = 0;
    p[27] = 0x36ULL;
    p[28] = 0;
    p[29] = 8;
    p[30] = 1;
    p[31] = 0x1AULL;
    p[32] = 1;
    p[33] = 0x46ULL;
    p[34] = 0x4000000000008001ULL;
    p[35] = 0xEEEEEEEEEEEEEEEEULL;
    p[36] = 0;
    p[37] = 0x45ULL;
    p[38] = -4;
    p[39] = 0x44ULL;
    p[40] = 0;
    p[41] = 0x49ULL;
    p[42] = 0x8000000080ULL;
    p[43] = 0x3BULL;
}

extern u64 D_006480D0[];
void func_00237018(void *, s32, s32);

void func_00237318(void) {
    D_006480D0[2] = 0xF000000000000001ULL;
    D_006480D0[3] = 0xEEEEEEEEEEEEEEEEULL;
    D_006480D0[4] = 0x800D0ULL;
    D_006480D0[5] = 0x4CULL;
    D_006480D0[6] = 0x31000070ULL;
    D_006480D0[7] = 0x4EULL;
    D_006480D0[8] = 0x740000007000ULL;
    D_006480D0[9] = 0x18ULL;
    D_006480D0[10] = 0x17F000001FF0000ULL;
    D_006480D0[11] = 0x40ULL;
    D_006480D0[12] = 0x5000DULL;
    D_006480D0[13] = 0x47ULL;
    D_006480D0[14] = 0x44ULL;
    D_006480D0[15] = 0x42ULL;
    D_006480D0[16] = 0;
    D_006480D0[17] = 0x4AULL;
    D_006480D0[18] = 0x20000045DD308002ULL;
    D_006480D0[19] = 6;
    D_006480D0[20] = 0x60ULL;
    D_006480D0[21] = 0x14ULL;
    D_006480D0[22] = 0x2000000001300000ULL;
    D_006480D0[23] = 0x16ULL;
    D_006480D0[24] = 0;
    D_006480D0[25] = 0x34ULL;
    D_006480D0[26] = 0;
    D_006480D0[27] = 0x36ULL;
    D_006480D0[28] = 5;
    D_006480D0[29] = 8;
    D_006480D0[30] = 1;
    D_006480D0[31] = 0x1AULL;
    D_006480D0[32] = 1;
    D_006480D0[33] = 0x46ULL;
    D_006480D0[34] = 0x4000000000008001ULL;
    D_006480D0[35] = 0xEEEEEEEEEEEEEEEEULL;
    D_006480D0[36] = 0;
    D_006480D0[37] = 0x45ULL;
    D_006480D0[38] = -4;
    D_006480D0[39] = 0x44ULL;
    D_006480D0[40] = 0;
    D_006480D0[41] = 0x49ULL;
    D_006480D0[42] = 0x8000000080ULL;
    D_006480D0[43] = 0x3BULL;
    func_00237018(D_006480D0, 22, 1);
}

/* needs make: uses rodata */
typedef int u128 __attribute__((mode(TI)));
extern u128 D_003F8380[];
extern u128 D_003F8F80[];
extern u128 D_003F9F80[];
extern u128 D_003FA380[];
extern u128 D_003FA780[];
extern u128 D_0040E780[];
extern u128 D_0040EB80[];

static inline void clr(u128 *p, s32 n) { for (; n > 0; n--) *p++ = 0; }

s32 func_00232ad0(s32 a) {

    switch (a) {
    case -1:
        clr(D_003F8380, 5824);
        return 0;
    case 0:
        clr(D_003F8380, 192);
        return 0;
    case 1:
        clr(D_003F8F80, 256);
        return 0;
    case 2:
        clr(D_003F9F80, 64);
        return 0;
    case 3:
        clr(D_003FA380, 64);
        return 0;
    case 4:
        clr(D_003FA780, 5120);
        return 0;
    case 5:
        clr(D_0040E780, 64);
        return 0;
    case 6:
        clr(D_0040EB80, 64);
        return 0;
    }
    return -1;
}
extern s32 D_00647FB4, D_00647FB0, D_00647FC4, D_00647FC8, D_00647FD4, D_00647FD8, D_00647FF0;
extern s32 D_00425C10, D_00425C14, D_00425CA8, D_00425CAC;
extern void (*D_00648034)(s32);
s32 func_002718d0(s32, s32, s32, s32, s32, s32);
s32 func_002715a0(s32, s32, s32 *);

s32 func_00235228(void) {
    s32 *pc = &D_00647FB4;
    s32 v, r;
    switch (*pc) {
    case 0:
        r = func_002718d0(D_00425C10, D_00425C14, (s32)"*", 0, D_00425CAC, D_00425CA8);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        v = D_00647FC8;
        if (v >= 0) {
            D_00425CAC = v;
            D_00647FF0 = 0;
        } else if (v == -2) {
            D_00425CAC = -1;
            D_00647FF0 = 1;
        } else if (v == -4) {
            D_00425CAC = -1;
            D_00647FF0 = 2;
        } else {
            D_00425CAC = -1;
            D_00647FF0 = 3;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}
extern s32 D_00648020;

extern s32 D_0064800C;
s32 func_00271cc8(s32, s32, s32);

s32 func_00235d70(void) {
    s32 *pc = &D_00647FB4;
    s32 r;
    switch (*pc) {
    case 0:
        r = func_00271cc8(D_00425C10, D_00425C14, D_00648020);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        switch (D_00647FC8) {
        case 0:
            D_0064800C = 0;
            break;
        case -2:
            D_0064800C = 1;
            break;
        case -4:
            D_0064800C = 2;
            break;
        case -5:
            D_0064800C = 3;
            break;
        case -6:
            D_0064800C = 4;
            break;
        default:
            D_0064800C = 5;
            break;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}
#include "data/data_003F.h"
#include "data/data_0042.h"
#include "data/pieces/D_003F7A68.h"
#include "data/pieces/D_00425C10.h"
#include "data/pieces/D_00425C14.h"
#include "data/pieces/D_00425CA8.h"
#include "data/pieces/D_00425CAC.h"
