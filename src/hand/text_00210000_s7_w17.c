#include "common.h"
#include "data/bss_0064.h"
typedef struct {
    u8 x0;
    u8 pad1[0x17];
    u8 n18;
    u8 a19[8];
    u8 n21;
    u8 a22[0x10];
    u8 x32;
    u8 pad33[9];
    s32 x3c;
    u8 a40[12];
    u8 a4c[12];
    u8 a58[12];
    u8 a64[12];
} SaveSub;
typedef struct { s32 x0; SaveSub s; } SaveE;
#include "data/pieces/D_003E3D70.h"
typedef E3D70_3E3D70_3 E3D70;
typedef struct { u8 pad[0x24]; s32 x24; } Obj;
extern SaveE *D_00304BE8;
#include "data/pieces/D_003E8E08.h"
extern s32 D_00642CF0[];
extern s32 D_003F46B0[];
extern s32 D_00642D18;
s32 func_00132f48(s32);
s32 func_0013c360(s32);
s32 func_001ee698(s32);
s32 func_001eeb88(s32);
s32 func_001eebb0(s32);
s32 func_001ef320(void);
s32 func_001ef540(s32);
s32 func_001ef658(s32);
s32 func_001ef720(s32);
void func_001f9270(void *, s32, s32, s32, s32, s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fd538(void *);
void func_00203788(void *, s32, s32, s32, s32);
void func_00206130(void *, s32, s32, s32, s32, s32);
void func_00208280(void *, s32, s32, s32, s32, s32);
void func_00208310(void *, s32, s32, s32, s32, s32);

/* rodata */
void func_00218218(Obj *a) {
    s32 n = a->x24;
    SaveE *e = &D_00304BE8[n];
    E3D70 *r = &D_003E3D70.e3D70_3[n];
    SaveSub *s = &e->s;
    u32 k = D_00642CF0[func_001fd538(a)];
    s32 y = D_00642D18 * 28 + 11;
    s32 x, i, j;
    u8 c;
    s32 t;
    s32 m;

    func_00206130(a, -224, y, 76, 2, 0x80FE7266);
    func_00206130(a, -27, y, 27, 2, 0x80FE7266);
    func_001f9270(a, 0, 16, D_003F46B0[k], 15, 0x801EC8C8);
    t = k < 8;
    func_00203788(a, 205, 6, 328, 0x80C8C8C8);
    if (t) switch (k) {
    case 0:
        D_003E8E08[0] = r->x3c;
        D_003E8E08[1] = r->x40;
        func_001f9438(a, 0, 22, 35, 279, 15, 0x80E6E6E6);
        func_00206130(a, 22, 50, 300, 2, 0x80323232);
        D_003E8E08[0] = r->x44;
        D_003E8E08[1] = r->x48;
        func_001f9438(a, 0, 22, 61, 280, 15, 0x80E6E6E6);
        func_00206130(a, 22, 76, 300, 2, 0x80323232);
        D_003E8E08[0] = func_001ef720(n);
        D_003E8E08[1] = func_001ef658(n);
        func_001f9438(a, 0, 22, 87, 281, 15, 0x80E6E6E6);
        func_00206130(a, 22, 102, 300, 2, 0x80323232);
        D_003E8E08[0] = r->x4c;
        func_001f9438(a, 0, 22, 113, 282, 15, 0x80E6E6E6);
        func_00206130(a, 22, 128, 139, 2, 0x80323232);
        D_003E8E08[0] = r->x50;
        func_001f9438(a, 0, 22, 139, 283, 15, 0x80E6E6E6);
        func_00206130(a, 22, 154, 139, 2, 0x80323232);
        D_003E8E08[0] = s->x0;
        func_001f9438(a, 0, 22, 165, 284, 15, 0x80E6E6E6);
        func_00206130(a, 22, 180, 139, 2, 0x80323232);
        D_003E8E08[0] = s->x3c;
        func_001f9438(a, 0, 22, 191, 285, 15, 0x80E6E6E6);
        func_00206130(a, 22, 206, 139, 2, 0x80323232);
        D_003E8E08[0] = r->x68;
        func_001f9438(a, 0, 172, 165, 286, 15, 0x80E6E6E6);
        func_00206130(a, 172, 206, 150, 2, 0x80323232);
        break;
    case 1:
        func_00208310(a, 10, 33, 0, n, 128);
        func_00206130(a, 30, 52, 288, 2, 0x80323232);
        if (n == 0 && func_001ef320()) {
            func_001f9438(a, 0, 30, 37, 287, 15, 0x80E6E6E6);
            D_003E8E08[0] = func_001eeb88(s->x32);
            func_001f9438(a, 0, 63, 62, 288, 15, 0x80E6E6E6);
            func_00206130(a, 58, 77, 262, 2, 0x80323232);
            func_00206130(a, 58, 52, 2, 26, 0x80323232);
        } else {
            D_003E8E08[0] = func_001eeb88(s->x32);
            func_001f9438(a, 0, 30, 37, 289, 15, 0x80E6E6E6);
        }
        func_00208280(a, 10, 86, 0, 30, 128);
        func_001f9438(a, 0, 30, 86, 290, 15, 0x80E6E6E6);
        x = 30;
        y = 129;
        for (i = 0; i < s->n18; i++) {
            func_001f94f0(a, 0, x, y - 15, func_001eebb0(s->a19[i]), 15, 0x80E6E6E6);
            func_00206130(a, x, y, 128, 2, 0x80323232);
            x = 190;
            if (i & 1) {
                x = 30;
                y += 26;
            }
        }
        break;
    case 2:
        func_00208280(a, 10, 33, 0, 27, 128);
        func_001f9438(a, 0, 30, 33, 291, 15, 0x80E6E6E6);
        x = 30;
        y = 75;
        m = s->n21;
        for (i = 0; i < m; i++) {
            func_001f94f0(a, 0, x, y - 15, func_001ee698(s->a22[i]), 15, 0x80E6E6E6);
            func_00206130(a, x, y, 128, 2, 0x80323232);
            x = 190;
            if (i & 1) {
                x = 30;
                y += 26;
            }
        }
        break;
    case 3:
        func_00208280(a, 10, 33, 0, 41, 128);
        func_001f9438(a, 0, 30, 33, 292, 15, 0x80E6E6E6);
        x = 30;
        y = 75;
        for (i = 0; i < 12 && (k = s->a40[i]); i++) {
            func_001f94f0(a, 0, x, y - 15, func_001ef540(k), 15, 0x80E6E6E6);
            func_00206130(a, x, y, 128, 2, 0x80323232);
            x = 190;
            if (i & 1) {
                x = 30;
                y += 26;
            }
        }
        break;
    case 4:
        func_00208280(a, 10, 33, 0, 41, 128);
        func_001f9438(a, 0, 30, 33, 292, 15, 0x80E6E6E6);
        x = 30;
        y = 75;
        for (i = 12; i < 24 && (k = s->a40[i]); i++) {
            func_001f94f0(a, 0, x, y - 15, func_001ef540(k), 15, 0x80E6E6E6);
            func_00206130(a, x, y, 128, 2, 0x80323232);
            x = 190;
            if (i & 1) {
                x = 30;
                y += 26;
            }
        }
        break;
    case 5:
        func_00208280(a, 10, 33, 0, 41, 128);
        func_001f9438(a, 0, 30, 33, 292, 15, 0x80E6E6E6);
        x = 30;
        y = 75;
        for (i = 24; i < 36 && (k = s->a40[i]); i++) {
            func_001f94f0(a, 0, x, y - 15, func_001ef540(k), 15, 0x80E6E6E6);
            func_00206130(a, x, y, 128, 2, 0x80323232);
            x = 190;
            if (i & 1) {
                x = 30;
                y += 26;
            }
        }
        break;
    case 6:
        func_00208280(a, 10, 33, 0, 41, 128);
        func_001f9438(a, 0, 30, 33, 292, 15, 0x80E6E6E6);
        x = 30;
        y = 75;
        for (i = 36; i < 48 && (k = s->a40[i]); i++) {
            func_001f94f0(a, 0, x, y - 15, func_001ef540(k), 15, 0x80E6E6E6);
            func_00206130(a, x, y, 128, 2, 0x80323232);
            x = 190;
            if (i & 1) {
                x = 30;
                y += 26;
            }
        }
        break;
    case 7:
        func_00208280(a, 10, 33, 0, 48, 128);
        func_001f9438(a, 0, 30, 33, 293, 15, 0x80E6E6E6);
        x = 30;
        y = 75;
        j = 0;
        for (i = 0; i < 7; i++) {
            if (func_0013c360(i) == 1) {
                func_001f94f0(a, 0, x, y - 15, func_00132f48(i), 15, 0x80E6E6E6);
                func_00206130(a, x, y, 128, 2, 0x80323232);
                x = 190;
                if (j & 1) {
                    x = 30;
                    y += 26;
                }
                j++;
            }
        }
        break;
    }
}
#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
