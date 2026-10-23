/* The synthesis menu (docs/modules.md "Session 43"), 0x002319d0-0x002327b0.
 * func_00232640(on_cursor, on_choice) opens it by itself (D_003F7E94 = 1,
 * the task func_002325f8; D_003F7E98 = 1 lets the list take input): the
 * frame D_003F7E70 (D_00647650) and the list D_003F7D60 (synth.faddr.c's
 * func_00231ea0) of the first D_00647668 = D_003F7D10[level] recipes of
 * D_003F7C48 (the item made, the first of its n ingredients in D_003F7A70
 * (id, count), and a flag: 1 can be made once).  The level is func_001ec360
 * (0-6); func_002319d0 counts the recipes made at least once (D_00647670[i],
 * D_006476F4), func_00231a80 raises the level when at most three are left
 * (to 5 and 6 only when none is).  func_00231cd0 / func_00231dd0 check a
 * recipe (D_00647660: the item, or -1 too few ingredients, -2 99 held, -3
 * made already), func_00231b98 makes it.  func_00232390 draws the chosen
 * recipe's ingredients (held / needed).  Most likely the Moogle's synthesis
 * shop; not proved by a boot. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003F7A70.h"
#include "data/pieces/D_003F7C48.h"
#include "data/pieces/D_003F7D88.h"
#include "data/types/text_00200000_s7_w19_p.h"
#include "text/textwin.h"

extern s32 D_003F7D10[];
extern s32 D_003F7E94;
extern s32 D_003F7E98;
extern u8 D_003F7D60[];
extern u8 D_003F7E70[];
extern s32 D_00647648;
extern s32 D_0064764C;
extern TextWin *D_00647650; /* src/data/bss_0064.c: s32 D_00647650 */
extern s32 D_00647654;
extern s32 D_00647658;
extern s32 D_0064765C;
extern s32 D_00647660;
extern s32 D_00647664;
extern s32 D_00647668;
extern s32 D_00647670[];
extern s32 D_006476F4;

void func_0011d768(s32);
s16 *func_0011ef10(s32, void *);
s32 func_001ec258(s32);
void func_001ec2c0(s32, s32);
s32 func_001ec360(void);
void func_001ec380(s32);
void func_001ef830(void);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f3840(void *);
void func_001f3e48(void *, void *);
s32 func_001f40c8(void);
void func_001f82b0(void);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00205b30(void *, void *);
s32 func_00207ca0(s32);
void func_00207d60(void *, s32, s32, s32, s32, s32, s32);
void func_0020b968(void);
void func_0020b998(void);
void func_0020bb90(s32, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0020dd38(void *, s32, s32, s32, s32, s32);

void func_002319d0(void) {
    s32 i;
    s32 v = func_001ec360();

    D_00647664 = v;
    D_00647668 = D_003F7D10[v];
    D_006476F4 = 0;
    for (i = 0; i < D_00647668; i++) {
        if ((D_00647670[i] = func_001ec258(i)) != 0) {
            D_006476F4++;
        }
    }
}

void func_00231a80(void) {
    s32 d = D_00647668 - D_006476F4;
    if (d < 4) {
        s32 s = D_00647664;
        if (s < 4) {
            func_001ec380(s + 1);
        } else if (s == 4) {
            if (d == 0) func_001ec380(5);
        } else if (s == 5) {
            if (d == 0) func_001ec380(6);
        }
    }
}

s32 func_00231b10(void) {
    return func_001ec360() == 6;
}

s32 func_00231b38(s32 arg0, s32 arg1) {
    W606Mem_304be8 *e = &D_00304BE8->m[arg0];
    s32 c = 0;
    s32 i;
    for (i = 0; i < e->sub.x21; i++) {
        if (e->sub.x22[i] == arg1) c++;
    }
    return c;
}

void func_00231b98(void) {
    s32 *p = &D_00647660;
    s32 *k;
    s32 *e;
    T7C48_3f7c48 *c;
    T7A70 *l;
    s32 n;
    if (*p > 0) {
        func_0011d768(18);
        k = &D_0064765C;
        e = &D_00647670[*k];
        if (*e == 0) {
            *e = 1;
            D_006476F4++;
            func_001ec2c0(*k, 1);
        }
        D_00304BE8->items[*p]++;
        c = &((T7C48_3f7c48 *)&D_003F7C48)[*k];
        n = c->n;
        l = &D_003F7A70[c->b2];
        for (; n > 0; n--) {
            D_00304BE8->items[l->id] -= (u8)l->max;
            l++;
        }
    } else {
        func_0011d768(4);
    }
}

void func_00231cd0(s32 arg0) {
    T7C48_3f7c48 *c = &((T7C48_3f7c48 *)&D_003F7C48)[D_0064765C];
    T7A70 *l;
    s32 n;
    if (c->flag == 1 && D_00647670[D_0064765C] != 0) {
        D_00647660 = -3;
        return;
    }
    n = c->n;
    l = &D_003F7A70[c->b2];
    D_00647660 = arg0;
    for (; n > 0; n--) {
        if (D_00304BE8->items[l->id] < l->max) {
            D_00647660 = -1;
            return;
        }
        l++;
    }
    if (D_00304BE8->items[D_00647660] >= 99) {
        D_00647660 = -2;
    }
}

s32 func_00231dd0(s32 k) {
    T7C48_3f7c48 *c = &((T7C48_3f7c48 *)&D_003F7C48)[k];
    T7A70 *l;
    s32 n;
    if (c->flag == 1 && D_00647670[k] != 0) {
        return -3;
    }
    n = c->n;
    l = &D_003F7A70[c->b2];
    for (; n > 0; n--) {
        if (D_00304BE8->items[l->id] < l->max) {
            return -1;
        }
        l++;
    }
    return D_00304BE8->items[c->id] < 99 ? 0 : -2;
}

void func_00232390(void *a0) {
    u32 i;
    s32 n, j, y, id, max, cnt, c, col;
    T7A70 *e;
    T7C48_3f7c48 *t;
    for (j = 0; (u32)j < 7; j++) func_00205b30(a0, &D_003F7D88[j]);
    y = 63;
    func_001fc308(a0, 11, 13, 0, 0, 61, 0, 0x80009100, 0x8027E4D4);
    func_001f9438(a0, 1, 490, 11, 426, 15, 0x4D508B2E);
    func_001f9438(a0, 0, 44, 42, 427, 15, 0x80C8C8C8);
    func_001f9438(a0, 0, 271, 42, 428, 15, 0x80C8C8C8);
    func_001f9438(a0, 1, 484, 42, 429, 15, 0x80C8C8C8);
    t = &((T7C48_3f7c48 *)&D_003F7C48)[D_0064765C];
    e = &D_003F7A70[t->b2];
    n = t->n;
    for (j = 0; j < n; j++) {
        id = e->id;
        max = e->max;
        e++;
        cnt = D_00304BE8->items[id];
        c = cnt < max ? 2 : 0;
        func_0020dd38(a0, c, 247, y, 194, id);
        col = func_00207ca0(0);
        func_001f9438(a0, 0, 400, y + 7, 85, 12, col);
        func_001fb428(a0, 0, 1, 0, 418, y + 7, max, 12, col);
        func_00207d60(a0, c, 445, y, 480, cnt, 12);
        y += 28;
    }
}

s32 func_002325f8(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    D_003F7E94 = 0;
    func_00231a80();
    return 4;
}

void func_00232640(s32 arg0, s32 arg1) {
    s32 *p = &D_003F7E94;
    if (*p == 0) {
        TextWin **q;
        TextWin *o, *a;
        func_001f3110();
        func_0020b968();
        func_0020bb90(0xE7, 0);
        func_0020bda8(0x10);
        *p = 1;
        D_003F7E98 = 1;
        func_001ef830();
        D_00647648 = arg0;
        D_0064764C = arg1;
        func_002319d0();
        a = func_001f31a8(D_003F7E70, 1);
        q = &D_00647650;
        *q = a;
        if (a != NULL) {
            o = func_001f31a8(D_003F7D60, 1);
            if (o != NULL) {
                func_001f3e48(o, *q);
                o->xcc = D_00647668;
                o->ud0.s.xd0 = D_00647654 << 4;
                o->ud0.s.xd2 = D_00647658 << 4;
            }
        }
        do {
            func_0011ef10(0x2BF84, func_002325f8);
        } while (0);
    }
}

void func_00232758(void) {
    func_001f3840(D_00647650);
    func_0020be10(0x10);
}

void func_00232780(void) {
    D_003F7E94 = 0;
}

void func_00232790(void) {
    D_003F7E94 = 0;
    D_00647654 = 0;
    D_00647658 = 0;
}
