#include "common.h"
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
typedef struct { u8 pad[8]; s32 x8; } Cfg;
typedef struct { u8 pad[16]; s32 x10; } E20;
extern Cfg *D_00425BC8;
extern s32 D_00642C94;
extern s32 D_00642C9C;
extern u16 D_00642CC8;
extern s32 D_00642CD0;
extern u16 D_00642CD4;
extern u8 D_003F4460[];
extern u8 D_003F4430[];
extern s32 D_003F44C8[];
extern E20 D_003F2C40[];
s32 func_001f42b8(void *);
void func_001f3758(void *);
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
        func_001f9438(a, 0, 86, y + 5, 51, 15, D_003F2C40[sel].x10);
        t = func_00132f88(func_0013c288(i));
        if (!t) t = func_001efbb8(212);
        func_001f94f0(a, 0, 96, y + 5, t, 15, D_003F2C40[sel].x10);
        y += 28;
    }
}
typedef struct { s32 *p; s32 n; } PN;
typedef struct { s32 x0; s32 x4; s32 x8; u8 padc[0x20 - 0xC]; u8 x20[1]; } S34B8;
typedef struct { u8 pad[0x44]; u8 name[116 - 0x44]; } Rec74;
typedef struct { Rec74 r[10]; u8 pad[6]; u8 x48e[1]; } S4BE8;
extern S4BE8 *D_00304BE8;
extern s32 D_00642CCC;
extern S34B8 *D_003F34B8;
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
    D_003F34B8->x20[k] = *(u8 *)&D_00642CD8;
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
extern s32 D_00642D10;
extern s32 D_00642D14;
s32 func_0013c360(s32);

void func_00218020(s32 n) {
    Rec74 *e = &D_00304BE8->r[n];
    s32 i;
    D_00642CF0[0] = 0;
    D_00642CF0[1] = 1;
    D_00642CF0[2] = 2;
    D_00642D10 = 3;
    D_00642D14 = 0;
    for (i = 0; e->name[i]; i++) D_00642D14++;
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

typedef struct Obj2 {
    u8 pad[0x10];
    struct Obj2 *x10;
    u8 pad14[0x24 - 0x14];
    s32 x24;
    u8 pad28[0xD8 - 0x28];
    s16 xd8;
} Obj2;
extern s32 D_00642CE8;
extern s32 D_00642D18;
extern u32 D_003E3D68;
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
            D_003F34B8->x0 = func_001fd538(a);
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
            D_003F34B8->x4 = func_001fd538(a);
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
            D_003F34B8->x8 = func_001fd538(a);
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
