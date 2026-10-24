/* The party models of the menus (docs/modules.md "Session 39"),
 * 0x00209d48-0x0020a8f0: func_00209d48 loads a model for each party member
 * (func_001ef8f8) into D_003F3530 and counts them in D_003F3870,
 * func_0020a248 sets one up (motion, colours, the bones from bone 52 on),
 * func_00209f70 sets the nine views D_00640E40 (one per member, four for the
 * models of D_00304BE8->x48e, one turning), func_00209e18 / func_0020a518 /
 * func_0020a758 animate and draw them, func_0020a1d8 frees them. */
#include "common.h"
#include "platform/vu.h"
#include "menu/partymdl.h"
#include "data/types/text_00200000_h70.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_00425CE0.h"

typedef struct { f32 m[4][4]; } __attribute__((aligned(16))) Mtx;
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) Vec4;
typedef struct { u8 pad[0x24]; f32 x24; u8 pad28[0x68]; s32 x90; } PartyView;   /* x90 the alpha */

extern PartyMdl D_003F3530[4];
extern s32 D_003F3870;
extern B64 D_003F3050[];
B64 D_00640E40[0x9] ALIGNED(64);
extern f32 D_002BBDFC;
extern f32 *D_003F31D0[];
extern f32 D_003F3150[];
extern f32 D_003F3178[];
extern u8 D_003F31E0[];
extern s32 D_002BC128;
extern s32 D_002BC130;

void *func_001ef8f8(s32);
void func_00122f20(void *, void *);
void func_00121e28(s32, void *);
void func_00121eb0(s32);
s32 func_001301d8(void *, s32, s32, s32);
void func_001321a0(void *, s32);
void func_00132220(void *, s32);
void func_00161de8(void *, void *, void *, s32);
void func_00162070(s32, void *, void *, void *);
void func_00162110(s32, s32);
s32 func_00162338(void *);
s32 func_00162348(void *, s32);
s32 func_00162368(void *, s32);
Mtx9 *func_001623e0(void *);
void func_001625c8(Mtx9 *, Mtx9 *);
void func_001655e0(void *, void *, f32, s32);
s32 func_00167698(s32);
void func_00167ac0(void *, s32, s32);
void func_00167d70(void *, f32);

#define K84 0.83999986946582794189453125f

void func_00209d48(void) {
    s32 i;
    void *p;
    D_003F3870 = 0;
    for (i = 0; i < 3; i++) {
        p = func_001ef8f8(i);
        if (p == 0) {
            D_003F3530[i].active = 0;
        } else {
            D_003F3530[i].active = 1;
            func_00122f20(p, &D_003F3530[i]);
            func_0020a248(i);
            D_003F3870++;
        }
    }
    D_003F3530[3].active = 0;
}

void func_00209e18(PartyView *p) {
    s32 i;
    s32 k = 0xea61;
    for (i = 0; i < D_003F3870; i++) {
        PartyMdl *e = &D_003F3530[i];
        s32 r = func_001301d8(e->x18, 1, 0, 0);
        func_001655e0(&D_003F3050[i], e->x14, e->x70, r);
        e->x50 = 0;
        e->x3c = 0;
        e->x70 += D_002BBDFC;
        func_00167d70(e->x14, D_002BBDFC);
        if ((f32)func_00167698(r) <= e->x70) e->x70 = 0.0f;
        e->x30 = k++;
        e->u34.w = (p->x90 << 24) | 0x606060;
        func_00161de8(e->x14, &D_00640E40[i], &e->x28, 0);
    }
}

void func_00209f70(void) {
    s32 i;
    f32 *t;
    f32 *f;
    B64 *c;
    func_00209d48();
    t = D_003F31D0[D_003F3870 - 1];
    for (i = 0; i < D_003F3870; i++) {
        PlatVu0ViewScreenMatrix(&D_00640E40[i], 512.0f, 0.7999999523162842f, K84, t[i], 1920.0f, 65792.0f, 16777000.0f, 1.0f, 5000.0f);
    }
    t = D_003F31D0[3];
    c = D_003F3050;
    f = &c->x38;
    for (i = 0; i < 4; i++) {
        PlatVu0ViewScreenMatrix(&D_00640E40[i + 4], 512.0f, 0.7999999523162842f, K84, t[i], 1920.0f, 65792.0f, 16777000.0f, 1.0f, 5000.0f);
        f[i * 16 - 1] = D_003F3150[D_00304BE8->x48e[i]];
        f[i * 16] = D_003F3178[D_00304BE8->x48e[i]];
    }
    PlatVu0ViewScreenMatrix(&D_00640E40[8], 512.0f, 0.7999999523162842f, K84, 2048.0f, 1920.0f, 65792.0f, 16777000.0f, 1.0f, 5000.0f);
}

void func_0020a1d8(void) {
    PartyMdl *e = D_003F3530;
    s32 i = 3;
    do {
        if (e->active != 0) {
            func_00162110(e->x0, (s32)&e->x14);
            if (e->xc0 != 0) {
                func_00121eb0((s32)e->xc0);
            }
        }
        i -= 1;
        e++;
    } while (i >= 0);
}

void func_0020a248(s32 idx) {
    PartyMdl *e = &D_003F3530[idx];
    s32 r, i, j, k, fl;
    Mtx9 *m;
    func_00162070(e->x0, &e->x10, &e->x1c, &e->x14);
    func_001321a0(e->x18, e->x8);
    func_00132220(e->x14, e->x8);
    func_00167ac0(e->x14, 0, 0);
    e->x70 = 0;
    e->x28 = 0;
    e->x30 = -1;
    e->x2c = 0;
    e->c38[0] = -128;
    e->c38[3] = -1;
    e->c38[1] = -128;
    e->u34.c[0] = 96;
    e->c38[2] = -128;
    e->u34.c[1] = 96;
    e->x48 = 0;
    e->u34.c[2] = 96;
    e->x50 = 0;
    e->u34.c[3] = -128;
    e->c40[0] = -128;
    e->c40[1] = -128;
    e->c40[7] = -1;
    e->x60 = 0x31000070;
    e->c40[2] = -128;
    e->c40[3] = -128;
    e->c40[4] = -128;
    e->x68 = 0x800d0;
    e->c40[5] = -128;
    e->c40[6] = -128;
    e->x3c = 0;
    func_001655e0(D_00425CE0, e->x14, e->x70, func_001301d8(e->x18, 1, 0, 0));
    r = func_00162348(e->x14, 52);
    if (r >= 0) {
        fl = 0;
        e->x78 = func_00162368(e->x14, r);
        e->x74 = func_00162338(e->x14) - e->x78;
        func_00121e28(e->x74 << 6, &e->xc0);
        m = func_001623e0(e->x14) + e->x78;
        func_001625c8(m, &e->x80);
        if (D_00304BE8->x48e[idx] == 2) {
            if (D_002BC128 == 9 || (D_002BC128 == 16 && D_002BC130 == 21)) fl = 1;
        }
        for (i = 0; i < e->x74; i++) {
            PlatVu0MulMatrix(e->xc0 + i * 4, &e->x80, m + i);
            if (fl) {
                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 3; k++) {
                        f32 *d = &e->xc0[i * 4 + j][k];
                        if (j == k) *d = 1.0f;
                        else *d = 0;
                    }
                }
            }
        }
    } else {
        e->x74 = 0;
        e->x78 = -1;
        e->xc0 = 0;
    }
}

void func_0020a518(PartyView *p, s32 a1, s32 *idx, s32 *col) {
    u32 i;
    s32 k = 0xea61;
    for (i = 0; i < D_003E3D68; i++) {
        s32 n = idx[i];
        PartyMdl *e = &D_003F3530[n];
        if (e->active) {
            s32 r = func_001301d8(e->x18, a1, 0, 0);
            func_001655e0(&D_003F3050[n], e->x14, e->x70, r);
            e->x70 += D_002BBDFC;
            func_00167d70(e->x14, D_002BBDFC);
            if ((f32)func_00167698(r) <= e->x70) e->x70 = 0.0f;
            e->x30 = k++;
            e->u34.w = col[i] | (p->x90 << 24) | ((col[i] << 16) | (col[i] << 8));
            func_00161de8(e->x14, &D_00640E40[i + 4], &e->x28, 0);
        } else {
            k += 2;
        }
    }
}

void func_0020a6b8(void) {
}

void func_0020a6c0(s32 n) {
    s32 v;
    void *q;
    PartyMdl *e;

    q = *(void **)((u8 *)func_001ef8f8(n) + 0x14c);
    v = 0;
    e = &D_003F3530[n];
    e->x50 = -1;
    if (q != NULL) {
        v = *(s32 *)((u8 *)q + 4);
    }
    e->x3c = v;
    e->x70 = 0;
}

void func_0020a728(s32 n) {
    PartyMdl *e = &D_003F3530[n];
    e->x50 = 0;
    e->x3c = 0;
}

void func_0020a758(PartyView *p, s32 n, s32 u2, s32 u3) {
    Mtx m;
    Vec4 v;
    PartyMdl *e = &D_003F3530[n];
    s32 i;
    Mtx9 *b;
    if (e->x78 < 0) return;
    v.x = 0;
    v.y = (f32)((s32)p->x24 % 256) * 0.00390625f * 6.2831855f - 3.1415928f;
    v.z = -1.57079613208770751953125f;
    v.w = 1.0f;
    PlatVu0RotMatrix(&m, D_00425CE0, &v);
    PlatVu0TransMatrix(&m, &m, D_003F31E0);
    b = func_001623e0(e->x14) + e->x78;
    for (i = 0; i < e->x74; i++) {
        PlatVu0MulMatrix(b + i, &m, e->xc0 + i * 4);
    }
    e->x30 = 0xea61;
    e->u34.w = (p->x90 << 24) | 0x606060;
    func_00161de8(e->x14, &D_00640E40[8], &e->x28, 0);
}

void func_0020a8e8(void) {
}

/* The views of the members, by the party size, and of the four models
 * (moved from src/hand/text_00200000_h70.c with its users). */
extern u8 D_003F31A0[];
extern u8 D_003F31A8[];
extern u8 D_003F31B0[];
extern u8 D_003F31C0[];
f32 *D_003F31D0[0x4] ALIGNED(16) = {
    (void *)D_003F31A0, (void *)D_003F31A8, (void *)D_003F31B0, (void *)D_003F31C0,
};
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003F3050.h"
#include "data/data_003F.h"
