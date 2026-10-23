/* Page 5 of the menu, part 1 (docs/modules.md "Session 41"),
 * 0x0021ade8-0x0021b860: the model the page shows (D_00643020, JMdl).
 * func_0021b4c8 (by entry n of D_003F50E0 / D_003F53C0 / D_003F56A0 /
 * D_003F5810) or func_0021b5c8 (by file id) asks for one; func_0021b6a0
 * steps the load (D_006430F0: 1 ask, 2 wait for func_0021b470, 3 set up with
 * func_0021b250, 4 shown), func_0021af38 draws it with the camera
 * func_0021ae28 sets up (D_00425D80), func_0021b418 frees it.
 * func_0021ade8 / func_0021b170 test an id against two-entry lists
 * (D_003F5980 / D_003F59C0).  Page 5 is most likely the journal (its frame,
 * journal.c, loads six files and counts six sections); not proved by a
 * boot. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_003F34C8.h"
#include "data/pieces/D_003F50E0.h"
#include "data/pieces/D_003F59A0.h"
#include "data/pieces/D_00425CE0.h"
#include "data/pieces/D_00425D80.h"
#include "data/pieces/D_00425F70.h"

typedef f32 Mtx[4][4];
typedef struct { u8 pad[8]; s32 x8; s32 xc; } JP8;
/* The model (D_00643020, 0xd0 bytes of bss). */
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
    JP8 *xc8;
    s32 xcc;
} JMdl;
typedef struct { u8 pad[0x90]; s32 x90; } JObj;

extern JMdl D_00643020;
extern s32 D_003F5980;
extern s32 D_003F59C0;
extern f32 D_003F53C0[];
extern u16 D_003F56A0[];
extern u16 D_003F5810[];
extern s32 D_00642EB0;
extern s32 D_00642F60;
s32 D_006430EC ALIGNED(4);

void FlushCache(s32);
void func_00131cc8(s32, void *);
void func_00131d68(s32, JMdl *);
s32 func_001301d8(void *, s32, s32, s32);
void func_001321a0(void *, s32);
void func_00132220(s32, s32);
JP8 *func_00147b08(s32, s32, s32);
s32 func_001560f8(s32, void *);
void func_00161de8(s32, void *, void *, s32);
void func_00162070(s32, s32 *, s32 *, s32 *);
void func_00162110(s32, void *);
void func_001655e0(void *, s32, s32, f32);
s32 func_00167698(s32);
void func_00167ac0(s32, s32, s32);
void func_00167d70(s32, f32);
void func_00176310(void *);
s32 func_001efcb0(s32, s32);
void func_00236a58(void);
void func_00266f38(s32, void *);
s32 func_00266c08(s32);
void func_00267578(void *, void *, void *);
void func_002675a8(s32, void *);
void func_002678b8(void *, void *, void *);
void func_00267b08(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void sceVu0MulMatrix(void *, void *, void *);
void func_0021b250(s32);
void func_0021b418(void);
void func_0021b470(void);

s32 func_0021ade8(s32 arg0) {
    s32 *var_a2;
    s32 temp_v1;
    s32 var_v0;
    u32 var_a1;

    var_a1 = 0;
    var_a2 = &D_003F5980;
loop_1:
    temp_v1 = *var_a2;
    var_a2 += 1;
    var_v0 = 1;
    if (temp_v1 == arg0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 2U) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

void func_0021ae28(void) {
    D_00425F70 = &D_00425D80;
    func_00267b08(D_00425D80.m40, 512.0f, 0.7999999523162842f, 0.839999854564666748046875f, 2048.0f, 2048.0f, 65792.0f, 16777000.0f, 1.0f, 5000.0f);
    D_00425F70->px = 0.0f;
    D_00425F70->py = -170.0f;
    D_00425F70->pz = -400.0f;
    D_00425F70->pw = 1.0f;
    D_00425F70->tx = 0.0f;
    D_00425F70->ty = -150.0f;
    D_00425F70->tz = 0.0f;
    D_00425F70->tw = 1.0f;
    D_00425F70->v160[0] = 0.0f;
    D_00425F70->v160[1] = 0.0f;
    D_00425F70->v160[2] = 1.0f;
    D_00425F70->v160[3] = 1.0f;
    D_00425F70->v170[0] = 0.0f;
    D_00425F70->v170[1] = 1.0f;
    D_00425F70->v170[2] = 0.0f;
    D_00425F70->v170[3] = 1.0f;
    D_00425F70->rx = 0.0f;
    D_00425F70->ry = 0.0f;
    D_00425F70->rz = 0.0f;
    D_00425F70->rw = 1.0f;
}

void func_0021af38(JObj *a) {
    Mtx m;
    Mtx m2;
    f32 v[4];
    s32 r;
    if (D_00643100 == 0) return;
    if (func_0021ade8(D_006430F8)) {
        D_00425F70->v1b0[0] = 1.0f;
        D_00425F70->v1b0[3] = (f32)a->x90 * 0.0078125f;
        D_00425F70->v1b0[1] = 1.0f;
        D_00425F70->v1b0[2] = 1.0f;
        func_002675a8(D_00643020.xc8->xc, D_00425F70->v1b0);
    }
    r = func_001301d8(D_00643020.x18, 0, 0, 0);
    func_00236a58();
    func_002678b8(m, D_00425CE0, D_003F59A0);
    func_00131cc8(D_006430F8, m2);
    sceVu0MulMatrix(m, m, m2);
    func_00267578(m, m, D_003F5990);
    sceVu0MulMatrix(m, D_00425F70->m80, m);
    func_001655e0(m, D_00643020.x14, r, D_00643020.x70);
    D_00643020.x70 += D_002BBDFC;
    func_00167d70(D_00643020.x14, D_002BBDFC);
    if ((f32)func_00167698(r) <= D_00643020.x70) D_00643020.x70 = 0.0f;
    D_00643020.x30 = 60000;
    v[3] = 1.0f;
    D_00643020.x34[3] = a->x90;
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    func_00267578(m, D_00425CE0, v);
    sceVu0MulMatrix(D_00425F70->m100, m, D_00425F70->m40);
    (*(void **)&D_002BC144) = D_00425F70->m40;
    (*(void **)&D_002BC140) = D_00425F70->m80;
    sceVu0MulMatrix(D_00425F70->m100, D_00425F70->m40, D_00425F70->m80);
    func_00161de8(D_00643020.x14, D_00425F70->m100, &D_00643020.x28, 0);
}

s32 func_0021b170(s32 arg0) {
    s32 *var_a2;
    s32 temp_v1;
    s32 var_v0;
    u32 var_a1;

    var_a1 = 0;
    var_a2 = &D_003F59C0;
loop_1:
    temp_v1 = *var_a2;
    var_a2 += 1;
    var_v0 = 1;
    if (temp_v1 == arg0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 2U) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

void func_0021b1b0(s32 a0, s32 a1, f32 x, f32 y) {
    u32 i;
    D_003F59B0 = x;
    D_003F59A0[1] = y;
    for (i = 0; i < 2; i++) {
        if (D_003F59C8[i] == D_006430F4) {
            D_003F59A0[1] = 0.0f;
            break;
        }
    }
    D_00643108 = a0;
    D_0064310C = a1;
    D_003F59B4 = a0 - 256;
    D_003F59B8 = a1 - 192;
}

void func_0021b250(s32 a) {
    s32 r;
    JP8 *p;
    Cam_425f70 *c;
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

void func_0021b418(void) {
    if (D_00643020.xcc) {
        func_00162110(D_00643020.x0, &D_00643020.x14);
        if (D_00643020.xc8) func_00176310(D_00643020.xc8);
        D_00643020.xcc = 0;
        D_00643100 = 0;
    }
}

void func_0021b470(void) {
    D_003F3504 += 1;
    D_003F34C8 -= 1;
}

void func_0021b4a0(void) {
    D_006430F0 = 0;
    D_006430F8 = -1;
    D_00643100 = 0;
    D_006430EC = 0;
}

/* The 256 goes through a local (c) so its li is born before the %hi of
 * D_00643108 in sched1 (local-alloc order); order by hill-climb. */
void func_0021b4c8(s32 n) {
    s32 *p;
    s32 h, h2, k, c;
    k = D_003F50E0[n];
    D_006430F4 = n;
    c = 256;
    D_006430FC = k;
    h2 = D_003F5810[n];
    D_003F59B0 = D_003F53C0[n];
    h = D_003F56A0[n];
    D_003F59A4 = 0;
    D_00643108 = c;
    D_0064310C = h;
    p = &D_006430F0;
    D_003F59B4 = 0;
    D_003F59B8 = h - 192;
    D_00643104 = h2;
    if (*p == 0) {
        *p = 1;
        D_006430F8 = -1;
        D_00643100 = 0;
        D_003F3504 = 0;
    } else if (*p == 4 && D_006430F8 != k) {
        *p = 1;
        D_00643100 = 0;
        D_003F3504 = 0;
    }
}

void func_0021b5c8(s32 a0, s32 a1, s32 a2, s32 a3, f32 f) {
    D_006430F4 = -1;
    D_006430FC = a0;
    D_003F59B0 = f;
    D_003F59A4 = 0;
    D_00643108 = a2;
    D_0064310C = a3;
    D_003F59B4 = a2 - 0x100;
    D_003F59B8 = a3 - 0xC0;
    D_00643104 = a1;
    if (D_006430F0 == 0) {
        D_006430F0 = 1;
        D_006430F8 = -1;
        D_00643100 = 0;
        D_003F3504 = 0;
    } else if (D_006430F0 == 4) {
        if (D_006430F8 != a0) {
            D_006430F0 = 1;
            D_00643100 = 0;
            D_003F3504 = 0;
        }
    }
}

void func_0021b6a0(void) {
    switch (D_006430F0) {
    case 0:
        break;
    case 1:
        switch (D_003F3504) {
        case 0:
            D_003F34C8++;
            D_003F3504 = 1;
            D_006430F0++;
            func_001560f8(D_006430FC, func_0021b470);
            D_006430F8 = D_006430FC;
            break;
        case 1:
            D_006430F0++;
            break;
        default:
            D_006430F0 = 3;
            break;
        }
        break;
    case 2:
        if (D_003F3504 == 2) D_006430F0++;
        break;
    case 3:
        if (D_006430F8 == D_006430FC) {
            FlushCache(0);
            func_0021b250(D_006430FC);
            D_006430F0++;
            D_00643100 = 1;
        } else {
            D_006430F0 = 1;
            D_003F3504 = 0;
        }
        break;
    case 4:
        break;
    }
}

s32 func_0021b7f0(void) {
    return D_00643100;
}

void func_0021b800(s32 arg0) {
    func_001efcb0(D_003F34E8, arg0);
}

void func_0021b820(void) {
    func_00266f38(func_00266c08(2), &D_00642EB0);
    func_00266f38(func_00266c08(2), &D_00642F60);
}

