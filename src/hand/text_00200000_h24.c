#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"

typedef struct { u8 pad0[0x24]; s32 f24; u8 pad[0xb0 - 0x28]; s32 b0; s32 b4; s16 b8; s16 ba; s16 bc; s16 be; s16 c0; s16 c2; s16 c4; s16 c6; u8 pad3[10]; s16 d2; u8 pad4[6]; s16 da; } Sbbc0;

#include "data/pieces/D_003E3D68.h"

#include "data/pieces/D_00425BC8.h"
void func_0011d768(s32);

s32 func_001efd98(s32);

s32 func_001f42b8(Sbbc0 *);
void func_001f3708(Sbbc0 *, s32);
s32 func_001fe570(Sbbc0 *);
void func_00207bb0(Sbbc0 *, s32);

extern s32 D_00641250[];
extern s32 D_00641258, D_0064125C, D_00641260, D_00641264, D_00641268, D_0064126C, D_00641270, D_00641274;
void func_00211398(void) {
    D_00641250[0] = 0;
    D_00641250[1] = 0;
    D_00641258 = 0;
    D_0064125C = 0;
    D_00641260 = 0;
    D_00641264 = 0;
    D_00641268 = 0;
    D_0064126C = 0;
    D_00641270 = 0;
    D_00641274 = 0;
}

void func_002113f0(Sbbc0 *a0) {
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) func_001f3708(a0, 6);
        }
    }
    func_00207bb0(a0, a0->f24);
}

void func_00211480(Sbbc0 *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->b4 -= v;
    a0->ba += v;
    a0->c0 += v;
    a0->f24 = a1;
}

typedef W606Mem_304be8 S4BE8e;
#include "data/pieces/D_00304BE8.h"
extern s32 D_00641BF0[], D_00641BE0[];

void func_00211698(void) {
    u32 i;
    for (i = 0; i < D_003E3D68; i++) {
        s32 v = D_00304BE8->m[((u8 *)D_00304BE8)[0x48e + i]].sub.x32;
        D_00641BF0[i] = D_00641BE0[i] = v;
    }
}

void func_001f9010(s32);
extern s32 D_00641BCC, D_00641BC8;
typedef struct { u8 pad[24]; u8 a[26]; u8 b; } S1BB0;
extern S1BB0 *D_00641BB0; /* src/data/bss_0064.c: s32 D_00641BB0 */
s32 func_001eebd8(s32);
s32 func_001eec00(s32);
void func_001f94f0(s32, s32, s32, s32, s32, s32, s32);
void func_00212c20(s32 a0) {
    s32 v;
    if (D_00641BC8 + D_00641BCC == 0) {
        v = func_001eebd8(D_00641BB0->b);
    } else {
        v = func_001eec00(D_00641BB0->a[D_00641BCC]);
    }
    func_001f9010(23);
    func_001f94f0(a0, 0, 174, 12, v, 17, 0x80c87850);
}

extern s32 D_00641BC4;
#include "data/pieces/D_003E8E08.h"
s32 func_001ee618(s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
void func_002131e8(s32 a0) {
    s32 x;
    s32 t;
    func_001f9010(23);
    t = D_00641BC4;
    x = 165;
    if (t) {
        (*(s32 *)&D_003E8E08) = func_001ee618(t);
        x = 166;
    }
    func_001f9438(a0, 0, 174, 12, x, 17, 0x80c87850);
}

void func_00214030(Sbbc0 *a0) {
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) func_001f3708(a0, 6);
        }
    }
    func_00207bb0(a0, a0->f24);
}

void func_002140c0(Sbbc0 *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->b4 -= v;
    a0->ba += v;
    a0->c0 += v;
    a0->f24 = a1;
}

#include "data/pieces/D_003F34B8.h"
typedef S34B8_3f34b8 S34B8;
void func_002161e8(s32, s32);
void func_00216180(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        D_003F34B8->a[i] = 4;
        func_002161e8(i, 4);
    }
}

extern s32 *D_003F41E8[];
extern s32 D_003F4200[][9];
void func_00170d60(s32, s32, s32);
void func_002161e8(s32 a0, s32 a1) {
    s32 *p;
    s32 i;
    if (a1 != 4) p = D_003F41E8[a1];
    else p = D_003F4200[a0];
    for (i = 0; i < 9; i++) func_00170d60(a0, i, p[i]);
}

extern u32 D_00642CCC; /* src/data/bss_0064.c: s32 D_00642CCC */
void func_00216280(void);
void func_00217fb0(void) {
    u32 *p = &D_00642CCC;
    u32 n = D_003E3D68 - 1;
    if (n < *p) *p = n;
    func_00216280();
}

extern s32 D_00642D18;

void func_00218d60(s32 a0) {
    s32 x;
    s32 t;
    func_001f9010(23);
    t = D_00642D18;
    x = 272;
    if (t) {
        (*(s32 *)&D_003E8E08) = func_001ee618(t);
        x = 273;
    }
    func_001f9438(a0, 0, 174, 12, x, 17, 0x80c87850);
}

void func_00219128(void) {
    S34B8 *p = D_003F34B8;
    p->f2c = 1;
    p->f8 = 0;
    p->f4 = 0;
    p->fc = 0;
    p->f10 = 0;
    p->f14 = 0;
    p->f18 = 0;
    p->f0 = 0;
}

#include "data/pieces/D_003F59A0.h"
extern f32 D_003F59B0;
extern s32 D_003F59B4, D_003F59B8;
extern s32 D_003F59C8[];
extern s32 D_006430F4;
extern s32 D_00643108, D_0064310C;

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

typedef struct { s32 f0; u8 pad[16]; u8 f14[200 - 20]; s32 fc8; s32 fcc; } S3020;
extern S3020 D_00643020;
extern s32 D_00643100;
void func_00162110(s32, void *);
void func_00176310(s32);
void func_0021b418(void) {
    if (D_00643020.fcc) {
        func_00162110(D_00643020.f0, D_00643020.f14);
        if (D_00643020.fc8) func_00176310(D_00643020.fc8);
        D_00643020.fcc = 0;
        D_00643100 = 0;
    }
}

extern s32 D_00642EA0;
extern u8 D_00642E98[];
#include "data/pieces/D_003F5C18.h"
void func_0021cfc8(void) {
    s32 i;
    D_00642EA0 = 0;
    for (i = 0; i < 6; i++) {
        if (D_003F5C18[i]) D_00642E98[D_00642EA0++] = i;
    }
}

extern s32 D_00643010, D_00643014;
extern s32 D_003F5C30[];
void func_0021fb50(void);
void func_002205c0(void);
void func_002210f0(void);
void func_00223978(void);
void func_00222b80(void);
void func_002234e8(void);
void func_0021db30(void) {
    s32 i;
    D_00643010 = 0;
    D_00643014 = 0;
    D_003F34B8->b112[1] = 0;
    for (i = 5; i >= 0; i--) D_003F5C30[i] = 0;
    func_0021fb50();
    func_002205c0();
    func_002210f0();
    func_00223978();
    func_00222b80();
    func_002234e8();
}

extern s32 D_0064324C, D_00643250;
extern s32 D_00643258[], D_00643268[];
extern s32 D_00643118, D_0064311C, D_00643120;
void func_0021fb50(void) {
    s32 i;
    D_0064324C = 0;
    D_00643250 = 0;
    for (i = 0; i < 3; i++) {
        D_00643258[i] = 0;
        D_00643268[i] = 0;
    }
    D_0064311C = -1;
    D_00643120 = -1;
    D_00643118 = 0;
}

extern s32 D_00643418;
extern u8 D_006433F8[];
s32 func_00206ee8(s32);
void func_00207298(s32);
void func_002072e0(s32);
void func_002204f0(void) {
    s32 i;
    for (i = 0; i < D_00643418; i++) {
        if (!func_00206ee8(D_006433F8[i])) {
            func_00207298(0);
            return;
        }
    }
    func_002072e0(0);
}

extern u8 D_003F6300[], D_003F62D0[];
s32 func_001f31a8(void *, s32);
void func_001f3e48(s32, s32);
void func_00220fe8(s32 a0) {
    s32 a[2];
    a[0] = func_001f31a8(D_003F6300, 50);
    if (a[0]) {
        func_001f3e48(a[0], a0);
        a[1] = func_001f31a8(D_003F62D0, 50);
        if (a[1]) func_001f3e48(a[1], a[0]);
    }
}

void func_0021b800(s32);
void func_002213a8(s32 a0) {
    if (a0 <= 0) func_0021b800(48);
    else if (a0 < 6) func_0021b800(49);
    else if (a0 < 10) func_0021b800(50);
    else if (a0 < 15) func_0021b800(a0 + 41);
    else func_0021b800(56);
}

extern s32 D_00643674;
extern u8 D_00643668[];
s32 func_00207250(s32);
void func_00222ab0(void) {
    s32 i;
    for (i = 0; i < D_00643674; i++) {
        if (!func_00207250(D_00643668[i])) {
            func_00207298(5);
            return;
        }
    }
    func_002072e0(5);
}

/* needs make: uses rodata */

s32 func_00219158(s32 a0) {
    switch (a0) {
    case 0: return D_003F34B8->f0;
    case 1: return D_003F34B8->f4;
    case 2: return D_003F34B8->f8;
    case 3: return D_003F34B8->f10;
    case 4: return D_003F34B8->f14;
    case 5: return D_003F34B8->f18;
    case 6:
    default: return D_003F34B8->f2c;
    }
}

void func_002191f0(s32 a0, s32 a1) {
    switch (a0) {
    case 0: D_003F34B8->f0 = a1; break;
    case 1: D_003F34B8->f4 = a1; break;
    case 2: D_003F34B8->f8 = a1; break;
    case 3: D_003F34B8->f10 = a1; break;
    case 4: D_003F34B8->f14 = a1; break;
    case 5: D_003F34B8->f18 = a1; break;
    case 6:
    default: D_003F34B8->f2c = a1; break;
    }
}
#include "data/data_003F.h"
