/* The item shop's menu, part 1 (docs/modules.md "Session 43"), 0x0022ebe8-0x0022f818:
 * buying.  func_0022eef8 is the list of the *D_00646A08 items D_00646A0C[] for
 * sale (price func_001ee708, munny func_001ef7a0; left / right change the
 * count D_00646A28 up to what the munny and 99 allow), with the party's
 * portraits along the bottom (D_003E3D6C members, D_00304BE8->x48e) and the
 * count each holds (func_001ef140), D_00646A20 the receiver (func_0022eee0
 * sets it and D_00647644 = 30 frames of its marker).  func_0022ebf8 checks a
 * purchase (D_00646A18: the item, or -1 too little munny, -2 full, -3 the
 * member cannot hold it, -4 too many; D_00647634 / D_00647638 the member and
 * the free slot), func_0022ee08 pays (func_001ef7f0) and gives the item.
 * D_00646A00 / D_00646A04 are the hooks of the cursor and of a purchase (set
 * by the frame, shopframe.c).  Not proved by a boot. */
#include "common.h"
#include "platform/pad.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D6C.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003F77B0.h"
#include "data/pieces/D_003F7A68.h"
#include "text/textwin.h"

extern void (*D_00646A00)(s32); /* src/data/bss_0064.c: s32 D_00646A00 */
extern void (*D_00646A04)(s32); /* src/data/bss_0064.c: s32 D_00646A04 */
extern u16 *D_00646A08;
extern u32 D_00646A20;
extern s32 D_00646A28;
extern Sub_304be8 *D_00647634; /* src/data/bss_0064.c: s32 D_00647634 */
extern s32 D_00647638;
extern u32 D_0064763C; /* src/data/bss_0064.c: s32 D_0064763C */
extern s32 D_003F7780[];
extern s32 D_003F7790[];
extern s32 D_003F77A0[];

void func_0011d768(s32);
u32 func_001ee708(s32);
s32 func_001ee9e0(s32);
s32 func_001ef0c0(s32);
s32 func_001ef140(s32, s32);
u32 func_001ef7a0(void);
void func_001ef7f0(s32);
s32 func_001ef8f8(u32);
s32 func_001f42b8(void *);
void func_001f8ee0(void *);
void func_001f8f30(void);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fbcb0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00202fc0(void *);
void func_00205b30(void *, void *);
void func_00206130(void *, s32, s32, s32, s32, s32);
void func_00207e20(void *, s32, s32, s32, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bd18(void *, s32);
void func_0020dd38(void *, s32, s32, s32, s32, s32);
void func_00242ef8(s32, s32, s32, s32 *, s32 *);

void func_0022ebe8(void) {

}

void func_0022ebf0(void) {

}

void func_0022ebf8(s32 idx) {
    s32 id, i, n, r;
    Sub_304be8 *m;

    id = D_00646A0C[idx];
    D_00646A18 = id;
    D_0064763C = func_001ee708(id) * D_00646A28;
    if (func_001ef7a0() < D_0064763C) goto err;
    if (D_00646A20 < D_003E3D6C) {
        if (D_00646A28 == 1) {
        if (func_001ee9e0(id)) {
            m = &D_00304BE8->m[D_00304BE8->x48e[D_00646A20]].sub;
            D_00647634 = m;
            n = m->x21;
            for (i = 0; i < n; i++) {
                if (!m->x22[i]) goto found;
            }
            D_00646A18 = -2;
            return;
        }
        D_00646A18 = -3;
        return;
        }
        D_00646A18 = -4;
        return;
    }
    if (D_00304BE8->items[D_00646A18] == 99) {
        D_00646A18 = -2;
        return;
    }
    if (D_00304BE8->items[D_00646A18] + D_00646A28 >= 100) {
        D_00646A18 = -4;
        return;
    }
    D_00647634 = 0;
    D_00647638 = D_00646A18;
    return;
found:
    D_00647638 = i;
    return;
err:
    D_00646A18 = -1;
}

s32 func_0022edc0(s32 arg0) {
    u32 temp_s0;

    temp_s0 = func_001ee708(arg0);
    return (func_001ef7a0() >= temp_s0) ? arg0 : -1;
}

s32 func_0022ee08(void) {
    s32 *p = &D_00646A18;
    func_0022ebf8(D_00646A14);
    if (*p > 0) {
        func_0011d768(8);
        func_001ef7f0(D_0064763C);
        if (D_00646A20 < D_003E3D6C) {
            { s32 o = (s32)D_00647634; ((u8 *)(D_00647638 + o))[0x22] = *p; }
        } else {
            D_00304BE8->items[*p] += D_00646A28;
        }
    } else {
        func_0011d768(4);
    }
    D_00646A28 = 1;
    return D_00646A18;
}

void func_0022eee0(s32 arg0) {
    D_00646A20 = arg0;
    D_00647644 = 0x1E;
}

void func_0022eef8(TextWin *a0) {
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
            if (D_00646A14 != a0->x24) {
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
            if (((D_00425BC8)->x10 & 0x80000080) && !((D_00425BC8)->x10 & 0x20000020)) {
                if (D_00646A28 >= 2) {
                    D_00646A28--;
                    snd = 1;
                    a0->x24 = D_00646A14;
                } else if (D_00425BC8->x8 & PAD_DIR(PAD_LEFT)) {
                    if (max != 1) {
                        D_00646A28 = max;
                        snd = 1;
                    }
                    a0->x24 = D_00646A14;
                }
            } else if (((D_00425BC8)->x10 & 0x20000020) && !((D_00425BC8)->x10 & 0x80000080)) {
                if (D_00646A28 < max) {
                    D_00646A28++;
                    snd = 1;
                    a0->x24 = D_00646A14;
                } else if (D_00425BC8->x8 & PAD_DIR(PAD_RIGHT)) {
                    if (max != 1) {
                        D_00646A28 = 1;
                        snd = 1;
                    }
                    a0->x24 = D_00646A14;
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
        func_001fb428(a0, 1, 0, 0, x + 33, 355, func_001ef140(D_00304BE8->x48e[j] , D_00646A0C[D_00646A14]), 15, j == D_00646A20 ? 0x80e6e6e6 : 0x80808080);
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
