#include "common.h"
#include "data/bss_0064.h"


typedef struct { u8 pad[0x24]; s32 x24; u8 pad28[0x90 - 0x28]; s32 x90; u8 pad94[0xb0 - 0x94]; s32 xb0; s32 xb4; u8 padb8[0xcc - 0xb8]; s16 xcc; } W22;
typedef struct { u8 pad0[8]; s32 x8; s32 xc; s32 x10; } Pad8;
#include "data/types/text_00220000_s6_23.h"
typedef struct { u8 pad[0x48e]; u8 x48e[16]; } S48e;
#include "data/pieces/D_00425BC8.h"
extern S48e *D_00304BE8;
#include "data/pieces/D_003E3D6C.h"
extern s32 D_003F7780[];
extern s32 D_003F7790[];
extern s32 D_003F77A0[];
extern T78D8 D_003F78D8[8];
extern s32 D_003F7A68;
extern void (*D_00646A00)(s32);
extern void (*D_00646A04)(s32);
extern s32 D_00646A1C;
extern u32 D_00646A24;
extern s32 D_00646A28;
extern s32 D_00646A30[];
extern s32 D_00647630;
void func_0011d768(s32);
s32 func_001ee728(s32);
s32 func_001ef0c0(s32);
s32 func_001ef140(s32, s32);
s32 func_001ef7a0(void);
s32 func_001ef8f8(u32);
s32 func_001f42b8(void *);
void func_001f8ee0(void *);
void func_001f8f30(void);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fbcb0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
void func_001fd5e0(void *, s32);
void func_001fd610(void *, s32);
s32 func_001fd618(void *);
void func_001fd688(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00202fc0(void *);
void func_00205b30(void *, void *);
s32 func_00206130(void *, s32, s32, s32, s32, s32);
void func_00207e20(void *, s32, s32, s32, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bd18(void *, s32);
void func_0020dd38(void *, s32, s32, s32, s32, s32);
void func_0022fa58(s32);
s32 func_0022fb50(s32);
void func_00242ef8(s32, s32, s32, s32 *, s32 *);

void func_0022fcb8(W22 *m) {
    s32 pos[2]; s32 k1, k3, r3, y3;
    s32 col[4];
    s32 idx, max, snd, r, c, id, sel, i, j, y, n;
    func_001fd5e0(m, D_00647630);
    func_001fd610(m, 8);
    func_001fd688(m);
    if (func_001f42b8(m)) {
        if (D_003F7A68 != 0) {
            if (D_00647630) {
                func_001fd858(m);
                func_0020bd18(m, 8);
                idx = func_001fd548(m);
                if (idx != m->x24) D_00646A28 = 1;
                max = 1;
                if (D_003E3D6C <= D_00646A24) max = func_001ef0c0(D_00646A30[idx]);
                snd = 0;
                if ((((Pad8 *)D_00425BC8)->x10 & 0x80000080) && !(((Pad8 *)D_00425BC8)->x10 & 0x20000020)) {
                    if (D_00646A28 > 1) {
                        D_00646A28--;
                        snd = 1;
                        m->x24 = idx;
                    } else if (((Pad8 *)D_00425BC8)->x8 & 0x80000080) {
                        D_00646A28 = max;
                        snd = max != 1;
                        m->x24 = idx;
                    }
                } else if ((((Pad8 *)D_00425BC8)->x10 & 0x20000020) && !(((Pad8 *)D_00425BC8)->x10 & 0x80000080)) {
                    if (D_00646A28 < max) {
                        D_00646A28++;
                        snd = 1;
                        m->x24 = idx;
                    } else if (((Pad8 *)D_00425BC8)->x8 & 0x20000020) {
                        if (max != 1) {
                            D_00646A28 = 1;
                            snd = 1;
                        }
                        m->x24 = idx;
                    }
                }
                if (snd) func_0011d768(1);
            }
            if (D_00646A24 != -1 && func_001fe5a0(m)) {
                func_0022fa58(func_001fd548(m));
                if (D_00646A04) D_00646A04(D_00646A1C);
            }
        } else {
            func_0020bc48(8, 544, -32);
        }
    }
    if (D_00646A00) D_00646A00(D_00647630 ? D_00646A30[func_001fd548(m)] : 0);
    for (j = 0; j < sizeof(D_003F78D8) / sizeof(D_003F78D8[0]); j++) func_00205b30(m, &D_003F78D8[j]);
    func_001fc308(m, 260, 11, 0, 0, 6, 0, 0x80007EFF, 0x8000EDFF);
    func_001fc308(m, 353, 11, 0, 0, 4, 0, 0x402760F5, 0x402760F5);
    func_001fbcb0(m, 1, 5, 1, 499, 8, func_001ef7a0(), 1);
    func_001f9438(m, 2, 357, 42, 102, 15, 0x801EC8C8);
    func_001f9438(m, 2, 471, 42, 103, 15, 0x801EC8C8);
    if (D_00647630) {
        j = 0;
        func_00202fc0(m);
        sel = func_001fd518(m);
        i = func_001fd618(m);
        y = func_001fd590(m);
        n = m->xcc;
        func_001f8ee0(m);
        for (; j < 9 && i < n; i++) {
            id = D_00646A30[i];
            if (func_0022fb50(id) < 0) c = (j == sel) ? 3 : 2;
            else c = j == sel;
            j++;
            func_0020dd38(m, c, 276, y, 164, id);
            func_00207e20(m, c, 444, y, func_001ee728(id));
            y += 28;
        }
        func_001f8f30();
    }
    func_00206130(m, 264, 354, 36, 2, 0x80808080);
    func_001f9438(m, 0, 264, 356, 85, 12, 0x80808080);
    func_001fb428(m, 1, 2, 0, 300, 356, D_00646A28, 12, 0x80808080);
    func_00206130(m, 264, 370, 36, 2, 0x80808080);
    func_001fc308(m, 264, 338, 0, 0, 17, 0, 0x60808080, 0x60808080);
    func_001fc308(m, 291, 338, 0, 0, 18, 0, 0x60808080, 0x60808080);
    {
        s32 t = D_003E3D6C * 48;
        pos[0] = m->xb0 + (470 - t) * 16;
        pos[1] = m->xb4 + 5104;
        col[0] = 128;
        col[1] = 128;
        col[2] = 128;
        col[3] = m->x90;
        y3 = 452 - t;
    }
    if (D_00646A24 != -1) func_001fc308(m, y3 + D_00646A24 * 48 - 10, 294, 0, 0, 23, 0, 0x40FF8528, 0x40FF8528);
    for (j = 0; j < D_003E3D6C; j++) {
        r3 = func_001ef8f8(j);
        if (!r3) break;
        func_001fc308(m, y3, 304, 0, 0, 21, 0, 0x26E6E6E6, 0x26E6E6E6);
        func_001fc308(m, y3, 304, 0, 0, 22, 0, 0x4C000000, 0x4C000000);
        if (D_00647630) func_001fb428(m, 1, 0, 0, y3 + 33, 355, func_001ef140(D_00304BE8->x48e[j], D_00646A30[func_001fd548(m)]), 15, j == D_00646A24 ? 0x80E6E6E6 : 0x80808080);
        y3 += 48;
        pos[0] += D_003F7790[j];
        pos[1] += D_003F77A0[j];
        func_00242ef8(r3, D_003F7780[j], D_003F7780[j], pos, col);
        pos[0] = pos[0] - D_003F7790[j] + 768;
        pos[1] -= D_003F77A0[j];
    }
    func_001fc308(m, 452, 304, 0, 0, 21, 0, 0x26E6E6E6, 0x26E6E6E6);
    func_001fc308(m, 452, 304, 0, 0, 22, 0, 0x4C000000, 0x4C000000);
    func_001fc308(m, 444, 314, 0, 0, 7, 0, 0x80808080, 0x80808080);
    if (D_00647630) func_001fb428(m, 1, 0, 0, 485, 355, func_001ef0c0(D_00646A30[func_001fd548(m)]), 15, D_003E3D6C == D_00646A24 ? 0x80E6E6E6 : 0x80808080);
}


#define func_001ef7a0 func_001ef7a0_s1

#include "data/pieces/D_003F77B0.h"
extern s32 D_003F7A68;
extern void (*D_00646A00)(s32);
extern void (*D_00646A04)(s32);
extern u16 *D_00646A08;
extern s32 *D_00646A0C;
extern s32 D_00646A18;
extern s32 D_00646A28;
extern s32 D_00647640;
void func_0011d768(s32);
s32 func_001ba3f0(s32);
s32 func_001ba458(s32);
u32 func_001eeaf0(s32);
u32 func_001ef7a0(void) __asm__("func_001ef7a0");
s32 func_001f42b8(void *);
void func_001f8ee0(void *);
void func_001f8f30(void);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fbcb0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00202fc0(void *);
void func_00205b30(void *, void *);
s32 func_00206130(void *, s32, s32, s32, s32, s32);
void func_00207e20(void *, s32, s32, s32, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bd18(void *, s32);
void func_0020e1c0(void *, s32, s32, s32, s32, s32);
s32 func_00230698(s32);
void func_002305b0(s32);

void func_002307c0(W22 *m) {
    s32 idx, snd, c, id, sel, i, j, y, n, k, t;
    u32 max, d;
    m->xcc = *D_00646A08;
    if (func_001f42b8(m)) {
        if (D_003F7A68 != 0) {
            func_001fd858(m);
            func_0020bd18(m, 8);
            idx = func_001fd548(m);
            if (idx != m->x24) D_00646A28 = 1;
            max = 1;
            i = D_00646A0C[idx];
            id = func_001eeaf0(i);
            if (id) {
                max = func_001ef7a0() / id;
                if (max) {
                    t = func_001ba458(i) - func_001ba3f0(i);
                    if (t < (s32)max) max = t;
                }
            }
            if (max == 0) max = 1;
            snd = 0;
            if ((((Pad8 *)D_00425BC8)->x10 & 0x80000080) && !(((Pad8 *)D_00425BC8)->x10 & 0x20000020)) {
                if (D_00646A28 > 1) {
                    D_00646A28--;
                    snd = 1;
                    m->x24 = idx;
                } else if (((Pad8 *)D_00425BC8)->x8 & 0x80000080) {
                    if (max != 1) {
                        D_00646A28 = max;
                        snd = 1;
                    }
                    m->x24 = idx;
                }
            } else if ((((Pad8 *)D_00425BC8)->x10 & 0x20000020) && !(((Pad8 *)D_00425BC8)->x10 & 0x80000080)) {
                if (D_00646A28 < (s32)max) {
                    D_00646A28++;
                    snd = 1;
                    m->x24 = idx;
                } else if (((Pad8 *)D_00425BC8)->x8 & 0x20000020) {
                    if (max != 1) {
                        D_00646A28 = 1;
                        snd = 1;
                    }
                    m->x24 = idx;
                }
            }
            if (snd) func_0011d768(1);
            if (func_001fe5a0(m)) {
                func_002305b0(idx);
                if (D_00646A04) D_00646A04(D_00646A18);
            }
        } else {
            func_0020bc48(8, 544, -32);
        }
    }
    k = func_001fd548(m);
    if (D_00646A00) D_00646A00(D_00646A0C[k]);
    for (j = 0; j < sizeof(D_003F77B0) / sizeof(D_003F77B0[0]); j++) func_00205b30(m, &D_003F77B0[j]);
    func_001fc308(m, 260, 11, 0, 0, 59, 0, 0x80FF5751, 0x80F7BC7A);
    func_001fc308(m, 353, 11, 0, 0, 4, 0, 0x402760F5, 0x402760F5);
    j = 0;
    func_001fbcb0(m, 1, 5, 1, 499, 8, func_001ef7a0(), 1);
    func_001f9438(m, 2, 357, 42, 102, 15, 0x801EC8C8);
    func_001f9438(m, 2, 471, 42, 103, 15, 0x801EC8C8);
    func_00202fc0(m);
    sel = func_001fd518(m);
    i = func_001fd618(m);
    y = func_001fd590(m);
    n = m->xcc;
    func_001f8ee0(m);
    for (; j < 9 && i < n; i++) {
        id = D_00646A0C[i];
        if (func_00230698(id) < 0) c = (j == sel) ? 3 : 2;
        else c = j == sel;
        j++;
        func_0020e1c0(m, c, 276, y, 164, id);
        func_00207e20(m, c, 444, y, func_001eeaf0(id));
        y += 28;
    }
    func_001f8f30();
    func_00206130(m, 264, 354, 36, 2, 0x80808080);
    func_001f9438(m, 0, 264, 356, 85, 12, 0x80808080);
    func_001fb428(m, 1, 2, 0, 300, 356, D_00646A28, 12, 0x80808080);
    func_00206130(m, 264, 370, 36, 2, 0x80808080);
    func_001fc308(m, 264, 338, 0, 0, 17, 0, 0x60808080, 0x60808080);
    func_001fc308(m, 291, 338, 0, 0, 18, 0, 0x60808080, 0x60808080);
    func_001fc308(m, 463, 310, 0, 0, 25, 0, 0x26E6E6E6, 0x26E6E6E6);
    func_001fc308(m, 463, 310, 0, 0, 26, 0, 0x4C000000, 0x4C000000);
    func_001fb428(m, 1, 2, 0, 497, 315, func_001ba3f0(D_00646A0C[k]), 15, 0x80808080);
    func_001f9438(m, 1, 425, 349, 104, 15, 0x80808080);
    func_001fbcb0(m, 1, 0, 1, 496, 348, D_00647640, 14);
}

#undef func_001ef7a0

#define func_001ef7a0 func_001ef7a0_s2
#define func_001ba3f0 func_001ba3f0_s2

extern s32 D_00646A28;
extern s32 D_00646A1C;
s32 func_001ba3f0(void) __asm__("func_001ba3f0");
u32 func_001ef7a0(void) __asm__("func_001ef7a0");

void func_00230e38(s32 a) {
    s32 *p;
    if (a >= 0) {
        p = &D_00646A28;
        if (func_001ba3f0() >= *p) {
            if (func_001ef7a0() <= 99998) D_00646A1C = a;
            else D_00646A1C = -1;
        } else D_00646A1C = -3;
    } else {
        D_00646A1C = -2;
    }
}

#undef func_001ba3f0
#undef func_001ef7a0

#define func_001ef7a0 func_001ef7a0_s3

extern T78D8 D_003F78D8[8];
extern s32 D_003F7A68;
extern void (*D_00646A00)(s32);
extern void (*D_00646A04)(s32);
extern s32 D_00646A1C;
extern s32 D_00646A28;
extern s32 D_00647640;
void func_0011d768(s32);
s32 func_001ba3d8(void);
s32 func_001ba3f0(s32);
s32 func_001eeb08(s32);
u32 func_001ef7a0(void) __asm__("func_001ef7a0");
s32 func_001f42b8(void *);
void func_001f8ee0(void *);
void func_001f8f30(void);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fbcb0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fbcd8(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
void func_001fd5e0(void *, s32);
void func_001fd610(void *, s32);
s32 func_001fd618(void *);
void func_001fd688(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00202fc0(void *);
void func_00205b30(void *, void *);
s32 func_00206130(void *, s32, s32, s32, s32, s32);
void func_00207e20(void *, s32, s32, s32, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bd18(void *, s32);
void func_0020e1c0(void *, s32, s32, s32, s32, s32);
void func_00230e38(s32);
s32 func_00230ec8(s32);

void func_00231018(W22 *m) {
    s32 ids[192];
    s32 vals[192];
    s32 idx, max, snd, c, id, sel, i, j, y, k, n, nn, q;
    n = 0;
    q = func_001ba3d8();
    for (j = 0; j < q; j++) {
        if (func_001ba3f0(j) && func_001eeb08(j)) {
            ids[n] = j;
            vals[n++] = func_001ba3f0(j);
        }
    }
    func_001fd5e0(m, n);
    func_001fd610(m, 8);
    func_001fd688(m);
    if (func_001f42b8(m)) {
        if (D_003F7A68 != 0) {
            if (n) {
                func_001fd858(m);
                func_0020bd18(m, 8);
                idx = func_001fd548(m);
                if (idx != m->x24) D_00646A28 = 1;
                max = vals[idx];
                snd = 0;
                if ((((Pad8 *)D_00425BC8)->x10 & 0x80000080) && !(((Pad8 *)D_00425BC8)->x10 & 0x20000020)) {
                    if (D_00646A28 > 1) {
                        D_00646A28--;
                        snd = 1;
                        m->x24 = idx;
                    } else if (((Pad8 *)D_00425BC8)->x8 & 0x80000080) {
                        if (max != 1) {
                            D_00646A28 = max;
                            snd = 1;
                        }
                        m->x24 = idx;
                    }
                } else if ((((Pad8 *)D_00425BC8)->x10 & 0x20000020) && !(((Pad8 *)D_00425BC8)->x10 & 0x80000080)) {
                    if (D_00646A28 < max) {
                        D_00646A28++;
                        snd = 1;
                        m->x24 = idx;
                    } else if (((Pad8 *)D_00425BC8)->x8 & 0x20000020) {
                        if (max != 1) {
                            D_00646A28 = 1;
                            snd = 1;
                        }
                        m->x24 = idx;
                    }
                }
                if (snd) func_0011d768(1);
            }
            if (func_001fe5a0(m)) {
                func_00230e38(n ? ids[func_001fd548(m)] : -1);
                if (D_00646A04) D_00646A04(D_00646A1C);
            }
        } else {
            func_0020bc48(8, 544, -32);
        }
    }
    k = func_001fd548(m);
    if (D_00646A00) D_00646A00(n ? ids[k] : -1);
    for (j = 0; j < sizeof(D_003F78D8) / sizeof(D_003F78D8[0]); j++) func_00205b30(m, &D_003F78D8[j]);
    func_001fc308(m, 260, 11, 0, 0, 59, 0, 0x80FF5751, 0x80F7BC7A);
    func_001fc308(m, 353, 11, 0, 0, 4, 0, 0x402760F5, 0x402760F5);
    func_001fbcb0(m, 1, 5, 1, 499, 8, func_001ef7a0(), 1);
    func_001f9438(m, 2, 357, 42, 102, 15, 0x801EC8C8);
    func_001f9438(m, 2, 471, 42, 103, 15, 0x801EC8C8);
    if (n) {
        j = 0;
        func_00202fc0(m);
        sel = func_001fd518(m);
        i = func_001fd618(m);
        y = func_001fd590(m);
        nn = m->xcc;
        func_001f8ee0(m);
        for (; j < 9 && i < nn; i++) {
            id = ids[i];
            if (func_00230ec8(id) < 0) c = (j == sel) ? 3 : 2;
            else c = j == sel;
            j++;
            func_0020e1c0(m, c, 276, y, 164, id);
            func_00207e20(m, c, 444, y, func_001eeb08(id));
            y += 28;
        }
        func_001f8f30();
    }
    func_00206130(m, 264, 354, 36, 2, 0x80808080);
    func_001f9438(m, 0, 264, 356, 85, 12, 0x80808080);
    func_001fb428(m, 1, 2, 0, 300, 356, D_00646A28, 12, 0x80808080);
    func_00206130(m, 264, 370, 36, 2, 0x80808080);
    func_001fc308(m, 264, 338, 0, 0, 17, 0, 0x60808080, 0x60808080);
    func_001fc308(m, 291, 338, 0, 0, 18, 0, 0x60808080, 0x60808080);
    func_001fc308(m, 463, 310, 0, 0, 25, 0, 0x26E6E6E6, 0x26E6E6E6);
    func_001fc308(m, 463, 310, 0, 0, 26, 0, 0x4C000000, 0x4C000000);
    if (n) func_001fb428(m, 1, 2, 0, 497, 315, vals[k], 15, 0x80808080);
    func_001f9438(m, 1, 425, 349, 104, 15, 0x80808080);
    func_001fbcd8(m, 1, 0, 1, 496, 348, D_00647640, 14, n ? 0x80808080 : 0x80404040);
}

#undef func_001ef7a0

#define func_001f9438 func_001f9438_s4
#define D_00425BC8 D_00425BC8_s4
typedef struct { u8 pad[8]; s32 x8; } F8;
extern F8 *D_00425BC8 __asm__("D_00425BC8");
typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[6]; s16 xbe; s16 xc0; s16 xc2; s16 xc4; s16 xc6; u8 p2[0xd2-0xc8]; s16 xd2; u8 p3[4]; s16 xd8; s16 xda; } O;
extern s32 D_006469B0, D_006469B4;
extern s32 D_003F7308[];
extern u8 D_003F7210[];
#include "data/pieces/D_003F47A8.h"
s32 func_001f42b8(void *);
void func_001f3708(void *, s32);
void func_0011d768(s32);
s32 func_00219428(void);
void func_00219418(s32);
void func_0020bc48(s32, s32, s32);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fd518(void *);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
s32 func_001fa808(void *, s32, s32, s32, s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32) __asm__("func_001f9438");
void func_00209820(void *, s32, s32, s32, void *);

typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[0xcc - 0xb8]; s16 xcc; } OCC;
extern u16 *D_00647700;
extern s32 D_003F7EC8;
extern void (*D_006476FC)(s32);
extern void (*D_006476F8)(s32);
extern u8 *D_00647704;
extern s32 D_00647708;
s32 func_001f4390(void);
void func_001fe180(void *);
s32 func_001fd548(void *);
void func_0010ea70(s32, s32, void *);
void func_001fea38(void *);
void func_002040c8(void *);
s32 func_001fd618(void *);
s32 func_001fd590(void *);
void func_001f8e18(void *);
void func_001f8f30(void);

void func_002327b0(OCC *a0) {
    s32 x, y, k, n;
    s32 i, y0;
    a0->xcc = *D_00647700;
    if (func_001f42b8(a0) != 0) {
        if (D_003F7EC8 != 0) {
            func_001fd858(a0);
            if (func_001fe570(a0) != 0) {
                D_003F7EC8 = 0;
                if (D_006476FC != 0) D_006476FC(func_001fd548(a0));
            }
        } else {
            func_001fe180(a0);
        }
    }
    if (func_001f4390 != 0) {
        x = ((a0->xb0 - 0x7000) >> 4) + 28;
        y0 = (a0->xb4 - 0x7400) >> 4;
        func_0010ea70(x, y0 + 40, (void *)D_00647708);
        func_001fea38(a0);
        func_002040c8(a0);
        i = func_001fd618(a0);
        n = a0->xcc;
        y = y0 + func_001fd590(a0);
        func_001f8e18(a0);
        for (k = 11; k >= 0; k--) {
            if (i < n) func_0010ea70(x, y, D_00647704 + i * 32);
            i++;
            y += 24;
        }
        func_001f8f30();
    }
    if (D_006476F8 != 0) D_006476F8(func_001fd548(a0));
}

#undef D_00425BC8
#undef func_001f9438


typedef struct { s32 type; s32 x4; s32 a[6]; } Cmd;
extern Cmd D_006477B0[64];
extern s32 D_006477A8, D_00647FB0, D_00647FB4, D_00647FB8, D_00647FBC, D_00647FC4, D_00647FCC, D_00647FD0, D_00647FD4, D_00647FD8, D_00647FDC, D_00647FE0;
extern s32 D_00425C10, D_00425C14, D_00425CA8, D_00425CAC, D_00648020, D_00648024, D_00648028, D_0064802C, D_00648034;

/* rodata */
void func_00234910(void) {
    if (D_00647FB8 != D_00647FBC) {
        switch (D_006477B0[D_00647FBC].type) {
        case 1:
            D_00647FB0 = 1;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648034 = D_006477B0[D_00647FBC].a[2];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 2:
            D_00647FB0 = 2;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00425CA8 = D_006477B0[D_00647FBC].a[2];
            D_00425CAC = D_006477B0[D_00647FBC].a[3];
            D_00648034 = D_006477B0[D_00647FBC].a[4];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 3:
            D_00647FB0 = 3;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00425CA8 = D_006477B0[D_00647FBC].a[3];
            D_00425CAC = D_006477B0[D_00647FBC].a[4];
            D_00648034 = D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 4:
            D_00647FB0 = 4;
            D_00647FB4 = 0;
            D_00647FCC = 0;
            D_00647FD0 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648034 = D_006477B0[D_00647FBC].a[2];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 5:
            D_00647FB0 = 5;
            D_00647FB4 = 0;
            D_00647FCC = 0;
            D_00647FD0 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648034 = D_006477B0[D_00647FBC].a[2];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 6:
            D_00647FB0 = 6;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648034 = D_006477B0[D_00647FBC].a[3];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 7:
            D_00647FB0 = 7;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648034 = D_006477B0[D_00647FBC].a[3];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 8:
            D_00647FB0 = 8;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648028 = D_006477B0[D_00647FBC].a[3];
            D_0064802C = D_006477B0[D_00647FBC].a[4];
            D_00648034 = D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 9:
            D_00647FB0 = 9;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648034 = D_006477B0[D_00647FBC].a[3];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 10:
            D_00647FB0 = 10;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648028 = D_006477B0[D_00647FBC].a[3];
            D_0064802C = D_006477B0[D_00647FBC].a[4];
            D_00648034 = D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 11:
            D_00647FB0 = 11;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648028 = D_006477B0[D_00647FBC].a[3];
            D_0064802C = D_006477B0[D_00647FBC].a[4];
            D_00648034 = D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 12:
            D_00647FB0 = 12;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648024 = D_006477B0[D_00647FBC].a[3];
            D_00648034 = D_006477B0[D_00647FBC].a[4];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 13:
            D_00647FB0 = 13;
            D_00648034 = D_006477B0[D_00647FBC].a[0];
            D_00647FC4 = D_006477B0[D_00647FBC].x4;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        }
    } else if (D_006477A8 != 0) {
        if (D_00647FD8 != 0) {
            D_00647FD8--;
        } else {
            D_00647FB0 = 1;
            D_00647FB4 = 0;
            D_00425C10 = D_00647FDC;
            D_00425C14 = D_00647FE0;
            D_00647FD8 = D_00647FD4;
            D_00648034 = 0;
        }
    }
}

#include "data/data_003F.h"
#include "data/pieces/D_003F7A68.h"
#include "data/pieces/D_00425C10.h"
#include "data/pieces/D_00425C14.h"
#include "data/pieces/D_00425CA8.h"
#include "data/pieces/D_00425CAC.h"
#include "data/pieces/D_003F78D8.h"
