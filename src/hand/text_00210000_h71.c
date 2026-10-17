#include "common.h"
typedef struct {
    u8 pad[0xA0];
    f32 xa0;
    u8 pada4[0xCA - 0xA4];
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
typedef struct { u8 pad[0x20]; u8 x20[1]; } S34B8;
typedef struct { u8 pad[1166]; u8 x48e[1]; } S4BE8;
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
