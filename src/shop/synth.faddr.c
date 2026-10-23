/* The synthesis menu's recipe list (src/shop/synth.c, docs/modules.md "Session 43"):
 * seven rows of D_003F7C48 from D_00647654, greyed when func_00231dd0 says the
 * recipe cannot be made, marked when made once (D_00647670); the party's
 * portraits with the count each holds of the item made.  Matches only with
 * -fforce-addr (session 7 flag sweep; without it one lui is scheduled after
 * the sll it precedes in the original). */
#include "common.h"
#include "data/bss_0064.h"
#include "text/textwin.h"

#include "data/types/faddr_text_00230000_s7.h"
#include "data/pieces/D_003E8E08.h"
extern s32 D_003F7E98;
extern s32 D_00647654;
extern s32 D_00647658;
extern s32 D_0064765C;
#include "data/pieces/D_003F7C48.h"
extern void (*D_0064764C)(s32);
extern s32 D_00647660;
extern void (*D_00647648)(s32);
extern s32 D_006476F4;
extern s32 D_00647670[];
#include "data/pieces/D_003E3D6C.h"
#include "data/pieces/D_00304BE8_s.h"
extern s32 D_003F7D30[];
extern s32 D_003F7D40[];
extern s32 D_003F7D50[];
s32 func_001f42b8(void *);
void func_001fd858(void *);
void func_0020bd18(void *, s32);
s32 func_001fd618(void *);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fe5a0(void *);
void func_00231cd0(s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_00202fc0(void *);
s32 func_001fd590(void *);
void func_001f8ee0(void *);
s32 func_00231dd0(s32);
void func_0020dd38(void *, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001f8f30(void);
s32 func_001ef8f8(s32);
s32 func_001ef140(s32, s32);
s32 func_001ef0c0(s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00242ef8(s32, s32, s32, s32 *, s32 *);

void func_00231ea0(TextWin *w) {
    s32 pos[2];
    s32 col[4];
    s32 id;
    s32 n, i, j, y, k, r, t, v, yy;
    E6 *e;
    s32 *p;
    if (D_003F7E98 && func_001f42b8(w)) {
        func_001fd858(w);
        func_0020bd18(w, 8);
        D_00647654 = func_001fd618(w);
        D_00647658 = func_001fd518(w);
        D_0064765C = func_001fd548(w);
        if (func_001fe5a0(w)) {
            func_00231cd0(D_003F7C48[D_0064765C].id);
            if (D_0064764C) D_0064764C(D_00647660);
        }
    }
    id = D_003F7C48[D_0064765C].id;
    if (D_00647648) D_00647648(id);
    n = w->xcc;
    (*(S4_3e8e08 *)&D_003E8E08).a = D_006476F4;
    (*(S4_3e8e08 *)&D_003E8E08).b = n;
    func_001f9438(w, 0, 160, 42, 430, 15, 0x80E6E6E6);
    j = 0;
    func_00202fc0(w);
    i = D_00647654;
    y = func_001fd590(w);
    func_001f8ee0(w);
    for (; j < 7 && i < n; j++, i++) {
        s32 c;
        e = &D_003F7C48[i];
        p = &D_00647670[i];
        if ((e->x4 == 1 && *p != 0) || func_00231dd0(i)) c = (j == D_00647658) ? 3 : 2;
        else c = j == D_00647658;
        func_0020dd38(w, c, 27, y, 204, e->id);
        if (*p) func_001fc308(w, 189, y + 7, 0, 0, 55, 0, 0x80009100, 0x8027E4D4);
        y += 28;
    }
    func_001f8f30();
    y = 303;
    pos[0] = w->xb0 + 5136;
    pos[1] = w->xb4 + 3760;
    col[0] = 128;
    col[1] = 128;
    col[2] = 128;
    col[3] = w->x90;
    for (k = 0; k < D_003E3D6C; ) {
        r = func_001ef8f8(k);
        if (!r) break;
        func_001fc308(w, y, 218, 0, 0, 21, 0, 0x26E6E6E6, 0x26E6E6E6);
        func_001fc308(w, y, 218, 0, 0, 22, 0, 0x4C000000, 0x4C000000);
        v = func_001ef140(D_00304BE8->x48e[k], id);
        func_001fb428(w, 1, 0, 0, y + 33, 269, v, 15, 0x80808080);
        y += 48;
        pos[0] += D_003F7D40[k];
        pos[1] += D_003F7D50[k];
        func_00242ef8(r, D_003F7D30[k], D_003F7D30[k], pos, col);
        pos[0] = pos[0] - D_003F7D40[k] + 768;
        pos[1] -= D_003F7D50[k];
        k++;
    }
    func_001fc308(w, y, 218, 0, 0, 21, 0, 0x26E6E6E6, 0x26E6E6E6);
    func_001fc308(w, y, 218, 0, 0, 22, 0, 0x4C000000, 0x4C000000);
    func_001fc308(w, y - 8, 230, 0, 0, 7, 0, 0x80808080, 0x80808080);
    func_001fb428(w, 1, 0, 0, y + 33, 269, func_001ef0c0(id), 15, 0x80808080);
}
#include "data/data_003F.h"
