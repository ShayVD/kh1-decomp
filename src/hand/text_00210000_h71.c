#include "common.h"
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
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
Obj *func_001f31a8(u8 *, s32);
void func_001f3e48(Obj *, void *);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);

#include "data/pieces/D_003F34C4.h"
typedef f32 Mtx[4][4];
extern s32 D_003F5C30[];
void func_0021b820(void);
extern s32 D_00643200[];
s32 func_0021b800(s32);
s32 func_00207088(s32);

extern s32 D_00643200[];
s32 func_00207088(s32);
void func_002072e0(s32);
void func_00207298(s32);

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
#include "vm/script_vm.h"
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
    return func_0010edb0(x, y, 256, D_00643424 * 2, a->x90, (s32)func_001c2df0((s8 *)D_003F3518, k));
}

#include "data/data_003F.h"
#include "data/data_003E.h"
