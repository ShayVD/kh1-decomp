/* The item page of the menu (docs/modules.md "Session 39"),
 * 0x0020d7d8-0x00210000: page 0 of the top menu (message 0x69; its open
 * function is func_002112f8).  Its windows are TextWins opened from the
 * descriptors D_003F3880 ... D_003F3A80, whose first word is the draw
 * callback here.  The tab of the list window (+0x24) picks what it shows:
 * a party member's item slots (src/menu/itemslots.c), the stock
 * (src/menu/itemstock.c) or the list of D_00641B98 (func_0020fc58);
 * func_0020db00 uses an item (from a member's slot or the stock) and opens
 * the result window, func_0020eb98 / func_0020f3c8 collect the slots and the
 * two stock lists D_00641390 / D_00641798 (sorted by func_0020f290), the
 * rows are drawn in src/menu/items.n32.c. */
#include "common.h"
#include "platform/pad.h"
#include "text/textwin.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003E8E08.h"

typedef W606Mem_304be8 DbMember;
typedef struct { u8 pad[0x25]; u8 n; u8 v[0x4e]; } E4BE8;

extern u8 D_003F3880[], D_003F38B0[], D_003F38E0[];
extern s32 D_003F3940[2][4];
extern s32 D_003F3960[2][4];
extern s32 D_00641224, D_00641228, D_00641230, D_00641234;
extern s32 D_0064126C, D_00641270;
extern s32 D_00641278[][16];
extern s32 D_00641378[];
extern s32 D_00641388, D_00641790;
extern s32 D_00641390[], D_00641798[];
extern s32 D_00641B98;

void func_0011d768(s32);
s32 func_00149600(s32, s32);
s32 func_001ba268(s32);
s32 func_001ba3d8(void);
s32 func_001ba3f0(s32);
s32 func_001ee698(s32);
s32 func_001ee7a8(void);
s32 func_001ee7c8(s32);
s32 func_001ee7f0(s32);
s32 func_001ee9b8(s32);
s32 func_001ee9e0(s32);
s32 func_001eea60(s32);
s32 func_001eeac0(s32);
void func_001ef830(void);
s32 func_001efd98(s32);
TextWin *func_001f31a8(void *, s32);
s32 func_001f3708(TextWin *, s32);
s32 func_001f3758(TextWin *);
void func_001f3e48(TextWin *, TextWin *);
s32 func_001f42b8(TextWin *);
TextWin *func_001f4468(TextWin *);
void func_001f8ee0(TextWin *);
void func_001f8f30(void);
void func_001f9010(s32);
void func_001f9438(TextWin *, s32, s32, s32, s32, s32, s32);
void func_001f94f0(TextWin *, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(TextWin *);
s32 func_001fd538(TextWin *);
s32 func_001fd548(TextWin *);
s32 func_001fd590(TextWin *);
void func_001fd5e0(TextWin *, s32);
void func_001fd610(TextWin *, s32);
s32 func_001fd618(TextWin *);
void func_001fd688(TextWin *);
void func_001fd858(TextWin *);
void func_001fdfd0(TextWin *);
s32 func_001fe570(TextWin *);
void func_00202fc0(TextWin *);
void func_002073b0(s32, TextWin *);   /* src/game/bitsets.c takes one; func_0020fee8 has the window in a1 */
void func_002079c8(TextWin *);
void func_00207b38(TextWin *, s32);
void func_00207bb0(TextWin *, s32);
void func_00207c28(TextWin *, s32);
void func_0020bd18(TextWin *, s32);
void func_0020c100(TextWin *, s32);
void func_0020d890(TextWin *, s32);
void func_0020d990(TextWin *, s32);
void func_0020da90(TextWin *, s32);
void func_0020e090(TextWin *, s32, s32, s32, s32, s32);
void func_0020ec50(TextWin *);
s32 func_0020f260(s32);
void func_0020f290(s32 *, s32, s32);
void func_0020f530(TextWin *);
void func_0020fc58(TextWin *);


void func_0020d7d8(TextWin *a0) {
    if (func_001f42b8(a0) != 0) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0) != 0) {
                func_001f3708(a0, 6);
            }
        }
    }
    func_0020c100(a0, a0->x28);
    func_001f9438(a0, 0, 0x80, 0xE, a0->x24, 0xF, 0x801EC8C8);
    func_002079c8(a0);
}

void func_0020d890(TextWin *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->xb4 -= v;
    a0->xba += v;
    a0->xc0 += v;
    a0->x24 = a1;
}

void func_0020d900(TextWin *a0) {
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) func_001f3708(a0, 6);
        }
    }
    func_00207b38(a0, a0->x24);
}

void func_0020d990(TextWin *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->xb4 -= v;
    a0->xba += v;
    a0->xc0 += v;
    a0->x24 = a1;
}

void func_0020da00(TextWin *a0) {
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) func_001f3708(a0, 6);
        }
    }
    func_00207bb0(a0, a0->x24);
}

void func_0020da90(TextWin *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->xb4 -= v;
    a0->xba += v;
    a0->xc0 += v;
    a0->x24 = a1;
}

s32 func_0020db00(TextWin *a0, s32 slot, s32 item, s32 a3) {
    s32 id, n, i, bits, first;
    TextWin *o;
    if (slot != -1) {
        DbMember *mp = &D_00304BE8->m[D_00304BE8->x48e[slot]];
        id = mp->sub.x22[item];
    } else {
        id = item;
    }
    if (func_001ee7c8(id)) {
        a3 = 0;
        n = D_003E3D68;
    } else {
        n = 1;
    }
    first = a3;
    bits = 0;
    do {
        n--;
        bits |= func_00149600(id, D_00304BE8->x48e[a3++]);
    } while (n != 0);
    for (i = 0; i < 7; i++) {
        if ((bits >> i) & 1) {
            if (slot != -1) {
                Sub_304be8 *mq = &D_00304BE8->m[D_00304BE8->x48e[slot]].sub;
                mq->x22[item] = 0;
            } else {
                D_00304BE8->items[item]--;
            }
            func_001ef830();
            if (i < 4) func_0011d768(14);
            else func_0011d768(7);
            o = func_001f31a8(D_003F3880, 6);
            if (o) {
                func_001f3e48(o, a0);
                func_0020d890(o, i + 153);
                o->x28 = first;
            }
            return 1;
        }
    }
    func_0011d768(4);
    o = func_001f31a8(D_003F38E0, 6);
    if (o) {
        func_001f3e48(o, a0);
        func_0020da90(o, 160);
    }
    return 0;
}

void func_0020e280(TextWin *a0) {
    TextWin *p;
    TextWin *o;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_001fdfd0(a0);
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) {
                func_001f3708(a0, 6);
                if (!func_001fd538(a0)) {
                    if (D_00641228 != -1) {
                        D_00304BE8->m[D_00304BE8->x48e[D_00641228]].sub.x22[D_00641230] = 0;
                    } else {
                        D_00304BE8->items[D_00641230]--;
                    }
                    D_00641224 = 5;
                    p = func_001f4468(a0);
                    o = func_001f31a8(D_003F38B0, 6);
                    if (o) {
                        func_001f3e48(o, p);
                        func_0020d990(o, 163);
                    }
                }
            }
        }
    }
    D_003E8E08[0] = func_001ee698(D_00641234);
    func_00207c28(a0, 128);
}

void func_0020e408(TextWin *o) {
    s32 s = o->x24;
    s32 f = 0;
    s32 x;
    switch (s) {
    case 0:
        if (D_00641234) {
            if (func_001ee7f0(D_00641234)) f = 1;
        }
        break;
    case 1:
        if (D_00641234) {
            if (func_001ee9e0(D_00641234)) f = 1;
        }
        break;
    case 2:
        if (D_00641228 != -1 && D_00641234) f = 1;
        break;
    case 3:
        if (D_00641234) f = func_001ee9b8(D_00641234) != 0;
        break;
    }
    if (D_00641228 != -1) {
        x = D_003F3940[f][s];
    } else {
        x = D_003F3960[f][s];
    }
    func_001f9010(23);
    func_001f9438(o, 0, 174, 12, x, 17, 0x80c87850);
}

void func_0020eb20(TextWin *w) {
    s32 id = w->u40.v.x40;
    if (id != 0) {
        func_001f9010(0x17);
        func_001f94f0(w, 0, 0xAE, 0xC, id, 0x11, 0x80C87850);
    }
}

void func_0020eb98(void) {
    u32 i;
    s32 j;
    for (i = 0; i < D_003E3D68; i++) {
        E4BE8 *e = (E4BE8 *)((u8 *)D_00304BE8 + D_00304BE8->x48e[i] * 0x74);
        D_00641378[i] = e->n;
        for (j = 0; j < D_00641378[i]; j++) {
            D_00641278[i][j] = e->v[j];
        }
    }
}

s32 func_0020f260(s32 id) {
    return (func_001ee7a8() << 8) | id;
}

void func_0020f290(s32 *a, s32 l, s32 r) {
    s32 i, j, t;
    u32 p;
    p = func_0020f260(a[(l + r) / 2]);
    i = l;
    j = r;
    for (;;) {
        while (func_0020f260(a[i]) < p) i++;
        while (p < func_0020f260(a[j])) j--;
        if (i >= j) break;
        t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
    if (l < i - 1) func_0020f290(a, l, i - 1);
    if (j + 1 < r) func_0020f290(a, j + 1, r);
}

void func_0020f3c8(void) {
    s32 i;
    D_00641388 = 0; D_00641790 = 0;
    for (i = 1; i < 256; i++) {
        if (D_00304BE8->items[i]) {
            if (func_001eea60(i)) { D_00641390[D_00641388++] = i; }
            if (func_001eeac0(i)) { D_00641798[D_00641790++] = i; }
        }
    }
    if (D_00641388) func_0020f290(D_00641390, 0, D_00641388 - 1);
    if (D_00641790) func_0020f290(D_00641798, 0, D_00641790 - 1);
}

void func_0020fbe0(void) {
    s32 i;
    s32 n = func_001ba3d8();
    D_00641B98 = 0;
    for (i = 0; i < n; i++) {
        if (func_001ba3f0(i)) D_00641B98++;
    }
}

void func_0020fc58(TextWin *o) {
    s32 buf[192];
    s32 n, i, j, sel, fl, q, k;
    TextWin *p;
    n = func_001ba3d8();
    D_00641B98 = 0;
    for (i = 0; i < n; i++) {
        if (func_001ba3f0(i)) { buf[D_00641B98] = i; D_00641B98++; }
    }
    if (!D_00641B98) return;
    func_001fd5e0(o, D_00641B98);
    func_001fd610(o, 8);
    func_001fd688(o);
    if (func_001f42b8(o)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3758(o);
            func_0011d768(3);
            D_00641224 = 0;
        } else {
            func_001fd858(o);
            func_0020bd18(o, 8);
            D_0064126C = (s32)(o->ud0.u.xd0 << 16) >> 20;
            D_00641270 = (s32)(o->ud0.u.xd2 << 16) >> 20;
            k = buf[func_001fd548(o)];
            p = o->next;
            if (p) p->u40.v.x40 = func_001ba268(k);
            if (func_001fe570(o)) {
                func_001f3758(o);
                D_00641224 = 0;
            }
        }
    }
    i = 0;
    func_00202fc0(o);
    sel = func_001fd518(o);
    n = func_001fd618(o);
    q = func_001fd590(o);
    fl = o->x28;
    func_001f8ee0(o);
    for (; i < 9 && n < D_00641B98; i++, n++) {
        s32 b = buf[n];
        s32 a = 2;
        if (fl) a = i == sel;
        func_0020e090(o, a, 0, q, 166, b);
        q += 28;
    }
    func_001f8f30();
}

void func_0020fea0(TextWin *w) {
    u32 tab = w->x24;
    if (tab < (u32)D_003E3D68) {
        func_0020ec50(w);
        return;
    }
    if (tab == D_003E3D68) {
        func_0020f530(w);
        return;
    }
    func_0020fc58(w);
}

void func_0020fee8(TextWin *w) {
    if ((u32)D_003E3D68 < (u32)w->x24 && w->x28 != 0) {
        func_002073b0(1, w);
    }
}

void func_0020ff28(TextWin *w) {
    func_001f9010(0x17);
    D_003E8E08[0] = w->x28;
    func_001f9438(w, 0, 0xAE, 0xC, w->x24, 0x11, 0x80C87850);
}
