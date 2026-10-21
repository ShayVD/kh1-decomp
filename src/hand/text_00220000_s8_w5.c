#include "common.h"
#include "data/bss_0064.h"

typedef struct {
    s32 magic;
    s32 ver;
    s32 x8;
    s32 xC;
    s32 x10;
    char name[36];
    s32 x38;
} Save3C;

typedef struct { s32 a, b, c, d; } S4;
#include "data/pieces/D_003E8E08.h"
typedef struct O98 {
    u8 pad[0xc];
    struct O98 *xc;
    s32 x10;
    u8 pad14[0x24 - 0x14];
    union { s32 i; u16 h; } x24;
    u8 p0[0x90 - 0x28];
    s32 x90;
    u8 p1[0xa0 - 0x94];
    f32 xa0;
    u8 p2[0xb0 - 0xa4];
    s32 xb0;
    s32 xb4;
    u8 p3[0xba - 0xb8];
    s16 xba;
    s16 xbc;
    s16 xbe;
    s16 xc0;
    s16 xc2;
    s16 xc4;
    s16 xc6;
    s16 xc8;
    s16 xca;
    s16 xcc;
    s16 xce;
    u8 p5[0xd2 - 0xd0];
    s16 xd2;
    u8 p6[0xd8 - 0xd4];
    s16 xd8;
    s16 xda;
} O98;
#include "data/pieces/D_00425BC8.h"
extern s32 D_006469B0;
extern s32 D_006469B4;
extern u8 D_003F7210[];
extern s32 D_003F7228[];
extern s32 D_003F7230[];
#include "data/pieces/D_003F7238.h"
extern s32 D_003F7248[];
void func_0011d768(s32);
s32 func_001f42b8(void);
s32 func_001fe570(void *);
void func_001fdfd0(void *);
s32 func_001fd538(void *);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_001f3708(void *, s32);
void func_0020bc48(s32, s32, s32);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001efbb8(s32);
s32 func_002192f8(void);
s32 func_00219348(void);
s32 func_00219380(void);
s32 func_002193b8(void);
s32 func_002193f0(void);
s32 func_00219428(void);
s32 func_00219458(s32);

#include "data/pieces/D_003F6E40.h"
extern s32 D_003F6F58[];
extern s32 D_006437C0;
extern s32 D_006437C4;
extern s32 D_006437C8[];
extern s32 D_006437D0[];
extern s32 D_006437DC;
extern s32 D_006437E4;
extern s32 D_006450C0[];
extern Save3C D_00645250[];
extern void *D_00646990;
s32 func_001ee428(s32);
s32 func_001ee440(s32);
void *func_001f31a8(void *, s32);
void func_001f3758(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
void func_001f8ba8(void *);
void func_001f8f30(void);
s32 func_001f9e48(void *, s32, s32, s32, void *, s32, s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_001ff488(void *, s32, s32, s32, s32, s32);
void func_00202fc0(void *);
void func_0020bd18(void *, s32);
void func_0020be10(s32);
void func_00229a10(void *);
void func_00233f18(void);
s32 func_00233f40(s32, s32);
void func_00233ff8(s32, s32);


typedef struct Nd { u8 pad[0x10]; struct Nd *x10; } Nd;
typedef struct { s32 x0; u8 pad[0xc]; s32 x10; } C28;
extern s32 D_006436D0;
extern s32 D_006436D4;
extern s32 D_006436F0;
extern s32 D_00643708;
extern s32 D_00643720[];
extern s32 D_00643730;
extern s32 D_0064373C;
extern s32 D_00643758;
extern s32 D_0064375C;
extern s32 D_00643760[];
extern u8 D_00643770[];
extern u8 D_00643778[];
extern s32 D_00643780[];
extern s32 D_00643790;
extern s32 D_00643794;
extern s32 D_0064379C;
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_003E3D68.h"
extern s32 D_003F34C0;
#include "data/pieces/D_003F34C4.h"
extern s32 D_003F6E2C;
#include "data/pieces/D_00425C28.h"
extern u8 D_003F6C30[];
extern u8 D_003F6C00[];
extern u8 D_003F6BD0[];
extern u8 D_003F68F0[];
extern u8 D_003F68C0[];
extern u8 D_003F6860[];
extern u8 D_003F6C60[];
extern s32 D_003F6CC8[];
void func_001f3840(void *);
void func_00109278(void);
void func_00233ef8(s32);
void func_001f4040(void *, s32);
void func_001f40a0(void *, s32);
void func_001f4058(void *, s32);
void func_00223a30(void *);
void *func_001f3520(void *, s32);
void func_00228700(void *);
void func_001f37c0(void *, s32);
void *func_001f4468(void *);
void func_0020d1d8(void *);
void func_002075f8(void);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);

void func_002287f8(void *arg0) {
    O98 *objs[3];
    s32 i, n, cur, k, c, y;

    if (func_001f42b8()) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3840(arg0);
            func_0011d768(3);
            func_0020be10(16);
        } else {
            func_001fd858(arg0);
            func_0020bd18(arg0, 8);
            D_006436D0 = func_001fd518(arg0);
            if (func_001fe5a0(arg0)) {
                k = D_00643720[D_006436D0];
                switch (k) {
                case 0:
                    func_0011d768(2);
                    func_001f3d58(arg0, 5);
                    func_001f3758(arg0);
                    func_00109278();
                    D_003F34C0 |= 2;
                    func_00233ef8(0);
                    D_00643758 = 0;
                    D_0064373C = 0;
                    (*(C28 *)&D_00425C28).x0 = 3;
                    (*(C28 *)&D_00425C28).x10 = 3;

                    objs[0] = func_001f31a8(D_003F6C30, 6);
                    if (objs[0]) {
                        func_001f3e48(objs[0], arg0);
                        func_001f4040(objs[0], 4);
                        func_001f40a0(objs[0], 0x5A000000);
                        objs[1] = func_001f31a8(D_003F6C00, 6);
                        if (objs[1]) {
                            func_001f3e48(objs[1], objs[0]);
                            D_006436D4 = D_006436F0;
                            objs[1]->xd2 = *(u16 *)&D_006436D4 << 4;
                            objs[2] = func_001f31a8(D_003F6BD0, 6);
                            if (objs[2]) {
                                func_001f3e48(objs[2], objs[1]);
                                func_001f3dc0(objs[1]);
                            }
                        }
                    }
                    break;
                case 1:
                    if ((n = D_003E3D68 - 1) != 0) {
                        D_003F34C0 |= 2;
                        func_0011d768(2);
                        for (i = 0; i < 4; i++) {
                            D_00643760[i] = i;
                            D_00643770[i] = (((u8 *)D_00304BE8) + 0x48E)[i];
                            D_00643780[i] = 96;

                        }
                        D_0064375C = 0;
                        D_00643790 = 0;
                        D_00643794 = 0;
                        D_0064379C = 0;
                        for (i = 0; i < 4; i++) {
                            D_00643778[i] = (((u8 *)D_00304BE8) + 0x48E)[i];
                        }
                        func_001f3d58(arg0, 5);
                        func_001f3758(arg0);
                        objs[0] = func_001f31a8(D_003F68F0, 6);
                        if (objs[0]) {
                            func_001f3e48(objs[0], arg0);
                            n = D_003E3D68;
                            objs[0]->xcc = n;
                            objs[0]->xba = n * 448 - 32;
                            objs[0]->xce = n;
                            if (D_00643708 >= n) {
                                D_00643708 = 0;
                            }
                            objs[0]->xd2 = *(u16 *)&D_00643708 << 4;
                            objs[1] = func_001f31a8(D_003F68C0, 6);
                            if (objs[1]) {
                                func_001f3e48(objs[1], objs[0]);
                                func_001f3dc0(objs[0]);
                            }
                        }
                    } else {
                        func_0011d768(4);
                        func_001f3d58(arg0, 5);
                        func_001f3758(arg0);
                        objs[0] = func_001f31a8(D_003F6860, 6);
                        if (objs[0]) {
                            func_001f3e48(objs[0], arg0);
                            func_001f4058(objs[0], 1);
                            func_001f3d58(objs[0], 6);
                            func_00223a30(objs[0]);
                        }
                    }
                    break;
                case 2:
                    if (D_003F6E2C == 3) {
                        func_0011d768(6);
                        func_001f3d58(arg0, 5);
                        func_001f3758(arg0);
                        objs[0] = func_001f3520(D_003F6C60, 6);
                        if (objs[0]) {
                            func_001f3e48(objs[0], arg0);
                            func_001f4058(objs[0], 1);
                            func_001f3d58(objs[0], 6);
                            func_00228700(objs[0]);
                        }
                    } else {
                        func_0011d768(4);
                    }
                    break;
                case 3:
                    func_001f37c0(((Nd *)D_003F34C4)->x10, 1);
                    func_001f3d58(((Nd *)D_003F34C4)->x10->x10, 2);
                    func_001f3d58(((Nd *)D_003F34C4)->x10->x10->x10, 2);
                    func_0020d1d8(func_001f4468(arg0));
                    func_0011d768(2);
                    func_002075f8();
                    break;
                }
            }
        }
    }
    cur = D_00643720[func_001fd518(arg0)];
    for (i = 0, y = 0; i < D_00643730; i++, y += 28) {
        k = D_00643720[i];
        c = cur == k;
        if (k == 2) {
            if (D_003F6E2C != 3) {
                c = cur == k ? 3 : 2;
            }
        } else if (k == 3) {
            c = cur == k ? 7 : 6;
        }
        func_00207830(arg0, c, 2, 0, y, 122, D_003F6CC8[k]);
    }
}
#include "data/data_003F.h"
