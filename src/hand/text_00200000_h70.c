#include "common.h"
#include "data/bss_0064.h"
typedef struct { u8 b[64]; } B64;
typedef struct {
    u8 pad0[0x14]; s32 x14; u8 x18[0x10]; u8 x28[8]; s32 x30; s32 x34; u8 pad38[4]; s32 x3c;
    u8 pad40[0x10]; s32 x50; u8 pad54[0x1c]; f32 x70; s32 x74; s32 x78; u8 pad7c[0x44]; u8 *xc0; u8 padc4[8]; s32 active;
} E3530;
typedef struct { E3530 e[3]; u8 pad[0x33c - 0x270]; s32 x33c; } S3530;
extern S3530 D_003F3530;
extern s32 D_003F3870;
extern B64 D_003F3050[];
B64 D_00640E40[0x9] ALIGNED(64);
extern f32 D_002BBDFC;
s32 func_001301d8(void *, s32, s32, s32);
void func_00161de8(s32, void *, void *, s32);
void func_001655e0(void *, s32, s32, f32);
s32 func_00167698(s32);
void func_00167d70(s32, f32);
typedef struct { u8 pad[0x34]; f32 x34; f32 x38; u8 pad3c[4]; } C3050;

typedef struct { u8 pad[0x90]; s32 x90; } P9e18;
void func_00209e18(P9e18 *p) {
    s32 i;
    s32 k = 0xea61;
    for (i = 0; i < D_003F3870; i++) {
        E3530 *e = &D_003F3530.e[i];
        s32 r = func_001301d8(e->x18, 1, 0, 0);
        func_001655e0(&D_003F3050[i], e->x14, r, e->x70);
        e->x50 = 0;
        e->x3c = 0;
        e->x70 += D_002BBDFC;
        func_00167d70(e->x14, D_002BBDFC);
        if ((f32)func_00167698(r) <= e->x70) e->x70 = 0.0f;
        e->x30 = k++;
        e->x34 = (p->x90 << 24) | 0x606060;
        func_00161de8(e->x14, &D_00640E40[i], e->x28, 0);
    }
}

extern f32 *D_003F31D0[];
extern f32 D_003F3150[];
extern f32 D_003F3178[];
typedef struct { u8 pad[4]; u8 x4; u8 pad5[0x21]; u8 x26[0x4e]; } T74;
typedef struct { T74 e[10]; u8 pad[0x48e - 0x488]; u8 x48e[11]; u8 x499[256]; } G4BE8;
extern G4BE8 *D_00304BE8;
void func_00209d48(void);
void func_00267b08(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
#define K84 0.83999986946582794189453125f

void func_00209f70(void) {
    s32 i;
    f32 *t;
    f32 *f;
    C3050 *c;
    func_00209d48();
    t = D_003F31D0[D_003F3870 - 1];
    for (i = 0; i < D_003F3870; i++) {
        func_00267b08(&D_00640E40[i], 512.0f, 0.7999999523162842f, K84, t[i], 1920.0f, 65792.0f, 16777000.0f, 1.0f, 5000.0f);
    }
    t = D_003F31D0[3];
    c = (C3050 *)D_003F3050;
    f = &c->x38;
    for (i = 0; i < 4; i++) {
        func_00267b08(&D_00640E40[i + 4], 512.0f, 0.7999999523162842f, K84, t[i], 1920.0f, 65792.0f, 16777000.0f, 1.0f, 5000.0f);
        f[i * 16 - 1] = D_003F3150[D_00304BE8->x48e[i]];
        f[i * 16] = D_003F3178[D_00304BE8->x48e[i]];
    }
    func_00267b08(&D_00640E40[8], 512.0f, 0.7999999523162842f, K84, 2048.0f, 1920.0f, 65792.0f, 16777000.0f, 1.0f, 5000.0f);
}

extern u32 D_003E3D68;
void func_0020a518(P9e18 *p, s32 a1, s32 *idx, s32 *col) {
    u32 i;
    s32 k = 0xea61;
    for (i = 0; i < D_003E3D68; i++) {
        s32 n = idx[i];
        E3530 *e = &D_003F3530.e[n];
        if (e->active) {
            s32 r = func_001301d8(e->x18, a1, 0, 0);
            func_001655e0(&D_003F3050[n], e->x14, r, e->x70);
            e->x70 += D_002BBDFC;
            func_00167d70(e->x14, D_002BBDFC);
            if ((f32)func_00167698(r) <= e->x70) e->x70 = 0.0f;
            e->x30 = k++;
            e->x34 = col[i] | (p->x90 << 24) | ((col[i] << 16) | (col[i] << 8));
            func_00161de8(e->x14, &D_00640E40[i + 4], e->x28, 0);
        } else {
            k += 2;
        }
    }
}

typedef struct { f32 m[4][4]; } __attribute__((aligned(16))) Mtx;
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) Vec4;
typedef struct { u8 pad[0x24]; f32 x24; u8 pad28[0x68]; s32 x90; } Pa758;
extern u8 D_00425CE0[];
extern u8 D_003F31E0[];
void func_002678b8(Mtx *, void *, Vec4 *);
void func_00267578(Mtx *, Mtx *, void *);
u8 *func_001623e0(s32);
void sceVu0MulMatrix(void *, void *, void *);
void func_0020a758(Pa758 *p, s32 n, s32 u2, s32 u3) {
    Mtx m;
    Vec4 v;
    E3530 *e = &D_003F3530.e[n];
    s32 i;
    u8 *b;
    if (e->x78 < 0) return;
    v.x = 0;
    v.y = (f32)((s32)p->x24 % 256) * 0.00390625f * 6.2831855f - 3.1415928f;
    v.z = -1.57079613208770751953125f;
    v.w = 1.0f;
    func_002678b8(&m, D_00425CE0, &v);
    func_00267578(&m, &m, D_003F31E0);
    b = func_001623e0(e->x14) + (e->x78 << 6);
    for (i = 0; i < e->x74; i++) {
        sceVu0MulMatrix(b + i * 64, &m, e->xc0 + i * 64);
    }
    e->x30 = 0xea61;
    e->x34 = (p->x90 << 24) | 0x606060;
    func_00161de8(e->x14, &D_00640E40[8], e->x28, 0);
}

extern s32 D_006411E0;
extern f32 D_006411E4;
extern f32 D_006411E8;
extern f32 D_006411EC;
extern f32 D_006411F0;
extern f32 D_006411F4;
extern f32 D_006411F8;
extern s32 D_006411FC;
extern f32 D_00641200;
extern f32 D_00641204; /* src/data/bss_0064.c: s32 D_00641204 */
extern f32 D_00641208;
extern f32 D_0064120C;
extern f32 D_00641210;
extern f32 D_00641214;
extern f32 D_00641218;
extern f32 D_002BBDFC;
s32 func_0020bb78(void);
void func_0020b6a8(void);
void func_0020b998(void) {
    if (D_006411E0) {
        D_006411E8 += D_002BBDFC;
        if (D_006411E4 <= D_006411E8) {
            D_00641210 = D_006411F4;
            D_00641214 = D_006411F8;
            D_006411E0 = 0;
        } else {
            D_00641210 = D_006411EC + (D_006411F4 - D_006411EC) * D_006411E8 / D_006411E4;
            D_00641214 = D_006411F0 + (D_006411F8 - D_006411F0) * D_006411E8 / D_006411E4;
        }
    }
    switch (D_006411FC) {
    case 1:
        break;
    case 0:
        D_00641204 += D_002BBDFC;
        if (D_00641200 <= D_00641204) {
            D_006411FC = 1;
            D_00641218 = 128.0f;
        } else {
            D_00641218 = D_00641208 + (D_0064120C - D_00641208) * D_00641204 / D_00641200;
        }
        break;
    case 2:
        D_00641204 += D_002BBDFC;
        if (D_00641200 <= D_00641204) {
            D_006411FC = 3;
            D_00641204 = D_00641200;
            D_00641218 = 0.0f;
        } else {
            D_00641218 = D_00641208 + (D_0064120C - D_00641208) * D_00641204 / D_00641200;
        }
        break;
    }
    if (func_0020bb78()) func_0020b6a8();
}

typedef struct { u8 pad[0x3c]; s32 x3c; s32 x40; s32 x44; s32 x48; u8 pad4c[0xe4 - 0x4c]; } E3D70;
extern E3D70 D_003E3D70[];
s32 func_001ee5f0(s32);
s32 func_001f94f0(s32, s32, s32, s32, s32, s32, s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0020be68(s32 a0, s32 x, u32 k) {
    s32 n = D_00304BE8->x48e[k];
    u8 *t = &D_00304BE8->e[n].x4;
    E3D70 *e = &D_003E3D70[n];
    func_001f94f0(a0, 2, x - 39, 5, func_001ee5f0(n), 13, 0x80808080);
    func_001fb428(a0, 1, 3, 0, x - 2, 25, *t, 11, 0x80208080);
    func_001fb428(a0, 1, 3, 0, x - 43, 39, e->x3c, 11, 0x8040a040);
    func_001f9438(a0, 0, x - 41, 39, 84, 11, 0x80308030);
    func_001fb428(a0, 1, 3, 0, x - 2, 39, e->x40, 11, 0x80308030);
    func_001fb428(a0, 1, 3, 0, x - 43, 53, e->x44, 11, 0x80b05050);
    func_001f9438(a0, 0, x - 41, 53, 84, 11, 0x80943e3e);
    func_001fb428(a0, 1, 3, 0, x - 2, 53, e->x48, 11, 0x80943e3e);
}

extern s32 D_003F3398[];
s32 func_00111798(void);
s32 func_001ee2d0(void);
s32 func_001ee308(void);
s32 func_001ee348(void);
s32 func_001ef7a0(void);
s32 func_001fbcb0(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0020ccb0(s32 a0) {
    s32 c, a, b, d, x;
    func_001fc308(a0, 10, 54, 0, 0, 5, 0, 0x40ff8a00, 0x40ff8a00);
    c = D_003F3398[func_00111798()];
    a = func_001ee2d0();
    b = func_001ee308();
    d = func_001ee348();
    x = func_001fbcb0(a0, 0, 2, 1, 51, 51, a, c);
    x = func_001fc308(a0, x - 2, 51, 0, 0, 0, c, 0x80808080, 0x80808080);
    x = func_001fbcb0(a0, 0, 2, 1, x - 3, 51, b, c);
    x = func_001fc308(a0, x - 2, 51, 0, 0, 0, c, 0x80808080, 0x80808080);
    x = func_001fbcb0(a0, 0, 2, 1, x - 3, 51, d, c);
    func_001fc308(a0, 9, 20, 0, 0, 4, 0, 0x402760f5, 0x402760f5);
    func_001fbcb0(a0, 1, 5, 1, x, 18, func_001ef7a0(), 1);
}

typedef struct { u8 pad[0x10]; s32 x10; u8 pad14[0x70]; s32 x84; u8 pad88[0x28]; s32 xb0; u8 padb4[4]; u16 xb8; u8 padba[4]; s16 xbe; u8 padc0[2]; s16 xc2; u8 padc4[8]; u16 xcc; u16 xce; u8 padd0[2]; s16 xd2; } Obj;
extern u8 D_003F3330[], D_003F3280[], D_003F3230[], D_003F3200[], D_003F3358[];
extern u16 D_00640E20, D_00640E24;
s32 func_001f4390(Obj *);
Obj *func_001f31a8(void *, s32);
void func_001f3e90(Obj *, Obj *);
void func_001f3e20(Obj *, Obj *);
void func_001f3d58(Obj *, s32);
void func_001f3dc0(Obj *);
void func_00207598(void);
void func_00205e30(Obj *, void *);
void func_00206130(Obj *, s32, s32, s32, s32, s32);
void func_0020ca30(Obj *, s32, s32, s32);
s32 func_0010fd18(void);
void func_001f9e48(Obj *, s32, s32, s32, s32, s32, s32);
void func_0020b3d8(Obj *, s32, s32);
void func_0020ca68(Obj *a0) {
    Obj *o[4];
    s32 d;
    if (func_001f4390(a0) && a0->x10 == 0) {
        o[0] = func_001f31a8(D_003F3330, 1);
        if (o[0]) {
            func_001f3e90(a0, o[0]);
            func_001f3e20(o[0], a0);
            o[0]->xcc = o[0]->xce = D_00640E20;
            func_00207598();
            o[0]->xd2 = D_00640E24 * 16;
            o[1] = func_001f31a8(D_003F3280, 6);
            if (o[1]) {
                func_001f3e90(o[0], o[1]);
                func_001f3e20(o[1], o[0]);
                func_001f3d58(o[1], 4);
                o[2] = func_001f31a8(D_003F3230, 1);
                if (o[2]) {
                    func_001f3e90(o[1], o[2]);
                    func_001f3e20(o[2], o[1]);
                    o[3] = func_001f31a8(D_003F3200, 54);
                    if (o[3]) {
                        func_001f3e90(o[2], o[3]);
                        func_001f3e20(o[3], o[2]);
                        func_001f3d58(o[3], 6);
                        d = 4 - D_003E3D68;
                        d *= 0x4f0;
                        o[3]->xb0 += d;
                        o[3]->xb8 -= d;
                        o[3]->x84 = 6;
                        func_001f3dc0(o[0]);
                    }
                }
            }
        }
    }
    func_00205e30(a0, D_003F3358);
    func_00206130(a0, 0, 62, 512, 2, 0x80f04646);
    func_0020ca30(a0, 0, 0x808f1f22, 0x80e16063);
    func_001fc308((s32)a0, 160, 35, 0, 19, 20, 0, 0x80399bff, 0x80399bff);
    func_001f9e48(a0, 0, 173, 35, func_0010fd18(), 19, 0x80399bff);
    func_0020b3d8(a0, 401, 4);
}

extern u8 *D_003F3448[];
extern s32 D_003F3468[];
extern s32 D_003F3488[];
void func_0020bb90(s32, s32);
void func_0020bd18(Obj *, s32);
void func_0020bda8(s32);
void func_0020d050(Obj *a0) {
    Obj *o[7];
    s32 i, d;
    for (i = 0; i < 7; i++) {
        o[i] = func_001f31a8(D_003F3448[i], D_003F3468[i]);
        if (o[i]) {
            func_001f3e90(a0, o[i]);
            func_001f3e20(o[i], a0);
            func_001f3d58(o[i], D_003F3488[i]);
            a0 = o[i];
        }
    }
    o[3]->xcc = o[3]->xce = D_00640E20;
    func_00207598();
    o[3]->xd2 = D_00640E24 * 16;
    d = 4 - D_003E3D68;
    i = d * 0x4f0;
    o[6]->xb0 += i;
    o[6]->xb8 -= i;
    o[6]->x84 = 6;
    func_001f3dc0(o[3]);
    func_0020bb90((o[3]->xb0 + o[3]->xc2 + o[3]->xbe - 0x7000) >> 4, 0);
    func_0020bd18(o[3], 8);
    func_0020bda8(16);
}

s32 func_001559f0(s32, s32);
extern s32 D_003F34CC;
extern s32 D_003F34D0;
extern s32 D_003F34D4;
extern s32 D_003F34D8;
extern s32 D_003F34DC;
extern s32 D_003F34E0;
extern s32 D_003F34E4;
extern s32 D_003F34E8;
extern s32 D_003F34EC;
extern s32 D_003F34F0;
extern s32 D_003F34F4;
extern s32 D_003F34F8;
extern s32 D_003F34FC;
extern s32 D_003F3500;
extern s32 D_003F3504;
extern s32 D_003F3508;
extern s32 D_003F350C;
extern s32 D_003F3510;
extern s32 D_003F3514;
extern s32 D_003F3518;
extern s32 D_003F351C;
extern s32 D_003F3520;
void func_0020d360(void) {
    D_003F34CC = 0; { s32 *p = &D_003F34D0; *p = func_001559f0(52, 1); }
    D_003F34D4 = 0; { s32 *p = &D_003F34D8; *p = func_001559f0(52, 1) + 0x4000; }
    D_003F34DC = 0; { s32 *p = &D_003F34E0; *p = func_001559f0(52, 1) + 0x1c000; }
    D_003F34E4 = 0; { s32 *p = &D_003F34E8; *p = func_001559f0(52, 1) + 0x2d000; }
    D_003F34EC = 0; { s32 *p = &D_003F34F0; *p = func_001559f0(52, 1) + 0x31000; }
    D_003F34F4 = 0; { s32 *p = &D_003F34F8; *p = func_001559f0(52, 1) + 0x34000; }
    D_003F34FC = 0; { s32 *p = &D_003F3500; *p = func_001559f0(53, 1); }
    D_003F3504 = 0; { s32 *p = &D_003F3508; *p = func_001559f0(54, 1); }
    D_003F350C = 0; { s32 *p = &D_003F3510; *p = func_001559f0(62, 1); }
    D_003F3514 = 0; { s32 *p = &D_003F3518; *p = func_001559f0(62, 1) + 0x54000; }
    D_003F351C = 0; { s32 *p = &D_003F3520; *p = func_001559f0(62, 1) + 0x5c000; }
}

typedef struct { u8 pad[8]; s32 flags; } G5bc8;
extern G5bc8 *D_00425BC8;
extern s32 D_00641224, D_00641228, D_00641230, D_00641234, D_003E8E08;
extern u8 D_003F38B0[];
s32 func_001f42b8(void *);
void func_001f3708(s32, s32);
void func_0011d768(s32);
void func_001fdfd0(s32);
s32 func_001fe570(void *);
s32 func_001fd538(s32);
s32 func_001f4468(s32);
void func_001f3e48(Obj *, s32);
void func_0020d990(Obj *, s32);
s32 func_001ee698(s32);
void func_00207c28(s32, s32);
void func_0020e280(s32 a0) {
    s32 p;
    Obj *o;
    if (func_001f42b8((void *)a0)) {
        if (D_00425BC8->flags & 0x4000) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_001fdfd0(a0);
            func_0020bd18((Obj *)a0, 8);
            if (func_001fe570((void *)a0)) {
                func_001f3708(a0, 6);
                if (!func_001fd538(a0)) {
                    if (D_00641228 != -1) {
                        D_00304BE8->e[D_00304BE8->x48e[D_00641228]].x26[D_00641230] = 0;
                    } else {
                        D_00304BE8->x499[D_00641230]--;
                    }
                    D_00641224 = 5;
                    p = func_001f4468(a0);
                    o = func_001f31a8(D_003F38B0, 6);
                    if (o) {
                        func_001f3e48(o, p);
                        func_0020d990(o, 163);
                    }
                }
            }
        }
    }
    D_003E8E08 = func_001ee698(D_00641234);
    func_00207c28(a0, 128);
}

extern s32 D_00641228, D_00641234;
extern s32 D_003F3940[2][4];
extern s32 D_003F3960[2][4];
typedef struct { u8 pad[0x24]; s32 x24; } O24;
s32 func_001ee7f0(s32);
s32 func_001ee9e0(s32);
s32 func_001ee9b8(s32);
void func_001f9010(s32);
void func_0020e408(O24 *o) {
    s32 s = o->x24;
    s32 f = 0;
    s32 x;
    switch (s) {
    case 0:
        if (D_00641234) {
            if (func_001ee7f0(D_00641234)) f = 1;
        }
        break;
    case 1:
        if (D_00641234) {
            if (func_001ee9e0(D_00641234)) f = 1;
        }
        break;
    case 2:
        if (D_00641228 != -1 && D_00641234) f = 1;
        break;
    case 3:
        if (D_00641234) f = func_001ee9b8(D_00641234) != 0;
        break;
    }
    if (D_00641228 != -1) {
        x = D_003F3940[f][s];
    } else {
        x = D_003F3960[f][s];
    }
    func_001f9010(23);
    func_001f9438((s32)o, 0, 174, 12, x, 17, 0x80c87850);
}

typedef struct { u8 pad[0x40]; s32 x40; } Sub40;
typedef struct { u8 pad[0x10]; Sub40 *x10; u8 pad14[0x14]; s32 x28; u8 pad2c[0xa4]; u16 xd0; u16 xd2; } Ofc;
extern s32 D_00641B98, D_0064126C, D_00641270;
s32 func_001ba3d8(void);
s32 func_001ba3f0(s32);
void func_001fd5e0(Ofc *, s32);
void func_001fd610(Ofc *, s32);
void func_001fd688(Ofc *);
s32 func_001f3758(Ofc *);
void func_001fd858(Ofc *);
s32 func_001fd548(Ofc *);
s32 func_001ba268(s32);
void func_00202fc0(Ofc *);
s32 func_001fd518(Ofc *);
s32 func_001fd618(Ofc *);
s32 func_001fd590(Ofc *);
void func_001f8ee0(Ofc *);
void func_0020e090(Ofc *, s32, s32, s32, s32, s32);
void func_001f8f30(void);
void func_0020fc58(Ofc *o) {
    s32 buf[192];
    s32 n, i, j, sel, fl, q, k;
    Sub40 *p;
    n = func_001ba3d8();
    D_00641B98 = 0;
    for (i = 0; i < n; i++) {
        if (func_001ba3f0(i)) { buf[D_00641B98] = i; D_00641B98++; } 
    }
    if (!D_00641B98) return;
    func_001fd5e0(o, D_00641B98);
    func_001fd610(o, 8);
    func_001fd688(o);
    if (func_001f42b8(o)) {
        if (D_00425BC8->flags & 0x4000) {
            func_001f3758(o);
            func_0011d768(3);
            D_00641224 = 0;
        } else {
            func_001fd858(o);
            func_0020bd18((Obj *)o, 8);
            D_0064126C = (s32)(o->xd0 << 16) >> 20;
            D_00641270 = (s32)(o->xd2 << 16) >> 20;
            k = buf[func_001fd548(o)];
            p = o->x10;
            if (p) p->x40 = func_001ba268(k);
            if (func_001fe570(o)) {
                func_001f3758(o);
                D_00641224 = 0;
            }
        }
    }
    i = 0;
    func_00202fc0(o);
    sel = func_001fd518(o);
    n = func_001fd618(o);
    q = func_001fd590(o);
    fl = o->x28;
    func_001f8ee0(o);
    for (; i < 9 && n < D_00641B98; i++, n++) {
        s32 b = buf[n];
        s32 a = 2;
        if (fl) a = i == sel;
        func_0020e090(o, a, 0, q, 166, b);
        q += 28;
    }
    func_001f8f30();
}

typedef struct { u8 pad[0x24]; f32 x24; } P1840;
extern s32 D_003F34C0, D_003F34C8, D_00641BA8, D_00641C00, D_00641C04, D_00641C08;
extern s32 D_00641BE0[];
void func_0020a728(s32, P1840 *);
void func_0020a6c0(s32, P1840 *);
void func_00211718(void);
void func_00149f10(s32, void (*)(void));
void func_00211840(P1840 *o) {
    s32 s;
    if (D_003F34C0 & 1) return;
    if (!D_00641C00) return;
    s = D_00641C08;
    switch (s) {
    case 0:
        o->x24 += D_002BBDFC;
        func_0020a758((Pa758 *)o, D_00641BA8, 10, 50);
        return;
    case 1:
        func_0020a728(D_00641BA8, o);
        D_003F34C8++;
        D_00641C04 = s;
        D_00641C08 = 2;
        func_00149f10(D_00641BE0[D_00641BA8], func_00211718);
        return;
    case 2:
        if (!D_00641C04) D_00641C08 = 3;
        break;
    case 3:
        func_0020a6c0(D_00641BA8, o);
        D_00641C08 = 0;
        break;
    }
}

extern s32 D_00642418[], D_00642818[], D_00642C18;
s32 func_001ef370(s32);
s32 func_001ef0c0(s32);
void func_0020f290(s32 *, s32, s32);

void func_002127e0(void) {
    s32 i, v;
    D_00642818[0] = 0;
    D_00642C18 = 1;
    D_00642418[0] = 0;
    for (i = 1; i < 256; i++) {
        if (D_00304BE8->x499[i] && func_001ef370(i) && func_001ef0c0(i) > 0) {
            s32 n = D_00642C18;
            D_00642C18 = n + 1;
            D_00642418[n] = i;
        }
    }
    if (D_00642C18 < 2) return;
    func_0020f290(&D_00642418[1], 0, D_00642C18 - 2);
    for (i = 1; i < D_00642C18; i++) {
        v = func_001ef0c0(D_00642418[i]);
        if (v > 0) D_00642818[i] = v;
    }
}

typedef u32 (*KF3de0)(s32);
extern KF3de0 D_003F3DE0[];
void func_00213e50(u8 *a, s32 lo, s32 hi, s32 k) {
    s32 i, j;
    u32 p;
    u8 t;
    i = lo;
    j = hi;
    p = D_003F3DE0[k](a[(lo + hi) / 2]);
    for (;;) {
        while (D_003F3DE0[k](a[i]) < p) i++;
        while (p < D_003F3DE0[k](a[j])) j--;
        if (i >= j) break;
        t = a[i]; a[i++] = a[j]; a[j--] = t;
    }
    if (lo < i - 1) func_00213e50(a, lo, i - 1, k);
    if (j + 1 < hi) func_00213e50(a, j + 1, hi, k);
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_003F31A0[];
extern u8 D_003F31A8[];
extern u8 D_003F31B0[];
extern u8 D_003F31C0[];
f32 *D_003F31D0[0x4] ALIGNED(16) = {
    (void *)D_003F31A0, (void *)D_003F31A8, (void *)D_003F31B0, (void *)D_003F31C0,
};
void func_00213d80();
void func_00213db8();
void func_00213e18();
KF3de0 D_003F3DE0[0x4] ALIGNED(16) = {
    (void *)func_00213d80, (void *)func_00213db8, (void *)func_00213e18, 0,
};
