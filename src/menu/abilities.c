/* The abilities page of the menu (docs/modules.md "Session 40"),
 * 0x00213d80-0x00216180: page 2 of the top menu (message 0x6b; its open
 * function is func_002160a8, set up func_00216118, reset func_00216140).
 * Its windows are opened from the descriptors D_003F3DF0 ... D_003F3FF0.
 * The member list (func_00215420) picks a member (D_00642C58 the cursor,
 * D_00642C28 the party slot or -1 for the shared abilities, D_00642C2C the
 * member, D_00642C30 its Sub_304be8) or, below the members, the shared list
 * D_00304BE8->list599 (D_00642C88 entries).  A member's abilities are the
 * bytes of Sub_304be8 +0x40 (`name` in D_00304BE8_s.h; D_00642C78[slot] of
 * them); bit 0x80 of an entry means it is equipped.  func_00214b20 /
 * func_00214fc8 are the two lists, func_002145d8 the window that equips,
 * removes or moves the chosen one (D_00642C34 / D_00642C3C, moved to
 * D_00642C4C / D_00642C54), func_00213e50 sorts a list by one of the keys
 * D_003F3DE0 (func_00213d80, func_00213db8 by AP, func_00213e18),
 * func_002148d0 shows the AP left (func_001ef720) and the total
 * (func_001ef658).  D_00642C24 is the page state.  Most likely the abilities
 * page (entries cost AP: func_001ef5c0); not proved by a boot.
 *
 * Window views: TextWin (include/text/textwin.h) where the types agree.
 * AbWin and WinP24 stay: their functions read +0xd0 / +0xd2 as plain s16,
 * and TextWin's +0xd0 is a union (a union access reorders); WinP24's +0x24 is
 * a pointer (as s32 the store moves: the alias set changes). */
#include "common.h"
#include "text/textwin.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E8E08.h"

typedef struct AbWin { u8 pad[0x10]; struct AbWin *x10; u8 p14[0x10]; s32 x24; s32 x28; u8 p2c[0xCE - 0x2C]; s16 xce; s16 xd0; s16 xd2; } AbWin;
typedef struct WinP24 {
    u8 pad0[0x24]; struct WinP24 *x24; s32 x28; u8 pad2c[0xB4 - 0x2C]; s32 xB4; u16 pB8; s16 xBA;
    u8 padBC[0xCC - 0xBC]; s16 xCC; s16 xCE; s16 xD0; s16 xD2;
} WinP24;
typedef u32 (*KF3de0)(s32);

extern u8 D_003F3DF0[], D_003F3E30[], D_003F3E60[], D_003F3E90[], D_003F3ED0[], D_003F3F00[];
extern u8 D_003F3F30[], D_003F3F60[], D_003F3F90[], D_003F3FC0[], D_003F3FF0[];
extern s32 D_003F3E18[], D_003F3EB8[];
extern void *D_00642C20;
extern s32 D_00642C24, D_00642C28, D_00642C2C;
extern Sub_304be8 *D_00642C30;
extern s32 D_00642C34, D_00642C38, D_00642C40, D_00642C4C, D_00642C50;
extern u32 D_00642C58;
extern s32 D_00642C5C, D_00642C60, D_00642C64, D_00642C68, D_00642C6C, D_00642C70;
extern s32 D_00642C78[];
extern s32 D_00642C88;

void func_0011d768(s32);
s32 func_001ee5f0(s32);
s32 func_001ef580(s32);
s32 func_001ef5c0(s32);
s32 func_001ef5f8(s32);
s32 func_001ef658(s32);
s32 func_001ef720(s32);
void func_001ef830(void);
s32 func_001efbb8(s32);
s32 func_001efd98(s32);
void *func_001f31a8(void *, s32);
void func_001f36b8(void *);
void func_001f3708(void *, s32);
s32 func_001f3758(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
void func_001f40a0(void *, s32);
s32 func_001f42b8(void *);
void *func_001f4468(void *);
void func_001f8ee0(void *);
void func_001f8f30(void);
void func_001f9010(s32);
s32 func_001f92b0(void *, s32, s32, s32, s32, s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd548(void *);
s32 func_001fd590(void *);
void func_001fd5e0(void *, s32);
void func_001fd610(void *, s32);
s32 func_001fd618(void *);
void func_001fd688(void *);
void func_001fd858(void *);
void func_001fe158(void *);
s32 func_001fe570(void *);
s32 func_001fe5a0(void *);
void func_00202fc0(void *);
void func_00206690(void *, s32, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);
void func_00207bb0(void *, s32);
void func_00209340(void *, s32, s32 *);
void func_0020bd18(void *, s32);
void func_00214130(void *, s32, s32, s32, s32, s32);
void func_00214290(void *, s32, s32, s32, s32, s32);
void func_00214a68(void);
void func_00214f50(void);

s32 func_00213d80(s32 arg0) {
    return (func_001ef5f8(arg0 & ~0x80) << 0x10) | (arg0 & 0x80);
}

s32 func_00213db8(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s0 = arg0 & ~0x80;
    temp_s1 = func_001ef5c0(temp_s0);
    return (temp_s1 << 0x18) | (func_001ef5f8(temp_s0) << 8) | (arg0 & 0x80);
}

s32 func_00213e18(s32 arg0) {
    return ((arg0 & 0x80) << 0x10) | func_001ef5f8(arg0 & ~0x80);
}

/* The sort keys of func_00213e50 (D_00642C48 picks one). */
KF3de0 D_003F3DE0[0x4] ALIGNED(16) = {
    (void *)func_00213d80, (void *)func_00213db8, (void *)func_00213e18, 0,
};

void func_00213e50(u8 *a, s32 lo, s32 hi, s32 k) {
    s32 i, j;
    u32 p;
    u8 t;
    i = lo;
    j = hi;
    p = D_003F3DE0[k](a[(lo + hi) / 2]);
    for (;;) {
        while (D_003F3DE0[k](a[i]) < p) i++;
        while (p < D_003F3DE0[k](a[j])) j--;
        if (i >= j) break;
        t = a[i]; a[i++] = a[j]; a[j--] = t;
    }
    if (lo < i - 1) func_00213e50(a, lo, i - 1, k);
    if (j + 1 < hi) func_00213e50(a, j + 1, hi, k);
}

void func_00213fb0(void) {
    if (D_00642C28 >= 0) {
        func_00213e50(D_00642C30->name, 0, D_00642C78[D_00642C28] - 1, D_00642C48);
        return;
    }
    func_00213e50(D_00304BE8->list599, 0, D_00642C88 - 1, D_00642C48);
}

void func_00214030(TextWin *a0) {
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) func_001f3708(a0, 6);
        }
    }
    func_00207bb0(a0, a0->x24);
}

void func_002140c0(TextWin *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->xb4 -= v;
    a0->xba += v;
    a0->xc0 += v;
    a0->x24 = a1;
}

/* func_00214130 and func_00214290 (the rows) are in abilities.n32.c. */

void func_00214380(TextWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, D_003F3E18[D_00642C70], 0x11, 0x80C87850);
}

void func_00214590(TextWin *arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, arg0->x24, 0x11, 0x80C87850);
}

/* func_002143e0 (the sort window) is in abilities.nostrict.c. */

void func_002145d8(TextWin *a) {
    s32 buf[3];
    s32 f, v;
    TextWin *o, *p;
    f = *(u32 *)&D_00642C3C & 0x80;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            D_00642C24 = 1;
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            v = func_001fd518(a);
            D_00642C6C = v;
            if ((p = a->next)) {
                if (v == 0) p->x24 = f ? 181 : 184;
                else p->x24 = D_003F3EB8[v];
            }
            if (func_001fe5a0(a)) {
                func_001f3d58(a, 5);
                p = func_001f4468(a);
                D_00642C44 = D_00642C6C;
                switch (D_00642C6C) {
                case 0:
                    func_001f3758(a);
                    if (D_00642C28 != -1) {
                        if (!f) {
                            func_0011d768(75);
                            D_00642C30->name[D_00642C34] |= 0x80;
                            D_00642C24 = 5;
                        } else if (D_00642C40 == 0) {
                            func_0011d768(5);
                            D_00642C30->name[D_00642C34] &= 0x7f;
                            D_00642C24 = 5;
                        } else {
                            func_0011d768(4);
                            if ((o = func_001f31a8(D_003F3DF0, 6))) {
                                func_001f3e90(p, o);
                                func_001f3e20(o, p);
                                func_002140c0(o, 202);
                            }
                        }
                    } else {
                        if (!f) func_0011d768(75);
                        else func_0011d768(5);
                        D_00304BE8->list599[D_00642C34] ^= 0x80;
                        D_00642C24 = 5;
                    }
                    break;
                case 1:
                    func_001f3758(a);
                    func_0011d768(2);
                    D_00642C24 = 4;
                    break;
                case 2:
                    func_001f3758(a);
                    func_0011d768(2);
                    D_00642C24 = 3;
                    break;
                }
            }
        }
    }
    buf[0] = f ? 185 : 186;
    buf[1] = 187;
    buf[2] = 188;
    func_00209340(a, 2, buf);
}

void func_002148d0(TextWin *arg0) {
    s32 temp_s0;

    func_001f92b0(arg0, 0, 0x10, func_001ee5f0(D_00642C2C), 0xF, 0x801EC8C8);
    func_001f9438(arg0, 0, 0x10, 0x22, 0x51, 0xE, 0x80E6E6E6);
    temp_s0 = func_001f9438(arg0, 0, func_001fb428(arg0, 0, 0, 0, 0x10, 0x36, func_001ef720(D_00642C2C), 0xE, 0x806464EC) + 2, 0x36, 0x54, 0xE, 0x596464EC);
    func_001fb428(arg0, 0, 0, 0, temp_s0 + 2, 0x36, func_001ef658(D_00642C2C), 0xE, 0x596464EC);
}

void func_002149f0(TextWin *arg0) {
    s32 temp_s1;

    temp_s1 = arg0->x24;
    if (temp_s1 != 0) {
        func_001f9010(0x17);
        func_001f94f0(arg0, 0, 0xAE, 0xC, temp_s1, 0x11, 0x80C87850);
    }
}

/* func_00214a68 (counts the abilities of the members) is in abilities.nosi.c. */

void func_00214b20(AbWin *a) {
    AbWin *o[2];
    s32 n;
    Sub_304be8 *sub;
    s32 money;
    s32 k, m, lim, idx, it, id, sel, i, j, y, c, fl;
    AbWin *p;
    k = a->x24;
    n = D_00642C78[k];
    k = D_00304BE8->x48e[k];
    sub = &D_00304BE8->m[k].sub;
    if (n == 0) return;
    if (D_00642C24 < 3) {
        m = 0;
        lim = 8;
    } else {
        m = 1;
        lim = 7;
    }
    func_001fd5e0(a, n);
    func_001fd610(a, lim);
    func_001fd688(a);
    money = func_001ef720(k);
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            if (!m) D_00642C24 = 0;
            else D_00642C24 = 2;
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            D_00642C5C = a->xd0 >> 4;
            D_00642C60 = a->xd2 >> 4;
            idx = func_001fd548(a);
            it = sub->name[idx];
            id = it & 0x7f;
            if ((p = a->x10)) p->x24 = func_001ef580(id);
            if (func_001fe5a0(a)) {
                p = func_001f4468(a);
                func_001f3d58(a, 5);
                func_001f3758(a);
                if (!m) {
                    func_0011d768(2);
                    D_00642C34 = idx;
                    D_00642C38 = id;
                    D_00642C3C = it;
                    D_00642C40 = 0;
                    if (money < func_001ef5c0(id)) D_00642C40 = 1;
                    D_00642C24 = 2;
                    if ((o[0] = func_001f31a8(D_003F3ED0, 6))) {
                        func_001f3e90(p, o[0]);
                        func_001f3e20(o[0], p);
                        o[0]->xd2 = *(u16 *)&D_00642C6C << 4;
                        if ((o[1] = func_001f31a8(D_003F3E90, 6))) {
                            func_001f3e90(o[0], o[1]);
                            func_001f3e20(o[1], o[0]);
                            func_001f3dc0(o[0]);
                        }
                    }
                } else {
                    func_0011d768(74);
                    D_00642C4C = idx;
                    D_00642C54 = it;
                    D_00642C50 = id;
                    D_00642C24 = 5;
                    sub->name[D_00642C34] = *(u8 *)&D_00642C54;
                    sub->name[D_00642C4C] = *(u8 *)&D_00642C3C;
                }
            }
        }
    }
    func_00202fc0(a);
    sel = func_001fd518(a);
    i = func_001fd618(a);
    y = func_001fd590(a);
    fl = a->x28;
    lim = a->xce + 1;
    func_001f8ee0(a);
    for (j = 0; j < lim && i < n; j++, i++) {
        idx = sub->name[i];
        func_00214290(a, !fl ? 2 : !(idx & 0x80) ? j == sel : money < func_001ef5c0(idx & ~0x80) ? (j == sel ? 3 : 2) : j == sel, 0, y, 166, idx);
        y += 28;
    }
    func_001f8f30();
}

/* func_00214f50 (counts the shared abilities) is in abilities.nogcse.c. */

void func_00214fc8(AbWin *a) {
    AbWin *o[2];
    s32 m, lim, idx, it, id, sel, i, j, y, fl;
    AbWin *p;
    if (D_00642C88 == 0) return;
    if (D_00642C24 < 3) {
        m = 0;
        lim = 8;
    } else {
        m = 1;
        lim = 7;
    }
    func_001fd5e0(a, D_00642C88);
    func_001fd610(a, lim);
    func_001fd688(a);
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            if (!m) D_00642C24 = 0;
            else D_00642C24 = 2;
        } else {
            Save_304be8 **b = &D_00304BE8;
            func_001fe158(a);
            func_0020bd18(a, 8);
            D_00642C64 = a->xd0 >> 4;
            D_00642C68 = a->xd2 >> 4;
            idx = func_001fd548(a);
            it = (*b)->list599[idx];
            id = it & 0x7f;
            if ((p = a->x10)) p->x24 = func_001ef580(id);
            if (func_001fe5a0(a)) {
                p = func_001f4468(a);
                func_001f3d58(a, 5);
                func_001f3758(a);
                if (!m) {
                    func_0011d768(2);
                    D_00642C34 = idx;
                    D_00642C38 = id;
                    D_00642C3C = it;
                    D_00642C40 = 0;
                    D_00642C24 = 2;
                    if ((o[0] = func_001f31a8(D_003F3ED0, 6))) {
                        func_001f3e90(p, o[0]);
                        func_001f3e20(o[0], p);
                        o[0]->xd2 = *(u16 *)&D_00642C6C << 4;
                        if ((o[1] = func_001f31a8(D_003F3E90, 6))) {
                            func_001f3e90(o[0], o[1]);
                            func_001f3e20(o[1], o[0]);
                            func_001f3dc0(o[0]);
                        }
                    }
                } else {
                    func_0011d768(74);
                    D_00642C4C = idx;
                    D_00642C54 = it;
                    D_00642C50 = id;
                    D_00642C24 = 5;
                    (*b)->list599[D_00642C34] = *(u8 *)&D_00642C54;
                    (*b)->list599[D_00642C4C] = *(u8 *)&D_00642C3C;
                }
            }
        }
    }
    func_00202fc0(a);
    sel = func_001fd518(a);
    i = func_001fd618(a);
    y = func_001fd590(a);
    fl = a->x28;
    lim = a->xce + 1;
    func_001f8ee0(a);
    for (j = 0; j < lim && i < D_00642C88; j++, i++) {
        s32 c = 2;
        idx = D_00304BE8->list599[i];
        if (fl) c = j == sel;
        func_00214130(a, c, 0, y, 166, idx);
        y += 28;
    }
    func_001f8f30();
}

void func_00215358(AbWin *arg0) {
    if (arg0->x24 != D_003E3D68) {
        func_00214b20(arg0);
        return;
    }
    func_00214fc8(arg0);
}

void func_00215388(TextWin *arg0) {
    s32 var_s0;

    func_001f9010(0x17);
    var_s0 = 0xBD;
    if (D_00642C58 != 0) {
        var_s0 = 0xBF;
        if ((u32) D_00642C58 < (u32) D_003E3D68) {
            var_s0 = 0xBE;
            D_003E8E08[0] = func_001ee5f0(D_00304BE8->x48e[D_00642C58]);
        }
    }
    func_001f9438(arg0, 0, 0xAE, 0xC, var_s0, 0x11, 0x80C87850);
}

void func_00215420(AbWin *a) {
    AbWin *q[2];
    AbWin *o;
    u32 v, i;
    s32 sel, y, c, k;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00642C20);
            func_0011d768(3);
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            v = func_001fd518(a);
            D_00642C58 = v;
            if ((o = a->x10) && (o = o->x10)) {
                o->x24 = v;
                if (v < D_003E3D68) {
                    o->xd0 = D_00642C5C << 4;
                    o->xd2 = D_00642C60 << 4;
                } else {
                    o->xd0 = D_00642C64 << 4;
                    o->xd2 = D_00642C68 << 4;
                }
            }
            if (func_001fe5a0(a)) {
                if (D_00642C58 < D_003E3D68) {
                    if (D_00642C78[D_00642C58]) {
                        func_0011d768(2);
                        D_00642C28 = D_00642C58;
                        k = D_00304BE8->x48e[D_00642C28];
                        D_00642C2C = k;
                        D_00642C30 = &D_00304BE8->m[k].sub;
                        D_00642C24 = 1;
                        func_001f3708(a, 5);
                        if ((o = a->x10)) {
                            func_001f36b8(o);
                            if ((o = o->x10)) {
                                o->x28 = 1;
                                if ((q[0] = func_001f31a8(D_003F3F30, 6))) {
                                    func_001f3e90(o, q[0]);
                                    func_001f3e20(q[0], o);
                                    if ((q[1] = func_001f31a8(D_003F3F00, 6))) {
                                        func_001f3e90(q[0], q[1]);
                                        func_001f3e20(q[1], q[0]);
                                    }
                                }
                                func_001f3dc0(o);
                            }
                        }
                    } else {
                        func_0011d768(4);
                    }
                } else if (D_00642C88) {
                    D_00642C28 = -1;
                    func_0011d768(2);
                    D_00642C24 = 1;
                    func_001f3708(a, 5);
                    if ((o = a->x10)) {
                        func_001f36b8(o);
                        if ((o = o->x10)) {
                            o->x28 = 1;
                            if ((q[0] = func_001f31a8(D_003F3F30, 6))) {
                                func_001f3e90(o, q[0]);
                                func_001f3e20(q[0], o);
                                func_001f40a0(o, 0x60000000);
                            }
                            func_001f3dc0(o);
                        }
                    }
                } else {
                    func_0011d768(4);
                }
            }
        }
    }
    sel = func_001fd518(a);
    y = 0;
    for (i = 0; i < D_003E3D68; i++) {
        if (D_00642C78[i]) c = i == sel;
        else c = i == sel ? 3 : 2;
        func_00207870(a, c, 0, 0, y, 122, func_001ee5f0(D_00304BE8->x48e[i]));
        y += 28;
    }
    if (D_00642C88) c = D_003E3D68 == sel;
    else c = D_003E3D68 == sel ? 3 : 2;
    func_00207830(a, c, 0, 0, y, 122, 192);
}

void func_00215838(void *a0) {
    WinP24 *w[3];
    s32 t; s32 t2;
    u16 h;
    if (func_001f42b8(a0)) {
        switch ((u32)D_00642C24) {
        case 0:
            if ((w[0] = func_001f31a8(D_003F3FC0, 6)) != 0) {
                func_001f3e90(a0, w[0]);
                func_001f3e20(w[0], a0);
                t2 = D_003E3D68 + 1;
                w[0]->xD2 = (u16)D_00642C58 * 16;
                w[0]->xCE = t2;
                w[0]->xCC = t2;
                w[0]->xBA = t2 * 448 - 32;
                if ((w[1] = func_001f31a8(D_003F3F90, 6)) != 0) {
                    func_001f3e90(w[0], w[1]);
                    func_001f3e20(w[1], w[0]);
                    if ((w[2] = func_001f31a8(D_003F3F60, 6)) != 0) {
                        func_001f3e90(w[1], w[2]);
                        func_001f3e20(w[2], w[1]);
                        if (D_00642C58 < D_003E3D68) {
                            w[2]->xD0 = (u16)D_00642C5C * 16;
                            w[2]->xD2 = (u16)D_00642C60 * 16;
                        } else {
                            w[2]->xD0 = (u16)D_00642C64 * 16;
                            w[2]->xD2 = (u16)D_00642C68 * 16;
                        }
                        w[2]->x24 = (void*)D_00642C58;
                        func_001f3dc0(w[0]);
                    }
                }
            }
            break;
        case 1:
        case 4:
        l1:
            if ((w[0] = func_001f31a8(D_003F3F60, 6)) != 0) {
                func_001f3e90(a0, w[0]);
                func_001f3e20(w[0], a0);
                if (D_00642C58 < D_003E3D68) {
                    w[0]->xD0 = (u16)D_00642C5C * 16;
                    w[0]->xD2 = (u16)D_00642C60 * 16;
                } else {
                    w[0]->xD0 = (u16)D_00642C64 * 16;
                    w[0]->xD2 = (u16)D_00642C68 * 16;
                }
                if (D_00642C24 == 4) {
                    w[0]->xB4 += 448;
                    w[0]->xBA -= 448;
                }
                w[0]->x24 = (void*)D_00642C58;
                w[0]->x28 = 1;
                if ((w[1] = func_001f31a8(D_003F3F30, 6)) != 0) {
                    func_001f3e90(w[0], w[1]);
                    func_001f3e20(w[1], w[0]);
                    if (D_00642C58 < D_003E3D68) {
                        if ((w[2] = func_001f31a8(D_003F3F00, 6)) != 0) {
                            func_001f3e90(w[1], w[2]);
                            func_001f3e20(w[2], w[1]);
                        }
                    }
                    func_001f3dc0(w[0]);
                }
            }
            break;
        case 2:
            if ((w[0] = func_001f31a8(D_003F3ED0, 6)) != 0) {
                func_001f3e90(a0, w[0]);
                func_001f3e20(w[0], a0);
                w[0]->xD2 = (u16)D_00642C6C * 16;
                if ((w[1] = func_001f31a8(D_003F3E90, 6)) != 0) {
                    func_001f3e90(w[0], w[1]);
                    func_001f3e20(w[1], w[0]);
                    func_001f3dc0(w[0]);
                }
            }
            break;
        case 3:
            if ((w[0] = func_001f31a8(D_003F3E60, 6)) != 0) {
                func_001f3e90(a0, w[0]);
                func_001f3e20(w[0], a0);
                w[0]->xD2 = (u16)D_00642C70 * 16;
                if ((w[1] = func_001f31a8(D_003F3E30, 6)) != 0) {
                    func_001f3e90(w[0], w[1]);
                    func_001f3e20(w[1], w[0]);
                    func_001f3dc0(w[0]);
                }
            }
            break;
        case 5:
            func_001ef830();
            D_00642C24 = 1;
            goto l1;
        }
    }
    switch (D_00642C24) {
    case 0:
        break;
    case 1:
        func_00206690(a0, 0, 83, 11);
        func_00207870(a0, 11, 0, 11, 71, 122, D_00642C28 >= 0 ? func_001ee5f0(D_00642C2C) : func_001efbb8(192));
        break;
    case 2:
        func_00206690(a0, 0, 83, 11);
        func_00207870(a0, 11, 0, 11, 71, 122, D_00642C28 >= 0 ? func_001ee5f0(D_00642C2C) : func_001efbb8(192));
        func_00206690(a0, 133, 83, 26);
        func_00214130(a0, 11, 159, 71, 166, D_00642C3C);
        break;
    case 3:
    case 4:
        func_00206690(a0, 0, 83, 11);
        func_00207870(a0, 11, 0, 11, 71, 122, D_00642C28 >= 0 ? func_001ee5f0(D_00642C2C) : func_001efbb8(192));
        func_00206690(a0, 133, 83, 26);
        func_00214130(a0, 11, 159, 71, 166, D_00642C3C);
        func_00206690(a0, 325, 83, 26);
        switch (D_00642C44) {
        case 1: t = 187; break;
        case 0: t = (D_00642C3C & 0x80) ? 185 : 186; break;
        case 2: default: t = 188; break;
        }
        func_00207830(a0, 11, 2, 351, 71, 122, t);
        func_00206690(a0, 473, 83, 39);
        break;
    case 5:
        func_00206690(a0, 0, 83, 11);
        func_00207870(a0, 11, 0, 11, 71, 122, D_00642C28 >= 0 ? func_001ee5f0(D_00642C2C) : func_001efbb8(192));
        func_00206690(a0, 133, 83, 26);
        func_00214130(a0, 11, 159, 71, 166, D_00642C3C);
        func_00206690(a0, 325, 83, 26);
        switch (D_00642C44) {
        case 1: t = 187; break;
        case 0: t = (D_00642C3C & 0x80) ? 185 : 186; break;
        case 2: default: t = 188; break;
        }
        func_00207830(a0, 11, 2, 351, 71, 122, t);
        func_00206690(a0, 473, 83, 39);
        switch (D_00642C44) {
        case 1:
            func_00206690(a0, 0, 111, 159);
            func_00214130(a0, 11, 159, 99, 166, D_00642C54);
            func_00206690(a0, 325, 111, 187);
            break;
        case 0:
            break;
        case 2:
        default:
            func_00206690(a0, 0, 111, 11);
            switch (D_00642C48) {
            case 1: t = 194; break;
            case 0: t = 193; break;
            case 2: default: t = 195; break;
            }
            func_00207830(a0, 11, 2, 11, 99, 122, t);
            func_00206690(a0, 133, 111, 379);
            break;
        }
        break;
    }
}

void func_00216078(TextWin *arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x6B);
}

void func_002160a8(TextWin *arg0) {
    TextWin *temp_v0;

    temp_v0 = func_001f31a8(D_003F3FF0, 0);
    if (temp_v0 != 0) {
        func_001f3e90(arg0, temp_v0);
        func_001f3e20(temp_v0, arg0);
    }
    D_00642C20 = arg0;
    D_00642C24 = 0;
    func_00214a68();
    func_00214f50();
}

void func_00216118(void) {
    if ((u32) D_003E3D68 < (u32) D_00642C58) {
        D_00642C58 = D_003E3D68;
    }
}

void func_00216140(void) {
    D_00642C58 = 0;
    D_00642C5C = 0;
    D_00642C60 = 0;
    D_00642C64 = 0;
    D_00642C68 = 0;
    D_00642C6C = 0;
    D_00642C70 = 0;
}
