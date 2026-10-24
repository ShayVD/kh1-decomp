/* The item shop's menu, part 2 (docs/modules.md "Session 43"), 0x0022f818-0x002305b0:
 * selling.  func_0022fc88 picks whose items to sell (D_00646A24: a party
 * member below D_003E3D6C, or the bag), and func_0022f818 lists them into
 * D_00646A30[] (D_00647630 of them; D_00646E30 the count, D_00647230 the
 * member's slot or the item; the bag's list is sorted by func_0020f290).
 * func_0022fcb8 is the list (price func_001ee728; left / right change the
 * count D_00646A28), func_0022fa58 checks a sale (D_00646A1C: the item, or
 * -1 munny full, -2 nothing to sell, -3 too many), func_0022fba8 sells
 * (func_001ef7b0 adds the munny).  Not proved by a boot. */
#include "common.h"
#include "platform/pad.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D6C.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003F7A68.h"
#include "data/types/text_00220000_s6_23.h"
#include "text/textwin.h"

extern void (*D_00646A00)(s32); /* src/data/bss_0064.c: s32 D_00646A00 */
extern void (*D_00646A04)(s32); /* src/data/bss_0064.c: s32 D_00646A04 */
extern s32 D_00646A1C;
extern u32 D_00646A24;
extern s32 D_00646A28;
extern s32 D_00646E30[];
extern s32 D_00647230[];
extern u8 *D_00647634; /* src/data/bss_0064.c: s32 D_00647634 */
extern s32 D_00647638;
extern s32 D_003F7780[];
extern s32 D_003F7790[];
extern s32 D_003F77A0[];
extern T78D8 D_003F78D8[8];

void func_0011d768(s32);
s32 func_001ee728(s32);
s32 func_001ef0c0(s32);
s32 func_001ef140(s32, s32);
u32 func_001ef7a0(void);
void func_001ef7b0(s32);
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
void func_0020f290(s32 *, s32, s32);
void func_00242ef8(s32, s32, s32, s32 *, s32 *);

void func_0022f818(void) {
    u32 sel = D_00646A24;
    s32 i, n, k, c;
    if (sel == -1) {
        D_00647630 = 0;
        return;
    }
    if (sel < D_003E3D6C) {
        D_00647634 = &D_00304BE8->m[D_00304BE8->x48e[sel]].sub.lv;
        n = D_00647634[0x21];
        D_00647630 = 0;
        for (i = 0; i < n; i++) {
            k = *(u8 *)(i + (s32)D_00647634 + 0x22);
            if (k != 0 && func_001ee728(k) != 0) {
                D_00646A30[D_00647630] = k;
                D_00646E30[D_00647630] = 1;
                D_00647230[D_00647630++] = i;
            }
        }
        return;
    }
    D_00647630 = 0;
    for (i = 1; i < 256; i++) {
        if (func_001ef0c0(i) != 0 && func_001ee728(i) != 0) {
            c = D_00647630; D_00647630 = c + 1; D_00646A30[c] = i;
        }
    }
    if (D_00647630 == 0) return;
    func_0020f290(D_00646A30, 0, D_00647630 - 1);
    for (i = 0; i < D_00647630; i++) {
        k = D_00646A30[i];
        D_00646E30[i] = func_001ef0c0(k);
        D_00647230[i] = k;
    }
}

void func_0022fa58(s32 i) {
    if (D_00647630 != 0) {
        s32 *p = &D_00646A1C;
        s32 n = D_00646A28;
        *p = D_00646A30[i];
        if (n == 1) {
            if (*p != 0) goto call;
        } else if (D_00646A24 >= D_003E3D6C && D_00646E30[i] >= n) {
            goto call;
        } else {
            *p = -3;
        }
        goto end;
    call:
        if (func_001ef7a0() > 99998) {
            *p = -1;
        }
    } else {
        D_00646A1C = -2;
    }
end:
    D_00647638 = D_00647230[i];
}

s32 func_0022fb50(s32 arg0) {
    if (D_00647630 == 0) return -2;
    if (arg0 != 0) {
        if (func_001ef7a0() > 99998) return -1;
    }
    return arg0;
}

void func_0022fba8(void) {
    s32 *p = &D_00646A1C;
    if (*p > 0) {
        s32 *q = &D_00646A28;
        func_0011d768(8);
        func_001ef7b0(func_001ee728(*p) * *q);
        if (D_00646A24 < D_003E3D6C) {
            s32 o = (s32)D_00647634;
            ((u8 *)(D_00647638 + o))[0x22] = 0;
        } else {
            D_00304BE8->items[*p] -= *q;
        }
        func_0022f818();
    } else {
        func_0011d768(4);
    }
    D_00646A28 = 1;
}

void func_0022fc88(s32 arg0) {
    D_00646A24 = arg0;
    func_0022f818();
    D_00646A28 = 1;
}

void func_0022fcb8(TextWin *m) {
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
                if ((D_00425BC8->x10 & PAD_DIR(PAD_LEFT)) && !(D_00425BC8->x10 & PAD_DIR(PAD_RIGHT))) {
                    if (D_00646A28 > 1) {
                        D_00646A28--;
                        snd = 1;
                        m->x24 = idx;
                    } else if (D_00425BC8->x8 & PAD_DIR(PAD_LEFT)) {
                        D_00646A28 = max;
                        snd = max != 1;
                        m->x24 = idx;
                    }
                } else if ((D_00425BC8->x10 & PAD_DIR(PAD_RIGHT)) && !(D_00425BC8->x10 & PAD_DIR(PAD_LEFT))) {
                    if (D_00646A28 < max) {
                        D_00646A28++;
                        snd = 1;
                        m->x24 = idx;
                    } else if (D_00425BC8->x8 & PAD_DIR(PAD_RIGHT)) {
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
