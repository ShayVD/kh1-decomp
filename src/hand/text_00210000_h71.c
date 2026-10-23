#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"
typedef struct ObjT {
    u8 pad[0x24];
    struct ObjT *x24; /* holds a byte id; pointer type matches the original aliasing */
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
} Obj;
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003F2C40.h"
typedef E20_3F2C40 E20;
extern s32 D_00642C94;
extern s32 D_00642C9C;
extern u16 D_00642CC8; /* src/data/bss_0064.c: s32 D_00642CC8 */
extern s32 D_00642CD0;
extern u16 D_00642CD4; /* src/data/bss_0064.c: s32 D_00642CD4 */
extern u8 D_003F4460[];
extern u8 D_003F4430[];
extern s32 D_003F44C8[];
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
void func_001fd858(void *);
void func_0020bd18(void *, s32);
s32 func_001fd518(void *);
s32 func_001fe570(void *);
void func_001f3d58(void *, s32);
Obj *func_001f4468(void *);
Obj *func_001f31a8(u8 *, s32);
void func_001f3e48(Obj *, void *);
void func_001f3dc0(Obj *);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_0013c288(s32);
s32 func_00132f88(s32);
s32 func_001efbb8(s32);

void func_00216640(void *a) {
    Obj *o[2];
    Obj *p;
    s32 i, y, sel, s;
    s32 *pv;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
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
                    o[0]->xcc = o[0]->xce = D_00642CC8;
                    o[0]->xd2 = D_00642CD4 << 4;
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
typedef struct { s32 *p; s32 n; } PN;
#include "data/pieces/D_003F34B8.h"
typedef W606Mem_304be8 Rec74;
typedef Save_304be8 S4BE8;
extern s32 D_00642CCC;
extern s32 D_00642CD8;
extern PN D_003F40F8[];
extern s32 *D_003F41E8[];
extern s32 D_003F4200[][9];
void func_00170d60(s32, s32, s32);

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

extern s32 D_00642CF0[];
s32 D_00642D10 ALIGNED(16);
s32 D_00642D14 ALIGNED(4);
s32 func_0013c360(s32);

void func_00218020(s32 n) {
    Rec74 *e = &D_00304BE8->m[n];
    s32 i;
    D_00642CF0[0] = 0;
    D_00642CF0[1] = 1;
    D_00642CF0[2] = 2;
    D_00642D10 = 3;
    D_00642D14 = 0;
    for (i = 0; e->sub.name[i]; i++) D_00642D14++;
    if (D_00642D14 >= 37) {
        D_00642CF0[3] = 3;
        D_00642CF0[4] = 4;
        D_00642CF0[5] = 5;
        D_00642CF0[6] = 6;
        D_00642D10 += 4;
    } else if (D_00642D14 >= 25) {
        D_00642CF0[3] = 3;
        D_00642CF0[4] = 4;
        D_00642CF0[5] = 5;
        D_00642D10 += 3;
    } else if (D_00642D14 >= 13) {
        D_00642CF0[3] = 3;
        D_00642CF0[4] = 4;
        D_00642D10 += 2;
    } else if (D_00642D14 > 0) {
        D_00642CF0[3] = 3;
        D_00642D10 += 1;
    }
    if (n == 0) {
        for (i = 0; i < 7; i++) {
            if (func_0013c360(i) == 1) {
                D_00642CF0[D_00642D10++] = 7;
                break;
            }
        }
    }
}

#include "data/pieces/D_003F34C4.h"
typedef N_3f34c4 Obj2;
extern s32 D_00642CE8;
extern s32 D_00642D18;
#include "data/pieces/D_003E3D68.h"
void func_001fdfd0(Obj2 *);
s32 func_001ee5f0(s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);

void func_00218dd0(Obj2 *a) {
    Obj2 *o;
    s32 v, k, s, y;
    u32 i;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758((void *)D_00642CE8);
            func_0011d768(3);
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            v = func_001fd518(a);
            D_00642D18 = v;
            if ((o = a->x10)) {
                u8 k8 = D_00304BE8->x48e[v];
                o->x24 = k8;
                if ((o = o->x10)) {
                    func_00218020(D_00304BE8->x48e[v]);
                    o->xd8 = D_00642D10;
                    func_001fdfd0(o);
                    o->x24 = k8;
                }
            }
        }
    }
    s = func_001fd518(a);
    y = 0;
    for (i = 0; i < D_003E3D68; i++) {
        k = i == s ? 11 : 0;
        func_00207870(a, k, 2, 0, y, 122, func_001ee5f0(D_00304BE8->x48e[i]));
        y += 28;
    }
}

extern u8 D_003F4730[];
extern u8 D_003F4700[];
extern u8 D_003F46D0[];
void func_001f3e90(void *, Obj *);
void func_001f3e20(Obj *, void *);

void func_00218f88(void *a) {
    Obj *o[3];
    if ((o[0] = func_001f31a8(D_003F4730, 6))) {
        u32 *n;
        s32 *v;
        func_001f3e90(a, o[0]);
        func_001f3e20(o[0], a);
        n = &D_003E3D68;
        v = &D_00642D18;
/*P*/
        o[0]->xba = *n * 448 - 32;
        o[0]->xce = *n;
        o[0]->xcc = *n;
        o[0]->xd2 = *v << 4;
/*Q*/
        if ((o[1] = func_001f31a8(D_003F4700, 6))) {
            S4BE8 **b;
            func_001f3e90(o[0], o[1]);
            func_001f3e20(o[1], o[0]);
            b = &D_00304BE8;
            o[1]->x24 = (Obj *)(u32)(*b)->x48e[*v];
            if ((o[2] = func_001f31a8(D_003F46D0, 6))) {
                func_001f3e90(o[1], o[2]);
                func_001f3e20(o[2], o[1]);
                o[2]->x24 = (Obj *)(u32)(*b)->x48e[*v];
                o[2]->xd8 = 8;
                func_001f3dc0(o[0]);
            }
        }
    }
    D_00642CE8 = (s32)a;
}

extern s32 D_00642D28;
extern s32 D_003F4790[];
s32 func_001fd538(void *);
void func_00206690(void *, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);

void func_00219a88(Obj2 *a) {
    Obj2 *o;
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

extern s32 D_003F4798[];

void func_00219c18(Obj2 *a) {
    Obj2 *o;
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

extern s32 D_003F47A0[];

void func_00219da8(Obj2 *a) {
    Obj2 *o;
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
typedef f32 Mtx[4][4];
#include "data/pieces/D_00425F70.h"
typedef Cam_425f70 Cam;
typedef struct { u8 pad[8]; s32 x8; } P8;
typedef struct {
    s32 x0;
    u8 pad4[4];
    s32 x8;
    s32 xc;
    s32 x10;
    s32 x14;
    u8 x18[4];
    s32 x1c;
    u8 pad20[8];
    s32 x28;
    s32 x2c;
    s32 x30;
    s8 x34[4];
    s8 x38[3];
    s8 x3b;
    s32 x3c;
    s8 x40[6];
    s8 x46;
    s8 x47;
    s32 x48;
    u8 pad4c[4];
    s32 x50;
    u8 pad54[0x60 - 0x54];
    u64 x60;
    u64 x68;
    f32 x70;
    s32 x74;
    s32 x78;
    u8 pad7c[0xC0 - 0x7C];
    s32 xc0;
    u8 padc4[4];
    P8 *xc8;
    s32 xcc;
} G20;
extern G20 D_00643020;
extern s32 D_00643104;
#include "data/pieces/D_00425CE0.h"
extern f32 D_003F59B0;
void func_0021b418(void);
void func_00131d68(void *, G20 *);
void func_00162070(s32, s32 *, s32 *, s32 *);
void func_001321a0(void *, s32);
void func_00132220(s32, s32);
void func_00167ac0(s32, s32, s32);
s32 func_001301d8(void *, s32, s32, s32);
void func_001655e0(void *, s32, s32, f32);
s32 func_0021ade8(void *);
P8 *func_00147b08(s32, void *, s32);
void func_002675a8(s32, void *);

void func_0021b250(void *a) {
    s32 r;
    P8 *p;
    Cam *c;
    func_0021b418();
    D_00643020.xcc = 1;
    func_00131d68(a, &D_00643020);
    func_00162070(D_00643020.x0, &D_00643020.x10, &D_00643020.x1c, &D_00643020.x14);
    func_001321a0(D_00643020.x18, D_00643020.x8);
    func_00132220(D_00643020.x14, D_00643020.x8);
    func_00167ac0(D_00643020.x14, 0, 63);
    D_00643020.x70 = 0;
    D_00643020.x50 = D_00643104;
    D_00643020.x30 = -1;
    D_00643020.x3b = -1;
    D_00643020.x47 = -1;
    D_00643020.x60 = 0x31000070;
    D_00643020.x68 = 0x000800D0;
    D_00643020.x28 = 0;
    D_00643020.x2c = 0;
    D_00643020.x38[0] = -128;
    D_00643020.x38[1] = -128;
    D_00643020.x38[2] = -128;
    D_00643020.x48 = 0;
    D_00643020.x34[0] = -128;
    D_00643020.x34[1] = -128;
    D_00643020.x34[2] = -128;
    D_00643020.x34[3] = -128;
    D_00643020.x40[0] = -128;
    D_00643020.x40[1] = -128;
    D_00643020.x40[2] = -128;
    D_00643020.x40[3] = -128;
    D_00643020.x40[4] = -128;
    D_00643020.x40[5] = -128;
    D_00643020.x46 = -128;
    D_00643020.x3c = 0;
    r = func_001301d8(D_00643020.x18, 0, 0, 0);
    func_001655e0(D_00425CE0, D_00643020.x14, r, D_00643020.x70);
    if (func_0021ade8(a)) {
        p = func_00147b08(D_00643020.xc, a, D_00643020.x14);
        c = D_00425F70;

        c->v1a0[0] = D_003F59B0;
        c->v1a0[3] = 1.0f;
        c->v1a0[1] = D_003F59B0;
        c->v1a0[2] = D_003F59B0;
        D_00643020.xc8 = p;

        func_002675a8(p->x8, c->v1a0);
    } else {
        D_00643020.xc8 = 0;
    }
    D_00643020.x78 = -1;
    D_00643020.x74 = 0;
    D_00643020.xc0 = 0;
}
void func_0021b860(void *, s32, s32, s32, s32, s32);

void func_0021c5e0(void *a, s32 x, s32 y) {
    s32 i, yy, xb, xc;
    xb = x + 52;
    xc = x + 195;
    func_0021b860(a, x, y, 0, 0, 6);
    func_0021b860(a, xb, y, 143, 0, 7);
    func_0021b860(a, xc, y, 0, 0, 8);
    yy = y + 51;
    for (i = 0; i < 12; i++) {
        func_0021b860(a, x, yy, 0, 0, 9);
        func_0021b860(a, xb, yy, 143, 0, 10);
        func_0021b860(a, xc, yy, 0, 0, 11);
        yy += 16;
    }
    func_0021b860(a, x, yy, 0, 0, 12);
    func_0021b860(a, xb, yy, 143, 0, 13);
    func_0021b860(a, xc, yy, 0, 0, 14);
    xb = x - 16;
    yy = y + 7;
    for (i = 0; i < 18; i++) {
        func_0021b860(a, xb, yy, 0, 0, 31);
        yy += 16;
    }
}

void func_0021c780(void *a, s32 x, s32 y) {
    s32 i, yy, xb, xc, y20;
    xb = x + 52;
    yy = y + 20;
    y20 = yy;
    xc = x + 198;
    func_0021b860(a, x, y, 0, 0, 15);
    func_0021b860(a, xb, y, 146, 0, 16);
    func_0021b860(a, xc, y, 0, 0, 17);
    for (i = 0; i < 16; i++) {
        func_0021b860(a, x, yy, 0, 0, 18);
        func_0021b860(a, xb, yy, 146, 0, 19);
        func_0021b860(a, xc, yy, 0, 0, 20);
        yy += 16;
    }
    func_0021b860(a, x, yy, 0, 0, 21);
    func_0021b860(a, xb, yy, 146, 0, 22);
    xb = x + 241;
    func_0021b860(a, xc, yy, 0, 0, 23);
    yy = y20;
    func_0021b860(a, xb, y, 0, 0, 0);
    for (i = 0; i < 16; i++) {
        func_0021b860(a, xb, yy, 0, 0, 4);
        yy += 16;
    }
    func_0021b860(a, xb, yy, 0, 0, 2);
    xb = x + 225;
    yy = y + 7;
    for (i = 0; i < 18; i++) {
        func_0021b860(a, xb, yy, 0, 0, 31);
        yy += 16;
    }
}

void func_0021c9a0(void *a, s32 x, s32 y) {
    s32 i, yy, xb, y20;
    yy = y + 20;
    y20 = yy;
    func_0021b860(a, x, y, 0, 0, 1);
    for (i = 0; i < 16; i++) {
        func_0021b860(a, x, yy, 0, 0, 5);
        yy += 16;
    }
    func_0021b860(a, x, yy, 0, 0, 3);
    yy = y20;
    xb = x + 241;
    func_0021b860(a, xb, y, 0, 0, 0);
    for (i = 0; i < 16; i++) {
        func_0021b860(a, xb, yy, 0, 0, 4);
        yy += 16;
    }
    func_0021b860(a, xb, yy, 0, 0, 2);
    xb = x + 225;
    yy = y + 7;
    for (i = 0; i < 18; i++) {
        func_0021b860(a, xb, yy, 0, 0, 31);
        yy += 16;
    }
}

typedef struct { u8 pad[0xC]; void *xc; } Ob3;
extern s32 D_00642E94;
extern s32 D_00643010;
extern s32 D_00643014;
extern u8 D_00642E98[];
extern s32 D_00642EA0;
extern u8 *D_003F59E8[];
extern s32 D_003F5A18[];
extern void (*D_003F5A00[])(Obj *);
extern u16 D_003E90AC;
extern s32 D_003F59D0[];
extern s32 D_003F5C30[];
void func_0021b820(void);
void func_00207560(void *, s32, s32);
s32 func_00207320(s32);
void func_00207428(void *, s32, s32);
void func_0021c4f8(void *);

void func_0021cd68(Ob3 *a) {
    Obj *o[2];
    s32 i, y, k, v;
    s32 *p;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a->xc);
            func_0011d768(3);
            D_00642E94 = 1;
        } else {
            func_001fd858(a);
            v = func_001fd518(a);
            D_00643010 = v;
            p = &D_00643014;
            *p = D_00642E98[v];
            if (func_001fe570(a)) {
                func_001f3758(a->xc);
                if ((o[0] = func_001f31a8(D_003F59E8[*p], D_003F5A18[*p]))) {
                    func_001f3e48(o[0], a->xc);
                    D_003F5A00[*p](o[0]);
                    o[0]->xa0 = D_003E90AC;
                }
            }
        }
    }
    func_0021b820();
    func_0021c5e0(a, 257, 72);
    y = 108;
    for (i = 0; i < D_00642EA0; i++) {
        k = D_00642E98[i];
        func_001f9438(a, 0, 330, y, D_003F59D0[k], 15, 0x80B4DCF5);
        if (D_003F5C30[k]) func_00207560(a, 450, y - 2);
        if (!func_00207320(k)) func_00207428(a, 435, y + 7);
        y += 28;
    }
    do { func_0021c4f8(a); } while (0);
}

extern s32 D_00643100;
extern u8 D_003F5A60[];
extern u8 D_003F5A30[];
s32 func_001f44a0(u8 *);
void func_001f37c0(Obj2 *, s32);
void func_0020d1d8(Obj *);
void func_0020bda8(s32);

void func_0021d028(void *a) {
    Obj *o[2];
    if (!func_001f42b8(a)) return;
    switch (D_00642E94) {
    case 0:
        if (!D_00643100) return;
        if (!(o[0] = func_001f31a8(D_003F5A60, 50))) return;
        func_001f3e48(o[0], a);
        if (!(o[1] = func_001f31a8(D_003F5A30, 6))) return;
        func_001f3e48(o[1], o[0]);
        {
            s32 *n = &D_00642EA0;
            s32 *c = &D_00643010;
            o[1]->xcc = *n;
            if (*c >= *n) *c = *n - 1;
            o[1]->xd2 = *c << 4;
        }
        break;
    case 1:
        if (func_001f44a0(D_003F5A60)) return;
        func_001f37c0(D_003F34C4->x10, 50);
        func_001f3d58(D_003F34C4->x10->x10, 2);
        func_001f3d58(D_003F34C4->x10->x10->x10, 2);
        func_0020d1d8(func_001f4468(a));
        func_0020bda8(16);
        break;
    }
}

typedef struct { u8 pad[0x24]; f32 x24; f32 x28; s32 x2c; s32 x30; } Ed;
void func_001f36b8(void *);
f32 func_001edcd8(f32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
void func_0021b1b0(f32, f32, s32, s32);
void func_0021af38(void *);

void func_0021e670(Ed *a) {
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f36b8(a);
            func_0011d768(3);
        } else {
            if (D_00425BC8->x4 & 0x100000) {
                a->x24 -= 0.02f;
                if (a->x24 < 0.1f) a->x24 = 0.1f;
            } else if (D_00425BC8->x4 & 0x400000) {
                a->x24 += 0.02f;
                if (10.0f < a->x24) a->x24 = 10.0f;
            }
            if (D_00425BC8->x4 & 0x800000) {
                a->x28 += 0.05235987755982988f;
                a->x28 = func_001edcd8(a->x28);
            } else if (D_00425BC8->x4 & 0x200000) {
                a->x28 -= 0.05235987755982988f;
                a->x28 = func_001edcd8(a->x28);
            }
            if ((s32)D_00425BC8->x4 < 0) {
                a->x2c -= 4;
                if (a->x2c < 0) a->x2c = 0;
            } else if (D_00425BC8->x4 & 0x20000000) {
                a->x2c += 4;
                if (a->x2c > 512) a->x2c = 512;
            }
            if (D_00425BC8->x4 & 0x10000000) {
                a->x30 -= 4;
                if (a->x30 < 0) a->x30 = 0;
            } else if (D_00425BC8->x4 & 0x40000000) {
                a->x30 += 4;
                if (a->x30 > 384) a->x30 = 384;
            }
        }
    }
    func_002053e8(a, 17, 73, 479, 295, 0x40357966);
    func_0021b1b0(a->x24, a->x28, a->x2c, a->x30);
    func_0021af38(a);
}

extern Obj2 *D_00643110; /* src/data/bss_0064.c: s32 D_00643110 */
extern s32 D_0064324C;
extern s32 D_00643200[];
extern s32 D_00643118;
extern s32 D_003F5F18[];
extern s32 D_00643278[];
s32 func_001fe5a0(void *);
void func_0021f410(void *);
s32 func_0021b800(s32);
s32 func_00207088(s32);

void func_0021f5f8(void *a) {
    s32 i, y;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00643110);
            func_0011d768(3);
        } else {
            s32 *p;
            func_001fd858(a);
            i = func_001fd518(a);
            p = &D_0064324C;
            *p = i;
            if (func_001fe5a0(a)) {
                if (D_00643200[*p]) {
                    func_001f3758(D_00643110->x10);
                    func_0021f410(a);
                    D_00643118 = 0;
                    func_0011d768(2);
                } else {
                    func_0011d768(3);
                }
            }
        }
    }
    y = 116;
    for (i = 0; i < 3; i++) {
        func_001f94f0(a, 0, 322, y, func_0021b800(D_003F5F18[i]), 15, D_00643200[i] ? 0x80461E00 : 0x40461E00);
        if (D_00643278[i]) func_00207560(a, 456, y - 2);
        if (!func_00207088(i)) func_00207428(a, 450, y + 10);
        y += 60;
    }
    func_0021b820();
    func_0021c4f8(a);
}

extern s32 D_00643200[];
extern u8 D_00643128[];
extern u8 D_00643160[];
extern u8 D_006431B0[];
extern u8 D_00643210[];
s32 func_0021dc08(s32);
s32 func_00207180(s32);
void func_00207000(s32);
void func_00207048(s32);
s32 func_00207088(s32);
void func_002072e0(s32);
void func_00207298(s32);

void func_0021f968(void) {
    s32 i;
    for (i = D_00643200[0] - 1; i >= 0; i--) {
        if (!func_00207180(func_0021dc08(D_00643128[i]))) {
            func_00207000(0);
            goto l1;
        }
    }
    func_00207048(0);
l1:
    for (i = D_00643200[1] - 1; i >= 0; i--) {
        if (!func_00207180(func_0021dc08(D_00643160[i]))) {
            func_00207000(1);
            goto l2;
        }
    }
    func_00207048(1);
l2:
    for (i = D_00643200[2] - 1; i >= 0; i--) {
        if (!func_00207180(func_0021dc08(D_006431B0[i])) && D_00643210[i]) {
            func_00207000(2);
            goto l3;
        }
    }
    func_00207048(2);
l3:
    if (func_00207088(0) && func_00207088(1) && func_00207088(2)) {
        func_002072e0(2);
        return;
    }
    func_00207298(2);
}

extern s32 D_00643418;
extern u8 D_006433F8[];
#include "data/pieces/D_003F5FF0.h"
extern s32 D_003F6070[];
s32 func_001eb9a8(s32, s32);
s32 func_00206ee8(s32);

void func_0021fbb8(void) {
    s32 i, k;
    D_00643418 = 0;
    for (i = 0; i < 31; i++) {
        if (func_001eb9a8(D_003F5FF0[i], D_003F6070[i])) D_006433F8[D_00643418++] = i;
    }
    for (i = 0; i < D_00643418; i++) {
        if (!func_00206ee8(D_006433F8[i])) {
            func_00207298(0);
            goto next;
        }
    }
    func_002072e0(0);
next:
    D_003F5C30[0] = 0;
    for (k = 9, i = 30;; k--) {
        if (!func_001eb9a8(D_003F5FF0[i], D_003F6070[i])) return;
        while (i != 0) {
            i--;
            if (D_003F5FF0[i] != k) goto cont;
        }
        D_003F5C30[0] = 1;
        return;
    cont:;
    }
}

extern u8 D_003F6180[];
extern u8 D_003F6150[];
extern u8 D_003F6120[];
extern s32 D_00643420;
extern s32 D_0064341C;

void func_00220338(void *a) {
    Obj *o[3];
    if (!(o[0] = func_001f31a8(D_003F6180, 50))) return;
    func_001f3e48(o[0], a);
    if (!(o[1] = func_001f31a8(D_003F6150, 50))) return;
    func_001f3e48(o[1], o[0]);
    if (!(o[2] = func_001f31a8(D_003F6120, 50))) return;
    func_001f3e48(o[2], o[1]);
    if (D_00643420 * 4 > D_00643418 / 4 * 4) D_00643420 = 0;
    if (D_00643418 < D_00643420 * 4 + D_0064341C) D_0064341C = 0;
    o[2]->xca = D_00643418;
    o[2]->xd8 = (D_00643418 + 3) / 4;
    o[2]->xda = D_00643420 << 4;
    if (D_00643418 < 4 || D_00643420 == o[2]->xd8 - 1) o[2]->xcc = (D_00643418 - 1) % 4 + 1;
    else o[2]->xcc = 4;
    o[2]->xd2 = D_0064341C << 4;
}
s32 D_006435E8[0xa] ALIGNED(8);
s32 D_00643610[0xa] ALIGNED(16);
s32 D_00643638[0xa] ALIGNED(8);
extern s32 D_0064342C;
extern s32 D_00643430[];
#include "data/pieces/D_003F61E0.h"
s32 D_006435BC ALIGNED(4);
s32 D_006435C0[0xa] ALIGNED(16);
extern s32 D_003F5C3C;
s32 func_001eb318(s32);

void func_002205e0(void) {
    s32 i;
    for (i = 0; i < 9; i++) {
        D_006435E8[i] = 0;
        D_00643610[i] = 0;
        D_00643638[i] = 0;
    }
    D_0064342C = 0;
    for (i = 0; i < 99; i++) {
        if ((D_00643430[i] = func_001eb318(i))) {
            D_00643610[D_003F61E0[i / 3]]++;
            D_0064342C++;
        }
    }
    D_006435BC = 0;
    for (i = 0; i < 9; i++) {
        if (D_00643610[i]) {
            D_006435C0[D_006435BC] = i;
            D_006435BC++;
        }
    }
    for (i = 0; i < 33; i++) D_00643638[D_003F61E0[i]] += 3;
    for (i = 0; i < 9; i++) D_006435E8[i] = D_00643638[i] - D_00643610[i];
    D_003F5C3C = D_0064342C == 99;
}

#include "data/pieces/D_003E8E08.h"
void func_0021b820(void);
void func_0021c9a0(void *, s32, s32);
void func_0021cb00(void *, s32, s32, s32, s32);
s32 func_002207f0(s32);
s32 func_0021b800(s32);

void func_002208b8(void *a) {
    s32 i, y;
    y = 86;
    func_0021b820();
    func_0021c9a0(a, 16, 72);
    func_0021cb00(a, 32, 108, 9, 30);
    func_0021cb00(a, 280, 108, 9, 30);
    for (i = 0; i < D_006435BC; i++) {
        func_001f94f0(a, 0, 280, y, func_002207f0(D_006435C0[i]), 15, 0x80461E00);
        (*(s32 *)&D_003E8E08) = D_006435E8[D_006435C0[i]];
        func_001f94f0(a, 0, 465, y, func_0021b800(17), 15, 0x80461E00);
        y += 30;
    }
    if (D_006435BC < 9) {
        func_001f94f0(a, 0, 280, y, func_0021b800(80), 15, 0x80461E00);
        (*(s32 *)&D_003E8E08) = 99;
        for (i = 0; i < D_006435BC; i++) (*(s32 *)&D_003E8E08) -= D_00643638[D_006435C0[i]];
        func_001f94f0(a, 0, 465, y, func_0021b800(17), 15, 0x80461E00);
    }
}

typedef struct {
    u8 pad[0x24];
    s32 x24;
    u8 pad28[0x90 - 0x28];
    s32 x90;
    u8 pad94[0xB0 - 0x94];
    s32 xb0;
    s32 xb4;
    u8 padb8[0xD8 - 0xB8];
    s16 xd8;
    s16 xda;
} Ob4;
extern s32 D_00643424;
extern s32 D_003F3518;
s32 func_001fd668(void *);
void func_00203788(void *, s32, s32, s32, u32);
void func_0021cb00(void *, s32, s32, s32, s32);
s32 func_0021fd88(s32);
s32 func_001c2df0(s32, s32);
s32 func_0010edb0(s32, s32, s32, s32, s32, s32);

s32 func_0021fd90(Ob4 *a) {
    s32 x, y, k;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
        } else {
            u32 b = D_00425BC8->x10;
            s32 n;
            k = 0;
            n = a->xd8;
            if (b & 0x80000480) {
                if (a->xda > 0) {
                    a->xda -= 16;
                    k = 1;
                }
            } else if (b & 0x20000820) {
                s32 m = n - 1;
                if (a->xda < m * 16) {
                    a->xda += 16;
                    k = 1;
                }
            }
            if (k) func_0011d768(k);
            D_00643424 = func_001fd668(a);
        }
    }
    func_00203788(a, 372, 40, 486, 0x80C8C8C8);
    func_0021b820();
    func_0021c9a0(a, 16, 72);
    func_0021cb00(a, 32, 108, 9, 30);
    func_0021cb00(a, 280, 108, 9, 30);
    x = ((a->xb0 - 0x7000) >> 4) + 32;
    y = ((a->xb4 - 0x7400) >> 4) + 84;
    k = func_0021fd88(a->x24);
    return func_0010edb0(x, y, 256, D_00643424 * 2, a->x90, func_001c2df0(D_003F3518, k));
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_003F5FC0[];
extern u8 D_003F61B0[];
extern u8 D_003F6330[];
extern u8 D_003F6620[];
extern u8 D_003F6710[];
extern u8 D_003F6800[];
u8 *D_003F59E8[0x6] ALIGNED(8) = {
    (void *)D_003F61B0, (void *)D_003F6710, (void *)D_003F5FC0, (void *)D_003F6330,
    (void *)D_003F6800, (void *)D_003F6620,
};
void func_0021faf8();
void func_00220580();
void func_002210b0();
void func_00222b40();
void func_002234a8();
void func_00223938();
void (*D_003F5A00[0x6])(Obj *) ALIGNED(16) = {
    (void *)func_00220580, (void *)func_002234a8, (void *)func_0021faf8, (void *)func_002210b0,
    (void *)func_00223938, (void *)func_00222b40,
};
#include "data/data_003F.h"
#include "data/data_003E.h"
