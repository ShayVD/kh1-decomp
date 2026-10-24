/* The status page of the menu (docs/modules.md "Session 40"),
 * 0x00218020-0x00219128: page 4 of the top menu (message 0x6d; its open
 * function is func_00218f88, set up func_002190e8, reset func_00219118).
 * Its windows are opened from the descriptors D_003F46D0 ... D_003F4730.
 * func_00218dd0 is the member list (D_00642D18 the cursor); func_00218020
 * builds the member's tab list D_00642CF0 (D_00642D10 tabs: the stats, the
 * equipment, the items, one tab per 12 abilities (D_00642D14 of them), and
 * the magic for member 0 when one is learnt), func_00218218 draws a tab
 * (D_003F46B0[tab] its title): the stats of D_003E3D70 and Sub_304be8, the
 * weapon and accessories, the item slots, the abilities, the magic.  Most
 * likely the status page; not proved by a boot.
 *
 * Window views: TextWin (include/text/textwin.h) where the types agree; the
 * member list keeps topmenu.c's N_3f34c4 (D_003F34C4.h) and func_00218f88
 * StWin (a pointer at +0x24 and plain s16 at +0xd2). */
#include "common.h"
#include "platform/pad.h"
#include "text/textwin.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003E3D70.h"
#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003F34C4.h"

typedef struct StWin {
    u8 pad[0x24];
    struct StWin *x24; /* holds a byte id; pointer type matches the original aliasing */
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
} StWin;

extern u8 D_003F46D0[], D_003F4700[], D_003F4730[];
extern s32 D_003F46B0[];
extern s32 D_00642CE8, D_00642D18;

s32 D_00642D10 ALIGNED(16);
s32 D_00642D14 ALIGNED(4);

void func_0011d768(s32);
s32 func_00132f48(s32);
s32 func_0013c360(s32);
s32 func_001ee5f0(s32);
s32 func_001ee618(s32);
s32 func_001ee698(s32);
s32 func_001eeb88(s32);
s32 func_001eebb0(s32);
s32 func_001ef320(void);
s32 func_001ef540(s32);
s32 func_001ef658(s32);
s32 func_001ef720(s32);
void *func_001f31a8(void *, s32);
s32 func_001f3758(void *);
void func_001f3dc0(void *);
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
s32 func_001f42b8(void *);
void func_001f9010(s32);
void func_001f9270(void *, s32, s32, s32, s32, s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd538(void *);
void func_001fd858(void *);
void func_001fdfd0(void *);
void func_00203788(void *, s32, s32, s32, u32);
void func_00206130(void *, s32, s32, s32, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);
void func_00208280(void *, s32, s32, s32, s32, s32);
void func_00208310(void *, s32, s32, s32, s32, s32);
void func_0020bd18(void *, s32);

void func_00218020(s32 n) {
    W606Mem_304be8 *e = &D_00304BE8->m[n];
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

void func_00218218(TextWin *a) {
    s32 n = a->x24;
    W606Mem_304be8 *e = &D_00304BE8->m[n];
    E3D70_3E3D70_3 *r = &D_003E3D70.e3D70_3[n];
    Sub_304be8 *s = &e->sub;
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
        D_003E8E08[0] = s->lv;
        func_001f9438(a, 0, 22, 165, 284, 15, 0x80E6E6E6);
        func_00206130(a, 22, 180, 139, 2, 0x80323232);
        D_003E8E08[0] = s->exp;
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
        for (i = 0; i < s->x18; i++) {
            func_001f94f0(a, 0, x, y - 15, func_001eebb0(s->x19[i]), 15, 0x80E6E6E6);
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
        m = s->x21;
        for (i = 0; i < m; i++) {
            func_001f94f0(a, 0, x, y - 15, func_001ee698(s->x22[i]), 15, 0x80E6E6E6);
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
        for (i = 0; i < 12 && (k = s->name[i]); i++) {
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
        for (i = 12; i < 24 && (k = s->name[i]); i++) {
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
        for (i = 24; i < 36 && (k = s->name[i]); i++) {
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
        for (i = 36; i < 48 && (k = s->name[i]); i++) {
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

void func_00218d60(TextWin *a0) {
    s32 x;
    s32 t;
    func_001f9010(23);
    t = D_00642D18;
    x = 272;
    if (t) {
        D_003E8E08[0] = func_001ee618(t);
        x = 273;
    }
    func_001f9438(a0, 0, 174, 12, x, 17, 0x80c87850);
}

void func_00218dd0(N_3f34c4 *a) {
    N_3f34c4 *o;
    s32 v, k, s, y;
    u32 i;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
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

void func_00218f58(TextWin *arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x6D);
}

void func_00218f88(void *a) {
    StWin *o[3];
    if ((o[0] = func_001f31a8(D_003F4730, 6))) {
        u32 *n;
        s32 *v;
        func_001f3e90(a, o[0]);
        func_001f3e20(o[0], a);
        n = &D_003E3D68;
        v = &D_00642D18;
        o[0]->xba = *n * 448 - 32;
        o[0]->xce = *n;
        o[0]->xcc = *n;
        o[0]->xd2 = *v << 4;
        if ((o[1] = func_001f31a8(D_003F4700, 6))) {
            Save_304be8 **b;
            func_001f3e90(o[0], o[1]);
            func_001f3e20(o[1], o[0]);
            b = &D_00304BE8;
            o[1]->x24 = (StWin *)(u32)(*b)->x48e[*v];
            if ((o[2] = func_001f31a8(D_003F46D0, 6))) {
                func_001f3e90(o[1], o[2]);
                func_001f3e20(o[2], o[1]);
                o[2]->x24 = (StWin *)(u32)(*b)->x48e[*v];
                o[2]->xd8 = 8;
                func_001f3dc0(o[0]);
            }
        }
    }
    D_00642CE8 = (s32)a;
}

void func_002190e8(void) {
  u32 temp_a0;
  u32 new_var;
  temp_a0 = 1;
  new_var = (u32) D_00642D18;
  temp_a0 = D_003E3D68 - temp_a0;
  if (temp_a0 < new_var)
  {
    D_00642D18 = temp_a0;
    if (1)
    {
    }
  }
}

void func_00219118(void) {
    D_00642D18 = 0;
}
