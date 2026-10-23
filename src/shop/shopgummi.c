/* The item shop's menu, part 3 (docs/modules.md "Session 43"), 0x002305b0-0x002316f8:
 * the same buy and sell lists for a second kind of goods, counted by
 * func_001ba3f0 (held) / func_001ba458 (the most one can hold) and set by
 * func_001ba358 / func_001ba420, priced func_001eeaf0 (buy) and func_001eeb08
 * (sell), D_00647640 the total held (shopframe.c's modes 2 and 3).  Most
 * likely the Gummi blocks; not proved by a boot.  func_002307c0 / func_002305b0
 * / func_00230728 buy (D_00646A18 as in shopbuy.c), func_00231018 /
 * func_00230e38 / func_00230f18 sell (D_00646A1C as in shopsell.c; the list
 * of what is held is built on the stack). */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003F77B0.h"
#include "data/pieces/D_003F7A68.h"
#include "data/types/text_00220000_s6_23.h"
#include "text/textwin.h"

extern void (*D_00646A00)(s32); /* src/data/bss_0064.c: s32 D_00646A00 */
extern void (*D_00646A04)(s32); /* src/data/bss_0064.c: s32 D_00646A04 */
extern u16 *D_00646A08;
extern s32 D_00646A1C;
extern s32 D_00646A28;
extern s32 D_0064763C;
extern s32 D_00647640;
extern T78D8 D_003F78D8[8];

void func_0011d768(s32);
void func_001ba358(s32, s32);
s32 func_001ba3d8(void);
s32 func_001ba3f0(s32);
void func_001ba420(s32, s32);
s32 func_001ba458(s32);
u32 func_001eeaf0(s32);
s32 func_001eeb08(s32);
u32 func_001ef7a0(void);
void func_001ef7b0(s32);
void func_001ef7f0(s32);
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
void func_0020be10(s32);
void func_0020e1c0(void *, s32, s32, s32, s32, s32);

void func_002305b0(s32 i) {
    s32 *p = &D_0064763C;
    s32 *q;
    s32 id = D_00646A0C[i];
    s32 a;
    *p = func_001eeaf0(id) * *(q = &D_00646A28);
    if (func_001ef7a0() >= (u32)*p) {
        a = func_001ba3f0(id);
        if (a == func_001ba458(id)) {
            D_00646A18 = -2;
            return;
        }
        a = func_001ba3f0(id) + *q;
        if (func_001ba458(id) < a) {
            D_00646A18 = -4;
            return;
        }
        D_00646A18 = id;
        return;
    }
    D_00646A18 = -1;
}

s32 func_00230698(s32 arg0) {
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 var_v0;
    u32 temp_s0;

    temp_s0 = func_001eeaf0(arg0);
    var_v0 = -1;
    if (func_001ef7a0() >= temp_s0) {
        temp_s0_2 = func_001ba3f0(arg0);
        if (temp_s0_2 == func_001ba458(arg0)) {
            return -2;
        }
        temp_s0_3 = func_001ba3f0(arg0);
        var_v0 = (temp_s0_3 < func_001ba458(arg0)) ? arg0 : -4;
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}

void func_00230728(void) {
    if (D_00646A18 >= 0) {
        func_0011d768(8);
        func_001ef7f0(D_0064763C);
        func_001ba358(D_00646A18, D_00646A28);
        D_00647640 += D_00646A28;
    } else {
        func_0011d768(4);
    }
    D_00646A28 = 1;
}

void func_002307c0(TextWin *m) {
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
            if ((D_00425BC8->x10 & 0x80000080) && !(D_00425BC8->x10 & 0x20000020)) {
                if (D_00646A28 > 1) {
                    D_00646A28--;
                    snd = 1;
                    m->x24 = idx;
                } else if (D_00425BC8->x8 & 0x80000080) {
                    if (max != 1) {
                        D_00646A28 = max;
                        snd = 1;
                    }
                    m->x24 = idx;
                }
            } else if ((D_00425BC8->x10 & 0x20000020) && !(D_00425BC8->x10 & 0x80000080)) {
                if (D_00646A28 < (s32)max) {
                    D_00646A28++;
                    snd = 1;
                    m->x24 = idx;
                } else if (D_00425BC8->x8 & 0x20000020) {
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

void func_00230e38(s32 a) {
    s32 *p;
    if (a >= 0) {
        p = &D_00646A28;
        if (func_001ba3f0(a) >= *p) {
            if (func_001ef7a0() <= 99998) D_00646A1C = a;
            else D_00646A1C = -1;
        } else D_00646A1C = -3;
    } else {
        D_00646A1C = -2;
    }
}

s32 func_00230ec8(s32 arg0) {
    if (arg0 >= 0) {
        return (func_001ef7a0() <= 0x1869EU) ? arg0 : -1;
    }
    return -2;
}

void func_00230f18(void) {
    s32 *p = &D_00646A1C;
    if (*p >= 0) {
        s32 *q = &D_00646A28;
        s32 *r;
        s32 i, n;
        func_0011d768(8);
        i = 0;
        func_001ef7b0(func_001eeb08(*p) * *q);
        func_001ba420(*p, func_001ba3f0(*p) - *q);
        r = &D_00647640;
        *r -= *q;
        n = func_001ba3d8();
        for (; i < n; i++) {
            if (func_001ba3f0(i) != 0 && func_001eeb08(i) != 0) {
                goto done;
            }
        }
        func_0020be10(16);
    } else {
        func_0011d768(4);
    }
done:
    D_00646A28 = 1;
}

void func_00231018(TextWin *m) {
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
                if ((D_00425BC8->x10 & 0x80000080) && !(D_00425BC8->x10 & 0x20000020)) {
                    if (D_00646A28 > 1) {
                        D_00646A28--;
                        snd = 1;
                        m->x24 = idx;
                    } else if (D_00425BC8->x8 & 0x80000080) {
                        if (max != 1) {
                            D_00646A28 = max;
                            snd = 1;
                        }
                        m->x24 = idx;
                    }
                } else if ((D_00425BC8->x10 & 0x20000020) && !(D_00425BC8->x10 & 0x80000080)) {
                    if (D_00646A28 < max) {
                        D_00646A28++;
                        snd = 1;
                        m->x24 = idx;
                    } else if (D_00425BC8->x8 & 0x20000020) {
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
