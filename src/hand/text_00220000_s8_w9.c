/* func_0022eef8 (hand): block A item id in idx (shared with the list loop), func_001ee708 result / x90 save in id (shared with the loop), D_00304BE8->items[idx]. */
#include "common.h"

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
extern S4 D_003E8E08;
typedef struct O98 {
    u8 pad[0xc];
    struct O98 *xc;
    s32 x10;
    u8 pad14[0x24 - 0x14];
    union { s32 i; u16 h; } x24;
    u8 p0[0x8c - 0x28];
    s32 x8c;
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
typedef struct { u8 pad[8]; s32 x8; s32 xc; u32 x10; } F8;
extern F8 *D_00425BC8;
extern s32 D_006469B0;
extern s32 D_006469B4;
extern u8 D_003F7210[];
extern s32 D_003F7228[];
extern s32 D_003F7230[];
extern s32 D_003F7238[];
extern s32 D_003F7248[];
void func_0011d768(s32);
s32 func_001f42b8(void *);
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

extern u8 D_003F6E40[];
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
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
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


typedef struct { u8 pad[0x10]; s32 x10; } F10;
typedef struct { u8 pad[0x48E]; u8 party[11]; u8 items[256]; } SvE;
extern SvE *D_00304BE8;
extern u32 D_003E3D6C;
extern s32 D_003F7A68;
extern u16 *D_00646A08;
extern s32 *D_00646A0C;
extern s32 D_00646A14;
extern s32 D_00646A20;
extern s32 D_00646A28;
extern s32 D_00647644;
extern void (*D_00646A00)(s32);
extern void (*D_00646A04)(s32);
extern u8 D_003F77B0[8][32];
extern s32 D_003F7780[];
extern s32 D_003F7790[];
extern s32 D_003F77A0[];
u32 func_001ee708(s32);
u32 func_001ef7a0(void);
void func_0022ebf8(s32);
void func_00205b30(void *, void *);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fbcb0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_0022edc0(s32);
void func_0020dd38(void *, s32, s32, s32, s32, s32);
void func_00207e20(void *, s32, s32, s32, s32);
void func_001f8ee0(void *);
void func_00206130(void *, s32, s32, s32, s32, s32);
s32 func_001ef8f8(u32);
s32 func_001ef140(s32, s32);
s32 func_001ef0c0(s32);
void func_00242ef8(s32, s32, s32, s32 *, s32 *);

void func_0022eef8(O98 *a0) {
    s32 pos[4];
    s32 col[4];
    s32 j, idx, id, max, lim, snd, pad, sel, i, y, cnt, c, x, save, r;
    u32 n, k;

    a0->xcc = *D_00646A08;
    if (func_001f42b8(a0)) {
        if (D_003F7A68 != 0) {
            func_001fd858(a0);
            func_0020bd18(a0, 8);
            D_00646A14 = func_001fd548(a0);
            if (D_00646A14 != a0->x24.i) {
                D_00646A28 = 1;
            }
            idx = D_00646A0C[D_00646A14];
            id = func_001ee708(idx);
            max = 1;
            if (id) {
                max = func_001ef7a0() / id;
                if (max) {
                    lim = 99 - D_00304BE8->items[idx] ;
                    if (lim < max) {
                        max = lim;
                    }
                }
            }
            if (max == 0) {
                max = 1;
            }
            snd = 0;
            if ((((F10 *)D_00425BC8)->x10 & 0x80000080) && !(((F10 *)D_00425BC8)->x10 & 0x20000020)) {
                if (D_00646A28 >= 2) {
                    D_00646A28--;
                    snd = 1;
                    a0->x24.i = D_00646A14;
                } else if (D_00425BC8->x8 & 0x80000080) {
                    if (max != 1) {
                        D_00646A28 = max;
                        snd = 1;
                    }
                    a0->x24.i = D_00646A14;
                }
            } else if ((((F10 *)D_00425BC8)->x10 & 0x20000020) && !(((F10 *)D_00425BC8)->x10 & 0x80000080)) {
                if (D_00646A28 < max) {
                    D_00646A28++;
                    snd = 1;
                    a0->x24.i = D_00646A14;
                } else if (D_00425BC8->x8 & 0x20000020) {
                    if (max != 1) {
                        D_00646A28 = 1;
                        snd = 1;
                    }
                    a0->x24.i = D_00646A14;
                }
            }
            if (snd) {
                func_0011d768(1);
            }
            if (func_001fe5a0(a0)) {
                func_0022ebf8(D_00646A14);
                if (D_00646A04) {
                    D_00646A04(D_00646A0C[D_00646A14]);
                }
            }
        } else {
            func_0020bc48(8, 544, -32);
        }
    }
    D_00646A14 = func_001fd548(a0);
    if (D_00646A00) {
        D_00646A00(D_00646A0C[D_00646A14]);
    }
    for (j = 0; j < sizeof(D_003F77B0) / 32; j++) {
        func_00205b30(a0, D_003F77B0[j]);
    }
    func_001fc308(a0, 260, 11, 0, 0, 6, 0, 0x80007eff, 0x8000edff);
    func_001fc308(a0, 353, 11, 0, 0, 4, 0, 0x402760f5, 0x402760f5);
    func_001fbcb0(a0, 1, 5, 1, 499, 8, func_001ef7a0(), 1);
    func_001f9438(a0, 2, 357, 42, 102, 15, 0x801ec8c8);
    func_001f9438(a0, 2, 471, 42, 103, 15, 0x801ec8c8);
    func_00202fc0(a0);
    sel = func_001fd518(a0);
    idx = func_001fd618(a0);
    y = func_001fd590(a0);
    cnt = a0->xcc;
    func_001f8ee0(a0);
    for (j = 0; j < 9 && idx < cnt; j++, y += 28) {
        id = D_00646A0C[idx++];
        if (func_0022edc0(id) < 0) {
            c = j == sel ? 3 : 2;
        } else {
            c = j == sel;
        }
        func_0020dd38(a0, c, 276, y, 164, id);
        func_00207e20(a0, c, 444, y, func_001ee708(id));
    }
    func_001f8f30();
    func_00206130(a0, 264, 354, 36, 2, 0x80808080);
    func_001f9438(a0, 0, 264, 356, 85, 12, 0x80808080);
    func_001fb428(a0, 1, 2, 0, 300, 356, D_00646A28, 12, 0x80808080);
    func_00206130(a0, 264, 370, 36, 2, 0x80808080);
    func_001fc308(a0, 264, 338, 0, 0, 17, 0, 0x60808080, 0x60808080);
    func_001fc308(a0, 291, 338, 0, 0, 18, 0, 0x60808080, 0x60808080);
    pos[0] = a0->xb0 + ((470 - D_003E3D6C * 48) << 4);
    pos[1] = a0->xb4 + 5104;
    col[2] = col[1] = col[0] = 128;
    col[3] = a0->x90;
    x = 452 - D_003E3D6C * 48;
    if (D_00646A20 != -1 && D_00647644 != 0) {
        D_00647644--;
        id = a0->x90;
        a0->x90 = id * D_00647644 / 30;
        func_001fc308(a0, x + D_00646A20 * 48 - 10, 296, 0, 0, 23, 0, 0x402395ff, 0x402395ff);
        a0->x90 = id;
    }
    for (j = 0; j < D_003E3D6C; j++) {
        r = func_001ef8f8(j);
        if (!r) break;
        func_001fc308(a0, x, 304, 0, 0, 21, 0, 0x26e6e6e6, 0x26e6e6e6);
        func_001fc308(a0, x, 304, 0, 0, 22, 0, 0x4c000000, 0x4c000000);
        func_001fb428(a0, 1, 0, 0, x + 33, 355, func_001ef140(D_00304BE8->party[j] , D_00646A0C[D_00646A14]), 15, j == D_00646A20 ? 0x80e6e6e6 : 0x80808080);
        pos[0] += D_003F7790[j];
        pos[1] += D_003F77A0[j];
        func_00242ef8(r, D_003F7780[j], D_003F7780[j], pos, col);
        pos[0] = pos[0] - D_003F7790[j] + 768;
        pos[1] -= D_003F77A0[j];
        x += 48;
    }
    func_001fc308(a0, 452, 304, 0, 0, 21, 0, 0x26e6e6e6, 0x26e6e6e6);
    func_001fc308(a0, 452, 304, 0, 0, 22, 0, 0x4c000000, 0x4c000000);
    func_001fc308(a0, 444, 316, 0, 0, 7, 0, 0x80808080, 0x80808080);
    func_001fb428(a0, 1, 0, 0, 485, 355, func_001ef0c0(D_00646A0C[D_00646A14]), 15, D_003E3D6C == D_00646A20 ? 0x80e6e6e6 : 0x80808080);
}
